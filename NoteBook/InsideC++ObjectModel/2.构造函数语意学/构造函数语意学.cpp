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

X foo_bar(){
    X xx;
    return xx;
}


假设 class 设计者显式定义了一个 copy constructor, 像下面这样:


X::X(const X& x);
Y::Y(const Y& y, int = 0);

那么在大部分情况下, 当一个 class object 以另一个同类实例作为初值, 上述的 constructor 会被调用。这可能会导致一个临时性  class object 的产生或导致程序代
码的蜕变(或两者都有)。



// !! Default Memberwise Initialization


如果 class 没有提供一个 explicit copy constructor 当如何? 

当 class object 以相同 class 的另一个 object 作为初值, 其内部是以所谓的 default memberwise initialization 手法完成的, 也就是把每一个内建的或派生的
data member 的值, 从某个 object 拷贝一份到另一个 object 身上。不过它并不会拷贝其中的 member class object, 而是以递归的方式施行 memberwise 
initialization。


例如, 考虑下面这个 class 声明:

class String{
public:
  //...
private:
  char* str;
  int len;
};

一个 String object 的 default memberwise initialization 发生在这种情况之下:

String noun = "Book";
String verb = noun;

其完成方式就好像个别设定每一个 members 一样:

verb.str = noun.str;
verb.len = noun.len;


如果一个 String object 被声明为另一个 class 的 member, 像这样:


class Word{
public:
  //...
private:
  int occurs_;
  String word_;
};

那么一个 Word object 的 default memberwise initialization 会拷贝其内建的 member occurs_, 然后再于 String member object word_ 身上递归实施 
memberwise initialization。

这样的操作实际上如何完成? ARM 告诉我们:

概念上而言, 对于一个 class X, 这个操作是被一个 copy constructor 实现出来的……

其中主要的字眼是“概念上”。这个注释又紧跟着一些解释:

一个良好的编译器可以为大部分 class objects 产生 bitwise copies, 因为它们有 bitwise copy semantics……

也就是说, 如果一个 class 未定义出 copy constructor, 编译器就自动为它产生出一个这句话不对, 而是应该像 ARM 所说:

Default constructors 和 copy constructors 在必要的时候才由编译器产生出来。

这个句子中的"必要"意指当 class 不展现 bitwise copy semantics 时。

一个 class object 可用两种方式复制得到, 一种是被初始化, 另一种是被指定(assignment)。从概念上而言, 这两个操作分别是以 copy constructor 和
copy assignment operator 完成的。


和以前一样, C++Standard 把 copy constructor 区分为 trivial 和 nontrivial 两种。只有 nontrivial 的实例才会被合成于程序之中。

决定一个 copy constructor 是否为 trivial 的标准在于 class 是否展现出所谓的 bitwise copy semantics。

// !! Bitwise Copy Semantics (位逐次拷贝)

在下面的程序片段中:

#include "Word.h"

Word noun("Book");
void foo(){
    Word verb = noun;
    //...
}

很明显 verb 是根据 noun  来初始化的。但是在尚未看过class Word 的声明之前, 我们不可能预测这个初始化操作的程序行为。


如果 class Word 的设计者定义了一个 copy constructor, verb 的初始化操作会调用它。但如果该 class 没有定义 explicit copy constructor, 那么是否会有一
个编译器合成的实例被调用? 这就得视该 class 是否展现 bitwise copy semantics 而定了。

举个例子, 已知下面的 class Word 声明:

class Word{
public:
  Word(const char *);
  ~Word(){
      delete[] str;
  }
private:
  int cnt;
  char *str;
};

这种情况下并不需要合成出一个 default copy constructor, 因为上述声明展现了 default copy semantics, 而 verb 的初始化操作也就不需要以一个函数调用收场。

然而, 如果 class Word 是这样声明:

class Word{
public:
  Word(const String&);
  ~Word();
private:
  String str;
};


其中 String 声明了一个 explicit copy constructor:

class String{
public:
  String(const char*);
  String(const String&);
  ~String();
};


这种情况下, 编译器必须合成出一个copy constructor, 以便调用 member class String object 的 copy constructor


inline Word::Word(const Word& wd){
    str.String::String(wd.str);
    cnt = wd.cnt;
}

有一点很值得注意: 在这被合成出来的 copy constructor 中, 如整数、指针、数组等等的 non class members 也都会被复制, 正如我们所期待的一样。


// !! 不要 Bitwise Copy Semantics


什么时候一个 class 不展现出 bitwise copy semantics  呢? 有 4 种情况:

1. 当 class 内含一个 member object 而后者的 class 声明有一个 copy constructor 时

2. 当 class 继承自一个 base class 而后者存在一个 copy constructor 时

3. 当 class 声明了一个或多个 virtual functions 时

4. 当 class 派生自一个继承串链, 其中有一个或多个 virtual base classes 时


在前两种情况中, 编译器必须将 member 或 base class 的 copy constructors 调用操作安插到被合成的 copy constructor 中。


// !! 重新设定 Virtual Table 的指针

回忆编译期间的两个程序扩张操作(只要有一个 class 声明了一个或多个 virtual functions 就会如此):

■ 增加一个 virtual function table (vtbl), 内含每一个有作用的 virtual function 的地址

■ 一个指向 virtual function table 的指针(vptr), 安插在每一个 class object 内


很显然, 如果编译器对于每一个新产生的 class object 的 vptr 不能成功而正确地设好其初值, 将导致可怕的后果。因此, 当编译器导入一个 vptr 到 class 之中时,该
 class 就不再展现 bitwise semantics 了。

现在, 编译器需要合成出一个 copy constructor 以求将 vptr 适当地初始化, 下面是个例子。


首先, 我定义两个 class, ZooAnimal 和 Bear:

class ZooAnimal{
public:
  ZooAnimal();
  virtual ~ZooAnimal();
  virtual void animate();
  virtual void draw();
  //...
private:
  //...
};


class Bear: public ZooAnimal{
public:
  Bear();
  void animate();
  void draw();
  virtual void dance();
  //...
private:
  //...
};

ZooAnimal class object 以另一个 ZooAnimal class object 作为初值, 或 Bear class object 以另一个 Bear class object 作为初值, 都可以直接靠
bitwise copy semantics 完成。

举个例子:

Bear yogi;
Bear winnie = yogi;

yogi 会被 default Bear constructor 初始化。而在 constructor 中, yogi 的 vptr 被设定指向 Bear class 的 virtual table (靠编译器安插的代码完成)。
因此,  把 yogi 的 vptr 值拷贝给 winnie 的 vptr 是安全的。


当一个 base class object 以其 derived class 的 object 内容做初始化操作时, 其 vptr 复制操作也必须保证安全,例如:

ZooAnimal franny = yogi;

franny 的 vptr 不可以被设定指向 Bear class 的 virtual table (但如果 yogi 的 vptr 被直接 bitwise copy 的话, 就会导致此结果), 否则当下面程序片段中
的 draw() 被调用而 franny 被传进去时, 就会炸毁(blow up):

void draw(const ZooAnimal& za){
    za.draw();
}

void foo(){
    draw(yogi);
    draw(franny);
}


也就是说, 合成出来的 ZooAnimal copy constructor 会显式设定 object 的 vptr 指向 ZooAnimal class  的 virtual table, 而不是直接从右手边的
class object 中将其 vptr 现值拷贝过来。


// !! 处理 Virtual Base Class Subobject

// !! 程序转化语意学

Program TransformationSemantics

已知下面的程序片段:

#include "X.h"

X foo(){
  X xx;
  //...
  return xx;
}


一个人可能会做出以下假设:

1. 每次 foo() 被调用, 就传回 xx 的值

2. 如果 class X 定义了一个 copy constructor, 那么当 foo() 被调用时, 保证该 copy constructor 也会被调用

第一个假设的真实性, 必须视 class X 如何定义而定。第二个假设的真实性, 虽然也部分地必须视 class X 如何定义而定, 但最主要的还是视你的 C++  编译器所提供的进取
性优化层级(degree of aggressive optimization) 而定。

一个人甚至可以假设在一个高质量的 C++ 编译器中, 上述两点对于 class X 的 nontrivial definitions 都不正确。


// !! 显式的初始化操作（Explicit Initialization）


已知有这样的定义:

X x0;

面的三个定义, 每一个都明显地以 x0 来初始化其 class object:

void foo_bar() {
  X x1(x0);
  X x2 = x0;
  X x3 = X(x0);
  //...
}

必要的程序转化有两个阶段:


1. 重写每一个定义, 其中的初始化操作会被剥除 (这里所谓的"定义"是指上述的 x1, x2, x3 三行; 在严谨的 C++ 用词中, "定义"是指"占用内存"的行为)

2. class的 copy constructor 调用操作会被安插进去


举个例子, 在明确的双阶段转化之后, foo_bar() 可能看起来像这样:

void foo_bar() {

  // 重写每一个定义,其中的初始化操作会被剥除
  X x1;
  X x2;
  X x3;

  // 编译器安插  X copy construction 的调用操作
  x1.X::X(x0);
  x2.X::X(x0);
  x3.X::X(x0);
  return 0;
}

其中的:

x1.X::X(x0);

就表现出对以下的 copy constructor 的调用:

X::X(const X& x){

}



// !! 参数的初始化 (Argument Initialization)


C++Standard 说, 把一个 class object 当做参数传给一个函数(或是作为一个函数的返回值), 相当于以下形式的初始化操作:

X xx = arg;

其中 xx 代表形式参数(或返回值), 而 arg 代表真正的参数值。因此, 若已知这个函数:

void foo(X xx);

下面这样的调用方式:

X xx;
foo(xx);


将会要求局部实例(local instance) x0 以 memberwise 的方式将 xx 当做初值。

在编译器实现技术上, 有一种策略是导入所谓的临时性 object, 并调用 copy constructor 将它初始化, 然后将此临时性 object 交给函数。

例如将前一段程序代码转换如下:

//  C++ 伪代码
// 编译器所产生出来的临时性对象
X __temp0;

// 编译器对 Copy constructor 的调用
__temp0.X::X(xx);

// 重新改写函数的调用, 以便使用上述临时对象
foo(__temp0);

然而这样的转换只做了一半功夫而已。你看出遗留问题了吗?  问题出在 foo() 的声明上。临时性 object 先以 class X 的 copy constructor 正确地设定了初值, 然后再
以 bitwise 方式拷贝到 x0 这个局部实例中。噢, 真讨厌, foo() 的声明因而也必须被转化, 形式参数必须从原先的一个 class X object 改变为一个 class X 
reference, 像这样:

void foo(const X& x);

其中 class X 声明了一个 destructor,  它会在 foo() 函数完成之后被调用, 对付那个临时性的 object。


另一种实现方法是以"拷贝建构"(copy construct) 的方式把实际参数直接建构在其应该的位置上, 此位置视函数活动范围的不同, 记录于程序堆栈中。在函数返回之前,局部对
象(local object) 的 destructor 会被执行。Borland C++ 编译器就是使用此法, 但它也提供一个编译选项,用以指定前一种做法, 以便和其早期版本兼容。


// !! 返回值的初始化 (Return Value Initialization)

已知下面这个函数定义:

X bar() {
  X xx;
  // 处理 xx
  return xx;
}


你可能会问 bar() 的返回值如何从局部对象 xx 中拷贝过来?


Stroustrup 在 cfront 中的解决做法是一个双阶段转化:

1. 首先加上一个额外参数,类型是 class object 的一个 reference。这个参数将用来放置被"拷贝建构(copy constructed)"而得的返回值

2. 在 return 指令之前安插一个 copy constructor 调用操作, 以便将欲传回之 object 的内容当做上述新增参数的初值

真正的返回值是什么? 最后一个转化操作会重新改写函数, 使它不传回任何值。根据这样的算法, bar() 转换如下:

// 函数转换
// 以反映出 Copy Constructor 的应用
// C++ 伪代码

void bar(X& _result) {// 加了一个额外参数
  X xx;
  // 编译器所产生的的 Default Constructor 的调用
  xx.X::X();
  //...
  // 编译器所产生的 Copy Constructor 的调用
  _result.X::X(xx);
  return;
}

现在编译器必须转换每一个 bar() 调用操作, 以反映其新定义。例如:

X xx = bar();

将被转换为下列两个指令句:

X xx;
bar(xx);

而:

bar().memfunc();

可能被转换为:

// 编译器所产生的的临时性对象
X _temp0;
(bar(_temp0), temp0).memfunc();


同理, 如果程序声明了一个函数指针, 像这样:

X(*pf)();
pf = bar();

它也必须被转化为:

void(*Pf)(X);
pf = bar();



// !! 在使用者层面做优化（Optimization at the User Level）

我相信始作俑者是 Jonathan Shopiro! 他对于像 bar() 这样一个函数, 最先提出"程序员优化"的观念: 定义一个"计算用"的 constructor。
换句话说程序员不再写:

X bar(const T& y, const T& z){
  X xx;
  // 以 y 和 x 来处理 xx
  return xx;
}

那会要求 xx 被"memberwise"地拷贝到编译器所产生的 _result 之中。

Jonathan 定义另一个 constructor, 可以直接计算 xx 的值:

X bar(const T& y, const T& z){
  return X(y, z);
}

于是当 bar() 的定义被转换之后, 效率会比较高:

// C++ 伪代码
void bar(X& _result){
  _result.X::X(y, z);
  return;
}


_result 被直接计算出来, 而不是经由 copy constructor 拷贝而得!

不过, 这种解决方法受到某种批评, 怕那些特殊计算用途的 constructor 可能会大量扩散。在这个层面上, class 的设计是以效率考虑居多, 而不是以"支持抽象化"为优先。


// !! 在编译器层面做优化 (Optimization at the Compiler Level)

在一个像 bar() 这样的函数中, 所有的 return 指令传回相同的具名数值, 因此编译器有可能自己做优化, 方法是以 result 参数取代 named return value。

X bar(){
  X xx;
  //...
  return xx;
}

编译器把其中的 xx 以 _result 取代:

void bar(X& _result){
  _result.X::X();
  //... 直接处理 _result
  return;
}

这样的编译器优化操作, 有时候被称为 Named Return Value (NRV)优化。

NRV 优化如今被视为标准  C++ 编译器的一个义不容辞的优化操作——虽然其需求其实超越了正式标准之外。为了对效率的改善有所感觉, 请你想想下面的代码:

class test{
  friend test_foo(double);
public:
  test(){
    memset(array, 0, 100*sizeof(double));
  }
private:
  double array[100];
};

同时请考虑以下函数, 它产生、修改并传回一个 test class object。

test foo(double val) {
  test local;

  local.array[0] = val;
  local.array[99] = val;
  return local;
}

有一个 main() 函数调用上述 foo() 函数 1000 万次:

int main(int argc, char* argv[]){
  for(int i = 0; i < 1000000; i++){
    test t = foo(double(i));
  }
  return 0;
}


一般而言, 面对"以一个 class object 作为另一个 class object 的初值"的情形, 语言允许编译器有大量的自由发挥空间。其利益当然是导致机器码产生时有明显的效
率提升。缺点则是你不能够安全地规划你的 copy constructor 的副作用, 必须视其执行而定。


// !! Copy Constructor: 要还是不要?

已知下面的 3D 坐标点类:

class Point3d{
public:
  Point3d(float x, float y, float z);
  //...
private:
  float x_, y_, z_;
};

这个 class 的设计者应该提供一个 explicit copy constructor 吗?

上述 class 的 default copy constructor 被视为 trivial。它既没有任何  member (或base) class objects 带有 copy constructor, 也没任何的
virtual base class 或 virtual function。


所以, 默认情况下, 一个 Point3d class object 的  memberwise 初始化操作会导致"bitwise copy"。这样的效率很高, 但安全吗?

答案是 yes。三个坐标成员是以数值来存储的。bitwise copy 既不会导致 memory leak, 也不会产生 address aliasing。因此,它既快速,又安全。

那么, 这个 class 的设计者应该提供一个 explicit copy constructor 吗?

你将如何回答这个问题? 答案当然很明显是 no。没有任何理由要你提供一个 copy constructor 函数实例, 因为编译器自动为你实施了最好的行为。

比较难以回答的是, 如果你被问及是否预见 class 需要大量的 memberwise 初始化操作,例如以传值的方式传回 objects? 如果答案是 yes, 那么提供一个
copy constructor 的 explicit inline 函数实例就非常合理——在"你的编译器提供 NRV 优化"的前提下。


例如, Point3d 支持下面一组函数:

Point3d operator+(const Point3d&, const Point3d&);
Point3d operator-(const Point3d&, const Point3d&);
Point3d operator*(const Point3d&);

所有那些函数都能够良好地符合 NRV template:
{
  Point3d result;
  //...
  return result;
}


实现 copy constructor 的最简单方法像这样:

Point3d::Point3d(const Point3d& rhs){
  x_ = rhs.x_;
  y_ = rhs.y_;
  z_ = rhs.z_;
}

这没问题, 但使用 C++library 的 memcpy() 会更有效率:

Point3d::Point3d(const Point3d& rhs){
  memcpy(this, &rhs, sizeof(Point3d));
}


然而不管使用 memcpy() 还是 memset(), 都只有在 classes 不含任何由编译器产生的内部 members 时才能有效运行。

如果 Point3d class 声明一个或一个以上的 virtual functions 或内含一个 virtual base class, 那么使用上述函数将会导致那些被编译器产生的内部 members的初值
被改写。

例如, 已知下面的声明:

class Shape{
public:
  // 这会改变内部的 vptr
  Shape(){
    memset(this, 0, sizeof(Shape));
  }
  ~Shape();
  //...
};

编译器为此 constructor 扩张的内容看起来像这样:

// 扩张后的 constructor
// C++ 伪代码
Shape::Shape(){
  _vptr_Shape = _vbtl_Shape;

  // memset 会将 vptr 清 0
  memset(this, 0, sizeof(Shape));
}

如你所见, 若要正确使用 memset() 和 memcpy(), 则需要掌握某些 C++Object Model 的语意学知识！


// !! 摘要

copy constructor 的应用, 迫使编译器多多少少对你的程序代码做部分转化。尤其是当一个函数以传值的方式传回一个 class object, 而该 class 有一个
copy constructor 时。

这将导致深奥的程序转化——不论在函数的定义上还是在使用上。此外，编译器也将 copy constructor 的调用操作优化，以一个额外的第一参数(数值被直接存放于其中)取代
NRV。程序员如果了解那些转换, 以及 copy constructor 优化后的可能状态, 就比较能够控制其程序的执行效率。


// !! 成员们的初始化队伍 (Member Initialization List)

当你写下一个 constructor 时, 就有机会设定 class members 的初值。要不是经由 member initialization list, 就是在 constructor 函数本体之内。除了 4 
种情况, 你的任何选择其实都差不多。

本节之中, 我首先要澄清何时使用 initialization list 才有意义, 然后解释 list 内部的真正操作是什么, 然后我们再来看看一些微妙的陷阱。

在下列情况下, 为了让你的程序能够被顺利编译, 你必须使用 member initialization list:

1. 当初始化一个 reference member 时

2. 当初始化一个 const member 时

3. 当调用一个 base class 的 constructor, 而它拥有一组参数时

4. 当调用一个 member class 的 constructor, 而它拥有一组参数时


在这 4 种情况下, 程序可以被正确编译并执行, 但是效率不高。例如:

class Word{
private:
  string name_;
  int cnt_;
public:
  Word() {
    name_ = 0;
    cnt_ = 0;
  }
};

在这里, Word constructor 会先产生一个临时性的 String object, 然后将它初始化, 之后以一个 assignment 运算符将临时性 object 指定给 name_, 随后再摧毁
那个临时性 object。这是故意的吗? 不大可能。编译器会产生一个警告吗? 我不知道!

以下是 constructor 可能的内部扩张结果:
// C++ 伪代码
Word::Word() {
  // 调用 string 的 default constructor
  name_.string::string();

  // 产生临时性对象
  string temp = string(0);

  // memberwise copy
  name_.string::operator=(temp);

  // 摧毁临时性对象
  temp_.string::~string();

  cnt_ = 0;
}

对代码反复审查并修正, 得到一个明显更有效率的实现方法:

// 较佳的方式
Word::Word() : name_(0){
  cnt_ = 0;
}


它会被扩张成这个样子:

Word::Word(){
  name_.string::string(0);
  cnt_ = 0;
}

顺带一提, 陷阱最有可能发生在这种形式的 template code 中:

template<typename T>
foo<T>::foo(T t){
  t_ = t;
}

这会引导某些程序员十分积极进取地坚持所有的 member 初始化操作必须在 member initialization list 中完成, 甚至即使是一个行为良好的 member, 如 cnt_:

Word::Word() : name_(0), cnt_(0){

}

在这里我们不禁要提出一个合理的问题: member initialization list 中到底会发生什么事情? 许多 C++ 新手对于 list 的语法感到迷惑, 他们误以为它是一组函数调
用。当然它不是！

'编译器会一一操作 initialization list, 以适当顺序在 constructor 之内安插初始化操作, 并且在任何 explicit user code 之前'。


例如, 先前的 Word constructor 被扩充为:

Word::Word(){
  name_.string.string(0);
  cnt_ = 0;
}

嗯……嗯, 它看起来很像是在 constructor 中指定 cnt_ 的值。

事实上, 有一些微妙的地方要注意: 'list 中的项目顺序是由 class 中的 members 声明顺序决定的, 不是由 initialization list 中的排列顺序决定的'。

在本例的 Word class 中, name_ 被声明于 cnt_ 之前, 所以它的初始化也比较早。

"初始化顺序"和"initialization list"中的项目排列顺序之间的外观错乱, 会导致下面意想不到的危险:

class X{
private:
  int i;
  int j;
public:
  X(int val): j(val), i(j) {

  }
};

上述程序代码看起来像是要把 j 设初值为 val, 再把 i 设初值为 j。问题在于, 由于声明顺序的缘故, initialization list 中的 i(j) 其实比 j(val) 更早执行。

这里还有一个有趣的问题, initialization list 中的项目被安插到 constructor 中, 会继续保存声明顺序吗?

X::X(int val) : j(val){
  i = j;
}

j 的初始化操作会被安插在 explicit user assignment 操作 (i=j) 之前还是之后 ? 如果声明顺序继续被保存, 则这份代码大大不。然而这份代码其实是正确的, 因为 
initialization list 的项目被放在 explicit user code 之前。

另一个常见的问题是, 你是否能够像下面这样, 调用一个 member function 以设定一个 member 的初值:

X::X(int val) : i(foo(val)), j(val){

}

其中 foo() 是 X 的一个 member function。答案是 yes, 但是……唔……之所以加上但是, 是因为我要给你一个忠告: 请使用存在于 constructor 体内的一个 member, 
而不要使用存在于 member initialization list 中的 member, 来为另一个 member 设定初值。

你并不知道 foo() 对 X object 的依赖性有多高, 如果你把 foo() 放在 constructor 体内, 那么对于到底是哪一个 member 在 foo() 执行时被设立初值这件事,就可
以确保不会发生模棱两可的情况。


Member function 的使用是合法的(当然, 我们必须不考虑它所用到的 members 是否已初始化), 这是因为和此 object 相关的 this 指针已经被建构妥当, 而 
constructor 大约被扩充为:

X::X(){
  i = this->foo(val);
  j = val;
}


最后, 如果一个 derived class member function 被调用, 其返回值被当做 base class constructor 的一个参数, 将会如何:


class FooBar : public X{
private:
  int fval_;
public:
  int fval(){return fval_;}
  FooBar(int val) : fval_(val), X(fval_) {

  }
  //...
};


你认为如何? 这是一个好主意吗? 下面是它可能的扩张结果:

FooBar::FooBar(){
  X::X(this, this->fval());
  fval_ = val;
}

它的确不是一个好主意。


简略地说，编译器会对 initialization list 一一处理并可能重新排序, 以反映出 members 的声明顺序。它会安插一些代码到 constructor 体内, 并置于任何 
explicit user code 之前。









