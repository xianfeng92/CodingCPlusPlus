
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

然而，正如前面指出的，实现时也可能分两步来处理这条语句: '使用复制构造函数创建一个临时对象，然后通过赋值将临时对象的值复制到新对象中'。这就是说，初始化总
是会调用复制构造函数，而使用 = 运算符时也可能调用赋值运算符。

与复制构造函数相似，赋值运算符的隐式实现也对成员进行逐个复制。如果成员本身就是类对象，则程序将使用为这个类定义的赋值运算符来复制该成员，但静态数据成员不
受影响。

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

有了更丰富的知识后，可以对 StringBad 类进行修订，将它重命名为 String 了。首先，添加前面介绍过的复制构造函数和赋值运算符，使类能够正确管理类对象使用的
内存。其次，由于您已经知道对象何时被创建和释放，因此可以让类构造函数和析构函数保持沉默，不再在每次被调用时都显示消息。另外，也不用再监视构造函数的工作情况
，因此可以简化默认构造函数，使之创建一个空字符串，而不是“C++”。


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

'在C++98 中，字面值0有两个含义:可以表示数字值零，也可以表示空指针，这使得阅读程序的人和编译器难以区分'。有些程序员使用（void *） 0 来标识空指针(空指针本
身的内部表示可能不是零)，还有些程序员使用 NULL，这是一个表示空指针的 C 语言宏。

C++11 供了更好的解决方案: 引入新关键字 nullptr，用于表示空指针。您仍可像以前一样使用 0——否则大量现有的代码将非法，但建议您使用 nullptr：

str = nullptr;


2. 比较成员函数

在 String 类中，执行比较操作的方法有 3 个。如果按字母顺序(更准确地说，按照机器排序序列)，第一个字符串在第二个字符串之前，则 Operator<() 函数返回 true。
要实现字符串比较函数，最简单的方法是使用标准的 strcmp() 函数，如果依照字母顺序，第一个参数位于第二个参数之前，则该函数返回一个负值; 如果两个字符串相同，则
返回 0; 如果第一个参数位于第二个参数之后，则返回一个正值。因此，可以这样使用 strcmp()：

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


在 C++ 中, 两个中括号组成一个运算符——中括号运算符，可以使用方法 operator 来重载该运算符。通常，二元 C++ 运算符（带两个操作数）位于两个操作数之间，例
如 2 + 5。但对于中括号运算符，一个操作数位于第一个中括号的前面, 另一个操作数位于两个中括号之间。因此，在表达式 city[0] 中，city是第一个操作数，[] 是运
算符，0 是第二个操作数。

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

介绍针对 String 类的程序清单之前，先来考虑另一个问题。假设要将常规字符串复制到 String 对象中。例如，假设使用 getline() 读取了一个字符串，并要将这个字符
串放置到 String 对象中，前面定义的类方法让您能够这样编写代码:

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

sayings1.cpp，该程序允许输入几个字符串。程序首先提示用户输入，然后将用户输入的字符串存储到 String 对象中，并显示它们，最后指出哪个字符串最短、哪个字符
串按字母顺序排在最前面。


// !!在构造函数中使用 new 时应注意的事项

至此，您知道使用 new 初始化对象的指针成员时必须特别小心。具体地说，应当这样做:

1. 如果在构造函数中使用 new 来初始化指针成员，则应在析构函数中使用 delete

2. new 和 delete 必须相互兼容。new 对应于 delete，new[] 对应于 delete[]

3. 如果有多个构造函数，则必须以相同的方式使用 new，要么都带中括号，要么都不带。因为只有一个析构函数，所有的构造函数都必须与它兼容。然而，可以在一个构造函数
   中使用 new 初始化指针，而在另一个构造函数中将指针初始化为空( 0或 C++11 中的 nullptr)，这是因为 delete(无论是带中括号还是不带中括号)可以用于空指针

   'NULL、0 还是 nullptr'

    以前，空指针可以用 0 或 NULL(在很多头文件中，NULL 是一个被定义为 0 的符号常量)来表示。C 程序员通常使用 NULL 而不是 0，以指出这是一个指针，就像使用‘\0’
    而不是 0 来表示空字符，以指出这是一个字符一样。然而，C++ 传统上更喜欢用简单的 0，而不是等价的 NULL。'C++11 提供了关键字 nullptr，这是一种更好的选择'。


4. 应定义一个复制构造函数，通过深度复制将一个对象初始化为另一个对象。通常，这种构造函数与下面类似

    String & String::operator=(const String & st)
    {
        if(*this == st)
        {
            return *this;
        }
        delete[] str;
        len = st.len;
        str = new char[len + 1];
        std::strcpy(str,st.str);
        return *this;
    }

    具体地说，该方法应完成这些操作: '检查自我赋值的情况，释放成员指针以前指向的内存，复制数据而不仅仅是数据的地址，并返回一个指向调用对象的引用'。


// !! 应该和不应该

下面的摘要包含了两个不正确的示例(指出什么是不应当做的)以及一个良好的构造函数示例:

String::String()
{
    str = "default string";// opps, no new[]
    len = std::strlen(str);
}

String::String(const char* s)
{
    len = std::strlen(s);
    str = new char;// opps, no []
    std::strcpy(str, s);// opps, no room
}

String::String(const String & st)
{
    len = st.len;
    str = new char[len + 1];// good, allocate space
    std::strcpy(str,st.str);// good, copy value
}


1. 第一个构造函数没有使用 new 来初始化 str。对默认对象调用析构函数时，析构函数使用 delete 来释放s tr。对不是使用 new 初始化的指针使用 delete 时，
结果将是不确定的，并可能是有害的。

    可将该构造函数修改为下面的任何一种形式：

    String::String()
    {
        len = 0;
        str = new char[1];
        str[0] = '\0';
    }


    String::String()
    {
        len = 0;
        str = 0;// or with c++ 11 nullptr
    }


    String::String()
    {
        static const char * s = "C++";
        len = std::strlen(s);
        str = new char[len + 1];
        std::strcpy(str, s);
    }


2. 摘录中的第二个构造函数使用了 new，但分配的内存量不正确。因此，new 返回的内存块只能保存一个字符。试图将过长的字符串复制到该内存单元中，将导致内存问题。
   另外，这里使用的 new 不带中括号，这与另一个构造函数的正确格式不一致。


3. 第三个构造函数是正确的。

最后，下面的析构函数无法与前面的构造函数正常地协同工作:

String::~String()
{
    delete str;// opps, should delete [] str
}

该析构函数未能正确地使用 delete。由于构造函数创建的是一个字符数组，因此析构函数应该删除一个数组。


// !! 包含类成员的类的逐成员复制

假设类成员的类型为 String 类或标准 string 类:

class Magazine
{
    private:
        String title;
        String publisher;
}


String 和 string 都使用动态内存分配，这是否意味着需要为 Magazine 类编写复制构造函数和赋值运算符？ 

不，至少对这个类本身来说不需要。'默认的逐成员复制和赋值行为有一定的智能'。如果您将一个 Magazine 对象复制或赋值给另一个 Magazine 对象，逐成员复制将使用成员
类型定义的复制构造函数和赋值运算符。也就是说，复制成员 title 时，将使用 String 的复制构造函数，而将成员 title 赋给另一个 Magazine 对象时，将使用 String 
的赋值运算符，依此类推。然而，如果M agazine 类因其他成员需要定义复制构造函数和赋值运算符，情况将更复杂；在这种情况下，这些函数必须显式地调用 String 和 
string 的复制构造函数和赋值运算符。

// !!有关返回对象的说明

当成员函数或独立的函数返回对象时, 有几种返回方式可供选择。可以返回指向对象的引用、指向对象的 const 引用或 const 对象。


1. 返回指向 const 对象的引用

使用 const 引用的常见原因是旨在提高效率，但对于何时可以采用这种方式存在一些限制。如果函数返回(通过调用对象的方法或将对象作为参数)传递给它的对象，可以通过返回引
用来提高其效率。


例如，假设要编写函数 Max()，它返回两个 Vector 对象中较大的一个。该函数将以下面的方式被使用:

Vector force1(50,60);
Vector force2(10,70);

max = Max(force1,force2);

下面两种实现都是可行的：

//version1
Vector Max(const Vector & v1, const Vector & v2)
{
    if(v1.magval() < v2.magval())
    {
        return v2;
    }
    return v1;
}

//version2
const Vector & Max(const Vector & v1, const Vector & v2)
{
    if(v1.magval() < v2.magval())
    {
        return v2;
    }
    return v1;
}

这里有三点需要说明。首先，'返回对象将调用复制构造函数，而返回引用不会'。因此，第二个版本所做的工作更少，效率更高。其次，引用指向的对象应该在调用函数执行时存在
。在这个例子中，引用指向 force1 或 force2，它们都是在调用函数中定义的，因此满足这种条件。第三，v1 和 v2 都被声明为 const 引用，因此返回类型必须为 const，
这样才匹配。


2. 返回指向非 const 对象的引用

两种常见的返回非 const 对象情形是:'重载赋值运算符以及重载与 cout 一起使用的 << 运算符'。前者这样做旨在提高效率，而后者必须这样做。

operator=() 的返回值用于连续赋值:

String s1("good");
String s2,s3;
s3 = s2= s1;

在上述代码中，s2.operator=() 的返回值被赋给 s3。为此，返回 String 对象或 String 对象的引用都是可行的。


Operator<<() 的返回值用于串接输出：

String s1("Happy");
cout << s1 << "world";

在上述代码中，operator<<（cout, s1） 的返回值成为一个用于显示字符串 “Happy” 的对象。返回类型必须是 ostream &，而不能仅仅是 ostream。如果使用返回类
型 ostream，将要求调用 ostream 类的复制构造函数，而 ostream 没有公有的复制构造函数。幸运的是，返回一个指向 cout 的引用不会带来任何问题，因为 cout 
已经在调用函数的作用域内。


3. 返回对象

'如果被返回的对象是被调用函数中的局部变量，则不应按引用方式返回它，因为在被调用函数执行完毕时，局部对象将调用其析构函数'。因此，当控制权回到调用函数时，引用
指向的对象将不再存在。在这种情况下，应返回对象而不是引用。通常，'被重载的算术运算符属于这一类'。

请看下述示例，它再次使用了 Vector 类:

Vector force1(50,60);
Vector force2(10,70);
Vector net;
net = force1 + force2;

返回的不是 force1，也不是 force2，force1 和 force2 在这个过程中应该保持不变。因此，'返回值不能是指向在调用函数中已经存在的对象的引用'。相反，在 
Vector::operator+() 中计算得到的两个矢量的和被存储在一个新的临时对象中，该函数也不应返回指向该临时对象的引用，而应该返回实际的 Vector 对象，而不
是引用：

Vector Vector::operator+(const Vector & b)
{
    return Vector(x+b.x,y+b.y);
}

'在这种情况下，存在调用复制构造函数来创建被返回的对象的开销，然而这是无法避免的'。


4. 返回 const 对象

前面的 Vector::operator+() 定义有一个奇异的属性，它旨在让您能够以下面这样的方式使用它：

net = force1 + force2;

然而，这种定义也允许您这样使用它:

force1 + force2 = net;
cout << "force1 + force2 = net" << (force1 + force2 = net).magval() << endl;


这提出了三个问题。为何编写这样的语句？ 这些语句为何可行？ 这些语句有何功能？

首先，没有要编写这种语句的合理理由，但并非所有代码都是合理的。即使是程序员也会犯错。例如，为 Vector 类定义 operator==()时，您可能错误地输入这样的
代码：

if(force1 + force2 = net)
{

}

而不是：

if(force1 + force2 == net)
{

}

另外，程序员通常很有创意，这可能导致错误。

其次，这种代码之所以可行，是因为复制构造函数将创建一个临时对象来表示返回值。因此，在前面的代码中，表达式 force1 + force2 的结果为一个临时对象。在语句1中，
该临时对象被赋给 net；在语句 2和 3中， net 被赋给该临时对象。

第三，使用完临时对象后，将把它丢弃。例如，对于语句 2，程序计算 force1 和 force2 之和，将结果复制到临时返回对象中，再用 net 的内容覆盖临时对象的内容，
然后将该临时对象丢弃。原来的矢量全都保持不变。语句 3 显示临时对象的长度，然后将其删除。

如果您担心这种行为可能引发的误用和滥用，有一种简单的解决方案: 将返回类型声明为 const Vector。例如，如果 Vector::operator+() 的返回类型被声明为 
const Vector，则语句 1仍然合法，但语句 2和语句 3将是非法的。


总之，'如果方法或函数要返回局部对象，则应返回对象，而不是指向对象的引用'。在这种情况下，将使用复制构造函数来生成返回的对象。如果方法或函数要返回一个没有公
有复制构造函数的类(如 ostream 类)的对象，它必须返回一个指向这种对象的引用。最后，有些方法和函数(如重载的赋值运算符)可以返回对象，也可以返回指向对象的引用，
在这种情况下，应首选引用，因为其效率更高。


// !! 使用指向对象的指针

C++ 程序经常使用指向对象的指针，因此，这里来练习一下。sayings2.cpp 使用两个指向 String 的指针实现了这种方法。最初，shortest 指针指向数组中的第一个对象。
每当程序找到比指向的字符串更短的对象时，就把 shortest 重新设置为指向该对象。同样，first 指针跟踪按字母顺序排在最前面的字符串。这两个指针并不创建新的对象，
而只是指向已有的对象。因此，这些指针并不要求使用 new 来分配内存。

除此之外，程序 sayings2.cpp 还使用一个指针来跟踪新对象:

String *favorite = new String(sayings[choice]);

'这里指针 favorite 指向 new 创建的未被命名对象'。这种特殊的语法意味着使用对象 saying[choice] 来初始化新的 String 对象，这将调用复制构造函数，因为复制
构造函数（const String &）的参数类型与初始化值（saying [choice]）匹配。程序使用 srand( )、rand( )和 time( ) 随机选择一个值。

// !! 使用 new 初始化对象

通常，如果 Class_name 是类，value 的类型为 Type_name，则下面的语句:

Class_name *pclass = new Class_name(value);

将调用如下构造函数：

Class_name(Type_name);

这里可能还有一些琐碎的转换，例如：

Class_Name(const Type_name & );

另外，如果不存在二义性，则将发生由原型匹配导致的转换(如从 int 到 double）。

下面的初始化方式将调用默认构造函数:

Class_Name *pclass = new Class_Name;

// !! 再谈 new 和 delete

string1.h, string1.cpp 和 saying2.cpp 组成的程序在两个层次上使用了 new 和 delete。

1. 首先，它使用 new 为创建的每一个对象的名称字符串分配存储空间，这是在构造函数中进行的，因此析构函数使用 delete 来释放这些内存。这样，当对象被释放时，
   用于存储字符串内容的内存将被自动释放。

2. 使用 new 来为整个对象分配内存：
   
   String *favorite = new String(sayings[choice]);

   '这不是为要存储的字符串分配内存，而是为对象分配内存'；'即为保存字符串地址的 str 指针和 len 成员分配内存'(程序并没有给 num_string 成员分配内存，
    这是因为 num_string 成员是静态成员，它独立于对象被保存)。'创建对象将调用构造函数，后者分配用于保存字符串的内存，并将字符串的地址赋给 str。然后，当程
    序不再需要该对象时，使用 delete 删除它'。对象是单个的，因此，程序使用不带中括号的 delete。与前面介绍的相同，这将只释放用于保存 str 指针和 len 成员的
    空间，并不释放 str 指向的内存，而该任务将由析构函数来完成


在下述情况下析构函数将被调用:

1. 如果对象是动态变量，则当执行完定义该对象的程序块时，将调用该对象的析构函数

2. 如果对象是静态变量(外部、静态、静态外部或来自名称空间)，则在程序结束时将调用对象的析构函数

3. 如果对象是用 new 创建的，则仅当您显式使用 delete 删除对象时，其析构函数才会被调用


// !! 指针和对象小结

使用对象指针时，需要注意几点:

1. 使用常规表示法来声明指向对象的指针

    String *glamour;

2. 可以将指针初始化为指向已有的对象

    String *first = &sayings[0];

3. 可以使用 new 来初始化指针，这将创建一个新的对象

    String *favorite = new String(sayings[choice]);

4. 对类使用 new 将调用相应的类构造函数来初始化新创建的对象

    String *gleep = new String；// invokes default constructor
    String *glob = new String("helloworld");// invokes String(const char *str)
    String *favorite = new String(sayings[choice]);// invokes String(const String &str)

5. 可以使用 -> 运算符通过指针访问类方法

6. 可以对对象指针应用解除引用运算符 (*) 来获得对象

// !! 再谈定位 new 运算符

'定位 new 运算符让您能够在分配内存时能够指定内存位置'。placenew1.cpp 使用了定位 new 运算符和常规 new 运算符给对象分配内存，其中定义的类的构造函数和析构
函数都会显示一些信息，让用户能够了解对象的历史。

#include<iostream>
#include<string>
#include<new>

using namespace std;

const int BUF = 512;

class JustTesting
{
    private:
        string words;
        int number;
    public:
        JustTesting(const string& s = "Just Testing", int n = 0)
        {
            words = s;
            number = n;
            cout << words << " constructed\n";
        }
        ~JustTesting()
        {
            cout << words << " destroyed\n";
        }
        void show() const
        {
            cout << words << ", " << number << endl;
        }

};

int main()
{
    char *buffer = new char[BUF];// get a block of memory
    JustTesting *pc1, *pc2;

    pc1 = new(buffer) JustTesting;// place object in buffer
    pc2 = new JustTesting("heap", 20);// place object on heap

    cout << "Memory block address:\n" << "buffer: " << (void *)buffer
    << " heap: " << pc2 << endl;
    cout << "Memory contents:\n";
    cout << pc1 <<": ";
    pc1->show();
    cout << pc2 <<": ";
    pc2->show();

    JustTesting *pc3,*pc4;
    pc3 = new (buffer) JustTesting("bad idea",6);
    pc4 = new JustTesting("heap2",10);

    cout << "Memory contents :\n";
    cout << pc3 << ":";
    pc3->show();

    cout << pc4 << ": ";
    pc4->show();
    delete pc2;// free heap1
    delete pc4;// free heap2

    delete[] buffer;// free buffer
    cout << "done\n";
    return 0;
}

该程序'使用 new 运算符创建了一个 512 字节的内存缓冲区'，然后使用 new 运算符在堆中创建两个 JustTesting 对象，并试图使用定位 new 运算符在内存缓冲区中创建
两个 JustTesting 对象。最后，它使用 delete 来释放使用 new 分配的内存。

下面是该程序的输出:


 » g++ --std=c++11 placenew1.cpp
--------------------------------------------------------------------------------
» ./a.out

Just Testing constructed
heap constructed
Memory block address:
buffer: 0x5584224a6eb0 heap: 0x5584224a74d0
Memory contents:
0x5584224a6eb0: Just Testing, 0
0x5584224a74d0: heap, 20
bad idea constructed
heap2 constructed
Memory contents :
0x5584224a6eb0:bad idea, 6
0x5584224a7500: heap2, 10
heap destroyed
heap2 destroyed
done
-------

在使用定位 new 运算符时存在两个问题。

1. 首先，在创建第二个对象时，定位 new 运算符使用一个新对象来覆盖用于第一个对象的内存单元。显然，如果类动态地为其成员分配内存，这将引发问题

2. 其次，将 delete 用于 pc2 和 pc4 时，将自动调用为 pc2 和 pc4 指向的对象调用析构函数；然而，将 delete[] 用于 buffer 时，不会为使用定位 new 
   算符创建的对象调用析构函数

程序员必须负责管用定位 new 运算符用从中使用的缓冲区内存单元。'要使用不同的内存单元，程序员需要提供两个位于缓冲区的不同地址，并确保这两个内存单元不重叠'。

例如，可以这样做:
pc1 = new(buffer) JustTesting;
pc3 = new(buffer + sizeof(JustTesting)) JustTesting("hello",10);

'如果使用定位 new 运算符来为对象分配内存，必须确保其析构函数被调用'。

但如何确保呢？

对于在堆中创建的对象，可以这样做：

delete pc2;

但不能像下面这样做：

delete pc1;
delete pc3;

原因在于 delete 可与常规 new 运算符配合使用，但不能与定位 new 运算符配合使用。

指针 pc3 没有收到 new 运算符返回的地址，因此 delete pc3 将导致运行阶段错误。在另一方面，指针 pc1 指向的地址与 buffer 相同，但 buffer 是使用 new []
初始化的，因此必须使用 delete [] 而不是 delete 来释放。即使 buffer 是使用 new 而不是 new [] 初始化的，delete pc1 也将释放 buffer，而不是 pc1。
这是因为 new/delete 系统知道已分配的 512 字节块 buffer，但对定位 new 运算符对该内存块做了何种处理一无所知。

该程序确实释放了 buffer:

delete[] buffer;// free buffer

'delete[] buffer: 释放使用常规 new 运算符分配的整个内存块，但它没有为定位 new 运算符在该内存块中创建的对象调用析构函数'。。您之所以知道这一点，是因为该
程序使用了一个显示信息的析构函数，该析构函数宣布了 “Heap1” 和 “Heap2” 的死亡，但却没有宣布 “Just Testing” 和 “Bad Idea” 的死亡。

这种问题的解决方案是，'显式地为使用定位 new 运算符创建的对象调用析构函数'。正常情况下将自动调用析构函数，这是需要显式调用析构函数的少数几种情形之一。显式地调
用析构函数时，必须指定要销毁的对象。由于有指向对象的指针，因此可以使用这些指针:

pc3->~JustTesting();
pc1->~JustTesting();


placenew2.cpp '对定位 new 运算符使用的内存单元进行管理，加入到合适的 delete 和显式析构函数调用'。需要注意的一点是正确的删除顺序。对于使用定位 new 运算
符创建的对象，应以与创建顺序相反的顺序进行删除。原因在于，晚创建的对象可能依赖于早创建的对象。另外，'仅当所有对象都被销毁后，才能释放用于存储这些对象的缓冲区'。

#include<iostream>
#include<string>
#include<new>

using namespace std;

const int BUF = 512;

class JustTesting
{
    private:
        string words;
        int number;
    public:
        JustTesting(const string& s = "Just Testing", int n = 0)
        {
            words = s;
            number = n;
            cout << words << " constructed\n";
        }
        ~JustTesting()
        {
            cout << words << " destroyed\n";
        }
        void show() const
        {
            cout << words << ", " << number << endl;
        }

};

int main()
{
    char *buffer = new char[BUF];// get a block of memory
    JustTesting *pc1, *pc2;

    pc1 = new(buffer) JustTesting;// place object in buffer
    pc2 = new JustTesting("heap", 20);// place object on heap

    cout << "Memory block address:\n" << "buffer: " << (void *)buffer
    << " heap: " << pc2 << endl;
    cout << "Memory contents:\n";
    cout << pc1 <<": ";
    pc1->show();
    cout << pc2 <<": ";
    pc2->show();

    JustTesting *pc3,*pc4;
    // fix placement new location
    pc3 = new (buffer+sizeof(JustTesting)) JustTesting("Bad Idea",6);
    pc4 = new JustTesting("heap2",10);

    cout << "Memory contents :\n";
    cout << pc3 << ":";
    pc3->show();

    cout << pc4 << ": ";
    pc4->show();
    delete pc2;// free heap1
    delete pc4;// free heap2

    // explicit destroy placement new object
    pc3->~JustTesting();
    pc1->~JustTesting();

    delete[] buffer;// free buffer
    cout << "done\n";
    return 0;
}

 » g++ --std=c++11 placenew2.cpp              
---------------------------------
 » ./a.out                                    
Just Testing constructed
heap constructed
Memory block address:
buffer: 0x5625e4e55eb0 heap: 0x5625e4e564d0
Memory contents:
0x5625e4e55eb0: Just Testing, 0
0x5625e4e564d0: heap, 20
Bad Idea constructed
heap2 constructed
Memory contents :
0x5625e4e55ed8:Bad Idea, 6
0x5625e4e56500: heap2, 10
heap destroyed
heap2 destroyed
Bad Idea destroyed
Just Testing destroyed
done
----------

'该程序使用定位 new 运算符在相邻的内存单元中创建两个对象，并调用了合适的析构函数'。


// !! 复习各种技术

至此，介绍了多种用于处理各种与类相关的问题的编程技术。可能难以掌握这些技术, 下面对它们进行总结，并介绍何时使用它们。

1. 重载 << 运算符

'要重新定义 << 运算符，以便将它和 cout 一起用来显示对象的内容'，请定义下面的友元运算符函数:

ostream& operator<<(ostream & os, const c_name & obj)
{
    os << ...；
    return os;
}

其中 c_name 是类名。如果该类提供了能够返回所需内容的公有方法，则可在运算符函数中使用这些方法，这样便不用将它们设置为友元函数了。


2. 转换函数

要将单个值转换为类类型，需要创建原型如下所示的类构造函数:

c_name(type_name value);

其中 c_name 为类名，type_name 是要转换的类型的名称。

要将类转换为其他类型，需要创建原型如下所示的类成员函数:

operator typeName();

虽然该函数没有声明返回类型，但应返回所需类型的值。使用转换函数时要小心。'可以在声明构造函数时使用关键字 explicit，以防止它被用于隐式转换'。

3. 其构造函数使用 new 的类

如果类使用 new 运算符来分配类成员指向的内存，在设计时应采取一些预防措施:

    1. 对于指向的内存是由 new 分配的所有类成员，都应在类的析构函数中对其使用 delete，该运算符将释放分配的内存

    2. 如果析构函数通过对指针类成员使用 delete 来释放内存，则每个构造函数都应当使用 new 来初始化指针，或将它设置为空指针

    3. 构造函数中要么使用 new[]，要么使用 new，而不能混用。如果构造函数使用的是 new[]，则析构函数应使用 delete[]；如果构造函数使用的是 new，则析构
       函数应使用 delete

    4. 应定义一个分配内存(而不是将指针指向已有内存)的复制构造函数。这样程序将能够将类对象初始化为另一个类对象。这种构造函数的原型通常如下：

    className(const Class_Name &);

    5. 应定义一个重载赋值运算符的类成员函数，其函数定义如下(其中 c_pointer 是 c_name 的类成员，类型为指向 type_name 的指针)




// !! 队列模拟

进一步了解类后, 可将这方面的知识用于解决编程问题。


// !!队列类

首先需要设计一个 Queue 类, 这里先列出队列的特征：

1. 队列存储有序的项目序列
2. 队列所能容纳的项目数有一定的限制
3. 应当能够创建空队列
4. 应当能够检查队列是否为空
5. 应当能够检查队列是否是满的
6. 应当能够在队尾添加项目
7. 应当能够从队首删除项目
8. 应当能够确定队列中项目数

设计类时，需要开发公有接口和私有实现。

// !! Queue 类的接口

从队列的特征可知，Queue 类的公有接口应该如下:

class Queue
{
    enum{Q_SIZE = 10};
    private:
    // later 
    public:
        Queue(int size = Q_SIZE);
        ~Queue();
        bool isEmpty() const;
        boo isFull() const;
        int queueCount()const;
        bool enqueue(const Item & item);
        bool dequeue(Item &item);
};

Queue line1;
Queue line2(20);


使用队列时，可以使用 typedef 来定义 Item。


// !! Queue 类的实现

'确定接口后，便可以实现它'。首先，需要确定如何表示队列数据。一种方法是使用 new 动态分配一个数组，它包含所需的元素数。然而，对于队列操作而言，数组并不
太合适。例如，删除数组的第一个元素后，需要将余下的所有元素向前移动一位； 否则需要作一些更费力的工作，如将数组视为是循环的。'然而链表能够很好地满足队列的
要求', '链表由节点序列构成。每一个节点中都包含要保存到链表中的信息以及一个指向下一个节点的指针'。对于这里的队列来说，数据部分都是一个 Item 类型的值，因
此可以使用下面的结构来表示节点:

struct Node 
{
    Item item;// data stored in the node
    struct Node *next;// point to next node
};

通常，链表最后一个节点中的指针被设置为 NULL（或 0），以指出后面没有节点了。'在 C++11 中，应使用新增的关键字 nullptr。要跟踪链表, 必须知道第一个节点
的地址'。可以让 Queue 类的一个数据成员指向链表的起始位置。具体地说，这是所需要的全部信息，有了这种信息后，就可以沿节点链找到任何节点。然而，'由于队列总
是将新项目添加到队尾，因此包含一个指向最后一个节点的数据成员将非常方便'。此外，'还可以使用数据成员来跟踪队列可存储的最大项目数以及当前的项目数'。

class Queue
{
private:
    struct Node 
    {
        Item item;// data stored in the node
        struct Node *next;// point to next node
    };
    enum {Q_SIZE = 10};
    Node *front;
    Node *rear;
    int items;
    const int q_size;
    ...
public:

};

上述声明使用了 C++ 的一项特性:'在类中嵌套结构或类声明。通过将 Node 声明放在 Queue 类中，可以使其作用域为整个类'。设计好数据的表示方式后，接下来需要编
写类方法。

// !!类方法

类构造函数应提供类成员的值。由于在这个例子中，队列最初是空的，因此队首和队尾指针都设置为 NULL（0或 nullptr），并将 items 设置为0。另外，还应将队列的最大
长度 qsize 设置为构造函数参数 qs 的值。

下面的实现方法无法正常运行:

Queue::Queue(int qs)
{
    front = rear = nullptr;
    items = 0;
    qsize = qs;// not acceptable
}

'问题在于 qsize 是常量，所以可以对它进行初始化，但不能给它赋值'。从概念上说, 调用构造函数时，对象将在括号中的代码执行之前被创建。因此，调用 Queue（int qs）
构造函数将导致程序首先给 4 个成员变量分配内存。然后，程序流程进入到括号中，使用常规的赋值方式将值存储到内存中。'因此对于 const 数据成员，必须在执行到构造函数
体之前，即创建对象时进行初始化'。

'C++ 提供了一种特殊的语法来完成上述工作，它叫做成员初始化列表(member initializer list)'。成员初始化列表由逗号分隔的初始化列表组成(前面带冒号)。它位于
参数列表的右括号之后、函数体左括号之前。如果数据成员的名称为 mdata，并需要将它初始化为 val，则初始化器为 mdata（val）。使用这种表示法，可以这样编写 Queue 
的构造函数:

Queue::Queue(int qs):qsize(qs)// initialize qs to qsize
{
    front = rear = nullptr;
    items = 0;
}

通常，初值可以是常量或构造函数的参数列表中的参数。这种方法并不限于初始化常量，可以将 Queue 构造函数写成如下所示:

Queue::Queue(int qs):qsize(qs),front(nullptr),rear(nullptr),items(0)
{

}

'只有构造函数可以使用这种初始化列表语法'。如上所示，对于 const 类成员，必须使用这种语法。另外，对于被声明为引用的类成员，也必须使用这种语法：

class Agency{...};

class Agent
{
    private:
        Agency &belong;// must use initializer list to initialize
        ...
};

Agent::Agent(Agency &a):belong(a){...}


'这是因为引用与 const 数据类似，只能在被创建时进行初始化'。对于简单数据成员，使用成员初始化列表和在函数体中使用赋值没有什么区别。'对于本身就是类对象的
成员来说，使用成员初始化列表的效率更高'。


成员初始化列表的语法

如果 Classy 是一个类，而 mem1、mem2 和 mem3 都是这个类的数据成员，则类构造函数可以使用如下的语法来初始化数据成员:

Classy::Classy(int n, int m):mem1(n),mem2(m),mem3(n*m+2)
{
    //...
}

代码将 mem1 初始化为 n，将 mem2 初始化为 0，将 mem3 初始化为 n*m + 2。'从概念上说，这些初始化工作是在对象创建时完成的，此时还未执行括号中的任何代码'。

请注意以下几点：

1. 这种格式只能用于构造函数

2. 必须用这种格式来初始化非静态 const 数据成员（至少在 C++11 之前是这样的）

3. 必须用这种格式来初始化引用数据成员

4. '数据成员被初始化的顺序与它们出现在类声明中的顺序相同'，与初始化器中的排列顺序无关

警告：

不能将成员初始化列表语法用于构造函数之外的其他类方法


'成员初始化列表使用的括号方式也可用于常规初始化'。也就是说，如果愿意，可以将下述代码:

int games = 162;
double talk = 2.43212;

替换为：

int games(162);
double talk(2.43212);

'这使得初始化内置类型就像初始化类对象一样'。

// !! C++11 的类内初始化

'C++11 允许您以更直观的方式进行初始化'：

class Classy
{
    int mem1 = 10;
    const int mem2 = 10010;
    //...
};

这与在构造函数中使用成员初始化列表等价:

Classy::Classy():mem1(10),mem2(10010){...}

成员 mem1 和 mem2 将分别被初始化为 10和 10010，除非调用了使用成员初始化列表的构造函数，在这种情况下，实际列表将覆盖这些默认初始值:

Classy::Classy(int n):mem1(n){...}

在这里，构造函数将使用 n 来初始化 mem1，但 mem2 仍被设置为 10010。



将项目添加到队尾(入队)比较麻烦。下面是一种方法:


bool Queue::dequeue(const Item & item)
{
    if(isFull())
    {
        return false;
    }
    Node *add = new Node;// create a node
    add->item = item;
    add->next = NULL;
    ++items;
    if(front == NULL)
    {
        front = add;
    }
    else
    {
        rear->next = add;
    }
    rear = add;
    return true;
}


删除队首项目(出队)也需要多个步骤才能完成。下面是一种方式：

bool Queue::dequeue(Item &item)
{
    if(front == NULL)
    {
        return false;
    }
    item = front->item;
    --items;
    Node *temp = front;
    front = front->next;
    delete temp;
    if(items == 0)
    {
        rear = NULL;
    }
    return true;
}

类需要一个显式析构函数——该函数删除剩余的所有节点。下面是一种实现，它从链表头开始，依次删除其中的每个节点:

Queue::~Queue()
{
    Node *temp;
    while(front != NULL)
    {
        temp = front;
        front = front->next;
        delete temp;
    }
}

'使用 new 的类通常需要包含显式复制构造函数和执行深度复制的赋值运算符',复制 Queue 对象的成员将生成一个新的对象，该对象指向链表原来的头和尾。因此，将项目添加到
复制的 Queue 对象中，将修改共享的链表。这样做将造成非常严重的后果。更糟的是, 只有副本的尾指针得到了更新，从原始对象的角度看，这将损坏链表。'显然，要克隆或复制
队列，必须提供复制构造函数和执行深度复制的赋值构造函数'。

当然，这提出了这样一个问题：为什么要复制队列呢？

也许是希望在模拟的不同阶段保存队列的瞬像，也可能是希望为两个不同的策略提供相同的输入。实际上，拥有拆分队列的操作是非常有用的，超市在开设额外的收款台时经常这样
做。同样，也可能希望将两个队列结合成一个或者截短一个队列。

但假设这里的模拟不实现上述功能。难道不能忽略这些问题，而使用已有的方法吗？当然可以。然而，在将来的某个时候，可能需要再次使用队列且需要复制。另外，您可能会忘记
没有为复制提供适当的代码。在这种情况下，程序将能编译和运行，但结果却是混乱的，甚至会崩溃。因此，最好还是提供复制构造函数和赋值运算符，尽管目前并不需要它们。

'幸运的是, 有一种小小的技巧可以避免这些额外的工作，并确保程序不会崩溃'。

这就是将所需的方法定义为伪私有方法：

class Queue
{
private:
    Queue(const Queue &q):qsize(q){...}
    Queue & operator=(const Queue &q){return *this}
    ...
};

这样做有两个作用：第一，它避免了本来将自动生成的默认方法定义。第二，因为这些方法是私有的，所以不能被广泛使用。也就是说，如果 nip 和 tuck 是 Queue对象，则
编译器就不允许这样做:

Queue snick(nip);
tuck = nip;

所以，'与其将来面对无法预料的运行故障，不如得到一个易于跟踪的编译错误，指出这些方法是不可访问的'。另外，在定义其对象不允许被复制的类时，这种方法也很有用。

C++11 提供了另一种禁用方法的方式——使用关键字 delete。


// !! Customer 类

接下来需要设计客户类。通常，ATM 客户有很多属性，例如姓名、账户和账户结余。然而，这里的模拟需要使用的唯一一个属性是客户何时进入队列以及客户交易所需的时间。当
模拟生成新客户时，程序将创建一个新的客户对象，并在其中存储客户的到达时间以及一个随机生成的交易时间。当客户到达队首时，程序将记录此时的时间，并将其与进入队列的
时间相减，得到客户的等候时间。

下面的代码演示了如何定义和实现 Customer 类：

class Customer
{
private:
    long arrive;
    int processtime;
public:
    Customer(){arrive = processtime = 0;}
    void set(long when);
    long when() const {return arrival;}
    int ptime() const {return processtime;}
};

void Customer::set(long when)
{
    processtime = std::rand() % 3+1;
    arrive = when;
}

默认构造函数创建一个空客户。set() 成员函数将到达时间设置为参数，并将处理时间设置为 1～3 中的一个随机值。

queue.h 将 Queue 和 Customer 类声明放到一起，而 queue.cpp 列出了方法。


// !! ATM 模拟

现在已经拥有模拟 ATM 所需的工具。程序允许用户输入 3 个数：队列的最大长度、程序模拟的持续时间（单位为小时）以及平均每小时的客户数。程序将使用循环——每次循环代
表一分钟。在每分钟的循环中，程序将完成下面的工作。

1. 判断是否来了新的客户。如果来了，并且此时队列未满，则将它添加到队列中，否则拒绝客户入队

2. 如果没有客户在进行交易， 则选取队列的第一个客户。确定该客户的已等候时间，并将 wait_time 计数器设置为新客户所需的处理时间

3. 如果客户正在处理中，则将 wait_time 计数器减 1

4. 记录各种数据，如获得服务的客户数目、被拒绝的客户数目、排队等候的累积时间以及累积的队列长度等

当模拟循环结束时，程序将报告各种统计结果

一个有趣的问题是，程序如何确定是否有新的客户到来。假设平均每小时有 10 名客户到达，则相当于每 6 分钟有一名客户。程序将计算这个值，并将它保存在 min_per_cust 
变量中。然而，刚好每 6 分钟来一名客户不太现实，我们真正(至少在大部分时间内)希望的是一个更随机的过程——但平均每 6 分钟来一名客户。程序将使用下面的函数来确定是
否在循环期间有客户到来:


bool newCustomer(double x)
{
    return (std::rand() * x / RAND_MAX < 1);
}

其工作原理如下：值 RAND_MAX 是在 cstdlib 文件中定义的，是 rand() 函数可能返回的最大值（0 是最小值）。假设客户到达的平均间隔时间 x 为 6，则 
rand()* x / RAND_MAX 的值将位于 0 到 6 之间。具体地说，平均每隔 6 次，这个值会有 1 次小于 1。然而，这个函数可能会导致客户到达的时间间隔有时为 1 分钟，
有时为 20 分钟。这种方法虽然很笨拙，但可使实际情况不同于有规则地每 6 分钟到来一个客户。如果客户到达的平均时间间隔少于 1 分钟，则上述方法将无效，但模拟并不
是针对这种情况设计的。如果确实需要处理这种情况，最好提高时间分辨率，比如每次循环代表 10 秒钟。

bank.cpp 给出了模拟的细节。长时间运行该模拟程序，可以知道长期的平均值；短时间运行该模拟程序，将只能知道短期的变化。


// !! 总结

本章介绍了定义和使用类的许多重要方面。其中的一些方面是非常微妙甚至很难理解的概念。如果其中的某些概念对于您来说过于复杂，也不用害怕——这些问题对于大多数 C++ 
的初学者来说都是很难的。通常，'对于诸如复制构造函数等概念,都是在由于忽略它们而遇到了麻烦后逐步理解的'。本章介绍的一些内容乍看起来非常难以理解，但是随着经验越
来越丰富，对其理解也将越透彻。

'在类构造函数中，可以使用 new 为数据分配内存，然后将内存地址赋给类成员'。这样，类便可以处理长度不同的字符串，而不用在类设计时提前固定数组的长度。在类构造函
数中使用 new，也可能在对象过期时引发问题。如果对象包含成员指针，同时它指向的内存是由 new 分配的，则释放用于保存对象的内存并不会自动释放对象成员指针指向的内
存。'因此在类构造函数中使用 new 类来分配内存时，应在类析构函数中使用 delete 来释放分配的内存'。这样，当对象过期时，将自动释放其指针成员指向的内存。

如果对象包含指向 new 分配的内存的指针成员，则将一个对象初始化为另一个对象，或将一个对象赋给另一个对象时，也会出现问题。'在默认情况下，C++ 逐个对成员进行初始化
和赋值，这意味着被初始化或被赋值的对象的成员将与原始对象完全相同'。如果原始对象的成员指向一个数据块，则副本成员将指向同一个数据块。当程序最终删除这两个对象时，
类的析构函数将试图删除同一个内存数据块两次，这将出错。解决方法是：定义一个特殊的复制构造函数来重新定义初始化，并重载赋值运算符。在上述任何一种情况下，新的定
义都将创建指向数据的副本，并使新对象指向这些副本。'这样，旧对象和新对象都将引用独立的、相同的数据，而不会重叠'。由于同样的原因，必须定义赋值运算符。对于每一种
情况，最终目的都是执行深度复制，即'复制实际的数据，而不仅仅是复制指向数据的指针'。

'对象的存储持续性为自动或外部时，在它不再存在时将自动调用其析构函数'。如果使用 new 运算符为对象分配内存，并将其地址赋给一个指针，则当您将 delete 用于该指针
时将自动为对象调用析构函数。'如果使用定位 new 运算符为类对象分配内存，则必须负责显式地为该对象调用析构函数，方法是使用指向该对象的指针调用析构函数方法'。

'C++ 允许在类中包含结构、类和枚举定义。这些嵌套类型的作用域为整个类， 这意味着它们被局限于类中， 不会与其它地方定义的同名结构、类和枚举发生冲突'。

'C++ 为类构造函数提供了一种可用来初始化数据成员的特殊语法'。这种语法包括冒号和由逗号分隔的初始化列表，被放在构造函数参数的右括号后，函数体的左括号之前。
每一个初始化器都由被初始化的成员的名称和包含初始值的括号组成。'从概念上来说，这些初始化操作是在对象创建时进行的，此时函数体中的语句还没有执行'。

语法如下：

queue(int qs):qsize(qs),items(0),front(NULL),back(NULL)
{

}

如果数据成员是非静态 const 成员或引用，则必须采用这种格式，但可将 C++11 新增的类内初始化用于非静态 const 成员。

'C++11 允许类内初始化，即在类定义中进行初始化':


class Queue
{
private:
    ...
    Node *front = NULL;
    enum {Q_SIZE = 10};
    Node *rear = NULL;
    int items = 0;
    const int qsize = Q_SIZE;
    ...
};


这与使用成员初始化列表等价。然而，使用成员初始化列表的构造函数将覆盖相应的类内初始化。'您可能已经注意到，与简单的 C 结构相比，需要注意的类细节要多得多。
作为回报，它们的功能也更强'。