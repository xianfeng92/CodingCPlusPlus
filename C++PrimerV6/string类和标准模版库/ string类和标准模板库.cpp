// !! string 类和标准模板库

至此您熟悉了 C++ 可重用代码的目标，这样做的一个很大的回报是可以重用别人编写的代码, 这正是类库的用武之地。。有很多商业 C++ 类库，也有一些库是 C++
程序包自带的。例如，曾使用过的头文件 ostream 支持。本章介绍一些其他可重用代码，它们将给编程工作带来快乐。

// !! string 类

很多应用程序都需要处理字符串。C 语言在 string.h (在 C++ 中为 cstring)中提供了一系列的字符串函数，很多早期的 C++ 实现为处理字符串提供了自己的类。

string 类是由头文件 string 支持的(注意，头文件 string.h 和 cstring 支持对 C-风格字符串 进行操纵的 C 库字符串函数，但不支持 string 类)。要使用类，
关键在于知道它的公有接口，而 string 类包含大量的方法，其中包括了若干构造函数，用于将字符串赋给变量、合并字符串、比较字符串和访问各个元素的重载运算符以及用
于在字符串中查找字符和子字符串的工具等。简而言之，string 类包含的内容很多。


// !! 构造字符串

先来看 string 的构造函数。毕竟，对于类而言，最重要的内容之一是: 有哪些方法可用于创建其对象。

str1.cpp 使用了 string 的7个构造函数(用 ctor 标识，这是传统 C++ 中构造函数的缩写)。string 实际上是模板具体化 basic_string<char> 的一个 typedef，同
时省略了与内存管理相关的参数。size_type 是一个依赖于实现的整型，是在头文件 string 中定义的。

#include <iostream>
#include <string>

// using string constructor
int main()
{
    using namespace std;
    string one("Lottery Winner");// ctor #1
    cout << one << endl;

    string two(20,'$');// ctor #2
    cout << two << endl;

    string three(one);// ctor #3
    cout << three << endl;

    one += "opps";// overloaded +=
    cout << one << endl;

    two = "Sorry! That was ";
    three[0] = 'P';
    string four;// ctor #4
    four = three + two;// overloaded +, =
    cout << four << endl;

    char alls[] = "All's will that end will ";
    string five(alls,20);// ctor #5

    cout << five << endl;
    string six(alls + 6,alls+10);// ctor #6
    cout << six << endl;

    string seven(&five[6],&five[10]);// ctor #6 again
    cout << seven << endl;

    string eight(four,7,16);// ctor #7
    cout << eight << endl;
    return 0;
}

程序中使用了重载 += 运算符，它将一个字符串附加到另一个字符串的后面; 重载的 = 运算符用于将一个字符串赋给另一个字符串; 重载的 << 运算符用于显示 string 对象;
重载的 [] 运算符用于访问字符串中的各个字符。

 » g++ --std=c++11 str1.cpp 
--------------------------------------------------------------------------------
 » ./a.out
Lottery Winner
$$$$$$$$$$$$$$$$$$$$
Lottery Winner
Lottery Winneropps
Pottery WinnerSorry! That was 
All's will that end 
will
will
 WinnerSorry! Th'
-------------------

1. 程序首先演示了可以将 string 对象初始化为常规的C-风格字符串，然后使用重载的 << 运算符来显示它:

    string one("Lottery Winner");// ctor #1
    cout << one << endl;

2. 构造函数将 string 对象 two 初始化为由 20 个 $ 字符组成的字符串

3. 复制构造函数将 string 对象 three 初始化为 string 对象 one

    string three(one);// ctor #3

4. 重载的 += 运算符将字符串 “Oops!” 附加到字符串 one 的后面

   one += "opps";// overloaded +=

   这里是将一个C-风格字符串附加到一个 string 对象的后面。但 += 运算符被多次重载，以便能够附加 string 对象和单个字符

5. 同样，= 运算符也被重载，以便可以将 string 对象、C-风格字符串或 char 值赋给 string 对象

    two = "Sorry! That was ";
    three[0] = 'P';

6. 重载 [] 运算符使得可以使用数组表示法来访问 string 对象中的各个字符

   three[0] = 'P';

7. 默认构造函数创建一个以后可对其进行赋值的空字符串

    string four;// ctor #4
    four = three + two;// overloaded +, =
    cout << four << endl;

    第 2 行使用重载的 + 运算符创建了一个临时 string 对象，然后使用重载的 = 运算符将它赋给对象 four。正如所预料的，+ 运算符将其两个操作数组合成一个 
    string 对象。该运算符被多次重载，以便第二个操作数可以是 string 对象、C-风格字符串或 char 值

8. 第 5 个构造函数将一个C-风格字符串和一个整数作为参数，其中的整数参数表示要复制多少个字符:

    char alls[] = "All's will that end will ";
    string five(alls,20);// ctor #5

9. 第 6 个构造函数有一个模板参数:

    template<typename Iter> string(Iter begin, Iter end);

    begin 和 end 将像指针那样，指向内存中两个位置(通常，begin 和 end 可以是迭代器——广泛用于STL中的广义化指针),。构造函数将使用 begin 和 end 指向的位置之
    间的值，对 string 对象进行初始化。[begin, end) 来自数学中，意味着包括 begin，但不包括 end 在内的区间。由于数组名相当于指针，所以 alls + 6 和 
    alls +10 的类型都是 char *，因此使用模板时，将用类型 char * 替换 Iter。第一个参数指向数组 alls 中的第一个 w，第二个参数指向第一个 well 后面的空格。

10. 第 7 个构造函数将一个 string 对象的部分内容复制到构造的对象中


// !! C++11 新增的构造函数

构造函数 string(string && str)类似于复制构造函数，导致新创建的 string 为 str 的副本。但与复制构造函数不同的是，它不保证将 str 视为 const。这种构造
函数被称为移动构造函数(move constructor)。

构造函数 string(initializer_list<char> il)让您能够将列表初始化语法用于 string 类。也就是说，它使得下面这样的声明是合法的:

string str = {'q','A','B','C','D','E','F'};

就 string 类而言，这可能用处不大，因为使用 C-风格字符串 更容易，但确实实现了让列表初始化语法普遍实用的意图。

// !! string 类输入

对于类，很有帮助的另一点是，知道有哪些输入方式可用。对于C-风格字符串，有 3 种方式:

char info[100];

cin >> info;// read a word
cin.getline(info,100);// read a line, discard '\n'
cin.get(info,100);// read a line, leave '\n' in queue


对于 string 对象，有两种方式：

string stuff;

cin >> stuff;
cin.getline(stuff,':');// read up to :, discard :
getline(stuff,':');//read up to :, discard :

在功能上，它们之间的主要区别在于，string 版本的 getline() 将自动调整目标 string 对象的大小，使之刚好能够存储输入的字符:

char fname[10];
string lname;
cin >> fname;// could be a problem if input size > 9
cin >> lname;// can read a very, very long word

cin.getline(fname,10);// may truncate word
getline(cin,lname);// no truncation

'自动调整大小的功能让 string 版本的 getline() 不需要指定读取多少个字符的数值参数'。

在设计方面的一个区别是，读取 C-风格字符串 的函数是 istream 类的方法，而 string 版本是独立的函数。这就是对于C-风格字符串输入，cin 是调用对象；而对于
string 对象输入，cin 是一个函数参数的原因。

这种规则也适用于 >> 形式，如果使用函数形式来编写代码，这一点将显而易见:

    cin.operator>>(fname);// istream class method
    operator>>(cin,lname);// regular function

下面更深入地探讨一下 string 输入函数。正如前面指出的，这两个函数都自动调整目标 string 的大小，使之与输入匹配。但也存在一些限制。

1. 第一个限制因素是 string 对象的最大允许长度，由常量 string::npos 指定。这通常是最大的 unsigned int 值，因此对于普通的交互式输入，这不会带来实际的限制；
   但如果您试图将整个文件的内容读取到单个 string 对象中，这可能成为限制因素

       string::npos

2. 第二个限制因素是程序可以使用的内存量


string 版本的 getline() 函数从输入中读取字符，并将其存储到目标 string 中，直到发生下列三种情况之一:

1. 到达文件尾，在这种情况下，输入流的 eofbit 将被设置，这意味着方法 fail() 和 eof() 都将返回 true

2. 遇到分界字符(默认为\n)，在这种情况下, 将把分界字符从输入流中删除，但不存储它

3. 读取的字符数达到最大允许值(string::npos和可供分配的内存字节数中较小的一个)，在这种情况下，将设置输入流的 failbit，这意味着方法 fail() 将返回true


'输入流对象有一个统计系统，用于跟踪流的错误状态'。在这个系统中, 检测到文件尾后将设置 eofbit 寄存器, 检测到输入错误时将设置 failbit 寄存器，出现无法识别的故
障(如硬盘故障) 时将设置 badbit 寄存器，一切顺利时将设置 goodbit 寄存器。

string 版本的 operator>>() 函数的行为与此类似，只是它不断读取，直到遇到空白字符并将其留在输入队列中，而不是不断读取，直到遇到分界字符并将其丢弃。'空白字符指
的是空格、换行符和制表符'，更普遍地说，是任何将其作为参数来调用 isspace() 时，该函数返回 true 的字符。


strfile.cpp 是一个从文件中读取字符串的简短示例，它假设文件中包含用冒号字符分隔的字符串，并使用指定分界符的 getline() 方法。然后，显示字符串并给它们编号，
每个字符串占一行。

#include<iostream>
#include<fstream>
#include <string>
#include <cstdlib>

int main()
{
    using namespace std;
    ifstream fin;
    fin.open("tobuy.txt");
    if(!fin.is_open())
    {
        cout << "Can't open file .Bye.\n";
        exit(EXIT_FAILURE);
    }
    string item;
    int count = 0;
    getline(fin,item,':');
    while(fin)// while input is good
    {
        ++count;
        cout << count << ": " << item << endl;
        getline(fin,item,':');
    }
    cout << "good bye!" << endl;
    fin.close();
    return 0;
}

 » g++ --std=c++11 strfile.cpp
--------------------------------------------------------------------------------
 » ./a.out hel    
1: Iphone1
2: IPhone2
3: IPhone3
4: IPhone4
5: IPhone5
6: NIO
7: 
meat
8: banana
9: apple
10: orange
11: orange
12: orange
13: orange
14: orange
15: orange
16: orange
17: orange
good bye!


注意, 将 : 指定为分界字符后，换行符将被视为常规字符。

// !! 使用字符串

现在，您知道可以使用不同方式来创建 string 对象、显示 string 对象的内容、将数据读取和附加到 string 对象中、给 string 对象赋值以及将两个 string 对象连结
起来。除此之外，还能做些什么呢？

1. '可以比较字符串。String 类对全部 6 个关系运算符都进行了重载'

    如果在机器排列序列中, 一个对象位于另一个对象的前面，则前者被视为小于后者。如果机器排列序列为 ASCII 码，则数字将小于大写字符，而大写字符小于小写字符。对
    于每个关系运算符, 都以三种方式被重载，以便能够将 string 对象与另一个 string 对象、C-风格字符串进行比较，并能够将C-风格字符串与 string 对象进行比较

    string snake1("cobra");
    string snake2("cobr1");

    char snake3[20] = "anaconda";

    if(snake1 < snake2)// operator<(const string &, const string &)

    ...

    if(snake1 == snake3);// operator==(const string &, const string &)

    ...

    if(snake2 != snake3);// operator==(const string &, const string &)


2. 可以确定字符串的长度。size() 和 length() 成员函数都返回字符串中的字符数

   if(snake1.length() == snake2.size())
   {
       cout << "Both string has same length" << endl;
   }

   为什么这两个函数完成相同的任务呢？ length() 成员来自较早版本的 string 类，而 size() 则是为提供 STL 兼容性而添加的

3. 可以以多种不同的方式在字符串中搜索给定的子字符串或字符

    size_type find(const string &str,size_type pos = 0)const ----> 从字符串 pos 位置开始，查找子字符串 str，如果找到则返回字符串首次出现位置
    首字符的索引；否则返回 string::npos;

    size_type find(const char *s,size_type pos = 0)const ----> 从字符串 pos 位置开始，查找子字符串 s，如果找到则返回字符串首次出现位置
    首字符的索引；否则返回 string::npos;

    size_type find(const char *s,size_type pos = 0, size_type n)const ----> 从字符串 pos 位置开始,查找子字符串 s 的前 n 个字符组成的字符串

    size_type find(char ch,size_type pos = 0, size_type n)const ----> 从字符串 pos 位置开始,查找字符 ch 

    string 库还提供了相关的方法： rfind()、find_first_of()、find_last_of()、find_first_not_of()和find_last_not_of()，它们的重载函数特征标都与
    find() 方法相同。rfind() 方法查找子字符串或字符最后一次出现的位置；find_first_of() 方法在字符串中查找参数中任何一个字符首次出现的位置。

    例如，下面的语句返回 r 在 “cobra” 中的位置（即索引3），因为这是 “hark” 中各个字母在 “cobra” 首次出现的位置：

    int where = snake1.find_first_of("hark");


    find_last_of() 方法的功能与此相同，只是它查找的是最后一次出现的位置。因此，下面的语句返回 a 在“cobra”中的位置:

    int where = snake1.find_last_of("hark");

    find_first_not_of() 方法在字符串中查找第一个不包含在参数中的字符，因此下面的语句返回 c 在 “cobra” 中的位置，因为 “hark” 中没有 c

    int where = snake1.find_first_not_of("hark")；

还有很多其他的方法，这些方法足以创建一个非图形版本的 Hangman 拼字游戏。'该游戏将一系列的单词存储在一个 string 对象数组中，然后随机选择一个单词，让人猜测单
词的字母'。如果猜错 6 次，玩家就输了。该程序使用 find() 函数来检查玩家的猜测，使用 += 运算符创建一个 string 对象来记录玩家的错误猜测。为记录玩家猜对的情况
，程序创建了一个单词，其长度与被猜的单词相同，但包含的是连字符。玩家猜对字符时，将用该字符替换相应的连字符。

