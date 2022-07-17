
如果把一个程序比作一个世界, 那么程序的启动无疑就是"创世"。

// !! 11.1 入口函数和程序初始化

// !! 11.1.1　程序从 main 开始吗?

正如基督徒认为世界的诞生起于 7 天创世一样, 任何一个合格的 C/C++ 程序员都应该知道一个事实: '程序从 main 函数开始'。但是事情的真相真是如此吗? 如果你善于观察, 就会发
现当程序执行到 main 函数的第一行时, 很多事情都已经完成了:

【铁证1】下面是一段 C 语言代码:

#include <stdio.h>
#include <stdlib.h>

int a = 3;

int main(int argc, char** argv) {
    int * p = (int *)malloc(sizeof(int));
    scanf("%d", p);
    printf("%d", a + *p);
    free(p);
    return 0
}

从代码中我们可以看到, 在程序刚刚执行到 main 的时候, 全局变量的初始化过程已经结束了 ( a 的值已经确定), main 函数的两个参数 (argc 和 argv) 也被正确传了进来。
此外, 在你不知道的时候, 堆和栈的初始化悄悄地完成了, 一些系统 I/O 也被初始化了, 因此可以放心地使用 printf 和 malloc。

【铁证2】而在 C++ 里, main 之前能够执行的代码还会更多, 例如如下代码:

#include <string>

using namespace std;

string v;

double foo() {
    return 1.0;
}

double g = foo();

int main(){
    return 0;
}

在这里, 对象 v 的构造函数, 以及用于初始化全局变量 g 的函数 foo 都会在 main 之前调用。

【铁证3】atexit 也是一个特殊的函数。atexit 接受一个函数指针作为参数, 并保证在程序正常退出 (指从 main 里返回或调用 exit 函数)时, 这个函数指针指向的函数会被调用。

void foo(void) {
     printf("bye!\n");
}

int main() {
    atexit(&foo);
     printf("end of main\n");
}

用 atexit 函数注册的函数的调用时机是在 main 结束之后, 因此这段代码的输出是:

end of main
bye!

所有这些事实都在为 "main 创论"提供不利的证据: 操作系统装载程序之后, 首先运行的代码并不是 main 的第一行, 而是某些别的代码, '这些代码负责准备好 main 函数执行所需要的环
境, 并且负责调用 main 函数', 这时候你才可以在 main 函数里放心大胆地写各种代码: 申请内存、使用系统调用、触发异常、访问 I/O。在 main 返回之后, 它会记录 main 函数的返
回值, 调用 atexit 注册的函数, 然后结束进程。


运行这些代码的函数称为入口函数或入口点 (Entry Point), 视平台的不同而有不同的名字。'程序的入口点实际上是一个程序的初始化和结束部分, 它往往是运行库的一部分'。

一个典型的程序运行步骤大致如下:

1. 操作系统在创建进程后, 把控制权交到了程序的入口, 这个入口往往是运行库中的某个入口函数

2. 入口函数对运行库和程序运行环境进行初始化, 包括堆、I/O、线程、全局变量构造, 等等

3. 入口函数在完成初始化之后, 调用 main 函数, 正式开始执行程序主体部分

4. main 函数执行完毕以后, 返回到入口函数, 入口函数进行清理工作, 包括全局变量析构、堆销毁、关闭 I/O 等, 然后进行系统调用结束进程


// !! 11.1.2　入口函数如何实现


// !! GLIBC 入口函数

glibc 的启动过程在不同的情况下差别很大, 比如静态的 glibc 和动态的 glibc 的差别, glibc 用于可执行文件和用于共享库的差别, 这样的差别可以组合出 4 种情况, 这里只选取
最简单的静态 glibc 用于可执行文件的时候作为例子


glibc 的程序入口为 _start (这个入口是由 ld 链接器默认的链接脚本所指定的, 我们也可以通过相关参数设定自己的入口)。_start 由汇编实现, 并且和平台相关, 下面可以单独看
i386 的 _start 实现:

libc\sysdeps\i386\elf\Start.S:
_start:
 xorl %ebp, %ebp
 popl %esi
 movl %esp, %ecx

 pushl %esp
 pushl %edx
 pushl $__libc_csu_fini
 pushl $__libc_csu_init
 pushl %ecx
 pushl %esi
 pushl main
 call __libc_start_main

 hlt

这里省略了一些不重要的代码, 可以看到 _start 函数最终调用了名为 __lib_start_main 的函数。加粗部分的代码是对该函数的完整调用过程, 其中开始的 7 个压栈指令用于给函数传递
参数。

在最开始的地方还有 3 条指令, 它们的作用分别为:

1. xor %ebp, %ebp: 这其实是让 ebp 寄存器清零。xor 的用处是把后面的两个操作数异或, 结果存储在第一个操作数里。这样做的目的表明当前是程序的最外层函数。
   ebp 设为 0 正好可以体现出这个最外层函数的尊贵地位

2. pop %esi 及 mov %esp, %ecx: 在调用 _start 前, 装载器会把用户的参数和环境变量压入栈中, 按照其压栈的方法, 实际上栈顶的元素是 argc, 而接着其下就是 argv 和环境变
   量的数组。


综合以上分析, 我们可以把 _start 改写为一段更具有可读性的伪代码:

void _start() {
    %ebp = 0;
    int argc = pop from stack;
    char** argv = top of stack;
    __libc_start_main( main, argc, argv, __libc_csu_init,  __libc_csu_fini, edx, top of stack );

}

其中 argv 除了指向参数表外, 还隐含紧接着环境变量表。这个环境变量表要在 __libc_start_main 里从 argv 内提取出来。


// !! 环境变量

环境变量是存在于系统中的一些公用数据, 任何程序都可以访问。通常来说, 环境变量存储的都是一些系统的公共信息, 例如系统搜索路径, 当前 OS 版本等。环境变量的格式为
key=value 的字符串, C 语言里可以使用 getenv 这个函数来获取环境变量信息。


查阅当前的环境变量, 在 Linux 下, 直接在命令行里输入 export 即可。

实际执行代码的函数是 __libc_start_main, 由于代码很长, 下面我们一段一段地看:

_start -> __libc_start_main:

int __libc_start_main (int (*main) (int, char **, char **), int argc, char * __unbounded *__unbounded ubp_av, 
            __typeof (main) init,
            void (*fini) (void),
            void (*rtld_fini) (void), 
            void * __unbounded stack_end) {
                #if __BOUNDED_POINTERS__
                 char **argv;
                 #else
                 # define argv ubp_av
                 #endif
                  int result;
                  ....
            }


这是 __libc_start_main 的函数头部, 可见和 _start 函数里的调用一致, 一共有 7 个参数, 其中 main 由第一个参数传入, 紧接着是 argc 和 argv。除了 main 的函数指针
之外, 外部还要传入 3 个函数指针, 分别是:

• init: main 调用前的初始化工作

• fini: main 结束后的收尾工作

• rtld_fini: 和动态加载有关的收尾工作, rtld 是 runtime loader 的缩写

最后的 stack_end 标明了栈底的地址, 即最高的栈地址。


接下来的代码如下:

char** ubp_ev = &ubp_av[argc + 1];
INIT_ARGV_and_ENVIRON;
__libc_stack_end = stack_end;

INIT_ARGV_and_ENVIRON 这个宏定义于 libc/sysdeps/generic/bp-start.h, 展开后本段代码变为:

char** ubp_ev = &ubp_av[argc + 1];
_environ = ubp_ev;
__libc_stack_end = stack_end;

图 11-2 实际上就是我们根据从 _start 源代码分析得到的栈布局, 让 __environ 指针指向原来紧跟在 argv 数组之后的环境变量数组。

接下来有另一个宏:

DL_SYSDEP_OSCHECK (__libc_fatal);

这是用来检查操作系统的版本, 宏的具体内容就不列出了。

接下来的代码颇为繁杂, 我们过滤掉大量信息之后, 将一些关键的函数调用列出:

__pthread_initialize_minimal();
__cxa_atexit(rtld_fini, NULL, NULL);
__libc_init_first (argc, argv, __environ);
__cxa_atexit(fini, NULL, NULL);
(*init)(argc, argv, __environ);


这一部分进行了一连串的函数调用, 注意到 __cxa_atexit 函数是 glibc 的内部函数, 等同于 atexit, 用于将参数指定的函数在 main 结束之后调用。

所以以参数传入的 fini 和 rtld_fini 均是用于 main 结束之后调用的。

在 __libc_start_main 的末尾, 关键的是这两行代码:

 result = main (argc, argv, __environ);
 exit (result);


在最后, main 函数终于被调用, 并退出。然后我们来看看 exit 的实现:


_start -> __libc_start_main -> exit:

void exit(int status) {
    while (__exit_funcs != NULL){
        ...
        __exit_funcs = __exit_funcs->next;
    }
    ...
     _exit (status);
}

其中 __exit_funcs 是存储由 __cxa_atexit 和 atexit 注册的函数的链表, 而这里的这个 while 循环则遍历该链表并逐个调用这些注册的函数, 由于其中琐碎代码过多, 这里就不
具体列出了。


最后的 _exit 函数由汇编实现, 且与平台相关, 下面列出 i386 的实现:

_start -> __libc_start_main -> exit -> _exit:

_exit:

 movl    4(%esp), %ebx
 movl    $__NR_exit, %eax
 int     $0x80
 hlt


可见 _exit 的作用仅仅是调用了 exit 这个系统调用。

也就是说, _exit 调用后, 进程就会直接结束。程序正常结束有两种情况, 一种是 main 函数的正常返回, 一种是程序中用 exit 退出。在 __libc_start_main 里我们可以看到, 即
使 main 返回了, exit 也会被调用。exit 是进程正常退出的必经之路, 因此把调用用 atexit 注册的函数的任务交给 exit 来完成可以说万无一失。


// !! 11.1.3　运行库与 I/O

一个程序的 I/O 指代了程序与外界的交互, 包括文件、管道、网络、命令行、信号等。更广义地讲, I/O 指代任何操作系统理解为"文件"的事务。

'对于一个任意类型的文件, 操作系统会提供一组操作函数, 这包括打开文件、读文件、写文件、移动文件指针等, 相信有编程经验的读者对此都不会陌生'。

有过 C 编程经验的读者应该知道, C 语言文件操作是通过一个 FILE 结构的指针来进行的。使用文件的最简单代码如下:

#include <stdio.h>

int main(int argc, char* argv[]) {
    FILE *f = fopen("test.dat", "wb");
    if(f == NULL){
        return -1;
    }
    fwrite("123", 3, 1, f);
    fclose(f);
    return 0;
}


在操作系统层面上, 文件操作也有类似于 FILE 的一个概念, 在 Linux 里, 这叫做文件描述符 (File Descriptor), 而在 Windows 里, 叫做句柄 (Handle)。
'用户通过某个函数打开文件以获得句柄, 此后用户操纵文件皆通过该句柄进行'。

'设计这么一个句柄的原因在于句柄可以防止用户随意读写操作系统内核的文件对象'。

无论是 Linux 还是 Windows, '文件句柄总是和内核的文件对象相关联的', 但如何关联细节用户并不可见。'内核可以通过句柄来计算出内核里文件对象的地址', 但此能力并不对用户开放。

下面举一个实际的例子, 在 Linux 中, 值为 0、1、2 的 fd 分别代表标准输入、标准输出和标准错误输出。

在程序中打开文件得到的 fd 从 3 开始增长。fd 具体是什么呢? '在内核中, 每一个进程都有一个私有的打开文件表', 这个表是一个指针数组, 每一个元素都指向一个内核的打开文件对象。

而 fd, 就是这个表的下标。'当用户打开一个文件时, 内核会在内部生成一个打开文件对象, 并在这个表里找到一个空项, 让这一项指向生成的打开文件对象, 并返回这一项的下标作为 fd'。

由于这个表处于内核, 并且用户无法访问到, 因此用户即使拥有 fd, 也无法得到打开文件对象的地址, 只能够通过系统提供的函数来操作。


在 C 语言里, 操纵文件的渠道则是 FILE 结构, 不难想象, C 语言中的 FILE 结构必定和 fd 有一对一的关系, 每个 FILE 结构都会记录自己唯一对应的 fd。

FILE、fd、打开文件表和打开文件对象的关系如图 11-4 所示。

图 11-4 中, 内核指针 p 指向该进程的打开文件表, 所以只要有 fd, 就可以用 fd+p 来得到打开文件表的某一项地址。stdin、stdout、stderr 均是 FILE 结构的指针。


在大致了解了 I/O 为何物之后, 我们就能知道 I/O 初始化的职责是什么了。'首先 I/O 初始化函数需要在用户空间中建立 stdin、stdout、stderr 及其对应的 FILE 结构, 使得程序
进入 main 之后可以直接使用 printf、scanf 等函数'。