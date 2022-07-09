// !! 3.1　目标文件的格式

现在 PC 平台流行的可执行文件格式 (Executable) 主要是 Windows 下的 PE(Portable Executable) 和 Linux 的 ELF (Executable Linkable Format), 它们都是
COFF (Common file format) 格式的变种。

'目标文件就是源代码编译后但未进行链接的那些中间文件' (Windows 的 .obj 和 Linux 下的 .o), 它跟可执行文件的内容与结构很相似, 所以一般跟可执行文件格式一起采用一种格
式存储。

不光是可执行文件 ( Windows 的 .exe 和 Linux 下的 ELF 可执行文件) 按照可执行文件格式存储。动态链接库 (DLL, Dynamic Linking Library) ( Windows的 .dll 和 
Linux 的.so) 及静态链接库 (Static Linking Library) ( Windows 的 .lib 和 Linux 的 .a) 文件都按照可执行文件格式存储。


'ELF 文件标准里面把系统中采用 ELF 格式的文件归为如表 3-1 所列举的 4 类'。

我们可以在 Linux 下使用 file 命令来查看相应的文件格式, 上面几种文件在 file 命令下会显示出相应的类型:


> file rcrt1.o 
rcrt1.o: ELF 64-bit LSB relocatable, x86-64, version 1 (SYSV), for GNU/Linux 3.2.0, not stripped


> file bash
bash: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, 
BuildID[sha1]=2a9f157890930ced4c3ad0e74fc1b1b84aad71e6, for GNU/Linux 3.2.0, stripped

> file ld-2.31.so 
ld-2.31.so: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, 
BuildID[sha1]=4587364908de169dec62ffa538170118c1c3a078, stripped

> file speech-service 
speech-service: ELF 64-bit LSB shared object, ARM aarch64, version 1 (SYSV), dynamically linked, interpreter /usr/lib/ldqnx-64.so.2, 
BuildID[md5/uuid]=d3992a4c54b168678b8e76ea7849f0b3, with debug_info, not stripped



Linux Standard Base (LSB)

Stripped 和 not stripped 的最大区别:

stripped: 将程序中的符号表的信息剔除掉了, 这样子编译出来的可执行文件体积比较小

not stripped: 则反之, 但是就是因为其保留了这些信息, 所以便于调试