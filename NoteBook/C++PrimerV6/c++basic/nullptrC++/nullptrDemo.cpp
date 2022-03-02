#include<iostream>


using namespace std;


// !! 引入 nullptr 的原因
// 引入 nullptr 的原因，这个要从 NULL 说起,C 和 C++ 中的 NULL 却不等价。NULL 表示指针不指向任何对象，但是问题在于 NULL 不是关键字，而只是一个宏定义(macro)

// 1.1 NULL 在 C 中的定义

// #define NULL (void*)0  // 在 C 中，习惯将 NULL 定义为 void* 指针值 0

// 1.2 NULL 在 C++ 中的定义
// #ifndef NULL  
// #ifdef __cplusplus  
// #define NULL    0  // 在 C++ 中，NULL 却被明确定义为整常数 0
// #else  
// #define NULL    ((void *)0)  
// #endif  
// #endif  

// 1.3 为什么 C++ 在 NULL 上选择不完全兼容 C ？
// 根本原因和 C++ 的重载函数有关。C++ 通过搜索匹配参数的机制，试图找到最佳匹配（best-match）的函数，而如果继续支持 void* 的隐式类型转换，
// 则会带来语义二义性（syntax ambiguous）的问题。
// 考虑下面两个重载函数
// void foo(int i);
// void foo(char *p)
// foo(NULL); // which is called?

// !! 2. nullptr 的应用场景


int main(int argc, char **argv)
{
    // !! 0（NULL） 和 nullptr 可以交换使用
    int *p1 = 0;
    int *p2 = nullptr;

    if(p1 == 0)
    {
        cout << "p1 == 0" << endl;
    }
    if(p2 == 0)
    {
        cout << "p2 == 0" << endl;
    }
    if(p1 == nullptr)
    {
        cout << "p1 == nullptr" << endl;
    }
    if(p2 == nullptr)
    {
        cout << "p2 == nullptr" << endl;
    }

    if(p1 == p1)
    {
        cout << " p1 == p2" << endl;
    }

    // !! 不能将 nullptr 赋值给整形
    int n1 = 0; // ok
    // int n2 = nullptr;       // error
    // if(n1 == nullptr) {}    // error  
    // if(n2 == nullptr) {}    // error  
    // if(nullprt) {}          // error  
    // nullptr = 0             // error  

    // !! 上面提到的重载问题，使用 nullptr 时，将调用 char*
    // void foo(int)   {cout << "int" << endl;}  
    // void foo(char*) {cout << "pointer" << endl;}  
  
    // foo(0);       // calls foo(int)  
    // foo(nullptr); // calls foo(char*)
    
}