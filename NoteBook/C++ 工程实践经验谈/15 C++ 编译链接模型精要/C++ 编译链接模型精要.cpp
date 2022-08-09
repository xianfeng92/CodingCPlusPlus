// !! C++ 编译链接模型精要

C++ 从 C 语言继承了一种古老的编译模型, 引发了其他语言中根本不存在的一些编译方面的问题 (比方说一次定义原则  (ODR))。理解这些问题有助于在实际开发中规避各种古怪的错误。


C++ 语言的三大约束是:

1. 与 C 兼容

2. 零开销 (zero overhead) 原则

3. 值语义


"与 C 兼容"的含义很丰富, 不仅仅是'兼容 C 的语法, 更重要的是兼容 C 语言的编译模型与运行模型', 也就是说能直接使用 C 语言的头文件和库。

比方说对于 connect(2) 这个系统函数, 它的头文件和原型如下。

#include <sys/socket.h>

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

C++ 的基本类型的长度和表示 (representation) 必须和 C 语言一样 (int、指针等等), C++ 编译器必须能理解头文件 sys/socket.h 中 struct sockaddr 的定义, 生成与
C 编译器完全相同的 layout (包括采用相同的对齐 (alignment) 算法), 并且遵循 C 语言的函数调用约定 (参数传递，返回值传递，栈帧管理等等), 才能直接调用这个C 语言库函数。

由于现代操作系统暴露出的原生接口往往是 C 语言描述的。C++ 兼容 C, 从而能在编译的时候直接使用这些头文件, 并链接到相应的库上。在运行的时候直接调用 C 语言的函数库, 这
省了一道中间层的手续, 可算作是 C++ 高效的原因之一。

C++ 至今 (C++11) 没有模块机制, 不能像其他现代编程语言那样用 import 或 using 来引入当前源文件用到的库 (含其他 package/module 里的函数或类), 而必须用 include 头
文件的方式来机械地将库的接口声明以文本替换的方式载入, 再重新 parse 一遍。这么做一方面让编译效率奇低, 编译器动辄要 parse 几万行预处理之后的源码, 哪怕源文件只有几百行;
另一方面, 也留下了巨大的隐患。部分原因是头文件包含具有传递性, 引入不必要的依赖;

比如有一个简单的小程序, 只用了 printf(3) 却不得不包含 stdio.h, 把其他不相关的函数、struct 定义、宏、typedef、全局变量等等也统统引入到当前命名空间。在预处理的时候会
读取近 20 个头文件, 预处理之后供编译器 parse 的源码有近千行, 这还算是短的。

#include <stdio.h>

int main(int argc, char **argv) {
    printf(”hello preprocessor\n”);
}


✗ gcc -E hello.cc | wc// 预处理之后有 886 行
    886    2158   18146


值得一提的是, 为了兼容 C 语言 C++ 付出了很大的代价。

1. 例如要兼容 C 语言的隐式类型转换规则 (例如整数类型提升), 让 C++ 的函数重载决议 (overload resolution) 规则无比复杂。

2. 另外 class 定义式后面那个分号也不晓得谋杀了多少初学者的时间




// !! C 语言的编译模型及其成因

1973 年初, C 语言基本定型, 主要新特性是支持结构体。此时 C 语言的编译模型已经基本定型, 即分为预处理、编译、汇编、链接这四个步骤, 沿用至今。


// !! 为什么 C 语言需要预处理?

了解了 C 语言的诞生背景, 我们可以归纳 PDP-11 上的第一代 C 编译器的硬性约束: 内存地址空间只有 16-bit, 程序和数据必须挤在这狭小的 64kB 空间里, 可谓捉襟见肘。

编译器没办法在内存里完整地表示单个源文件的抽象语法树, 更不可能把整个程序（由多个源文件组成）放到内存里, 以完成交叉引用（不同源文件的函数之间相互调用, 使用外部变量等等）。
由于内存限制, 编译器必须要能分别编译多个源文件, 生成多个目标文件, 再设法把这些目标文件组合 (链接) 为一个可执行文件。

在今天看来, C 语言这种支持把一个大程序分成多个源文件的功能几乎是顺理成章的。

或许是受内存限制, 一个可执行程序不能太大, Dennis Ritchie 编写的 PDP-11 C 编译器不是一个可执行文件, 而是 7 个可执行文件: cc、cpp、as、ld、c0、c1、c2。其中 cc 
是个 driver, 用于调用另外几个程序。

cpp 是预处理器。c0、c1、c2 是 C 编译器的三个阶段 (phase), c0 的作用是把源程序编译为两个中间文件, c1 把中间文件编译为汇编源代码, c2 是可选的, 用于对生成汇编代码做
窥孔优化。as 是汇编器, 把汇编代码转换为目标文件。ld 是链接器, 把目标文件和库文件链接成可执行文件。


不用 cc, 手工编译一个简单程序 prog.c 的过程是:

/lib/cpp prog.c > prog.i # prog.i 是预处理之后的源代码
/lib/c0 prog.i temp1 temp2 # c0 生成 temp1 和 temp2 这两个中间文件
/lib/c1 temp1 temp2 prog.s # c1 读入 temp1 和 temp2 生成汇编代码 prog.s
as - prog.s # 把 prog.s 汇编为目标文件 a.out。猜猜 a.out 的原意？
ld -n /lib/crt0.o a.out -lc # 把 a.out 链接为可执行文件



// IP socket address structure
struct sockaddr_in {
    uint_16_t sin_family;
    uint_16_t sin_port;
    struct in_addr sin_addr;
    unsigned char sin_zero[8];
}

// Generic socket address structure (for connect, bind, and accept)
struct sockaddr {
    uint_16_t sa_family;
    char sa_data[14];
}

