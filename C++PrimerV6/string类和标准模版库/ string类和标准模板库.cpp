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

#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<cctype>

using std::string;
const int NUM = 26;
const string worldlist[NUM] = 
{
    "applist","bee","hello","worldlist","Sorry","please","enter","your","name","help",
    "me","get","it","done","see","about","NOT","tiom","shares","Student","shortest",
    "other","full","funny","integer","xforg"
}

int main()
{
    using std::cout;
    using std::endl;
    using std::cin;
    using std::tolower;

    std::srand(std::time(NULL));
    char play;
    cout << "Will you play a word game ?<y/n>\n";
    cin >> play;
    play = tolower(play);
    while(play == 'y')
    {
        string target = worldlist[std::rand() % NUM];
        int length = target.length();
        string attempt(length,'-');
        string badchars;
        int guesses = 6;
        cout << "Guess my secret word. It has " << length << " Letters and your guess\n"
        << "one letter at a time. You get " << guesses << " wrong guesses.\n";
        cout << "your word is " << attempt << endl;
        while(guesses > 0 && attempt != target)
        {
            char letter;
            cout << "Guess a letter: ";
            cin >> letter;
            if(badchars.find(letter) != string::npos || attempt.find(letter) != string::npos)
            {
                cout << "You already guess that, Try Again\n";
                continue;
            }
            int loc = target.find(letter);
            if(loc == string::npos)
            {
                cout << "Oh, bad guess!\n";
                --guesses;
                badchars += letter;// add to string
            }
            else
            {
                cout << "Good guess\n";
                attempt[loc] = letter;
                loc = target.find(letter,loc+1);
                while(loc != string::npos)
                {
                    attempt[loc] =letter;
                    loc = target.find(letter,loc+1);
                }
            }
            cout << "your word is " << attempt << endl;

            if(attempt != target)
            {
                if(badchars.length() > 0)
                {
                    cout << "Bad choice " << badchars << endl;
                }
                cout << "guesses " << guesses << endl;
            }
        }
        if(guesses > 0)
        {
            cout << "That right!\n";
        }
        else
        {
            cout << "sorry the word is " << target << ".\n";
            cout << "Will you play again ?"
            cin >> play;
            play = tolower(play);
        }
    }
    cout << "Bye\n";
    return 0;
}


1. 由于关系运算符被重载，因此可以像对待数值变量那样对待字符串:

    while(guesses > 0 && attempt != target)

    与对C-风格字符串使用 strcmp() 相比，这样简单些。

2. 使用 find() 来检查玩家以前是否猜过某个字符。如果是，则它要么位于 badchars 字符串(猜错)中，要么位于 attempt 字符串(猜对)中：

    if(badchars.find(letter) != string::npos || attempt.find(letter) != string::npos)

    npos 变量是 string 类的静态成员，它的值 string 对象能存储的最大字符数。'由于索引从0开始，所以它比最大的索引值大 1，因此可以使用它来表示没有查找到字符
    或字符串'。

3. 该程序利用了这样一个事实: '+= 运算符的某个重载版本使得能够将一个字符附加到字符串中'

    badchars += letter;



// !!string 还提供了哪些功能

string 库提供了很多其他的工具，包括完成下述功能的函数:

1. 删除字符串的部分或全部内容
2. 用一个字符串的部分或全部内容替换另一个字符串的部分或全部内容
3. 将数据插入到字符串中或删除字符串中的数据
4. 将一个字符串的部分或全部内容与另一个字符串的部分或全部内容进行比较
5. 从字符串中提取子字符串
6. 将一个字符串中的内容复制到另一个字符串中、交换两个字符串的内容


首先来看自动调整大小的功能。在 str2.cpp中，每当程序将一个字母附加到字符串末尾时将发生什么呢？不能仅仅将已有的字符串加大，因为相邻的内存可能被占用了。因此，可
能需要分配一个新的内存块，并将原来的内容复制到新的内存单元中。如果执行大量这样的操作，效率将非常低，因此很多 C++ 实现分配一个比实际字符串大的内存块，为字符串提
供了增大空间。然而，如果字符串不断增大，超过了内存块的大小，程序将分配一个大小为原来两倍的新内存块，以提供足够的增大空间，避免不断地分配新的内存块。
'方法 capacity() 返回当前分配给字符串的内存块的大小，而 reserve() 方法让您能够请求内存块的最小长度'。

str2.cpp 是一个使用这些方法的示例。

#include<iostream>
#include<string>

int main()
{
    using namespace std;
    string empty;
    string small = "bit";
    string large = "Are you OK？ See you later\n";
    cout << "Sizes\n";
    cout << "\tempty " << empty.size() << "\n";
    cout<< "\tsmall " << small.size() << "\n";
    cout <<"\tlarge " << large.size() << "\n";

    cout << "Capacities\n";
    cout << "\tempty " << empty.capacity() << "\n";
    cout<< "\tsmall " << small.capacity() << "\n";
    cout <<"\tlarge " << large.capacity() << "\n";

    empty.reserve(50);
    cout << "Capacities after empty.reserve(50):" << empty.capacity() << "\n";
    return 0;
}

 » g++ --std=c++11 str2.cpp
--------------------------------------------------------------------------------
 » ./a.out hel
Sizes
	empty 0
	small 3
	large 28
Capacities
	empty 15
	small 15
	large 28
Capacities after empty.reserve(50):50

如果您有 string 对象，但需要C-风格字符串，该如何办呢？

例如，您可能想打开一个其名称存储在 string 对象中的文件:

string filename;
cout << "Enter filename\n";
cin >> filename;
ofstream fout;

不幸的是，open() 方法要求使用一个C-风格字符串作为参数；幸运的是，c_str() 方法返回一个指向C-风格字符串的指针，该C-风格字符串的内容与用于调用 c_str() 
方法的 string 对象相同。因此可以这样做:

    fout.open(filename.c_str());


// !! 字符串种类

本节将 string 类看作是基于 char 类型的。事实上，正如前面指出的，string 库实际上是基于一个模板类的:

    template <typename charT,typename traits = char_traits<charT>,typename Allocator = allocator<charT> >

    basic_string{...}

模板 basic_string 有 4 个具体化，每个具体化都有一个 typedef 名称:

typedef basic_string<char> string;
typedef basic_string<wchar_t> wstring;
typedef basic_string<char16_t> u16string;// C++11
typedef basic_string<char32_t> u32string;// C++11

这让您能够使用基于类型 wchar_t、char16_t、char32_t 和 char 的字符串。甚至可以开发某种类似字符的类，并对它使用 basic_string 类模板（只要它满足某些要求）。
traits 类描述关于选定字符类型的特定情况，如如何对值进行比较。对于 wchar_t、char16_t、char32_t 和 char 类型，有预定义的 char_traits 模板具体化，它们
都是 traits 的默认值。Allocator 是一个管理内存分配的类。对于各种字符类型，都有预定义的 allocator 模板具体化，它们都是默认的。它们使用 new 和 delete。


// !! 智能指针模板类

智能指针是行为类似于指针的类对象，但这种对象还有其他功能。


void remodel(std::string &str)
{
    std::string *ps = new std::string(str);
    ...
    str = ps;
    return 0;
}

您可能发现了其中的缺陷。每当调用时，该函数都分配堆中的内存，但从不收回，从而导致内存泄漏。您可能也知道解决之道——只要别忘了在 return 语句前添加下面的语句，
以释放分配的内存即可:

    delete ps;

'但凡涉及“别忘了”的解决方法，很少是最佳的'。因为您有时可能忘了，有时可能记住了，但可能在不经意间删除或注释掉了这些代码。即使确实没有忘记，也可能有问题。

请看下面的变体：

void remodel(std::string &str)
{
    std::string *ps = new std::string(str);
    ...
    if(wire_thing)
    {
        throw exception();
    }
    str = ps;
    delete ps;
    return 0;
}

当出现异常时，delete 将不被执行，因此也将导致内存泄漏。

当 remodel() 这样的函数终止(不管是正常终止，还是由于出现了异常而终止)，本地变量都将从栈内存中删除--因此指针 ps 占据的内存将被释放。如果 ps 指向的内存也被释
放，那该有多好啊。如果 ps 有一个析构函数，该析构函数将在 ps 过期时释放它指向的内存。因此 ps 的问题在于，它只是一个常规指针, 不是有析构函数的类对象。'如果它是
对象，则可以在对象过期时，让它的析构函数删除指向的内存'。这正是 auto_ptr、unique_ptr 和 shared_ptr 背后的思想。模板 auto_ptr 是 C++98 提供的解决方案，
C++11 已将其摒弃，并提供了另外两种解决方案。然而，虽然 auto_ptr 被摒弃，但它已使用了多年；同时，如果您的编译器不支持其他两种解决方案，auto_ptr 将是唯一的选择

// !! 使用智能指针

这三个智能指针模板(auto_ptr、unique_ptr 和 shared_ptr)都定义了类似指针的对象，可以将 new 获得的地址赋给这种对象。当智能指针过期时，其析构函数将使用
delete 来释放内存。因此，如果将 new 返回的地址赋给这些对象, 将无需记住稍后释放这些内存: '在智能指针过期时，这些内存将自动被释放'。


要创建智能指针对象，必须包含头文件 memory，该文件模板定义。

然后使用通常的模板语法来实例化所需类型的指针。例如，模板 auto_ptr 包含如下构造函数：


template<typename T> class auto_ptr
{
    public:
        explicit auto_ptr(int *p = 0) throw();
    ...
};

本书前面说过，throw() 意味着构造函数不会引发异常；与 auto_ptr 一样， throw() 也被摒弃。因此，请求 X 类型的 auto_ptr 将获得一个指向 X 类型的 auto_ptr

auto_ptr<double> ad(new double());
auto_ptr<string> as(new string());

'new double 是 new 返回的指针，指向新分配的内存块'。它是构造函数 auto_ptr<double> 的参数，即对应于原型中形参 p 的实参。同样，new string 也是构造函数的
实参。

其他两种智能指针使用同样的语法:

unique_ptr<double> ud(new double);
shared_ptr<string> ss(new string);


因此，要转换 remodel() 函数，应按下面 3 个步骤进行:

1．包含头文件 memory
2．将指向 string 的指针替换为指向 string 的智能指针对象；
3．删除 delete 语句

#include<memory>
void remodel(std::string &str)
{
    std::unique_ptr<string> ps(new std::string(str));
    ...
    if(wire_thing)
    {
        throw exception();
    }
    str = *ps;
    return 0;
}

注意到智能指针模板位于名称空间 std 中。


smrtptrs.cpp 是一个简单的程序，演示了如何使用全部三种智能指针。要编译该程序，您的编译器必须支持 C++11 新增的类 share_ptr 和 unique_ptr。每个智能指针
都放在一个代码块内，这样离开代码块时，指针将过期。Report类使用方法报告对象的创建和销毁。


所有智能指针类都一个 explicit 构造函数，该构造函数将指针作为参数。因此不能自动将指针转换为智能指针对象:

shared_ptr<double> pd;
double *p_reg = new double();
ps = p_reg;// not allowed(explicit conversion)
ps = shared_ptr<double>(p_reg);// okay

shared_ptr<double> pshare = p_reg;// not allowed(explicit conversion)
shared_ptr<double> pshare(p_reg);// okay


由于智能指针模板类的定义方式， 智能指针对象的很多方面都类似于常规指针。例如，如果 ps 是一个智能指针对象，则可以对它执行解除引用操作（* ps）、用它来访问结构
成员(ps->puffIndex) 将它赋给指向相同类型的常规指针。

但在此之前，先说说对全部三种智能指针都应避免的一点：

string vacation("I want lonely as a cloud");
shared_ptr<string> pvac(vacation); // NO

'pvac 过期时，程序将把 delete 运算符用于非堆内存，这是错误的'。


// !! 有关智能指针的注意事项

为何有三种智能指针呢？实际上有 4 种，但本书不讨论 weak_ptr。为何摒弃 auto_ptr 呢?

先来看下面的赋值语句:

auto_ptr<string> ps(new string("I want to be a string"));
auto_ptr<string> vocation;
vocation = ps;

上述赋值语句将完成什么工作呢？

如果 ps 和 vocation 是常规指针，则两个指针将指向同一个 string 对象。这是不能接受的，因为程序将试图删除同一个对象两次——一次是ps过期时，另一次是vocation过
期时。要避免这种问题，方法有多种。

1. 定义赋值运算符，使之执行深复制。这样两个指针将指向不同的对象，其中的一个对象是另一个对象的副本。

2. 建立所有权(ownership)概念，对于特定的对象，只能有一个智能指针可拥有它，这样只有拥有对象的智能指针的构造函数会删除该对象。然后，让赋值操作转让所有权。这就是
   用于 auto_ptr 和 unique_ptr 的策略，但 unique_ptr 的策略更严格

3. 创建智能更高的指针，跟踪引用特定对象的智能指针数。这称为引用计数(reference counting)。例如，赋值时，计数将加1，而指针过期时，计数将减1。仅当最后一个指针过
   期时，才调用 delete。这是 shared_ptr 采用的策略。

#include<iostream>
#include<memory>
#include<string>

int main()
{
    using namespace std;
    auto_ptr<string> films[5] =
    {
        auto_ptr<string> (new string("following")),
        auto_ptr<string> (new string("nio")),
        auto_ptr<string> (new string("apple")),
        auto_ptr<string> (new string("hell")),
        auto_ptr<string> (new string("funck"))
    };

    auto_ptr<string> pwin;
    pwin = films[2];// films[2] lose ownership
    for(int i = 0; i < 5; i++)
    {
        cout << *films[i] << endl;
    }
    cout << "the winter is " << *pwin << endl;
    return 0;
}

 » ./a.out hel
following
nio
[1]    176168 segmentation fault (core dumped)  ./a.out hel
--------------------------------------------------------------------------------
» 

这里的问题在于，下面的语句将所有权从 films[2] 转让给 pwin:

    pwin = films[2];// films[2] lose ownership


这导致 films[2] 不再引用该字符串。在 auto_ptr 放弃对象的所有权后，便可能使用它来访问该对象。当程序打印 films[2] 指向的字符串时，却发现这是一个空指针，这
显然讨厌的意外。


flow.cpp 中使用 shared_ptr 代替 auto_ptr(这要求编译器支持 C++11 新增的 shared_ptr 类)，则程序将正常运行。

#include<iostream>
#include<memory>
#include<string>

int main()
{
    using namespace std;
    shared_ptr<string> films[5] =
    {
        shared_ptr<string> (new string("following")),
        shared_ptr<string> (new string("nio")),
        shared_ptr<string> (new string("apple")),
        shared_ptr<string> (new string("hell")),
        shared_ptr<string> (new string("funck"))
    };

    shared_ptr<string> pwin;
    pwin = films[2];// films[2] lose ownership
    for(int i = 0; i < 5; i++)
    {
        cout << *films[i] << endl;
    }
    cout << "the winter is " << *pwin << endl;
    return 0;
}

 » g++ --std=c++11 flow_s.cpp 
--------------------------------------------------------------------------------
 » ./a.out hel
following
nio
apple
hell
funck
the winter is apple


'使用 auto_ptr 时，该程序在运行阶段崩溃。如果使用 unique_ptr，结果将如何呢？与 auto_ptr 一样，unique_ptr 也采用所有权模型。但使用 unique_ptr 时，程序
不会等到运行阶段崩溃，而在编译器因下述代码行出现错误'


 » g++ --std=c++11 fowl_u.cpp 
fowl_u.cpp: In function ‘int main()’:
fowl_u.cpp:18:19: error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>& std::unique_ptr<_Tp, _Dp>::operator=
(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = std::__cxx11::basic_string<char>; _Dp = std::default_delete<std::__cxx11::basic_string
<char> >]’
   18 |     pwin = films[2];// films[2] lose ownership
      |                   ^
In file included from /usr/include/c++/9/memory:80,
                 from fowl_u.cpp:2:
/usr/include/c++/9/bits/unique_ptr.h:415:19: note: declared here
  415 |       unique_ptr& operator=(const unique_ptr&) = delete;


// !! unique_ptr 为何优于 auto_ptr

请看下面的语句:

auto_ptr<string> p1(new string("hello"));
auto_ptr<string> p2;
p2 = p1; // #3

在语句 #3 中，p2 接管 string 对象的所有权后，p1 的所有权将被剥夺。前面说过，这是件好事，可防止 p1 和 p2 的析构函数试图删除同一个对象；但如果程序随后试图
使用 p1，这将是件坏事，因为 p1 不再指向有效的数据


下面来看使用 unique_ptr 的情况:

unique_ptr<string> p1(new string("hello"));
unique_ptr<string> p2;
p2 = p1; // #3


编译器认为语句#3非法，避免了 p1 不再指向有效数据的问题。因此，unique_ptr 比 auto_ptr 更安全('编译阶段错误比潜在的程序崩溃更安全')


但有时候，将一个智能指针赋给另一个并不会留下危险的悬挂指针。假设有如下函数定义:

unique_ptr<string> demo(const char *s)
{
    unique_ptr<string> temp(new string(s));
    return temp;
}

并假设编写了如下代码:

unique_ptr<string> ps;
ps = demo("fuckyou");


demo() 返回一个临时 unique_ptr，然后 ps 接管了原本归返回的 unique_ptr 所有的对象，而返回的 unique_ptr 被销毁。这没有问题，因为 ps 拥有了 string
对象的所有权。'这里的另一个好处是 demo() 返回的临时 unique_ptr很快被销毁，没有机会使用它来访问无效的数据'。换句话说，没有理由禁止这种赋值。神奇的是，编译
器确实允许这种赋值！


总之，程序试图将一个 unique_ptr 赋给另一个时，如果源 unique_ptr 是个临时右值，编译器允许这样做; 如果源 unique_ptr 将存在一段时间，编译器将禁止这样做:

using namespace std;
unique_ptr<string> pu1(new string("fuck"));
unique_ptr<string> pu2;
pu2 = pu1;// #1 not allowed
unique_ptr<string> pu3;
pu3 = unique_ptr<string>(new string("you!"));// #2 allowed

语句 #1 将留下悬挂的 unique_ptr（pul），这可能导致危害。语句 #2 不会留下悬挂的 unique_ptr，因为它调用 unique_ptr 的构造函数，该构造函数创建的临时对象
在其所有权转让给 pu 后就会被销毁。

C++ 有一个标准库函数 std::move()，让您能够将一个 unique_ptr 赋给另一个。下面是一个使用前述 demo() 函数的例子，该函数返回一个 unique_ptr<string>对象:

using namespace std;
unique_ptr<string> pu1(new string("fuck"));
unique_ptr<string> pu2;
pu2 = move(pu1);// enable assignment
unique_ptr<string> pu3;


相比于 auto_ptr，unique_ptr 还有另一个优点。它有一个可用于数组的变体。别忘了，必须将 delete 和 new 配对，将 delete[]和 new[] 配对。模板 auto_ptr 
使用 delete 而不是 delete[]，因此只能与 new 一起使用，而不能与 new[] 一起使用。但 unique_ptr 有使用 new[] 和 delete[] 的版本:

    std::unique_ptr<double[]> pda(new double(5));// will use delete[]

警告:

使用 new 分配内存时，才能使用 auto_ptr 和 shared_ptr


// !! 选择智能指针

应使用哪种智能指针呢？

1. 如果程序要使用多个指向同一个对象的指针，应选择 shared_ptr

    这样的情况包括: 有一个指针数组，并使用一些辅助指针来标识特定的元素，如最大的元素和最小的元素; 两个对象包含都指向第三个对象的指针；STL 容器包含指针。
    很多 STL 算法都支持复制和赋值操作，这些操作可用于 shared_ptr，但不能用于 unique_ptr(编译器发出警告)和 auto_ptr(行为不确定)

2. 如果程序不需要多个指向同一个对象的指针，则可使用 unique_ptr

    如果函数使用 new 分配内存，并返回指向该内存的指针，将其返回类型声明为 unique_ptr 是不错的选择。这样，所有权将转让给接受返回值的 unique_ptr，而该智
    能指针将负责调用 delete

    unique_ptr<int> make_int(int n)
    {
        return unique_ptr<int>(new int(n));
    }


    void show(unique_ptr<int> &pi)// pass by reference
    {
        cout << *pa << endl;
    }

    int main()
    {
        ...
        vector<unique_ptr<int>> vp(size);
        for(int i=0; i<vp.size(); i++)
        {
            vp[i] = make_int(rand() % 1000);
            vp.push_back(make_int(rand() % 1000));
            for_each(vp.begin(), vp.end(),show);
        }
    }


其中的 push_back() 调用没有问题，因为它返回一个临时 unique_ptr，该 unique_ptr 被赋给 vp 中的一个 unique_ptr

在 unique_ptr 为右值时，可将其赋给 shared_ptr，这与将一个 unique_ptr 赋给另一个需要满足的条件相同

unique_ptr<int> pup(make_int(rand() % 1000));
shared_ptr<int> sup(pup);// not allowed, pup is left value
shared_ptr<int> sus(make_int(rand() % 1000));// okay

模板 shared_ptr 包含一个显式构造函数，可用于将右值 unique_ptr 转换为 shared_ptr。shared_ptr 将接管原来归 unique_ptr 所有的对象。

如果您的编译器没有提供 unique_ptr，可考虑使用 BOOST 库提供的 scoped_ptr, 它与 unique_ptr 类似


// !! 标准模板库

STL 提供了一组表示容器、迭代器、函数对象和算法的模板。

1. 容器是一个与数组类似的单元, 可以存储若干个值。STL 容器是同质的，即存储的值的类型相同

2. 算法是完成特定任务(如对数组进行排序或在链表中查找特定值)的处方

3. 迭代器能够用来遍历容器的对象，与能够遍历数组的指针类似，是广义指针

4. 函数对象是类似于函数的对象, 可以是类对象或函数指针(包括函数名，因为函数名被用作指针)

'STL 使得能够构造各种容器(包括数组、队列和链表)和执行各种操作（包括搜索、排序和随机排列）'。

STL 不是面向对象的编程，而是一种不同的编程模式---泛型编程(generic programming)。这使得 STL 在功能和方法方面都很有趣。


// !! 模板类 vector

可以创建 vector 对象，将一个 vector 对象赋给另一个对象，使用 [] 运算符来访问 vector 元素。'要使类成为通用的，应将它设计为模板类'，STL 正是这样做的---
在头文件 vector 中定义了一个 vector 模板。

要创建 vector 模板对象，可使用通常的 <type> 表示法来指出要使用的类型。另外，vector 模板使用动态内存分配，因此可以用初始化参数来指出需要多少矢量:

#include <vector>
using namespace std;
vector<int> ratings(5);
int n;
cin>>n;
vector<double> scores(n);

由于运算符 [] 被重载，因此创建 vector 对象后，可以使用通常的数组表示法来访问各个元素:

ratings[0] = 9;
for(int i = 1; i <n ; i++)
{
    cout << scores[i] << endl;
}

分配器

'各种 STL 容器模板都接受一个可选的模板参数, 该参数指定使用哪个分配器对象来管理内存'。例如，vector 模板的开头与下面类似:

template <class T, class Allocator = allocator<T> >
class Vector
{

};

如果省略该模板参数的值, 则容器模板将默认使用 allocator<T> 类。这个类使用 new 和 delete。

