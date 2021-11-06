
// !! 目标文件是什么样的

一个 目标文件/可执行文件 的基本组成部分都是段（Segment/Section）, 段就是'把一个程序的不同部分分类存放'，形成不同的段。

一个目标文件最基本的段包括：

1. 代码段（程序段）.text，代码段就是存放程序的逻辑代码部分

2. 数据段.data，用于存放变量数据，但是这里存放的是已初始化的全局、静态变量

3. BSS（Block Started by Symbol）.bss，BSS 是'为未初始化的全局变量和局部的静态变量预留位置'

// !! SimpleSection.o 的结构

// SimpleSection.c
int printf(const char *format, ...);

int global_init_var = 84;
int global_uninit_var;

void func1(int i)
{
    printf("%d\n", i);
}

int main()
{
    static int static_var = 85;
    static int static_var2;

    int a = 1;
    int b;

    func1(static_var+static_var2+a+b);

    return a;
    
}

// gcc -c 表示只编译不链接
gcc -c SimpleSection.c  

// !! objdump 查看目标文件的结构和内容

具体使用参考： objdump --help

-h 表示 Display the contents of the section headers

» objdump -h SimpleSection.o                      

SimpleSection.o：     文件格式 elf64-x86-64

节：
Idx Name          Size      VMA               LMA               File off  Algn
  0 .text         0000005f  0000000000000000  0000000000000000  00000040  2**0
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000008  0000000000000000  0000000000000000  000000a0  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000004  0000000000000000  0000000000000000  000000a8  2**2
                  ALLOC
  3 .rodata       00000004  0000000000000000  0000000000000000  000000a8  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .comment      0000002b  0000000000000000  0000000000000000  000000ac  2**0
                  CONTENTS, READONLY
  5 .note.GNU-stack 00000000  0000000000000000  0000000000000000  000000d7  2**0
                  CONTENTS, READONLY
  6 .note.gnu.property 00000020  0000000000000000  0000000000000000  000000d8  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  7 .eh_frame     00000058  0000000000000000  0000000000000000  000000f8  2**3


// !! objdump -s -d SimpleSection.o 

objdump 的 -s 参数会将所有段的内容以十六进制的方式打印出来，-d 参数可以将所以包含的指令段反汇编

» objdump -s -d SimpleSection.o

SimpleSection.o：     文件格式 elf64-x86-64

Contents of section .text:
 0000 f30f1efa 554889e5 4883ec10 897dfc8b  ....UH..H....}..
 0010 45fc89c6 488d3d00 000000b8 00000000  E...H.=.........
 0020 e8000000 0090c9c3 f30f1efa 554889e5  ............UH..
 0030 4883ec10 c745f801 0000008b 15000000  H....E..........
 0040 008b0500 00000001 c28b45f8 01c28b45  ..........E....E
 0050 fc01d089 c7e80000 00008b45 f8c9c3    ...........E... 
Contents of section .data:
 0000 54000000 55000000                    T...U...        
Contents of section .rodata:
 0000 25640a00                             %d..            
Contents of section .comment:
 0000 00474343 3a202855 62756e74 7520392e  .GCC: (Ubuntu 9.
 0010 332e302d 31377562 756e7475 317e3230  3.0-17ubuntu1~20
 0020 2e303429 20392e33 2e3000             .04) 9.3.0.     
Contents of section .note.gnu.property:
 0000 04000000 10000000 05000000 474e5500  ............GNU.
 0010 020000c0 04000000 03000000 00000000  ................
Contents of section .eh_frame:
 0000 14000000 00000000 017a5200 01781001  .........zR..x..
 0010 1b0c0708 90010000 1c000000 1c000000  ................
 0020 00000000 28000000 00450e10 8602430d  ....(....E....C.
 0030 065f0c07 08000000 1c000000 3c000000  ._..........<...
 0040 00000000 37000000 00450e10 8602430d  ....7....E....C.
 0050 066e0c07 08000000                    .n......        

Disassembly of section .text:

0000000000000000 <func1>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	48 83 ec 10          	sub    $0x10,%rsp
   c:	89 7d fc             	mov    %edi,-0x4(%rbp)
   f:	8b 45 fc             	mov    -0x4(%rbp),%eax
  12:	89 c6                	mov    %eax,%esi
  14:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # 1b <func1+0x1b>
  1b:	b8 00 00 00 00       	mov    $0x0,%eax
  20:	e8 00 00 00 00       	callq  25 <func1+0x25>
  25:	90                   	nop
  26:	c9                   	leaveq 
  27:	c3                   	retq   

0000000000000028 <main>:
  28:	f3 0f 1e fa          	endbr64 
  2c:	55                   	push   %rbp
  2d:	48 89 e5             	mov    %rsp,%rbp
  30:	48 83 ec 10          	sub    $0x10,%rsp
  34:	c7 45 f8 01 00 00 00 	movl   $0x1,-0x8(%rbp)
  3b:	8b 15 00 00 00 00    	mov    0x0(%rip),%edx        # 41 <main+0x19>
  41:	8b 05 00 00 00 00    	mov    0x0(%rip),%eax        # 47 <main+0x1f>
  47:	01 c2                	add    %eax,%edx
  49:	8b 45 f8             	mov    -0x8(%rbp),%eax
  4c:	01 c2                	add    %eax,%edx
  4e:	8b 45 fc             	mov    -0x4(%rbp),%eax
  51:	01 d0                	add    %edx,%eax
  53:	89 c7                	mov    %eax,%edi
  55:	e8 00 00 00 00       	callq  5a <main+0x32>
  5a:	8b 45 f8             	mov    -0x8(%rbp),%eax
  5d:	c9                   	leaveq 
  5e:	c3                   	retq   


// !! linux 下 size 命令可以用来查看 ELF 文件的代码段、数据段和 BSS 段的长度

» size SimpleSection.o                                                                                         1 ↵ parallels@xforg
   text	   data	    bss	    dec	    hex	filename
    219	      8	      4	    231	     e7	SimpleSection.o