// !! 03 同步并发操作

// !! 条件变量 (condition variable)

在并发编程中, 一种常见的需求是: 一个线程等待另一个线程完成某个事件后, 再继续执行任务。对于这种情况, 标准库提供了 std::condition_variable

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

class A{
public:
  void step1(){
      {
          std::lock_guard<std::mutex> l(m_);
          step1_done = true;
      }
      std::cout << "step1 done" << std::end;
      cv.notify_one();
  }

  void step2(){
      std::unique_lock<std::mutex> l(m_);
      cv.wait(l, [this]{ return step1_done; });
      step2_done = true;
      std::cout << "step2 done" << std::endl;
      cv.notify_one();
  }

  void step3(){
      std::unique_lock<std::mutex> l(m_);
      cv.wait(l, [this]{ return step2_done; });
      std::cout << "step3 done" << std::endl;
  }
private:
 std::mutex m_;
 std::condition_variable cv;
 bool step1_done = false;
 bool step2_done = false;
};

int main(){
    A a;
    std::thread t1{&A::step1, &a};
    std::thread t2{&A::step2, &a};
    std::thread t3{&A::step3, &a};

    t1.join();
    t2.join();
    t3.join();
    return 0;
}


有多个能唤醒的任务时, notify_one() 会随机唤醒一个

#include <condition_variable>
#include <thread>
#include <mutex>
#include <iostream>

class A{
public:
  void wait1(){
      std::unique_lock<std::mutex> l(m_);
      cv.wait(l, [this]{return done;});
      std::cout << "1";
  }

  void wait2(){
      std::unique_lock<std::mutex> l(m_);
      cv.wait(l, [this]{return done;});
      std::cout << "2";
  }

  void signal(){
      {
          std::lock_guard<std::mutex> l(m_);
          done = true;
      }
      cv.notify_all();
  }
private:
  std::mutex m_;
  std::condition_variable cv;
  bool done = false;
};

int main(int argc, char* argv[]){
    A a;

    std::thread t1{&A::wait1, &a};
    std::thread t2{&A::wait2, &a};
    std::thread t3{&A::signal, &a};

    t1.join();
    t2.join();
    t3.join();
    return 0;
}// 12 or 21


std::condition_variable 只能与 std::unique_lock 协作, 为此标准库提供了更通用的 std::condition_variable_any

#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>

class Mutex{
public:
  void lock();
  void unlock();
};

class A{
public:
  void signal(){
      std::cout << "1";
      cv.notify_one();
  }

  void wait(){
      Mutex m_;
      cv.wait(m);
      std::cout << "2";
  }
private:
  std::condition_variable_any cv;  
};

int main(int argc, char* argv[]){
    A a;

    std::thread t1{&A::wait, &a};
    std::thread t2{&A::signal, &a};

    t1.join();
    t2.join();
    return 0;
}


与 std::stack 一样, std::queue 的 front 和 pop 存在 race condition, 为此将 front 和 pop 合并成 try_pop 函数, 此外利用 
std::condition_variable 实现 wait_and_pop 的接口, 当没有元素可弹出时会阻塞, 直至有元素可弹出

#include<condition_variable>
#include <memory>
#include <mutex>
#include <queue>

template<typename t>
class ConcurrentQueue{
public:
  ConcurrentQueue() = default;
  ConcurrentQueue(const ConcurrentQueue &rhs){
      std::lock_guard<std::mutex> lock(rhs.m_);
      q_ = rhs.q_;
  }

  void push(T& x) {
      std::lock_guard<std::mutex> lock(m_);
      q_.push(std::move(x));
      cv_.notify_one();
  }

  std::shared_ptr<T>  wait_and_pop(T& res) {
      std::unique_lock<std::mutex> l(m_);
      cv_.wait(l, [this]{return !q.empty();});
      auto res = std::make_shared<T>(std::move(q_.front()));
      q_.pop();
      return res;
  }

  bool try_pop(T& res) {
      std::lock_guard<std::mutex> l(m_);
      if(q_.empty()) {
          return false;
      }
      res = std::move(q_.front());
      q_.pop();
      return true;
  }

  std::shared_ptr<T> try_pop(){
      std::lock_guard<std::mutex> l(m_);
      if(q_.empty()) {
          return nullptr;
      }
      auto res = std::make_shared<T>(std::move(q_.front()));
      q_.pop();
      return res;
  }

  bool empty() const{
      std::lock_guard<std::mutex> l(m_);
      return q_.empty();
  }

private:
  std::mutex m_;
  std::condition_variable cv_;
  std::queue<T> q_;
};


这个实现有一个异常安全问题, notify_one() 只会唤醒一个线程, 如果多线程等待时, 被唤醒线程 wait_and_pop 中抛出异常(如构造 std::shared_ptr 对象时可能抛异
常), 其余线程将永远不被唤醒。用 notify_all() 可解决此问题, 但会有不必要的唤醒, 抛出异常时再调用 notify_one() 更好一些。对于此场景, 最好的做法是将内部的
std::queue<T> 改为 std::queue<std::shared_ptr<T>>, std::shared_ptr 对象只在 push 中构造, 这样 wait_and_pop 就不会抛异常。

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <utility>

template<typename T>
class ConcurrentQueue{
public:
  ConcurrentQueue() = default;
  ConcurrentQueue(const ConcurrentQueue & rhs){
      std::lock_guard<std::mutex> l(m_);
      q_ = rhs.q_;
  }

  void push(T& x) {
    auto data = std::make_shared<T>(std::move(x));
    std::lock_guard<std::mutex> l(m_);
    q_.push(data);
    cv_.notify_one();
  }


  void wait_and_pop(T& res){
      std::unique_lock<std::mutex> l(m_);
      cv_.wait(l, [this]{return !q.empty();});
      res = std::move(*q_.front())
      q_.pop();
  }

  std::shared_ptr<T> wait_and_pop(){
      std::unique_lock<std::mutex> l(m_);
      cv_.wait(l, [this]{return !q.empty();});
      auto res = q_.front();
      q_.pop();
      return res;
  }


  bool try_pop(T& res){
      std::lock_guard<std::mutex> l(m_);
      if(q_.empty()){
          return false;
      }
      res = std::move(*q_.front());
      q_.pop();
      return true;
  }

  std::shared_ptr<T> try_pop(){
      std::lock_guard<std::mutex> l(m_);
      if(q_.empty()){
          return nullptr;
      }
      auto res = std::move(*q_.front());
      q_.pop();
      return res;
  }


  bool empty() const {
      std::lock_guard<std::mutex> l(m_);
      return q_.empty();
  }

private:
  std::mutex m_;
  std::condition_variable cv_;
  std::queue<T> q_;
};

// !! 信号量 (semaphore)


