#include<string>


// !! 命名空间(namespace):为了防止名字冲突提供了更加可控的机制
// 命名空间分割了全局命名空间，其中每个命名空间是一个作用域。

// !! 自定义命名空间---每个命名空间都是一个作用域
// 命名空间作用域后面无需分号
namespace cplusplus_primer
{
    class Sales_data{};
    Sales_data operator+(const Sales_data&, const Sales_data&);
    class Query{};
    class Query_base{};
}

cplusplus_primer::Query q = cplusplus_primer::Query("hello");

// !! 命名空间可以是不连续的
// 如果之前定义过命名空间 cplusplus_primer，则如下代码会打开已经存在的命名空间 cplusplus_primer ，然后添加一个新成员 Query_Result
// 如果之前没有定义过命名空间 cplusplus_primer,则上述代码会创建一个新的命名空间 cplusplus_primer
namespace cplusplus_primer
{
    class Query_Result{};
}



// !! 全局命名空间：全局作用域中定义的名字被隐式的添加到全局命名空间中。
// !! 全局作用域中定义的名字（即在所有类、函数及命名空间之外定义的名字）也就是定义在全局命名空间（global namespace）
// 全局命名空间以隐式的方式声明，并且在所有程序中都存在。
// 作用域运算符同样适用于全局作用域的成员，形式如下：

::member_name;// 表示全局命名空间中的一个成员


// !! 嵌套命名空间
// 嵌套命名空间同时是一个嵌套的作用域，它嵌套在外层命名空间的作用域中
namespace cplusplus_primer
{
    // 第一个嵌套的命名空间：定义了库的Query部分
    namespace Querylib
    {
        class Query {};
        Query operator&(const Query &, const Query &);
        // ...
    }

    // 第二个嵌套命名空间：定义了库 Sales_data 部分
    namespace Bookstore
    {
        class Quote{};
        // ...
    }
}

cplusplus_primer::Querylib::Query q;


// !! 内联命名空间
// c++ 11 新标准引入了一种新的嵌套命名空间，称为内联命名空间（inline namespace）
// !! 内联命名空间中的名字可以被外层命名空间直接使用
// 定义内联命名空间的方式是关键字 namespace 前面加 inline
inline namespace FifthEd
{

}

namespace FifthEd
{
    class Query_base{};
    // ...
}

namespace ForthEd
{
    class item_base{};
    class Query_base{};
    // ...
}


namespace cplusplus_primer
{
    #include "FifthEd.h"
    #include "ForthEd.h"
    // ...
}

// 因为 FifthEd 是内联的，所以可以 cplusplus_primer:: 代码可以直接获得 FifthEd 的成员

// !! 未命名的命名空间（unnamed namespace） --- 关键字 namespace 后紧跟花括号括起来的一系列声明语句
// 未命名的命名空间中定义的变量拥有静态的生命周期：它们在第一次使用前创建，并且直到程序结束时销毁

// !! 一个未命名的命名空间可以在某个给定的文件中不连续，但是不能跨越多个文件
// 每个文件定义自己的未命名的命名空间；如果两个文件都含义未命名的命名空间，则这两个空间互相无关。
// 在这两个未命名的命名空间中可以定义相同的名字，并且这些定义表示的是不同的实体。
// 如果一个头文件定义了未命名的命名空间，则该命名空间中定义的名字将在每个包含了该头文件的文件中对应不同实体



int i;// i 的全局声明，定义在全局命名空间中
namespace
{
    int i; // 二义性，i 既定义在全局命名空间中，又定义在嵌套的未命名的命名空间中
}




namespace local
{
    namespace
    {
        int j;
    }
}

local::j;// 正确，定义在嵌套的未命名的命名空间

// !! 未命名的命名空间取代文件中的静态声明

// 在标准 C++ 引入命名空间之前，程序需要将名字声明成 static 的以使其对于整个文件有效。
// 在文件中进行静态声明的做法是从 C 语言那里继承而来的。在 C 语言中，声明为 static 的全局实体在其所在的文件外不可见

// !! 在文件中进行静态声明的做法已经被 C ++ 取消掉了，现在的做法是使用未命名的命名空间


// !! 使用命名空间成员

// 1. 命名空间别名---使得我们可以为命名空间的名字设置一个短得多的同义词
namespace cplusplus_primer
{
    //...
}

namespace primer = cplusplus_prim；


// 2. using 声明：扼要概述
// using 声明语句一次只引入命名空间中的一个成员。using 声明引入的名字：它的有效范围从 using 声明的地方开始，一直到 using
// 声明所在的作用域结束为止

// 3. using 指示
// 与 using 声明的不同之处是：我们无法控制哪些名字可见，因为所以的名字都可见


// 命名空间 A 和函数 f 都定义在全局作用域中
namespace A
{
    int i,j;
}

void f()
{
    using namespace A;// using 指示，把 A 中的名字注入到全局作用域中
    cout << i*j << endl;// 使用命名空间 A 中的 i，j
}


namespace blip
{
    int i = 16；
    int j = 15;
    int k = 23;
    // ...
}

int j = 0;// 正确； blip 中的 j 隐藏在命名空间中

void manip()
{
    using namespace blip;// using 指示，把 blip 中的名字添加到全局作用域中
    ++i;// 将 blip::i 设置为 17
    ++j;// 二义性错误，是全局的 j 还是 blip::j
    ++::j;// 正确；使用全局命名空间中的 j
    ++blip::j;// 正确；使用 blip 命名空间中的 j
    int k = 97;// 当前局部的 k 隐藏 blip::k
    ++k;// k = 98
}


// !! 头文件与 using 声明和指示
// !! 头文件如果在其顶层作用域中含义 using 指示或者声明，则会将名字注入到所以包含该头文件的文件中
// 通常情况下，头文件应该只负责定义接口的名字，而不定义实现部分的名字。因此，头文件只能在它的函数或者命名空间内使用 using 声明或指示


// !! 相比于使用 using 指示，在程序中对命名空间中的每个成员使用 using 声明效果会更好，这样做可以减少注入到命名空间中名字数量


// !! 类、命名空间与作用域
namespace A
{
    int i;
    namespace B
    {
        int i;// 在 B 中隐藏了 A::i
        int j;
        int f1()
        {
            int j;// j 是函数 f1 的局部变量，隐藏了 A::B::j;
            return i;
        }
    }// 命名空间 B 结束，此时 B 中定义的名字不可见

    int f2()
    {
        return j;// 错误，j 没有被定义
    }

    int j = i;// 使用 A::i 进行初始化
}


// 对于位于命名空间中的类而言，常规查找规则仍然适用：
// 当成员函数使用某个名字时，首先在该函数进行查找，然后在类中进行查找（包括基类），接着在外层作用域中进行查找，
// 这时一个或者几个外层作用域有可能就是命名空间
namespace C
{
    int i, k;
    class C1
    {
    public:
        C1() : i(0), k(0) {}// 正确，初始化 C1::i 和 C1:;j
        int f1() { return k; }// 返回 A::k
        int f2() { return h; }// 错误，h 未定义
        int f3();

    private:
        int i;// 在 C1 中隐藏了 C::i
        int j;
    };
    int h = i;// 用 C::i 进行初始化
}

int C::C1::f3() { return h; }



// !! 实参相关的查找与类类型形参
// operator>> 定义在标准库 string， string 又定义在命名空间 std 中
// 但是我们不用 std:: 限定符和 using 声明就可以调用 operator>> 
std::string s;
operator>>(std::cin,s);

// !! 当我们给函数传递一个类类型对象时，除了在常规的作用域中查找外还会查找实参类所属的命名空间

// !! 友元函数与实参相关查找
namespace D
{
    class E
    {
        friend void f2();
        friend void f(const E&);
        //...
    };
}

// f2 和 f 是命名空间 D 的成员。即使 f 不存在其他声明，我们也能通过实参相关查找规则调用f

int main()
{
    D::E cobj;
    f(cobj);// 正确，通过 D::E 中的友元声明找到f
    f2();// 错误，D::f2 没有被声明
}

// !! 重载与命名空间
// 与实参相关的查找和重载

namespace NS
{
    class Quote{};
    void display(const Quote&){}
}

class Bulk_item : public NS::Quote {};

int main()
{
    Bulk_item book1;
    // 我们会在每个实参类（以及实参类的基类）所属的命名空间中搜寻候选函数。在这些命名空间中所有与被调函数同名的函数
    // 都将被添加到候选集中，即使其中某些函数在调用语句处不可见也是如此
    display(book1);
    return 0;
}

// !! 重载与 using 声明
// using 声明语句声明的是一个名字，而不是一个函数
// 当我们为函数书写 using 声明时，该函数的所有版本都会被引入当前作用域中
using NS::print;


