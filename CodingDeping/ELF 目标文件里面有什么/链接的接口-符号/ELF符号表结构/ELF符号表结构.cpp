
// !! ELF 符号表结构

// !! 使用 nm 查看 ELF 文件的符号表

 » nm SimpleSection.o 
0000000000000000 T func1
0000000000000000 D global_init_var
                 U _GLOBAL_OFFSET_TABLE_
0000000000000004 C global_uninit_var
0000000000000028 T main
                 U printf
0000000000000004 d static_var.1919
0000000000000000 b static_var2.1920
--------------------------------------------------------------------------------


// !! 使用 readelf 查看 ELF 文件的符号表信息

 » readelf -s SimpleSection.o 

Symbol table '.symtab' contains 18 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS SimpleSection.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 
     6: 0000000000000004     4 OBJECT  LOCAL  DEFAULT    3 static_var.1919
     7: 0000000000000000     4 OBJECT  LOCAL  DEFAULT    4 static_var2.1920
     8: 0000000000000000     0 SECTION LOCAL  DEFAULT    7 
     9: 0000000000000000     0 SECTION LOCAL  DEFAULT    8 
    10: 0000000000000000     0 SECTION LOCAL  DEFAULT    9 
    11: 0000000000000000     0 SECTION LOCAL  DEFAULT    6 
    12: 0000000000000000     4 OBJECT  GLOBAL DEFAULT    3 global_init_var
    13: 0000000000000004     4 OBJECT  GLOBAL DEFAULT  COM global_uninit_var
    14: 0000000000000000    40 FUNC    GLOBAL DEFAULT    1 func1
    15: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _GLOBAL_OFFSET_TABLE_
    16: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND printf
    17: 0000000000000028    55 FUNC    GLOBAL DEFAULT    1 main           

1. ELF 文件中符号表通常是文件中的一个段（'.symtab'）

2. Bind 符号绑定类型

   LOCAL 局部符号，对于目标文件外部不可见到； GLOBAL 全局符号，外部可见

3. Type 为符号类型

   OBJECT：该符号是个数据对象，比如变量、数组等； FUNC：该符号是函数或者其他可执行代码； FILE： 该符号表示文件名，一般都是该目标文件所对应的源文件名
   （SimpleSection.c）； 

4. NOTYPE 未知类型符合

5. SECTION 该符号表示一个段, ndx 为该符号所在的段

   如果符号定义在本目标文件中，那么这个成员表示符号所在的段在段表中的下标； 
   如果符号不是定义在本目标文件中： UND 表示未定义 ; COM 表示该符号是一个 COMMON 块 类型的符号

6. Value 表示符号的值
   
   // !! 每一个符号都以一个对应的值，如果这个符号是一个变量或者函数，那么符号的值就是该变量或函数的地址。

   特别地，在可执行文件中，符号的值表示符号的虚拟地址，这个虚拟地址对于动态链接器来说十分有用

7. Size 为符号大小
   
   特别地，对于 main 和 func1 是定义在 SimpleSection.c 中的函数，属于指令，位于 .text 段中。其 Size 表示函数指令所占的字节数，Value 是函数相对于代
   码段起始位置的偏移量。

8. static_var2.1920 和 static_var2.1920 两个静态变量，只对编译单元内部可见