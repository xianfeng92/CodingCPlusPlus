// !! 站在对象模型的尖端

// !! Template

这一节的焦点放在 template 的语意上面, 我们将讨论 templates 在编译系统中"何时"、"为什么"以"如何"发挥其功能。

下面是有关 template 的三个主要讨论方向:

1. template 的声明。基本来说就是当你声明一个 template class、template class member function 等等时, 会发生什么事情

2. 如何实例化 (instantiates) class object、inline nonmember 以及 member template functions。这些是每一个编译单位都会拥有一份实例的东西

3. 如何实例化 (instantiates) nonmember、member template functions 以及 static template class members。这些都是每一个可执行文件中只需要
   一份实例的东西。这也就是一般而言 template 所带来的问题

// !! 使用实例化(instantiation)这个字眼来表示进程(process) 将真正的类型和表达式绑定到 template 相关形式参数(formal parameters)上头的操作


举个例子, 下面是一个 template function:

template<typename Type>
Type min(const Type & t1, const Type &t2);

用法如下:

min(1.0,2.0);

于是进程就把 Type 绑定为 double 并产生 min() 的一个程序文字实例(并适当施以 mangling, 给它一个独一无二的名称), 其中 t1 和 t2 的类型都是 double。


// !! Template 的实例化行为（Template Instantiation)

考虑下面的 template Point class:

template<typename Type>
class Point {
public:
    enum Status{unallocated, normalized}
    Point(Type x = 0.0, Type y = 0.0, Type z = 0.0){}
    ~Point();
    void * operator now(size_t);
    void operator delete(void *, size_t);
private:
    static Point<Type> *freelist;
    static int chunkSize;
    Type x, y, z;
};


首先, 当编译器看到 template class 声明时, 它会做出什么反应 ?在实际程序中, 什么反应也没有!也就是说, 上述的 static data members 并不可用。
nested enum 或其 enumerators 也一样。

虽然 enum Status 的真正类型在所有的 Point instantiations 中都一样, 但它们每一个都只能够通过 template Point class 的某个实例来存取或操作。因此我
们可以这样写:

Point<float>::Status s;


但不能这样写:

Point::Status s;

同样道理, freeList 和 chunkSize 对程序而言也还不可用。我们不能够写:

Point::freeList;

我们必须显式地指定类型, 才能使用 freeList:

Point<float>::freeList;

像上面这样使用 static member, 会使其一份实例与 Point class 的 float instantiation 在程序中产生关联。

如果我们写:

Point<double>::freeList;

就会出现第二个 freeList 实例, 与 Point class 的 double instantiation 产生关联。


如果我们定义一个指针, 指向特定的实例, 像这样:

Point<float> *ptr = nullptr;

再一次, 程序中什么也没有发生。为什么呢 ? 因为一个指向 class object 的指针, 本身并不是一个 class object, 编译器不需要知道与该 class 有关的任何
members 的数据或 object 布局数据。


所以将 Point 的一个 float 实例实例化也就没有必要了。

如果不是 pointer 而是 reference, 又如何? 假设:

const Point<float> &ref = 0;

是的, 它真的会实例化一个 Point 的 float 实例。这个定义的真正语意会被扩展为:

Point<float> temp(float(0));
const Point<float> &ref = temp;


为什么 ? 因为 reference 并不是无物(no object)的代名词。0 被视为整数, 必须被转换为以下类型的一个对象:

Point<float> 

如果没有转换的可能, 这个定义就是错误的, 会在编译时被挑出来。

// !! 所以, 一个 class object 的定义, 不论是由编译器暗中地做, 或是由程序员像下面这样显式地做:

const Point<float> origin;

都会导致 template class 的实例化, 也就是说, float instantiation 的真正对象布局会被产生出来。


回顾先前的 template 声明, 我们看到 Point 有三个 nonstatic members, 每一个的类型都是 Type。Type 现在被绑定为 float, 所以 origin 的配置空间必
须足够容纳三个 float 成员。

然而, member functions (至少对于那些未被使用过的) 不应该被"实例化"。只有在 member functions 被使用的时候,C++Standard才要求它们被实例化。目前的
编译器并不精确遵循这项要求。之所以由使用者来主导"实例化"(instantiation)规则, 有两个主要原因:

1. 空间和时间效率的考虑。如果 class中有 100 个 member functions, 但你的程序只针对某个类型使用其中两个,针对另一个类型使用其中五个, 那么将其他 193 
   个函数都实例化将会花费大量的时间和空间

2. 尚未实现的机能。并不是一个 template 实例化的所有类型就一定能够完整支持一组 member functions 所需要的所有运算符。如果只实例化那些真正用到的 
   member functions, template 就能够支持那些原本可能会造成编译时期错误的类型(types)


举个例子, origin 的定义需要调用 Point 的 default constructor 和 destructor, 那么只有这两个函数需要被"实例化"。

类似的道理, 当程序员写:

Point<float> *ptr = new Point<float>;

时, 只有:

1. Point template 的 float 实例

2. new 运算符

3. default constructor 需要被实例化

有趣的是, 虽然 new 运算符是这个 class 的一个 implicitly static member, 以至于它不能够直接处理其任何一个 nonstatic members, 但它还是依赖真正的
template 参数类型, 因为它的第一参数 size_t 代表 class 的大小。


这些函数在什么时候实例化? 目前流行两种策略:

1. 编译的时候。那些函数将实例化于 origin 和 p 存在的那个文件中

2. 在链接的时候。那么编译器会被一些辅助工具重新激活。template 函数实例可能被放在这一文件中、别的文件中或一个分离的存储位置


// !! Template 中的名称决议法 (Name Resolution within a Template)

你必须能够区分以下两种意义。一种是 C++Standard 所谓的 scope of the template definition, 也就是 定义出 template 的程序端。另一种是 C++Standard
所谓的 scope of the template instantiation, 也就是实例化 template 的程序端。


第一种情况举例如下:

//scope of the template definition
extern double foo(double);

template<typename type>
class ScopeRules{
public:
    void invariant(){
        _member = foo(_val);
    }
    type type_dependent(){
        return foo(_member);
    }
    //...
private:
    int _val;
    int _member;
};


第二种情况举例如下:

extern int foo(int);

ScopeRules<int> srI;

在 ScopeRules template 中有两个 foo() 调用操作。在 scope of template definition 中, 只有一个 foo() 函数声明位于 scope 之内。然而在
scope of template instantiation, 两个 foo() 函数声明都位于 scope 之内。如果我们有一个函数调用操作:


srI.invariant();

那么, 在 invariant() 中调用的究竟是哪一个 foo() 函数实例呢?

// 调用的是哪个 foo 实例呢？？？
_member = foo(_val);

在调用操作的那一点上, 程序中的两个函数实例是:

extern double foo(double);
extern int foo(int);

而 _val 的类型是 int。那么你认为选中的是哪一个呢? 结果, 被选中的是直觉以外的那一个:

extern double foo(double);


Template之 中, 对于一个 nonmember name 的决议结果, 是根据这个 name 的使用是否与用以实例化该 template 的参数类型有关而决定的。如果其使用互不相关,
那么就以 scope of the template declaration 来决定 name。如果其使用互有关联, 那么就以 scope of the template instantiation 来决定 name。


在第一个例子中, foo() 与用以实例化 ScopeRules 的参数类型无关:

这是因为_val 的类型是 int; _val 是一个类型不会变动的 template class member。也就是说, 被用来实例化这个 template 的真正类型, 对于_val 的类型并没
有影响。

此外, 函数的决议结果只和函数的原型(signature)有关, 和函数的返回值没有关系。因此 _member 的类型并不会影响哪一个 foo() 实例被选中。


让我们另外看看与类型相关(type-dependent)的用法:

srI.type_dependent();

这个函数的内容如下:

return foo(_member);


它究竟会调用哪一个 foo() 呢?

这个例子很清楚地与 template 参数有关, 因为该参数将决定 _member 的真正类型。所以这一次 foo() 必须在 scope of the template instantiation 中决议,
本例中这个 scope 有两个 foo() 函数声明。由于 _member 的类型在本例中为 int, 所以应该是 int 版的 foo() 出线。如果 ScopeRules 以 double 类型实例化,
那么就应该是 double 版的 foo() 出线。


这意味着一个编译器必须保持两个 scope contexts:

1. scope of the template declaration, 用以专注于一般的 template class

2. scope of the template instantiation, 用以专注于特定的实例


编译器的决议(resolution) 算法必须决定哪一个才是适当的 scope, 然后在其中搜寻适当的 name


// !! Member Function 的实例化行为 Member Function Instantiation

对于 template 的支持, 最困难的莫过于 template function 的实例化(instantiation)。

下面是编译器设计者必须回答的三个主要问题:

1. 编译器如何找出函数的定义 ?

   答案之一是包含 template program text file, 就好像它是一个 header 文件一样。Borland 编译器就遵循这个策略。另一种方法是要求一个文件命名规则, 例如
   ,我们可以要求, 在 Point.h 文件中发现的函数声明, 其 template program text 一定要放置于文件 Point.C或Point.cpp 中, 依此类推。

2. 编译器如何能够只实例化程序中用到的 member functions ?

   解决办法之一就是, 根本忽略这项要求, 把一个已经实例化的 class 的所有 member functions 都产生出来。Borland 就是这么做的。
   另一种策略就是模拟链接操作, 检测看看哪一个函数真正需要, 然后只为它们产生实例。

3. 编译器如何阻止 member definitions 在多个 .o 文件中都被实例化呢

   解决办法之一就是产生多个实例, 然后从链接器中提供支持,只留下其中一个实例, 其余都忽略。另一个办法就是由使用者来导引模拟链接阶段的实例化策略, 决定哪些实
   例(instances) 才是所需求的。

目前, 不论是编译时期还是链接时期的实例化(instantiation)策略, 均存在以下弱点: 当 template 实例被产生出来时, 有时候会大量增加编译时间。很显然, 这将
是 template functions 第一次实例化时的必要条件。然而当那些函数被非必要地再次实例化, 或是当决定那些函数是否需要再实例化所花的代价太大时, 编译器的表现
令人失望!

C++ 支持 template 的原始意图可以想见是一个由使用者导引的自动实例化机制(use-directed automatic instantiation mechanism), 既不不需要使用者的介入,
也不需要相同文件有多次的实例化行为。但是这已被证明是非常难以达成的任务, 比任何人此刻所能想象的还要难。


// !! 执行期类型识别（Runtime Type Identification, RTTI）


// !! Type-Safe Downcast（保证安全的向下转换操作）

C++ 被吹毛求疵的一点就是,它缺乏一个保证安全的 downcast (向下转换操作)。只有在类型真的可以被适当转换的情况下,你才能够执行 downcast。

一个 type-safe downcast 必须在执行期对指针有所查询, 看看它是否指向它所展现(表达) 之 object 的真正类型。

因此, 欲支持 type-safe downcast, 在 object 空间和执行时间上都需要一些额外负担:

1. 需要额外的空间以存储类型信息 (type information), 通常是一个指针, 指向某个类型信息节点

2. 需要额外的时间以决定执行期的类型(runtime type),正如其名所示, 这需要在执行期才能决定

这样的机制面对下面这样平常的 C 结构, 会如何影响其大小、效率以及链接兼容性呢?

char * wintable[] = {"hello world, how are you?", "fine, and you ?"};

很明显, 它所导致的空间和效率上的不良后果甚为可观。

冲突发生在两组使用者之间:

1. 程序员大量使用多态(polymorphism), 并因而需要正统而合法的大量 downcast 操作

2. 程序员使用内建数据类型以及非多态设备, 因而不受各种额外负担所带来的不良后果

理想的解决方案是, 为两派使用者提供正统而合法的需要----虽然或许得牺牲一些设计上的纯度与优雅性。你知道要怎么做吗?

C++ 的 RTTI 机制提供了一个安全的 downcast 设备, 但只对那些展现多态(也就是使用继承和动态绑定)的类型有效。我们如何分辨这些? 编译器能否光看 class 的定义
就决定这个 class 用以表现一个独立的 ADT 还是一个支持多态的可继承子类型(subtype) ? 

1. 当然, '策略之一就是导入一个新的关键词',优点是可以清楚地识别出支持新特质的类型, 缺点则是必须翻新旧程序。

2. 另一个策略是'通过声明一个或多个 virtual functions 来区别 class 声明'。其优点是透明化地将旧有程序转换过来, 只要重新编译就好。缺点则是可能会将一个其
实并非必要的 virtual function 强迫导入继承体系的 base class 身上。从编译器的角度来看, 这个策略还有其他优点, 就是大量降低额外负担。所有 polymorphic 
classes 的 objects 都维护了一个指针vptr, 指向 virtual function table。只要我们把与该 class 相关的 RTTI object 地址放进 virtual table 中
(通常放在第一个 slot ), 那么额外负担就降低为: 每一个 class object 只多花费一个指针。这一指针只需被设定一次, 它是被编译器静态设定的。


// !! Type-Safe Dynamic Cast（保证安全的动态转换）


'dynamic_cast 运算符可以在执行期决定真正的类型'。

如果 downcast 是安全的(也就是说, 如果 base type pointer 指向一个 derived class object), 这个运算符会传回被适当转换过的指针。如果 downcast 不是
安全的, 这个运算符会传回 0。


下面就是我们如何重写我们原本的 cfront downcast:

typedef type *ptype;
typedef fct *pfct;

simplify_conv_op(ptype pt)
{
    if(pfct = dynamic_cast<fct*>(pt))
    {
        //...
    }
    else
    {
        //...
    }
}

什么是 dynamic_cast 的真正成本呢 ? 

pfct 的一个类型描述器会被编译器产生出来。由 pt 所指向的 class object 类型描述器必须在执行期通过 vptr 取得。下面就是可能的转换:

((type_info*))(pt->vptr[0])->_type_description;

type_info 是 C++Standard 所定义的类型描述器的 class 名称, 该 class 中放置着待索求的类型信息。virtual table 的第一个 slot 内含 type_info 
object 的地址; 此 type_info object 与 pt 所指的 class type 有关。'这两个类型描述器被交给一个 runtime library 函数, 比较之后告诉我们是否吻合'。
很显然这比 static cast 昂贵得多, 但却安全得多。



// !! References 并不是 Pointers

程序执行中对一个 class 指针类型施以 dynamic_cast 运算符, 会获得 true 或false:

1. 如果传回真正的地址, 则表示这一 object 的动态类型被确认了, 一些与类型有关的操作现在可以施行于其上

2. 如果传回 0, 则表示没有指向任何 object, 意味着应该以另一种逻辑施行于这个动态类型未确定的 object 身上


dynamic_cast 运算符也适用于 reference 身上。然而对于一个 non-type-safe cast, 其结果不会与施行于指针的情况相同。为什么? 一个 reference 不可以像指
针那样把自己设为 0 便代表了 no object; 若将一个 reference 设为0, 会引起一个临时性对象被产生出来, 该临时对象的初值为 0, 这个 reference 然后被设定成为
该临时对象的一个别名。因此当 dynamic_cast 运算符施行于一个 reference 时, 不能够提供对等于指针情况下的那一组 true/false。

取而代之的是, 会发生下列事情:

1. 如果 reference 真正参考到适当的 derived class, downcast 会被执行而程序可以继续进行

2. 如果 reference 并不真正是某一种 derived class, 那么, 由于不能够传回 0, 因此抛出一个 bad_cast exception


// !! Typeid 运算符

使用 typeid 运算符, 就有可能以一个 reference 达到相同的执行期替代路线:

simplify_conv_op(const type &rt)
{
    if(typeid(rt) == typeid(Fot))
    {
        Fot & fot = static_cast<Fot&>(rt);
        ...
    }
    else
    {
        //...
    }
}


// !! 7.4 效率有了，弹性呢？


传统的 C++ 对象模型提供有效率的执行期支持。这份效率, 再加上与 C 之间的兼容性, 造成了 C++ 的广泛被接受度。然而, 在某些领域方面, 像是动态共享函数
库(dynamically shared libraries)、共享内存(shared memory)以及分布式对象(distributed object)方面, 这个对象模型的弹性还是不够。


// !! 动态共享函数库(Dynamic Shared Libraries)

理想中, 一个动态链接的 shared library 应该像"突然造访"一样。也就是说, 当应用程序下一次再执行时, 会透明化地取用新的 library 版本。新的 library 问世
不应该对旧的应用程序产生侵略性, 应用程序不应该需要为此重新建造(building)一次。

然而, 在目前的 C++ 对象模型中, 如果新版 library 中的 class object 布局有所变更, 上述的 library 无侵略性 说法便有待商榷了。这是因为 class 的大小
及其每一个直接(或继承而来)的 members 的偏移位置 offset 都在编译时期就已经固定。

这虽然带来了效率, 却在二进制层面(binary level) 阻碍了弹性。如果 object 布局改变, 应用程序就必须重新编译(building)。


// !! 共享内存(Shared Memory)


当一个 shared library 被加载时, 它在内存中的位置由 runtime linker 决定, 一般而言与执行中的进程(process)无关。