
// !! 设计优化

我们可以粗略地将性能优化分为两种类型:'编码优化和设计优化'。编码优化定义为不需要完整理解要解决的问题或者应用程序的执行流程就能实施的优化。通过定义可以看出，
编码优化用于局部代码，同时该过程不牵涉周围的代码。除了这些容易实现的优化之外，剩下的所有优化都可以归结为设计优化。这些优化是系统性的--它们依赖于其他组件甚至
一些关联度很低的模块的代码。设计优化贯穿于所有代码。这并非一个精确的数学定义，而且某些优化很难用这个不甚精确的定义来界定。

通过学习本章提供的实例，设计优化的整体思路将会变得更加清晰明了。

// !! 设计灵活性

过去的 10 年中，我们遇到过很多远不能满足其性能要求的 C++ 工程。所有这些性能失败的关键在于: '为了过度的灵活性和可重用性而调整了设计以及实现方案'。由于受到可重
用理念的羁绊，生产出来的软件性能很差，甚至无法使用，当然更不用提代码可重用了。C++ 将面向对象编程带入主流，并为众多程序设计组织欣然接受面向对象编程铺平了道路。
面向对象编程的培训机构将 C 语言程序员塑造成为新一代的编程人员，他们'专注于创造具有通用性、灵活性和可重用性的软件'。然而，问题是性能与灵活性总是相互对立的，而且
低劣的设计或实现是无法兼顾二者的。这好比两个作用方向相反的力之间的对立。

如果您想反弹琵琶，要证明程序的性能与灵活性确实可以找到平衡点，那么可能需要将标准模板库(Standard Template Library，STL)作为证据加入讨论。STL 具有功能强大
、通用、灵活以及可扩展的特点。'在某些情况下，STL 产生的代码其性能可以匹敌手工编码的 C 语言代码'。

这好像击败了我们的观点。下面进行深入讨论。

以 STL 中的 accumulate() 函数为例：它可以对任意集合中的对象累加。这个函数接收如下 3 个参数:

● 指向集合开始位置的迭代器。
● 指示集合结束位置的迭代器。
● 初始值。

accumulate() 函数将集合从开始位置到结束位置的所有对象累加到初始值中。此函数可以累加不同类型的对象：整型、浮点型、字符型、字符串，甚至是用户自定义类型，而且不
必关心集合是否是数组、链表、向量或者其他集合。它所关心的全部在于用户是否传递了其需要的两个控制迭代起止位置的指示器。此外，accumulate() 函数除了加法运算外，也
可以进行其他类型的二元运算。可以指定二元操作符作为可选参数。很明显，这是一段优秀的代码。它具有高灵活性以及通用性。有时，accumulate() 函数甚至会表现出卓越的性
能。它可以累加如下的整型数组:

sum = accumulate(&a[0], &a[size], 0);

它和如下自编的代码一样快：

int sum = 0;
for(int i = 0; i < size; ++i)
{
    sum += a[i];
}

这相当不错。accumulate() 函数的实现类似于中的代码行：

template <class InputIterator, class T>
T accumulate(InputIterator first, InputIterator end, T initialValue)
{
    while(first != end)
    {
        initialValue += *first++;
    }
}

accumulate() 函数实现的优点在于它对集合以及集合所包含的对象做的假设极少，它只需要知道两件事情：

● 从 first 迭代器开始顺序递增，直到最终碰到 end 迭代器；
● 集合中所包含的对象对“+”操作符来说是可接受的。

这两个最低限度的假设保证了 accumulate() 函数极大的灵活性。但同时也会变为该函数的性能弱点。这些假设也许满足高性能整型数相加的需要，但其他具有复杂结构的类型
将不得不舍弃其类型特有知识的优势。以 string 类型为例，假设将连接如下字符串集合:

vector<string> vectorstr;
for(int i = 0; i < 100; i++)
{
    vectorstr.push_back("abcd");
}

使用 accumulate() 函数应该是首选，除非必要，无须重新编写代码：

string empty;

result = accumulate(vectorstr.begin(), vectorstr.end(),empty);

这种办法确实可以用，但速度如何呢？对这段代码的 100，000 次迭代进行计时：

vector<string> vectorstr;
for(int i = 0; i < 100000; i++)
{
    result = accumulate(vectorstr.begin(), vectorstr.end(),empty);
}

这段代码消耗29s。自编代码的性能可能胜过STL吗？笔者做了如下尝试：

void stringSum1(vector<string> vs, string& result)
{
    int i = 0;
    int totalInputLength = 0;
    int  vectorSize = vs.size();

    int *stringSizes = new int[vectorSize];

    for(int i = 0; i < vectorSize; i++)
    {
        stringSizes[i] = vs[i].length();
        totalInputLength += vs[i].length();
    }

    char *s = new char[totalInputLength + 1];
    int sp = 0;
    for(int i = 0; i < vectorSize; i++)
    {
        memcpy(&s[sp], vs[i].c_str(), stringSizes[i]);
        sp += stringSizes[i];
    }

    delete[] stringSizes;
    result = s;
    return;
}

同样，对这个方法进行计时：

编代码更快——只需5s，速度提高了5倍多。该方法的效率远远超过了 accumulate() 函数，原因在于我们为了提高性能而牺牲了通用性。stringSum1() 函数对 string 
类型做了如下特别的假设：

● 需要相加的唯一对象就是字符串
● string 类型相加需要申请内存分配来存储 string 结果

通过这些假设可以预先知道 string 类型结果的大小，由此可以通过一个简单步骤申请足够大的内存来存储结果。这是自编代码比 accumulate() 函数快如此多的根本原因。
accumulate() 函数需要多次实时的调用以分配额外内存缓冲区，而这些缓冲区的大小事先无法知道。更为糟糕的是，每次当 accumulate() 函数用完缓冲空间时，就会将旧内
存缓冲区中的内容复制到新申请的更大的一块内存缓冲区内。

这个例子清楚地说明了如何通过降低灵活性来增加效率。stringSum1() 在灵活性和功能上远不及 accumulate() 函数。除了 string 类型对象外，它无法对其他类型对象进行
相加。这好比一个 60 瓦的灯泡和一束激光的差距。并非激光束所携带的能量比灯泡多，它只是将光束集中于某个狭窄的范围。尽管无法使用激光束来照亮房间，但可以使用它在墙上
打一个洞。

我们的目的绝不是批评 STL, 只需要考虑在某些性能热点上替代 STL 的代码。由于这些热点无法预测，所以默认情况下，在软件开发的早期阶段应当全部使用 STL。这个讨论的目
的是强调一个原则，由于人们对开发可重用软件趋之若鹜，现在这个原则已经被弃之一旁：'在软件灵活性与性能之间有一个基本的平衡'。

'在典型的应用中，特定的条件和简化的假设是常见的获取高性能的方法'。软件库是通用的, 但应用程序却不是。'将关注的焦点集中于代码的细节将会产生更高效的代码'。


// !! 缓存

缓存先前的结果有多种不同的方式。其中的一种方式是将其作为对象的成员数据。如果您发现自己的程序不断重复地使用一个对象来获得一个相关的结果，那么更好的做法是将这
个结果作为此对象的数据成员保存起来，并在将来的计算中使用。


// !! 高效的数据结构

'软件性能通常等同于算法和所使用的数据结构的效率，有时算法和数据结构的效率被认为是影响软件性能的最重要因素'。不论事实如何，使用高效率的算法是实现软件高效率的一
个必要条件，这是毋庸置疑的。如果选择了低效的算法，那么不管进行多少细微调整都无济于事。您当然可以把所有变量都放入寄存器中、内联所有函数，以及展开所有循环。不过
，'不管怎样冒泡排序的速度都比不上快速排序'。关于该重要话题的详细讨论已经超出了本书的范围，高效的算法和数据结构已经成为研究的热点，而且有很多书籍专门论述这个主题。
高效算法很重要，而且是必需的，但却不是程序高效的充分条件。以我们的经验看，软件性能是由若干因素共同影响的，而且无法挑出哪一个最为重要。例如，心脏无疑是一个重要的
器官，但如果没有肝脏，你也无法存活。过多的专注于算法并将其作为决定性能的唯一因素显然是错误的。


// !! 延迟计算

许多性能优化通过更高效的计算方法来获取速度。一些重大的性能优化不仅可以通过提高计算速度实现，还通过消除计算来获得。

延迟计算问题看似更加可能出现在大规模的代码中，比如，为旅行商问题(Traveling Salesman Problem，TSP)编写一个方法，问题描述占用一段，代码实现少于 100 行。
TSP问题的描述和实现可以被一个开发者完全理解，这是典型的小规模工程。在这种环境中，几乎不可能发现那些毫无用处且可以轻松避免的昂贵计算。从本质上讲，小规模代码
优化通常是棘手的。

当您参与大规模设计工程时，常常会发现自己难以招架。大规模工程可能包含成千上万行代码，问题描述不再是占用一小段，很有可能 HTTP 协议说明书就占用了100页。而且问
题描述不是固定的，而是时常变化的，从一个版本到下一个版本不断变化，受到市场趋势和顾客要求的影响。

复杂性的增加会导致出现这样一种情况：团队中没有任何一个人对整体实施情况有深入和全面的认识。开发团队被划分为更小的组，每个组专门负责整个解决方案的特定方面。
对整体情况缺乏了解导致大量严重影响性能的编码和设计错误，只有在这种复杂的情况下，延迟计算作为一种调整武器的作用才得以显现。


// !! 无用计算

实践中可能会遇到一种编程习惯, 那就是不假思索地用零填充大的数据结构。您可以通过调用 calloc() 分配一块用零填充的内存块，或者调用 
memset(void＊block，0，int blockLen) 自己完成。

Web 服务器使用缓冲套接字对象来存储新进来的请求：

class BufferStremaSocket
{
private:
    int socketId;
    char inputBuffer[4096];
};

BufferedStreamSocket 构造函数自动用零填充输入缓冲区：

BufferedStreamSocket::BufferedStreamSocket(...)
{
    memset(buffer,0，4096);
}

我们通常不反对调用 memset() ，它有其相应的作用，只有当调用 memset() 没有什么意义时我们才反对。

详细检查源代码后可以发现没有在任何地方使用填零的输入缓冲区。而且我们从没有假设它的存在，也没有使用它。显而易见地，“只有在某些情况下”缓冲区才执行 memset()。当
从套接字中读取数据并复制到用户提供的缓冲区时，当需要获得读取的字节数目时，都要执行 memset() 。读取字节的数目可以获知数据缓冲区的逻辑结束位置，这不同于 null 
终止符的字符串。既然从未使用过，那么构造函数调用 memset() 纯粹是浪费时间。

尽管这些无用计算的例子看似很愚蠢，而且您会认为自己从不做这些事情。但实际上，我们在许多场合都碰到过这样的计算，尤其是在复杂、大规模代码中。


// !! 失效代码

这是另一类听起来愚蠢但实际上经常发生的情况。这里讨论的是那些已经不提供功能却仍在执行路径中的代码。这种情况在学校布置的编程作业或者小型程序原型中不经常发生，而在大
型编程任务中不时能遇见。用户对软件的需求不断变化，而软件在版本更迭的过程不断演进。新的功能被添加到软件中，而同时旧功能可能被丢弃。实现本身随着bug的修复和功能的增
强而不断变化。不断变化的需求和实现产生了许多僵死的（从未被执行）和失效的（被执行但无用）代码。


// !! 要点

● 在软件性能和灵活性之间存在一种基本的平衡。对于在 80% 时间内执行的 20% 的软件，性能通常损失在灵活性上

● 在代码细节中可以利用缓存优化代码，在整个程序设计中也能采用这种方法。通常可以通过将先前的计算结果保存起来避免大量的计算

● 对于软件的高效性而言，使用高效的算法和数据结构是必要条件，但并非充分条件

● 有些计算只有在特定执行条件下才需要。这些计算应该被推迟到确实需要它们的路径上来完成。如果过早地执行计算，那么其结果可能并没有被使用

● 大型软件往往会变得错综复杂，杂乱不堪。混乱软件的一大特点就是执行失效代码：那些曾经用来实现某个目标，但现在已经不需要的代码。定期清理失效和僵死代码可以增强
  软件性能，同时对于软件也是一种维护