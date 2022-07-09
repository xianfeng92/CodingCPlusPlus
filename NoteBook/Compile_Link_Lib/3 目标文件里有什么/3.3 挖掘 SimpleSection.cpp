// !! 3.3　挖掘SimpleSection.o

很多问题其实在表面上看似很简单, 其实深入内部会发现很多鲜为人知的秘密, 或者发现以前自己认为理所当然的东西居然是错误的或者是有偏差的。

'真正了不起的程序员对自己的程序的每一个字节都了如指掌'。

                                     ——佚名


int printf( const char* format, ... );

int global_init_var = 84;
int global_uninit_var;

void func1( int i ){
    printf( "%d\n",  i );
}

int main(){

    static int static_var = 85;
    static int static_var2;
    int a = 1;
    int b;
    func1( static_var + static_var2 + a + b );

    return a;
}

我们使用 GCC 来编译这个文件(参数 -c 表示只编译不链接):

> gcc -c SimpleSection.c

2080 7月   9 12:34  SimpleSection.o

我们得到了一个 2080 字节的 SimpleSection.o 目标文件。

我们可以使用 binutils 的工具 objdump 来查看 object 内部的结构:

> objdump -h SimpleSection.o 

SimpleSection.o:     文件格式 elf64-x86-64

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
  4 .comment      0000002c  0000000000000000  0000000000000000  000000ac  2**0
                  CONTENTS, READONLY
  5 .note.GNU-stack 00000000  0000000000000000  0000000000000000  000000d8  2**0
                  CONTENTS, READONLY
  6 .note.gnu.property 00000020  0000000000000000  0000000000000000  000000d8  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  7 .eh_frame     00000058  0000000000000000  0000000000000000  000000f8  2**3
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, DATA

参数 -h 就是把 ELF 文件的各个段的基本信息打印出来。

从上面的结果来看, SimpleSection.o 的段的数量比我们想象中的要多, 除了最基本的代码段、数据段和 BSS 段以外, 还有 3 个段分别是只读数据段 (.rodata)、注释信息段
(.comment) 和堆栈提示段(.note.GNU-stack), 这 3 个额外的段的意义我们暂且不去细究。

先来看看几个重要的段的属性, 其中最容易理解的是段的长度 (Size) 和段所在的位置 (File Offset), 每个段的第 2 行中的 CONTENTS、ALLOC 等表示段的各种属性, CONTENTS
表示该段在文件中存在。我们可以看到 BSS 段没有 CONTENTS, 表示它实际上在 ELF 文件中不存在内容。

有一个专门的命令叫做 size, 它可以用来查看 ELF 文件的代码段、数据段和BSS段的长度:

> size SimpleSection.o

 text	   data	    bss	    dec	    hex	filename
 219	      8	      4	    231	     e7	SimpleSection.o


// !! 3.3.1　代码段

挖掘各个段的内容, 我们还是离不开 objdump 这个利器。objdump的 -s 参数可以将所有段的内容以十六进制的方式打印出来, -d 参数可以将所有包含指令的段反汇编。

objdump -s -d SimpleSection.o

SimpleSection.o:     文件格式 elf64-x86-64

Contents of section .text:
 0000 f30f1efa 554889e5 4883ec10 897dfc8b  ....UH..H....}..
 0010 45fc89c6 488d3d00 000000b8 00000000  E...H.=.........
 0020 e8000000 0090c9c3 f30f1efa 554889e5  ............UH..
 0030 4883ec10 c745f801 0000008b 15000000  H....E..........
 0040 008b0500 00000001 c28b45f8 01c28b45  ..........E....E
 0050 fc01d089 c7e80000 00008b45 f8c9c3    ...........E... 

"Contents of section .text"就是 .text 的数据以十六进制方式打印出来的内容, 总共 0x5b 字节. 最左面一列是偏移量, 中间 4 列是十六进制内容, 最右面一列是 .text 
段的 ASCII 码形式。对照下面的反汇编结果, 可以很明显地看到 .text 段里所包含的正是 SimpleSection.c 里两个函数 func1() 和 main() 的指令。

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


// !! 3.3.2　数据段和只读数据段

.data 段保存的是那些已经初始化了的全局静态变量和局部静态变量。

前面的 SimpleSection.c 代码里面一共有两个这样的变量, 分别是 global_init_variable 与 static_var。这两个变量每个 4 个字节, 一共刚好 8 个字节, 所以 .data 这个段
的大小为 8 个字节。

SimpleSection.c 里面我们在调用  printf 的时候, 用到了一个字符串常量 "%d\n", 它是一种只读数据, 所以它被放到了 ".rodata" 段, 我们可以从输出结果看到 .rodata 这个
段的 4 个字节刚好是这个字符串常量的 ASCII 字节序, 最后以 \0 结尾。

'.rodata 段存放的是只读数据, 一般是程序里面的只读变量 (如 const 修饰的变量) 和字符串常量'。

单独设立 .rodata 段有很多好处, 不光是在语义上支持了 C++ 的 const 关键字, 而且操作系统在加载的时候可以将 .rodata 段的属性映射成只读, 这样对于这个段的任何修改操作都会
作为非法操作处理, 保证了程序的安全性。


// !! 3.3.3　BSS段

.bss 段存放的是未初始化的全局变量和局部静态变量, 如上述代码中 global_uninit_var 和 static_var2 就是被存放在 .bss 段, 其实更准确的说法是 .bss 段为它们预留了空间。


// !! 3.3.4　其他段

除了.text、.data、.bss 这 3 个最常用的段之外, ELF 文件也有可能包含其他的段, 用来保存与程序相关的其他信息。












