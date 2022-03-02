
// !! 最小的 "Helloworld" 程序

// TinyHelloWorld.c
char * str = "Hello world!\n";
void print(void)
{
    asm("movl $13,%%edx \n"
        "movl %0,%%ecx \n"
        "movl $0,%%ebx \n"
        "movl $4,%%eax \n"
        "int $0x80 \n"
        ::"r"(str):"edx","ecx","ebx");
}
void exit(void)
{
    asm("movl $42,%ebx \n"
        "movl $1, %eax \n"
        "int $0x80 \n");
}
void nomain(void)
{
    print();
    exit();
}


1.  生成目标文件 

gcc -c -fno-builtin TinyHelloWorld.c

» gcc -c -fno-builtin TinyHelloWorld.c  
TinyHelloWorld.c: Assembler messages:
TinyHelloWorld.c:6: 错误： unsupported instruction `mov'

该问题是因为在 64位机器上编译 32 位的汇编码导致的, 解决方法就是加个 -m32 的选项，使 gcc 使用 32 位的 ABI 

gcc选项说明:

a. -c 只编译汇编成目标文件不链接

b. -fno-builtin 关闭gcc内置函数功能
    gcc编译器提供了很多内置函数(Built-in Function)，它会把一些常用的C库函数替换成编译器的内置函数，以达到优化的功能。比如 gcc 会将只有字符串参数的 
    printf 函数替换成 puts ,以节省格式解析的时间'

2. 链接生成可执行文件

» ld -static -e nomain -o TinyHelloWorld TinyHelloWorld.o
ld: i386 architecture of input file `TinyHelloWorld.o' is incompatible with i386:x86-64 output
ld: TinyHelloWorld.o: in function `print':
TinyHelloWorld.c:(.text+0xe): undefined reference to `_GLOBAL_OFFSET_TABLE_'
ld: TinyHelloWorld.o: in function `exit':
TinyHelloWorld.c:(.text+0x3c): undefined reference to `_GLOBAL_OFFSET_TABLE_'
ld: TinyHelloWorld.o: in function `nomain':
TinyHelloWorld.c:(.text+0x5c): undefined reference to `_GLOBAL_OFFSET_TABLE_'
------------------------------------------------------------------------------

原来刚才编译的过程中生成了 elf_i386 格式的目标文件，由于系统是 64bit 的，默认情况下输入文件格式为 elf_x86_64，这就导致了实际输入文件格式与期待的
输入文件格式不匹配'.

 ld -m elf_i386 -static -e nomain -o TinyHelloWorld TinyHelloWorld.o

ld选项说明

----------------------------------------------------------------------------------------------------------------------------

-static 让链接器使用静态链接的方式进行链接

-e 指定程序入口函数

-m 设置输入文件格式

-o 指定输出文件的文件名

 » ./TinyHelloWorld                  
Hello world!
