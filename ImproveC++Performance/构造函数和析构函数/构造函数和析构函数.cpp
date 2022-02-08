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




