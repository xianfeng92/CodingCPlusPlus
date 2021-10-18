
# 规定 cmake 软件的最低版本。这行命令是可选的，可以不写这句话，但在有些情况下，如果 CMakeLists.txt 文件中使用了一些
# 高版本 cmake 特有的一些命令时，就需要加上这一行，提醒用户升级到该版本之后再执行 cmake
cmake_minimum_required(VERSION 2.8)

# 指定项目的名称
# 项目最终编译生成的可执行文件不一定是这个项目名称，而是由另一条命令 (add_executable) 指定的
PROJECT(helloworld)

SET( hello_SRCS CMakeListsDemo.cpp )


# ADD_EXECUTABLE creates an executable from the listed sources
# Tip: add sources to a list (hello_SRCS), do not list them in ADD_EXECUTABLE
# 告诉工程生成一个可执行文件。该命令定义了工程最终生成的可执行文件的文件名以及参与编译的头文件和cpp文件。
ADD_EXECUTABLE( hello ${hello_SRCS} )

# 使用 message 命令查看变量具体内容
message(STATUS "The CMAKE_VERSION  is ${CMAKE_VERSION}")
message(STATUS "The CMAKE_SOURCE_DIR  is ${CMAKE_SOURCE_DIR}")
message(STATUS "The CMAKE_SOURCE_DIR  is ${CMAKE_INSTALL_PREFIX}")

#  系统名称，比如Linux-2.6.22
message(STATUS "The CMAKE_SYSTEM Version is ${CMAKE_SYSTEM}")
message(STATUS "The CMAKE_SYSTEM_PROCESSOR Version is ${CMAKE_SYSTEM_PROCESSOR}")


# 编译选项，Release 或者 Debug
set(CMAKE_BUILD_TYPE "Release")

# set c++11 编译选项
# -std=c++11 包含 C++11 特性
# 编译标志，设置 C++11 编译
# 设置 C++ 编译选项，也可以通过指令 ADD_DEFINITIONS() 添加
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -std=c++11 -O2")

SET( mylib_SRCS library.cpp )

# ADD_LIBRARY creates an static library from the listed sources
# Add SHARED to generate shared libraries (Unix) or dynamic libraries (Windows)
# 不加SHARED 生成.a 静态库，加了SHARED ，生成.so 动态链接库
# 告诉工程生成一个库文件
ADD_LIBRARY( mylib ${mylib_SRCS} )




