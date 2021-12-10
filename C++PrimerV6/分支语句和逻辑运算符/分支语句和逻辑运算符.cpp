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

有时候，通过键盘输入并非最好的选择。例如，假设您编写了一个股票分析程序，并下载了一个文件，其中包含 1000 种股票的价格。在这种情况下，
让程序直接读取文件，而不是手工输入文件中所有的值，将方便得多。同样，让程序将输出写入到文件将更为方便，这样可得到有关结果的永久性记录。

幸运的是，C++ 使得将读取键盘输入和在屏幕上显示输出（统称为控制台输入/输出）的技巧用于文件输入/输出（文件 I/O）非常简单。








