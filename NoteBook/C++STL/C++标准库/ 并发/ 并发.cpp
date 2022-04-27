// !! 并发

现代化体系结构 (modern system architecture) 通常支持同时执行多个任务(task)和多个线程(thread)。特别是如果采用多处理器内核(multiple processor core),
那么程序执行时间可在多线程情况下获得大幅改善。

然而, 并行(in parallel)处理也带来了新挑战:不再是完成一个语句后进行另一语句, 而是'多语句同时执行, 于是可能导致并发访问(concurrently accessing)同一资源,
造成创建、读取、涂写、删除等动作不在预期次序下发生，形成不可预测的结果'。事实上多线程并发访问数据很容易变成噩梦，带来诸如死锁之类的问题，而"线程之间彼此等待"只
能算是最单纯的一种情况。

在 C++11 之前,不论语言或标准库,对并发处理没有任何支持,纵使实现(implementation) 可自由给予若干承诺。 随着 C++11 到来, 这种情况有了改变, 不论语言自身或标
准库都得到强化, 可支持并发编程(concurrent programming):

1. 语言核心定义了一个内存模型,保证当你更改"被两个不同线程使用"的两个 object 时, 它们彼此独立, 并引入了一个新关键字 thread_local 用以定义"变量带有 thread
  专属值"

2. 标准库提供的支持允许你启动多线程, 包括得以传递实参、返回数值、跨线程边界传递异常、同步化(synchronize)等, 使我们能够对"控制流程"和"数据访问"实现同步化


标准库在不同的层面分别提供支持, 它提供一个高级接口, 允许你启动线程,包括传递实参、处理结果和异常, 而那是架构在若干与之对应的低层接口上。换句话说, 标准库也提供
一组低层接口, 像是 mutex 或 atomic, 用来对付放宽的内存次序(relaxed memory order, RMO)。


本章组织如下:

1. 首先介绍各式各样的多线程启动办法。介绍了高级和低层接口后, 开始介绍启动线程的细节

2. 对于同步化线程(synchronizing thread)所引发的问题提供了一份详细讨论。最主要的问题就是数据的并发访问(concurrent data access)

3. 最后, 探讨用以"同步化线程"和"并发数据访问"的各种特性:

   mutex 和 lock (互斥体和锁), 包括 call_once() 

   condition variable (条件变量)

   Atomic



// !! 高级接口: async() 和 Future


对初学者而言, "以多线程运行程序" 的最佳起点就是 C++ 标准库中由 std::async() 和 class std::future<> 提供的高级接口:

1. async() 提供一个接口, 让一段机能(a piece of functionality)或说一个 callable object 若是可能的话在后台运行,成为一个独立线程。

2. class future<> 允许你等待线程结束并获取其结果(一个返回值，或者也许是一个异常)


// !! async() 和 Future 的第一个用例

假设我们需要计算两个操作数的总和,而这两个操作数是两个函数的返回值。寻常做法如下:

func1() + func2();

这意味着对操作数的处理是循序发生的。程序首先调用  func1() 然后调用 func2(), 或是颠倒过来(根据语言规则,这一次序无法预期)。不论哪种情况, 整体处理时间是
func1() 所花时间加上 func2() 所花时间, 再加上计算总和所花的时间。

近年来, 使用多处理器(multiprocessor)的硬件几乎处处可见, 我们因此可以将上述计算做得更好, 可以尝试并行运行 func1() 和 func2(), 使其整体运行时间只需是
"func1() 和 func2() 运行时间中的较大者"加上计算总和的时间。


下面是第一个示范程序:

#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <random>
#include <thread>

using namespace std;

int doSomething(char c) {
  std::default_random_engine dre(c);
  std::uniform_int_distribution<int> id(10, 1000);

  for (int i = 0; i < 10; i++) {
        this_thread::sleep_for(std::chrono::microseconds(id(dre)));
        cout.put(c).flush();
  }
  return c;
}

int func1() { return doSomething('.'); }

int func2() { return doSomething('+'); }

int main(int argc, char** argv) {
  std::cout << "starting func1() at background and func2() in foreground: "
            << std::endl;

  // start func1() async(now or later)
  std::future<int> result1(std::async(func1));

  int result2 = func2();  // call func2() sync(here and now)

  // print result(wait func1 to finish) add add it result to result2
  int result = result1.get() + result2;

  std::cout << "result1 + result2 is " << result << std::endl;

  return 0;
}

为了让事情视觉化, 我将 func1() 和 func2() 内的繁复处理简化为对 doSomething() 的调用, 它不时打印一个被当作实参传递进去的字符, 并最终返回该字符的 int 值。
所谓"不时"是借由一个"随机数生成器"(用以指定时间间隔)实现, 其中 std::this_thread::sleep_for() 作为当前线程的暂停时间。注意, 我们需要一个独一无二的
seed(种子)交给"随机数生成器"构造函数, 此处采用被传入的字符 c, 确保产生出不同的随机数序列。

现在, 不再这么调用:

int result = func1() + func2();


改而这么调用:

std::future<int> result1(std::async(func1));
int result = func2();

int result = result1.get() + result2;

首先使用 std::async() 尝试启动 func1() 于后台, 并将结果赋值给某个 std::future object:

std::future<int> result2(std::async(func1));

在这里, async() 尝试将其所获得的函数立刻异步启动于一个分离线程内。因此概念上 func1() 在这里被启动了, 不会造成 main() 停滞。基于两个原因, 返回
future object 是必要的:

1. 它允许你取得传给 async() 的那个函数的未来结果--也许是个返回值, 也许是个异常。这个 future object 已受到"被启动函数"返回类型的特化,如果被启动的是个返
   回"无物"的后台任务(background task), 这就会是 std::future<void>


2. 它必须存在, 确保"目标函数"或快或慢终会被调用。注意先前我说 async() 尝试启动目标函数。如果这样的事情没发生, 稍后我们需要这个 future object 才能强迫启
   动之(当我们需要函数的运行结果或当我们想要确保该函数被执行时)

因此, 即使你对启动于后台的那个函数的结果不感兴趣，还是需要握有这个 future object

为了能够在"启动及控制函数"处与"返回之 future object" 之间交换数据, 二者都指向一个所谓的 shared state。


当然, 你可以(并且通常会) 使用 auto 来声明 future object:

auto result1(std::async(func1));


接下来我们启动 func2() 于前台(foreground), 这是个正常的同步化调用, 于是程序在此停滞:

int result2 = func2();

如果先前 func1() 成功地被 async() 启动且尚未结束, 现在 func1() 和 func2() 就是并行运作。

接下来处理总和。这就是需要 func1() 成果的时刻。为了获得它, 我们对先前返回的 future object 调用 get():


int result = result1.get() + result2;

随着 get() 被调用, 以下三件事情之一会发生:

1. 如果 func1() 被 async() 启动于一个分离线程中并且已结束, 你会立刻获得其结果

2. 如果 func1() 被启动但尚未结束, get() 会引发停滞(block) 待 func1() 结束后获得结果

3. 如果 func1() 尚未启动, 会被强迫启动如同一个同步调用; get() 会引发停滞直至产生结果


这样的行为很重要, 因为这确保了在单线程环境中, 或是当 async() 无法启动新线程时(不论基于任何理由), 程序仍能有效运作。

调用 async() 并不保证传入的函数一定会被启动和结束。如果有个线程处于可用状态, 那么它的确会被启动, 但如果不是这样(也许你的环境不支持多线程, 或者也许当时无线程
可用), 这一调用会被推迟至你明确说你需要其结果(也就是当调用 get())或只是希望目标函数完成其任务(也就是调用 wait())。

因此:

std::future<int> result1(std::async(func1));

和

result1.get();

的组合允许你以某种方式优化程序:

1. 如果可能,当 main 线程的下一个语句被处理时 func1() 被并行运行

2. 如果无法并行运行, 那么 func1() 会在 get() 被调用时被循序调用(called sequentially

这就意味着无论如何都能保证至少在 get() 执行后一定会调用 func1()---不是异步就是同步

注意, 如果没调用 get() 就不保证 func1() 一定会被调用。一如我所说, 如果 async() 无法立刻启动它所收到的函数, 就会推迟调用, 使得当程序"调用 get() 意欲明确
索求目标函数的结果"(或是调用 wait()) 才被调用。如果没有那样一个明确请求, 即使 main() 终止造成程序结束, 也不会唤醒后台线程。


也请注意, 你必须确保只在最必要时才索取"被 async() 启动"的那个函数的执行结果。

例如以下优化或许不是你要的:

std::future<int> result1(std::async(func1));
int result = result2 + result1.get();

由于上述第二个语句右侧的核算顺序不明确, result1.get() 有可能在 func2() 之前被调用, 于是你又一次获得了循序式处理(sequential processing)。


为了获得最佳效果，一般而言你的目标应该将调用 async() 和调用 get() 之间的距离最大化,即'早调用而晚返回(Call early and return late)'。

如果传给 async() 的函数不返回任何东西, async() 会产出一个 future<void>, 那是 future<> 的一个偏特化版, 这种情况下 get() 返回"无物":

std::future<void> result1(std::async(func1));
...

result1.get();

最后请注意, 传给 async() 的东西可以是任何类型的 callable object: 可以是函数、成员函数、函数对象(function object)或 lambda。你可采用 inline 
形式将"应该在专属线程中运行"的函数写成一个 lambda 并传递:

std::async([](){...});



// !! Launch (发射)策略

你也可以强迫 async() 绝不推延目标函数的执行, 只要明确传入一个 launch 策略用以指挥 async(), 告诉它当它被调用时应明确地以异步方式启动目标函数:

std::future<int> result1(std::async(std::launch::async, func1));

如果异步调用在此处无法实现, 程序会抛出一个 std::system_error 异常, 并带差错码 resource_unavailable_try_again, 它相当于 POSIX 的 errno EAGAIN。

有了这个 async 发射策略, 就不必非得调用 get() 了, 因为如果返回的 future 生命即将结束, 这个程序必会等待 func1() 结束。因此, 如果你不调用 get(), 当离开
future object 作用域时(此处是指 main() 结束), 程序会等待后台任务(background task)结束。尽管如此, 程序结束前调用 get() 会让行为更加清晰。

如果你不将 std::async(std::launch::async, ...) 的结果赋值出去, 调用者会在此停滞(block)到目标函数结束, 那就相当于一个完完全全的同步调用(synchronous 
call)。


与此类似, 你可以强制延缓执行(deferred execution) 以 std::launch::deferred 为发射策略传给 async()。下面的做法允许你延缓 func1() 直到你对 f 调用
get():

std::future<int> result1(std::async(std::launch::deferred, func1));

这保证 func1() 绝不会在没有 get() (或 wait()) 的情况下启动。

这个策略的特别在于允许你写出 lazy evaluation (缓式求值)。例如:

auto f1 = std::async(std::launch::deferred, task1);
auto f2 = std::async(std::launch::deferred, task2);
...

auto val = thisOrThat ? task1.get() : task2.get();



// !! 处理异常


目前已讨论的是线程和后台任务 (background task) 成功执行的情况。然而万一出现异常将如何 ?

好消息是:没有什么特别事情会发生; "对 future 调用 get()" 也能处理异常。事实上当 get() 被调用, 且后台操作已经(或随后由于异常) 而终止, 该异常不会在此线程
内被处理, 而是会再次被传播出去。因此, 欲处理后台操作所生的异常, 你只需要偕同 get() 做出"以同步方式调用该操作"所做的相同动作即可。

#include <future>
#include <list>
#include <iostream>
#include <exception>

using namespace std;

void task1(){

    list<int> v;
    while(1){
        for(int i=0; i< 1000000; ++i){
            v.push_back(i);
        }
        cout.put('.').flush();
    }
}

int main(int argc, char** argv){

    cout << "Starting 2 task" << endl;
    cout << "-task1: process endless loop of memory consumption" << endl;
    cout << "-task2: wait for  return and the for task1" << endl;

    auto f1 =  std::async(task1);

    cin.get();

    cout << "wait for the end of task1" << endl;
    try{
        f1.get();

    }catch(const std::exception& e){
        cout << "Exception: " << e.what() << endl;
    }    
}

这个无限循环迟早会出现异常(也许是个 bad_alloc), 该异常会终止线程, 因为它未被捕获。Future object 会保持这一状态直到 get() 被调用。搭配 get() 后这个异常
在 main() 内被进一步传播。

'现在总结 async() 接口和 future 如下':
 
 async() 提供一种编程环境, 让我们有机会并行启动某些"稍后(当 get() 被调用时) 才会用到其结果"的动作。换句话说, 如果你有某个独立机能（函数） f, 你有可能受
 益于并行机制(parallelization), 做法是在你需要调用 f 时改而把 f 传给 async(), 然后在你需要 f 的结果时改为"对 async() 返回的 future 调用 get()"。
 于是, 你拥有相同的行为, 但是有机会获得较佳效率, 因为 f 有可能并行运行--在 f 的执行结果被索取之前。


// !! 等待和轮询 (Waiting and Polling)

一个 future<> 只能被调用 get() 一次。在那之后 future 就处于无效状态, 而这种状态只能借由"对 future 调用 valid()" 来检测。此情况下对它的任何调用
(析构除外) 会导致不可预期的行为。


但是 future 也提供一个接口, 允许我们等待后台操作完成而不需要处理其结果。这个接口可被调用一次以上; 也可以结合一个 duration(时间段)或 timepoint(时间点)
以限制等待时间。

只要对某个 future 调用  wait(), 就可以强制启动该future象征的线程并等待这一后台操作终止:

std::future<int> f(std::async(func1));
...
f.wait();// wait for func1 be done


另外还有两个类似函数, 但它们并不强制启动线程(如果线程尚未启动的话):

1. 使用 wait_for() 并给予一个时间段, 就可让"异步、运行中"的操作等待一段有限时间

std::future<int> f(std::async(func1));
...
f.wait_for(std::chrono::seconds(10));// wait for at most 10 seconds for func1


1.使用 wait_for() 并给予一个时间段, 就可让"异步、运行中"的操作等待一段有限时间

std::future<int> f(std::async(func1));
...

f.wait_until(std::system_clock::now() + std::chrono::seconds(1));

不论 wait_for() 或 wait_until() 都返回以下三种东西之一:

1. std::future_status::deferred--如果 async() 延缓了操作而程序中又完全没有调用 wait() 或 get() (那会强制启动), 这种情况下上述两个函数都会立刻返回

2. std::future_status::timeout---如果某个操作被异步启动但尚未结束, 而 waiting 又已逾期(对于给定的时间段而言)

3. std::future_status::ready -- 如果操作已完成

wait_for() 或 wait_until() 特别让我们得以写出所谓的 speculative execution(投机性运行)。


举个例子, 考虑这样的情景: 我们必须在某个时间段内获得某一运算之尚堪可用的结果(usable result), 而如果有精确结果(accurate answer)更好。


int quickComputation();
int accurateComputation();
std::future<int> f;

int bestResultInTime(){

    auto tp = std::chrono::system_clock::now() + std::chrono::minutes(1);
    f = std::async(std::launch::async, accurateComputation);

    int guess = quickComputation();

    std::future_status s = f.wait_for(tp);

    if(s == std::future_status::ready){
        return f.get();
    }else{
        return guess;
    }
}

注意 future f 不能是声明于 bestResultInTime() 内的 local 对象, 那样的话若时间太短以至于无法完成 accurateComputation(),future 析构函数会停滞
(block)直到异步操作结束。

如果传入一个 zero 时间段, 或一个过去时间点, 就可以仅轮询(poll) 是否有个后台任务已被启动，或是否它正在运行中:

future<...> f(async(func));

while(f.wait_for(std::chrono::seconds(0) != std::chrono::future_status::ready)){
    ...
}

然而请注意, 如此循环有可能不会结束,在单线程环境中, 这一调用将被推迟直至 get() 被调用。



// !! 实例：等待两个Task

#include <future>
#include <thread>
#include <chrono>
#include <iostream>
#include <random>
#include <exception>

using namespace std;


void doSomething(char c){
    default_random_engine dre(c);
    uniform_int_distribution<int> id(10, 1000);
    for(int i=0; i < 1000; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
        cou.put(c).flush();
    }
}

int main(int argc, char** argv){

    cout << "Starting 2 operation async " << endl;
    auto f1 = std::async([](){doSomething('.');});
    auto f2 = std::async([](){doSomething('+')});
    // if at least one of background task is running
    if(f1.wait_for(std::chrono::seconds(0) != std::future_status::deferred || 
       f2.wait_for(std::chrono::seconds(0) != std::future_status::deferred))){

           while(f1.wait_for(std::chrono::seconds(0) != std::future_status::ready && 
                 f2.wait_for(std::chrono::seconds(0) != std::future_status::ready))){
                     ...
                     this_thread.yield();
                 }
       }
       cout.put('\n').flush();

       try {
           f1.get();
           f2.get();
       }catch(const std::exception& e){
           cout << e.what() << endl;
       }

       cout << "done" << endl;

    return 0;
}

再一次, 我们有个操作函数 doSomething() 不时打印一个被传为实参的字符。

现在, 借由 async(), 我们在后台启动 doSomething() 两次, 打印两种不同字符, 使用不同的延迟时间, 后者由相应的随机数序列(random-number sequence)产生:


auto f1 = std::async([]() {doSomething('.');});
auto f2 = std::async([]() {doSomething('+');});

在多线程环境中, 此时将同时运行起两个操作, 不定时打印出不同的字符。

接下来, 轮询(poll)是否其中一个操作已完成:


while (f1.wait_for(std::chrono::seconds(0) != std::future_status::ready)
        f2.wait_for(std::chrono::seconds(0) != std::future_status::ready)){
            ...
            this_thread.yield();
        }

然而万一 async() 被调用时上述两个 task 都未被在后台启动, 这个循环将永远不会结束, 所以我们首先必须检查是否至少有一个操作未被推迟 (not deferred):


if(f1.wait_for(std::chrono::seconds(0) != std::future_status::deferred
   f2.wait_for(std::chrono::seconds(0)) != std::future_status::deferred)){


   }


事实上，如果你移除 sleep_for()语句(它会在每次打印字符时强制推迟), 第一循环会在首次 context switch (切换至其他线程)前全部做完，那么程序的输出比较可能
像下面这样:

Starting 2 operation async
...........
+++++++++++
done

如果环境不支持多线程, 这份输出还是会出现, 因为这种情况下对 doSomething() 的两次调用将会借由对 get() 的调用而被同步调用。


// !! 传递实参 (Passing Argument)

前一个例子示范了"传递实参给后台任务"的一种做法: 使用一个 lambda 并让它调用后台函数:

auto f1 = std::async([](){doSomething('.');});

当然, 也可以传递"在 async() 语句之前就已存在"的实参。一如以往, 可采用 by value 方式或 by reference 方式传递它们:

char c = '@';
auto f2 = std::async([=](){doSomething(c);});

由于定义 capture 为 [=], 因此传递给 lambda 的是 c 的拷贝(copy) 及所有其他 visible object, 所以在 lambda 内你可以传递那个 c 拷贝给 doSomething()。


然而另有其他办法可以传递实参给 async(),  因为 async() 提供了 callable object 的惯常接口。举个例子m 如果你传递 function pointer 作为第一实参给
async(), 你可以传递更多实参, 它们将成为被调用的那个函数的参数:

char c = '@';
auto f = std::async(doSomething, c);

也可以采用 by reference 方式传递实参, 但这么做的风险是, 被传递值甚至可能在后台任务启动前就变得无效。这对于 lambda 及"直接被调用的函数"都适用:

char c = '@';
auto f1 = std::async([&](){doSomething(c);});
auto f2 = std::async(doSomething, std::ref(c));

但是, 当心, 如果你"以 by reference 方式传递实参"只是为了可在另一个线程中改动它们, 你可能轻易落入不明确行为(undefined behavior) 之中。

考虑下面的例子, 在试图启动一个输出循环(于后台打印一个字符)后, 你改变该字符:

void doSomething(const char& c);
...
char c = '@';
auto f = std::async([&](){doSomething(c);});// pass by reference
...
c = '_';
f.get();


首先,"这里"以及"在 doSomething() 内"对 c 的处理, 其次序无法预期。因此, 该字符的变换可能发生于输出循环之前、之中或之后。更糟的是,'我们在某一线程中改动 
c, 在另一个线程中读取 c, 这是对同一对象的异步并发处理(所谓 data race)', 将导致不可预期的行为, 除非你使用 mutex(互斥体) 或 atomic 保护并发处理动作。

所以, 让我们说清楚: 如果你使用 async(), 就应该以 by value 方式传递所有"用来处理目标函数"的必要 object, 使 async() 只需使用局部拷贝(local copy)。
如果复制成本太高, 请让那些 object 以 const reference 的形式传递, 且不使用 mutable。


你也可以传给 async() 一个"指向成员函数"的 pointer。这种情况下, 位于该成员函数名称之后的第一个实参必须是个 reference 或 pointer, 指向某个 object,
后者将调用该成员函数:

class X{
public:
    void mem(int num);
    ...
};

X x;
auto a = std::async(&X::mem,x,42);// try to call x.mem(42) async



// !! Shared Future

正如我们已看到的, class std::future 提供了"处理并发运算之未来结果"的能力。然而你只能处理该结果一次。第二次调用 get() 会导致不可预期的行为
(根据 C++ 标准库的说法, 通常是鼓励抛出一个 std::future_error)。


然而有时候, 多次处理"并发运算之未来结果"是合理的, 特别当多个其他线程都想处理这份结果时。基于这个目的, C++ 标准库提供了 class std::shared_future, 于是你可
以多次调用 get(), 导致相同结果, 或导致抛出同一个异常。

考虑下面这个例子:

#include <future>
#include <thread>
#include <iostream>
#include <stdexcept>

using namespace std;

int querrNumber(){
    cout << "Read number: ";
    int num;
    cin >> num;

    if(!cin){
        throw std::runtime_error("no number read");
    }
    return num;
}

void doSomething(char c, shared_future<int> f){

    try{
        f.get();// get result of queryNumber

        for(int i = 0; i < num; i++){
            this_thread::sleep_for(std::chrono::milliseconds(100));
            cout.put(c).flush();
        }
    }catch(const std::exception& e){
        cout << e.what() << endl;
    }
}

int main(int argc, char** argv){

    try{
        shared_future<int> f = std::async(queryNumber);

        auto f1 = std::async(std::launch::async, doSomething, '.', f);
        auto f2 = std::async(std::launch::async, doSomething, '+', f);
        auto f3 = std::async(std::launch::async, doSomething, '-', f);

        f1.get();
        f2.get();
        f3.get();
    }catch(const std::exception& e){
        cout << e.what() << endl;
    }

    cout << "done" << endl;
    return 0;
}

此例之中有个线程调用 queryNumber() 查询一个整数值, 该值随后被其他已执行的多个线程使用。为执行这份任务, 用以启动"查询线程"的那个 std::async() 的执行结果被
赋值给一个 shared_future object, 后者以返回值为 template 参数:


shared_future<int> f = std::async(queryNumber);

也就是说, shared future 可以寻常的 future 为初值, 于是 future 的状态会被搬移到 shared future 身上。为了能在上述声明式中使用 auto, 你可以改而调用成员函
数 share():

auto f = std::async(queryNumber).share();

就内部而言, '所有 shared future object 共享所谓 shared state, 后者由 async() 建立,用来存放目标函数的运行结果(也存放函数本身——如果它被推迟执行的话)'。

这个 shared future 随后被传给其他线程, 它们启动 doSomething() 并以该 shared future 作为第二实参:

auto f1 = std::async(std::launch::async, doSomething, '.', f);
auto f2 = std::async(std::launch::async, doSomething, '+', f);
auto f3 = std::async(std::launch::async, doSomething, '-', f);

每一次 doSomething() 被调用, 便通过传入之第二参数 shared future 的成员函数 get(), 等待及处理 queryNumber() 的执行结果:

void doSomething(char c, shared_future<int> f){
    try{
        int num = f.get();
        for(int i = 0; i < num; i++){
            ...
        }
    }catch(...){
        ...
    }
}


如果 queryNumber() 抛出异常(当程序未能读到整数时), 那么对 doSomething() 的每一次调用都会获得因 f.get() 而来的异常, 于是对应的异常处理
(exception handling) 便会发生。


一位并发库(concurrency library)作者——在某次私下联络中所言:"如果代码紧紧保持着高度协调, 以 by reference 方式传递是好的。但如果代码进入一个对于目标和限制
都不甚了解的地带, 那么还是以 by value 方式传递较佳"。


// !! 低层接口: Thread 和 Promise

'除了高级接口 async() 和 (shared) future, C++ 标准库还提供了一个启动及处理线程的低层接口'。


// !! Class std::thread

欲启动某个线程, 只需先声明一个 class std::thread 对象, 并将目标任务(task)当作初始实参, 然后要么就等待它结束, 要么就将它卸离(detach):

void doSomething();

std::thread t(doSomething);// start do something in background
...

t.join();// wait for to finish(block util doSomething ends)


就像对待 async() 一样, 你可以传入任何 callable object (可以是 function、member function、function object、lambda), 并可夹带任何可能的实参。
然而请注意, 除非你真的知道你在做什么, 否则面对"处理目标函数所必须"的所有 object 都应该以 by value 方式传递, 使得 thread 只使用 local copy。


此外, 这是个低层接口, 所以我们会感兴趣这一接口和高级的 async() 相比之下不提供哪些性质:

1. Class thread 没有所谓发射策略(launch policy)。'C++ 标准库永远试着将目标函数启动于一个新线程中。如果无法做到会抛出 std::system_error 并带着差错
    码 resource_unavailable_try_again'

2. 没有接口可处理线程结果, 唯一可获得的是一个独一无二的线程 ID

3. 如果发生异常, 但未被捕捉于线程之内, 程序会立刻中止并调用 std::terminate()。若想将异常传播至线程外的某个 context, 必须使用 exception_ptr

4. 你必须(像个调用者般地)声明是否"想要等待线程结束"(那就调用 join()) 或打算"将它自母体卸离 (detach) 使它运行于后台而不受任何控制"(那就调用 detach())。
   如果你在 thread object 寿命结束前不这么做, 或如果它发生了一次 move assignment, 程序会中止并调用 std::terminate()。


5. 如果你让线程运行于后台而 main() 结束了, 所有线程会被鲁莽而硬性地终止。


下面是第一个完整例子:

#include <chrono>
#include <iostream>
#include <random>
#include <stdexcept>
#include <thread>

using namespace std;

void doSomething(int num, char c) {
  try {
    default_random_engine dre(c);
    uniform_int_distribution<int> id(10, 1000);
    for (int i = 0; i < num; i++) {
      std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
      cout.put(c).flush();
    }
  }catch (std::exception& e) {
      cout << e.what() << endl;
  }
}

int main(int argc, char** argv) {
    try{
        std::thread t1(doSomething);
        cout << "Staring fg thread" << t1.get_id() << endl;

        for(int i = 0; i < 5 ; i++) {
            thread t(doSomething, 10, i + 'a');
            cout << "detach started fg thread" << t.get_id() << endl;
            t.detach();// detach the thread into background
        }

        cin.get();// wait for any input
        cout << "-join fg thread " << t1.get_id() << endl;
        t1.join();
    }catch(const std::exception& e){
        cout << e.what() << endl;
    }

    return 0;
}

本例的 main() 启动若干线程, 让它们都执行 doSomething()。基于以下原因不论 main() 或是 doSomething() 都有 try-catch 子句:

1. 在 main() 中, "创建线程"这个动作有可能抛出一个夹带差错码 resource_unavailable_try_again 的异常 std::system_error

2. 在 doSomething() 中, 由于此函数被启动为 std::thread, 任何异常若未被捕捉都会造成程序终止

main() 所启动的第一个线程, 稍后我们便"等待它结束":

thread t1(doSomething,5,'.');
...

t1.join();

其他线程则是启动之后便被卸离(detached), 所以有可能 main() 结束时它们还在执行:

for(int i=0; i< 5; i++){
    thread t(doSomething, 10, 'a'+i);
    t.detach();
}

一旦 main() 结束, 程序会立刻终止所有后台线程。


// !! 当心 Detached Thread (卸离后的线程)

Detached thread (卸离后的线程) 很容易形成问题--如果它们使用 nonlocal 资源的话。问题出在你丧失了对 detached thread 的控制, 没有轻松的办法可以得知它是
否运行, 以及运行多久。因此, 请确定绝不要让一个 detached thread 访问任何寿命已结束的 object。基于这个理由, "以 by reference 方式传递变量和 object"给线
程, 总是带有风险。'强烈建议以 by value 方式传递'。

请注意, 寿命问题一样困扰 global 和 static object, 因为当程序退离 exit, detached thread 可能还在运行, 意味着它仍有可能访问"已被销毁"或"正在析构"的
global 或 static object, 这会导致不可预期的行为。

所以, 请考虑以下数点作为 detached thread 的一般性规则:

1. Detached thread 应该宁可只访问 local copy

2. 如果 detached thread 用上了一个 global or static object, 你应该做以下事情之一:

   确保这些 global/static object 在"对它们进行访问"之所有 detached thread 都结束(或都不再访问它们) 之前不被销毁。一种做法就是使用 condition variable
   , 它让 detached thread 用来发信号说它们已结束。离开 main() 或调用 exit() 之前你必须先设置妥这些 condition variable, 然后发信号(to signal)说可进
   行析构了

   以调用 quick_exit() 的方式结束程序。这个函数之所以存在完全是为了以"不调用 global 和 static object 析构函数"的方式结束程序

由于 std::cin、std::cout 和 std::cerr 及其他 global stream object 按标准所说乃是"在程序运行期间不会被销毁", 所以 detached thread 访问这些 object
应该不会导致不可预期的行为。

尽管如此, 请牢记一个经验法则:终止 detached thread 的唯一安全方法就是搭配"...at_thread_exit()" 函数群中的某一个。这会"强制 main thread 等待 detached 
thread 真正结束"。或者你也可以选择忽略这一性质而相信某位评论家所言: 'Detached thread 应该被移到‘危险性质’的篇章中, 几乎没有人需要它'。



// !! Thread ID

如你所见, 程序打印 thread ID 时, 若非借由 thread object, 就是在一个 thread 内使用 name-space this_thread (此亦由<thread>提供):


void doSomething(int num, char c){
    ...
    cerr <<this_thread::get_id() << endl;

    thread t(doSomething, 10, 'a');
    cout << t.get_id() << endl;
}

这所谓 thread ID 隶属于特殊类型 std::thread::id, 其值独一无二。此外, class id 有个 default 构造函数, 会产生一个独一无二的 ID 用来表现"no thread":

std::cout << "id of no thread" << std::thread::id() << std::endl;

唯一允许对 thread ID 进行的操作是"比较", 以及调用 output 操作符输出至某个 stream。你不该有任何进一步假设, 像是"no thread 拥有 ID 0 或 main thread
拥有ID 1"之类的想象。事实上实现(implementation) 有可能在被申请时才动态生成这些ID, 而不是在 thread 被启动时就生成之, 那么 main thread 的编号就取决于
先前对 thread ID 的申请次数。以下代码:


std::thread t1(doSomething, 5, 'a');
std::thread t2(doSomething, 6, 'b');
std::thread t3(doSomething, 7, 'c');

std::cout << "t3 ID" << t3.get_id() << endl;
std::cout << "main ID " << std::this_thread::get_id() << endl;
std::cout << "no thread ID" << std::thread::id() << endl;

因此, 识别线程(例如主线程 master thread) 的唯一办法是, 将线程启动时的 ID 存储下来, 以此为唯一识别值:

std::thread::id masterThreadId;
void doSomething(int num, char c){
    if(std::this_thread::get_id() == masterThreadId){
        ...
    }
    ...
}


std::thread master(doSomething, 10, 'n');
masterThreadId = master.get_id();
...

std::thread slave(doSomething, 11, 'w');
...

注意, 已结束的线程的 ID 可能会被系统拿去重复使用。



// !! Promise

现在, 新问题来了: 如何在线程之间传递参数和处理异常(也就是高级接口如 async() 如何实现这一技术)。欲传递数值给线程, 你可以仅仅把它们当作实参来传递。
如果你需要线程的运行结果, 可用 by reference 方式传递, 就像 async() 描述的那样。

然而, 另一个用来传递运行结果和异常(亦被视为一种结果)的一般性机制是: class std::promise。所谓 promise object 是 future object 的配对兄弟, 二者都能暂时
持有一个 shared state (用来表现一个结果值或一个异常)。但 future object 允许你取回数(借由 get()), promise object 却是让你提供数据(借由 set_...() 函数
群中的一个)。

下面是个例子:

#include <thread>
#include <future>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <functional>
#include <utility>

using namespace std;

void doSomething(std::promise<std::string> &p){
    try{
        std::cout << "read char ('x' for exception)" << std::endl;
        char c = std::cin.get();
        if(c == 'x'){
            std::string s =  std::runtime_error(std::string("char") + c + "process");
            p.set_value(std::move(s));
        }
    }
}


int main(int argc, char** argv){
    try{
        std::promise<std::string> p;
        std::thread t(doSomething, std::ref(p));
        t.detach();
        ...
        std::future<std::string> f(p.get_future());
        std::cout << "result: " << f.get() << std::endl;
    }catch(const std::exception& e){
        cout << e.what() << endl;
    }catch(...){
        std::cerr << "Exception"  << std::endl;
    }
    return 0;
}

在包含 <future> (其中有 promise 的声明)之后, 你可以声明一个 promise object, 令它针对"持有值"或"返回值"特化(如果两者都是none, 就特化为 void):


std::promise<std::string> p;

Promise 内部会建立一个 shared state, 在这里被用来存放一个相应类型的值或一个异常, 并可被 future object 取其数据当作线程结果。

这个 promise 随后被传给一个在分离线程(separate thread)中运行的任务(task):

std::thread t(doSomething, std::ref);

借由 std::ref()我们确保这个 promise 以 by reference 方式传递, 使其状态得以被改变(copying 不适用于 promise)。

然后在线程内调用 set_value() 或 set_exception(), 便得以在 promise 中存放一个值或一个异常:

void doSomething(std::promise<std::string> &p){
    try
    {
        p.set_value(std::move(s));// store result
    }
    catch(const std::exception& e)
    {
        p.set_exception(std::current_exception());// store exception
        std::cerr << e.what() << '\n';
    } 
}

此处用上了定义于 <exception> 内的辅助函数 std::current_exception(), 它会将当前异常以类型 std::exception_ptr 生成出来, 如果当前并无异常就生成
nullptr。这个异常会被存放于 promise object 内部。

一旦 shared state 存有某值或某个异常, 其状态就转变为 ready。于是你可以在他处取出其内容。但是"取出"动作需要借助一个"共享相同 shared state"的
future object。为此, 我们在 main() 内对 promise object 调用 get_future(), 建立起这一相应的 future object。也可以在启动线程之前先建立该
future object:


std::future<std::string> f(p.get_future());

现在, 通过 get() 我们可以取得"被存储的结果", 或是令"被存储的异常"再次被抛出:

f.get();




// !! Class packaged_task<>

async() 予你一个权柄, 使你得以处理 task 的成果, 该 task 是你尝试立刻启动于后台的。然而有时候虽然你需要处理一个后台 task 的成果, 你其实不需要立刻启动该
task。举个例子, thread pool 可控制何时运行以及多少个后台 task 同时运行, 此情况下我们不再这么写:


double compute(double x, double y);
std::future<double> f = std::async(compute, 7, 5);
...
double res = f.get();

而是写成这样:

double compute(double x, double y);
std::package_task<double(double,double)> task(compute);// create a task
...
task(7, 5);// start a task(typically in a seperat thread)
...
double res = task.get();

其中的 task 通常(但非一定)启动于某一分离线程中。

上述的 class std::packaged_task<> 定义于 <future> 内, 持有目标函数及其可能结果。



// !! 细说启动线程 (Starting a Thread)

介绍完"启动线程"和"处理返回值或异常"之高级及低层接口后, 让我们总结所有概念, 并提供若干尚未提及的细节。


Thread 接口层级

call std::async()   return value or exception automatically are provide by a std::future<>

call task of class std::packaged_task return value or exception automatically are provide by a std::future

call object of class std::thread  set value or exception in a std::promise<>


概念上, 我们有数个层面可以启动线程并处理其返回值或异常:

1. 低层接口 class thread 让我们得以启动线程。为了"返回数据", 我们需要可共享的变量(global 或 static 变量, 或是以实参传递的变量)。为了"返回异常",可利用类
   型 std::exception_ptr (它被  std::current_exception() 返回并可被 std::rethrow_exception()处理。


2. Shared state 的概念使我们能够以一种较便捷的方法处理返回值或异常。搭配低层接口所提供的 promise 我们可以建立一个 shared state 然后通过一个 future 来
   处理它。


3. 在高级层面中, class packaged_task 或 async() 会自动建立一个 shared state, 它会因为一个 return 语句或一个未被捕获的异常(uncaught exception)而
   设置妥。

4. packaged_task 允许我们建立一个"带着 shared state"的 object, 但我们必须明确写出何时启动该线程

5. 若是使用std::async(), 我们无须关心线程何时真正启动。我们唯一确知的是当需要结果时就调用 get()



// !! Shared State


如你所见, 上述几乎所有性质都用到一个中心概念: shared state。它允许"启动及控制后台机能"的 object (一个 promise、packaged task 或是 async()) 能够和"处
理其结果"的  object (一个 future 或  shared future) 相互沟通。因此, shared state 必须能够持有被启动之目标函数以及某些状态 (state) 和结果(一个返回值
或一个异常)

Shared state 如果持有其函数运行结, 我们说它是 ready (也就是返回值或异常已备妥待取)。Shared state 通常被实现为一个 reference-counted object——当它被
最后一个使用者释放时即被销毁。




// !! 细说 async()

一般而言, std::async() 是个辅助函数, 用来在分离线程中启动某个函数(如果可能的话)。因此, '如果低层平台支持多线程, 你可以让函数并发运转'; 如果低层平台不支持,
也没有任何损失。

然而 async() 的真实行为复杂得多, 且高度取决于 launch(发射) 策略,后者可作为第一实参。基于这个因素, 以下便以应用程序开发者的角度描述 async() 的三个标准调
用形式。

future async(std::launch::async, F func, args...);

1. 尝试启动 func 并给予实参 args, 形成一个异步任务(asynchronous task; 一个并行线程)

2. 如果以上办不到, 就抛出 std::system_error 异常, 带着差错码 std::errc::resource_unavailable_try_again

3. 被启动的线程保证在程序结束前完成, 除非程序中途失败(abort)

以下情况会结束线程(完成工作):

1. 对返回的 future 调用 get() 或 wait()

2. 如果最后一个指向"返回之 future 所代表的 shared stat"的 object 被销毁

3. 这意味着对 async() 的调用会造成停滞 (block) 直到 func 完成---如果 async() 的返回值未被使用的话


future async(std::launch::deferred, F func, args...);


1. 传递 func 并夹带实参 args, 形成一个推迟任务(deferred task)。当我们对返回的 future 调用 wait() 或 get(), 那个推迟任务即被同步调用
   (synchronously called)


2. 如果未曾如上调用 wait() 和 get(), 那个推迟任务(deferred task) 绝不会启动



future async(F func, args...);

1. 相当于调用 async() 并携带 std::launch::async 和 std::launch::deferred 组合而成的 launch 策略。系统会根据当前形势选择其中一个发射策略。也就是说,
   如果"立即发射"策略行不通的话, 会造成 func 被推迟调用

2. 也就是说, 如果 async() 可以为 func 启动一个新线程, 就那么做, 否则 func 就会被推迟, 直到我们对返回的 future 调用 get() 或 wait()

3. 如果没有对返回的 future 调用 get() 或 wait(), func 有可能永不被调用

4. 注意,如果无法异步调用 func, 本形式的 async() 不会抛出 system_error 异常(但有可能因为其他原因而抛出 system error)


'所有 async() 形式都只要求 func 是个 callable object (不论 function、member function、function object、lambda 都可以)'

将发射策略 std::launch::async|std::launch::deferred 传递给 async(), 其后果和不传递任何发射策略是一样的。发射策略设为 0 会导致不可预期的行为(C++ 标
准库未涵盖此情况, 不同的实现可能行为互异)



// !! 细说 Future

'Class future<> 用来表现某一操作的成果(outcome): 可能是个返回值或是一个异常, 但不会二者都是'。


这份成果被管理于一个 shared state 内, 后者可被 std::async() 或一个 std::packaged_task 或一个 promise 创建出来。这份成果也许尚未存在, 因此 future
持有的也可能是"生成该成果"的每一件必要东西。

如果 future 是被 async() 返回且其相关的 task 受到推迟, 对它调用 get() 或 wait() 会同步启动该 task。注意, wait_for() 和 wait_until() 都不会令一个
被推迟任务(deferred task)启动。

成果只能被取出一次。因此 future 可能处于 valid 或 invalid 状态: 有效意味着"某一操作的成果或爆发的异常"尚未被取出。


'class future<> 可用的操作'


future f;// Default 构造函数, 建立一个 future,带着无效状态

future f(rv);// Move constructor, 取 rvalue rv 的内容建立一个新的 future, 并令 rv 带着无效状态
f = rv;

f.valid();// 如果 f 具备有效状态返回 true 否则返回 false

f.get();// block 直到后台任务执行完成, 它会迫使被 deferred 的线程同步启动
f.wait();//block 直到后台任务执行完成, 它会迫使被 deferred 的线程同步启动

f.wait_for(dur);// block dur 时间段, 或直到后台任务完成.但被推迟的线程并不会强制启动 
f.wait_until(dur);// block dur 时间段, 或直到后台任务完成.但被推迟的线程并不会强制启动

f.shared();// 产生一个 shared_future 带着当前状态, 并令 f 的状态失效


注意, get() 的返回值取决于 future<> 的特化类型。

1. 如果它是 void, get() 获得的就是 void 也就是"无物"

2. 如果 future 的 template 参数是个 reference 类型, get() 便返回一个 reference 指向返回值

3. 否则 get() 返回返回值的一份 copy, 或是对返回值进行 move assign 动作---取决于返回类型是否支持 move assignment 语义


注意, 只可调用 get()  一次, 因为 get() 会令 future 处于无效状态。



// !! 细说 Shared Future


// !! 细说 class std::packaged_task

class std::packaged_task<> 被用来同时持有目标函数及其"成果"(也就是所谓的 shared state)。"成果" 也许是个返回值或是目标函数所触发的异常。你可以拿相应
的目标函数来初始化 packaged task, 而后通过对 packaged task 实施 operator() 调用该目标函数。最后, 你可以对此 packaged task 取一个 future 以便处理
其成果。

'下面列出了 class packaged_task 的操作函数'。

packaged_task pt;// Default 构造函数, 建立一个 packaged_task, 不带 shared state 也不带 stored result

packaged_task pt(f);// 为 task f 建议一个对象

packaged_task pt(alloc, f);// 为 task f 建议一个对象, 使用分配器 alloc

pt.~packaged_task();// 销毁 *this

swap(pt1, pt2);// 两个 packaged_task 互换

pt.valid();// 如何 pt 有一个 shared state, 就返回 true

pt.get_future();//产生一个 future object,用来取回 share state

pt(args);// 调用 task 并令 shared state 成为 ready

pt.make_ready_at_thread_exit();//调用 task 并令 线程退出时令 shared state 成为 ready

pt.reset();// 为 pt 建立一个新的 shared state 

由于此 task 之构造函数而发生的任何异常, 例如"缺乏可用内存", 也会被存放于 shared state。

如果调用 task 或调用 get_future() 却没有可用状态, 会抛出 std::future_error 异常并带着差错码 std::future_errc::no_state。

第二次调用 get_future() 会抛出 std::future_error 异常并带着差错码 std::future_errc::future_already_retrieved。

析构函数和 reset() 会抛弃 shared state, 意思是 packaged task 会释放 shared state, 并且如果 shared state 尚未 ready 就令它变成 ready, 然后将一个
std::future_error 异常并夹带差错码 std::future_errc::broken_promise 存储起来当作成果。

一如往常, make_ready_at_thread_exit() 函数用来确保在 task 的成果被处理之前, 终结该 task 的线程的局部对象(local object)和其他材料会先被妥善清理。




// !! 细说 class std::thread

class std::thread, 其对象用来启动和表现线程。这些对象和操作系统提供的线程呈现一对一映射关系。



'class thread 的操作函数'


thread t;// Default 构造函数, 建立一个 nonjoinable thread object

thread t(f,...);// 创建一个 thread object, 表示 f 将被启动在一个线程中

thread t(rv);// Move constructor, 创建一个新的 thread object, 取 rv 的状态并令 rv 变成 nonjoinable

t.~thread();// 销毁 *this; 如果线程是 joinable 则调用 terminate() 

t.joinable();// 如果 t 关联一个线程(也就是说它是 joinable)便产生 true

t.join();// 等待关联线程完成工作, 然后令此 object 变成 nonjoinable

t.detach();// 解除 t 与线程之间的关联并且让线程继续运行,并令 object 变成 nonjoinable

t.get_id()

t.native_handle();// 返回一个依赖于平台的类型 native_handle_type, 用于不具可移植性的扩展


'Thread object 和线程之间的关联始于您将一个 callable object 指派为初值(或是 move copy/assign) 给它, 并夹带可能有的实参'。

这个关联的结束有两个情况:'一是由于 join() (它将等待线程成果) 或是由于 detach() (它将明确失去对线程的关联)'。不论哪一个函数都必须在 thread object 生命
结束前或在一个新的 thread object 被 move assigned 之前被调用, 否则程序就会因 std::terminate() 而中止。

'如果 thread object 关联至某个线程, 它就是所谓 joinable'。此情况下调用 joinable() 会获得 true, 调用 get_id() 会获得 thread ID, 其值不同于
std::thread::id() 所得。


Thread ID 有自己的类型 std::thread::id。其 default 构造函数会产出一个独一无二的 ID 用以表示"非线程"。如果没有任何线程被关联, 调用 thread::get_id()
获得的便是那个特殊值, 如果 thread object 关联至某个线程(也就是 joinable), 调用 thread::get_id() 便会获得另一个独一无二的 ID。


唯一可对 thread ID 执行的操作是对它们进行比较, 或是将它们写至一个 output stream。


注意, detached thread 不应该访问生命已结束的 object。这意味着当我们结束程序时, 必须确定 detached thread 不会访问 global/static object。


此外, class std::thread 还提供一个 static 成员函数, 用来查询并行线程的可能数量(只是一个参考值):

unsigned int std::thread::hardware_concurrency();


. 返回可能的线程数量
· 该数量只是个参考值, 不保证准确
· 如果数量不可计算或不明确, 返回值是0。




// !! Namespace this_thread

针对任何线程(包括主线程 main thread), <thread> 声明一个命名空间 std::this_thread, 用以提供线程专属的 global 函数。


'命名空间 std::this_thread 提供的线程专属操作'

this_thread::get_id(); // 获取当前线程的 id
this_thread::sleep_for(dur);// 将某个线程阻塞(block) dur 时间段
this_thread::sleep_until(tp);// 将某个线程阻塞(block) 直到时间点 tp
this_thread::yield();// 建议释放控制以便重新调度让先一个线程能够执行


注意, 当处理系统时间调整(system-time adjustment)时, sleep_for() 和 sleep_until() 往往不同

函数this_thread::yield() 用来告诉系统, 放弃当前线程的时间切片(time slice) 余额是有好处的, 这将使运行环境得以重新调度(reschedule)以便允许其他线程执行。


"放弃控制"的一个典型例子是, 当等待或轮询(wait or poll)另一线程, 或等待或轮询"某个 atomic flag 被另一线程设定"

while(!readFlag){
    std::this_thread::yield();
}

另一个例子是, 当你尝试锁定多个 lock/mutex 却无法取得其中一个 lock 或 mutex, 那么在尝试不同次序的 lock/mutex 之前你可以使用 yield(), 这会让你的程序更
快些。



// !! 线程同步化与 Concurrency(并发)问题

使用多线程(multiple thread) 几乎总是会伴随"数据的并发访问" (concurrent data access)。'多个线程彼此毫无关系地运行是很罕见的'。线程有可能提供数据给其他
线程处理, 或是备妥必要的先决条件(precondition) 用以启动其他进程(process)。

这就是多线程棘手的原因。许多事情有可能往错误的方向走。或者换个角度说,许多事情也许和新手甚至经验丰富的程序员的预期不同。

因此, 讨论同步化线程(synchronize thread)和并发数据处理的技术之前, 我们必须先了解问题所在。然后我们就可以开始讨论以下的线程同步化技术:

1. Mutex 和 lock(互斥体和锁), 包括 call_once()

2. Condition variable (条件变量)

3. Atomic



// !! 当心 Concurrency (并发)

在详细讨论 concurrency 引发的问题之前, 让我先制定第一条规则, 为的是可能你已经打算直接动手干了而不深入此节。如果你只学一条"如何面对多线程"的规则, 应该就是这
一条了:


'多个线程并发处理相同的数据而又不曾同步化(synchronization), 那么唯一安全的情况就是:所有线程只读取数据'。

所谓"相同的数据", 意思是使用相同内存区(same memory location)。如果不同的线程并发处理它们手上不同的变量或对象或成员, 不会有问题, 因为自 C++11 起每个变量
都保证拥有自己的内存区。

然而, 当两个或更多线程并发处理相同的变量或对象或成员, 而且至少其中一个线程改动了它, 而你又不曾同步化(synchronize)该处理动作, 你就可能有了深深的麻烦。
这就是 C++ 所谓的 data race。C++11 标准中定义的 data race 是"不同线程中的两个互相冲突的动作, 其中至少一个动作不是 atomic(不可切割的), 而且无一个动作
发生在另一动作之前"。Data race 总是导致不可预期的行为。


'就像处于 data race 情况一样, 我们的问题在于, 代码也许经常能够如你所愿, 但却不是永远如此, 这正是编程时面对的最难缠问题之一'。也许, 使用其他数据, 或进入生产
模式, 或换到另一个平台, 你的程序突然就完蛋了。所以, 如果使用多线程, 要特别小心 concurrent data access。



// !! Concurrent Data Access 为什么造成问题

为了解 concurrent data access 造成的问题, 我们必须了解当我们使用 concurrecy 时 C++ 给了什么保证。注意, 一个编程语言如 C++, 总是个抽象层, 用以支持不
同的平台和硬件, 后者根据其体系结构和目的提供不同的能力和接口。因此, 一个像  C++ 这样的标准具体描述了语句和操作的影响, 但并非等同于其所产生的汇编码(assembler 
code)。'标准描述的是 what 而不是 how'。


一般而言, 行为不会被定义得太谨慎以至于只能有一种实现。事实上行为甚至有可能不被明确定义, 例如函数调用时其实参核值(argument evaluation)次序就没有具体说明。
如果程序对此有特定的期待, 会导致不可预期的行为。


因此,重要的问题是:语言给了什么保证? 在该范围内程序员不该期望更多, 即使某些额外的保证似乎很明显。

'事实上关于所谓 as-if 规则, 每个编译器都可以将代码无限优化,只要程序行为外观上相同。因此, 被生成的代码是个黑盒子, 是可以变化的, 只要可观测行为保持稳定'。

以下摘自 C++standard:

1. 任何实现(implementation) 可以自由忽视国际标准(International Standard)的任何规定, 只要最终成果貌似遵守了那些规定--'这可由程序的可观测行为加以判断'。


未定义行为之所以存在, 是为了给予编译器和硬件厂商以自由度和能力去生成最佳代码,不论他们的"最佳"标准在哪里。是的,它适用于两端: 编译器有可能展开循环(loop),重新安
排语句, 去除无用代码(dead code), 预先获取数据, 而在现代化体系结构中, 一个以硬件实现的 buffer 有可能重新安排(reorder) load 或 store。

'重新安排次序(reordering) 对于改善程序速度也许有帮助, 但它们亦有可能产生破坏行为'。为了受益于"最快的速度", "安全性"也许不在默认考虑范围内。因此, 特别针对
concurrent data access, 我们必须了解我们手上有些什么保证。




// !!  什么情况下可能出错

为了给予编译器和硬件以足够的自由度完成优化, C++ 一般并不给予许多"你或许期待"的保证。原因是, 在所有情况中(而非仅仅那些有用的地方)实施这些保证, 会带来太高的效率
成本。事实上, 在 C++ 中我们可能会遭遇以下问题:


1.  unsynchronized data access(未同步化的数据访问): 并行运行的两个线程读和写同一笔数据，不知道哪一个语句先来。

2.  Half-written data(写至半途的数据): 某个线程正在读数据, 另一个线程改动它, 于是读取中的线程甚至可能读到改了一半的数据, 读到一个半新半旧值。

3.  Reordered statement(重新安排的语句): 语句和操作有可能被重新安排次序(reordered), 也许对于每一个单线程正确，但对于多个线程的组合却破坏了预期的行为


// !! Unsynchronized Data Access（未同步化的数据访问)


以下代码确保以 val 的绝对值为实参调用f(), 如果  val 是负数就将它反相:


if(val >= 0){
    f(val);
}else{
    f(-val);
}

在单线程环境中上述代码没问题。然而在一个多线程环境中, 这段代码不一定能成功运作。如果多个线程处理 val, val 的值有可能在"if 子句"和"调用 f()" 之间被改变,造
成负值被传给 f()。

基于相同理由, 以下代码:

std::vector<std::string> v;
...
if(!v.empty()){
    std::cout << v.front() << std::endl;
}

也可能形成问题。如果 v 被多个线程共享，由于 v 有可能在"调用 empty() "和"调用 front()"之间变成空(empty), 导致不可预期的行为。


注意这个问题也可能出现在"以 C++ 标准库提供的函数完成"的代码。例如:


v.at(5);

"如果 v 没有足够元素就会抛出异常"这个保证不再成立, 因为当 at() 被调用时另一个线程有可能改动 v。

因此, 请牢记以下文字:


'除非另有说明, C++ 标准库提供的函数通常不支持"写或读"动作与另一个"写"动作(写至同一笔数据)并发执行'。

也就是说, 除非另有说明, 来自多线程"对同一 object 的多次调用"会导致不可预期的行为。

然而 C++ 标准库对于线程安全还是提供了若干保证。例如:


1. 并发处理同一容器内的不同元素是可以的(但vector<bool>例外）。因此, 不同的线程可以并发读和/或写同一容器内的不同元素。例如,每个线程可以处理某些事然后将结果
   存储于一个共享的 vector 内专属该线程的某元素。


2. 并发处理 string stream、file stream 或 stream buffer 会导致不可预期的行为。但是一如进入本章之前我们所见的, 格式化输入自和输出至某个标准stream
   (它和 C I/O 同步化了) 是可以的, 虽然这可能导致插叙的字符。



// !! Half-Written Data (写至半途的数据)

考虑我们有一个变量:

long long x;

某个线程对它写入数值:

x = -1;

另一个线程读取它:

count << x;

程序的输出是什么? 也就是说当第二线程输出 x 时它读到哪个值? 以下皆有可能:

. 0 (x的旧值)——如果第一线程尚未赋予它 -1
· -1 (x的新值)——如果第一线程已经赋予它 -1
· 任何其他值——如果第二线程在"第一线程对 x 赋值 -1 的过程中"读取 x

上述最后一项在一台 32-bit  计算机上很可能发生--如果赋值操作导致两个 store, 而来自第二线程的读取操作发生在"第一个  store 已完成且第二个 store 尚未完成"
之际。

注意, 以上仅仅不适用于 long long。即使基本数据类型如 int 或 bool, 标准也不保证读或写是 atomic (不可切割的),意指独占而不可被打断(exclusive 
noninterruptable)。Data race 不是那么有可能发生, 但如果你想完全消除其可能性, 就必须采取手段。

相同情况也适用于繁复的数据结构, 即使它们由 C++ 标准库提供。例如面对 std::list<>, 程序员有权决定是否确保"当某个线程正在安插或删除元素时, 容器不会被另一个线
程改动"。否则其他线程便有可能用到这个 list 的不一致状态(inconsistent state), 例如"前向指针"已修改但"后向指针"尚未被改。



// !! Reordered Statement (重新安排的语句)

让我们讨论另一个简单例子。假设有两个共享对象, 一个是 long, 用来将 data 从某个线程传递到另一个线程, 另一个是 bool readyFlag, 用来表示第一线程是否已提供数
据:

long data;
bool readyFlag;

一种天真做法是, 将"某线程中对 data 的设""另一线程中对 data 的消"同步化(synchronize)。于是, 供应端这么调用:

data = 42;
readyFlag = true;


而消费端这么调用:


while(!readyFlag){
    usleep(10000);
    ...
}

foo(data);


在不知任何细节的情况下, 几乎每个程序员一开始都会认为第二线程必是在 data 有值 42 之后才调用 foo(), 他们认为"对 foo() 的调用"只有在 readyFlag 是 true 
的前提下才能触及,而那又唯有发生在第一线程将 42 赋值给 data 之后, 因为赋值之后才令 readyFlag 变成 true。
但其实这并非必要。事实上第二线程的输出有可能是 data"在第一线程赋值 42 之前"的旧值(甚至任何值, 因为 42 赋值动作有可能只做一半)。


也就是说, '编译器和/或硬件有可能重新安排语句, 使得实际执行以下动作':


readyFlag = true;
data = 42;


'一般而言, 基于 C++ 规则, 这样的重新安排(reordering) 是允许的, 因为 C++ 只要求编译所得的代码在单一线程内的可观测行为'(observable behavior inside 
a thread) 正确。对于第一线程, 并不在意先改变 readyFlag 还是 data; 从这个线程的角度看, 两个语句毫不相干。'因此,重新安排语句是被允许的, 只要单一线程的
可视效果相同'。

基于相同理由, 甚至第二线程也可能被重新安排语句,前提是不影响该线程的行为:

foo(data);
while(!readyFlag){
    ...
}

但是请注意, 这样的重新排列有可能在 foo() 抛出异常时影响其可观测行为。因此是否允许这样的重新排列,取决于细节,原则上说它是有问题的。

再强调一次,允许如此更改,原因是默认情况下 C++  编译器应该有能力生成高度优化代码,而某些优化行为可能需要重新排列语句。默认情况下这些优化并未被要求在意"是否存在
其他线程", 这样能让优化更容易些,因为这种情况下只需要局部分析(local analysis)便足够。



// !! 解决问题所需要的性质 (Feature)

为解决 concurrent data access 的三个主要问题, 我们需要先建立以下概念:

1. Atomicity (不可切割性): 这意味着读或写一个变量,或是一连串语句,'其行为是独占的、排他的、无任何打断', 因此一个线程不可能读到"因另一线程而造成的"中间状态

2. Order (次序): 我们需要一些方法保证"具体指定之语句"的次序


C++ 标准库提供了多种办法来处理这些概念, 让程序在 concurrent access  方面获得额外的保证:

1. 你可以使用 future 和 promise , 它们都保证 atomicity 和 order: 一定是在形成成果(返回值或异常)之后才设定 shared state, 这意味着读和写不会并发发生。

2. 你可以使用 mutex 和 lock 来处理 critical section 或 protected zone, 借此得以授予独占权力, 使得(例如)一个"检验动作"和一个"依赖该检验结果的操作"
之间不会发生任何事。Lock 提供 atomicity, 它会阻塞(blocking)所有"使用 second lock" 的处理行为, 直到作用于相同资源身上的 first lock 被释放。更精准地
说, 被某个线程获得的 lock object, 它"被另一线程获得"之前必须先被成功释放。然而如果两个线程使用 lock 来处理数据, 每次运行的次序都有可能发生变化。


3. 你可以使用 condition variable 有效地令某线程等待若干"被另一线程控制的"判断式(predicate)成为 true。这有助于应付多线程间的次序, 允许一或多个线程处理
   其他一或多个线程所提供的数据或状态。

4. 你可以使用 atomic data type 确保每次对变量或对象的访问动作都是不可切割的(atomic)--只要 atomic type 上的操作次序保持稳定(stable)。有了 atomic, 我
   们得以进入 lock-free 编程,而那是专家偶尔也会出错的领域。


// !! volatile 和 Concurrency


注意, 我并没有说 volatile 是个"用来解决 concurrent data access 问题"的性质(feature), 虽然你可能因为以下原因而有那样的期盼:

1. volatile 是个 C++ 关键字, 用来阻止"过度优化"

2. 在 Java 中, volatile 对于 atomicity 和 order 提供了某些保证


在 C++ 中, volatile"只"具体表示对外部资源(像是共享内存)的访问不该被优化掉。如果没有 volatile, 编译器也许会消除对同一块共享内存区看似多余的 load, 只因它在
整个程序中看不到这个区域的任何改变。但是在 C++, volatile 既不提供 atomicity 也不提供特别的 order。因此 volatile 的语义在 C++ 和 Java 之间如今有些差异。



// !!  Mutex 和 Lock


Mutex 全名 mutual exclusion (互斥体), 是个 object, 用来协助采取独占排他(exclusive)方式控制"对资源的并发访问"。这里所谓"资源"可能是个 object, 或多个
object 的组合。为了获得独占式的资源访问能力, 相应的线程必须锁定(lock)  mutex, 这样可以防止其他线程也锁定 mutex, 直到第一个线程解锁(unlock) mutex。


// !! 使用  Mutex 和 Lock

我们打算保护"许多地方都会用到的" object val 的并发访问动作(concurrent access):

int val;

将 concurrent access 同步化的一个粗浅做法是, 引入 mutex, 用来赋予独占性并加控制:


int val;
std::mutex val_mutex;


此后每次访问都必须锁定这个 mutex 以求独占。例如某个线程可能会这么做(注意这是低劣做法，我们正是要改善它):


val_mutex.lock();
if(val > 0){
    foo(val);
}else{
    f(-val);
}
val_mutex.unlock();


另一个线程可能这样访问同一资源:

val_mutex.lock();
val ++;
val_mutex.unlock();

'有一点很重要: 凡是可能发生 concurrent access 的地方都该使用同一个 mutex, 不论读或写皆如此'。

这个简单的办法有可能演变得十分复杂。举个例子,你应该确保异常--它会终止独占--解除(unlock) 相应的 mutex, 否则资源就有可能被永远锁住。此外也可能出现
deadlock 情景:'两个线程在释放它们自己的 lock 之前彼此等待对方的 lock'。

C++ 标准库试图处理这些问题(但目前仍无法从概念上根本解决)。举个例子, 面对异常你不该自己 lock/unlock mutex, 应该使用 RAII 守则(Resource Acquisition Is 
Initialization),构造函数将获得资源, 而析构函数——甚至当"异常造成生命期结束"它也总是会被调用--则负责为我们释放资源。为了这个目的, C++ 标准库提供了
class std::lock_guard


int val;
std::mutex val_mutex;// control exclusive access to val
...

std::lock_guard<std::mutex> lg(val_mutex);// lock and automatically unlock
if(val > 0){
    foo(val);
}else{
    foo(-val);
}

'然而请注意, 这样的 lock 应该被限制在可能之最短周期内', 因为它们会阻塞(block)其他代码的并行运行机会。由于析构函数会释放这个 lock, 你或许会想明确安插大括
号, 令 lock 在更进一步语句被处理前先被释放:


int val;
std::mutex val_mutex;
...
{
   std::lock_guard<std::mutex> lg(val_mutex);
   if(val >= 0){
       foo(val);
   }else{
       foo(-val);
   }
}// ensure that lock get release here



// !! Mutex 和 Lock 的第一个完整用例

#include <future>
#include <mutex>
#include <iostream>
#include <string>


std::mutex print_mutex;

void print(const std::string& message){
    std::lock_guard<std::mutex> lg(print_mutex);
    for(char c: message){
        std::cout.put(c).flush();
    }
    std::cout << std::endl;
}


int main(int argc, char* argv[]){
    auto f1 = std::async(std::launch::async, print,"hello world");

    auto f2 = std::async(std::launch::async, print, "hello world");

    auto f3 = std::async(std::launch::async, print, "hello world");

    return 0;
}


所谓将输出同步化(synchronize) 就是令每次对 print() 的调用都独占地写出所有字符, 为此我们引入一个 mutex 给 print() 使用, 以及一个 lock guard 用来锁
定被保护区:

std::mutex print_mutex;
...
void print(const std::string& message){
    std::lock_guard<std::mutex> lg(print_mutex);
    for(char c : message){
        std::cout.put(c).flush();
    }
    std::cout << std::endl;
}

在这里, lock guard 的构造函数会调用 mutex 的 lock(), 如果资源(亦即 mutex) 已被取走, 它会 block(阻塞), 直到"对保护区的访问"再次获得允许。然而 lock 的
次序仍旧不明确，因此上述三行输出有可能以任何次序出现。



// !! 递归的（Recursive） Lock

有时候, 递归锁定(to lock recursively)是必要的, 典型例子是 active object 或 monitor, 它们在每个 public 函数内放一个 mutex 并取得其 lock, 用以防止
data race 腐蚀对象的内部状态。例如一个数据库接口可能像这样:


class DatabaseAccess{
private:
    std::mutex db_mutex;
    ...
public:
    void createTable(...){
        std::lock_guard<std::mutex> lg(db_mutex);
        ...
    }

    void insertTable(...){
        std::lock_guard<std::mutex> lg(db_mutex);
        ...
    }


};

当我们引入一个  public 成员函数而它可能调用其他 public 成员函数, 情况变得复杂:


void createTableAndInsert(...){
    std::lock_guard<std::mutex> lg(db_mutex);
    ...
    createTable();//Error deadlock because db_mutex is lock again
}

调用 createTableAndInsertData() 会造成 deadlock, 因为它锁住 dbMutex 之后调用 createTable(), 造成后者尝试再次 lock dbMutex, 那将会
block 直到 dbMutex 变为可用, 而这绝不会发生, 因为 createTableAndInsertData() 会 block 直到 createTable() 完成。

如果平台侦测到类似上述的 deadlock, C++  标准库允许第二次 lock 抛出异常 std::system_error 并带差错码  resource_deadlock_would_occur。但这并非必然
而且情况往往不是如此。

借着使用 recursive_mutex, 上述行为不再有问题。这个 mutex 允许同一线程多次锁定, 并在最近一次(last)相应的 unlock() 时释放 lock:


class DatabaseAccess{
private:
    std::recursive_mutex db_mutex;
    ...
public:
    void insertData(...){
        std::lock_guard<std::recursive_mutex> lg(db_mutex);
        ...
    }

    void createTable(...){
        std::lock_guard<std::recursive_mutex> lg(db_mutex);
        ...
    }

    void createTableAndInsertData(...){
        std::lock_guard<std::recursive_mutex> lg(db_mutex);
        ...
        createTable();
    }

    ...
};


// !! 尝试性的 Lock 以及带时间性的 Lock

有时候程序想要获得一个 lock 但如果不可能成功的话它不想永远 block 。针对这种情况, mutex 提供成员函数 try_lock(), 它试图取得一个 lock, 成功就返回 true, 
失败则返回 false。

为了仍能够使用 lock_guard (使当下作用域的任何出口都会自动unlock mutex), 你可以传一个额外实参 adopt_lock 给其构造函数:

std::mutex m;
while(!m.try_lock()){
    doSomethingOtherStuff();
}

std::lock_guard<std::mutex> lg(m, std::adopt_lock);
...

注意, try_lock() 有可能假性失败, 也就是说即使 lock 并未被他人拿走它也有可能失败(返回 false)。 

为了等待特定长度的时间, 你可以选用(带时间性的)所谓 timed mutex。有两个特殊 mutex class std::timed_mutex 和 std::recursive_timed_mutex 额外允许你
调用 try_lock_for() 或 try_lock_until(), 用以等待某个时间段或直至抵达某个时间点。这对于实时需求(real-time requirement)或避免可能的 deadlock 或许有
帮助。


std::timed_mutex m;

if(m.try_lock_for(std::chrono::seconds(1)) == false){
    std::lock_guard<std::mutex> lg(m, std::adopt_lock);
    ...
}else{
    couldNotGetTheLock();
}


// !! 处理多个 Lock

'通常一个线程一次只该锁定一个 mutex, 然而有时候必须锁定多个 mutex'(例如为了传送数据, 从一个受保护资源到另一个)。

这种情况下若以目前介绍过的 lock 机制来应付, 可能变得复杂且具风险: 你或许取得第一个 lock 却拿不到第二个 lock, 或许发生 deadlock--如果以不同的次序去锁住
相同的 lock。


C++ 标准库为此提供了若干便捷函数, 让你锁定多个 mutex。例如:


std::mutex m1;
std::mutex m2;

...
{
    std::lock(m1, m2);// lock both mutex
    std::lock_guard<std::mutex> lockM1(m1, std::adopt_lock);
    std::lock_guard<std::mutex> lockM2(m2, std::adopt_lock);
    ...
}


全局函数 std::lock() 会锁住它收到的所有 mutex, 而且 blocking 直到所有 mutex 都被锁定或直到抛出异常。

如果是后者, 已被成功锁定的 mutex 都会被解锁。一如以往, 成功锁定之后你可以并且应该使用 lock guard, 并以 adopt_lock 作为初始化的第二实参,确保任何情况下这
些 mutex 在离开作用域时会被解锁。'注意这个 lock() 提供了一个 deadlock 回避机制, 但那也意味着多个 lock 的锁定次序并不明确'。


以此相同方式你可以尝试"取得多个 lock"且"若并非所有 lock 都可用也不至于造成 blocking"。


std::mutex m1;
std::mutex m2;
int idx = std::try_lock(m1, m2);
if(idx < 0){// both lock success
    std::lock_guard<std::mutex> lockM1(m1, std::adopt_lock);
    std::lock_guard<std::mutex> lockM2(m2, std::adopt_lock);
    ...
}else{
    std::cerr << "cannot lock mutex m" << std::endl;
}


注意, 这个 try_lock() 不提供 deadlock 回避机制, 但它保证以出现于实参列的次序来试着完成锁定。



虽然代码看起来好像建立了"离开作用域时会自动解锁"的 lock, 其实并非如此, 那些 mutex 仍然保持锁定:


std::mutex m1;
std::mutex m2;
...
{
    std::try_lock(m1, m2);
    ...
}

// Oops, mutex are still lock


// !! Class unique_lock


'除了 class lock_guard<>, C++ 标准库还提供了 class unique_lock<>, 它对付 mutex 更有弹性'。Class unique_lock<> 提供的接口和 class 
lock_guard<> 相同, 而又允许明确写出"何时"以及"如何"锁定或解锁其 mutex。

与 class lock_guard 相较, class unique_lock 添加了以下三个构造函数:

1. 你可以传递 try_to_lock 表示企图锁定 mutex 但不希望 blocking:

std::unique_lock<std::mutex> lock(mutex, std::try_to_lock);
...
if(lock){// if lock was successfully
    ...
}


2. 你可以传递一个时间段或时间点给构造函数, 表示尝试在一个明确的时间周期内锁定:

std::unique_lock<std::mutex> lock(mutex, std::chrono::seconds(1));


3. 你可以传递 defer_lock, 表示初始化这一 lock object 但尚未打算锁住 mutex:

std::unique_lock<std::mutex> lock(mutex, std::defer_lock);
...
lock.lock();
...

上述的 defer_lock flag 可以用来建立一或多个 lock 并于稍后才锁住它们:


std::mutex m1;
std::mutex m2;

std::unique_lock<std::mutex> lockM1(m1, std::defer_lock);
std::unique_lock<std::mutex> lockM2(m2, std::defer_lock);

...

std::lock(m1, m2);// lock both mutex(or none if possible)


此外, class unique_lock  提供  release() 用来释放 mutex, 或是将其 mutex 拥有权转移给另一个 lock。


有了 lock_guard 和 unique_lock  作为工具, 现在我们可以实现一个粗浅例子, 以轮询(polling) 某个 ready flag 的方式,令一个线程等待另一个线程:


#include <mutex>

bool readyFlag;
std::mutex readyFlagMutex;

void thread1(){
    ...
    std::lock_guard<std::mutex> lock(readyFlagMutex);
    readyFlag = true;
}

void thread2(){
    std::unique_lock<std::mutex> ul(readyFlagMutex);
    while(!readyFlag){
        ul.unlock();
        std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        ul.lock();
    }
}// release lock


面对这段代码可能会有的典型疑虑, 我有以下两点解释:

1.  如果你惊讶为什么我使用 mutex 来控制 readyFlag 的读和写, 请回忆本章一开始介绍的准则:任何"带有至少一个 write"的并发处理(concurrent access)都应
该被同步化。


2. 如果你惊讶为什么声明 readyFlag 时竟不需要 volatile (如此便是允许 thread2() 中对其多次读取可被优化掉), 那么请注意:这些"对 readyFlag 的读取"发生在
critical section 内(也就是在某个 lock  的设立和解除之间)。这样的代码不得以"读/写动作被移出 critical section 之外"的形式被优化。


尽管如此, 这样对于"某一满足条件"的轮询(polling)通常不是好办法。更好的做法是使用 condition variable (条件变量)。


// !! 细说 Mutex 和 Lock

// !! 细说 Mutex

C++ 标准库提供了以下 mutex class

1. Class std::mutex, 同一时间只可被一个线程锁定。如果它被锁住, 任何其他 lock() 都会阻塞(block), 直到这个 mutex 再次可用, 且 try_lock() 会失败。

2. Class std::recursive_mutex, 允许在同一时间多次被同一线程获得其 lock。其典型应用是: 函数捕获一个 lock 并调用另一函数而后者再次捕获相同的 lock。

3. Class std::timed_mutex 额外允许你传递一个时间段或时间点, 用来定义多长时间内它可以尝试捕捉一个 lock。为此它提供了  try_lock_for() 和
   try_lock_until()。

4. Class std::recursive_timed_mutex 允许同一线程多次取得其 lock,可指定期限。


mutex  的操作函数:

mutex m;// Default 构造函数, 建立一个未锁定的 mutex
m.~mutex();
m.lock();// 尝试锁住 mutex(可能会造成阻塞)
m.try_lock();// 尝试锁住 mutex,如果锁定成功返回 true
m.try_lock_for(dur);//尝试在时间段 dur  内锁住,如果锁定成功返回 true
m.try_lock_until(tp);// 尝试在时间点 tp 之前锁住.如果锁定成功返回 true
m.unlock();//解除 mutex。如果它未曾被锁住, 行为不明确
m.native_handle();//


lock() 有可能抛出 std::system_error 并夹带以下差错码:

1. operation_not_permitted--如果线程的特权级(privilege)不足以执行此操作

2. resource_deadlock_would_occur -- 如果平台侦测到有个 deadlock 即将发生

3. device_or_resource_busy--如果 mutex 已被锁定而又无法形成阻塞(blocking)


如果程序解除 unlock 一个并非它所拥有的 mutex object, 或是销毁一个被任何线程拥有的 mutex object, 或是线程拥有 mutex object 但却结束了生命,将导致不明
确的行为。


// !! 细说 Class lock_guard


class std::lock_guard 提供了一个很小的接口, 用以确保一个 locked mutex 在离开作用域时总是会被释放。它的整个生命期间总是与一个  lock 相关联 associated
--也许是被明白申请, 也许是在构造期间接受(adopted)。

Class lock_guard 的操作函数:


lock_guard lg(m);// 为 mutex 建立一个 lock_guard 并锁定之
lock_guard lg(m, std::adopt_lock);// 为已经锁定的 mutex 建立一个 lock_guard
lg.~lock_guard();


// !! 细说 Class unique_lock

















































