
// !! 1 为什么要动态链接

首先，要明确一个问题：~~ 为什么要用动态链接 ? ~~

主要出于以下两个原因：

1. 静态链接会造成硬盘与内存的空间浪费

静态链接是在链接的时候就把程序依赖的所有目标文件都合并到最终的可执行程序里，而一个程序往往会用到许多公共的目标文件（库），例如 C 语言标准库
（stdio.h、stdlib.h 等）。如果计算机中的每个程序都包含 C 语言标准库的目标文件， 那么以当今计算机中程序的数量来看，你的硬盘空间是大概率不够的。同时，
静态链接的程序是被整体加载到内存中的， 因此，当多个程序都被加载到内存中，它们所包含的标准库部分也会被重复加载许多次， 这就造成了内存空间的极大浪费，
以今计算机操作系统中运行的程序数量来看，你有限的内存大小也是顶不住的。

2. 静态链接程序的更新困难

如果一个程序（假设是 Program1）使用的一个第三方公共目标文件（假设是 Lib.o） 进行了更新， 那么 Program1 需要进行重新链接，再发布给用户，用户需要重新下
载整个程序，如果这个程序用了 100 个模块（目标文件、库），每个假设是 1MB，整个程序 100MB，那么即使每次只改动了某个模块的一个地方，那么也要重新链接整
个程序，用户也要重新下载，对用户非常不友好。


// !! 2 动态链接

// !! 动态链接的原理就是把程序的模块分割开来, 使之成为一个个相互独立的文件， 并一直保持这种状态，直到程序被加载到内存中运行。

当点击该程序运行时, 该程序所依赖的所有模块（文件）都被加载到内存， 然后由 ~~动态链接器~~ 进行链接操作，链接操作基本与静态链接一致。

// !! 这种把链接过程推迟到运行时进行的思想就是动态链接的基本原理

1. 动态链接所加载的部分模块（公共模块）是可以被多个程序共用的，这就大大减少了内存浪费

2. 倘若程序中的某个模块更新了，理论上我们只需要覆盖掉老版本的模块目标文件就行（不过实际还要考虑得多一点，比如新旧接口兼容问题）


// !! 3 程序可扩展性和兼容性

动态链接还带来一个特点， 就是程序可以在运行时动态地选择加载各种程序模块，这种机制可以被用来制作插件（Plug-in）

动态连接还加强了程序在不同 平台/机器 的兼容性， 比如一个程序在不同平台运行时可以动态地链接到由操作系统提供的动态链接库， 这些动态链接库相当于在程序和操作系
统之间增加了一个~~中间层~~，从而消除了程序对不同平台依赖的差异性。有一句话说得好，“在计算机领域，没有什么是不能通过添加一层中间层解决的”（比如操作系统 A 和操作系统 B 
对于 printf() 的实现机制不同，如果我们的程序是静态链接的，那么程序就需要在 A、B 两个平台分别编译链接；如果用的是动态链接，那么程序只需要有一个版本，就可以在两个操
作系统上运行，动态地选择 printf() 的实现版本。


// !! 动态连接的基本实现

动态链接需要操作系统的支持, Linux 下的动态链接文件称作动态共享对象（Dynamic Shared Object），简称共享对象，一般以 .so 为后缀； Windows下的动态链接文件称作动态
链接库（Dynamic Linking Library），后缀一般为 .dll。


// !! 简单的动态链接例子

 /* Program1.c */
 #include"Lib.h"
 ​
 int main()
 {
         foobar(1);
         return 0;
 }

  /* Program2.c */
 #include"Lib.h"
 ​
 int main()
 {
         foobar(2);
         return 0;
 }

  /* Lib.h */
 #ifndef LIB_H
 #define LIB_H
 ​
 void foobar(int i);
 ​
 #endif

  /* Lib.c */
 #include"stdio.h"
 ​
 void foobar(int i)
 {
         printf("Printing from Lib.so %d\n", i);
         sleep(-1);
 }



编译链接过程:

>> gcc -fPIC -shared -o Lib.so Lib.c 

>> gcc -o Program1 Program1.c ./Lib.so

>> gcc -o Program2 Program2.c ./Lib.so

// !! 为什么在生成可执行文件的时候仍要 Lib.so “参与链接工作”呢？

其实这里的链接并不是真正的链接, 而是为了让 Program1 知道其中引用的 foobar 函数是一个动态链接的符号，从而不进行重定位，而是把这个过程留到装载时再进行。
同时，如果 Lib.so “不参与链接”, 那么生成可执行文件的过程可能会产生~找不到符号定义的问题~。

运行其中一个可执行文件（以 Program1 为例）, 并查看它的虚拟地址空间映射，如下：

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
~/Stan/xforg/CodingCPlusPlus/CodingDeping/动态链接(main*) » ./Program1&                                                                                          parallels@xforg
[1] 106833
Printing from Lib.so 1                                                                                                                                                           
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
~/Stan/xforg/CodingCPlusPlus/CodingDeping/动态链接(main*) » cat /proc/106833/maps                                                                                parallels@xforg
56120526c000-56120526d000 r--p 00000000 08:05 2385078                    /home/parallels/Stan/xforg/CodingCPlusPlus/CodingDeping/动态链接/Program1
56120526d000-56120526e000 r-xp 00001000 08:05 2385078                    /home/parallels/Stan/xforg/CodingCPlusPlus/CodingDeping/动态链接/Program1
56120526e000-56120526f000 r--p 00002000 08:05 2385078                    /home/parallels/Stan/xforg/CodingCPlusPlus/CodingDeping/动态链接/Program1
56120526f000-561205270000 r--p 00002000 08:05 2385078                    /home/parallels/Stan/xforg/CodingCPlusPlus/CodingDeping/动态链接/Program1
561205270000-561205271000 rw-p 00003000 08:05 2385078                    /home/parallels/Stan/xforg/CodingCPlusPlus/CodingDeping/动态链接/Program1
561205523000-561205544000 rw-p 00000000 00:00 0                          [heap]
7f7b617a1000-7f7b617a4000 rw-p 00000000 00:00 0 
7f7b617a4000-7f7b617c9000 r--p 00000000 08:05 2623652                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f7b617c9000-7f7b61941000 r-xp 00025000 08:05 2623652                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f7b61941000-7f7b6198b000 r--p 0019d000 08:05 2623652                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f7b6198b000-7f7b6198c000 ---p 001e7000 08:05 2623652                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f7b6198c000-7f7b6198f000 r--p 001e7000 08:05 2623652                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f7b6198f000-7f7b61992000 rw-p 001ea000 08:05 2623652                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f7b61992000-7f7b61996000 rw-p 00000000 00:00 0 
7f7b619af000-7f7b619b0000 r--p 00000000 08:05 2385076                    /home/parallels/Stan/xforg/CodingCPlusPlus/CodingDeping/动态链接/Lib.so
7f7b619b0000-7f7b619b1000 r-xp 00001000 08:05 2385076                    /home/parallels/Stan/xforg/CodingCPlusPlus/CodingDeping/动态链接/Lib.so
7f7b619b1000-7f7b619b2000 r--p 00002000 08:05 2385076                    /home/parallels/Stan/xforg/CodingCPlusPlus/CodingDeping/动态链接/Lib.so
7f7b619b2000-7f7b619b3000 r--p 00002000 08:05 2385076                    /home/parallels/Stan/xforg/CodingCPlusPlus/CodingDeping/动态链接/Lib.so
7f7b619b3000-7f7b619b4000 rw-p 00003000 08:05 2385076                    /home/parallels/Stan/xforg/CodingCPlusPlus/CodingDeping/动态链接/Lib.so
7f7b619b4000-7f7b619b6000 rw-p 00000000 00:00 0 
7f7b619b6000-7f7b619b7000 r--p 00000000 08:05 2623648                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f7b619b7000-7f7b619da000 r-xp 00001000 08:05 2623648                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f7b619da000-7f7b619e2000 r--p 00024000 08:05 2623648                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f7b619e3000-7f7b619e4000 r--p 0002c000 08:05 2623648                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f7b619e4000-7f7b619e5000 rw-p 0002d000 08:05 2623648                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f7b619e5000-7f7b619e6000 rw-p 00000000 00:00 0 
7fffa718a000-7fffa71ab000 rw-p 00000000 00:00 0                          [stack]
7fffa71ae000-7fffa71b2000 r--p 00000000 00:00 0                          [vvar]
7fffa71b2000-7fffa71b4000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0                  [vsyscall]
-----------------------------------------------------------------------------------------

可以看到其中不止有 Program1 的映射， 还有 libc-2.31.so 、Lib.so 、ld-2.31.so 等共享对象，其中:

libc-2.31.so 是动态链接的 C 语言运行库

ld-2.31.so 是 Linux 下的动态链接器

在开始执行 Program1 之前，系统会把控制权交给动态链接器（ld-2.31.so）， 并由它完成所有的动态链接工作，然后再把控制权交还给 Program1 开始执行


~/Stan/xforg/CodingCPlusPlus/CodingDeping/动态链接(main*) » readelf -l Lib.so                                                                                    parallels@xforg

Elf 文件类型为 DYN (共享目标文件)
Entry point 0x1080
There are 11 program headers, starting at offset 64

程序头：
  Type           Offset             VirtAddr           PhysAddr
                 FileSiz            MemSiz              Flags  Align
  LOAD           0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000560 0x0000000000000560  R      0x1000
  LOAD           0x0000000000001000 0x0000000000001000 0x0000000000001000
                 0x000000000000017d 0x000000000000017d  R E    0x1000
  LOAD           0x0000000000002000 0x0000000000002000 0x0000000000002000
                 0x00000000000000dc 0x00000000000000dc  R      0x1000
  LOAD           0x0000000000002e10 0x0000000000003e10 0x0000000000003e10
                 0x0000000000000220 0x0000000000000228  RW     0x1000
  DYNAMIC        0x0000000000002e20 0x0000000000003e20 0x0000000000003e20
                 0x00000000000001c0 0x00000000000001c0  RW     0x8
  NOTE           0x00000000000002a8 0x00000000000002a8 0x00000000000002a8
                 0x0000000000000020 0x0000000000000020  R      0x8
  NOTE           0x00000000000002c8 0x00000000000002c8 0x00000000000002c8
                 0x0000000000000024 0x0000000000000024  R      0x4
  GNU_PROPERTY   0x00000000000002a8 0x00000000000002a8 0x00000000000002a8
                 0x0000000000000020 0x0000000000000020  R      0x8
  GNU_EH_FRAME   0x000000000000201c 0x000000000000201c 0x000000000000201c
                 0x000000000000002c 0x000000000000002c  R      0x4
  GNU_STACK      0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000000 0x0000000000000000  RW     0x10
  GNU_RELRO      0x0000000000002e10 0x0000000000003e10 0x0000000000003e10
                 0x00000000000001f0 0x00000000000001f0  R      0x1

 Section to Segment mapping:
  段节...
   00     .note.gnu.property .note.gnu.build-id .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt 
   01     .init .plt .plt.got .plt.sec .text .fini 
   02     .rodata .eh_frame_hdr .eh_frame 
   03     .init_array .fini_array .dynamic .got .got.plt .data .bss 
   04     .dynamic 
   05     .note.gnu.property 
   06     .note.gnu.build-id 
   07     .note.gnu.property 
   08     .eh_frame_hdr 
   09     
   10     .init_array .fini_array .dynamic .got 
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// !! 地址无关代码

动态链接需要在开始执行程序之前对各个模块中数据和引用的地址进行确定, 也就是静态链接时的重定位。

动态链接实现重定位的方式有两种:

1. 装载时重定位

   装载时重定位很简单，就是在模块装载时先确定装载地址（目标地址/基地址），然后依据这个装载地址修改其中的绝对地址引用进行重定位（因为模块是按照一个整体被装载的，
   所以代码和数据之间的相对位置是不会改变的）。这种方式的缺点就是一个共享对象的指令部分不能被多个进程所共享， 仍然起不到节省内存空间的作用。因为指令部分中的引用在
   装载时被修改后就与进程相关了，取决于这个共享对象在该进程虚拟空间中被分配的地址，是一个固定值，而对于不同的进程，该共享对象的虚拟地址都是不一样的，所以一份指令不能
   被多个进程所共享。


2. 地址无关代码（Position-Independent Code, PIC）

   解决这个问题的方法就是地址无关代码技术， 其实就是在指令部分和被引用的地址之间增加了一层，这一层称为~全局偏移表（Global Offset Table, GOT）~，在共享对象
   文件中是名为 .got 的段。使用这种技术的目的是希望共享模块的指令部分与装载地址无关， 从而能被多个进程共享。于是一个自然的想法就是把指令中那些需要修改的部分
   分离出来放在数据部分，因为每个进程都有单独的一个数据部分的副本，从而可以满足我们的需求。


// !! 使用 GCC 产生地址无关代码很简单，我们只需要使用 ”-fPIC” 参数接口

// !! 模块中各种类型的地址引用方式：

1. 模块内部的函数调用和跳转
2. 模块内部的数据访问， 比如模块中定义的一些全局变量、静态变量等
3. 模块外部的函数调用、跳转等
4. 模块外部的数据访问， 比如其他模块中定义的全局变量

代码中对函数和数据的访问大致可以分为以下四种：

 static int a;   //注意这里是静态全局变量
 extern int b;
 extern void ext();
 ​
 void bar()
 {
     a = 1;  //类型2 模块内部数据访问
     b = 2;  //类型4 模块外部数据访问
 }
 ​
 void foo()
 {
     bar();  //类型1 模块内部函数调用
     ext();  //类型3 模块外部函数调用
 }

                指令跳转、调用              数据访问
模块内部         （1）相对跳转和调用          （2）相对地址访问


模块外部         （3）间接跳转和调用（GOT）    （4）直接访问（GOT）


// !! -fPIC

使用 GCC 产生地址无关代码很简单， 我们还需要使用 “-fPIC” 参数即可。

// !! 如何区别一个 DSO 是否为 PIC

>> readelf -d Lib.so| grep TEXTREL 

如果上面的命令有任何输出，那么 Lib.so 就不是 PIC 的，否则就是 PIC 的。PIC 的 DSO 是不会包含任何代码段重定位表的，TEXTREL 表示代码段重定位表的地址。

// !!  数据段地址无关

我们之前讨论的都是指令（代码）部分的地址无关性，其实数据段里面也有绝对地址的引用问题，例如一个指针变量 p 指向一个全局静态变量 a，a 的地址会随着不同进程的
装载而不同，解决这个问题的方法是利用~重定位表~，其中包含 a 的重定位信息，在动态装载的时候就会被重定位。


装载时重定位和地址无关代码的优缺:

装载时重定位----> 运行速度较PIC方案要快,代码部分不能被共享

地址无关代码(PIC) ----> 代码部分能被共享, 比装载时重定位的方法运行时多了计算当前地址以及间接寻址的过程

对于动态连接的可执行文件，GCC 默认会使用 PIC 的方法产生可执行文件的代码段部分


// !! 延迟绑定（Lazing Binding）

'动态链接的确有许多优点，比静态链接要灵活的多，但它是以牺牲一部分性能为代价的'。据统计 ELF 程序在静态链接下要比动态链接快点，大约 1% ~ 5%，这当然取决于程序本身的
特性以及运行环境等。'因为要在真正运行程序前将程序引用到的所有函数都进行动态链接'，这个过程很耗时，导致用户在点击运行程序后需要等待的时间变长，影响用户体验。

同时，在我们使用程序的时候，并不是所有在程序中被引用的函数都真正被调用了（比如 if 判断就会导致有些函数不会被调用）。于是考虑能不能在函数第一次被调用
的时候才对函数进行链接，这样也能将原本的时间（一次性链接所有函数）平摊到每次调用函数的时候——一个函数第一次链接所需要的时间很少，使得用户体验得到明显提升。

// !! 这种方案称作延迟绑定（Lazy Binding），基本思想就是在函数第一次被用到的时候才进行绑定（符号查找、重定位等），这样可以大幅提高程序的启动速度

ELF 具体使用的是 PLT（Procedure Linkage Table） 方法，在 ELF 文件中表现为段名中包含 plt 的段，其本质就是在指令和 GOT 之间又增加了一层跳转的过程，
'在第一次调用的时候，调用一个“绑定函数”来完成函数的绑定过程（填充GOT表中的项），在之后的调用时，直接调用 GOT 表中的项'。每一个函数都在 plt 中有一个对应的项。


动态链接器绑定过程具体调用的方法是 _dl_runtime_resolve(), 它需要的两个参数:

1. 这个函数绑定发生在哪个模块（module）

2. 需要绑定的是哪个函数（function）


// !! 动态链接相关结构

动态链接的简要流程:

1. OS 加载可执行文件头，检查其合法性，再从头部中的 “Program Header” 中读取每个 Segment 的虚拟地址、文件地址和属性, 并将它们映射到进程的
   虚拟地址空间的相应位置。这些步骤跟前面静态链接的情况下的装载基本无异。在静态链接下，OS 接着就可以把 CPU 控制权转交给可执行文件的入口地址，
   然后程序开始执行，一切看起来非常直观。

2. 在映射完可执行文件之后， OS 将 CPU 的控制权交给动态链接器（Dynamic Linker）（ld.so）的入口地址, 由其完成程序的动态链接过程

3. 在完成动态链接工作之后, 将动态链接器会将 CPU 控制权交给可执行文件的入口地址，程序开始正式执行


// !! “.interp” 段

这个段的内容是一个字符串, 保存的是可执行文件用到的动态链接器的路径。

用 objdump -s xxx 即可查看 xxx 的不同段的内容，如果 xxx 是动态链接的可执行程序，那么就能找到 .interp 段的内容


>>  objdump -s Program1

Program1：     文件格式 elf64-x86-64

Contents of section .interp:
 0318 2f6c6962 36342f6c 642d6c69 6e75782d  /lib64/ld-linux-x86-64.so.2
 0328 7838362d 36342e73 6f2e3200            
Contents of section .note.gnu.property:

在 Linux 下可执行文件所需要的动态链接器的路径几乎都是 /lib64/ld-linux- x86-64.so.2 。在 Liux 系统中，/lib64/ld-linux- x86-64.so.2 
为一个软连接。

/lib64 » ls -li                                                                                                             
总用量 0
2623708 lrwxrwxrwx 1 root root 32 Dec 16  2020 ld-linux-x86-64.so.2 -> /lib/x86_64-linux-gnu/ld-2.31.so

/lib/x86_64-linux-gnu/ld-2.31.so 才是真正的动态链接器。在 Linux 中，操作系统 OS 对可执行文件的加载的时候，它回去寻找该可执行文件所需要的
相应的动态链接器，即 “.interp” 指定的路径的共享对象。


// !! “.dynamic” 段

动态链接 ELF 中最重要的结构应该是 ”.dynamic” 段， 这个段里面保存了动态链接器所需要的基本信息，比如'依赖于哪些共享对象、动态链接符号表的位置、动态链接重定位表的位置、
共享对象初始化代码的地址'等。

”.dynamic” 段的结构 Elf64_Dyn 或 Elf32_Dyn 定义在 /usr/include/elf.h 文件中，如下:

~ » cd /usr/include                                             
--------------------------------------------------------------------------------
/usr/include » subl elf.h 

// !! ps: /usr/include linux 下开发和编译应用程序所需要的头文件  

/* Dynamic section entry.  */

typedef struct
{
  Elf32_Sword	d_tag;			/* Dynamic entry type */
  union
    {
      Elf32_Word d_val;			/* Integer value */
      Elf32_Addr d_ptr;			/* Address value */
    } d_un;
} Elf32_Dyn;

typedef struct
{
  Elf64_Sxword	d_tag;			/* Dynamic entry type */
  union
    {
      Elf64_Xword d_val;		/* Integer value */
      Elf64_Addr d_ptr;			/* Address value */
    } d_un;
} Elf64_Dyn;


Elf64_Dyn 或 Elf32_Dyn 结构由一个类型值加上一个附加的数值或指针，对于不同的类型，后面附加的数值或者指针有着不同的含义。这里列举几个比较常见的类型值
(这些值都是定义在”elf.h”里面的宏)，如下所示:

/usr/include » subl elf.h 

#define DT_NULL		0		/* Marks end of dynamic section */
#define DT_NEEDED	1		/* Name of needed library */
#define DT_PLTRELSZ	2		/* Size in bytes of PLT relocs */
#define DT_PLTGOT	3		/* Processor defined value */
#define DT_HASH		4		/* Address of symbol hash table */
#define DT_STRTAB	5		/* Address of string table */
#define DT_SYMTAB	6		/* Address of symbol table */
#define DT_RELA		7		/* Address of Rela relocs */
#define DT_RELASZ	8		/* Total size of Rela relocs */
#define DT_RELAENT	9		/* Size of one Rela reloc */
#define DT_STRSZ	10		/* Size of string table */
#define DT_SYMENT	11		/* Size of one symbol table entry */
#define DT_INIT		12		/* Address of init function */
#define DT_FINI		13		/* Address of termination function */
#define DT_SONAME	14		/* Name of shared object */
#define DT_RPATH	15		/* Library search path (deprecated) */
#define DT_SYMBOLIC	16		/* Start symbol search here */
#define DT_REL		17		/* Address of Rel relocs */
#define DT_RELSZ	18		/* Total size of Rel relocs */
#define DT_RELENT	19		/* Size of one Rel reloc */
#define DT_PLTREL	20		/* Type of reloc in PLT */
#define DT_DEBUG	21		/* For debugging; unspecified */


Linux 还提供了一个 ldd 命令用来查看程序主模块或一个共享库依赖于哪些共享库

// !! 动态符号表

在静态链接中，有一个专门的段叫做符号表”.symtab”(Symbol Table) '里面保存了所有关于该目标文件的符号的定义和引用'。动态链接的符号表示实际上它跟静态链接十分相似。比如
前面例子中的 Program1 程序依赖于 Lib.so，引用到了里面的 foobar() 函数。那么对于 Program1 来说，我们往往称 Program1 导入(Import)了 foobar() 函数，foobar 
是 Program1 的导入函数(Import Function)； 而站在 Lib.so 的角度来看，它实际上定义了 foobar() 函数，并且提供给其它模块使用，我们往往称 Lib.so 导出(Export)了
foobar() 函数，foobar() 是 Lib.so 的导出函数(Export Function)。

这种导入导出关系放到静态链接的情形下，我们可以把它们看作普通的函数定义和引用。

为了表示动态链接这些模块之间的符号导入导出关系，ELF 专门有一个叫做动态符号表(Dynamic Symbol Table)的段来保存这些信息，这个段的段名通常叫做 
”.dynsym”(Dynamic Symbol)。

”.dynsym” 只保存了与动态链接相关的符号, 对于那些模块内部的符号. 比如模块私有变量则不保存。很多时候动态链接的模块同时拥有”.dynsym”和”.symtab”两个表，”.symtab” 中往
往保存了所有符号，包括”.dynsym”中的符号。

与”.symtab”类似, 动态符号表也需要一些辅助的表, 比如用于保存符号名的字符串表。静态链接时叫做'符号字符串表' ”.strtab”(String Table), 在这里就是动态符号字符串表 
”.dynstr”(String Table), 在这里就是'动态符号字符串表' ”.dynstr” (Dynamic String Table)

由于动态链接下, 我们需要在程序运行时查找符号, 为了加快符号的查找过程往往还有辅助的符号哈希表(“.hash”)

我们可以用 readelf 工具来查看 ELF 文件的动态符号表及它的哈希表, 如下所示:

// !! 动态链接符号表的结构与静态链接的符号表几乎一样, 我们可以简单地将导入函数看作是对其它目标文件中函数的引用; 把导出函数看作是在本目标文件
// !! 定义的函数就可以了。

// !! 动态链接重定位表

'共享对象需要重定位的主要原因是导入符号的存在'。动态链接下, 无论是可执行文件或共享对象一旦它依赖于其它共享对象, 也就是说有导入的符号时, 那么它的代码或数据中就会有对
于导入符号的引用。在编译时这些导入符号的地址未知. 在静态链接中, 这些未知的地址引用在最终链接时被修正; 但是在动态链接中,导入符号的地址在运行时才确定, 所以'需要在运行时
将这些导入符号的引用修正即需要重定位'.


// !! 动态链接重定位相关结构

共享对象的重定位与前面”静态链接”中的目标文件的重定位是类似的. 唯一有区别的是目标文件的重定位是在静态链接时完成的, 而共享对象的重定位是在装载时完成的。
在静态链接中, 目标文件里面包含有专门用于表示重定位信息的重定位表, 比如 ”.rel.text” 表示是代码段的重定位表, ”.rel.data” 是数据段的重定位表。动态链接的文件中, 
也有类似的重定位表分别叫做 ”.rel.dyn”(“.rela.dyn”)和”.rel.plt”(“.rela.plt”), 它们分别相当于 ”.rel.text”和”.rel.data”。”.rel.dyn” 实际上是对数据引用的修正
,它所修正的位置位于 ”.got” 以及数据段; 而 ”.rel.plt” 是对函数引用的修正, 它所修正的位置位于”.got.plt”。

我们可以使用 readelf 来查看一个动态链接的文件的重定位表:

readelf -r Lib.so



// !! 动态链接时进程堆栈初始化信息

站在动态链接器的角度看, 当操作系统把控制权交给它的时候, 它将开始做链接工作, 那么至少它需要知道关于可执行文件和本进程的一些信息, 比如可执行文件有几个段(“Segment”)、
每个段的属性、程序的入口地址(因为动态链接器到时候需要把控制权交给可执行文件)等。这些信息往往由操作系统传递给动态链接器, 保存在进程的堆栈里面。

进程初始化的时候, 堆栈里面保存了关于进程执行环境和命令行参数等信息。事实上, 堆栈里面还保存了动态链接器所需要的一些辅助信息数组(Auxiliary Vector)。辅助信息的格式也是
一个结构数组, 它的结构定义在 ”/usr/include/elf.h”:

