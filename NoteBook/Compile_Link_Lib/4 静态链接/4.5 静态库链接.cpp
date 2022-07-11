// !! 4.5　静态库链接

程序之所以有用, 因为它会有输入输出, 这些输入输出的对象可以是数据, 可以是人, 也可以是另外一个程序, 还可以是另外一台计算机, 一个没有输入输出的程序没有任何意义。
但是一个程序如何做到输入输出呢? 最简单的办法是使用操作系统提供的应用程序编程接口 (API, Application Programming Interface)。当然, 操作系统也只是一个程序, 它怎
么实现跟人机交互设备、跟其他计算机以及其他程序交互呢?

'让我们还是先回到一个比较初步的问题, 就是程序如何使用操作系统提供的 API'。

在一般的情况下, 一种语言的开发环境往往会附带有语言库 (Language Library)。这些库就是对操作系统的 API 的包装, 比如我们经典的 C 语言版 Hello World 程序, 它使用 C 
语言标准库的 printf 函数来输出一个字符串,  printf 函数对字符串进行一些必要的处理以后, 最后会调用操作系统提供的 API。

各个操作系统下, 往终端输出字符串的 API 都不一样; 在 Linux 下, 它是一个 write 的系统调用, 而在 Windows 下它是 WriteConsole 系统 API。

库里面还带有那些很常用的函数, 比如 C 语言标准库里面有很常用一个函数取得一个字符串的长度叫 strlen(), 该函数即遍历整个字符串后返回字符串长度, 这个函数并没有调用任何操作
系统的 API, 也没有做任何输入输出。

其实一个静态库可以简单地看成一组目标文件的集合, 即很多目标文件经过压缩打包后形成的一个文件。比如我们在 Linux 中最常用的 C 语言静态库 libc 位于 /usr/lib/libc.a, 它属
于 glibc 项目的一部分;

我们知道在一个 C 语言的运行库中, 包含了很多跟系统功能相关的代码, 比如输入输出、文件操作、时间日期、内存管理等。glibc 本身是用 C 语言开发的, 它由成百上千个 C 语言源代
码文件组成, 也就是说, 编译完成以后有相同数量的目标文件, 比如输入输出有 printf.o, scanf.o; 文件操作有 fread.o, fwrite.o; 时间日期有 date.o, time.o; 内存管理有
malloc.o 等。把这些零散的目标文件直接提供给库的使用者, 很大程度上会造成文件传输、管理和组织方面的不便, '于是通常人们使用 ar 压缩程序将这些目标文件压缩到一起, 并且对其
进行编号和索引, 以便于查找和检索, 就形成了 libc.a 这个静态库文件'。

我们也可以使用 ar 工具来查看这个文件包含了哪些目标文件:

ar -t libc.a

init-first.o
libc-start.o
sysdep.o
version.o
check_fds.o
libc-tls.o
elf-init.o
dso_handle.o
errno.o
errno-loc.o
iconv_open.o
iconv.o
iconv_close.o
gconv_open.o
gconv.o
gconv_close.o
gconv_db.o
gconv_conf.o
gconv_builtin.o
gconv_simple.o
gconv_trans.o
gconv_cache.o
gconv_dl.o
gconv_charset.o
setlocale.o
findlocale.o
loadlocale.o
loadarchive.o
localeconv.o
nl_langinfo.o
nl_langinfo_l.o
mb_cur_max.o
newlocale.o
duplocale.o
freelocale.o
....


libc.a 里面总共包含了 1 400 个目标文件, 那么, 我们如何在这么多目标文件中找到 printf 函数所在的目标文件呢?

使用 objdump 查看 libc.a 的符号可以发现, 可以看到 printf 函数被定义在了 printf.o 这个目标文件中。这里我们似乎找到了最终的机制, 那就是 Hello World 程序编译出来的
目标文件只要和 libc.a 里面的 printf.o 链接在一起, 最后就可以形成一个可用的可执行文件了

fprintf.o:     文件格式 elf64-x86-64
0000000000000000 g     F .text	00000000000000b7 __fprintf
0000000000000000         *UND*	0000000000000000 .hidden __vfprintf_internal
0000000000000000  w    F .text	00000000000000b7 _IO_fprintf
0000000000000000 g     F .text	00000000000000b7 .hidden fprintf


'幸好 ld 链接器会处理这一切繁琐的事务, 自动寻找所有须要的符号及它们所在的目标文件, 将这些目标文件从 libc.a 中解压出来, 最终将它们链接在一起成为一个可执行文件'。


我们可以使用下面的 GCC 命令编译 hello.c, -verbose表示将整个编译链接过程的中间步骤打印出来:

gcc hello.c --verbose
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/9/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none:hsa
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 9.4.0-1ubuntu1~20.04.1' --with-bugurl=file:///usr/share/doc/gcc-9/README.Bugs --enable-languages=c,ada,c++,go,brig,d,fortran,objc,obj-c++,gm2 --prefix=/usr --with-gcc-major-version-only --program-suffix=-9 --program-prefix=x86_64-linux-gnu- --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-gnu-unique-object --disable-vtable-verify --enable-plugin --enable-default-pie --with-system-zlib --with-target-system-zlib=auto --enable-objc-gc=auto --enable-multiarch --disable-werror --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-offload-targets=nvptx-none=/build/gcc-9-Av3uEd/gcc-9-9.4.0/debian/tmp-nvptx/usr,hsa --without-cuda-driver --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
Thread model: posix
gcc version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.1) 
COLLECT_GCC_OPTIONS='-v' '-mtune=generic' '-march=x86-64'
 /usr/lib/gcc/x86_64-linux-gnu/9/cc1 -quiet -v -imultiarch x86_64-linux-gnu hello.c -quiet -dumpbase hello.c -mtune=generic -march=x86-64 -auxbase hello -version -fasynchronous-unwind-tables -fstack-protector-strong -Wformat -Wformat-security -fstack-clash-protection -fcf-protection -o /tmp/ccDDkDgs.s
GNU C17 (Ubuntu 9.4.0-1ubuntu1~20.04.1) version 9.4.0 (x86_64-linux-gnu)
	compiled by GNU C version 9.4.0, GMP version 6.2.0, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.22.1-GMP

GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
ignoring nonexistent directory "/usr/local/include/x86_64-linux-gnu"
ignoring nonexistent directory "/usr/lib/gcc/x86_64-linux-gnu/9/include-fixed"
ignoring nonexistent directory "/usr/lib/gcc/x86_64-linux-gnu/9/../../../../x86_64-linux-gnu/include"
#include "..." search starts here:
#include <...> search starts here:
 /usr/lib/gcc/x86_64-linux-gnu/9/include
 /usr/local/include
 /usr/include/x86_64-linux-gnu
 /usr/include
End of search list.
GNU C17 (Ubuntu 9.4.0-1ubuntu1~20.04.1) version 9.4.0 (x86_64-linux-gnu)
	compiled by GNU C version 9.4.0, GMP version 6.2.0, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.22.1-GMP

GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
Compiler executable checksum: c0c95c0b4209efec1c1892d5ff24030b
COLLECT_GCC_OPTIONS='-v' '-mtune=generic' '-march=x86-64'
 as -v --64 -o /tmp/ccIk4LHu.o /tmp/ccDDkDgs.s
GNU汇编版本 2.34 (x86_64-linux-gnu) 使用BFD版本 (GNU Binutils for Ubuntu) 2.34
COMPILER_PATH=/usr/lib/gcc/x86_64-linux-gnu/9/:/usr/lib/gcc/x86_64-linux-gnu/9/:/usr/lib/gcc/x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/9/:/usr/lib/gcc/x86_64-linux-gnu/
LIBRARY_PATH=/usr/lib/gcc/x86_64-linux-gnu/9/:/usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/9/../../../../lib/:/lib/x86_64-linux-gnu/:/lib/../lib/:/usr/lib/x86_64-linux-gnu/:/usr/lib/../lib/:/usr/lib/gcc/x86_64-linux-gnu/9/../../../:/lib/:/usr/lib/
COLLECT_GCC_OPTIONS='-v' '-mtune=generic' '-march=x86-64'

 /usr/lib/gcc/x86_64-linux-gnu/9/collect2 -plugin /usr/lib/gcc/x86_64-linux-gnu/9/liblto_plugin.so -plugin-opt=/usr/lib/gcc/x86_64-linux-gnu/9
 /lto-wrapper -plugin-opt=-fresolution=/tmp/ccxvj75r.res -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-
 through=-lc -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s --build-id --eh-frame-hdr -m elf_x86_64 --hash-style=gnu --as
 -needed -dynamic-linker /lib64/ld-linux-x86-64.so.2 -pie -z now -z relro /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/Scrt1.o 
 /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/9/crtbeginS.o 
 -L/usr/lib/gcc/x86_64-linux-gnu/9 -L/usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/9/../../../../
 lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/9/../../.. 
 /tmp/ccIk4LHu.o -lgcc --push-state --as-needed -lgcc_s --pop-state -lc -lgcc --push-state --as-needed -lgcc_s --pop-state /usr/lib/gcc/
 x86_64-linux-gnu/9/crtendS.o /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/crtn.o

COLLECT_GCC_OPTIONS='-v' '-mtune=generic' '-march=x86-64'

关键的三个步骤, 第一步是调用 /usr/lib/gcc/x86_64-linux-gnu/9/cc1 程序, 这个程序实际上就是 GCC 的 C 语言编译器, 它将 hello.c 编译成一个临时的汇编文件 
/tmp/ccDDkDgs.s, 然后调用 as 程序, as 程序是 GNU 的汇编器, 它将 /tmp/ccDDkDgs.s 汇编成临时目标文件 /tmp/ccIk4LHu.o, 这个 “/tmp/ccIk4LHu.o 实际上就是前面
的 hello.o, 接着最关键的步骤是最后一步, GCC 调用 collect2 程序来完成最后的链接。但是按照我们之前的理解, 链接过程应该由 ld 链接器来完成, 这里怎么忽然杀出个 
collect2? 这是个什么程序?

实际上 collect2 可以看作是 ld 链接器的一个包装, 它会调用 ld 链接器来完成对目标文件的链接, 然后再对链接结果进行一些处理, 主要是收集所有与程序初始化相关的信息并且构造
初始化的结构。

在这里, 可以简单地把 collect2 看作是 ld 链接器。可以看到最后一步中, 至少有下列几个库和目标文件:

•crt1.o
•crti.o
•crtbeginT.o
•libgcc.a
•libc.a
•crtend.o
•crtn.o


// !!  Q/A

Q: 为什么静态运行库里面一个目标文件只包含一个函数? 比如 libc.a 里面 printf.o 只有 printf() 函数、strlen.o 只有 strlen() 函数, 为什么要这样组织?

A: 我们知道, 链接器在链接静态库的时候是以目标文件为单位的。比如我们引用了静态库中的 printf() 函数, 那么链接器就会把库中包含 printf() 函数的那个目标文件链接进来, 
   如果很多函数都放在一个目标文件中, 很可能很多没用的函数都被一起链接进了输出结果中。由于运行库有成百上千个函数, 数量非常庞大, 每个函数独立地放在一个目标文件中可以尽量
   减少空间的浪费, 那些没有被用到的目标文件（函数）就不要链接到最终的输出文件中。





