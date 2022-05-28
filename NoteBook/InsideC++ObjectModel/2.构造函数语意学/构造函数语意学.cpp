// !! 构造函数语意学

本章大量出现以下英文术语:

1. implicit: 暗中的、隐式的 (通常意指并非在程序源代码中出现的)

2. explicit: 显式的 (通常意指程序源代码中所出现的)

3. trivial: 没有用的

4. nontrivial: 有用的

5. memberwise: 对每一个 member 施以……

6. bitwise: 对每一个 bit 施以……

7. semantics: 语意


关于 C++, 最常听到的一个抱怨就是, 编译器背着程序员做了太多事情。

Conversion 运算符就是最常被引用的一个例子。Jerry Schwarz, iostream 函数库的建筑师, 就曾经说过一个故事。

他说他最早的意图是支持一个 iostream class object 的标量测试 (scalar test), 像这样:

if(cin){
    ...
}

为了让 cin 能够求得一个真假值, Jerry 首先为它定义一个 conversion 运算符: operator int()。

在良好行为如上者, 这的确可以正确运行。但是在下面这种错误的程序设计中, 它的行为就势必令人大吃一惊了:

cin << intValue << std::endl;

这个粗心的程序员要的应该是 cout 而不是 cin。Class 层次结构的 type-safe 天性应该能够捕捉这类输出运算符的错误运用。然而, 带有几分唯物主义色彩的编译器,比较喜
欢找到一个正确的诠释 (如果有的话), 而不只是把程序标示为错误就算了！

在此例中,内建的左移位运算符 (left shift operator, <<) 只有在 cin 可改变为和一个整数值同义时才适用。编译器会检查可以使用的各个 conversion 运算符,然后它
找到了 operator int(), 那正是它要的东西。左移位运算符现在可以操作了; 如果没有成功,至少也是合法的:

int temp = cin.operator int();
temp << intval;

Jerry 如何解决这个意想不到的行为? 他以 operator void*() 取代 operator int()。

在不少程序员之间, 存在一种忐忑不安的情绪,认为一个被编译器暗中施行的 user-defined conversion 运算符可能不会导致 Schwarz Error。事实上关键词 explicit
之所以被导入这个语言, 就是为了给程序员提供一种方法, 使他们能够制止"单一参数的 constructor"被当做一个 conversion 运算符。

问题出在编译器太过按照字面意义来解释你的意图, 而没有在背后为你多做点什么事情——虽然, 要让程序员相信他们被 Schwarz Error 盯上是颇为困难的。


// !! Default Constructor 的构造操作

C++Annotated Reference Manual 告诉我们: "default constructors…… 在需要的时候被编译器产生出来"。

关键字眼是"在需要的时候"。被谁需要? 做什么事情? 看看下面这段程序代码:

class Foo{
public:
  int val;
  Foo *p_next;
};

void foo_bar(){
    Foo bar;
    if(bar.val || bar.p_next){
        // do something
    }
}

在这个例子中, 正确的程序语意是要求 Foo 有一个 default constructor, 可以将它的两个 members 初始化为 0。

上面这段代码可曾符合 ARM 所说的在需要的时候? 答案是 no。其间的差别在于一个是程序的需要, 一是编译器的需要。程序如果有需要,那是程序员的责任; 本例要承担责任的
是设计 class Foo 的人。是的, 上述程序片段并不会合成出一个 default constructor。

那么, 什么时候才会合成出一个 default constructor 呢? 当编译器需要它的时候! 此外, 被合成出来的 constructor 只执行编译器所需的行动。也就是说, 即使有需要
为 class Foo 合成一个 default constructor, 那个 constructor 也不会将两个 data members val 和 pnext 初始化为 0。

为了让上一段代码正确执行, class Foo 的设计者必须提供一个显式的 default constructor, 将两个 members 适当地初始化。

C++Standard 已经修改了 ARM 中的说法,虽然其行为事实上仍然是相同的。C++Standard [ISO-C++95] 这么说:

'对于 class X, 如果没有任何 user-declared constructor, 那么会有一个 default constructor 被隐式 (implicitly) 声明出来……一个被隐式声明出来的 
default constructor 将是一个 trivial (浅薄而无能,没啥用的) constructor……'

C++Standard 然后开始一一叙述什么样情况下这个 implicit default constructor 会被视为 trivial。


// !! 带有 Default Constructor 的 Member Class Object


如果一个 class 没有任何 constructor, 但它内含一个 member object, 而后者有 default constructor, 那么这个 class 的 implicit default constructor
就是 nontrivial, 编译器需要为该 class 合成出一个 default constructor。不过这个合成操作只有在 constructor 真正需要被调用时才会发生。

于是出现了一个有趣的问题:在 C++ 各个不同的编译模块中,编译器如何避免合成出多个 default constructor (比如说一个是为 A.C 文件合成, 另一个是为 B.C 文件合成)
呢? 解决方法是把合成的 default constructor、copy constructor、destructor、assignment copy operator 都以 inline 方式完成。一个 inline 函数有静
态链接(static linkage), 不会被文件以外者看到。如果函数太复杂, 不适合做成 inline, 就会合成出一个 explicit non-inline static实例。

举个例子，在下面的程序片段中，编译器为 class Bar 合成一个 default constructor:

class Foo{
public:
  Foo();
  Foo(int);
};

class Bar{
public:
  Foo foo;
  char *str;
};


void foo_bar() {
    Bar bar;
    if(str){
        //do something
    }
}


被合成的 Bar default constructor 内含必要的代码, 能够调用  class Foo 的 default constructor 来处理 member object Bar::foo, 但它并不产生任何代
码来初始化 Bar::str。是的, 将 Bar::foo 初始化是编译器的责任, 将 Bar::str 初始化则是程序员的责任。被合成的 default constructor 看起来可能像这样:


inline Bar::Bar(){
    foo.Foo::Foo();
};


再一次请你注意, 被合成的 default constructor 只满足编译器的需要, 而不是程序的需要。


为了让这个程序片段能够正确执行, 字符指针 str 也需要被初始化。让我们假设程序员经由下面的 default constructor 提供了 str 的初始化操作:

Bar::Bar(){
    str = 0;
}

现在程序的需求获得满足了, 但是编译器还需要初始化 member object foo。由于 default constructor 已经被显式地定义出来,编译器没办法合成第二个。噢，伤脑筋。
你可能会这样说。编译器会采取什么行动呢?

编译器的行动是: 如果 class A 内含一个或一个以上的 member class objects, 那么 class A 的每一个 constructor 必须调用每一个 member classes 的 
default constructor。'编译器会扩张已存在的 constructors, 在其中安插一些代码, 使得 user code 被执行之前, 先调用必要的 default constructors'。

延续前一个例子, 扩张后的 constructors 可能像这样:

Bar::Bar(){
    foo.Foo::Foo();
    str = 0;
}

如果有多 class member objects 都要求 constructor 初始化操作, 将如何 ?

C++ 语言要求以 member objects 在 class 中的声明顺序来调用各个 constructors。这一点由编译器完成, 它为每一个 constructor 安插程序代码, 以 member 声明
顺序调用每一个 member 所关联的 default constructors。


举个例子, 假设我们有以下三个 classes:

class Dopey{
public:
  Dopey();
};

class Sneezy{
public:
  Sneezy();
};

class BashFull{
public:
  BashFull();
};

以及一个 class Snow_White:

class Snow_White{
public:
  Dopey dopey;
  Sneezy sneezy;
  BashFull bash;
  //...
private:
  int number;
};

如果 Snow_White 没有定义 default constructor, 就会有一个 nontrivial constructor 被合成出来, 依序调用 Dopey、Sneezy、Bashful 的 
default constructors。然而如果 Snow_White 定义了下面这样的 default constructor:

Snow_White::Snow_White() : sneezy(1024){
    number = 2048;
}


它会被扩张为:

Snow_White::Snow_White() : sneezy(1024){
    // insert member class objects
    dopey.Dopey::Dopey();
    sneezy.Sneezy::Sneezy();
    bashfull.BashFull::BashFull();

    // explict user code
    number = 2048;
}

// !! 带有 Default Constructor 的 Base Class

类似的道理, 如果一个没有任何 constructors 的 class 派生自一个带有 default constructor 的 base class, 那么这个 derived class 的 default 
constructor 会被视为 nontrivial, 并因此需要被合成出来。它将调用上一层 base classes 的 default constructor (根据它们的声明顺序)。对一个后继派生的 
class 而言, 这个合成的 constructor 和一个被显式提供的 default constructor 没有什么差异。

如果设计者提供多个 constructors, 但其中都没有 default constructor 呢? 编译器会扩张现有的每一个 constructors, 将用以调用所有必要之 default constructors
的程序代码加进去。


// !! 带有一个 Virtual Function 的 Class


另有两种情况, 也需要合成出 default constructor:

1. class声明 (或继承)一个 virtual function

2. class 派生自一个继承串链, 其中有一个或更多的 virtual base classes

不管哪一种情况, 由于缺乏由 user 声明的 constructors, 编译器会详细记录合成一个 default constructor 的必要信息。

以下面这个程序片段为例:

class Widget{
public:
  virtual void flip() = 0;
  //...
};

void flip(const Widget& widget){
    widget.flip();
}

// 假设 Bell 和 Whisker 都继承自 Widget
void foo(){
    Bell b;
    Whisker w;
    flip(b);
    flip(w);
}

下面两个扩张行动会在编译期间发生:

1. 一个 virtual function table 会被编译器产生出来, 内放 class 的 virtual functions 地址

2. 在每一个 class object 中, 一个额外的 pointer member 会被编译器合成出来, 内含相关之 class vtbl 的地址

此外, widget.flip() 的虚拟调用操作(virtual invocation)会被重新改写, 以使用 widget 的 vptr 和 vtbl 中的 flip() 条目:

(*widget.vptr[1])(&widget);

其中:

1 表示 flip() 在 virtual table 中的固定索引

&widget 代表要交给被调用的某个 flip() 函数实例的 this 指针

为了让这个机制发挥功效,编译器必须为每一个 Widget (或其派生类的) object 的 vptr 设定初值, 放置适当的 virtual table 地址。对于 class 所定义的每一个
constructor, 编译器会安插一些代码来做这样的事情。


对于那些未声明任何 constructors 的 classes, 编译器会为它们合成一个 default constructor, 以便正确地初始化每一个 class object 的 vptr。


// !! 带有一个 Virtual Base Class 的 Class

Virtual base class 的实现法在不同的编译器之间有极大的差异。然而, 每一种实现法的共同点在于必须使 virtual base class 在其每一个 derived class object
中的位置, 能够于执行期准备妥当。

例如在下面这段程序代码中:

class X{
public:
  int i;
};

class A : public virtual X{
public:
  int j;
};

class B : public virtual X{
public:
  double d;
};


class C : public A, public B{
public:
  int k;
};

// 无法在编译时期决定出 pa->X::i 的位置

void foo(const A* pa){
    pa->i = 100;
}

int main(){
    foo(new A());
    foo(new B());
    return 0;
}

编译器无法固定住 foo() 之中经由 pa 而存取的 X::i 的实际偏移位置, 因为 pa 的真正类型可以改变。编译器必须改变执行存取操作的那些代码, 使 X::i 可以延迟至执
行期才决定下来。

原先 cfront 的做法是靠在 derived class object 的每一个 virtual base classes 中安插一个指针完成。所有经由 reference 或 pointer 来存取一个
virtual base class 的操作都可以通过相关指针完成。在我的例子中, foo() 可以被改写如下, 以符合这样的实现策略:

void foo(const A* pa){
    pa->_vbcX->i = 100;
}

正如你所揣测的那样, _vbcX(或编译器所做出的某个什么东西)是在 class object 构造期间被完成的。

对于 class 所定义的每一个 constructor, 编译器会安插那些允许每一个 virtual base class 的执行期存取操作的代码。如果 class 没有声明任何 constructors,
编译器必须为它合成一个 default constructor。


// !! 总结

有 4 种情况, 会造成编译器必须为未声明 constructor 的 classes 合成一个 default constructor。

C++Standard 把那些合成物称为 implicit nontrivial default constructors。被合成出来的 constructor 只能满足编译器(而非程序)的需要。它之所以能够完成任
务, 是借着调用 member object 或 base class 的 default constructor 或是为每一个 object 初始化其 virtual function 机制或 virtual base class 机制
而完成的。

至于没有存在那 4 种情况而又没有声明任何 constructor 的 classes, 我们说它们拥有的是 implicit trivial default constructors, 它们实际上并不会被合成出来。

'在合成的 default constructor 中，只有 base class subobjects 和 member class objects 会被初始化'。

所有其他的 nonstatic data member (如整数、整数指针、整数数组等等) 都不会被初始化。这些初始化操作对程序而言或许有需要, 但对编译器则非必要。如果程序需要一个
把某指针设为 0的 default constructor, 那么提供它的人应该是程序员。


C++ 新手一般有两个常见的误解:

1. 任何 class 如果没有定义 default constructor, 就会被合成出一个来

2. 编译器合成出来的 default constructor 会显式设定 class 内每一个 data member 的默认值



// !! Copy Constructor 的构造操作


有三种情况, 会以一个 object 的内容作为另一个 class object 的初值。最明显的一种情况当然就是对一个 object 做显式的初始化操作, 像这样:

Class X{...};
X x;
X xx = x;

另两种情况是当 object 被当做参数交给某个函数时, 例如:

extern void foo(X x);

void bar(){
    X xx;
    foo(xx);
}

以及当函数传回一个 class object 时, 例如:














