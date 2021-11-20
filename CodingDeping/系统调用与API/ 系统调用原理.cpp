// !!  系统调用原理

// !! 特权级与中断

现代的 CPU 常常可以在多种截然不同的特权级别下执行指令，在现代操作系统中，通常也据此有两种特权级别，分别为用户模式(User Mode)和内核模式(Kernel Mode)
，也被称为用户态和内核态。'由于有多种特权模式的存在，操作系统就可以让不同的代码运行在不同的模式上，以限制它们的权力，提供稳定性和安全性'。系统调用是运行
在内核态的，而应用程序基本都是运行在用户态的。

用户态的程序如何运行内核态的代码呢？ 

'操作系统一般是通过中断(Interrupt)来从用户态切换到内核态'。

什么是中断呢？ 

'中断是一个硬件或软件发出的请求，要求CPU暂停当前的工作转手去处理更加重要的事情'。

中断一般具有两个属性，一个称为中断号(从0开始)，一个称为中断处理程序(Interrupt Service Routine, ISR)。

不同的中断具有不同的中断号而同时一个中断处理程序一一对应一个中断号。

在内核中，有一个数组称为'中断向量表(Interrupt Vector Table)'，这个数组的第 n 项包含了指向第 n 号中断的中断处理程序的指针。当中断到来时，CPU 会暂停
当前执行的代码，根据中断的中断号，在中断向量表中找到对应的中断处理程序，并调用它。中断处理程序执行完成之后，CPU会继续执行之前的代码。

通常意义上，中断有两种类型:                              

1. 一种称为硬件中断，这种中断来自于硬件的异常或其它事件的发生，如电源掉电、磁盘被按下等

2. 另一种称为软件中断，软件中断通常是一条指令(i386下是int)，带有一个参数记录中断号，使用这条指定用户可以手动触发某个中断并执行其中断处理程序

由于中断号是很有限的，操作系统不会舍得用一个中断号来对应一个系统调用，而更倾向于用一个或少数几个中断号来对应所有的系统调用。


// !! 基于 int 的 Linux 的经典系统调用实现


1. 触发中断: 首先当程序在代码里调用一个系统调用时，是以一个函数的形式调用的，例如：程序调用 fork：

int main(int argc, char ** argv) 
{
    fork();
}

fork 函数是对系统调用 fork 的封装，可以用下列宏来定义它：

_syscall0(pid_t,fork);

_syscall0 是一个宏函数，用于定义一个没有参数的系统调用的封装。它的第一个参数为这个系统调用的返回值类型，这里为 pid_t 是一个 Linux 自定义类型，
代表进程的 id。_syscall0 第二个参数为系统调用的名称， _syscall0 展开之后会形参一个和系统调用名称同名的函数。

#define _syscall0(type,name)

type name(void) 
{
    long _res;
    __asm__ volatile("int $0x80"
    : "=a"(__res)
    : "0"(___NR_##name));
    __syscall_return(type,__res);
}

对于 _syscall0(pid_t,fork) 上面的宏定义展开为：

pid_t fork(void) 
{
    long _res;
    __asm__ volatile("int $0x80"
    : "=a"(__res)
    : "0"(__NR_fork));
    __syscall_return(pid_t,__res);
}

1. __asm__ 为 GCC 的关键字，表示接下来要嵌入汇编代码。volatile 告诉 GCC 不要对这段代码做任何优化

2. __asm__ 第一个参数是一个字符串，代码汇编代码文本。 int $0x80 就是要调用 0x80 号中断

3. "=a"(__res) 表示用 eas 输出返回数据并存储在 __res

4. "0"(__NR_fork) 0 指示由编译器选择和输出相同的寄存器（即 eax ）来传递参数。__NR_fork 为一个宏定义，表示系统调用的
    调用号。

    对于 x86 体系结构：
    #define __NR_exit 1
    #define __NR_fork 2
    #define __NR_read 3


而 __syscall_return 是另外一个宏，定义如下：

#define __syscall_return(type,res)

do
{
    if((unsigned long)res >= (unsigned long)(-125))
    {
        errno = -res;
        res = -1;
    }
    return (type)(res);
}while(0)


这个宏用于检查系统调用的返回值，并把它相应的转换为 C 语言的 errno 错误码。在 Linux 中，系统调用使用返回值传递错误码，如果返回值为
负数，那么表明调用失败。而 在 C 语言里，大多数使用 -1 表示调用失败，而将错误信息存储在 errno 中。


2. 切换堆栈：在实际执行中断向量表的第 0x80 号元素所对应的函数之前，CPU 首先还要进行栈的切换。在 Linux 中，用户态和内核态使用的是不同的栈，两者各自负
   责各自的函数调用，互不干扰。但在应用程序调用 0x80 号中断时，程序的执行流程从用户态切换到内核态，这时程序的当前栈必须也相应地从用户栈切换到内核栈。
   从中断处理函数中返回时，程序的当前栈还要从内核栈切换回用户栈。

3. 中断处理程序：在int指令合理地切换了栈之后，程序的流程就切换到了中断向量表中记录的 0x80 号中断处理程序。内核里的系统调用函数往往以 sys_ 加上系统调
   用函数名来命名，例如 sys_fork、sys_open 等。


// !! Linux 的新型系统调用机制

使用 ldd 来获取一个可执行文件 ls 的共享库的依赖情况

» ldd  /bin/ls                                                                                     
	linux-vdso.so.1 (0x00007ffe4f3ba000)
	libselinux.so.1 => /lib/x86_64-linux-gnu/libselinux.so.1 (0x00007f66c2a5a000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f66c2868000)
	libpcre2-8.so.0 => /lib/x86_64-linux-gnu/libpcre2-8.so.0 (0x00007f66c27d8000)
	libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f66c27d2000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f66c2ac5000)
	libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f66c27af000)
---------------------------------------------------------------------------------------------------------------------


可以看到 linux-vdso.so.1 没有与任何实际的文件相对应，'这个共享库是 Linux 用于支持新型系统调用的”虚拟”共享库'。linux-vdso.so.1 并不存在实际的文件，
它只是操作系统生成的一个虚拟动态共享库(Virtual Dynamic Shared Library, VDSO)。可以通过 Linux 的 proc 文件系统来查看一个可执行程序的内存映像。

cat  /proc/self/maps

7fc43fdba000-7fc43fdbb000 rw-p 00000000 00:00 0 
7ffe91327000-7ffe91348000 rw-p 00000000 00:00 0                          [stack]
7ffe913cd000-7ffe913d1000 r--p 00000000 00:00 0                          [vvar]
7ffe913d1000-7ffe913d3000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0                  [vsyscall]


我们可以看见地址 7ffe913d1000 到  7ffe913d3000 的地方被映射了vdso，也就是 linux-vdso.so.1






























