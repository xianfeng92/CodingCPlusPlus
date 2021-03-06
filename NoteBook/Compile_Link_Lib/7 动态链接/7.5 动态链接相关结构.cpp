// !! 7.5　动态链接相关结构

动态链接情况下, 可执行文件的装载与静态链接情况基本一样。

首先操作系统会读取可执行文件的头部, 检查文件的合法性, 然后从头部中的 Program Header 中读取每个 Segment 的虚拟地址、文件地址和属性, 并将它们映射到进程虚拟空间的相应
位置, 这些步骤跟前面的静态链接情况下的装载基本无异。'在静态链接情况下, 操作系统接着就可以把控制权转交给可执行文件的入口地址, 然后程序开始执行', 一切看起来非常直观。

但是在动态链接情况下, 操作系统还不能在装载完可执行文件之后就把控制权交给可执行文件, 因为我们知道可执行文件依赖于很多共享对象。这时候, 可执行文件里对于很多外部符号的引用
还处于无效地址的状态, 即还没有跟相应的共享对象中的实际位置链接起来。

所以在映射完可执行文件之后, 操作系统会先启动一个动态链接器 (Dynamic Linker)。

'在 Linux 下, 动态链接器 ld.so 实际上是一个共享对象, 操作系统同样通过映射的方式将它加载到进程的地址空间中'。

操作系统在加载完动态链接器之后, 就将控制权交给动态链接器的入口地址(与可执行文件一样, 共享对象也有入口地址)。'当动态链接器得到控制权之后, 它开始执行一系列自身的初始化操作
, 然后根据当前的环境参数, 开始对可执行文件进行动态链接工作'。当所有动态链接工作完成以后, 动态链接器会将控制权转交到可执行文件的入口地址, 程序开始正式执行。

// !! 7.5.1　.interp 段

那么系统中哪个才是动态链接器呢, 它的位置由谁决定? 是不是所有的 *NIX 系统的动态链接器都位于 /lib/ld.so 呢? 实际上, 动态链接器的位置既不是由系统配置指定, 也不是由环境
参数决定, 而是由 ELF 可执行文件决定。

在动态链接的 ELF 可执行文件中, 有一个专门的段叫做 .interp 段 (interp 是 interpreter (解释器) 的缩写)。如果我们使用 objdump 工具来查看, 可以看到 .interp 内
容:

> objdump -s Program1

Program1:     文件格式 elf64-x86-64

Contents of section .interp:
 0318 2f6c6962 36342f6c 642d6c69 6e75782d  /lib64/ld-linux-
 0328 7838362d 36342e73 6f2e3200           x86-64.so.2

.interp 的内容很简单, 里面保存的就是一个字符串, 这个字符串就是可执行文件所需要的动态链接器的路径, 在 Linux 下, 可执行文件所需要的动态链接器的路径几乎都是
/lib64/ld-linux- x86-64.so.2


在 Linux 的系统中, /lib64/ld-linux- x86-64.so.2 通常是一个软链接:

ld-linux-x86-64.so.2 -> /lib/x86_64-linux-gnu/ld-2.31.so

在 Linux 中, 操作系统在对可执行文件的进行加载的时候, 它会去寻找装载该可执行文件所需要相应的动态链接器, 即 .interp 段指定的路径的共享对象。

'动态链接器在 Linux 下是 Glibc 的一部分, 也就是属于系统库级别的, 它的版本号往往跟系统中的 Glibc 库版本号是一样的'

当系统中的 Glibc 库更新或者安装其他版本的时候, /lib64/ld-linux- x86-64.so.2 这个软链接就会指向到新的动态链接器, 而可执行文件本身不需要修改 .interp 中的动态链接器
路径来适应系统的升级。

> getconf GNU_LIBC_VERSION
glibc 2.31

> ls -li

ld-linux-x86-64.so.2 -> /lib/x86_64-linux-gnu/ld-2.31.so

我们也可以用这个命令来查看一个可执行文件所需要的动态链接器的路径, 在 Linux下, 往往是如下结果:


> readelf -l Program1 | grep interpreter
      [Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]



// !! 7.5.2 .dynamic 段

类似于 .interp 这样的段, ELF 中还有几个段也是专门用于动态链接的, 比如 .dynamic 段和 .dynsym 段等。

动态链接 ELF 中最重要的结构应该是 .dynamic 段, 这个段里面保存了动态链接器所需要的基本信息, 比如依赖于哪些共享对象、动态链接符号表的位置、动态链接重定位表的位置、
共享对象初始化代码的地址等。

.dynamic 段的结构很经典, 就是我们已经碰到过的 ELF 中眼熟的结构数组, 结构定义在 elf.h 中:

typedef struct {
    Elf32_Sword d_tag;
    union {
        Elf32_Sword d_val;
        Elf32_Addr d_ptr;
    } d_un;
} Elf32_Dyn;

Elf32_Dyn 结构由一个类型值加上一个附加的数值或指针, 对于不同的类型, 后面附加的数值或者指针有着不同的含义。

这里列举几个比较常见的类型值, 如表 7-2 所示:

从上面给出的这些定义来看, '.dynamic 段里面保存的信息有点像 ELF 文件头, 只是我们前面看到的 ELF 文件头中保存的是静态链接时相关的内容, 比如静态链接时用到的符号表、重定位
表等, 这里换成了动态链接下所使用的相应信息了'。

使用 readelf 工具可以查看 .dynamic 段的内容:

> readelf -d Lib.so 

Dynamic section at offset 0x2e20 contains 24 entries:
  标记        类型                         名称/值
 0x0000000000000001 (NEEDED)             共享库：[libc.so.6]
 0x000000000000000c (INIT)               0x1000
 0x000000000000000d (FINI)               0x1170
 0x0000000000000019 (INIT_ARRAY)         0x3e10
 0x000000000000001b (INIT_ARRAYSZ)       8 (bytes)
 0x000000000000001a (FINI_ARRAY)         0x3e18
 0x000000000000001c (FINI_ARRAYSZ)       8 (bytes)
 0x000000006ffffef5 (GNU_HASH)           0x2f0
 0x0000000000000005 (STRTAB)             0x3d8
 0x0000000000000006 (SYMTAB)             0x318
 0x000000000000000a (STRSZ)              127 (bytes)
 0x000000000000000b (SYMENT)             24 (bytes)
 0x0000000000000003 (PLTGOT)             0x4000
 0x0000000000000002 (PLTRELSZ)           48 (bytes)
 0x0000000000000014 (PLTREL)             RELA
 0x0000000000000017 (JMPREL)             0x530
 0x0000000000000007 (RELA)               0x488
 0x0000000000000008 (RELASZ)             168 (bytes)
 0x0000000000000009 (RELAENT)            24 (bytes)
 0x000000006ffffffe (VERNEED)            0x468
 0x000000006fffffff (VERNEEDNUM)         1
 0x000000006ffffff0 (VERSYM)             0x458
 0x000000006ffffff9 (RELACOUNT)          3
 0x0000000000000000 (NULL)               0x0

另外 Linux 还提供了一个命令用来查看一个程序主模块或一个共享库依赖于哪些共享库:

> ldd Lib.so 
	linux-vdso.so.1 (0x00007ffc93d35000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f905e1db000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f905e3ea000)



// !! 7.5.3 动态符号表

为了完成动态链接, 最关键的还是所依赖的符号和相关文件的信息。我们知道在静态链接中, 有一个专门的段叫做符号表 .symtab (Symbol Table), 里面保存了所有关于该目标文件的符
号的定义和引用。

动态链接的符号表示实际上它跟静态链接十分相似, 比如前面例子中的 Program1 程序依赖于 Lib.so, 引用到了里面的 foobar() 函数。那么对于 Program1 来说, 我们往往称
Program1 导入 (Import) 了 foobar 函数, foobar 是 Program1 的导入函数 (Import Function); 而站在 Lib.so 的角度来看, 它实际上定义了 foobar() 函数, 并且提供给
其他模块使用, 我们往往称 Lib.so 导出 (Export) 了 foobar() 函数, foobar 是 Lib.so 的导出函数 (Export Function)。

为了表示动态链接这些模块之间的符号导入导出关系, ELF 专门有一个叫做动态符号表 (Dynamic Symbol Table) 的段用来保存这些信息, 这个段的段名通常叫做 .dynsym (Dynamic 
Symbol)。

与 .symtab 不同的是, .dynsym 只保存了与动态链接相关的符号, 对于那些模块内部的符号, 比如模块私有变量则不保存。

很多时候动态链接的模块同时拥有 .dynsym 和 .symtab 两个表, .symtab 中往往保存了所有符号, 包括 .dynsym 中的符号。

与 .symtab 类似, 动态符号表也需要一些辅助的表, 比如用于保存符号名的字符串表。静态链接时叫做符号字符串表 .strtab (String Table), 在这里就是动态符号字符串表 
.dynstr (Dynamic String Table);

'由于动态链接下, 我们需要在程序运行时查找符号, 为了加快符号的查找过程, 往往还有辅助的符号哈希表 (.hash)'。

我们可以用 readelf 工具来查看 ELF 文件的动态符号表及它的哈希表:

>readelf -sD Lib.so 

Symbol table of '.gnu.hash' for image:
  Num Buc:    Value          Size   Type   Bind Vis      Ndx Name
    7   0: 0000000000001139    55 FUNC    GLOBAL DEFAULT  14 foobar


动态链接符号表的结构与静态链接的符号表几乎一样, 我们可以简单地将导入函数看作是对其他目标文件中函数的引用; 把导出函数看作是在本目标文件定义的函数就可以了。


// !!7.5.4　动态链接重定位表

'共享对象需要重定位的主要原因是导入符号的存在'。动态链接下, 无论是可执行文件或共享对象, 一旦它依赖于其他共享对象, 也就是说有导入的符号时, 那么它的代码或数据中就会有对于
导入符号的引用。

在编译时这些导入符号的地址未知, 在静态链接中, 这些未知的地址引用在最终链接时被修正。

'在动态链接中, 导入符号的地址在运行时才确定, 所以需要在运行时将这些导入符号的引用修正, 即需要重定位'。

对于动态链接来说, 如果一个共享对象不是以 PIC 模式编译的, 那么毫无疑问, 它是需要在装载时被重定位的; 如果一个共享对象是 PIC 模式编译的, 那么它还需要在装载时进行重定位吗?
是的, PIC 模式的共享对象也需要重定位。


对于使用 PIC 技术的可执行文件或共享对象来说, 虽然它们的代码段不需要重定位 (因为地址无关), 但是数据段还包含了绝对地址的引用, 因为代码段中绝对地址相关的部分被分离了出来, 
变成了 GOT, 而 GOT 实际上是数据段的一部分。除了 GOT 以外, 数据段还可能包含绝对地址引用


// !! 动态链接重定位相关结构

在静态链接中, 目标文件里面包含有专门用于表示重定位信息的重定位表, 比如 .rel.text 表示是代码段的重定位表, .rel.data 是数据段的重定位表。


动态链接的文件中, 也有类似的重定位表分别叫做 .rel.plt  和 .rel.dyn, 它们分别相当于 .rel.text 和 .rel.data。

'.rel.dyn 实际上是对数据引用的修正, 它所修正的位置位于 .got 以及数据段; 而 .rel.plt 是对函数引用的修正, 它所修正的位置位于 .got.plt'。

我们可以使用 readelf 来查看一个动态链接的文件的重定位表:


> readelf -r Lib.so

重定位节 '.rela.dyn' at offset 0x488 contains 7 entries:
  偏移量          信息           类型           符号值        符号名称 + 加数
000000003e10  000000000008 R_X86_64_RELATIVE                    1130
000000003e18  000000000008 R_X86_64_RELATIVE                    10f0
000000004028  000000000008 R_X86_64_RELATIVE                    4028
000000003fe0  000100000006 R_X86_64_GLOB_DAT 0000000000000000 _ITM_deregisterTMClone + 0
000000003fe8  000300000006 R_X86_64_GLOB_DAT 0000000000000000 __gmon_start__ + 0
000000003ff0  000400000006 R_X86_64_GLOB_DAT 0000000000000000 _ITM_registerTMCloneTa + 0
000000003ff8  000600000006 R_X86_64_GLOB_DAT 0000000000000000 __cxa_finalize@GLIBC_2.2.5 + 0

重定位节 '.rela.plt' at offset 0x530 contains 2 entries:
  偏移量          信息           类型           符号值        符号名称 + 加数
000000004018  000200000007 R_X86_64_JUMP_SLO 0000000000000000 printf@GLIBC_2.2.5 + 0
000000004020  000500000007 R_X86_64_JUMP_SLO 0000000000000000 sleep@GLIBC_2.2.5 + 0

readelf -S Lib.so
There are 30 section headers, starting at offset 0x37f8:

节头：
  [号] 名称              类型             地址              偏移量
       大小              全体大小          旗标   链接   信息   对齐
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .note.gnu.propert NOTE             00000000000002a8  000002a8
       0000000000000020  0000000000000000   A       0     0     8
  [ 2] .note.gnu.build-i NOTE             00000000000002c8  000002c8
       0000000000000024  0000000000000000   A       0     0     4
  [ 3] .gnu.hash         GNU_HASH         00000000000002f0  000002f0
       0000000000000024  0000000000000000   A       4     0     8
  [ 4] .dynsym           DYNSYM           0000000000000318  00000318
       00000000000000c0  0000000000000018   A       5     1     8
  [ 5] .dynstr           STRTAB           00000000000003d8  000003d8
       000000000000007f  0000000000000000   A       0     0     1
  [ 6] .gnu.version      VERSYM           0000000000000458  00000458
       0000000000000010  0000000000000002   A       4     0     2
  [ 7] .gnu.version_r    VERNEED          0000000000000468  00000468
       0000000000000020  0000000000000000   A       5     1     8
  [ 8] .rela.dyn         RELA             0000000000000488  00000488
       00000000000000a8  0000000000000018   A       4     0     8
  [ 9] .rela.plt         RELA             0000000000000530  00000530
       0000000000000030  0000000000000018  AI       4    23     8
  [10] .init             PROGBITS         0000000000001000  00001000
       000000000000001b  0000000000000000  AX       0     0     4
  [11] .plt              PROGBITS         0000000000001020  00001020
       0000000000000030  0000000000000010  AX       0     0     16
  [12] .plt.got          PROGBITS         0000000000001050  00001050
       0000000000000010  0000000000000010  AX       0     0     16
  [13] .plt.sec          PROGBITS         0000000000001060  00001060
       0000000000000020  0000000000000010  AX       0     0     16
  [14] .text             PROGBITS         0000000000001080  00001080
       00000000000000f0  0000000000000000  AX       0     0     16
  [15] .fini             PROGBITS         0000000000001170  00001170
       000000000000000d  0000000000000000  AX       0     0     4
  [16] .rodata           PROGBITS         0000000000002000  00002000
       0000000000000019  0000000000000000   A       0     0     1
  [17] .eh_frame_hdr     PROGBITS         000000000000201c  0000201c
       000000000000002c  0000000000000000   A       0     0     4
  [18] .eh_frame         PROGBITS         0000000000002048  00002048
       0000000000000094  0000000000000000   A       0     0     8
  [19] .init_array       INIT_ARRAY       0000000000003e10  00002e10
       0000000000000008  0000000000000008  WA       0     0     8
  [20] .fini_array       FINI_ARRAY       0000000000003e18  00002e18
       0000000000000008  0000000000000008  WA       0     0     8
  [21] .dynamic          DYNAMIC          0000000000003e20  00002e20
       00000000000001c0  0000000000000010  WA       5     0     8
  [22] .got              PROGBITS         0000000000003fe0  00002fe0
       0000000000000020  0000000000000008  WA       0     0     8
  [23] .got.plt          PROGBITS         0000000000004000  00003000
       0000000000000028  0000000000000008  WA       0     0     8
  [24] .data             PROGBITS         0000000000004028  00003028
       0000000000000008  0000000000000000  WA       0     0     8
  [25] .bss              NOBITS           0000000000004030  00003030
       0000000000000008  0000000000000000  WA       0     0     1
  [26] .comment          PROGBITS         0000000000000000  00003030
       000000000000002b  0000000000000001  MS       0     0     1
  [27] .symtab           SYMTAB           0000000000000000  00003060
       00000000000004f8  0000000000000018          28    46     8
  [28] .strtab           STRTAB           0000000000000000  00003558
       0000000000000192  0000000000000000           0     0     1
  [29] .shstrtab         STRTAB           0000000000000000  000036ea
       000000000000010d  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  l (large), p (processor specific)


在静态链接中我们已经碰到过两种类型的重定位入口 R_386_32 和 R_386_PC32, 这里可以看到几种新的重定位入口类型: R_X86_64_RELATIVE 、 R_X86_64_GLOB_DAT 和
R_X86_64_JUMP_SLO。

实际上这些不同的重定位类型表示重定位时有不同的地址计算方法;

我们先来看看 R_X86_64_GLOB_DAT 和 R_X86_64_JUMP_SLO, 这两个类型的重定位入口表示, 被修正的位置只需要直接填入符号的地址即可。

比如我们看 printf 这个重定位入口, 它的类型为 R_X86_64_JUMP_SLO, 它的偏移为 000000004018, 它实际上位于 .got.plt 中。

我们知道, .got.plt 的前三项是被系统占据的, 从第四项开始才是真正存放导入函数地址的地方。而第四项刚好是 0x000015c8 + 4 * 3 = 0x000015d4, 即 __gmon_start__, 第五
项是 printf, 第六项是 sleep, 第七项是 __cxa_finalize。所以 Lib.so 的 .got.plt 的结构如图 7-10 所示。

当动态链接器需要进行重定位时, 它先查找 printf 的地址, printf 位于 libc-2.6.1.so。

假设链接器在全局符号表里面找到 printf 的地址为 0x08801234, 那么链接器就会将这个地址填入到 .got.plt 中的偏移为 0x000015d8 的位置中去, 从而实现了地址的重定位, 即
实现了动态链接最关键的一个步骤。



// !! 7.5.5　动态链接时进程堆栈初始化信息

站在动态链接器的角度看, 当操作系统把控制权交给它的时候, 它将开始做链接工作, 那么至少它需要知道关于可执行文件和本进程的一些信息, 比如可执行文件有几个段 (Segment)、每个段
的属性、程序的入口地址 (因为动态链接器到时候需要把控制权交给可执行文件) 等。

这些信息往往由操作系统传递给动态链接器, 保存在进程的堆栈里面。

我们在前面提到过, 进程初始化的时候, 堆栈里面保存了关于进程执行环境和命令行参数等信息。'事实上, 堆栈里面还保存了动态链接器所需要的一些辅助信息数组 (Auxiliary Vector)'。

辅助信息的格式也是一个结构数组, 它的结构被定义在 elf.h:

typedef struct {
    unit32_t a_type;
    union {
        unit32_t a_val;
    } a_un;
} Elf32_auxv_t;

是不是已经对这种结构很熟悉了? 没错, 跟前面的 .dynamic 段里面的结构如出一辙。先是一个 32 位的类型值, 后面是一个 32 位的数值部分。你可能会很奇怪为什么要用一个 union 把
后面的 32 位数值包装起来, 事实上这个 union 没什么用, 只是历史遗留而已, 可以当作不存在。

我们摘录几个比较重要的类型值, 这几个类型值是比较常见的, 而且是动态链接器在启动时所需要的, 如表 7-3 所示。


介绍了这么多关于辅助信息数组的结构, 我们还没看到它到底位于进程堆栈的哪个位置呢。事实上, 它位于环境变量指针的后面。

比如我们假设操作系统传给动态链接器的辅助信息有 4 个, 分别是:

• AT_PHDR, 值为0x08048034, 程序表头位于 0x08048034

• AT_PHENT, 值为 20, 程序表头中每个项的大小为 20 字节

• AT_PHNUM, 值为7, 程序表头共有 7 个项

• AT_ENTRY, 0x08048320, 程序入口地址为 0x08048320

