// !! 开始学习 C++

// !! 进入C++

首先介绍一个显示消息的简单 C++ 程序。使用 C++ 工具 cout 生成字符输出。C++ 对大小写敏感，也就是说区分大写字符和小写字符。这意味着大小写必须与示例中相同。
例如，该程序使用的是 cout，如果将其替换为 Cout 或 COUT，程序将无法通过编译，并且编译器将指出使用了未知的标识符（编译器也是对拼写敏感的，因此请不要使用
kout或coot）。'文件扩展名 cpp 是一种表示 C++ 程序的常用方式'。

// myfirst.cpp  -- display a message

#include <iostream>

int main()
{
    using namespace std;
    cout << "Come up and C++ me some time" << endl;
    cout << "you won't forget it" << endl;
    return 0;
}

 » g++ --std=c++11 myfirst.cpp 
--------------------------------------------------------------------------------
 » ./a.out

Come up and C++ me some time
you won't forget it'


您使用函数来创建 C++ 程序。'通常先将程序组织为主要任务，然后设计独立的函数来处理这些任务'。

程序 myfirst.cpp 中的示例非常简单，只包含一个名为 main( ) 的函数。myfirst.cpp 示例包含下述元素。

1. 注释，由前缀//标识

2. 预处理器编译指令#include

3. 函数头：int main()

4. 编译指令 using namespace

5. 函数体，用{和}括起

6. 使用 C++ 的 cout 工具显示消息的语句

7. 结束 main( ) 函数的 return 语句


先来看看 main( ) 函数，因为了解了 main( ) 的作用后，main( ) 前面的一些特性（如预处理器编译指令）将更易于理解。

// !! main() 函数

去掉修饰后，程序 myfirst.cpp 示例程序的基本结构如下:

int main()
{
    statements;
    return 0;
}

这几行表明有一个名为 main( ) 的函数，并描述了该函数的行为。这几行代码构成了函数定义（function definition）。该定义由两部分组成：第一行 int main() 叫函数头
（function heading），花括号{ }中包括的部分叫函数体。'函数头对函数与程序其他部分之间的接口进行了总结；函数体是指出函数应做什么的计算机指令'。在 C++ 中，每条
完整的指令都称为语句。所有的语句都以分号结束。main() 中最后一条语句叫做返回语句（return statement），它结束该函数。


1. 语句和分号

   语句是要执行的操作。为理解源代码，编译器需要知道一条语句何时结束，另一条语句何时开始。有些语言使用语句分隔符。例如，FORTRAN 通过行尾将语句分隔开来，Pascal 使用
   分号分隔语句。在 Pascal 中，有些情况下可以省略分号，例如 END 前的语句后面，这种情况下，实际上并没有将两条语句分开。'不过 C++ 与 C 一样，也使用终止符
   （terminator），而不是分隔符。终止符是一个分号，它是语句的结束标记，是语句的组成部分，而不是语句之间的标记'。结论是：在 C++ 中，不能省略分号。

2. 作为接口的函数头

   通常，C++ 函数可被其他函数激活或调用，函数头描述了函数与调用它的函数之间的接口。位于函数名前面的部分叫做函数返回类型，它描述的是从函数返回给调用它的函数的信息。
   函数名后括号中的部分叫做形参列表（argument list）或参数列表（parameter list）；它描述的是从调用函数传递给被调用的函数的信息。这种通用格式用于 main( ) 时让
   人感到有些迷惑，因为通常并不从程序的其他部分调用 main()。然而，通常，main() 被启动代码调用，而启动代码是由编译器添加到程序中的，是程序和操作系统
   （UNIX、Windows 7或其他操作系统）之间的桥梁。事实上，该函数头描述的是 main() 和操作系统之间的接口。来看一下 main() 的接口描述，该接口从 int 开始。C++ 函数
   可以给调用函数返回一个值，这个值叫做返回值（return value）。在这里，从关键字 int 可知，main() 返回一个整数值。接下来，是空括号。通常，C++ 函数在调用另一个
   函数时，可以将信息传递给该函数。括号中的函数头部分描述的就是这种信息。在这里，空括号意味着 main() 函数不接受任何信息，或者 main()不接受任何参数。
   （main() 不接受任何参数并不意味着 main() s是不讲道理的、发号施令的函数。相反，术语参数（argument）只是计算机人员用来表示从一个函数传递给另一个函数的信息）。
   简而言之，下面的函数头表明 main() 函数可以给调用它的函数返回一个整数值，且不从调用它的函数那里获得任何信息.

   int main();

   int main(void);// very explicit style

   最后，ANSI/ISO C++ 标准对那些抱怨必须在 main() 函数最后包含一条返回语句过于繁琐的人做出了让步。如果编译器到达 main() 函数末尾时没有遇到返回语句，则认为 
   main() 函数以如下语句结尾：

   return 0;

   这条隐含的返回语句只适用于 main() 函数，而不适用于其他函数。


3. 为什么 main() 不能使用其他名称

   之所以将 myfirst.cpp 程序中的函数命名为 main()，原因是必须这样做。通常 C++ 程序必须包含一个名为 main() 的函数（不是Main( )、MAIN( )或mane( )。记住，
   大小写和拼写都要正确）。由于 myfirst.cpp 程序只有一个函数，因此该函数必须担负起 main() 的责任。'在运行 C++ 程序时，通常从main() 函数开始执行。因此，如果
   没有main( )，程序将不完整，编译器将指出未定义 main() 函数'。


4. C++ 注释

   C++ 注释以双斜杠打头。'注释是程序员为读者提供的说明，通常标识程序的一部分或解释代码的某个方面'。编译器忽略注释，毕竟，它对 C++ 的了解至少和程序员一样，在任何
   情况下，它都不能理解注释。
   // !! 提示：

   应使用注释来说明程序。程序越复杂，注释的价值越大。注释不仅有助于他人理解这些代码，也有助于程序员自己理解代码，特别是隔了一段时间没有接触该程序的情况下。

   C-风格注释

   C++ 也能够识别 C 注释，C 注释包括在符号 /* 和 */ 之间：

   #include <iostream> /* a C-style comment */

   由于 C-风格注释以 */ 结束，而不是到行尾结束，因此可以跨越多行。可以在程序中使用 C 或 C++ 风格的注释，也可以同时使用这两种注释。但'应尽量使用 C++ 注释，因为这
   不涉及到结尾符号与起始符号的正确配对，所以它产生问题的可能性很小'。事实上，C99 标准也在 C 语言中添加了 // 注释。


5.  C++ 预处理器和 iostream 文件

    下面简要介绍一下需要知道的一些知识。如果程序要使用 C++ 输入或输出工具，请提供这样两行代码：
    #include<iostream>
    using namespace std;

    可使用其他代码替换第 2 行，这里使用这行代码旨在简化该程序（如果编译器不接受这几行代码，则说明它没有遵守标准 C++98，使用它来编译本书的示例时，将出现众多其他的
    问题）。'C++ 和 C 一样，也使用一个预处理器，该程序在进行主编译之前对源文件进行处理'。

    #include <iostream>

    该编译指令导致预处理器将 iostream 文件的内容添加到程序中。这是一种典型的预处理器操作: 在源代码被编译之前，替换或添加文本。

    为什么要将 iostream 文件的内容添加到程序中呢？
    
    答案'涉及程序与外部世界之间的通信。iostream 中的io指的是输入（进入程序的信息）和输出（从程序中发送出去的信息）'。C++ 的输入/输出方案涉及 iostream 文件中的
    多个定义。为了使用 cout 来显示消息，第一个程序需要这些定义。'#include 编译指令导致 iostream 文件的内容随源代码文件的内容一起被发送给编译器'。实际上，
    iostream 文件的内容将取代程序中的代码行 #include <iostream>。原始文件没有被修改，而是将源代码文件和 iostream 组合成一个复合文件，编译的下一阶段将使用
    该文件。

6. 头文件名

   像 iostream 这样的文件叫做包含文件（include file）—由于它们被包含在其他文件中；'也叫头文件（header file）—由于它们被包含在文件起始处'。'C++ 编译器自带了很
   多头文件，每个头文件都支持一组特定的工具'。C 语言的传统是头文件使用扩展名 h，将其作为一种通过名称标识文件类型的简单方式。例如: 头文件 math.h 支持各种 C 语言
   数学函数，但 C++ 的用法变了。现在对老式 C 的头文件保留了扩展名 h（C++程序仍可以使用这种文件），而 C++ 头文件则没有扩展名。有些 C 头文件被转换为 C++ 头文件，
   这些文件被重新命名，去掉了扩展名 h（使之成为C++风格的名称），并在文件名称前面加上前缀c（表明来自C语言）。例如，C++ 版本的 math.h 为 cmath。有时 C 头文件的 C 版本
   和 C++ 版本相同，而有时候新版本做了一些修改。

7. 名称空间

   如果使用 iostream，而不是 iostream.h，则应使用下面的'名称空间编译指令'来使 iostream 中的定义对程序可用:

   using namespace std;

   这叫做 using 编译指令。最简单的办法是，现在接受这个编译指令，以后再考虑它

   名称空间支持是一项 C++ 特性，旨在让您编写大型程序以及将多个厂商现有的代码组合起来的程序时更容易，它还有助于组织程序。一个潜在的问题是，可能使用两个已封装好的产品
   ，而它们都包含一个名为 wanda() 的函数。这样，使用 wanda() 函数时，编译器将不知道指的是哪个版本。名称空间让厂商能够将其产品封装在一个叫做名称空间的单元中，这样
   就可以用名称空间的名称来指出想使用哪个厂商的产品。因此， Microflop Industries 可以将其定义放到一个名为 Microflop 的名称空间中。这样其 wanda() 函数的全称
   为 Microflop::wanda()；同样 Piscine 公司的 wanda() 版本可以表示为 Piscine::wanda()。这样，程序就可以使用名称空间来区分不同的版本了:

   Microflop::wanda();
   Piscine::wanda();

   按照这种方式，类、函数和变量便是 C++ 编译器的标准组件，它们现在都被放置在名称空间 std 中。仅当头文件没有扩展名 h 时，情况才是如此。这意味着在 iostream 中定义
   的用于输出的 cout 变量实际上是 std::cout，而 endl 实际上是 std::endl。因此，可以省略编译指令 using，以下述方式进行编码:

   using std::cout;
   using std::endl;
   using std::cin;


8. 使用 cout 进行 C++ 输出

    现在来看一看如何显示消息。myfirst.cpp 程序使用下面的 C++ 语句:

    cout << "Come up and C++ me some time" << endl;

    双引号括起的部分是要打印的消息。'在 C++ 中，用双引号括起的一系列字符叫做字符串，因为它是由若干字符组合而成的'。<< 符号表示该语句将把这个字符串发送给 cout；
    该符号指出了信息流动的路径。cout 是什么呢？ '它是一个预定义的对象，知道如何显示字符串、数字和单个字符等'。从概念上看，输出是一个流，即从程序流出的一系列字符。
    cout 对象表示这种流，其属性是在 iostream 文件中定义的。'cout 的对象属性包括一个插入运算符（<<），它可以将其右侧的信息插入到流中'。

    cout << "Come up and C++ me some time" << endl;

    它将字符串 “Come up and C++ me some time” 插入到输出流中。因此, 与其说程序显示了一条消息，不如说它将一个字符串插入到了输出流中。


9. 控制符 endl

  'endl 是一个特殊的 C++ 符号，表示一个重要的概念：重起一行'。在输出流中插入 endl 将导致屏幕光标移到下一行开头。诸如 endl 等对于 cout 来说有特殊含义的特殊符号
  被称为控制符（manipulator）。和 cout 一样，endl 也是在头文件 iostream 中定义的，且位于名称空间 std 中。C++ 还提供了另一种在输出中指示换行的旧式方法: C语言
  符号 \n， \n 被视为一个字符，名为换行符。显示字符串时，在字符串中包含换行符，而不是在末尾加上 endl，可减少输入量。'一个差别是，endl 确保程序继续运行前刷新输出
  （将其立即显示在屏幕上）'； 而使用 “\n” 不能提供这样的保证，这意味着在有些系统中，有时可能在您输入信息后才会出现提示。

10. C++ 源代码的格式化

    有些语言（如FORTRAN）是面向行的，即每条语句占一行。对于这些语言来说，回车的作用是将语句分开。然而，在 C++ 中，分号标示了语句的结尾。因此，在 C++ 中，回车的作
    用就和空格或制表符相同。也就是说，在 C++ 中，通常可以在能够使用回车的地方使用空格，反之亦然。这说明既可以把一条语句放在几行上，也可以把几条语句放在同一行上。
    例如，可以将 myfirst.cpp 重新格式化为如下所示:

    #include <iostream>

    int
    main()
    {
        using namespace 
        std; cout 
        << 
        "Come up and C++ me some time"
        << 
        endl;

    }

    这样虽然不太好看，但仍然是合法的代码。必须遵守一些规则，具体地说，在 C 和 C++ 中，不能把空格、制表符或回车放在元素（比如名称）中间，也不能把回车放在字符串中间。

    下面是一个不能这样做的例子:

    int ma in() // INVALID --- space in name
    re
    turn 0; // INVALID -- carriage return in word

    然而，C++11 新增的原始（raw）字符串可包含回车


    1. 源代码中的标记和空白

    一行代码中不可分割的元素叫做标记（token）。'通常必须用空格、制表符或回车将两个标记分开，空格、制表符和回车统称为空白（white space）'。有些字符（如括号和逗
    号）是不需要用空白分开的标记。


// !! C++ 源代码风格

虽然 C++ 在格式方面赋予了您很大的自由，但如果遵循合理的风格, 程序将更便于阅读。有效但难看的代码不会令人满意。它遵循了下述规则。

1. 每条语句占一行

2. 每个函数都有一个开始花括号和一个结束花括号，这两个花括号各占一行

3. 函数中的语句都相对于花括号进行缩进

4. 与函数名称相关的圆括号周围没有空白

前三条规则旨在确保代码清晰易读；第四条规则帮助区分函数和一些也使用圆括号的 C++ 内置结构（如循环）。


// !! C++ 语句

C++ 程序是一组函数，而每个函数又是一组语句。C++ 有好几种语句，下面介绍其中的一些。


// carrot.cpp --- food processing program

#include <iostream>
int main()
{
    using namespace std;
    
    int carrots; // declare an integer variable

    carrots = 25;
    cout << "I have ";
    cout << carrots;
    cout << " carrots.";
    cout << endl;
    carrots = carrots - 1;
    cout << "Crunch, crunch. Now I have " << carrots << " carrots." << endl;
    return 0;
}

空行将声明语句与程序的其他部分分开。这是 C 常用的方法，但在 C++ 中不那么常见。下面是该程序的输出:

» g++ --std=c++11 carrot.cpp 
--------------------------------------------------------------------------------
» ./a.out

I have 25 carrots.
Crunch, crunch. Now I have 24 carrots.

1. 声明语句和变量

   计算机是一种精确的、有条理的机器。要将信息项存储在计算机中，必须指出信息的存储位置和所需的内存空间。在 C++ 中，完成这种任务的一种相对简便的方法，是使用声明语
   句来指出存储类型并提供位置标签。例如，程序 carrot.cpp 中包含这样一条声明语句（注意其中的分号）:

   int carrots; 

   '这条语句提供了两项信息：需要的内存以及该内存单元的名称'。具体地说，这条语句指出程序需要足够的存储空间来存储一个整数，在 C++ 中用 int 表示整数。'编译器负责分配和
   标记内存的细节'。C++ 可以处理多种类型的数据，而 int 是最基本的数据类型。它表示整数—没有小数部分的数字。C++ 的 int 类型可以为正，也可以为负，但是大小范围取决于
   实现。完成的第二项任务是给存储单元指定名称。在这里，该声明语句指出，此后程序将使用名称 carrots 来标识存储在该内存单元中的值。Carrots 被称为变量，因为它的值可以
   修改。'在 C++ 中，所有变量都必须声明'。如果省略了 carrots.cpp 中的声明，则当程序试图使用 carrots 时，编译器将指出错误。事实上，程序员尝试省略声明，可能只是
   为了看看编译器的反应。这样，以后看到这样的反应时，便知道应检查是否省略了声明。

   因此，声明通常指出了要存储的数据类型和程序对存储在这里的数据使用的名称。'程序中的声明语句叫做定义声明（defining declaration）语句，简称为定义（definition）。
   这意味着它将导致编译器为变量分配内存空间'。在较为复杂的情况下，还可能有引用声明（reference declaration）。这些声明命令计算机使用在其他地方定义的变量。通常，
   声明不一定是定义，但在这个例子中，声明是定义。

   提示：
   对于声明变量，C++ 的做法是尽可能在首次使用变量前声明它。


2. 赋值语句

   赋值语句将值赋给存储单元。例如，下面的语句将整数 25 赋给变量 carrots 表示的内存单元：

    carrots = 25;
    carrots = carrots - 1;

   符号 = 叫做赋值运算符。C++（和C） 有一项不寻常的特性—可以连续使用赋值运算符。

   int i;
   int j;
   int k;
   i = j = k = 88;

   赋值将从右向左进行。首先，88 被赋给 k；然后，k 的值（现在是88）被赋给 j；然后 j 的值 88 被赋给 i（C++ 遵循 C 的爱好，允许外观奇怪的代码）。

   赋值运算符右边的表达式 carrots – 1 是一个算术表达式。计算机将变量 carrots 的值 25 减去 1 ，得到 24。然后赋值运算符将这个新值存储到变量 carrots 
   对应的内存单元中

3. cout 的新花样

    cout << carrots;

    程序没有打印 “carrots”，而是打印存储在 carrots 中的整数值，即 25。实际上，这将两个操作合而为一了。首先，cout 将 carrots 替换为其当前值 25；然后把值
    转换为合适的输出字符。如上所示，cout 可用于数字和字符串。这似乎没有什么不同寻常的地方，但别忘了，整数 25 与字符串 “25” 有天壤之别。'该字符串存储的是书写该数
    字时使用的字符，即字符 3 和 8'。程序在内部存储的是字符 3  和字符 8 的编码。要打印字符串，cout 只需打印字符串中各个字符即可。但整数 25 被存储为数值，计算机
    不是单独存储每个数字，而是将 25 存储为二进制数。'这里的要点是，在打印之前 cout 必须将整数形式的数字转换为字符串形式'。另外，cout 很聪明，知道 carrots 是一
    个需要转换的整数。

    与老式 C 语言的区别在于 cout 的聪明程度。在 C 语言中，要打印字符串 “25” 和整数 25，可以使用 C 语言的多功能输出函数printf()：

    printf("Printing a string :%s\n","25");
    printf("Printing a int: %d\n",25);

    撇开 printf() 的复杂性不说，必须用特殊代码（%s和%d）来指出是要打印字符串还是整数。如果让 printf() 打印字符串，但又错误地提供了一个整数，由于 printf()
    不够精密，因此根本发现不了错误。它将继续处理，显示一堆乱码。'cout 的智能行为源自 C++ 的面向对象特性。实际上，C++ 插入运算符（<<）将根据其后的数据类型相应地
    调整其行为，这是一个运算符重载的例子"'。


// !! 其他 C++ 语句  

再来看几个 C++ 语句的例子。程序 getinfo.cpp 中的程序对前一个程序进行了扩展，要求在程序运行时输入一个值。为实现这项任务，它使用了 cin，这是与 cout 对应的用于输
入的对象。另外，该程序还演示了 cout 对象的多功能性。

// getinfo.cpp--input and output

#include <iostream>

int main()
{
    using namespace std;

    int carrots;

    cout << "How many carrots do you have?" << endl;
    cin >> carrots;
    cout << "Here are two more. ";
    carrots = carrots + 2;

    cout << "Now you have " << carrots << " carrots. " << endl;
    return 0;
}

该程序包含两项新特性：用 cin 来读取键盘输入以及将四条输出语句组合成一条。

1. 使用 cin

   上面的输出表明，从键盘输入的值 （12） 最终被赋给变量 carrots。下面就是执行这项功能的语句：

   cin >> carrots;

   从这条语句可知，信息从 cin 流向 carrots。显然，对这一过程有更为正式的描述。'就像 C++ 将输出看作是流出程序的字符流一样，它也将输入看作是流入程序的字符流'。
   iostream 文件将 cin 定义为一个表示这种流的对象。输出时，<< 运算符将字符串插入到输出流中；输入时，cin 使用 >> 运算符从输入流中抽取字符。通常，需要在运算
   符右侧提供一个变量，以接收抽取的信息（符号 << 和 >> 被选择用来指示信息流的方向）。与 cout 一样，'cin 也是一个智能对象, 它可以将通过键盘输入的一系列字符
   转换为接收信息的变量能够接受的形式'。在这个例子中，程序将 carrots 声明为一个整型变量，因此输入被转换为计算机用来存储整数的数字形式。

2. 使用 cout 进行拼接

   getinfo.cpp 中的另一项新特性是将 4 条输出语句合并为一条。iostream 文件定义了 << 运算符，以便可以像下面这样合并（拼接）输出:

   cout << "Now you have " << carrots << " carrots. " << endl;

   这样能够将字符串输出和整数输出合并为一条语句。得到的输出与下述代码生成的相似：

   cout << "Now you have ";
   cout << carrots;
   cout << " carrots. ";
   cout << endl;

   根据有关 cout 的建议，也可以按照这样的方式重写拼接版本，即将一条语句放在 4 行上:

   cout << "Now you have " 
   << carrots 
   << " carrots. " 
   << endl;

   '这是由于 C++ 的自由格式规则将标记(Token)间的换行符和空格看作是可相互替换的'。当代码行很长，限制输出的显示风格时，最后一种技术很方便。


// !! 类简介

看了足够多的 cin 和 cout 示例后，可以学习有关对象的知识了。'类是 C++ 中面向对象编程（OOP）的核心概念之一'。'类是用户定义的一种数据类型'。'要定义类，需要描述它能
够表示什么信息和可对数据执行哪些操作. 类之于对象就像类型之于变量'。也就是说，类定义描述的是数据格式及其用法，而对象则是根据数据格式规范创建的实体。

下面更具体一些, 前文讲述过下面的变量声明:

int carrots;

上面的代码将创建一个类型为 int 的变量（carrots）。也就是说 carrots 可以存储整数，可以按特定的方式使用---例如, 用于加和减。现在来看 cout。它是一个 ostream 
类对象。'ostream 类定义（iostream 文件的另一个成员）描述了 ostream 对象表示的数据以及可以对它执行的操作，如将数字或字符串插入到输出流中'。同样，cin 是一个 
istream 类对象，也是在 iostream 中定义的。

注意：

类描述了一种数据类型的全部属性（包括可使用它执行的操作），对象是根据这些描述创建的实体。

知道类是用户定义的类型，但作为用户，并没有设计 ostream 和 istream 类。就像函数可以来自函数库一样，类也可以来自类库。ostream 和 istream 类就属于这种情况。从技
术上说，它们没有被内置到 C++ 语言中，而是语言标准指定的类。这些类定义位于 iostream 文件中，没有被内置到编译器中。如果愿意，程序员甚至可以修改这些类定义，虽然这不
是一个好主意。iostream 系列类和相关的 fstream （或文件I/O）系列类是早期所有的实现都自带的唯一两组类定义。然而 ANSI/ISO C++ 委员会在 C++ 标准中添加了其他一些
类库。另外多数实现都在软件包中提供了其他类定义。 '事实上，C++ 当前之所以如此有吸引力，很大程度上是由于存在大量支持 UNIX、Macintosh 和 Windows 编程的类库'。

类描述指定了可对类对象执行的所有操作。要对特定对象执行这些允许的操作， 需要给该对象发送一条消息。例如，如果希望 cout 对象显示一个字符串，应向它发送一条消息，告诉它
，“对象！显示这些内容！”。 'C++ 提供了两种发送消息的方式：一种方式是使用类方法（本质上就是函数调用）；另一种方式是重新定义运算符，cin 和 cout 采用的就是这种方式'。
因此，下面的语句使用重新定义的 << 运算符将 "显示消息" 发送给 cout:

cout << "I am not a crook.";


// !! 函数

由于函数用于创建 C++ 程序的模块，对 C++ 的 OOP 定义至关重要，因此必须熟悉它。C++ 函数分两种： 有返回值的和没有返回值的。在标准 C++ 函数库中可以找到这两类函数
的例子，您也可以自己创建这两种类型的函数。下面首先来看一个有返回值的库函数，然后介绍如何编写简单的函数。

1. 使用有返回值的函数

   有返回值的函数将生成一个值，而这个值可赋给变量或在其他表达式中使用。例如，标准 C/C++ 库包含一个名为 sqrt() 的函数，它返回平方根。假设要计算 6.25的平方根，
   并将这个值赋给变量x，则可以在程序中使用下面的语句：

   x = sqrt(6.25);

   表达式 sqrt(6.25) 将调用 sqrt() 函数。'表达式 sqrt(6.25) 被称为函数调用，被调用的函数叫做被调用函数（called function）'，包含函数调用的函数叫做调用函数
   （calling function）。圆括号中的值（这里为 6.25）是发送给函数的信息，这被称为传递给函数。以这种方式发送给函数的值叫做参数。函数 sqrt() 得到的结果为 2.5，并
   将这个值发送给调用函数；发送回去的值叫做函数的返回值（return value）。可以这么认为，函数执行完毕后，语句中的函数调用部分将被替换为返回的值。因此，这个例子将返
   回值赋给变量 x。简而言之, '参数是发送给函数的信息，返回值是从函数中发送回去的值'。情况基本上就是这样，只是在使用函数之前，C++ 编译器必须知道函数的参数类型和返回
   值类型。也就是说，函数是返回整数、字符、小数还是别的什么东西？ 如果缺少这些信息，编译器将不知道如何解释返回值。'C++ 提供这种信息的方式是使用函数原型语句'。

   sqrt() 的函数原型像这样:

   double sqrt(double);// function property

   原型结尾的分号表明它是一条语句，这使得它是一个原型，而不是函数头。如果省略分号，编译器将把这行代码解释为一个函数头，并要求接着提供定义该函数的函数体。

   在程序中使用 sqrt() 时，也必须提供原型。可以用两种方法来实现：
   
   1. 在源代码文件中输入函数原型
   2. 包含头文件 cmath（老系统为 math.h），其中定义了原型

   第二种方法更好，因为头文件更有可能使原型正确。'对于 C++ 库中的每个函数，都在一个或多个头文件中提供了其原型'。请通过手册或在线帮助查看函数描述来确定应使用哪个
   头文件。例如 sqrt() 函数的说明将指出，应使用 cmath 头文件。不要混淆函数原型和函数定义。'可以看出，原型只描述函数接口。也就是说，它描述的是发送给函数的信息和
   返回的信息。而定义中包含了函数的代码，如计算平方根的代码'。C 和 C++ 将库函数的这两项特性（原型和定义）分开了。'库文件中包含了函数的编译代码，而头文件中则包含了
   原型'。

   应在首次使用函数之前提供其原型。通常的做法是把原型放到 main() 函数定义的前面。
    // sqrt.cpp  -- using sqrt() function

    #include <iostream>
    #include<cmath>

    int main()
    {
        using namespace std;

        double area;
        cout << "Enter the floor area, in square feet or your home:";
        cin >> area;
        double side;
        side = sqrt(area);
        cout << "That the equivalent of a square " << side << "feet to the side." << endl;
        cout << "How fascinating!" << endl;
        return 0;
    }

    cin 知道如何将输入流中的信息转换为 double 类型，cout 知道如何将 double 类型插入到输出流中。这些对象都很智能化。


// !! 函数变态

有些函数需要多项信息。这些函数使用多个参数，参数间用逗号分开。例如，数学函数 pow() 接受两个参数，返回值为以第一个参数为底，第二个参数为指数的幂。
该函数的原型如下：

double pow(double，double);// property of a function with two arguments

要计算5的8次方，可以这样使用该函数:

answer = pow(5,8);

另外一些函数不接受任何参数。例如，有一个 C 库（与 cstdlib 头文件相关的库）包含一个 rand() 函数，该函数不接受任何参数，并返回一个随机整数。
该函数的原型如下:

int rand(void);// property of a function that takes  no argument

关键字 void 明确指出，该函数不接受任何参数。如果省略 void，让括号为空，则 C++ 将其解释为一个不接受任何参数的隐式声明。可以这样使用该函数：

myGuess = rand();

注意，与其他一些计算机语言不同，在  C++ 中，函数调用中必须包括括号，即使没有参数。



// !! 用户定义的函数

标准C库提供了 140 多个预定义的函数。如果其中的函数能满足要求，则应使用它们。但用户经常需要编写自己的函数，尤其是在设计类的时候。无论如何，设计自己的函数很有意思
前面已经使用过好几个用户定义的函数，它们都叫 main()。每个 C++ 程序都必须有一个main( )函数，用户必须对它进行定义。假设需要添加另一个用户定义的函数。和库函数一样
，也可以通过函数名来调用用户定义的函数。'对于库函数，在使用之前必须提供其原型，通常把原型放到 main() 定义之前'。但现在您必须提供新函数的源代码。最简单的方法是，
将代码放在 main() 的后面。程序 ourfunc.cpp 演示了这些元素。

程序 ourfunc.cpp

// ourfunc.cpp
#include<iostream>

void simon(int);// function property for simon()

int main()
{
    using namespace std;
    simon(3);
    cout << "Pick a integer: ";
    int count;
    cin >> count;
    simon(count);
    cout << "Done!" << endl;
    return 0;
}

void simon(int n)// difine the simon function
{
    using namespace std;
    cout << "Simon says touch you toes " << n << "times." << endl;
}


main() 函数两次调用 simon() 函数，一次的参数为 3，另一次的参数为变量 count。在这两次调用之间，用户输入一个整数，用来设置 count 的值。这个例子没有在 cout 
提示消息中使用换行符。这样将导致用户输入与提示出现在同一行中。

1. 函数格式
   simon() 函数的定义与 main() 的定义采用的格式相同。首先，有一个函数头；然后是花括号中的函数体。注意，定义 simon() 的源代码位于 main() 的后面。和 C 
   一样（但不同于 Pascal），'C++ 不允许将函数定义嵌套在另一个函数定义中。每个函数定义都是独立的，所有函数的创建都是平等的'。


// !! 总结

C++ 程序由一个或多个被称为函数的模块组成。程序从 main() 函数（全部小写）开始执行，因此该函数必不可少。函数由函数头和函数体组成。函数头指出函数的返回值（如果有的话）
的类型和函数期望通过参数传递给它的信息的类型。函数体由一系列位于花括号 { } 中的 C++ 语句组成。

有多种类型的 C++ 语句，包括下述 6 种:

1. 声明语句：定义函数中使用的变量的名称和类型

2. 赋值语句：使用赋值运算符（=）给变量赋值

3. 消息语句：将消息发送给对象，激发某种行动

4. 函数调用：执行函数。被调用的函数执行完毕后，程序返回到函数调用语句后面的语句

5. 函数原型：声明函数的返回类型、函数接受的参数数量和类型

6. 返回语句：将一个值从被调用的函数那里返回到调用函数中

类是用户定义的数据类型规范，它详细描述了如何表示信息以及可对数据执行的操作。对象是根据类规范创建的实体，就像简单变量是根据数据类型描述创建的实体一样。
C++ 提供了两个用于处理输入和输出的预定义对象（cin和cout），它们是 istream 和 ostream 类的实例，这两个类是在 iostream 文件中定义的。为 ostream 类
定义的插入运算符（<<）使得将数据插入到输出流成为可能；为 istream 类定义的抽取运算符（>>）能够从输入流中抽取信息。cin 和 cout 都是智能对象，能够根据程序
上下文自动将信息从一种形式转换为另一种形式。C++ 可以使用大量的 C 库函数。要使用库函数，应当包含提供该函数原型的头文件。





















































