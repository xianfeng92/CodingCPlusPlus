
// !! 符号解析与重定位

在完成空间和地址的分配之后, '链接器就进入了符号解析与重定位的步骤, 这也是静态链接的核心内容'

使用 objdump -d 参数可以查看到 a.o 的反汇编代码

// a.c
extern int shared;
int main() //全局符号
{
    int a = 100;
    swap(&a, &shared);
}

» objdump -d a.o                                                      

a.o：     文件格式 elf64-x86-64

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
  21:	b8 00 00 00 00       	mov    $0x0,%eax
  26:	e8 00 00 00 00       	callq  2b <main+0x2b>
  2b:	b8 00 00 00 00       	mov    $0x0,%eax
  30:	c9                   	leaveq 
  31:	c3                   	retq   
-----------------------------------------------------------

1. 程序代码中使用的是 VAM ,在未进行空间分配之前,main 函数的地址是 0000000000000000

2. 引用 shared 和 swap 时的地址全部为 00 00 00 00

» objdump -d ab                                                       

ab：     文件格式 elf64-x86-64


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
  401021:	b8 00 00 00 00       	mov    $0x0,%eax
  401026:	e8 07 00 00 00       	callq  401032 <swap>
  40102b:	b8 00 00 00 00       	mov    $0x0,%eax
  401030:	c9                   	leaveq 
  401031:	c3                   	retq   

1. a.o 和 b.o 链接后， shared 的引用地址为 e2 2f 00 00， swap 的引用地址为 07 00 00 00

// !! 重定位表

ELF文件中，有一个叫做重定位表的结构专门用来保存这些与重定位相关的信息，它在ELF文件中往往是一个或多个段。重定位表有时候也叫做重定位段。

'使用 objdump 来查看目标文件的重定位表'

 » objdump -r a.o                                                      

a.o：     文件格式 elf64-x86-64

RELOCATION RECORDS FOR [.text]:
OFFSET           TYPE              VALUE 
000000000000001a R_X86_64_PC32     shared-0x0000000000000004
0000000000000027 R_X86_64_PLT32    swap-0x0000000000000004

objdump -r a.o  这个命令可以用来查看 a.o 里面需要重定位的地位，即 a.o 所引用到的外部符号的地址。每个需要被重定位的地方叫一个重定位入口，
重定位入口的偏移表示。从 a.o 的重定位符号表中可以看出 000000000000001a 和 0000000000000027 地址部分需要重定位。


// !! 符号解析

在重定位的过程中也伴随这符号解析的过程，'每个重定位的入口都是对一个符号的引用'， 那么当链接器须要对某个符号的引用进行重定位时，它就要确定这个符号
的目标地址。'这时候链接器就会去查找由所有输入目标文件的符号组成的全局符号表，找到相应的符号进行重定位'。


'链接器扫面完所有输入目标文件之后，所有这些未定义的符号都应该能够在全局符号表中找到，否则链接器就报符号未定义错误'。

