
// !! 首先说明

编译器是翻译代码为计算机语言的一个工具, 我们平时写的代码如果想在某个特定的计算机上执行(计算机的 cpu 构架不同), 就需要编译器来对代码进行编译汇编
链接, 而'汇编和链接的过程对于每个不同的平台上过程都不一样'。

gcc 和 clang 是两个不同的编译器, 而 'make 和 cmake 是搭配编译器来方便用户进行多文件编译而发明的工具'。


~ » gcc -v                                                 
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/9/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none:hsa
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-linux-gnu

~ » cmake -version                                             
cmake version 3.16.3

CMake suite maintained and supported by Kitware (kitware.com/cmake).


~ » make -version                                               
GNU Make 4.2.1
为 x86_64-pc-linux-gnu 编译
Copyright (C) 1988-2016 Free Software Foundation, Inc.
许可证：GPLv3+：GNU 通用公共许可证第 3 版或更新版本<http://gnu.org/licenses/gpl.html>。
本软件是自由软件：您可以自由修改和重新发布它。
在法律允许的范围内没有其他保证。



// !! 具体解释

gcc 和 clang 都是编译器。 

gcc 是 GNU Compiler Collection, 也称为 GNU 编译器套件, 可以理解为编译器, 它可以编译很多种语言: C/C++、FORTRAN、JAVA、OBJC、ADA等。
假如我有一个源文件(比如 .c 文件), 我就可以用 gcc 命令来编译它。

clang 也一样, Clang 是一个 C 语言、C++、Objective-C、Objective-C++ 语言的轻量级编译器。源代码发布于 BSD 协议下。Clang 将支持其普通
lambda 表达式、返回类型的简化处理以及更好的处理 constexpr 关键字。

但是光有 gcc 和 clang 是不行的, '如果你的源文件很多, 那就需要一个一个去编译, 太麻烦工作量巨大'。我们平常用的 VC++、Visual Studio、Clion 
这种大型IDE, 里面使用的编译器就是 gcc 或 clang。但是我们通常在使用的时候也就只需要按一个按钮就可以实现对程序的编译, 这是如何进行的呢? IDE 里面
已经帮你做了你需要做的一切了。

'make 工具相当于一个智能的批处理工具, 本身没有编译和链接的功能, 而是用类似于批处理的方式通过调用 makefile 文件中用户指定的命令来进行编译和链接。
而 makefile 又是什么, 就相当于用户将要执行的一系列命令, make 根据 makefile 中的命令对相应的源文件进行编译和链接的'。

makefile 中可能就有类似的一下命令: gcc -o test.c

makefile 文件在 github 源码安装程序中很常见, 你下载了一个源码包, 通常在 readme 中会有这样的一句:

$ make all
$ make install # root required

'make all 即编译所有, 当然这个源码包中必须有 makefile 文件才行, 执行 make all 这个命令后 make 会根据 makefile 中的命令进行编译'

当然这个是“别人家”的源码包, 这个通常都给你写好了, 但是如果你自己要编译很多源文件的时候, 也是要自己写吗?

我们需要 cmake 工具,这样就可以更加方便地生成 makefile 文件给 make 用。'cmake 可以跨平台生成对应平台能用的 makefile, 无需自己根据每个平台的
不同特性去修改'。而 cmake 根据什么生成 makefile, 它需要根据 CMakeLists.txt 文件(组态档)去生成 makefile。

下面是一个 CMakeLists.txt 文件:

cmake_minimum_required(VERSION 3.8)
project(First_Code)

set(CMAKE_CXX_STANDARD 11)

#set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp test.cpp assignment.cpp)
add_executable(First_Code ${SOURCE_FILES})