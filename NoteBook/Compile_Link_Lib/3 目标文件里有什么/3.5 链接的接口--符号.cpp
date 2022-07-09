// !! 3.5　链接的接口——符号

链接过程的本质就是要把多个不同的目标文件之间相互"粘"到一起, 或者说像玩具积木一样, 可以拼装形成一个整体。为了使不同目标文件之间能够相互粘合, 这些目标文件之间必须有固
定的规则才行, 就像积木模块必须有凹凸部分才能够拼合。

'在链接中,目标文件之间相互拼合实际上是目标文件之间对地址的引用,即对函数和变量的地址的引用'。比如目标文件 B 要用到了目标文件 A 中的函数 foo, 那么我们就称目标文件 A 
定义(Define) 了函数 foo, 称目标文件 B 引用( Reference) 了目标文件 A 中的函数 foo。

'每个函数或变量都有自己独特的名字,才能避免链接过程中不同变量和函数之间的混淆'。在链接中, 我们将函数和变量统称为符号(Symbol), 函数名或变量名就是符号名(Symbol Name)。

我们可以将符号看作是链接中的粘合剂, 整个链接过程正是基于符号才能够正确完成。'链接过程中很关键的一部分就是符号的管理,每一个目标文件都会有一个相应的符号表(Symbol Table),
这个表里面记录了目标文件中所用到的所有符号'。'每个定义的符号有一个对应的值, 叫做符号值 (Symbol Value), 对于变量和函数来说, 符号值就是它们的地址'。

除了函数和变量之外, 还存在其他几种不常用到的符号。

我们将符号表中所有的符号进行分类,它们有可能是下面这些类型中的一种:

• '定义在本目标文件的全局符号, 可以被其他目标文件引用'。比如 SimpleSection.o 里面的 func1、main 和 global_init_var

• '在本目标文件中引用的全局符号, 却没有定义在本目标文件, 这一般叫做外部符号(External Symbol)', 也就是我们前面所讲的符号引用。比如 SimpleSection.o 里面的 printf

•  段名,这种符号往往由编译器产生, 它的值就是该段的起始地址。比如 SimpleSection.o 里面的 .text、.data等

• '局部符号, 这类符号只在编译单元内部可见'。比如 Simple-Section.o 里面的 static_var 和 static_var2。'调试器可以使用这些符号来分析程序或崩溃时的核心转储文件'。这些
   局部符号对于链接过程没有作用, 链接器往往也忽略它们。

• 行号信息, 即目标文件指令与源代码中代码行的对应关系, 它也是可选的

对于我们来说, 最值得关注的就是全局符号, 即上面分类中的第一类和第二类。因为'链接过程只关心全局符号的相互“粘合”', 局部符号、段名、行号等都是次要的, 它们对于其他目标文件来
说是"不可见"的, 在链接过程中也是无关紧要的。

我们可以使用很多工具来查看 ELF 文件的符号表, 比如 readelf、objdump、nm 等, 比如使用 nm 来查看 SimpleSection.o 的符号结果如下:

nm SimpleSection.o 

0000000000000000 T func1
0000000000000000 D global_init_var
                 U _GLOBAL_OFFSET_TABLE_
0000000000000004 C global_uninit_var
0000000000000028 T main
                 U printf
0000000000000004 d static_var.1919
0000000000000000 b static_var2.1920


// !! 3.5.1　ELF 符号表结构

'ELF 文件中的符号表往往是文件中的一个段, 段名一般叫 .symtab'。

readelf -s SimpleSection.o

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

第一列 Num 表示符号表数组的下标, 从 0 开始, 共 15 个符号; 第二列 Value 就是符号值, 即 st_value; 第三列 Size 为符号大小, 即 st_size; 第四列和第五列分别为符号类
型和绑定信息, 即对应 st_info 的低 4 位和高 28 位; 第七列 Ndx 即 st_shndx, 表示该符号所属的段; 当然最后一列也最明显, 即符号名称。


// !! 3.5.2　特殊符号

'当我们使用 ld 作为链接器来链接生产可执行文件时, 它会为我们定义很多特殊的符号, 这些符号并没有在你的程序中定义, 但是你可以直接声明并且引用它, 我们称之为特殊符号'。

几个很具有代表性的特殊符号如下:

•__executable_start, 该符号为程序起始地址, 注意, 不是入口地址, 是程序的最开始的地址

• __etext 或 _etext 或 etext, 该符号为代码段结束地址, 即代码段最末尾的地址

• _end 或 end, 该符号为程序结束地址

我们可以在程序中直接使用这些符号:

> gcc SpecialSymbol.c
> ./a.out 

Executable Start BC0000
Text End BC1265 BC1265 BC1265
Data End BC4010 BC4010
Executable End BC4018 BC4018


// !! 3.5.3　符号修饰与函数签名

约在 20 世纪 70 年代以前, 编译器编译源代码产生目标文件时, 符号名与相应的变量和函数的名字是一样的。比如一个汇编源代码里面包含了一个函数 foo, 那么汇编器将它编译成目标文
件以后, foo 在目标文件中的相对应的符号名也是 foo。

'为了防止类似的符号名冲突, UNIX 下的 C 语言就规定, C 语言源代码文件中的所有全局的变量和函数经过编译以后, 相对应的符号名前加上下划线 _'。

这种简单而原始的方法的确能够暂时减少多种语言目标文件之间的符号冲突的概率, 但还是没有从根本上解决符号冲突的问题。

比如同一种语言编写的目标文件还有可能会产生符号冲突, 当程序很大时, 不同的模块由多个部门开发, 它们之间的命名规范如果不严格, 则有可能导致冲突。'于是像 C++ 这样的后来设计的
语言开始考虑到了这个问题, 增加了名称空间 (Namespace) 的方法来解决多模块的符号冲突问题'。

GCC 编译器也可以通过参数选项 -fleading-underscore 或 -fno-leading-underscore 来打开和关闭是否在 C 语言符号前加上下划线。


// !! C++ 符号修饰

众所周知, 强大而又复杂的 C++ 拥有类、继承、虚机制、重载、名称空间等这些特性, 它们使得符号管理更为复杂。

最简单的例子, 两个相同名字的函数 func(int) 和 func(double), 尽管函数名相同, 但是参数列表不同, 这是 C++ 里面函数重载的最简单的一种情况, 那么编译器和链接器在链接过程
中如何区分这两个函数呢?

为了支持 C++ 这些复杂的特性, 人们发明了符号修饰(Name Decoration)或符号改编(Name Mangling)的机制, 下面我们来看看 C++ 的符号修饰机制。


首先出现的一个问题是 C++ 允许多个不同参数类型的函数拥有一样的名字, 就是所谓的函数重载; 另外 C++ 还在语言级别支持名称空间, 即允许在不同的名称空间有多个同样名字的符号。


int func(int);
float func(float);

class C{
    int func(int);
    class C2{
        int func(int);
    };
};

namespace N {
    int func(int);
    class C {
        int func(int);
    };
}

这段代码中有 6 个同名函数叫 func, 只不过它们的返回类型和参数及所在的名称空间不同。我们引入一个术语叫做'函数签名 (Function Signature),函数签名包含了一个函数的信息,
包括函数名、它的参数类型、它所在的类和名称空间及其他信息'。

在编译器及链接器处理符号时, 它们使用某种名称修饰的方法, 使得每个函数签名对应一个修饰后名称(Decorated Name)。'C++ 编译器和链接器都使用符号来识别和处理函数和变量', 所以
对于不同函数签名的函数, 即使函数名相同, 编译器和链接器都认为它们是不同的函数。

由于不同的编译器采用不同的名字修饰方法, 必然会导致由不同编译器编译产生的目标文件无法正常相互链接, 这是导致不同编译器之间不能互操作的主要原因之一。


// !! 3.5.4 Extern "C"

C++ 为了与 C 兼容, 在符号的管理上, C++ 有一个用来声明或定义一个 C 的符号的 extern "C" 关键字用法:

extern "C" {
    int func1(int);
    int var;
}

'C++ 编译器会将在 extern "C" 的大括号内部的代码当作 C 语言代码处理'。所以很明显, 上面的代码中, C++ 的名称修饰机制将不会起作用。它声明了一个 C 的函数 func, 定义了一
个整形全局变量 var。

如果单独声明某个函数或变量为 C 语言的符号, 那么也可以使用如下格式:

extern "C" int func1(int);
extern "C" int var;

C++ 编译器会在编译 C++ 的程序时默认定义这个宏, 我们可以使用条件宏来判断当前编译单元是不是 C++ 代码。

#ifdef __cplusplus
extern "C" {
#endif

    void *memset(void *, int, size_t);
#ifdef __cplusplus
}
#endif

'如果当前编译单元是 C++ 代码, 那么 memset 会在 extern "C" 里面被声明; 如果是 C 代码, 就直接声明'。上面这段代码中的技巧几乎在所有的系统头文件里面都被用到。


// !! 3.5.5　弱符号与强符号

我们经常在编程中碰到一种情况叫符号重复定义。多个目标文件中含有相同名字全局符号的定义, 那么这些目标文件链接的时候将会出现符号重复定义的错误。

比如我们在目标文件 A 和目标文件 B 都定义了一个全局整形变量 global, 并将它们都初始化, 那么链接器将 A 和 B 进行链接时会报错:

b.o:(.data+0x0): multiple definition of 'global'
a.o:(.data+0x0): first defined here

这种符号的定义可以被称为强符号 (Strong Symbol)。有些符号的定义可以被称为弱符号 (Weak Symbol)。

'对于 C/C++ 语言来说, 编译器默认函数和初始化了的全局变量为强符号, 未初始化的全局变量为弱符号'。

我们也可以通过 GCC 的 __attribute__((weak)) 来定义任何一个强符号为弱符号。

比如我们有下面这段程序:

extern int ext;
int weak;
int strong = 1;

__attribute__((weak))weak2 = 2;

int main() {
    return 0;
}

上面这段程序中,  weak 和 weak2 是弱符号, strong 和 main 是强符号, 而 ext 既非强符号也非弱符号, 因为它是一个外部变量的引用。

针对强弱符号的概念, 链接器就会按如下规则处理与选择被多次定义的全局符号:

• 规则1: 不允许强符号被多次定义(即不同的目标文件中不能有同名的强符号); 如果有多个强符号定义, 则链接器报符号重复定义错误

• 规则2: 如果一个符号在某个目标文件中是强符号, 在其他文件中都是弱符号, 那么选择强符号

• 规则3: 如果一个符号在所有目标文件中都是弱符号, 那么选择其中占用空间最大的一个


// !! 弱引用和强引用

目前我们所看到的对外部目标文件的符号引用在目标文件被最终链接成可执行文件时, 它们须要被正确决议, 如果没有找到该符号的定义, 链接器就会报符号未定义错误, 这种被称为强引
用(Strong Reference)。


在 GCC 中, 我们可以通过使用 __attribute__((weakref)) 这个扩展关键字来声明对一个外部函数的引用为弱引用, 比如下面这段代码:

__attribute__((weakref)) void foo();

int main() {
    foo();
}

我们可以将它编译成一个可执行文件, GCC 并不会报链接错误。但是当我们运行这个可执行文件时, 会发生运行错误。因为当 main 函数试图调用 foo 函数时, foo 函数的地址为 0, 于
是发生了非法地址访问的错误。

一个改进的例子是:

__attribute__(weakref) void foo();

int main() {
    if(foo) foo();
    return 0;
}

'这种弱符号和弱引用对于库来说十分有用, 比如库中定义的弱符号可以被用户定义的强符号所覆盖, 从而使得程序可以使用自定义版本的库函数'; 或者程序可以对某些扩展功能模块的引用定义
为弱引用, 当我们将扩展模块与程序链接在一起时, 功能模块就可以正常使用; 如果我们去掉了某些功能模块, 那么程序也可以正常链接, 只是缺少了相应的功能, 这使得程序的功能更加容易
裁剪和组合。

在 Linux 程序的设计中, 如果一个程序被设计成可以支持单线程或多线程的模式, 就可以通过弱引用的方法来判断当前的程序是链接到了单线程的 Glibc 库还是多线程的 Glibc库(是否在
编译时有 -lpthread 选项), 从而执行单线程版本的程序或多线程版本的程序。

我们可以在程序中定义一个 pthread_create 函数的弱引用, 然后程序在运行时动态判断是否链接到 pthread 库从而决定执行多线程版本还是单线程版本:

#include <stdio.h>
#include <pthread.h>

__attribute__(weak) int pthread_create(pthread_t*, const pthread_attr_t*, void* (*)(void*), void*);

int main() {
    if (pthread_create) {
         printf("This is multi-thread version!\n");
    } else {
         printf("This is single-thread version!\n");
    }
    return 0;
}







