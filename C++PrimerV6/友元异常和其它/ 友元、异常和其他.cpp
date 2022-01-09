// !! 友元、异常和其他

本章先介绍一些 C++ 语言最初就有的特性，然后介绍 C++ 语言新增的一些特性。前者包括友元类、友元成员函数和嵌套类，它们是在其他类中声明的类。

后者包括异常、运行阶段类型识别(RTTI)和改进后的类型转换控制:

1. C++ 异常处理提供了处理特殊情况的机制，如果不对其进行处理，将导致程序终止

2. RTTI 是一种确定对象类型的机制

3. 新的类型转换运算符提高了类型转换的安全性


// !! 友元

'类并非只能拥有友元函数，也可以将类作为友元'。在这种情况下,友元类的所有方法都可以访问原始类的私有成员和保护成员。另外，也可以做更严格的限制，只将特定的成员函
数指定为另一个类的友元。


// !! 友元类

什么时候希望一个类成为另一个类的友元呢？

假定需要编写一个模拟电视机和遥控器的简单程序。决定定义一个 Tv 类和一个 Remote 类，来分别表示电视机和遥控器。很明显，这两个类之间应当存在某种关系，但是什么样
的关系呢？ 遥控器并非电视机，反之亦然，所以公有继承的 is-a 关系并不适用。遥控器也非电视机的一部分，反之亦然，因此包含或私有继承和保护继承的 has-a 关系也不适
用。事实上，'遥控器可以改变电视机的状态，这表明应将 Romote 类作为 Tv 类的一个友元'。

首先定义 Tv 类, 可以用一组状态成员(描述电视各个方面的变量)来表示电视机。下面是一些可能的状态:

1. 开/关

2. 频道设置

3. 音量设置

4. 有线电视或天线调节模式

5. TV调谐或A/V输入

接下来，必须给类提供一些修改这些设置的方法。当前，很多电视机都将控件藏在面板后面，但大多数电视机还是可以在不使用遥控器的情况下进行换台等工作的，通常只能逐频道
换台，而不能随意选台。同样，通常还有两个按钮，分别用来增加和降低音量。

遥控器的控制能力应与电视机内置的控制功能相同，它的很多方法都可通过使用 Tv 方法来实现。另外，遥控器通常都提供随意选择频道的功能，即可以直接从 2 频道换到 20 频
道，并不用逐次切换频道。另外，很多遥控器都有多种工作模式，如用作电视控制器和 DVD 遥控器。

这些考虑因素表明，定义应类似于 tv.h。定义中包括一些被定义为枚举的常数。下面的语句使 Remote 成为友元类：

friend class Remote;

友元声明可以位于公有、私有或保护部分，其所在的位置无关紧要。由于 Remote 类提到了 Tv 类，所以编译器必须了解 Tv 类后，才能处理 Remote 类，为此，最简单的方法
是首先定义 Tv 类。


tv.h 中，大多数类方法都被定义为内联的。除构造函数外，所有的 Romote 方法都将一个 Tv 对象引用作为参数，这表明遥控器必须针对特定的电视机。

tv.cpp 列出了其余的定义。音量设置函数将音量成员增减一个单位，除非声音到达最大或最小。频道选择函数使用循环方式，最低的频道设置为 1，它位于最高的频道设置
maxchannel 之后。

很多方法都使用条件运算符在两种状态之间切换:

void onoff(){state = (state == On)? Off:On}

如果两种状态值分别为 true（1）和 false（0），则可以结合使用将在附录E讨论的按位异或和赋值运算符（^=）来简化上述代码:

void onoff() {state^=1;}


'类友元是一种自然用语，用于表示一些关系'。如果不使用某些形式的友元关系，则必须将 Tv 类的私有部分设置为公有的，或者创建一个笨拙的、大型类来包含电视机和遥控器。
这种解决方法无法反应这样的事实, 即同一个遥控器可用于多台电视机。


// !! 友元成员函数

从上一个例子中的代码可知，大多数 Remote 方法都是用 Tv 类的公有接口实现的。这意味着这些方法不是真正需要作为友元。事实上，唯一直接访问 Tv 成员的 Remote 方法
是 Remote::set_chan()，因此它是唯一需要作为友元的方法。'确实可以选择仅让特定的类成员成为另一个类的友元，而不必让整个类成为友元'，但这样做稍微有点麻烦，必须小
心排列各种声明和定义的顺序。下面介绍其中的原因。

让Remote::set_chan() 成为 Tv 类的友元的方法是，在 Tv 类声明中将其声明为友元：


class Tv
{
    friend void Remote::set_chan(Tv &t, int c);
    ...
};


然而，要使编译器能够处理这条语句，它必须知道 Remote 的定义。否则，它无法知道 Remote 是一个类，而 set_chan 是这个类的方法。这意味着应将 Remote 的定义放到
Tv 的定义前面。Remote 的方法提到了 Tv 对象，而这意味着 Tv 定义应当位于 Remote 定义之前。'避开这种循环依赖的方法是，使用前向声明(forward declaration)'。
为此，需要在 Remote 定义的前面插入下面的语句:

class Tv;// forward declaration

这样，排列次序应如下:

class Tv;// forward declaration
class Remote
{

};

class Tv
{

};

能否像下面这样排列呢？


class Remote;// forward declaration

class Tv
{

};

class Remote
{

};


答案是不能。原因在于，在编译器在 Tv 类的声明中看到 Remote 的一个方法被声明为 Tv 类的友元之前，应该先看到 Remote 类的声明和 set_chan() 方法的声明。


还有一个麻烦, Remote 声明包含了内联代码，例如:

void onoff(Tv &t) {t.onoff();}

由于这将调用 Tv 的一个方法，所以编译器此时必须已经看到了 Tv 类的声明，这样才能知道 Tv 有哪些方法，但正如看到的，该声明位于 Remote 声明的后面。这种问
题的解决方法是，使 Remote 声明中只包含方法声明，并将实际的定义放在 Tv 类之后。这样，排列顺序将如下:

class Tv;// forward declaration

class Remote// Tv-using method as propertypes only
{

};

class Tv
{

};

// put remote method definition here

Remote 方法的原型与下面类似:

void onoff(Tv &t);

检查该原型时，所有的编译器都需要知道 Tv 是一个类，而前向声明提供了这样的信息。当编译器到达真正的方法定义时，它已经读取了 Tv 类的声明，并拥有了编译这些方法
所需的信息。通过在方法定义中使用 inline 关键字, 仍然可以使其成为内联方法。tvfm.h 列出了修订后的头文件。

如果在 tv.cpp 和 use_tv.cpp 中包含 tvfm.h 而不是 tv.h，程序的行为与前一个程序相同，区别在于，只有一个 Remote 方法是 Tv 类的友元，而在原来的版本中，
所有的 Remote 方法都是 Tv 类的友元。

// !! 嵌套类

'在 C++ 中, 可以将类声明放在另一个类中'。在另一个类中声明的类被称为嵌套类(nested class)，它通过提供新的类型类作用域来避免名称混乱。包含类的成员函数可以创
建和使用被嵌套类的对象; '仅当声明位于公有部分，才能在包含类的外面使用嵌套类，而且必须使用作用域解析运算符'。

对类进行嵌套与包含并不同。'包含意味着将类对象作为另一个类的成员，而对类进行嵌套不创建类成员，而是定义了一种类型，该类型仅在包含嵌套类声明的类中有效'。

'对类进行嵌套通常是为了帮助实现另一个类，并避免名称冲突'。

Queue 类示例嵌套了结构定义，从而实现了一种变相的嵌套类:

class Queue
{
    private:
        // class scope definitions
        // Node is nested structure definition local to this class
        struct Node{
            Item item;
            struct Node * next;
        }
        ...
};


由于结构是一种其成员在默认情况下为公有的类，所以 Node 实际上是一个嵌套类，但该定义并没有充分利用类的功能。具体地说，它没有显式构造函数，下面进行补救。

首先，找到 Queue 示例中创建 Node 对象的位置。从类声明和方法定义可知，唯一创建了 Node 对象的地方是 enqueue() 方法:

bool Queue::enqueue(Item item)
{
    if(isFull())
    {
        return false;
    }
    Node *add = new Node();
    add->item = item;
    add->next = nullptr;
    ...
}

上述代码创建 Node 后，显式地给 Node 成员赋值，这种工作更适合由构造函数来完成。

知道应在什么地方以及如何使用构造函数后，便可以提供一个适当的构造函数定义:

class Queue
{
    class Node
    {
        public:
            Item item;
            Node * next;
            Node(const Item & i) : item(i),next(0){}
    };

    ...
};

该构造函数将节点的 item 成员初始化为 i，并将 next 指针设置为 0，这是使用 C++ 编写空值指针的方法之一(使用 NULL 时，必须包含一个定义 NULL 的头文
件; 如果您使用的编译器支持 C++11，可使用 nullptr)。

接下来，需要使用构造函数重新编写 enqueue()：

bool Queue::enqueue(const Item &item)
{
    if(isFull()) return false;

    Node * add = new Node(item);
    ...
}

这使得 enqueue() 的代码更短，也更安全，因为它自动进行初始化，无需程序员记住应做什么。


// !! 嵌套类和访问权限

有两种访问权限适合于嵌套类。首先，嵌套类的声明位置决定了嵌套类的作用域, 即它决定了程序的哪些部分可以创建这种类的对象。其次，和其他类一样，嵌套类的公有部分、保
护部分和私有部分控制了对类成员的访问。

'在哪些地方可以使用嵌套类以及如何使用嵌套类，取决于作用域和访问控制'。

// !! 作用域

1. 如果嵌套类是在另一个类的私有部分声明的，则只有后者知道它。

2. 如果嵌套类是在另一个类的公有部分声明的，则允许后者、后者的派生类以及外部世界使用它，因为它是公有的。然而，由于嵌套类的作用域为包含它的类，因此在外部世界使用
   它时，必须使用类限定符。

class Team
{
    public:
        class Coach
        {
            ...
        }
        ...
};

现在假定有一个失业的教练，他不属于任何球队。要在 Team 类的外面创建 Coach 对象，可以这样做:

Team::Coach forhire;

嵌套结构和枚举的作用域与此相同。'其实，很多程序员都使用公有枚举来提供可供客户程序员使用的类常数'。


// !! 访问控制

类可见后，起决定作用的将是访问控制。对嵌套类访问权的控制规则与对常规类相同。

'总之，类声明的位置决定了类的作用域或可见性。类可见后，访问控制规则(公有、保护、私有、友元)将决定程序对嵌套类成员的访问权限'。


// !! 模板中的嵌套



// !!  异常

程序有时会遇到运行阶段错误, 导致程序无法正常地运行下去。例如，程序可能试图打开一个不可用的文件, 请求过多的内存，或者遭遇不能容忍的值。通常，程序员都会试图预
防这种意外情况。'C++ 异常为处理这种情况提供了一种功能强大而灵活的工具'。异常是相对较新的 C++ 功能，有些老式编译器可能没有实现。另外，有些编译器默认关闭这种特
性，您可能需要使用编译器选项来启用它。

讨论异常之前，先来看看程序员可使用的一些基本方法。作为试验，以一个计算两个数的调和平均数的函数为例。两个数的调和平均数的定义是：这两个数字倒数的平均值的倒数，
因此表达式为:

2.0 * x *y/(x+y);

如果 y 是 x 的负值，则上述公式将导致被零除---一种不允许的运算。对于被零除的情况, 很多新式编译器通过生成一个表示无穷大的特殊浮点值来处理，cout 将这种值显示为
Inf、inf、INF 或类似的东西; 而其他的编译器可能生成在发生被零除时崩溃的程序。最好编写在所有系统上都以相同的受控方式运行的代码。


// !! 调用 abort()

对于这种问题，处理方式之一是，如果其中一个参数是另一个参数的负值，则调用 abort() 函数。Abort() 函数的原型位于头文件 cstdlib或 stdlib.h)中，其典型实现是向
标准错误流(即 cerr 使用的错误流)发送消息  abnormal program termination, 然后终止程序。它还返回一个随实现而异的值，告诉操作系统(如果程序是由另一个程序调用
的，则告诉父进程)，处理失败。abort() 是否刷新文件缓冲区(用于存储读写到文件中的数据的内存区域)取决于实现。'如果愿意，也可以使用 exit()，该函数刷新文件缓冲区，
但不显示消息'。

#include <iostream>
#include <cstdlib>

double hmean(double a, double b);

int main()
{
    double x, y,z;
    std::cout << "Enter two number:\n";
    while(std::cin >> x >> y)
    {
        z = hmean(x, y);
        std::cout << "Harmonic mead of " << x << " and " << y << " is " << z << std::endl;
        std::cout << "Enter next set number(q to quit):" << std::endl;
    }
    std::cout << "Bye~";
    return 0;
}


double hmean(double a, double b)
{
    if(a == -b)
    {
        std::cout << "untenable argument to hmean\n";
        std::abort();
    }
    return 2.0 * a * b/(a+b);
}

 » g++ --std=c++11 error1.cpp 
--------------------------------------------------------------------------------
 » ./a.out
Enter two number:
1 -1
untenable argument to hmean
[1]    896707 abort (core dumped)  ./a.out

为了避免异常终止，程序应在调用 hmean() 函数之前检查 x 和 y 的值。然而，依


// !! 返回错误码

'一种比异常终止更灵活的方法是，使用函数的返回值来指出问题'。例如，ostream 类的 get（void）成员通常返回下一个输入字符的 ASCII 码，但到达文件尾时，将返回特殊
值 EOF。对 hmean() 来说，这种方法不管用。任何数值都是有效的返回值，因此不存在可用于指出问题的特殊值。在这种情况下，可使用指针参数或引用参数来将值返回给调用程
序，并使用函数的返回值来指出成功还是失败。istream 族重载 >> 运算符使用了这种技术的变体。通过告知调用程序是成功了还是失败了，使得程序可以采取除异常终止程序之外
的其他措施。

error2.cpp 是一个采用这种方式的示例，它将 hmean() 的返回值重新定义为 bool，让返回值指出成功了还是失败了，另外还给该函数增加了第三个参数，用于提供答案。

#include <iostream>
#include <cfloat> // for DBL_MAX

bool hmean(double a, double b, double *ans);

int main()
{
    double x, y, z;
    std::cout << "Enter two number:\n";
    while (std::cin >> x >> y)
    {
        if (hmean(x, y, &z))
        {
            std::cout << "Harmonic mead of " << x << " and " << y << " is " << z << std::endl;
        }
        else
        {
            std::cout << "One value should not be negative of the other\n";
        }
        std::cout << "Enter next set number(q to quit):" << std::endl;
    }
    std::cout << "Bye~\n";
    return 0;
}

bool hmean(double a, double b, double *ans)
{
    if (a == -b)
    {
        *ans = DBL_MAX;
        return false;
    }
    *ans = 2.0 * a * b / (a + b);
    return true;
}


 » g++ --std=c++11 error2.cpp
--------------------------------------------------------------------------------
 » ./a.out
Enter two number:
1 -1
One value should not be negative of the other
Enter next set number(q to quit):


程序设计避免了错误输入导致的恶果，让用户能够继续输入。'当然，设计确实依靠用户检查函数的返回值，这项工作是程序员所不经常做的'。

第三参数可以是指针或引用。对内置类型的参数，很多程序员都倾向于使用指针，因为这样可以明显看出是哪个参数用于提供答案。

另一种在某个地方存储返回条件的方法是使用一个全局变量。可能问题的函数可以在出现问题时将该全局变量设置为特定的值，而调用程序可以检查该变量。'传统的 C 语言数学
库使用的就是这种方法，它使用的全局变量名为 errno'。当然，必须确保其他函数没有将该全局变量用于其他目的。


// !! 异常机制

'C++ 异常是对程序运行过程中发生的异常情况(例如被 0 除)的一种响应'。异常提供了将控制权从程序的一个部分传递到另一部分的途径。

对异常的处理有 3 个组成部分:

1. 引发异常

2. 使用处理程序捕获异常

3. 使用 try 块

程序在出现问题时将引发异常。例如，可以修改 hmean()，使之引发异常，而不是调用 abort() 函数。throw 语句实际上是跳转，即命令程序跳到另一条语句。throw 关键字表
示引发异常，紧随其后的值(例如字符串或对象)指出了异常的特征。

程序使用异常处理程序(exception handler)来捕获异常，异常处理程序位于要处理问题的程序中。catch 关键字表示捕获异常。处理程序以关键字 catch 开头，随后是位于括
号中的类型声明，它指出了异常处理程序要响应的异常类型; 然后是一个用花括号括起的代码块，指出要采取的措施。catch 关键字和异常类型用作标签，指出当异常被引发时，程
序应跳到这个位置执行。异常处理程序也被称为 catch 块。

try 块标识其中特定的异常可能被激活的代码块，它后面跟一个或多个 catch 块。try 块是由关键字 try 指示的，关键字 try 的后面是一个由花括号括起的代码块，表明需要注
意这些代码引发的异常。


要了解这 3 个元素是如何协同工作的，最简单的方法是看一个简短的例子，如 error3.cpp 所示。

#include <iostream>
#include <cstdlib>

double hmean(double a, double b);

int main()
{
    double x, y,z;
    std::cout << "Enter two number:\n";
    while(std::cin >> x >> y)
    {
        try
        {// start of try block
            z = hmean(x, y);
        }// end of try block
        catch(const char *s)// start of exception handler
        {
            std::cout << s << std::endl;
            std::cout << "Enter a new pair of numbers:\n";
            continue;
        }
    }
    std::cout << "Bye~";
    return 0;
}


double hmean(double a, double b)
{
    if(a == -b)
    {
        throw "bad hmean() argument: a = -b not allowed"
    }
    return 2.0 * a * b/(a+b);
}


引发异常的代码与下面类似：

    if(a == -b)
    {
        throw "bad hmean() argument: a = -b not allowed"
    }

其中被引发的异常是字符串 “bad hmean() arguments: a = -b not allowed”。异常类型可以是字符串或其他C++类型， 通常为类类型。

执行 throw 语句类似于执行返回语句，因为它也将终止函数的执行； '但 throw 不是将控制权返回给调用程序，而是导致程序沿函数调用序列后退，直到找到包含 try 块的
函数'。

处理程序(或 catch 块)与下面类似:

        catch(const char *s)// start of exception handler
        {
            std::cout << s << std::endl;
            std::cout << "Enter a new pair of numbers:\n";
            continue;
        }


关键字 catch 表明这是一个处理程序，而 char *s 则表明该处理程序与字符串异常匹配。

执行完 try 块中的语句后，如果没有引发任何异常，则程序跳过 try 块后面的 catch 块，直接执行处理程序后面的第一条语句。

'如果函数引发了异常，而没有 try 块或没有匹配的处理程序时，将会发生什么情况。在默认情况下下，程序最终将调用 abort() 函数，但可以修改这种行为'。


// !! 将对象用作异常类型

'通常，引发异常的函数将传递一个对象'。

这样做的重要优点之一是，可以使用不同的异常类型来区分不同的函数在不同情况下引发的异常。另外，对象可以携带信息，程序员可以根据这些信息来确定引发异常的原因。
同时，catch 块可以根据这些信息来决定采取什么样的措施。

例如，下面是针对函数 hmean() 引发的异常而提供的一种设计:

class bad_hmean
{
    private:
        double v1;
        double v2;
    public:
        bad hmean(int a = 0, int b = 0):v1(a),v2(b){}
        void mesg();
};

inline bad hmean::mesg()
{
    std::cout << "hmean("<< v1 << "," << v2 << "):"
    << "invalid arguments: a = -b\n";
}

可以将一个 bad_hmean 对象初始化为传递给函数 hmean() 的值，而方法 mesg() 可用于报告问题。函数 hmean() 可以使用下面这样的代码:

if(a == -b)
{
    throw bad_hmean(a,b);
}

上述代码调用构造函数 bad_hmean()，以初始化对象，使其存储参数值。



// !! 异常规范和 C++11

'有时候，一种理念看似有前途，但实际的使用效果并不好'。一个这样的例子是异常规范(exception specification)，这是 C++98 新增的一项功能，但 C++11 却将其摒弃
了。这意味着 C++11 仍然处于标准之中，但以后可能会从标准中剔除，因此不建议您使用它。

然而，忽视异常规范前，您至少应该知道它是什么样的，如下所示:

double harm(double a, double b) throw(bad_thing);// may throw bad_thing exception
double marm() throw();// doesn't' throw a exception

其中的 throw() 部分就是异常规范，它可能出现在函数原型和函数定义中，可包含类型列表，也可不包含。

异常规范的作用之一是，告诉用户可能需要使用 try 块。然而，这项工作也可使用注释轻松地完成。异常规范的另一个作用是，让编译器添加执行运行阶段检查的代码，检查是否违
反了异常规范。这很难检查。

例如，marm() 可能不会引发异常，但它可能调用一个函数，而这个函数调用的另一个函数引发了异常。另外，您给函数编写代码时它不会引发异常，但库更新后它却会引发异常。总
之，编程社区(尤其是尽力编写安全代码的开发人员)达成的一致意见是，最好不要使用这项功能。而 C++11 也建议您忽略异常规范。

然而，C++11 确实支持一种特殊的异常规范：您可使用新增的关键字 noexcept 指出函数不会引发异常：

double marm() noexcept;// marm() doesn't' throw exception

有关这种异常规范是否必要和有用存在一些争议，有些人认为最好不要使用它(至少在大多数情况下如此)；而有些人认为引入这个新关键字很有必要，理由是知道函数不会引发异常有
助于编译器优化代码。通过使用这个关键字，编写函数的程序员相当于做出了承诺。

// !! 栈解退

假设 try 块没有直接调用引发异常的函数，而是调用了对引发异常的函数进行调用的函数，则程序流程将从引发异常的函数跳到包含 try 块和处理程序的函数。

这涉及到栈解退(unwinding the stack)。

首先来看一看 C++ 通常是如何处理函数调用和返回的。C++ 通常通过将信息放在栈中来处理函数调用。具体地说，程序将调用函数的指令的地址(返回地址)放到栈中。当被调用的函
数执行完毕后，程序将使用该地址来确定从哪里开始继续执行。另外，函数调用将函数参数放到栈中。在栈中，这些函数参数被视为自动变量。如果被调用的函数创建了新的自动变量
，则这些变量也将被添加到栈中。如果被调用的函数调用了另一个函数，则后者的信息将被添加到栈中，依此类推。当函数结束时，程序流程将跳到该函数被调用时存储的地址处，同时
栈顶的元素被释放。'因此，函数通常都返回到调用它的函数，依此类推，同时每个函数都在结束时释放其自动变量'。如果自动变量是类对象，则类的析构函数(如果有的话)将被调用。

现在假设函数由于出现异常而终止，则程序也将释放栈中的内存, 但不会在释放栈的第一个返回地址后停止，而是继续释放栈，直到找到一个位于 try 块中的返回地址。

error5.cpp 是一个栈解退的示例。其中，main() 调用了 means()，而 means() 又调用了 hmean() 和 gmean()。函数 means() 计算算术平均数、调和平均数和几何平
均数。


#include <iostream>
#include <cmath>
#include <string>
#include "exc_mean.h"

class demo
{
    private:
        std::string word;

    public:
        demo(const std::string &str)
        {
            word = str;
            std::cout << "demo " << word <<" created\n";
        }

        ~demo()
        {
            std::cout << "demo " << word << " deleted\n";
        }

        void show() const
        {
            std::cout << "demo " << word << " lives!\n";
        }
};

// function prototypes
double hmean(double a, double b);
double gmean(double a, double b);
double means(double a, double b);

int main()
{
    using std::cout;
    using std::endl;
    using std::cin;

    double x, y;
    double z;
    {
        demo d1("found in block in main()");
        cout << "Enter two numbers:\n";
        while (cin >> x >> y)
        {
            try
            {
                z = means(x, y);
                cout << "The means of " << x << " and " << y << "is " << z << endl;
                cout << "Enter next pair:\n";
            }
            catch(bad_hmean &bg)
            {
                bg.mesg();
                cout << "Try Again:\n";
                continue;
            }
            catch(bad_gmean &bg)
            {
                bg.mesg();
                cout << "The values Used " << bg.v1 << " and " << bg.v2 << endl;
                cout << "SOrry , you don't get to play more\n";
                break;
            }    
        }
        d1.show();
    }
    cout << "Bye!\n";
    cin.get();
    cin.get();
    return 0;
}

double hmean(double a, double b)
{
    if(a == -b)
    {
        throw bad_hmean(a,b);
    }
    return 2.0 * a * b/(a+b);
}

double gmean(double a, double b)
{
    if(a < 0 || b < 0)
    {
        throw bad_gmean(a,b);
    }
    return std::sqrt(a*b);
}

double means(double a, double b)
{
    double am,hm,gm;
    demo d2("found in means");
    am = (a + b)/2.0;
    try
    {
        hm = hmean(a, b);
        gm = gmean(a, b);
    }
    catch(bad_hmean &bg)
    {
        bg.mesg();
        std::cout << "Caught in means() ";
        throw;// rethrow the exception
    }
    d2.show();
    return (am + hm + gm)/ 3.0;
}

 » g++ --std=c++11 error5.cpp                                                                     
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
» ./a.out                                                                                         
demo found in block in main() created
Enter two numbers:
6 12
demo found in means created
demo found in means lives!
demo found in means deleted
The means of 6 and 12is 8.49509
Enter next pair:
6 -6
demo found in means created
hmean(6,-6):invalid arguments: a = -b
Caught in means() demo found in means deleted
hmean(6,-6):invalid arguments: a = -b
Try Again:
6 -8
demo found in means created
demo found in means deleted
The values Used 6 and -8
SOrry , you don't get to play more
demo found in block in main() lives!
demo found in block in main() deleted
Bye!

1. 首先，正如 demo 类的构造函数指出的，在 main() 函数中创建了一个 demo 对象。接下来，调用了函数 means()，它创建了另一个 demo 对象。函数 means()
   使用 6 和 12 来调用函数 hmean() 和 gmean()，它们将结果返回给 means()，后者计算一个结果并将其返回。返回结果前，means() 调用了 d2.show()；返回结果
   后，函数 means() 执行完毕，因此自动为 d2 调用析构函数:

   demo found in means lives!
   demo found in means deleted 

2. 接下来的输入循环将值 6 和 −6 发送给函数 means()，然后 means() 创建一个新的 demo 对象，并将值传递给 hmean()。函数 hmean() 引发 bad_hmean 异常，
   该异常被means() 中的 catch 块捕获，下面的输出指出了这一点:

   hmean(6,-6):invalid arguments: a = -b
   Caught in means() 

   该 catch 块中的 throw 语句导致函数 means() 终止执行，并将异常传递给 main() 函数。语句 d2.show() 没有被执行表明 means()函数被提前终止。但需要指出的
   是，还是为 d2 调用了析构函数：

   demo found in means deleted
   
   这演示了异常极其重要的一点:程序进行栈解退以回到能够捕获异常的地方时， 将释放栈中的自动存储型变量。如果变量是类对象，将为该对象调用析构函数。


3. 与此同时，重新引发的异常被传递给 main()，在该函数中，合适的 catch 块将捕获它并对其进行处理：

    hmean(6,-6):invalid arguments: a = -b
    Try Again:



异常机制将负责释放栈中的自动变量。


// !! exception 类

C++ 异常的主要目的是为设计容错程序提供语言级支持，即异常使得在程序设计中包含错误处理功能更容易，以免事后采取一些严格的错误处理方式。异常的灵活性和相对方便性激
励着程序员在条件允许的情况下在程序设计中加入错误处理功能。总之，异常是这样一种特性：类似于类，可以改变您的编程方式。

较新的 C++ 编译器将异常合并到语言中。例如，为支持该语言，exception 头文件定义了 exception 类，C++ 可以把它用作其他异常类的基类。代码可以引发 exception 
异常，也可以将 exception 类用作基类。有一个名为 what() 的虚拟成员函数，它返回一个字符串，该字符串的特征随实现而异。然而，由于这是一个虚方法，因此可以在从 
exception 派生而来的类中重新定义它:

#include<exception>

class bad_hmean: public std::exception
{
    public:
        const char * what()
        {
            return "bad arguments to hmean()";
        }
        ...
};

class bad_gmean: public std::exception
{
    public:
        const char * what()
        {
            return "bad arguments to gmean()";
        }
        ...
};

如果不想以不同的方式处理这些派生而来的异常, 可以在同一个基类处理程序中捕获它们:

try
{
    /* code */
}
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
}

否则，可以分别捕获它们。

C++ 库定义了很多基于 exception 的异常类型。


1. stdexcept 异常类

头文件 stdexcept 定义了其他几个异常类。首先，该文件定义了 logic_error 和 runtime_error 类，它们都是以公有方式从 exception 派生而来的:

class logic_error: public exception
{
    public:
        explicit logic_error(const std::string &what_msg);
        ...
};


class domain_error: public logic_error
{
    public:
        explicit domain_error(const std::string &what_msg);
        ...
};


注意，这些类的构造函数接受一个 string 对象作为参数，该参数提供了方法 what() 以 C-风格字符串方式返回的字符数据。

这两个新类被用作两个派生类系列的基类。异常类系列 logic_error 描述了典型的逻辑错误。总体而言，通过合理的编程可以避免这种错误，但实际上这些错误还是可能发生
的。每个类的名称指出了它用于报告的错误类型:

1. domain_error

2. invalid_argument

3. length_error

4. out_of_bounds

每个类独有一个类似于 logic_error 的构造函数，让您能够提供一个供方法 what() 返回的字符串。

1. 数学函数有定义域(domain)和值域(range)。'定义域由参数的可能取值组成, 值域由函数可能的返回值组成'。如果您编写一个函数，该函数将一个参数传递给函数 
   std::sin()，则可以让该函数在参数不在定义域 −1 到 +1 之间时引发 domain_error 异常。

2. 异常 invalid_argument 指出给函数传递了一个意料外的值。例如，如果函数希望接受一个这样的字符串: 其中每个字符要么是 ‘0’ 要么是 ‘1’，则当传递的字符串中包含
   其他字符时，该函数将引发 invalid_argument 异常。

3. 异常 length_error 用于指出没有足够的空间来执行所需的操作。例如，string 类的 append() 方法在合并得到的字符串长度超过最大允许长度时，将引发 length_error
   异常。
4. 异常 out_of_bounds 通常用于指示索引错误, 例如，您可以定义一个类似于数组的类，其 operator()[] 在使用的索引无效时引发 out_of_bounds 异常


接下来，runtime_error 异常系列描述了可能在运行期间发生但难以预计和防范的错误。每个类的名称指出了它用于报告的错误类型：

1. range_error

2. overflow_error

3. underflow_error

每个类独有一个类似于 runtime_error 的构造函数，让您能够提供一个供方法 what() 返回的字符串。

1. 下溢(underflow)错误在浮点数计算中。一般而言，存在浮点类型可以表示的最小非零值，计算结果比这个值还小时将导致下溢错误

2. 整型和浮点型都可能发生上溢错误，当计算结果超过了某种类型能够表示的最大数量级时，将发生上溢错误

3. 计算结果可能不再函数允许的范围之内，但没有发生上溢或下溢错误，在这种情况下，可以使用range_error异常

一般而言，logic_error 系列异常表明存在可以通过编程修复的问题，而 runtime_error 系列异常表明存在无法避免的问题。所有这些错误类有相同的常规特征，它们之间的主
要区别在于：不同的类名让您能够分别处理每种异常。另一方面，继承关系让您能够一起处理它们。


// !! bad_alloc 异常和 new

对于使用 new 导致的内存分配问题，C++ 的最新处理方式是让 new 引发 bad_alloc 异常。头文件 new 包含 bad_alloc 类的声明，它是从 exception 类公有派生而来的。
但在以前，当无法分配请求的内存量时，new 返回一个空指针。

#include <iostream>
#include <new>
#include <cstdlib>// for exit(), EXIT_FAILURE

using namespace std;


struct Big 
{
    double stuff[2000000000000];
};

int main()
{
    Big *pb;
    try
    {
        cout << "Try to get a big block of memory" << endl;
        pb = new Big[100000];
        cout << "Got past the new request:\n";
    }
    catch(bad_alloc &ba)
    {
        cout << "Caught the exception\n";
        cout << ba.what() << endl;
        exit(EXIT_FAILURE);
    }
    cout << "Memory successfully allocated\n";
    pb[0].stuff[0] = 4;
    cout << pb[0].stuff[0] << endl;
    delete[] pb;
    return 0;
}

 » g++ --std=c++11 newexcp.cpp
--------------------------------------------------------------------------------
 » ./a.out
Try to get a big block of memory
Caught the exception
std::bad_alloc
----------------


// !! 空指针和 new

很多代码都是在 new 失败时返回空指针时编写的。为处理 new 的变化，有些编译器提供了一个标记（开关），让用户选择所需的行为。当前，C++ 标准提供了一种在失败时返回
空指针的 new，其用法如下：

int *pi = new(std::nothrow) int();


// !! 异常、类和继承

异常、类和继承以三种方式相互关联。首先，可以像标准 C++ 库所做的那样，从一个异常类派生出另一个；其次，可以在类定义中嵌套异常类声明来组合异常；第三，这种嵌套声明
本身可被继承，还可用作基类。

#ifndef B668A86D_E02F_489A_A7E8_8666633077E8
#define B668A86D_E02F_489A_A7E8_8666633077E8

#include <stdexcept>
#include <string>

class Sales
{
    protected:
        enum {MONTHS = 12};

    public:
        class bad_index: public std::logic_error
        {
            private:
                int bi;
            public:
                explicit bad_index(int ix, const std::string &s = "Index Error in Sales Object");
                int bi_val() const { return bi;}
                virtual ~bad_index() throw(){}
        };
        explicit Sales(int yy = 0);
        Sales(int yy, const double *gr, int n);
        virtual ~Sales();
        int year() const { return year;}
        virtual double operator()(int i) const;
        virtual double &operator()(int i);
    private:
        double ggross[MONTHS];
        int year;
};

class LabeledSales: public Sales
{
    public:
        class nbad_index: public Sales::bad_index
        {
            private:
                std::string lbl;
            public:
                nbad_index(const std::string &lb, int ix, const std::string &s = "Index Error in LabeledSales Object\n");
                const std::string & label_val() const{return lbl;}
                virtual ~nbad_index() throw() {}
        };
        explicit LabeledSales(const std::string &lb = "none", int yy = 0);
        LabeledSales(connst std::strchr &lb,int yy, const double * gr, int n);
        virtual ~LabeledSales(){}
        const std::string & Label() const{return label;}
        virtual double operator()(int i)const;
        virtual double &operator()(int i);
    private:
        int label;
};

#endif /* B668A86D_E02F_489A_A7E8_8666633077E8 */


1. 首先，符号常量 MONTHS 位于 Sales 类的保护(protected)部分，这使得派生类(如 LabeledSales)能够使用这个值。

2. bad_index 被嵌套在 Sales 类的公有(public)部分中，这使得客户类的 catch 块可以使用这个类作为类型。注意，在外部使用这个类型时，需要使用 Sales::bad_index 
   来标识。这个类是从 logic_error 类派生而来的, 能够存储和报告数组索引的超界值(out-of-bounds value)

3. nbad_index 类被嵌套到 LabeledSales 的公有部分，这使得客户类可以通过 LabeledSales::nbad_index 来使用它

4. 这两个类都有重载的 operator[]()方法，这些方法设计用于访问存储在对象中的数组元素，并在索引超界时引发异常。

5. bad_index 和 nbad_index 类都使用了异常规范 throw()，这是因为它们都归根结底是从基类 exception 派生而来的，而 exception 的虚构造函数使用了异常规
   范 throw()。这是 C++98 的一项功能，在 C++11 中，exception 的构造函数没有使用异常规范。




// !! 异常何时会迷失方向

异常被引发后，在两种情况下，会导致问题。

1. 如果它是在带异常规范的函数中引发的，则必须与规范列表中的某种异常匹配，否则称为意外异常(unexpected exception)。在默认情况下，这将导致程序异常终止

2. 如果异常不是在函数中引发的(或者函数没有异常规范)，则必须捕获它。如果没被捕获(在没有 try 块或没有匹配的 catch 块时，将出现这种情况)，则异常被称为未捕获异
   常(uncaught exception)。在默认情况下，这将导致程序异常终止。

然而，可以修改程序对意外异常和未捕获异常的反应。

未捕获异常不会导致程序立刻异常终止。相反，程序将首先调用函数 terminate()。在默认情况下，terminate() 调用 abort() 函数。可以指定 terminate() 应调用的
函数(而不是abort()) 来修改 terminate() 的这种行为。为此，可调用 set_terminate() 函数。set_terminate() 和 terminate() 都是在头文件 exception
中声明的：

typedef void(*terminate_handler)();

terminate_handler set_terminate(terminate_handler f) throw();// c++98
terminate_handler set_terminate(terminate_handler f) noexcept;// c++11

void terminate()// c++98
void terminate() noexcept;// C++11

其中的 typedef 使 terminate_handler 成为这样一种类型的名称: 指向没有参数和返回值的函数的指针。

set_terminate() 函数将不带任何参数且返回类型为 void 的函数的名称(地址)作为参数，并返回该函数的地址。如果调用了 set_terminate() 函数多次，则
terminate() 将调用最后一次 set_terminate() 调用设置的函数。


假设希望未捕获的异常导致程序打印一条消息，然后调用 exit() 函数，将退出状态值设置为5。首先，请包含头文件 exception。可以使用 using 编译指令、适当的 
using 声明或 std:: 限定符，来使其声明可用。

#include <exception>
using namespace std;

然后，设计一个完成上述两种操作所需的函数，其原型如下:

void myQuite()
{
    cout << "Terminating due to uncaught exception\n" << endl;
    exit(5);
}

最后，在程序的开头，将终止操作指定为调用该函数。

set_terminate(myQuite);

现在，如果引发了一个异常且没有被捕获，程序将调用 terminate()，而后者将调用 MyQuit()。

接下来看意外异常。通过给函数指定异常规范，可以让函数的用户知道要捕获哪些异常。假设函数的原型如下:

double Argh(double, double) throw(out_of_bounds);

则可以这样使用该函数:

try
{
    x = Argh(1.2,3.4);
}
catch (out_of_bounds &ex) 
{

}

知道应捕获哪些异常很有帮助，因为默认情况下, 未捕获的异常将导致程序异常终止。

'原则上，异常规范应包含函数调用的其他函数引发的异常'。例如，如果 Argh() 调用了 Duh() 函数，而后者可能引发 retort 对象异常，则 Argh() 和 Duh() 
的异常规范中都应包含 retort。除非自己编写所有的函数，并且特别仔细，否则无法保证上述工作都已正确完成。例如，可能使用的是老式商业库，而其中的函数没有异常规范。
这表明应进一步探讨这样一点，即如果函数引发了其异常规范中没有的异常，情况将如何？'这也表明异常规范机制处理起来比较麻烦，这也是 C++11 将其摒弃的原因之一'。


// !!有关异常的注意事项

从前面关于如何使用异常的讨论可知, 应在设计程序时就加入异常处理功能，而不是以后再添加。这样做有些缺点。例如，'使用异常会增加程序代码，降低程序的运行速度'。
异常规范不适用于模板，因为模板函数引发的异常可能随特定的具体化而异。异常和动态内存分配并非总能协同工作。

下面进一步讨论动态内存分配和异常。首先，请看下面的函数:

void test1(int n)
{
    std::string mesg("I am trapped in an endless loop\n");
    ...
    if(oh_no)
    {
        throw exception();
    }
    ...
    return;
}

string 类采用动态内存分配。通常，当函数结束时，将为 mesg 调用 string 的析构函数。虽然 throw 语句过早地终止了函数，但它仍然使得析构函数被调用，这要归功于
栈解退。因此在这里，内存被正确地管理。


void test2(int n)
{
    double *ar = new double[n];
    ...
    if(oh_no)
    {
        throw exception();
    }
    ...
    delete[] ar;
    return;
}


这种泄漏是可以避免的。例如，可以在引发异常的函数中捕获该异常，在 catch 块中包含一些清理代码，然后重新引发异常:

void test3(int n)
{
    double *ar = new double[n];
    ...
    try
    {
        if(oh_no)
        {
            throw exception();
        }
    }
    catch(const std::exception& e)
    {
        delete[]ar;
        throw;
    }
    ...
    delete[] ar;
    return;
}


然而，这将增加疏忽和产生其他错误的机会。

'总之，虽然异常处理对于某些项目极为重要，但它也会增加编程的工作量、增大程序、降低程序的速度。另一方面，不进行错误检查的代价可能非常高'。

// !! 异常处理

在现代库中，异常处理的复杂程度可能再创新高---主要原因在于文档没有对异常处理例程进行解释或解释得很蹩脚。任何熟练使用现代操作系统的人都遇到过未处理的异常导致的错
误和问题。这些错误背后的程序员通常面临一场艰难的战役，需要不断了解库的复杂性：什么异常将被引发，它们发生的原因和时间，如何处理它们，等等。程序员新手很快将发现，
理解库中异常处理像学习语言本身一样困难，现代库中包含的例程和模式可能像 C++ 语法细节一样陌生而困难。要开发出优秀的软件，必须花时间了解库和类中的复杂内容，就像
必须花时间学习 C++ 本身一样。'通过库文档和源代码了解到的异常和错误处理细节将使程序员和他的软件受益'。

// !! RTTI

'RTTI 是运行阶段类型识别(Runtime Type Identification)的简称'。这是新添加到 C++ 中的特性之一，很多老式实现不支持。'RTTI 旨在为程序在运行阶段确定对象的
类型提供一种标准方式'。

假设有一个类层次结构, 其中的类都是从同一个基类派生而来的，则可以让基类指针指向其中任何一个类的对象。这样便可以调用这样的函数：在处理一些信息后，选择一个类，并创
建这种类型的对象，然后返回它的地址，而该地址可以被赋给基类指针。

如何知道指针指向的是哪种对象呢？

在回答这个问题之前，先考虑为何要知道类型。可能希望调用类方法的正确版本，在这种情况下，只要该函数是类层次结构中所有成员都拥有的虚函数，则并不真正需要知道对象的
类型。但派生对象可能包含不是继承而来的方法，在这种情况下，只有某些类型的对象可以使用该方法。也可能是出于调试目的，想跟踪生成的对象的类型。对于后两种情况，RTTI
提供解决方案。


// !! RTTI 的工作原理

C++ 有 3 个支持 RTTI 的元素。

1. 如果可能的话, dynamic_cast 运算符将使用一个指向基类的指针来生成一个指向派生类的指针; 否则，该运算符返回 0---空指针

2. typeid 运算符返回一个指出对象的类型的值

3. type_info 结构存储了有关特定类型的信息

'只能将 RTTI 用于包含虚函数的类层次结构'，原因在于只有对于这种类层次结构, 才应该将派生对象的地址赋给基类指针。


// !! dynamic_cast 运算符

dynamic_cast 运算符是最常用的 RTTI 组件，它不能回答"指针指向的是哪类对象"这样的问题，但能够回答"是否可以安全地将对象的地址赋给特定类型的指针"这样的问题。
我们来看一看这意味着什么。假设有下面这样的类层次结构:

class Grand{...}// has virtual methods
class Superb: public Grand{...}
class Magnificent : public Superb{...}

接下来假设有下面的指针:

Grand *pg = new Grand();
Grand *ps = new Superb();
Grand *pm = new Magnificent();

最后，对于下面的类型转换:

Magnificent *p1 = (Magnificent*)pm;// #1
Magnificent *p2 = (Magnunctions*)pg;// #2
Superb *p3 = (Magnunctions*)pm;// #3

哪些是安全的？

根据类声明，它们可能全都是安全的，但只有那些指针类型与对象的类型(或对象的直接或间接基类的类型)相同的类型转换才一定是安全的。

如，类型转换 #1 就是安全的，因为它将 Magificent 类型的指针指向类型为 Magnificent 的对象。类型转换 #2 就是不安全的，因为它将基数对象(Grand)的地址赋给派生
类(Magnificent)指针。因此，程序将期望基类对象有派生类的特征，而通常这是不可能的。然而，类型转换 #3 是安全的，因为它将派生对象的地址赋给基类指针。即公有派生确
保 Magnificent 对象同时也是一个 Superb 对象（直接基类）和一个 Grand 对象（间接基类）。因此，将它的地址赋给这 3 种类型的指针都是安全的。虚函数确保了将这3
种指针中的任何一种指向 Magnificent 对象时，都将调用 Magnificent 方法。


然而，先来看一下 dynamic_cast 的语法。该运算符的用法如下，其中 pg 指向一个对象:

Superb *pm = dynamic_cast<Superb *>(pg);


指针 pg 的类型是否可被安全地转换为 Superb *？ 如果可以，运算符将返回对象的地址，否则返回一个空指针。

#include <iostream>
#include <ctime>
#include <cstdlib>

using std::cout;
class Grand
{
    private:
        int hold;
    public:
        Grand(int h = 0) : hold(h){}
        virtual void speak() const { cout << "I am good grand class!\n"}
        virtual int Value() const { return hold; }
};

class Superb: public Grand
{
    public:
        Superb(int h = 0):Grand(h){}
        void speak() const { cout << "I am good superb class!\n"}
        virtual void say() const { cout << "I hold the superb value of " << Value() <<"!\n"; }
};

class Magnificent: public Superb
{
    private:
        char ch;
    public:
        Magnificent(int h = 0, char c = 'A'):Superb(h),ch(c){}
        void speak() const { cout << "I am good Magnificent class!\n";}
        void say() const { cout << "I hold the character " << ch << "and an integer " << Value() << "!\n";}
};


Grand * GetOne();

int main()
{
    std::srand(std::time(0));
    Grand *pg;
    Superb *ps;
    for(int i = 0; i < 5; i++)
    {
        pg = GetOne();
        pg->speak();
        if(ps = dynamic_cast<Superb*>(pg))
        {
            ps->say();
        }
    }
    return 0;
}

Grand * GetOne()
{
    Grand *p;
    switch(std::rand() % 3)
    {
        case 0: p = new Grand(std::rand() % 100);
            break;
        case 1: p = new Superb(std::rand() % 100);
            break;
        case 2: p = new Magnificent(std::rand() % 100, 'A' + std::rand() % 26);
            break;
    }
    return p;
}


 » g++ --std=c++11 rtti1.cpp
--------------------------------------------------------------------------------
 » ./a.out

I am good grand class!
I am good grand class!
I am good Magnificent class!
I hold the character Sand an integer 0!
I am good superb class!
I hold the superb value of 76!
I am good Magnificent class!
I hold the character Wand an integer 45!


// !! typeid 运算符和 type_info 类

typeid 运算符使得能够确定两个对象是否为同种类型, 可以接受两种参数:

1. 类名
2. 结果为对象的表达式

typeid 运算符返回一个对 type_info 对象的引用，其中，type_info 是在头文件 typeinfo 中定义的一个类。type_info 类重载了 == 和 != 运算符，以便可以使
用这些运算符来对类型进行比较。

例如，如果 pg 指向的是一个 Magnificent 对象，则下述表达式的结果为 bool 值 true，否则为 false:

typeid(Magnificent) == typeid(pg);

如果 pg 是一个空指针，程序将引发 bad_typeid 异常。该异常类型是从 exception 类派生而来的，是在头文件 typeinfo 中声明的。

type_info类的实现随厂商而异，但包含一个 name() 成员，该函数返回一个随实现而异的字符串: 通常（但并非一定）是类的名称。例如，下面的语句显示指针pg指向的对象所
属的类定义的字符串:

cout << "Now processing type is" << typeid(pg).name() << endl;


// !! 误用 RTTI 的例子

