#include<string>
#include<iostream>

using namespace std;


int fun();

// 变量 num 在 main 函数的后边进行声明和初始化的话，那么在 main 函数中是不能直接引用 num 这个变量
int main(int argc, char **argv)
{
    fun();
    // 利用 extern 关键字先声明一下num变量，告诉编译器num这个变量是存在的，但是不是在这之前声明的
    extern int num;
    cout << num << endl;
    // !! extern 这个关键字的真正的作用是引用不在同一个文件中的变量或者函数
    extern int key;
    // !! extern 除了引用另一个文件中的变量外，还可以引用另一个文件中的函数，引用方法和引用变量相似
    extern void func();
    return 0;
}

// num 的声明和初始化
int num = 12;

// 在 func 函数中是可以正常使用，因为 func 对 num 的调用是发生在 num 的声明和初始化之后
int fun()
{
    cout <<"fun " << num << endl;
}