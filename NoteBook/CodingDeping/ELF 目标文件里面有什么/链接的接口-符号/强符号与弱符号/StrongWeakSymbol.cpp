// !! 强符号与弱符号

'多个目标文件含有相同名字的全局符号定义', 那么这些目标文件链接(Linking)的时候将会出现符号重复定义的错误。 我们在 main.c 和 other.c 都定义了一个全
局整形变量 global，并将它们都初始化，那么链接器将 main.c 的目标文件 和 other.c 的目标文件进行链接时会报错。

» gcc main.c other.c                                        
/usr/bin/ld: /tmp/cc0yf8GE.o:(.data+0x0): multiple definition of `a'; 
/tmp/cc04nLHC.o:(.data+0x0): first defined here
collect2: error: ld returned 1 exit status

对于 C/C++ 语言来说，编译器默认函数和'初始化了的全局变量称为强符号（Strong Symbol）'，'未初始化的全局变量为弱符号（Weak Symbol）'

__attribute__((weak)) 是 gcc 提供的将强符号转为弱符号的关键字

// main1.c
extern int ext;  
int weak1;  
int strong = 1;  
int __attribute__((weak)) weak2 = 2;  
  
int main()  
{
        printf("%d,%d,%d\n", weak1,strong,weak2);
        return 0;  
}

weak1 和 weak2 为弱符号； main 和 strong 为强符号； ext 即非强符号也非弱符号，因为它是一个外部变量的引用。

// !! 针对强弱符号的概念，链接器会按照如下规则处理与选择多次定义的全局符号

1. 不允许强符号被多次定义(即：不同目标文件中不能有同名的强符号)； 如果有多个强符号定义，则链接器报符号重复定义错误

2. 如果一个符号在某个目标文件中为强符号，在其它目标文件中为弱符号，那么选择强符号

3. 如果一个符号在所以的目标文件中都是弱引用，那么现在其中占空间最大的一个。比如目标文件 A 中定义全局变量 global 为 int 型，
   目标文件 B 中定义全局变量 global 为 double 型，那么目标 A 和 B 链接后，符号 global 占 8 个字节


// !! 强引用与弱引用

目前我们所看到的'对外部目标文件的符号引用'在目标文件被最终链接成可执行文件时，它们需要被正确决议，如果没有找到该符号的定义， 链接器就会报符号未定义的错误，
这种被称为强引用 （Strong Reference）； 与之相对应的还有一种弱引用 （Weak Reference）， 在处理弱引用时，如果该符号有定义，则链接器将该符号的引用决议。
如果该符号未被定义，则链接器对其该引用不报错。

链接器处理强引用和弱引用的过程几乎一样，只是对于未定义的弱引用，链接器不认为它是一个错误。一般对于未定义的弱引用, 链接器默认其为 0，或者是一个特殊的值，以便于程
序代码能够识别。


// !! 弱引用和弱符号主要用于库的链接过程

在 GCC 中，使用 __attribute__((weak_ref)) 这个扩展关键字来声明对一个外部函数的引用为弱引用


// main2.c
#include <stdio.h>

__attribute__((weakref)) void foo();

int main()
{
    foo();
    printf("call foo()\n");
}

// main2.c
#include <stdio.h>

__attribute__((weakref)) void foo();

int main()
{
    if (foo)
    {
        foo();
        printf("call foo()\n");
    }
}



这种弱符号和弱引用对于库来说十分有用，比如库中定义的弱符号可以用户定义的强符号覆盖，从而使得程序可以使用自定义版本的函数； 或者程序可以对某些扩展功能某块
的引用定义为弱引用，当我们将扩展模块与程序链接在一起时，功能模块就可以正常使用; 如果我们去掉一些模块功能，那么程序也可以正常链接，只是缺少相应的功能。


在 Linux 程序的设计中, 如果一个程序被设计成可以支持单线程或多线程的模式，就可以通过弱引用的方法来判断当前的程序是链接到了单线程的Glibc库还是多线程的Glibc
库（是否在编译时有 -lpthread 选项）, 从而执行单线程版本的程序或多线程版本的程序。我们可以在程序中定义一个 pthread_create 函数的弱引用， 然后程序在运行时动
态判断是否链接到 pthread 库从而决定执行多线程版本还是单线程版本


#include <stdio.h>
#include <pthread.h>

// 定义一个 pthread_create 函数的弱引用，程序在运行时动态判断是否链接到 pthread 库从而决定执行多线程版本还是单线程版本

int pthread_create( pthread_t*, const pthread_attr_t*, 
void* (*)(void*), void*) __attribute__ ((weakref));
int main()
{
    if(pthread_create) 
    {
            printf("This is multi-thread version!\n");
            // run the multi-thread version
            // main_multi_thread()
    } 
    else 
    {
            printf("This is single-thread version!\n");   
            // run the single-thread version
            // main_single_thread()
    }
}

 » gcc pthread.c  -o pt                                      
» ./pt                                                       
This is multi-thread version!
» gcc pthread.c  -lpthread -o pt                                                                          
 » ./pt                                                    
This is multi-thread version!

// !! 最新版本 GCC 无需指定，自动帮忙链接 lpthread ？？？？？？？











