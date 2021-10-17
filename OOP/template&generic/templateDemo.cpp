#include <iostream>
#include "Blob.h"

using namespace std;

// !! 模版是 c++ 泛型编程的基础。一个模版就是一个创建类或者函数的蓝图或者说公式。

// 函数模版（function template）---一个函数模版就是一个公式，可用来生成针对特定类型的函数版本

// 模版定义以关键字 template 开始，后面跟一个模版参数列表
// 模版参数表示在类或者函数中用到了类型或值。当我们使用模版时，我们指定模版实参（隐式地或者显示地）将其绑定到模版参数上
template <typename T>
// !! T 表示的实际类型在编译时根据 compare 的使用情况来确定
int compare(const T& a, const T& b)
{
    if(a < b) return -1;
    if(a > b) return 1;
    return 0;
}

// !! 模版类型参数
// 类型参数可以用来指定返回类型和函数的参数类型
template<typename T> T foo(T* p)
{
    T tmp = *p;
    // ...
    return tmp;
}

// 类型参数前必须使用关键字 class 或者 typename； 在模版参数列表中， typename 和 class 没有什么不同
template<typename T, class U> calc(const T&, const U&);


// !! 非类型模版参数
// 除了定义类型参数，还可以在模版中定义非类型参数；一个非类型参数表示一个值而非一个类型
// 我们通过一个特定的类型名而非关键字 typename 或 class 来指定非类型参数
// 当一个模版被实例化时，非类型参数被一个用户提供的或者编译器推断的值所代替；这些值必须是常量表达式，从而允许编译器在编译时实例化模版


template<unsigned N,unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M])
{
    return strcmp(p1, p2);
}

// !! inline 和 constexpr 的函数模版
// 函数模版可以声明为 inline 或 constexpr 
// inline 说明符跟在模版参数列表之后
template<typename T> inline T min(const T&, const T&);

// !! 编写类型无关的代码---模版程序应该尽量减小对实参类型的要求
// 我们最初的 compare 函数虽然简单，但它说明了编写泛型代码的两个重要原则
// 1. 模版中的函数参数是 const ----保证函数可以用于不能拷贝的类型
// 2. 函数体中的条件判断仅使用 < 比较----降低了compare函数对要处理的类型要求


// !! 模版编译
// 当编译器遇到一个模版定义时，它并不生成代码；只有当我们实例化出模版的一个特定版本时，编译器才会生成代码


// 模版函数和类模版成员函数的定义通常放在头文件中
// 模版包含两种名字：
// 1. 那些不依赖于模版参数的名字
// 2. 那些依赖于模版参数的名字
// 当使用模版时，所以不依赖于模版参数的名字必须是可见的，这是由模版提供者来保证；用来实例化模版的所以函数、类型以及与类型关联的运算符都必须是可见的


// 模版的编译错误
// 通常，编译器会在三个阶段报告错误：
// 1. 编译模版本身时； 2. 编译器遇到模版使用时； 3. 模版实例化时


// !! 类模版 ----用来生成类的蓝图
// 为了使用类模版，我们必须在模版名后的尖括号中提供额外的信息


// !! 实例化类模版
// 当我们使用类模版时，我们必须提供额外的信息（显示模版实参列表，它们被绑定到模版参数），编译器使用这些模版实参来实例化特定的类
Blob<int> ia;
Blob<int> ia2 = {1,2,3,4,5,6,7,8,9,10};
Blob<string> is;
// !! 一个类模版的每个实例都形成一个独立的类


// !! 在模版作用域中引用模版类型

// !! 类模版成员函数的实例化
// 默认情况下，对于一个实例化了的类模版，其成员函数只有当程序用到它时才会被实例化

// !! 在类模版自己的作用域中，我们可以直接使用模版名而不提供实参
// 当我们处于一个类模版的作用域中，编译器处理模版自身引用就好像我们已经提供了与模版参数匹配的实参一样


// !! 在类模版外使用类模版名
// 当我们在类模版外定义其成员时，必须记住，我们不在类的作用域中，直到遇到类名(通常还有作用域运算符）才表示进入类的作用域

// 为了引用模版的一个特定实例，我们必须首先声明模版自身
// 前置声明，在 Blob 中声明友元所需要的
template<typename> class BlobStr;
template<typename> class Blob;
template<typename T> bool operator==(const Blob<T> &, const Blob<T> &);

template<typename T> class Blob
{
    friend class BlobStr;
    friend class operator==<T>(const Blob<T> &, const Blob<T> &);
};


// !! 类模版的 static 成员
// 所以的 Foo<X> 类型的对象共享相同的 ctr 对象和 count 函数
// 我们可以使用一个类类型对象来直接访问一个 static 成员：Foo<int>::count();
template <typename T>
class Foo
{
public:
    static std::size_t count() const;

private:
    static std::size_t ctr;
};

// !! 一个特定文件所需要的所以模版的声明通常一起放置在文件开始位置，出现于任何使用这些模版的代码之前


// 使用类的类型成员

// 回忆一下，我们用作用域运算符(::)来访问 static 成员和类型成员；在普通的代码中，编译器掌握类的定义，因此它知道通过作用域
// 访问的名字是类型还是 static 成员。
std::string size_type;// 编译器有 string 的定义，从而知道 size_type 是一个类型


// !! 如果我们希望使用一个模版类型参数的类型成员时，就必须显示的告诉编译器该名字是一个类型。我们使用关键字 typename 来实现这一点
template<typename T>
template T::value_type top(const T& c)
{
    if(!c.empty())
    {
        return c.back();
    }
    else
    {
        return typename T::value_type();
    }
}


// !! 模版默认实参和类模版
template <typename T = int>
class Numbers // T 默认为 int
{
public:
    Numbers(T v = 0) : v(v) {}

private:
    T val;

};

Numbers<double> num;
Numbers<> numdef;// 空表示我们希望使用默认类型（T 默认为 int）


// !!成员模版
// 一个类（无论是普通类还是模版类）可以包含本身是模版的成员函数，这种成员被称为成员模版


class DebugDelete
{
    public:
    DebugDelete(std::ostream &s = std::cerr):os(s) {}

    // 与任何函数模版相同，T 的类型由编译器推断
    template <typename T> void operator()(T *p) const
    {
        os << "delete unique_ptr " << std::endl;
        delete p;
    }
    private:
    std::ostream &os;
}

double* p = new double;
DebugDelete dg;
dg(p);// 调用 DebugDelete::operator()（double *）

int *ip = new int;
DebugDelete()(ip);


// !!控制实例化
// 当模版被使用时才会进行实例化这一特性意味着，相同实例可能出现在多个对象文件中。当两个或者多个独立编译的源文件使用了
// 相同的模版并提供了相同的模版参数时，每个文件中就都会有该模版的一个实例。

// 在大系统中，在多个文件中实例化相同模版的额外开销可能非常严重。

// 在新标准中，我们可以通过显示实例化来避免这种开销

// 当编译器遇到 extern 模版声明时，它不会在本文件中生成实例化代码
// 将一个实例化声明为 extern 就表示承诺在程序的其他位置有该实例化的一个非 extern 的声明（定义）
// 对于一个给定的实例化版本，可能只有一个 extern 声明，但是只有一个定义
extern template class Blob<string>;

int main(int argc, char **argv)
{
    // 当我们调用一个模版函数时，编译器（通常）用参数的实参的类型来为我们推断模版实参的类型，然后将其绑定到 T
    // 然后编译器用推断出的模版参数来为我们实例化一个特定版本的函数，这些编译器生成的版本通常称为模版实例
    int result = compare(1, 2);
    cout << result << endl;

    int result1 = compare("hi","nomi");
    cout << result1 << endl;
}


