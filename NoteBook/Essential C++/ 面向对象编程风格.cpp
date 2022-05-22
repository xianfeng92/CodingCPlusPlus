// !! 面向对象编程风格

class 的主要用途在于引入一个崭新的数据类型, 能够更直接地在我们所设计的程序系统中, 表现我们想表现的实体。好比图书馆的借阅系统, 如果我们利用 Book、Borrower 、
DueDate 这些类来进行程序设计,往往会比使用基本的字符类型、算术类型、布尔类型轻松多了。

当我们的应用系统布满许多类, 其间有着是一种(is-a-kind-of)的关系时,以对象为基础 object-based 的编程模型反而会拖累我们的程序设计工作。

以对象为基础 (object-based) 的类机制无法轻松针对这四个 are-a-kind-of 的 Book 类的共通性质进行系统化的划分。

为什么? 

因为这种模型无法让我们更进一步地指出类间的关系。类间的关系依赖面向对象编程模型 (object-oriented programming model) 加以设定。



// !! 面向对象编程概念

Object-Oriented Programming Concepts

面向对象编程概念的两项最主要特质是:继承 (inheritance) 和多态 (polymorphism)。

前者使我们得以将一群相关的类组织起来,并让我们得以分享其间的共通数据和操作行为; 后者让我们在这些类之上进行编程时, 可以如同操控单一个体, 而非相互独立的类, 并赋
予我们更多弹性来加入或移除任何特定类。

继承机制定义了父子 parent/child 关系。父类 parent 定义了所有子类 children 共通的公有接口 public interface 和私有实现 private implementation。每个
子类都可以增加或覆盖 override 继承而来的东西, 以实现其自身独特的行为。

在 C++ 中, 父类被称为基类 base class,子类被称为派生类 derived class。父类和子类之间的关系则称为继承体系 (inheritance hierarchy)。

在面向对象应用程序中, 我们会间接利用指向抽象基类的 pointer 或 reference 来操作系统中的各对象,而不直接操作各个实际对象。这让我们得以在不更动旧有程序的前提下,
加入或移除任何一个派生类。


下面是个小例子:


void loan_check_in(LibMat &mat){
    mat.check_in();
}

此函数若要具有实质意义, 那么每当 loan_check_in() 被调用, mat 必定得指向我们程序中的某个实际对象。此外, 被调用的 check_in() 函数也势必得被解析 resolved 
为 mat 所代表的实际对象所拥有的那个check_in() 函数。这便是整个进行过程。

问题是,它到底是如何工作的?

面向对象编程风格的第二个独特概念是多态 polymorphism: 让基类的 pointer 或  reference 得以十分透明地指向其任何一个派生类的对象。以上述的 loan_check_in()
为例, mat 总是指向  LibMat 的某个派生对象。但究竟是哪一个? 答案是除非程序实际执行的当下, 否则无法确定。而且, loan_check_in() 的每次执行情况都可能不同。

动态绑定 (dynamic binding) 是面向对象编程风格的第三个独特概念。


在非面向对象的编程风格中,当我们写下这样一行:

mat.check_in();

'编译器在编译时就依据 mat 所属的类决定究竟执行哪一个 check_in() 函数'。'由于程序执行之前就已解析出应该调用哪一个函数, 所以这种方式被称为静态绑定'
(static binding)。

但在面向对象编程方法中, 编译器无法得知究竟哪一份 check_in() 函数会被调用。每次 loan_check_in() 执行时, 仅能在执行过程中依据 mat 所指的实际对象来决定调
用哪一个 check_in()。

"找出实际被调用的究竟是哪一个派生类的 check_in() 函数"这一解析操作会延迟至运行时(run-time)才进行, 此即我们所谓的动态绑定 (dynamic binding)。

继承特性让我们得以定义一整群互有关联的类, 并共享共通的接口, 就像前述的各种图书馆藏。

多态则让我们得以用一种与类型无关 (type-independent) 的方式来操作这些类对象。'我们通过抽象基类的  pointer 或 reference 来操控其共通接口', 而实际执行起来
的操作则需要等到运行时, 依据 pointer 或 reference 所指的实际对象的类型才能决定。 是的! '多态和动态绑定的特性, 只有在使用 pointer 或 reference 时才能发挥'。


// !! 漫游：面向对象编程思维

A Tour of Object-Oriented Programming


接下来, 让我实现一个三层的类体系, 并借此引入 C++ 语言中的基本组成和支持面向对象编程方法的语法元素。

我以 LibMat 这个抽象基类作为类体系中的最根本的类。我从 LibMat 派生出 Book, 并从 Book 派生出 AudioBook。我们先限定接口只有一个 constructor、一个
destructor 和一个 print() 函数。我为每个 member function 加上一些程序代码, 输出信息表示它们的存在, 让我们得以跟踪程序的行为。

'默认情形下, member function 的解析 (resolution) 皆在编译时静态地进行。 若要令其在运行时动态进行, 我们就得在它的声明前加上关键字 virtual'。

LibMat 的声明表示, 其 destructor 和 print() 皆为 virtual。

#ifndef NOTEBOOK_ESSENTIAL_20C_2B_2B_LIBMAT_H_
#define NOTEBOOK_ESSENTIAL_20C_2B_2B_LIBMAT_H_

#include <iostream>

class LibMat{
public:
  LibMat(){cout << "LibMat::LibMat() default constructor" << endl;}

  ~LibMat(){cout << "LibMat::~LibMat() default destruct" << endl;}

  virtual bool print() const{
      cout << "LibMat::print() default print" << endl;
  }

  
};
#endif // NOTEBOOK_ESSENTIAL_20C_2B_2B_LIBMAT_H_


现在, 我定义一个 non-member function print(), 它接受一个参数, 其形式为 const LibMat reference:

void print(const LibMat& mat){
    cout << "In global print function" << endl;
    // 根据 mat 实际所指向的对象,解析该指向哪一个 print member function
    mat.print();
}

在 main() 程序中重复调用 print(), 并依次将 LibMat 对象、Book 对象、AudioBook 对象当作参数传递给它。每次 print() 被执行, 都会依据 mat  实际所指的
对象, 在  LibMat、Book、AudioBook 三者之间挑选正确的  print() member function 加以调用。


我们该如何实现派生类 Book 呢 ? 为了清楚标示这个新类乃是继承自一个已存在的类, 其名称之后必须接一个冒号(:), 然后紧跟着关键字 public 和基类的名称:


#ifndef NOTEBOOK_ESSENTIAL_20C_2B_2B_BOOK_H_
#define NOTEBOOK_ESSENTIAL_20C_2B_2B_BOOK_H_

class Book : public LibMat{
public:
  Book(const std::string &title, const std::string &author) : title_(title), author_(author) {
      cout << "Book::book" <<"title: "<< title << "author: " << author << endl;
  }

  virtual ~Book(){
      cout << "Book::~book() destructor" << endl;
  }

  virtual void print() const {
      cout << "Book::print()--I am book object " << "my title: " << title << endl;
      cout << "my author: " << author << endl;
  }

  const string &title() const { return title_; }
  const string &author() const { return author_; }

protected:
  string title_;
  string author_;
};

#endif // NOTEBOOK_ESSENTIAL_20C_2B_2B_BOOK_H_

Book 中的 print() 覆盖 (override) 了 LibMat 的 print()。这也正是 mat.print() 所调用的函数。title() 和 author() 是两个所谓的访问函数
(access function), 都是 non-virtual inline 函数。过去我们不曾介绍关键字 protected, 被声明为 protected 的所有成员都可以被派生类直接访问,除此之外, 
都不得直接访问 protected 成员。


#ifndef NOTEBOOK_ESSENTIAL_20C_2B_2B_AUDIOBOOK_H_
#define NOTEBOOK_ESSENTIAL_20C_2B_2B_AUDIOBOOK_H_

class AudioBook : public Book{
public:
  AudioBook(const string &name, const string &title, const string &narrator) : Book(name, title), narrator_(narrator){
      cout << "AudioBook::AudioBook()" << endl;
  }

  ~AudioBook(){
      cout << "AudioBook::~AudioBook()" << endl;
  }

  virtual void print() const {
      cout << "AudioBook::print()" << endl;
      cout << "my title = " << title << endl;
      cout << "my author = " << author << endl;
      cout << "my narrator = " << narrator << end;
  }

  const string &narrator() const { return narrator_; }
protected:
  string narrator_;
};

#endif // NOTEBOOK_ESSENTIAL_20C_2B_2B_AUDIOBOOK_H_

使用派生类时不必刻意区分继承而来的成员和自身定义的成员。



// !! 不带继承的多态

Polymorphism without Inheritance



// !! 定义一个抽象基类

Defining an Abstract Base Class

'定义抽象类的第一个步骤就是找出所有子类共通的操作行为'。

举个例子, 所有数列类的共通操作行为是什么呢 ? 这些操作行为所代表的便是 num_sequence 这个基类的公有接口 public interface。

class num_sequence{
public:
  elem(int pos);
  void get_elem(int pos);
  const char* who_i_am() const;
  ostream& print(ostream& os = cout) const;
  bool check_integrity(int pos);
  static int max_elems();
};

elem() 会返回用户所指定的位置上的元素值。max_elems() 会返回最大的元素个数。check_integrity() 会判断传入的 pos 是否为有效位置。print() 会输出元素值。
gen_elems() 会产生数列元素。what_am_i() 会返回一个字符串, 代表数列的名称。

'设计抽象基类的下一步, 便是设法找出哪些操作行为与类型相关 (type-dependent)' -- 也就是说,有哪些操作行为必须根据不同的派生类而有不同的实现方式。

这些操作行为应该成为整个类继承体系中的虚函数 (virtual function)。

以本例而言, 每个数列类都必须提供它们自己的  gen_elems() 实现,  但 check_integrity() 就不会因为类型的不同而有任何差异--它必须能够判断 pos  位置是否有效, 
而其判断方式并不因数列类型而有所不同。同样地, max_elems() 也不会因类型不同而有任何差异--所有数列类型都储存着同样个数的元素。


并非每一个函数都能如此轻易地做出区分。what_am_i() 也许会(也许不会)和类型相关--这和我们的继承体系的实现有关。


注意, static member function 无法被声明为虚拟函数。


'设计抽象基类的第三步, 便是试着找出每个操作行为的访问层级'(access level)。


'如果某个操作行为应该让一般程序皆能访问, 我们应该将它声明为 public', 例如 elem()、max_elems()、what_am_i()。


但如果某个操作行为在基类之外不需要被用到, 我们就将它声明为 private。即使是该基类的派生类, 亦无法访问基类中的 private member。

第三种访问层级, 是所谓的 protected。这种层级的操作行为可让派生类访问, 却不允许一般程序使用。


每个虚函数, 要么得有其定义, 要么可设为纯虚函数 pure virtual function--如果对于该类而言, 这个虚函数并无实质意义的话。将虚函数赋值为 0, 意思便是令它为一
个纯虚函数。

void gen_elems(int pos) = 0;

任何类如果声明有一个(或多个)纯虚函数, 那么, 由于其接口的不完整性(纯虚函数没有函数定义,  是谓不完整), 程序无法为它产生任何对象。这种类只能作为派生类的子对象
(subobject)使用, 而且前提是这些派生类必须为所有虚函数提供确切的定义。

根据一般规则, 凡基类定义有一个(或多个)虚函数, 应该要将其 destructor 声明为 virtual, 像这样:

class num_sequence{
public:
  ~num_sequence();
  //...
};

但是我并不建议在我们的这个基类中将其 destructor 声明为 pure virtual -- 虽然它其实不具有任何实质意义的实现内容。对这类 destructor 而言, 最好是提供空白定
义, 像下面这样:

inline num_sequence::~num_sequence(){

}


// !! 定义一个派生类

Defining a Derived Class

派生类由两部分组成: 一是基类构成的子对象(subobject), 由基类的 non-static data member -- 如果有的话——组成, 二是派生类的部分(由派生类的 non-static 
data member 组成)。

派生类的这种合成本质忠实地反映在了其声明语法上:

class Fibonacci : public num_sequence {
public:
  //...
};

派生类的名称之后紧跟着冒号、关键字 public、以及基类的名称。唯一的规则是, 类进行继承声明之前, 其基类的定义必须已经存在(这也就是必须先行包含含有 num_sequence
类定义头文件的原因)。

Fibonacci class 必须为从基类继承而来的每个纯虚函数提供对应的实现。除此之外, 它还必须声明 Fibonacci class 专属的 member。

以下便是 Fibonacci class 的定义:

class Fibonacci : public num_sequence{
public:
  Fibonacci(int len = 1, int beg_pos = 1) : len_(len),beg_pos_(beg_pos) {}
  virtual int elem(int pos) const;
  virtual const char* who_i_am() const { return "Fibonacci"; }
  virtual ostream& print(ostream& os = cout);
  int length() const { return len_; }
  int beg_pos() const { return beg_pos_;}

protected:
  virtual void gen_elems(int pos) const;
  int len_;
  int beg_pos_;
  static  vector<int>  elems_;
};


在我的设计中, 每个派生类都有长度和起始位置这两项 data member。len() 和 beg_pos() 这两个函数被声明为 non-virtual, 因为它们并无基类所提供的实体可供覆盖。
但也因为它们并非基类提供的接口的一员, 所以当我们通过基类的 pointer 或 reference 进行操作时, 无法访问它们。

谈到这里,我的看法是,当我们面临萃取基类和派生类之间的性质,以决定哪些东西(包括接口和实际成员)属于谁时, 面向对象设计所面对的挑战，将不只是编程层面而已。一般而言,
这是一个不断迭代的过程,过程之中借着程序员的经验和用户的反馈, 不断演进。

以下便是 elem() 的实现。派生类的虚函数必须精确吻合基类中的函数原型。在类之外对虚函数进行定义时, 不必指明关键字 virtual:


int Fibonacci::elem(int pos) const {
  if(!check_integrity(pos)) return -1;
  if(pos > elems_.size()) Fibonacci::gen_elems(pos);
  return elems_[pos];
}

请注意, elem() 调用继承来的 check_integrity(), 其形式仿佛后者为其自身成员一般。

'一般来说, 继承而来的 public 成员和 protected 成员, 不论在继承体系中的深度如何, 都可被视为派生类自身拥有的成员'。基类的 public member 在派生类中同样也
是 public, 同样开放给派生类的用户使用。


基类的 protected member 在派生类中同样也是 protected, 同样只能给后续的派生类使用, 无法给目前这个派生类的用户使用。至于基类的 private member, 则完全无
法让派生类使用。

在 elem() 内, 我们清楚地知道我们想调用的究竟是哪一个 gen_elems()。在 Fibonacci::elem() 中我们想调用的是 Fibonacci::gen_elems(), 明确得很, 不必等到
运行时才进行 gen_elems() 的解析操作。

事实上, 我们希望跳过虚函数机制, 使该函数在编译时就完成解析, 不必等到运行时才解析。这就是我们指明调用对象的原因。'通过 class scope 运算符, 我们可以明确告诉
编译器, 我们想调用哪一份函数实例'。于是, 运行时发生的虚拟机制便被遮掩了。


void Fibonacci::gen_elems(int pos){
  if(elems_.empty()){
    elems_.push_back(1);
    elems_.push_back(1);
  }
  if(elems_.size() < pos){
    int ix = elems_.size();
    int n_2 = elems_[ix -2];
    int n_1 = elems_[ix -1];
    for(; ix <= pos; ++ix){
      int elem = n_2 + n_1;
      elems_.push_back(elem);
      n_2 = n_1;
      n_1 = elem;
    }
  }
}


ostream& Fibonacci::print(ostream& os ) const{
  //...
  return os;
}

'每当派生类有某个 member 与其基类的 member 同名, 便会遮掩住基类的那份 member'。也就是说, 派生类内对该名称的任何使用, 都会被解析为该派生类自身的那份 
member, 而非继承来的那份 member。

这种情况下, 如果要在派生类内使用继承来的那份 member, 必须利用  class scope 运算符加以限定。例如:


inline bool Fibonacci::check_integrity(int pos) const {
  if(!num_sequence.check_integrity(pos)) return false;
  if(pos > elems_.size()){
    Fibonacci::gen_elems(pos);
  }
  return true;
}

这种解决方法带来的问题是, 在基类中 check_integrity() 并未被视为虚函数。于是, 每次通过基类的 pointer 或  reference 来调用 check_integrity(), 解析出来
的都是  num_sequence 的那一份, 未考虑到 pointer 或 reference 实际指向的究竟是什么对象。


void Fibonacci::example(){
  num_sequence *ps = new Fibonacci(2,8);
  ps->elem(1024);
  ps->check_integrity(1024);
}


基于这个原因, 一般而言, 在基类和派生类中提供同名的 non-virtual 函数, 并不是好的解决办法。基于此点而归纳出来的结论或许是: 基类中的所有函数都应该被声明为 
virtual。我不认为这是个正确的结论, 但它的确可以马上解决我们所面临的两难困境。

造成这种两难困境的深层原因是, 当派生类欲检查其自身状态的完整性时, 已实现完成的基类缺乏足够的知识。


我再重复一次, 我认为, '所谓设计,必须来来回回地借着程序员的经验和用户的反馈演进'。


本例中, 较好的解决方案是重新定义 check_integrity(), 令它拥有两个参数:


bool num_sequence::check_integrity(int pos, int size) {
  if(pos <= 0 || pos >= max_elems){
    return false;
  }

  if(pos > size){
    gen_elems(pos);
  }
  return true;
}

在这个 check_integrity() 版本中, gen_elems() 通过虚拟机制被调用。如果 check_integrity() 是由 Fibonacci 对象调用, 那么后续就会调用 Fibonacci 的
gen_elems()。如果 check_integrity() 是由 Triangular 对象调用, 那么后续就会调用 Triangular 的 gen_elems(), 以此类推。



// !!  运用继承体系

Using an Inheritance Hierarchy





// !! 基类应该多么抽象

How Abstract Should a Base Class Be ?

在目前的设计之下, 抽象基类提供的是接口, 并未提供任何实现。每个派生类不仅必须提供本身专属的元素产生算法, 还必须支持特定元素的搜索、元素的打印、数列长度和起始位置
的维护等任务。这样的设计好不好呢?

如果抽象基类的设计者,同时提供了一些派生类,而且他预期不会常有其他派生类需要加入此继承体系内,那么这样的设计可以顺畅工作。但是如果时常需要加入新的数列类,而且这类工
作还外包给数学能力甚于编程能力的程序员,那么这样的设计反而会使派生类的加入工作变得更为复杂。


以下是基类的另一个设计方式,'将所有派生类共有的实现内容剥离出来, 移至基类内'。接口依旧没有变动, 前一节的程序亦不必改变  -- 当然重新编译是免不了的。这样的设计简
化了我们为提供派生类而必须付出的努力。


class num_sequence{
public:
  virtual ~num_sequence();
  virtual const char* who_i_am() const;
  ostream& print(ostream& os = cout) const;
  int length() const; { return length_; }
  int beg_pos() const { return beg_pos_; }
  static int max_elems() { return 64; }
protected:
  virtual void gen_elems(int pos) const = 0;
  bool check_integrity(int pos, int size) const;
  num_sequence(int len, int bp, vector<int>& ve) : length_(len), beg_pos_(bp), relems_(ve){}
  int length_;
  int beg_pos_;
  vector<int> &relems_;
};

有一个新的 data member 被加入 num_sequence 类内: relems_ 是个 reference to int vector。为什么它被声明为 reference 而非 pointer 呢?  reference
永远无法代表空对象(null object), pointer 却有可能是 null。让它成为 reference, 我们就再也不必检查它是否为 null 了。

Data member 如果是个 reference, 必须在 constructor 的 member initialization list 中加以初始化。一旦初始化，就再也无法指向另一个对象。如果 
data member 是个 pointer, 就无此限制: 我们可以在 constructor 内加以初始化，也可以先将它初始化为 null, 稍后再令它指向某个有效的内存地址。'程序设计过程中
我们便是根据这些不同的性质来决定要使用 reference 或  pointer'。


// !! 初始化、析构、复制

Initialization,Destruction,and Copy

如今的 num_sequence 具有实际的 data member, 我必须为它们提供初始化行为。我可以将初始化操作留给每个派生类, 但这么做会有潜在的危机。'较好的设计方式是,为基类
提供 constructor, 并利用这个 constructor 处理基类所声明的所有 data member 的初始化操作'。

记住, num_sequence 乃是一个抽象基类, 我们无法为它定义任何对象。num_sequence 扮演的角色是每个派生类对象的子对象(subobject)。基于这个原因, 我将基类的
constructor 声明为 protected 而非 public。

派生类对象的初始化行为, 包含调用其基类的 constructor, 然后再调用派生类自己的 constructor。这个过程有助于我们了解, 派生类对象之中其实含有多个子对象:由基类
constructor 初始化的基类子对象, 以及由派生类 constructor 所初始化的派生类子对象。

派生类的 constructor, 不仅必须为派生类的 data member 进行初始化操作, 还需要为其基类的 data member 提供适当的值。


当我们以某个 Fibonacci 对象作为另一个 Fibonacci 对象的初值时,又会发生什么事呢?


Fibonacci fb1(2,3);
Fibonacci fb2 = fb1;

如果我们为 Fibonacci 定义了一个 copy constructor,以上便会调用该 copy constructor。

如果基类未自行定义 copy constructor, 那又会发生什么事呢? 不会太糟, 因为 default memberwise initialization 程序会起来执行。


// !! 在派生类中定义一个虚函数

Defining a Derived Class Virtual Function

'当我们定义派生类时, 我们必须决定,究竟要将基类中的虚函数覆盖掉,还是原封不动地加以继承'。如果我们继承了纯虚函数(pure virtual function), 那么这个派生类也会
被视为抽象类, 也就无法为它定义任何对象。

如果我们决定覆盖基类所提供的虚函数, 那么派生类提供的新定义, 其函数原型必须完全符合基类所声明的函数原型, 包括:参数列表、返回类型、常量性(constness)

当我们在派生类中,为了覆盖基类的某个虚函数,而进行声明操作时,不一定得加上关键字 virtual。'编译器会依据两个函数的原型声明,决定某个函数是否会覆盖其基类中的同名函数'


// !! 虚函数的静态解析（Static Resolution）

有两种情况, 虚函数机制不会出现预期行为:

1. 基类的 constructor 和 destructor 内

2. 当我们使用的是基类的对象, 而非基类对象的 pointer 或 reference 时


当我们构造派生类对象时, 基类的 constructor 会先被调用。如果在基类的 constructor 中调用某个虚函数, 会发生什么事? 调用的应该是派生类所定义的那一份吗？

问题出在此刻派生类中的 data member 尚未初始化。如果此时调用派生类的那一份虚函数, 它便有可能访问未经初始化的 data member, 这可不是一件好事。

'基于这个原因, 在基类的 constructor 中, 派生类的虚函数绝对不会被调用'。

为了能够在单一对象中展现多种类型, 多态(polymorphism)需要一层间接性。'在 C++ 中, 唯有用基类的 pointer 和 reference 才能够支持面向对象编程概念'。

当我们为基类声明一个实际对象(例如 print() 的第一参数), 同时也就分配出了足以容纳该实际对象的内存空间。如果稍后传入的却是个派生类对象, 那就没有足够的内存放置派
生类中的各个 data member。例如, 当我们将 AudioBook 对象传给 print():

int main(){
  AudioBook iWish("hello");
  print(iWish, &iWish, iWish);
}

只有 iWish 内的基类子对象(也就是属于 LibMat 的成分)被复制到为参数 object 而保留的内存中。其他的子对象(Book 成分和 AudioBook 成分)则被切掉 sliced off了。

至于另两个参数, pointer 和 reference, 则被初始化为 iWish 对象所在的内存地址。这就是它们能够指向完整的 AudioBook 对象的原因。



// !! 运行时的类型鉴定机制

RunTime Type Identification

每个类都拥有一份 who_am_i() 函数, 都返回一个足以代表该类的字符串:

class Fibonacci : public num_sequence {
public:
  virtual const char* who_i_am() const { return "Fibonacci";}
  //...
};

另一种设计手法, 便是只提供唯一的一份 who_am_i(), 令各派生类通过继承机制加以复用。

这种设计的一种可能做法, 就是为 num_sequence 增加一个 string member, 并令每一个派生类的 constructor 都将自己的类名作为参数, 传给 num_sequence 的
constructor。例如:


inline Fibonacci::Fibonacci(int len, int beg_pos) : num_sequence(len, beg_pos, "Fibonacci"){}

另一种实现便是利用所谓的 typeid 运算符, 这是所谓运行时类型鉴定机制(RunTime Type Identification, RTTI)的一部分, 由程序语言支持。

'它让我们得以查询多态化的 class pointer 或 class reference, 获得其所指对象的实际类型'。

#include <typeinfo>

inline const char* num_sequence::who_i_am() const{
  return typeid(*this).name();
}

使用 typeid 运算符之前, 必须先包含头文件 typeinfo。typeid 运算符会返回一个 type_info 对象, 其中储存着与类型相关的种种信息。

每一个多态类(polymorphic class), 如 Fibonacci、Pell 等等, 都对应一个 type_info 对象, 该对象的 name() 函数会返回一个 const char*, 用以表示类名。

who_am_i() 函数中的表达式:

typeid(*this);

会返回一个 type_info 对象, 关联至 who_am_i() 函数之中由 this 指针所指对象的实际类型。


type_info class 也支持相等和不等两个比较操作。例如, 以下程序代码可以决定 ps 是否指向某个 Fibonacci 对象:


num_sequence *ps = &fb1;
//...
if(typeid(*ps) == typeid(Fibonacci)){
  //...
}

如果接下来我们这么写:

ps->gen_elems(64);

我们就可预期调用的是 Fibonacci 的 gen_elems()。然而, 虽然我们从这个检验操作中知道 ps 的确指向某个 Fibonacci 对象, 但直接在此通过 ps 调用 Fibonacci 的
gen_elems() 函数, 却会产生编译错误:

ps->Fibonacci::gen_elems(64);

是的, ps 并不知道它所指向的对象实际上是什么类型——纵使我们知道, typeid 及虚函数机制也知道。

为了调用 Fibonacci 所定义的 gen_elems(), 我们必须指示编译器, 将 ps 的类型转换为 Fibonacci 指针。static_cast 运算符可以担起这项任务:

if(typeid(*ps) == typeid(Fibonacci)){
  Fibonacci *p = static_cast<Fibonacci*>(ps);
  p->gen_elems(64);
}

static_cast 其实有潜在危险, 因为编译器无法确认我们所进行的转换操作是否完全正确。这也就是我要把它安排在 typeid 运算符的运算结果为真的条件下的原因。


dynamic_cast 运算符就不同, 它提供有条件的转换:

if(Fibonacci *p = dynamic_cast<Fibonacci *>(ps)){
  p->gen_elems(64);
}

'dynamic_cast 也是一个 RTTI 运算符, 它会进行运行时检验操作, 检验 ps 所指对象是否属于 Fibonacci 类'。如果是, 转换操作便会发生, 于是 p 便指向该 
Fibonacci 对象。如果不是, dynamic_cast 运算符返回0。一旦 if 语句中的条件不成立, 那么对 Fibonacci 的 gen_elems() 所进行的静态调用操作也不会发生。


























