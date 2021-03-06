// !! 11.3　运行库与多线程

// !! 11.3.1　CRT 的多线程困扰

// !! 线程的访问权限

线程的访问能力非常自由, 它可以访问进程内存里的所有数据, 甚至包括其他线程的堆栈 (如果它知道其他线程的堆栈地址, 然而这是很少见的情况), 线程也拥有自己的私有存储空间, 包括:

1. 栈 (尽管并非完全无法被其他线程访问, 但一般情况下仍然可以认为是私有的数据)

2. 线程局部存储 (Thread Local Storage, TLS)。线程局部存储是某些操作系统为线程单独提供的私有空间, 但通常只具有很有限的尺寸

3. 寄存器 (包括 PC 寄存器), 寄存器是执行流的基本数据, 因此为线程私有


从 C 程序员的角度来看, 数据在线程之间是否私有如表 11-3 所示。


// !! 多线程运行库

现有版本的 C/C++ 标准 (特指 C++03、C89、C99)对多线程可以说只字不提, 因此相应的 C/C++ 运行库也无法针对线程提供什么帮助, 也就是说在运行库里不能找到关于创建、结束、
同步线程的函数。

由于多线程在现代的程序设计中占据非常重要的地位, 主流的 C 运行库在设计时都会考虑到多线程相关的内容。

这里我们所说的"多线程相关"主要有两个方面, 一方面是提供那些多线程操作的接口, 比如创建线程、退出线程、设置线程优先级等函数接口; 另外一方面是 C 运行库本身要能够在多线程的
环境下正确运行。

对于第一方面, 主流的 CRT 都会有相应的功能。

Linux 下, glibc 也提供了一个可选的线程库 pthread (POSIX Thread), 它提供了诸如 pthread_create()、pthread_exit() 等函数用于线程的创建和退出。
很明显, 这些函数都不属于标准的运行库, 它们都是平台相关的。

对于第二个方面, C 语言运行库必须支持多线程的环境, 这是什么意思呢? 

实际上, 最初 CRT 在设计的时候是没有考虑多线程环境的, 因为当时根本没有多线程这样的概念。到后来多线程在程序中越来越普及, C/C++ 运行库在多线程环境下吃了不少苦头。
例如:

1. errno: '在 C 标准库里, 大多数错误代码是在函数返回之前赋值在名为 errno 的全局变量里的'。多线程并发的时候, 有可能 A 线程的 errno 的值在获取之前就被 B 线程给覆盖
   掉, 从而获得错误的出错信息

2. strtok() 等函数都会使用函数内部的局部静态变量来存储字符串的位置, 不同的线程调用这个函数将会把它内部的局部静态变量弄混乱

3. malloc/new 与 free/delete: '堆分配/释放函数或关键字在不加锁的情况下是线程不安全的'。由于这些函数或关键字的调用十分频繁, 因此在保证线程安全的时候显得十分繁琐

4. 异常处理: 在早期的 C++ 运行库里, 不同的线程抛出的异常会彼此冲突, 从而造成信息丢失的情况

5. printf/fprintf 及其他 IO 函数: 流输出函数同样是线程不安全的, 因为它们共享了同一个控制台或文件输出。不同的输出并发时, 信息会混杂在一起

6. 其他线程不安全函数: 包括与信号相关的一些函数


通常情况下, C 标准库中在不进行线程安全保护的情况下自然地具有线程安全的属性的函数有:

1. 字符处理 (ctype.h), 包括 isdigit、toupper 等, 这些函数同时还是可重入的

2. 字符串处理函数 (string.h), 包括 strlen、strcmp 等, 但其中涉及对参数中的数组进行写入的函数(如strcpy)仅在参数中的数组各不相同时可以并发

3. 数学函数 (math.h), 包括 sin、pow 等, 这些函数同时还是可重入的

4. 字符串转整数/浮点数 (stdlib.h), 包括 atof、atoi、atol、strtod、strtol、strtoul

5. 获取环境变量 (stdlib.h), 包括 getenv, 这个函数同时还是可重入的

6. 变长数组辅助函数


为了解决 C 标准库在多线程环境下的窘迫处境, 许多编译器附带了多线程版本的运行库。


// !! 11.3.2　CRT 改进


// !! 使用 TLS

多线程运行库具有什么样的改进呢?  首先, errno 必须成为各个线程的私有成员。

在 glibc 中, errno 被定义为一个宏, 如下:

#define errno (*__errno_location ())

函数 __errno_location 在不同的库版本下有不同的定义, 在单线程版本中, 它仅直接返回了全局变量 errno 的地址。而在多线程版本中, 不同线程调用 __errno_location 返回的地
址则各不相同。


// !! 加锁

'在多线程版本的运行库中, 线程不安全的函数内部都会自动地进行加锁, 包括 malloc、printf 等', 而异常处理的错误也早早就解决了。因此使用多线程版本的运行库时, 即使在
malloc/new 前后不进行加锁, 也不会出现并发冲突。


// !! 改进函数调用方式

C 语言的运行库为了支持多线程特性, 必须做出一些改进。

'一种改进的办法就是修改所有的线程不安全的函数的参数列表, 改成某种线程安全的版本'。

比如 MSVC 的 CRT 就提供了线程安全版本的 strtok() 函数: strtok_s, 它们的原型如下:

char *strtok(char *strToken, const char *strDelimit );
char *strtok_s( char *strToken, const char *strDelimit, char **context);

改进后的 strtok_s 增加了一个参数, 这个参数 context 是由调用者提供一个 char* 指针, strtok_s 将每次调用后的字符串位置保存在这个指针中。而之前版本的 strtok 函数会将
这个位置保存在一个函数内部的静态局部变量中, 如果有多个线程同时调用这个函数, 有可能出现冲突。

与 MSVC CRT 类似, Glibc 也提供了一个线程安全版本的 strtok() 叫做 strtok_r()。

'但是很多时候改变标准库函数的做法是不可行的。标准库之所以称之为"标准", 就是它具有一定的权威性和稳定性, 不能随意更改'。

如果随意更改, 那么所有遵循该标准的程序都需要重新进行修改, 这个"标准"是不是值得遵循就有待商榷了。

'所以更好的做法是不改变任何标准库函数的原型, 只是对标准库的实现进行一些改进, 使得它能够在多线程的环境下也能够顺利运行, 做到向后兼容'。


// !! 11.3.3　线程局部存储实现

很多时候, 开发者在编写多线程程序的时候都希望存储一些线程私有的数据。

我们知道, 属于每个线程私有的数据包括线程的栈和当前的寄存器, 但是这两种存储都是非常不可靠的, 栈会在每个函数退出和进入的时候被改变; 而寄存器更是少得可怜, 我们不可能拿寄存
器去存储所需要的数据。

假设我们要在线程中使用一个全局变量, 但希望这个全局变量是线程私有的, 而不是所有线程共享的, 该怎么办呢?

这时候就须要用到线程局部存储 (TLS, Thread Local Storage) 这个机制了。TLS 的用法很简单, 如果要定义一个全局变量为 TLS 类型的, 只需要在它定义前加上相应的关键字即可。
对于 GCC 来说, 这个关键字就是 __thread, 比如我们定义一个 TLS 的全局整型变量:

__thread int number;

'一旦一个全局变量被定义成 TLS 类型的, 那么每个线程都会拥有这个变量的一个副本, 任何线程对该变量的修改都不会影响其他线程中该变量的副本'。




