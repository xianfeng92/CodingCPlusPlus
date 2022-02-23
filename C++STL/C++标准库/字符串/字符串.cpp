// !! 字符串

string 可能是混乱的根源, 因为这个字眼的确切含义比较模糊, 它是指一个类型为 char*(亦可加上 const)的寻常字符数组(charater array)? 或是 
class string<> 的一个实例 ? 或泛指代表某种 string 的某个 object ? 本章之中我对术语 string 的定义是: '根据 C++ 标准库中"某个string类型
(string、wstring、u16string或u32string)"创建出来的object'。'至于寻常由 char* 或  const char* 类型所构成的 string, 我采用的术语是 
C-string'。

注意, 在 C++98 中, string 字面常量(例如"hello")的类型会被转为 const char*。为了向后兼容, 有一个隐式(但不被鼓励的) 转换可把它们转为 char*。
严格地说, 字面常量(例如"hello")的原本类型是 const char[6], 但此类型被自动转换(蜕变)为 const char* , 所以你几乎总是可以在声明式中使用
和看到 const char*。


// !! C++11 带来的最新改变

C++98 已经规范出  string class 的几乎所有特性。下面是 C++11 增补的几个最重要的特性:

1. string 如今提供了 front() 和 back(), 用来访问第一元素和最末元素, 还提供 shrink_to_fit() 用来缩小容量

2.string 如今提供了方便的函数用来将 string 转换为数值, 以及反向转换

3. data() 和 c_str()  不会再造成"指向 string"的 reference、iterator 和 pointer 无效

4. string 如今支持 move 语义以及初值列(initializer list)

5. string 如今可以间接要求提供一个 end-of-string 字符(对string而言是'\0'), 因为对于一个string s, s[s.length()]] 应该总是合法且
   s.data() 返回的字符包含一个末尾的 end-of-string 字符

// !! String Class 的目的

C++ 标准库中的 string class 使你得以将 string 当作一般类型而不会令用户感觉任何问题。你可以像对待基础类型那样针对 string 复制、赋值和比较,
再也不必担心内存是否足够、占用的内存实际长度等问题, 只需运用操作符, 例如以 = 进行赋值, 以 == 进行比较, 以 + 进行串连。'简而言之, C++ 标准库对
string 的设计思维就是, 让它的行为尽可能像基础类型, 不至于在操作上引起什么麻烦'(至少原则如此)。现今世界的数据处理大部分就是 string 的处理, 所以
对于从 C、Fortran 或类似语言一路走来的程序员而言, 这是非常重要的进步, 因为 string 在那些语言中往往是烦恼之源。

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    // 没有传入实参, 表示它们均使用 string 的 default 构造函数, 于是都被初始化为空字符串
    string filename, basename, extname, tmpname;
    const string suffix("tmp");

    for(int i =0; i < argc; i++)
    {
        filename = argv[i];
        // 所有查找函数的返回类型都是 string::size_type, 这是 string class 定义的一个无正负号整数类型
        // 字符串 filename 中查找第一个 '.' 字符
        string::size_type idx = filename.find('.');
        // 如果查找失败, 必须返回一个特殊值, 该值就是 npos, 定义于 string class 中
        // 请特别注意, 当你打算检验查找函数的返回值时, 应该使用 string：：size_type 类型而不是 int 或 unsigned。
        // 否则上述与 string：：npos 的比较动作将无法有效运行
        if(idx == string::npos)
        {
            tmpname = filename + '.' + suffix;
        }
        else
        {
            // substr() 的第一实参是起始索引值, 可有可无的第二实参是字符个数(不是终点索引值)
            basename = filename.substr(0, idx);
            // 如果没有指定第二实参, 那么所有剩余字符都将被视为子字符串返回
            extname = filename.substr(idx + 1);
            if(extname.empty())
            {
                tmpname = filename;
                tmpname += suffix;
            }
            else if(extname == suffix)
            {
                tmpname = filename;
                // 是的 size() 和length() 都返回 string 的字符个数
                tmpname = filename.replace(idx + 1, extname.size(), "xxx");
            }
            else
            {
                tmpname = filename;
                // 如果指明 string::npos, 意思是“剩余所有字符"
                tmpname = filename.replace(idx + 1,string::npos, suffix);
            }
        }
    }
    cout << "filename: " << tmpname << endl;
}

 » g++ --std=c++11 stringdemo1.cpp
--------------------------------------------------------------------------------
 » ./a.out hello.txt 
filename: hello.tmp