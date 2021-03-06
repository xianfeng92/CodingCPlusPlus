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

'STL 提供了一组表示容器、迭代器、函数对象和算法的模板'。

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



// !! 可对矢量执行的操作

除分配存储空间外， vector 模板还可以完成哪些任务呢 ？

1. 所有的STL容器都提供了一些基本方法，其中包括 size()---返回容器中元素数目

2. swap()---交换两个容器的内容

3. begin()----返回一个指向容器中第一个元素的迭代器、end()---返回一个表示超过容器尾的迭代器


'什么是迭代器？'

它是一个广义指针。事实上，它可以是指针，也可以是一个可对其执行类似指针的操作---如解除引用(如operator*())和递增(如 operator++())---的对象。稍后将知道，'通
过将指针广义化为迭代器，让 STL 能够为各种不同的容器类(包括那些简单指针无法处理的类)提供统一的接口'。每个容器类都定义了一个合适的迭代器，该迭代器的类型是一个名为 
iterator 的 typedef，其作用域为整个类。例如，要为 vector 的 double 类型规范声明一个迭代器, 可以这样做:

vector<double>::iterator pd;// pd an iterator

假设 scores 是一个 vector<double> 对象:

vector<double> scores;

则可以使用迭代器 pd 执行这样的操作:

pd = scores.begin();
*pd = 22;
++pd;


正如您看到的，迭代器的行为就像指针。顺便说一句，还有一个 C++11 自动类型推断很有用的地方。例如，可以不这样做:

vector<double>::iterator pd = scores.begin();

而这样做:

auto pd = scores.begin();


'什么是超过结尾(past-the-end)呢'？

它是一种迭代器，指向容器最后一个元素后面的那个元素。这与C-风格字符串最后一个字符后面的空字符类似，只是空字符是一个值，而“超过结尾”是一个指向元素的指针
(迭代器)。end() 成员函数标识超过结尾的位置。如果将迭代器设置为容器的第一个元素，并不断地递增，则最终它将到达容器结尾，从而遍历整个容器的内容。因此，如果
scores 和 pd 的定义与前面的示例中相同，则可以用下面的代码来显示容器的内容:

for(pd = scores.begin(); pd != scores.end(); ++pd) 
{
    cout << *pd << endl;
}

vector 模板类也包含一些只有某些 STL 容器才有的方法。

1. push_back() 是一个方便的方法，它将元素添加到矢量末尾。这样做时，它将负责内存管理，增加矢量的长度, 使之能够容纳新的成员。这意味着可以编写这样的代码:

    vector<double> scores;
    double temp;
    while (cin >> temp && temp >= 0)
    {
        scores.push_back(temp);
    }

    每次循环都给 scores 对象增加一个元素。在编写或运行程序时，无需了解元素的数目。'只要能够取得足够的内存，程序就可以根据需要增加 scores 的长度'。

2. erase() 方法删除矢量中给定区间的元素。它接受两个迭代器参数，这些参数定义了要删除的区间。了解 STL 如何使用两个迭代器来定义区间至关重要。第一个迭代器指向区
   间的起始处，第二个迭代器位于区间终止处的后一个位置。

   例如，下述代码删除第一个和第二个元素，即删除 begin() 和 begin()+1 指向的元素(由于vector提供了随机访问功能，因此 vector 类迭代器定义了诸如 begin()+2
   等操作):

   scores.erase(scores.begin(), scores.begin() + 2);

   如果 it1 和 it2 是迭代器，则 STL 文档使用 [p1, p2) 来表示从 p1 到 p2(不包括 p2)的区间。

3. insert() 方法的功能与 erase() 相反。它接受 3 个迭代器参数，第一个参数指定了新元素的插入位置，第二个和第三个迭代器参数定义了被插入区间，该区间通常是另一个
   容器对象的一部分。例如，下面的代码将矢量 new_v 中除第一个元素外的所有元素插入到 old_v 矢量的第一个元素前面:

   vector<int> old_v;
   vector<int> new_v;
   .....
   old_v.insert(old_v.begin(), new_v.begin()+1, old_v.end());

顺便说一句，对于这种情况，拥有超尾元素是非常方便的，因为这使得在矢量尾部附加元素非常简单。

下面的代码将新元素插入到 old.end() 前面，即矢量最后一个元素的后面。

old_v.insert(old_v.end(),new_v.begin()+1,new_v.end());


// !! 对矢量可执行的其他操作

程序员通常要对数组执行很多操作，如搜索、排序、随机排序等。矢量模板类包含了执行这些常见的操作的方法吗 ？

没有！ STL 从更广泛的角度定义了非成员(non-member) 函数来执行这些操作，即不是为每个容器类定义 find() 成员函数，而是定义了一个适用于所有容器类的非成员函
数 find()。'这种设计理念省去了大量重复的工作'。

例如，假设有 8 个容器类，需要支持 10 种操作。如果每个类都有自己的成员函数，则需要定义 80(8*10) 个成员函数。但采用 STL 方式时，只需要定义 10 个非成员函数即可。
在定义新的容器类时，只要遵循正确的指导思想，则它也可以使用已有的 10 个非成员函数来执行查找、排序等操作。

另一方面，'即使有执行相同任务的非成员函数，STL 有时也会定义一个成员函数'。这是因为对有些操作来说，类特定算法的效率比通用算法高，因此，vector 的成员函数 swap()
的效率比非成员函数 swap() 高，但非成员函数让您能够交换两个类型不同的容器的内容。

下面来看 3 个具有代表性的 STL 函数: for_each()、random_shuffle()和 sort()。

1. for_each() 函数可用于很多容器类，它接受 3 个参数。前两个是定义容器中区间的迭代器，最后一个是指向函数的指针。for_each() 函数将被指向的函数应用于容器区间
中的各个元素。被指向的函数不能修改容器元素的值。可以用 for_each() 函数来代替 for 循环。例如，可以将代码:

vector<Review> books;
for(pr = books.begin(); pr != books.end(); pr++)
{
    ShowReview(*pr);
}

替换为：

for_each(books.begin(), books.end(),ShowReview);

这样可避免显式地使用迭代器变量。

2. Random_shuffle() 函数接受两个指定区间的迭代器参数，并随机排列该区间中的元素。例如，下面的语句随机排列 books 矢量中所有元素:

Random_shuffle(books.begin(), books.end());


与可用于任何容器类的 for_each 不同，该函数要求容器类允许随机访问，vector 类可以做到这一点。


3. sort() 函数也要求容器支持随机访问。该函数有两个版本，第一个版本接受两个定义区间的迭代器参数，并使用为存储在容器中的类型元素定义的 < 运算符，对区间中的
元素进行操作。例如，下面的语句按升序对 coolstuff 的内容进行排序，排序时使用内置的 < 运算符对值进行比较:

vector<int> coolstuff;
...
sort(coolstuff.begin(), coolstuff.end());

'如果容器元素是用户定义的对象，则要使用 sort()，必须定义能够处理该类型对象的 operator<() 函数'。

例如，如果为 Review 提供了成员或非成员函数 operator<()，则可以对包含 Review 对象的矢量进行排序。由于 Review 是一个结构，因此其成员是公有的，这样的非成
员函数将为:

bool operator<(const Review & r1, const Review & r2)
{
    if(r1.title < r2.title)
    {
        return true;
    }
    else if(r1.title == r2.title && r1.rating < r2.rating)
    {
        return true;
    }
    else
    {
        return false;
    }
}


有了这样的函数后，就可以对包含 Review 对象(如books)的矢量进行排序了:

sort(books.begin(), books.end());


// !! 基于范围的for循环（C++11）

基于范围的 for 循环是为用于 STL 而设计的。

for_each(books.begin(), books.end(),showReview);

可将其替换为下述基于范围的 for 循环:

for(auto x : books)
{
    showReview(x);
}

根据 book 的类型(vector<Review>)，编译器将推断出 x 的类型为 Review，而循环将依次将 books 中的每个 Review 对象传递给 showReview()。


// !! 泛型编程

有了一些使用 STL 的经验后，来看一看底层理念。STL 是一种泛型编程(generic programming)。'面向对象编程关注的是编程的数据方面，而泛型编程关注的是算法'。它们之间
的共同点是抽象和创建可重用代码，但它们的理念绝然不同。

泛型编程旨在编写独立于数据类型的代码。在 C++ 中，完成通用程序的工具是模板。'模板使得能够按泛型定义函数或类，而 STL 通过通用算法更进了一步'。


// !! 为何使用迭代器

'理解迭代器是理解 STL 的关键所在'。模板使得算法独立于存储的数据类型, 而迭代器使算法独立于使用的容器类型。因此，它们都是 STL 通用方法的重要组成部分。

为了解为何需要迭代器，我们来看如何为两种不同数据表示实现 find 函数，然后来看如何推广这种方法。

首先看一个在 double 数组中搜索特定值的函数，可以这样编写该函数:

double * find_ar(double *ar, int n, const double &val)
{
    for(int i = 0; i < n; i++)
    {
        if(ar[i] == val)
        {
            return &ar[i];
        }
    }
    return 0;// or in c++11 nullptr
}


如果函数在数组中找到这样的值，则返回该值在数组中的地址, 否则返回一个空指针。该函数使用下标来遍历数组。'可以用模板将这种算法推广到包含 == 运算符的、任意类型的数组'。
尽管如此，这种算法仍然与一种特定的数据结构(数组)关联在一起。

下面来看搜索另一种数据结构——链表的情况。链表由链接在一起的 Node 结构组成:

struct Node 
{
    double item;
    Node *p_next;
};


假设有一个指向链表第一个节点的指针，每个节点的 p_next 指针都指向下一个节点，链表最后一个节点的 p_next 指针被设置为 0，则可以这样编写 find_ll() 函数:

Node * find_ll(Node *head, const double &val)
{
    Node *start;
    for(start = head; start != 0; start = start->p_next)
    {
        if(start->item == val)
        {
            return start;
        }
    }
    return 0;
}

同样，'也可以使用模板将这种算法推广到支持 == 运算符的任何数据类型的链表'。然而，这种算法也是与特定的数据结构---链表关联在一起。

从实现细节上看，这两个 find 函数的算法是不同的:'一个使用数组索引来遍历元素，另一个则将 start 重置为 start->p_next'。但从广义上说，这两种算法是相同的:将值
依次与容器中的每个值进行比较，直到找到匹配的为止。

'泛型编程旨在使用同一个 find 函数来处理数组、链表或任何其他容器类型'。'即函数不仅独立于容器中存储的数据类型，而且独立于容器本身的数据结构'。'模板提供了存储在容
器中的数据类型的通用表示', 因此还需要'遍历容器中的值的通用表示,迭代器正是这样的通用表示'。


要实现 find 函数，迭代器应具备哪些特征呢？下面是一个简短的列表。

1. 应能够对迭代器执行解除引用的操作，以便能够访问它引用的值。即如果 p 是一个迭代器，则应对 *p 进行定义

2. 应能够将一个迭代器赋给另一个。即如果 p 和 q 都是迭代器，则应对表达式 p = q 进行定义

3. 应能够将一个迭代器与另一个进行比较，看它们是否相等。即如果 p 和 q 都是迭代器，则应对p == q和p != q进行定义

4. 应能够使用迭代器遍历容器中的所有元素，这可以通过为迭代器 p 定义 ++p 和 p++ 来实现

迭代器也可以完成其他的操作，但有上述功能就足够了，至少对 find 函数是如此。实际上，STL 按功能的强弱定义了多种级别的迭代器。'顺便说一句，常规指针
就能满足迭代器的要求'，因此，可以这样重新编写 find_arr() 函数:

typedef double * iterator;

iterator find_ar(iterator ar,int n,const double &val)
{
    for(int i = 0; i < n; i++)
    {
        if(*ar == val)
        {
            return ar;
        }
    }
    return 0;
}

然后可以修改函数参数，使之接受两个指示区间的指针参数，其中的一个指向数组的起始位置，另一个指向数组的超尾; 同时函数可以通过返回尾指针, 来指出没有找到要找的值。
下面的 find_ar() 版本完成了这些修改:

typedef double * iterator;
iterator find_ar(iterator begin, iterator end, const double &val)
{
    iterator ar;
    for(ar = begin; ar != end; ar++)
    {
        if(*ar == val)
        {
            return ar;
        }
    }
    return end;// indicate val not find
}


对于 find_ll() 函数，可以定义一个迭代器类，其中定义了运算符 * 和 ++:

struct Node
{
    double item;
    Node *p_next;
};

class iterator
{
    Node *pr;

public:
    iterator(): pr(0){}
    iterator(Node *p): pr(p) {}
    double operator*(){return pr->item;}
    iterator operator++(int)
    {
        iterator tmp = *this;
        pr = pr->next;
        return tmp;
    }
    // ... 
    operator==()
    operator!=()
    
};

为区分 ++ 运算符的前缀版本和后缀版本，C++ 将 operator++ 作为前缀版本，将 operator++(int) 作为后缀版本; 其中的参数永远也不会被用到，所以不必指定
其名称。这里重点不是如何定义 iterator 类，而是有了这样的类后，第二个 find 函数就可以这样编写:

iterator find_ll(iterator head, const double &val)
{
    iterator start;
    for(start = head; start != 0; start++)
    {
        if(*start == val)
        {
            return start；
        }
    }
    return 0;
}

这和 find_ar() 几乎相同，差别在于如何表达已到达最后一个值。'可以要求链表的最后一个元素后面还有一个额外的元素，即让数组和链表都有超尾元素，并在迭代器到达超
尾位置时结束搜索'。这样，find_ar() 和 find_ll() 检测数据尾的方式将相同，从而成为相同的算法。注意,增加超尾元素后，对迭代器的要求变成了对容器类的要求。

STL 遵循上面介绍的方法。首先，每个容器类(vector、list、deque 等)定义了相应的迭代器类型。对于其中的某个类，迭代器可能是指针; 而对于另一个类，则可能是对象。
'不管实现方式如何，迭代器都将提供所需的操作，如 * 和 ++(有些类需要的操作可能比其他类多)'。其次，每个容器类都有一个超尾标记，当迭代器递增到超越容器的最后一个值后
，这个值将被赋给迭代器。。每个容器类都有 begin() 和 end() 方法，它们分别返回一个指向容器的第一个元素和超尾位置的迭代器。每个容器类都使用 ++ 操作，让迭代器从指
向第一个元素逐步指向超尾位置，从而遍历容器中的每一个元素。

使用容器类时，无需知道其迭代器是如何实现的，也无需知道超尾是如何实现的，而只需知道它有迭代器，其 begin() 返回一个指向第一个元素的迭代器，end() 返回一个指向超尾
位置的迭代器即可。例如，假设要打印 vector<double> 对象中的值，则可以这样做:

vector<double>::iterator pd;
for(pd = scores.begin(); pd != scores.end(); pd++)
{
    cout << *pd << endl;
}

其中，下面的代码行将 pr 的类型声明为 vector<double> 类的迭代器:

vector<double>::iterator pd;
for(pd = scores.begin(); pd != scores.end(); pd++)
{
    cout << *pd << endl;
}

如果要使用 list<double> 类模板来存储分数，则代码如下：

list<double>::iterator pd;
for(pd = scores.begin(); pd != scores.end(); pd++)
{
    cout << *pd << endl;
}

唯一不同的是 pr 的类型。因此，'STL 通过为每个类定义适当的迭代器，并以统一的风格设计类，能够对内部表示绝然不同的容器，编写相同的代码'。

使用 C++11 新增的自动类型推断可进一步简化: 对于矢量或列表，都可使用如下代码:

for(auto pd = scores.begin(); pd != scores.end(); pd++)
{
    cout << *pd << endl;
}

'实际上，作为一种编程风格，最好避免直接使用迭代器，而应尽可能使用 STL 函数(如for_each())来处理细节'。

也可使用 C++11 新增的基于范围的 for 循环:

for(auto x:scores)
{
    cout << x << endl;
}

'来总结一下 STL 方法'

首先是处理容器的算法, '应尽可能用通用的术语来表达算法, 使之独立于数据类型和容器类型'。为使通用算法能够适用于具体情况，应定义能够满足算法需求的迭代器，并把要求加
到容器设计上。即基于算法的要求, 设计基本迭代器的特征和容器特征。

// !! 迭代器类型

不同的算法对迭代器的要求也不同。

1. 查找算法需要定义 ++ 运算符, 以便迭代器能够遍历整个容器; 它要求能够读取数据，但不要求能够写数据(它只是查看数据，而并不修改数据)

2. 排序算法要求能够随机访问, 以便能够交换两个不相邻的元素。如果 iter 是一个迭代器，则可以通过定义 + 运算符来实现随机访问，这样就可以使用像 iter + 10 这样的
   表达式了。另外, 排序算法要求能够读写数据。

STL 定义了 5 种迭代器， 并根据所需的迭代器类型对算法进行了描述。这 5 种迭代器分别是'输入迭代器、输出迭代器、正向迭代器、双向迭代器和随机访问迭代器'。

例如，find() 的原型与下面类似：

template<class InputIterator, class T> 
InputIterator find(InputIterator first, InputIterator last, const T &val);

这指出，这种算法需要一个输入迭代器。

同样，下面的原型指出排序算法需要一个随机访问迭代器:

template<class RandomAccessIterator, class T> 
void sort(RandomAccessIterator first, RandomAccessIterator last);


对于这 5 种迭代器，都可以执行解除引用操作(即为它们定义了*运算符)，也可进行比较，看其是相等(使用 == 运算符，可能被重载了)还是不相等(使用 != 运算符，可能被重载了
)。如果两个迭代器相同，则对它们执行解除引用操作得到的值将相同。即如果表达式 iter1 == iter2 为真，则下述表达式也为真:

iter1 = iter2;

    is true,then following is always true

*iter1 == *iter2

当然，对于内置运算符和指针来说，情况也是如此。因此，这些要求将指导您如何对迭代器类重载这些运算符。


// !! 输入迭代器

术语"输入"是从程序的角度说的,'来自容器的信息被视为输入', 就像来自键盘的信息对程序来说是输入一样。因此，'输入迭代器可被程序用来读取容器中的信息'。具体地说，对输入
迭代器解引用将使程序能够读取容器中的值, 但不一定能让程序修改值。因此,'需要输入迭代器的算法将不会修改容器中的值'。

输入迭代器必须能够访问容器中所有的值, 这是通过支持 ++ 运算符(前缀格式和后缀格式)来实现的。如果将输入迭代器设置为指向容器中的第一个元素，并不断将其递增，直到到达
超尾位置，则它将依次指向容器中的每一个元素。顺便说一句, 并不能保证输入迭代器第二次遍历容器时, 顺序不变。

另外, 输入迭代器被递增后，也不能保证其先前的值仍然可以被解引用。'基于输入迭代器的任何算法都应当是单通行(single-pass)的，不依赖于前一次遍历时的迭代器值，也不依
赖于本次遍历中前面的迭代器值'。

注意，输入迭代器是单向迭代器，可以递增，但不能倒退。


// !! 输出迭代器

STL 使用术语"输出"来指用于将信息从程序传输给容器的迭代器，因此程序的输出就是容器的输入。输出迭代器与输入迭代器相似，只是解引用让程序能修改容器值, 而不能读取。
也许您会感到奇怪，能够写，却不能读。发送到显示器上的输出就是如此，cout 可以修改发送到显示器的字符流, 却不能读取屏幕上的内容。STL 足够通用，其容器可以表示输出设
备，因此容器也可能如此。另外，如果算法不用读取容器的内容就可以修改它(如通过生成要存储的新值)，则没有理由要求它使用能够读取内容的迭代器。

简而言之，对于单通行、只读算法，可以使用输入迭代器; 而对于单通行、只写算法，则可以使用输出迭代器。

// !! 正向迭代器

与输入迭代器和输出迭代器相似，正向迭代器只使用 ++ 运算符来遍历容器，所以它每次沿容器向前移动一个元素; 然而，与输入和输出迭代器不同的是，它总是按相同的顺序遍历一
系列值。另外, 将正向迭代器递增后，仍然可以对前面的迭代器值解引用(如果保存了它)，并可以得到相同的值。这些特征使得多次通行算法成为可能。

正向迭代器既可以使得能够读取和修改数据，也可以使得只能读取数据:

int *ptr;// read-write interator
const int *ptr2;// read-only interator


// !! 双向迭代器

假设算法需要能够双向遍历容器，情况将如何呢 ？

例如，reverse 函数可以交换第一个元素和最后一个元素、将指向第一个元素的指针加 1、将指向第二个元素的指针减 1，并重复这种处理过程。双向迭代器具有正向迭代器的所有
特性，同时支持两种(前缀和后缀)递减运算符。

// !! 随机访问迭代器

'有些算法(标准排序和二分检索)要求能够直接跳到容器中的任何一个元素，这叫做随机访问，需要随机访问迭代器'。随机访问迭代器具有双向迭代器的所有特性，同时添加了支持随机
访问的操作(如指针增加运算)和用于对元素进行排序的关系运算符。


// !! 迭代器层次结构

您可能已经注意到, 迭代器类型形成了一个层次结构。正向迭代器具有输入迭代器和输出迭代器的全部功能，同时还有自己的功能; 双向迭代器具有正向迭代器的全部功能，同时还有
自己的功能; 随机访问迭代器具有正向迭代器的全部功能，同时还有自己的功能。

根据特定迭代器类型编写的算法可以使用该种迭代器, 也可以使用具有所需功能的任何其他迭代器。所以具有随机访问迭代器的容器可以使用为输入迭代器编写的算法。

为何需要这么多迭代器呢？

'目的是为了在编写算法尽可能使用要求最低的迭代器，并让它适用于容器的最大区间'。这样，通过使用级别最低的输入迭代器，find() 函数便可用于任何包含可读取值的容器。而 
sort() 函数由于需要随机访问迭代器，所以只能用于支持这种迭代器的容器。

各种迭代器的类型并不是确定的, 而只是一种概念性描述。正如前面指出的，每个容器类都定义了一个类级 typedef 名称--iterator，因此 'vector<int> 类的迭代器类型为 
vector<int>::interator, 矢量迭代器是随机访问迭代器，它允许使用基于任何迭代器类型的算法'，因为随机访问迭代器具有所有迭代器的功能。同样，'list<int> 类的迭代器
类型为 list<int>::iterator。STL 实现了一个双向链表，它使用双向迭代器'，因此不能使用基于随机访问迭代器的算法，但可以使用基于要求较低的迭代器的算法。


// !!  概念、改进和模型

STL 有若干个用 C++ 语言无法表达的特性，如迭代器种类。因此，虽然可以设计具有正向迭代器特征的类，但不能让编译器将算法限制为只使用这个类。原因在于，'正向迭代器是一系
列要求，而不是类型'。所设计的迭代器类可以满足这种要求, 常规指针也能满足这种要求。STL 算法可以使用任何满足其要求的迭代器实现。'STL 文献使用术语概念(concept)来描
述一系列的要求'。因此，存在输入迭代器概念、正向迭代器概念，等等。'顺便说一句，如果所设计的容器类需要迭代器，可考虑 STL，它包含用于标准种类的迭代器模板'。

概念可以具有类似继承的关系。例如，双向迭代器继承了正向迭代器的功能。然而，不能将 C++ 继承机制用于迭代器。例如，可以将正向迭代器实现为一个类，而将双向迭代器实现为
一个常规指针。因此，对 C++ 而言，这种双向迭代器是一种内置类型，不能从类派生而来。然而，从概念上看，它确实能够继承。有些 STL 文献使用术语改进(refinement)来表示
这种概念上的继承，因此, 双向迭代器是对正向迭代器概念的一种改进。

概念(concept)的具体实现被称为模型(model)。因此，'指向 int 的常规指针是一个随机访问迭代器模型，也是一个正向迭代器模型，因为它满足该概念的所有要求'。

// !! 将指针用作迭代器

'迭代器是广义指针，而指针满足所有的迭代器要求'。迭代器是 STL 算法的接口，而指针是迭代器，因此 'STL 算法可以使用指针来对基于指针的非 STL 容器进行操作'。例如，可
将 STL 算法用于数组。假设 Receipts 是一个 double 数组，并要按升序对它进行排序:

const int SIZE = 100;
double Receipts[SIZE];

STL sort() 函数接受指向容器第一个元素的迭代器和指向超尾的迭代器作为参数。&Receipts[0](或 Receipts)是第一个元素的地址，&Receipts[SIZE](Receipts + SIZE)
是数组最后一个元素后面的元素的地址。因此，下面的函数调用对数组进行排序:

sort(Receipts, Receipts+SIZE)；

C++ 确保了表达式 Receipts + n 是被定义的，只要该表达式的结果位于数组中。因此, C++ 支持将超尾概念用于数组，使得可以将 STL 算法用于常规数组。'由于指针是迭代器，
而算法是基于迭代器的，这使得可将 STL 算法用于常规数组'。同样，可以将 STL 算法用于自己设计的数组形式, 只要提供适当的迭代器(可以是指针，也可以是对象)和超尾指示器即
可。

// !! copy()、ostream_iterator 和 istream_iterator

STL 提供了一些预定义迭代器。为了解其中的原因，这里先介绍一些背景知识。有一种算法(名为 copy())可以将数据从一个容器复制到另一个容器中。这种算法是以迭代器方式实现
的，所以它可以从一种容器到另一种容器进行复制，甚至可以在数组之间复制，因为可以将指向数组的指针用作迭代器。例如，下面的代码将一个数组复制到一个矢量中:

int casts[10] = {0,1,2,3,4,5,6,7,8,9};
vector<int> dice(10);
copy(casts, casts+10, dice.begin());// copy array to vector

copy() 前两个迭代器参数表示要复制的范围, 最后一个迭代器参数表示要将第一个元素复制到什么位置。前两个参数必须是(或最好是)输入迭代器，最后一个参数必须是(或最好是)
输出迭代器。copy() 函数将覆盖目标容器中已有的数据, 同时目标容器必须足够大，以便能够容纳被复制的元素。


现在，假设要将信息复制到显示器上。如果有一个表示输出流的迭代器, 则可以使用 copy()。STL 为这种迭代器提供了 ostream_iterator 模板。用 STL 的话说，该模板是输
出迭代器概念的一个模型, 它也是一个适配器(adapter)--一个类或函数，可以将一些其他接口转换为 STL 使用的接口。可以通过包含头文件 iterator 并作下面的声明来创建这
种迭代器:

#include<iterator>
...
ostream_iterator<int, char> out_iter(cout, " ");

out_iter 迭代器现在是一个接口，让您能够使用 cout 来显示信息。第一个模板参数(为 int)指出了被发送给输出流的数据类型; 第二个模板参数(为 char)指出了输出
流使用的字符类型(另一个可能的值是 wchar_t)。构造函数的第一个参数(为 cout)指出了要使用的输出流，它也可以是用于文件输出的流; 最后一个字符串参数是在发送给输出
流的每个数据项后显示的分隔符。

可以这样使用迭代器：

*out_iter++ = 15;// works like cout << 15 << " "

对于常规指针，这意味着将 15 赋给指针指向的位置，然后将指针加 1。但对于该 ostream_iterator，这意味着将 15 和由空格组成的字符串发送到 cout 管理的输出流中，并为
下一个输出操作做好了准备。可以将 copy() 用于迭代器，如下所示:

ostream_iterator<int, char> out_iter(cout, " ");
copy(dice.begin(), dice.end(), out_iter);// copy vector to output stream

这意味着将 dice 容器的整个区间复制到输出流中, 即显示容器的内容。

也可以不创建命名的迭代器，而直接构建一个匿名迭代器。即可以这样使用适配器:

copy(dice.begin(), dice.end(), ostream_iterator<int, char>(cout, " "));


iterator 头文件还定义了一个 istream_iterator 模板，使 istream 输入可用作迭代器接口。它是一个输入迭代器概念的模型，可以使用两个 istream_iterator 对象来
定义 copy() 的输入范围:

copy(instream_iterator<int, char>(cin), instream_iterator<int, char>(), dice.begin());

istream_iterator 也使用两个模板参数。第一个参数指出要读取的数据类型，第二个参数指出输入流使用的字符类型。使用构造函数参数 cin 意味着使用由 cin 管理的输入流，
省略构造函数参数表示输入失败，因此上述代码从输入流中读取，直到文件结尾、类型不匹配或出现其他输入故障为止。


// !! 其他有用的迭代器

除了 ostream_iterator 和 istream_iterator 之外，头文件 iterator 还提供了其他一些专用的预定义迭代器类型。它们是 reverse_iterator、back_insert_iterator
front_insert_iterator 和 insert_iterator。

我们先来看 reverse -iterator 的功能。对 reverse_iterator 执行递增操作将导致它被递减。为什么不直接对常规迭代器进行递减呢？主要原因是为了简化对已有的函数的使
用。假设要显示 dice 容器的内容，正如刚才介绍的，可以使用 copy() 和 ostream_iterator 来将内容复制到输出流中:

ostream_iterator<int, char> out_iter(cout, " ");
copy(dice.begin(), dice.end(), out_iter);// display in forward order

现在假设要反向打印容器的内容。vector 类有一个名为 rbegin() 的成员函数和一个名为 rend()的成员函数，前者返回一个指向超尾的反向迭代器，后者返回一个指向第一个元素
的反向迭代器。因为对迭代器执行递增操作将导致它被递减，所以可以使用下面的语句来反向显示内容:

ostream_iterator<int, char> out_iter(cout, " ");
copy(dice.rbegin(), dice.rend(), out_iter);// display in reverse order

甚至不必声明反向迭代器。

必须对反向指针做一种特殊补偿。假设 rp 是一个被初始化为 dice.rbegin() 的反转指针。那么 *rp 是什么呢？ 因为 rbegin() 返回超尾，因此不能对该地址进行解引用。
同样，如果 rend() 是第一个元素的位置, 则 copy() 必须提早一个位置停止，因为区间的结尾处不包括在区间中。

'反向指针通过先递减，再解除引用解决了这两个问题'。即 *rp 将在 *rp 的当前值之前对迭代器执行解除引用。也就是说，如果 rp 指向位置 6，则 *rp 将是位置5的值，依次
类推。

#include<iostream>
#include<vector>
#include<iterator>

int main()
{
    using namespace std;

    int casts[10] = {0,1,2,3,4,5,6,7,8,9};
    vector<int> dice(10);
    // copy from array to vector
    copy(casts, casts+10, dice.begin());

    cout << "Let the dice be cast!\n";
    // create an ostream_iterator
    ostream_iterator<int, char> out_iter(cout, " ");
    // copy from vector to ostream_iterator
    copy(dice.begin(), dice.end(), out_iter);

    cout << endl;
    cout << "Implicit use of reverse iterator\n";
    copy(dice.rbegin(), dice.rend(), out_iter);

    cout << endl;

    cout << "Explicit use of reverse iterator\n";
    vector<int>::reverse_iterator ri;
    for(ri = dice.rbegin(); ri != dice.rend(); ++ri)
    {
        cout << *ri << endl;
    }
    cout << endl;
    return 0;
}



// !! 容器种类

STL 具有容器概念和容器类型。'概念是具有名称(如容器、序列容器、关联容器等)的通用类别'; '容器类型是可用于创建具体容器对象的模板'。以前的 11 个容器类型分别
是 deque、list、queue、priority_queue、stack、vector、map、multimap、set、multiset 和 bitset；C++11 新增了 forward_list、unordered_map、
unordered_multimap、unordered_set 和 unordered_multiset，且不将 bitset 视为容器，而将其视为一种独立的类别。

// !! 容器概念

没有与基本容器概念对应的类型，但概念描述了所有容器类都通用的元素。它是一个概念化的抽象基类——说它概念化，是因为容器类并不真正使用继承机制。'换句话说，容器概念指
定了所有 STL 容器类都必须满足的一系列要求'。

1. '容器是存储其他对象的对象'。被存储的对象必须是同一种类型的，它们可以是 OOP 意义上的对象，也可以是内置类型值。存储在容器中的数据为容器所有，这意味着当容器过期
    时，存储在容器中的数据也将过期(然而，如果数据是指针的话，则它指向的数据并不一定过期)。

2.  '不能将任何类型的对象存储在容器中，具体地说，类型必须是可复制构造的和可赋值的'。基本类型满足这些要求; 只要类定义没有将复制构造函数和赋值运算符声明为私有或保
     护的，则也满足这种要求

3. 基本容器不能保证其元素都按特定的顺序存储, 也不能保证元素的顺序不变，但对概念进行改进后，则可以增加这样的保证。


如果复杂度为编译时间，则操作将在编译时执行，执行时间为 0。固定复杂度意味着操作发生在运行阶段，但独立于对象中的元素数目。线性复杂度意味着时间与元素数目成正比。即如
果 a 和 b 都是容器，则 a == b 具有线性复杂度，因为 == 操作必须用于容器中的每个元素。实际上，这是最糟糕的情况。如果两个容器的长度不同，则不需要作任何的单独比较。


复杂度要求是 STL 特征, 虽然实现细节可以隐藏, 但性能规格应公开, 以便程序员能够知道完成特定操作的计算成本。


// !! C++11 新增的容器要求

X u(rv)  ---> 调用移动构造函数后，u 的值与 rv 的原始值相同

X u = rv ---> 作用同X u(rv)

a = rv ---> 调用移动赋值运算符后，u 的值与 rv 的原始值相同

a.cbegin() ---> 返回指向容器第一个元素的 const 迭代器


复制构造和复制赋值以及移动构造和移动赋值之间的差别在于: '复制操作保留源对象，而移动操作可修改源对象，还可能转让所有权，而不做任何复制'。如果源对象是临时的，移
动操作的效率将高于常规复制。


// !! 序列


'可以通过添加要求来改进基本的容器概念'。序列(sequence)是一种重要的改进，因为 7 种 STL 容器类型(deque、C++11 新增的 forward_list、list、queue、
priority_queue、stack 和 vector)都是序列(队列让您能够在队尾添加元素，在队首删除元素。deque 表示的双端队列允许在两端添加和删除元素)。序列概念增加了迭代器至
少是正向迭代器这样的要求，这保证了元素将按特定顺序排列，不会在两次迭代之间发生变化。array 也被归类到序列容器，虽然它并不满足序列的所有要求。

'序列还要求其元素按严格的线性顺序排列'，即存在第一个元素、最后一个元素，除第一个元素和最后一个元素外，每个元素前后都分别有一个元素。数组和链表都是序列，但分支结
构(其中每个节点都指向两个子节点)不是。

因为序列中的元素具有确定的顺序，因此可以执行诸如将值插入特定位置、删除特定区间等操作。

X a(n, t) ---> 声明一个名为 a 的由 n 个 t 值组成的序列

X(n, t)  ---> 创建一个由 n 个 t 值组成的匿名序列

a.insert(p, t) ---> 将 t 插入 p 的前面

a.insert(p, n, t)  ---> 将 n 个 t 插入 p 的前面

a.insert(p, i, j) ---> 将区间 [i，j) 中的元素插入 p 的前面

a.erase(p) ---> 删除 p 指向的元素

a.erase(p, q) ---> 删除区间[p，q)中的元素

a.clear() ---> 等价于 erase(begin(), end())


下面详细介绍这 7 种序列容器类型。

// !! vector

vector 模板是在 vector 头文件中声明的。'简单地说，vector 是数组的一种类表示，它提供了自动内存管理功能，可以动态地改变 vector对象的长度，并随着元素的添加和
删除而增大和缩小'。它提供了对元素的随机访问。在尾部添加和删除元素的时间是固定的，但在头部或中间插入和删除元素的复杂度为线性时间。

除序列外，vector 还是可反转容器(reversible container)概念的模型。这增加了两个类方法 rbegin()和 rend()，前者返回一个指向反转序列的第一个元素的迭代器，后
者返回反转序列的超尾迭代器。因此，如果 dice 是一个 vector<int> 容器，而 Show(int) 是显示一个整数的函数，则下面的代码将首先正向显示 dice 的内容，然后反向
显示：

for_each(dice.begin(), dice.end(),Show);
cout << endl;

for_each(dice.rbegin(), dice.rend(),Show);
cout << endl;

'vector 模板类是最简单的序列类型，除非其他类型的特殊优点能够更好地满足程序的要求，否则应默认使用这种类型'。


// !! deque

deque 模板类(在 deque 头文件中声明) 表示双端队列(double-ended queue)，通常被简称为 deque。在 STL 中，其实现类似于 vector 容器，支持随机访问。主要区别
在于，从 deque 对象的开始位置插入和删除元素的时间是固定的，而不像 vector 中那样是线性时间的。所以，'如果多数操作发生在序列的起始和结尾处，则应考虑使用 deque 
数据结构'。

为实现在 deque 两端执行插入和删除操作的时间为固定的这一目的，deque 对象的设计比 vector 对象更为复杂。因此，尽管二者都提供对元素的随机访问和在序列中部执行线
性时间的插入和删除操作，但 vector 容器执行这些操作时速度要快些。


// !! list

list 模板类(在 list 头文件中声明) 表示双向链表。除了第一个和最后一个元素外，每个元素都与前后的元素相链接，这意味着可以双向遍历链表。list 和 vector 之间关键的
区别在于，list 在链表中任意位置进行插入和删除的时间都是固定的(vector 模板提供了除结尾处外的线性时间的插入和删除，在结尾处，它提供了固定时间的插入和删除)。
因此，'vector 强调的是通过随机访问进行快速访问，而 list 强调的是元素的快速插入和删除'。

insert() 和 splice() 之间的主要区别在于: insert() 将原始区间的副本插入目标地址，而 splice() 则将原始区间移到目标地址。因此，在 one 的内容与 three 合并后
，one为空。splice() 方法执行后，迭代器仍有效。也就是说，如果将迭代器设置为指向 one 中的元素，则在 splice() 将它重新定位到元素 three 后，该迭代器仍然指向相
同的元素。注意，'unique() 只能将相邻的相同值压缩为单个值'。程序执行 three.unique() 后，three 中仍包含不相邻的两个 4 和两个 6。但应用 sort() 后再应用
unique() 时，每个值将只占一个位置。

还有非成员 sort() 函数，但它需要随机访问迭代器。因为快速插入的代价是放弃随机访问功能，所以不能将非成员函数 sort() 用于链表。因此，这个类中包括了一个只能在类中
使用的成员版本。



// !! forward_list（C++11）

'C++11 新增了容器类 forward_list，它实现了单链表'。在这种链表中，每个节点都只链接到下一个节点，而没有链接到前一个节点。因此 forward_list 只需要正向迭代器，
而不需要双向迭代器。因此，不同于 vector 和 list，forward_list 是不可反转的容器。相比于 list，forward_list 更简单、更紧凑，但功能也更少。


// !! queue

'queue 模板类(在头文件 queue 中声明)是一个适配器类'。'queue 模板让底层类(默认为 deque)展示典型的队列接口'。

queue 模板的限制比 deque 更多。它不仅不允许随机访问队列元素，甚至不允许遍历队列。'它把使用限制在定义队列的基本操作上'，可以将元素添加到队尾，从队首删除元素，查
看队首和队尾的值，检查元素数目和测试队列是否为空。


// !! priority_queue

priority_queue 模板类(在 queue 头文件中声明)是另一个适配器类，它支持的操作与 queue 相同。两者之间的主要区别在于，在 priority_queue 中，最大的元素被移到队
首。内部区别在于，默认的底层类是 vector。可以修改用于确定哪个元素放到队首的比较方式，方法是提供一个可选的构造函数参数:

priority_queue<int> pr1;// default version
priority_queue<int> pr2(grater<int>);// using grater<int> to order


// !! stack

与 queue 相似，'stack(在头文件 stack) 也是一个适配器类，它给底层类(默认情况下为 vector)提供了典型的栈接口'。

stack 模板的限制比 vector 更多。它不仅不允许随机访问栈元素，甚至不允许遍历栈。'它把使用限制在定义栈的基本操作上, 即可以将压入推到栈顶、从栈顶弹出元素、
查看栈顶的值、检查元素数目和测试栈是否为空'。


// !! 关联容器

'关联容器(associative container) 是对容器概念的另一个改进'。关联容器将值与键关联在一起，并使用键来查找值。'关联容器的优点在于，它提供了对元素的快速访问'。与序
列相似，关联容器也允许插入新元素，但不能指定元素的插入位置。原因是关联容器通常有用于确定数据放置位置的算法，以便能够快速检索信息。'关联容器通常是使用某种树实现的'。
树是一种数据结构，其根节点链接到一个或两个节点，而这些节点又链接到一个或两个节点，从而形成分支结构。像链表一样，节点使得添加或删除数据项比较简单; 但相对于链表，
树的查找速度更快。

STL 提供了 4 种关联容器 set、multiset、map 和 multimap。前两种是在头文件 set 中定义的，而后两种是在头文件 map 中定义的。

最简单的关联容器是 set，其值类型与键相同，键是唯一的，这意味着集合中不会有多个相同的键。确实，对于 set 来说，值就是键。'multiset 类似于set，只是可能有多个值的
键相同'。例如，如果键和值的类型为 int，则 multiset 对象包含的内容可以是 1、2、2、2、3、5、7、7。

在 map 中，值与键的类型不同，键是唯一的，每个键只对应一个值。multimap 与 map 相似，只是一个键可以与多个值相关联。


// !! set示例

STL set 模拟了多个概念，它是关联集合，可反转，可排序，且键是唯一的，所以不能存储多个相同的值。与 vector 和 list 相似，set 也使用模板参数来指定要存储的值类型：

set<string> A;// a set of string object

第二个模板参数是可选的，可用于指示用来对键进行排序的比较函数或对象。默认情况下，将使用模板 less< >。老式 C++ 实现可能没有提供默认值，因此必须显式指定模板参数:

set<string,less<string> B;

#include<iostream>
#include<set>
#include<algorithm>
#include<iterator>
#include<string>

int main()
{
    using std::cout;
    using std::endl;
    using std::copy;
    using std::ostream_iterator;
    using std::set;
    using std::string;

    const int N = 6;
    string s1[N] = {"buffoon", "thinkers", "for", "heavy", "can", "for"};
    set<string> A(s1,s1+N);
    ostream_iterator<string,char> out(cout, "  ");
    copy(A.begin(),A.end(),out);
    return 0;
}


--------------------------------------------------------------------------------
» ./a.out 
buffoon  can  for  heavy  thinkers


数学为集合定义了一些标准操作，例如，并集包含两个集合合并后的内容。如果两个集合包含相同的值，则这个值将在并集中只出现一次，这是因为键是唯一的。交集包含两个集合都有
的元素。两个集合的差是第一个集合减去两个集合都有的元素。


STL 提供了支持这些操作的算法。它们是通用函数，而不是方法，因此并非只能用于 set 对象。然而，所有 set 对象都自动满足使用这些算法的先决条件，即容器是经过排序的。
set_union() 函数接受 5 个迭代器参数。前两个迭代器定义了第一个集合的区间，接下来的两个定义了第二个集合区间，最后一个迭代器是输出迭代器，指出将结果集合复制到什
么位置。例如，要显示集合 A 和 B 的并集，可以这样做:

set_union(A.begin(), A.end(),B.begin(),B.end(),ostream_iterator<string,char>(cout, " "));

假设要将结果放到集合 C 中，而不是显示它，则最后一个参数应是一个指向 C 的迭代器。显而易见的选择是 C.begin()，但它不管用，原因有两个。首先，关联集合将键看作常量，
所以 C.begin() 返回的迭代器是常量迭代器，不能用作输出迭代器。不直接使用 C.begin() 的第二个原因是，与 copy()相似，set_union() 将覆盖容器中已有的数据，并要
求容器有足够的空间容纳新信息。C 是空的，不能满足这种要求。但前面讨论的模板 insert_iterator 可以解决这两个问题。前面说过，它可以将复制转换为插入。另外，它还模
拟了输出迭代器概念，可以用它将信息写入容器。因此，可以创建一个匿名 insert_iterator，将信息复制给 C。前面说过，其构造函数将容器名称和迭代器作为参数:

set_union(A.begin(), A.end(),B.begin(),B.end(),insert_iterator<set<string>>(C,C.begin()));

两个有用的 set 方法是 lower_bound()和 upper_bound()。方法 lower_bound()将键作为参数并返回一个迭代器，该迭代器指向集合中第一个不小于键参数的成员。同样，
方法 upper_bound() 将键作为参数，并返回一个迭代器，该迭代器指向集合中第一个大于键参数的成员。例如，如果有一个字符串集合，则可以用这些方法获得一个这样的区间，
即包含集合中从“b”到“f”的所有字符串。


// !! multimap 示例

与 set 相似，'multimap 也是可反转的、经过排序的关联容器，但键和值的类型不同，且同一个键可能与多个值相关联'。基本的 multimap 声明使用模板参数指定键的类型和
存储的值类型。例如，下面的声明创建一个 multimap 对象，其中键类型为 int，存储的值类型为 string:

multimap<int, string> codes;

第 3 个模板参数是可选的，指出用于对键进行排序的比较函数或对象。在默认情况下，将使用模板 less< >。

为将信息结合在一起，实际的值类型将键类型和数据类型结合为一对。为此，STL 使用模板类 pair<class T, class U> 将这两种值存储到一个对象中。如果 keytype 是键
类型，而 datatype 是存储的数据类型，则值类型为 pair<const keytype, datatype>。例如，前面声明的 codes 对象的值类型为 pair<const int, string>。

例如，假设要用区号作为键来存储城市名(这恰好与 codes 声明一致，它将键类型声明为 int，数据类型声明为 string)，则一种方法是创建一个 pair，再将它插入:

pair<const int, string> item(123,"hello");
codes.insert(item);

也可使用一条语句创建匿名 pair 对象并将它插入:

codes.insert(pair<const int, string>(123,"hello"));

因为数据项是按键排序的，所以不需要指出插入位置。


对于 pair 对象，可以使用 first 和 second 成员来访问其两个部分了:

pair<const int, string> item(123,"hello");
cout << item.first << item.second << endl;

'如何获得有关 multimap 对象的信息呢'？

成员函数count() 接受键作为参数，并返回具有该键的元素数目。成员函数 lower_bound() 和 upper_bound() 将键作为参数，且工作原理与处理 set 时相同。成员函数
equal_range() 用键作为参数，且返回两个迭代器，它们表示的区间与该键匹配。为返回两个值，该方法将它们封装在一个 pair 对象中，这里 pair 的两个模板参数都是迭代器。


// !! 无序关联容器（C++11）

'无序关联容器是对容器概念的另一种改进'。与关联容器一样，无序关联容器也将值与键关联起来，并使用键来查找值。但底层的差别在于:'关联容器是基于树结构的，而无序关联容器
是基于数据结构哈希表的，这旨在提高添加和删除元素的速度以及查找算法的效率'。有 4 种无序关联容器，它们是 unordered_set、unordered_multiset、unordered_map
和 unordered_multimap。



// !! 函数对象

很多 STL 算法都使用函数对象---也叫函数符(functor)。'函数符是可以以函数方式与 () 结合使用的任意对象'。

这包括函数名、指向函数的指针和重载了()运算符的类对象(即定义了函数 operator()() 的类）。例如，可以像这样定义一个类:

#ifndef A2178979_144D_44E6_93E6_A778A4BF6346
#define A2178979_144D_44E6_93E6_A778A4BF6346

class Linear
{
private:
    double slope;
    double y0;
public:
    Linear(double s1_ = 0, double y_ = 0):slope(s1_), y0(y_) {}
    double operator()(double x) {return x*slope + y0;}
};
#endif /* A2178979_144D_44E6_93E6_A778A4BF6346 */


这样，重载的 () 运算符将使得能够像函数那样使用 Linear 对象:

Linear f1;
Linear f2(2.5,10.0);
double y1 = f1(12.5);
double y2 = f2(0.4);


其中 y1 将使用表达式 0 + 1 * 12.5 来计算，y2 将使用表达式 10.0 + 2.5 * 0.4 来计算。在表达式 y0 + slope * x 中，y0 和 slope 的值来自对象的构造函数，
而 x 的值来自 operator()() 的参数。

还记得函数 for_each 吗？ 它将指定的函数用于区间中的每个成员:

for_each(books.begin(), books.end(),showReview);

通常，第 3 个参数可以是常规函数，也可以是函数符。实际上，这提出了一个问题：如何声明第 3 个参数呢？不能把它声明为函数指针，因为函数指针指定了参数类型。

由于容器可以包含任意类型，所以预先无法知道应使用哪种参数类型。STL 通过使用模板解决了这个问题。for_each 的原型看上去就像这样:

template < class InputIterator, class Function>
Function for_each(InputIterator first, InputIterator last, Function f);

ShowReview() 的原型如下:

void ShowReview(const Review &rr);

这样，标识符 ShowReview 的类型将为 void(*)(const Review &)，这也是赋给模板参数 Function 的类型。'对于不同的函数调用， Function 参数可以表示具有重载的 
() 运算符的类类型'。最终，for_each() 代码将具有一个使用 f() 的表达式。在 ShowReview() 示例中，f 是指向函数的指针，而 f() 调用该函数。如果最后的 for_each()
参数是一个对象，则 f() 将是调用其重载的 () 运算符的对象。

// !! 函数符概念

正如 STL 定义了容器和迭代器的概念一样，它也定义了函数符概念。

1. 生成器(generator)是不用参数就可以调用的函数符

2. 一元函数(unary function)是用一个参数可以调用的函数符

3. 二元函数(binary function)是用两个参数可以调用的函数符

例如，提供给 for_each() 的函数符应当是一元函数，因为它每次用于一个容器元素。

当然，这些概念都有相应的改进版：

1. 返回 bool 值的一元函数是谓词(predicate)

2. 返回 bool 值的二元函数是二元谓词(binary predicate)

一些 STL 函数需要谓词参数或二元谓词参数。

bool worseThan(const Review & r1, const Review & r2);
sort(books.begin(), books.end(),worseThan);

list 模板有一个将谓词作为参数的 remove_if() 成员，该函数将谓词应用于区间中的每个元素，如果谓词返回 true，则删除这些元素。

例如，下面的代码删除链表 scores 中所有大于 100 的元素:

bool tooBig(int n) { return n > 100; }
list<int> scores;
...
scores.remove_if(tooBig);

最后这个例子演示了类函数符适用的地方。假设要删除另一个链表中所有大于 200 的值。如果能将取舍值作为第二个参数传递给 tooBig()，则可以使用不同的值调用该函数，
但谓词只能有一个参数。'如果设计一个 TooBig 类，则可以使用类成员而不是函数参数来传递额外的信息':

#ifndef AA54AFB5_903A_4C1E_A3BC_82D053866997
#define AA54AFB5_903A_4C1E_A3BC_82D053866997
template <typename T>
class TooBig
{
private:
    T cutoff;
public:
    TooBig(const T &t) : cutoff(t){}
    bool operator()(const T &v) {return v > cutoff;}
};

#endif /* AA54AFB5_903A_4C1E_A3BC_82D053866997 */

这里，一个值(V)作为函数参数传递，而第二个参数 (cutoff)是由类构造函数设置的。



// !! 预定义的函数符

STL 定义了多个基本函数符，它们执行诸如将两个值相加、比较两个值是否相等操作。提供这些函数对象是为了支持将函数作为参数的 STL 函数。

例如，考虑函数 transform()。它有两个版本。第一个版本接受 4 个参数，前两个参数是指定容器区间的迭代器，第 3 个参数是指定将结果复制到哪里的迭代器，最后一
个参数是一个函数符，它被应用于区间中的每个元素，生成结果中的新元素。例如，请看下面的代码:

const int LIM = 5;
double arr[LIM] = {1,2,3,4,5};
vector<double> gr8(arr,arr + LIM);
ostream_iterator<double, char> out(cout, " ");
transform(gr8.begin(), gr8.end(),out,sqrt);

上述代码计算每个元素的平方根，并将结果发送到输出流。目标迭代器可以位于原始区间中。例如，将上述示例中的 out 替换为 gr8.begin() 后，新值将覆盖原来的值。
很明显，使用的函数符必须是接受单个参数的函数符。

第 2 种版本使用一个接受两个参数的函数，并将该函数用于两个区间中元素。它用另一个参数（即第 3 个）标识第二个区间的起始位置。例如，如果 m8 是另一个
vector<double> 对象，mean（double，double）返回两个值的平均值，则下面的代码将输出来自 gr8 和 m8 的值的平均值:

transform(gr8.begin(), gr8.end(),m8.begin(),out,mean);

现在假设要将两个数组相加。不能将 +  作为参数，因为对于类型 double 来说，+ 是内置的运算符，而不是函数。可以定义一个将两个数相加的函数，然后使用它:

double add(double x, double y)
{
    return x + y;
}

...
transform(gr8.begin(), gr8.end(),m8.begin(),out,add);

然而，这样必须为每种类型单独定义一个函数。

更好的办法是定义一个模板(STL 已经有一个模板了，这样就不必定义)。'头文件 functional(以前为 function.h)定义了多个模板类函数对象，其中包括 plus< >()'。

可以用 plus<> 类来完成常规的相加运算:

#include<functional>

plus<double> add;// create a plus<double> object
double y = add(1.0,2.3);// using plus<double>::iterator()()

它使得将函数对象作为参数很方便:

transform(gr8.begin(), gr8.end(),m8.begin(),out,plus<double>());

这里，代码没有创建命名的对象，而是用 plus<double> 构造函数构造了一个函数符，以完成相加运算(括号表示调用默认的构造函数，传递给 transform() 的是构造出来
的函数对象)。


'对于所有内置的算术运算符、关系运算符和逻辑运算符，STL 都提供了等价的函数符'。


// !! 自适应函数符和函数适配器

STL 提供了使用这些工具的函数适配器类。例如，假设要将矢量 gr8 的每个元素都增加 2.5 倍，则需要使用接受一个一元函数参数的 transform() 版本，就像前面的例子
那样：

transform(gr8.begin(), gr8.end(),m8.begin(),out,sqrt);

multiplies() 函数符可以执行乘法运行，但它是二元函数。因此需要一个函数适配器，将接受两个参数的函数符转换为接受 1 个参数的函数符。

来看 binder1st。假设有一个自适应二元函数对象 f2()，则可以创建一个 binder1st  对象，该对象与一个将被用作 f2()的第一个参数的特定值(val)相关联:

binder1st(f2,val) f1;

这样，使用单个参数调用 f1(x) 时，返回的值与将 val 作为第一参数、将 f1() 的参数作为第二参数调用 f2() 返回的值相同。'即 f1(x) 等价于 f2(val, x)，只是
前者是一元函数，而不是二元函数'。f2() 函数被适配。同样，仅当 f2() 是一个自适应函数时，这才能实现。


看上去有点麻烦。然而，STL 提供了函数 bind1st()，以简化 binder1st 类的使用。可以问其提供用于构建 binder1st 对象的函数名称和值，它将返回一个这种类型的
对象。例如，要将二元函数 multiplies() 转换为将参数乘以 2.5 的一元函数，则可以这样做:

bind1st(multiplies(),2.5);

因此，将 gr8 中的每个元素与 2.5 相乘，并显示结果的代码如下:

transform(gr8.begin(), gr8.end(),out, bind1st(multiplies(),2.5));


binder2nd 类与此类似，只是将常数赋给第二个参数，而不是第一个参数。

'C++11 提供了函数指针和函数符的替代品----lambda 表达式'


// !! 算法

STL 包含很多处理容器的非成员函数，前面已经介绍过其中的: sort()、copy()、find()、random_shuffle()、set_union()、set_intersection()、
set_difference() 和 transform()。可能已经注意到，它们的总体设计是相同的，'都使用迭代器来标识要处理的数据区间和结果的放置位置'。有些函数还接受一
个函数对象参数, 并使用它来处理数据。


'对于算法函数设计，有两个主要的通用部分'。

1. 首先，它们都'使用模板来提供泛型'

2. 其次，它们都'使用迭代器来提供访问容器中数据的通用表示'

因此，copy() 函数可用于将 double 值存储在数组中的容器、将 string 值存储在链表中的容器，也可用于将用户定义的对象存储在树结构中(如 set 所使用的)
的容器。因为指针是一种特殊的迭代器，所以诸如 copy() 等 STL 函数可用于常规数组。

'统一的容器设计使得不同类型的容器之间具有明显关系'。例如，可以使用 copy()将常规数组中的值复制到 vector 对象中，将 vector 对象中的值复制到 list 对象
中，将 list 对象中的值复制到 set 对象中。可以用 == 来比较不同类型的容器，如 deque 和 vector。之所以能够这样做，是因为容器重载的 == 运算符使用迭代器
来比较内容，因此如果 deque 对象和 vector 对象的内容相同，并且排列顺序也相同，则它们是相等的。


// !!算法组

STL 将算法库分成 4 组:

1. 非修改式序列操作
2. 修改式序列操作
3. 排序和相关操作
4. 通用数字运算

前 3 组在头文件 algorithm 中描述，第 4 组是专用于数值数据的, 有自己的头文件，称为 numeric 。

1. 非修改式序列操作对区间中的每个元素进行操作。这些操作不修改容器的内容。例如，find()和for_each()就属于这一类

2. 修改式序列操作也对区间中的每个元素进行操作。然而，顾名思义，它们可以修改容器的内容。可以修改值，也可以修改值的排列顺序。transform()、
   random_shuffle()和 copy()属于这一类

3. 排序和相关操作包括多个排序函数（包括 sort()）和其他各种函数，包括集合操作

4. 数字操作包括将区间的内容累积、计算两个容器的内部乘积、计算小计、计算相邻对象差的函数。通常，这些都是数组的操作特性，因此 vector 是最有可能使用这些操
   作的容器。


// !! 算法的通用特征

STL 函数使用迭代器和迭代器区间, '从函数原型可知有关迭代器的假设'。例如，copy() 函数的原型如下:

template<class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result);

因为标识符 InputIterator 和 OutputIterator 都是模板参数，所以它们就像 T 和 U 一样。然而，'STL 文档使用模板参数名称来表示参数模型的概念'。因此上述
声明告诉我们，区间参数必须是输入迭代器或更高级别的迭代器，而指示结果存储位置的迭代器必须是输出迭代器或更高级别的迭代器。

'对算法进行分类的方式之一是按结果放置的位置进行分类'。

有些算法就地完成工作, 有些则创建拷贝。

1. sort() 函数完成时，结果被存放在原始数据的位置上，因此，sort() 是就地算法(in-place algorithm)

2. copy() 函数将结果发送到另一个位置，所以它是复制算法(copying algorithm)

transform() 函数可以以这两种方式完成工作。与 copy() 相似，它使用输出迭代器指示结果的存储位置；与 copy() 不同的是，transform() 允许输出迭代器指向
输入区间，因此它可以用计算结果覆盖原来的值。

有些算法有两个版本---就地版本和复制版本。STL 的约定是，复制版本的名称将以 _copy 结尾。复制版本将接受一个额外的输出迭代器参数，该参数指定结果的放置位置。
例如，函数 replace() 的原型如下:

template <class ForwardIterator, class T>
void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value);


它将所有的 old_value 替换为 new_value，这是就地发生的。由于这种算法同时读写容器元素，因此迭代器类型必须是 ForwardIterator 或更高级别的。复制版本的
原型如下:

template <class InputIterator, class OutputIterator, class T>
OutputIterator replace_copy(InputIterator first, InputIterator last, OutputIterator result, const T& old_value, const T& new_value);

在这里，结果被复制到 result 指定的新位置，因此对于指定区间而言，只读输入迭代器足够了。

注意，replace_copy() 的返回类型为 OutputIterator。'对于复制算法，统一的约定是：返回一个迭代器，该迭代器指向复制的最后一个值后面的一个位置'。


'有些函数有这样的版本，即根据将函数应用于容器元素得到的结果来执行操作'。这些版本的名称通常以 _if 结尾。例如，如果将函数用于旧值时，返回的值为 true，则 
replace_if() 将把旧值替换为新的值。下面是该函数的原型:

template <class ForwardIterator, class Predicate, class T>
void replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, const T& new_value);

如前所述，谓词是返回 bool 值的一元函数。

与 InputIterator 一样，Predicate 也是模板参数名称，可以为 T 或 U。'然而，STL 选择用 Predicate 来提醒用户，实参应模拟 Predicate 概念'。

// !! STL 和 string 类

string 类虽然不是 STL 的组成部分，但设计它时考虑到了 STL。例如，它包含 begin()、end()、rbegin() 和 rend()等成员，因此可以使用 STL 接口。
next_permutation() 算法将区间内容转换为下一种排列方式。

#include<iostream>
#include<string>
#include<algorithm>

int main()
{
    using namespace std;
    string letters;
    cout << "Enter a letter grouping(quit to quit): ";
    while (cin >> letters && letters != "quit")
    {
        cout << "premutations of " << letters << endl;
        sort(letters.begin(), letters.end());
        cout << letters << endl;
        while(next_permutation(letters.begin(), letters.end))
        {
            cout << letters << endl;
        }
        cout << "Enter next sequence(quit to quit): ";
    }
    cout << "Done.\n";
    return 0;
}



// !! 函数和容器方法

有时可以选择使用 STL 方法或 STL 函数。'通常方法是更好的选择'。首先，它更适合于特定的容器；其次，作为成员函数，它可以使用模板类的内存管理工具，从而在需要
时调整容器的长度。

例如，假设有一个由数字组成的链表，并要删除链表中某个特定值（例如 4）的所有实例。如果 la 是一个 list<int> 对象，则可以使用链表的 remove() 方法:

la.remove(4);

调用该方法后，链表中所有值为 4 的元素都将被删除，同时链表的长度将被自动调整。

还有一个名为 remove() 的STL算法，它不是由对象调用，而是接受区间参数。因此，如果 lb 是一个 list<int> 对象，则调用该函数的代码如下:

remove(lb.begin(), lb.end(), 4);

然而，由于该 remove() 函数不是成员，因此不能调整链表的长度。它将没被删除的元素放在链表的开始位置，并返回一个指向新的超尾值的迭代器。这样，便可以用该迭代
器来修改容器的长度。例如，可以使用链表的 erase() 方法来删除一个区间，该区间描述了链表中不再需要的部分。

#include<iostream>
#include<list>
#include<algorithm>

void show(int);

const int LIM = 10;

int main()
{
    using namespace std;
    int ar[LIM] = {1,2,3,4,5,6,7,8,9,10};
    list<int> la(ar, ar + LIM);
    list<int> lb(la);

    cout << "Original list content:\n\t";
    for_each(la.begin(), la.end(),show);
    cout << endl;
    la.remove(4);
    cout << "After using remove method:\n\t";
    for_each(la.begin(), la.end(),show);
    cout << endl;
    list<int>::iterator last;
    last = remove(lb.begin(), lb.end(),4);
    cout << "After using remove function:\n";
    cout << "lb:\t";
    for_each(lb.begin(), lb.end(),show);
    cout << endl;
    la.erase(last, lb.end());
    cout << "After using erase method\n";
    cout << "la\t";
    for_each(la.begin(), la.end(),show);
    cout << endl;
    return 0;
}

void show(int v)
{
    std::cout << v << ' ';
}


// !! 使用 STL

'STL 是一个库，其组成部分协同工作。STL 组件是工具，但也是创建其他工具的基本部件'。


假设要编写一个程序，让用户输入单词。希望最后得到一个按输入顺序排列的单词列表、一个按字母顺序排列的单词列表（忽略大小写），并记录每个单词被输入的次数。出于
简化的目的，假设输入中不包含数字和标点符号。

输入和保存单词列表很简单。

vector<string> words;
string input;
while (cin >> input && input != "quit")
{

}

如何得到按字母顺序排列的单词列表呢？

可以使用 sort()，然后使用 unique()，但这种方法将覆盖原始数据，因为 sort() 是就地算法。

有一种更简单的方法，可以避免这种问题：创建一个 set<string> 对象，然后将矢量中的单词复制(使用插入迭代器)到集合中。集合自动对其内容进行排序，因此无须调用
sort()；集合只允许同一个键出现一次，因此无须调用 unique()。

这里要求忽略大小写，处理这种情况的方法之一是使用 transform()而不是 copy()，将矢量中的数据复制到集合中。使用一个转换函数将字符串转换成小写形式。

string & ToLower(string &str)
{
    transform(str.begin(), str.end(),str.begin(),tolower);
    return str;
}

要获得每个单词在输入中出现的次数，可以使用 count() 函数。它将一个区间和一个值作为参数，并返回这个值在区间中出现的次数。

可以使用 vector 对象来提供区间，并使用 set 对象来提供要计算其出现次数的单词列表。即对于集合中的每个词，都计算它在矢量中出现的次数。要将单词与其出现的次数
关联起来，可将单词和计数作为 pair<const string, int> 对象存储在 map 对象中。单词将作为键（只出现一次），计数作为值。这可以通过一个循环来完成：

map<string, int> wordmap;
set<string>::iterator si;
for(si = map.begin(); si != map.end(); si++)
{
    wordmap.insert(pair<string, int>(*si, count(words.begin(), words.end(), *si)));
}


map类有一个有趣的特征：可以用数组表示法（将键用作索引）来访问存储的值。例如，wordmap[“the”]表示与键“the”相关联的值，这里是字符串“the”出现的次数。因
为wordset容器保存了wordmap使用的全部键，所以可以用下面的代码来存储结果，这是一种更具吸引力的方法:


for(si = wordset.begin(); si != wordset.end(); ++si)
{
    wordmap[*si] = count(words.begin(), words.end(), *si);
}


因为 si 指向 wordset 容器中的一个字符串，所以 *si 是一个字符串，可以用作 wordmap 的键。



这里的寓意在于，'使用 STL 时应尽可能减少要编写的代码。STL 通用、灵活的设计将节省大量工作'。另外，STL 设计者就是非常关心效率的算法人员，算法是经过仔细选
择的，并且是内联的。


// !! vector、valarray 和 array

C++ 为何提供三个数组模板 vector、valarray 和 array。这些类是由不同的小组开发的，用于不同的目的。

1. 'vector 模板类是一个容器类和算法系统的一部分'，它支持面向容器的操作，如排序、插入、重新排列、搜索、将数据转移到其他容器中等。

2. valarray 类模板是面向数值计算的，不是 STL 的一部分。例如，它没有 push_back()和 insert()方法，但为很多数学运算提供了一个简单、直观的接口

3. 'array 是为替代内置数组而设计的，它通过提供更好、更安全的接口，让数组更紧凑，效率更高'。Array 表示长度固定的数组，因此不支持 push_back() 和 
    insert()，但提供了多个 STL 方法，包括 begin()、end()、rbegin()和rend()，这使得很容易将 STL 算法用于 array 对象。

例如，假设有如下声明：

vector<double> ved1(10), ved2(10), ved3(10)；
array<double,10> vod1, vod2, vod3;
valarray<double> vad1(10), vad2(10), vad3(10);


同时，假设 ved1、ved2、vod1、vod2、vad1 和 vad2 都有合适的值。要将两个数组中第一个元素的和赋给第三个数组的第一个元素，使用 vector 类时，可以这样
做：

transform(ved1.begin(), ved1.end(),ved2.begin(),ved3.begin(),plus<double>());


对于 array 类，也可以这样做:

transform(vod1.begin(),vod1.end(),vod2.begin(),vod3.begin(),plus<double>());

然而，'valarray 类重载了所有算术运算符，使其能够用于 valarray 对象'，因此您可以这样做:

vad3 = val1 + vad2;// + overload

同样，下面的语句将使 vad3 中每个元素都是 vad1 和 vad2 中相应元素的乘积：

vad3 = vad1 * vad2;// * overload

要将数组中每个元素的值扩大 2.5 倍，STL 方法如下:

transform(vad3.begin(), vad3.end(), vad3.begin(),bind1st(multiplies<double>(),2.5));

valarray 类重载了将 valarray 对象乘以一个值的运算符，还重载了各种组合赋值运算符，因此可以采取下列两种方法之一:

vad3 = vad3 * 2.5; //
vad3 *= 2.5; //


假设您要计算数组中每个元素的自然对数，并将计算结果存储到另一个数组的相应元素中，STL 方法如下：

transform(ved1.begin(),ved2.begin(),ved3.begin(),log);

valarray 类重载了这种数学函数，使之接受一个valarray参数，并返回一个valarray对象，因此您可以这样做：

ved3 = log(ved3);


valarray 类还提供了方法 sum()（计算valarray对象中所有元素的和）、size()（返回元素数）、max()（返回最大的元素值）和 min()（返回最小的元素值）。


正如您看到的，'对于数学运算而言，valarray 类提供了比 vector 更清晰的表示方式，但通用性更低'。

valarray 的接口更简单是否意味着性能更高呢？

在大多数情况下，答案是否定的。简单表示法通常是使用类似于您处理常规数组时使用的循环实现的。

可以将 STL 功能用于 valarray 对象吗？

通过回答这个问题，可以快速地复习一些 STL 原理。假设有一个包含 10 个元素的 valarray<double> 对象：

valarray<double> vad(10);

使用数字填充该数组后，能够将 STL sort() 函数用于该数组吗？

valarray 类没有 begin() 和 end()方法，因此不能将它们用作指定区间的参数：

sort(vad.begin(), vad.end());// No, no begin(), end()

另外，vad 是一个对象，而不是指针，因此不能像处理常规数组那样，使用 vad 和 vad + 10 作为区间参数，即下面的代码不可行:

sort(vad, vad + 10);// No,vad is object no address

可以使用地址运算符：

sort(&vad[0], &vad[10]);// Maybe ?

'但 valarray 没有定义下标超过尾部一个元素的行为'。这并不一定意味着使用 &vadp[10] 不可行。事实上，使用 6 种编译器测试上述代码时，都是可行的；但这确实
意味着可能不可行。为让上述代码不可行，需要一个不太可能出现的条件，如让数组与预留给堆的内存块相邻。然而，如果 3.85 亿元的交易命悬于您的代码，您可能不想冒
代码出现问题的风险。

为解决这种问题，C++11 提供了接受 valarray 对象作为参数的模板函数 begin() 和 end()。因此，您将使用 begin(vad) 而不是 vad.begin。这些函数返回的值
满足 STL 区间需求:

sort(begin(vad), end(vad));// C++ 11 fixed




// !! 模板 initializer_list（C++11）

模板 initializer_list 是 C++11 新增的。您可使用初始化列表语法将 STL 容器初始化为一系列值:


std::vector<double> payments = {11.21,23.4,45.54,67.21};

这将创建一个包含 4 个元素的容器，并使用列表中的 4 个值来初始化这些元素。这之所以可行，是因为容器类现在包含将 initializer_list<T> 作为参数的构造函数。


例如，vector<double> 包含一个将 initializer_list<double> 作为参数的构造函数，因此上述声明与下面的代码等价:


std::vector<double> payments({11.21,23.4,45.54,67.21});


这里显式地将列表指定为构造函数参数。


'除非类要用于处理长度不同的列表, 否则让它提供接受 initializer_list 作为参数的构造函数没有意义'。


#ifndef B18834E3_5536_4B67_8898_500B7914710D
#define B18834E3_5536_4B67_8898_500B7914710D

class Position
{
private:
    int x;
    int y;
    int z;
public:
    Position(int x, int y, int z)::x(x), y(y), z(z){ }
    ...
    // no initializer_list constructor
};

#endif /* B18834E3_5536_4B67_8898_500B7914710D */


// !! 使用 initializer_list

要在代码中使用 initializer_list 对象，必须包含头文件 initializer_list。这个模板类包含成员函数 begin()和end()，您可使用这些函数来访问列表元素
它还包含成员函数 size()，该函数返回元素数。


//!! 总结

'C++ 提供了一组功能强大的库，这些库提供了很多常见编程问题的解决方案以及简化其他问题的工具'。


1. string 类为将字符串作为对象来处理提供了一种方便的方法。string 类提供了自动内存管理功能以及众多处理字符串的方法和函数。例如，这些方法和函数让您能够
   合并字符串，将一个字符串插入另一个字符串中，反转字符串，在字符串中搜索字符或子字符串，以及执行输入和输出操作。

2. 诸如 auto_ptr 以及 C++11 新增的 shared_ptr 和 unique_ptr 等智能指针模板使得管理由 new 分配的内存更容易。如果使用这些智能指针(而不是常规指针)
   来保存 new 返回的地址，则不必在以后使用删除运算符。'智能指针对象过期时，其析构函数将自动调用 delete 运算符'。

3. STL 是一个容器类模板、迭代器类模板、函数对象模板和算法函数模板的集合，它们的设计是一致的，都是基于泛型编程原则的。算法通过使用模板，从而独立于所存储的
   对象的类型；通过使用迭代器接口, 从而独立于容器的类型。'迭代器是广义指针'。

4. STL 使用术语“概念”来描述一组要求。例如，正向迭代器的概念包含这样的要求，即正向迭代器能够被解除引用，以便读写，同时能够被递增。'概念真正的实现方式被称为
   概念的“模型”'。例如，正向迭代器概念可以是常规指针或导航链表的对象。基于其他概念的概念叫作“改进”。例如，双向迭代器是正向迭代器概念的改进。

诸如 vector 和 set 等容器类是容器概念(如容器、序列和关联容器)的模型。STL 定义了多种容器类模板——vector、deque、list、set、multiset、map、multimap
和 bitset；'还定义了适配器类模板 queue、priority_queue 和 stack'; 这些类让底层容器类能够提供适配器类模板名称所建议的特性接口。
'因此，stack 虽然在默认情况下是基于 vector 的，但仍只允许在栈顶进行插入和删除'。

有些算法被表示为容器类方法，但大量算法都被表示为通用的、非成员函数，这是通过将迭代器作为容器和算法之间的接口得以实现的。这种方法的一个优点是：只需一个诸如
for_each() 或 copy()这样的函数，而不必为每种容器提供一个版本；另一个优点是：STL 算法可用于非 STL 容器，如常规数组、string对象、array对象以及您设计
的秉承 STL 迭代器和容器规则的任何类。


5. '容器和算法都是由其提供或需要的迭代器类型表征的'。应当检查容器是否具备支持算法要求的迭代器概念。例如，for_each() 算法使用一个输入迭代器，所有的 STL 
    容器类类型都满足其最低要求；而 sort() 则要求随机访问迭代器，并非所有的容器类都支持这种迭代器。


6. STL 还提供了函数对象(函数符)，函数对象是重载了 () 运算符(即定义了 operator()() 方法) 的类。可以使用函数表示法来调用这种类的对象，同时可以携带额外
   的信息。自适应函数符有 typedef 语句，这种语句标识了函数符的参数类型和返回类型。这些信息可供其他组件（如函数适配器）使用。


'通过表示常用的容器类型，并提供各种使用高效算法实现的常用操作，STL 提供了一个非常好的可重用代码源。可以直接使用 STL 工具来解决编程问题，也可以把它们作为
基本部件，来构建所需的解决方案'。


模板类 complex 和 valarray 支持复数和数组的数值运算。




