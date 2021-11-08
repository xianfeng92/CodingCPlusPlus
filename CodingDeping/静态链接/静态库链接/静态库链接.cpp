// !! 静态库链接

'程序之所以有用，因为它会有输入输出'，这些输入输出对象可以是数据、也可以是人、也可以是另外一个程序，还可以是另外一台计算机。

'是一个程序如何做到输入输出呢？' 

1. 最简单的办法是使用操作系统提供的应用程序编程接口(API)。当然，操作系统也是一个程序。

'程序如何使用操作系统提供的 API ?'

1.  一般情况下，一种语言的开发环境往往会附带'语言库(language Library)'， 这些库就是对操作系统 API 的包装， 比如 C 语言标准库里的 printf()。
    库里面还有一些很常用的函数，这部分函数不调用操作系统 API,比如 C 语言库里 strlen() 函数


其实'一个静态库可以简单地看成一组目标文件的集合', 即很多目标文件经过压缩打包后形成的一个文件。比如 Linux 中最常用的 C 语言静态库 libc 位于
/usr/lib/libc.a，它属于 glibc 项目的一部分。将一些 .o 文件使用 ar 压缩程序将这些目标文件压缩到一起，并且对其进行编号和索引，以便于查找
和检索，就形成了 libc.a 这个静态库。


我们知道一个 C 语言的运行库，包含很多系统相关的功能代码, 比如输入输出、文件操作、时间日期、内存管理等。glibc 本身是由 C 语言开发的，它有成百上千个
C 语言源文件代码组成，也就是说，编译以后有相同数量的目标文件， 比如输入输出有 printf.o scanf.o ; 文件操作有 fread.o fwrite.o ； 时间日期有
data.o time.o ; 内存管理有 malloc.o 等。把这些零散的目标文件直接提供给库的使用者，很大程度会造成文件传输、管理和组织方面的不便，于是通常人们
使用 ar 压缩程序将这些目标文件压缩在一起， 并对其进行编号和索引，以便于查找和索引，就形成了 libc.a 这个静态库文件。


'为什么静态运行库里面一个目标文件只包含一个函数'？ 比如 libc.a 里面 printf.o 只有 printf() 函数、strlen.o 只有 strlen() 函数？

'链接器在进行静态链接时是以目标文件为单位的'。比如我们引用了静态库中的 printf() 函数，那么链接器就会把库中包含 printf() 函数的那个目标文件链接进来，
如果多个函数都放在一个目标文件中, 很可能一些没有用的函数也被链接进输出结果中，这样浪费了空间。


~ » gcc --print-file-name=libc.a                                                                     
/usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/libc.a
-----------------------------------------------------------------

~ » ar -t /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/libc.a | grep "printf"           
vfprintf.o
vprintf.o
printf_fp.o
reg-printf.o
printf-prs.o
printf_fphex.o
printf_size.o
fprintf.o
printf.o
....


objdump -t /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/libc.a


printf.o：     文件格式 elf64-x86-64

SYMBOL TABLE:
0000000000000000 l    d  .text	0000000000000000 .text
0000000000000000 l    d  .data	0000000000000000 .data
0000000000000000 l    d  .bss	0000000000000000 .bss
0000000000000000 l    d  .note.GNU-stack	0000000000000000 .note.GNU-stack
0000000000000000 l    d  .note.gnu.property	0000000000000000 .note.gnu.property
0000000000000000 l    d  .eh_frame	0000000000000000 .eh_frame
0000000000000000 g     F .text	00000000000000c9 __printf
0000000000000000         *UND*	0000000000000000 stdout
0000000000000000         *UND*	0000000000000000 .hidden __vfprintf_internal
0000000000000000         *UND*	0000000000000000 _GLOBAL_OFFSET_TABLE_
0000000000000000         *UND*	0000000000000000 __stack_chk_fail
0000000000000000 g     F .text	00000000000000c9 _IO_printf
0000000000000000 g     F .text	00000000000000c9 printf



使用 GCC 命名编译 hello.c， “--verbose” 表示将整个编译链接过程的中间步骤打印出来， “-static” 表示静态链接， “-fno-builtin” 表示关闭内置函数优化选项

 » gcc -static --verbose -fno-builtin hello.c 
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/9/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none:hsa
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 9.3.0-17ubuntu1~20.04' --with-bugurl=file:///usr/share/doc/gcc-9/README.Bugs --enable-languages=c,ada,c++,go,brig,d,fortran,objc,obj-c++,gm2 --prefix=/usr --with-gcc-major-version-only --program-suffix=-9 --program-prefix=x86_64-linux-gnu- --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-gnu-unique-object --disable-vtable-verify --enable-plugin --enable-default-pie --with-system-zlib --with-target-system-zlib=auto --enable-objc-gc=auto --enable-multiarch --disable-werror --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-offload-targets=nvptx-none=/build/gcc-9-HskZEa/gcc-9-9.3.0/debian/tmp-nvptx/usr,hsa --without-cuda-driver --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
Thread model: posix
gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04) 
COLLECT_GCC_OPTIONS='-static' '-v' '-fno-builtin' '-mtune=generic' '-march=x86-64'

// !! cc1 用于预处理和编译流程
 /usr/lib/gcc/x86_64-linux-gnu/9/cc1 -quiet -v -imultiarch x86_64-linux-gnu hello.c -quiet -dumpbase hello.c -mtune=generic -march=x86-64 -auxbase hello -version -fno-builtin -fasynchronous-unwind-tables -fstack-protector-strong -Wformat -Wformat-security -fstack-clash-protection -fcf-protection -o /tmp/ccgpyAyY.s
GNU C17 (Ubuntu 9.3.0-17ubuntu1~20.04) version 9.3.0 (x86_64-linux-gnu)
	compiled by GNU C version 9.3.0, GMP version 6.2.0, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.22.1-GMP

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
GNU C17 (Ubuntu 9.3.0-17ubuntu1~20.04) version 9.3.0 (x86_64-linux-gnu)
	compiled by GNU C version 9.3.0, GMP version 6.2.0, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.22.1-GMP

GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
Compiler executable checksum: bbf13931d8de1abe14040c9909cb6969
COLLECT_GCC_OPTIONS='-static' '-v' '-fno-builtin' '-mtune=generic' '-march=x86-64'
 as -v --64 -o /tmp/ccWVDyXW.o /tmp/ccgpyAyY.s
GNU汇编版本 2.34 (x86_64-linux-gnu) 使用BFD版本 (GNU Binutils for Ubuntu) 2.34
COMPILER_PATH=/usr/lib/gcc/x86_64-linux-gnu/9/:/usr/lib/gcc/x86_64-linux-gnu/9/:/usr/lib/gcc/x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/9/:/usr/lib/gcc/x86_64-linux-gnu/
LIBRARY_PATH=/usr/lib/gcc/x86_64-linux-gnu/9/:/usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/9/../../../../lib/:/lib/x86_64-linux-gnu/:/lib/../lib/:/usr/lib/x86_64-linux-gnu/:/usr/lib/../lib/:/usr/lib/gcc/x86_64-linux-gnu/9/../../../:/lib/:/usr/lib/
COLLECT_GCC_OPTIONS='-static' '-v' '-fno-builtin' '-mtune=generic' '-march=x86-64'

// !! collect2 用于目标文件的链接
 /usr/lib/gcc/x86_64-linux-gnu/9/collect2 -plugin /usr/lib/gcc/x86_64-linux-gnu/9/liblto_plugin.so -plugin-opt=/usr/lib/gcc/x86_64-linux-gnu/9/lto-wrapper 
 -plugin-opt=-fresolution=/tmp/ccDlYSGW.res -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_eh -plugin-opt=-pass-through=-lc 
 --build-id -m elf_x86_64 --hash-style=gnu --as-needed -static -z relro /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/crt1.o 
 /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/9/crtbeginT.o -L/usr/lib/gcc/x86_64-linux-gnu/9 
 -L/usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/9/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib 
 -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/9/../../.. /tmp/ccWVDyXW.o --start-group -lgcc -lgcc_eh -lc --end-group 
 /usr/lib/gcc/x86_64-linux-gnu/9/crtend.o /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/crtn.o
COLLECT_GCC_OPTIONS='-static' '-v' '-fno-builtin' '-mtune=generic' '-march=x86-64'


1. 第一步是调用 cc1 程序进行预处理以及编译过程，它将 hello.c 编译成一个临时的汇编文件 /tmp/ccgpyAyY.s

2. GCC 程序调用 as 程序，as 程序是 GNU 的汇编器，它将 /tmp/ccgpyAyY.s 汇编成 /tmp/ccWVDyXW.o

3. 接着最关键的一步，GCC 程序调用 collect2 完成最后的链接，collect2 可以看做是链接器 ld 的一个包装，它会调用 ld 链接器来完成目标文件的链接，
   然后再对链接结构做进一步处理

链接中用的目标文件：crtn.o、crtend.o、crt1.o、crti.o、crtbeginT.o







