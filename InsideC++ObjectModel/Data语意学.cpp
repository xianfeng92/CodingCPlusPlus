// !! Data语意学（The Semantics of Data）


class X{};
class Y : public virtual X{};
class Z : public virtual X{};
class A : public Y, public Z{};


上述 X、Y、Z、A 中没有任何一个 class 内含明显的数据, 其间只表示了继承关系。所以发信者认为每一个 class 的大小都应该是 0。当然不对! 即使是 class X
小也不为 0:

#include <iostream>

using namespace std;

class X{};
class Y : public virtual X{};
class Z : public virtual X{};
class A : public Y, public Z{};

int main()
{
    cout << "sizeof X is " << sizeof(X) << endl;
    cout << "sizeof Y is " << sizeof(Y) << endl;
    cout << "sizeof Z is " << sizeof(Z) << endl;
    cout << "sizeof A is " << sizeof(A) << endl;

    return 0;
}


~/Stan/xforg/CodingCPlusPlus/InsideC++ObjectModel (main*) » g++ --std=c++11 datademo.cpp 
--------------------------------------------------------------------------------
~/Stan/xforg/CodingCPlusPlus/InsideC++ObjectModel (main*) » ./a.out
sizeof X is 1
sizeof Y is 8
sizeof Z is 8
sizeof A is 16


让我们依序看看每一个 class 的声明, 并看看它们为什么获得上述结果。

一个空的 class 如:

class X{};// sizeof(X) yield 1 bytes

事实上并不是空的, 它有一个隐藏的 1 byte 大小, 那是被编译器安插进去的一个 char。这使得这一 class 的两个 objects 得以在内存中配置独一无二的地址:

X a, b;
if(&a == &b)
{
    cerr << "nooooo";
}

Y 和 Z 的大小都是 8。这个大小和机器有关, 也和编译器有关。事实上 Y 和 Z 的大小受到三个因素的影响:

1. 语言本身所造成的额外负担(overhead) 当语言支持 virtual base classes 时, 就会导致一些额外负担。在 derived class 中, 这个额外负担反映在某种形式
   的指针身上, 它或者指向 virtual base class subobject, 或者指向一个相关表格; 表格中存放的若不是 virtual base class subobject 的地址, 就是其偏
   移位置(offset)

2. 编译器对于特殊情况所提供的优化处理 Virtual base class X subobject 的 1 bytes 大小也出现在 class Y 和 Z 身上。传统上它被放在 derived class
   的固定部分的尾端。某些编译器会对 empty virtual base class 提供特殊支持。

3. Alignment 的限制 class Y 和 Z 的大小截至目前为 5 bytes。在大部分机器上, 聚合的结构体大小会受到 alignment 的限制, 使它们能够更有效率地在内存中被
   存取。


编译器之间的潜在差异正说明了 C++ 对象模型的演化。这个模型为一般情况提供了解决之道。

当特殊情况逐渐被挖掘出来时,种种启发(尝试错误)法于是被引入,提供优化的处理。如果成功, 启发法于是就提升为普遍的策略,并跨越各种编译器而合并。它被视为标准
(虽然它并不被规范为标准), 久而久之也就成了语言的一部分。Virtual function table 就是一个好例子。


那么, 你期望 class A 的大小是什么呢 ? 很明显, 某种程度上必须视你所使用的编译器而定。

首先, 请你考虑那种并未特别处理 empty virtual base class 的编译器。如果我们忘记 Y 和 Z 都是"虚拟派生"自 class X, 我们可能会回答 16,毕竟 Y 和 Z 
的大小都是 8。然而当我们对 class A 施以 sizeof 运算符时, 得到的答案竟然是 12。到底是怎么回事呢?

记住, 一个 virtual base class subobject 只会在 derived class 中存在一份实例, 不管它在 class 继承体系中出现了多少次! 

class A 的大小由下列几点决定:

1. 被大家共享的唯一一个 class X 实例, 大小为 1 byte

2. Base class Y 的大小, 减去因 virtual base class X 而配置的大小结果是 4 bytes

3. Base class Z 的算法亦同。加起来是 8 bytes

4. class A 自己的大小: 0 byte

5. class A 的 alignment数量(如果有的话)。

前述三项总和, 表示调整前的大小是 9 bytes。class A 必须调整至 4 bytes 边界, 所以需要填补 3 bytes。结果是 12 bytes。


现在如果我们考虑那种 " 特别对 empty virtual base class 做了处理" 的编译器呢 ?

如前述, class X 实例的那 1 byte 将被拿掉, 于是额外的 3 bytes 填补额也不必了, 因此 class A 的大小将是 8 bytes。注意, 如果我们在 
virtual base class X 中放置一个(以上)的 data members, 两种编译器("有特殊处理"者和"没有特殊处理"者) 就会产生出完全相同的对象布局。



// !! 一个 class 的 data members, 一般而言, 可以表现这个 class 在程序执行时的某种状态。Nonstatic data members 放置的是"个别的 class object"
// !! 感兴趣的数据, static data members 则放置的是"整个 class"感兴趣的数据。

1. C++ 对象模型尽量以空间优化和存取速度优化的考虑来表现 nonstatic data members, 并且保持和 C 语言 struct 数据配置的兼容性。它把数据直接存放在每一个
   class object 之中。对于继承而来的 nonstatic data members (不管是 virtual 还是 nonvirtual base class)也是如此。不过并没有强制定义其间的排
   列顺序。

2. 至于 static data members, 则被放置在程序的一个 global data segment 中, 不会影响个别的 class object 的大小。在程序之中， 不管该 class 被产生
   出多少个 objects , static data members 永远只存在一份实例

每一个 class object 因此必须有足够的大小以容纳它所有的 nonstatic data members。有时候其值可能令你吃惊, 因为它可能比你想象的还大, 原因是: 

1. 由编译器自动加上的额外 data members, 用以支持某些语言特性(主要是各种 virtual 特性)

2. 因为 alignment(边界调整)的需要


// !! Data Member 的绑定（The Binding of a Data Member）

考虑下面这段程序代码:

// 某个 foo.h 头文件, 从某处含入
extern float x;

// 程序员 Point3d.h 的头文件
class Point3d
{
public:
    Point3d(float x, float y, float z)
    float x() const { return x; }
    void x(float x) { x = x;}
    //...
private:
    float x;
    float y;
    float z;
};


如果我问你 Point3d::X() 传回哪一个 x ? 是 class 内部那个 x, 还是外部(extern) 那个 x? 今天每个人都会回答我是内部那一个。这个答案是正确的,
但并不是从过去以来一直都正确!

在 C++ 最早的编译器上, 如果在 Point3d::X() 的两个函数实例中对 x 做出参阅(取用)操作, 该操作将会指向 global x object! 这样的绑定结果几乎普遍地
不在大家的预期之中, 并因此导出早期 C++ 的两种防御性程序设计风格:

1. 把所有的 data members 放在 class声明起头处, 以确保正确的绑定

class Point3d
{
private:
    float x;
    float y;
    float z;
public:
    Point3d(float x, float y, float z);
    float x() const { return x; }
    void x(float x) { x = x;}
    //...
};

2. 把所有的 inline functions, 不管大小都放在 class 声明之外

class Point3d
{
private:
    float x;
    float y;
    float z;
public:
    Point3d(float x, float y, float z);
    //...
};

inline float x() const { return x; }

inline void x(float x) { x = x;}


C++ Standard 以 "member scope resolution rules" 来精炼这个 "rewriting rule". 其效果是, 如果一个 inline 函数在 class 声明之后立刻被定义的
话, 那么就还是对其评估求值(evaluate)。也就是说, 当一个人写下以下这样的代码:

class Point3d
{
public:
    Point3d(float x, float y, float z)
    // 对于函数本体的分析将延迟,直到 class 声明的右大括号出现才开始
    float x() const { return x; }
    void x(float x) { x = x;}
    //...
private:
    float x;
    float y;
    float z;
};

'对 member functions 本体的分析, 会直到整个 class 的声明都出现了才开始'。


因此在一个 inline member function 躯体之内的一个 data member 绑定操作, 会在整个 class 声明完成之后才发生。然而, 这对于 member function
的 argument list 并不为真。Argument list 中的名称还是会在它们第一次遭遇时被适当地决议(resolved) 完成。


因此在 extern 和 nested type names 之间的非直觉绑定操作还是会发生。例如在下面的程序片段中, length 的类型在两个 member function signatures
中都决议(resolve) 为 global typedef, 也就是 int。当后续再有 length 的 nested typedef 声明出现时, C++ Standard 就把稍早的绑定标示为非法:

typedef int length;

class Point3d
{
public:
    Point3d(float x, float y, float z)
    // length 被决议为 global length
    // val_被决议为 Point3d::val_
    void mumble(length val) { val_ = val;}
    length mumble(){ return val_; }
    //...
private:
    // length 必须对 "本 class 对它的第一个操作" 之前被看见
    // 这样的声明将使先前的参考操作不合法
    typedef float length;
    length val_:
};

上述这个语言状况, 仍然需要某种防御性程序风格: 请总是把" nested type 声明" 放在 class 的起始处。在上述例子中, 如果把 length 的 nested typedef
定义于 "在 class 中被参考"之前, 就可以确保非直觉绑定的正确性。


// !! Data Member 的布局（Data Member Layout）


已知下面一组 data members:

class Point3d
{
public:
    //...
private:
    float x;
    static List<Point3d*> *freelist;
    float y;
    static const int chunkSize = 250;
    float z;
};

Nonstatic data members 在 class object 中的排列顺序将和其被声明的顺序一样, 任何中间介入的 static data members 如 freeList 和 chunkSize 都不
会被放进对象布局之中。







