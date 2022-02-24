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


第二个例子从标准输入设备取得一个个英文单词, 然后将其内各个字符逆序打印。单词和单词之间以一般空白字符(换行符 newline、空格字符 space 或制表符 tab)
或逗号、句号、分号分隔开来。

#include<iostream>
#include<string>

using namespace std;

int main(int argc, char **argv)
{
    // 本程序中, 所有间隔字符被定义于一个特殊的 string 常量内
    const string delims(", \n");
    string line;
    // 外层循环不断地将新行读入 string line 之中
    // getline() 是一个可以从 stream 读取 string 的特殊函数, 它逐字读取, 直到一行结束(通常以换行符作为标志)
    while (getline(cin, line))
    {
        string::size_type begIdx, endIdx;
        // 函数 find_first_not_of() 返回"不隶属于实参所指之 string" 的第一个字符的索引, 所以本例返回第一个"分隔符（delims）以外"
        // 的字符
        begIdx = line.find_first_not_of(delims);
        while (begIdx != string::npos)
        {
            // 内层循环的第一个语句用来查找当前单词的结尾
            endIdx = line.find_first_of(delims, begIdx);
            if(endIdx == string::npos)
            {
                endIdx = line.length();
            }
            // 以下语句将所有字符逆序打印出来
            for(int i = endIdx - 1; i >= static_cast<int>(begIdx); --i)
            {
                cout << line[i];
            }
            cout << ' ';
            // 和先前对 find_first_not_of() 的调用不同, 这里把上一个单词的终点当作查找起点
            begIdx = line.find_first_not_of(delims, endIdx);
        }
    }
}

 » g++ --std=c++11 stringdemo2.cpp
--------------------------------------------------------------------------------
 » ./a.out
hello,world
olleh dlrow 




// !! String Class 细节描述

// !! String 的各种相关类型

// !! 头文件

头文件 <string> 定义了所有的 string 类型和其函数。

#include <string>

一如既往, 所有标识符都定义于命名空间 std 之中。

class Template basic_string<>

在 <string> 之中, class basic_string<> 被定义为所有 string 类型的基础模板类(basic template class):

namespace std
{
    template <typename charT,typename traits = char_traits<charT>
    , typename Allocator = allocator<charT>>
    class basic_string;
}

这个 class 将字符类型、字符类型的 trait、内存模型(memory model)都参数化了:

1. 第一参数是单个字符所属类型

2. 带默认值的第二参数是个 trait class, 提供 string class 的所有"字符内核操作"。这个 trait class 规定如何复制字符或比较字符。

3. 带默认值的第三参数定义了 string class 所采取的内存模型, 一如寻常, 默认使用 allocator


// !! 具体的 String 类型

C++ 标准库提供了若干 basic_string<> 特化版本:                          0

1. string 是针对 char 而预定义的特化版本

namespace std
{
    typedef basic_string<char> string;
}


2. 于使用宽字符(例如 Unicode 或某些亚洲字符集) 的 string, 存在三个预定义的特化版本:                          0

namespace std
{
    typedef basic_string<wchar_t> wstring;
    typedef basic_string<char16_t> u16string;
    typedef basic_string<char32_t> u32string;
}

以下几节的讨论适合于上述所有 string class。由于所有 string class 采用相同接口, 所以用法和问题都一样。我将以 string 代表任何 string type, 
包括 string、wstring、u16string 和 u32string。由于一般软件开发大多顺应欧美环境, 所以本书的例子大多采用 string 类型。


'只有单实参的 const char* 版本才将字符 '\0' 视为 string 的结尾特殊符号, 其他所有情况下 '\0' 都不被视为特殊字符':

std::string s1("nico");// initial s1 with 'n' 'i' 'c' 'o'

std::string s2("nico",5);// initial s2 with 'n' 'i' 'c' 'o' '\0'

std::string s3(5,'\0');// initial s3 with '\0' '\0' '\0' '\0' '\0'

s1.length();// output 4
s2.length();// output 5
s3.length();// output 5

因此, 一般而言, string 可以内含任何字符, 甚至可以包含二进制文件( binary file) 的内容。

把一个 null pointer 传入作为 cstr 会导致不明确的行为。


// !!未提供的操作函数

C++ 标准库的 string class 并未解决所有可能遇到的 string 问题。事实上它并没有提供下列问题的直接解决方案:

1. 正则表达式(regular expression)---C++11 独立出另一个小型库来处理

2. 文本处理(text processing)


// !! 构造函数和析构函数（Constructor and Destructor）

注意, 你不能以单一字符初始化某字符串, 但是可以这么做:

std::string s1('x');// error
std::string s2(1,'x');// okay
std::string s3({'x'});// ok (since c++ 11)

这表示存在一个从 const char* 到 string 的自动类型转换, 但不存在一个从 char 到 string 的自动类型转换。


// !! String 的构造函数和析构函数

string s --- 生成一个空 string
string s(str) --- Copy 构造函数, 创建一个 string str 的拷贝
string s(cstr) --- 以 C-string 作为字符串 s 的初值
string s(begin, end) ---以 [begin, end) 区间内的字符作为 s 的初值
string s(num, c) --- 生成一个字符串包括 num 个 c 字符
s.~string() --- 销毁所有字符释放内存


// !! String 和 C-String


C++ standard 将 string literal(字符串字面常量) 的类型由 char* 改为 const char*。为了提供向后兼容性, C++standard 规定了一个颇有争议的隐
式转换, 可从 const char* 隐式转为 char*。


由于 string literal 的类型并非 string, 因此在新的 string object 和传统的 C-string 之间必须存在一个强关系: 在“string 与 
string-like object” 的共通操作中(例如比较、附加、插入等动作) 都应该可以使用 C-string。或者具体地说, 存在一个从 const char* 到 string 的隐
式类型转换。然而现实却不存在一个从 string object 到 C-string 的自动类型转换, '这是出于安全考虑, 防止意外类型转换导致奇异行为( char* 经常有奇
异行为)和模棱两可(例如在一个结合了 string 和 C-string 的表达式中, 如果既可把 string 转化为 char* 也可反其道而行, 就会导致模棱两可, 也就是所谓
歧义)'。

有好几种办法可以创建或复制 C-string。更具体地说, c_str() 可以得到"string 对应的 C-string", 所得结果和"以'\0'为结尾"的字符数组一样。运用
copy(), 你也可以将 string 内容复制或写入既有的 C-string 或字符数组内。

还要注意, 千万不要以旧式的 null pointer(NULL) 取代 nullptr 或取代 char* 参数, 这会导致奇异的行为, 因为 NULL 具有整数类型, 如果某个操作被
重载(overloaded), 接受"单一整数类型", 那么 NULL 会被解释为数字 0或"其值为 0"的字符。

'So you should always use nullptr or char* pointers'.


有三个函数可以将 string 内容转换为字符数组或 C-String:

1. 'data() 和 c_str() 以字符数组的形式返回 string 内容'。该数组在位置[size()]上有一个 end-of-string 字符, 所以其结果是一个内含'\0'字符的
    有效 C-string

    string s1("hello world");
    s1.c_str();
    s1.data();

2. copy() 将 string 内容复制到"调用者提供的字符数组"中, 其末尾不添加 '\0' 字符。注意, data() 和 c_str() 返回的字符数组由该 string 拥有。也
   就是说, 调用者绝不可以改动它或释放其内存。
   
   例如:

   #include<cstring>
   #include<string>

   std::string s("11234");

   atoi(s.c_str());// convert string to integer

   char buf[1024];
   s.copy(buf,1024);// copy at most 1024 characters to string s


'一般而言, 整个程序中你应该坚持使用 string, 直到你必须将其内容转化为 char* 时才把它们转换为 C-string'。

'注意 c_str() 和 data() 的返回值的有效期限在下次调用 non-const 成员函数时即告终止'。

    std::string s("hello world");
    ...
    foo(s.c_str());// s.c_str() is valid during the whole statement
    const char *p;
    p = s.c_str();
    foo(p);// p is valid during the whole statement
    s += "nio";
    foo(p);// Error, argument is invalid


// !!大小和容量(Size and Capacity)

为了高效无误地运用 string, 你应该理解 string 的大小和容量之间的关系。一个 string 存在三种“大小”:

1. size() 和 length() 返回 string 的现有字符数。两个函数等效。成员函数 empty() 用来检验字符数是否为 0, 亦即字符串是否为空。你应该优先使用该
   函数, 因为它比 length() 或 size() 更快。

2. max_size() 返回 "string 最多能够包含的字符数"。string 通常包含"单独一个内存区块内的所有字符", 所以可能与 PC 本身的限制有关系。返回值
   一般而言是索引类型之最大值减 1。之所以 "减 1"有两个原因:(1) 最大值本身是 npos; (2) 具体实现中可因此轻易在内部缓冲区之末尾添加一个'\0', 以便将
   这个 string 当作 C-string 使用(例如通过 c_str() 。一旦某个操作函数使用一个长度大于 max_size() 的 string, length_error 异常就会被抛出。

3. capacity() 重新分配内存之前, string 所能包含的最大字符数


   让 string 拥有足够的容量是很重要的, 原因有二:

   1. 重新分配会造成所有指向 string 的 reference、pointer 和 iterator失效

   2. 重新分配 (reallocation) 很耗时间


因此, 如果程序要用到指向 string 的reference、pointer 和 iterator, 抑或需要很快的执行速度, 就必须考虑容量(capacity) 问题。'成员函数 
reserve() 就用来避免重分配行为, 它使你得以预留一定容量, 并确保该容量用尽之前 reference 一直保持有效':

string s;
s.reserve(80);

容量概念应用于 string 和应用于 vector 是相同的; 但有一个显著差异: 对 string 你可以调用 reserve() 缩减实际容量, 而 vector 的 reserve() 
却没有这项功能。

拿一个"小于现有容量"的实参来调用 reserve(), 实际上就是一种非强制性缩减请求(nonbinding shrink request), 如果实参"小于现有字符数", 则被视
为"非强制性合身缩减"的请求(nonbinding shrink-to-fit request)。也就是说, '你可能想要缩减容量至某个目标, 但不保证可以如愿'。

为什么缩减动作是非强制性的呢? 

因为"如何获得最佳效能"由实现决定。具体实现 string 时, 不同的实现对于速度和内存耗用量之间的取舍可能有不同的思路。

// !! 元素访问(Element Access)

string 允许我们对其所包含的字符进行读/写。有两种方法可以访问单一字符: subscript(下标)操作符 [] 和成员函数 at()。自 C++11 开始, front() 
和 back() 也被提供, 分别用来访问第一字符和最末字符。


'所有这些函数都返回某指定索引之对应位置上的字符'。

一如以往, 第一个字符的索引为 0, 最末字符的索引为 length() -1。但是请注意以下区别:

1. 'operator[] 并不检查索引是否有效, at() 则会检查'。如果调用 at() 时指定的索引无效, 系统会抛出 out_of_range 异常。'如果调用 operator[] 
    时指定的索引无效, 其行为不明确——可能访问非法内存, 因而引起某些讨厌的边缘效应甚至崩溃'(崩溃还算运气好, 因为你好歹知道出错了)。

2. '一般而言, 最末字符的更后面位置也是有效的'。因此, "当前实际字符数" 可被当成一个有效的索引。此情况下 operator[] 返回的是"由字符类型之 
    default 构造函数所产生"的字符, 就类型为 string 的对象来说返回值是 char '\0'。

3. front() 相当于 [0]。这意味着对于空 string, 获得的是 end-of-string(对 string 而言是'\0')

4. 对于 at(), "当前字符个数"不是个有效索引

5. 对一个空 string 调用 back() 会导致不明确的行为


举个例子:

const std::string cs("nico");// cs constains 'n' 'i' 'c' 'o'
std::string s("abcde");// s constains 'a' 'b' 'c' 'd' 'e'
std::string t;

s[2];// yields 'c' as char &
s.at(2);// yields 'c' as char &
s.front();// yields 'a' as char &
cs[2];// yields 'i' as const char &
cs.at(2);// yields 'i' as const char &
s[100];// Error undefine behaviour
s.at(100);// throw out of range error
t.front();// yield '\0'
t.back();// Error undefine behaviour

s[s.length()];// yield '\0'(undefine behaviour before C++ 11)
s.at(s.length());// throw out of range error


为了允许改动 string 内容, operator[] 的 non-const 版本以及 at()、front() 和 back() 都返回字符的 reference。一旦发生重分配行为, 
那些 reference 立即失效:

std::string s("abcde");
char & r = s[2];
char *p = &s[3];

r = 'X';
*p = 'Y';

s = "new long value";// reallocation invalidate r and p

r = 'X';// Error undefine behaviour
p = 'Y';// Error undefine behaviour

这里, 为了避免运行时期出错, 我们应该在 r 和 p 被初始化之前, 先运用 reserve() 保留足够的容量。


以下操作可能导致"指向字符"的 reference 和 pointer 失效:

1. 以swap() 交换两值

2. 以 operator>>() 或 getline() 读入新值

3. 调用 operator[]、at()、begin()、end()、rbegin() 和 rend() 之外的任何 non-const 成员函数



// !! 比较（Comparison）

string 支持常见的比较(comparison) 操作符, 操作数可以是 string 或 C-string:

std::string s1, s2;
...
s1 == s2;
s1 < "hello";

如果以 <、<=、> 或 >= 比较 string, 将会是根据"当前之 char trait"将字符依字典顺序逐一比较。

例如以下所有比较结果均为 true:

std::string s1("aaa") < std::string s2("bbb");
std::string s3("ccc") < std::string s4("ccd");
std::string s5("ddd") < std::string s6("dddddd");

也可以使用成员函数 compare() 比较子字符串, '此函数针对一个 string 可接受多个实参进行处理, 如此一来就可以采用索引和长度, 双管齐下定位出子字符串'。
请注意 compare() 返回的是整数值而非 Boolean 值, 意义如下: 0 表示相等, 小于 0 表示小于, 大于 0 表示大于。例如:

std::string s("abcd");
s.compare("abcd");// return 0
s.compare("dcba");// return < 0
s.compare("ab");// return > 0

s.compare(s);// return 0

s.compare(0,2,s,2,2);// return a value < 0
s.compare(1,2,"bcx",2);// "bc" == "bc", return 0

'如果想采用不同的比较准则, 你可以自行定义一个比较准则并采用 STL 的比较算法'。


// !! 更改内容（Modifier）

你可以运用不同的成员函数或操作符更改 string 内容。


// !! 赋值（Assignment）

使用 operator= 可对 string 赋予新值。新值可以是 string、C-string 或单一字符。'如果需要多个实参来描述新值, 可改用成员函数 assign()'。
举个例子:

const std::string aString("othello");
std::string s;
s = aString;// assign
s = "two\n lines";// assign
s = ' ';assign

s.assign(aString);// assign
s.assign(aString,1,3);// "the"
s.assign(aString,2,string::npos);// "hello"
s.assign(5, 'x'); // "xxxxx"


也可以对"两个 iterator  定义出来的字符区间" 进行赋值


// !! 交换(Swapping Values)


和许多"不平淡的"(nontrivial) 类型一样, string 类型提供了一个特殊的 swap() 函数用来交换两个 string 内容。这个特殊化的 swap() 保证常量复杂
度, 所以如果赋值后不再需要旧值, 你应该利用这个函数进行交换, 从而达成赋予新值的目的。


// !! 令 string 成空

std::string s;
s = "";// assign a empty string
s.clear();// clear contents
s.erase();// erase all characters


// !! 安插和移除(Inserting and Removing)字符

string 提供了许多成员函数用于安插(insert)、移除(remove)、替换(replace)、抹除(erase)字符。另有 operator+=、append() 和 push_back() 
可附加字符。实例如下:

#include<cstring>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s1("hello world");
    string::size_type pos = s1.find("world");
    s1.replace(pos,5,"nio");

    cout << "s1 is " << s1 << endl;

    const string aString("see you");
    string s;
    s += aString;
    s += "two \n line ";
    s.append(aString);
    s.append(aString, 1, 3);
    s.append(aString, 2, string::npos);
    
    s.push_back('\0');


    
    return 0;
}


operator+= 将单一实参附加于 string 末尾, append() 可接受多个实参指明附加值。另有一个 append() 版本可将两个 iterator 所指出的字符区间附加
于 string 末尾。push_back() 是为支持 back inserter 而设, STL 算法可借此向 string 末尾添加字符。


和 append() 类似, 成员函数 insert() 也允许你安插字符。'使用 insert() 时需要知道安插位置的索引, 新字符将被安插于此位置之后'。

std::string s = "i18n";
s.replace(1,2,"nternationallizatio");// internationalization
s.erase(13);// international
s.erase(7, 5);// internal



// !! 子字符串（Substring）及字符串接合（String Concate-nation）

你可以使用成员函数 substr() 从 string 身上萃取出 substring。例如:

std::string s("interchangeability");
s.substr();// return a copy of string s
s.substr(11);// "ability"
s.substr(5, 6);// "change"
s.substr(s.find('c'));// "changeability"


你可以使用 operator+ 把两个 string(或C-string) 接合起来。例如:

std::string s1("enter");
std::string s2("nation");
std::string i18n;
i18n = 'i' + s1.substr(1) + s2 + "aliz" + s2.substr(1);

自 C++11 开始, operator+ 也被重载以应付"身为rvalue reference"的 string, 用以支持 move 语义。因此, 如果一个 string 实参被传给 operator+
且以后不再被使用, 你就应对该 string 使用 move() 将它搬移给操作符。例如:

string foo()
{
    std::string s1('hello');
    std::string s2('world');
    std::string s3 = std::move(s1) + std::move(s2);
    return s;
}


// !! I/O操作符


