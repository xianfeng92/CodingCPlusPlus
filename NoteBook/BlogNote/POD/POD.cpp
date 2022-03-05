
//!! POD


// !! 概述

很久很久以前, C 语言统一了江湖。几乎所有的系统底层都是用 C 写的, 当时定义的基本数据类型有 int、char、short long 等整数类型、浮点类型(float, double)、
枚举(enum)、void、指针、数组、结构(struct)等等。然后只要碰到一串 01010110010 之类的数据, 编译器都可以正确的把它解析出来。

那么到了 C++ 诞生之后, 出现了继承、派生这样新的概念, 于是就诞生了一些新的数据结构。比如某个派生类, C 语言中哪有派生的概念啊, 遇到这种数据编译器就不认识
了。可是我们的计算机世界里, 主要的系统还是用 C 写的啊, 为了和旧的 C 数据相兼容, C++ 就提出了 POD 数据结构概念。


POD 是 Plain Old Data 的缩写, 是 C++ 定义的一类数据结构概念, 比如 int、float 等都是 POD 类型的。'Plain 代表它是一个普通类型, Old 代表它是旧的,
与几十年前的 C 语言兼容, 那么就意味着可以使用 memcpy() 这种最原始的函数进行操作'。两个系统进行交换数据, 如果没有办法对数据进行语义检查和解释, 那就只能以
非常底层的数据形式进行交互, 而'拥有 POD 特征的类或者结构体通过二进制拷贝后依然能保持数据结构不变'。也就是说, '能用 C 的 memcpy() 等函数进行操作的类、结
构体就是 POD 类型的数据'。


基本上谈到这个概念, 一般都是说某某 class、struct、union 是不是 POD 类型的。

// !! POD 的特征

是不是 POD 类型的, 可以用 is_pod<T>::value 来判断。那什么样的类、结构体是拥有 POD 特性的呢?

要求有两个: 一个是它必须很平凡、很普通; 另一个是布局有序。

// !! 能平凡就平凡

trival(平凡)是个概念:

1. 不能写构造/析构函数、拷贝/移动构造函数、拷贝/移动运算符, 而是用编译器自动为我们生成, 那这个数据就是"平凡的"。非要写的话, 用 C++ 11 的
  default 关键字

例如下列代码用 std::is_trivial<T>::value 来判断是否"平凡":

#include <iostream>


using namespace std;

class A{
    public:
    int max(int x, int y){return x > y ? x : y;}
};

class B{
    public:
        B(){}
};

class C{
    public:
        C() = default;
};

int main()
{
    // yield 1
    cout << "A is trivial is " << std::is_trivial<A>::value << endl;
    // yield 0
    cout << "B is trivial is " << std::is_trivial<B>::value << endl;
    // yield 1
    cout << "C is trivial is " << std::is_trivial<C>::value << endl;
    return 0;
}

2. '不能有 虚函数 和 虚基类'。

'只要满足以上条件, 就是拥有平凡(trival)特征的数据类型'


//!! 布局要有序

除了平凡(trivial)之外, 还对布局有要求。为了便于理解讲述, 我们把'非静态数据称为普通数据'。


1. 普通成员有相同的访问级别

   例如下面的类, 因为 a 和 b 的访问级别不一样, 所以布局无序, 自然就不是 POD 类型的数据。当然, 如果 b 写成 static int b, 例子中的 A 类就是 POD 类
   型的了。所以一定要看清每个字, 是"普通成员"。

class A{
    public:
        int a;
    private:
        int b;
};


2. 第一个成员必须是自己的

class A{
    int a;
};

class A1 : public A
{
    A a;
    int A1;// 错了，第一个必须是 A1 的数据成员
};


3. 只要有父类, 普通成员只能在其中一个类中,不可分散

class A{
    int a;
};

class A1 : public A{
    int b;// 普通成员只能在其中一个类中
};


// !! 如何使用 POD 类型的数据?

具有 POD 性质的数据可以使用 C 语言中的 memcpy() 等底层函数, 那我们来看看怎么用。



