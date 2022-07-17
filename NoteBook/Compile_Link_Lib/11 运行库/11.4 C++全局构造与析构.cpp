// !! 11.4　C++ 全局构造与析构

'在 C++ 的世界里, 入口函数还肩负着另一个艰巨的使命, 那就是在 main 的前后完成全局变量的构造与析构'。


// !! 11.4.1　glibc 全局构造与析构

在前面介绍 glibc 的启动文件时已经介绍了 .init 和 .finit 段, 我们知道这两个段中的代码最终会被拼成两个函数 _init() 和 _finit(), 这两个函数会先于/后于 main 函数执
行。但是它们具体是在什么时候被执行的呢? 由谁来负责调用它们呢? 它们又是如何进行全局对象的构造和析构的呢?

为了表述方便, 下面使用这样的代码编译出来的可执行文件进行分析:

class HelloWorld {
    public:
     HelloWorld();
     ~HelloWorld();
};

HelloWorld hw;

HelloWorld::HelloWorld() {
    ...
}

HelloWorld::~HelloWorld() {
    ...
}

int main() {
    return 0;
}

为了了解全局对象的构造细节, 对程序的启动过程进行更深一步的研究是必须的。

在本章的第一节里, 由 _start 传递进来的 init 函数指针究竟指向什么? 通过对地址的跟踪, init 实际指向了 __libc_csu_init 函数。这个函数位于 Glibc 源代码目录的
csu\Elf-init.c, 让我们来看看这个函数的定义:

_start -> __libc_start_main -> __libc_csu_init:

void __libc_csu_init (int argc, char **argv, char **envp) {
    ...
    __init();
    const size_t size = __init_array_end -  __init_array_start;
    for (size_t i = 0; i < size; i++) {
         (*__init_array_start [i]) (argc, argv, envp);
    }
}

这段代码调用了 _init 函数。那么 _init() 是什么呢? 是不是想起来前面介绍过的定义在 crti.o 的 _init() 函数呢? 没错, __libc_csu_init 里面调用的正是 .init 段,也就
是说, 用户所有放在 .init 段的代码就将在这里被执行。

看到这里, 似乎我们的线索要断了, 因为 _init 函数的实际内容并不定义在 Glibc 里面, 它是由各个输入目标文件中的 .init 段拼凑而来的。

_init 调用了一个叫做 __do_global_ctors_aux 的函数, 如果你在 glibc 源代码里面查找这个函数是不可能找到它的。因为它并不属于 glibc, 而是来自于 GCC 提供的一个目标文件
crtbegin.o。

'链接器在进行最终链接时, 有一部分目标文件是来自于 GCC, 它们是那些与语言密切相关的支持函数'。很明显, C++ 的全局对象构造是与语言密切相关的, 相应负责构造的函数来自于
GCC 也非常容易理解。

'对于每个编译单元 ((.cpp), GCC 编译器会遍历其中所有的全局对象, 生成一个特殊的函数, 这个特殊函数的作用就是对本编译单元里的所有全局对象进行初始化'。

我们可以通过对本节开头的代码进行反汇编得到一些粗略的信息, 可以看到 GCC 在目标代码中生成了一个名为 _GLOBAL__I_Hw 的函数, 由这个函数负责本编译单元所有的全局\静态对象
的构造和析构, 它的代码可以表示为:

static void GLOBAL__I_Hw(void) {
    Hw::Hw(); // 构造对象
    atexit(__tcf_1); // 一个神秘的函数叫做 __tcf_1 被注册到了 exit
}

GLOBAL__I_Hw 作为特殊的函数当然也享受特殊待遇, '一旦一个目标文件里有这样的函数, 编译器会在这个编译单元产生的目标文件 (.o) 的 .ctors 段里放置一个指针, 这个指针指向的
便是 GLOBAL__I_Hw'。

那么把每个目标文件的全局/静态对象构造的函数地址放在一个特殊的段里面有什么好处呢? 

当然不为别的, 为的是能够让链接器把这些特殊的段收集起来, 收集齐所有的全局构造函数后就可以在初始化的时候进行构造了。

在编译器为每个编译单元生成一份特殊函数之后, 链接器在连接这些目标文件时, 会将同名的段合并在一起, 这样, 每个目标文件的 .ctors 段将会被合并为一个 .ctors 段, 其中的内容是
各个目标文件的 .ctors 段的内存拼接而成。由于每个目标文件的 .ctors 段都只存储了一个指针 (指向该目标文件的全局构造函数), 因此拼接起来的 .ctors 段就成为了一个函数指针数
组, 每一个元素都指向一个目标文件的全局构造函数。'这个指针数组不正是我们想要的全局构造函数的地址列表吗?' 如果能得到这个数组的地址, 岂不是构造的问题就此解决了?

还记得在链接的时候, 各个用户产生的目标文件的前后分别还要链接上一个 crtbegin.o 和 crtend.o 吧? 这两个 glibc 自身的目标文件同样具有 .ctors 段, 在链接的时候, 这两个
文件的 .ctors 段的内容也会被合并到最终的可执行文件中。

那么这两个文件的 .ctors 段里有什么呢?

1. crtbegin.o: 作为所有 .ctors 段的开头部分, crtbegin.o 的 .ctor 段里面存储的是一个 4 字节的字 1(0xFFFFFFFF), 由链接器负责将这个数字改成全局构造函数的数量。然
   后这个段还将起始地址定义成符号 __CTOR_LIST__, 这样实际上 __CTOR_LIST__ 所代表的就是所有 .ctor 段最终合并后的起始地址了

2. crtend.o: 这个文件里面的 .ctors 内容就更简单了, 它的内容就是一个 0, 然后定义了一个符号 __CTOR_END__, 指向 .ctor 段的末尾


链接器在链接用户的目标文件的时候, crtbegin.o 总是处在用户目标文件的前面, 而 crtend.o 则总是处在用户目标文件的后面。例如链接两个用户的目标文件 a.o 和 b.o 时, 实际链
接的目标文件将是 (按顺序) ld crti.o crt-begin.o a.o b.o crtend.o crtn.o。在这里我们忽略 crti.o 和 crtn.o, 因为这两个目标文件和全局构造无关。

在合并 crtbegin.o、用户目标文件和 crtend.o 时, 链接器按顺序拼接这些文件的 .ctors 段, 因此最终形成 .ctors 段的过程将如图 11-10 所示。

在了解了可执行文件的 .ctors 段的结构之后, 再回过头来看 __do_global_ctor_aux 的代码就很容易了。__do_global_ctor_aux 从 __CTOR_LIST__ 的下一个位置开始, 按顺序
执行函数指针, 直到遇上 NULL (__CTOR_END__), 如此每个目标文件的全局构造函数都能被调用。


// !! 【小实验】

在 main 前调用函数:

glibc 的全局构造函数是放置在 .ctors 段里的, 因此如果我们手动在 .ctors 段里添加一些函数指针, 就可以让这些函数在全局构造的时候 (main 之前) 调用:

#include <stdio.h>

void my_init() {
    printf("Hello ");
}

typedef void (*ctor_t)(void);

ctor_t __attribute__((section (".ctors"))) my_init_p = &my_init;

int main() {
    printf("World!\n");
    return 0;
}

> gcc ctorsDemo.cpp 
> ./a.out 
Hello World!

当然, 事实上, gcc 里有更加直接的办法来达到相同的目的, 那就是使用 __attribute__((constructor))

示例如下:

#include <stdio.h>
void my_init(void) __attribute__((constructor));
void my_init(void) {
     printf("Hello ");
}

int main() {
    printf("World!\n");
    return 0;
}


// !! 析构

对于早期的 glibc 和 GCC, 在完成了对象的构造之后, 在程序结束之前, crt 还要进行对象的析构。实际上正常的全局对象析构与前面介绍的构造在过程上是完全类似的, 而且所有的函数、
符号名都一一对应, 比如 .init 变成了 .finit、__do_global_ctor_aux 变成了 __do_global_dtor_aux、 __CTOR_LIST__变成了 __DTOR_LIST__ 等。

__libc_start_main 将 __libc_csu_fini 通过 __cxa_exit() 注册到退出列表中, 这样当进程退出前 exit() 里面就会调用 __libc_csu_fini。


'编译器对每个编译单元的全局对象, 都会生成一个特殊的函数来调用这个编译单元的所有全局对象的析构函数', 它的调用顺序与 GLOBAL__I_Hw() 调用构造函数的顺序刚好相反。

例如对于前面的例子中的代码, 编译器生成的所谓的神秘函数内容大致是:

static void __tcf_1(void) //这个名字由编译器生成
{
     Hw.~HelloWorld();
}

由于全局对象的构建和析构都是由运行库完成的, 于是在程序或共享库中有全局对象时, 记得不能使用 -nonstartfiles 或 -nostdlib 选项, 否则, 构建与析构函数将不能正常执行
(除非你很清楚自己的行为, 并且手工构造和析构全局对象)


// !! Collect2

我们在第2章时曾经碰到过 collect2 这个程序, 在链接时它代替 ld 成为了最终链接器, 一般情况下就可以简单地将它看成 ld。实际上 collect2 是 ld 的一个包装, 它最终还是调
用 ld 完成所有的链接工作.



