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
    std::time_t c = std::chrono::system_clock::to_time_t(t);// UNIX 时间戳，秒
    //  %F 即 %Y-%m-%d，%T 即 %H:%M:%S，如 2011-11-11 11:11:11
    std::cout << std::put_time(std::localtime(&c), "%F %T");
    return 0;
}



std::chrono::duration 表示时间间隔

namespace std{
    namespace chrono {
        using nanoseconds = duration<long long, nano>;
        using microseconds = duration<long long, micro>;
        using milliseconds = duration<long long, milli>
        using seconds = duration<long long, seconds>;
        using minutes = duration<long long, ratio<60>>;
        using hours = duration<long long, ratio<3600>>;

        //C++ 20
        using days   = duration<int, ratio_multiply<ratio<24>, hours::period>>;
        using weeks  = duration<int, ratio_multiply<ratio<7>, days::period>>;
        using years  = duration<int, ratio_multiply<ratio<146097, 400>, days::period>>;
        using months = duration<int, ratio_divide<years::period, ratio<12>>>;
    }
}


C++14 在 std::literals::chrono_literals 中提供了表示时间的后缀

#include <cassert>
#include <chrono>

using namespace std::literals::chrono_literals;

int main() {
  auto a = 45min;
  assert(a.count() == 45);
  auto b = std::chrono::duration_cast<std::chrono::seconds>(a);
  assert(b.count() == 2700);
  auto c = std::chrono::duration_cast<std::chrono::hours>(a);
  assert(c.count() == 0);  // 转换会截断
}

duration 支持四则运算

#include <cassert>
#include <chrono>

using namespace std::literals::chrono_literals;

int main() {
  assert((1h - 2 * 15min).count() == 30);
  assert((0.5h + 2 * 15min + 60s).count() == 3660);
}


'使用 duration 设置等待时间'

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int f(){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}


int main(int argc, char* argv[]){
    auto res = std::async(f);
    if(res.wait_for(std::chrono::seconds(5)) == std::future_status::ready){
        std::cout << res.get() << std::endl;
    }
    return 0;
}


std::chrono::time_point 是表示时间的类型, 值为从某个时间点开始计时的时间长度

// 第一个模板参数为开始时间点的时钟类型, 第二个为时间单位
std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>


'std::chrono::time_point 可以与 duration 加减, 也可以与自身相减'

#include <cassert>
#include <chrono>

int main(int argc, char* argv[]) {
    std::chrono::system_clock::time_point a = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::chrono::system_clock::time_point b = std::chrono::system_clock::now();
    long long diff = std::chrono::duration_cast<std::chrono::seconds>(b - a).count();

    assert(diff == 60);
    return 0;
}


// !! 函数式编程 (functional programming)

'函数式编程是一种编程范式, 使用的函数为纯函数, 即如果函数的调用参数相同, 则永远返回相同的结果'。 纯函数不会改变外部状态，因此对于只使用纯函数的函数式编程，
天生就不存在 race condition 的问题。

Haskell 是一种常见的函数式编程语言, 以快速排序为例, Haskell 中的实现如下:

quickSort :: Ord a => [a] -> [a]
quickSort [] = []
quickSort (x : xs) = l ++ [x] ++ r
  where
    l = quickSort (filter (<= x) xs)
    r = quickSort (filter (> x) xs)

main :: IO ()
main = print (quickSort "downdemo") -- "downdemo"


相同思路的 C++ 实现

#include <algorithm>
#include <iostream>
#include <list>
#include <utility>

template<typename T>
std::list<T> quick_sort(std::list<T> v){
    if(v.empty()) return v;
    std::list<T> res;
    res.splice(res.begin(), v, v.begin());// 将 v 的首元素移到 res 中
     // 将 v 按条件划分为两部分，并返回第一个不满足条件元素的迭代器
    auto it = std::partition(v.begin(), v.end(),[&](const T& x){return x < res.front();});
    std::list<T> low;
    low.splice(low.end(), v, v.begin(), it);  // 转移左半部分到 low
    auto l(quick_sort(std::move(low)));       // 递归对左半部分快速排序
    auto r(quick_sort(std::move(v)));         // 递归对右半部分快速排序
    res.splice(res.end(), r);                 // 右半部分移到结果后
    res.splice(res.begin(), l);               // 左半部分移到结果前
    return res;
}

int main() {
  for (auto& x : quick_sort(std::list<int>{1, 3, 2, 4, 5})) {
    std::cout << x;  // 12345
  }
}



// !! 链式调用

链式调用是函数式编程中经常使用的形式, 常见于 ReactiveX, 比如 RxJS, 当上游产生数据时交给下游处理, 将复杂的异步逻辑拆散成了多个小的操作, 只需要关注每一步操作
并逐步转换到目标结果即可。C++20 的 ranges 使用的 range-v3 就脱胎自 RxCpp


// !! CSP (Communicating Sequential Processes)


1. CSP 是一种描述并发系统交互的编程模型, 线程理论上是分开的, 没有共享数据, 每个线程可以完全独立地思考, 消息通过 communication channel 在不同线程间传递, 
   线程行为取决于收到的消息, 因此每个线程实际上是一个状态机, 收到一条消息时就以某种方式更新状态, 并且还可能发送消息给其他线程。

2. Erlang 采用了这种编程模型, 并用于 MPI 做 C 和 C++ 的高性能计算。真正的 CSP 没有共享数据, 所有通信通过消息队列传递, 但由于 C++ 线程共享地址空间,无法强制
   实现这个要求，所以需要应用或者库的作者来确保线程间不会共享数据


