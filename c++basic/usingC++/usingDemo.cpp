
#include <iostream>
#define isNs1 1
using namespace std;

// !! 基本使用
// 局部与全局 using
void func() 
{
    cout<<"::func"<<endl;
}

namespace ns1
{
    void func()
    {
        cout << "ns1::func" << endl;
    }
}

namespace ns2
{
#ifdef isNs1
    using ns1::func; /// ns1 中的函数
#elif isGlobal
    using ::func; /// 全局中的函数
#else
    void func()
    {
        cout << "other::func" << endl;
    }
#endif
}


// !! 函数重载
// 在继承过程中，派生类可以覆盖重载函数的0个或多个实例，一旦定义了一个重载版本，那么其他的重载版本都会变为不可见
class Base
{
public:
    void f()
    {
        cout << "f()" << endl;
    }
    void f(int n)
    {
        cout << "Base::f(int)" << endl;
    }
};

class Derived : private Base
{
public:
    using Base::f;
    void f(int n)
    {
        cout << "Derived::f(int)" << endl;
    }
};

int main(int argc, char **argv)
{
     /**
     * 这就是为什么在c++中使用了 cmath 而不是 math.h 头文件
     */
    
    ns2::func(); // 会根据当前环境定义宏的不同来调用不同命名空间下的func()函数
    Base b;
    Derived d;
    d.f();
    d.f(1);
    return 0;
}