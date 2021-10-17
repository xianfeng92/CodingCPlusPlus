#include <thread>
#include <iostream>
#include<mutex>
#include <string>

// !! std::lock_guard RAII 模板类的简单实现，功能简单
// 1. std::lock_guard 在构造函数中进行加锁，析构函数中进行解锁
// 2. 锁在多线程编程中，使用较多，因此 c++11 提供了 lock_guard 模板类；在实际编程中，我们也可以根据自己的场景编写 resource_guard RAII类，避免忘掉释放资源

// !! std::unique_lock 是通用互斥包装器，允许延迟锁定、锁定的有时限尝试、递归锁定、所有权转移和与条件变量一同使用
// unique_lock 比 lock_guard 使用更加灵活，功能更加强大,使用 unique_lock 需要付出更多的时间、性能成本
using namespace std;
std::mutex mtx; // mutex for critical section


struct Box
{
    explicit Box(int num):num_things{num}{}
    int num_things;
    std::mutex m; // mutex for critical section
};

void transform(Box& from, Box& to, int num)
{
    std::unique_lock<std::mutex> lock1(from.m,std::defer_lock);
    std::unique_lock<std::mutex> lock2(to.m,std::defer_lock);
    // std::defer_lock 调用 std::unique_lock 的构造函数，不会立即去获取锁，而是延迟到 std::lock(lock1,lock2) 时以原子方式执行锁定操作

    // 锁定操作是通过使用可变参数模板 std::lock 以原子方式执行锁定操作
    std::lock(lock1,lock2);

    from.num_things -= num;
    to.num_things += num;
    
}// 'from.m' and 'to.m' mutexes unlocked in 'unique_lock' dtors

int main(int argc, char **argv)
{
    Box acc1(100);
    Box acc2(200);

    std::thread t1(transform,std::ref(acc1),std::ref(acc2),10);
    std::thread t2(transform,std::ref(acc1),std::ref(acc2),20);
    t1.join();
    t2.join();
    return 0;
}