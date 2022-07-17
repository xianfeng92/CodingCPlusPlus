// !! 7.2　简单的动态链接例子

首先通过一个简单的例子来大致地感受一下动态链接, 我们还是以图 7-2 中的 Program1 和 Program2 来做演示。我们分别需要如下几个源文件: Program1.c、Program2.c、Lib.c 
和 Lib.h。它们的源代码如清单 7-1 所示。


程序很简单, 两个程序的主要模块 Program1.c 和 Program2.c 分别调用了 Lib.c 里面的 foobar() 函数, 传进去一个数字, foobar() 函数的作用就是打印这个数字。
然后我们使用 GCC 将 Lib.c 编译成一个共享对象文件:

> gcc -fPIC -shared -o Lib.so Lib.c

上面 GCC 命令中的参数 -shared 表示产生共享对象;

'这时候我们得到了一个 Lib.so 文件, 这就是包含了 Lib.c 的 foobar() 函数的共享对象文件'。

然后我们分别编译链接 Program1.c 和 Program2.c:

✗ gcc -o Program1 Program1.c ./Lib.so
✗ gcc -o Program2 Program2.c ./Lib.so

这样我们得到了两个程序 Program1 和 Program2, 这两个程序都使用了 Lib.so 里面的 foobar() 函数。

从 Program1 的角度看, 整个编译和链接过程如图 7-3 所示。

Lib.c 被编译成 Lib.so 共享对象文件, Program1.c 被编译成 Program1.o 之后, 链接成为可执行程序 Program1。

图 7-3 中有一个步骤与静态链接不一样, 那就是 Program1.o 被连接成可执行文件的这一步。在静态链接中, 这一步链接过程会把 Program1.o 和 Lib.o 链接到一起, 并且产生输出
可执行文件 Program1。但是在这里, Lib.o 没有被链接进来, 链接的输入目标文件只有 Program1.o, '但从前面的命令行中我们看到, Lib.so 也参与了链接过程。这是怎么回事呢'?


// !! 关于模块 (Module)

'在静态链接时, 整个程序最终只有一个可执行文件, 它是一个不可以分割的整体';

在动态链接下, 一个程序被分成了若干个文件, 有程序的主要部分, 即可执行文件 (Program1) 和程序所依赖的共享对象 (Lib.so), 很多时候我们也把这些部分称为模块, 即动态链接
下的可执行文件和共享对象都可以看作是程序的一个模块。

让我们再回到动态链接的机制上来, 当程序模块 Program1.c 被编译成为 Program1.o 时, 编译器还不不知道 foobar() 函数的地址, 这个内容我们已在静态链接中解释过了。当链接器
将 Program1.o 链接成可执行文件时, 这时候链接器必须确定 Program1.o 中所引用的 foobar() 函数的性质。如果 foobar() 是一个定义与其他静态目标模块中的函数, 那么链接器
将会按照静态链接的规则, 将 Program1.o 中的 foobar 地址引用重定位; '如果 foobar() 是一个定义在某个动态共享对象中的函数, 那么链接器就会将这个符号的引用标记为一个动态
链接的符号, 不对它进行地址重定位, 把这个过程留到装载时再进行'。

那么这里就有个问题, 链接器如何知道 foobar 的引用是一个静态符号还是一个动态符号? 这实际上就是我们要用到 Lib.so 的原因。

'Lib.so 中保存了完整的符号信息' (因为运行时进行动态链接还须使用符号信息), 把 Lib.so 也作为链接的输入文件之一, 链接器在解析符号时就可以知道: foobar 是一个定义在 
Lib.so 的动态符号。这样链接器就可以对 foobar 的引用做特殊的处理, 使它成为一个对动态符号的引用。



// !! 动态链接程序运行时地址空间分布

对于静态链接的可执行文件来说, 整个进程只有一个文件要被映射, 那就是可执行文件本身。但是对于动态链接来说, 除了可执行文件本身之外, 还有它所依赖的共享目标文件。
那么这种情况下, 进程的地址空间分布又会怎样呢?


我们还是以上面的 Program1 为例, 但是当我们试图运行 Program1 并且查看它的进程空间分布时, 程序一运行就结束了。所以我们得对程序做适当的修改, 在 Lib.c 中的 foobar()
函数里面加入 sleep 函数:

#include <stdio.h>

void foobar(int i){
    printf("Printing from Lib.so %d\n", i);
    sleep(-1);
}

然后就可以查看进程的虚拟地址空间分布:

> ./Program1 &
[7] 110247
Printing from Lib.so 1                                                          
> cat /proc/110247/maps 
56542b5f0000-56542b5f1000 r--p 00000000 08:05 2490968                    /Program1
56542b5f1000-56542b5f2000 r-xp 00001000 08:05 2490968                    /Program1
56542b5f2000-56542b5f3000 r--p 00002000 08:05 2490968                    /Program1
56542b5f3000-56542b5f4000 r--p 00002000 08:05 2490968                    /Program1
56542b5f4000-56542b5f5000 rw-p 00003000 08:05 2490968                    /Program1
56542ca9e000-56542cabf000 rw-p 00000000 00:00 0                          [heap]
7fd3bfbbb000-7fd3bfbbe000 rw-p 00000000 00:00 0 
7fd3bfbbe000-7fd3bfbe0000 r--p 00000000 08:05 2631845                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7fd3bfbe0000-7fd3bfd58000 r-xp 00022000 08:05 2631845                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7fd3bfd58000-7fd3bfda6000 r--p 0019a000 08:05 2631845                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7fd3bfda6000-7fd3bfdaa000 r--p 001e7000 08:05 2631845                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7fd3bfdaa000-7fd3bfdac000 rw-p 001eb000 08:05 2631845                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7fd3bfdac000-7fd3bfdb0000 rw-p 00000000 00:00 0 
7fd3bfdc6000-7fd3bfdc7000 r--p 00000000 08:05 2490952                    /Lib.so
7fd3bfdc7000-7fd3bfdc8000 r-xp 00001000 08:05 2490952                    /Lib.so
7fd3bfdc8000-7fd3bfdc9000 r--p 00002000 08:05 2490952                    /Lib.so
7fd3bfdc9000-7fd3bfdca000 r--p 00002000 08:05 2490952                    /Lib.so
7fd3bfdca000-7fd3bfdcb000 rw-p 00003000 08:05 2490952                    /Lib.so
7fd3bfdcb000-7fd3bfdcd000 rw-p 00000000 00:00 0 
7fd3bfdcd000-7fd3bfdce000 r--p 00000000 08:05 2631841                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7fd3bfdce000-7fd3bfdf1000 r-xp 00001000 08:05 2631841                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7fd3bfdf1000-7fd3bfdf9000 r--p 00024000 08:05 2631841                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7fd3bfdfa000-7fd3bfdfb000 r--p 0002c000 08:05 2631841                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7fd3bfdfb000-7fd3bfdfc000 rw-p 0002d000 08:05 2631841                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7fd3bfdfc000-7fd3bfdfd000 rw-p 00000000 00:00 0 
7ffeb897d000-7ffeb899e000 rw-p 00000000 00:00 0                          [stack]
7ffeb89a4000-7ffeb89a8000 r--p 00000000 00:00 0                          [vvar]
7ffeb89a8000-7ffeb89aa000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0                  [vsyscall]


我们看到, 整个进程虚拟地址空间中, 多出了几个文件的映射。Lib.so 与 Program1 一样, 它们都是被操作系统用同样的方法映射至进程的虚拟地址空间, 只是它们占据的虚拟地址和长度
不同。Program1 除了使用 Lib.so 以外, 它还用到了动态链接形式的 C 语言运行库 ibc-2.31.so。另外还有一个很值得关注的共享对象就是 ld-2.31.so, 它实际上是 Linux 下的动
态链接器。动态链接器与普通共享对象一样被映射到了进程的地址空间, '在系统开始运行 Program1 之前, 首先会把控制权交给动态链接器, 由它完成所有的动态链接工作以后再把控制权交
给 Program1, 然后开始执行'。

我们通过 readelf 工具来查看 Lib.so 的装载属性, 就如我们在前面查看普通程序一样:

>  readelf -l Lib.so

Elf 文件类型为 DYN (共享目标文件)
Entry point 0x1080
There are 11 program headers, starting at offset 64

程序头：
  Type           Offset             VirtAddr           PhysAddr
                 FileSiz            MemSiz              Flags  Align
  LOAD           0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000560 0x0000000000000560  R      0x1000
  LOAD           0x0000000000001000 0x0000000000001000 0x0000000000001000
                 0x000000000000017d 0x000000000000017d  R E    0x1000
  LOAD           0x0000000000002000 0x0000000000002000 0x0000000000002000
                 0x00000000000000dc 0x00000000000000dc  R      0x1000
  LOAD           0x0000000000002e10 0x0000000000003e10 0x0000000000003e10
                 0x0000000000000220 0x0000000000000228  RW     0x1000
  DYNAMIC        0x0000000000002e20 0x0000000000003e20 0x0000000000003e20
                 0x00000000000001c0 0x00000000000001c0  RW     0x8
  NOTE           0x00000000000002a8 0x00000000000002a8 0x00000000000002a8
                 0x0000000000000020 0x0000000000000020  R      0x8
  NOTE           0x00000000000002c8 0x00000000000002c8 0x00000000000002c8
                 0x0000000000000024 0x0000000000000024  R      0x4
  GNU_PROPERTY   0x00000000000002a8 0x00000000000002a8 0x00000000000002a8
                 0x0000000000000020 0x0000000000000020  R      0x8
  GNU_EH_FRAME   0x000000000000201c 0x000000000000201c 0x000000000000201c
                 0x000000000000002c 0x000000000000002c  R      0x4
  GNU_STACK      0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000000 0x0000000000000000  RW     0x10
  GNU_RELRO      0x0000000000002e10 0x0000000000003e10 0x0000000000003e10
                 0x00000000000001f0 0x00000000000001f0  R      0x1

 Section to Segment mapping:
  段节...
   00     .note.gnu.property .note.gnu.build-id .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt 
   01     .init .plt .plt.got .plt.sec .text .fini 
   02     .rodata .eh_frame_hdr .eh_frame 
   03     .init_array .fini_array .dynamic .got .got.plt .data .bss 
   04     .dynamic 
   05     .note.gnu.property 
   06     .note.gnu.build-id 
   07     .note.gnu.property 
   08     .eh_frame_hdr 
   09     
   10     .init_array .fini_array .dynamic .got 


除了文件的类型与普通程序不同以外, 其他几乎与普通程序一样。还有有一点比较不同的是, 动态链接模块的装载地址是从地址 0x00000000 开始的。我们知道这个地址是无效地址, 并且从上
面的进程虚拟空间分布看到, Lib.so 的最终装载地址并不是 0x00000000, 而是 0xb7efc000。

从这一点我们可以推断, '共享对象的最终装载地址在编译时是不确定的, 而是在装载时, 装载器根据当前地址空间的空闲情况, 动态分配一块足够大小的虚拟地址空间给相应的共享对象'。