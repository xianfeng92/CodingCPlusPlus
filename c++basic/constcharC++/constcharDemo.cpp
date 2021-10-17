#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    // !! 指针 p 被放置在全局的只读存储区（const），一旦通过该指针对内存写就会出错
    // "helloworld" 是一个字符串字面量(string constant)
    char *p = "helloworld";

    // 双引号引起来的字符串是 const 的,所以 const 字符串初始化指针时，指针应该也是 const
    const char *pp = "helloworld";// output warning: ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings]


    const char *p1 = "learning";
    const char *p2 = "learning";

    cout << "p1 address is " << &p1 << endl;
    cout << "p2 address is " << &p2 << endl;

    // !! 取而代之的，应该是使用数组来做初始化声明
    char str[] = "xforg";
    str[0] = 'X';
    str[1] = 'F';
    cout << "str is " << str << endl;


    // 自 C++11 起，我们可以定义 raw string 字符串字面常量
    // Raw string 允许我们定义所见即所得的字符串字面常量，从而可以省下很多用来修饰特殊字符的符号

    // 例如一个用来表示”两个反斜线和一个n“的寻常字面常量可以定义如下

    char str1[] = "\\\\n";

    //也可以定义它为如下 raw string literal R"{"results":[],"type":"audio_level"}"

    string audio_level(R"({"results":[],"type":"audio_level"})");

    audio_level.insert(12, to_string(110));

    cout << "audio level is:" << audio_level << endl;// output:audio level is:{"results":[110],"type":"audio_level"}
    
    cout << R"(("{Kill && Bill}))" << endl; // output: ("{Kill && Bill})

}