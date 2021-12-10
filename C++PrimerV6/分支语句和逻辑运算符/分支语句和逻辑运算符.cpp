// !! 分支语句和逻辑运算符

设计智能程序的一个关键是使程序具有决策能力。

现在，来研究一下 C++ 是如何使用分支语句在可选择的操作中做出决定的。程序应使用哪一种防止吸血鬼的方案（大蒜还是十字架）呢？用户选
择了哪个菜单选项呢？ 用户是否输入了 0？C++ 提供了 if 和 switch 语句来进行决策


// !! if 语句

当 C++ 程序必须决定是否执行某个操作时，通常使用 if 语句来实现选择。if 有两种格式：if 和 if else。首先看一看简单的 if，它模仿英
语，如“If you have a Captain Cookie card, you get a free cookie（如果您有一张 Captain Cookie 卡，就可获得免费的小甜饼）”。
如果测试条件为 true，则 if 语句将引导程序执行语句或语句块；如果条件是 false，程序将跳过这条语句或语句块。因此，if 语句让程序能够决定
是否应执行特定的语句。

if(test_condition)
  statement;

如果 test-condition（测试条件）为 true，则程序将执行 statement（语句），后者既可以是一条语句，也可以是语句块。如果测试条件为 false，
则程序将跳过语句。和循环测试条件一样，if 测试条件也将被强制转换为 bool 值，因此 0 将被转换为 false，非零为 true。整个 if 语句被视为一
条语句


例如，假设读者希望程序计算输入中的空格数和字符总数，则可以在 while 循环中使用 cin.get（char） 来读取字符，然后使用 if 语句识别空格字符并
计算其总数。程序 if.cpp 完成了这项工作，它使用句点（.）来确定句子的结尾。

// if.cpp
#include<iostream>

int main()
{
    using std::cin;
    using std::cout;
    char ch;
    int spaces = 0;
    int total = 0;
    cin.get(ch);
    while (ch != '.')
    {
        if(ch == ' ')
        {
            ++spaces;
        }
        ++total;
        cin.get(ch);
    }
    cout << "spaces: " << spaces << "\n";
    cout << "total: " << total << "\n";
    return 0;
}


 » g++ --std=c++11 if.cpp
-------------------------------------------------------------------------------
 » ./a.out
kill bill   .
spaces: 4
total: 12

正如程序中的注释指出的，仅当 ch 为空格时，语句 ++spaces ;才被执行。因为语句 ++total ;位于 if 语句的外面，因此在每轮循环中都将被执行。
注意，字符总数中包括按回车键生成的换行符。

// !! if else 语句

if 语句让程序决定是否执行特定的语句或语句块，而 if else 语句则让程序决定执行两条语句或语句块中的哪一条，这种语句对于选择其中一种操作很有用。C++ 
的 if else 语句模仿了简单的英语，如 “If you have a Captain Cookie card, you get a Cookie Plus Plus, else you just get a Cookie 
d'Ordinaire（如果您拥有 Captain Cookie 卡，将可获得 Cookie Plus Plus，否则只能获得 Cookie d'Ordinaire）”。if else 语句的通用格式如下:

if(test_condition)
    statement1;
else
    statement2

如果测试条件为 true 或非零，则程序将执行 statement1，跳过 statement2。


例如，假设要通过对字母进行加密编码来修改输入的文本（换行符不变）。这样，每个输入行都被转换为一行输出，且长度不变。这意味着程序对换行符采用一种操作，
而对其他字符采用另一种操作。正如程序 ifelse.cpp 所表明的，if else 使得这项工作非常简单。该程序清单还演示了限定符 std::，这是编译指令 using 的替
代品之一。

// ifelse.cpp
#include<iostream>

int main()
{
    char ch;

    std::cout << "Type and I shall repeat.\n";
    std::cin >> ch;
    while(ch != '.')
    {
        if(ch == '\n')
        {
            std::cout << ch;
        }
        else
        {
            std::cout << ++ch;
        }
        std::cin >> ch;
    }
    std::cout << "\n Please excuse the slight confusion.\n";
    return 0;
}


// !! 逻辑表达式

经常需要测试多种条件。例如，字符要是小写，其值就必须大于或等于 'a'，且小于或等于 'z'。如果要求用户使用 y 或 n 进行响应，则希望用户无论输入大
写（Y 和 N）或小写都可以。为满足这种需要，C++ 提供了 3 种逻辑运算符，来组合或修改已有的表达式。这些运算符分别是逻辑OR（||）、逻辑AND（&&）和
逻辑NOT（!）。下面介绍这些运算符。

// !! 逻辑 OR 运算符：||

在英语中，当两个条件中有一个或全部满足某个要求时，可以用单词 or 来指明这种情况。

C++ 可以采用逻辑 OR 运算符（||），将两个表达式组合在一起。如果原来表达式中的任何一个或全部都为 true（或非零），则得到的表达式的值为 true；
否则，表达式的值为 false。

5 == 5 || 5 == 9;
5 > 3 || 4 < 12;
5 > 10 || 10 < 1;

由于 || 的优先级比关系运算符低，因此不需要在这些表达式中使用括号。

C++ 规定，|| 运算符是个顺序点（sequence point）。也是说，先修改左侧的值，再对右侧的值进行判定（C++11 的说法是，运算符左边的子表达式先于
右边的子表达式）。例如，请看下面的表达式:

i++;
6||i == j;

'如果左侧的表达式为 true，则 C++ 将不会去判定右侧的表达式，因为只要一个表达式为 true，则整个逻辑表达式为 true'

// !! 逻辑AND运算符：&&

逻辑 AND 运算符（&&），也是将两个表达式组合成一个表达式。仅当原来的两个表达式都为 true 时，得到的表达式的值才为 true。



// !! 逻辑NOT运算符：!

!运算符将它后面的表达式的真值取反。也是说，如果 expression 为 true，则 !expression 是 false；如果 expression 为 false，则 !expression 
是 true。更准确地说，如果 expression 为 true 或非零，则 !expression 为 false。

// !! 字符函数库 cctype

'C++ 从 C 语言继承了一个与字符相关的、非常方便的函数软件包，它可以简化诸如确定字符是否为大写字母、数字、标点符号等工作'，这些函数的原型是在头
文件 cctype (老式的风格中为 ctype.h) 中定义的。

例如，如果 ch 是一个字母，则 isalpha（ch） 函数返回一个非零值，否则返回 0。同样，如果 ch 是标点符号（如逗号或句号），函数 ispunct（ch） 将
返回 true。（这些函数的返回类型为 int，而不是 bool，但通常 bool 转换让您能够将它们视为 bool 类型）

使用这些函数比使用 AND 和 OR 运算符更方便。例如，下面是使用 AND 和 OR 来测试字 ch 是不是字母字符的代码：

if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))

与使用 isalpha() 相比：

if(isalpha(ch))

isalpha() 不仅更容易使用，而且更通用。AND/OR 格式假设 A-Z 的字符编码是连续的，其他字符的编码不在这个范围内。这种假设对于 ASCII 码来说是
成立的，但通常并非总是如此。

程序 cctypes.cpp 演示一些 ctype 库函数。具体地说，它使用 isalpha() 来检查字符是否为字母字符，使用 isdigits() 来测试字符是否为数字字符，
使用 isspace() 来测试字符是否为空白，如换行符、空格和制表符，使用 ispunct() 来测试字符是否为标点符号。

// cctypes.cpp
#include<iostream>
#include<cctype>

int main()
{
    using namespace std;
    cout << "Enter text for analysis, and type S for terminate input .\n";
    char ch;
    int spaces = 0;
    int digits = 0;
    int chars = 0;
    int puncs = 0;
    int other = 0;

    cin.get(ch);
    while (ch != 'S')
    {
        if(isalpha(ch))
        {
            ++chars;
        }
        else if(isdigit(ch))
        {
            ++digits;
        }
        else if(isspace(ch))
        {
            ++spaces;
        }
        else if(ispunct(ch))
        {
            ++puncs;
        }
        else
        {
            ++other;
        }
        cin.get(ch);
    }
}

// !! ?: 运算符

C++ 有一个常被用来代替 if else 语句的运算符，这个运算符被称为条件运算符（?:），它是 C++ 中唯一一个需要 3 个操作数的运算符。
该运算符的通用格式如下：

expression1 ?; expression2:expression3;

// !! switch 语句

假设要创建一个屏幕菜单，要求用户从5个选项中选择一个，例如，便宜、适中、昂贵、奢侈、过度。虽然可以扩展 if else if else 序列来处理这 5 种
情况，但 'C++ 的switch语句能够更容易地从大型列表中进行选择'。下面是 switch 语句的通用格式


switch (integer_expression)
{
    case label1: 
    break;
    case label2:
    break;
    case label3:
    break;
    default:
    break;
}

'C++ 的 switch 语句就像指路牌，告诉计算机接下来应执行哪行代码'。执行到 switch 语句时，程序将跳到使用 integer-expression 的值标记
的那一行。

// !! break 和 continue 语句

break 和 continue 语句都使程序能够跳过部分代码。可以在 switch 语句或任何循环中使用 break 语句，使程序跳到 switch 或循环后面的语句处执行。
continue 语句用于循环中，让程序跳过循环体中余下的代码，并开始新一轮循环。


// !!  读取数字的循环

假设要编写一个将一系列数字读入到数组中的程序，并允许用户在数组填满之前结束输入。一种方法是利用 cin。请看下面的代码:

int n;
cin >> n;

如果用户输入一个单词，而不是一个数字，情况将如何呢？ 发生这种类型不匹配的情况时，将发生 4 种情况:

1. n 的值保持不变

2. 不匹配的输入将被留在输入队列中

3. cin 对象中的一个错误标记被设置

4. 对 cin 方法的调用将返回 false（如果被转换为 bool 类型）

方法返回 false 意味着可以用非数字输入来结束读取数字的循环。。非数字输入设置错误标记意味着必须重置该标记，程序才能继续读取输入。
clear() 方法重置错误输入标记，同时也重置文件尾。

假设要编写一个程序，来计算平均每天捕获的鱼的重量。这里假设每天最多捕获 5 条鱼，因此一个包含 5 个元素的数组将足以存储所有的数据，
但也可能没有捕获这么多鱼。在程序 cinfish.cpp 中，如果数组被填满或者输入了非数字输入，循环将结束。

// cinfish.cpp
#include<iostream>

const int MAX = 5;

int main()
{
    using namespace std;
    double fish[MAX];
    cout << "Please Enter your fish weight.\n";
    cout << "You May Enter up to " << MAX << " fish <q to terminate>";
    cout << "Fish #1: ";
    int i = 0;
    while (i < MAX && cin >> fish[i])
    {
        if(++i < MAX)
        {
            cout << "fish# " << i+1 << ":"
        }
    }
    double total = 0.0;
    for(int j = 0; j < i; ++j)
    {
        total += fish[j];
    }

    if(i == 0)
    {
        cout << "No fish found";
    }
    else
    {
        cout << total / i << " = average weight of " << i << " fish.\n";
    }
    cout << "Done!\n";
    return 0;
}



// !!  简单文件输入/输出

有时候，通过键盘输入并非最好的选择。例如，假设您编写了一个股票分析程序，并下载了一个文件，其中包含 1000 种股票的价格。在这
种情况下，让程序直接读取文件，而不是手工输入文件中所有的值，将方便得多。同样，让程序将输出写入到文件将更为方便，这样可得到有
关结果的永久性记录。

幸运的是，C++ 使得将读取键盘输入和在屏幕上显示输出（统称为控制台输入/输出）的技巧用于文件输入/输出（文件 I/O）非常简单。

// !! 文本 I/O 和文本文件

使用 cin 进行输入时，程序将输入视为一系列的字节，其中每个字节都被解释为字符编码。'不管目标数据类型是什么，输入一开始都是字符
数据——文本数据'。然后，cin 对象负责将文本转换为其他类型。为说明这是如何完成的，来看一些处理同一个输入行的代码。

假设有如下示例输入行：

38.5 19.2

来看一下使用不同数据类型的变量来存储时，cin 是如何处理该输入行的。首先，来看使用 char 数据类型的情况:

char ch;
cin >> ch;

输入行中的第一个字符被赋给 ch。在这里，第一个字符是数字 3，其字符编码（二进制）被存储在变量 ch 中。输入和目标变量都是字符，因
此不需要进行转换。注意，这里存储的数值 3，而是字符 3 的编码。执行上述输入语句后，输入队列中的下一个字符为字符 8，下一个输入操
作将对其进行处理。

接下来看看 int 类型:

int n;
cin >> n;

'在这种情况下，cin 将不断读取，直到遇到非数字字符'。也就是说，它将读取 3 和 8，这样句点将成为输入队列中的下一个字符。cin 通过
计算发现，这两个字符对应数值 38，因此将 38 的二进制编码复制到变量 n 中。

接下来看看 double 类型:

double x;
cin >> x;

'在这种情况下，cin 将不断读取，直到遇到第一个不属于浮点数的字符'。也就是说，cin 读取 3、8、句点和 5，使得空格成为输入队列
中的下一个字符。cin 通过计算发现，这四个字符对应于数值 38.5，因此将 38.5 的二进制编码（浮点格式）复制到变量 x 中。


接下来看看 char 数组的情况:

char word[50];
cin >> word;

'在这种情况下，cin 将不断读取，直到遇到空白字符'。也就是说，它读取 3、8、句点 和 5，使得空格成为输入队列中的下一个字符。
然后，cin将这 4 个字符的字符编码存储到数组 word 中，并在末尾加上一个空字符。

最后，来看一下另一种使用 char 数组来存储输入的情况：

char word[50];
cin.getline(world,50);

'在这种情况下，cin 将不断读取，直到遇到换行符'（示例输入行少于 50 个字符）。所有字符都将被存储到数组 word 中，并在末尾加上一
个空字符。换行符被丢弃，输入队列中的下一个字符是下一行中的第一个字符。


'对于输入，将执行相反的转换。即整数被转换为数字字符序列，浮点数被转换为数字字符和其他字符组成的字符序列（如284.53或−1.58E+06）'。
字符数据不需要做任何转换。

这里的要点是，输入一开始为文本。因此，控制台输入的文件版本是文本文件，即每个字节都存储了一个字符编码的文件。并非所有的文件都是
文本文件，例如，数据库和电子表格以数值格式（即二进制整数或浮点格式）来存储数值数据。另外，字处理文件中可能包含文本信息，但也可能
包含用于描述格式、字体、打印机等的非文本数据。

// !! 写入到文本文件中

对于文件输出，C++ 使用类似于 cout 的东西。下面来复习一些有关将 cout 用于控制台输出的基本事实，为文件输出做准备。

1. 必须包含头文件iostream
2. 头文件 iostream 定义了一个用处理输出的 ostream 类
3. 头文件 iostream 声明了一个名为 cout 的 ostream 变量（对象）
4. 必须指明名称空间 std；例如，为引用元素 cout 和 endl，必须使用编译指令 using 或前缀 std::
5. 可以结合使用 cout 和运算符 << 来显示各种类型的数据

文件输出与此极其相似。

1. 必须包含头文件fstream
2. 头文件 fstream 定义了一个用于处理输出的 ofstream 类
3. 需要声明一个或多个 ofstream 变量（对象），并以自己喜欢的方式对其进行命名，条件是遵守常用的命名规则
4. 必须指明名称空间 std；例如，为引用元素 ofstream，必须使用编译指令 using 或前缀 std::
5. 需要将 ofstream 对象与文件关联起来。为此，方法之一是使用 open() 方法
6. 使用完文件后，应使用方法 close() 将其关闭。
7. 可结合使用 ofstream 对象和运算符 << 来输出各种类型的数据


注意，虽然头文件 iostream 提供了一个预先定义好的名为 cout 的 ostream 对象，但您必须声明自己的 ofstream 对象，为其命名，
并将其同文件关联起来。下面演示了如何声明这种对象：

ofstream outFile；
ofstream fout；

下面演示了如何将这种对象与特定的文件关联起来：

outFile.open("hello.txt");
char filename[50];
cin >> filename;
fout.open(filename);


方法 open() 接受一个 C-Style string 作为参数，这可以是一个字面字符串，也可以是存储在数组中的字符串。

下面演示了如何使用这种对象：

double wt = 12.321;
fout << wt;
char line[81] = "Object are closer than appear.";
fout << line << endl;


'重要的是，声明一个 ofstream 对象并将其同文件关联起来后，便可以像使用 cout 那样使用它'。所有可用于 cout 的操作和方法
（如 <<、endl 和 setf()）都可用于 ofstream 对象。


总之，使用文件输出的主要步骤如下:

1． 包含头文件fstream

2． 创建一个 ofstream 对象

3． 将该ofstream对象同一个文件关联起来

4． 就像使用 cout 那样使用该 ofstream 对象


程序 outfile.cpp 中的程序演示了这种方法。它要求用户输入信息，然后将信息显示到屏幕上，再将这些信息写入到文件中。


// outfile.cpp
#include<iostream>
#include<fstream>// for file I/O

int main()
{
    using namespace std;
    char automobile[50];
    int year;
    double a_price;
    double d_price;

    ofstream outfile;
    outfile.open("hello.txt");
    cout << "Enter to make and model of automobile: ";
    cin.getline(automobile,50);
    cout << "Enter the model of year: ";
    cin >> year;
    cout << "Enter the origin asking price: ";
    cin >> a_price;
    d_price = a_price * 0.913;

    // display information on screen with cout
    cout << fixed;
    cout.precision(2);
    cout.setf(ios_base::showpoint);
    cout << "Make and model " << automobile << endl;
    cout << "year " << year << endl;
    cout << " was asking " << a_price << endl;
    cout << "Now asking " << d_price << endl;

    // now do exact same thing using outFile instead of cout
    outFile.fixed;
    outFile.precision(2);
    outFile.self(ios_base::showpoint);
    outFile << "Make and model " << automobile << endl;
    outFile << "year " << year << endl;
    outFile << "was asking " << a_price << endl;
    outFile << "Now asking " << d_price << endl;
    return 0;
}



该程序的最后一部分与 cout 部分相同，只是将 cout 替换为 outFile 而已。

1. ，声明一个 ofstream 对象后，便可以使用方法 open() 将该对象特定文件关联起来：

ofstream outFile;
outFile.open("hello.txt");

程序使用完该文件后，应该将其关闭：

outFile.close();

注意，方法 close() 不需要使用文件名作为参数，这是因为 outFile 已经同特定的文件关联起来。如果您忘记关闭文件，程序正常终止时将自
动关闭它。


回到 open() 方法：

outFile.open("hello.txt");

1. 在这里，该程序运行之前，文件 hello.txt 并不存在。在这种情况下，方法 open() 将新建一个名为 hello.txt 的文件。

2. 如果在此运行该程序，文件 hello.txt 存在，此时情况将如何呢？ 默认情况下，open() 将首先截断该文件，即将其长度截短到零——丢其原有
的内容，然后将新的输出加入到该文件中

'打开文件用于接受输入时可能失败'。例如，指定的文件可能已经存在，但禁止对其进行访问。因此细心的程序员将检查打开文件的操作是否成功


// !! 读取文本文件

文本文件输入，它是基于控制台输入的。控制台输入涉及多个方面，下面首先总结这些方面:

1. 必须包含头文件 iostream

2. 头文件 iostream 定义了一个用处理输入的 istream 类

3. 头文件 iostream 声明了一个名为 cin 的 istream 变量（对象）

4. 必须指明名称空间std；例如，为引用元素 cin，必须使用编译指令 using或前缀 std::

5. 可以结合使用 cin 和运算符 >> 来读取各种类型的数据

6. 可以使用 cin 和 get() 方法来读取一个字符，使用 cin 和 getline() 来读取一行字符

7. 可以结合使用 cin 和 eof()、fail() 方法来判断输入是否成功

8. 对象 cin 本身被用作测试条件时，如果最后一个读取操作成功，它将被转换为布尔值 true，否则被转换为 false


文件输出与此极其相似:

1. 必须包含头文件 fstream

2. 头文件 fstream 定义了一个用于处理输入的 ifstream 类

3. 需要声明一个或多个 ifstream 变量（对象），并以自己喜欢的方式对其进行命名，条件是遵守常用的命名规则

4. 必须指明名称空间 std；例如，为引用元素 ifstream，必须使用编译指令 using 或前缀 std::

5. 需要将 ifstream 对象与文件关联起来。为此，方法之一是使用 open() 方法

6. 使用完文件后，应使用 close() 方法将其关闭

7. 可结合使用 ifstream 对象和运算符 >> 来读取各种类型的数据

8. 可以使用 ifstream 对象和 get() 方法来读取一个字符，使用 ifstream 对象和 getline() 来读取一行字符

9. 以结合使用 ifstream 和 eof()、fail() 等方法来判断输入是否成功

10. ifstream 对象本身被用作测试条件时，如果最后一个读取操作成功，它将被转换为布尔值 true，否则被转换为 false


注意，虽然头文件 iostream 提供了一个预先定义好的名为 cin 的 istream 对象，'但您必须声明自己的 ifstream 对象，为其
命名，并将其同文件关联起来'。下面演示了如何声明这种对象:

ifstream inFile;
ifstream fin;

下面演示了如何将这种对象与特定的文件关联起来:

inFile.open("hello.txt");
char filename[50];
cin >> filename;
inFile.open(filename);

'方法 open() 接受一个 C-Style string 作为参数，这可以是一个字面字符串，也可以是存储在数组中的字符串'。

下面演示了如何使用这种对象:

double wt;
inFile >> wt;

char line[100];
inFile.getline(line, 100);

重要的是，声明一个 ifstream 对象并将其同文件关联起来后，便可以像使用 cin 那样使用它。所有可用于 cin 的操作和方法都
可用于 ifstream 对象。

如果试图打开一个不存在的文件用于输入，情况将如何呢？ 这种错误将导致后面使用 ifstream 对象进行输入时失败。
检查文件是否被成功打开的首先方法是使用方法 is_open() ，为此，可以使用类似于下面的代码：

inFile.open("hello.txt")
if(！inFile.is_open())
{
    exit(EXIT_FAILURE);
}


如果文件被成功地打开，方法 is_open() 将返回 true；因此如果文件没有被打开，表达式 !inFile.isopen() 将为 true。'函数 exit() 
的原型是在头文件 cstdlib 中定义的，在该头文件中，还定义了一个用于同操作系统通信的参数值 EXIT_FAILURE' 。函数 exit() 终止程序。


程序 sumafile.cpp 中的程序打开用户指定的文件，读取其中的数字，然后指出文件中包含多少个值以及它们的和与平均值。

// sumafile.cpp
#include<iostream>
#include<fstream>
#include<cstdlib>

const int SIZE = 60;

int main()
{
    using namespace std;
    char filename[SIZE];
    ifstream inFile;
    cout << "Enter name of data file: ";
    cin.getLine(filename,SIZE);
    inFile.open(filename);
    if(!inFile.is_open())
    {
        cout << "Can not open file " << filename << endl;
        cout << "program terminated" << endl;
        exit(EXIT_FAILURE);
    }
    double value;
    double sum = 0;
    int count = 0;
    
    inFile >> value;
    
    while(inFile.good())
    {
        ++count;
        sum += value;
        inFile >> value;
    }
    if(inFile.eof())
    {
        cout  << "End of file Reached" << endl;
    }
    else if(inFile.fail())
    {
        cout << "Input terminated by data mismatch.\n";
    }
    else
    {
        cout << "Input terminated by unknow reason.\n";
    }
    if(count == 0)
    {
        cout << "No data Processed.\n";
    }
    else
    {
        cout << "Item read : " << count << endl;
        cout << "sum : " << sum << endl;
        cout << "average : " << average << endl;
    }
    inFile.close();
    return 0;
}

该程序没有使用硬编码文件名，而是将用户提供的文件名存储到字符数组 filename 中，然后将该数组用作 open() 的参数：

inFile.open(filename);

'检查文件是否被成功打开至关重要'。下面是一些可能出问题的地方：指定的文件可能不存在；文件可能位于另一个目录（文件夹）中；访问可能被拒绝； 
用户可能输错了文件名或省略了文件扩展名。检查文件是否被成功打开可避免将这种将精力放在错误地方的情况发生。

读者需要特别注意的是文件读取循环的正确设计。读取文件时，有几点需要检查:

1. 首先，程序读取文件时不应超过 EOF。如果最后一次读取数据时遇到 EOF，方法 eof() 将返回 true

2. 其次，程序可能遇到类型不匹配的情况

例如，程序 sumafile.cpp 期望文件中只包含数字。如果最后一次读取操作中发生了类型不匹配的情况，方法 fail() 将返回 true（如果遇到了 EOF，该方法也将
返回 true）。

3. 最后，可能出现意外的问题，如文件受损或硬件故障。如果最后一次读取文件时发生了这样的问题，方法 bad()将返回 true。

'不要分别检查这些情况，一种更简单的方法是使用 good() 方法，该方法在没有发生任何错误时返回 true'

while (inFile.good()) 
{

}

然后，如果愿意，可以使用其他方法来确定循环终止的真正原因：

if(inFile.eof())
{

}
if(inFile.fail())
{

}

这些代码紧跟在循环的后面，用于判断循环为何终止。

由于 eof() 只能判断是否到达 EOF，而 fail() 可用于检查 EOF 和类型不匹配，因此上述代码首先判断是否到达 EOF。

方法 good() 指出最后一次读取输入的操作是否成功，这一点至关重要。这意味着应该在执行读取输入的操作后，立刻应用这种测试。为此，一种标准方法是，
在循环之前（首次执行循环测试前）放置一条输入语句，并在循环的末尾（下次执行循环测试之前）放置另一条输入语句:


inFile >> value;
while (inFile.good())
{
    inFile >> value;
}


鉴于以下事实，可以对上述代码进行精简：表达式 inFile >> value 的结果为 inFile，而在需要一个 bool 值的情况下，inFile 的结果为
inFile.good( )，即 true 或 false。因此，可以将两条输入语句用一条用作循环测试的输入语句代替。也就是说，可以将上述循环结构替换为
如下循环结构：

while (inFile >> value)
{
    inFile >> value;
}

这种设计仍然遵循了在测试之前进行读取的规则，因为要计算表达式 inFile >> value 的值，程序必须首先试图将一个数字读取到 value 中。



// !! 总结

使用引导程序选择不同操作的语句后，程序和编程将更有趣。C++ 提供了 if 语句、if else 语句和 switch 语句来管理选项。if 语句使程序有条件地执行
语句或语句块，也就是说，如果满足特定的条件，程序将执行特定的语句或语句块。if else 语句程序选择执行两个语句或语句块之一。可以在这条语句后再加上
if else，以提供一系列的选项。switch 语句引导程序执行一系列选项之一。

C++ 还提供了帮助决策的运算符。if 和 if else 语句通常使用关系表达式作为测试条件。通过使用逻辑运算符（&&、||和!），可以组合或修改关系表达式，
创建更细致的测试。条件运算符（?:）提供了一种选择两个值之一的简洁方式。cctype 字符函数库提供了一组方便的、功能强大的工具，可用于分析字符输入。

对于文件 I/O 来说，循环和选择语句是很有用的工具；文件 I/O 与控制台 I/O 极其相似。声明 ifstream 和 ofstream 对象，并将它们同文件关联起来后，
便可以像使用 cin 和 cout 那样使用这些对象。

使用循环和决策语句，便可以编写有趣的、智能的、功能强大的程序。



