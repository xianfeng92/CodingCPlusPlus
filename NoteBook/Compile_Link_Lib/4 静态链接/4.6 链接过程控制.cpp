// !! 4.6　链接过程控制

由于整个链接过程有很多内容须要确定: 使用哪些目标文件? 使用哪些库文件? 是否在最终可执行文件中保留调试信息、输出文件格式 (可执行文件还是动态链接库)? 还要考虑是否要导出
某些符号以供调试器或程序本身或其他程序使用等。


// !! 4.6.1　链接控制脚本

'链接器一般都提供多种控制整个链接过程的方法, 以用来产生用户所须要的文件'。

一般链接器有如下三种方法:

• 使用命令行来给链接器指定参数, 我们前面所使用的 ld 的 -o、-e 参数就属于这类, 这种方法我们已经在前面使用很多次了

• 将链接指令存放在目标文件里面, 编译器经常会通过这种方法向链接器传递指令

• 使用链接控制脚本, 使用链接控制脚本方法就是本节要介绍的, 也是最为灵活、最为强大的链接控制方法

前面我们在使用 ld 链接器的时候, 没有指定链接脚本, 其实 ld 在用户没有指定链接脚本的时候会使用默认链接脚本

以使用下面的命令行来查看 ld 默认的链接脚本:

> ld -verbose
GNU ld (GNU Binutils for Ubuntu) 2.34
支持的仿真:
   elf_x86_64
   elf32_x86_64
   elf_i386
   elf_iamcu
   elf_l1om
   elf_k1om
   i386pep
   i386pe
使用内部链接脚本:
==================================================
/* Script for -z combreloc -z separate-code */
/* Copyright (C) 2014-2020 Free Software Foundation, Inc.
   Copying and distribution of this script, with or without modification,
   are permitted in any medium without royalty provided the copyright
   notice and this notice are preserved.  */
OUTPUT_FORMAT("elf64-x86-64", "elf64-x86-64", "elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)
SEARCH_DIR("=/usr/local/lib/x86_64-linux-gnu"); 
SEARCH_DIR("=/lib/x86_64-linux-gnu"); 
SEARCH_DIR("=/usr/lib/x86_64-linux-gnu"); 
SEARCH_DIR("=/usr/lib/x86_64-linux-gnu64"); 
SEARCH_DIR("=/usr/local/lib64"); 
SEARCH_DIR("=/lib64"); 
SEARCH_DIR("=/usr/lib64"); 
SEARCH_DIR("=/usr/local/lib"); 
SEARCH_DIR("=/lib"); 
SEARCH_DIR("=/usr/lib"); 
SEARCH_DIR("=/usr/x86_64-linux-gnu/lib64"); 
SEARCH_DIR("=/usr/x86_64-linux-gnu/lib");

SECTIONS
{
  PROVIDE (__executable_start = SEGMENT_START("text-segment", 0x400000)); . = SEGMENT_START("text-segment", 0x400000) + SIZEOF_HEADERS;
  .interp         : { *(.interp) }
  .note.gnu.build-id  : { *(.note.gnu.build-id) }
  .hash           : { *(.hash) }
  .gnu.hash       : { *(.gnu.hash) }
  .dynsym         : { *(.dynsym) }
  .dynstr         : { *(.dynstr) }
  .gnu.version    : { *(.gnu.version) }
  .gnu.version_d  : { *(.gnu.version_d) }
  .gnu.version_r  : { *(.gnu.version_r) }
  .rela.dyn       :
    {
      *(.rela.init)
      *(.rela.text .rela.text.* .rela.gnu.linkonce.t.*)
      *(.rela.fini)
      *(.rela.rodata .rela.rodata.* .rela.gnu.linkonce.r.*)
      *(.rela.data .rela.data.* .rela.gnu.linkonce.d.*)
      *(.rela.tdata .rela.tdata.* .rela.gnu.linkonce.td.*)
      *(.rela.tbss .rela.tbss.* .rela.gnu.linkonce.tb.*)
      *(.rela.ctors)
      *(.rela.dtors)
      *(.rela.got)
      *(.rela.bss .rela.bss.* .rela.gnu.linkonce.b.*)
      *(.rela.ldata .rela.ldata.* .rela.gnu.linkonce.l.*)
      *(.rela.lbss .rela.lbss.* .rela.gnu.linkonce.lb.*)
      *(.rela.lrodata .rela.lrodata.* .rela.gnu.linkonce.lr.*)
      *(.rela.ifunc)
    }
  .rela.plt       :
    {
      *(.rela.plt)
      PROVIDE_HIDDEN (__rela_iplt_start = .);
      *(.rela.iplt)
      PROVIDE_HIDDEN (__rela_iplt_end = .);
    }
  . = ALIGN(CONSTANT (MAXPAGESIZE));
  .init           :
  {
    KEEP (*(SORT_NONE(.init)))
  }
.plt            : { *(.plt) *(.iplt) }
.plt.got        : { *(.plt.got) }
.plt.sec        : { *(.plt.sec) }
  .text           :
  {
    *(.text.unlikely .text.*_unlikely .text.unlikely.*)
    *(.text.exit .text.exit.*)
    *(.text.startup .text.startup.*)
    *(.text.hot .text.hot.*)
    *(SORT(.text.sorted.*))
    *(.text .stub .text.* .gnu.linkonce.t.*)
    /* .gnu.warning sections are handled specially by elf.em.  */
    *(.gnu.warning)
  }
  .fini           :
  {
    KEEP (*(SORT_NONE(.fini)))
  }

默认的 ld 链接脚本存放在 /usr/lib/ldscripts/ 下, 不同的机器平台、输出文件格式都有相应的链接脚本。比如 Intel IA32 下的普通可执行 ELF 文件链接脚本文件为 
elf_i386.x ,IA32 下共享库的链接脚本文件为 elf_i386.xs 等。

当我们使用 ld 来生成一个共享目标文件的时候, 它就会使用 elf_i386.xs 作为链接控制脚本。

当然, 为了更加精确地控制链接过程, 我们可以自己写一个脚本, 然后指定该脚本为链接控制脚本。

比如可以使用 -T 参数:

>ld -T link.script


// !! 4.6.2　最小的程序


为了演示链接的控制过程, 我们接着要做一个最小的程序: 这个程序的功能是在终端上输出 Hello world!。可能很多人的第一反应就是我们学 C 语言时候的那个经典的使用 printf
的 helloworld, 然后对着屏幕盲打一遍该程序源代码后编译链接一气呵成, 连鼠标都没有移动一下, 非常好, 你的 C 语言基础很扎实。


• 首先, 经典的 helloworld 使用了 printf 函数, 该函数是系统 C 语言库的一部分。为了使用该函数, 我们必须在链接时将 C 语言库与程序的目标文件链接产生最终可执行文件。
  我们希望小程序能够脱离 C 语言运行库, 使得它成为一个独立于任何库的纯正的程序。

• 其次, 经典的 helloworld 由于使用了库, 所以必须有 main 函数。我们知道一般程序的入口在库的 _start, 由库负责初始化后调用 main 函数来执行程序的主体部分。为了不
  使用 main 这个我们已经感到厌烦的函数名, 小程序使用 no-main 作为整个程序的入口。

• 接着, 经典的 helloworld 会产生多个段: main 程序的指令部分会产生 .text 段、字符串常量 Hello world!\n 会被放在数据段或只读数据段,还有 C 库所包含的各种段。
  为了演示 ld 链接脚本的控制过程, 我们将小程序的所有段都合并到一个叫 tinytext 的段，注意:这个段是我们任意命名的, 是由链接脚本控制链接过程生成的。

char* str = "Hello world!\n";

void print() {
    asm("movl $13, %%edx \n\t"
    "movl %0,%%ecx  \n\t"
    "movl $0,%%ebx  \n\t"
    "movl $4,%%eax  \n\t"
    "int $0x80      \n\t"
     ::"r"(str):"edx","ecx","ebx");
    );
}

void exit() {
    asm( "movl $42,%ebx  \n\t"
     "movl $1,%eax  \n\t"
      "int $0x80     \n\t" );
}

void nomain(){
    print();
    exit();
}

从源代码我们可以看到, 程序入口为 nomain() 函数, 然后该函数调用 print() 函数, 打印 Hello World, 接着调用 exit() 函数, 结束进程。这里的 print 函数使用了
Linux 的 WRITE 系统调用, exit() 函数使用了 EXIT 系统调用。

这里我们使用了 GCC 内嵌汇编, 对这种内嵌汇编格式不熟悉的话, 请参照 GCC 手册关于内嵌汇编的部分。

这里简单介绍系统调用: 系统调用通过 0x80 中断实现, 其中 eax 为调用号, ebx、ecx、edx 等通用寄存器用来传递参数, 比如 WRITE 调用是往一个文件句柄写入数据, 如果用 C 
语言来描述它的原型就是:

int write(int filedesc, char* buffer, int size);

• WRITE 调用的调用号为 4, 则 eax = 4

• filedesc 表示被写入的文件句柄, 使用 ebx 寄存器传递, 我们这里是要往默认终端(stdout) 输出, 它的文件句柄为 0, 即 ebx = 0

• buffer 表示要写入的缓冲区地址, 使用 ecx 寄存器传递, 我们这里要输出字符串 str, 所以 ecx = str

• size 表示要写入的字节数, 使用 edx 寄存器传递, 字符串 Hello world!\n 长度为 13 字节, 所以 edx = 13


同理, EXIT 系统调用中, ebx 表示进程退出码 (Exit Code), 比如我们平时的 main 程序中的 return 的数值会返回给系统库, 由系统库将该数值传递给 EXIT 系统调用。
这样父进程就可以接收到子进程的退出码。EXIT 系统调用的调用号为 1, 即 eax = 1。

这里要调用 EXIT 结束进程是因为如果是普通程序, main() 函数结束后控制权返回给系统库, 由系统库负责调用 EXIT, 退出进程。我们这里的 nomain() 结束后系统控制权不会返回,
可能会执行到 nomain() 后面不正常的指令, 最后导致进程异常退出。

我们先不急于使用链接脚本, 而先使用普通命令行的方式来编译和链接 TinyHelloWorld.c:


> gcc -m32 -c -fno-builtin TinyHelloWorld.c
// gcc 的 -m32 参数编译产生 32 位的目标代码

> ld -static -m elf_i386 -e nomain -o TinyHelloWorld TinyHelloWorld.o
// 使用 -m elf_i386 参数可以使得 64 位的 ld 能够兼容 32 位的库


这里 GCC 和 ld 的参数的意义如下:

• -fno-builtin GCC 编译器提供了很多内置函数 (Built-in Function), 它会把一些常用的 C 库函数替换成编译器的内置函数, 以达到优化的功能。比如 GCC 会将只有字符串参数的
  printf 函数替换成 puts, 以节省格式解析的时间。exit() 函数也是 GCC 的内置参数之一, 所以我们要使用 -fno-builtin 参数来关闭 GCC 内置函数功能

• -static 这个参数表示 ld 将使用静态链接的方式来链接程序, 而不是使用默认的动态链接的方式

• -e nomain 表示该程序的入口函数为 nomain, 还记得 ELF 文件头 Elf32_Ehdr 的 e_entry 成员吗? 这个参数就是将 ELF 文件头的 e_entry 成员赋值成 nomain 函数的地址

• -o TinyHelloWorld 表示指定输出可执行文件名为 TinyHelloWorld

我们得到了一个 924 字节 (依赖于系统环境) 的 ELF 可执行文件, 运行它以后能够正确打印 Hello world! 并且正常退出。


// !! 4.6.3　使用 ld 链接脚本

如果把整个链接过程比作一台计算机, 那么 ld 链接器就是计算机的 CPU, 所有的目标文件、库文件就是输入, 链接结果输出的可执行文件就是输出, 而链接控制脚本正是这台计算机的"程序",
它控制 CPU 的运行, 以"程序"要求的方式将输入加工成所须要的输出结果。链接控制脚本程序使用一种特殊的语言写成, 即 ld 的链接脚本语言, 这种语言并不复杂, 只有为数不多的几种
操作。

无论是输出文件还是输入文件, 它们的主要的数据就是文件中的各种段, 我们把输入文件中的段称为 Input Sections, 输出文件中的段称为 Output Sections。

简单来讲, 控制链接过程无非是控制输入段如何变成输出段, 比如哪些输入段要合并一个输出段, 哪些输入段要丢弃; 指定输出段的名字、装载地址、属性，等等。

我们先来看看 TinyHelloWorld 的链接脚本 TinyHelloWorld.lds

ENTRY(nomain)
SECTIONS {
     . = 0x08048000 + SIZEOF_HEADERS;
     tinytext  : { *(.text) *(.data) *(.rodata) }
      /DISCARD/ : { *(.comment) }
}

这是一个非常简单的链接脚本, 第一行的 ENTRY(nomain) 指定了程序的入口为 nomain() 函数; 后面的 SECTIONS 命令一般是链接脚本的主体, 这个命令指定了各种输入段到输出段的变
换, SECTIONS 后面紧跟着的一对大括号里面包含了 SECTIONS 变换规则, 其中有三条语句, 每条语句一行。第一条是赋值语句, 后面两条是段转换规则, 它们的含义分别如下:

•. = 0x08048000 + SIZEOF_HEADERS 第一条赋值语句的意思是将当前虚拟地址设置成 0x08048000 +SIZEOF_HEADERS, SIZEOF_HEADERS 为输出文件的文件头大小


• tinytext : { *(.text) *(.data) *(.rodata) } 第二条是个段转换规则, 它的意思即为所有输入文件中的名字为 .text、.data或 .rodata 的段依次合并到输出文件的
  tiny-text。

• /DISCARD/ : { *(.comment) } 第三条规则为: 将所有输入文件中的名字为 .comment 的段丢弃, 不保存到输出文件中。

通过上述两条转换规则, 我们就达到了 TinyHelloWorld 程序的第三个要求: 最终输出的可执行文件只有一个叫 tinytext 的段。


我们通过下面的命令行来编译 TinyHelloWorld, 并且启用该链接控制脚本:

>  gcc -m32 -c -fno-builtin TinyHelloWorld.c

>  ld -static -m elf_i386 -T TinyHelloWorld.lds -o TinyHelloWorld TinyHelloWorld.o
