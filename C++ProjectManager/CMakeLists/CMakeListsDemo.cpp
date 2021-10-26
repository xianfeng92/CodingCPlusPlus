#include <string>
#include<iostream>

using namespace std;

// !! 基本语法规则
// CMake 要求工程主目录和所有存放源代码子目录下都要编写 CMakeLists.txt 文件
// CMake 变量使用 ${} 方式取值,但是在 IF 控制语句中是直接使用变量名

int main(int argc, char **argv)
{
    cout << "Hello CMakeLists World" << endl;
    // !! 常见 CMakeLists.txt 中指令剖析
}