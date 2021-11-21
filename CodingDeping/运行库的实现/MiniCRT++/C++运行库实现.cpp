// !! C++ 运行库实现

通常 C++ 的运行库都是独立于 C 语言运行库的，'Linux 下 C 语言运行库为 libc.so、libc.a，而 C++ 运行库为 libstdc++.so、libstdc++.a'
一般这些 C++ 的运行库都是依赖于 C 运行库的，它们仅包含对 C++ 的一些特性的支持，比如 new/delete、STL、异常处理、流（stream）等。但是它们并不包含诸
如入口函数、堆管理、基本文件操作等这些特性，而这些也是 C++ 运行库所必需的，比如 C++ 的流和文件操作依赖于 C 运行库的基本文件操作，所以它必须依赖于 C 运
行库。


在实现 Mini CRT 对 C++ 的支持时，遵循如下原则:

1. HelloWorld 程序无须用到的功能就不实现，比如异常

2. 尽量简化设计，尽量符合 C++ 标准库的规范

3. 对于可以直接在头文件实现的模块尽量在头文件中实现，以免诸多的类、函数的声明和定义造成代码量膨胀，不便于演示

4. 支持 Windows 和 Linux。虽然 C++ 运行库几乎没有与系统相关的部分（全局构造和析构除外），C 运行库已经将大部分系统相关部分封装成 C 标准库接口
   C++ 运行库只须要调用这些接口即可

5. 另外值得一提的是: 模板是不需要运行库支持的，它的实现依赖于编译器和链接器，对运行库基本上没有要求

对 C++ 的标准库进行简化，最终目标是实现一个能够成功运行如下C++程序代码的运行库:

// test.cpp
#include "iostream"
#include "string"

using namespace std;

int main(int argc, char* argv[])
{
    string* msg = new string("Hello World");
    cout << *msg << endl;
    delete msg;
    return 0;
}


// !! new 与 delete

C++ 中的操作符函数 operator new，一般被定义为:

void* operator new(unsigned int size);

所以实现 new/delete 就是实现这两个操作符函数, 而这两个函数的主要功能是申请和释放堆空间，这再容易不过了，因为在 Mini CRT 中已经实现了堆空间的申请
和释放函数: malloc 和 free

//new_delete.cpp

extern "C" void* malloc(unsigned int);
extern "C" void free(void*);

void *operator new(unsigned int size)
{
    return malloc(size);
}

void operator delete(void *p)
{
    free(p);
}

void *operator new[](unsigned int size)
{
    return malloc(size);
}

void operator delete[](void *p)
{
    free(p);
}

上面的实现除了申请和释放堆空间之外，没有任何对象构造和析构的调用，'其实对象的构造和析构是在 new/delete 之后和之前由编译器负责产生相应的代码进行调用的'，
new/delete 仅仅负责堆空间的申请和释放，不负责构造和析构。在真实的 C++ 运行库中，new/delete 的实现要比上面的复杂一些，它们除了使用 malloc/free 申
请释放空间之外，还支持 new_handler 在申请失败时给予程序进行补救的机会、还可能会抛出 bad_alloc 异常等，由于 Mini CRT 并不支持异常，所以就省略了这些内容。

// !! C++ 全局构造与析构

C++ 全局构造与析构的实现依赖于编译器、链接器和运行库三者共同的支持和协作。Mini CRT 对于全局对象构造与析构的实现基于“运行库”中描述的 Glibc，本质上没有多大的
区别，仅仅是将它们简化到最简程度，保留本质而去除了一些繁琐的细节。

通过“运行库”可以得知，C++ 全局构造和析构的实现在 Glibc 原理十分相似，'构造函数主要实现的是依靠特殊的段合并后形成构造函数数组，而析构则依赖于 atexit() 函数'

全局构造对于 GCC 来说，须要定义 “.ctor” 段的起始部分和结束部分，然后定义两个函数指针分别指向它们。真正的构造部分则只要由一个循环将这两个函数指针指向的所有函数
都调用一遍即可。而 Glibc 需要两个文件： ctrbegin.o 和 crtend.o，这两个文件在编译时必须位于输入文件的开始和结尾部分，所有在这两个文件之外的输入文件中的 “.ctor” 
段就不会被正确地合并。

// ctors.cpp
typedef void (*init_func)(void);
#ifdef WIN32
#pragma section(".CRT$XCA", long, read)
#pragma section(".CRT$XCZ", long, read)

__declspec(allocate(".CRT$XCA")) init_func ctors_begin[] = {0};
__declspec(allocate(".CRT$XCZ")) init_func ctors_end[] = {0};

extern "C" void do_global_ctors()
{
    init_func *p = ctors_begin;
    while (p < ctors_end)
    {
        if (*p != 0)
            (**p)();
        ++p;
    }
}
#else

void run_hooks();
extern "C" void do_global_ctors()
{
    run_hooks();
}
#endif

Linux 的全局构造还需要 crtbegin 和 crtend 两个部分。

    // !! atexit 实现

    atexit 实现的基本思路很简单，使用一个链表把所有注册的函数存储起来，到
    exit() 时将链表遍历一遍，执行其中所有的回调函数，Windows 版的 atexit 的确可以按照这
    个思路实现。

    Linux 版的 atexit 要复杂一些，因为 GCC 实现全局对象的析构不是调用的 atexit，而是调用的 __cxa_atexit。为了兼容 GCC，Mini CRT 不得不实现它。它的定义与
    atexit() 有所不同的是， __cxa_atexit 所接受的参数类型和 atexit 不同：

typedef void (*cxa_func_t)(void *);
typedef void (*atexit_func_t)(void);
int __cxa_atexit(cxa_func_t func, void *arg, void *);
int atexit(atexit_func_t func);



// !! 入口函数修改

由于增加了全局构造和析构的支持，那么需要对 Mini CRT 的入口函数和 exit() 函数进行修改，把对 do_global_ctors() 和 mini_crt_call_exit_routine() 的调用加入
到 entry() 和 exit() 函数中去。


// !! stream 与 string

C++ helloWorld 程序里面一般都会用到 cout 和 string ，以展示 C++ 的特性，'流和字符串是 C++ STL 的最基本的两个部分', 在有了流和字符串之后，Mini CRT 将最终
宣告完成，可以考虑将它重命名为 Mini CRT++。


string 和 stream 的实现将遵循下列原则:

1. 不支持模板定制，即这两个类仅支持char字符串类型，不支持自定义分配器等，没有 basic_string 模板类

2. 流对象仅实现 ofstream，且没有继承体系，即没有 ios_base、stream、ostream、fstream 等类似的相关类

3. 流对象没有内置的缓冲功能，即没有 stream_buffer 类支持

4. cout 作为 ofstream 的一个实例，它的输出文件是标准输出


// !! 如何使用 Mini CRT++

为了能够在 linux 下正常运行，还需要建立一个新的源代码文件叫 sysdep.cpp，用于定义 linux 平台相关的一个函数：

extern "C"
{
    void *__dso_handle = 0;
}

这个函数用于处理共享库的全局对象的构造与析构。由于共享库可能在进程退出之前被卸载，为保证共享库的全局对象被正确的析构，GCC 的 __cxa_atexit() 第三个参数用于标示这
个析构函数属于哪个共享对象，它就是 __dso_handle  这个符号。Mini CRT 不考虑对共享库的支持，为防止链接时出现符号未定义错误，定义这个符号为 0。


Mini CRT++ 在 Linux 平台下编译的方法如下:

gcc -c -fno-builtin -nostdlib  -fno-stack-protector entry.c malloc.c string.c stdio.c printf.c atexit.c -m32

g++ -c -nostdinc++ -fno-rtti -fno-exceptions  -fno-builtin -nostdlib -fno-stack-protector crtbegin.cpp crtend.cpp ctors.cpp new_delete.cpp sysdep.cpp iostream.cpp sysdep.cpp

ar -rs minicrt.a malloc.o printf.o stdio.o string.o ctors.o atexit.o iostream.o new_delete.o sysdep.o


在 Linux 下使用 Mini CRT++ 的方法如下

g++ -c -nostdinc++ -fno-rtti -fno-exceptions -fno-builtin -nostdlib -fno-stack-protector test.cpp

ld -static -e mini_crt_entry entry.o crtbegin.o test.o minicrt.a crtend.o -o test