// !! 3.4　ELF 文件结构描述

ELF 目标文件格式的最前部是 ELF文件头 (ELF Header), 它包含了描述整个文件的基本属性, 比如 ELF 文件版本、目标机器型号、程序入口地址等。紧接着是 ELF 文件各个段。其中
ELF 文件中与段有关的重要结构就是段表 (Section Header Table), 该表描述了 ELF 文件包含的所有段的信息, 比如每个段的段名、段的长度、在文件中的偏移、读写权限及段的其他
属性。

// !! 3.4.1　文件头

我们可以用 readelf 命令来详细查看 ELF 文件

查看 ELF 文件头:

readelf -h SimpleSection.o

ELF 头：
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  类别:                              ELF64
  数据:                              2 补码，小端序 (little endian)
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI 版本:                          0
  类型:                              REL (可重定位文件)
  系统架构:                          Advanced Micro Devices X86-64
  版本:                              0x1
  入口点地址：               0x0
  程序头起点：          0 (bytes into file)
  Start of section headers:          1184 (bytes into file)
  标志：             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           0 (bytes)
  Number of program headers:         0
  Size of section headers:           64 (bytes)
  Number of section headers:         14
  Section header string table index: 13

从上面输出的结果可以看到, ELF 的文件头中定义了 ELF 魔数、文件机器字节长度、数据存储方式、版本、运行平台、ABI 版本、ELF 重定位类型、硬件平台、硬件平台版本、入口地址、
程序头入口和长度、段表的位置和长度及段的数量等。

'ELF魔数'

我们可以从前面 readelf 的输出看到, 最前面的 Magic 的 16 个字节. '这种魔数用来确认文件的类型, 操作系统在加载可执行文件的时候会确认魔数是否正确, 如果不正确会拒绝加载'。

// !! 3.4.2　段表

我们知道 ELF 文件中有很多各种各样的段, 这个段表 (Section Header Table) 就是保存这些段的基本属性的结构。段表是 ELF 文件中除了文件头以外最重要的结构, 它描述了 ELF 的
各个段的信息，比如每个段的段名、段的长度、在文件中的偏移、读写权限及段的其他属性。'编译器、链接器和装载器都是依靠段表来定位和访问各个段的属性的'


我们可以使用 readelf 工具来查看 ELF 文件的段, 它显示出来的结果才是真正的段表结构:

readelf -S SimpleSection.o
There are 14 section headers, starting at offset 0x4a0:

节头：
  [号] 名称              类型             地址              偏移量
       大小              全体大小          旗标   链接   信息   对齐
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         0000000000000000  00000040
       000000000000005f  0000000000000000  AX       0     0     1
  [ 2] .rela.text        RELA             0000000000000000  00000380
       0000000000000078  0000000000000018   I      11     1     8
  [ 3] .data             PROGBITS         0000000000000000  000000a0
       0000000000000008  0000000000000000  WA       0     0     4
  [ 4] .bss              NOBITS           0000000000000000  000000a8
       0000000000000004  0000000000000000  WA       0     0     4
  [ 5] .rodata           PROGBITS         0000000000000000  000000a8
       0000000000000004  0000000000000000   A       0     0     1
  [ 6] .comment          PROGBITS         0000000000000000  000000ac
       000000000000002c  0000000000000001  MS       0     0     1
  [ 7] .note.GNU-stack   PROGBITS         0000000000000000  000000d8
       0000000000000000  0000000000000000           0     0     1
  [ 8] .note.gnu.propert NOTE             0000000000000000  000000d8
       0000000000000020  0000000000000000   A       0     0     8
  [ 9] .eh_frame         PROGBITS         0000000000000000  000000f8
       0000000000000058  0000000000000000   A       0     0     8
  [10] .rela.eh_frame    RELA             0000000000000000  000003f8
       0000000000000030  0000000000000018   I      11     9     8
  [11] .symtab           SYMTAB           0000000000000000  00000150
       00000000000001b0  0000000000000018          12    12     8
  [12] .strtab           STRTAB           0000000000000000  00000300
       000000000000007c  0000000000000000           0     0     1
  [13] .shstrtab         STRTAB           0000000000000000  00000428
       0000000000000074  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  l (large), p (processor specific)

readelf 输出的结果就是 ELF 文件段表的内容, 那么就让我们对照这个输出来看看段表的结构。


段的类型 (sh_type) 正如前面所说的, 段的名字只是在链接和编译过程中有意义, 但它不能真正地表示段的类型。我们也可以将一个数据段命名为 .text, 对于编译器和链接器来说, 主要
决定段的属性的是段的类型 (sh_type) 和段的标志位 (sh_flags)。

段的标志位 (sh_flag) 段的标志位表示该段在进程虚拟地址空间中的属性, 比如是否可写, 是否可执行等。


// !! 3.4.3 重定位表

我们注意到, SimpleSection.o 中有一个叫做 .rel.text 的段, 它的类型 (sh_type) 为 SHT_REL, 也就是说它是一个重定位表(Relocation Table)。
正如我们最开始所说的, 链接器在处理目标文件时, 须要对目标文件中某些部位进行重定位, 即代码段和数据段中那些对绝对地址的引用的位置。这些重定位的信息都记录在 ELF 文件的重定
位表里面, 对于每个须要重定位的代码段或数据段, 都会有一个相应的重定位表。

比如 SimpleSection.o 中的 .rela.text 就是针对 .text 段的重定位表, 因为 .text 段中至少有一个绝对地址的引用, 那就是对 printf 函数的调用; 而 .data 段则没有对绝对
地址的引用, 它只包含了几个常量, 所以 SimpleSection.o 中没有针对 .data 段的重定位表 .rel.data。


// !! 3.4.4　字符串表

ELF 文件中用到了很多字符串, 比如段名、变量名等。因为字符串的长度往往是不定的, 所以用固定的结构来表示它比较困难。一种很常见的做法是把字符串集中起来存放到一个表, 然后使用
字符串在表中的偏移来引用字符串。