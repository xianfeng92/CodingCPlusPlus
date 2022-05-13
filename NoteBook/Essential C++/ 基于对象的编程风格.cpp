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

What Is the this Pointer ?

我们得设计一个 copy() 成员函数, 才能够以 Triangular class object 作为另一个 Triangular class object 的初值。

假设有以下两个对象:

Triangular tri1(8);
Triangular tri2(8, 3);

调用:

tri1.copy(tri2);


会将 tri2 的长度及起始位置赋值给 tri1。copy() 必须返回被复制出来的对象。

本例中, tri1 不仅是复制的目标, 也用来接收复制的结果。这该如何完成呢 ? 以下是 copy() 的一份实现:

Triangular& Triangular::copy(const Triangular& rhs){
  length_ = rhs.length();
  beg_pos_ = rhs.beg_pos();
  next_ = rhs.next();
  return ???;// 应该返回什么呢？
}


其中 rhs (right hand side 的缩写)被绑定至 tri2, 而以下这个赋值操作:

length_ = rhs.length();

length_ 指向 tri1 内的相应成员。'我们还需要一种可以指向 tri1 整个对象的方法, 所谓 this 指针便扮演了这样的角色'。

this 指针系在 member function 内用来指向其调用者(一个对象)。本例中, this 指向 tri1。这是怎么办到的呢? 内部工作过程是, 编译器自动将 this 指针加到每一个
member function 的参数列表, 于是 copy() 被转换为以下形式:


Triangular& Triangular::copy(Triangular *this, const Triangular& rhs) {
  length_ = rhs.length();
  beg_pos_ = rhs.beg_pos();
  next_ = rhs.next();
  return *this;
}

整个转换过程还需要另一个配合:每次调用 copy() 都需要提供两个参数。为此, 原始调用方式:

tri1.copy(tri2);

会被转换为:

copy(&tri1, tri2);

'在 member function 内, this 指针可以让我们访问其调用者的一切'。

欲以一个对象复制出另一个对象, 先确定两个对象是否相同是个好习惯。这必须再次运用 this 指针:

Triangular& Triangular::copy(Triangular *this, const Triangular& rhs){
  if(this == &rhs){
    return *this;
  }
  length_ = rhs.length();
  beg_pos_ = rhs.beg_pos();
  next_ = rhs.next();
  return *this;
}



// !! 静态类成员

Static Class Members

static data member 用来表示唯一的、可共享的 member。

它可以在同一类的所有对象中被访问。例如以下这份定义, 我们声明  elems_ 是 Triangular class 的一个 static data member:


class Triangular{
public:
private:
  static vector<int> elems_;
};

对 class 而言, static data member 只有唯一的一份实体, 因此我们必须在程序代码文件中提供其清楚的定义。这种定义看起来很像全局对象 global object 的定义。
唯一的差别是, 其名称必须附上 class scope 运算符:

vector<int> Triangular::elem_;


如果要在 class member function 内访问 static data member, 其方式有如访问一般 non-static 数据成员


// !! Static Member Function (静态成员函数)

考虑以下的 is_elem(), 给定某值, 它会依据该值是否在 Triangular 数列内而返回 true 或 false:

bool Triangular::is_elem(int value){
  if(!elem_.size() || elem_.size() - 1 < value )
  gen_elems_to_value(value);
  vector<int>::iterator found_it;
  vector<int>::iterator end_it  = elem_.end();
  found_it = find(elem_begin(), end_it, value);
  return found_it != end_it;
}


一般情形下, member function 必须通过其类的某个对象来调用。这个对象会被绑定至该 member function 的 this 指针。

有了 this 指针, member function 才能够访问储存于每个对象中的 non-static data member。

然而, 上述的 is_elem() 并未访问任何 non-static data member。它的工作和任何对象都没有任何关联, 因而应该可以很方便地以一般 non-member function 的方式
来调用。


但是我们不能这样写:

if(is_elem(8))


因为这样一来就没有办法让编译器或程序阅读者知道我们想调用的究竟是哪一个 is_elem()。class scope 运算符可以解决这种令人混淆的问题:

if(Triangular::is_elem(8))

于是 static member function 便可以在这种与任何对象都无瓜葛的情形之下被调用。


注意, member function 只有在不访问任何 non-static member 的条件下才能够被声明为 static, 声明方式是在声明之前加上关键字 static:


class Triangular{
public:
  static bool is_elem(int value);
  static void get_elements(int value);
  static void gen_elems_to_value(int value);
private:
  static vector<int> elems_;
};


当我们在 class 主体外部进行 member function 的定义时, 无须重复加上关键字 static。




// !! 打造一个 Iterator Class

Building an Iterator Class

为了说明如何对 class 进行运算符重载操作, 让我们体验一下如何实现一个 iterator class。我们必须提供以下操作方式:


Triangular tri(8);
Triangular::iterator it = tri.begin();
Triangular::iterator end = tri.end();

while(it != end){
  cout << *it << " ";
  ++it;
}

为了让上述程序代码得以工作, 我们必须为此 iterator class 定义 !=、*、++ 等运算符。这应如何办到呢?

我们可以像定义 member function 那样来定义运算符。运算符函数看起来很像普通函数, 唯一差别是它不用指定名称, 只需在运算符前加上关键字 operator 即可。
例如:

class Triangular_iterator{
public:
  Triangular_iterator(int index) : index_(index) {}
  bool operator--(const Triangular_iterator&) const;
  bool operator!=(const Triangular_iterator&) const;
  int operator*() const;
  Triangular_iterator& operator++();
  Triangular_iterator operator++(int);
private:
  int index_;
  void check_integrity() const;
};

Triangular_iterator 维护一个索引值, 用以索引 Triangular 中用来储存数列元素的那个 static data member, 也就是_elems。为了达到这个目的, Triangular
必须赋予 Triangular_iterator 的 member function 特殊的访问权限。

如果两个 Triangular_iterator 对象的 index_ 相等, 我们便说这两个对象相等:

inline Triangular_iterator::operator==(const Triangular_iterator& rhs) const {
  return index_ == rhs.index_;
}


所谓运算符, 可以直接作用于其 class object:

if(tri1 == tri2){

}

如果我们希望将运算符作用于指针所指的对象, 就得先提领该指针, 取出其所指对象:

if(*ptri1 == *ptri2)

以下是运算符重载的规则:

● 不可以引入新的运算符。除了 .、.*、 ::、 ?: 四个运算符, 其他的运算符皆可被重载。

● 运算符的操作数个数不可改变。每个二元运算符都需要两个操作数, 每个一元运算符都需要恰好一个操作数。因此, 我们无法定义出一个 equality 运算符, 并令它接受两个以
  上或两个以下的操作数

● 运算符的优先级 (precedence) 不可改变

● 运算符函数的参数列表中，必须至少有一个参数为 class 类型


Non-member 运算符的参数列表中, 一定会比相应的 member 运算符多出一个参数, 也就是 this  指针。对 member 运算符而言, 这个 this 指针隐式代表左操作数。


// !! 嵌套类型 (Nested Type)

typedef 可以为某个类型设定另一个不同的名称。其通用形式为:

typedef exiting_type new_type;

其中的 existing_type 可以是任何一个内置类型、复合类型或 class 类型。在我们的例子中, 我令 iterator 等同于 Triangular_iterator, 以简化其使用形式。以下
是定义一个 iterator object 的语法:

Triangular::iterator it = tri.begin();

我们得使用 class scope 运算符来指引编译器, 让它在面对 iterator 这个字眼时, 查看 Triangular 内部提供的定义。


如果我们只是写:

iterator it = tri.begin();

编译器就不知道在面对 iterator 这个字时该查看 Triangular 的内容, 于是以上声明出现错误。

如果将 iterator 嵌套放在每个"提供 iterator 抽象概念"的 class 内, 我们就可以提供有着相同名称的多个定义。但是这样的声明语法有些复杂:

Triangular::iterator it = tri.begin();
vector<int>::iterator it = vec.begin();
string::iterator it = str.begin();



// !! 合作关系必须建立在友谊的基础上

Collaboration Sometimes Requires Friendship

以下的 non-member operator*()  会直接访问 Triangular 的 private elems_ 以及 Triangular_iterator 的 private check_integrity():

inline int operator*(const Triangular &rhs) {
  rhs.check_integrity();
  return Triangular::elems_(rhs.index());
}

为什么上述程序直接访问 private member 却可以通过编译呢? 因为任何 class 都可以将其他 function  或 class 指定为朋友(friend)。'而所谓 friend, 具备了与
class member function 相同的访问权限, 可以访问 class 的 private member'。


为了让 operator*() 通过编译, 不论 Triangular 或 Triangular_iterator 都必须将 operator*() 声明为"朋友":


class Triangular{
friend int  operator*(const Triangular& rhs);
//...
};


class Triangular_iterator{
friend int operator*(const Triangular & rhs);
};

'只要在某个函数的原型 prototype 前加上关键字 friend, 就可以将它声明为某个 class 的 friend'。

这份声明可以出现在 class 定义的任意位置上, 不受  private  或 public 的影响。如果你希望将数个重载函数都声明为某个 class 的 friend, 你必须明确地为每个函数
加上关键字 friend。


Triangular_iterator 内的 operator*()  和  check_integrity() 都需要直接访问 Triangular 的 private member, 因此我们将两者都声明为 Triangular 的
friend:


class Triangular{
  friend int Triangular_iterator::operator*();
  friend int Triangular_iterator::check_integrity();
};

为了让上述定义成功通过编译,我们必须在上述两行之前,先提供 Triangular_iterator 的定义让 Triangular 知道。否则编译器就没有足够的信息可以确定上述两个函数
原型是否正确,也无法确定它们是否的确是 Triangular_iterator 的 member function。


我们也可以令  class A 与 class B 建立 friend 关系, 借此让 class A 的所有 member function 都成为 class B 的 friend。


class Triangular{
public:
  friend class Triangular_iterator;
  //...
};


如果以这种形式来声明 class 间的友谊, 就不需要在友谊声明之前先显现 class 的定义。


不过, 我们也并非一定得以 friend 方式达到目的。如果 Triangular 提供一个 public member function 来访问 max_elems_, 以及另一个 public member functions
来返回 elems_ 的当前大小, 那么 check_integrity() 就不再需要主动建立友谊。

友谊的建立, 通常是为了效率考虑。



// !!  实现一个 copy assignment operator

Implementing a Copy Assignment Operator


默认情况下, 当我们将某个 class object 赋值给另一个, 像下面这样:

Triangular tri1(8), tri2(3,2);
tri1 = tri2;

class data member 会被依次复制过去。在我们的例子中, length_、beg_pos_、next_ 都会从 tri2 被复制到 tri1 去。这称为 default memberwise copy
(默认的成员逐一复制操作)

以 Triangular 为例, default memberwise copy 即已足够, 我们不需要另做其他事情。


只要 class 设计者明确提供了 copy assignment operator, 它就会被用来取代 default memberwise copy 行为。


// !! 实现一个 function object

Implementing a Function Object

所谓 function object 乃是一种提供有 function call 运算符的 class。


当编译器在编译过程中遇到函数调用, 例如:

It(ival);

lt 可能是函数名称, 可能是函数指针, 也可能是一个提供了 function call 运算符的 function object。

如果  lt 是个 class object, 编译器便会在内部将此语句转换为:

It.operator(ival) // 内部转换结果

function call 运算符可接受任意个数的参数: 零个、一个、两个或更多。

下面就来实现一个 function call 运算符, 测试传入值是否小于某指定值。将此 class 命名为 LessThan, 其每个对象都必须被初始化为某基值。此外，也提供该基值的读取
及写入操作。实现如下:

class LessThan{
public:
  LessThan(int val) : val_(val){}
  int comp_val() const { return val_; }
  void comp_val(int val) { val_ = val; }
  bool operator()(int val) const;
private:
  int val_;
};


其中的 function call 运算符实现如下:


inline bool LessThan::operator()(int val) const{
  return val < val_;
}


定义 LessThan object 的方式和定义一般对象并没有两样:

LessThan l10(10);

将 function call 运算符应用于对象身上, 便可以调用 function call 运算符:

int count_less_than(const std::vector<int> &vec, int comp){
  LessThan l(comp);
  int count = 0;
  for(int i=0; i<vec.size(); i++>){
    if(l(vec[i])){
      count++;
    }
  }
  return count;
}


通常我们会把 function object 当作参数传给泛型算法。




// !! 重载 iostream  运算符

Providing Class Instances of the iostream Operators

我们常常会希望对某个 class object 进行读取和写入操作。如果我们想要显示 tri 对象的内容,可能会希望这样写:

cout << tri << endl;

为了支持上述形式, 我们必须另外提供一份重载的 output 运算符:


ostream& operator<<(ostream & os, const Triangular& rhs){
  os << ": " << rhs.begin_pos() << ", " << rhs.length() << endl;
  rhs.display(rhs.length(), rhs.begin_pos(), os);
  return os;
}


传入函数的 ostream 对象又被原封不动地返回, 如此一来我们便得以串接多个 output 运算符。

参数列表中的两个对象皆以传址 (by reference)方式传入。其中的 ostream 对象并未声明为 const, 因为每个 output 操作都会更改 ostream 对象的内部状态。


至于 rhs 这种将被输出的对象, 就会被声明为 const——因为这里之所以使用传址方式, 是基于效率考虑而非为了修改其对象内容。

为什么不把 output 运算符设计为一个 member function 呢 ? 

因为作为一个 member function, 其左操作数必须是隶属于同一个 class 的对象。

如果 output 运算符被设计为 tri class member function, 那么 tri object 就必须被放在 output 运算符的左侧:

tri << cout << " ";

这种奇怪的形式必定对 class 用户造成困惑!


// !! 指针,指向 Class Member Function

Pointers to Class Member Functions













































