#include <string>
#include <iostream>


using namespace std;

class Base
{
public:
    virtual void show(int x = 1)
    {
        cout << "base show x is "<< x << endl;
    }
    ~Base()
    {
        cout << "base destroy" << endl;
    }
};


class Derived : public Base
{
public:
    // 这里的 virtual 关键字可以省略，因为只有基类里面被声明为虚函数，派生类中默认都是虚的
    // 或者定义为 virtual void show(){cout << "Derived show" << endl;}
    void show(int x = 100)
    {
        cout << "Derived show x is " << x << endl;
    }

    ~Derived()
    {
        cout << "Derived destroy" << endl;
    }
};


// !! 虚函数表与虚函数指针
// vtable(虚函数表):每一个含有虚函数的类都会维护一个虚函数表，里面按照声明顺序记录了虚函数的地址
// vptr(虚函数指针)：一个指向虚函数表的指针，每个对象都会拥有这样的一个指针


class A
{
public:
    virtual void func();
};


class B
{
    public:
    void func();
};

// !! 虚函数中默认参数
// 1. 默认参数不包含在函数签名里;函数签名定义了函数的输入与输出，包括参数及参数的类型、返回值及其类型、可能会抛出或传回的exceptions、
//    该方法在面向对象程序中的可用性方面的信息诸如public、static或prototype等关键字等
// 2. 默认参数是静态绑定的，虚函数是动态绑定的。默认参数的使用需要看指针或者引用本身的类型，而不是对象的类型
// 3. 绝不重新定义继承而来的缺省参数


// !! 静态函数可以声明为虚函数吗?----静态函数不可以声明为虚函数，同时也不能被const 和 volatile关键字修饰
// 1. static成员函数不属于任何类对象或类实例，所以即使给此函数加上 virtual 也是没有任何意义
// 2. 虚函数依靠 vptr 和 vtable 来处理。vptr 在类的构造函数中创建生成，并且只能用 this 指针来访问它，静态成员函数没有 this 指针，无法访问vptr


// !! 构造函数可以为虚函数吗？
// 构造函数不可以声明为虚函数。同时除了inline之外，构造函数不允许使用其它任何关键字


// !!析构函数可以为虚函数吗？
// 析构函数可以声明为虚函数。如果我们需要删除一个指向派生类的基类指针时，应该把析构函数声明为虚函数。事实上，
// 只要一个类有可能会被其它类所继承，就应该声明虚析构函数(哪怕该析构函数不执行任何操作)



// !!纯虚函数与抽象类

// !! 纯虚函数 -- 在基类中声明但不定义的虚函数，但要求任何派生类都要定义自己的实现方法
// 在基类中实现纯虚函数的方法是在函数原型后加“=0”，如 virtual void func() = 0

// !! 抽象类---含有纯虚函数的类为抽象类

class BaseA
{
private:
    int x;

public:
    // pure virtual
    virtual void func() = 0;
    int getX()
    {
        return x;
    }
};



class DerivedA : public BaseA
{
public:
    // 继承并重写基类的纯虚函数，如果没有重写，派生类也会是抽象类
    void func()
    {
        cout << "call func" << endl;
    }

private:
    int y;
};

// !! 纯虚函数的特点以及用途总结如下
// 1. 必须在继承类中重新声明该函数(实现可以为空)，否则继承类仍为抽象类，程序无法编译通过
// 2. 派生类仅仅只是继承纯虚函数的接口，因此使用纯虚函数可以规范接口形式
// 3. 声明纯虚函数的基类无法实例化对象
// 4. 纯虚函数的声明就是在告诉子类的设计者，“你必须提供一个纯虚函数的实现，但我不知道你会怎样实现它”



int main(int argc, char* argv[])
{
    // !! 1. 虚函数的调用取决于指向或者引用的对象的类型，而不是指针或者引用自身的类型。
    // \虚函数的调用取决指针和引用的动态类型~~~
    Base *pBase = new Derived();
    // output Derived show
    pBase->show();
    // base destroy, not call Derived destroy！！！！ we should make virtual ~Base()
    delete pBase;
    // 因为 A 比 B 多一个虚函数指针
    cout <<(sizeof(A) > sizeof(B))<< endl;

}