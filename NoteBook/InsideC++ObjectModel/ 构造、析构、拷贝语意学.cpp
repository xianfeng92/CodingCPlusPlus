
// !!  构造、析构、拷贝语意学（Semantics of Construction，Destruction，and Copy）

考虑下面这个 abstract base class 声明:

class Abstract_base{
    public:
        virtual ~Abstract_base();
        virtual void interface() = 0;
        virtual const char* mumble() const {return mumble_;}

    protected:
    char* mumble_;
};

你看出了什么问题没有 ?

虽然这个 class 被设计为一个抽象的 base class (其中有 pure virtual function, 使得 Abstract_base 不可能拥有实例),但它仍然需要一个显式的构造函数
以初始化其 data member mumble_。


如果没有这个初始化操作, 其 derived class 的局部性对象 mumble_ 将无法决定初值, 例如:

class Concrete_derived : public Abstract_base
{
public:
    Concrete_derived();
    //...
private:
    //...
};

void foo(){
    // Abstract_base::mumble_ 未被初始化
    Concrete_derived trouble;
}


你可能会争辩说, 也许 Abstract_base 的设计者意图让其每一个 derived class 提供 mumble_ 的初值。然而如果是这样, derived class 的唯一要求就是
Abstract_base 必须提供一个带有唯一参数的 protected constructor:

Abstract_base::Abstract_base(char *mumble = 0):mumble_(mumble){}

一般而言, class 的 data member 应该被初始化, 并且只在 constructor 中或是在 class 的其他 member functions 中指定初值。其他任何操作都将破坏封
装性质, 使 class 的维护和修改更加困难。

当然,你也可能争辩说设计者的错误并不在于未提供一个 explicit constructor, 而是他不应该在抽象的 base class 中声明 data members。这是比较强而有力的论
点(把 interface 和 implementation 分离), 但它并不是行遍天下皆有理, 因为将"被共享的数据"抽取出来放在 base class 中, 毕竟是一种正当的设计。


// !! “无继承”情况下的对象构造


C++ 新手常常很惊讶地发现,一个人竟然可以定义和调用 (invoke) 一个 pure virtual function; 不过它只能被静态地调用 (invoked statically), 不能经由虚
拟机制调用。例如, 你可以合法地写下这段代码:

// ok,定义 pure virtual function
// 但只能被静态调用（invocate statically）
inline void Abstract_base::inteface() const
{
    //...
}

inline void Concrete_derived::inteface() const
{
    // ok, 静态调用（static invocation）
    Abstract_base::inteface();
    //...
}


要不要这样做, 全由 class 设计者决定。唯一的例外就是 pure virtual destructor: class 设计者一定得定义它。为什么?  因为每一个 derived class 
destructor 会被编译器加以扩张, 以静态调用的方式调用其 "每一个 virtual base class" 以及 "上一层 base class" 的 destructor。因此, 只要缺乏任
何一个 base class destructors 的定义, 就会导致链接失败。

你可能会争辩说, 难道对一个 pure virtual destructor 的调用操作, 不应该在"编译器扩张 derived class 的 destructor"时压抑下来吗? 不! class 设计者
可能已经真的定义了一个 pure virtual destructor 。这样的设计是以 C++ 语言的一个保证为前提: 继承体系中每一个 class object 的 destructors 都会被调
用。所以编译器不能够压抑这一调用操作。

你也可能争辩说, 难道编译器不应该有足够的知识"合成" (如果 class 设计者忘记定义或不知道要定义) 一个 pure virtual destructor 的函数定义吗? 不! 编译器的
确没有足够知识, 因为编译器对一个可执行文件采取"分离编译模型"之故。

一个比较好的替代方案就是, 不要把 virtual destructor 声明为 pure。


// !! 虚拟规格的存在（Presence of a Virtual Specification）

如果你决定把 Abstract_base::mumble() 设计为一个 virtual function, 那将是一个糟糕的选择, 因为其函数定义内容并不与类型有关, 因而几乎不会被后继的
derived class 改写。

一般而言, 把所有的成员函数都声明为 virtual function, 然后再靠编译器的优化操作把非必要的 virtual invocation 去除, 并不是好的设计理念。


// !! 虚拟规格中 const 的存在


// !! 重新考虑 class 的声明

class Abstract_base
{
public:
    virtual ~Abstract_base();
    virtual void interface() = 0;
    const char* mumble() const { return mumble_;}
protected:
    char* mumble_;
    Abstract_base(char* pd = 0);
};


考虑下面这个程序片段:

Point global;
Point foobar(){
    Point local;
    Point *pp = new Point();
    *pp = local;
    delete pp;
    return local;
}


L1、L5、L6 表现出三种不同的对象产生方式: global 内存配置、local 内存配置和 heap 内存配置。L7 把一个 class object 指定给另一个, L10 设定返回值, L9
则显式地以 delete 运算符删除 heap object。

// !! 一个 object 的生命, 是该 object 的一个执行期属性

1. local object 的生命从 L5 的定义开始, 到 L10 为止

2. global object 的生命和整个程序的生命相同

3. heap object 的生命从它被 new 运算符配置出来开始, 到它被 delete 运算符摧毁为止


下面是 Point 的第一次声明, 可以写成 C 程序。

// !!  C++Standard 说这是一种所谓的 Plain Old Data 声明形式:

typedef struct{
    float x, y, z;
} Point;


如果我们以 C++ 来编译这段代码, 会发生什么事?

观念上, 编译器会为 Point 声明一个 trivial default constructor、一个 trivial destructor、一个  trivial copy constructor, 以及一个
trivial copy assignment operator。

'但实际上, 编译器会分析这个声明, 并为它贴上 Plain Old Data 标签'。

当编译器遇到这样的定义:

Point global;

观念上 Point 的 trivial constructor 和 destructor 都会被产生并被调用, constructor 在程序起始(startup) 处被调用而 destructor 在程序的
exit() 处被调用 (exit() 是由系统产生的, 放在 main() 结束之前)。然而, 事实上那些 trivial members 要不是没被定义, 就是没被调用, 程序的行为一如
它在 C 中的表现一样。

唔, 只有一个小小的例外。在 C 中, global 被视为一个"临时性的定义", 因为它没有显式的初始化操作。一个"临时性的定义"可以在程序中发生多次。那些实例会被
链接器折叠起来, 只留下单独一个实例, 被放在程序 data segment 中一个"特别保留给未初始化之 global objects 使用"的空间。

由于历史的缘故, 这块空间被称为 BSS, 这是 Block Started by Symbol 的缩写, 是 IBM 704 assembler 的一个 pseudo-op。

C++ 并不支持"临时性的定义", 这是因为 class 构造行为的隐式应用之故。虽然大家公认这个语言可以判断一个 class objects 或是一个 Plain Ol'Data', 但似
乎没有必要搞得那么复杂。

// !! 因此, global 在 C++ 中被视为完全定义(它会阻止第二个或更多个定义)。

C 和 C++ 的一个差异就在于, BSS data segment 在 C++ 中相对地不重要。C++ 的所有全局对象都被以"初始化过的数据"来对待。


foobar() 函数中的 L5, 有一个 Point object local, 同样也是既没有被构造也没有被析构。当然啦, Point object local 如果没有先经过初始化, 可能会成
为一个潜在的程序"臭虫"---万一第一次使用它就需要其初值的话。

至于 heap object 在 L6 的初始化操作:

Point *heap = new Point();

会被转换为对 new 运算符 (由 library 提供) 的调用:

Point *heap = __new(sizeof(Point));

再一次强调一下, 并没有 default constructor 施行于 new 运算符所传回的 Point object 身上。

L7 对此 object  有个指派  (赋值,assign) 操作, 如果 local 曾被适当地初始化过, 一切就没有问题:

*heap = local;

观念上, 这样的指定操作会触发 trivial copy assignment operator 做拷贝搬运操作。然而实际上该 object 是一个 Plain Old Data, '所以赋值操
作(assignment) 将只是像 C 那样的纯粹位搬移操作'。


L9 执行一个 delete 操作:

delete heap;

会被转换为对  delete 运算符(由 library 提供)的调用:

_delete(heap);


观念上, 这样的操作会触发 Point 的 trivial destructor。但一如我们所见, destructor 要不是没有被产生就是没有被调用。最后, 函数以传值(by value)
的方式将 local 当做返回值传回, 这在观念上会触发 trivial copy constructor, 不过实际上 return 操作只是一个简单的位拷贝操作, 因为对象是个
Plain Old Data'。


// !! 抽象数据类型（Abstract Data Type）

以下是 Point 的第二次声明, 在 public 接口之下多了 private 数据, 提供完整的封装性, 但没有提供任何 virtual function:

class Point
{
public:
    Point(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x_(x), y_(y), z_(z){}
    // no copy constructor, copy operator
    // or destructor define

private:
    float x_, y_, z_;
};

这个经过封装的 Point class, 其大小并没有改变,还是三个连续的 float。是的,不论 private 或 public 存取层, 或是 member function 的声明, 都不会
占用额外的对象空间。

我们并没有为 Point 定义一个 copy constructor 或 copy operator, 因为默认的位语意( default bitwise semantics) 已经足够。我们也不需要提供一个
destructor, 因为程序默认的内存管理方法也已足够。

对于一个 global 实例:

Point global;// 实施 Point::Point(0.0,0.0,0.0);

现在有了 default constructor 作用于其上。由于 global 被定义在全局范畴中,其初始化操作将延迟到程序启动 (startup) 时才开始。

'如果要将 class 中的所有成员都设定常量初值, 那么给予一个 explicit initialization list 会比较有效率些'。

举个例子, 考虑下面这个程序片段:

void mumble(){
    Point local1 = {1.0,2.3,3.4};
    Point local2;
    local2._x = 10.0;
    local2._y = 2.3;
    local2._z = 3.4;
}


'local1 的初始化操作会比 local2 的有效率些'。这是因为当函数的 activation record 被放进程序堆栈时, 上述 initialization list 中的常量就可以被
放进 local1 内存中了。

Explicit initialization list 带来三项缺点:

1. 只有当 class members 都是 public, 此法才奏效

2. 只能指定常量, 因为它们在编译时期就可以被评估求值(evaluated)

3. 由于编译器并没有自动施行之, 所以初始化行为的失败可能性会高一些


那么, explicit initialization list 所带来的效率优点, 能够补偿其软件工程上的缺点吗?


一般而言, 答案是 no。然而在某些特殊情况下又不一样。例如, 或许你以手工打造了一些巨大的数据结构如调色盘(color palette), 或是你正要把一堆常量数
据(像是以 Alias 或 SoftImage 软件产生出来的复杂几何模型中的控制点和节点)倾倒给程序, 那么 explicit initialization list 的效率会比 inline
constructor 好得多, 特别是对全局对象(global object)而言。

在编译器层面,会有一个优化机制用来识别 inline constructors, 后者简单地提供一个 member-by-member 的常量指定操作。然后编译器会抽取出那些值,并且
对待它们就好像是  explicit initialization list 所供应的一样, 而不会把 constructor 扩展成为一系列的 assignment 指令。


于是, local Point object 的定义:

{
    Point local;
}

现在被附加上 default Point constructor 的 inline expansion:

{
    Point local;
    local.x_ = 0.0f;
    local.y_ = 0.0f;
    local.z_ = 0.0f;
}

L6 配置出一个 heap Point object:

Point *heap = new Point();

现在则被附加一个对 default Point constructor 的有条件调用操作:

Point *heap = _new(sizeof(Point));
if(heap != nullptr){
    heap->Point::Point();
}


然后才又被编译器进行 inline expansion 操作。至于把 local object 赋值给 heap 指针所指向的对象:

*heap = local;

则保持着简单的位拷贝操作。

以传值方式传回 local object, 情况也是一样:

return local;

L9 删除 heap 所指的对象:

delete heap;

该操作并不会导致 destructor 被调用, 因为我们并没有显式地提供一个 destructor 函数实例。

观念上, 我们的 Point class 有一个相关的 default copy constructor、copy operator、和 destructor。然而它们都是无关痛痒的(trivial), 而且编译
器实际上根本没有产生它们。


// !! 为继承做准备

我们的第三个 Point 声明, 将为"继承性质"以及某些操作的动态决议(dynamic resolution)做准备。目前我们限制对 z 成员做存取操作:

class Point
{
public:
    Point(float x = 0.0f, float y = 0.0f): x_(x), y_(y){}
    // no copy constructor, copy operator
    // no destructor defined
    virtual float z();
protected:
    float x_, y_;
};








