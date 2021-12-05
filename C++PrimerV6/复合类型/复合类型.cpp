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


结构声明的位置很重要。对于 structur.cpp 而言，有两种选择。可以将声明放在 main() 函数中，紧跟在开始括号的后面。另一种选择是将声明放到 main() 的前面，这
里采用的便是这种方式，'位于函数外面的声明被称为外部声明'。对于这个程序来说，两种选择之间没有实际区别。但是对于那些包含两个或更多函数的程序来说，差别很大。'外
部声明可以被其后面的任何函数使用，而内部声明只能被该声明所属的函数使用'。通常应使用外部声明，这样所有函数都可以使用这种类型的结构

变量也可以在函数内部和外部定义，外部变量由所有的函数共享（这将在第9章做更详细的介绍）。C++ 不提倡使用外部变量，但提倡使用外部结构声明。另外，在外部声明符号
常量通常更合理。


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

答案是肯定的，只要您使用的编译器支持对以 string 对象作为成员的结构进行初始化。'一定要让结构定义能够访问名称空间 std'。为此，可以将编译指令 using 移到结
构定义之前；也可以像前面那样，将 name 的类型声明为 std::string。

// !! 其他结构属性

'C++ 使用户定义的类型与内置类型尽可能相似'。

例如，可以将结构作为参数传递给函数，也可以让函数返回一个结构。另外，还可以使用赋值运算符（=）将结构赋给另一个同类型的结构，这样结构中每个成员都将被设置为
另一个结构中相应成员的值，即使成员是数组。这种赋值被称为成员赋值（memberwise assignment）

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

inflatable 结构包含一个数组（name）。也可以创建元素为结构的数组，方法和创建基本类型数组完全相同。例如，要创建一个包含 100 个 inflatable 结构的数组，
可以这样做:

inflatable gifts[100]；

这样，gifts 将是一个 inflatable 数组，其中的每个元素（如 gifts[0] 或 gifts[99]）都是 inflatable 对象，可以与成员运算符一起使用：

cin >> gifts[0].volume;
cout << gifts[99].price << endl;

记住，gifts 本身是一个数组，而不是结构，因此像 gifts.price 这样的表述是无效的。

要初始化结构数组，可以结合使用初始化数组的规则（用逗号分隔每个元素的值，并将这些值用花括号括起）和初始化结构的规则（用逗号分隔每个成员的值，并将这些值用花括号
括起）。由于数组中的每个元素都是结构，因此可以使用结构初始化的方式来提供它的值。因此，最终结果为一个被括在花括号中、用逗号分隔的值列表，其中每个值本身又是一个
被括在花括号中、用逗号分隔的值列表:

inflatable guests[2] = 
{
    {"bambi",0.5,21.22},
    {"joooo",4.3,32.45}
};

可以按自己喜欢的方式来格式化它们。例如，两个初始化位于同一行，而每个结构成员的初始化各占一行。


// !! 结构中的位字段

与 C 语言一样，'C++ 也允许指定占用特定位数的结构成员'，这使得创建与某个硬件设备上的寄存器对应的数据结构非常方便。

字段的类型应为整型或枚举，接下来是冒号，冒号后面是一个数字，它指定了使用的位数。'可以使用没有名称的字段来提供间距'。'每个成员都被称为位字段（bit field）'。
下面是一个例子:

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

也就是说，结构可以同时存储 int、long 和 double，共用体只能存储 int、long 或 double。共用体的句法与结构相似，但含义不同。例如，请看下面的声明:

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

因此，pail 有时可以是 int 变量，而有时又可以是 double 变量。'由于共用体每次只能存储一个值，因此它必须有足够的空间来存储最大的成员，所以，共用体的
长度为其最大成员的长度'。

'共用体的用途之一是，当数据项使用两种或更多种格式（但不会同时使用）时，可节省空间'。

例如，假设管理一个小商品目录，其中有一些商品的 ID 为整数，而另一些的 ID 为字符串。在这种情况下，可以这样做:

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
C++ 还用于嵌入式系统编程，如控制烤箱、MP3播放器或火星漫步者的处理器。对这些应用程序来说，内存可能非常宝贵。'另外，共用体常用于操作系统数据结构或硬件数据结构'。





