//!! 处理数据

'面向对象编程（OOP）的本质是设计并扩展自己的数据类型'。设计自己的数据类型就是让类型与数据匹配。如果正确做到了这一点，将会发现以后使用数据时会容
易得多。然而，'在创建自己的类型之前，必须了解并理解 C++ 内置的类型，因为这些类型是创建自己类型的基本组件'。内置的 C++ 类型分两组:基本类型和复合类型
。基本类型，即整数和浮点数。似乎只有两种类型，但 C++ 知道，没有任何一种整型和浮点型能够满足所有的编程要求，因此对于这两种数据，它提供了多种变体。


// !! 简单变量

程序通常都需要存储信息—如 Google 股票当前的价格、纽约市 8 月份的平均湿度、美国宪法中使用最多的字母及其相对使用频率或猫王模仿者的数目。为把信息存储
在计算机中，程序必须记录 3 个基本属性:

1. 信息将存储在哪里

2. 要存储什么值

3. 存储何种类型的信息

例如，假设实验室首席助理 Igor 使用了下面的语句:

int braincount;
braincount = 5;

这些语句告诉程序，它正在存储整数，并使用名称 braincount 来表示该整数的值（这里为5）。'实际上，程序将找到一块能够存储整数的内存，将该内存单元标记为
braincount，并将 5 复制到该内存单元中；然后，您可在程序中使用 braincount 来访问该内存单元'。这些语句没有告诉您，这个值将存储在内存的什么位置，但
程序确实记录了这种信息。实际上，可以使用 & 运算符来检索 braincount 的内存地址。

// !! 变量名

C++ 提倡使用有一定含义的变量名。如果变量表示差旅费，应将其命名为 cost_of_trip 或 costOfTrip ，而不要将其命名为 x 或 cot。必须遵循几种简单的
C++ 命名规则:

1. 在名称中只能使用字母字符、数字和下划线

2. 名称的第一个字符不能是数字

3. 区分大写字符与小写字符

4. 不能将 C++ 关键字用作名称

'以两个下划线或下划线和大写字母打头的名称被保留给实现（编译器及其使用的资源）使用。以一个下划线开头的名称被保留给实现，用作全局标识符'。如果想用两
个或更多的单词组成一个名称，通常的做法是用下划线字符将单词分开，如 my_onions 或者从第二个单词开始将每个单词的第一个字母大写，如 myEyeTooth。
（C程序员倾向于按C语言的方式使用下划线，而Pascal程序员喜欢采用大写方式）这两种形式都很容易将单词区分开，如 carDrip 和 cardRip 或 boat_sport 
和 boats_port。

// !! 整型

整数就是没有小数部分的数字，如 2、98、-5286 和 0。整数有很多，如果将无限大的整数看作很大，则不可能用有限的计算机内存来表示所有的整数。因此，语言
只能表示所有整数的一个子集。有些语言只提供一种整型（一种类型满足所有要求！），而 C++ 则提供好几种，这样便能够根据程序的具体要求选择最合适的整型。

'不同 C++ 整型使用不同的内存量来存储整数。使用的内存量越大，可以表示的整数值范围也越大'。另外，有的类型（符号类型）可表示正值和负值，而有的类型
（无符号类型）不能表示负值。术语宽度（width）用于描述存储整数时使用的内存量。使用的内存越多，则越宽。

C++ 的基本整型（按宽度递增的顺序排列）分别是 char、short、int、long 和 C++11 新增的 long long，其中每种类型都有符号版本和无符号版本，因此总
共有 10 种类型可供选择。

1. 整型 short、int、long 和 long long

   计算机内存由一些叫做位（bit）的单元组成。C++ 的 short、int、long 和 long long 类型通过使用不同数目的位来存储值，最多能够表示 4 种不同的
   整数宽度。如果在所有的系统中，每种类型的宽度都相同，则使用起来将非常方便。例如, 如果 short 总是 16 位，int 总是 32 位等等。不过生活并非那么简单，
   没有一种选择能够满足所有的计算机设计要求。

   C++ 提供了一种灵活的标准，它确保了最小长度（从 C 语言借鉴而来）, 如下所示:

   1. short 至少16位
   2. int 至少与 short 一样长
   3. long 至少 32 位，且至少与 int 一样长
   4. long long 至少 64 位，且至少与 long 一样长


// !! 位与字节

计算机内存的基本单元是位（bit）。可以将位看作电子开关，可以开，也可以关。关表示值 0，开表示值 1。8 位的内存块可以设置出 256 种不同的组合，因为每一位都可以
有两种设置，所以 8 位的总组合数为 2×2×2×2×2×2×2×2，即 256。因此，8 位单元可以表示 0-255 或者 -128 到 127 。每增加一位，组合数便加倍。这意味着可以把 
16 位单元设置成 65536 个不同的值，把 32 位单元设置成 4294 672 296 个不同的值，把 64 位单元设置为 18 446 744 073 709 551 616 个不同的值。作为比较，
unsigned long 存储不了地球上当前的人数和银河系的星星数，而 long long 能够。

'字节（byte）通常指的是 8 位的内存单元'。从这个意义上说，字节指的就是描述计算机内存量的度量单位，1KB 等于 1024 字节，1MB 等于 1024KB。然而，C++ 对字节的定
义与此不同。C++ 字节由至少能够容纳实现的基本字符集的相邻位组成，也就是说，可能取值的数目必须等于或超过字符数目。

在美国，基本字符集通常是 ASCII 和 EBCDIC 字符集，它们都可以用 8 位来容纳，所以在使用这两种字符集的系统中，C++ 字节通常包含8位。然而，国际编程可能需要使用更
大的字符集，如 Unicode，因此有些实现可能使用 16 位甚至 32 的字节。

实际上，short 是 short int 的简称，而 long 是 long int 的简称，但是程序设计者们几乎都不使用比较长的形式。

这 4 种类型（int、short、long 和 long long）都是符号类型，这意味着每种类型的取值范围中，负值和正值几乎相同。例如，16 位的int的取值范围为 -32768 到 
+32767。

要知道系统中整数的最大长度，可以在程序中使用 C++ 工具来检查类型的长度。首先，sizeof 运算符返回类型或变量的长度，单位为字节（运算符是内置的语言元素，对一个或
多个数据进行运算，并生成一个值。例如，加号运算符+将两个值相加）。前面说过，“字节”的含义依赖于实现，因此在一个系统中，两字节的 int 可能是16位，而在另一个系统中
可能是 32 位。其次，头文件 climits 中包含了关于整型限制的信息。具体地说，它定义了表示各种限制的符号名称。例如，INT_MAX 为 int 的最大取值，CHAR_BIT 为字节
的位数。程序 limits.cpp 演示了如何使用这些工具。该程序还演示如何初始化，即使用声明语句将值赋给变量。

// limits.cpp --- some integer limits

#include<iostream>
#include<climits>


int main()
{
    using namespace std;
    int n_int = INT_MAX;
    short n_short = SHORT_MAX;
    long n_long = LONG_MAX;
    long long n_llong = LLONG_MAX;


    // sizeof operator yields size of type or of variable
    cout << "int is " << sizeof(n_int) << "bytes" << endl;
    cout << "short is " << sizeof(n_short) << "bytes" << endl;
    cout << "long is " << sizeof(n_long) << "bytes" << endl;
    cout << "long long is " << sizeof(n_llong) << "bytes" << endl;
    
    cout << "Maxmum Value :" << endl;
    cout << "int :" << n_int << endl;
    cout << "short: " << n_short << endl;
    cout << "long: " << n_long << endl;
    cout << "long long :" << n_llong << endl;

    cout << "Max int value is :" << INT_MAX << endl;
    cout << "Bits per Byte is :" << CHAR_BIT << endl;
    
    return 0;
}


» g++ --std=c++11 limits.cpp
--------------------------------------------------------------------------------
» ./a.out

int is 4 bytes
short is 2 bytes
long is 8 bytes
long long is 8 bytes
Maxmum Value :
int :2147483647
short: 32767
long: 9223372036854775807
long long :9223372036854775807
Max int value is :2147483647
Bits per Byte is :8


1. 运算符 sizeof 和头文件 limits

   ssizeof 运算符指出，在使用 8 位字节的系统中，int 的长度为 4 个字节。可对类型名或变量名使用 sizeof 运算符。对类型名（如int）使用 sizeof 运算符时，应将
   名称放在括号中；但对变量名（如n_short）使用该运算符，括号是可选的:

   sizeof n_short;

   头文件 climits 定义了'符号常量'来表示类型的限制。如前所述，INT_MAX 表示类型int能够存储的最大值。编译器厂商提供了 climits 文件，该文件指出了其编译器中
   的值。例如，在使用 16 位 int 的老系统中，climits 文件将 INT_MAX 定义为 32767。


2. 符号常量—预处理器方式

climits 文件中包含与下面类似的语句行:

#define INT_MAX 2147483647

在 C++ 编译过程中，首先将源代码传递给预处理器。在这里 #define 和 #include 一样，也是一个预处理器编译指令。该编译指令告诉预处理器: 在程序中查找 INT_MAX，
并将所有的 INT_MAX 都替换为 32767。因此 #define 编译指令的工作方式与文本编辑器或字处理器中的全局搜索并替换命令相似。修改后的程序将在完成这些替换后被编译。
预处理器查找独立的标记（单独的单词），跳过嵌入的单词。也就是说，预处理器不会将 PINT_MAXTM 替换为 P32767IM。也可以使用 #define 来定义自己的符号常量
。'#define 编译指令是 C 语言遗留下来的。C++ 有一种更好的创建符号常量的方法（使用关键字 const ），所以不会经常使用 #define'。'有些头文件，尤其是那些
被设计成可用于 C 和 C++ 中的头文件，必须使用 #define'。


3. 初始化

初始化将赋值与声明合并在一起。例如，下面的语句声明了变量 n_int，并将 int 的最大取值赋给它:

int n_int = INT_MAX;

也可以使用字面值常量来初始化。可以将变量初始化为另一个变量，条件是后者已经定义过。甚至可以使用表达式来初始化变量，条件是当程序执行到该声明时，表达式中所有
的值都是已知的。

int uncles = 5;
int aunts = uncles;
int chairs = aunts + 10;

如果将 uncles 的声明移到语句列表的最后，则另外两条初始化语句将非法，因为这样当程序试图对其他变量进行初始化时，uncles 的值是未知的。

前面的初始化语法来自 C 语言，C++ 还有另一种 C 语言没有的初始化语法:

int owls = 10086; // traditional C initialization, set owls to 10086
int wrens(10010); // alternative C++ syntax , set wrens to 10010


// !! 警告：

'如果不对函数内部定义的变量进行初始化，该变量的值将是不确定的。这意味着该变量的值将是它被创建之前，相应内存单元保存的值'。


如果知道变量的初始值应该是什么，则应对它进行初始化。将变量声明和赋值分开，可能会带来瞬间悬而未决的问题:

short year
...
year = 2021;

然而， 在声明变量时对它进行初始化，可避免以后忘记给它赋值的情况发生。



4. C++11 初始化方式

还有另一种初始化方式，这种方式用于数组和结构，但在 C++98 中，也可用于单值变量:

int hamburgers = {12}; // set hamburgers value to 12

将大括号初始化器用于单值变量的情形还不多， 但 C++11 标准使得这种情形更多了。首先，采用这种方式时，可以使用等号（=），也可以不使用:

int key = {12};
int value{12};

其次，大括号内可以不包含任何东西。在这种情况下变量将被初始化为零:

int keyword = {};


为何需要更多的初始化方法 ？ 有充分的理由吗 ？

'原因是让新手更容易学习 C++'，这可能有些奇怪。以前 C++ 使用不同的方式来初始化不同的类型: 初始化类变量的方式不同于初始化常规结构的方式，而初始化常规结构
的方式又不同于初始化简单变量的方式; '通过使用 C++ 新增的大括号初始化器，初始化常规变量的方式与初始化类变量的方式更像'。C++11 使得可将'大括号初始化器'用于
任何类型（可以使用等号，也可以不使用），这是一种通用的初始化语法。


5. 无符号类型

前面介绍的 4 种整型都有一种不能存储负数值的无符号变体, 其优点是可以增大变量能够存储的最大值。例如，如果 short 表示的范围为 −32768 到 +32767，则无符号版本
的表示范围为 0-65535。'当然，仅当数值不会为负时才应使用无符号类型，如人口、粒数等'。要创建无符号版本的基本整型，只需使用关键字 unsigned 来修改声明即可:

unsigned short change;// unsigned short type
unsigned int rovert;// unsigned int type
unsigned value; // also unsigned int
unsigned long gone;// unsigned long type
unsigned long long lang_lang;

注意，unsigned 本身是 unsigned int 的缩写。

程序 exceed.cpp 演示了如何使用无符号类型，并说明了程序试图超越整型的限制时将产生的后果。

// exceed.cpp ---- exceeding some integer limit

#include<iostream>
#define ZERO 0
#include<climits>

int main()
{
    using namespace std;
    short sam = SHRT_MAX;// initialize a variable to maxValue
    unsigned short sue = sam;// ok, if sam is defined

    count << "Sam has  " << sam << " dollars, and sue has " << sue << " dollars" << endl;

    cout << "Add $1 to each account. " << endl << "Now";
    sam = sam + 1;
    sue = sue + 1;
    cout << "Sam has " << sam << " dollars, and sue has " << sue;
    cout << " dollars deposit. \nPoor sam" << endl;

    sam = ZERO;
    sue = ZERO;
    cout << "Sam has " << sam << " dollars, and sue has " << sue;
    cout << " dollars deposit. \nPoor sam" << endl;
    cout << "Take $1 to each account. " << endl << "Now";
    sam = sam -1;
    sue = sue -1;
    cout << "Sam has " << sam << " dollars, and sue has " << sue;
    cout << " dollars deposit. \nPoor sam" << endl;
    return 0;
}


» g++ --std=c++11 exceed.cpp
» ./a.out
Sam has  32767 dollars, and sue has 32767 dollars
Add $1 to each account. Now
Sam has -32768 dollars, and sue has 32768 dollars deposit. 
Poor sam
Sam has 0 dollars, and sue has 0 dollars deposit. 
Poor sam
Take $1 to each account. Now
Sam has -1 dollars, and sue has 65535 dollars deposit. 
Poor sam

该程序将一个 short 变量（sam）和一个 unsigned short 变量（sue）分别设置为最大的 short 值，在我们的系统上，是 32767。然后将这些变量的值都加 1。这对于
sue 来说没有什么问题，因为新值仍比无符号整数的最大值小得多；但 sam 的值从 32767 变成了 −32768 ！同样，对于 sam，将其设置为 0 并减去 1，也不会有问题；
但对于无符号变量 sue，将其设置为 0 并减去后，它变成了 65535。可以看出，'这些整型变量的行为就像里程表。如果超越了限制，其值将为范围另一端的取值'。C++ 确保
了无符号类型的这种行为；但 C++ 并不保证符号整型超越限制（上溢和下溢）时不出错， 而这正是当前实现中最为常见的行为。


// !! 选择整型类型

C++ 提供了大量的整型，应使用哪种类型呢？

'通常，int 被设置为对目标计算机而言最为“自然”的长度。自然长度（natural size）指的是计算机处理起来效率最高的长度'。如果没有非常有说服力的理由来选择其他
类型，则应使用 int。

现在来看看可能使用其他类型的原因。

1. 如果变量表示的值不可能为负，如文档中的字数，则可以使用无符号类型，这样变量可以表示更大的值

2. 如果知道变量可能表示的整数值大于 16 位整数的最大可能值，则使用 long,即使系统上 int 为32位，也应这样做,这样，将程序移植到16位系统时，就不会突然无法
   正常工作

3. 如果要存储的值超过 20 亿，可使用 long long

4. 如果 short 比 int 小，则使用 short 可以节省内存。通常，仅当有大型整型数组时，才有必要使用 int,如果节省内存很重要，则应使用 short 而不是使用 int，
   即使它们的长度是一样的.例如，假设要将程序从 int 为 16 位的系统移到 int 为 32 位的系统，则用于存储 int 数组的内存量将加倍，但 short 数组不受影响。

5. 如果只需要一个字节，可使用 char


// !! 整型字面值

整型字面值（常量）是显式地书写的常量，如 212 或 1776。与 C 相同，C++ 能够以三种不同的计数方式来书写整数：基数为 10、基数为 8（老式 UNIX 版本）和基数为 
16（硬件黑客的最爱）


'C++ 使用前一（两）位来标识数字常量的基数'。如果第一位为 1～9，则基数为 10（十进制）；因此 93 是以 10 为基数的。如果第一位是 0，第二位为 1～7，则基数为
8（八进制）；因此 042 的基数是 8，它相当于十进制数 34。如果前两位为 0x或 0X，则基数为 16（十六进制）；因此 0x42 为十六进制数，相当于十进制数 66。
对于十六进制数，字符 a～f 和 A～F 表示了十六进制位，对应于 10～15。0xF为 15，0xA5为165（10 个 16 加 5 个 1）

// hexoct.cpp --- show hex and octal literals

#include<iostream>

int main()
{
    using namespace std;
    int chest = 42;
    int waist = 0x42;
    int inseam = 042;

    cout << "Monsieur cuts a striking figure!\n";
    cout << "chest =: " << chest << "(42 in decimal)\n";
    cout << "waist =: " << waist << "(0x42 in hex) \n";
    cout << "inseam =: " << inseam << "(042 in octal)\n";
    return 0;
}

在默认情况下，cout 以十进制格式显示整数，而不管这些整数在程序中是如何书写的，如下面的输出所示:

» g++ --std=c++11 hexoct.cpp
--------------------------------------------------------------------------------
 » ./a.out

Monsieur cuts a striking figure!
chest =: 42(42 in decimal)
waist =: 66(0x42 in hex) 
inseam =: 34(042 in octal)

'记住，这些表示方法仅仅是为了表达上的方便'。例如，如果 CGA 视频内存段为十六进制 B000，则不必在程序中使用之前将它转换为十进制数 45056，而只需使用 0xB000 
即可。'不管把值书写为 10、012 还是 0xA，都将以相同的方式存储在计算机中—被存储为二进制数'（以 2 为基数）。


顺便说一句，如果要以十六进制或八进制方式显示值，则可以使用 cout 的一些特殊特性。前面指出过，头文件 iostream 提供了控制符 endl，用于指示 cout 重起一行。
同样，它还提供了控制符 dec、hex 和 oct，分别用于指示 cout 以十进制、十六进制和八进制格式显示整数。程序 hexoct2.cpp 使用了 hex 和 oct 以上述三种格式
显示十进制值 42。默认格式为十进制，在修改格式之前，原来的格式将一直有效。


// hexoct2.cpp

#include<iostream>

int main()
{
    using namespace std;
    int chest = 42;
    int waist = 42;
    int inseam = 42;

    cout << "Monsieur cuts a striking figure!\n";
    cout << "chest =: " << chest << "(42 in decimal)\n";
    cout << hex;
    cout << "waist =: " << waist << "(42 in hex) \n";
    cout << oct;
    cout << "inseam =: " << inseam << "(42 in octal)\n";
    return 0;
}

 » g++ --std=c++11 hexoct2.cpp
--------------------------------------------------------------------------------
» ./a.out
Monsieur cuts a striking figure!
chest =: 42(42 in decimal)
waist =: 2a(42 in hex) 
inseam =: 52(42 in octal)


'诸如 cout<<hex 等代码不会在屏幕上显示任何内容，而只是修改 cout 显示整数的方式'。因此，控制符 hex 实际上是一条消息，告诉 cout 采取何种行为。另外，由于
标识符 hex 位于名称空间 std 中，而程序使用了该名称空间，因此不能将 hex 用作变量名。然而，如果省略编译指令 using，而使用 std::cout、std::endl、std::hex
和 std::oct，则可以将 hex 用作变量名。

// !! C++ 如何确定常量的类型




















