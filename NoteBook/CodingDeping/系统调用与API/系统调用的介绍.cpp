// !! 系统调用的介绍


'系统调用(System Call) 是应用程序(运行库也是应用程序的一部分)与操作系统内核之间的接口'，它决定了应用程序是如何与内核打交道的。无论程序是直接
进行系统调用，还是通过运行库，最终还是会到达系统调用这个层面上。


// !! 1. 什么是系统调用

在现代的操作系统里，'程序运行的时候其本身是没有权利访问多少系统资源的'。由于系统有限的资源有可能被多个不同的应用程序同时访问，如果不加以保护，
那么各个应用程序难免产生冲突。'现代操作系统将可能产生冲突的系统资源给保护起来，阻止应用程序直接访问'。这些系统资源包括文件、网络、IO、各种设备等。

举个例子，无论在 Windows 下还是 Linux 下，程序员都没有机会擅自去访问硬盘的某扇区上面的数据，而必须通过文件系统;也不能擅自修改任意文件，所有的这些
操作都必须经由操作系统所规定的方式来进行, 比如我们使用 fopen 去打开一个没有权限的文件就会发生失败。此外，有一些行为，应用程序不借助操作系统是无法
办到或不能有效地办到的。

'为了让应用程序有能力访问系统资源，也为了让程序借助操作系统做一些必须由操作系统支持的行为，每个操作系统都会提供一套接口，以供应用程序使用'。这些接口往往
通过中断来实现，比如 'Linux 使用 0x80 号中断作为系统调用的入口'。

系统调用覆盖的功能很广，有程序运行所必需的支持，例如创建、退出进程和线程、进程内存管理，也有对系统资源的访问，例如文件、网络、进程间通信、硬件设备的
访问，也可能有对图形界面的操作支持。

系统调用既然作为一个接口，而且是非常重要的接口，它的定义将十分重要。

1. '首先系统调用必须有明确的定义，即每个调用的含义、参数、行为都需要有严格而清晰的定义，这样应用程序(运行库)才可以正确地使用它'；

2. '其次它必须保持稳定和向后兼容'，如果某次系统更新导致系统调用接口发生改变，新的系统调用接口与之前版本完全不同，这是无法想象的，因为所有之前能正常
   运行的程序都将无法使用。

'所以操作系统的系统调用往往从一开始定义后就基本不做改变，而仅仅是增加新的调用接口，以保持向后兼容'
   
// !! Linux 系统调用

在 x86 下，系统调用由 0x80 中断完成，各个通用寄存器用于传递参数，'EAX 寄存器用于表示系统调用的接口号'，每个系统调用都对应于内核源代码中的一个函数，
它们都是以 sys_ 开头的，比如 exit 调用对应内核中的 sys_exit 函数。Linux 内核版本提供了很多个系统调用，这些系统调用都可以在程序里面直接使用，它
的 C 语言形式被定义在 /usr/include/unistd.h 中

比如我们完全可以绕过 glibc 的 fopen、fread、fclose 打开读取和关闭文件，而直接使用 open()、read()和close() 来实现文件的读取，使用 write 向屏幕
输出字符串(标准输出的文件句柄为0)，使用 read 系统调用来实现读取用户输入(标准输入的文件句柄为1)。不过由于绕过了 glibc 的文件读取机制，所有位于 glibc 
中的缓冲、按行读取文本文件等这些机制都没有了，读取的就是文件的原始数据。

include <stdlib.h>
int main(int argc, char *argv[])
{
    char buffer[64];
    char * error_message = "open file failed\n";
    char * success_message = "open file succeeded\n";
    int fb = open("readme.txt",0,0);
    if(fd == -1)
    {
        write(0,error_message,strlen(error_message));
        return -1;
    }
    write(0,success_message,strlen(success_message));
    read(fd,buffer,64);
    close(fd);
    return 0;
}


我们可以使用 Linux 的 man 命令查看每个系统调用的详细说明，如： man 2 read

READ(2)                    Linux Programmer's Manual                   READ(2)

NAME
       read - read from a file descriptor

SYNOPSIS
       #include <unistd.h>

       ssize_t read(int fd, void *buf, size_t count);

DESCRIPTION
       read()  attempts to read up to count bytes from file descriptor fd into
       the buffer starting at buf.

       On files that support seeking, the read operation commences at the file
       offset, and the file offset is incremented by the number of bytes read.
       If the file offset is at or past the end of file, no  bytes  are  read,
       and read() returns zero.

       If count is zero, read() may detect the errors described below.  In the
       absence of any errors, or if read() does not check for errors, a read()
       with a count of 0 returns zero and has no other effects.

       According to POSIX.1, if count is greater than SSIZE_MAX, the result is
       implementation-defined; see NOTES for the upper limit on Linux'.



// !! 系统调用的弊端

系统调用完成了应用程序和内核交流的工作，事实上，包括 Linux，大部分操作系统的系统调用都有两个特点:

1. 使用不便 ----> '操作系统提供的系统调用接口往往过于原始，程序员需要了解很多与操作系统相关的细节'。如果没有进行很好的包装，使用起来不方便

2. 各个操作系统之间系统调用不兼容 ----> 首先 Windows 系统和 Linux 系统之间的系统调用就基本上完全不同，虽然它们的内容很多都一样，但是定义和实现大不一
   样。即使是同系列的操作系统的系统调用都不一样，比如 Linux 和 UNIX 就不相同



'解决计算机的问题可以通过增加层来实现'，于是运行库挺身而出，它作为系统调用与程序之间的一个抽象层可以保持着这样的特点:

1. 使用简便：因为运行库本身就是语言级别的，它一般都设计相对比较友好
2. 形式统一：运行库有它的标准，叫做标准库， 凡是所有遵循这个标准的运行库理论上都是相互兼容的，不会随着操作系统或编译器的变化而变化


'运行时库将不同的操作系统的系统调用包装为统一固定的接口，使得同样的代码，在不同的操作系统下都可以直接编译，并产生一致的效果'这就是源代码级上的可移植性。
但是运行库也有运行库的缺陷，比如 C 语言的运行库为了保证多个平台之间能够相互通用，于是它只能取各个平台之间功能的交集。