#include <iostream>
#include <thread>
// !! 标准 C++ 库中对多线程支持的声明在新的头文件中：管理线程的函数和类在<thread>中声明，而保护共享数据的函数和类在其他头文件中声明


using namespace std;

// 因为每个线程都必须具有一个初始函数(initial function)，新线程的执行在这里开始。对于应用程序来说，初始函数是 main()，
// 但是对于其他线程，可以在 std::thread 对象的构造函数中指定
void hello()
{
    cout << "Hello Concerrent World" << endl;
}

// !! C++中使用多线程并不复杂，复杂的是如何设计代码以实现其预期的行为
int main(int argc, char **argv)
{
    std:thread tHello(hello);
    // join 这会导致调用线程(在main()中)等待与 std::thread tHello 对象相关联的线程
    t.join();
    return 0;
}