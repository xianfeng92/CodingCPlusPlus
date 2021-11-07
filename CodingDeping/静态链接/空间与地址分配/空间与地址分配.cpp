
当我们有两个目标文件时， 如何将它们链接起来形成一个可执行文件 ？ 这个过程发生了什么 ？ 这基本上就是链接的核心内容：静态链接

/*a.c*/
extern int shared;
int main() //全局符号
{
    int a = 100;
    swap(&a, &shared);
}

/*b.c*/
int shared = 1;           //全局符号
void swap(int *a, int *b) //全局符号
{
    *a ^= *b ^= *a ^= *b;
}


// !! 空间与地址分配

对于链接器来说，整个链接过程中，它就是将几个输入目标文件加工后合并成一个输出文件。但'链接器如何将各个段合并到输出文件' ？

1. 按序叠加

   一个简单方案就是将输入目标文件按照次序叠加起来， 就是直接将各个目标文件依次合并。 但这样有一个问题，在有很多输入文件的情况下，输出文件将会有很多
   零散的段，这样就是早成内存空间大量的内部碎片，造成空间浪费


2. 相似段合并
   
   一个更加实际的方法是将相同性质的段合并到一起。

　链接两步走:

　　　　Step1.空间与地址分配

　　　　Step2.符号解析与重定位

» objdump -h a.o                                                      

a.o：     文件格式 elf64-x86-64

节：
Idx Name          Size      VMA               LMA               File off  Algn
  0 .text         00000032  0000000000000000  0000000000000000  00000040  2**0
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, CODE
  1 .data         00000000  0000000000000000  0000000000000000  00000072  2**0
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  0000000000000000  0000000000000000  00000072  2**0

 » objdump -h b.o                                                      

b.o：     文件格式 elf64-x86-64

节：
Idx Name          Size      VMA               LMA               File off  Algn
  0 .text         0000004f  0000000000000000  0000000000000000  00000040  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .data         00000004  0000000000000000  0000000000000000  00000090  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000000  0000000000000000  0000000000000000  00000094  2**0


» objdump -h ab                                                       

ab：     文件格式 elf64-x86-64

节：
Idx Name          Size      VMA               LMA               File off  Algn
  0 .note.gnu.property 00000020  00000000004001c8  00000000004001c8  000001c8  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  1 .text         00000081  0000000000401000  0000000000401000  00001000  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  2 .eh_frame     00000058  0000000000402000  0000000000402000  00002000  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  3 .data         00000004  0000000000404000  0000000000404000  00003000  2**2



1. VMA = virtual memory address 即虚拟地址, LMA = Load memory Address 加载地址 正常情况下两者应该是一样的
   目标文件 b.o 和 a.o 所有段的 VMA 为 0 因为虚拟空间还没有被分配，所以默认值都是 0 ，等到链接后 ab 的 .text 段被分配到了
   0000000000401000，大小为 81 字节， .data 段被分配到了 0000000000404000， 大小为 4 字节


2.符号地址的确定

  当段地址如：.text 确定以后，链接器开始计算各个符号的虚拟地址。因为各个符号在段内的相对位置是固定的，所以这个时候 "main" 的地址已经确定了。
  只不过链接器需要给每个符号加上一个偏移量，使它们能够调整到正确的虚拟地址。