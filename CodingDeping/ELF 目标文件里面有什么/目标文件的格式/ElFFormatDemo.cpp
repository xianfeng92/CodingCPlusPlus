
// !! 目标文件的格式

目标文件就是源代码经过编译后的，链接之前的文件，经过链接就变成了可执行文件， 它也是一种二进制文件。

目标文件的格式其实与最终的可执行文件的格式是一致的，只是没有经过符号的链接过程。在 Linux 环境下，可执行文件的格式叫 ELF
（Executable Linkable Format）

// !! ELF 文件下又可以分为 4 种类型

1. 可重定位文件（Relocatable File）
   包含代码和数据，'可以被链接成可执行文件或共享目标文件', 静态链接库也可以归为这一类。 如： Linux 下的 .o   Windows  下的 .obj 

2. 可执行文件（Executable File）
   这类文件包含了可以直接执行的程序，它的代码就是 ELF 可执行文件，它们一般都是没有扩展名的。 如： /bin/bash 文件， Windows 下的 .exe 文件

3. 共享目标文件（Shared Object File） 
   也是一种可重定位文件，但是它可以被用于'动态链接'。 如： Linux 下的 .so, Windows 下的 DLL

4. 核心转储文件（Core Dump File）
   进程意外终止的时候，系统把进程地址空间的内容和一些其他信息存放到核心转储文件中，可以用于排除 BUG。 如： Linux 下的 coredump

// !! Linux 下可以使用 file 命名查看文件格式

--------------------------------------------------------------------
~/Stan/xforg/linux_asr_1.0_forModernC++/build(devel2*) » file linuxasr
linuxasr: ELF 64-bit LSB executable, ARM aarch64, version 1 (GNU/Linux), dynamically linked, interpreter /lib/ld-linux-aarch64.so.1, for GNU/Linux 3.18.0, BuildID[sha1]=b67e23266db11743f31ff7ed582e49152f0bd35b, with debug_info, not stripped
