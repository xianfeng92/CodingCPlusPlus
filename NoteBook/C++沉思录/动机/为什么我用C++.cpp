// !! 为什么我用 C++

尽管 C++ 程序天生不如相应的 C 程序快，但是 C++ 使我能在自己的智力所及的范围内使用一些高超的技术，而对我来说，用 C 来实现这些
技术太困难了


// !! 可靠性与通用性

C 没有内建的可变长数组: 编译时修改数组大小的唯一方法就是动态分配内存。因此，我想避免任何限制，就不得不导致大量的动态内存分配和由此带来
的复杂性，复杂性又让我担心可靠性。


当时，我想 C++ 有这么几个特点对我有帮助:

1. 抽象数据类型的观念

2. 另一个优势是 Jonathan Shopiro 最近写的一个组件包，用于处理字符串和链表。



为什么 C 必须考虑这些细枝末节，再来看一看 C++ 程序员怎样才可能避免它们

'尽管 C 有字符串文本量，但它实际上没有真正的字符串概念'。字符串常量实际上是未命名的字符数组的简写（由编译器在尾部插入空字符来标识串尾），
程序员负责决定如何处理这些字符。因此，尽管下面的语句是合法的:

char hello[] = "hello";

但是这样就不对了:

char hello[5];
hello = "hello";

因为 C 没有复制数组的内建方法。第一个例子中用 6 个元素声明了一个字符数组，元素的初值分别是‘h’、‘e’、‘l’、‘l’、‘o’和‘\0’（一个空字符）。
第二个例子是不合法的，因为 C 没有数组的赋值，最接近的方法是：

char *hello;
hello = "Hello";

这里的变量 hello 是一个指针，而不是数组：它指向包含了字符串常量 “hello” 的内存。


假设我们定义并初始化了两个字符“串”：

char hello[] = "hello";
char world[] = "world";

并且希望把它们连接起来。我们希望库可以提供一个 concatenate 函数，这样我们就可以写成这样：

char helloworld[];
concatenate(helloworld,hello,world);

可惜的是，这样并不奏效，因为我们不知道 helloworld 数组应该占用多大内存。通过写成

char helloworld[12];// 危险
concatenate(helloworld,hello,world);

可以将它们连接起来，但是我们连接字符串时并不想去数字符的个数。当然，通过下面的语句，我们可以分配绝对够用的内存：

char helloworld[10000];// 浪费但任然危险
concatenate(helloworld,hello,world);

但是到底多少才够用？只要我们必须预先指定字符数组的大小为常量，我们就要接受猜错许多次的事实。

避免猜错的唯一办法就是动态决定串的大小。因此，譬如我们希望可以这样写：

char * helloworld;
helloworld = concatenate("hello","world");

让 concatenate 函数负责判断包含变量 hello 和 world 的连接所需内存的大小、分配这样大小的内存、形成连接以及返回一个指向该内存的指针
等所有这些工作。


// !! 重复利用的软件

考虑问题的本质是什么，再定义一个类来抓住这个本质，并确保这个类能独立地工作。然后在遇到符合这个本质的问题时就使用这个类。令人惊讶的是，
解决方法通常只用编译一次就能工作了。

