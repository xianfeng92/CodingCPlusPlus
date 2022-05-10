// !! 基于对象的编程风格

根据过去的种种使用经验, 我们明白了 class 的哪些相关事务呢?

首先, 在使用 class 之前, 由于它并非程序语言本身内置, 所以我们必须先让程序知道它。通常我们会包含某个头文件来完成这件事:

#include <string>

std::string words[4] = {"hello", "world", "happy", "today"};

class 名称被视为一个类型 (type)名称, 就像内置类型 int、double 一样。

Class object的初始化做法有很多种:

std::string dummy("dummy");
std::vector<std::string> svec1;
std::vector<std::string> svec2(5);
std::vector<std::string> svec3(5, "hello");
std::vector<std::string> svec4(words, words + 4);


每个 class 都会提供一组操作函数, 让我们作用于其 object 上。这些操作函数包括具名函数: 如 size() 和 empty() 以及重载运算符, 如 equality 和 assignment 
运算符。


if(svec4 != svec3 || !svec2.empty()) {

}

if(svec4.size() == 4){

}


'通常我们并不知道 class 的实现内容'。例如, string 是在每次我们要求计算其大小时才去计算呢? 还是它将自己的大小储存在每个  object 之中呢? vector 的元素究竟
是储存在 vector 对象内呢? 还是存在其他地方, 再通过 vector 对象中的指针加以定位呢? 这些我们都不知道。

一般而言, class 由两部分组成: 一组公开的 public 操作函数和运算符, 以及一组私有的 private 实现细节。

这些操作函数和运算符称为 class 的 member function, 并代表这个 class 的公开接口。身为 class 的用户, 只能访问其公开接口。这也就是我们使用 string、vector
的方式。

例如, 针对 string 的 member function size(), 我们只知其原型声明 (prototype), 亦即: 参数列表为 void, 返回整数值。

'class 的 private 实现细节可由 member function 的定义以及与此 class 相关的任何数据组成'。例如,假设 string class object 的 size() 每次被调用, 都会
重新计算其字符串长度, 那么就不需要任何相关数据来储存这份信息--size() 定义中可能利用 for 循环之类的遍历方式, 取得字符串长度。但如果  string class object 
欲储存其字符串长度,就必须在每个 class object 中定义 private data member, 并在 size() 定义中将该值返回。每当字符串长度有所变动, 这份 data member 都必
须同步更新。


'class 用户通常不会关心此等实现细节。身为一个用户, 我们只利用其公开接口来进行编程'。这种情形下, 只要接口没有更改, 即使实现细节重新打造, 所有的应用程序代码也不
需要变动。

这一章, 我们的境界'将从 class 的使用提升至 class 的设计与实现'。这正是 C++ 程序员的主要工作。



// !! 如何实现一个 Class

How to Implement a Class

好的, 该从哪里着手呢? 

一般来说, 我们会从所谓的抽象 (abstraction) 开始。

想想 stack 这个例子, 'stack 是计算机科学中十分基础的一个抽象概念, 它允许我们叠放许多数值, 并以后进先出(last-in, first-out, LIFO) 的顺序取出'。
我们以 pushing 方式将新数值叠放到堆栈内, 并以 popping 方式取出 stack 内最后一个被 pushed 的数值。用户通常还会要求其他操作行为, 像是询问 stack 的空间
是否已满 (full) 或是否为空 (empty) 或询问 stack 的元素个数 (size)。stack 也可能提供查看 (peeking) 能力, 观察 stack 内最后一个被 pushed 的数值。


我们应该让 stack 存放哪一类型的元素呢? 

通用型  stack  应该可以存放各种类型元素, 如果把  stack 定义为 class template 便可以达到这个目的。


class 的声明以关键字 class 开始, 其后接一个  class 名称(可任意命名):

class Stack;

此句只是作为 'Stack class 的前置声明 (forward declaration), 将 class 名称告诉编译器, 并未提供此 class 的任何其他信息'(像是 class 支持的操作行为及所
包含的 data member 等)。

前置声明使我们得以进行类指针 (class pointer) 定义, 或以此 class 作为数据类型:

Stack *pt = 0;// 定义一个类指针
void process(Stack& stack);// 以 Stack 作为数据类型


接下来, 在定义实际的 Stack class object 或访问 Stack 的任何一个 member 之前, 必须先定义 class 本身。


class Stack {
public:
...
private:
...
};

Class 定义由两部分组成: class 的声明, 以及紧接在声明之后的主体。主体部分由一对大括号括住, 并以分号结尾。


主体内的两个关键字 public 和 private 用来标示每个块的"member 访问权限"。Public member 可以在程序的任何地方被访问, private member 只能在
member function 或 class friend 内被访问。


以下是 Stack class 的起始定义:

class Stack {
public:
  bool push(const std::string&);
  bool pop(std::string& elem);
  bool peek(std::string& elem);
  bool empty();
  bool size(){return _stack.size();}
private:
  vector<std::string> _stack;
};

这一份 Stack 提供了本节一开始找出的六个操作行为。其元素被储存于名为 _stack 的 string vector 内。以下说明如何定义并使用 Stack class object:


void fill_stack(Stack& stack, istream &is = cin){
    string str;
    while(is >> str && !stack.full()) {
        stack.push(str);
    }
    std::cout << stack.size() << std::endl;
}


'所有 member function 都必须在 class 主体内进行声明。至于是否要同时进行定义, 可自由决定'。如果要在 class 主体内定义，这个 member function 会自动地被
视为 inline 函数。

例如, size() 即是 Stack 的一个 inline member。要在 class 主体之外定义 member function, 必须使用特殊的语法, 目的在于分辨该函数究竟属于哪一个class。

如果希望该函数为 inline, 应该在最前面指定关键字 inline:


inline bool Stack::empty() {
    return stack.empty();
}

bool Stack::pop(string& elem) {
    if(empty()) return false;
    elem = _stack.back();
    _stack.pop_back();
    return true;
}


上述的:

Stack::empty()

告诉编译器 (或程序读者)说, empty() 是 Stack class (而非 vector 或 string)的一个 member。

class 名称之后的两个冒号 (Stack::) 即所谓的 class scope resolution (类作用域解析) 运算符。

class 定义及其 inline member function 通常都会被放在与 class 同名的头文件中。例如 Stack class 的定义和其 empty() 函数定义都应该放在 Stack.h 头文件
中。此即用户想要使用 Stack 时应该包含的文件。

non-inline member function 应该在程序代码文件中定义, 该文件通常和 class 同名, 其后接着扩展.cpp 或.cc


以下便是 Stack member function 的定义。full() 会将目前的元素个数拿来和底层 vector 的 max_size() 数值做比较。push() 则是在 _stack 未满的前提下将元
素插入。


inline bool Stack::full(){
    return _stack.max_size() == _stack.size();
}


bool Stack::peek(string& elem){
    if(empty()) return false;
    elem = _stack.back();
    _stack.pop_back();
    return true;
}


bool Stack::push(string& elem) {
    if(full()) return false;
    _stack.push_back(elem);
    return true;
}


虽然我们已经提供给用户一整组操作行为, 但还未能完成 Stack 的完整定义。


// !! 什么是构造函数和析构函数

What Are Class Constructors and the Class Destructor ?

每个数列都很适合设计为 class, 一个数列的 class object 可以表现出该数列在某范围内的元素。默认情形下, 起始位置为 1。例如:

Fibonacci fib1(7, 3);

便定义了拥有 7 个元素的 Fibonacci object, 起始位置为 3。

Pell pel(10);

则定义了具有 10 个元素的 Pell object, 起始位置为默认值 1。

Fibonacci fib2(fib1);

定义了一个 Fibonacci object fib2, 并以 fib1 作为 fib2 的初值。换句话说, fib2 是 fib1 的副本。

每个 class 都必须记住它自己的长度——数列的元素个数——和起始位置。但起始位置不得为零值或负值。

所以,我以整数储存长度及起始位置。此刻我再定义第三个 member_next, 用来记录迭代 (iterate) 操作的下一个元素。


class Triangulator {
public:
...
private:
  int length_;
  int beg_pos_;
  int next_;
};


Trangulator tri(8, 3);

tri 内含一份 length_ (初值8), 一份 beg_pos_ (初值3), 一份 next_ (初值2), 因为 vector 的第三个元素的索引值为 2。注意, 它没有包含实际上用来储存
triangular 数列元素的 vector。为什么? 因为我们不希望在每个 class object 中都复制一份这个 vector;  所有 class object 共享一份 vector 便已足够。

这些 data member 如何被初始化呢?  

噢, 魔法不会自动产生; 编译器不会自动为我们处理。'如果我们提供一个或多个特别的初始化函数,编译器就会在每次 class object 被定义出来时,调用适当的函数加以处理'。
这些特别的初始化函数称为 constructor。

constructor 的函数名称必须与 class 名称相同。语法规定, constructor 不应指定返回类型, 亦不用返回任何值。它可以被重载 overloaded。

例如, Triangular class 可能有三个 constructor:

class Triangular{
public:
  Triangular();
  Triangular(int len);
  Triangular(int len, int beg_pos);
private:
  ...
};

class object 定义出来后, 编译器便自动根据获得的参数, 挑选出应被调用的 constructor。

例如:

Triangular t;

会对 t 应用 default constructor。


Triangular t(10, 3);

会调用带有两个参数的 constructor。括号内的值会被视为传给 constructor 的参数。同样,


Triangular t3 = 8;

会调用带有单一参数的 constructor。

出人意料的是, 以下程序代码无法成功定义一个 Triangular object。

Triangular t5();

此行将 t5 定义为一个函数, 其参数列表是空的，返回 Triangular object。

很显然这是个奇怪的解释。为什么它会被这样解释呢?  因为 C++ 必须兼容于C。对 C 而言, t5 之后带有小括号, 会使 t5 被视为函数。正确的 t5 声明方式, 应该和先前的
t 一样:

Triangular t5;

最简单的 constructor 是所谓的 default constructor。它不需要任何参数 (argument)。

这意味着两种情况。第一, 它不接受任何参数:

Triangular::Triangulator(){
    length_= 1;
    beg_pos_= 1;
    next_ = 0;
}


由于我们为两个整数提供了默认值,所以这个 default constructor 同时支持原本的三个 constructor。

// !! Member Initialization List

constructor 定义的第二种初始化语法, 是所谓的 member initialization list (成员初始化列表):

Triangular::Triangular(const Triangular& ls) : length_(ls.length_), beg_pos_(ls.beg_pos_), next_(ls.next_){

}

member initialization list 紧接在参数列表最后的冒号后面, 是个以逗号分隔的列表。其中, 欲赋值给  member 的数值被放在 member 名称后面的小括号中; 这使它们
看起来像是在调用 constructor。

就本例而言 (本例没有 member object), 第一种和第二种 constructor 定义方式是等价的, 并没有谁优于谁的问题。

Member initialization list 主要用于将参数传给 member class object 的 constructor。假设我们重新定义:

class Triangular{
public:
...
private:
  string name_;
  int length_;
  int beg_pos_;
  int next_;
};


为了将 name_ 的初值传给 string constructor, 我们必须以 member initialization list 完成。


和 constructor 对立的是 destructor。所谓 destructor 乃是用户自定义的一个 class member。一旦某个 class 提供有 destructor, 当其 object 结束生命时,
便会自动调用 destructor 处理善后。Destructor 主要用来释放在 constructor 中或对象生命周期中分配的资源。


// !! Memberwise Initialization (成员逐一初始化)

默认情形下, 当我们以某个 class object 作为另一个 object 的初值, 例如:

Triangular t1(8);
Triangular t2(t1);

class data member 会被依次复制。此即所谓的 default memberwise initialization (默认的成员逐一初始化操作)。

当我们设计 class 时, 必须问问自己, 在此 class 之上进行"成员逐一初始化"的行为模式是否适当 ? 如果答案肯定, 我们就不需要另外提供 copy constructor。但如果答
案是否定的, 我们就必须另行定义 copy constructor 并在其中编写正确的初始化操作。

如果有必要为某个 class 编写 copy constructor, 那么同样有必要为它编写 copy assignment operator


// !!  何谓 mutable (可变)和 const (不变)

What Are mutable and const ?

看看下面这个小函数:

int sum(const Triangulator& tri){
    int beg_pos = tri.beg_pos();
    int len = tri.length();
    int sum = 0;
    for(int i = 0; i < len; i++){
        sum += tri.elem[i];
    }
    return sum;
}

tri 是个 const reference 参数, 因此编译器必须保证 tri 在 sum() 之中不会被修改。

但是, sum() 所调用的任何一个 member function 都有可能更改 tri 的值。为了确保 tri 的值不被更改, 编译器必须确保 c()、length()、elem() 都不会更改
其调用者。编译器如何得知这项信息呢? 是的, class 设计者必须在 member function 身上标注 const, 以此告诉编译器: 这个 member function 不会更改
class object 的内容:

class Triangular{
public:
  int length() const { return length_; }
  int beg_pos() const { return beg_pos_; }
  int elem(int pos) const;

  bool next();
private:
  int  length_;
  int beg_pos_;
  int next_;
  static vector<int> elem;
};

const 修饰符紧接于函数参数列表之后。凡是在 class 主体以外定义者, 如果它是一个 const member function, 那就必须同时在声明与定义中指定 const。


int  Triangular::elem(int pos) const{
    ...
}

虽然编译器不会为每个函数进行分析, 决定它究竟是 const 还是 non-const, 但它会检查每个声明为 const 的 member function, 看看它们是否真的没有更改
class object 内容。

例如, 假设我们将以下的 next() 声明为 const member function, 就会产生编译错误, 因为很显然它会更改其调用者的值。


设计 class 时, 鉴定其 const member function 是一件很重要的事。如果你忘了这么做, 要知道, 没有一个 const reference class 参数可以调用公开接口中的
non-const 成分(但目前许多编译器对此情况都只给警告)。用户也许会因此大声咒骂, 将 const 加到 class 内并非易事, 特别是如果某个 member function 被广泛使用
之后。


// !! Mutable Data Member (可变的数据成员)

以下是 sum() 的另一种做法, 借由 next() 和 next_reset() 两个 member function 对 tri 元素进行迭代:

int sum(const Triangular& tri){
  if(!tri.length()) return 0;
  int val, sum = 0;
  tri.next_reset();
  while(tri.next() < val){
    sum += val;
  }
  return sum;
}

这段程序会通过编译吗? 不, 至少现在不行。tri 是个 const object,  而 next_reset() 和 next() 都会更改 next_ 值, 它们都不是 const member function。
但它们却被 tri 调用, 于是造成错误。

如果我们很希望采用 sum() 的这份实现, 则 next() 和 next_reset() 势必得改为 const。但它们真的改变了 next_ 的值呀! 唔, 我们可以做一个很好的区别。

检讨一下, length_ 和 beg_pos_ 提供了数列的抽象属性。如果我们改变 tri 的长度或起始位置, 形同改变其性质, 将和未改变前的状态不再相同。

然而 next_ 只是用来让我们得以实现出 iterator 机制, 它本身不属于数列抽象概念的一环。'改变 next_ 的值, 从意义上来说, 不能视为改变 class object 的状态',
或者说不算是破坏了对象的常量性(constness)。


关键字  mutable 可以让我们做出这样的声明。只要将 next_ 标示为 mutable, 我们就可以宣称:'对 next_ 所做的改变并不会破坏 class object 的常量性'。


class Triangular{
public:
  bool next(int& val) const;
  void next_reset() const { next_ = beg_pos_;}
private:
  mutable int next_;
  int beg_pos_;
  int length_;
};


现在, next() 和 next_reset() 既可以修改 next_ 的值, 又可以被声明为 const member function。


// !! 什么是 this 指针














