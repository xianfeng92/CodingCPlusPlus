
// !! 文件头（ELF Header）

使用 readelf 读取 ELF 头文件信息

参考：readelf --help

readelf 的 -h 参数表示 Display the ELF file header

» readelf -h SimpleSection.o

ELF 头：
  Magic：   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
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

 » readelf -h libjsoncpp.so.1.9.4 
ELF 头：
  Magic：   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  类别:                              ELF64
  数据:                              2 补码，小端序 (little endian)
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI 版本:                          0
  类型:                              DYN (共享目标文件)
  系统架构:                          AArch64
  版本:                              0x1
  入口点地址：               0xe730
  程序头起点：          64 (bytes into file)
  Start of section headers:          291528 (bytes into file)
  标志：             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         6
  Size of section headers:           64 (bytes)
  Number of section headers:         35
  Section header string table index: 32


  1. Start of section headers 表示 段表的位置

  2. Section header string table index 表示 


// !! ELF段表

我们知道 ELF 文件中有各种各样的段，这个段表（Section Header Table）就是保存这些段的基本属性的结构。段表是 ELF 文件中除文件头
（ELF Header）以外最重要的结构， 它描述了各个段的信息，比如每个段的段名、段的长度、在文件中的偏移、读写权限等

也就是说 ELF 的段结构是由段表决定的，'编译器、链接器、装载器都是根据段表来定位和访问各个段的属性'。

readelf 的 -S 参数 Display the sections' header'

» readelf -S SimpleSection.o 

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
       000000000000002b  0000000000000001  MS       0     0     1
  [ 7] .note.GNU-stack   PROGBITS         0000000000000000  000000d7
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
--------------------------------------------

1. 段的类型

    PROGBITS----> 程序段。代码段和数据段都是这种类型

    SYMTAB ----> 表示段的内容为符号表

    NULL ----> 无效段

    RELA -----> 重定位表，该段包含重定位信息

    NOTE -----> 提示性信息

    NOBITS -----> 表示该段在文件中没有内容，如 .bss

    
2. 重定位表
   .rela.text  就是为一个重定位表（Relocation Table）。链接器在处理目标文件时，需要对目标文件的默写部分进行重定位。
   对于需要重定位的代码段或者数据段都会有一个相对应的重定位表，如： .text  ------> .rela.text


3. 字符串表

    ELF 文件中用到了很多字符串，比如段名和变量名。一般字符串表在 ELF 中也是以段的形式保存，常见的有：.strtab（字符串表），.shstrtab （段表字符串表）
    .strtab（字符串表）-----> 用来保存普通字符串,比如符号的名字
    .shstrtab （段表字符串表） -------> 用来保存段表中用到的字符串，常见的是段名（sh_name）



// !! 只有分析 ELF 的文件头，就可以得到段表以及段表字符串表，从而解析整个 ELF 文件