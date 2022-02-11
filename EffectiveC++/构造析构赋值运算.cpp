
// !! 构造/析构/赋值运算

几乎你写的每一个 class 都会有一或多个构造函数、一个析构函数、一个 copy assignment 操作符。这些很难让你特别兴奋，毕竟它们是你的基本谋生工具，控制着基础操作，
像是产出新对象并确保它被初始化、摆脱旧对象并确保它被适当清理、以及赋予对象新值。如果这些函数犯错，会导致深远且令人不愉快的后果，遍及你的整个 classes。所以确保
它们行为正确是生死攸关的大事。


// !! 条款05：了解C++默默编写并调用哪些函数

什么时候 empty class(空类)不再是个 empty class 呢？

当 C++ 处理过它之后。是的，如果你自己没声明，编译器就会为它声明(编译器版本的)一个 copy 构造函数、一个 copy assignment 操作符和一个析构函数。此外如果你没有声
明任何构造函数，编译器也会为你声明一个 default 构造函数。所有这些函数都是 public 且 inline 。


因此，如果你写下：

class Empty{...}

这就好像你写下这样的代码:

class Empty
{
public:
    Empty(){...}
    Empty(const Empty & rhs){...}
    ~Empty(){...}

    Empty& operator=(const Empty &rhs){...}

};


'惟有当这些函数被需要(被调用)，它们才会被编译器创建出来'。程序中需要它们是很平常的事。下面代码造成上述每一个函数被编译器产出:

Empty e1; //
Empty e2(e1); //
e2 = e1;

好，我们知道了，编译器为你写函数，但这些函数做了什么呢？

唔，'default 构造函数和析构函数主要是给编译器一个地方用来放置“藏身幕后”的代码，像是调用 base classes 和 non-static 成员变量的构造函数和析构函数'。注意，编
译器产出的析构函数是个 non-virtual，除非这个 class 的 base class 自身声明有 virtual 析构函数(这种情况下这个函数的虚属性 virtualness；主要自 base class)。


copy 构造函数和 copy assignment 操作符，编译器创建的版本只是单纯地将来源对象的每一个 non-static 成员变量拷贝到目标对象。

考虑一个 NamedObject template，它允许你将一个个名称和类型为 T 的对象产生关联:

template<typename  T>
class NamedObject
{
public:
    NamedObject(const char * name, const T &value);
    NamedObject(const std::string &name, const T &value);
    ...

private:
    std::string nameValue;
    T objectValue;
};

由于其中声明了一个构造函数，编译器于是不再为它创建 default 构造函数。这很重要，意味如果你用心设计一个 class，其构造函数要求实参，你就无须担心编译器会毫无挂虑地
为你添加一个无实参构造函数（即 default 构造函数）而遮盖掉你的版本。


NamedObject 既没有声明 copy 构造函数，也没有声明 copy assignment 操作符，所以编译器会为它创建那些函数(如果它们被调用的话)。

现在，看看 copy 构造函数的用法:

NamedObject<int> no1("hello",2);
NamedObject<int> no2(no1);// call copy constructor

编译器生成的 copy 构造函数必须以 no1.nameValue 和 no1.objectValue 为初值设定 no2.nameValue 和 no2.objectValue。两者之中，nameValue 的类型是 string
，而标准 string  有个 copy 构造函数，所以 no2.nameValue 的初始化方式是调用 string 的 copy 构 造 函 数 并 以 no1.nameValue 为实参。objectValue 的类型是
int(因为对此 template 具现体而言 T 是 int)，那是个内置类型，所以 no2.objectValue 会以拷贝 no1.objectValue 内的每一个bits 来完成初始化。


如果你打算在一"内含 reference 成员"的 class 内支持赋值操作(assignment)，你必须自己定义 copy assignment 操作符。面对内含const成员的 classes，编译器的反
应也一样。更改 const 成员是不合法的，所以编译器不知道如何在它自己生成的赋值函数内面对它们。


请记住

■ 编译器可以暗自为 class 创建 default构造函数、copy 构造函数、copy assignment 操作符，以及析构函数。


// !! 条款06：若不想使用编译器自动生成的函数, 就该明确拒绝

地产中介商卖的是房子，一个中介软件系统自然而然想必有个 class 用来描述待售房屋:

class HomeForSale{...}

每一位真正的地产中介商都会说，任何一笔资产都是天上地下独一无二，没有两笔完全相像。因此我们也认为，为 HomeForSale 对象做一份副本有点没道理。你怎么可以复制某些
先天独一无二的东西呢？

因此，你应该乐意看到 HomeForSale 的对象拷贝动作以失败收场:

HomeForSale h1;
HomeForSale h2;
HomeForSale h3(h1);// 企图拷贝 h1---不该通过编译
h1 = h2;// 企图拷贝 h2---不该通过编译

啊呀，阻止这一类代码的编译并不是很直观。'通常如果你不希望 class 支持某一特定机能，只要不声明对应函数就是了'。但这个策略对 copy 构造函数和 copy assignment
操作符却不起作用，因为如果你不声明它们，而某些人尝试调用它们，编译器会为你声明它们。

这把你逼到了一个困境。如果你不声明 copy构造函数 或 copy assignment 操作符，编译器可能为你产出一份，于是你的 class 支持 copying。如果你声明它们，你的
class 还是支持 copying。但这里的目标却是要阻止 copying！

答案的关键是，所有编译器产出的函数都是 public。为阻止这些函数被创建出来，你得自行声明它们，但这里并没有什么需求使你必须将它们声明为 public。因此你可以将
copy构造函数或 copy assignment 操作符声明为 private。

class HomeForSale
{
public:
    ...
private:
    HomeForSale(const HomeForSale &rhs);
    HomeForSale &operator=(const HomeForSale & rhs);
};

or

class HomeForSale
{
public:
    HomeForSale(const HomeForSale &rhs) = delete;
    HomeForSale &operator=(const HomeForSale &rhs) = delete;
}；


请记住

■ 为驳回编译器自动（暗自）提供的机能，可将相应的成员函数声明为 private 并且不予实现或者使用 delete 关键字



// !! 条款07：为多态基类声明 virtual 析构函数

有许多种做法可以记录时间，因此，设计一个 TimeKeeper base class 和一些 derived classes 作为不同的计时方法，相当合情合理:

class TimeKeeper
{
public:
    TimeKeeper();
    ~TimeKeeper();
    ...
};

class AtomicTimeKeeper : public TimeKeeper{ }// 原子钟
class WaterTimeKeeper : public TimeKeeper{ }// 水中
class WriesTimeKeeper : public TimeKeeper{ }//腕表

许多客户只想在程序中使用时间，不想操心时间如何计算等细节，这时候我们可以设计 factory 函数，返回指针指向一个计时对象。

TimeKeeper *getTimeKeeper();// 返回一个指针，指向一个 TimeKeeper 派生类动态分配的对象

为遵守 factory 函数的规矩，被 getTimeKeeper() 返回的对象必须位于 heap。因此为了避免泄漏内存和其他资源，将 factory 函数返回的每一个对象适当地 delete 
掉很重要：

TimeKeeper * ptk = getTimeKeeper();
...

delete ptk;

条款 13 说"倚赖客户执行 delete 动作，基本上便带有某种错误倾向"，条款 18 则谈到 factory 函数接口该如何修改以便预防常见之客户错误，但这些在此都是次要的，因为
此条款内我们要对付的是上述代码的一个更根本弱点:"纵使客户把每一件事都做对了，仍然没办法知道程序如何行动"。


问题出在 getTimeKeeper 返回的指针指向一个 derived class 对象(如 AtomicClock)，而那个对象却经由一个 base class 指针(例如一个 TimeKeeper* 指针)
被删除，而目前的 base class(TimeKeeper) 有个 non-virtual 析构函数。

这是一个引来灾难的秘诀，因为 C++ 明白指出，当 derived class 对象经由一个 base class 指针被删除，而该 base class 带着一个 non-virtual 析构函数，其结
果未有定义——实际执行时通常发生的是对象的 derived 成分没被销毁。

消除这个问题的做法很简单: 给 base class 一个 virtual 析构函数。此后删除 derived class 对象就会如你想要的那般。是的，它会销毁整个对象，包括所有 
derived class  成分:

class TimeKeeper
{
public:
    TimeKeeper();
    virtual ~TimeKeeper();
    ...
};


像 TimeKeeper 这样的 base classes 除了析构函数之外通常还有其他 virtual 函数，因为 virtual 函数的目的是允许 derived class 的实现得以定制化
(见条款 34)。

例如 TimeKeeper 就可能拥有一个 virtual getCurrentTime，它在不同的 derived classes 中有不同的实现码。任何 class 只要带有 virtual 函数都几乎确定应
该也有一个 virtual 析构函数。

如果 class 不含 virtual 函数，通常表示它并不意图被用做一个 base class。当 class 不企图被当作 base class，令其析构函数为 virtual 往往是个馊主意。

考虑一个用来表示二维空间点坐标的 class:

class point
{
public:
    Point(int x, int y);
    ~Point();
private:
    int x, y;
};


如果 int 占用 32 bits，那么 Point 对象可塞入一个 64-bit 缓存器中。更有甚者，这样一个 Point 对象可被当做一个“64-bit 量”传给以其他语言如 C 或FORTRAN撰
写的函数。然而当 Point 的析构函数是 virtual，形势起了变化。

'欲实现出 virtual 函数，对象必须携带某些信息，主要用来在运行期决定哪一个 virtual 函数该被调用'。这份信息通常是由一个所谓 vptr（virtual table pointer）指
针指出。'vptr 指向一个由函数指针构成的数组，称为 vtbl（virtual table）'；每一个带有 virtual 函数的 class 都有一个相应的 vtbl。

当对象调用某一 virtual 函数，实际被调用的函数取决于该对象的 vptr 所指的那个 vtbl——编译器在其中寻找适当的函数指针。

virtual 函数的实现细节不重要。重要的是如果 Point class 内含 virtual 函数，其对象的体积会增加: 在 32-bit 计算机体系结构中将占用 64 bits(为了存放两个 
ints)至 96 bits(两个 ints 加上 vptr)；在 64-bit 计算机体系结构中可能占用 64～128 bits，因为指针在这样的计算机结构中占 64 bits。因此，为 Point 添加一个
vptr 会增加其对象大小达 50%～100%！Point 对象不再能够塞入一个 64-bit 缓存器，而 C++ 的 Point 对象也不再和其他语言（如 C）内的相同声明有着一样的结构
(因为其他语言的对应物并没有 vptr)，因此也就不再可能把它传递至（或接受自）其他语言所写的函数，除非你明确补偿 vptr——那属于实现细节，也因此不再具有移植性。



因此，无端地将所有 classes 的析构函数声明为 virtual，就像从未声明它们为 virtual 一样，都是错误的。

许多人的心得是：只有当 class 内含至少一个 virtual 函数，才为它声明 virtual 析构函数。

即使 class 完全不带 virtual 函数，被“non-virtual析构函数问题”给咬伤还是有可能的。举个例子，标准 string 不含任何 virtual 函数，但有时候程序员会错误地把
它当做 base class:

class SpecialString : public std::string// 馊主意，std::string 有两个 non virtual 析构函数
{
...
};

乍看似乎无害，但如果你在程序任意某处无意间将一个 pointer-to-SpecialString  转换为一个 pointer-to-string，然后将转换所得的那个 string 指针 delete 掉，
你立刻被流放到“行为不明确”的恶地上:


SpecialString *ss = new SpecialString("hello world");
std::string *ps;
...
ps = ss;
...
delete ps;


相同的分析适用于任何不带 virtual 析构函数的 class，包括所有 STL 容器如 vector，list，set，tr1::unordered_map 等等。

如果你曾经企图继承一个标准容器或任何其他"带有 non-virtual 析构函数" 的 class，拒绝诱惑吧！

有时候令 class 带一个 pure virtual 析构函数，可能颇为便利。还记得吗，pure virtual 函数导致 abstract classes -- 也就是不能被实体化(instantiated)
的 class。

然而有时候你希望拥有抽象 class，但手上没有任何 pure virtual 函数，怎么办？

唔，由于抽象 class 总是企图被当作一个 base class 来用，而又由于 base class 应该有个 virtual 析构函数，并且由于 pure virtual 函数会导致抽象 class，
因此解法很简单: 为你希望它成为抽象的那个 class 声明一个 pure virtual 析构函数。

下面是个例子:

class AWOV
{
public:
    virtual ~AWOV() = 0;
};

这个 class 有一个 pure virtual 函数，所以它是个抽象 class，又由于它有个 virtual 析构函数，所以你不需要担心析构函数的问题。然而这里有个
窍门：你必须为这个 pure virtual 析构函数提供一份定义:

AWOV::~AWOV(){}


'析构函数的运作方式是，最深层派生(most derived)的那个 class 其析构函数最先被调用，然后是其每一个 base class 的析构函数被调用'。'编译器会在 AWOV 的
derivedclasses 的析构函数中创建一个对 ～AWOV 的调用动作，所以你必须为这个函数提供一份定义'。如果不这样做，连接器会发出抱怨。

请记住

■ polymorphic (带多态性质的) base classes 应该声明一个 virtual 析构函数。如果 class 带有任何 virtual 函数，它就应该拥有一个 virtual 析构函数

■ Classes 的设计目的如果不是作为 base classes 使用，或不是为了具备多态性(polymorphically)，就不该声明 virtual 析构函数


// !! 条款08：别让异常逃离析构函数


