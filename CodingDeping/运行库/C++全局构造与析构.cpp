
// !! C++ 全局构造与析构

在 C++ 世界里，入口函数还肩负一个艰巨的使命，那就是在 main 函数前后完成全局变量的构造和析构。


// !! glib 全局构造与析构

glibc 启动文件时的 2 个代码段 .init 和 .finit 段，最终会拼成2个函数 _init() 和 _finit()，它们会先于和后于 main 函数的执行。但是它们具体是在什么时候执行？
由谁调用呢？ 又是如何对全局对象构造和析构呢？


libc -------------------------------------------> GCC 的 crtbegin.o

_start -> __libc_start_main -> __libc_csu_init -> __do_global_ctors_aux

// __do_global_ctors_aux 来自 GCC 提供的一个目标文件 crtbegin.o
void __do_global_ctors_aux(void)
{
	/* Call constructor functions */
	unsigned long nptrs = (unsigned long) __CTRO_LIST__[0]; // 取得数组第一个元素
	unsigned i;
	for (i = nptrs; i >= 1; i--)
		__CTRO_LIST__[i] (); // 调用第 i 个函数指针指向的函数
}

数组__CTRO_LIST__存放的是所有全局对象的构造函数的指针


// !! 问题来了：谁负责构建这个数组呢？


对于每个编译单元 （.cpp），GCC 编译器会遍历其中所有的全局对象，生成一个特殊的函数，其作用是对本编译单元里的所有全局对象进行初始化。

GCC 在目标代码中生成了一个名为 GLOBAL__I_Hw 的函数，'负责本编译单元所有全局/静态对象的构造和析构'，其代码可以表示成：

static void GLOBAL__I_Hw(void) // 当前.cpp文件的全局构造函数
{
	Hw::Hw(); // 构造对象
	atexit(__tcf_1); // 一个神秘的函数__tcf_1__被注册到了 exit
}

一旦一个目标文件里 GLOBAL__I_Hw 这样的特殊函数，编译器会在编译单元参数的目标文件（.o）的 .ctors 段放置一个指针，指向 GLOBAL__I_Hw


编译器为每个编译单元生成一份特殊函数后，链接器在连接这些目标文件时，会将这些同名的段合并在一起，这样，每个目标文件的 .ctors 段会被合并成一个.ctor 段。每个
目标文件的 .ctors 存储了一个指向该目标文件的全局构造函数（GLOBAL__I_Hw），因此，拼接起来的 .ctors 段就是一个函数指针数组，每个元素都指向一个目标文件的全
局构造函数。


// !! 如何获取这个指针数组（的地址）呢？

链接的时候，各个用户产生的目标文件前后分别还要链接上 2 个 glibc 自身的目标文件 crtbegin.o, crtend.o。这 2 个文件同样具有 .ctors 段，这 2 个文件的 .ctors 
段内容也会被合并到最终的可执行文件中。

1. crtbegin.o： 作为所有 .ctors 段的开头部分，crtbegin.o 的 .ctor 段内存储的是 4byte -1（0xFFFFFFFF），由'链接器负责将这个数字改成全局构造函数的数量'。
   然后，这个段还将起始地址定义成符号 __CTOR_LIST__  代表所有 .ctor 段最终合并后的起始地址

2. crtend.o: 文件内 .ctors 内容简单，就是一个 0，然后定义了一个符号 __CTOR_END__ ，指向 .ctor 段末尾

链接 2 个用户的目标文件 a.o 和 b.o 时，实际链接的目标文件顺序: crti.o crtbegin.o a.o b.o crtend.o crtn.o, '其中 crti.o，crtn.o 是用于提供 main 之前
和之后执行代码的机制，与全局构造无关'; 合并 crtbegin.o、用户目标文件（a.o和b.o）、crtend.o 时，链接器按顺序拼接这些文件的 .ctors 段。


TIPS: 可以手动在 .ctors 段里添加函数指针，让这些函数在全局构造的时候（main之前）调用

#include <stdio.h>
void my_init(void)
{
	printf("Hello");
}
typedef void (*ctor_t)(void);
// 在 .ctors 段添加一个函数指针
ctor_t __attribute__((section (".ctors"))) my_init_p = &my_init;

int main()
{
	printf("World!\n");
	return 0;
}

my_init 函数在 main 之前被调用



// !! 析构

通过 __cxa_atexit() 在 exit() 函数中注册进程退出回调函数来实现析构。

回到 GLOBAL__I_Hw()，编译器对每个编译单元的全局对象，都会生成一个特殊的函数来调用这个编译单元的所有全局对象的析构函数，其调用顺序与 GLOBAL__I_Hw()
调用构造函数的顺序刚好相反。编译器生成的神秘函数 __tcf_1 大致内容：

static void __tcf_1(void) // 编译器生成的名字
{
	Hw.~HelloWorld();
}

__tcf_1 函数负责析构 Hw 对象，而在 GLOBAL__I_Hw 中，我们通过 __cxa_exit() 注册了 __tcf_1，而通过 __cxa_exit() 注册的函数在进程退出时被调用顺
序满足先注册后调用的特定，这样，析构顺序与构造顺序完全符合（先构造后析构）。










