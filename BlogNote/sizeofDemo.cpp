#include <iostream>

using namespace std;


void fun(int arr[10]){
    int n = sizeof(arr);
    cout << "fun sizeof arr is " << n << " bytes" << endl;
}

//  由于在编译时计算, 因此 sizeof 不能用来返回动态分配的内存空间的大小
// 实际上, 用 sizeof 来返回类型以及静态分配的对象、结构或数组所占的空间，返回值跟对象、结构、数组所存储的内容没有关系
//  具体而言，当参数分别如下时，sizeof返回的值表示的含义如下：
    // 数组——编译时分配的数组空间大小
    // 指针——存储该指针所用的空间大小（存储该指针的地址的长度，是长整型，应该为 8)
    // 类型——该类型所占的空间大小
    // 对象——对象的实际占用空间大小
    // 函数——函数的返回类型所占的空间大小。函数的返回类型不能是 void
int main(){


    // 特性0：sizeof 是运算符，不是函数


    // sizeof 不能求得 void 类型的长度

    cout << "sizeof void is " << sizeof(void) << " bytes" << endl;

    //     sizeofDemo.cpp:13:45: warning: invalid application of ‘sizeof’ to a void type [-Wpointer-arith]
    //    13 |     cout << "sizeof void is " << sizeof(void) << " bytes" << endl;
    //       |       
    // sizeof void is 1 bytes


    // 特性2：sizeof能求得void类型的指针的长度
    cout << "sizeof void* is " << sizeof(void *) << " bytes" << endl;
    cout << "sizeof int* is " << sizeof(int *) << " bytes" << endl;
    cout << "sizeof double* is " << sizeof(double *) << " bytes" << endl;
    cout << "sizeof float* is " << sizeof(float *) << " bytes" << endl;
    cout << "size of long* is " << sizeof(long *) << " bytes" << endl;

    // sizeof void* is 8 bytes
    // sizeof int* is 8 bytes
    // sizeof double* is 8 bytes
    // sizeof float* is 8 bytes
    // size of long* is 8 bytes

    // sizeof 能求得静态分配内存的数组的长度!
    int a[10];
    cout << "sizeof a is " << sizeof(a) << " bytes" << endl;

    // sizeof a is 40 bytes

    // 非常需要注意的是对函数的形参数组使用 sizeof 的情况。举例来说, 假设有如下的函数

    fun(a);
    // fun sizeof arr is 8 bytes
    // 原因是在函数参数传递时, 数组被转化成指针了, 或许你要问为什么要转化成指针，原因可以在很多书上找到，我简单说一下: 假如直接传递整个数组的话，那么必然
    // 涉及到数组元素的拷贝(实参到形参的拷贝)，当数组非常大时，这会导致函数执行效率极低！而只传递数组的地址(即指针)那么只需要拷贝 8byte


    // sizeof 不能求得动态分配的内存的大小

    int *pi = new int[10];

    cout << "sizeof pi is " << sizeof(pi) << " bytes" << endl;
    // sizeof pi is 8 bytes

    // sizeof 不能对不完整的数组求长度!

    // 当表达式作为 sizeof 的操作数时，它返回表达式的计算结果的类型大小, 但是它不对表达式求值~

    // sizeof 可以对函数调用求大小, 并且求得的大小等于返回类型的大小, 但是不执行函数体

    return 0;
}