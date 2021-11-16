// !! Linux动态链接器实现


内核在装载完 ELF 可执行文件以后就返回到用户空间，将控制权交给程序的入口。对于不同链接形式的 ELF 可执行文件，这个程序的入口是有区别的。

1. 对于静态链接的可执行文件来说，程序的入口就是 ELF 文件头里面的 e_entry 指定的入口

2. 对于动态链接的可执行文件，内核会分析它的动态链接器地址(在”.interp”段)， 将动态链接器映射至进程地址空间，然后把控制权交给动态链接器

在Linux下，可执行文件所需要的动态链接器的路径几乎都是 ”/lib64/ld-linux-x86-64.so.2”， 其它的 *nix 操作系统可能会有不同的路径。


在 Linux 的系统中，/lib64/ld-linux-x86-64.so.2 通常是一个软链接, ld-linux-x86-64.so.2 -> /lib/x86_64-linux-gnu/ld-2.31.so


动态链接器是个非常特殊的共享对象，它不仅是个共享对象，还是个可执行的程序，可以直接在命令行下面运行。共享库和可执行文件实际上没什么区别，除了文件头的标
志位和扩展名有所不同之外，其它都是一样的。

/lib64 » ./ld-linux-x86-64.so.2                                                                    
Usage: ld.so [OPTION]... EXECUTABLE-FILE [ARGS-FOR-PROGRAM...]
You have invoked `ld.so', the helper program for shared library executables.
This program usually lives in the file `/lib/ld.so', and special directives
in executable files using ELF shared libraries tell the system's program
loader to load the helper program from this file.  This helper program loads
the shared libraries needed by the program executable, prepares the program
to run, and runs it.  You may invoke this helper program directly from the
command line to load and run an ELF executable file; this is like executing
that file itself, but always uses this helper program from the file you
specified, instead of the helper program file specified in the executable
file you run.  This is mostly of use for maintainers to test new versions
of this helper program; chances are you did not intend to run this program.

  --list                list all dependencies and how they are resolved
  --verify              verify that given object really is a dynamically linked


// !! 动态链接器本身应该是静态链接的，它不能依赖于其它共享对象

动态链接器'本身是用来帮助其它 ELF 文件解决共享对象依赖问题的，如果它也依赖于其它共享对象，那么谁来帮它解决依赖问题？ 所以它本身必须不依赖于其它共享对象。
这一点可以使用 ldd 来判断，如下所示:

/lib64 » ldd ld-linux-x86-64.so.2                                                            
	statically linked

是不是 PIC 对于动态链接器来说并不关键，动态链接器可以是 PIC 的也可以不是，但往往使用 PIC 会更加简单一些。一方面，如果不是 PIC 的话，会使得代码段无法共享，
浪费内存；另一方面也会使 /lib64/ld-linux-x86-64.so.2 本身初始化更加复杂，因为自举时还需要对代码段进行重定位。实际上的 /lib64/ld-linux-x86-64.so.2 
是 PIC 的。








