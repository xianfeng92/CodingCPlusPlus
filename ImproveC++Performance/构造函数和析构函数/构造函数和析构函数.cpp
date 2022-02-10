// !! 构造函数和析构函数

在理想的世界中，构造函数和析构函数是不存在开销的。它们将只执行必要的初始化和清除工作，普通的编译器都会内联它们。例如这样的 C 代码:

{
    struct X x1;
    init(&x1);
    ...
    cleanup(&x1);
}

在C++中会像这样：

{
    X x2;
    ...
}

它们的开销是一样的。理论上是如此。由这里深入软件开发的世界时，大家会发现实际情况与此稍有不同。我们经常会遇到继承和复合实现，它们对于所解决的问题而言，过于灵活
和通用。它们执行的计算可能几乎或者完全没有必要。在实践中发现性能开销与继承和复合相关联，也是我们意料之中的事情。'这是一个更大问题的冰山一角，即代码重用和性能之间
的基本矛盾'。继承和复合与代码重用有关。通常，可重用代码会在某种特定场合下计算某些不需要的数据。每次调用一个所做此类计算工作超过实际所需的函数时，对代码的性能就
是一次打击。

// !! 继承

'在面向对象的设计中，继承和复合是两种把类联系在一起的方式'。

本节我们要讨论基于继承的设计与构造函数和析构函数的开销之间的联系。我们从一个实用的例子开始这个讨论: 线程同步构造的实现。在多线程应用程序中，您经常需要为了限制并
发访问共享资源而提供线程同步。线程同步的构造各式各样，最常见的 3 种方式是:'信号(semaphore)、互斥(mutex)和临界区(critical section)'。

'信号方式提供了受限的并发'。它允许最多为给定上限的线程访问共享资源。当并发线程的最大数量为 1 时，我们称这种特殊的信号量为互斥(MUTual EXclusion)。
互斥方式通过在任何时间允许且只允许一个线程对共享资源进行操作来保护共享资源。一般情况下共享资源可以由分散于应用程序各处的各个代码段进行操作。


以一个共享队列为例。该队列中元素的个数通常由 enqueue() 和 dequeue() 共同管理。很明显，不能允许多个线程同时对元素个数进行修改。

Type& dequeue()
{
    get_the_lock(queue_lock);
    ...
    -- numOfElements;
    ...
    release_the_lock(queue_lock);
    ...
}


void enqueue(const Type& value)
{
    get_the_lock(queue_lock);
    ...
    ++ numOfElements;
    ...
    release_the_lock(queue_lock);
}

如果 enqueue() 和  dequeue() 都能并发地修改 numberOfElements，我们很可能得到的是一个包含错误值的 numberOfElements。修改这个变量必须以原子操作完成。

'互斥锁最简单的应用是临界区'。临界区是指某一时间只能由一个线程执行的一个代码段。线程在进入临界区之前就必须为获得锁而竞争来达到互斥的效果。成功获取锁的线程就
可以进入临界区。当要退出临界区时，该线程释放锁以允许其他线程进入。

    get_the_lock(queue_lock);
    {// 临界区开始
    // 受保护的代码
    ...
    }// 临界区结束
    release_the_lock(queue_lock);

在例子 dequeue() 中，很容易就可以检查代码，验证每一个锁操作都有与之相匹配的解锁操作。实际上我们习惯于看到几百行代码的例程中包含多条返回语句。如果在代码执行的
过程中于某处获得了锁，那么在执行任何一条返回语句之前必须释放锁。您可以想象这将是维护人员的梦魇，几乎肯定会有漏洞在这里出现。大型工程可能有许多人在编写代码和修复
漏洞。当你在有 100 行代码的例程中添加一条返回语句时，很可能忽略之前曾获得锁这个事实。这就是第一个问题。第二个问题是异常: 如果抛出一个异常的同时又持有锁，那么您
只好在捕获该异常时手工释放锁。这是很别扭的。

C++ 为这两个难题提供了一个漂亮的解决方法。'当一个对象到达其作用域结尾处时，会自动调用析构函数'。所以'我们可以利用自动调用的析构函数解决锁的维护问题'。把锁封装
在对象内部并让构造函数获得锁，析构函数将自动释放锁。如果在由 100 行代码的例程组成的函数内部定义这样的对象，就无须再担心多条返回声明了。'编译器在每条返回语句之前
插入对带锁的析构函数的调用, 于是锁总是能够被释放'。

使用构造函数和析构函数对去获取和释放共享资源会导致如下所示的锁类实现:


class NIOLock
{
public:
    NIOLock(pthread_mutex_t &key):theKey(key)
    {
        pthread_mutex_lock(&theKey);
    }

    ~NIOLock()
    {
        pthread_mutex_unlock(&theKey);
    }
private:
    pthread_mutex_t &theKey;
};

编程环境通常提供多种风格的同步构造。风格的区别表现在以下几个方面：

1. 并发级别 

    信号允许不多于给定最大数量的线程共享资源。互斥只允许一个线程访问共享资源。

2. 嵌套

    某些构造允许线程在已持有一个锁的情况下再次获得该锁。而这种锁嵌套在另外一些构造的情况下则会发生死锁

3. 通知

    在资源变为可用时，有一些同步构造会通知所有正在等待的线程。这种方式是很低效的，因为除了第一个线程之外，其他所有线程被唤醒后会发现它们不够快，因为资源已经被其他
    线程获得。一个更为有效的通知方案是仅唤醒一个正在等待的进程。

4. 读/写锁 

    允许多个线程读取一个受保护的值，但是只允许一个线程修改它。

5. 内核/用户空间 
    
    某些同步机制只在内核空间中有效。

6. 进程间/进程内 

    一般情况下，同一进程中的线程间同步要比不同进程中的线程同步更为高效。

尽管这些同步构造在语义和性能方面差别很大，但是它们使用相同的锁/解锁协议。这是非常诱人的，因为可以把这种相似性转化为一种基于继承的锁类层级，而这些锁类均来自同一
基类。在我们开发某个产品时，最开始找到了一种实现，大体上是下面这个样子：

class BaseLock
{
public:
    // LogSource 对象将在稍后解释
    BaseLock(pthread_mutex_t &key, LogSource &log);

    virtual ~BaseLock(){};
};

就像你看到的，BaseLock 这个类没什么功能。它的构造函数和析构函数都是空的。'设计 BaseLock 类的意义在于我们将从这个类中派生出各种各样的锁类'。风格各异的锁类自
然要以不同的 BaseLock 子类来实现。MutexLock 就是一个派生出来的类：

class MutexLock : public BaseLock
{
public:
    MutexLock(pthread_mutex_t &key, LogSource &log);
    ~MutexLock();
private:
    pthread_mutex_t &theKey;
    LogSource &theLog;
};

MutexLock 的构造函数和析构函数有如下的实现：

MutexLock::MutexLock(pthread_mutex_t &key, LogSource &log):BaseLock(key, log),theKey(key),theLog(log)
{
    pthread_mutex_lock(&theKey);
    #if defined(DEBUG)
    cout << "MutexLock" << &theKey << "created at  " << log.file() << "line " << log.line() <<'\n';
    #endif

}

MutexLock::~MutexLock()
{
    pthread_mutex_unlock(&theKey);
     #if defined(DEBUG)
    cout << "MutexLock" << &theKey << "destroyed at  " << log.file() << "line " << log.line() <<'\n';
    #endif
}

MutexLock 的实现使用了尚未讨论过的 LogSource 对象。LogSource 对象必须在该对象创建时捕获文件名和源代码行号。在记录错误和跟踪信息时，有必要描述信息源的位置
。C 程序员会用(char ＊)处理文件名，用 int 处理行号。我们 C++ 开发人员则选择在一个 LogSource 对象中把它们全部封装进去。又一次，我们构建了一个什么也不做的基
类，不过由此得到的将是一个更为有用的派生类:

class BaseLogSource
{
public:
    BaseLogSource(){}
    virtual ~BaseLogSource(){}

};

class LogSource : public BaseLogSource
{
public:
    LogSource(const char* name, int num):filename(name), linenum(num){}
    ~LogSource(){}
    char *file();
    int line();
private:
    char *filename;
    int linenum;
};

LogSource 对象就这样被创建并作为参数传递给 MutexLock 对象的构造函数。在得到锁时 LogSource 对象捕获源文件和行号。这些信息在调试死锁时会派上用场。

假设 sharedCounter 是一个可以由多个线程访问且需要序列化的整型变量。我们通过在局部范围内插入一个锁对象来提供互斥:

{
    MutexLock myLock(theKey,LogSource(__FILE__,__LINE__));
    ++sharedCounter;
}

MutexLock 和 LogSource 对象的创建同时触发了对它们各自基类的调用。这一小段代码调用了大量构造函数:

● BaseLogSource
● LogSource
● BaseLock
● MutexLock

当 sharedCounter 变量的值递增之后，我们走到了作用域的结尾，并触发了几个相应的析构函数:

● MutexLock
● BaseLock
● LogSource
● BaseLogSource

对共享资源的保护总计用到 8  个构造函数和析构函数。'代码复用和性能之间的矛盾一直是个令我们挠头的问题'。如果我们抛弃所有这些对象，而去开发一个只做必须做的事情而
不做其他的手工版本，找出都有哪些开销将是一件很有趣的事。也就是说，我们只在更新 sharedCounter 的前后进行关于锁的操作:

{
    pthread_mutex_lock(&theKey);
    ++ sharedCounter;
    pthread_mutex_unlock(&theKey);
}

很显然这个版本比前面的版本更为高效。采用面向对象的设计使我们不得不用更多的指令。

'那些指令都是专门用于创建和销毁对象的。我们需要考虑它们的开销吗'？

这要根据应用背景来判断: 如果我们是在一个性能敏感的流程里，那么就需要这样做。在一些特定情况下，如果总的计算开销很小而执行那些指令的代码段又调用得比较频繁，那么那
些附加指令的开销就变得十分显著。'我们所关心的就是被浪费的指令与所有计算的总指令的比率'。

刚才讨论的代码取自于一个网关的实现，它把数据包从一个通信适配器路由导向到另一个。这是一个大约包含 5000 条指令的关键执行路径。MutexLock 对象在该路径中被用到几次
。而这几次调用累计起来的指令开销占到全部开销的 10%，这是非常可观的。

'如果打算在性能要求严格的应用程序里使用 C++ 和面向对象的设计，我们无法负担这样奢侈的行为'。在提供一个 C++ 的基础方案之前，我们应该很快指出设计中明显的过度使用
行为。如果临界区像一条整型变量递增语句那样简单，那么要这些面向对象系统干什么呢？ 使用锁对象的好处在于它可以实现:

● 对包含多个返回点的复杂子程序的维护
● 从异常中恢复
● 锁操作中的多态
● 日志记录的多态

这些优点在我们的例子中都不是十分重要的。临界区定义有清晰的唯一出口，同时整型变量的递增操作也不会抛出异常。锁操作和日志记录中的多态同样是一些无所谓有无的东西。有趣
的是，正如这个代码段所示，实际上程序员在熟练地做这件事情，这说明对象的创建与销毁的开销被严重忽视了。

那么在一个确实有必要使用锁对象的复杂例程里，事情会如何呢？ 我们仍然需要减少它的开销。首先我们来考虑 LogSource 对象。那条消息耗费了 4 次函数调用：基类和派生类的
构造函数和析构函数。这种奢侈的做法我们的环境是无法承担的。'在提及 C++ 性能时，内联通常用来作为一种补救方法'。尽管内联在此有所帮助，但是它并没有彻底解决这个问题。
在最理想的情况下，内联将消除所有四个构造函数和析构函数的调用开销。即使这样，LogSource 对象仍然会强制带来一些性能开销。第一，它是 MutexLock 构造函数的一个附加参
数。第二，要分配 MutexLock 的 LogSource 指针成员。此外，当创建 LogSource 对象时，建立其虚表指针需要附加一些指令。

'在对性能要求敏感的路径中，需要使用一种常识性的折中方法, 丢弃不重要的功能来换取有价值的性能'。

LogSource 对象必须这样做。在构造函数里，即使是内置类型，分配成员数据字段也要耗费一些指令。每个成员数据字段的开销也许不大，但是它们对性能的影响是会累积的。这个开
销会随着构造函数所初始化的数据成员数量的增多而相应增加。

使用 LogSource 对象的代码是用 ＃ifdef DEBUG 括起来的，这个事实更进一步地证明，该对象的使用并不是必需的。只有在开发测试阶段才会用到 DEBUG 编译标志；在关闭 
DEBUG 的情况下进行编译的结果才会发布给客户。当在生产环境中执行代码时，我们为 LogSource 对象付出了代价，却从未真正使用它。这是纯粹的开销。LogSource 对象应该
在其所有剩余部分使用 ＃ifdef 来彻底地消灭，包括清除 MutexLock 的指针成员和构造函数参数。对 LogSource 对象局部使用 ＃ifdef 是开发马虎的一个例子。这并不罕见
，由此可见，摆脱马虎的 C++ 开发作风之不易。

下一步是消除锁类层次中的 BaseLock 根类。从 BaseLock 的角度讲，它不提供任何数据成员，并且除了构造函数原型之外，不提供任何有意义的接口。BaseLock 对整个类设计的
贡献是存在争议的。尽管内联的使用已经减少了调用开销，但是 BaseLock 的虚析构函数还是会引起在 MutexLock 对象中设置虚表指针的开销。节省一次赋值也许不会改变什么，
但是节省每一个小的开销对性能将会有大帮助。内联其余的 MutexLock 构造函数和析构函数将消除对这两个函数的调用开销。

'消除 LogSource 类、BaseLock 类，以及内联 MuteLock 构造函数和析构函数，这几项操作联合起来将会显著地削减指令数量'。这样将会产生和 C 手工编码一样有效率的代码。
对内联后的 MutexLock 由编译器产生的代码将等价于如下伪代码:

{
    MutexLock::theKey = key;
    pthread_mutex_lock(&MutexLock::theKey);
    ++ sharedCounter;
    pthread_mutex_unlock(&MutexLock::the);
}

以上 C++ 代码段几乎与手工编码的 C 代码等价，而且我们认为它也将同样地高效。假如果真如此，那么利用锁对象便可以提供 C++ 新增的强大功能，同时不损失效率。为了验证这个
假设，我们测试了三种互斥锁的实现:

● 直接调用 pthread_mutex_lock() 和 pthread_mutex_unlock()
● 不从基类继承的独立互斥对象
● 从基类派生的互斥对象

在第一个测试中，我们只是简单地在共享资源的前后调用 pthread_mutex_lock() 和 pthread_mutex_unlock() 来实现锁:


int main()// 版本1
{
    ...
    // 开始计时
    for(int i=0; i< 10000, i++)
    {
        pthread_mutex_lock(&theKey);
        ++sharedCounter;
        pthread_mutex_unlock(&theKey);
    }
    // 结束计时
    ...
}

int main()// 版本2
{
    ...
    // 开始计时
    for(int i=0; i< 10000, i++)
    {
        SimpleMutex m(mutex);
        ++sharedCounter;
    }
    // 结束计时
    ...
}

int main()// 版本3
{
    ...
    // 开始计时
    for(int i=0; i< 10000, i++)
    {
        DerivedMutex m(mutex);
        ++sharedCounter;
    }
    // 结束计时
    ...
}

运行 100 万次测试循环的计时结果证实了我们的假设。版本 1 和版本 2  在 1.01s 内执行完毕。然而版本 3 却用掉了 1.62s。在版本 1 中，我们使用了互斥调用——这已经是
最高效的办法了。这个例子的意义在于使用独立的对象不会产生任何性能代价。'编译器将构造函数和析构函数内联从而达到了最高效率'，可是我们却为继承付出沉重的代价。基于继
承的锁对象(版本 3)使性能降低了大约 60% 。

这并不是说继承根本上就是代码性能的绊脚石。'我们必须区分全部计算开销、必需开销和计算损失(computional penalty)'。全部计算开销是一次计算中所执行的全部指令的总和。
必需开销是全部指令的子集，它的结果是必要的。这部分计算是必需的，其余部分即为计算损失。计算损失是可以通过别的设计和实现来消除的那部分计算。

为了更清晰地阐明这一点，我们把 SimpleMutex 类作为例子来分析：

class SimpleMutex
{
public:
    SimpleMutex(pthread_mutex_t &lock):myLock(lock)
    {
        acquire();
    }
    ~SimpleMutex()
    {
        release();
    }
private:
    int acquire()
    {
        return pthread_mutex_lock(&myLock);
    }

    int release()
    {
        return pthread_mutex_unlock(&myLock);
    }
    pthread_mutex_t &myLock;
};


SimpleMutex 的构造函数隐含着以下各项计算开销：

● 初始化 myLock 成员
● 调用 acquire() 方法
● 在 acquire() 方法中调用 pthread_mutex_lock()

第三项是必需开销。不管设计如何，使用何种方式，你都必须调用 pthread_mutex_lock() 来锁定资源。第一项，设置 myLock 成员则是计算损失。这是因为采用了基于对象的设
计方式，我们不得不这样做。未能内联 acquire() 调用会导致额外的性能损失。实际上，编译器极有可能通过内联来消除这种损失。

因此，我们不能断言采用了复杂的继承的设计一定是坏的，也不能断定它们总是带来性能损失。

我们只能说总的开销会随着派生树规模的增长而增加。如果所有的计算都是有价值的，那么它们都是必需的开销。实际上，继承层次不见得是完善的。在这种情况下，它们很可能会导
致计算损失。


// !! 复合

对象的复合与继承一样，都引入了与对象创建和销毁有关的类似性能问题。'在对象被创建(或销毁)时，必须同时创建(或销毁)它所包含的成员对象'。

class Trace
{
    ...
    string theFunctionName;
};

创建 Trace 类型的对象时，构造函数会调用 string 的构造函数来初始化 string 数据成员。这种行为是递归性的:如果类 A 包含一个类 B 成员，而 B 又包含一个 C 成员，
则 A 的构造函数就会调用 B 对象的构造函数。依此类推，B 的构造函数又会调用 C 对象的构造函数。鉴于在复合(包容)层次的每一层都可能有多个属性，所以复合层次会产生一个
树形结构，而不是一个简单的列表。'因此，复合树的大小关系到复合的全部开销，而复合树有可能变得非常庞大'。此外，我们必须强调"代价"并不必然意味着"开销"。如果程序用到
了对象的所有功能，那么就不存在开销问题，因为这正是是您需要的。

另一方面，Trace 的例子是一个“代价”与“开销”碰巧一致的例子。'我们并不需要用 string 对象的强大功能去表示正在被跟踪的函数的名字'。我们没有用该对象做任何高深的事情
，因而完全可以将它替换为 char 指针。'一个 char 指针的构造比一个 string 对象廉价多了'。遗憾的是，一些 C++ 编程社区似乎认为，不使用过于复杂的 C++ 数据类型就等
同于对编程不够精通，这将导致编程者滥用复杂的 C++ 数据类型而不是遵守最重要的原则:"尽全力使用最简单的解决方案"。

可以想象一下在复杂的层次中包含巨大的派生和复合树，构造和销毁一个对象的代价将猛增。如果在性能敏感的流程中可以考虑使用这种层次结构的话，在设计阶段需要时刻牢记这一
点。


创建和销毁被包含对象是另一个值得注意的问题。'在创建（或销毁）被包含对象时无法阻止子对象的创建(或销毁)，因为这是编译器自动强加的步骤'。

以前面的 Trace 为例:

class Trace
{
public:
    Trace(const char* name);

private:
    string theFunctionName;
};

Trace 对象的创建将会创建一个 string 子对象。同样，Trace 的析构函数将会销毁 string 子对象。这种行为在实现过程中完全是自动的，你无法去阻止。

'为了对子对象的创建和销毁进行更好的控制，可以用指针来代替它':

class Trace
{
public:
    Trace(const char* name);

private:
    string *theFunctionName;
};

这样我们就可以控制 string 对象的创建和销毁了。当然我们仍然可以选择执行完整的初始化。这种方式将创建一个新的 string 对象，并设置一个指向它的指针:

Trace::Trace(char *name):theFunctionName(new string(name))
{
    ...
}

我们也可以选择部分初始化。我们为这些指针分配一个无效初值，以说明在使用这些对象之前必须创建它们。我们期望的使用模式是：在通常情况下跟踪是关闭的，并且所创建的
Trace 对象很少使用。因此，'使创建和销毁对象的开销达到最小是极为重要的':

Trace::Trace(char *name):theFunctionName(nullptr)
{
    if(traceIsActive)
    {
        theFunctionName = new string(name);
        ...
    }
}

由于采用这种使用方式，第一种和第二种方式十分低效。在通常情况下跟踪应该是关闭的，所以构造  string 对象的努力毫无价值。第三种方式是最有效的，因为向一个指针赋值
0 比构造一个新对象要廉价得多。注意，使用模式决定了哪种方式最有效。如果使用模式是跟踪永远打开，那么第一种方式（包含子对象，而不是指针）是最佳选择。'将 string 
对象嵌入到 Trace 对象中，效率将会更高，因为它占用的是栈内存而不是堆内存, 堆内存的分配与释放代价是相当高昂的'。基于栈的内存在编译时分配，而在函数调用返回时的
堆栈清除阶段被释放。

// !! 缓式构造

性能优化经常会打破竞争因素之间的脆弱平衡。'也许这就是我们说性能最佳与代码优化是相悖的原因吧'。性能优化经常需要牺牲一些其他软件目标，诸如灵活性、可维护性、成本和
重用之类的重要目标经常必须为性能让步。解决了性能问题，换而言之，生成了高质量的代码，而不影响其他软件开发目标的情况是很少见的。我们有时很幸运，没有付出代价就消除简
单的编码错误，获得更高的性能。

我们准备展示的第一种优化便是这样一个例子。该例子从代码段中消除了对从未使用的对象的创建(和随后的销毁)。

'如果打算在代码段的性能敏感路径中实例化一个对象, 您应当考虑开销的因素'。最廉价的对象无疑是从不实例化的对象。

在 C、Pascal和其他常用语言中，数据类型必须在代码块的开头定义。因此我们养成了在例程的开头定义例程所需的所有变量的习惯：

void function()
{
    int i, j;
    ...
    compute(i,j);
    ...
    return;
}

'在 C++ 中，不自觉地在程序开始处预先定义所有对象的做法是一种浪费'。因为这样可能会创建一些直到最后都没有用到的对象。这种情况在实际中是发生过的。在我们的 C++ 
代码中，有一个用于分配和回收空闲内存的类 DataPacket:

class DataPacket
{
public:
    DataPacket(char *data, int sz):size(sz)
    {
        buffer = new char[sz];
        ...
    }
    ~DataPacket()
    {
        delete[] buffer;
        ...
    }
private:
    char *buffer;
};

在一定程度上由于内存分配和回收的原因，DataPacket 的创建和销毁开销很大。它占用了 400 多条指令，在我们当时的场景下这样的开销是相当可观的。

DataPacket 被用在程序的性能敏感路径上，该段程序的作用是把数据从一个适配器引导到另一个适配器上去:

void routeData(char *data, int size) 
{
    DataPacket packet(data, size);
    bool direction = getDirection();
    ...
    if(UPSTREAM == direction)
    {
        computeSomething(packet);
    }
    else
    {

    }
}


当且仅当数据发往上游时 packet 对象才会被使用，这种情况发生的概率为 50%。数据发往下游时，根本不会用到 packet 对象。然而 packet 对象却在作用域的开始就被无条
件地创建了。'有一半的时间被闲置，这对计算的时间而言是一种完全的浪费'。

如您所想，这里的解决方案非常简单。packet 对象仅当它确实被需要的时候才会创建。对 packet 的定义应该移到需要使用它的范围，也就是数据发往上游时:

void routeData(char *data, int size) 
{
    bool direction = getDirection();
    ...
    if(UPSTREAM == direction)
    {
        DataPacket packet(data, size);
        computeSomething(packet);
    }
    else
    {

    }
}

'尽管 C++ 语言专家自从 C++ 语言面市之日起就一直劝说编程者把变量的创建延迟到第一次使用前，但是在实际产品代码中仍然可以找到这种编码错误'。C++ 和 C 之间的兼容性被
说成是 C++ 的优点之一，但是兼容性却产生了风格上的不连续。坚持把现在已过时的 C 声明语法用在 C++ 中会产生巨大的性能开销。不幸的是，实际中经常发生这种无意义的错误
。C++ 之所以比 C 更好，其原因部分在于它能够延迟变量的创建。'必须提一下，C 语言中允许在任何块的开头定义变量。因为定义 C 变量没有运行时的开销，故而 C 程序员喜欢
在函数块的开头定义所有变量'。但是，在 C++ 中不是这样，所以一定要注意对象定义的位置。

// !! 冗余构造

继续研究这种简单却导致高昂开销的编码错误，我们再举出一个纯开销的例子:对被包含对象创建两次。

类 Person 包含类 string 的一个对象:

class Person
{
public:
    Person(const char *s)
    {
        name = s;
    }
private:
    string name;
};

考虑一下下面的 Person 默认构造函数的实现:

    Person(const char *s)// 版本 0
    {
        name = s;
    }

必须先实例化 Person 对象，然后再执行 Person 构造函数。Person::Person(char＊) 初始化列表中没有列出被包含的 string 对象。因此，编译器必须插入一个调用以调用
string 的默认构造函数，以便于正确地初始化  string 成员对象，然后执行 Person 的构造函数。语句 name=s；把 char 类型指针 s 赋给左边的 string 型对象。
string::operator=(const char＊) 被调用来执行这个赋值操作。赋值操作所执行的计算本质上覆盖了先前初始化时调用 string 默认构造函数的结果。包含在默认 string 
构造函数中的计算结果完全被扔掉了。

'许多优化需要某种折中。大家经常拿速度换取清晰度、简洁性、重用性或其他的衡量指标'。

然而在本例中，优化根本不需要任何牺牲。可以重写 Person 的构造函数，在不牺牲任何质量的情况下找回失去的速度。你可以通过指定 string 成员 name 的显式初始化来实现这
一点。

Person::Person(const char *s):name(s)// 版本 1
{
    ...
}

这个构造函数将产生完全相同的 Person 对象，唯一的改变是改善了性能。我们所做的仅仅是对 string::string(const char＊)  进行唯一一次调用，使用 s 初始化 name。
通过对以下循环计时，我们对性能差别进行了测试:

for(int i = 0; i < 1000000, i ++)
{
    Person p("nio");
}

幸好，默认的 string 构造函数开销是非常小的，使得这种低效几乎可以忽略不记。但您不会总碰到这样的好事，因此不要指望它。

假设由于某种原因您绕过了标准的 string 的实现，而编写了自己的实现。我们把它称作 SuperString：

#ifndef SUPERSTRING_H_
#define SUPERSTRING_H_

class SuperString {
 public:
  SuperString(const char* s = 0);
  SuperString(const SuperString& s);
  SuperString& operator=(const SuperString& s);

  ~SuperString() { delete[] str; }

 private:
  char* str;
};

inline SuperString::SuperString(const char *s):str(s)
{
    if(s != 0)
    {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }
}

inline SuperString::SuperString(const string &s):str(0)
{
    if(s.str)
    {
        str = new char[strlen(s.str) + 1];
        strcpy(str, s.str);
    }
}

SuperString& SuperString::operator=(const SuperString &s)
{
    if(str != s.str)
    {
        delete[] str;
        str =  new char[strlen(s.str) + 1];
        strcpy(str, s.str);

    }
    else
    {
        str = 0;
    }
    return *this;
}

#endif  // SUPERSTRING_H_


不仅如此，您还已经决定在 Person 的实现中使用 SuperString 替换 string 成员:

class Person
{
public:
    Person(const char *s)// 版本2
    {
        name = s;
    }
private:
    SuperString name;
};


由于您没有提供接收 char 型指针参数的 SuperString 赋值操作符，所以赋值操作符需要用 SuperString 对象的引用作为参数。因此，Person 构造函数中的
语句:

name = s;

会触发创建一个临时 SuperString 对象。编译器会调用相应的 SuperString 构造函数把 char 型指针 s 转换为 SuperString 类型。利用伪代码，我们将 
Person::Person(char＊)实现的转换表示为如下形式:

Person::Person(const char *s)
{
    name.SuperString::SuperString();
    SuperString _temp;
    _temp.SuperString::SuperString(s);
    name.SuperString::operator=(_temp);
    _temp.SuperString::~SuperString();
}

通过调用  SuperString 赋值操作符，临时 SuperString 对象（temp）的内容被赋予成员 name。随后调用 SuperString 的析构函数清除该临时对象。

我们总共有两次对 SuperString  构造函数的调用，其中一个调用对应于赋值操作符，另一个调用对应于析构函数。这种实现对性能造成了十分严重的损害。

版本 3 通过显式初始化 SuperString 成员解决了这个问题：

Person::Person(const char *s):name(s)// 版本 3
{

}

版本 2 中在构造函数部分同时使用隐式初始化和显式赋值。版本 3 中使用显式初始化但没有赋值操作。在我们自己编写 SuperString 的情况下，版本 3 要快 2 倍多。如果提
供了一个接收 char 型指针参数的赋值操作符的话，性能损失将不会那么严重。那样就彻底不需要临时 SuperString 对象了。有趣的是，版本 3 要稍快于使用编译器实现的
string 版本（版本1）。我们自己编写的 SuperString 不提供像 string 类那么丰富的功能。

'通常情况下，如果代码不必提供太多灵活性的话，那么代码就会运行得更快'。

// !!  要点

● 构造函数和析构函数可以像手工编写的 C 代码一样有效。然而在实践中，它们经常包含冗余计算

● 对象的创建(或销毁)触发对父对象和成员对象的递归创建(或销毁)。要当心复杂层次中对象的复合使用。它们使得创建和销毁的开销更为高昂

● 要确保所编写的代码实际使用了所有创建的对象和这些对象所执行的计算。'我们鼓励程序员深入研究他们所使用的类'。这个建议不会受到面向对象程序设计提倡者的欢迎，
  毕竟面向对象的程序设计劝诫将类作为黑盒使用，不鼓励人们窥探其内部结构。怎样平衡这两条相互对立的建议呢？ 这个问题没有简单的答案，因为它与所处的环境有关。尽
  管黑盒方法对于 80% 的代码都能表现得十分完美，但它却可能对另外 20% 性能要求苛刻的代码造成很大的伤害。它也是与应用程序相关的。'有的应用程序注重可维护性和灵活
  性，而另一些应用程序则可能把对性能的考虑放在最为重要的位置'。
  '作为程序员，应当清楚自己到底更看重哪个方面'。

● 对象的生命周期不是无偿的。'至少对象的创建和销毁会消耗 CPU 周期'。不要随意创建一个对象，除非你打算使用它。'通常情况下，要等到需要使用对象的地方再创建它'。

● '编译器必须初始化被包含的成员对象之后再执行构造函数体'。您必须在初始化阶段完成成员对象的创建。这可以降低随后在构造函数部分调用赋值操作符的开销。在某些情况下
  ，这样也可以避免临时对象的产生。

