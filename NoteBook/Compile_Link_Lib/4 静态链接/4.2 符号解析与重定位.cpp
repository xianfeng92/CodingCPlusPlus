// !! 4.2　符号解析与重定位

// !! 4.2.1　重定位

'在完成空间和地址的分配步骤以后, 链接器就进入了符号解析与重定位的步骤, 这也是静态链接的核心内容'。

在分析符号解析和重定位之前, 首先让我们来看看 a.o 里面是怎么使用这两个外部符号的, 也就是说我们在 a.c 的源程序里面使用了 shared 变量和 swap 函数, 那么编译器在将 a.c 
编译成指令时, 它如何访问 shared 变量? 如何调用 swap 函数?

使用 objdump 的 -d 参数可以看到 a.o 的代码段反汇编结果:

objdump -d a.o 

a.o:     文件格式 elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	48 83 ec 10          	sub    $0x10,%rsp
   c:	c7 45 fc 64 00 00 00 	movl   $0x64,-0x4(%rbp)
  13:	48 8d 45 fc          	lea    -0x4(%rbp),%rax
  17:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 1e <main+0x1e>
  1e:	48 89 c7             	mov    %rax,%rdi
  21:	e8 00 00 00 00       	callq  26 <main+0x26>
  26:	b8 00 00 00 00       	mov    $0x0,%eax
  2b:	c9                   	leaveq 
  2c:	c3                   	retq 

我们可以很清楚地看到 a.o 的反汇编结果中, a.o 共定义了一个函数 main。这个函数占用 0x33 个字节, 共 11 条指令; 最左边那列是每条指令的偏移量, 每一行代表一条指令。


objdump -d ab 

ab:     文件格式 elf64-x86-64

Disassembly of section .text:

0000000000401000 <main>:
  401000:	f3 0f 1e fa          	endbr64 
  401004:	55                   	push   %rbp
  401005:	48 89 e5             	mov    %rsp,%rbp
  401008:	48 83 ec 10          	sub    $0x10,%rsp
  40100c:	c7 45 fc 64 00 00 00 	movl   $0x64,-0x4(%rbp)
  401013:	48 8d 45 fc          	lea    -0x4(%rbp),%rax
  401017:	48 8d 35 e2 2f 00 00 	lea    0x2fe2(%rip),%rsi        # 404000 <shared>
  40101e:	48 89 c7             	mov    %rax,%rdi
  401021:	e8 07 00 00 00       	callq  40102d <swap>
  401026:	b8 00 00 00 00       	mov    $0x0,%eax
  40102b:	c9                   	leaveq 
  40102c:	c3                   	retq   

000000000040102d <swap>:
  40102d:	f3 0f 1e fa          	endbr64 
  401031:	55                   	push   %rbp
  401032:	48 89 e5             	mov    %rsp,%rbp
  401035:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  401039:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  40103d:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  401041:	8b 10                	mov    (%rax),%edx
  401043:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  401047:	8b 00                	mov    (%rax),%eax
  401049:	31 c2                	xor    %eax,%edx
  40104b:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  40104f:	89 10                	mov    %edx,(%rax)
  401051:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  401055:	8b 10                	mov    (%rax),%edx
  401057:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  40105b:	8b 00                	mov    (%rax),%eax
  40105d:	31 c2                	xor    %eax,%edx
  40105f:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  401063:	89 10                	mov    %edx,(%rax)
  401065:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  401069:	8b 10                	mov    (%rax),%edx
  40106b:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  40106f:	8b 00                	mov    (%rax),%eax
  401071:	31 c2                	xor    %eax,%edx
  401073:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  401077:	89 10                	mov    %edx,(%rax)
  401079:	90                   	nop
  40107a:	5d                   	pop    %rbp
  40107b:	c3                   	retq   


// !! 4.2.2　重定位表

那么链接器是怎么知道哪些指令是要被调整的呢? 这些指令的哪些部分要被调整? 怎么调整? 比如上面例子中 mov 指令和 call 指令的调整方式就有所不同。事实上在 ELF 文件中, 有一个
叫重定位表(Relocation Table) 的结构专门用来保存这些与重定位相关的信息, 我们在前面介绍 ELF 文件结构时已经提到过了重定位表, 它在 ELF 文件中往往是一个或多个段。

'对于可重定位的 ELF 文件来说, 它必须包含有重定位表, 用来描述如何修改相应的段里的内容'。对于每个要被重定位的 ELF 段都有一个对应的重定位表, 而一个重定位表往往就是 ELF 文
件中的一个段, 所以其实重定位表也可以叫重定位段, 我们在这里统一称作重定位表。比如代码段 .text 如有要被重定位的地方, 那么会有一个相对应叫 .rel.text 的段保存了代码段的重
定位表; 如果代码段 .data 有要被重定位的地方, 就会有一个相对应叫 .rel.data 的段保存了数据段的重定位表。

我们可以使用 objdump 来查看目标文件的重定位表:

objdump -r a.o 

a.o:     文件格式 elf64-x86-64

RELOCATION RECORDS FOR [.text]:
OFFSET           TYPE              VALUE 
000000000000001a R_X86_64_PC32     shared-0x0000000000000004
0000000000000022 R_X86_64_PLT32    swap-0x0000000000000004


RELOCATION RECORDS FOR [.eh_frame]:
OFFSET           TYPE              VALUE 
0000000000000020 R_X86_64_PC32     .text

这个命令可以用来查看 a.o 里面要重定位的地方, 即 a.o 所有引用到外部符号的地址。'每个要被重定位的地方叫一个重定位入口 (Relocation Entry), 我们可以看到 a.o 里面有两个
重定位入口'。

重定位入口的偏移 (Offset) 表示该入口在要被重定位的段中的位置, "RELOCATION RECORDS FOR [.text]" 表示这个重定位表是代码段的重定位表, 所以偏移表示代码段中须要被调
整的位置。



// !! 4.2.3　符号解析

'在我们通常的观念里, 之所以要链接是因为我们目标文件中用到的符号被定义在其他目标文件, 所以要将它们链接起来'。

比如我们直接使用 ld 来链接 a.o, 而不将 b.o 作为输入。链接器就会发现 shared 和 swap 两个符号没有被定义, 没有办法完成链接工作:

> ld a.o
ld: 警告: 无法找到项目符号 _start; 缺省为 0000000000401000
ld: a.o: in function `main':
a.c:(.text+0x1a): undefined reference to `shared'
ld: a.c:(.text+0x22): undefined reference to 'swap'

这也是我们平时在编写程序的时候最常碰到的问题之一, 就是链接时符号未定义。'导致这个问题的原因很多, 最常见的一般都是链接时缺少了某个库或者输入目标文件路径不正确或符号的声明
与定义不一样'。所以从普通程序员的角度看, 符号的解析占据了链接过程的主要内容。

其实重定位过程也伴随着符号的解析过程, 每个目标文件都可能定义一些符号, 也可能引用到定义在其他目标文件的符号。重定位的过程中, 每个重定位的入口都是对一个符号的引用, 那么'当
链接器须要对某个符号的引用进行重定位时, 它就要确定这个符号的目标地址'。这时候链接器就会去查找由所有输入目标文件的符号表组成的全局符号表, 找到相应的符号后进行重定位。

比如我们查看 a.o 的符号表:

readelf -s a.o 

Symbol table '.symtab' contains 13 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS a.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    6 
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    7 
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    8 
     8: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 
     9: 0000000000000000    45 FUNC    GLOBAL DEFAULT    1 main
    10: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND shared
    11: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _GLOBAL_OFFSET_TABLE_
    12: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND swap

GLOBAL 类型的符号, 除了 main 函数是定义在代码段之外, 其他两个 shared 和 swap 都是 UND, 即 undefined 未定义类型, 这种未定义的符号都是因为该目标文件中有关于它们的
重定位项。'在链接器扫描完所有的输入目标文件之后, 所有这些未定义的符号都应该能够在全局符号表中找到, 否则链接器就报符号未定义错误'。