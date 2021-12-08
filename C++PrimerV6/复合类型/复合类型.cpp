// !! 复合类型

假设您开发了一个名叫 User-Hostile 的计算机游戏，玩家需要用智慧来应对一个神秘、险恶的计算机界面。现在，必须编写一个程序来跟踪 5 年来游戏每月的销售量，或者希望盘
点一下与黑客英雄累积的较量回合。您很快发现，'需要一些比 C++ 的简单基本类型更复杂的东西，才能满足这些数据的要求，C++ 也提供了这样的东西—复合类型'。这种类型是基于
基本整型和浮点类型创建的。影响最为深远的复合类型是类，它是将学习的 OOP 的堡垒。然而，C++ 还支持几种更普通的复合类型，它们都来自 C 语言。

例如，数组可以存储多个同类型的值。一种特殊的数组可以存储一系列字符(字符串)。结构可以存储多个不同类型的值。而指针则是一种将数据所处位置告诉计算机的变量。

// !! 数组

数组（array）是一种数据格式，能够存储多个同类型的值。例如，数组可以存储 60 个 int 类型的值（这些值表示游戏 5 年来的销售量）、12 个 short 值（这些值表示每个月的天数）
或 365 个 float 值（这些值指出一年中每天在食物方面的开销）。

'每个值都存储在一个独立的数组元素中，计算机在内存中依次存储数组的各个元素。'

要创建数组，可使用声明语句。数组声明应指出以下三点:

1. 存储在每个元素中的值的类型

2. 数组名

3. 数组中的元素数

在 C++ 中，可以通过修改简单变量的声明，添加中括号（其中包含元素数目）来完成数组声明。

例如，下面的声明创建一个名为 months 的数组，该数组有 12 个元素，每个元素都可以存储一个 short 类型的值:

short months[12];// creat a array of 12 short

事实上，可以将数组中的每个元素看作是一个简单变量。

声明数组的通用格式如下：

typeName arrayName[arraySize];

表达式 arraySize 指定元素数目，它必须是整型常数（如10）或 const 值，也可以是常量表达式（如 8 * sizeof（int）），即其中所有的值在编译时都是已知的。
具体地说，arraySize 不能是变量，变量的值是在程序运行时设置的。

1. 作为复合类型的数组

数组之所以被称为复合类型，是因为它是使用其他类型来创建的。不能仅仅将某种东西声明为数组，它必须是特定类型的数组。没有通用的数组类型，但存在很多特定的数组类型，
如 char 数组或 long 数组。例如，请看下面的声明：

float loans[20];

loans 的类型不是数组，而是 float 数组 。这强调了 loans 组是使用 float 类型创建的。

数组的很多用途都是基于这样一个事实: 可以单独访问数组元素。方法是使用下标或索引来对元素进行编号。C++ 数组从 0 开始编号和。C++ 使用带索引的方括号表示法来指定数组
元素。例如，months[0] 是 months 数组的第一个元素，months[11] 是最后一个元素。注意，最后一个元素的索引比数组长度小 1。因此，数组声明能够使用一个声明创建大量的
变量，然后便可以用索引来标识和访问各个元素。

2. 有效下标值的重要性

'编译器不会检查使用的下标是否有效'。例如，如果将一个值赋给不存在的元素 months[101]，编译器并不会指出错误。但是程序运行后，这种赋值可能引发问题，它可能破坏数据或
代码，也可能导致程序异常终止。所以必须确保程序只使用有效的下标值。

程序 arrayone.cpp 中的马铃薯分析程序说明了数组的一些属性，包括声明数组、给数组元素赋值以及初始化数组。

// arrayone.cpp ---small array of integer


#include <iostream>

int main()
{
    using namespace std;
    int yams[3];// create array with 3 elements
    yams[0] = 7; // assign value to first elements
    yams[1] = 8; // assign value to second elements
    yams[2] = 6; // assign value to third elements

    int yamcost[3] = {20,30,5};// create a initialize array

    cout << "Total yams = " << endl;
    cout << yams[0] + yams[1] + yams[2] << endl;
    cout << "The packaged with " << yams[1] << " yams cost ";
    cout << yamcost[1] << " cents per yam.\n";

    int total = yams[0] * yamcost[0] + yams[1] * yamcost[1] + yams[2] * yamcost[2];
    cout << "The total yams cost " << total << "cents .\n";

    cout << "size of yams array is " << sizeof(yams);
    cout << "bytes.\n";
    cout << "size of one elements is " << sizeof(yams[0]);
    cout << "bytes.\n";
    return 0;
}

 » g++ --std=c++11 arrayone.cpp 
--------------------------------------------------------------------------------
 » ./a.out
Total yams = 
21
The packaged with 8 yams cost 30 cents per yam.
The total yams cost 410cents .
size of yams array is 12bytes.
size of one elements is 4bytes.

该程序首先创建一个名为 yams 的包含 3 个元素的数组。由于 yams 有 3 个元素，它们的编号为 0～2，因此 arrayone.cpp 使用索引 0～2 分别给这三个元素赋值。
'Yam 的每个元素都是 int，都有 int 类型的权力和特权'，因此 arrayone.cpp 能够将值赋给元素、将元素相加和相乘，并显示它们。

如果没有初始化函数中定义的数组，则其元素值将是不确定的，这意味着元素的值为以前驻留在该内存单元中的值。

如果将 sizeof 运算符用于数组名，得到的将是整个数组的字节数。如果将 sizeof 用于数组元素，则得到的将是元素的长度（单位为字节）。这表明 yams 是一个数组，
而 yams[1] 只是一个 int 变量。

3. 数组的初始化规则

C++ 有几条关于初始化数组的规则，它们限制了初始化的时刻，决定了数组的元素数目与初始化器中值的数目不相同时将发生的情况。我们来看看这些规则。
只有在定义数组时才能使用初始化，此后就不能使用了，也不能将一个数组赋给另一个数组：

int cards[4] = {1,2,3,4};
int hands[4];
hands[4] = {1,2,3,4};// not allowed
cards = hands; // not allowed

然而, 可以使用下标分别给数组中的元素赋值。

初始化数组时，提供的值可以少于数组的元素数目。例如，下面的语句只初始化 hotelTips 的前两个元素：

float hotelTips[4] = {5.0,2.5};

如果只对数组的一部分进行初始化，则编译器将把其他元素设置为 0。因此，将数组中所有的元素都初始化为 0 非常简单—只要显式地将第一个元素初始化为 0，然后让编译器将
其他元素都初始化为 0 即可：

long totals[1222] = {0};

如果初始化为 {1} 而不是 {0}，则第一个元素被设置为 1，其他元素都被设置为 0。

如果初始化数组时方括号内 [] 为空，C++ 编译器将计算元素个数。例如，对于下面的声明:

short things[] = {1,2,3,4};

编译器将使 things 数组包含 4 个元素。

4. 让编译器去做

通常，让编译器计算元素个数是种很糟的做法，因为其计数可能与您想象的不一样。例如，您可能不小心在列表中遗漏了一个值。然而，这种方法对于将字符数组初始化为一个
字符串来说比较安全，很快您将明白这一点。如果主要关心的问题是程序，而不是自己是否知道数组的大小，则可以这样做:

short things[] = {1,2,3,4};
int num_things = sizeof(things)/sizeof(things[0]);

这样做是有用还是偷懒取决于具体情况。


5.  C++11 数组初始化方法

C++11 将使用大括号的初始化（列表初始化）作为一种通用初始化方式，可用于所有类型。数组以前就可使用列表初始化，但 C++11 中的列表初始化新增了一些功能。
首先，初始化数组时，可省略等号（=）; 其次，可不在大括号内包含任何东西，这将把所有元素都设置为零; 第三，列表初始化禁止缩窄转换;

'C++ 标准模板库（STL）提供了一种数组替代品—模板类 vector，而 C++11 新增了模板类 array， 这些替代品比内置复合类型数组更复杂、更灵活。'


// !! 字符串

字符串是存储在内存的连续字节中的一系列字符。C++ 处理字符串的方式有两种。第一种来自 C 语言，常被称为 C-风格字符串（C-style string）。'存储在连续字节中的一
系列字符意味着可以将字符串存储在 char 数组中，其中每个字符都位于自己的数组元素中'。'字符串提供了一种存储文本信息的便捷方式'，如提供给用户的消息（“请告诉我您
的瑞士银行账号”）或来自用户的响应（“您肯定在开玩笑”）。

C-风格字符串（C-style string） 具有一种特殊的性质：以空字符（null character）结尾，空字符被写作 \0，其 ASCII 码为 0，用来标记字符串的结尾。例如，请看
下面两个声明:

char dog[8] = {'b','e','a','u','x','','I','I'}; // a char array, but not a string
char cat[8] = {'b','e','a','u','x','',"I",'\0'}; // a char array and also a C-style string

这两个数组都是 char 数组，但只有第二个数组是字符串。空字符对 C-风格字符串 而言至关重要。例如，C++ 有很多处理字符串的函数，其中包括 cout 使用的那些函数。'它
们都逐个地处理字符串中的字符，直到到达空字符为止'。如果使用 cout 显示上面的 cat 这样的字符串，则将显示前 7 个字符，发现空字符后停止。但是，如果使用 cout 显示
上面的 dog 数组（它不是字符串），cout 将打印出数组中的 8 个字母，并接着将内存中随后的各个字节解释为要打印的字符，直到遇到空字符为止。由于空字符（实际上是被设
置为 0的字节）在内存中很常见，因此这一过程将很快停止。但尽管如此，'还是不应将不是字符串的字符数组当作字符串来处理。'

在 cat 数组示例中，将数组初始化为字符串的工作看上去冗长乏味—使用大量单引号，且必须记住加上空字符。不必担心，有一种更好的、将字符数组初始化为字符串的方法—只需
使用一个用引号括起的字符串即可，这种字符串被称为字符串常量（string constant）或字符串字面值（string literal），如下所示：

char bird[11] = "Mr.cheeps"; // the \0 is understood
char fish[] = "Bubbles";// let compiler count

用引号括起的字符串隐式地包括结尾的空字符，因此不用显式地包括它。另外，各种 C++ 输入工具通过键盘输入，将字符串读入到 char 数组中时，将自动加上结尾的空字符。

'当然，应确保数组足够大，能够存储字符串中所有字符—包括空字符'。使用字符串常量初始化字符数组是这样的一种情况，即让编译器计算元素数目更为安全。让数组比字符串长
没有什么害处，只是会浪费一些空间而已。'处理字符串的函数根据空字符的位置，而不是数组长度来进行处理'。C++ 对字符串长度没有限制。

注意，'字符串常量（使用双引号）不能与字符常量（使用单引号）互换。字符常量（如'S'）是字符编码的简写表示'。在 ASCII 系统上，'S' 只是 83 的另一种写法，因此，
下面的语句将 83 赋给 shirt_size：

char shirt_size = 'S';

但 "S" 不是字符常量，它表示的是两个字符（字符 S 和 \0）组成的字符串。更糟糕的是，"S" 实际上表示的是字符串所在的内存地址。因此下面的语句试图将一个内存地址
赋给 shirt_size：

char shirt_size = "S";

由于地址在 C++ 中是一种独立的类型，因此 C++ 编译器不允许这种不合理的做法。

// !! 拼接字符串常量

有时候，字符串很长，无法放到一行中。C++ 允许拼接字符串字面值，即将两个用引号括起的字符串合并为一个。'事实上，任何两个由空白（空格、制表符和换行符）分隔
的字符串常量都将自动拼接成一个'。因此，下面所有的输出语句都是等效的:

cout << "I would give my right arm to be" "a great violinst.\n";
cout << "I would give my right arm to be a great violinst.\n";
cout << "I would give my right ar"
"m to be a great violinst.\n";

注意，拼接时不会在被连接的字符串之间添加空格，第二个字符串的第一个字符将紧跟在第一个字符串的最后一个字符（不考虑 \0）后面。第一个字符串中的 \0 字符将被第二个
字符串的第一个字符取代。

// !! 在数组中使用字符串

要将字符串存储到数组中，最常用的方法有两种—将数组初始化为字符串常量、将键盘或文件输入读入到数组中。程序 清单4.2 演示了这两种方法，它将一个数组初始化为用引号
括起的字符串，并使用 cin 将一个输入字符串放到另一个数组中。该程序还使用了标准C语言库函数 strlen() 来确定字符串的长度。标准头文件 cstring 提供了该函数以及很多
与字符串相关的其他函数的声明。

// string.cpp

#include<cstring>// for the strlen function
#include<iostream>

int main()
{
    using namespace std;
    const int Size = 15;
    char name1[Size];// empty array
    char name2[Size] = "C++owboy";
    cout << "Howdy!,I'm " << name2;
    cout << "! What your name? \n";
    cin >> name1;
    cout << "Well, " << name1 << " your name has ";
    cout << strlen(name1) << " letters and is stored.\n";
    cout << "in an array of " << sizeof(name1) << " bytes.\n";
    cout << "Your initial is " << name1[0] << ".\n";
    name2[3] = '\0';
    cout << "Here are the first three character of my name :";
    cout << name2 << endl;
    return 0;
}

 » g++ --std=c++11 string.cpp 
--------------------------------------------------------------------------------
» ./a.out

Howdy!,I'm C++owboy! What your name? 
basicman
Well, basicmanyour name has 8 letters and is stored.
in an array of 15 bytes.
Your initial is b.
Here are the first three character of my name :C++'

1. 首先，sizeof 运算符指出整个数组的长度：15 字节，但 strlen() 函数返回的是存储在数组中的字符串的长度，而不是数组本身的长度

2. 另外，strlen() 只计算可见的字符，而不把空字符计算在内,因此，对于 basicman，返回的值为 8，而不是 9

3. 由于 name1 和 name2 是数组，所以可以用索引来访问数组中各个字符

4. 另外，该程序将 name2[3] 设置为空字符, 这使得字符串在第 3 个字符后即结束，虽然数组中还有其他的字符

5. 该程序使用符号常量来指定数组的长度。程序常常有多条语句使用了数组长度。使用符号常量来表示数组长度后，当需要修改程序以使用不同的数组长度时，工作将变
   得更简单—只需在定义符号常量的地方进行修改即可

// !! 字符串输入

程序 string.cpp 有一个缺陷，这种缺陷通过精心选择输入被掩盖掉了。程序 instr1.cpp 揭开了它的面纱，揭示了字符串输入的技巧。

// instr1.cpp

#include<iostream>

int main()
{
    using namespace std;
    const int ArSize = 20;
    char name[ArSize];
    char dessert[ArSize];

    cout << " Enter your name: \n";
    cin >> name;
    cout << "Enter your favorite dessert: \n";
    cin >> dessert;
    cout << "I have some delicious " << dessert;
    cout << " for you " << name << ". \n";
    return 0;
}

该程序的意图很简单：读取来自键盘的用户名和用户喜欢的甜点，然后显示这些信息。

» ./a.out
 Enter your name: 
Alistair Dreeb
Enter your favorite dessert: 
I have some delicious Dreeb for you Alistair. 

1. cin 是如何确定已完成字符串输入呢？由于不能通过键盘输入空字符，因此 cin 需要用别的方法来确定字符串的结尾位置。'cin 使用空白（空格、制表符和换行符）来确定字符
   串的结束位置'，这意味着 cin 在获取字符数组输入时只读取一个单词。读取该单词后，cin 将该字符串放到数组中，并自动在结尾添加空字符。这个例子的实际结果是，cin 
   把 Alistair 作为第一个字符串，并将它放到 name 数组中。这把 Dreeb 留在输入队列中。当 cin 在输入队列中搜索用户喜欢的甜点时，它发现了 Dreeb，因此 cin 
   读取 Dreeb，并将它放到 dessert 数组中

2. 另一个问题是，输入字符串可能比目标数组长（运行中没有揭示出来）。像这个例子一样使用 cin，确实不能防止将包含 30 个字符的字符串放到 20 个字符的数组中的情况发生。


// !! 每次读取一行字符串输入

'每次读取一个单词通常不是最好的选择'。例如，假设程序要求用户输入城市名，用户输入 New York 或 Sao Paulo。您希望程序读取并存储完整的城市名，而不仅仅是 New 
或 Sao。'要将整条短语而不是一个单词作为字符串输入，需要采用另一种字符串读取方法'。具体地说，需要采用面向行而不是面向单词的方法。

'幸运的是，istream 中的类（如 cin）提供了一些面向行的类成员函数：getline() 和 get( )'。这两个函数都读取一行输入，直到到达换行符。


然而，随后 getline() 将丢弃换行符，而 get() 将换行符保留在输入序列中。

1. 面向行的输入：getline()

getline() 函数读取整行，它使用通过回车键输入的换行符来确定输入结尾。要调用这种方法，可以使用 cin.getline()。该函数有两个参数。第一个参数是用来存储输入行的
数组的名称，第二个参数是要读取的字符数。如果这个参数为 20，则函数最多读取 19 个字符，余下的空间用于存储自动在结尾处添加的空字符(\0)。'getline() 成员函数在
读取指定数目的字符或遇到换行符时停止读取'。

例如，假设要使用 getline() 将姓名读入到一个包含 20 个元素的 name 数组中。可以使用这样的函数调用：

cin.getline(name,20);

这将把一行读入到 name 数组中— 如果这行包含的字符不超过 19 个。

// instr2.cpp

#include <iostream>

int main()
{
    using namespace std;
    const int ArSize = 20;
    char name[ArSize];
    char dessert[ArSize];
    cout << " Enter your name: \n";
    cin.getline(name,ArSize);
    cout << "Enter your favorite dessert: \n";
    cin.getline(dessert,ArSize);
    cout << " I have some delicious " << dessert;
    cout << " for you " << name << ". \n";
    return 0;
}

该程序现在可以读取完整的姓名以及用户喜欢的甜点！'getline() 函数每次读取一行, 它通过换行符来确定行尾，但不保存换行符。在存储字符串时，它用空字符来替换换行符'。

2.面向行的输入：get()

我们来试试另一种方法。istream 类有另一个名为 get() 的成员函数，该函数有几种变体。其中一种变体的工作方式与 getline() 类似，它们接受的参数相同，解释参数的
方式也相同，并且都读取到行尾。但 get 并不再读取并丢弃换行符，而是将其留在输入队列中。

假设我们连续两次调用 get():

cin.get(name,ArSize);
cin.get(dessert,ArSize);

由于第一次调用后，换行符将留在输入队列中，因此第二次调用时看到的第一个字符便是换行符。因此 get() 认为已到达行尾，而没有发现任何可读取的内容。如果不借助于
帮助，get() 将不能跨过该换行符。

幸运的是，get() 有另一种变体。使用不带任何参数的 cin.get() 调用可读取下一个字符（即使是换行符），因此可以用它来处理换行符，为读取下一行输入做好准备。
也就是说，可以采用下面的调用序列:

cin.get(name,ArSize);// read first line
cin.get();// read newline
cin.get(dessert,ArSize);// read second line

另一种使用 get() 的方式是将两个类成员函数拼接起来（合并），如下所示：

cin.get(name,ArSize).get();// concatenate member function

之所以可以这样做，是由于 cin.get（name，ArSize） 返回一个 cin 对象，该对象随后将被用来调用 get() 函数。同样，下面的语句将把输入中连续的两行分别读入到数组
name1 和 name2 中，其效果与两次调用 cin.getline() 相同：

cin.get(name1,ArSize).get().get(name2,ArSize);

为什么要使用 get()，而不是 getline() 呢？首先，老式实现没有 getline()。其次，get() 使输入更仔细。例如，假设用 get() 将一行读入数组中。如何知道停止读取
的原因是由于已经读取了整行，而不是由于数组已填满呢？ 查看下一个输入字符，如果是换行符，说明已读取了整行；否则，说明该行中还有其他输入。总之，getline() 使用起
来简单一些，但 get() 使得检查错误更简单些。可以用其中的任何一个来读取一行输入；只是应该知道，它们的行为稍有不同。

// !! 空行和其他问题

当 getline() 或 get() 读取空行时，将发生什么情况？

当前的做法是，当get()（不是 getline()）读取空行后将设置失效位（failbit）, 这意味着接下来的输入将被阻断，但可以用下面的命令来恢复输入：

cin.clear();

另一个潜在的问题是，输入字符串可能比分配的空间长。如果输入行包含的字符数比指定的多，则 getline() 和 get() 将把余下的字符留在输入队列中，而 getline()
还会设置失效位，并关闭后面的输入。

// !! 混合输入字符串和数字

混合输入数字和面向行的字符串会导致问题, 请看 numstr.cpp 中的简单程序。

// numstr.cpp

#include<iostream>

int main()
{
    using namespace std;
    cout << " What year was your house built? \n";
    int year;
    cin >> year;
    cout >> " What is street address.\n";
    char address[80];
    cin.getline(address, 80);
    cout << "Year Built: " << year << endl;
    cout << "Street Address: " << address << endl;
    cout << "Done! \n";
    return 0;
}

 » g++ --std=c++11 numstr.cpp
--------------------------------------------------------------------------------

 » ./a.out
 What year was your house built? 
1988
 What is street address.
Year Built: 1988
Street Address: 
Done! 


用户根本没有输入地址的机会。问题在于，'当 cin 读取年份，将回车键生成的换行符留在了输入队列中'。后面的 cin.getline() 看到换行符后，将认为是一个空行，并
将一个空字符串赋给 address 数组。

解决之道是，在读取地址之前先读取并丢弃换行符。这可以通过几种方法来完成， 其中包括使用没有参数的 get() 和使用接受一个 char 参数的 get()，如前面的例子所示。
可以单独进行调用：

cin>>year;
cin.get();

也可以利用表达式 cin>>year 返回 cin 对象，将调用拼接起来:

(cin>>year).get();

按上述任何一种方法修改程序 numstr.cpp， 它便可以正常工作:

// numstr.cpp

#include<iostream>

int main()
{
    using namespace std;
    cout << " What year was your house built? \n";
    int year;
    (cin >> year).get();
    cout >> " What is street address.\n";
    char address[80];
    cin.getline(address, 80);
    cout << "Year Built: " << year << endl;
    cout << "Street Address: " << address << endl;
    cout << "Done! \n";
    return 0;
}

C++ 程序常使用指针（而不是数组）来处理字符串。


// !! string 类简介

ISO/ANSI C++98 标准通过添加 string 类扩展了 C++ 库，因此现在可以用 string 类型的变量（使用 C++ 的话说是对象）而不是字符数组来存储字符串。
'string 类使用起来比数组简单，同时提供了将字符串作为一种数据类型的表示方法'。要使用 string 类，必须在程序中包含头文件 string。string 类位于名称空间
std中，因此您必须提供一条 using 编译指令，或者使用 std::string 来引用它。'string 类定义隐藏了字符串的数组性质，让您能够像处理普通变量那样处理字符串'。
程序 strtype.cpp 说明了 string 对象与字符数组之间的一些相同点和不同点。

// strtype.cpp

#include<iostream>
#include<string>

int main()
{
    using namespace std;

    char charr1[20];
    char charr2[20] = "jaguar";
    string str1;// create a empty string
    string str2 = "panther";// create a initialise string

    cout << "Enter a kind of feline: ";
    cin >> charr1;
    cout << "Enter a another kind of feline: ";
    cin >> str1;
    cout << "Here are some felines: \n";
    cout << charr1 << " " << charr2 << " " << str1 << " " << str2 << endl;
    cout << "The third letter in " << str2 << " is " << str2[2] << endl;
    
    return 0;
}

 » g++ --std=c++11 strtype.cpp 
--------------------------------------------------------------------------------
 » ./a.out

Enter a kind of feline: ocelot
Enter a another kind of feline: tiger
Here are some felines: 
ocelot jaguar tiger panther
The third letter in panther is n

从这个示例可知，在很多方面，使用 string 对象的方式与使用字符数组相同:

1. 可以使用 C-风格字符串 来初始化 string 对象

2. 可以使用 cin 来将键盘输入存储到 string 对象中

3. 可以使用 cout 来显示 string 对象

4. 可以使用数组表示法来访问存储在 string 对象中的字符

程序 strtype.cpp 表明， 'string 对象和字符数组之间的主要区别是，可以将 string 对象声明为简单变量，而不是数组'


'类设计让程序能够自动处理 string 的大小'。例如，str1 的声明创建一个长度为 0 的 string 对象，但程序将输入读取到 str1 中时，将自动调整 str1 的长度：

cin >> str1;

'这使得与使用数组相比，使用 string 对象更方便，也更安全'。从理论上说，可以将 char 数组视为一组用于存储一个字符串的 char 存储单元，而 string 类变量是一个
表示字符串的实体。


// !!C++11 字符串初始化

C++11 允许将列表初始化用于 C-style string 和 string 对象:

char first_data[] = {"Le Chapon Dodu"};
char second_data[]{"The Element Plate"};
string third_data = {"Hello World"};
string fourth_data = {"tell me you job"};


// !! 赋值、拼接和附加

使用 string 类时，某些操作比使用数组时更简单。例如，不能将一个数组赋给另一个数组，但可以将一个 string 对象赋给另一个 string 对象:

char charr1[20];
char charr2[20] = "jaguar";

string str1;
string str2 = "panther";
charr1 = charr2; // INVALID
str1 = str2; // OK

string 类简化了字符串合并操作。可以使用运算符 + 将两个 string 对象合并起来，还可以使用运算符 += 将字符串附加到 string 对象的末尾。


string str3;
str3 = str1 + str2;
str1 += str2; // add str2 to the end of str1


程序 strtype2.cpp 演示了这些用法, 可以将 C-Style string 或 string 对象与 string 对象相加，或将它们附加到 string 对象的末尾。

// strtype2.cpp

#include<iostream>
#include<string>

int main()
{
    using namespace std;
    string s1 = "penguin";
    string s2,s3;

    cout << "You can assign one string Object to another : s2 = s1\n";
    cout << "s2 = \"buzzard\"\n";
    s2 = "buzzard";
    cout <<"s2: " << s2 << endl;
    cout << "you can concatenate string : s3 = s2 + s1 \n";
    s3 = s2 + s1;
    cout << "s3: " << s3 << endl;
    cout << " you can append string .\n";
    s1 += s2;
    cout << "s1 += s2 yields s1 =  " << s1 << endl;
    s2 += "for a day";
    cout << "s2 += \"for a day\" yields s2 = " << s2 << endl;

    return 0;
}

 » g++ --std=c++11 strtype2.cpp
--------------------------------------------------------------------------------
 » ./a.out
You can assign one string Object to another : s2 = s1
s2 = "buzzard"
s2: buzzard
you can concatenate string : s3 = s2 + s1 
s3: buzzardpenguin
 you can append string .
s1 += s2 yields s1 =  penguinbuzzard
s2 += "for a day" yields s2 = buzzardfor a day

// !! string 类的其他操作

在 C++ 新增 string 类之前，程序员也需要完成诸如给字符串赋值等工作。对于 C-Style string，程序员使用 C 语言库中的函数来完成这些任务。头文件 cstring
提供了这些函数。

例如，可以使用函数 strcpy() 将字符串复制到字符数组中，使用函数 strcat() 将字符串附加到字符数组末尾：

strcpy(charr1,charr2);// copy charr2 to charr1
strcat(charr1,charr2);// append contents of charr2 to charr1

程序 strtype3.cpp 对用于 string 对象的技术和用于字符数组的技术进行了比较。

// strtype3.cpp

#include <iostream>
#include<string>
#include<cstring>

int main()
{
    using namespace std;
    char charr1[20];
    char charr2[20] = "jaguar";
    string str1;
    string str2 = "panther";

    // assignment for string object and character arrays
    str1 = str2;
    strcpy(charr1, charr2);

    // appending for string object and character arrays
    str1 += " paste";
    strcpy(charr1, "juice");

    // finding the length of the string object and a C-Style string
    int len1 = str1.size();
    int len2 = strlen(charr1);

    cout << "The string " << str1 << " has length " << len1 << " characters.\n";
    cout << "The string " << charr1 << " has length " << len2 << " characters.\n";
    return 0;
}

处理 string 对象的语法通常比使用 C 字符串函数简单，尤其是执行较为复杂的操作时。例如，对于下述操作:

str3 = str1 + str2;

使用 C-Style string 时，需要使用的函数如下:

strcpy(charr3, charr1);
strcat(charr3, charr2);

另外，使用字符数组时，总是存在目标数组过小，无法存储指定信息的危险，如下面的示例所示:

函数 strcat() 试图将全部 12 个字符复制到数组 charr3 中，这将覆盖相邻的内存。这可能导致程序终止，或者程序继续运行，但数据被损坏。'string 类具有自动调整
大小的功能，从而能够避免这种问题发生'。C 函数库确实提供了与 strcat()和 strcpy() 类似的函数 -- strncat() 和 strncpy()，它们接受指出目标数组最大允许长
度的第三个参数，因此更为安全，但使用它们进一步增加了编写程序的复杂度。

下面是两种确定字符串中字符数的方法: 

int len1 = str1.size();
int len2 = strlen(charr1);

函数 strlen() 是一个常规函数，它接受一个 C-Style string 作为参数，并返回该字符串包含的字符数。函数 size()的功能基本上与此相同，但句法不同: str1 不
是被用作函数参数，而是位于函数名之前，它们之间用句点连接。这种句法表明，str1 是一个对象，而 size() 是一个类方法。在这里，str1 是一个 string 对象，而 
size() 是 string 类的一个方法。总之，C 函数使用参数来指出要使用哪个字符串，而 C++ string 类对象使用对象名和句点运算符来指出要使用哪个字符串。

// !! string 类 I/O

可以使用 cin 和运算符 >> 来将输入存储到 string 对象中，使用 cout 和运算符 << 来显示 string 对象，其句法与处理 C-Style string 相同。但每次读取一行
而不是一个单词时，使用的句法不同，程序 strtype4.cpp 说明了这一点。

// strtype4.cpp

#include<iostream> 
#include<string> // make string class available
#include<cstring>// C-style string library

int main()
{
    using namespace std;
    char charr[20];
    string str;

    cout << "The length of the string in charr before input : " << strlen(charr) << endl;
    cout << "The length of the string str before input : " << str.size() << endl;

    cout << "Enter a line of text: \n";
    cin.getline(charr,20);// indicate maximum length
    cout << "You Entered : " << charr << endl;

    cout << "Enter another line of text: \n";
    getline(cin,str);// cin now an argument; no length specifier
    cout << "You entered : " << str << endl;

    cout << "The length of string in charr after input : " << strlen(charr) << endl;
    cout << "The length of string in str after input : " << str.size() << endl;
    return 0;
}

 » g++ --std=c++11 strtype4.cpp
--------------------------------------------------------------------------------
 » ./a.out

The length of the string in charr before input :6
The length of the string str before input :0
Enter a line of text: 
hellokitty
You Entered : hellokitty
Enter another line of text: 
lbj 
You entered : lbj
The length of string in charr after input : 10
The length of string in str after input : 3


在用户输入之前，该程序指出数组 charr 中的字符串长度为 6，这比该数组的长度要小。

这里要两点需要说明：

1. 首先，未初始化的数组的内容是未定义的

2. 其次，函数 strlen() 从数组的第一个元素开始计算字节数，直到遇到空字符（\0）

3. 对于未被初始化的数据，第一个空字符(\0)的出现位置是随机的，因此您在运行该程序时，得到的数组长度很可能与此不同

4. 用户输入之前，str 中的字符串长度为 0, 这是因为未被初始化的 string 对象的长度被自动设置为 0

下面是将一行输入读取到数组中的代码:

cin.getline(charr,20);

这种句点表示法表明，函数 getline() 是 istream 类的一个类方法。第一个参数是目标数组；第二个参数数组长度，getline() 使用它来避免超越数组的边界。

下面是将一行输入读取到 string 对象中的代码:

getline(cin,str);

这里没有使用句点表示法，这表明这个 getline() 不是类方法。它将 cin 作为参数，指出到哪里去查找输入。另外，也没有指出字符串长度的参数，因为 string 对象将根
据字符串的长度自动调整自己的大小。

像下面这样的代码使用istream类的一个成员函数: 
cin >> x;


像下面处理string 对象的代码使用 string 类的一个友元函数:

cin >> str;


// !! 结构简介

假设要存储有关篮球运动员的信息，则可能需要存储他（她）的姓名、工资、身高、体重、平均得分、命中率、助攻次数等。希望有一种数据格式可以将所有这些信息存储在一个单
元中。数组不能完成这项任务，因为虽然数组可以存储多个元素，但所有元素的类型必须相同。也就是说，一个数组可以存储 20 个 int，另一个数组可以存储 10 个 float，
但同一个数组不能在一些元素中存储 int，在另一些元素中存储 float。

C++ 中的结构的可以满足要求（存储篮球运动员的信息）。'结构是一种比数组更灵活的数据格式，因为同一个结构可以存储多种类型的数据'，这使得能够将有关篮球运动员的
信息放在一个结构中，从而将数据的表示合并到一起。

如果要跟踪整个球队，则可以使用结构数组。结构也是 C++ OOP 堡垒（类）的基石。学习有关结构的知识将使我们离 C++ 的核心 OOP 更近。

结构是用户定义的类型，而结构声明定义了这种类型的数据属性。定义了类型后，便可以创建这种类型的变量。

因此创建结构包括两步:

1. 首先，定义结构描述—它描述并标记了能够存储在结构中的各种数据类型

2. 然后按描述创建结构变量（结构数据对象）

例如，假设 Bloataire 公司要创建一种类型来描述其生产线上充气产品的成员。具体地说，这种类型应存储产品名称、容量（单位为立方英尺）和售价。

下面的结构描述能够满足这些要求:

struct inflatable // structure declaration
{
    char name[20];
    float volume;
    double price;
};

1. '关键字 struct 表明，这些代码定义的是一个结构的布局'。
2. 标识符 inflatable 是这种数据格式的名称，因此新类型的名称为 inflatable

这样，便可以像创建 char 或 int 类型的变量那样创建 inflatable 类型的变量了。

接下来的大括号中包含的是结构存储的数据类型的列表，其中每个列表项都是一条声明语句。列表中的每一项都被称为结构成员，因此 infatable 结构有 3 个成员

总之，结构定义指出了新类型（这里是 inflatable ）的特征。

定义结构后，便可以创建这种类型的变量了:

inflatable hat;

如果您熟悉 C 语言中的结构，则可能已经注意到了，C++ 允许在声明结构变量时省略关键字 struct:

struct inflatable goose;

'在 C++ 中，结构标记的用法与基本类型名相同。这种变化强调的是，结构声明定义了一种新类型'。

在 C++ 中，省略 struct 不会出错。由于 hat 的类型为 inflatable，因此可以使用成员运算符 （.） 来访问各个成员。

例如，hat.volume 指的是结构的 volume 成员，hat.price 指的是 price 成员。同样，vincent.price 是 vincent 变量的 price 成员。

'总之，通过成员名能够访问结构的成员，就像通过索引能够访问数组的元素一样'。

由于 price 成员被声明为 double 类型，因此 hat.price 和 vincent.price 相当于是 double 类型的变量，可以像使用常规 double 变量那样来使用它们。
总之，hat 是一个结构，而 hat.price 是一个 double 变量。

顺便说一句，访问类成员函数（如 cin.getline()）的方式是从访问结构成员变量（如 vincent.price）的方式衍生而来的。


// !! 在程序中使用结构

// structur.cpp

#include<iostream>

struct inflatable// struct declaration
{
    char name[20];
    float volume;
    double price;
};


int main()
{
    using namespace std;
    inflatable guess = 
    {
        "Gloris",
        1.88,
        2.99
    };

    inflatable pal = 
    {
        "Kooo",
        23.11,
        212.32
    };

    cout << "Expand you guest list with  " << guess.name;
    cout << " and " << pal.name << "!\n";
    cout << "You can have both of $ ";
    cout << guest.price + pal.price << "!\n";
    return 0;
}

 » g++ --std=c++11 structur.cpp
--------------------------------------------------------------------------------
 » ./a.out
Expand you guest list with  Gloris and Kooo!
You can have both of $ 215.31!


结构声明的位置很重要。对于 structur.cpp 而言，有两种选择。可以将声明放在 main() 函数中，紧跟在开始括号的后面。另一种选择是将声明放到 main() 的前面
，这里采用的便是这种方式，'位于函数外面的声明被称为外部声明'。对于这个程序来说，两种选择之间没有实际区别。但是对于那些包含两个或更多函数的程序来说，差别
很大。'外部声明可以被其后面的任何函数使用，而内部声明只能被该声明所属的函数使用'。通常应使用外部声明，这样所有函数都可以使用这种类型的结构

变量也可以在函数内部和外部定义，外部变量由所有的函数共享（这将在第9章做更详细的介绍）。C++ 不提倡使用外部变量，但提倡使用外部结构声明。另外，在外部声明
符号常量通常更合理。


// !! C++11 结构初始化

与数组一样，C++11 也支持将列表初始化用于结构，且等号（=）是可选的:

inflatable duck{"hello",1.222,4.332};

其次，如果大括号内未包含任何东西，各个成员都将被设置为零。最后，不允许缩窄转换。


// !! 结构可以将 string 类作为成员吗

可以将成员 name 指定为 string 对象而不是字符数组吗？即可以像下面这样声明结构吗？

#include<string>
struct inflatable
{
    std::string name;
    float volume;
    float price;
};

答案是肯定的，只要您使用的编译器支持对以 string 对象作为成员的结构进行初始化。'一定要让结构定义能够访问名称空间 std'。为此，可以将编译指令 using 移
到结构定义之前；也可以像前面那样，将 name 的类型声明为 std::string。

// !! 其他结构属性

'C++ 使用户定义的类型与内置类型尽可能相似'。

例如，可以将结构作为参数传递给函数，也可以让函数返回一个结构。另外，还可以使用赋值运算符（=）将结构赋给另一个同类型的结构，这样结构中每个成员都将被设
置为另一个结构中相应成员的值，即使成员是数组。这种赋值被称为成员赋值（memberwise assignment）

//  assgn_st.cpp

#include<iostream>

struct inflatable
{
    char name[20];
    float volume;
    float price;
};

int main()
{
    using namespace std;
    inflatable bouquet = 
    {
        "sunflowers",
        0.20,
        12.49
    };
    inflatable choice;

    cout << "bouquet " << bouquet.name << "for $" <<bouquet.price << endl;

    choice = bouquet; // assign one struct to another

    cout << "choice: " << choice.name << "for $" << choice.price << endl;
    return 0;
}


» g++ --std=c++11 assgn_st.cpp 
--------------------------------------------------------------------------------
 » ./a.out
bouquet sunflowersfor $12.49
choice: sunflowersfor $12.49


从中可以看出，成员赋值是有效的，因为 choice 结构的成员值与 bouquet 结构中存储的值相同。


'可以同时完成定义结构和创建结构变量的工作'。为此，只需将变量名放在结束括号的后面即可:


struct peaks
{
    int key_number;
    char car[12];
} mr_smith;

甚至可以初始化以这种方式创建的变量：


struct perks
{
    int key_number;
    char car[12];
} mr_smith = 
{
    7, 
    "Packe"
};

然而，将结构定义和变量声明分开, 可以使程序更易于阅读和理解。

// !! 结构数组

inflatable 结构包含一个数组（name）。也可以创建元素为结构的数组，方法和创建基本类型数组完全相同。例如，要创建一个包含 100 个 inflatable 结构的
数组，可以这样做:

inflatable gifts[100]；

这样，gifts 将是一个 inflatable 数组，其中的每个元素（如 gifts[0] 或 gifts[99]）都是 inflatable 对象，可以与成员运算符一起使用：

cin >> gifts[0].volume;
cout << gifts[99].price << endl;

记住，gifts 本身是一个数组，而不是结构，因此像 gifts.price 这样的表述是无效的。

要初始化结构数组，可以结合使用初始化数组的规则（用逗号分隔每个元素的值，并将这些值用花括号括起）和初始化结构的规则（用逗号分隔每个成员的值，并将这些值
用花括号括起）。由于数组中的每个元素都是结构，因此可以使用结构初始化的方式来提供它的值。因此，最终结果为一个被括在花括号中、用逗号分隔的值列表，其中每
个值本身又是一个被括在花括号中、用逗号分隔的值列表:

inflatable guests[2] = 
{
    {"bambi",0.5,21.22},
    {"joooo",4.3,32.45}
};

可以按自己喜欢的方式来格式化它们。例如，两个初始化位于同一行，而每个结构成员的初始化各占一行。


// !! 结构中的位字段

与 C 语言一样，'C++ 也允许指定占用特定位数的结构成员'，这使得创建与某个硬件设备上的寄存器对应的数据结构非常方便。

字段的类型应为整型或枚举，接下来是冒号，冒号后面是一个数字，它指定了使用的位数。'可以使用没有名称的字段来提供间距'。'每个成员都被称为位字段
（bit field）'。下面是一个例子:

struct torgle_register
{
    unsigned int SN:4;// 4 bits for SN value
    unsigned int :4; // 4 bits unused
    bool goodIn:1;// valid input (1 bit )
    bool goodTorgle;// successfully torgle
};

可以像通常那样初始化这些字段，还可以使用标准的结构表示法来访问位字段：

torgle_register tr = {14,true,false};
...
if(tr.goodTorgle)
...

位字段通常用在低级编程中。

// !! 共同体

共用体（union）是一种数据格式，它能够存储不同的数据类型，但只能同时存储其中的一种类型。

也就是说，结构可以同时存储 int、long 和 double，共用体只能存储 int、long 或 double。共用体的句法与结构相似，但含义不同。

例如，请看下面的声明:

union one4all
{
    int int_val;
    float float_val;
    double double_val;
};

可以使用 one4all 变量来存储 int、long 或 double，条件是在不同的时间进行:

one4all pail;
pail.int_val = 15;// store an int
cout << pal.int_val << endl;
pail.double_val = 3.234;// store a double, int value is lost
cout << pal.double_val << endl;

因此，pail 有时可以是 int 变量，而有时又可以是 double 变量。'由于共用体每次只能存储一个值，因此它必须有足够的空间来存储最大的成员。

所以，共用体的长度为其最大成员的长度'。

'共用体的用途之一是，当数据项使用两种或更多种格式（但不会同时使用）时，可节省空间'。

例如，假设管理一个小商品目录，其中有一些商品的 ID 为整数，而另一些的 ID 为字符串。

在这种情况下，可以这样做:

struct widget 
{
    char brand[20];
    int type;
    union id
    {
        long id_num;
        char id_char[20];
    } id_val;
};

...

Widget price;
...

if(price.type == 1)
{
    cin >> price.id_val.id_num;
}
else
{
    cin >> price.id_val.id_char;
}

'共用体常用于（但并非只能用于）节省内存。当前，系统的内存多达数 GB 甚至数 TB，好像没有必要节省内存，但并非所有的 C++ 程序都是为这样的系统编写的'。
C++ 还用于嵌入式系统编程，如控制烤箱、MP3播放器或火星漫步者的处理器。对这些应用程序来说，内存可能非常宝贵。'另外，共用体常用于操作系统数据结构或
硬件数据结构'。


// !! 枚举

'C++ 的 enum 工具提供了另一种创建符号常量的方式，这种方式可以代替 const'。它还允许定义新类型，但必须按严格的限制进行。使用 enum 的句法与使用结构
相似。

例如，请看下面的语句：
enum spectrum 
{
    red，
    orange, 
    yellow,
    green,
    blue,
    violet,
    indigo,
    ultraviolet
};

这条语句完成两项工作:

1. 让 spectrum 成为新类型的名称；spectrum 被称为枚举（enumeration），就像 struct 变量被称为结构一样'

2. 将 red、orange、yellow 等作为符号常量，它们对应整数值 0～7, 这些常量叫作枚举量（enumerator）

在默认情况下，将整数值赋给枚举量，第一个枚举量的值为 0，第二个枚举量的值为 1。依次类推, 可以通过显式地指定整数值来覆盖默认值

可以用枚举名来声明这种类型的变量:

spectrum brand; // brand is variable of type spectrum

枚举变量具有一些特殊的属性，下面来看一看。

在不进行强制类型转换的情况下，只能将定义枚举时使用的枚举量赋给这种枚举的变量，如下所示:

brand = blue;// ok, blue is a enumerator
brand = 1000;// invalid, 1000 not an enumerator

因此，spectrum 变量受到限制，只有 8 个可能的值。如果试图将一个非法值赋给它，则有些编译器将出现编译器错误，而另一些则发出警告。'为获得最大限度的
可移植性，应将把非 enum 值赋给 enum 变量视为错误'。

对于枚举，只定义了赋值运算符。具体地说，没有为枚举定义算术运算:

brand = orange;
++brand;// not valid
brand = yellow + blue;// not valid, but a little tricky

'枚举量是整型，可被提升为 int 类型，但 int 类型不能自动转换为枚举类型':

int color = blue;
brand = 3;// invalid, int not converted to spectrum
color = 3 + yellow;// valid, red converted to int

如果 int 值是有效的， 则可以通过强制类型转换， 将它赋给枚举变量：

brand = spectrum(3);// typecast 3 to type spectrum

'如果试图对一个不适当的值进行强制类型转换，将出现什么情况呢？ 结果是不确定的, 这意味着这样做不会出错，但不能依赖得到的结果':

brand = spectrum(10086);


// !! 设置枚举量的值

可以使用赋值运算符来显式地设置枚举量的值:

enum bits{one = 1, two = 2, three = 3, four = 8};

指定的值必须是整数。也可以只显式地定义其中一些枚举量的值:

enum bigstep{first,second = 100,third};

这里，first 在默认情况下为 0。后面没有被初始化的枚举量的值将比其前面的枚举量大 1。因此，third 的值为101。

最后, 可以创建多个值相同的枚举量:

enum{zero,null=0,one,num_one = 1};

其中，zero 和 null 都为 0，one 和 num_one 都为 1。


// !! 枚举的取值范围

最初，对于枚举来说，只有声明中指出的那些值是有效的。然而，C++ 现在通过强制类型转换，增加了可赋给枚举变量的合法值。每个枚举都有取值范围（range），
通过强制类型转换，可以将取值范围中的任何整数值赋给枚举变量，即使这个值不是枚举值。例如，假设 bits 和 myflag 的定义如下:

enum bits{one = 1, two = 2, four = 4, eight = 8};
bits myFlag;

则下面的代码将是合法的:

myFlag = bits(6);

其中 6 不是枚举值，但它位于枚举定义的取值范围内。


取值范围的定义如下:

1. 首先，要找出上限，需要知道枚举量的最大值。找到大于这个最大值的、最小的 2 的幂，将它减去 1，得到的便是取值范围的上限。例如，前面定义的 bigstep 的最大值
   枚举值是101。在 2 的幂中，比这个数大的最小值为 128，因此取值范围的上限为 127。
   
2. 计算下限，需要知道枚举量的最小值。如果它不小于 0，则取值范围的下限为 0；否则，采用与寻找上限方式相同的方式，但加上负号。例如，如果最小的枚举量为 −6，而
   比它小的、最大的 2 的幂是−8（加上负号），因此下限为 −7

'选择用多少空间来存储枚举由编译器决定。对于取值范围较小的枚举，使用一个字节或更少的空间；而对于包含 long 类型值的枚举，则使用 4 个字节'。

//  !! 指针和自由存储空间

计算机程序在存储数据时必须跟踪的 3 种基本属性。为了方便，这里再次列出了这些属性:

1. 信息存储在何处

2. 存储的值为多少

3. 存储的信息是什么类型

您使用过一种策略来达到上述目的：定义一个简单变量。声明语句指出了值的类型和符号名，还让程序为值分配内存，并在内部跟踪该内存单元。

下面来看一看另一种策略，它在开发 C++ 类时非常重要。'这种策略以指针为基础，指针是一个变量，其存储的是值的地址，而不是值本身'。

在讨论指针之前，我们先看一看如何找到常规变量的地址。只需对变量应用地址运算符（&），就可以获得它的位置。例如，如果 home 是一个变量，则 &home 是它的地址。

程序 address.cpp 演示了这个运算符的用法:

// address.cpp

#include<iostream>

int main()
{
    using namespace std;
    int donuts = 6;
    double cups = 4.5;

    cout << "donuts value is " << donuts;
    cout << " and donuts address is " << &donuts << endl;

    cout << "cups value is " << cups;
    cout << " and cups address is " << &cups << endl;
    return 0;
}

 » g++ --std=c++11 address.cpp 
--------------------------------------------------------------------------------
 » ./a.out

donuts value is 6 and donuts address is 0x7ffd81716a5c
cups value is 4.5 and cups address is 0x7ffd81716a60

显示地址时，该实现的 cout 使用十六进制表示法，因为这是常用于描述内存的表示法。在该实现中，donuts 的存储位置比 cups 要低。两个地址的差为 0x7ffd81716a
60 –0x7ffd81716a5c（即 4）。这是有意义的，因为 donuts 的类型为int，而这种类型使用 4 个字节。当然，不同系统给定的地址值可能不同。有些系统可能先存储 
cups，再存储 donuts，这样两个地址值的差将为 8 个字节，因为 cups 的类型为 double。另外，在有些系统中，可能不会将这两个变量存储在相邻的内存单元中。

'使用常规变量时，值是指定的量，而地址为派生量'。


// !! 指针与 C++ 基本原理

面向对象编程与传统的过程性编程的区别在于:'OOP 强调的是在运行阶段（而不是编译阶段）进行决策。运行阶段指的是程序正在运行时，编译阶段指的是编译器将
程序组合起来时'。'运行阶段决策提供了灵活性，可以根据当时的情况进行调整'。例如，考虑为数组分配内存的情况。传统的方法是声明一个数组。要在 C++ 中声明数组，
必须指定数组的长度。因此，数组长度在程序编译时就设定好了；这就是编译阶段决策。您可能认为，在 80% 的情况下，一个包含 20 个元素的数组足够了，但程序有时
需要处理 200 个元素。为了安全起见，使用了一个包含 200 个元素的数组。这样，程序在大多数情况下都浪费了内存。'OOP 通过将这样的决策推迟到运行阶段进行，使
程序更灵活'。在程序运行后，可以这次告诉它只需要 20 个元素，而还可以下次告诉它需要 205 个元素。

总之，'使用 OOP 时，您可能在运行阶段确定数组的长度。为使用这种方法，语言必须允许在程序运行时创建数组'。

'C++ 采用的方法是，使用关键字 new 请求正确数量的内存以及使用指针来跟踪新分配的内存的位置'。

处理存储数据的新策略刚好相反，'将地址视为指定的量，而将值视为派生量'。一种特殊类型的变量—指针用于存储值的地址。因此，指针名表示的是地址。*运算符被称为
间接值（indirect velue）或解除引用（dereferencing）运算符， 将其应用于指针，可以得到该地址处存储的值。

程序 pointer.cpp 说明了这几点，它还演示了如何声明指针。

//  pointer.cpp

#include<iostream>

int main()
{
    using namespace std;
    int updates = 6;// declare a variable
    int * p_updates;// declare a pointer to an int
    p_updates = &updates;// assign address of int to pointer

    cout << "Address: &update is : " << &updates;
    cout << ", p_updates is : " << p_updates << endl;


    *p_updates = *p_updates + 1;

    cout << "Now update is : " << updates << endl;
    return 0;
}

 » g++ --std=c++11 pointer.cpp 
./a.out
Address: &update is : 0x7ffdff9af2dc, p_updates is : 0x7ffdff9af2dc
Now update is : 7

从中可知，in t变量 updates 和指针变量 p_updates 只不过是同一枚硬币的两面。变量 updates 表示值，并使用 & 运算符来获得地址；而变量 p_updates 表
示地址，并使用 * 运算符来获得值。由于 p_updates 指向 updates，因此 *p_updates 和 updates 完全等价。可以像使用 int 变量那样使用 *p_updates。


// !! 声明和初始化指针

我们来看看如何声明指针。'计算机需要跟踪指针指向的值的类型'。例如，char 的地址与 double 的地址看上去没什么两样，但 char 和 double 使用的字节数是不
同的，它们存储值时使用的内部格式也不同。因此，指针声明必须指定指针指向的数据的类型。

例如，前一个示例包含这样的声明:

int *p_updates;

这表明，*p_updates 的类型为 int。由于 * 运算符被用于指针，因此 p_updates 变量本身必须是指针。我们说 p_updates 指向 int 类型，我们还说 p_updates 
的类型是指向 int 的指针，或 int* 。可以这样说，p_updates 是指针（地址），而 *p_updates 是 int，而不是指针。

在 C++ 中，int * 是一种复合类型，是指向 int 的指针。可以用同样的句法来声明指向其他类型的指针:

double *tax_ptr;
char *str;

由于已将 tax_ptr 声明为一个指向 double 的指针，因此'编译器知道 *tax_ptr 是一个 double 类型的值'。也就是说，它知道 *tax_ptr 是一个以浮点格式存储
的值，这个值（在大多数系统上）占据 8 个字节。

'指针变量不仅仅是指针，而且是指向特定类型的指针'。tax_ptr 的类型是指向 double 的指针（或 double * 类型），str 是指向 char 的指针类型（或 char *）。
尽管它们都是指针，却是不同类型的指针。和数组一样，指针都是基于其他类型的。

'虽然 tax_ptr 和 str 指向两种长度不同的数据类型，但这两个变量本身的长度通常是相同的'。一般来说，地址需要 2 个还是 4 个字节，取决于计算机系统
（有些系统可能需要更大的地址，系统可以针对不同的类型使用不同长度的地址）。

可以在声明语句中初始化指针。在这种情况下，被初始化的是指针，而不是它指向的值。也就是说，下面的语句将 pt（而不是*pt）的值设置为 &higgens:

int higgens = 10;
int *pt = &higgens;

程序  init_ptr.cpp 演示了如何将指针初始化为一个地址。

//  init_ptr.cpp

#include<iostream>

int main()
{
    using namespace std;
    int higgens = 10;
    int *pt = &higgens;

    cout << "The value of higgens= " << higgens;
    cout << ", Address of higgens= " << &higgens << endl;

    cout << "The value of *pt " << *pt;
    cout << "; value of pt " << pt << endl;
}


// !!指针的危险

危险更易发生在那些使用指针不仔细的人身上。极其重要的一点是：'在 C++ 中创建指针时，计算机将分配用来存储地址的内存，但不会分配用来存储指针所指向的数据的
内存'。为数据提供空间是一个独立的步骤，忽略这一步无疑是自找麻烦，如下所示:

long *fellow;
*fellow = 223323;

fellow 确实是一个指针，但它指向哪里呢？上述代码没有将地址赋给 fellow。那么 223323 将被放在哪里呢？我们不知道。由于 fellow 没有被初始化，它可能有任
何值。不管值是什么，程序都将它解释为存储 223323 的地址。如果 fellow 的值碰巧为 1200，计算机将把数据放在地址 1200 上，即使这恰巧是程序代码的地址。
fellow 指向的地方很可能并不是所要存储 223323 的地方。这种错误可能会导致一些最隐匿、最难以跟踪的bug。

警告：

'一定要在对指针应用解除引用运算符（*）之前，将指针初始化为一个确定的、适当的地址。这是关于使用指针的金科玉律'


// !! 指针和数字

指针不是整型，虽然计算机通常把地址当作整数来处理。从概念上看，指针与整数是截然不同的类型。整数是可以执行加、减、除等运算的数字，而指针描述的是位置
，将两个地址相乘没有任何意义。从可以对整数和指针执行的操作上看，它们也是彼此不同的。因此，不能简单地将整数赋给指针:

int *pt;
pt = 0xB8000000;

在这里，左边是指向 int 的指针，因此可以把它赋给地址，但右边是一个整数。您可能知道，0xB8000000 是老式计算机系统中视频内存的组合段偏移地址，但这条语
句并没有告诉程序，这个数字就是一个地址。在 C99 标准发布之前，C 语言允许这样赋值。但 C++ 在类型一致方面的要求更严格，编译器将显示一条错误消息，通告类型不
匹配。

'要将数字值作为地址来使用，应通过强制类型转换将数字转换为适当的地址类型':

int *pt;
pt = (int *)0xB8000000

这样，'赋值语句的两边都是整数的地址，因此这样赋值有效'。


// !! 使用 new 来分配内存

对指针的工作方式有一定了解后，来看看它如何实现在程序运行时分配内存。前面我们都将指针初始化为变量的地址；'变量是在编译时分配的有名称的内存，而指针只是
为可以通过名称直接访问的内存提供了一个别名'。

'指针真正的用武之地在于，在运行阶段分配未命名的内存以存储值'。在这种情况下，只能通过指针来访问内存。

在 C 语言中，可以用库函数 malloc() 来分配内存；在 C++ 中仍然可以这样做，但 C++ 还有更好的方法---new 运算符。

下面来试试这种新技术，在运行阶段为一个 int 值分配未命名的内存，并使用指针来访问这个值。这里的关键所在是 C++ 的 new 运算符。程序员要告诉 new，需要为
哪种数据类型分配内存；'new 将找到一个长度正确的内存块，并返回该内存块的地址'。程序员的责任是将该地址赋给一个指针。

下面是一个这样的示例:

int *pn = new int;

new int 告诉程序，需要适合存储 int 的内存。new 运算符根据类型来确定需要多少字节的内存。然后，它找到这样的内存，并返回其地址。接下来，将地址赋给 pn，pn 是
被声明为指向 int 的指针。现在，pn 是地址，而 *pn 是存储在那里的值。

将这种方法与将变量的地址赋给指针进行比较：

int higgens;
int *pt = &higgens;

在这两种情况（ pn 和 pt）下，都是将一个 int 变量的地址赋给了指针。在第二种情况下，可以通过名称 higgens 来访问该 int，在第一种情况下，则只能通过该指针
进行访问。

这引出了一个问题：pn 指向的内存没有名称，如何称呼它呢？ 我们说 pn 指向一个数据对象，这里的“对象”不是“面向对象编程”中的对象，而是一样“东西”。'术语“数据
对象”比“变量”更通用，它指的是为数据项分配的内存块'。因此，变量也是数据对象，但 pn 指向的内存不是变量。乍一看，处理数据对象的指针方法可能不太好用，但它使
程序在管理内存方面有更大的控制权。

为一个数据对象（可以是结构，也可以是基本类型）获得并指定分配内存的通用格式如下：

typeName * pointer_name = new typeName;

需要在两个地方指定数据类型：用来指定需要什么样的内存和用来声明合适的指针。当然，如果已经声明了相应类型的指针，则可以使用该指针，而不用再声明一个新的
指针。程序 use_new.cpp 演示了如何将 new 用于两种不同的类型。

// use_new.cpp

#include<iostream>

int main()
{
    using namespace std;
    int nights = 1001;
    int *pt = new int;
    *pt = 1001;

    cout << "nights value = ";
    cout << nights << ": location " << &nights << endl;
    cout << "int";
    cout << "night = " << *pt << ": location " << pt << endl;
    double *db = new double;
    *pd = 100000.111;
    cout << "double";
    cout << "value = " << *pd << ": location " << pd << endl;
    cout << "location of pointer pd = " << &pd << endl;
    cout << "size of pt " << sizeof(pt) << endl;
    cout << "size of *pt " << sizeof(*pt) << endl;
    cout << "size of pd " << sizeof(pd) << endl;
    cout << "size of *pd " << sizeof(*pd) << endl;
    return 0;
}

 » g++ --std=c++11 use_new.cpp
--------------------------------------------------------------------------------
 » ./a.out
nights value = 1001: location 0x7ffed134ad54
intnight = 1001: location 0x55754c6e9eb0
doublevalue = 100000: location 0x55754c6ea2e0
location of pointer pd = 0x7ffed134ad58
size of pt 8
size of *pt 4
size of pd 8
size of *pd 8

当然，内存位置的准确值随系统而异。

1. 该程序使用 new 分别为 int 类型和 double 类型的数据对象分配内存。这是在程序运行时进行的。指针 pt 和 pd 指向这两个数据对象，如果没有它们，将无法访问
这些内存单元。有了这两个指针，就可以像使用变量那样使用 *pt 和 *pd 了。将值赋给 *pt 和 *pd，从而将这些值赋给新的数据对象。同样，可以通过打印 *pt 和 *pd 
来显示这些值。

2. 该程序还指出了必须声明指针所指向的类型的原因之一。'地址本身只指出了对象存储地址的开始，而没有指出其类型（使用的字节数）'。从这两个值的地址可以知道，它
们都只是数字，并没有提供类型或长度信息。另外，指向 int 的指针的长度与指向 double 的指针相同。它们都是地址，但由于 use_new.cpp 声明了指针的类型，因此
程序知道 *pd 是 8 个字节的 double 值，*pt 是 4 个字节的 int 值。use_new.cpp 打印 *pd 的值时，cout 知道要读取多少字节以及如何解释它们。


// !! 内存被耗尽？

计算机可能会由于没有足够的内存而无法满足 new 的请求。在这种情况下，new通常会引发异常；而在较老的实现中，new 将返回 0。在 C++ 中，值为 0 的指针被称
为空指针（null pointer）。


// !! 使用 delete 释放内存

当需要内存时，可以使用 new 来请求，这只是 C++ 内存管理数据包中有魅力的一个方面。另一个方面是 delete 运算符，它使得在使用完内存后，能够将其归还给内存池，
这是通向最有效地使用内存的关键一步。归还或释放（free）的内存可供程序的其他部分使用。使用 delete 时，后面要加上指向内存块的指针（这些内存块最初是用 new 
分配的）:

int *ps = new int;
...
delete ps;

这将释放 ps 指向的内存，但不会删除指针 ps 本身。例如，可以将 ps 重新指向另一个新分配的内存块。一定要配对地使用 new 和 delete；否则将发生内存泄漏
（memory leak），也就是说，被分配的内存再也无法使用了。如果内存泄漏严重，则程序将由于不断寻找更多内存而终止。

不要尝试释放已经释放的内存块，C++ 标准指出，这样做的结果将是不确定的，这意味着什么情况都可能发生。

另外，不能使用 delete 来释放声明变量所获得的内存：

int *pt = new int;
...
delete pt;// okay
delete pt // not ok now
int jud = 10;
int *pt = &jud;
delete pt;// not allowed, memory not allocate by new


警告:
只能用 delete 来释放使用 new 分配的内存。然而，对空指针使用 delete 是安全的。

'一般来说，不要创建两个指向同一个内存块的指针，因为这将增加错误地删除同一个内存块两次的可能性'。

// !! 使用 new 来创建动态数组

'如果程序只需要一个值，则可能会声明一个简单变量，因为对于管理一个小型数据对象来说，这样做比使用 new 和指针更简单'，尽管给人留下的印象不那么深刻。

'通常，对于大型数据（如数组、字符串和结构），应使用 new，这正是 new 的用武之地'。

例如，假设要编写一个程序，它是否需要数组取决于运行时用户提供的信息:

1. '如果通过声明来创建数组，则在程序被编译时将为它分配内存空间'。不管程序最终是否使用数组，数组都在那里，它占用了内存。在编译时给数组分配内存被称为静态
    联编（static binding），意味着数组是在编译时加入到程序中的

2. 但使用 new 时，如果在运行阶段需要数组，则创建它；如果不需要，则不创建。还可以在程序运行时选择数组的长度。这被称为动态联编（dynamic binding），意味
   着'数组是在程序运行时创建的。这种数组叫作动态数组（dynamic array）'。使用静态联编时，必须在编写程序时指定数组的长度；使用动态联编时，程序将在运行时
   确定数组的长度。

下面来看一下关于动态数组的两个基本问题: 如何使用 C++ 的 new 运算符创建数组以及如何使用指针访问数组元素。

1．使用 new 创建动态数组

在 C++ 中，创建动态数组很容易；'只要将数组的元素类型和元素数目告诉 new 即可'。必须在类型名后加上方括号，其中包含元素数目。例如，要创建一个包含 10 个 
int 元素的数组，可以这样做：

int *psome = new int[10];// get a block of 10 ints

new 运算符返回第一个元素的地址。在这个例子中，该地址被赋给指针 psome。


当程序使用完 new 分配的内存块时，应使用 delete 释放它们。然而，对于使用 new 创建的数组，应使用另一种:

delete []psome;// free a dynamic array

方括号告诉程序，应释放整个数组，而不仅仅是指针指向的元素。

请注意 delete 和指针之间的方括号。如果使用 new 时，不带方括号，则使用 delete 时，也不应带方括号。如果使用 new 时带方括号，则使用 delete 时也应带方
括号。

'总之，使用 new 和 delete 时，应遵守以下规则':

1. 不要使用 delete 来释放不是 new 分配的内存

2. 不要使用 delete 释放同一个内存块两次

3. 如果使用 new [] 为数组分配内存，则应使用 delete[] 来释放

4. 对空指针应用 delete 是安全的

'现在我们回过头来讨论动态数组'。

psome 是指向一个 int（数组第一个元素）的指针。您的责任是跟踪内存块中的元素个数。也就是说，由于编译器不能对 psome 是指向 10 个整数中的第 1 个这种情况进行
跟踪，因此编写程序时，必须让程序跟踪元素的数目。

实际上，程序确实跟踪了分配的内存量，以便以后使用 delete [] 运算符时能够正确地释放这些内存。但这种信息不是公用的。例如，'不能使用 sizeof 运算符来确定动态
分配的数组包含的字节数'。

为数组分配内存的通用格式如下：

type_name * pointer_name = new type_name[num_elements];

使用 new 运算符可以确保内存块足以存储 num_elements 个类型为 type_name 的元素，而 pointer_name 将指向第 1 个元素。

// !! 使用动态数组

创建动态数组后，如何使用它呢？

首先，从概念上考虑这个问题。下面的语句创建指针 psome，它指向包含 10 个 int 值的内存块中的第 1 个元素：

int *psome = new int[10];

可以将它看作是一根指向该元素的手指。假设 int 占 4 个字节，则将手指沿正确的方向移动 4 个字节，手指将指向第 2 个元素。总共有 10 个元素，这就是手指的移动
范围。因此，'new 语句提供了识别内存块中每个元素所需的全部信息'。

现在从实际角度考虑这个问题。如何访问其中的元素呢？

第一个元素不成问题。由于 psome 指向数组的第 1 个元素，因此 *psome 是第 1 个元素的值。这样，还有 9 个元素。如果没有使用过 C 语言，下面这种最简单的方法
可能会令您大吃一惊：'只要把指针当作数组名使用即可'。也就是说，对于第 1 个元素，psome[0], 而不是 *psome；对于第 2 个元素，可以使用 psome[1]，依此类推。
这样，使用指针来访问动态数组就非常简单了，虽然还不知道为何这种方法管用。

'可以这样做的原因是，C 和 C++ 内部都使用指针来处理数组。数组和指针基本等价是 C 和 C++ 的优点之一'


程序 arraynew.cpp 演示了如何使用 new 来创建动态数组以及使用数组表示法来访问元素；它还指出了指针和真正的数组名之间的根本差别。

// arraynew.cpp
#include<iostream>

int main()
{
    using namespace std;
    double *p3 = new double[3];// space for 3 doubles
    p3[0] = 0.2;
    p3[1] = 0.5;
    p3[2] = 0.8;

    cout << "p3[1] is " << p3[1] <<"\n";
    p3 = p3 + 1;
    cout << "Now p3[0] is " << p3[0] <<".\n" << "and p3[1] is " << p3[1] << ". \n";
    p3 = p3 - 1;// point back to begin
    delete[] p3;
    return 0;
}

下面是该程序的输出：

 » g++ --std=c++11 arraynew.cpp 
--------------------------------------------------------------------------------
 » ./a.out
p3[1] is 0.5
Now p3[0] is 0.5.
and p3[1] is 0.8.


从中可知， arraynew.cpp 将指针 p3 当作数组名来使用，p3[0] 为第1个元素，依次类推。

下面的代码行指出了数组名和指针之间的根本差别:

p3 = p3 + 1;// ok for pointer, wrong for array name

'不能修改数组名的值。但指针是变量，因此可以修改它的值'。请注意将 p3 加 1 的效果。表达式 p3[0] 现在指的是数组的第 2 个值。因此，将 p3 加 1 导致它指向第 2
个元素而不是第 1 个。将它减 1 后，指针将指向原来的值，这样程序便可以给 delete[] 提供正确的地址。相邻的int地址通常相差 2 个字节或 4 个字节，而将 p3 加 1 
后，它将指向下一个元素的地址，这表明指针算术有一些特别的地方。情况确实如此。


// !!  指针、数组和指针算术

'指针和数组基本等价的原因在于指针算术（pointer arithmetic）和 C++ 内部处理数组的方式'。首先，我们来看一看算术。将整数变量加 1 后，其值将增加 1；但将'指针
变量加 1 后，增加的量等于它指向的类型的字节数'。将指向 double 的指针加 1 后，如果系统对 double 使用 8 个字节存储，则数值将增加 8；将指向 short 的指针加 
1 后，如果系统对 short 使用 2 个字节存储，则指针值将增加 2。

程序 清单4.19 演示了这种令人吃惊的现象，它还说明了另一点：C++ 将数组名解释为地址。

// addpntrs.cpp

#include<iostream>

int main()
{
    using namespace std;
    double wages[3] = {10000.0,20000.0,300000.0};
    short stacks[3] = {3,1,2};

    double *pd = wages;
    short *ps = &stacks[0];

    cout << "pd - " << pd << " *pd " << *pd << endl;
    pd = pd + 1;
    cout << "pd - " << pd << " *pd " << *pd << endl;
    cout << "ps - " << ps << " *ps " << *ps << endl;
    ps = ps + 1;
    cout << "ps - " << ps << " *ps " << *ps << endl;
    cout << "stacks[0] - " << stacks[0] << " stacks[1] " << stacks[1] << endl;
    cout << "*stacks = " << *stacks << " *(stacks+1)" << *(stacks + 1) << endl;
    cout << sizeof(wages) << "= size of wages array\n";
    cout << sizeof(stacks) << "= size of stacks array\n";
    return 0;
}

 » g++ --std=c++11 addpntrs.cpp
--------------------------------------------------------------------------------

 » ./a.out
pd - 0x7fffc07a3230 *pd 10000
pd - 0x7fffc07a3238 *pd 20000
ps - 0x7fffc07a322a *ps 3
ps - 0x7fffc07a322c *ps 1
stacks[0] - 3 stacks[1] 1
*stacks = 3 *(stacks+1)1
24= size of wages array
6= size of stacks array

在多数情况下，C++ 将数组名解释为数组第 1 个元素的地址。

注意：

'将指针变量加  1后，其增加的值等于指向的类型占用的字节数'。

现在来看一看数组表达式 stacks[1]。C++ 编译器将该表达式看作是 *（stacks + 1），这意味着先计算数组第 2 个元素的地址，然后找到存储在那里的值。最后的
结果便是 stacks[1] 的含义（运算符优先级要求使用括号，如果不使用括号，将给 *stacks 加 1，而不是给 stacks 加 1）。

从该程序的输出可知，*（stacks + 1） 和 stacks[1] 是等价的。同样， *（stacks + 2） 和 stacks[2] 也是等价的。通常，使用数组表示法时，C++ 都执行下面
的转换：

arrayname[i] becomes *(arrayname+i);

如果使用的是指针，而不是数组名，则 C++ 也将执行同样的转换:

pointer_name[i] becomes *(pointer_name+i);

因此，在很多情况下，可以相同的方式使用指针名和数组名。对于它们，可以使用数组方括号表示法，也可以使用解除引用运算符（*）。在多数表达式中，它们都表示地址。
'区别之一是，可以修改指针的值，而数组名是常量'。另一个区别是，'对数组应用 sizeof 运算符得到的是数组的长度，而对指针应用 sizeof 得到的是指针的长度'，即使
指针指向的是一个数组。


// !! 数组的地址

对数组取地址时，数组名也不会被解释为其地址。等等，数组名难道不被解释为数组的地址吗？不完全如此：数组名被解释为其第一个元素的地址，而对数组名应用地址运算符
时，得到的是整个数组的地址：

short tell[10];// tell a array of 20 bytes
cout << tell << endl;//  display address &tell[0]
cout << &tell << endl; //  display address of whole array

从数字上说，这两个地址相同；但从概念上说，&tell[0]（即 tell）是一个2字节内存块的地址，而 &tell 是一个 20 字节内存块的地址。

因此，表达式 tell + 1 将地址值加2，而表达式&(tell + 1) 将地址加 20。换句话说，tell 是一个 short 指针（* short），而 &tell 是一个这样的指针，
即指向包含 10 个元素的 short 数组（short (*) [10]）。


// !!  指针小结

1. 声明指针

要声明指向特定类型的指针，请使用下面的格式：

typename * pointer_name;

下面是一些示例：

double *pn;
char *pc;

其中，pn 和 pc 都是指针，而 double *和 char * 是指向 double 的指针和指向 char 的指针。


2. 给指针赋值

'应将内存地址赋给指针。可以对变量名应用 & 运算符，来获得被命名的内存的地址，new 运算符返回未命名的内存的地址'。


3. 对指针解除引用

'对指针解除引用意味着获得指针指向的值'。对指针应用解除引用或间接值运算符（*）来解除引用。


4. 区分指针和指针所指向的值

如果 pt 是指向 int 的指针，则 *pt 不是指向 int 的指针，而是完全等同于一个 int 类型的变量。pt 才是指针。


5. 数组名

在多数情况下，C++ 将数组名视为数组的第一个元素的地址。


6. 指针算术

'C++ 允许将指针和整数相加。加 1 的结果等于原来的地址值加上指向的对象占用的总字节数'。还可以将一个指针减去另一个指针，获得两个指针的差。后一种运算
将得到一个整数，仅当两个指针指向同一个数组（也可以指向超出结尾的一个位置）时，这种运算才有意义, 这将得到两个元素的间隔。


7. 数组的动态联编和静态联编

使用数组声明来创建数组时，将采用静态联编，即数组的长度在编译时设置：

double arr[3];// static binding, size fixed at compile time

使用 new[] 运算符创建数组时，将采用动态联编（动态数组），即将在运行时为数组分配空间，其长度也将在运行时设置。使用完这种数组后，应使用 delete []释放
其占用的内存：

int size;
cin >> size;
int *ps = new int[size];

...

delete[]ps;


8. 数组表示法和指针表示法

'使用方括号数组表示法等同于对指针解除引用'：

tacos[0] equals *tacos
tacos[1] equals *(tacos + 1)

数组名和指针变量都是如此，因此对于指针和数组名，既可以使用指针表示法，也可以使用数组表示法。


//  !! 指针和字符串

数组和指针的特殊关系可以扩展到 C-Style string。请看下面的代码:

char flower[10] = "rose";
cout << flower << "s are red\n";

数组名是第一个元素的地址，因此 cout 语句中的 flower 是包含字符 r 的 char 元素的地址。cout 对象认为 char 的地址是字符串的地址，因此它打印该地址处
的字符，然后继续打印后面的字符，直到遇到空字符（\0）为止。'总之，如果给 cout 提供一个字符的地址，则它将从该字符开始打印，直到遇到空字符为止'。

这里的关键不在于 flower 是数组名，而在于 flower 是一个 char 的地址。这意味着可以将指向 char 的指针变量作为 cout 的参数，因为它也是 char 的地址。
当然，该指针指向字符串的开头，稍后将核实这一点。

前面的 cout 语句中最后一部分的情况如何呢？

如果 flower 是字符串第一个字符的地址，则表达式 “s are red\n” 是什么呢？为了 与cout 对字符串输出的处理保持一致，这个用引号括起的字符串也应当是一个地址。
'在 C++ 中，用引号括起的字符串像数组名一样，也是第一个元素的地址'。上述代码不会将整个字符串发送给 cout，而只是发送该字符串的地址。'这意味着对于数组中的
字符串、用引号括起的字符串常量以及指针所描述的字符串，处理的方式是一样的，都将传递它们的地址'。与逐个传递字符串中的所有字符相比，这样做的工作量确实要少。


程序 ptrstr.cpp 演示了如何使用不同形式的字符串。它使用了两个字符串库中的函数。函数 strlen() 我们以前用过，它返回字符串的长度。函数 strcpy() 将字符串从
一个位置复制到另一个位置。这两个函数的原型都位于头文件 cstring 中。该程序还通过注释指出了应尽量避免的错误使用指针的方式。

// ptrstr.cpp
#include <iostream>
#include <cstring>

int main()
{
    using namespace std;
    char animal[20] = "bear";
    const char * bird = "wren";
    char * ps;

    cout << animal << " and " << bird << "\n";
    // cout << ps << "\n";// may display garbage or cause a crash
    cout << "Enter a kind of animal: ";
    cin >> animal;// ok, if input < 20 characters
    // cin >> ps;// Too horrible, ps doesn't' pointer to allocated space

    ps = animal;
    cout << ps << "\n";
    cout << "Before using strcpy(): " << "\n";
    cout << animal << " at " << (int*)animal << "\n";
    cout << ps << " at " << (int*)ps << "\n";
    ps = new char[strlen(animal) + 1];// get new storage
    strcpy(ps,animal);
    cout << " After Using strcpy():\n";
    cout << animal << " at " << (int*)animal << "\n";
    cout << ps << " at " << (int*)ps << "\n";
    delete[] ps;
    return 0;
}

 » g++ --std=c++11 ptrstr.cpp
--------------------------------------------------------------------------------
 » ./a.out
bear and wren
Enter a kind of animal: monkey
monkey
Before using strcpy(): 
monkey at 0x7ffd7f5ea390
monkey at 0x7ffd7f5ea390
 After Using strcpy():
monkey at 0x7ffd7f5ea390
monkey at 0x55da410f16d0


程序创建了一个 char 数组（animal）和两个指向 char 的指针变量（bird 和 ps）。该程序首先将 animal 数组初始化为字符串“bear”，就像初始化数组一样。然后，
程序执行了一些新的操作，将 char 指针初始化为指向一个字符串：

 const char * bird = "wren";

记住，“wren” 实际表示的是字符串的地址，因此这条语句将 “wren” 的地址赋给了 bird 指针。一般来说，编译器在内存留出一些空间，以存储程序源代码中所有用引号括
起的字符串，并将每个被存储的字符串与其地址关联起来

字符串字面值是常量，这就是为什么代码在声明中使用关键字 const 的原因。以这种方式使用 const 意味着可以用 bird 来访问字符串，但不能修改它。

对于输入，情况有点不同。只要输入比较短，能够被存储在数组中，则使用数组 animal 进行输入将是安全的。然而，使用 bird 来进行输入并不合适：

1. '有些编译器将字符串字面值视为只读常量，如果试图修改它们，将导致运行阶段错误'。在 C++ 中，字符串字面值都将被视为常量，但并不是所有的编译器都对以前的行为做
    了这样的修改。

2. 有些编译器只使用字符串字面值的一个副本来表示程序中所有的该字面值

试图将信息读入 ps 指向的位置将更糟。'由于 ps 没有被初始化，因此并不知道信息将被存储在哪里，这甚至可能改写内存中的信息'。幸运的是，要避免这种问题很容易
—只要使用足够大的 char 数组来接收输入即可。'请不要使用字符串常量或未被初始化的指针来接收输入'。

为避免这些问题，也可以使用 std::string 对象，而不是数组。

警告：

在将字符串读入程序时，应使用已分配的内存地址。该地址可以是数组名，也可以是使用 new 初始化过的指针。

接下来，请注意下述代码完成的工作：

ps = animal;// set ps point to string
...
cout << animal << " at " << (int*)animal << "\n";
cout << ps << " at " << (int*)ps << "\n";

它将生成下面的输出：

monkey at 0x7ffd7f5ea390
monkey at 0x7ffd7f5ea390

一般来说，如果给 cout 提供一个指针，它将打印地址。但如果指针的类型为 char*，则 cout 将显示指向的字符串。'如果想要显示字符串的地址，则必须将这种指针强制转换为另
一种指针类型'，如 int *。因此，ps 显示为字符串 “monkey”， 而 （int *）ps 显示为该字符串的地址。注意，'将 animal 赋给 ps 并不会复制字符串，而只是复制地址'。
这样，这两个指针将指向相同的内存单元和字符串。

要获得字符串的副本，还需要做其他工作。首先，需要分配内存来存储该字符串，这可以通过声明另一个数组或使用 new 来完成。后一种方法使得能够根据字符串的长度来指定所
需的空间：

ps = new char[strlen(animal)+1];

字符串 “monkey” 不能填满整个 animal 数组，因此这样做浪费了空间。'使用 strlen() 来确定字符串的长度，并将它加 1 来获得包含空字符时该字符串的长度'。随后，
程序使用 new 来分配刚好足够存储该字符串的空间。


接下来，需要将 animal 数组中的字符串复制到新分配的空间中。将 animal 赋给 ps 是不可行的，因为这样只能修改存储在 ps 中的地址，从而失去程序访问新分配内存的
唯一途径。需要使用库函数 strcpy()：

strcpy(ps,animal);

strcpy() 函数接受 2 个参数。第一个是目标地址，第二个是要复制的字符串的地址。'您应确保分配了目标空间，并有足够的空间来存储副本'。在这里，我们用 strlen() 来确定
所需的空间，并使用 new 获得可用的内存。

通过使用 strcpy() 和 new，将获得 “monkey” 的两个独立副本：

monkey at 0x7ffd7f5ea390
monkey at 0x55da410f16d0

另外，new 在离 animal 数组很远的地方找到了所需的内存空间。


经常需要将字符串放到数组中。'初始化数组时，请使用 = 运算符；否则应使用 strcpy()或 strncpy()'。strcpy() 其工作原理如下：

char food[20] = "carrots";
strcpy(food,"flan");

注意，类似下面这样的代码可能导致问题，因为 food 数组比字符串小：

strcpy(food,"good good study, day day up,oh yeah!");

'在这种情况下，函数将字符串中剩余的部分复制到数组后面的内存字节中，这可能会覆盖程序正在使用的其他内存'。

要避免这种问题，请使用 strncpy()。该函数还接受第 3 个参数—要复制的最大字符数。然而要注意的是:'如果该函数在到达字符串结尾之前，目标内存已经用完，则它将不会添加空字符'。
因此，应该这样使用该函数：

strncpy(food,"good good study, day day up,oh yeah!",19);
food[19] = '\0';

您对使用 C-Style string 和 cstring 库的一些方面有了了解后，便可以理解为何使用 C++ string 类型更为简单了： 您不用担心字符串会导致数组越界，并可以使用赋值运算符而
不是函数 strcpy() 和 strncpy()。


// !!  使用 new 创建动态结构

'在运行时创建数组优于在编译时创建数组，对于结构也是如此'。需要在程序运行时为结构分配所需的空间，这也可以使用 new 运算符来完成。通过使用 new 可以创建动态结构。同样，
'“动态”意味着内存是在运行时，而不是编译时分配的'。将 new 用于结构由两步组成：创建结构和访问其成员。要创建结构，需要同时使用结构类型和 new。例如，要创建一个未命名的
 inflatable 类型，并将其地址赋给一个指针，可以这样做:

 inflatable * ps = new inflatable;

这将把足以存储 inflatable 结构的一块可用内存的地址赋给 ps, 这种句法和 C++ 的内置类型完全相同。

'创建动态结构时，不能将成员运算符句点用于结构名，因为这种结构没有名称，只是知道它的地址。C++ 专门为这种情况提供了一个运算符：箭头成员运算符（−>）'。该运算符由连字符
和大于号组成，可用于指向结构的指针，就像点运算符可用于结构名一样。例如，如果 ps 指向一个 inflatable 结构，则 ps−>price 是被指向的结构的 price 成员。


另一种访问结构成员的方法是，如果 ps 是指向结构的指针，则 *ps 就是被指向的值—结构本身。由于 *ps 是一个结构，因此 （*ps）.price 是该结构的 price 成员。
C++ 的运算符优先规则要求使用括号。


一个使用 new 和 delete 的示例:

下面介绍一个使用 new 和 delete 来存储通过键盘输入的字符串的示例。程序 delete.cpp 定义了一个函数 getname()，该函数返回一个指向输入字符串的指针。该函数将输入读入到
一个大型的临时数组中，然后使用 new[] 创建一个刚好能够存储该输入字符串的内存块，并返回一个指向该内存块的指针。对于读取大量字符串的程序，这种方法可以节省大量内存（实际编
写程序时，使用 string 类将更容易，因为这样可以使用内置的 new 和 delete）。

假设程序要读取 100 个字符串，其中最大的字符串包含 79 个字符，而大多数字符串都短得多。如果用 char 数组来存储这些字符串，则需要 1000 个数组，其中每个数组的长度为
 80 个字符。这总共需要 80000 个字节，而其中的很多内存没有被使用。另一种方法是，创建一个数组，它包含 100 个指向 char 的指针，然后使用 new 根据每个字符串的需要
 分配相应数量的内存。这将节省几万个字节。'是根据输入来分配内存，而不是为每个字符串使用一个大型数组'。另外，还可以使用 new 根据需要的指针数量来分配空间。就目前而言
 ，这有点不切实际，即使是使用 1000 个指针的数组也是这样，不过程序 delete.cpp 还是演示了一些技巧。另外，为演示 delete 是如何工作的，该程序还用它来释放内存以便
 能够重新使用。

 // delete.cpp

#include <iostream>
#include <cstring>

int main()
{
    using namespace std;
    char * name;
    name = getName();
    cout << name << " at " << (int*)name << "\n";
    delete [] name;
    return 0;
}

char * getName()
{
    char tmp[80];
    cout << "Enter last name: ";
    cin >> tmp;
    char *pn = new char[strlen(tmp) + 1];
    strcpy(pn, tmp);
    return pn;
}

 » g++ --std=c++11 delete.cpp
--------------------------------------------------------------------------------
 » ./a.out

Enter last name: kittybaby 
kittybaby at 0x5622a8a9e6d0

来看一下程序 delete.cpp 中的函数 getname()。它使用 cin 将输入的单词放到 tmp 数组中，然后使用 new 分配新内存，以存储该单词。程序需要 strlen（temp）+ 1 
个字符（包括空字符）来存储该字符串，因此将这个值提供给 new。获得空间后，getname() 使用标准库函数 strcpy() 将 tmp 中的字符串复制到新的内存块中。该函数并不
检查内存块是否能够容纳字符串，但 getname() 通过使用 new 请求合适的字节数来完成了这样的工作。最后，函数返回 pn，这是字符串副本的地址。

在 main() 中，返回值（地址）被赋给指针 name。该指针是在 main() 中定义的，但它指向 getname() 函数中分配的内存块。然后，程序打印该字符串及其地址。
接下来，在释放 name 指向的内存块后，main() 再次调用 getname(), C++ 不保证新释放的内存就是下一次使用 new 时选择的内存，从程序运行结果可知，确实不是。
在这个例子中，getname() 分配内存，而 main() 释放内存。'将 new 和 delete 放在不同的函数中通常并不是个好办法，因为这样很容易忘记使用 delete'。不过这个
例子确实把 new 和 delete 分开放置了，只是为了说明这样做也是可以的。


// !! 自动存储、静态存储和动态存储

'根据用于分配内存的方法，C++ 有 3 种管理数据内存的方式：自动存储、静态存储和动态存储（有时也叫作自由存储空间或堆）'。在存在时间的长短方面，以这 3 种方式分配
的数据对象各不相同。下面简要地介绍每种类型（C++11 新增了第四种类型—线程存储）。

1. 自动存储

'在函数内部定义的常规变量使用自动存储空间，被称为自动变量（automatic variable）'，这意味着它们在所属的函数被调用时自动产生，在该函数结束时消亡。'实际上，自动
变量是一个局部变量，其作用域为包含它的代码块'。代码块是被包含在花括号中的一段代码。到目前为止，我们使用的所有代码块都是整个函数。然而，在下一章将会看到，函数内也
可以有代码块。如果在其中的某个代码块定义了一个变量，则该变量仅在程序执行该代码块中的代码时存在。'自动变量通常存储在栈中'。这意味着执行代码块时，其中的变量将依次加
入到栈中，而在离开代码块时，将按相反的顺序释放这些变量，这被称为后进先出（LIFO）。因此，在程序执行过程中，栈将不断地增大和缩小。

2. 静态存储

'静态存储是整个程序执行期间都存在的存储方式'。使变量成为静态的方式有两种: 一种是在函数外面定义它; 另一种是在声明变量时使用关键字 static

static double fee = 23.43;

在 K&R C 中，只能初始化静态数组和静态结构，而 C++ Release 2.0（及后续版本）和cANSI C 中，也可以初始化自动数组和自动结构。然而，一些您可能已经发现，有些 
C++ 实现还不支持对自动数组和自动结构的初始化。自动存储和静态存储的关键在于：这些方法严格地限制了变量的寿命。变量可能存在于程序的整个生命周期（静态变量），也可能
只是在特定函数被执行时存在（自动变量）。

3. 动态存储

'new 和 delete 运算符提供了一种比自动变量和静态变量更灵活的方法'。它们管理了一个内存池，这在 C++ 中被称为自由存储空间（free store）或堆（heap）。 该内存池同
用于静态变量和自动变量的内存是分开的。new 和 delete 让您能够在一个函数中分配内存，而在另一个函数中释放它。因此，'数据的生命周期不完全受程序或函数的生存时间控制'。
与使用'常规变量相比，使用 new 和 delete 让程序员对程序如何使用内存有更大的控制权'。然而，内存管理也更复杂了。'在栈中，自动添加和删除机制使得占用的内存总是连续的，
但 new 和 delete 的相互影响可能导致占用的自由存储区不连续，这使得跟踪新分配内存的位置更困难'。


// !! 栈、堆和内存泄漏

如果使用 new 运算符在自由存储空间（或堆）上创建变量后，没有调用 delete，将发生什么情况呢 ？

如果没有调用 delete，则即使包含指针的内存由于作用域规则和对象生命周期的原因而被释放，在自由存储空间上动态分配的变量或结构也将继续存在。实际上，将会无法访问自由存储空
间中的结构，因为指向这些内存的指针无效。这将导致内存泄漏。'被泄漏的内存将在程序的整个生命周期内都不可使用；这些内存被分配出去，但无法收回'。极端情况（不过不常见）是，内
存泄漏可能会非常严重，以致于应用程序可用的内存被耗尽，出现内存耗尽错误，导致程序崩溃。另外，这种泄漏还会给一些操作系统或在相同的内存空间中运行的应用程序带来负面影响，导
致它们崩溃。即使是最好的程序员和软件公司，也可能导致内存泄漏。要避免内存泄漏，最好是养成这样一种习惯，即同时使用 new 和 delete 运算符，在自由存储空间上动态分配内存，随
后便释放它。'C++ 智能指针有助于自动完成这种任务'。


// !! 数组的替代品


1. 模板类 vector

模板类 vector 类似于 string 类，也是一种动态数组。您可以在运行阶段设置 vector 对象的长度，可在末尾附加新数据，还可在中间插入新数据。基本上，它是使用 new 创建动态数组的
替代品。实际上，vector 类确实使用 new 和 delete 来管理内存，但这种工作是自动完成的。这里不深入探讨模板类意味着什么，而只介绍一些基本的实用知识。首先，要使用 vector 对象
，必须包含头文件 vector。其次，vector 包含在名称空间 std 中，因此您可使用 using 编译指令、using 声明或 std::vector。第三，模板使用不同的语法来指出它存储的数据类型。
第四，vector 类使用不同的语法来指定元素数。



2. 模板类 array（C++11）

'vector 类的功能比数组强大，但付出的代价是效率稍低'。如果您需要的是长度固定的数组，使用数组是更佳的选择，但代价是不那么方便和安全。有鉴于此，C++11 新增了模板类 array，它
也位于名称空间 std 中。'与数组一样，array 对象的长度也是固定的，也使用栈（静态内存分配），而不是自由存储区，因此其效率与数组相同，但更方便，更安全'。要创建 array 对象，需
要包含头文件 array。array 对象的创建语法与 vector 稍有不同：



#include<array>

...
using namespace std;

array<int,5> ai;
array<double,5> ad = {1.2,1.2,1.2,1.2,1.2};

在 C++11 中，可将列表初始化用于 vector 和 array 对象，但在 C++98 中，不能对 vector 对象这样做。


4. 比较数组、vector 对象和 array 对象

要了解数组、vector 对象和 array 对象的相似和不同之处，最简单的方式可能是看一个使用它们的简单示例，如程序 choices.cpp 所示。

// choices.cpp

#include <vector>
#include<array>
#include<iostream>

int main()
{
    using namespace std;

    // C, original C++
    double a1[4] = {1.2,2.4,4.4,2.7};
    // C++ 98 STL
    vector<double> a2(4);// create a vector with 4 elements
    a2[0] = 1.0/3.0; 
    a2[1] = 1.0/5.0; 
    a2[2] = 1.0/7.0;
    a2[3] = 1.0/9.0; 

    // C++ 11 ---create and initialize array object
    array<double,4> a3 = {1.0,2.0,3.0,4.2};
    array<double,4> a4;

    a4 = a3; // valid for array object of some size

    // using array notation
    cout <<"a1[2] = " << a1[2] << " at " << &a1[2] << endl;
    cout <<"a2[2] = " << a2[2] << " at " << &a2[2] << endl;
    cout <<"a3[2] = " << a3[2] << " at " << &a3[2] << endl;
    cout <<"a4[2] = " << a4[2] << " at " << &a4[2] << endl;

    a1[-2] = 20.222;
    cout <<"a1[-2] = " << a1[-2] << " at " << &a1[-2] << endl;
    cout <<"a3[2] = " << a3[2] << " at " << &a3[2] << endl;
    cout <<"a4[2] = " << a4[2] << " at " << &a4[2] << endl;
    return 0;
}

 » g++ --std=c++11 choices.cpp
--------------------------------------------------------------------------------
 » ./a.out
a1[2] = 4.4 at 0x7ffda1f4e640
a2[2] = 0.142857 at 0x55ba3791fec0
a3[2] = 3 at 0x7ffda1f4e660
a4[2] = 3 at 0x7ffda1f4e680
a1[-2] = 20.222 at 0x7ffda1f4e620
a3[2] = 3 at 0x7ffda1f4e660
a4[2] = 3 at 0x7ffda1f4e680


1. 首先，注意到无论是数组、vector 对象还是 array 对象，都可使用'标准数组表示法来访问各个元素'

2. 其次，从地址可知，array 对象和数组存储在相同的内存区域（即栈）中，而 vector 对象存储在另一个区域（自由存储区或堆）中

3. 第三，注意到可以将一个 array 对象赋给另一个 array 对象；而对于数组，必须逐元素复制数据。

接下来，下面一行代码需要特别注意:

a1[-2] = 20.222;

索引 -2 是什么意思呢？ 本章前面说过，这将被转换为如下代码：

*(a1 - 2) = 20.222;

其含义如下：找到 a1 指向的地方，向前移两个 double 元素，并将 20.222 存储到目的地。也就是说，'将信息存储到数组的外面'。与 C 语言
一样，C++ 也不检查这种超界错误。在这个示例中，这个位置位于 array 对象 a3 中。其他编译器可能将 20.222 放在 a4 中，甚至做出更糟糕
的选择。这表明数组的行为是不安全的。

vector 和 array 对象能够禁止这种行为吗？

如果您让它们禁止，它们就能禁止。也就是说，您仍可编写不安全的代码，如下所示：

a2[-2] = 22;
a3[200] = 12;

然而，您还有其他选择。一种选择是使用成员函数 at()。就像可以使用 cin 对象的成员函数 getline() 一样，您也可以使用 vector 和 array 
对象的成员函数 at()：

a2.at(1) = 12;

中括号表示法和成员函数 at() 的差别在于，'使用 at() 时将在运行期间捕获非法索引，而程序默认将中断。这种额外检查的代价是运行时间更长，这就
是 C++ 允许您使用任何一种表示法的原因所在'。另外，这些类还让您能够降低意外超界错误的概率。例如， 它们包含成员函数 begin() 和 end()，
让您能够确定边界，以免无意间超界。

// !!总结














































