# include<iostream>
# include "TestNew.h"

using namespace std;

// 内存的分配方式有三种:
// 1. 从静态存储区域分配。内存在程序编译的时候就已经分配好，这块内存在程序的整个运行期间都存在。例如全局变量，static 变量
// 2. 在栈上创建。在执行函数时，函数内局部变量的存储单元都可以在栈上创建，函数执行结束后在将这些局部变量的内存空间回收。在栈上分配内存空间效率很高，但是分配的内存容量有限
// 3. 从堆上分配的。程序在运行的时候用 malloc 或 new 申请任意多少的内存，程序员自己负责在何时用 free 或 delete 释放内存
// 编译器处理完类中全部的声明后才会处理成员函数的定义，即成员函数体直到整个函数可见后才会被处理
// 如果没有在构造函数的初始值列表中显示的初始化成员，则该成员在构造函数体之前执行默认初始化
TestNew::TestNew(int id)
{
    this->id = id;
}

TestNew::~TestNew()
{
    cout << "对象 " << this->id << " 执行析构函数" << endl;
}

int main()
{
    TestNew test(1234);
    TestNew *pTest = new TestNew(1111);
    delete pTest;
}
