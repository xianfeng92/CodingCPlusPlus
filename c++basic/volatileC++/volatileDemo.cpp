
#include <iostream>

using namespace std;

 // !! volatile 应用
// 1. 并行设备的硬件寄存器（如状态寄存器）。假设要对一个设备进行初始化，此设备的某一个寄存器为 0xff800000
int *output = (unsigned int *)0xff800000; //定义一个IO端口；
int init(void)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        *output = i;
    }
}

// 经过编译器优化后，编译器认为前面循环半天都是废话，对最后的结果毫无影响，因为最终只是将 output 这个指针赋值为 9，
// 所以编译器最后给你编译编译的代码结果相当于:

int  init(void)  
{  
    *output = 9;  
}

// 如果你对此外部设备进行初始化的过程是必须是像上面代码一样顺序的对其赋值，显然优化过程并不能达到目的。反之如果你不是对此端口反复写操作，
// 而是反复读操作，其结果是一样的，编译器在优化后，也许你的代码对此地址的读操作只做了一次。然而从代码角度看是没有任何问题的。
// 这时候就该使用 volatile 通知编译器这个变量是一个不稳定的，在遇到此变量时候不要优化。
static int i = 0;
/* Interrupt service routine */
void IRS()
{
    i=1;
}

void doSomething
{

}

volatile  bool bStop=false;  // bStop 为共享全局变量 
//第一个线程
void threadFunc1()
{
    ...
    while(!bStop){...}
}

//第二个线程终止上面的线程循环
void threadFunc2()
{
    ...
    bStop = true;
}
// 要想通过第二个线程终止第一个线程循环，如果 bStop 不使用 volatile 定义，那么这个循环将是一个死循环，因为 bStop 已经读取到了寄存器中，寄存器中 bStop 的值永远
// 不会变成FALSE，加上 volatile ，程序在执行时，每次均从内存中读出 bStop 的值，就不会死循环了

int main(int argc, char **argv)
{
    // !! 被 volatile 修饰的变量，在对其进行读写操作时，会引发一些可观测的副作用。而这些可观测的副作用，是由程序之外的因素决定的

    // !! 一个中断服务子程序中访问到的变量
    while (1)
    {
        if (i)
        {
            doSomething();
        }
    }
    // 由于编译器判断在 main 函数里面没有修改过 i，因此可能只执行一次对从 i 到某寄存器的读操作，然后每次 if 判断都只使用这个寄存器里面
    // 的“i副本”，导致 doSomething 永远不会被调用。如果将变量 i 加上 volatile 修饰，则编译器保证对变量 i 的读写操作都不会被优化，从而保证了
    // 变量 i 被外部程序更改后能及时在原程序中得到感知



    // !! 多线程应用中被多个任务共享的变量
    // 当多个线程共享某一个变量时，该变量的值会被某一个线程更改，应该用 volatile 声明。 当多个线程共享某一个变量时，该变量的值会被某一
    // 个线程更改，应该用 volatile 声明



    // !! 3. volatile常见问题
    // 一个指针可以是volatile吗？为什么？
    // 可以。尽管这并不常见。一个例子是当一个中断服务子程序修该一个指向一个buffer的指针时


    // !! 4.volatile 使用
    // volatile 关键字是一种类型修饰符，用它声明的类型变量表示可以被某些编译器未知的因素（操作系统、硬件、其它线程等）更改。
    // 所以使用 volatile 告诉编译器不应对这样的对象进行优化。
    // volatile 关键字声明的变量，每次访问时都必须从内存中取出值
    // const 可以是 volatile （如只读的状态寄存器）
    // 指针可以是 volatile
    
    return 0;
}

// 下面的函数有什么错误？
int square(volatile int *ptr)
{
    return *ptr * *ptr;
}

// 由于 ptr 指向一个 volatile 型参数，编译器将产生类似下面的代码:
int square(volatile int *ptr)
{
    int a, b;
    a = *ptr;
    b = *ptr;
    return a * b;
}

// 由于 *ptr 的值可能被意想不到地改变，因此 a 和 b 可能是不同的。结果，这段代码可能返回的不是你所期望的平方值！
// 正确的代码如下：
long square(volatile int *ptr)
{
    int a = *ptr;
    return a * a;
}