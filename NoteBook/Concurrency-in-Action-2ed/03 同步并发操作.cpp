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

'信号量用于实现多线程之间指定数量的事件通知',P 操作对信号量减 1, V 操作对信号量加 1, 若 P 操作将导致信号量小于 0 则阻塞,直至可减少信号量为止。C++20 提供了 
std::counting_semaphore, 构造时通过模板参数设置信号量的最大值, 通过函数参数设置信号量的初始值, acquire() 即 P 操作, 会在信号量值不小于 0 时将信号量减 1,
否则阻塞至可以减 1 为止, release() 即 V 操作, 会将信号量加上指定值(不指定则加 1)并唤醒指定数量的被 acquire() 阻塞的信号量。

#include <iostream>
#include <semaphore>
#include <thread>

class A{
public:
  void wait1(){
      sem_.acquire();
      std::cout << "1";
  }

  void wait2(){
      sem_.acquire();
      std::cout << "2";
  }

  void signal(){
      sem_.release(2);
  }

private:
  std::count_semaphore<2> sem_(0);// 初始值 0，最大值 2
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
}

std::binary_semaphore 是最大值为 1 的信号量, 它是模板参数为 1 的 std::counting_semaphore 的别名

#include <iostream>
#include <thread>
#include <semaphore>

class A{
public:
  void wait1(){
      sem_.acquire();
      std::cout << "1";
  }

  void wait2(){
      sem_.acquire();
      std::cout << "2";
  }

  void signal(){
      sem_.release(2);
      std::cout << "3"
  };
private:
  std::binary_semaphore sem_(0);
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
}


// !! 屏障 (barrier)

'C++20 提供了 std::barrier, 它用一个值作为要等待的线程的数量来构造, 调用 std::barrier::arrive_and_wait 会阻塞至所有线程完成任务'(因此称为屏障), 当最
后一个线程完成任务时, 所有线程被释放, barrier 被重置。构造 std::barrier 时可以额外设置一个 noexcept 函数, 当所有线程到达阻塞点时, 由其中一个线程运行该函数。
如果想从线程集中移除线程, 则在该线程中对 barrier 调用 std::barrier::arrive_and_drop。

#include <barrier>
#include <cassert>
#include <iostream>
#include <thread>

class A{
public:
  void f(){
      std::barrier sync_point{3, []() noexcept{++i_};};
      for(auto x : tasks_){
          x = std::thread([&]{
              std::cout << 1;
              sync_point.arrive_and_wait();
              assert(i_ == 1);
              std::cout <<2;
              sync_point.arrive_and_wait();
              assert(i_ == 2);
              std::cout <<3;
          };);
      }
      for(auto& x : tasks_){
          x.join();// 析构 barrier 前 join 所有使用了 barrier 的线程
      }// 析构 barrier 时, 线程再调用 barrier 的成员函数是 undefined behavior
  }
private:
  std::thread tasks_[] = {};
  int i_ = 0;
};


int main(int argc, char* argv[]){
    A a;
    a.f();
    return 0;
}

C++ 20 提供了 std::latch 作为一次性屏障, 它用一个值作为计数器的初始值来构造,
    std::latch::count_down 将计数器减 1, std::latch::wait 将阻塞至计数器为 0,
    如果想让计数器减一并阻塞至为 0 则可以调用 std::latch::arrive_and_wait。
#include <iostream>
#include <latch>
#include <string>
#include <thread>

class A {
 public:
  void f() {
    for (auto& x : data_) {
      x.t = std::jthread([&]() {
        x.s += x.s;
        done_.count_down();
      };);
    }
    done_.wait();
    for (auto& x : data_) {
      std::cout << x.s << std::endl;
    }
  }

 private:
  struct {
    std::string s;
    std::jthread t;
  } data_[3] = {{"a"}, {"b"}, {"c"}};
  std::latch done_(3);
};

int main(int argc, char* argv[]){
    A a;
    a.f();
    return 0;
}


// !! 期值 (future)

std::thread 只能运行函数, 无法获取函数的返回值, 为此'标准库提供了 std::future 来关联线程运行的函数和函数的返回结果, 这种获取结果的方式是异步的'。通过 
std::async() 创建异步任务的 std::future, std::async 的创建任务的传参方式和 std::thread 一样。

#include <future>
#include <thread>

class A{
public:
  int f(int i) { return i; }
};

int main(int argc, char* argv[]){
    A a;
    std::future<int> res = std::async(&A::f, &a, 1);
    std::cout << res.get() << std::endl;
    return 0;
}


std::future 只能 get() 一次

#include <future>
#include <thread>

int main(int argc, char* argv[]){
    std::future<int> res = std::async(&A::f, &a, 1);
    res.get();
    try{
        res.get();
    }catch(std::future_error e){
        std::cout << e.what() << std::endl;
    }
}

std::async 的第一个参数可以指定为枚举 std::launch 的值, 用于设置任务的运行策略

namespace std{
    enum class launch{// names for launch options passed to async
       async = 0x1,// 运行新线程来执行任务
       deferred = 0x2// 惰性求值，请求结果时才执行任务
    }
}

// std::async 创建任务默认使用两者
std::async([]{});// 等价于 std::async(std::launch::async | std::launch::deferred, [] {})


还可以用 std::packaged_task 封装异步任务, 它可以用于在两个线程之间传递任务, 比如一个线程将异步任务加入队列, 另一个线程不断从队列中取任务执行

#include<iostream>
#include<future>

int main(int argc, char* argv[]){
    std::packaged_task<int(int)> task([](int i){ return i; });
    task(1);// 请求计算结果, 内部的 future 将设置结果值
    std::future<int> res = task.get_future();
    std::cout << res.get_() << std::endl;
    return 0;
}


一种更简单的情况是: 只需要一个固定的返回值, 为此使用 std::promise 即可

#include <future>
#include <iostream>

int main(int argc, char* argv[]){
    std::promise<int> ps;
    ps.set_value(1);// 内部的 future 将设置结果值
    std::future<int> res = ps.get_future();
    std::cout << res.get() << std::endl;
    return 0;
}


std::promise 可以实现事件通知的效果

#include <chrono>
#include <future>
#include <iostream>

class A{
public:
  void signal(){
      std::cout << 1;
      ps_.set_value();
  }
  
  void wait(){
      std::future<void> res = ps_.get_future();
      res.wait();
      std::cout << 2;
  }
private:
  std::promise<void> ps_;
};


int main(int argc, char* argv[]){
    A a;
    std::thread t1{&A::wait, &a};
    std::thread t2{&A::signal, &a};

    t1.join();
    t2.join();

    return 0;
}

不同于 std::condition_variable 的是 std::promise 只能通知一次, 因此通常用来创建暂停状态的线程

#include <chrono>
#include <iostream>
#include <future>

class A{
public:
  void task(){std::cout<< 1;}

  void wait_for_task(){
      ps_.get_future().wait();
      task();
  }

  void signal(){
      ps_.set_value();
  }
private:
  std::promise<void> ps_;
};

int main(){
    A a;
    std::thread t1{&A::wait_for_task, &a};
    std::thread t2{&A::signal, &a};

    t1.join();
    t2.join();
    return 0;
}


std::promise 只能关联一个 std::future

#include <future>
#include <iostream>

int main(int argc, char * argv[]){
    std::promise<void> ps;
    auto a = ps.get_future();
    try {
        auto b = ps.get_future();
    }catch(std::future_error e){
        std::cerr << e.what() << std::endl;
    }
}

std::future 可以存储任务中的异常

#include <iostream>
#include <stdexcept>
#include <future>

int main(int argc, char* argv[]){
    std::future<void> res = std::async([]{throw std::logic_error("error happen")});
    try{
        res.get();
    }catch(std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}


std::promise 需要手动存储异常

#include <future>
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]){
    std::promise<void> ps;
    try{
        throw std::logic_error("error");
    }catch(std::exception& e){
        ps.set_exception(std::current_exception());
    }
    auto res = ps.get_future();
    try{
        res.get_value();
    }catch(std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
}


如果 std::packaged_task 和 std::promise 直到析构都未设置值, std::future::get() 会抛异常

#include <future>
#include <iostream>

int main(int argc, char * argv[]){
    std::future<void> f1;
    std::future<void> f2;
    {
        std::packaged_task<void> task([]{});
        std::promise<void> ps;
        f1 = task.get_future();
        f2 = ps.get_future();
    }
    try{
        f1.get();
    }catch(std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    try{
        f2.get();
    }catch(std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

'std::shared_future 可以多次获取结果, 它可以通过 std::future 的右值构造'。每一个 std::shared_future 对象上返回的结果不同步, 多线程访问 
std::shared_future 需要加锁防止 race condition, 更好的方法是给每个线程拷贝一个 std::shared_future 对象, 这样就可以安全访问而无需加锁

#include <future>

int main(int argc, char* argv[]){
    std::promise<void> ps;
    std::future<void> ft = ps.get_future();
    std::shared_future<void> sf(std::move(ft));
    ps.set_value();
    sf.get();
    sd.get();
    return 0;
}



可以直接用 std::future::share() 生成 std::shared_future

#include <future>

int main(int argc, char* argv[]){
    std::promise<void> ps;
    auto res = ps.get_future().share();
    ps.set_value();
    res.get();
    res.get();
    return 0;
}



// !! 时钟

'对于标准库来说, 时钟是提供了四种信息的类':

1. 当前时间, 如 std::chrono::system_clock::now()

2. 表示时间值的类型, 如 std::chrono::time_point

3. 时钟节拍（一个 tick 的周期),一般一秒有 25 个 tick, 一个周期则为 std::ratio<1, 25>

4. 通过时钟节拍确定时钟是否稳定(steady,匀速), 如 std::chrono::steady_clock::is_steady()


获取当前 UNIX 时间戳, 单位为纳秒

#ifdef _WIN32
#include <chrono>
#elif defined __GNUC__
#include <time.h>
#endif

long long now_in_ns() {
#ifdef _WIN32
  return std::chrono::duration_cast<std::chrono::nanoseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
#elif defined __GNUC__
  struct timespec t;
  clockid_t clk_id = CLOCK_REALTIME;
  clock_gettime(clk_id, &t);
  return t.tv_sec * 1e9 + t.tv_nsec;
#endif
}


用 std::put_time 格式化打印时间

#include <chrono>
#include <iomanip>
#include <iostream>

int main(int argc, char **argv){
    std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
    std::time_t c = std::chrono::system_clock::to_time_t(t);
    //  %F 即 %Y-%m-%d，%T 即 %H:%M:%S，如 2011-11-11 11:11:11
    std::cout << std::put_time(std::localtime(&c), "%F %T");
    return 0;
}





