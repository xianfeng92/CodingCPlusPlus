// !! 值语义与数据抽象

// !! 什么是值语义

'值语义 (value sematics) 指的是对象的拷贝与原对象无关，就像拷贝 int 一样'。C++ 的内置类型 (bool/int/double/char) 都是值语义, 标准库里的 complex<> 、pair<>、
vector<>、map<>、string 等等类型也都是值语意, '拷贝之后就与原对象脱离关系'。

与值语义对应的是“对象语义/object sematics”, 或者叫做引用语义 (reference sematics), 由于“引用”一词在 C++ 里有特殊含义, 所以我在本文中使用“对象语义”这个术语。
对象语义指的是面向对象意义下的对象, 对象拷贝是禁止的。例如 拷贝 Thread 是无意义的, 也是被禁止的: 因为 Thread 代表线程, 拷贝一个 Thread 对象并不能让系统增加一个一模一
样的线程。

同样的道理, 拷贝一个 Employee 对象是没有意义的, 一个雇员不会变成两个雇员, 他也不会领两份薪水。拷贝 TcpConnection 对象也没有意义, 系统里边只有一个 TCP 连接, 拷贝 
TcpConnection 对象不会让我们拥有两个连接。

面向对象意义下的"对象"是 non-copyable。

'Java 里边的 class 对象都是对象语义/引用语义'。

ArrayList<Integer> a = new ArrayList<Integer>();
ArrayList<Integer> b = a;

那么 a 和 b 指向的是同一个 ArrayList 对象, 修改 a 同时也会影响 b。


C++ 中的值语义对象也可以是 mutable, 比如 complex<>、pair<>、vector<>、map<>、string 都是可以修改的。

值语义的对象不一定是 POD, 例如 string 就不是 POD, 但它是值语义的。

值语义的对象不一定小, 例如 vector<int> 的元素可多可少, 但它始终是值语义的。



// !! 值语义与生命期

'值语义的一个巨大好处是生命期管理很简单', 就跟 int 一样——你不需要操心 int的生命期。值语义的对象要么是 stack object 或者直接作为其他 object 的成员, 因此我们不用担心
它的生命期（一个函数使用自己 stack 上的对象, 一个成员函数使用自己的数据成员对象）。相反, 对象语义的 object 由于不能拷贝, 我们只能通过指针或引用来使用它。

一旦使用指针和引用来操作对象, 那么就要担心所指的对象是否已被释放, 这一度是 C++ 程序 bug 的一大来源。此

此外, 由于 C++ 只能通过指针或引用来获得多态性, 那么在 C++ 里从事基于继承和多态的面向对象编程有其本质的困难——对象生命期管理（资源管理）。

现在有了 smart pointer, 我们可以借助 smart pointer 把对象语义转换为值语义, 从而轻松解决对象生命期.

'如果不使用 smart pointer, 用 C++ 做面向对象编程将会困难重重'。


// !! 值语义与标准库

'C++ 要求凡是能放入标准容器的类型必须具有值语义'。

但是, 由于 C++ 编译器会为 class 默认提供 copy constructor 和 assignment operator, 因此除非明确禁止, 否则 class 总是可以作为标准库的元素类型——尽管程序可以编译
通过, 但是隐藏了资源管理方面的 bug。

在现代 C++ 中, 一般不需要自己编写 copy constructor 或 assignment operator, 因为只要每个数据成员都具有值语义的话, 编译器自动生成的 member-wise 
copying&assigning 就能正常工作; 如果以 smart ptr 为成员来持有其他对象, 那么就能自动启用或禁用 copying&assigning。



// !! 值语义与 C++ 语言

值语义是 C++ 语言的三大约束之一, C++ 的设计初衷是让用户定义的类型 (class) 能像内置类型 (int) 一样工作, 具有同等的地位。

为此 C++ 做了以下设计（妥协）:

1. class 的 layout 与 C struct 一样, 没有额外的开销。定义一个只包含一个 int 成员的 class 的对象开销和定义一个 int 一样

2. 甚至 class data member 都默认是 uninitialized, 因为函数局部的 int 是 uninitialized

3. class 可以在 stack 上创建, 也可以在 heap 上创建。因为 int 可以是 stack variable

4. class 的数组就是一个个 class 对象挨着, 没有额外的 indirection。因为 int 数组就是这样

5. 编译器会为 class 默认生成 copy constructor 和 assignment operator。C++ 的对象默认是可以拷贝的, 这是一个尴尬的特性。

6. 当 class type 传入函数时, 默认是 make a copy (除非参数声明为 reference)。因为把 int 传入函数时是 make a copy。C++ 的函数调用比其他语言复杂之处在于参数传递
   和返回值传递。C++ 对象是值语义, 如果以 pass-by-value 方式把对象传入函数, 会涉及拷贝构造。代码里看到一句简单的函数调用，实际背后发生的可能是一长串对象构造操作, 因此
   减少无谓的临时对象是 C++ 代码优化的关键之一。

7. 当函数返回一个 class type 时, 只能通过 make a copy (C++ 不得不定义 RVO 来解决性能问题)。因为函数返回 int 时是 make a copy。

8. 以 class type 为成员时, 数据成员是嵌入的。


// !! 什么是数据抽象

C++ 的强大之处在于抽象不以性能损失为代价。

数据抽象 (data abstraction) 是与面向对象 (object-oriented) 并列的一种编程范式 (programming paradigm)。


支持数据抽象一直是 C++ 语言的设计目标, Bjarne Stroustrup 在他的《The C++ Programming Language》第二版中写道:

The C++ programming language is designed to

1. be a better C

2. support data abstraction

3. support object-oriented programming

4. supports generic programming

那么到底什么是数据抽象？

简单的说, 数据抽象是用来描述 (抽象) 数据结构的。数据抽象就是 ADT。一个 ADT 主要表现为它支持的一些操作, 比方说 stack.push、stack.pop, 这些操作应该具有明确的时间和空
间复杂度。另外, 一个 ADT 可以隐藏其实现细节, 比方说 stack 既可以用动态数组实现, 又可以用链表实现。

按照这个定义, 数据抽象和基于对象 (object-based) 很像, 那么它们的区别在哪里? 语义不同。ADT 通常是值语义, 而 object-based 是对象语义。

比方说:

stack<int> a;
a.push(10);
stack<int> b = a;
b.push(20);

这时候 a 里仍然有元素 10。

// !! C++ 标准库中的数据抽象

C++ 标准库里 complex<> 、pair<>、vector<>、list<>、map<>、set<>、string、 stack、queue 都是数据抽象的例子。vector 是动态数组, 它的主要操作有 size()、
begin()、end()、push_back() 等等, 这些操作不仅含义清晰, 而且计算复杂度都是常数。类似的, list 是链表, map 是有序关联数组, set 是有序集合、stack 是 FILO 栈、
queue 是 FIFO 队列。动态数组、链表、有序集合、关联数组、栈、队列都是定义明确 (操作、复杂度) 的抽象数据类型。


// !! 数据抽象与面向对象的区别

本文把 data abstraction、object-based、object-oriented 视为三个编程范式。这种细致的分类或许有助于理解区分它们之间的差别。

庸俗地讲，面向对象 (object-oriented) 有三大特征: 封装、继承、多态。而基于对象 (object-based) 则只有封装, 没有继承和多态, 即只有具体类, 没有抽象接口。
它们两个都是对象语义。

'面向对象真正核心的思想是消息传递 (messaging), 封装继承多态只是表象'。

数据抽象与它们两个的界限在于"语义", 数据抽象不是对象语义, 而是值语义。

数据抽象是针对"数据"的, 这意味着 ADT class 应该可以拷贝, 只要把数据复制一份就行了。如果一个 class 代表了其他资源 (文件、员工、打印机、账号), 那么它就是 
object-based 或 object-oriented 而不是数据抽象。

ADT class 可以作为 Object-based/object-oriented class 的成员, 但反过来不成立, 因为这样一来 ADS class 的拷贝就失去意义了。


// !! 数据抽象所需的语言设施

不是每个语言都支持数据抽象, 下面简要列出"数据抽象"所需的语言设施。

支持数据聚合

数据聚合 data aggregation 或者 value aggregates。即定义 C style struct, 把有关数据放到同一个 struct 里。这种数据聚合 struct 是 ADT 的基础, struct List、
struct HashTable 等能把链表和哈希表结构的数据放到一起, 而不是用几个零散的变量来表示它。


全局函数与重载


成员函数与 private 数据

数据也可以声明为 private 防止外界意外修改。不是每个 ADT 都适合把数据声明为 private, 例如 complex、point、pair<> 这样的 ADT 使用 public data 更加合理。



拷贝控制  (copy control)

当拷贝一个 ADT 时会发生什么? 比方说拷贝一个 stack 是不是应该把它的每个元素按值拷贝到新 stack?


操作符重载

如果要写动态数组, 我们希望能像使用内置数组一样使用它, 比如支持下标操作。C++ 可以重载 operator[] 来做到这一点。


效率无损

抽象不代表低效。在 C++ 中提高抽象的层次并不会降低效率。


