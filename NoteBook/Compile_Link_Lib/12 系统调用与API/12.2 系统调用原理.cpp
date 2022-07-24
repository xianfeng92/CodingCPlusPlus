// !! 12.2　系统调用原理

// !! 12.2.1　特权级与中断

'现代的 CPU 常常可以在多种截然不同的特权级别下执行指令',在现代操作系统中, 通常也据此有两种特权级别, 分别为用户模式 (User Mode) 和内核模式 (Kernel Mode), 也被称为
用户态和内核态。

由于有多种特权模式的存在, 操作系统就可以让不同的代码运行在不同的模式上, 以限制它们的权力, 提高稳定性和安全性。普通应用程序运行在用户态的模式下, 诸多操作将受到限制, 这些
操作包括访问硬件设备、开关中断、改变特权模式等。

一般来说, 运行在高特权级的代码将自己降至低特权级是允许的, 但反过来低特权级的代码将自己提升至高特权级则不是轻易就能进行的, 否则特权级的作用就有名无实了。

在将低特权级的环境转为高特权级时, 须要使用一种较为受控和安全的形式, 以防止低特权模式的代码破坏高特权模式代码的执行。

系统调用是运行在内核态的, 而应用程序基本都是运行在用户态的。

'用户态的程序如何运行内核态的代码呢' ?

操作系统一般是通过中断 (Interrupt) 来从用户态切换到内核态。

什么是中断呢?

'中断是一个硬件或软件发出的请求, 要求 CPU 暂停当前的工作转手去处理更加重要的事情'。


举一个例子, 当你在编辑文本文件的时候, 键盘上的键不断地被按下, CPU 如何获知这一点的呢?

一种方法称为轮询 (Poll), 即 CPU 每隔一小段时间（几十到几百毫秒）去询问键盘是否有键被按下, 但除非用户是疯狂打字员, 否则大部分的轮询行为得到的都是“没有键被按下”的回应, 
这样操作就被浪费掉了。

另外一种方法是 CPU 不去理睬键盘, 而当键盘上有键被按下时, 键盘上的芯片发送一个信号给 CPU, CPU 接收到信号之后就知道键盘被按下了, 然后再去询问键盘被按下的键是哪一个。
这样的信号就是一种中断.

中断一般具有两个属性, 一个称为中断号 (从 0 开始), 一个称为中断处理程序 (Interrupt Service Routine,ISR)。不同的中断具有不同的中断号, 而同时一个中断处理程序一一
对应一个中断号。

在内核中, 有一个数组称为中断向量表 (Interrupt Vector Table), 这个数组的第 n 项包含了指向第 n 号中断的中断处理程序的指针。

'当中断到来时, CPU 会暂停当前执行的代码, 根据中断的中断号, 在中断向量表中找到对应的中断处理程序并调用它'。中断处理程序执行完成之后, CPU 会继续执行之前的代码。


一个简单的示意图如图 12-2 所示。



通常意义上, 中断有两种类型, '一种称为硬件中断, 这种中断来自于硬件的异常或其他事件的发生', 如电源掉电、键盘被按下等。'另一种称为软件中断', 软件中断通常是一条指令 (i386 下
是 int) 带有一个参数记录中断号, 使用这条指令用户可以手动触发某个中断并执行其中断处理程序。

例如在 i386 下, int 0x80 这条指令会调用第 0x80 号中断的处理程序。

'由于中断号是很有限的, 操作系统不会舍得用一个中断号来对应一个系统调用, 而更倾向于用一个或少数几个中断号来对应所有的系统调用'。

例如, i386 下 Windows 里绝大多数系统调用都是由 int 0x2e 来触发的, 而 Linux 则使用 int 0x80 来触发所有的系统调用。

对于同一个中断号, 操作系统如何知道是哪一个系统调用要被调用呢? 和中断一样, 系统调用都有一个系统调用号, 就像身份标识一样来表明是哪一个系统调用, 这个系统调用号通常就是系统
调用在系统调用表中的位置, 例如 Linux 里 fork 的系统调用号是 2。

这个系统调用号在执行 int 指令前会被放置在某个固定的寄存器里, '对应的中断代码会取得这个系统调用号, 并且调用正确的函数'。

以 Linux 的 int 0x80 为例, 系统调用号是由 eax 来传入的。用户将系统调用号放入 eax, 然后使用 int 0x80 调用中断, 中断服务程序就可以从 eax 里取得系统调用号, 进而调用
对应的函数。





// !! 12.2.2　基于 int 的 Linux 的经典系统调用实现


图 12-3 是以 fork 为例的 Linux 系统调用的执行流程。


接下来让我们一步一步地了解这个过程的细节:


//! 1. 触发中断

首先当程序在代码里调用一个系统调用时, 是以一个函数的形式调用的, 例如程序调用 fork:

int main() {
    fork();
}

fork 函数是一个对系统调用 fork 的封装, 可以用下列宏来定义它:

__syscall0(pid_t, fork);

'_syscall0 是一个宏函数, 用于定义一个没有参数的系统调用的封装'。它的第一个参数为这个系统调用的返回值类型, 这里为 pid_t 是一个 Linux 自定义类型, 代表进程的 id。
_syscall0 的第二个参数是系统调用的名称, _syscall0 展开之后会形成一个与系统调用名称同名的函数。

下面的代码是 i386 版本的 syscall0 定义:

#define __syscall0(type, name)    \
type name(void) {                 \
    long __res;                   \
    __asm__ volatile ("int 0x80"  \
    : "=a" (__res)                \
    : "0" (__NR_ ##name));        \
    __syscall_return(type,__res);  \
}

对于 syscall0(pid_t, fork), 上面的宏将展开为:


pid_t fork(void){
    long __res;
     __asm__ volatile ("int $0x80"
     : "=a" (__res): "0" (__NR_fork));
     __syscall_return(pid_t,__res);
}

如果读者对这种 AT&T 格式的汇编不熟悉, 请看下面的解释。


1. 首先 __asm__ 是一个 gcc 的关键字, 表示接下来要嵌入汇编代码。volatile 关键字告诉 GCC 对这段代码不进行任何优化。

2. __asm__ 的第一个参数是一个字符串, 代表汇编代码的文本。这里的汇编代码只有一句: int $0x80 这就要调用 0x80 号中断。

3. "=a" (__res) 表示用 eax (a 表示 eax) 输出返回数据并存储在 __res 里。

4. "0" (__NR_##name)) 表示 __NR_##name 为输入, "0" 指示由编译器选择和输出相同的寄存器 (即 eax) 来传递参数。


更直观一点, 可以把这段汇编改写为更为可读的格式:

main -> fork:

pid_t fork() {
    long __res;
    $eax = __NR_fork
    int $0x80
    __res = $eax
    __syscall_return(pid_t, __res);
}

__NR_fork 是一个宏, 表示 fork 系统调用的调用号, 对于 x86 体系结构, 该宏的定义可以在 Linux/include/asm-x86/unistd_32.h 里找到:


#define __NR_restart_syscall      0
#define __NR_exit                       1
#define __NR_fork                       2
#define __NR_read                       3
#define __NR_write                      4
......


而 __syscall_return 是另一个宏, 定义如下:

#define __syscall_return(type, __res)

do{
    if ((unsigned long)(res) >= (unsigned long)(-125)){
        errno = -(res);
        res = -1;
    }
    return (type)res;
}while(0);

这个宏用于检查系统调用的返回值, 并把它相应地转换为 C 语言的 errno 错误码。

在 Linux 里, 系统调用使用返回值传递错误码, 如果返回值为负数那么表明调用失败, 返回值的绝对值就是错误码。而在 C 语言里则不然, C 语言里的大多数函数都以返回语 -1 表示调用失
败, 而将出错信息存储在一个名为 errno 的全局变量 (在多线程库中, errno 存储于 TLS 中)里。

__syscall_return 就负责将系统调用的返回信息存储在 errno 中。
 
这样, fork 函数在汇编之后就会形成类似如下的汇编代码:

fork:
mov eax, 2
int 0x80
cmp eax,0xFFFFFF83
jb syscall_noerror
neg eax
mov errno,eax
mov eax,0xFFFFFFFF
syscall_noerror:ret


如果系统调用本身有参数要如何实现呢 ?

下面是 x86 Linux 下的 syscall1, 用于带 1 个参数的系统调用:

#define __syscall1(type, name, type1, arg1)
type name(type1, arg1) {
    long __res;
     __asm__ volatile ("int $0x80"                       \
             : "=a" (__res)                               \
             : "0" (__NR_##name), "b" ((long)(arg1)));     \
    __syscall_return(type,__res); 
}


这段代码和 _syscall0 不同的是它多了一个 “b” ((long)(arg1))。这一句的意思是先把 arg1 强制转换为 long, 然后存放在 EBX (b代表 EBX) 里作为输入。

当用户调用某个系统调用的时候, 实际是执行了以上一段汇编代码。CPU 执行到 int $0x80 时会保存现场以便恢复, 接着会将特权状态切换到内核态。然后 CPU 便会查找中断向量表中的
第 0x80 号元素。


// !! 2. 切换堆栈

在实际执行中断向量表中的第 0x80 号元素所对应的函数之前, CPU 首先还要进行栈的切换。

在 Linux 中, 用户态和内核态使用的是不同的栈, 两者各自负责各自的函数调用, 互不干扰。

但在应用程序调用 0x80 号中断时, 程序的执行流程从用户态切换到内核态, 这时程序的当前栈必须也相应地从用户栈切换到内核栈。从中断处理函数中返回时, 程序的当前栈还要从内核栈切
换回用户栈。

所谓的"当前栈"指的是 ESP 的值所在的栈空间。如果 ESP 的值位于用户栈的范围内, 那么程序的当前栈就是用户栈, 反之亦然。此外, 寄存器 SS 的值还应该指向当前栈所在的页。

所以, 将当前栈由用户栈切换为内核栈的实际行为就是:

1. 保存当前的 ESP、SS 的值

2. 将 ESP、SS 的值设置为内核栈的相应值

反过来, 将当前栈由内核栈切换为用户栈的实际行为则是:

1. 恢复原来 ESP、SS 的值

2. 用户态的 ESP 和 SS 的值保存在哪里呢 ? 答案是内核栈上。这一行为由 i386 的中断指令自动地由硬件完成。

当 0x80 号中断发生的时候, CPU 除了切入内核态之外, 还会自动完成下列几件事:

1. 找到当前进程的内核栈 (每一个进程都有自己的内核栈)

2. 在内核栈中依次压入用户态的寄存器 SS、ESP、EFLAGS、CS、EIP


而当内核从系统调用中返回的时候, 须要调用 iret 指令来回到用户态, iret 指令则会从内核栈里弹出寄存器 SS、ESP、EFLAGS、CS、EIP 的值, 使得栈恢复到用户态的状态。


这个过程可以用图 12-4 来表示。




// !! 3. 中断处理程序

在 int 指令合理地切换了栈之后, 程序的流程就切换到了中断向量表中记录的 0x80 号中断处理程序。


Linux 内部的 i386 中断服务流程如图 12-5 所示。




main -> fork -> int 0x80 -> system_call:

ENTRY(system_call)    
......    
SAVE_ALL    
......    
cmpl $(nr_syscalls), %eax    
jae syscall_badsys

在这里一开始使用宏 SAVE_ALL 将各种寄存器压入栈中, 以免它们的值被后续执行的代码所覆盖。然后接下来使用 cmpl 指令比较 eax 和 nr_syscalls 的值, nr_syscalls 是比最大
的有效系统调用号大 1 的值, 因此, 如果 eax (即用户传入的系统调用号) 大于等于 nr_syscalls, 那么这个系统调用就是无效的, 如果这样接着就会跳转到后面的 syscall_badsys 
执行。


如果系统调用号是有效的, 那么程序就会执行下面的代码:

syscall_call:
call *sys_call_table(0,%eax,4)
......
RESTORE_REGS
......
iret


确定系统调用号有效并且保存了寄存器之后, 接下来要执行的就是调用 *sys_call_table (0,%eax,4) 来查找中断服务程序并执行。执行结束之后, 使用宏 RESTORE_REGS 来恢复之前被
SAVE_ALL 保存的寄存器。最后通过指令 iret 从中断处理程序中返回。


究竟什么是 *sys_call_table(0,%eax,4) ? 我们在 Linux/arch/i386/kernel/syscall_table.S 里能找到定义:

.dataENTRY(sys_call_table)
.long sys_restart_syscall
.long sys_exit
.long sys_fork
.long sys_read
.long sys_write
......


这就是 Linux 的 i386 系统调用表, 这个表里的每一个元素 (long, 4 字节) 都是一个系统调用函数的地址。

那么不难推知 *sys_call_table(0,%eax,4) 指的是 sys_call_table 上偏移量为 0+%eax * 4 上的那个元素的值指向的函数, 也就是 %eax 所记录的系统调用号所对应的系统调用
函数.例如, 如果 %eax=2 那么 sys_fork 就会调用。


SAVE_ALL 的作用为保存寄存器, 因此其内容就是将各个寄存器压入栈中。

SAVE_ALL 的大致内容如下: 

 #define SAVE_ALL \
 ...... 
 push %eax
 push %ebp
 push %edi
 push %esi
 push %edx
 push %ecx
 push %ebx
 mov $(KERNEL_DS), %edx
 mov %edx, %ds
 mov %edx, %es

我们可以发现 SAVE_ALL 的一系列 push 指令的最后 6 条所压入栈中的寄存器恰好就是用来存放系统调用参数的 6 个寄存器, 连顺序都一样, 这当然不是一个巧合。





// !! 12.2.3　Linux 的新型系统调用机制

由于基于 int 指令的系统调用在奔腾 4 代处理器上性能不佳, Linux 在 2.5 版本起开始支持一种新型的系统调用机制。


这种新机制使用 Intel 在奔腾 2 代处理器就开始支持的一组专门针对系统调用的指令—— sysenter 和 sysexit。

如果使用 ldd 来获取一个可执行文件的共享库的依赖情况, 你会发现一些奇怪的现象:

> ldd cat
	linux-vdso.so.1 (0x00007ffceb5bd000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f7e2baec000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f7e2bd02000)


我们可以看到 linux-vdso.so.1 没有与任何实际的文件相对应, 那么这个库究竟是做什么的呢? '正是 Linux 用于支持新型系统调用的"虚拟"共享库'。

linux-vdso.so.1 并不存在实际的文件, 它只是操作系统生成的一个虚拟动态共享库 (Virtual Dynamic Shared Library, VDSO)。

这个库总是被加载在地址 0x00007ffceb5bd000 的位置上。我们可以通过 Linux 的 proc 文件系统来查看一个可执行程序的内存映像, 看看能不能找到这个虚拟文件:


> cat /proc/self/maps
56327d921000-56327d923000 r--p 00000000 08:05 2621592                    /usr/bin/cat
56327d923000-56327d928000 r-xp 00002000 08:05 2621592                    /usr/bin/cat
56327d928000-56327d92b000 r--p 00007000 08:05 2621592                    /usr/bin/cat
56327d92b000-56327d92c000 r--p 00009000 08:05 2621592                    /usr/bin/cat
56327d92c000-56327d92d000 rw-p 0000a000 08:05 2621592                    /usr/bin/cat
56327dc4c000-56327dc6d000 rw-p 00000000 00:00 0                          [heap]
7f8a1aded000-7f8a1ae0f000 rw-p 00000000 00:00 0 
7f8a1ae0f000-7f8a1b682000 r--p 00000000 08:05 2621468                    /usr/lib/locale/locale-archive
7f8a1b682000-7f8a1b6a4000 r--p 00000000 08:05 2631845                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f8a1b6a4000-7f8a1b81c000 r-xp 00022000 08:05 2631845                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f8a1b81c000-7f8a1b86a000 r--p 0019a000 08:05 2631845                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f8a1b86a000-7f8a1b86e000 r--p 001e7000 08:05 2631845                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f8a1b86e000-7f8a1b870000 rw-p 001eb000 08:05 2631845                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f8a1b870000-7f8a1b876000 rw-p 00000000 00:00 0 
7f8a1b88c000-7f8a1b88d000 r--p 00000000 08:05 2631841                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f8a1b88d000-7f8a1b8b0000 r-xp 00001000 08:05 2631841                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f8a1b8b0000-7f8a1b8b8000 r--p 00024000 08:05 2631841                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f8a1b8b9000-7f8a1b8ba000 r--p 0002c000 08:05 2631841                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f8a1b8ba000-7f8a1b8bb000 rw-p 0002d000 08:05 2631841                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f8a1b8bb000-7f8a1b8bc000 rw-p 00000000 00:00 0 
7fff20f55000-7fff20f76000 rw-p 00000000 00:00 0                          [stack]
7fff20ff2000-7fff20ff6000 r--p 00000000 00:00 0                          [vvar]
7fff20ff6000-7fff20ff8000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0                  [vsyscall]

我们可以看见地址 ffffffffff600000 到 ffffffffff601000 的地方被映射了 vdso, 也就是 linux-vdso.so.1。


