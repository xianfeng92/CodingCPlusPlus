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




