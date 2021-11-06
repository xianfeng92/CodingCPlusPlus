// !! 编译和链接：被隐藏的过程

对于平常的应用程序开发, 我们很少去关注编译和链接过程。通常开发环境都是集成开发环境 IDE 做了， IDE 一般都将编译和链接过程一步完成，通常将这种编译
和链接并到一起的过程成为构建 (build)。 即使使用命令行编译，基本上也是一条命令，优化了其他的过程。

// !! 被隐藏的过程

以 “Hello World” 程序为例, 来介绍程序的编译与链接过程

// hello.c
#include <stdio.h>
int main()
{
    printf("Hello World!\n");
    return 0;
}

在  Linux 下我们使用 GCC 来编译 Hello World 程序

» gcc hello.c -o hello                                           
» ./hello                                                       
Hello World!

'GCC 编译命令隐藏了构建过程中的一些复杂的步骤'，如下所示:

1. 预处理（Propressing）
2. 编译（Compilation）
3. 汇编（Assembly）
4. 链接（Linking）

// !! 预编译

预编译步骤将源代码文件 hello.c 以及相关头文件，如: stdio.h 等预编译生成一个.i 文件。

» gcc -E hello.c -o hello.i
或
» cpp hello.c > hello.i

预编译'主要处理源代码中的以 “#” 开始的预编译指令', 如: “#include”、“#define”等，其主要处理规则如下:

1. 将所有的 “#define” 删除，并且展开所有的宏定义

2. 处理所有条件预编译指令, 如: “#if”、“#ifdef”、“#else”、“#endif”

3. 处理 #include 预编译指令，将被包含的文件插入到该预编译指令的位置。该过程是递归进行的，因为被包含的文件可能还包含其他文件

4. '删除所有的注释“//”和“/ /”'

5. '添加行号和文件名标识'，比如 #2 “hello.c” 2，以便于编译时编译器产生调试试用的行号信息以及用于编译时产生编译错误或警告时能够显示行号

6. 保留所有的 #pragma 编译器指令，因为编译器须要试用他们

预编译生成的 .i 文件不包含任何宏定义，因为所有的宏已经被展开，并且包含的文件也已经被插入到 .i 文件中。所以当我们无法判断宏定义是否正确或头文件包含是否
正确时，可以查看预编译后的文件来确定问题

// !! 编译

编译就是把预处理生成的文件进行一系列词法分析、语法分析、语义分析、优化，生成相应的汇编代码文件。这个过程是整个程序构建的核心部分, 也是最复杂的部
分之一。现在版本的 GCC 把预编译和编译两个步骤合并成了一个步骤，使用一个叫 cc1 的程序来完成。

/usr/lib/gcc/x86_64-linux-gnu/9 » ls                                                                                
32           crtendS.o          include            libgcc.a      libitm.so               libquadmath.a       libtsan.a
cc1          crtfastmath.o      libasan.a          libgcc_eh.a   libitm.spec             libquadmath.so      libtsan.so
cc1plus      crtoffloadbegin.o  libasan_preinit.o  libgcc_s.so   liblsan.a               libsanitizer.spec   libubsan.a
collect2     crtoffloadend.o    libasan.so         libgcov.a     liblsan_preinit.o       libssp_nonshared.a  libubsan.so
crtbegin.o   crtoffloadtable.o  libatomic.a        libgomp.a     liblsan.so              libstdc++.a         lto1
crtbeginS.o  crtprec32.o        libatomic.so       libgomp.so    liblto_plugin.so        libstdc++fs.a       lto-wrapper
crtbeginT.o  crtprec64.o        libbacktrace.a     libgomp.spec  liblto_plugin.so.0      libstdc++.so        plugin
crtend.o     crtprec80.o        libcc1.so          libitm.a      liblto_plugin.so.0.0.0  libsupc++.a         x32

cc1plus 用于编译 C++ 
cc1 用于编译 C 语言

使用 cc1 来编译 hello.c 

» /usr/lib/gcc/x86_64-linux-gnu/9/cc1  hello.c     

 main
Analyzing compilation unit
Performing interprocedural optimizations
 <*free_lang_data> <visibility> <build_ssa_passes> <opt_local_passes> <remove_symbols> <targetclone> <free-fnsummary>Streaming LTO
 <whole-program> <hsa> <fnsummary> <inline> <free-fnsummary> <single-use> <comdats>Assembling functions:
 <materialize-all-clones> <simdclone> main
Time variable                                   usr           sys          wall               GGC
 phase setup                        :   0.00 (  0%)   0.00 (  0%)   0.01 ( 50%)    1222 kB ( 70%)
 phase parsing                      :   0.00 (  0%)   0.00 (  0%)   0.01 ( 50%)     458 kB ( 26%)
 phase opt and generate             :   0.01 (100%)   0.00 (  0%)   0.00 (  0%)      57 kB (  3%)
 preprocessing                      :   0.00 (  0%)   0.00 (  0%)   0.01 ( 50%)     136 kB (  8%)
 initialize rtl                     :   0.01 (100%)   0.00 (  0%)   0.00 (  0%)      12 kB (  1%)
 TOTAL                              :   0.01          0.00          0.02           1747 kB


只进行编译，不汇编，可以生成硬件平台相关的汇编语言 hello.s

'实际上 GCC 的这些命名只是这些后台程序的包装，它会根据不同的参数要求去调用预编译编译程序 cc1、汇编器 as、链接器 ld'


// !! 汇编

汇编器将汇编代码转换成机器可以执行的指令，每一个汇编语句几乎都对应一条机器指令。汇编过程只需要根据汇编指令和机器指令的对照表一一翻译即可。

 » where as                                                                         
/usr/bin/as
/bin/as

>> as hello.s -o hello.o

虽然 hello.o 已经是二进制的机器码了, 但是它仍然不能执行，因为它缺少系统运行所必须的库，比如 C 语言 printf() 对应的汇编语言的 puts 函数。确切的说，系统
还不知道 puts 函数在内存中的具体位置。如果我们在一份源代码中使用了外部的函数或者变量，还需要重要的一步:链接。


// !! 链接

链接是 C/C++ 开发中经常使用的部分。下面的命令进行链接, 生成名为 hello 的可执行文件

>> gcc hello.o -o hello

上面的命令基于动态链接的方式, 生成的 hello 已经是一个可执行文件。实际上，这个命令隐藏了很多背后的内容。printf() 方法属于 libc 库，上面的命令并没有体现出
来如何将hello.o 和 libc 库链接的过程。

为了体现链接, 我们使用链接器 ld，将多个模块链接起来，生成名为 myhello 的可执行文件:

$ ld -o myhello hello.o /usr/lib/x86_64-linux-gnu/crt1.o /usr/lib/x86_64-linux-gnu/crti.o /usr/lib/x86_64-linux-gnu/crtn.o -lc -dynamic-linker 
  /lib64/ld-linux-x86_64.so.2

我们终于将一份源代码编译成了可执行文件！ 这个命令有点长，涉及到文件和路径也有点多，它将多个文件和库链接到 myhello 中。crt1.o、crti.o 和 crtn.o 是 C 运行时
所依赖的环境。

如果提示 crt1.o 这几个文件找不到，可以使用 find 命令来查找:

$ find /usr/lib -name 'crt1.o'





