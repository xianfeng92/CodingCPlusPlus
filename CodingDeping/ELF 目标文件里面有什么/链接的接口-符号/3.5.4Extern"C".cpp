
// !! extern "C"

c++ 为了和 C 兼容，在符号的管理上， C++ 有一个用来声明或定义一个 C 的符号的 extern "C" 关键字用法：

extern "C" 
{
    int func(int);
    int var;
}

c++ 编译器会将在 extern "C" 的大括号里面的代码当做 C 语言代码来处理。

如果单独声明某个变量或者函数是 C 语言的符号，可以使用如下格式：

extern "C" int func11(int);
extern "C" int value;


很多时候我们会碰到有些头文件声明了一些 C 语言的函数和全局变量，但是这个头文件可能会被 C++ 的代码包含。比如我们常见的 C 语言库函数
中的 string.h 中声明的 memset 这个函数，它的原型如下：

memset(void*, int, size_t);

如果在 C++ 语言中，编译器会认为这个 memset 是一个 C++ 函数，将 memset 的符号修饰成 _Z6memsetPvii, 这样链接器就无法与C语言
库的 memset 符号进行链接


可以使用 c++ 的宏 __cplusplus, C++ 编译器会在编译 C++ 的程序时默认定义这个宏，我们可以使用条件宏来判断当前编译单元是不是
C++ 代码

#ifdef __cplusplus
extern "C" {
#endif

void *memset(void *p, int, size_t);

#ifdef __cplusplus
}
#endif

如果当前编译单元是 C++ 代码，那么 memset 会在  extern "C" 中声明； 如果是 C 代码，就直接声明。







