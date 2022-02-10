
// !! 虚函数

随着程序语言的发展，编译器、解释器、汇编器以及链接器承担了程序员的部分职责，使编程任务得以简化。程序变得更加易于开发、维护以及扩展。但问题也随之而来，'技术发展的
实质往往是一个有得必有失的零和博弈'。

值得一提的是, 编程上的改进常常会降低程序运行的速度。例如，C++ 对 C 的贡献之一是函数调用的动态绑定，C++ 把类型解析的任务转交给编译器实现，从而减轻了程序员的负
担，这是它的优点。但另一方面，它也带来负面作用，即开销过高。

// !! 虚函数的构造

'如果确实想避免使用虚函数，可以自己编写类型解析代码来达到动态绑定的目的'。

假如我们正在维护一个动物园动物的类层次，其中 ZooAnimal 是基类:

class ZooAnimal
{
public:
    ...
    virtual void draw();
    int resolveType() {return myType;}
private:
    int myType;
    ...
};

动物园的其他动物类派生自类 ZooAnimal。 resolveType() 方法可以在程序运行期间区分熊(Bear)和猴子(Monkey)。

class Bear: public ZooAnimal
{
public:
    Bear(const char *name):myName(name),myType(BEAR){ }
    void draw() override;
    ...
};

每一个动物类都在其构造函数中设置它的相应种类。

如果我们要描绘动物园的所有动物，可以用如下的代码行来实现。

void drawAllAnimal(ZooAnimal *pz)// 指向列表中第一个动物的指针
{
    for(ZooAnimal *p = pz; p; p = p->next)
    {
        switch(p->resolveType())
        {
            case BEAR:
                ((Bear *)p)->draw();
                break;
            case MONKEY:
                ((Monkey *)p)->draw();
                break;
            default
                break;
        }
    }
}

维护这段代码令人头疼，因为无论何时，只要有一只动物离开动物园，就必须将它移出 switch 语句；同样，只要新来一只动物，又需要将它添加到 switch 语句中。

'虚函数的动态绑定技术可以使代码从这种依赖关系中解脱出来'。

因为 ZooAnimal::draw() 是一个虚函数，我们可以在运行期间利用动态绑定。

void drawAllAnimal(ZooAnimal *pz)
{
    for(ZooAnimal *p = pz; p; p = p->next)
    {
        p->draw();
    }
}

这段代码仍然可以区分熊和猴子，它是如何办到的呢？

为方便后期绑定，我们必须有一种机制在运行期间而不是编译期间来解析虚函数调用。如果 X 类定义了虚函数或者它本身派生于这样的类，编译器就会为 X 类创建一张虚函数表
(vtbl)。'虚函数表存储了为该特定类定义的所有虚函数指针'。每个类对应一张虚函数表，类的每个对象都有指向该表的隐藏指针---因为只有编译器知道 vptr 在对象中的偏移
量。'编译器通过在对象的构造函数中插入代码来正确地初始化 vptr'。

● 构造函数必须初始化 vptr

● 虚函数是通过指针间接调用的，所以必须先得到指向虚函数表的指针，然后再获得正确的函数偏移量

● 内联是在编译时决定的。编译器不可能把运行时才解析的虚函数设置为内联

客观地看待 C++，前两项并不能算是性能损失。不管怎样，即使我们竭尽全力避免使用动态绑定，也必须为这两条付出代价。在构造函数中设置 vptr 的代价与在 Bear 的实现中
初始化成员变量的代价相当。

Bear(const char *name):myName(name),myType(BEAR){ }

第二项即间接调用函数的代价，它与必须在逻辑上区分 Bear::draw() 和 Monkey::draw() 的 switch 语句的代价相当。

那么虚函数的真正代价只剩第三项。'无法内联虚函数造成的性能损失最大'。

'由于在编译期间不能确定所调用的函数所属的对象类型，所以大多数虚函数调用都是在运行期间解析的'。编译期间无法解析对内联造成了负面影响。由于内联是在编译期间确定的，
所以它需要具体函数的信息，但如果在编译期间不能确定将调用哪个函数(例如虚函数这种典型的情况)，就无法使用内联。

评估虚函数的性能损失就是评估无法内联该函数所造成的损失。这种损失的代价并不固定，它取决于函数的复杂程度和调用频率。一种极端情况是频繁调用的简单函数，它们是内联的
最大受益者，若无法内联则会造成重大性能损失。另一极端情况是很少调用的复杂函数。

如果特定的虚函数产生了性能问题，我们该怎么办呢？

为了消除虚函数调用，必须允许编译器在编译期间就解析函数的绑定。通过对类选择进行硬编码或者将它作为模板参数来传递，可以避免使用动态绑定。

下面我们将通过具体的实例来讨论这些方法。

// !! 模板和继承

'只能在运行期间解析的虚函数调用是不允许使用内联的'。这往往会造成性能问题，该问题我们必须解决。因为函数调用的动态绑定是继承的结果，所以消除动态绑定的一种方法
是用基于模板的设计来替代继承。

'模板把解析的步骤从运行期间提前到编译期间，从这个意义上说，模板提高了性能'。而对于我们所关心的编译时间，适当增加也是可以接受的。

继承和模板的设计空间有些重叠，我们将讨论这样一个例子。

假设我们要开发一个线程安全的 string 类，它可以在 Win32 环境下被并发线程安全地使用。在该环境下, 有多种同步策略可供选择，比如临界区、互斥和信号等，这里我们只
列出一些。'为便于使用上述任意一种策略，我们希望 string 类能够提供一定的灵活性，使我们在不同场景下可以选择某一种策略而放弃另一种'。继承是一种满足同步机制
共性的合理选择。

Locker 抽象基类将声明公共接口:

class Locker
{
public:
    Locker();
    virtual ~Locker();
    virtual void lock() = 0;
    virtual void unlock() = 0;
};

CriticalSectionLock 和 MutexLock 将从基类 Locker 派生出来。

class CriticalSectionLock: public Locker {...}
class MutexLock : public Locker  {...}

因为我们不想重新设计，所以选择从现有的标准 string 类派生出线程安全的 string 类。余下的设计选项是:

● 硬编码 可以从 string 类中派生出三个独立类：CriticalSectionString、MutexString 和 SemaphoreString。每个类实现各自名字所代表的同步机制

● 继承 可以派生出一个单独的 ThreadSafeString 类，它包含指向 Locker 对象的指针。在运行期间通过多态机制选择特定的同步机制

● 模板 基于模板的 string 类，该类由 Locker 类型参数化后得到


// !! 硬编码

标准的 string 类被用做基类。'每个由它派生的类实现某一特定的同步机制'。例如 CriticalSectionString

class CriticalSectionString : public string
{
public:
    ...
    int  length();

private:
    CriticalSectionLock cs;
};

int  CriticalSectionString::length()
{
    cs.lock();
    int len = string.length();
    cs.unlock();
    return len;
}

虽然从父类 string 中得到了字符串的实际长度，但是我们将这步操作放在临界区内以保证计算的完整性。

这种设计在性能上具有优势。尽管 lock() 和 unlock() 方法是虚函数，但是它们可以被适当的编译器静态地解析。这三个线程安全的 string 类都在编译期间指定了特定的同
步类。因此，编译器可以绕过动态绑定来选择正确的 lock() 和 unlock() 方法。更重要的是，这种设计允许编译器内联这两个方法。但是，该设计的不足之处在于需要为每种同
步机制编写各自的 string 类，导致代码重用性较低。


// !! 继承

为每种同步机制都实现单独的 string 类是件痛苦的事情。'另一种方法是把所选择的同步机制作为构造函数的参数':

using std::string;

class ThreadSafeString : public string 
{
public:
    ThreadSafeString(const char* s, Locker *lockPtr):string(s), pLock(lockPtr){}
    ...
    int length();

private:
    Locker *pLock;
}


int ThreadSafeString::length()
{
    pLock->lock();
    int len = string::length();
    pLock->unlock();
    return len;
}

这个类根据传递给构造函数的 Locker 指针使用所有可用的同步策略。它可以按下面的方式使用临界区：

{
    CriticalSectionLock cs;
    ThreadSafeString("Hello",&cs);
    ...
}

这种实现比前一种简洁得多。但是它确实带来了性能的损失：虚函数调用 lock() 和 unlock() 仅在执行期间解析，因此不能对它们内联。


// !! 模板

基于模板的设计结合了两方面的优点：重用和效率。ThreadSafeString 是作为模板实现的，它的参数由 Locker 模板参数决定。

template <typename LOCKER>
class ThreadSafeString : public string
{
public:
    ThreadSafeString(const char *s):string(s){}
    ...
    int length();
private:
    LOCKER lock;
};

length 方法的实现与前一种类似:

template<typename LOCKER>
inline int ThreadSafeString::length()
{
    lock.lock();
    int  len = string::length();
    lock.unlock();
    return len;
}

如果我们想使用临界区保护策略，可以用 CriticalSectionLock 来实例化模板：

{
    ThreadSafeString<CriticalSectionLock> cstring = "Hello";
}

这种设计也避免了对 lock 和 unlock 的虚函数调用。'ThreadSafeString 声明在实例化模板时选择特定的同步类型'。如同硬编码一样，它使编译器可以解析这两个虚函数调
用并且内联它们。

正如您所看到的，'模板把计算从执行期间提前到编译期间来做，并且在编译时使用内联，因此提高了性能'。

// !! 要点

● 虚函数的代价在于无法内联函数调用，因为这些调用是在运行时动态绑定的。唯一潜在的效率问题是从内联获得的速度（如果可以内联的话）。但对于那些代价并非取决于调用和返
  回开销的函数来说，内联效率不是问题

● 模板比继承提供更好的性能。它把对类型的解析提前到编译期间，我们认为这是没有成本的

