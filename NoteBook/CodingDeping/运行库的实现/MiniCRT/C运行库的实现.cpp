// !! C 语言运行库

CRT 的基本功能及设计的几个基本原则:

1. 首先 Mini CRT 应该以 ANSI C 的标准库为目标，尽量做到与其接口相一致

2. 具有自己的入口函数（mini_crt_entry）

3. 基本的进程相关操作（exit）

4. 支持堆操作（malloc、free）

5. 支持基本的文件操作（fopen、fread、fwrite、fclose、fseek）

6. 支持基本的字符串操作（strcpy、strlen、strcmp）

7. 支持格式化字符串和输出操作（printf、sprintf）

8. 支持 atexit() 函数

9. 跨平台

为了使CRT能够同时支持 Linux 和 Windows 两个平台，必须针对这两个操作系统环境的不同进行条件编译。在 Mini CRT 中，使用宏 WIN32 为标准来决定是 
Windows 还是 Linux，因此实际的代码常常呈现这样的结构:

#ifdef WIN32
//Windows部分实现代码
#else
//Linux部分实现代码
#endif


// !! 实现流程

// !! 开始

1. 入口函数

   程序运行的最初入口点不是 main 函数，而是由运行库为其提供的入口函数。。它主要负责三部分工作：准备好程序运行环境以及初始化运行库，调用 main 函数执行程
   序主题，清理程序运行后的各种资源； 运行库为所有程序提供的入口函数应该相同， 在链接程序时必须指定该入口函数名
   入口函数：
			void mini_crt_entry(void)
			{
				//初始化部分 ---> 这里的初始化主要负责准备好程序运行的环境，包括准备 main 函数的参数，初始化运行库，包括堆，IO 等
				int ret = main();
				//结束部分 ------> 主要负责清理程序运行资源
				exit(ret);
			}

2. main

   我们知道 main 函数的原型为: int main(int argc, char *argv[]), 其中 argc 和 argv 分别是 main 函数的 2 个参数，它们分别表示程序运行时的参
   数个数和执行指向参数的字符串指针数组。在 Linux 下，当进程被初始化时，它的堆栈结构中就保存着环境变量和传递给 main 函数的参数，我们可以通过 ESP 寄存
   器获得这 2 个参数。但是一旦进入到 mini_crt_entry 之后，ESP 寄存器就会随着函数的执行而被改变，我们知道 EBP 的内容就是进入函数后 ESP+4。那么可以
   推断 EBP-4 所执行的内容应该就是 argc,而 EBP-8 就是 argv

3. CRT初始化
   完成了获取 main 函数参数的代码后，还需要在入口函数里对 CRT 进行初始化。需要初始化的主要是堆和 IO 部分

4. 结束部分处理
   Mini CRT 的结束部分很简单，它要完成 2 项任务：一个就是由调用 atexit() 注册的退出回调函数；另外一个就是实现结束进程。


// !! 堆的实现

在遵循 Mini CRT 的原则下，将 Mini CRT 堆的实现概括为如下几条:

1.实现一个以'空闲链表算法'为基础的堆空间分配算法
2.为了简单起见，堆空间大小固定为 32MB，初始化后空间再也不扩展或缩小
3.在 Windows 平台下不适用 HeapAlloc 等堆分配算法，采用 VirtualAlloc 向系统直接申请 32MB 空间
4.在 Linux 平台下，使用 brk 将数据段结束地址向后调整 32MB，将这块空间做为堆空间
  brk 系统调用能够设置进程的数据段 .data 边界，而 sbrk 能够移动进程的数据段边界，显然若是将数据段边界后移，就至关于分配了必定量的内存。
  可是这段内存初始只是分配了虚拟空间，这些空间的申请一开始是不会提交的（即不会分配物理页面），当进程需要访问一个地址的时候，操作系统会检测到页缺乏
  异常，从而会为被访问的地址所在的页分配物理页面。故而这种被动的物理分配，又被称为按践踏分配(Alloc on Trample)。 


'整个堆空间按照是否被占用而被分割成若干个空闲（Free）块和占用（Used）块，它们直接由双向链表链接起来'

堆分配算法的基本步骤：

1. 当用户需要申请一块内存时，堆分配算法遍历整个链表，直到找到一块足够大的空闲块（Free Block），如果这个空闲块大小刚好等于所申请的大小，那么直接将这个
   空闲块标记为（Used Block），然后将它的地址返回给用户。

2. 如果空闲块大小大于所申请的大小，那么这个空闲块将会被分成两块，其中一块大小为所申请的大小，标记为占用(Used)； 另一块为空闲块(Free)

3. 当用户释放某一块空间时，堆分配算法会判断被释放前后两个块是否为空闲块，如果是，将它们合并成一个空闲块。



// !! IO 与文件操作

在传统的 C 语言和 UNIX 里面，IO 和文件是同一个概念，'所有的 IO 都是通过对文件的操作来实现的'。因此，只要实现了文件的基本操作（fopen、fread、fwrite、fclose 和 
fseek），即完成了 Mini CRT 的 IO 部分。

Mini CRT 的 IO 部分设计实现的基本原则:

1. 仅实现基本的文件操作，包括 fopen、fread、fwrite、fclose 及 fseek

2. 为了简单起见，不实现缓冲（Buffer）机制

3. 不对 Windows 下的换行机制进行转换，即 “\r\n” 与 “\n” 之间不进行转换

4. 支持三个标准的输入输出 stdin、stdout 和 stderr

5. 在 Windows 下，文件基本操作可以使用API：CreateFile、ReadFile、WriteFile、CloseHandle 和 SetFilePointer 实现

6. Linux 不像 Windows 那样有API接口，必须使用内嵌汇编实现 open、read、write、close 和 seek 这几个系统调用

7. fopen 时仅区分 “r”、“w” 和 “+” 这几种模式及它们的组合，不对文本模式和二进制模式进行区分，不支持追加模式（“a”）


// !! 字符串相关操作

字符串相关的操作也是 CRT 的一部分，包括计算字符串长度、比较两个字符串、整数与字符串之间的转换等。'由于这部分功能无须涉及任何与内核交互，是纯粹的用户态的计算'，
所以它们的实现相对比较简单。



// !! 格式化字符串

CRT 中一个如雷贯耳的函数，那就是 printf

1. printf 实现仅支持%d、%s，且不支持格式控制（比如%08d）

2. 实现 fprintf 和 vfprintf，实际上 printf 是 fprintf 的特殊形式，即目标文件为标准输出的 fprintf

3. 实现与文件字符串操作相关的几个函数，fputc 和 fputs


// !! 如何使用Mini CRT

'Mini CRT 也将以库文件和头文件的形式提供给用户'。。首先建立一个 minicrt.h 的头文件，然后将所有相关的常数定义、宏定义，以及 Mini CRT 所实现的函数声明等放在该头文
件里。当用户程序使用 Mini CRT 时，仅需要 #include “minicrt.h” 即可。

由于动态库的实现比静态库要复杂，所以 Mini CRT 仅仅以静态库的形式提供给最终用户，在 Linux 下它是 minicrt.a。

// !! linux (手动编译链接)

gcc -c -fno-builtin -nostdlib  entry.c malloc.c stdio.c string.c printf.c
ar -rs minicrt.a malloc.o printf.o stdio.o string.o
gcc -c -ggdb -fno-builtin -nostdlib MiniCRTDemo.c
ld -static -e mini_crt_entry entry.o MiniCRTDemo.o minicrt.a -o MiniCRTDemo


1. -fno-builtin参数: 关闭 GCC 的内置函数功能，默认状况下 GCC 会把 strlen\strcmp 等函数展开成它内部的实现
2. -nostdlib: 表示不适用任何来自 Glibc、GCC 的库文件和启动文件，它包含了-nostartfiles这个参数
3. -fno-stack-protector: 关闭堆栈保护功能，最新版本的 GCC 在处理变长参数函数的状况下会要求实现对堆栈的保护函数


// !! linux (make)

make
./test
make clean