#include<iostream>
#include<thread>
#include <unistd.h>

using namespace std;

// !! 如何启动线程启动

// 1. 使用 C++ 线程库启动线程，可以归结为构造 std::thread 对象
// void do_some_work();
// std::thread my_thread(do_some_work);

// 2. std::thread 可以用可调用（callable）类型构造，将带有函数调用符类型的实例传入 std::thread 类中，替换默认的构造函数


class background_task
{
    public:
    void operator()() const
    {
        // do_something();
        cout << "Hello background_task" << endl;
    }
};

//!!  启动了线程，你需要明确是要等待线程结束(join)，还是让其自主运行(detach)。如果 std::thread 对象销毁之前还没有做出决定，
// !! 程序就会终止(std::thread的析构函数会调用std::terminate())。因此，即便是有异常存在，也需要确保线程能够正确的加入(joined)或分离(detached)

int main(int argc, char **argv)
{
    background_task f;
    std::thread my_thread(f);
    my_thread.join();

    // 3. 使用 lambda 表达式
    // std::thread my_thread1([]
    // {
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    // cout << "I am in my_thread1 " << endl;
    // std::thread my_thread2([]
    // {
    //     int i = 0;
    //     while(1)
    //     {
    //       cout << "I am In my_thread2 and detached thread "  << i ++ << endl;
    //     }
    // });
    // my_thread2.detach();
    // });


    // if (my_thread1.joinable())
    // {
    //     my_thread1.join();
    // }



    // !! std::thread::hardware_concurrency() 在新版 C++ 标准库中是一个很有用的函数。这个函数将返回能同时并发在一个程序中的线程数量
    cout << "Support Max thread number is " << std::thread::hardware_concurrency()<< endl;


    // !! 当前线程中调用 std::this_thread::get_id() (这个函数定义在<thread>头文件中)也可以获得线程标识
    cout << "current Thread Id is " << std::this_thread::get_id() << endl;

    

    return 0;
}