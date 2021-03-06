// !! 4.1　空间与地址分配

对于多个输入目标文件, 链接器如何将它们的各个段合并到输出文件? 或者说, 输出文件中的空间如何分配给输入文件?

// !! 4.1.1　按序叠加

一个最简单的方案就是将输入的目标文件按照次序叠加起来, 如图 4-1 所示。

图 4-1 中的做法的确很简单, 就是直接将各个目标文件依次合并。但是这样做会造成一个问题, 在有很多输入文件的情况下,输出文件将会有很多零散的段。比如一个规模稍大的应用程序可能
会有数百个目标文件, 如果每个目标文件都分别有 .text 段、.data 段和 .bss 段, 那最后的输出文件将会有成百上千个零散的段。这种做法非常浪费空间, 因为每个段都须要有一定的地
址和空间对齐要求, 比如对于 x86 的硬件来说, 段的装载地址和空间的对齐单位是页, 也就是 4 096 字节, 那么就是说如果一个段的长度只有 1 个字节, 它也要在内存中占用 4 096 字
节。'这样会造成内存空间大量的内部碎片, 所以这并不是一个很好的方案'。


// !! 4.1.2　相似段合并

一个更实际的方法是将相同性质的段合并到一起, 比如将所有输入文件的 .text 合并到输出文件的 .text 段, 接着是 .data 段、 .bss 段等, 如图 4-2 所示。

正如我们前文所提到的, '.bss 段在目标文件和可执行文件中并不占用文件的空间, 但是它在装载时占用地址空间'。所以链接器在合并各个段的同时, 也将 .bss 合并, 并且分配虚拟空间。
从 .bss 段的空间分配上我们可以思考一个问题, 那就是这里的所谓的 空间分配 到底是什么空间? 

"链接器为目标文件分配地址和空间"这句话中的"地址和空间"其实有两个含义: 第一个是在输出的可执行文件中的空间; 第二个是在装载后的虚拟地址中的虚拟地址空间。对于有实际数据的段,
比如 .text 和 .data 来说, 它们在文件中和虚拟地址中都要分配空间, 因为它们在这两者中都存在; 而对于 .bss 这样的段来说, 分配空间的意义只局限于虚拟地址空间, 因为它在文件
中并没有内容。

'事实上, 我们在这里谈到的空间分配只关注于虚拟地址空间的分配, 因为这个关系到链接器后面的关于地址计算的步骤, 而可执行文件本身的空间分配与链接过程关系并不是很大'。

现在的链接器空间分配的策略基本上都采用上述方法中的第二种, 使用这种方法的链接器一般都采用一种叫两步链接 (Two-pass Linking) 的方法,也就是说整个链接过程分两步:

'第一步 空间与地址分配'

扫描所有的输入目标文件, 并且获得它们的各个段的长度、属性和位置,'并且将输入目标文件中的符号表中所有的符号定义和符号引用收集起来，统一放到一个全局符号表'。这一步中, 链接器
将能够获得所有输入目标文件的段长度, 并且将它们合并, 计算出输出文件中各个段合并后的长度与位置, 并建立映射关系。


'第二步 符号解析与重定位'

使用上面第一步中收集到的所有信息,读取输入文件中段的数据、重定位信息, 并且进行符号解析与重定位、调整代码中的地址等。事实上第二步是链接过程的核心, 特别是重定位过程。

我们使用 ld 链接器将 a.o 和 b.o 链接起来:

> gcc -c a.c b.c -fno-stack-protector
> ld a.o b.o -e main -o ab

• -e main 表示将 main 函数作为程序入口, ld 链接器默认的程序入口为 _start
• -o ab 表示链接输出文件名为 ab, 默认为 a.out

让我们使用 objdump 来查看链接前后地址的分配情况:

objdump -h a.o

a.o:     文件格式 elf64-x86-64

节：
Idx Name          Size      VMA               LMA               File off  Algn
  0 .text         0000002d  0000000000000000  0000000000000000  00000040  2**0
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000000  0000000000000000  0000000000000000  0000006d  2**0
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  0000000000000000  0000000000000000  0000006d  2**0
                  ALLOC
  3 .comment      0000002c  0000000000000000  0000000000000000  0000006d  2**0
                  CONTENTS, READONLY
  4 .note.GNU-stack 00000000  0000000000000000  0000000000000000  00000099  2**0
                  CONTENTS, READONLY
  5 .note.gnu.property 00000020  0000000000000000  0000000000000000  000000a0  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  6 .eh_frame     00000038  0000000000000000  0000000000000000  000000c0  2**3
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, DATA


objdump -h b.o 

b.o:     文件格式 elf64-x86-64

节：
Idx Name          Size      VMA               LMA               File off  Algn
  0 .text         0000004f  0000000000000000  0000000000000000  00000040  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .data         00000004  0000000000000000  0000000000000000  00000090  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  0000000000000000  0000000000000000  00000094  2**0
                  ALLOC
  3 .comment      0000002c  0000000000000000  0000000000000000  00000094  2**0
                  CONTENTS, READONLY
  4 .note.GNU-stack 00000000  0000000000000000  0000000000000000  000000c0  2**0
                  CONTENTS, READONLY
  5 .note.gnu.property 00000020  0000000000000000  0000000000000000  000000c0  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  6 .eh_frame     00000038  0000000000000000  0000000000000000  000000e0  2**3
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, DATA


objdump -h ab 

ab:     文件格式 elf64-x86-64

节：
Idx Name          Size      VMA               LMA               File off  Algn
  0 .note.gnu.property 00000020  00000000004001c8  00000000004001c8  000001c8  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  1 .text         0000007c  0000000000401000  0000000000401000  00001000  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  2 .eh_frame     00000058  0000000000402000  0000000000402000  00002000  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  3 .data         00000004  0000000000404000  0000000000404000  00003000  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  4 .comment      0000002b  0000000000000000  0000000000000000  00003004  2**0
                  CONTENTS, READONLY


VMA 表示 Virtual Memory Address, 即虚拟地址; LMA 表示Load Memory Address, 即加载地址, 正常情况下这两个值应该是一样的

链接后的程序中所使用的地址已经是程序在进程中的虚拟地址, 即我们关心上面各个段中的 VMA (Virtual Memory Address) 和 Size, 而忽略文件偏移 (File off)。我们可以看到,
在链接之前,目标文件中的所有段的 VMA 都是 0, 因为虚拟空间还没有被分配, 所以它们默认都为 0。等到链接之后, 可执行文件 ab 中的各个段都被分配到了相应的虚拟地址。

整个链接过程前后, 目标文件各段的分配、程序虚拟地址如图 4-3 所示。

从图 4-3 中可以看到, a.o 和 b.o 的代码段被先后叠加起来, 合并成 ab 的一个 .text 段, 加起来的长度为 0x72。所以 ab 的代码段里面肯定包含了 main 函数和 swap 函数的
指令代码。那么, 为什么链接器要将可执行文件 ab 的 .text 分配到 0x08048094、将 .data 分配 0x08049108? 而不是从虚拟空间的 0 地址开始分配呢? 这涉及操作系统的进程虚拟
地址空间的分配规则, 在 Linux 下, ELF可执行文件默认从地址 0x08048000 开始分配。


// !! 4.1.3　符号地址的确定

我们还是以 a.o 和 b.o 作为例子, 来分析这两个步骤中链接器的工作过程。

在第一步的扫描和空间分配阶段, 链接器按照前面介绍的空间分配方法进行分配, 这时候输入文件中的各个段在链接后的虚拟地址就已经确定了, 比如 .text 段起始地址为 0x08048094, 
.data 段的起始地址为 0x08049108。

当前面一步完成之后, 链接器开始计算各个符号的虚拟地址。因为各个符号在段内的相对位置是固定的, 所以这时候其实 main、shared 和 swap 的地址也已经是确定的了, 只不过链接器须
要给每个符号加上一个偏移量, 使它们能够调整到正确的虚拟地址。

比如我们假设 a.o 中的 main 函数相对于 a.o 的 .text 段的偏移是X, 但是经过链接合并以后, a.o 的 .text 段位于虚拟地址 0x08048094, 那么 main 的地址应该是
0x08048094+X。