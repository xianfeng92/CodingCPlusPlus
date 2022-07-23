// !! 13.3　C++ 运行库实现

现在 Mini CRT 已经能够支持最基本的 C 语言程序运行了。C++ 作为兼容 C 语言的扩展语言, 它的运行库的实现其实并不复杂, 在这一章中将介绍如何为 Mini CRT 添加对 C++
语言的一些常用的操作支持。

'通常 C++ 的运行库都是独立于 C 语言运行库的, 比如 Linux 下 C 语言运行库为 libc.so/libc.a, 而 C++ 运行库为(libstdc++.so/libstdc++.a)';

一般这些 C++ 的运行库都是依赖于 C 运行库的, 它们仅包含对 C++ 的一些特性的支持, 比如 new/delete、STL、异常处理、流(stream)等。但是它们并不包含诸如入口函数、堆管理、
基本文件操作等这些特性, 而这些也是 C++ 运行库所必需的, '比如 C++ 的流和文件操作依赖于 C 运行库的基本文件操作, 所以它必须依赖于 C 运行库'。

当然, 要完整实现一个 C++ 的运行库是很费事的一件事, C++ 标准模板库 STL 包含了诸如流、容器、算法、字符串等，规模较为庞大。


出于演示的目的, 我们将对 C++ 的标准库进行简化, 最终目标是实现一个能够成功运行如下 C++ 程序代码的运行库:


#include <iostream>
#include <string>

using namespace std;

int main(){
    string * msg = new string("Hello, world!");
    cout << *msg << endl;
    delete msg;
    return 0;
}

上面这段程序看似简单, 实际上它用到了 C++ 运行库的诸多功能, 我们将所用到的特性列举如下:

1. string 类的实现

2. stream 类的实现, 包括操纵符 (Manipulator)  endl

3. 全局对象构造和析构 cout

4. new/delete


在实现 Mini CRT 对 C++ 的支持时, 我们遵循如下原则:

1. HelloWorld 程序无须用到的功能就不实现, 比如异常

2. 尽量简化设计, 尽量符合 C++ 标准库的规范

3. 对于可以直接在头文件实现的模块尽量在头文件中实现, 以免诸多的类、函数的声明和定义造成代码量膨胀, 不便于演示

4. 与前面的 Mini CRT 实现一样, 运行库代码要做到可以在 Windows 和 Linux 上同时运行, 因此对于平台相关部分要使用条件编译分别实现。虽然 C++ 运行库几乎没有与系统相关的
   部分(全局构造和析构除外), 'C 运行库已经将大部分系统相关部分封装成 C 标准库接口, C++ 运行库只须要调用这些接口即可'。

5. '另外值得一提的是, 模板是不需要运行库支持的, 它的实现依赖于编译器和链接器, 对运行库基本上没有要求'


// !! 13.3.1　new 与 delete

首先从比较简单的模块入手, 全局 new/delete 操作的实现应该是最简单的部分。我们知道, new 操作的功能是从堆上分配一块对象大小的空间, 然后运行对象的初始化函数将这个空间地址
返回; 而 delete 则是与 new 相反的操作, 它首先运行对象的析构函数, 然后释放堆空间。


那么 new 和 delete 究竟在 C++ 中是一个什么样的地位呢? 它们是编译器内置的操作吗? 它们跟运行库有什么关系呢? 为了解释这些问题, 首先来看一小段代码:

class C{

};

int main(int argc, char* argv[]){
    C* c = new C();
    return 0;
}

假如用 GCC 编译这段代码并且反汇编, 将会看到 new 操作的实现:

>  gcc -c hello.cpp 
>  objdump -dr hello.o 

hello.o:     文件格式 elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	48 83 ec 20          	sub    $0x20,%rsp
   c:	89 7d ec             	mov    %edi,-0x14(%rbp)
   f:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
  13:	bf 01 00 00 00       	mov    $0x1,%edi
  18:	e8 00 00 00 00       	callq  1d <main+0x1d>
			19: R_X86_64_PLT32	_Znwm-0x4
  1d:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  21:	b8 00 00 00 00       	mov    $0x0,%eax
  26:	c9                   	leaveq 
  27:	c3                   	retq   


可以看到, new 操作的实现实际上是调用了一个叫做 _Znwm 的函数, 如果用 c++filt 将这个符号反修饰(Demangle), 可以看到它的真面目:

> c++filt _Znwm
operator new(unsigned long)


可以看到 _Znwm 实际上是一个叫做 operator new 的函数, 这也是我们在 C++ 中熟悉的操作符函数。在 C++ 中, 操作符实际上是一种特殊的函数, 叫做操作符函数, 一般 new 
操作符函数被定义为:

void* operator new(unsigned long size);

除了 new、delete 这样的操作符以外, +、-、*、% 等都可以被认为是操作符, 这些操作符都有相对应的操作符函数。

对于 operator new 函数来说, 它的参数 size 是指须要申请的空间大小, 一般是指 new 对象的大小, 而返回值是申请的堆地址。delete 操作符函数的参数是对象的地址, 它没有返回
值。

于是 new/delete 的实现变得尤为简单, 它们的实现源代码如清单 13-8 所示。

extern "C" void malloc(unsigned int);
extern "C" void free(void *);

void operator new(unsigned int size) {
    return malloc(size);
}

void delete(void *ptr) {
    free(ptr);
}

void* operator new[](unsigned int size) {
    return malloc(size);
}

void delete[](void *ptr) {
    free(ptr);
}

在上面代码中除了 new/delete 之外, 我们还看到了 new[] 和 delete[], 它们分别是用来申请和释放对象数组的, 在这里一并予以实现。

另外除了申请和释放堆空间之外, 没有看到任何对象构造和析构的调用, 其实对象的构造和析构是在 new/delete 之前/之后由编译器负责产生相应的代码进行调用的, new/delete 仅仅
负责堆空间的申请和释放, 不负责构造和析构。

另外值得一提的是, 在使用真实的 C++ 运行库时, 也可以使用上面这段代码自己实现 new/delete, 这样就会将原先 C++ 运行库的 new/delete 覆盖, 使得有机会在 new/delete 时记
录对象的空间分配和释放, 可以实现一些特殊的功能, 比如检查程序是否有内存泄露。这种做法往往被称为全局 new/delete 操作符重载 (Global new/delete operator overloading)。

除了重载全局 new/delete 操作符之外, 也可以重载某个类的 new/delete, 这样可以实现一些特殊的需求, 比如指定对象申请地址 (Replacement new)或者使用自己实现的堆算法对某
个对象的申请/释放进行优化, 从而提高程序的性能等


// !! 13.3.2　C++ 全局构造与析构

C++ 全局构造与析构的实现是有些特殊的, 它与编译器、链接器的关系比较紧密。它们的实现是依赖于编译器、链接器和运行库三者共同的支持和协作的。

构造函数主要实现的是依靠特殊的段合并后形成构造函数数组, 而析构则依赖于 atexit() 函数。

对于 GCC 来说, 须要定义 .ctor 段的起始部分和结束部分, 然后定义两个函数指针分别指向它们。真正的构造部分则只要由一个循环将这两个函数指针指向的所有函数都调用一遍即可。

typedef void(*init_func)(void);

#ifdef WIN32
#pragma section(".CRT$XCA",long,read)
#pragma section(".CRT$XCZ",long,read)
__declspec(allocate(".CRT$XCA")) init_func ctors_begin[] = { 0 };
__declspec(allocate(".CRT$XCZ")) init_func ctors_end[] = { 0 };

extern "C" void do_global_ctors() {
    init_func* p = ctors_begin;
    while (p < ctors_end) {
        if(*p != 0) {
            **(P)();
        }
        ++p;
    }
}

#else

void run_hooks();
extern "C" void do_global_ctors() {
    run_hooks();
}

#endif

在 .ctors.cpp 中包含了 Windows 的全局构造的所有实现代码, 但 Linux 的全局构造还需要 crtbegin 和 crtend 两个部分。


这两个文件内容如清单 13-10、清单 13-11 所示。

#ifndef WIN32
typedef void(*ctor_func)(void);

ctor_func ctors_begin[1] __attribute__((section(".ctor"))) = { (ctor_func) - 1 }; 

void run_hooks() {
    const ctor_func* list = ctors_begin;
     while ((int)*++list != -1) {
        (*list)();
     }
}
#endif


#ifndef WIN32
typedef void (*ctor_func)(void);
ctor_func crt_end[1] __attribute__ ((section(".ctors"))) = { (ctor_func) -1};
#endif


// !! 13.3.3　atexit 实现

atexit() 的用法十分简单, 即由它注册的函数会在进程退出前, 在 exit() 函数中被调用。atexit() 和 exit() 函数实际上并不属于 C++ 运行库的一部分, 它们是 C 语言运行库的
一部分。在前面实现 Mini CRT 时我们在 exit() 函数的实现中预留了对 atexit() 的支持。

本来可以不实现 atexit() 的, 毕竟它不是非常重要的 CRT 函数, 但是在这里不得不实现 atexit 的原因是: 所有全局对象的析构函数——不管是 Linux 还是 Windows——都是通过 
atexit 或其类似函数来注册的, 以达到在程序退出时执行的目的。'实现它的基本思路也很简单, 就是使用一个链表把所有注册的函数存储起来, 到 exit() 时将链表遍历一遍, 执行其中所
有的回调函数', Windows 版的 atexit 的确可以按照这个思路实现。

Linux 版的 atexit 要复杂一些, 导致这个的问题的原因是 GCC 实现全局对象的析构不是调用的 atexit, 而是调用的 __cxa_atexit。

这个函数在前面的全局构造和析构中也碰到过, 它不是 C 语言标准库函数, 它是 GCC 实现的一部分。为了兼容 GCC, Mini CRT 不得不实现它。它的定义与 atexit() 有所不同的是, 
__cxa_atexit 所接受的参数类型和 atexit 不同:

typedef void(*cxa_func_t)(void*);
typedef void(*atexit_func_t)(void*);
int __cxa_atexit(cxa_func_t func, void* arg, void*);
int atexit(atexit_func_t func);

__cxa_atexit 所接受的函数指针必须有一个 void* 型指针作为参数, 并且调用 __cxa_atexit 的时候, 这个参数 (void* arg) 也要随着记录下来, 等到要执行的时候再传递进去。
也就是说, __cxa_atexit() 注册的回调函数是带一个参数的, 我们必须把这个参数也记下来。__cxa_atexit 的最后一个参数可以忽略, 在这里不会用到。


于是在设计链表时要考虑到这一点, 链表的节点必须能够区分是否是 atexit() 函数 __cxa_atexit() 注册的函数, 如果是 __cxa_atexit() 注册的函数, 还要把回调函数的参数保存
下来。我们定义链表节点的结构如下:

typedef struct _func_node {
    atexit_func_t func;
    void* arg;
    int is_cxa;
    struct _func_node* next;
} func_node;


其中 is_cxa 成员如果不为 0, 则表示这个节点是由 __cxa_atexit() 注册的回调函数, arg 成员表示相应的参数。atexit 的实现代码如清单 13-12 所示。

#include "minicrt.h"

typedef struct _func_node {
    atexit_func_t func;
    void* arg;
    int is_cxa;
    struct _func_node* next;
};


static _func_node* atexit_list = 0;

int register_exit(atexit_func_t func, void* arg, int is_cxa) {
    func_node* node;
    if(!func) return 0;

    node = (func_node*)malloc(sizeof(func_node));

    if(!node) return 0;

    node->func = func;
    node->arg = arg;
    node->is_cxa = is_cxa;
    node->next = atexit_list;
    atexit_list = node;
    return 0;
}

#ifndef WIN32

typedef void(*cxa_func_t)(void*);

int __cxa_atexit(cxa_func_t func, void* arg, void* unused) {
     return register_atexit((atexit_func_t)func, arg, 1);
}

#endif

int atexit(atexit_func_t func){

    return register_atexit(func, 0, 0);
}


void mini_crt_call_exit_routine() {
    func_node* p = atexit_list;
    for(; p != 0; p = p->next) {
        #ifdef WIN32
        p->func();
        #else
        if(p->is_cxa){
             ((cxa_func_t)p->func)(p->arg);
        }else {
             p->func();
        }
        #endif
        free(p);
    }
     atexit_list = 0;
}


值得一提的是, 在注册函数时, 被注册的函数是插入到列表头部的, 而最后 mini_crt_call_exit_routine() 是从头部开始遍历的, 于是由 atexit() 或 __cxa_atexit() 注册的
函数是按照先注册后调用的顺序, 这符合析构函数的规则, 因为先构造的全局对象应该后析构。



// !! 13.3.4　入口函数修改

