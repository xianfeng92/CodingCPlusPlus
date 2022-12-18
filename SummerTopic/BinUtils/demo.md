#include <stdio.h>

int main(void)
{
  printf("Hello World\n");
  return 0;
}


## 步骤 1：用 cpp 预处理

C 预处理程序 (cpp) 用于扩展所有宏并将头文件包含进来。

在此示例中, 头文件 stdio.h 将被包含在源代码中。stdio.h 是一个头文件, 其中包含有关程序内使用的 printf 函数的信息。对源代码运行 cpp 其结果保存在名为 hello.i 的文件中。可以使用文本
编辑器打开该文件以查看其内容。打印 “hello world” 的源代码在该文件的底部。

➜  BinUtils git:(main) ✗ cpp hello.c > hello.i
➜  BinUtils git:(main) ✗ ls -li
total 32
1622925 -rw-rw-r-- 1 xforg xforg   540 12月 18 12:33  demo.md
1621594 -rw-rw-r-- 1 xforg xforg  1031 12月 18 12:27 'GNU Binutils.md'
1622927 -rw-rw-r-- 1 xforg xforg    77 12月 18 12:29  hello.c
1622936 -rw-rw-r-- 1 xforg xforg 17963 12月 18 12:33  hello.i


## 步骤 2：用 gcc 编译

在此阶段, 无需创建目标文件, 就将步骤 1 中生成的预处理源代码转换为汇编语言指令。这个阶段使用 GNU 编译器集合（gcc）。对 hello.i 文件运行带有 -S 选项的 gcc 命令后, 它将创建一个名
为 hello.s 的新文件。该文件包含该 C 程序的汇编语言指令。

➜  BinUtils git:(main) ✗ gcc -Wall -S hello.i           
➜  BinUtils git:(main) ✗ ls -li
total 36
1622925 -rw-rw-r-- 1 xforg xforg  1263 12月 18 13:06  demo.md
1621594 -rw-rw-r-- 1 xforg xforg  1031 12月 18 12:27 'GNU Binutils.md'
1622927 -rw-rw-r-- 1 xforg xforg    77 12月 18 12:29  hello.c
1622936 -rw-rw-r-- 1 xforg xforg 17963 12月 18 12:33  hello.i
1622944 -rw-rw-r-- 1 xforg xforg   664 12月 18 13:12  hello.s
➜  BinUtils git:(main) ✗ cat hello.s          
        .file   "hello.c"
        .text
        .section        .rodata
.LC0:
        .string "Hello World"
        .text
        .globl  main
        .type   main, @function
main:
.LFB0:
        .cfi_startproc
        endbr64
        pushq   %rbp
        .cfi_def_cfa_offset 16
        .cfi_offset 6, -16
        movq    %rsp, %rbp
        .cfi_def_cfa_register 6
        leaq    .LC0(%rip), %rax
        movq    %rax, %rdi
        call    puts@PLT
        movl    $0, %eax
        popq    %rbp
        .cfi_def_cfa 7, 8
        ret
        .cfi_endproc
.LFE0:
        .size   main, .-main
        .ident  "GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0"
        .section        .note.GNU-stack,"",@progbits
        .section        .note.gnu.property,"a"
        .align 8
        .long   1f - 0f
        .long   4f - 1f
        .long   5
0:
        .string "GNU"
1:
        .align 8
        .long   0xc0000002
        .long   3f - 2f
2:
        .long   0x3
3:
        .align 8
4:


## 步骤 3：用 as 汇编

汇编器(As)的目的是将汇编语言指令转换为机器语言代码, 并生成扩展名为 .o 的目标文件。此阶段使用默认情况下在所有 Linux 平台上都可用的 GNU 汇编器。

➜  BinUtils git:(main) ✗ as hello.s -o hello.o
➜  BinUtils git:(main) ✗ ls -li
total 40
1622925 -rw-rw-r-- 1 xforg xforg  2960 12月 18 13:25  demo.md
1621594 -rw-rw-r-- 1 xforg xforg  1031 12月 18 12:27 'GNU Binutils.md'
1622927 -rw-rw-r-- 1 xforg xforg    77 12月 18 12:29  hello.c
1622936 -rw-rw-r-- 1 xforg xforg 17963 12月 18 12:33  hello.i
1622950 -rw-rw-r-- 1 xforg xforg  1496 12月 18 13:26  hello.o
1622944 -rw-rw-r-- 1 xforg xforg   664 12月 18 13:12  hello.s


现在你有了第一个 ELF 格式的文件; 但是, 还不能执行它。

➜  BinUtils git:(main) ✗ file hello.o                               
hello.o: ELF 64-bit LSB relocatable, x86-64, version 1 (SYSV), not stripped


## 步骤 4: 用 ld 链接

这是编译的最后阶段, 将目标文件链接以创建可执行文件。可执行文件通常需要外部函数, 这些外部函数通常来自系统库（libc）。

你可以使用 ld 命令直接调用链接器; 但是, 此命令有些复杂。相反, 你可以使用带有 -v（详细）标志的 gcc 编译器, 以了解链接是如何发生的。

Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/11/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none:amdgcn-amdhsa
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 11.3.0-1ubuntu1~22.04' --with-bugurl=file:///usr/share/doc/gcc-11/README.Bugs --enable-languages=c,ada,c++,go,brig,d,fortran,objc,obj-c++,m2 --prefix=/usr --with-gcc-major-version-only --program-suffix=-11 --program-prefix=x86_64-linux-gnu- --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --enable-bootstrap --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-gnu-unique-object --disable-vtable-verify --enable-plugin --enable-default-pie --with-system-zlib --enable-libphobos-checking=release --with-target-system-zlib=auto --enable-objc-gc=auto --enable-multiarch --disable-werror --enable-cet --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-offload-targets=nvptx-none=/build/gcc-11-xKiWfi/gcc-11-11.3.0/debian/tmp-nvptx/usr,amdgcn-amdhsa=/build/gcc-11-xKiWfi/gcc-11-11.3.0/debian/tmp-gcn/usr --without-cuda-driver --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu --with-build-config=bootstrap-lto-lean --enable-link-serialization=2
Thread model: posix
Supported LTO compression algorithms: zlib zstd
gcc version 11.3.0 (Ubuntu 11.3.0-1ubuntu1~22.04) 
COMPILER_PATH=/usr/lib/gcc/x86_64-linux-gnu/11/:/usr/lib/gcc/x86_64-linux-gnu/11/:/usr/lib/gcc/x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/11/:/usr/lib/gcc/x86_64-linux-gnu/
LIBRARY_PATH=/usr/lib/gcc/x86_64-linux-gnu/11/:/usr/lib/gcc/x86_64-linux-gnu/11/../../../x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/11/../../../../lib/:/lib/x86_64-linux-gnu/:/lib/../lib/:/usr/lib/x86_64-linux-gnu/:/usr/lib/../lib/:/usr/lib/gcc/x86_64-linux-gnu/11/../../../:/lib/:/usr/lib/
COLLECT_GCC_OPTIONS='-v' '-mtune=generic' '-march=x86-64' '-dumpdir' 'a.'
 /usr/lib/gcc/x86_64-linux-gnu/11/collect2 -plugin /usr/lib/gcc/x86_64-linux-gnu/11/liblto_plugin.so -plugin-opt=/usr/lib/gcc/x86_64-linux-gnu/11/lto-wrapper -plugin-opt=-fresolution=/tmp/cczl34hC.res -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lc -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s --build-id --eh-frame-hdr -m elf_x86_64 --hash-style=gnu --as-needed -dynamic-linker /lib64/ld-linux-x86-64.so.2 -pie -z now -z relro /usr/lib/gcc/x86_64-linux-gnu/11/../../../x86_64-linux-gnu/Scrt1.o /usr/lib/gcc/x86_64-linux-gnu/11/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/11/crtbeginS.o -L/usr/lib/gcc/x86_64-linux-gnu/11 -L/usr/lib/gcc/x86_64-linux-gnu/11/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/11/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/11/../../.. hello.o -lgcc --push-state --as-needed -lgcc_s --pop-state -lc -lgcc --push-state --as-needed -lgcc_s --pop-state /usr/lib/gcc/x86_64-linux-gnu/11/crtendS.o /usr/lib/gcc/x86_64-linux-gnu/11/../../../x86_64-linux-gnu/crtn.o
COLLECT_GCC_OPTIONS='-v' '-mtune=generic' '-march=x86-64' '-dumpdir' 'a.'

COMPILER_PATH
LIBRARY_PATH 
COLLECT_GCC_OPTIONS

运行此命令后，你应该看到一个名为 a.out 的可执行文件:

➜  BinUtils git:(main) ✗ ls -li
total 60
1622978 -rwxrwxr-x 1 xforg xforg 15960 12月 18 13:34  a.out
1622925 -rw-rw-r-- 1 xforg xforg  7456 12月 18 13:34  demo.md
1621594 -rw-rw-r-- 1 xforg xforg  1031 12月 18 12:27 'GNU Binutils.md'
1622927 -rw-rw-r-- 1 xforg xforg    77 12月 18 12:29  hello.c
1622936 -rw-rw-r-- 1 xforg xforg 17963 12月 18 12:33  hello.i
1622950 -rw-rw-r-- 1 xforg xforg  1496 12月 18 13:26  hello.o
1622944 -rw-rw-r-- 1 xforg xforg   664 12月 18 13:12  hello.s

对 a.out 运行 file 命令, 结果表明它确实是 ELF 可执行文件：

➜  BinUtils git:(main) ✗ file a.out  
a.out: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=cd5e6b8b950665bf0cf56f4fb1af4fdbc4e54635, for GNU/Linux 3.2.0, not stripped

运行该可执行文件, 看看它是否如源代码所示工作：

➜  BinUtils git:(main) ✗ ./a.out  
Hello World








