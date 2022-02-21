// !! Cmake 命令

// !! 让 CMake 找到我的头文件

include_directories ([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])

'将指定目录添加到编译器的头文件搜索路径之下', 指定的目录被解释成当前源码路径的相对路径。

它相当于 g++ 选项中的 -I 参数的作用, 也相当于环境变量中增加路径到 CPLUS_INCLUDE_PATH 变量的作用。


├── CMakeLists.txt    #最外层的 CMakeList.txt
├── main.cpp    #源文件, 包含被测试的头文件
├── sub    #子目录
 └── test.h    #测试头文件, 是个空文件, 被外层的 main.cpp 包含


1. 不使用  include_directories  包含子目录 sub, 直接在 main.cpp 里面包含 "test.h"

# CMakeList.txt
cmake_minimum_required(VERSION 3.18.2)
project(include_directories_test)
add_executable(test main.cpp)

//main.cpp
#include "test.h"
#include <stdio.h>
int main(int argc, char **argv)
{
    printf("hello, world!\n");
    return 0;
}

执行 cmake.. && make -j8  会提示找不到头文件的错误:

fatal error: 'test.h' file not found 
#include "test.h"

2. 使用 include_directories 包含子目录 sub,并在 main.cpp 里面包含 "test.h"

# CMakeList.txt
cmake_minimum_required(VERSION 3.18.2)
project(include_directories_test)
include_directories(sub) #与上个场景不同的地方在于此处
add_executable(test main.cpp)

//main.cpp
#include "test.h"
#include <stdio.h>
int main(int argc, char **argv)
{
    printf("hello, world!\n");
    return 0;
}

执行 cmake.. && make -j8 会生成可执行文件 test, 使用 ./test 执行后会输出打印 hello, world!。当然, 不使用 include_directories(sub), 
在 main.cpp 中直接使用 #include "sub/test.h" 也是可以的。


// !! 让 CMake 找到我的库文件

添加库文件的环境变量,便于代码中直接使用库文件的相对路径。

它相当于 g++ 命令的 -L 选项的作用, 也相当于环境变量中增加 LD_LIBRARY_PATH 的路径的作用

// !! 让 CMake 找到我的源文件

1. 明确指明包含的源文件
add_executable(demo main.cpp test.cpp util.cpp)

2. 搜索当前目录下的所有.cpp 文件
aux_source_directory(./src hello_src)
add_executable(demo ${hello_src})

3. 自定义搜索规则

file(GLOB SRC_LIST "*.cpp" "*.cc")
add_executable(demo ${SRC_LIST})
GLOB 不支持递归遍历子目录

'若想实现递归遍历子目录, 请使用 GLOB_RECURSE'

file(GLOB_RECURSE SOURCE_FILES
        "src/*.cpp"
        "src/src/*.cpp"
        "src/src/*/*.cpp"
        "src/*.cc"
        "src/src/*.cc"
        "src/src/*/*.cc"
        "src/*.c"
        "src/src/*.c"
        "src/src/*/*.c"
        )


// !! 告诉 CMake 我的构建目标

aux_source_directory(./src hello_src)
add_execuadd_executable(${PROJECT_NAME} ${hello_src})

其作用是使用 ${hello_src} 里面的源文件来生成一个可执行文件, 起名叫 ${PROJECT_NAME}, 即 hello.在一开始定义的那个 project(hello) 中的 
hello。

// !! 告诉 CMake 我要链接哪个库文件

target_link_libraries(${PROJECT_NAME} util)

仅需知道, 名字叫 ${PROJECT_NAME} 这个 target 需要链接 util 这个库, 会优先搜索 libutil.a, 如果没有就搜索 
libutil.so(util.dll, util.dylib)

// !! 传递 FLAGS 给 C++ 编译器

set(CMAKE_CXX_FLAGS   "-std=c++11")             # c++11
set(CMAKE_CXX_FLAGS   "-g")                     # 调试信息
set(CMAKE_CXX_FLAGS   "-Wall")                  # 开启所有警告

set(CMAKE_CXX_FLAGS_DEBUG   "-O0" )             # 调试包不优化
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG " )   # release包优化


