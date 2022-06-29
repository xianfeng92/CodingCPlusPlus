## gcc/g++常用编译选项

gcc 是 GNU Compiler Collection 的缩写, 它包括 C、C++、Objective-C、Fortran、Java、Ada 和 Go 语言的库和前端。gcc 最初是给 GNU 操作系统
编写的编译器, GUN系统是完全自由开放的软件。GCC 支持几乎所有的操作系统平台和硬件。

### 使用 gcc 参数发现程序中的错误

'编译是生成应用程序的过程, 同时也是对程序检验的过程'。虽然警告不影响程序的编译,也可以生成应用程序,但很多项目都要求程序0警告,这样能够避免很多错误的
发生。

-Wall

根据字面意思理解, 打开"所有"的编译警告。确实,  它是编译程序时的必选项, '修正编译时产生的警告,是增强程序健壮性的重要一步'。


-Wextra

打开  -Wall 未打开的更多编译警告。


-Werror

把警告当作错误来处理。此时,编译器遇到第一个警告时就会停下来,逐个修正警告后编译都会继续进行。

-g

打开 gdb 调试时使用的符号表。使用此编译选项后, 可以使用 gdb 调试程序, 非常方便好用。但是遇到比较复杂的错误, 如栈信息被破坏的情况时, gdb 也无能为力。


### 使用 gcc 参数


-fPIC
使用 -fPIC 产生位置无关的代码

当产生共享库的时候,应该创建位置无关的代码, 这会让共享库使用任意的地址而不是固定的地址,要实现这个功能,需要使用 -fPIC 参数。

-D
使用 -D 参数可以使用编译时的宏

参数 D 可以用作定义编译时的宏。

-std
使用参数 -std 指定支持的 c++/c 的标准

gcc -std=c++11 hello-world.cpp

标准如 c++11, c++14, c90, c89等。


-static-libstdc++
使用 -static-libstdc++ 静态链接 libstdc++

-M
使用 -M 生成文件关联的信息

gcc -M main.c
main.o: main.c /usr/include/stdc-predef.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/sys/cdefs.h \
 /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-64.h \
 /usr/lib/gcc/x86_64-redhat-linux/4.8.5/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/x86_64-redhat-linux/4.8.5/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h








