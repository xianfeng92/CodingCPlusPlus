
// !! 链接过程控制

整个链接过程有很多内容需要确定：使用哪些目标文件？ 使用哪些库文件？ 是否在最终可执行文件中保留调试信息、输出文件格式（可执行文件还是动态链接库）？
还要考虑是否导出某些符合以供调试器、程序本身或其他程序使用。

操作系统内核从本质上讲，它也是一个程序，其实也就是一个文件。


各个链接器平台的链接控制过程各不相同,这里介绍的为 ld：

1. -static 表示使用静态链接方式来链接程序，而不是用默认的动态链接的方式

2. -e 指定该程序的入口函数

3. -o 指定输出文件名

4. -T 指定链接控制脚本

// !! 链接控制脚本

链接器一般都提供多种控制整个链接过程的方法, 以产生用户所需的文件， 一般有如下三种方法:

1. 使用命令行给链接器指定参数，如 -e指定入口函数

2. 将链接指令存放在目标文件里， 编译器经常会通过这种方法给链接器传递指令

3. 使用链接控制脚本，这种比较灵活和强大，使用 -T 指定脚本

无论是输入文件还是输出文件，它们的主要数据就是文件中的各种 section，我们把输入文件中的 section 称为 input sections(输入段)，输出文件中的 
section 称为 output sections(输出段)。简单来说, 控制链接过程无非就是控制输入段如何变成输出段，如哪些 section 要丢弃，合并的顺序等

使用链接器时，如果没有指定链接脚本，则会使用一个默认的链接脚本。

~ » ld --verbose                                               
GNU ld (GNU Binutils for Ubuntu) 2.34
  支持的仿真：
   elf_x86_64
   elf32_x86_64
   elf_i386
   elf_iamcu
   elf_l1om
   elf_k1om
   i386pep
   i386pe
使用内部链接脚本：
==================================================
/* Script for -z combreloc -z separate-code */
/* Copyright (C) 2014-2020 Free Software Foundation, Inc.
   Copying and distribution of this script, with or without modification,
   are permitted in any medium without royalty provided the copyright
   notice and this notice are preserved.  */


