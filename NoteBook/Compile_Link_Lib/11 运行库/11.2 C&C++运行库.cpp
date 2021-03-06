// !! 11.2　C/C++ 运行库

// !! 11.2.1　C 语言运行库

'任何一个 C 程序, 它的背后都有一套庞大的代码来进行支撑, 以使得该程序能够正常运行'。这套代码至少包括入口函数及其所依赖的函数所构成的函数集合。当然, 它还理应包括各种
标准库函数的实现。

这样的一个代码集合称之为运行时库 (Runtime Library)。而 C 语言的运行库, 即被称为 C 运行库 (CRT)。

一个 C 语言运行库大致包含了如下功能:

1. 启动与退出: 包括入口函数及入口函数所依赖的其他函数等

2. 标准函数: 由 C 语言标准规定的 C 语言标准库所拥有的函数实现

3. I/O: I/O 功能的封装和实现

4. 堆: 堆的封装和实现

5. 语言实现: 语言中一些特殊功能的实现

6. 调试: 实现调试功能的代码


'在这些运行库的组成成分中, C 语言标准库占据了主要地位并且大有来头'。

C 语言标准库是 C 语言标准化的基础函数库, 我们平时使用的 printf、exit 等都是标准库中的一部分。标准库定义了 C 语言中普遍存在的函数集合, 我们可以放心地使用标准库中规
定的函数而不用担心在将代码移植到别的平台时对应的平台上不提供这个函数。


// !! 标准库的历史

1999 年, C99 标准诞生, C 语言标准库得到了进一步的扩充, 头文件 complex.h、fenv.h、inttypes.h、stdbool.h、stdint.h 和 tgmath.h 进入标准库。自此, C 语言标准库
的面貌一直延续至今。

初生的 C 语言在功能上非常不完善, 例如不提供 I/O 相关的函数。

第一个完整的 C 语言标准建立于 1989 年, 此版本的 C 语言标准称为 C89。由 C89 指定的 C 语言基础函数库就称为 ANSI C 标准运行库 (简称标准库)。

在 1999 年, C99 标准诞生, C 语言标准库得到了进一步的扩充, 头文件 complex.h、fenv.h、inttypes.h、stdbool.h、stdint.h 和 tgmath.h 进入标准库。


// !! 11.2.2　C 语言标准库

'ANSI C 的标准库由 24 个 C 头文件组成'。与许多其他语言 (如 Java) 的标准库不同, C 语言的标准库非常轻量, 它仅仅包含了数学函数、字符/字符串处理, I/O 等基本方面,

例如:

1. 标准输入输出 stdio.h

2. 文件操作 stdio.h

3. 字符操作 ctype.h

4. 数学函数 math.h

5. 资源管理 stdlib.h

6. 格式转换 stdlib.h

7. 时间/日期 time.h

8. 断言 assert.h

9. 各种类型上的常数 limits.h & float.h


除此之外, C 语言标准库还有一些特殊的库, 用于执行一些特殊的操作, 例如:

10. 变长参数 stdarg.h

11. 非局部跳转 setjmp.h


// !! 1. 变长参数

变长参数是 C 语言的特殊参数形式, 例如如下函数声明:

int printf(const char* format, ...);

如此的声明表明, printf 函数除了第一个参数类型为 const char* 之外, 其后可以追加任意数量、任意类型的参数。

在函数的实现部分, 可以使用 stdarg.h 里的多个宏来访问各个额外的参数: 假设 lastarg 是变长参数函数的最后一个具名参数(例如 printf 里的 format), 那么在函数内部定义类
型为 va_list 的变量:

va_list ap;

该变量以后将会依次指向各个可变参数。ap 必须用宏 va_start 初始化一次, 其中 lastarg 必须是函数的最后一个具名的参数。

va_start(ap, lastarg);

此后, 可以使用 va_arg 宏来获得下一个不定参数 (假设已知其类型为 type):

type next = va_arg(ap, type);

在函数结束前, 还必须用宏 va_end 来清理现场。


变长参数的实现得益于 C 语言默认的 cdecl 调用惯例的自右向左压栈传递方式。设想如下的函数:

int sum(unsigned num, ...);

其语义如下:

第一个参数传递一个整数 num, 紧接着后面会传递 num 个整数, 返回 num 个整数的和。

当我们调用:

int n = sum(3, 16, 38, 53);

参数在栈上会形成如图 11-7 所示的布局。

在函数内部, 函数可以使用名称 num 来访问数字 3, 但无法使用任何名称访问其他的几个不定参数。但此时由于栈上其他的几个参数实际恰好依序排列在参数 num 的高地址方向, 因此可以
很简单地通过 num 的地址计算出其他参数的地址。sum 函数的实现如下:


int sum(unsigned num, ...){
     int* p = &num + 1;
     int ret = 0;
     while(num --) {
        ret += *p++;
     }
     return ret;
}


在这里我们可以观察到两个事实:

1. sum 函数获取参数的量仅取决于 num 参数的值, 因此, 如果 num 参数的值不等于实际传递的不定参数的数量, 那么 sum 函数可能取到错误的或不足的参数

2. cdecl 调用惯例保证了参数的正确清除。我们知道有些调用惯例是由被调用方负责清除堆栈的参数, 然而, 被调用方在这里其实根本不知道有多少参数被传递进来, 所以没有办法清除堆栈。
   而 cdecl 恰好是调用方负责清除堆栈, 因此没有这个问题。


printf 的不定参数比 sum 要复杂得多, 因为 printf 的参数不仅数量不定, 而且类型也不定。所以 printf 需要在格式字符串中注明参数的类型, 例如用 %d 表明是一个整数。

printf 里的格式字符串如果将类型描述错误, 因为不同参数的大小不同, 不仅可能导致这个参数的输出错误, 还有可能导致其后的一系列参数错误。


下面让我们来看 va_list 等宏应该如何实现。

va_list 实际是一个指针, 用来指向各个不定参数。'由于类型不明, 因此这个 va_list 以 void* 或 char* 为最佳选择'。

va_start 将 va_list 定义的指针指向函数的最后一个参数后面的位置, 这个位置就是第一个不定参数。

va_arg 获取当前不定参数的值, 并根据当前不定参数的大小将指针移向下一个参数。

va_end 将指针清 0。

按照以上思路, va 系列宏的一个最简单的实现就可以得到了, 如下所示:


#define va_list char*
#define va_start(ap,arg) (ap=(va_list)&arg+sizeof(arg))
#define va_arg(ap,t) (*(t*)((ap+=sizeof(t))-sizeof(t)))
#define va_end(ap) (ap=(va_list)0)


// !! 11.2.3　glibc 与 MSVC CRT

运行库是平台相关的, 因为它与操作系统结合得非常紧密。'C 语言的运行库从某种程度上来讲是 C 语言的程序和不同操作系统平台之间的抽象层, 它将不同的操作系统 API 抽象成相同的
库函数'。

比如我们可以在不同的操作系统平台下使用 fread 来读取文件, 而事实上 fread 在不同的操作系统平台下的实现是不同的, 但作为运行库的使用者我们不需要关心这一点。

虽然各个平台下的 C 语言运行库提供了很多功能, 但很多时候它们毕竟有限, 比如用户的权限控制、操作系统线程创建等都不是属于标准的 C 语言运行库。

Linux 和 Windows 平台下的两个主要 C 语言运行库分别为 glibc (GNUC Library) 和 MSVCRT (Microsoft Visual C Runtime), 我们在下面将会分别介绍它们。

值得注意的是, 像线程操作这样的功能并不是标准的 C 语言运行库的一部分, 但是 glibc 和 MSVCRT 都包含了线程操作的库函数。

比如 glibc 有一个可选的 pthread 库中的 pthread_create() 函数可以用来创建线程; 而 MSVCRT 中可以使用 _beginthread() 函数来创建线程。所以 glibc 和 MSVCRT 事实
上是标准 C 语言运行库的超集, 它们各自对 C 标准库进行了一些扩展。


// !! glibc

glibc 即 GNU C Library, 是 GNU 旗下的 C 标准库。

GNU 操作系统的最初计划的内核是 Hurd, 一个微内核的构架系统。Hurd 因为种种原因开发进展缓慢, 而 Linux 因为它的实用性而逐渐风靡, 最后取代 Hurd 成了 GNU 操作系统的内核。

于是 glibc 从最初开始支持 Hurd 到后来渐渐发展成同时支持 Hurd 和 Linux, 而且随着 Linux 的越来越流行, glibc 也主要关注 Linux 下的开发, 成为了 Linux 平台的 C 标准库。


20 世纪 90 年代初, 在 glibc 成为 Linux 下的 C 运行库之前, Linux 的开发者们因为开发的需要, 从 Linux 内核代码里面分离出了一部分代码, 形成了早期 Linux 下的 C 运行库。

这个 C 运行库又被称为 Linux libc。这个版本的 C 运行库被维护了很多年, 从版本 2 一直开发到版本 5。

如果你去看早期版本的 Linux, 会发现 /lib 目录下面有 libc.so.5 这样的文件, 这个文件就是第五个版本的 Linux libc。

1996 年 FSF 发布了 glibc 2.0, '这个版本的 glibc 开始支持诸多特性, 比如它完全支持 POSIX 标准、国际化、IPv6、64 位数据访问、多线程及改进了代码的可移植性'。

在此时 Linux libc 的开发者也认识到单独地维护一份 Linux 下专用的 C 运行库是没有必要的, 于是 Linux 开始采用 glibc 作为默认的 C 运行库, 并且将 2.x 版本的 glibc 看
作是 Linux libc 的后继版本。

于是我们可以看到, glibc 在 /lib 目录下的 .so 文件为 libc.so.6, 即第六个 libc 版本, 而且在各个 Linux 发行版中, glibc 往往被称为 libc6。

glibc 在 Linux 平台下占据了主导地位之后, 它又被移植到了其他操作系统和其他硬件平台, 诸如 FreeBSD、NetBSD 等, 而且它支持数十种 CPU 及嵌入式平台。

glibc 的发布版本主要由两部分组成, '一部分是头文件, 比如 stdio.h、stdlib.h 等, 它们往往位于 /usr/include'; 另外一部分则是库的二进制文件部分, '二进制部分主要的就是
C 语言标准库, 它有静态和动态两个版本'。


动态的标准库它位于 /lib/x86_64-linux-gnu/libc.so.6; 而静态标准库位于 /lib/x86_64-linux-gnu/libc.a。

事实上 glibc 除了 C 标准库之外, 还有几个辅助程序运行的运行库, 这几个文件可以称得上是真正的"运行库"。它们就是 /usr/lib/crt1.o、/usr/lib/crti.o 和 /usr/lib/crtn.o。
是不是对这几个文件还有点印象呢? 我们在第2章讲到静态库链接的时候已经碰到过它们了, 虽然它们都很小, 但这几个文件都是程序运行的最关键的文件。


// !! glibc 启动文件

'crt1.o 里面包含的就是程序的入口函数 _start, 由它负责调用 __libc_start_main 初始化 libc 并且调用 main 函数进入真正的程序主体'。

实际上最初开始的时候它并不叫做 crt1.o, 而是叫做 crt.o, 包含了基本的启动、退出代码。

由于当时有些链接器对链接时目标文件和库的顺序有依赖性, crt.o 这个文件必须被放在链接器命令行中的所有输入文件中的第一个, 为了强调这一点, crt.o 被更名为 crt0.o, 表示它是
链接时输入的第一个文件。

后来由于 C++ 的出现和 ELF 文件的改进, 出现了必须在 main() 函数之前执行的全局/静态对象构造和必须在 main() 函数之后执行的全局/静态对象析构。

为了满足类似的需求, 运行库在每个目标文件中引入两个与初始化相关的段 .init 和 .finit。运行库会保证所有位于这两个段中的代码会先于/后于 main() 函数执行, 所以用它们来实现
全局构造和析构就是很自然的事情了。链接器在进行链接时, 会把所有输入目标文件中的 .init 和 .finit 按照顺序收集起来, 然后将它们合并成输出文件中的 .init 和 .finit。但是这
两个输出的段中所包含的指令还需要一些辅助的代码来帮助它们启动 (比如计算 GOT 之类的), '于是引入了两个目标文件分别用来帮助实现初始化函数的 crti.o 和 crtn.o'。

与此同时, 为了支持新的库和可执行文件格式, crt0.o 也进行了升级, 变成了 crt1.o。crt0.o 和 crt1.o 之间的区别是 crt0.o 为原始的, 不支持 .init 和 .finit 的启动代码,
而 crt1.o 是改进过后, 支持 .init 和 .finit 的版本。

这一点我们从反汇编 crt1.o 可以看到, 它向 libc 启动函数 __libc_start_main() 传递了两个函数指针 __libc_csu_init 和 __libc_csu_fini, 这两个函数负责调用
_init() 和 _finit()。

为了方便运行库调用, 最终输出文件中的 .init 和 .finit 两个段实际上分别包含的是 _init() 和 _finit() 这两个函数, 我们在关于运行库初始化的部分也会看到这两个函数,并且在
C++ 全局构造和析构的章节中也会分析它们是如何实现全局构造和析构的。

crti.o 和 crtn.o 这两个目标文件中包含的代码实际上是 _init() 函数和 _finit() 函数的开始和结尾部分, 当这两个文件和其他目标文件顺序链接起来以后, 刚好形成两个完整的函数
_init() 和 _finit()。


> objdump -dr crti.o 

crti.o:     文件格式 elf64-x86-64


Disassembly of section .init:

0000000000000000 <_init>:
   0:	f3 0f 1e fa          	endbr64 
   4:	48 83 ec 08          	sub    $0x8,%rsp
   8:	48 8b 05 00 00 00 00 	mov    0x0(%rip),%rax        # f <_init+0xf>
			b: R_X86_64_REX_GOTPCRELX	__gmon_start__-0x4
   f:	48 85 c0             	test   %rax,%rax
  12:	74 02                	je     16 <_init+0x16>
  14:	ff d0                	callq  *%rax

Disassembly of section .fini:

0000000000000000 <_fini>:
   0:	f3 0f 1e fa          	endbr64 
   4:	48 83 ec 08          	sub    $0x8,%rsp


> objdump -dr crtn.o 

crtn.o:     文件格式 elf64-x86-64


Disassembly of section .init:

0000000000000000 <.init>:
   0:	48 83 c4 08          	add    $0x8,%rsp
   4:	c3                   	retq   

Disassembly of section .fini:

0000000000000000 <.fini>:
   0:	48 83 c4 08          	add    $0x8,%rsp
   4:	c3                   	retq   


'于是在最终链接完成之后, 输出的目标文件中的 .init 段只包含了一个函数 _init(), 这个函数的开始部分来自于 crti.o 的 .init 段, 结束部分来自于 crtn.o 的 .init段'。

为了保证最终输出文件中 .init 和 .finit 的正确性, 我们必须保证在链接时, crti.o 必须在用户目标文件和系统库之前, 而 crtn.o 必须在用户目标文件和系统库之后。链接器的输
入文件顺序一般是:

ld crt1.o crti.o [user_objects] [system_libraries] crtn.o


// !! 提示

在默认情况下, ld 链接器会将 libc、crt1.o 等这些 CRT 和启动文件与程序的模块链接起来, 但是有些时候, 我们可能不需要这些文件, 或者希望使用自己的 libc 和 crt1.o 等启动
文件, 以替代系统默认的文件, 这种情况在嵌入式系统或操作系统内核编译的时候很常见。

'GCC 提高了两个参数 -nostartfile 和 -nostdlib, 分别用来取消默认的启动文件和 C 语言运行库'。

除了全局对象构造和析构之外, .init 和 .finit 还有其他的作用。由于它们的特殊性 (在 main 之前/后执行), 一些用户监控程序性能、调试等工具经常利用它们进行一些初始化和反初
始化的工作。

当然我们也可以使用 __attribute__((section(“.init”))) 将函数放到 .init 段里面, 但是要注意的是普通函数放在 .init 是会破坏它们的结构的, 因为函数的返回指令使得
_init() 函数会提前返回, 必须使用汇编指令, 不能让编译器产生 ret 指令。


// !! GCC 平台相关目标文件

就这样, 我们在链接时碰到过的诸多输入文件中, 已经解决了 crt1.o、crti.o 和 crtn.o, 剩下的还有几个 crtbeginT.o、libgcc.a、libgcc_eh.a、crtend.o。

严格来讲, 这几个文件实际上不属于 glibc, 它们是 GCC 的一部分, 它们都位于 GCC 的安装目录下:

> /usr/lib/gcc/x86_64-linux-gnu/9

首先是 crtbeginT.o 及 crtend.o, 这两个文件是真正用于实现 C++ 全局构造和析构的目标文件。

那么为什么已经有了 crti.o 和 crtn.o 之后, 还需要这两个文件呢? 我们知道, C++ 这样的语言的实现是跟编译器密切相关的, 而 glibc 只是一个 C 语言运行库, 它对 C++ 的实现
并不了解。而 'GCC 是 C++ 的真正实现者, 它对 C++ 的全局构造和析构了如指掌'。

'crtbeginT.o 和 crtend.o 来配合 glibc 实现 C++ 的全局构造和析构'。

事实上是 crti.o 和 crtn.o 中的 .init 和 .finit 提供一个在 main() 之前和之后运行代码的机制, 而真正全局构造和析构则由 crtbeginT.o 和 crtend.o 来实现。


由于 GCC 支持诸多平台, 能够正确处理不同平台之间的差异性也是 GCC 的任务之一。比如有些 32 位平台不支持 64 位的 long long 类型的运算, 编译器不能够直接产生相应的
CPU 指令, 而是需要一些辅助的例程来帮助实现计算。

ibgcc.a 里面包含的就是这种类似的函数, 这些函数主要包括整数运算、浮点数运算 (不同的 CPU 对浮点数的运算方法很不相同)等, 而 libgcc_eh.a 则包含了支持 C++ 的异常处
理 (Exception Handling) 的平台相关函数。






