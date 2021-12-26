
// !! 类和动态内存分配

通常，最好是在程序运行时(而不是编译时)确定诸如使用多少内存等问题。对于在对象中保存姓名来说，通常的 C++ 方法是，在类构造函数中使用 new 运算符在程序运
行时分配所需的内存。为此，通常的方法是使用 string 类，它将为您处理内存管理细节。


// !!动态内存和类

您希望下个月的早餐、午餐和晚餐吃些什么？ 在第三天的晚餐喝多少盎司的牛奶？ 在第 15 天的早餐中需要在谷类食品添加多少葡萄干？ '如果您与大多数人一样，就会等到
进餐时再做决定'。

C++ 在分配内存时采取的部分策略与此相同, 让程序在运行时决定内存分配，而不是在编译时决定。'这样可根据程序的需要，而不是根据一系列严格的存储类型规则来使用内存'。
C++ 使用 new 和 delete 运算符来动态控制内存。遗憾的是，在类中使用这些运算符将导致许多新的编程问题。在这种情况下，析构函数将是必不可少的，而不再是可有可无
的。有时候，还必须重载赋值运算符，以保证程序正常运行。


// !! 复习示例和静态类成员

我们已经有一段时间没有使用 new 和 delete 了，所以这里使用一个小程序来复习它们。这个程序使用了一个新的存储类型:静态类成员。首先设计一个 StringBad 类，然
后设计一个功能稍强的 String 类('提供这种友好的接口涉及大量的编程技术')。

StringBad 和 String 类对象将包含一个字符串指针和一个表示字符串长度的值。这里使用 StringBad 和 String 类，主要是为了深入了解 new、delete 和静态类成员的
工作原理。因此，构造函数和析构函数调用时将显示一些消息，以便您能够按照提示来完成操作。另外，将省略一些有用的成员和友元函数，如重载的 ++ 和 >> 运算符以及转换函
数，以简化类接口, strngbad.h 列出了这个类的声明。

'为什么将它命名为 StringBad 呢' ？

这是为了表示提醒，StringBad 是一个还没有开发好的示例。'这是使用动态内存分配来开发类的第一步，它正确地完成了一些显而易见的工作'，例如，它在构造函数和析构函数中
正确地使用了 new 和 delete。它其实不会执行有害的操作，'但省略了一些有益的功能，这些功能是必需的，但却不是显而易见的'。通过说明这个类存在的问题，有助于在稍后将
它转换为一个功能更强的 String 类时，理解和牢记所做的一些并不明显的修改。

#ifndef D4E611A8_CDD4_4BD0_BF66_0CCC4ECA3598
#define D4E611A8_CDD4_4BD0_BF66_0CCC4ECA3598

class StringBad
{
private:
    char *str;// pointer to string
    int len;
    static int num_strings;// number of object
public:
    StringBad();
    StringBad(const char * str);
    ~StringBad();
    friend ostream & operator<<(ostream & os, const StringBad & st);
};

#endif /* D4E611A8_CDD4_4BD0_BF66_0CCC4ECA3598 */

对这个声明，需要注意的有两点。首先，它使用 char 指针(而不是 char 数组)来表示姓名。'这意味着类声明没有为字符串本身分配存储空间，而是在构造函数中使用 new 
来为字符串分配空间'。这避免了在类声明中预先定义字符串的长度。

将 num_strings 成员声明为静态存储类。'静态类成员有一个特点：无论创建了多少对象，程序都只创建一个静态类变量副本'。也就是说，类的所有对象共享同一个静态
成员，就像家中的电话可供全体家庭成员共享一样。。假设创建了 10 个 StringBad 对象，将有 10 个 str 成员和 10 个 len 成员，但只有一个共享的 num_strings 
成员。

#include <iostream>
#include "stringbad.h"

using std::cout;

// init static class member
int stringbad::num_strings = 0;

//class method
stringbad::stringbad(const char * s)
{
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    ++num_strings;
    cout << num_strings << ": " << str << "object creat";
}

stringbad::stringbad()
{
    len = 4;
    str = new char[len];
    std::strcpy(str,"C++");
    ++num_strings;
    cout << num_strings << ": " << str << "object creat";
}


stringbad::~stringbad()
{
    cout << str << " object destroy";
    --num_strings;
    cout <<num_strings << " left";
    delete[] str;
}


ostream & stringbad::operator<<(ostream &os, const StringBad & st)
{
    os << st.str;
    return os;
}

首先，请注意中的下面一条语句：

int stringbad::num_strings = 0;

这条语句将静态成员 num_strings 的值初始化为零。'请注意，不能在类声明中初始化静态成员变量，这是因为声明描述了如何分配内存，但并不分配内存'。

您可以使用这种格式来创建对象，从而分配和初始化内存。对于静态类成员，可以在类声明之外使用单独的语句来进行初始化，'这是因为静态类成员是单独存储的，而不是对象
的组成部分'。请注意，初始化语句指出了类型，并使用了作用域运算符，但没有使用关键字 static。

'初始化是在方法文件中, 而不是在类声明文件中进行的'，这是因为类声明位于头文件中，程序可能将头文件包括在其他几个文件中。如果在头文件中进行初始化，将出现多个
初始化语句副本，从而引发错误。


现在来看程序的第一个构造函数，'它使用一个常规 C 字符串来初始化 String 对象':

stringbad::stringbad(const char * s)
{
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    ++num_strings;
    cout << num_strings << ": " << str << "object creat";
}

'类成员 str 是一个指针，因此构造函数必须提供内存来存储字符串'。初始化对象时，可以给构造函数传递一个字符串指针:

stringbad bosd("Nio");

'构造函数必须分配足够的内存来存储字符串，然后将字符串复制到内存中'。

下面介绍其中的每一个步骤:

1. 首先，使用 strlen() 函数计算字符串的长度，并对 len 成员进行初始化

2. 使用 new 分配足够的空间来保存字符串，然后将新内存的地址赋给 str 成员(strlen() 返回字符串长度，但不包括末尾的空字符'\0'，因此构造函数将 len 加 1)

3. 构造函数使用 strcpy() 将传递的字符串复制到新的内存中，并更新对象计数

4. 最后，构造函数显示当前的对象数目和当前对象中存储的字符串，以助于掌握程序运行情况

'要理解这种方法，必须知道字符串并不保存在对象中'。'字符串单独保存在堆内存中，对象仅保存了指出到哪里去查找字符串的信息'。

不能这样做：

str = s;// not way to go

这只保存了地址，而没有创建字符串副本。


默认构造函数与此相似，但它提供了一个默认字符串: “C++”。

'析构函数中包含了示例中对处理类来说最重要的东西':

stringbad::~stringbad()
{
    cout << str << " object destroy";
    --num_strings;
    cout <<num_strings << " left";
    delete[] str;
}

该析构函数首先指出自己何时被调用。这部分包含了丰富的信息，但并不是必不可少的。然而，delete 语句却是至关重要的。str 成员指向 new 分配的内存。

'当 StringBad 对象过期时，str 指针也将过期。但 str 指向的内存仍被分配，除非使用 delete 将其释放'。'删除对象可以释放对象本身占用的内存，但并不能自动释放
属于对象成员的指针指向的内存'。因此，必须使用析构函数。在析构函数中使用 delete 语句可确保对象过期时，由构造函数使用 new 分配的内存被释放。

vegnews.cpp 是从处于开发阶段的 Daily Vegetable 程序中摘录出来的，演示了 StringBad 的构造函数和析构函数何时运行及如何运行。该程序将对象声明放在一个内部
代码块中，因为析构函数将在定义对象的代码块执行完毕时调用。如果不这样做，析构函数将在 main() 函数执行完毕时调用，导致您无法在执行窗口关闭前看到析构函数显
示的消息。


#include<iostream>
#include "stringbad.h"
using std::cout;


void callme1(StringBad &);// pass by reference
void callme2(StringBad);// pass by value

int main()
{
    using std::endl;
    {
        cout << "starting a inner block:\n";
        StringBad headline1("Celery Stalks at Midnight");
        StringBad headline2("Lettuce Prey");
        StringBad sports("Spinach Leaves bowl for Dollar");
        
        cout << "headline1: " << headline1 << endl;
        cout << "headline2: " << headline2 << endl;
        cout << "sports: " <<sports << endl;

        callme1(headline1);
        cout << "headline1: " << headline1 << endl;
        callme2(headline2);
        cout << "headline2: " << headline2 << endl;

        cout << "Initialize one object to another:\n";
        StringBad sailor = sports;

        cout << "Assign one object to another:\n";
        StringBad knot;
        knot = headline1;
        cout << "knot " << knot << endl;
        cout << "Exit the block:\n";
    }
    cout << "End of main()\n";
    return 0;
}

void callme1(StringBad &rsb)
{
    cout << "string pass by reference:\n";
    cout << rsb << '\n';
}

void callme2(StringBad rsb)
{
    cout << "string pass by value:\n";
    cout << rsb << '\n';
}


 » g++ --std=c++11 stringbad.cpp vegnews.cpp
--------------------------------------------------------------------------------
 » ./a.out

starting a inner block:
1: Celery Stalks at Midnightobject creat2: Lettuce Preyobject creat3: Spinach Leaves bowl for Dollarobject creatheadline1: Celery Stalks at Midnight
headline2: Lettuce Prey
sports: Spinach Leaves bowl for Dollar
string pass by reference:
Celery Stalks at Midnight
headline1: Celery Stalks at Midnight
string pass by value:
Lettuce Prey
Lettuce Prey object destroy2 leftheadline2: 
Initialize one object to another:
Assign one object to another:
3: C++object creatknot Celery Stalks at Midnight
Exit the block:
free(): double free detected in tcache 2
[1]    845844 abort (core dumped)  ./a.out

输出中出现的各种非标准字符随系统而异，这些字符表明，StringBad 类名副其实（是一个糟糕的类）。另一种迹象是对象计数为负。在使用较新的编译器和操作系统的机器上运
行时，该程序通常会在显示有关还有 −1 个对象的信息之前中断，而有些这样的机器将报告通用保护错误（GPF）。GPF 表明程序试图访问禁止它访问的内存单元，这是另一种糟糕
的信号。

请看下面的代码：

stringbad sailor = sports;

这使用的是哪个构造函数呢？ 

不是默认构造函数，也不是参数为 const char * 的构造函数。记住，这种形式的初始化等效于下面的语句：

stringbad sailor = stringbad(sports);

'当您使用一个对象来初始化另一个对象时，编译器将自动生成上述构造函数(称为复制构造函数，因为它创建对象的一个副本)'。自动生成的构造函数不知道需要更新静态变量 
num_string，因此会将计数方案搞乱。

// !! 特殊成员函数


StringBad 类的问题是由特殊成员函数引起的。这些成员函数是自动定义的，就 StringBad 而言，这些函数的行为与类设计不符。具体地说，C++ 自动提供了下面这些
成员函数:

1. 默认构造函数，如果没有定义构造函数

2. 默认析构函数，如果没有定义

3. 复制构造函数，如果没有定义

4. 赋值运算符，如果没有定义

5. 地址运算符，如果没有定义

更准确地说，编译器将生成上述最后三个函数的定义---如果程序使用对象的方式要求这样做。例如，如果您将一个对象赋给另一个对象，编译器将提供赋值运算符的定义。

结果表明，StringBad 类中的问题是由'隐式复制构造函数和隐式赋值运算符引起的'。

隐式地址运算符返回调用对象的地址(即 this 指针的值)。默认析构函数不执行任何操作，因此这里也不讨论，但需要指出的是，这个类已经提供默认构造函数。至于其他
成员函数还需要进一步讨论。

C++11 提供了另外两个特殊成员函数：移动构造函数 (move constructor) 和移动赋值运算符 (move assignment operator)


// !! 默认构造函数

'如果没有提供任何构造函数，C++ 将创建默认构造函数'。例如，假如定义了一个 Klunk 类，但没有提供任何构造函数，则编译器将提供下述默认构造函数:

Klunk::Klunk()
{

}

也就是说，编译器将提供一个不接受任何参数，也不执行任何操作的构造函数(默认的默认构造函数)，这是因为创建对象时总是会调用构造函数:

Klunk lunk;// invokes a default constructor

'默认构造函数使 Lunk 类似于一个常规的自动变量，也就是说，它的值在初始化时是未知的'。

如果定义了构造函数，C++ 将不会定义默认构造函数。如果希望在创建对象时不显式地对它进行初始化，则必须显式地定义默认构造函数。这种构造函数没有任何参数，但
可以使用它来设置特定的值:

Klunk::Klunk()// explicit default constructor
{
    klunc_c = 100;
    ...
}

'带参数的构造函数也可以是默认构造函数，只要所有参数都有默认值'。例如，Klunk 类可以包含下述内联构造函数：


Klunk::Klunk(ing n = 0)
{
    klunc_c = n;
    ...
}

但只能有一个默认构造函数。也就是说，不能这样做：

Klunk(){klunc_c = 0;}
Klunk(ing n = 0){klunc_c = n;}

这为何有二义性呢？ 请看下面两个声明:

Klunk kar(10);// ok
Klunk bus;// invalid

第二个声明既与构造函数#1（没有参数）匹配，也与构造函数#2（使用默认参数 0）匹配。这将导致编译器发出一条错误消息。




