
// !! gcc -c 编译出目标文件

gcc -c SimpleSection.c  编译输出 SimpleSection.o 目标文件（ELF格式）

// !! objdump 可以用来查看 SimpleSection.o 目标文件的结构和内容

/Stan/xforg/CodingCPlusPlus/GCCDeping(main*) » objdump -h SimpleSection.o 

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
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, DATA
------------------------------------------------------------------


// !! linux 下 size 命令可以用来查看 ELF 文件的代码段、数据段和 BSS 段的长度

~/Stan/xforg/CodingCPlusPlus/GCCDeping(main*) » size SimpleSection.o                                                                                         1 ↵ parallels@xforg
   text	   data	    bss	    dec	    hex	filename
    219	      8	      4	    231	     e7	SimpleSection.o


// !! objdump -s -d SimpleSection.o 

objdump -s -d SimpleSection.o 会将 SimpleSection.o 中关键的段信息显示出来，而省略其它的辅助性段，比如：

符号表、字符串表、段名字符号表、重定位表等

/Stan/xforg/CodingCPlusPlus/GCCDeping(main*) » objdump -s -d SimpleSection.o

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


// !! 使用 readelf 工具来查看 ELF 文件的段，它显示的结果才是真正的段表结构

readelf -S SimpleSection.o 

/Stan/xforg/CodingCPlusPlus/GCCDeping(main*) » readelf -S SimpleSection.o 
There are 14 section headers, starting at offset 0x4a0:

节头：
  [号] 名称              类型             地址              偏移量
       大小              全体大小          旗标   链接   信息   对齐
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         0000000000000000  00000040
       000000000000005f  0000000000000000  AX       0     0     1
  [ 2] .rela.text        RELA             0000000000000000  00000380
       0000000000000078  0000000000000018   I      11     1     8
  [ 3] .data             PROGBITS         0000000000000000  000000a0
       0000000000000008  0000000000000000  WA       0     0     4
  [ 4] .bss              NOBITS           0000000000000000  000000a8
       0000000000000004  0000000000000000  WA       0     0     4
  [ 5] .rodata           PROGBITS         0000000000000000  000000a8
       0000000000000004  0000000000000000   A       0     0     1
  [ 6] .comment          PROGBITS         0000000000000000  000000ac
       000000000000002b  0000000000000001  MS       0     0     1
  [ 7] .note.GNU-stack   PROGBITS         0000000000000000  000000d7
       0000000000000000  0000000000000000           0     0     1
  [ 8] .note.gnu.propert NOTE             0000000000000000  000000d8
       0000000000000020  0000000000000000   A       0     0     8
  [ 9] .eh_frame         PROGBITS         0000000000000000  000000f8
       0000000000000058  0000000000000000   A       0     0     8
  [10] .rela.eh_frame    RELA             0000000000000000  000003f8
       0000000000000030  0000000000000018   I      11     9     8
  [11] .symtab           SYMTAB           0000000000000000  00000150
       00000000000001b0  0000000000000018          12    12     8
  [12] .strtab           STRTAB           0000000000000000  00000300
       000000000000007c  0000000000000000           0     0     1
  [13] .shstrtab         STRTAB           0000000000000000  00000428
       0000000000000074  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  l (large), p (processor specific)
--------------------------------------------



// !! 读取 ELF 头文件信息

/Stan/xforg/CodingCPlusPlus/GCCDeping(main*) » readelf -h SimpleSection.o
ELF 头：
  Magic：   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  类别:                              ELF64
  数据:                              2 补码，小端序 (little endian)
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI 版本:                          0
  类型:                              REL (可重定位文件)
  系统架构:                          Advanced Micro Devices X86-64
  版本:                              0x1
  入口点地址：               0x0
  程序头起点：          0 (bytes into file)
  Start of section headers:          1184 (bytes into file)
  标志：             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           0 (bytes)
  Number of program headers:         0
  Size of section headers:           64 (bytes)
  Number of section headers:         14
  Section header string table index: 13



/Stan/xforg/linux_asr_1.0_forModernC++/build(devel2*) » readelf -h linuxasr 
ELF 头：
  Magic：   7f 45 4c 46 02 01 01 03 00 00 00 00 00 00 00 00 
  类别:                              ELF64
  数据:                              2 补码，小端序 (little endian)
  Version:                           1 (current)
  OS/ABI:                            UNIX - GNU
  ABI 版本:                          0
  类型:                              EXEC (可执行文件)
  系统架构:                          AArch64
  版本:                              0x1
  入口点地址：               0x42d2a8
  程序头起点：          64 (bytes into file)
  Start of section headers:          677048 (bytes into file)
  标志：             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         9
  Size of section headers:           64 (bytes)
  Number of section headers:         39
  Section header string table index: 36
--------------------------------------------------------------------------------
~/Stan/xforg/linux_asr_1.0_forModernC++/build(devel2*) »        parallels@xforg



~/Stan/xforg/linux_asr_1.0_forModernC++/eu/third_party/lib(devel2*) » readelf -h libjsoncpp.so.1.9.4 
ELF 头：
  Magic：   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  类别:                              ELF64
  数据:                              2 补码，小端序 (little endian)
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI 版本:                          0
  类型:                              DYN (共享目标文件)
  系统架构:                          AArch64
  版本:                              0x1
  入口点地址：               0xe730
  程序头起点：          64 (bytes into file)
  Start of section headers:          291528 (bytes into file)
  标志：             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         6
  Size of section headers:           64 (bytes)
  Number of section headers:         35
  Section header string table index: 32



