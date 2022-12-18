
# Binutils

The GNU Binutils are a collection of binary tools. The main ones are:

1. ld - the GNU linker.
2. as - the GNU assembler.
3. gold - a new, faster, ELF only linker.

But they also include:

1. addr2line - Converts addresses into filenames and line numbers.

2. ar - A utility for creating, modifying and extracting from archives.

3. c++filt - Filter to demangle encoded C++ symbols.

4. dlltool - Creates files for building and using DLLs.

5. elfedit - Allows alteration of ELF format files.

6. gprof - Displays profiling information.

7. gprofng - Collects and displays application performance data.

8. nlmconv - Converts object code into an NLM.

9. nm - Lists symbols from object files.

10. objcopy - Copies and translates object files.

11. objdump - Displays information from object files.

12. readelf - Displays information from any ELF format object file.

13. size - Lists the section sizes of an object or archive file.

14. strings - Lists printable strings from files.

15. strip - Discards symbols.


## readelf：显示 ELF 文件信息

  BinUtils git:(main) ✗ readelf -h hello.o
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (Relocatable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x0
  Start of program headers:          0 (bytes into file)
  Start of section headers:          600 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           0 (bytes)
  Number of program headers:         0
  Size of section headers:           64 (bytes)
  Number of section headers:         14
  Section header string table index: 13

➜  BinUtils git:(main) ✗ readelf -h a.out  
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              DYN (Position-Independent Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x1060
  Start of program headers:          64 (bytes into file)
  Start of section headers:          13976 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         13
  Size of section headers:           64 (bytes)
  Number of section headers:         31
  Section header string table index: 30
➜  BinUtils git:(main) ✗ 

readelf 命令可提供有关二进制文件的大量信息。在这里, 它会告诉你它是 ELF 64 位格式, 这意味着它只能在 64 位 CPU 上执行, 而不能在 32 位 CPU 上运行。它还告诉你它应在 
X86-64（Intel/AMD）架构上执行。

在你知道的其他系统二进制文件上尝试一下 readelf 命令，例如 ls。

➜  BinUtils git:(main) ✗ readelf -h /usr/bin/ls
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              DYN (Position-Independent Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x6ab0
  Start of program headers:          64 (bytes into file)
  Start of section headers:          136224 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         13
  Size of section headers:           64 (bytes)
  Number of section headers:         31
  Section header string table index: 30

使用 ldd 命令了解 ls 命令所依赖的系统库，如下所示:

  ➜  BinUtils git:(main) ✗ ldd /usr/bin/ls
        linux-vdso.so.1 (0x00007fff171fd000)
        libselinux.so.1 => /lib/x86_64-linux-gnu/libselinux.so.1 (0x00007f87bdbdc000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f87bd9b4000)
        libpcre2-8.so.0 => /lib/x86_64-linux-gnu/libpcre2-8.so.0 (0x00007f87bd91d000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f87bdc40000)

对 libc 库文件运行 readelf 以查看它是哪种文件。

➜  BinUtils git:(main) ✗ readelf -h /lib/x86_64-linux-gnu/libc.so.6             
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 03 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - GNU
  ABI Version:                       0
  Type:                              DYN (Shared object file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x29f50
  Start of program headers:          64 (bytes into file)
  Start of section headers:          2212080 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         14
  Size of section headers:           64 (bytes)
  Number of section headers:         66
  Section header string table index: 65


## size：列出节的大小和全部大小

➜  BinUtils git:(main) ✗ size hello.o                      
   text    data     bss     dec     hex filename
    130       0       0     130      82 hello.o

对目标文件和可执行文件运行 size 命令。请注意, 根据 size 命令的输出可以看出: 可执行文件（a.out）的信息要比目标文件（hello.o）多得多

➜  BinUtils git:(main) ✗ size a.out  
   text    data     bss     dec     hex filename
   1374     600       8    1982     7be a.out

但是这里的 text、data 和 bss 节是什么意思？

text 节是指二进制文件的代码部分, 其中包含所有可执行指令。data 节是所有初始化数据所在的位置, bss 节是所有未初始化数据的存储位置。一般来说, 在静态的映像文件中, 各个部分称之为 节(section), 而在运行时的各个部分称之为 段(segment), 有时统称为段。


比较其他一些可用的系统二进制文件的 size 结果。

➜  BinUtils git:(main) ✗ size /usr/bin/ls
   text    data     bss     dec     hex filename
 120464    4720    4800  129984   1fbc0 /usr/bin/ls

只需查看 size 命令的输出，你就可以看到 gcc 和 gdb 是比 ls 大得多的程序:

➜  BinUtils git:(main) ✗ size /usr/bin/gcc
   text    data     bss     dec     hex filename
 842013    8696   14224  864933   d32a5 /usr/bin/gcc
➜  BinUtils git:(main) ✗ size /usr/bin/gdb
   text    data     bss     dec     hex filename
9351198  921056  124656 10396910         9ea4ee /usr/bin/gdb

## strings：打印文件中的可打印字符串

在 strings 命令中添加 -d 标志以仅显示 data 节中的可打印字符通常很有用。


➜  BinUtils git:(main) ✗ strings -d hello.o
Hello World

另一方面，在 a.out（可执行文件）上运行 strings 会显示在链接阶段该二进制文件中包含的其他信息:

➜  BinUtils git:(main) ✗ strings -d a.out
/lib64/ld-linux-x86-64.so.2
__cxa_finalize
__libc_start_main
puts
libc.so.6
GLIBC_2.2.5
GLIBC_2.34
_ITM_deregisterTMCloneTable
__gmon_start__
_ITM_registerTMCloneTable
PTE1
u+UH
Hello World
:*3$"

## objdump：显示目标文件信息

另一个可以从二进制文件中转储机器语言指令的 binutils 工具称为 objdump。使用 -d 选项, 可从二进制文件中反汇编出所有汇编指令。

编译是将源代码指令转换为机器代码的过程。机器代码仅由 1 和 0 组成, 人类难以阅读。因此, 它有助于将机器代码表示为汇编语言指令。汇编语言是什么样的? 请记住, 汇编语言是特定于体系结构的;
由于我使用的是 Intel（x86-64）架构, 因此如果你使用 ARM 架构编译相同的程序, 指令将有所不同。

➜  BinUtils git:(main) ✗ objdump  -d hello.o       

hello.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
   0:   f3 0f 1e fa             endbr64 
   4:   55                      push   %rbp
   5:   48 89 e5                mov    %rsp,%rbp
   8:   48 8d 05 00 00 00 00    lea    0x0(%rip),%rax        # f <main+0xf>
   f:   48 89 c7                mov    %rax,%rdi
  12:   e8 00 00 00 00          call   17 <main+0x17>
  17:   b8 00 00 00 00          mov    $0x0,%eax
  1c:   5d                      pop    %rbp
  1d:   c3                      ret    
➜  BinUtils git:(main) ✗ 

该输出乍一看似乎令人生畏, 但请花一点时间来理解它, 然后再继续。回想一下, .text 节包含所有的机器代码指令。汇编指令可以在第四列中看到（即 push、mov、call、pop、ret 等）。这些指令作
用于寄存器, 寄存器是 CPU 内置的存储器位置。


现在对可执行文件（a.out）运行 objdump 并查看得到的内容。可执行文件的 objdump 的输出可能很大, 因此我使用 grep 命令将其缩小到 main 函数：

➜  BinUtils git:(main) ✗ objdump  -d a.out | grep -A 9 main\>
...
--
0000000000001149 <main>:
    1149:       f3 0f 1e fa             endbr64 
    114d:       55                      push   %rbp
    114e:       48 89 e5                mov    %rsp,%rbp
    1151:       48 8d 05 ac 0e 00 00    lea    0xeac(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    1158:       48 89 c7                mov    %rax,%rdi
    115b:       e8 f0 fe ff ff          call   1050 <puts@plt>
    1160:       b8 00 00 00 00          mov    $0x0,%eax
    1165:       5d                      pop    %rbp
    1166:       c3                      ret    
➜  BinUtils git:(main) ✗ 


请注意, 这些指令与目标文件 hello.o 相似, 但是其中包含一些其他信息:

目标文件 hello.o 具有以下指令：call 17 <main+0x17>

可执行文件 a.out 由以下指令组成，该指令带有一个地址和函数：call   1050 <puts@plt>
上面的汇编指令正在调用 puts 函数。请记住, 你在源代码中使用了一个 printf 函数。编译器插入了对 puts 库函数的调用，以将 Hello World 输出到屏幕。

查看 put 上方一行的说明：

➜  BinUtils git:(main) ✗ readelf -x .rodata a.out

Hex dump of section '.rodata':
  0x00002000 01000200 48656c6c 6f20576f 726c6400 ....Hello World.

## strip：从目标文件中剥离符号

该命令通常用于在将二进制文件交付给客户之前减小二进制文件的大小。请记住, 由于重要信息已从二进制文件中删除, 因此它会妨碍调试。但是, 这个二进制文件可以完美地执行。


对 a.out 可执行文件运行该命令, 并注意会发生什么。首先, 通过运行以下命令确保二进制文件没有被剥离（not stripped）：

➜  BinUtils git:(main) ✗ file a.out
a.out: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=909b87f11b30d751c291b98d2390db0cbe10b4c6, for GNU/Linux 3.2.0, with debug_info, not stripped

在运行 strip 命令之前，请记下二进制文件中最初的字节数:

➜  BinUtils git:(main) ✗ du -b a.out
17040   a.out

现在对该可执行文件运行 strip 命令, 并使用 file 命令以确保正常完成：

➜  BinUtils git:(main) ✗ strip a.out       
➜  BinUtils git:(main) ✗ file a.out
a.out: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=909b87f11b30d751c291b98d2390db0cbe10b4c6, for GNU/Linux 3.2.0, stripped
➜  BinUtils git:(main) ✗ 

➜  BinUtils git:(main) ✗ du -b a.out 
14472   a.out



## addr2line：转换地址到文件名和行号

addr2line 工具只是在二进制文件中查找地址, 并将其与 C 源代码程序中的行进行匹配。

用 -g 标志编译并执行它。正如预期：

➜  BinUtils git:(main) ✗ gcc -g atest.c 
➜  BinUtils git:(main) ✗ 
➜  BinUtils git:(main) ✗ 
➜  BinUtils git:(main) ✗ ./a.out 
Within function1
Within function2
Within main

现在使用 objdump 来标识函数开始的内存地址。你可以使用 grep 命令来过滤出所需的特定行。函数的地址在下面突出显示（55 push %rbp 前的地址):

➜  BinUtils git:(main) ✗ objdump -d a.out | grep -A 2 -E 'main>:|function1>:|function2>:'
0000000000001149 <function1>:
    1149:       f3 0f 1e fa             endbr64 
    114d:       55                      push   %rbp
--
0000000000001167 <function2>:
    1167:       f3 0f 1e fa             endbr64 
    116b:       55                      push   %rbp
--
0000000000001185 <main>:
    1185:       f3 0f 1e fa             endbr64 
    1189:       55                      push   %rbp


现在, 使用 addr2line 工具从二进制文件中的这些地址映射到 C 源代码匹配的地址

➜  BinUtils git:(main) ✗ addr2line -e a.out 0000000000001149    
/home/xforg/Desktop/CodingCPlusPlus/SummerTopic/BinUtils/atest.c:5

➜  BinUtils git:(main) ✗ addr2line -e a.out 0000000000001185                
/home/xforg/Desktop/CodingCPlusPlus/SummerTopic/BinUtils/atest.c:17


## nm：列出目标文件的符号

使用上面的 C 程序测试 nm 工具。使用 gcc 快速编译并执行它。

➜  BinUtils git:(main) ✗ gcc -g atest.c
➜  BinUtils git:(main) ✗ ./a.out
Within function1
Within function2
Within main
➜  BinUtils git:(main) ✗


➜  BinUtils git:(main) ✗ nm a.out | grep -Ei 'function|main'
0000000000001149 T function1
0000000000001167 T function2
                 U __libc_start_main@GLIBC_2.34
0000000000001185 T main

你可以看到函数被标记为 T, 它表示 text 节中的符号, 而变量标记为 D，表示初始化的 data 节中的符号。

想象一下在没有源代码的二进制文件上运行此命令有多大用处？这使你可以窥视内部并了解使用了哪些函数和变量。当然，除非二进制文件已被剥离, 这种情况下它们将不包含任何符号, 因此 nm 就命令不会
很有用

➜  BinUtils git:(main) ✗ strip a.out
                                                                                                                                 
➜  BinUtils git:(main) ✗ 
➜  BinUtils git:(main) ✗ nm a.out | grep -Ei 'function|main'
nm: a.out: no symbols