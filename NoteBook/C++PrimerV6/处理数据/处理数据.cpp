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

'程序的声明将特定的整型变量的类型告诉了 C++ 编译器'，但编译器是如何知道常量的类型呢？假设在程序中使用常量表示一个数字：

cout << "Year: " << 2121 << endl;

程序将把 2021 存储为 int、long 还是其他整型呢？答案是: '除非有理由存储为其他类型（如使用了特殊的后缀来表示特定的类型，或者值太大，不能存储为 int），否则 
C++ 将整型常量存储为 int 类型'。


首先来看看后缀。后缀是放在数字常量后面的字母，用于表示类型。

1. 整数后面的 l 或 L 后缀表示该整数为 long 常量
2. u 或 U 后缀表示 unsigned int 常量
3. ul （可以采用任何一种顺序，大写小写均可）表示 unsigned long 常量

例如，在 int 为16位、long 为32位的系统上，数字 22022 被存储为 int，占 16 位，数字 22022L 被存储为 long，占32位。同样，22022LU 和 22022UL 都被存储为
unsigned long。'C++11 提供了用于表示类型 long long 的后缀 LL，还提供了用于表示类型 unsigned long long 的后缀 ull、Ull、uLL 和 ULL'。

'由于小写 l 看上去像1，因此应使用大写 L 作后缀'


// !! 在 C++ 中，对十进制整数采用的规则，与十六进制和八进制稍微有些不同。

1. 对于不带后缀的十进制整数，将使用下面几种类型中能够存储该数的最小类型来表示：int、long 或 long long。在 int 为16位、long 为32位的计算机系统上，
   20000 被表示为 int 类型，40000 被表示为 long 类型，3000000000 被表示为 long long 类型

2. 对于不带后缀的十六进制或八进制整数，将使用下面几种类型中能够存储该数的最小类型来表示：int、unsigned int long、unsigned long、long long 或 
   unsigned long long。在将 40000 表示为 long 的计算机系统中，十六进制数 0x9C40（40000）将被表示为 unsigned int。'这是因为十六进制常用来表示内存地址
   ，而内存地址是没有符号的，因此，unsigned int 比 long 适合用来表示 16 位的地址'


// !! char类型: 字符和小整数

'顾名思义，char 类型是专为存储字符（如字母和数字）而设计的'。现在，存储数字对于计算机来说算不了什么，但存储字母则是另一回事。'编程语言通过使用字母的数值编码
解决了这个问题'。

因此，char 类型是另一种整型。

1. 它足够长，'能够表示目标计算机系统中的所有基本符号'—所有的字母、数字、标点符号等

2. 实际上，'很多系统支持的字符都不超过 128 个，因此用一个字节就可以表示所有的符号'。虽然 char 最常被用来处理字符，但也可以将它用做比 short 更小的整型

在美国，最常用的符号集是 ASCII 字符集。字符集中的字符用数值编码（ASCII 码）表示。例如，字符 A 的编码为 65，字母 M 的编码为 77。

// chartype.cpp

#include <iostream>

int main()
{
    using namespace std;
    char ch;// declare a char variable

    cout << "Enter a character" << endl;
    cin >> ch;
    cout << "Hola! ";
    cout << "Thanks for the  " << ch <<" character " << endl;
    return 0;
}

 » g++ --std=c++11 chartype.cpp
--------------------------------------------------------------------------------
 » ./a.out
Enter a character
M
Hola! Thanks for the  M character 

有趣的是，程序中输入的是 M，而不是对应的字符编码77。另外，程序将打印 M，而不是77。通过查看内存可以知道，77 是存储在变量 ch 中的值。这种神奇的力量不是来自 
char 类型，而是来自 cin 和 cout，这些工具为您完成了转换工作。输入时，cin 将键盘输入的 M 转换为 77；输出时，cout 将值 77 转换为所显示的字符 M；'cin 和 
cout 的行为都是由变量类型引导的'。如果将 77 存储在 int 变量中，则 cout 将把它显示为 77（也就是说，cout显示两个字符7）

// morechar.cpp

#include <iostream>

int main()
{
    using namespace std;
    char ch = 'M';
    int i = ch;

    cout << "The ASCII code for " << ch << " is " << i << endl;
    cout << "Add one to the character code :" << endl;
    ch = ch + 1;
    i = ch;
    cout << "The ASCII code for " << ch << " is " << i << endl;

    cout << "Displaying char ch using cout.put(ch):";
    cout.put(ch);

    cout << "Using cout.put() to display a char character";
    cout.put('!');
    cout << "Done!" << endl;
    return 0;
}

 » g++ --std=c++11 morechar.cpp
--------------------------------------------------------------------------------
 » ./a.out
The ASCII code for M is 77
Add one to the character code :
The ASCII code for N is 78
Displaying char ch using cout.put(ch):NUsing cout.put() to display a char character!Done!

1. ‘M’ 表示字符 M 的数值编码，因此将 char 变量 ch 初始化为‘M’，将把 ch 设置为 77。然后，程序将同样的值赋给 int 变量 i，这样 ch 和 i 的值都是 77。
cout 把 ch 显示为 M，而把 i 显示为 77。如前所述，'值的类型将引导 cout 选择如何显示值'

由于 ch 实际上是一个整数，因此可以对它使用整数操作，如加 1，这将把 ch 的值变为 78。然后，程序将 i 重新设置为新的值（也可以将i加1）。cout 再次将这个值的
char 版本显示为字符，将 int 版本显示为数字。

2. 成员函数 cout.put()

   cout.put() 到底是什么东西？ 其名称中为何有一个句点？ 函数 cout.put() 是一个重要的 C++ OOP 概念—成员函数—的第一个例子。'类定义了如何表示和控制数据。
   成员函数归类所有，描述了操纵类数据的方法'。例如类 ostream 有一个 put() 成员函数，用来输出字符。只能通过类的特定对象（例如这里的 cout 对象）来使用成员
   函数。要通过对象（如 cout）使用成员函数， 必须用句点将对象名和函数名称（put()）连接起来。'句点被称为成员运算符'。

3. char 字面值

   在 C++ 中，书写字符常量的方式有多种。对于常规字符（如字母、标点符号和数字），'最简单的方法是将字符用单引号括起。这种表示法代表的是字符的数值编码'。
   例如, ASCII 系统中的对应情况如下: 'A'为65，即字符 A 的 ASCII 码; 'a' 为 97，即字符 a 的 ASCII 码; '5' 为 53，即数字 5 的 ASCII 码；
   ' '为 32，即空格字符的 ASCII 码； '!' 为 33，即惊叹号的 ASCII 码。

'有些字符不能直接通过键盘输入到程序中'。例如，按回车键并不能使字符串包含一个换行符；相反，程序编辑器将把这种键击解释为在源代码中开始新的一行。其他一些字符也无法
从键盘输入，因为 C++ 语言赋予了它们特殊的含义。例如， 双引号字符用来分隔字符串字面值，因此不能把双引号放在字符串字面值中。

'对于这些字符，C++ 提供了一种特殊的表示方法—转义序列'。例如，\a 表示振铃字符，它可以使终端扬声器振铃。转义序列 \n 表示换行符，\” 将双引号作为常规字符，而不是
字符串分隔符。可以在字符串或字符常量中使用这些表示法，如下例所示:

char alarm = '\a';
cout << alarm << "Dont do that again.\n";

注意，应该像处理常规字符（如Q）那样处理转义序列（如 \n）。也就是说，'将它们作为字符常量时，应用单引号括起；将它们放在字符串中时，不要使用单引号'。

转义序列的概念可追溯到使用电传打字机与计算机通信的时代，'现代系统并非都支持所有的转义序列'。例如， 输入振铃字符时，有些系统保持沉默。

换行符可替代 endl，用于在输出中重起一行。可以以字符常量表示法（‘\n’）或字符串方式（“\n”）使用换行符。下面三行代码都将光标移到下一行开头:

cout << endl;
cout << '\n';
cout << "\n";

可以将换行符嵌入到较长的字符串中，这通常比使用 endl 方便。例如，下面两条 cout 语句的输出相同:

cout << endl << endl << "What next ? " << endl << "Enter the number: " << endl;
cout << "\n\nWhat next ? \n Enter the number: \n";


最后，可以基于字符的八进制和十六进制编码来使用转义序列。

例如，Ctr+Z 的 ASCII 码为26，对应的八进制编码为 032，十六进制编码为 0x1a。可以用下面的转义序列来表示该字符：\032 或 \x1a。将这些编码用单引号括起，
可以得到相应的字符常量，如'\032'，也可以将它们放在字符串中，如"hi\x1a there"。

程序 bondini.cpp 演示了一些转义序列。它使用振铃字符来提请注意，使用换行符使光标前进，使用退格字符使光标向左退一格。

// bondini.cpp

#include<iostream>

int main()
{
    using namespace std;
    cout << "\aOperation \"HyperHype\" is now activated!\n";
    cout << "Enter your agent code:_____\b\b\b\b\b\b";
    long code;
    cin >> code;
    cout << "\a your entered " << code << "...\n";
    cout << "\a Code verify! Procesed with plan Z3 \n";
    return 0;
}


 » g++ --std=c++11 bondini.cpp
--------------------------------------------------------------------------------
» ./a.out
Operation "HyperHype" is now activated!
Enter your agent code:__12334_
 your entered 12334...
 Code verify! Procesed with plan Z3 



 // !! 通用字符名

 C++ 实现支持一个基本的源字符集，即可用来编写源代码的字符集。它由标准美国键盘上的字符（大写和小写）和数字、C 语言中使用的符号（如{和=}以及其他一些字符
 （如换行符和空格）组成。


// !!signed char 和 unsigned char

与 int 不同的是，char 在默认情况下既不是没有符号，也不是有符号。'是否有符号由 C++ 实现决定，这样编译器开发人员可以最大限度地将这种类型与硬件属性匹配起来'。
如果 char 有某种特定的行为对您来说非常重要，则可以显式地将类型设置为 signed char 或 unsigned char:

char fodo;
unsigned char bar;
signed char snark;

'如果将 char 用作数值类型，则 unsigned char 和 signed char 之间的差异将非常重要'。unsigned char 类型的表示范围通常为 0～255，而 signed char 的表示
范围为 −128~127。例如，假设要使用一个 char 变量来存储像 200 这样大的值，则在某些系统上可以，而在另一些系统上可能不可以。但使用 unsigned char 可以在任何系
统上达到这种目的。另一方面，如果使用 char 变量来存储标准 ASCII 字符，则 char 有没有符号都没关系，在这种情况下，可以使用 char。


// !! wchar_t

程序需要处理的字符集可能无法用一个 8 位的字节表示，如日文汉字系统。对于这种情况，C++ 的处理方式有两种。首先，如果大型字符集是实现的基本字符集，则编译器厂商可以
将 char 定义为一个 16 位的字节或更长的字节。其次，一种实现可以同时支持一个小型基本字符集和一个较大的扩展字符集。8 位 char 可以表示基本字符集，另一种类型
 wchar_t（宽字符类型）可以表示扩展字符集。wchar_t 类型是一种整数类型，它有足够的空间，可以表示系统使用的最大扩展字符集。这种类型与另一种整型
 （底层（underlying）类型）的长度和符号属性相同。'对底层类型的选择取决于实现，因此在一个系统中，它可能是 unsigned short，而在另一个系统中，则可能是 int'。

'cin 和 cout 将输入和输出看作是 char 流，因此不适于用来处理 wchar_t 类型。iostream 头文件的最新版本提供了作用相似的工具— wcin 和 wcout，可用于处理 
wchar_t 流'。

另外，可以通过加上前缀 L 来指示宽字符常量和宽字符串。下面的代码将字母 P 的 wchar_t 版本存储到变量 bob 中，并显示单词 tall 的 wchar_t 版本：

wchar_t bob = L'P';// a wide-character constant
wcout << L"tall" << endl; // outputing a wide-character string 

在支持两字节 wchar_t 的系统中，上述代码将把每个字符存储在一个两个字节的内存单元中。


// !! C++11 新增的类型：char16_t 和 char32_t

随着编程人员日益熟悉 Unicode，类型 wchar_t 显然不再能够满足需求。事实上，在计算机系统上进行字符和字符串编码时，仅使用 Unicode 码点并不够。具体地说，进行字
符串编码时，如果有特定长度和符号特征的类型，将很有帮助，而类型 wchar_t 的长度和符号特征随实现而已。

'因此，C++11 新增了类型 char16_t 和 char32_t，其中前者是无符号的，长 16 位，而后者也是无符号的，但长 32 位。' C++11 使用前缀 u 表示 char16_t 字符常量
和字符串常量，如 u‘C’和 u“be good”; 并使用前缀 U 表示 char32_t 常量，如 U‘R’ 和 U“dirty rat”。

与 wchar_t 一样，char16_t 和 char32_t 也都有底层类型—一种内置的整型，但底层类型可能随系统而已。

// !! bool 类型

ANSI/ISO C++ 标准添加了一种名叫 bool 的新类型（对 C++ 来说是新的）。它的名称来源于英国数学家 George Boole，是他开发了逻辑律的数学表示法。在计算中，布尔
变量的值可以是 true 或 false。过去，C++ 和 C 一样，也没有布尔类型。然而，现在可以使用 bool 类型来表示真和假了，它们分别用预定义的字面值 true 和 false 
表示。也就是说，可以这样编写语句:

bool is_ready = true;

字面值 true 和 false 都可以通过提升转换为 int 类型，true 被转换为 1，而 false 被转换为 0：

int ans = true;
int promise = false;

另外，任何数字值或指针值都可以被隐式转换（即不用显式强制转换）为 bool 值。任何非零值都被转换为 true，而零被转换为 false。


// !! const 限定符

现在回过头来介绍常量的符号名称。符号名称指出了常量表示的内容。另外，如果程序在多个地方使用同一个常量，则需要修改该常量时，只需修改一个符号定义即可。
前面关于 #define 语句的说明指出过，C++ 有一种更好的处理符号常量的方法，这种方法就是使用 const 关键字来修改变量声明和初始化。例如，假设需要一个
表示一年中月份数的符号常量，请在程序中输入下面这行代码:

const int Months = 12;

这样，便可以在程序中使用 Months，而不是 12 了（在程序中，12 可能表示一英尺有多少英寸或一打面包圈是多少个，而名称 Months 指出了值 12 表示的是什么）。

常量（如 Months）被初始化后，其值就被固定了，编译器将不允许再修改该常量的值。如果您这样做，g++ 将指出程序试图给一个只读变量赋值。

'关键字 const 叫做限定符，因为它限定了声明的含义'。

一种常见的做法是将名称的首字母大写，以提醒您 Months 是个常量。'这决不是一种通用约定，但在阅读程序时有助于区分常量和变量'。另一种约定是将整个名称大写，
使用 #define 创建常量时通常使用这种约定:

const int MONTHS = 12;

如果在声明常量时没有提供值，则该常量的值将是不确定的，且无法修改。

如果以前使用过 C 语言，您可能觉得前面讨论的 #define 语句已经足够完成这样的工作了。但 const 比 #define 好:

1. 首先，它能够明确指定类型

2. 其次，可以使用 C++ 的作用域规则将定义限制在特定的函数或文件中

3. 可以将 const 用于更复杂的类型

// !! 提示：

'如果读者在学习 C++ 之前学习过 C 语言，并打算使用 #define 来定义符号常量，请不要这样做，而应使用 const'。

// !! 浮点数

了解各种 C++ 整型后，来看看浮点类型，它们是 C++ 的第二组基本类型。浮点数能够表示带小数部分的数字，如 M1 油箱的汽油里程数（0.56 MPG），它们提供的值范
围也更大。如果数字很大，无法表示为 long 类型，如人体的细菌数（估计超过100兆），则可以使用浮点类型来表示。

使用浮点类型可以表示诸如 2.5、3.14159 和 122442.32 这样的数字，即带小数部分的数字。'计算机将这样的值分成两部分存储,一部分表示值，另一部分用于对值进
行放大或缩小'。对于数字 34.1245 和 34124.5，它们除了小数点的位置不同外，其他都是相同的。可以把第一个数表示为 0.341245（基准值）和 100（缩放因子），
而将第二个数表示为 0.341245（基准值相同）和 10000（缩放因子更大）。'缩放因子的作用是移动小数点的位置，术语浮点因此而得名'。

C++ 内部表示浮点数的方法与此相同，只不过它基于的是二进制数，因此缩放因子是 2 的幂，不是 10 的幂。幸运的是，程序员不必详细了解内部表示。'重要的是，浮点数能
够表示小数值、非常大和非常小的值'，它们的内部表示方法与整数有天壤之别。

// !! 书写浮点数

C++ 有两种书写浮点数的方式:

1. 使用常用的标准小数点表示法：即使小数部分为0（如 8.0），小数点也将确保该数字以浮点格式（而不是整数格式）表示。（C++标准允许实现表示不同的区域；例如，
提供了使用欧洲方法的机制，即将逗号而不是句点用作小数点。然而，这些选项控制的是数字在输入和输出中的外观，而不是数字在代码中的外观）

2. 第二种表示浮点值的方法叫做 E 表示法，其外观是像这样的: 3.45E6，这指的是 3.45 与 1000000 相乘的结果；E6 指的是 10 的 6 次方，即 1 后面 6 个 0。
因此，3.45E6 表示的是 3450000，6 被称为指数，3.45 被称为尾数。'E 表示法最适合于非常大和非常小的数'

'E 表示法确保数字以浮点格式存储，即使没有小数点'。注意，既可以使用 E 也可以使用 e，指数可以是正数也可以是负数。然而，数字中不能有空格，因此 7.2 E6 是非
法的。

指数为负数意味着除以 10 的乘方，而不是乘以 10 的乘方。因此，8.33E~4 表示 8.33/10^4，即 0.000833。

记住：

d.dddE+n 指的是将小数点向右移 n 位，而 d.dddE～n 指的是将小数点向左移 n 位。'之所以称为“浮点”，就是因为小数点可移动'。


// !! 浮点类型


和 ANSI C 一样， C++ 也提供了 3 种浮点类型：float、double 和 long double， 这些类型是按它们可以表示的有效数位和允许的指数最小范围来描述的。
有效位（significant figure）是数字中有意义的位。

例如，加利福尼亚的 Shasta 山脉的高度为 14179 英尺，该数字使用了 5 个有效位，指出了最接近的英尺数。然而，将 Shasta 山脉的高度写成约 14000 英尺时，有
效位数为 2 位，因为结果经过四舍五入精确到了千位。

在这种情况下，其余的 3 位只不过是占位符而已。有效位数不依赖于小数点的位置。例如，可以将高度写成 14.162 千英尺。这样仍有 5 个有效位，因为这个值精确到了第 5 
位。

事实上，C 和 C++ 对于有效位数的要求是：

1. float 至少 32 位，double 至少 48 位，且不少于 float

2. long double 至少和 double 一样多。这三种类型的有效位数可以一样多。

'通常 float 为 32 位，double 为 64 位，long double 为 80、96 或 128 位。另外，这 3 种类型的指数范围至少是 −37 到 37。可以从头文件 cfloat 或
float.h 中找到系统的限制( cfloat 是 C 语言的 float.h 文件的 C++ 版本）'

下面是 Borland C++ Builder 的 float.h 文件中的一些批注项:

/* Number of decimal digits, q, such that any floating-point number with q
   decimal digits can be rounded into a floating-point number with p radix b
   digits and back again without change to the q decimal digits,

	p * log10(b)			if b is a power of 10
	floor((p - 1) * log10(b))	otherwise
*/
#undef FLT_DIG
#undef DBL_DIG
#undef LDBL_DIG
#define FLT_DIG		__FLT_DIG__
#define DBL_DIG		__DBL_DIG__
#define LDBL_DIG	__LDBL_DIG__


程序 floatnum.cpp 演示了 float 和 double 类型及它们表示数字时在精度方面的差异（即有效位数）

#include <iostream>

int main()
{
    using namespace std;
    cout.setf(ios_base::fixed, ios_base::floatfield);// fixed-point

    float tub = 10.0 / 3.0;// good to about 6 places
    double mint = 10.0 / 3.0;// good to about 15 places

    const float million = 1.0e6;

    cout << "tub : " <<tub << endl;
    cout << " a million tubs = " << million * tub;
    cout <<  ",\n and ten million tubs = ";
    cout << 10 * million * tub << endl;

    cout << "mint = " << mint << "and a million mints =";
    cout << million * mint << endl;
    return 0;
}

» g++ --std=c++11 floatnum.cpp
-------------------------------------------------------------------------------
 » ./a.out
tub : 3.333333 a million tubs = 3333333.250000,
and ten million tubs = 33333332.000000
mint = 3.333333 and a million mints = 3333333.333333


1. '通常 cout 会删除结尾的零, 例如，将 3333333.250000 显示为 3333333.25 , 调用 cout.setf() 将覆盖这种行为'。这里要注意的是，为何 float 的精度比 double 
低。tub 和 mint 都被初始化为 10.0/3.0 — 3.333333333333333333…… 由于 cout 打印 6 位小数，因此 tub 和 mint 都是精确的。但当程序将每个数乘以一百万后，
tub 在第 7 个 3 之后就与正确的值有了误差。tub 在 7 位有效位上还是精确的（该系统确保 float 至少有6位有效位，但这是最糟糕的情况）。然而 double 类型的变量显
示了 13 个 3，因此它至少有 13 位是精确的。

cout 所属的 ostream 类有一个类成员函数，能够精确地控制输出的格式—字段宽度、小数位数、采用小数格式还是 E 格式等。

2. 读取包含文件

C++ 源文件开头的'包含编译指令(#include)'总是有一种魔咒的力量，新手 C++ 程序员通过阅读和体验来了解哪个头文件添加哪些功能，再一一包含它们，以便程序能够运行。
'不要将包含文件作为神秘的知识而依赖'；可以随便打开、阅读它们。它们都是文本文件，因此可以很轻松地阅读它们。'被包含在程序中的所有文件都存在于计算机中，或位于计算机
可以使用的地方'。找到那些要使用的包含文件，看看它们包含的内容。'您将会很快地知道，所使用的源文件和头文件都是知识和信息的很好来源'。在有些情况下，它们都是最好的
文档。当使用更复杂的包含文件，并开始在应用程序中使用其他非标准库时，这种习惯将非常有帮助。


// !! 浮点常量

在程序中书写浮点常量的时候，程序将把它存储为哪种浮点类型呢？

'在默认情况下，像 8.24 和 2.4E8 这样的浮点常量都属于 double 类型'。如果希望常量为 float 类型，请使用 f 或 F 后缀。对于 long double 类型，可使用 l 或
 L 后缀（由于 l 看起来像数字 1，因此 L 是更好的选择）。

1.234f;// a float constant
2.456E20F// a float constant
2.34222222222E28 // a double constant
2.2L// a long double constant

// !! 浮点数的优缺点

与整数相比，浮点数有两大优点。首先，它们可以表示整数之间的值。其次，由于有缩放因子，它们可以表示的范围大得多。另一方面，浮点运算的速度通常比整数运算慢，
且精度将降低。

#include <iostream>

int main()
{
    using namespace std;
    float a = 2.34E+22f;
    float b = a + 1.0f;
    cout << " a = " << a << " b = " << b << endl;
    cout << " b - a = " << b - a << endl;
    return 0;
}

该程序将数字加 1， 然后减去原来的数字, 结果应该为 1。

» g++ --std=c++11 fltadd.cpp 
--------------------------------------------------------------------------------
 » ./a.out
 a = 2.34e+22 b = 2.34e+22
 b - a = 0

问题在于，2.34E+22 是一个小数点左边有 23 位的数字, 加上 1，就是在第 23 位加 1。但 float 类型只能表示数字中的前 6 位或前 7 位，因此修改第 23 位对这个值
不会有任何影响。

// !! 将类型分类

'C++ 对基本类型进行分类，形成了若干个族'。类型 signed char、short、int 和 long 统称为符号整型；它们的无符号版本统称为无符号整型； C++11 新增了 long 
long。'bool、char、wchar_t、符号整数和无符号整型统称为整型'; C++11 新增了 char16_t 和 char32_t 。'float、double 和 long double 统称为浮点型'。
'整数和浮点型统称算术（arithmetic）类型'。


// !! C++ 算术运算符

'C++ 使用运算符来运算'。它提供了几种运算符来完成 5 种基本的算术计算：加法、减法、乘法、除法以及求模。每种运算符都使用两个值（操作数）来计算结果。
'运算符及其操作数构成了表达式'。

int wheels = 4 + 2; //

4 和 2 都是操作数，+ 是加法运算符，4 + 2 则是一个表达式，其值为 6。


下面是 5 种基本的 C++ 算术运算符:

1. + 运算符对操作数执行加法运算。例如，4+20 等于 24

2. − 运算符从第一个数中减去第二个数。例如，12−3 等于 9

3. * 运算符将操作数相乘。例如，28 * 4 等于 112

4. / 运算符用第一个数除以第二个数。例如 1000/5 等于 200。如果两个操作数都是整数，则结果为商的整数部分。例如，17/3 等于5，小数部分被丢弃

5. % 运算符求模。也就是说，它生成第一个数除以第二个数后的余数。 例如，19%6 为 1，因为 19 是 6 的 3 倍余 1。两个操作数必须都是整型，将该运算符用于浮点
   数将导致编译错误

// arith.cpp --- some C++ arithmetic
#include<iostream>

int main()
{
    using namespace std;
    float hats,heads;
    cout.setf(ios_base::fixed,ios_base::floatfield);
    
    cout << "Enter a number: ";
    cin >> hats;
    cout << "Enter another number: ";
    cin >> heads;

    cout << " hats: " <<hats << "; heads: " <<heads << endl;
    cout << " hats + heads: " <<hats + heads << endl;
    cout << "hats - heads: " <<hats - heads << endl;
    cout << "hats * heads: " <<hats * heads << endl;
    cout << "hats / heads: " <<hats / heads << endl;
    return 0;
}

下面是该程序的输出，从中可知 C++ 能够完成简单的算术运算：

 » g++ --std=c++11 arith.cpp 
--------------------------------------------------------------------------------
 » ./a.out
Enter a number: 12
Enter another number: 23
 hats: 12.000000; heads: 23.000000
 hats + heads: 35.000000
hats - heads: -11.000000
hats * heads: 276.000000
hats / heads: 0.521739

记住，对于 float，C++ 只保证 6 位有效位。如果将 61.419998 四舍五入成 6 位，将得到 61.4200，这是保证精度下的正确值。如果需要更高的精度，请使用 double 
或 long double。

// !! 运算符优先级和结合性

读者是否委托 C++ 来完成复杂的算术运算？是的，但必须知道 C++ 使用的规则。例如，很多表达式都包含多个运算符。这样将产生一个问题：究竟哪个运算符最先被使用呢？

int flyingpigs = 3 + 4 * 5;

操作数 4 旁边有两个运算符：+ 和 *。'当多个运算符可用于同一个操作数时，C++ 使用优先级规则来决定首先使用哪个运算符'。

1. 算术运算符遵循通常的代数优先级，先乘除，后加减

2. 当然，可以使用括号来执行自己定义的优先级

// !! 除法分支

'除法运算符（/）的行为取决于操作数的类型'。如果两个操作数都是整数，则 C++ 将执行整数除法。这意味着结果的小数部分将被丢弃，使得最后的结果是一个整数。如果其中有
一个（或两个）操作数是浮点值，则小数部分将保留， 结果为浮点数。程序 divide.cpp 演示了 C++ 除法如何处理不同类型的值。

// divide.cpp

#include<iostream>

int main()
{
    using namespace std;
    cout.setf(ios_base::fixed,ios_base::floatfield);
    cout << "Integer divide: 9/5 = " << 9/5 << endl;
    cout << "Floating divide: 9.0/5.0 = " << 9.0/5.0 << endl;
    cout << "Mixed divide: 9.0/5 = " << 9.0/5 << endl;
    cout << "Double divide: 1e7/9.0 = " << 9.0/5 << endl;
    cout << "Float divide: 1e7/9.0f = " << 9.0/5 << endl;
    return 0;
}


 » g++ --std=c++11 divide.cpp
--------------------------------------------------------------------------------
 » ./a.out
Integer divide: 9/5 = 1
Floating divide: 9.0/5.0 = 1.800000
Mixed divide: 9.0/5 = 1.800000
Double divide: 1e7/9.0 = 1111111.111111
Float divide: 1e7/9.0f = 1111111.111111
--------------------------------------------------------------------------------

从第一行输出可知，整数 9 除以 5 的结果为整数 1。4/5 的小数部分（或 0.8）被丢弃。接下来的两行表明，当至少有一个操作数是浮点数时，结果为 1.8。实际上，对不
同类型进行运算时，C++ 将把它们全部转换为同一类型。最后两行的相对精度表明，如果两个操作数都是 double 类型，则结果为 double 类型；如果两个操作数都是 float 
类型，则结果为 float 类型。'记住，浮点常量在默认情况下为 double 类型。'

// !! 运算符重载简介

在程序 divide.cpp 中，除法运算符表示了 3 种不同的运算：int 除法、float 除法和 double 除法。'C++ 根据上下文（这里是操作数的类型）来确定运算符的含义'。'使用
相同的符号进行多种操作叫做运算符重载（operator overloading）'。

'C++ 有一些内置的重载示例, C++ 还允许扩展运算符重载，以便能够用于用户定义的类，因此在这里看到的是一个重要的 OOP 属性'。

// !!求模运算符

求模运算符返回整数除法的余数。它与整数除法相结合，尤其适用于解决要求将一个量分成不同的整数单元的问题，例如将英寸转换为英尺和英寸，或者将美元转换为元、角、
分、厘。

// !! 类型转换

C++ 丰富的类型允许根据需求选择不同的类型， 这也使计算机的操作更复杂。例如，将两个 short 值相加涉及到的硬件编译指令可能会与将两个 long 值相加不同。由于有 11 
种整型和 3 种浮点类型， 因此计算机需要处理大量不同的情况，尤其是对不同的类型进行运算时。


为处理这种潜在的混乱，C++ 自动执行很多类型转换:

1. 将一种算术类型的值赋给另一种算术类型的变量时，C++ 将对值进行转换

2. 表达式中包含不同的类型时，C++ 将对值进行转换

3. 将参数传递给函数时，C++ 将对值进行转换


// !! 初始化和赋值进行的转换

C++ 允许将一种类型的值赋给另一种类型的变量。这样做时, 值将被转换为接收变量的类型。例如，假设 so_long 的类型为long，thirty 的类型为 short，而程序中包含这样的
语句：

so_long = thirty;

则进行赋值时，程序将 thirty 的值（通常是16位）扩展为 long 值（通常为32位）。扩展后将得到一个新值，这个值被存储在 so_long 中，而 thirty 的内容不变。

将一个值赋给值取值范围更大的类型通常不会导致什么问题。例如，将 short 值赋给 long 变量并不会改变这个值，只是占用的字节更多而已。然而，将一个很大的 long 值
（如2111222333）赋给 float 变量将降低精度。因为 float 只有 6 位有效数字，因此这个值将被四舍五入为 2.11122E9。因此，有些转换是安全的，有些则会带来麻烦。

1. 将 0 赋给 bool 变量时，将被转换为 false；而非零值将被转换为 true

2. 将浮点值赋给整型将导致两个问题。首先，将浮点值转换为整型会将数字截短（除掉小数部分）。其次，float 值对于 int 变量来说可能太大了。在这种情况下，C++ 并没有定义结果应
   该是什么；这意味着不同的实现的反应可能不同。

传统初始化的行为与赋值相同，程序 init.cpp 演示了一些初始化进行的转换。

// init.cpp --- type change on initialization

#include<iostream>

int main()
{
    using namespace std;
    cout.setf(ios_base::fixed,ios_base::floatfield);

    float tree = 3;// int convert to float
    int guess(3.1234);// double convert to int
    int debt = 7.2e12;// result not defined in C++
    cout << "Tree: " << tree << endl;
    cout << "Guess: " << guess << endl;
    cout << "Debt: " << debt << endl;
    return 0;
}


// !! 以 {} 方式初始化时进行的转换（C++11）

'C++11 将使用大括号的初始化称为列表初始化（list-initialization），因为这种初始化常用于给复杂的数据类型提供值列表'。与程序 init.cpp 所示的初始化方式相比，它对类型
转换的要求更严格。具体地说，'列表初始化不允许缩窄（narrowing），即变量的类型可能无法表示赋给它的值'。

例如，不允许将浮点型转换为整型。在不同的整型之间转换或将整型转换为浮点型可能被允许，条件是编译器知道目标变量能够正确地存储赋给它的值。例如，可将 long 变量初始化为 int
值，因为 long 总是至少与 int 一样长；相反方向的转换也可能被允许，只要 int 变量能够存储赋给它的 long 常量。


// !! 表达式中的转换

当同一个表达式中包含两种不同的算术类型时，将出现什么情况呢？ 在这种情况下，C++ 将执行两种自动转换：首先，一些类型在出现时便会自动转换；其次，有些类型在与其他类型同时出现
在表达式中时将被转换。

1. 先来看看自动转换。在计算表达式时，C++ 将 bool、char、unsigned char、signed char 和 short 值转换为 int
   具体地说，true 被转换为 1，false 被转换为 0。这些转换被称为整型提升（integral promotion）, 例如，请看下面的语句：

   short chickens = 20;
   short ducks = 35;
   short fowl = chickens + ducks;

   为执行第 3 行语句，C++ 程序取得 chickens 和 ducks 的值，并将它们转换为 int。然后程序将结果转换为 short 类型， 因为结果将被赋给一个 short 变量。这种说法可能有
   点拗口，但是情况确实如此。'通常将 int 类型选择为计算机最自然的类型，这意味着计算机使用这种类型时，运算速度可能最快。'

2. 还有其他一些整型提升: 如果 short 比 int 短，则 unsigned short 类型将被转换为 int；如果两种类型的长度相同，则 unsigned short 类型将被转换为 unsigned int

3. 同样 wchar_t 被提升成为下列类型中第一个宽度足够存储 wchar_t 取值范围的类型：int、unsigned int、long 或 unsigned long

4. 将不同类型进行算术运算时, 也会进行一些转换, 例如将 int 和 float 相加时。

   当运算涉及两种类型时，较小的类型将被转换为较大的类型。


// !! 传递参数时的转换

传递参数时的类型转换通常由 C++ 函数原型控制。然而，也可以取消原型对参数传递的控制，尽管这样做并不明智。在这种情况下，C++ 将对 char 和 short 类型（signed 和 
unsigned）应用整型提升。另外，为保持与传统 C 语言中大量代码的兼容性，在将参数传递给取消原型对参数传递控制的函数时，C++ 将 float 参数提升为 double。


// !! 强制类型转换

'C++ 还允许通过强制类型转换机制显式地进行类型转换'。（C++ 认识到，必须有类型规则，而有时又需要推翻这些规则）。强制类型转换的格式有两种。例如，为将存储在变量 thorn 
中的 int 值转换为 long 类型，可以使用下述表达式中的一种:

(long)thorn;
long(thorn);

第一种格式来自 C 语言，第二种格式是纯粹 C++。新格式的想法是，要让强制类型转换就像是函数调用。这样对内置类型的强制类型转换就像是为用户定义的类设计的类型转换。

C++ 还引入了 4 个强制类型转换运算符，对它们的使用要求更为严格:

static_cast<> 可用于将值从一种数值类型转换为另一种数值类型。例如，可以像下面这样将 thorn 转换为 long 类型：

static_cast<long>(thorn);


// !! C++11 中的 auto 声明

C++11 新增了一个工具，'让编译器能够根据初始值的类型推断变量的类型'。在初始化声明中，如果使用关键字 auto，而不指定变量的类型，编译器将把变量的类型设置成与初始值相同。


auto n = 10; // n is int
auto x = 1.6; // x is double
auto y = 1.6f; // y is float

然而，自动推断类型并非为这种简单情况而设计的；事实上，如果将其用于这种简单情形，甚至可能让您误入歧途。

'处理复杂类型，如标准模块库（STL）中的类型时，自动类型推断的优势才能显现出来。'

例如，对于下述 C++98 代码：

std::vector<double> scores;
std::vector<double>::iterator pv = scores.begin();

C++11 允许您将其重写为下面这样:

std::vector<double> scores;
auto pc = scores.begin();


// !! 总结

C++ 的基本类型分为两组：一组由存储为整数(char、bool、short、int、long、long long)的值组成; 另一组由存储为浮点（float、double、long double）格式的值
组成。'整型之间通过存储值时使用的内存量及有无符号来区分'。整型从最小到最大依次是：bool、char、signed char、unsigned char、short、unsigned short、int、
unsigned int、long、unsigned long 以及 C++11 新增的 long long 和 unsigned long long。还有一种 wchar_t 类型，它在这个序列中的位置取决于实现。
C++11 新增了类型 char16_t 和 char32_t，它们的宽度足以分别存储 16 和 32 位的字符编码。'C++ 确保了 char 足够大，能够存储系统基本字符集中的任何成员，而 wchar_t
则可以存储系统扩展字符集中的任意成员'。short 至少为 16 位，而 int 至少与 short 一样长，long 至少为 32 位。确切的长度取决于实现。'字符通过其数值编码来表示。I/O 
系统决定了编码是被解释为字符还是数字'。

浮点类型可以表示小数值以及比整型能够表示的值大得多的值。3 种浮点类型分别是 float、double 和 long double。C++ 确保 float 不比 double 长，而 double 不比 
long double 长。通常，float 使用 32 位内存，double 使用 64 位，long double 使用 80 到 128 位。

'通过提供各种长度不同、有符号或无符号的类型，C++ 使程序员能够根据特定的数据要求选择合适的类型。'

C++ 使用运算符来提供对数字类型的算术运算：加、减、乘、除和求模。当两个运算符对同一个操作数进行操作时，C++ 的优先级和结合性规则可以确定先执行哪种操作。

对变量赋值、在运算中使用不同类型、使用强制类型转换时，C++ 将把值从一种类型转换为另一种类型。很多类型转换都是“安全的”，即可以在不损失和改变数据的情况下完成转换。
例如，可以把 int 值转换为 long 值，而不会出现任何问题。对于其他一些转换，如将浮点类型转换为整型，则需要更加小心。开始，读者可能觉得大量的 C++ 基本类型有些多余，尤其是
考虑到各种转换规则时。但是很可能最终将发现，某些时候，只有一种类型是需要的，此时您将感谢 C++ 提供了这种类型。







