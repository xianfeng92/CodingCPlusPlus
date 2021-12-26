
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

第二个声明既与构造函数#1（没有参数）匹配，也与构造函数 #2（使用默认参数 0）匹配。这将导致编译器发出一条错误消息。

// !! 复制构造函数

'复制构造函数用于将一个对象复制到新创建的对象中'。也就是说，它用于初始化过程中(包括按值传递参数)，而不是常规的赋值过程中。

类的复制构造函数原型通常如下:

Class_Name(const Class_Name &);

它接受一个指向类对象的常量引用作为参数。


例如，String 类的复制构造函数的原型如下:

StringBad(const StringBad &);

对于复制构造函数，需要知道两点: 何时调用和有何功能。

'何时调用复制构造函数'

新建一个对象并将其初始化为同类现有对象时, 复制构造函数都将被调用。

这在很多情况下都可能发生，'最常见的情况是将新对象显式地初始化为现有的对象'。例如，假设 motto 是一个 StringBad 对象，则下面 4 种声明都将调用复制
构造函数:

StringBad omino(motto);// call StringBad(const StringBad &)
StringBad metoo = motto;// call StringBad(const StringBad &)
StringBad also = StringBad(motto);// call StringBad(const StringBad&)
StringBad * pstring = new StringBad(motto);// call StringBad(const StringBad &)

其中中间的 2 种声明可能会使用复制构造函数直接创建 metoo 和 also ，也可能使用复制构造函数生成一个临时对象，然后将临时对象的内容赋给 metoo 和 also，
这取决于具体的实现。最后一种声明使用 motto 初始化一个匿名对象，并将新对象的地址赋给 pstring 指针。

每当程序生成了对象副本时，编译器都将使用复制构造函数。'具体地说，当函数按值传递对象或函数返回对象时，都将使用复制构造函数'。

由于按值传递对象将调用复制构造函数，因此应该按引用传递对象。这样可以节省调用构造函数的时间以及存储新对象的空间。

// !!默认的复制构造函数的功能

'默认的复制构造函数逐个复制非静态成员(成员复制也称为浅复制)，复制的是成员的值'。

下述语句：

StringBad sailor = sports;

与下面的代码等效(只是由于私有成员是无法访问的，因此这些代码不能通过编译):

StringBad sailor;
sailor.str = sports.str;
sailor.len = sports.len;

'如果成员本身就是类对象，则将使用这个类的复制构造函数来复制成员对象'。静态函数(如 num_strings) 不受影响，因为它们属于整个类，而不是各个对象。


// !! 回到 Stringbad：复制构造函数的哪里出了问题

解决办法是提供一个对计数进行更新的显式复制构造函数:

StringBad::StringBad(const StringBad &)
{
    ++num_strings;
    ...
}

提示:

如果类中包含这样的静态数据成员, 即其值将在新对象被创建时发生变化，则应该提供一个显式复制构造函数来处理计数问题。

1.定义一个显式复制构造函数以解决问题

'解决类设计中这种问题的方法是进行深度复制(deep copy)'。也就是说，复制构造函数应当复制字符串并将副本的地址赋给 str 成员，而不仅仅是复制字符串地址。

StringBad::StringBad(const StringBad &st)
{
    ++num_strings;
    len = st.len;
    str = new char[len+1];
    std::strcpy(str,st.str);// copy string to new location
    cout << num_strings << ": " << str << " object created\n";
}

必须定义复制构造函数的原因在于: '一些类成员是使用 new 初始化的、指向数据的指针，而不是数据本身'。

警告：

'如果类中包含了使用 new 初始化的指针成员，应当定义一个复制构造函数，以复制指向的数据，而不是指针，这被称为深度复制'。复制的另一种形式(成员复制或浅复制)
只是复制指针值。浅复制仅浅浅地复制指针信息，而不会深入“挖掘”以复制指针引用的结构。


// !! Stringbad 的其他问题: 赋值运算符

ANSI C 允许结构赋值，而 'C++ 允许类对象赋值, 这是通过自动为类重载赋值运算符实现的'。这种运算符的原型如下:

Class_Name & Class_Name::operator=(const Class_Name &);

它接受并返回一个指向类对象的引用。例如，StringBad 类的赋值运算符的原型如下:

StringBad & StringBad::operator=(const StringBad &);

1．赋值运算符的功能以及何时使用它

'将已有的对象赋给另一个对象时，将使用重载的赋值运算符':

StringBad headline1("helloworld");
...
StringBad knot;
knot = headline1;// assign operator invokes

初始化对象时, 并不一定会使用赋值运算符:

StringBad metto = knot;// use copy constructor, possible assign, too

这里，metoo 是一个新创建的对象，被初始化为 knot 的值，因此使用复制构造函数。

然而，正如前面指出的，实现时也可能分两步来处理这条语句: '使用复制构造函数创建一个临时对象，然后通过赋值将临时对象的值复制到新对象中'。这就是说，初始化总是会
调用复制构造函数，而使用 = 运算符时也可能调用赋值运算符。

与复制构造函数相似，赋值运算符的隐式实现也对成员进行逐个复制。如果成员本身就是类对象，则程序将使用为这个类定义的赋值运算符来复制该成员，但静态数据成员不受
影响。

2. 赋值的问题出在哪里

将 headline1 赋给 knot：

knot = headline1;

3. 解决赋值的问题

    '对于由于默认赋值运算符不合适而导致的问题，解决办法是提供赋值运算符(进行深度复制)定义'。其实现与复制构造函数相似，但也有一些差别。

    1.由于目标对象可能引用了以前分配的数据，所以函数应使用 delete[] 来释放这些数据

    2. 函数应当避免将对象赋给自身；否则，给对象重新赋值前，释放内存操作可能删除对象的内容

    3. 函数返回一个指向调用对象的引用

通过返回一个对象，函数可以像常规赋值操作那样，连续进行赋值，即如果 S0、S1 和 S2 都是 StringBad 对象，则可以编写这样的代码:

S0 = S1 = S2;
S0.operator=(S1.operator-(S2));


下面的代码说明了如何为 StringBad 类编写赋值运算符：

StringBad & StringBad::operator=(const StringBad & st)
{
    if(this == &st) return;
    delete[] str;
    len = st.len;
    str = new char[len+1];
    std::strcpy(str,st.str);
    return *this;
}

代码首先检查自我复制，这是通过查看赋值运算符右边的地址(&st)是否与接收对象（this）的地址相同来完成的。如果相同，程序将返回 *this，然后结束。

如果地址不同，函数将释放 str 指向的内存，这是因为稍后将把一个新字符串的地址赋给 str。如果不首先使用 delete 运算符，则上述字符串将保留在内存中。
由于程序中不再包含指向该字符串的指针，因此这些内存被浪费掉。

接下来的操作与复制构造函数相似，'即为新字符串分配足够的内存空间，然后将赋值运算符右边的对象中的字符串复制到新的内存单元中'。


// !! 改进后的新 String 类

有了更丰富的知识后，可以对 StringBad 类进行修订，将它重命名为 String 了。首先，添加前面介绍过的复制构造函数和赋值运算符，使类能够正确管理类对象使用的内存。
其次，由于您已经知道对象何时被创建和释放，因此可以让类构造函数和析构函数保持沉默，不再在每次被调用时都显示消息。另外，也不用再监视构造函数的工作情况，因此可以
简化默认构造函数，使之创建一个空字符串，而不是“C++”。


接下来，可以在类中添加一些新功能。'string 类应该包含标准字符串函数库 cstring 的所有功能，才会比较有用'，但这里只添加足以说明其工作原理的功能(string 
类只是一个用作说明的示例，而 C++ 标准 string 类的内容丰富得多）。

具体地说，将添加以下方法：

//返回被存储的字符串的长度
int length() const { return len;}

// 接下来的 3 个友元函数能够对字符串进行比较
friend bool operator>(const string& lhs, const string& rhs);
friend bool operator<(const string& lhs, const string& rhs);
friend bool operator==(const string& lhs, const string& rhs);

// operator>>()函数提供了简单的输入功能
friend std::istream& operator>>(std::istream&, string&);

// 两个 operator 函数提供了以数组表示法访问字符串中各个字符的功能
char &operator[](int i);
const char & operator[](int i) const;

// 静态类方法 Howmany() 将补充静态类数据成员 num_string
static int Howmany() const;



1. 修订后的默认构造函数

请注意新的默认构造函数，它与下面类似：

String::String()
{
    len = 0;
    str = new char[1];
    str[0] = '\0';
}

您可能会问，为什么代码为：

str = new char[1];

而不是：

str = new char;

'上面两种方式分配的内存量相同，区别在于前者与类析构函数兼容，而后者不兼容'。

析构函数中包含如下代码：

delete[] str;

delete[] 与使用 new[] 初始化的指针和空指针都兼容。因此对于下述代码:

str = new char[1];
str[0] = '\0';

可修改为：

str = 0;// set str to the null pointer

对于以其他方式初始化的指针，使用 delete [] 时，结果将是不确定的:

char words[15] = "bad idea";
char *p1 = words;
char *p2 = new char;
char *p3;

delete[] p1;// undefined
delete[] p2;// undefined
delete[] p3;// undefined


C++11 空指针

'在C++98 中，字面值0有两个含义:可以表示数字值零，也可以表示空指针，这使得阅读程序的人和编译器难以区分'。有些程序员使用（void *） 0 来标识空指针(空指针本身的
内部表示可能不是零)，还有些程序员使用 NULL，这是一个表示空指针的 C 语言宏。

C++11 供了更好的解决方案: 引入新关键字 nullptr，用于表示空指针。您仍可像以前一样使用 0——否则大量现有的代码将非法，但建议您使用 nullptr：

str = nullptr;


2. 比较成员函数

在 String 类中，执行比较操作的方法有 3 个。如果按字母顺序(更准确地说，按照机器排序序列)，第一个字符串在第二个字符串之前，则 Operator<() 函数返回 true。
要实现字符串比较函数，最简单的方法是使用标准的 strcmp() 函数，如果依照字母顺序，第一个参数位于第二个参数之前，则该函数返回一个负值; 如果两个字符串相同，则返回 
0; 如果第一个参数位于第二个参数之后，则返回一个正值。因此，可以这样使用 strcmp()：

bool operator<(const String &st1, const String &st2)
{
    if(std::strcmp(st1.str,st2.str))
    {
        return true;
    }
    return false;
}

因为内置的 < 运算符返回的是一个布尔值，所以可以将代码进一步简化为：

bool operator<(const String &st1, const String &st2)
{
    return (std::strcmp(st1.str,st2.str) < 0);
}


同样，可以按照下面的方式来编写另外两个比较函数:

bool operator>(const String &st1, const String &st2)
{
    return (st2 < st1);
}

bool operator==(const String &st1, const String &st2)
{
    return (std::strcmp(st1.str,st2.str) == 0);
}

将比较函数作为友元，有助于将 String 对象与常规的 C 字符串进行比较。例如，假设 answer 是 String 对象，则下面的代码：

if("love" == answer)

将被转换为:

if(operator==("love",answer))

然后，编译器将使用某个构造函数将代码转换为：

if(operator==(String("love"), answer))

这与原型是相匹配的。


2. 使用中括号表示法访问字符

对于标准C-风格字符串来说，可以使用中括号来访问其中的字符:

char city[30] = "shanghai";
cout << city[1] << endl;


在 C++ 中, 两个中括号组成一个运算符——中括号运算符，可以使用方法 operator 来重载该运算符。通常，二元 C++ 运算符（带两个操作数）位于两个操作数之间，例如 
2 + 5。但对于中括号运算符，一个操作数位于第一个中括号的前面, 另一个操作数位于两个中括号之间。因此，在表达式 city[0] 中，city是第一个操作数，[] 是运算符，
0 是第二个操作数。

假设 opera 是一个 String 对象:

String opera = "NIO, to the moon";

则对于表达式 opera[4]，C++ 将查找名称和特征标与此相同的方法：

String::operator[](int i);

'如果找到匹配的原型，编译器将使用下面的函数调用来替代表达式 opera[4]':

opera.operator[](4);

opera 对象调用该方法，数组下标 4 成为该函数的参数。

下面是该方法的简单实现：

char & String::operator[](int i)
{
    return str[i];
}

有了上述定义后，语句：

cout << opera[4];

将被转换为：

cout << opera.operator[](4);

将返回类型声明为 char &，便可以给特定元素赋值。例如，可以编写这样的代码：

String means = "helloworld";
means[0] = 'r';

第二条语句将被转换为一个重载运算符函数调用:

means.operator[](0) = 'r';

这里将 r 赋给方法的返回值，而函数返回的是指向 means.str[0] 的引用，因此上述代码等同于下面的代码：

means.str[0] = 'r';

假设有下面的常量对象：

const String answer = "helloworld";

如果只有上述 operator 定义，则下面的代码将出错：

cout << answer[1];

原因是 answer 是常量，而上述方法无法确保不修改数据(实际上，有时该方法的工作就是修改数据，因此无法确保不修改数据)。


'在重载时，C++ 将区分常量和非常量函数的特征标，因此可以提供另一个仅供 const String 对象使用的 operator 版本':

const char & String::operator[](int i) const
{
    return str[i];
}

有了上述定义后，就可以读/写常规 String 对象了；而对于 const String 对象，则只能读取其数据。


3. 静态类成员函数

可以将成员函数声明为静态的(函数声明必须包含关键字 static，但如果函数定义是独立的，则其中不能包含关键字 static），这样做有两个重要的后果。

    1. 首先，不能通过对象调用静态成员函数；实际上，静态成员函数甚至不能使用 this 指针。如果静态成员函数是在公有部分声明的，则可以使用类名和作用
       域解析运算符来调用它。。例如，可以给 String 类添加一个名为 HowMany() 的静态成员函数，方法是在类声明中添加如下原型/定义：

       static HowMany()
       {
           return num_strings;
       }

       调用它的方式如下：

       String::HowMany();

       其次，由于静态成员函数不与特定的对象相关联，因此只能使用静态数据成员。例如，静态方法 HowMany() 可以访问静态成员 num_string，但不能访问 str 和 
       len。


4. 进一步重载赋值运算符

介绍针对 String 类的程序清单之前，先来考虑另一个问题。假设要将常规字符串复制到 String 对象中。例如，假设使用 getline() 读取了一个字符串，并要将这个字符串
放置到 String 对象中，前面定义的类方法让您能够这样编写代码:

String name;
char temp[40];
cin.getline(temp,40);
name = temp;

'但如果经常需要这样做，这将不是一种理想的解决方案'。为解释其原因，先来回顾一下最后一条语句是怎样工作的。

1. 程序使用构造函数 String（const char *）来创建一个临时 String 对象，其中包含 temp 中的字符串副本(只有一个参数的构造函数被用作转换函数)。

2. 使用 String & String::operator=（const String &） 函数将临时对象中的信息复制到 name 对象中

3. 程序调用析构函数 ~String() 删除临时对象


'为提高处理效率，最简单的方法是重载赋值运算符，使之能够直接使用常规字符串，这样就不用创建和删除临时对象了'。下面是一种可能的实现：

String & String::operator=(const char *s)
{
    delete []str;
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s););
    return *this;
}

一般说来，必须释放 str 指向的内存，并为新字符串分配足够的内存。

sayings1.cpp，该程序允许输入几个字符串。程序首先提示用户输入，然后将用户输入的字符串存储到 String 对象中，并显示它们，最后指出哪个字符串最短、哪个字符串
按字母顺序排在最前面。


// !!在构造函数中使用 new 时应注意的事项

至此，您知道使用 new 初始化对象的指针成员时必须特别小心。具体地说，应当这样做:

1. 如果在构造函数中使用 new 来初始化指针成员，则应在析构函数中使用 delete

2. 