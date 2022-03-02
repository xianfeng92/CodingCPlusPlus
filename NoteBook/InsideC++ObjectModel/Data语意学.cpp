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

'Nonstatic data members 在 class object 中的排列顺序将和其被声明的顺序一样', 任何中间介入的 static data members 如 freeList 和 chunkSize 
都不会被放进对象布局之中。

在上述例子里, 每一个 Point3d 对象是由三个 float 组成的, 顺序是 x、y、z。static data members 存放在程序的 data segment 中, 和个别的 
class objects 无关。

C++ Standard 要求, 在同一个 access section (也就是 private、public、protected 等区段)中, members 的排列只需符合"较晚出现的 members 在
class object 中有较高的地址" 这一条件即可。也就是说, 各个 members 并不一定得连续排列。什么东西可能会介于被声明的 members 之间呢 ? members
的边界调整(alignment) 可能就需要填补一些 bytes。

对于 C 和 C++ 而言这的确是真的, 对目前的 C++ 编译器实现情况而言, 这也是真的。


编译器还可能会合成一些内部使用的 data members, 以支持整个对象模型。vptr 就是这样的东西, 目前所有的编译器都把它安插在每一个"内含 virtual function 
之 class"的 object 内。

vptr 会被放在什么位置呢 ? 传统上它被放在所有显式声明的 members 的最后。不过如今也有一些编译器把 vptr 放在一个 class object 的最前端。

C++ Standard 秉承先前所说的"对于布局所持的放任态度", 允许编译器把那些内部产生出来的 members 自由地放在任何位置上, 甚至放在那些被程序员声明出来的
members 之间。

C++Standard 也允许编译器将多个 access sections 之中的 data members 自由排列, 不必在乎它们出现在 class 声明中的顺序。也就是说, 下面这样的声明:


class Point3d
{
public:

private:
    float x;
    static List<Point3d*> freeList;
private:
    float y;
    static const int chunkSize = 80;
private:
    float z;
};

其 class object 的大小和组成都和我们先前声明的那个相同, 但是 members 的排列顺序则视编译器而定。编译器可以随意把 y 或 z 或其他什么东西放在第一个,
不过据我所知, 目前没有任何编译器会这么做。

目前各家编译器都是把一个以上的 access sections 连锁在一起, 依照声明的顺序, 成为一个连续区块。Access sections 的多寡并不会招来额外负担。例如在一
个 section 中声明 8 个 members, 或是在 8 个 sections 中总共声明 8 个 members, 得到的 object 大小是一样的。


下面这个 template function, 接受两个 data members, 然后判断谁先出现在 class object 之中。如果两个 members 都是不同的 access sections 中的
第一个被声明者, 此函数就可以用来判断哪一个 section 先出现:

template<typename class_type, typename data_type1, typename data_type2>
char * accessOrder(data_type1 class_type::*mem1, data_type2 class_type::*mem2)
{
    assert(mem1 != mem2);
    return mem1  < mem2 ? "mem1 occurs first" : "mem2 occurs first";
}

上述函数可以这样被调用:

accessOrder(&Point3d::z, &Point3d::y);

于是 class_type 会被绑定为 Point3d, 而 data_type1 和 data_type2 会被绑定为 float。



// !! Data Member 的存取

已知下面这段程序代码:

Point3d origin;
origin.x = 10.12;

你可能会问 x 的存取成本是什么 ?

答案视 x 和 Point3d 如何声明而定。x 可能是个 static member, 也可能是个 nonstatic member。Point3d 可能是个独立(非派生)的 class, 也可能是从另一
个单一的 base class 派生而来; 虽然可能性不高, 但它甚至可能是从多重继承或虚拟继承而来的。

下面几节将依次检验每一种可能性。

在开始之前, 让我先抛出一个问题。如果我们有两个定义, origin 和 pt:

Point3d origin;
Point3d *pt = &origin;


通过 origin 存取, 和通过 pt 存取, 有什么重大差异吗? 如果你的回答是 yes, 请你从 class Point3d 和 data member x 的角度来说明差异的发生因素。我会在这
一节结束前重返这个问题并提出我的答案。


// !! Static Data Members

'Static data members, 按其字面意义, 被编译器提出于 class 之外,并被视为一个 global 变量(但只在 class 生命范围之内可见)'。每一个 member 的存取许
可(private、protected 或 public), 以及与 class 的关联, 并不会招致任何空间上或执行时间上的额外负担——不论是在个别的 class objects 还是在 
static data member 本身。

每一个 static data member 只有一个实例, 存放在程序的 global data segment 之中。每次程序取用 static member 时, 就会被内部转化为对该唯一 extern
实例的直接参考操作。例如:

Point3d::chunkSize = 25;

从指令执行的观点来看, 这是 C++ 语言中"通过一个指针和通过一个对象来存取 member, 结论完全相同"的唯一一种情况。这是因为"经由 member selection operators
(. 运算符) 对一个 static data member 进行存取操作" 只是文法上的一种便宜行事而已。member 其实并不在 class object 之中, 因此存取 static members 并
不需要通过 class object。


但如果 chunkSize 是一个从复杂继承关系中继承而来的 member, 又当如何? 或许它是一个" virtual base class 的 virtual base class" 的 member 也说不定。
哦, 那无关紧要, 程序之中对于 static members 还是只有唯一一个实例, 而其存取路径仍然是那么直接。


如果 static data member 是经由函数调用, 或其他某些语法而被存取呢? 举个例子, 如果我们写:

foobar().chunkSize;

调用 foobar() 会发生什么事情? 在 C++ 的准标准(pre-Standard)规格中, 没有人知道会发生什么事, 因为 ARM 并未指定 foobar() 是否必须被求值(evaluated)。
cfront 的做法是简单地把它丢掉。但 C++ Standard 明确要求 foobar() 必须被求值(evaluated), 虽然其结果并无用处。下面是一种可能的转化:

(void)foobar();
Point3d::chunkSize = 250;

'若取一个 static data member 的地址, 会得到一个指向其数据类型的指针', 而不是一个指向其 class member 的指针, 因为 static member 并不内含在一个
class object 之中。例如:

&Point3d::chunkSize;

会获得类型如下的内存地址:

const int *;


如果有两个 classes, 每一个都声明了一个 static member freeList, 那么当它们都被放在程序的 data segment 时, 就会导致名称冲突。编译器的解决方法是暗中对
每一个 static data member 编码(这种手法有个很美的名称: name-mangling), 以获得一个独一无二的程序识别代码。有多少个编译器, 就有多少种 name-mangling
做法! 通常不外乎是表格啦、文法措辞啦等。任何 name-mangling 做法都有两个重点:

1.一个算法, 推导出独一无二的名称

2.万一编译系统(或环境工具)必须和使用者交谈, 那些独一无二的名称可以轻易被推导回到原来的名称



// !! Nonstatic Data Members

Nonstatic data members 直接存放在每一个 class object 之中。除非经由显式的(explicit) 或隐式的(implicit) class object, 否则没有办法直接存取它们。
只要程序员在一个 member function 中直接处理一个 nonstatic data member, 所谓"implicit class object" 就会发生。

例如下面这段代码:

Point3d Point3d::translate(const Point3d &pt)
{
    x += pt.x;
    y += pt.y;
    z += pt.z;
}

表面上所看到的对于 x、y、z 的直接存取, 事实上是经由一个"implicit class object"(由 this 指针表达) 完成的。事实上这个函数的参数是:

Point3d Point3d::translate(Point3d *const this, const Point3d &py)
{
    this->x += py.x;
    this->y += py.y;
    this->z += py.z;
}


欲对一个 nonstatic data member 进行存取操作, 编译器需要把 class object 的起始地址加上 data member 的偏移位置(offset)。


origin._y = 0.3;

那么地址 &origin._y 将等于:

&origin + (&Point3d::_y - 1);

请注意其中的 -1 操作。指向 data member 的指针, 其 offset 值总是被加上 1, 这样可以使编译系统区分出"一个指向 data member 的指针, 用以指出 class 的
第一个 member" 和"一个指向 data member 的指针, 没有指出任何 member"两种情况。


每一个 nonstatic data member 的偏移位置(offset) 在编译时期即可获知, 甚至如果 member 属于一个 base class subobject(派生自单一或多重继承串链)也
是一样的。因此, 存取一个 nonstatic data member, 其效率和存取一个 C struct member 或一个 nonderived class 的 member 是一样的。

现在让我们看看虚拟继承。虚拟继承将为"经由 base class subobject 存取 class members" 导入一层新的间接性, 比如:

Point3d *pt;
pt->_x = 10.21;

其执行效率在 _x 是一个 struct member、一个 class member、单一继承、多重继承的情况下都完全相同。

但如果 _x 是一个 virtual base class 的 member, 存取速度会稍慢一点。


以两种方法存取 x 坐标, 像这样:

origin.x = 0.3;
pt->x = 0.3;


"从 origin 存取"和"从 pt 存取"有什么重大的差异?

答案是"当 Point3d 是一个 derived class, 而其继承结构中有一个 virtual base class, 并且被存取的 member 是一个从该 virtual base class 继承而来的
member "时, 就会有重大的差异。这时候我们不能够说 pt 必然指向哪一种 class type(因此, 我们也就不知道编译时期这个 member 真正的 offset 位置), 所以这个
存取操作必须延迟至执行期, 经由一个额外的间接导引, 才能够解决。但如果使用 origin, 就不会有这些问题, 其类型无疑是 Point3d class, 而即使它继承自 
virtual base class, members 的 offset 位置也在编译时期就固定了。一个积极进取的编译器甚至可以静态地经由 origin 就解决掉对 x 的存取。



// !! “继承”与Data Member

'在 C++ 继承模型中, 一个 derived class object 所表现出来的东西, 是其自己的 members 加上其 base class(es) members 的总和'。


至于 derived class members 和 base class(es) members 的排列顺序, 则并未在 C++Standard 中强制指定; 理论上编译器可以自由安排之。
在大部分编译器上, base class members 总是先出现, 但属于 virtual base class 的除外。


了解这种继承模型之后, 你可能会问, 如果我为 2D 或 3D 坐标点提供两个抽象数据类型如下:

class Point2d
{

private:
    float x, y;
};

class Point3d
{

private:
    float x, y, z;
};

这和"提供两层或三层继承结构, 每一层(代表一个维度)是一个 class, 派生自较低维层次" 有什么不同?


// !! 只要继承不要多态（Inheritance without Polymorphism）

想象一下, 程序员或许希望, 不论是 2D 或 3D 坐标点, 都能够共享同一个实例, 但又能够继续使用 "与类型性质相关(所谓 type-specific)" 的实例。

我们有一个设计策略, 就是从 Point2d 派生出一个 Point3d, 于是 Point3d 将继承 x 和 y 坐标的一切(包括数据实例和操作方法)。带来的影响则是可以共享"数据本身"
以及"数据的处理方法", 并将之局部化。

'一般而言, 具体继承(concrete inheritance, 相对于虚拟继承 virtual inheritance) 并不会增加空间或存取时间上的额外负担'。

class Point2d
{
public:
    Point2d(float x = 0.0f, float y = 0.0f):x_(x), y_(y){}
    float x() const {return x_;}
    float y() const {return y_;}
    void setX(float x) {x_ = x;}
    void setY(float y) {y_ = y;}

    void operator+=(const Point2d& other)
    {
        x_ += other.x_;
        y_ += other.y_;
    }

private:
    float x_;
    float y_;
};



class Point3d : public Point2d
{
public:
    Point3d(float x = 0.0f, float y = 0.0f, float z = 0.0f): Point2d(x, y), z_(z){}
    float z() const { return z_;}
    void setZ)(float z) { z_ = z}

    void operator+=(const Point3d &other)
    {
        Point2d::operator+=(other);
        z_ = other.z();
    }
private:
    float z_;
};

这样设计的好处就是可以把管理 x 和 y 坐标的程序代码局部化。此外, 这个设计可以明显表现出两个抽象类之间的紧密关系。当这两个 classes 独立的时候, 
Point2d object 和 Point3d object 的声明和使用都不会有所改变。所以这两个抽象类的使用者不需要知道 objects 是否为独立的 classes 类型, 或是彼此之间
有继承的关系。


把两个原本独立不相干的 classes 凑成一对 "type/subtype", 并带有继承关系, 会有什么易犯的错误呢 ?


'经验不足的人可能会重复设计一些相同操作的函数'。

以我们例子中的 constructor 和 operator+= 为例, 它们并没有被做成 inline 函数(也可能是编译器为了某些理由没有支持 inline member functions)。
Point3d object 的初始化操作或加法操作, 将需要部分的 Point2d object 和部分的 Point3d object 作为成本。

'一般而言, 选择某些函数做成 inline 函数, 是设计 class 时的一个重要课题'。


第二个易犯的错误是, 把一个 class 分解为两层或更多层, 有可能会为了"表现 class 体系之抽象化"而膨胀所需的空间。

C++ 语言保证"出现在 derived class 中的 base class subobject 有其完整原样性", 正是重点所在。这似乎有点难以理解! 最好的解释方法就是彻底了解一个
实例, 让我们从一个具体的 class 开始:


class Concrete
{
public:
    //...
private:
int value;
char c1;
char c2;
char c3;
};


在一台 32 位机器中, 每一个 Concrete class object 的大小都是 8 bytes, 细分如下:


1. value 占用 4 bytes

2. c1、c2 和 c3 各占用 1 bytes

3. alignment (调整到 word 边界)需要 1 bytes


现在假设, 经过某些分析之后, 我们决定了一个更逻辑的表达方式, 把 Concrete 分裂为三层结构:

class Concrete1
{
public:
    //...
private:
    int val1;
    char bit1;
};

class Concrete2 : public Concrete1
{
public:
    //...
private:
    char bit2;
};

class Concrete3 : public Concrete2
{
public:
    //...
private:
    char bit3;
};


从设计的观点来看, 这个结构可能比较合理。但从实现的观点来看, 我们可能会受困于一个事实:现在 Concrete3 object 的大小是 16 bytes, 比原先的设计多了
100%。 

怎么回事, 还记得" base class subobject " 在 derived class 中的原样性吗 ? 让我们踏遍这一继承结构的内存布局, 看看到底发生了什么事。

1. Concrete1 内含两个 members: val 和 bit1, 加起来是 5 bytes。而一个 Concrete1 object 实际用掉 8 bytes, 包括填补用的 3 bytes,
   以使 object 能够符合一台机器的 word 边界。不论是 C 或 C++ 都是这样。一般而言, 边界调整(alignment)是由处理器(processor)来决定的

2. 到目前为止没什么需要抱怨的。但这种典型的布局会导致轻率的程序员犯下错误。Concrete2 加了唯一一个 nonstatic data member bit2, 数据类型为 char。
   轻率的程序员以为它会和 Concrete1 捆绑在一起, 占用原本用来填补空间的 1 bytes; 于是 Concrete2 object 的大小为 8 bytes, 其中 2 bytes 用于填补
   空间。然而 Concrete2 的 bit2 实际上却是被放在填补空间所用的 3 bytes 之后。于是其大小变成 12 bytes, 不是 8 bytes。其中有 6 bytes浪费在填补空
   间上。相同的道理使得 Concrete3 object 的大小是 16 bytes, 其中 9 bytes 用于填补空间。

让我们声明以下一组指针:

Concrete2 *pc2;
Concrete1 *pc1_1;
Concrete1 *pc1_2;

其中 pc1_1 和 pc1_2 两者都可以指向前述三种 classes objects。下面这个指定操作:

*pc1_2 = *pc1_1;

应该执行一个默认的"memberwise"复制操作(复制一个个的 members)。如果 pc1_1 实际指向一个 Concrete2 object 或 Concrete3 object, 则上述操作应该将
复制内容指定给其 Concrete1 subobject。

然而, 如果 C++ 语言把 derived class members (也就是 Concrete2::bit2 或 Concrete3::bit3) 和 Concrete1 subobject 捆绑在一起, 去除填补空间,
上述那些语意就无法保留了。


// !! 加上多态（Adding Polymorphism）

如果我要处理一个坐标点, 而不打算在乎它是一个 Point2d 或 Point3d 实例, 那么我需要在继承关系中提供一个 virtual function 接口。让我们看看如果这么做, 
情况会有什么改变:

class Point2d {
public:
    Point2d(float x = 0.0f, float y = 0.0f) : x_(x), y_(y) {}

    // x y 的存取函数与前一版相同

    virtual float z();
    virtual void z(float value);

    virtual void operator+=(const Point2d& other);
    {
        x_ += other.x_;
        y_ += other.y_;
    }

private:
    float x_;
    float y_;
};

'只有当我们企图以多态的方式 (polymorphically) 处理 2d 或 3d 坐标点时, 在设计之中导入一个 virtual 接口才显得合理'。也就是说, 写下这样的代码:

void foo(Point2d &p1, Point2d &p2)
{
    p1 += p2;
}

其中, p1 和 p2 可能是 2d, 也可能是 3d 坐标点。这并不是先前任何设计所能支持的。'这样的弹性, 当然正是面向对象程序设计的中心'。支持这样的弹性, 势必对我
们的 Point2d class 带来空间和存取时间上的额外负担:

1. 导入一个和 Point2d 有关的 virtual table, 用来存放它所声明的每一个 virtual functions 的地址。这个 table 的元素个数一般而言是被声明的
   virtual functions 的个数, 再加上一个或两个 slots (用以支持 runtime type identification)。

2. 在每一个 class object 中导入一个 vptr, 提供执行期的链接, 使每一个 object 能够找到相应的 virtual table

3.  加强 constructor, 使它能够为 vptr 设定初值, 让它指向 class 所对应的 virtual table。这可能意味着在 derived class 和每一个 base class 的
    constructor 中, 重新设定 vptr 的值。其情况视编译器优化的积极性而定。

4.  加强 destructor, 使它能够抹消指向 class 之相关 virtual table 的 vptr。要知道, vptr 很可能已经在 derived class destructor 中被设定为
    derived class 的 virtual table 地址。记住, destructor 的调用顺序是反向的: 从 derived class 到 base class。一个积极的优化编译器可以压抑
    那些大量的指定操作

这些额外负担带来的冲击程度视被处理的 Point2d objects 的个数和生命期而定, 也视对这些 objects 做多态程序设计所得的利益而定。如果一个应用程序知道它所能使
用的 point objects 只限于二维坐标点或三维坐标点, 则这种设计所带来的额外负担可能变得令人无法接受。



以下是新的 Point3d 声明:

class Point3d : public Point2d
{
public:
    Point3d(float x = 0.0f, float y = 0.0f, float z = 0.0f) : Point2d(x, y), z_(z){}
    float z() const { return z_; }
    void z(float value) { z_ = value; }

    void operator+=(const Point2d& other)
    {
        Point2d::operator+=(other);
        z_ = other.z();
    }
private:
    float z_;
};

虽然 class 的声明语法没有改变, 但每一件事情都不一样了: 两个 z() member functions 以及 operator+=() 运算符都成了虚拟函数; 每一个 
Point3d class object 内含一个额外的 vptr member (继承自 Point2d); 多了一个 Point3d virtual table; 此外每一个 virtual member functions
的调用也比以前复杂了

目前在 C++ 编译器那个领域里有一个主要的讨论题目: 把 vptr 放置在 class object 的哪里会最好? 

在 cfront 编译器中, 它被放在 class object 的尾端。


到了 C++2.0, 开始支持虚拟继承以及抽象基类, 并且由于面向对象范式(OO paradigm)的兴起, 某些编译器开始把 vptr 放到 class object 的起头处。


// !! 多重继承（Multiple Inheritance）

单一继承提供了一种 自然多态 (natural polymorphism) 形式, 是关于 classes 体系中的 base type 和 derived type 之间的转换。


base class 和 derived class 的 objects 都是从相同的地址开始, 其间差异只在于 derived object 比较大, 用以多容纳它自己的 nonstatic data members。
下面这样的指定操作:

Point3d p3d;
Point2d *p2d = &p3d;

把一个 derived class object 指定给 base class (不管继承深度有多深) 的指针或 reference。这个操作并不需要编译器去调停或修改地址。它很自然地可以
发生, 而且提供了最佳执行效率。

例如, 考虑下面这个多重继承所获得的 class Vertex3d:

class Point2d{
public:
    //...
protected:
    float x_;
    float y_;
};


class Point3d : public Point2d
{
public:
    //...
protected:
    float z_;
};

class Vertex
{
public:
private:
    Vertex *next;
};


class Vertex3d : public Point3d, public Vector
{
public:
    //...
private:
    float mumble;
};



多重继承的问题主要发生于 derived class objects 和其第二或后继的 base class objects 之间的转换。不论是直接转换如下:


extern void mumble(const Vertex&);

Vertex3d v;
...
// 将一个 Vertex3d 转换为 Vertex 这是不自然的。
mumble(V);

或是经由其所支持的 virtual function 机制做转换。

对一个多重派生对象,  将其地址指定"最左端(也就是第一个) base class 的指针", 情况将和单一继承时相同, 因为二者都指向相同的起始地址。需付出的成本只有地址的
指定操作而已。至于第二个或后继的 base class 的地址指定操作, 则需要将地址修改过: 加上(或减去, 如果 downcast 的话)介于中间的 base class subobject的
大小, 例如:

Vertex3d v3d;
Vertex *pv;
Point2d *p2d;
Point3d *p3d;


那么下面这个指定操作:

pv = &v3d;

需要这样的内部转化:

// 虚拟 C++ 代码

pv - (Vertex*)((char*)&v3d + sizeof(Point3d));


而下面的指定操作:

p3d = &v3d;
p2d = &v3d;

都只需要简单地拷贝其地址就好。


C++Standard 并未要求 Vertex3d 中的 base classes Point3d 和 Vertex 有特定的排列顺序。原始的 cfront 编译器是根据声明顺序来排列它们的。
因此 cfront 编译器制作出来的 Vertex3d 对象, 将可被视为一个 Point3d subobject (其中又有一个 Point2d subobject) 加上一个 Vertex subobject, 
最后再加上 Vertex3d 自己的部分。目前各编译器仍然以此方式完成多重 base classes 的布局(但如果加上虚拟继承, 就不一样了)。


// !! 虚拟继承（Virtual Inheritance）

多重继承的一个语意上的副作用就是, 它必须支持某种形式的"shared subobject 继承"。


典型的一个例子是最早的 iostream library:

class ios{...};
class iostream : public ios{...};
class ostream : public ios{...};
class iostream : public istream, public ostream{...};


不论是 istream 还是 ostream 都内含一个 ios subobject。

然而在 iostream 的对象布局中, 我们只需要单一一份 ios subobject 就好。'语言层面的解决办法是导入所谓的虚拟继承':

class ios{...}
class istream : public virtual ios{...};
class ostream : public virtual ios{...};
class iostream : public istream, public ostream{...};


一如其语意所呈现的复杂度, 要在编译器中支持虚拟继承, 实在是难度颇高。


在上述 iostream 例子中, 实现技术的挑战在于, 要找到一个足够有效的方法, 将 istream 和 ostream 各自维护的一个 ios subobject, 折叠成为
为一个由 iostream 维护的单一 ios subobject, 并且还可以保存 base class 和 derived class 的指针(以及 references)之间的多态指定操作
(polymorphism assignments)。


一般的实现方法如下所述。Class 如果内含一个或多个 virtual base class subobjects, 像 istream 那样, 将被分割为两部分: 一个不变区域和一个共享区域。

不变区域中的数据, 不管后继如何衍化, 总是拥有固定的 offset(从 object 的开头算起), 所以这一部分数据可以被直接存取。至于共享区域, 所表现的就是
virtual base class subobject。这一部分的数据, 其位置会因为每次的派生操作而有变化, 所以它们只可以被间接存取。各家编译器实现技术之间的差异就在于间接
存取的方法不同。以下说明三种主流策略。

下面是 Vertex3d 虚拟继承的层次结构:

class Point2d
{
public:
    //...
private:
    float x_;
    float y_;
};


class Vertex : public Point2d
{
public:
    //...
protected:
    Vertex *next;
};


class Point3d : public virtual Point2d
{
public:
    //...
protected:
    float z_;
};


class Vertex3d : public Point3d, public Vertex
{
public:
    //...
private:
    float mumble;
};


一般的布局策略是先安排好 derived class 的不变部分, 然后再建立其共享部分。


然而, 这中间存在着一个问题: 如何能够存取 class 的共享部分呢?

cfront 编译器会在每一个 derived class object 中安插一些指针, 每个指针指向一个 virtual base class。要存取继承得来的 virtual base class members
, 可以通过相关指针间接完成。举个例子, 如果我们有以下的 Point3d 运算符:


void Point3d
operator+=(const Point3d & point)
{
    x_ += other.x_;
    y_ += other.y_;
    z_ += other.z_;
}



在 cfront 策略之下, 这个运算符会被内部转换为:


// 虚拟 C++ 代码

_vbcPoint2d->x_ += other._vbcPoint2d->x;
_vbcPoint2d->y_ += other._vbcPoint2d->y;
z_ += other.z_;

而一个 derived class 和一个 base class 的实例之间的转换, 像这样:


Point2d *p2d = pv3d;

在 cfront 实现模型之下, 会变成:

// 虚拟 C++ 代码
Point2d *p2d = pv3d ? pv3d->_vbc_Point2d : 0;

这样的实现模型有两个主要的缺点:

1. 每一个对象必须针对其每一个 virtual base class 背负一个额外的指针。然而理想上我们却希望 class object 有固定的负担, 不因为其 
   virtual base classes 的个数而有所变化。想想看这该如何解决?

2. 由于虚拟继承串链的加长, 导致间接存取层次的增加。这里的意思是, 如果我有三层虚拟派生, 我就需要三次间接存取(经由三个 virtual base class 指针)。然而
   理想上我们却希望有固定的存取时间, 不因为虚拟派生的深度而改变。


MetaWare 和其他编译器到今天仍然使用 cfront 的原始实现模型来解决第二个问题, 它们经由拷贝操作取得所有的 nested virtual base class 指针,放到
derived class object 之中。这就解决了"固定存取时间"的问题, 虽然付出了一些空间上的代价。


至于第一个问题, 一般而言有两个解决方法。

1. Microsoft 编译器引入所谓的 virtual base class table。每一个 class object 如果有一个或多个 virtual base classes, 就会由编译器安插一个指针, 
  指向 virtual base class table。至于真正的 virtual base class 指针, 当然是被放在该表格中

2. 第二个解决方法, 是在 virtual function table 中放置 virtual base class 的 offset(而不是地址)

上述每一种方法都是一种实现模型, 而不是一种标准。每一种模型都是用来解决存取 shared subobject 内的数据(其位置会因每次派生操作而有变化) 所引发的问题。
由于对 virtual base class 的支持带来额外的负担以及高度的复杂性, 每一种实现模型多少有点不同, 而且我想还会随着时间而进化。


经由一个非多态的 class object 来存取一个继承而来的 virtual base class 的 member, 像这样:

Point3d origin;
...
origin.x_ = 10;


'可以被优化为一个直接存取操作, 就好像一个经由对象调用的 virtual function 调用操作, 可以在编译时期被决议(resolved)完成一样'。在这次存取以及下一次存
取之间, 对象的类型不可以改变, 所以 virtual base class subobjects 的位置会变化的问题在此情况下就不再存在了。


// !! 一般而言, virtual base class 最有效的一种运用形式就是: 一个抽象的 virtual base class, 没有任何 data members。


// !! 对象成员的效率（Object Member Efficiency）


下面几个测试, 旨在测试聚合(aggregation)、封装(encapsulation)以及继承(inheritance)所引发的额外负荷的程度。


所有测试都是以个别局部变量的加法、减法、赋值(assign)等操作的存取成本为依据。下面就是个别的局部变量:

float pA_x = 0.321, pA_y = 0.12232, pA_z = 0.1231;
float pB_x = 12.31, pB_y = 31.312, pB_z 23.23123;

每个表达式需执行 1000 万次, 如下所示:

for(int i = 0; i < 10000000; i++)
{
    pB_x = pA_x - pB_z;
    pB_y = pA_y + pB_z;
    pB_z = pA_z + pB_y;
}


我们首先针对三个 float 元素所组成的局部数组进行测试:

enum fussy{x,y,z};
float pB[3] = {12.21,23,43,31.312};
float pA[3] = {12.12,0.213,0.12099};
for(int i = 0; i < 10000000; i++)
{
    pB[x] = pA[x] - pB[z];
    pB[y] = pA[y]+ pB[z];
    pB[z] = pA[z] + pB[y];
}

第二个测试是把同质的数组元素转换为一个 C struct 数据抽象类型, 其中的成员皆为 float, 成员名称是 x、y、z:

struct PP{
    float x;
    float y;
    float z;
};

PP pA;
PP pB;

for(int i = 0; i < 10000000; i++)
{
    pB.x = pA.x - pB.z;
    pB.y = pA.y+ pB.z;
    pB.z = pA.z + pB.y;
}


更深一层的抽象化, 是做出数据封装, 并使用 inline 函数。坐标点现在以一个独立的 Point3d class 来表示。我尝试两种不同形式的存取函数。第一, 我定义一
个 inline 函数, 传回一个 reference, 允许它出现在 assignment 运算符的两端:


class Point3d
{
public:
    Point3d(float x = 0.0f, float y = 0.0f, float z = 0.0f):x_(x), y_(y), z_(z){}

    float& x() {return x_;}
    float& y() {return y_;}
    float& z() {return z_;}

private:
    float x_;
    float y_;
    float z_;
};


那么真正对每一个坐标元素的存取操作应该像这样:

Point3d pA;
Point3d pB;

for(int i = 0; i < 10000000; i++)
{
    pB.x() = pA.x() - pB.z();
    pB.y() = pA.y()+ pB.z();
    pB.z() = pA.z() + pB.y();
}


我所定义的第二种存取函数形式是, 提供一对 get/set 函数:

float x() { return x_; }
void x(float x) { x_ = x; }

于是对每一个坐标值的存取操作应该像这样:

pB.x(pA.x() - pB.z());

这里所显示的重点在于, 如果把优化开关打开, "封装" 就不会带来执行期的效率成本。使用 inline 存取函数亦然。


// !! 指向Data Members的指针（Pointer to Data Members）

考虑下面的 Point3d 声明。其中有一个 virtual function, 一个static data member, 以及三个坐标值:

#include <iostream>

using namespace std;

class Point3d {
 public:
  Point3d(float x = 0.0f, float y = 0.0f, float z = 0.0f)
      : x_(x), y_(y), z_(z) {}
  virtual ~Point3d();
  //...
 private:
  static Point3d origin;
  float x_, y_, z_;
};

每一个 Point3d class object 含有三个坐标值, 依序为 x、y、z, 以及一个 vptr。至于 static data member origin, 则将被放在 class object
之外。唯一可能因编译器不同而不同的是 vptr 的位置。C++Standard 允许 vptr 被放在对象中的任何位置: 在起始处, 在尾端, 或是在各个 members 之间。
然而实际上, 所有编译器不是把 vptr 放在对象的头, 就是放在对象的尾。


那么, 取某个坐标成员的地址, 代表什么意思 ? 例如, 以下操作所得到的值代表什么:

&Point3d::z_;

上述操作将得到 z 坐标在 class object 中的偏移位置(offset)。


最低限度其值将是 x 和 y 的大小总和, 因为 C++ 语言要求同一个 access level 中的 members 的排列顺序应该和其声明顺序相同。

// !! 取一个 nonstatic data member 的地址, 将会得到它在 class 中的 offset
// !! 取一个绑定于真正 class object 身上的 data member 的地址，将会得到该 member 在内存中的真正地址


// !! 指向 Members 的指针的效率问题








