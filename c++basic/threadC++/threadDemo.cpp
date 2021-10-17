#include <iostream>
#include <thread>
#include <memory>
#include <unistd.h>
#include "DisplayThread.h"

using namespace std;

void funcHappy()
{
    cout << "I am Happy" << endl;
    usleep(100);
    cout << "thead id is " << std::this_thread::get_id() << endl;
}

void funcValued(int value)
{
    cout << "I am Valued "<< value << endl;
    cout << "thread id is " << std::this_thread::get_id() << endl;
}

int main(int argc, char **argv)
{
    // 进程：进程指正在运行的程序。确切的来说，当一个程序进入内存运行，即变成一个进程，进程是处于运行过程中的程序，并且具有一定独立功能
    // 线程：线程是进程中的一个执行单元，负责当前进程中程序的执行，一个进程中至少有一个线...
    // 简而言之：一个程序运行后至少有一个进程，一个进程中可以包含多个线程

    // 原始的 c++ 标准仅支持单线程编程，新的c++标准（c++11或c++0x）于2011年发布，引入了新的线程库
    // 在 linux 下的编译方法：g++ -std=c++11 sample.cpp -lpthread
    // !! 使用函数指针创建线程
    std::thread t(funcHappy);
    std::thread t1(funcValued,100);



    // !!使用函数对象创建线程
    // std::thread t2((DisplayThread()));

    t.join();
    t1.join();
    // t2.join();
    return 0;

}