// !! 7.6　动态链接的步骤和实现

// !! 7.6.1　动态链接器自举

我们知道动态链接器本身也是一个共享对象, 但是事实上它有一些特殊性。对于普通共享对象文件来说, 它的重定位工作由动态链接器来完成; 它也可以依赖于其他共享对象, 其中的被依赖的共
享对象由动态链接器负责链接和装载。

'可是对于动态链接器本身来说, 它的重定位工作由谁来完成? 它是否可以依赖于其他的共享对象'?

这是一个"鸡生蛋,蛋生鸡"的问题, 为了解决这种无休止的循环, 动态链接器这个"鸡"必须有些特殊性。

首先是, '动态链接器本身不可以依赖于其他任何共享对象'; 其次是动态链接器本身所需要的全局和静态变量的重定位工作由它本身完成。

第一个条件我们可以人为地控制, 在编写动态链接器时保证不使用任何系统库、运行库; 对于第二个条件,'动态链接器必须在启动时有一段非常精巧的代码可以完成这项艰巨的工作而同时又不
能用到全局和静态变量'。

'这种具有一定限制条件的启动代码往往被称为自举 (Bootstrap)'。

'动态链接器入口地址即是自举代码的入口', 当操作系统将进程控制权交给动态链接器时, 动态链接器的自举代码即开始执行。

自举代码首先会找到它自己的 GOT。而 GOT 的第一个入口保存的即是 .dynamic 段的偏移地址, 由此找到了动态连接器本身的 .dynamic 段。通过 .dynamic 中的信息, 自举代码便可
以获得动态链接器本身的重定位表和符号表等, 从而得到动态链接器本身的重定位入口, 先将它们全部重定位。'从这一步开始, 动态链接器代码中才可以开始使用自己的全局变量和静态变量'。

实际上在动态链接器的自举代码中, 除了不可以使用全局变量和静态变量之外, 甚至不能调用函数, 即动态链接器本身的函数也不能调用。

这是为什么呢? 其实我们在前面分析地址无关代码时已经提到过, 实际上使用 PIC 模式编译的共享对象, 对于模块内部的函数调用也是采用跟模块外部函数调用一样的方式, 即使用 GOT/PLT
的方式, 所以在 GOT/PLT 没有被重定位之前, 自举代码不可以使用任何全局变量, 也不可以调用函数。


// !! 7.6.2　装载共享对象

完成基本自举以后, 动态链接器将可执行文件和链接器本身的符号表都合并到一个符号表当中, 我们可以称它为全局符号表 (Global Symbol Table)。

然后链接器开始寻找可执行文件所依赖的共享对象, '.dynamic 段中有一种类型的入口是 DT_NEEDED, 它所指出的是该可执行文件(或共享对象)所依赖的共享对象'。
由此, 链接器可以列出可执行文件所需要的所有共享对象, 并将这些共享对象的名字放入到一个装载集合中。然后链接器开始从集合里取一个所需要的共享对象的名字, 找到相应的文件后打
开该文件, 读取相应的 ELF 文件头和 .dynamic 段, 然后将它相应的代码段和数据段映射到进程空间中。

如果这个 ELF 共享对象还依赖于其他共享对象, 那么将所依赖的共享对象的名字放到装载集合中。如此循环直到所有依赖的共享对象都被装载进来为止, 当然链接器可以有不同的装载顺序,
'如果我们把依赖关系看作一个图的话, 那么这个装载过程就是一个图的遍历过程, 链接器可能会使用深度优先或者广度优先或者其他的顺序来遍历整个图, 这取决于链接器, 比较常见的算法
一般都是广度优先的'。


'当一个新的共享对象被装载进来的时候, 它的符号表会被合并到全局符号表中, 所以当所有的共享对象都被装载进来的时候, 全局符号表里面将包含进程中所有的动态链接所需要的符号'。

// !! 符号的优先级

在动态链接器按照各个模块之间的依赖关系, 对它们进行装载并且将它们的符号并入到全局符号表时, 会不会有这么一种情况发生, 那就是有可能两个不同的模块定义了同一个符号?

让我们来看看这样一个例子: 共有 4 个共享对象 a1.so、a2.so、b1.so 和 b2.so, 它们的源代码文件分别为 a1.c、a2.c、b1.c 和 b2.c:

#include <stdio.h>

void a() {
    printf("a1.c\n");
}

#include <stdio.h>

void a() {
    printf("a2.c\n");
}

void a();
void b1() {
    a();
}

void a();

void b2() {
    a();
}

可以看到 a1.c 和 a2.c 中都定义了名字为 a 的函数。那么由于 b1.c 和 b2.c 都用到了外部函数 a, 但由于源代码中没有指定依赖于哪个共享对象中的函数 a, 所以我们在编译时指
定依赖关系。我们假设 b1.so 依赖于 a1.so, b2.so 依赖于 a2.so, 将 b1.so 与 a1.so 进行链接, b2.so 与 a2.so 进行链接:

> gcc -fPIC -shared a1.c -o a1.so -Xlinker -rpath ./
> gcc -fPIC -shared a2.c -o a2.so -Xlinker -rpath ./
> gcc -fPIC -shared b1.c a1.so -o b1.so -Xlinker -rpath ./
> gcc -fPIC -shared b2.c a2.so -o b2.so -Xlinker -rpath ./
>
> ldd b1.so
	linux-vdso.so.1 (0x00007fffa8df2000)
	a1.so => ./a1.so (0x00007fb572cd2000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fb572aca000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fb572cde000)


>ldd b2.so
	linux-vdso.so.1 (0x00007fff42dea000)
	a2.so => ./a2.so (0x00007f1d50190000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f1d4ff88000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f1d5019c000)


那么当有程序同时使用 b1.c 中的函数 b1 和 b2.c 中的函数 b2 会怎么样呢? 比如有程序 main.c:

#include <stdio.h>

void b1();
void b2();

int main() {
    b1();
    b2();
    return 0;
}

然后我们将 main.c 编译成可执行文件并且运行:

> gcc main.c b1.so b2.so -o main -Xlinker -rpath ./
> ./main 

a1.c
a1.c

'-XLinker -rpath ./ 表示链接器在当前路径寻找共享对象, 否则链接器会报无法找到 a1.so 和 a2.so 错误'

很明显, main 依赖于 b1.so 和 b2.so; b1.so 依赖于 a1.so; b2.so 依赖于 a2.so, 所以当动态链接器对 main 程序进行动态链接时, b1.so、b2.so、a1.so 和 a2.so 都会
被装载到进程的地址空间, 并且它们中的符号都会被并入到全局符号表, 通过查看进程的地址空间信息可看到:

./main &
[1] 362832
a1.c                                                                                                                        
a1.c
➜  7 动态链接 git:(main) ✗ cat /proc/362832/maps 
559f5c471000-559f5c472000 r--p 00000000 08:05 2491581                    /main
559f5c472000-559f5c473000 r-xp 00001000 08:05 2491581                    /main
559f5c473000-559f5c474000 r--p 00002000 08:05 2491581                    /main
559f5c474000-559f5c475000 r--p 00002000 08:05 2491581                    /main
559f5c475000-559f5c476000 rw-p 00003000 08:05 2491581                    /main
559f5d105000-559f5d126000 rw-p 00000000 00:00 0                          [heap]
7f33e71a5000-7f33e71a7000 rw-p 00000000 00:00 0 
7f33e71a7000-7f33e71a8000 r--p 00000000 08:05 2491567                    /a2.so
7f33e71a8000-7f33e71a9000 r-xp 00001000 08:05 2491567                    /a2.so
7f33e71a9000-7f33e71aa000 r--p 00002000 08:05 2491567                    /a2.so
7f33e71aa000-7f33e71ab000 r--p 00002000 08:05 2491567                    /a2.so
7f33e71ab000-7f33e71ac000 rw-p 00003000 08:05 2491567                    /a2.so
7f33e71ac000-7f33e71ad000 r--p 00000000 08:05 2491587                    /a1.so
7f33e71ad000-7f33e71ae000 r-xp 00001000 08:05 2491587                    /a1.so
7f33e71ae000-7f33e71af000 r--p 00002000 08:05 2491587                    /a1.so
7f33e71af000-7f33e71b0000 r--p 00002000 08:05 2491587                    /a1.so
7f33e71b0000-7f33e71b1000 rw-p 00003000 08:05 2491587                    /a1.so
7f33e71b1000-7f33e71d3000 r--p 00000000 08:05 2631845                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f33e71d3000-7f33e734b000 r-xp 00022000 08:05 2631845                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f33e734b000-7f33e7399000 r--p 0019a000 08:05 2631845                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f33e7399000-7f33e739d000 r--p 001e7000 08:05 2631845                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f33e739d000-7f33e739f000 rw-p 001eb000 08:05 2631845                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f33e739f000-7f33e73a3000 rw-p 00000000 00:00 0 
7f33e73b9000-7f33e73ba000 r--p 00000000 08:05 2491574                    /b2.so
7f33e73ba000-7f33e73bb000 r-xp 00001000 08:05 2491574                    /b2.so
7f33e73bb000-7f33e73bc000 r--p 00002000 08:05 2491574                    /b2.so
7f33e73bc000-7f33e73bd000 r--p 00002000 08:05 2491574                    /b2.so
7f33e73bd000-7f33e73be000 rw-p 00003000 08:05 2491574                    /b2.so
7f33e73be000-7f33e73bf000 r--p 00000000 08:05 2491570                    /b1.so
7f33e73bf000-7f33e73c0000 r-xp 00001000 08:05 2491570                    /b1.so
7f33e73c0000-7f33e73c1000 r--p 00002000 08:05 2491570                    /b1.so
7f33e73c1000-7f33e73c2000 r--p 00002000 08:05 2491570                    /b1.so
7f33e73c2000-7f33e73c3000 rw-p 00003000 08:05 2491570                    /b1.so
7f33e73c3000-7f33e73c5000 rw-p 00000000 00:00 0 
7f33e73c5000-7f33e73c6000 r--p 00000000 08:05 2631841                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f33e73c6000-7f33e73e9000 r-xp 00001000 08:05 2631841                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f33e73e9000-7f33e73f1000 r--p 00024000 08:05 2631841                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f33e73f2000-7f33e73f3000 r--p 0002c000 08:05 2631841                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f33e73f3000-7f33e73f4000 rw-p 0002d000 08:05 2631841                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f33e73f4000-7f33e73f5000 rw-p 00000000 00:00 0 
7ffd9e217000-7ffd9e238000 rw-p 00000000 00:00 0                          [stack]
7ffd9e293000-7ffd9e297000 r--p 00000000 00:00 0                          [vvar]
7ffd9e297000-7ffd9e299000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0                  [vsyscall]


这 4 个共享对象的确都被装载进来了, 那 a1.so 中的函数 a 和 a2.so 中的函数 a 是不是冲突了呢? 为什么 main 的输出结果是两个 a1.c 呢?
也就是说 a2.so 中的函数 a 似乎被忽略了。

'这种一个共享对象里面的全局符号被另一个共享对象的同名全局符号覆盖的现象又被称为共享对象全局符号介入 (Global Symbol Interpose)'。

'关于全局符号介入这个问题, 实际上 Linux 下的动态链接器是这样处理的: 它定义了一个规则, 那就是当一个符号需要被加入全局符号表时, 如果相同的符号名已经存在, 则后加入的符
号被忽略'。

从动态链接器的装载顺序可以看到, 它是按照广度优先的顺序进行装载的, 首先是 main, 然后是 b1.so、b2.so、a1.so, 最后是 a2.so。当 a2.so 中的函数 a 要被加入全局符号表时,
先前装载 a1.so 时, a1.so 中的函数 a 已经存在于全局符号表, 那么 a2.so 中的函数 a 只能被忽略。

所以整个进程中, 所有对于符合 a 的引用都会被解析到 a1.so 中的函数 a, 这也是为什么 main 打印出的结果是两个 a1.c 而不是理想中的 a1.c 和 a2.c。

'由于存在这种重名符号被直接忽略的问题, 当程序使用大量共享对象时应该非常小心符号的重名问题', 如果两个符号重名又执行不同的功能, 那么程序运行时可能会将所有该符号名的引用解
析到第一个被加入全局符号表的使用该符号名的符号, 从而导致程序莫名其妙的错误。


// !! 全局符号介入与地址无关代码

前面介绍地址无关代码时, 对于第一类模块内部调用或跳转的处理时, 我们简单地将其当作是相对地址调用/跳转。但实际上这个问题比想象中要复杂, 结合全局符号介入, 关于调用方式的分类
的解释会更加清楚。

还是拿前面 pic.c 的例子来看, 由于可能存在全局符号介入的问题, foo 函数对于 bar 的调用不能够采用第一类模块内部调用的方法, 因为一旦 bar 函数由于全局符号介入被其他模块中
的同名函数覆盖, 那么 foo 如果采用相对地址调用的话, 那个相对地址部分就需要重定位, 这又与共享对象的地址无关性矛盾。

'所以对于 bar() 函数的调用, 编译器只能采用第三种, 即当作模块外部符号处理, bar() 函数被覆盖, 动态链接器只需要重定位 .got.plt, 不影响共享对象的代码段'。

'为了提高模块内部函数调用的效率, 有一个办法是把 bar() 函数变成编译单元私有函数, 即使用 static 关键字定义 bar() 函数', 这种情况下, 编译器要确定 bar() 函数不被其他模
块覆盖, 就可以使用第一类的方法, 即模块内部调用指令, 可以加快函数的调用速度。


// !! 7.6.3　重定位和初始化

当上面的步骤完成之后, '链接器开始重新遍历可执行文件和每个共享对象的重定位表, 将它们的 GOT/PLT 中的每个需要重定位的位置进行修正'。因为此时动态链接器已经拥有了进程的全局
符号表, 所以这个修正过程也显得比较容易。

重定位完成之后, 如果某个共享对象有 .init 段, 那么动态链接器会执行 .init 段中的代码, 用以实现共享对象特有的初始化过程, 比如最常见的, 共享对象中的 C++ 的全局/静态对象
的构造就需要通过 .init 来初始化。

相应地, 共享对象中还可能有 .finit 段, 当进程退出时会执行 .finit 段中的代码, 可以用来实现类似 C++ 全局对象析构之类的操作。

当完成了重定位和初始化之后, 所有的准备工作就宣告完成了, 所需要的共享对象也都已经装载并且链接完成了, 这时候动态链接器就如释重负, 将进程的控制权转交给程序的入口并且开
始执行。


// !! 7.6.4 Linux动态链接器实现

对于静态链接的可执行文件来说, 程序的入口就是 ELF 文件头里面的 e_entry 指定的入口; 对于动态链接的可执行文件来说, 如果这时候把控制权交给 e_entry 指定的入口地址, 那么肯
定是不行的, 因为可执行文件所依赖的共享库还没有被装载, 也没有进行动态链接。所以对于动态链接的可执行文件, 内核会分析它的动态链接器地址 (在 .interp 段), 将动态链接器映射
至进程地址空间, 然后把控制权交给动态链接器。

Linux 动态链接器是个很有意思的东西, 它本身是一个共享对象, 它的路径是 /lib/ld-linux.so.2, 这实际上是个软链接, 它指向 /lib/ld-x.y.z.so, 这个才是真正的动态连接器文
件。共享对象其实也是 ELF 文件, 它也有跟可执行文件一样的 ELF 文件头 (包括e_entry、段表等)。'动态链接器是个非常特殊的共享对象, 它不仅是个共享对象, 还是个可执行的程序',
可以直接在命令行下面运行:

./ld-linux-x86-64.so.2 
Usage: ld.so [OPTION]... EXECUTABLE-FILE [ARGS-FOR-PROGRAM...]
You have invoked `ld.so', the helper program for shared library executables.
This program usually lives in the file `/lib/ld.so', and special directives
in executable files using ELF shared libraries tell the system's' program
loader to load the helper program from this file.  This helper program loads
the shared libraries needed by the program executable, prepares the program
to run, and runs it.  You may invoke this helper program directly from the
command line to load and run an ELF executable file; this is like executing
that file itself, but always uses this helper program from the file you
specified, instead of the helper program file specified in the executable
file you run.  This is mostly of use for maintainers to test new versions
of this helper program; chances are you did not intend to run this program.

  --list                list all dependencies and how they are resolved
  --verify              verify that given object really is a dynamically linked
			object we can handle
  --inhibit-cache       Do not use /etc/ld.so.cache
  --library-path PATH   use given PATH instead of content of the environment
			variable LD_LIBRARY_PATH
  --inhibit-rpath LIST  ignore RUNPATH and RPATH information in object names
			in LIST
  --audit LIST          use objects named in LIST as auditors
  --preload LIST        preload objects named in LIST


'其实 Linux 的内核在执行 execve() 时不关心目标 ELF 文件是否可执行 (文件头 e_type 是 ET_EXEC 还是 ET_DYN)', 它只是简单按照程序头表里面的描述对文件进行装载然后把
控制权转交给 ELF 入口地址 (没有 .interp 就是 ELF 文件的 e_entry; 如果有 .interp 的话就是动态链接器的 e_entry)。

这样我们就很好理解为什么动态链接器本身可以作为可执行程序运行, 这也从一个侧面证明了共享库和可执行文件实际上没什么区别, 除了文件头的标志位和扩展名有所不同之外,其他都是一样
的。

Linux 的 ELF 动态链接器是 Glibc 的一部分, 它的源代码位于 Glibc 的源代码的 elf 目录下面, 它的实际入口地址位于 sys-deps/i386/dl-manchine.h 中的 _start.

_start 调用位于 elf/rtld.c 的 _dl_start() 函数。_dl_start() 函数首先对 ld.so (以下简称 ld-x.y.z.so 为 ld.so) 进行重定位, 因为 ld.so 自己就是动态链接器, 没
有人帮它做重定位工作, 所以它只好自己来, 美其名曰"自举"。

完成自举之后就可以调用其他函数并访问全局变量了。调用 _dl_start_final, 收集一些基本的运行数值, 进入 _dl_sysdep_start, 这个函数进行一些平台相关的处理之后就进入了 
_dl_main, 这就是真正意义上的动态链接器的主函数了。


// !! 关于动态链接器的实现的几个问题还是很值得思考的

1. 动态链接器本身是动态链接的还是静态链接的? 

动态链接器本身应该是静态链接的, 它不能依赖于其他共享对象, 动态链接器本身是用来帮助其他 ELF 文件解决共享对象依赖问题的, 如果它也依赖于其他共享对象, 那么谁来帮它解决依赖
问题? 所以它本身必须不依赖于其他共享对象。这一点可以使用 ldd 来判断:

> ldd ld-linux-x86-64.so.2 
	statically linked


2. 动态链接器本身必须是 PIC 的吗?

是不是 PIC 对于动态链接器来说并不关键, 动态链接器可以是 PIC 的也可以不是, 但'往往使用 PIC 会更加简单一些'。一方面, 如果不是 PIC 的话, 会使得代码段无法共享,浪费内存;
另一方面也会使 ld.so 本身初始化更加复杂, 因为自举时还需要对代码段进行重定位。实际上的 ld-linux.so.2 是 PIC 的。





