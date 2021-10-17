#include <iostream>
#include <string>


using namespace std;

//!!  sizeof() 类大小计算

class EmptyClass{};


class A
{
    public:
        char b;
        // 对于包含虚函数的类，不管有多少个虚函数，只有一个虚指针, vptr 的大小
        virtual void fun() {};
        // 静态数据成员被编译器放在程序的一个 global data members 中，它是类的一个数据成员，但不影响类的大小。不管这个类产生了多少个实例，
        // 还是派生了多少新的类，静态数据成员只有一个实例。静态数据成员，一旦被声明，就已经存在
        static int c;
        static int d;
        static int f;
};

class B
{
    virtual void fun();
    virtual void fun1();
    virtual void fun2();
    virtual void fun3();
};

class C
{
    public:
        char a;
        int b;
};


class D:C
{
    public:
        short a;
        long b;
};

class E
{
    virtual void fun() {}
};

class F
{
    virtual void fun2() {}
};

class G : virtual public  E, virtual public F
{
    public:
        virtual void fun3() {}
};


int main(int argc, char **argv)
{
    // 1. 空类的大小为1字节, output 1
    cout << "Size of EmptyClass is " << sizeof(EmptyClass) << endl;
    

    // 字节对齐、静态变量不影响类的大小、vptr指针 = 8, output 16
    cout << "Size of A is " << sizeof(A) << endl;

    // 对于包含虚函数的类，不管有多少个虚函数，只有一个虚指针, vptr 的大小。output 8
    cout << "Size of B is " << sizeof(B) << endl;


    // output 8
    cout << "Size of C is " << sizeof(C) << endl;
    // output 24
    cout << "Size of D is " << sizeof(D) << endl;

    cout << "Size of Short is " << sizeof(short) << endl;
    cout << "Size of long is " << sizeof(long) << endl;

    cout<<sizeof(E)<<" "<<sizeof(F)<<" "<<sizeof(G) << endl;
    
}






