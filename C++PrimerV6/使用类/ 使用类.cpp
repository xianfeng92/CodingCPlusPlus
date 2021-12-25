// !! 使用类

C++ 类特性丰富、复杂、功能强大。

'学习 C++ 的难点之一是需要记住大量的东西, 但在拥有丰富的实践经验之前, 根本不可能全部记住这些东西'。也许，学习本章知识的最好方法是，在我们自己开发的C++ 程
序中使用其中的新特性。对这些新特性有了充分的认识后，就可以添加其他 C++ 特性了。正如 C++ 创始人 Bjarne Stroustrup 在一次 C++ 专业程序员大会上所建议的:
"轻松地使用这种语言。不要觉得必须使用所有的特性，不要在第一次学习时就试图使用所有的特性"。

// !! 运算符重载

下面介绍一种使对象操作更美观的技术。运算符重载是一种形式的 C++ 多态。'运算符重载将重载的概念扩展到运算符上，允许赋予 C++ 运算符多种含义'。实际上，很多 C++
运算符已经被重载。例如，将 * 运算符用于地址，将得到存储在这个地址中的值；但将它用于两个数字时，得到的将是它们的乘积。'C++ 根据操作数的数目和类型来决定采用
哪种操作'。

'C++ 允许将运算符重载扩展到用户定义的类型'，例如，允许使用 + 将两个对象相加。编译器将根据操作数的数目和类型决定使用哪种加法定义。'重载运算符可使代码看起来更
自然'。

例如，将两个数组相加是一种常见的运算。通常，需要使用下面这样的 for 循环来实现:

for(int i = 0; i < 20; i++) 
{
    arr3[i] = arr1[i] + arr2[i];
}

但在 C++ 中，可以定义一个表示数组的类，并重载 + 运算符。于是便可以有这样的语句:

arr3 = arr2 + arr1;

'这种简单的加法表示法隐藏了内部机理，并强调了实质，这是 OOP 的另一个目标'。

要重载运算符，需使用被称为运算符函数的特殊函数形式。运算符函数的格式如下:

operatorop(argument list);

例如，operator +() 重载 + 运算符，operator *() 重载 * 运算符。op 必须是有效的 C++ 运算符，不能虚构一个新的符号。

例如，不能有 operator@() 这样的函数，因为 C++ 中没有 @ 运算符。然而，operator 函数将重载 [] 运算符，因为 [] 是数组索引运算符。例如，假设有一个 
Salesperson 类，并为它定义了一个operator +() 成员函数，以重载 + 运算符，以便能够将两个 Saleperson 对象的销售额相加，则如果 district2、sid 和 sara 
都是 Salesperson 类对象，便可以编写这样的等式:

district2 = sid + sara;

'编译器发现，操作数是 Salesperson 类对象，因此使用相应的运算符函数替换上述运算符':

district2 = sid.operator+(sara);

然后该函数将隐式地使用 sid(因为它调用了方法)，而显式地使用 sara 对象(因为它被作为参数传递)，来计算总和，并返回这个值。'当然最重要的是，可以使用简便的 + 运
算符表示法，而不必使用笨拙的函数表示法'。


// !! 计算时间：一个运算符重载示例

#ifndef A3278E75_2B07_4E7F_B108_C15F9D0C188E
#define A3278E75_2B07_4E7F_B108_C15F9D0C188E

class Time
{
private:
    int hour;
    int minute;
public:
    Time();
    Time(int h, int m = 0);
    void addMinute(int m);
    void addHour(int h);
    void reset(int h = 0, int m = 0);
    Time sum(const Time& t) const;
    void show() const;
};

#endif /* A3278E75_2B07_4E7F_B108_C15F9D0C188E */

Time 类提供了用于调整和重新设置时间、显示时间、将两个时间相加的方法。


mytime0.cpp 列出了方法定义。请注意，当总的分钟数超过 59 时，AddMin() 和 Sum() 方法是如何使用整数除法和求模运算符来调整 minutes 和 hours 值的。另外，由
于这里只使用了 iostream 的 cout，且只使用了一次，因此使用 std::cout 比导入整个名称空间更经济。

#include<iostream>
#include "mytime0.h"

Time::Time()
{
    hours = minutes = 0;
}

Time::Time(int h, int m)
{
    hours = h;
    minutes = m;
}

void Time::addMinute(int m)
{
    if(minutes + m > 59)
    {
        hours += (minutes + m)/60;
        minutes = (minutes + m)%60;
    }
    else
    {
        minutes += m;
    }
}

void Time::addHour(int h)
{
    hours += h;
}

void Time::remove(int h, int m)
{
    hours =h;
    minutes =m
}

Time Time::sum(const Time &t) const
{
    Time sum;
    sum.minute = minutes + t.minute;
    sum.hours = hours + t.hour + (minutes + t.minute)/60;
    sum.minutes = (minutes + t.minute) % 60;
    return sum;
}

void Time::show() const
{
    std::cout << hours << "hour" << ":" << "minutes" << ":" << minutes << '\n';
}

来看一下 Sum() 函数的代码。注意参数是引用，但返回类型却不是引用。'将参数声明为引用的目的是为了提高效率'。如果按值传递 Time 对象，代码的功能将相同，但传递引
用，速度将更快，使用的内存将更少。

然而，返回值不能是引用。因为函数将创建一个新的 Time 对象(sum)，来表示另外两个 Time 对象的和。'返回对象将创建对象的副本，而调用函数可以使用它'。

'如果返回类型为 Time &，则引用的将是 sum 对象。但由于 sum 对象是局部变量，在函数结束时将被删除，因此引用将指向一个不存在的对象'。使用返回类型 Time 意味着
 程序将在删除 sum 之前构造它的拷贝，调用函数将得到该拷贝。

警告:

'不要返回指向局部变量或临时对象的引用。函数执行完毕后，局部变量和临时对象将消失，引用将指向不存在的数据'。

最后，usetime0.cpp 对 Time 类中计算时间总和的部分进行了测试。

#include <iostream>
#include "mytime0.h"

int main()
{
    using std::cout;
    using std::endl;
    Time planing;
    Time coding(2,40);
    Time fixing(5,55);
    Time total;
    cout << "planning time: \n";
    planning.show();
    cout << endl;

    cout << "coding time: \n";
    coding.show();
    cout<<endl;

    cout << "fix time: \n";
    fixing.show();
    cout << endl;

    total = coding.sum(fixing);
    cout << "time time: \n";
    total.show();
    count << endl;
    return 0;
}


 » g++ --std=c++11 mytime0.cpp usetime0.cpp
--------------------------------------------------------------------------------
 » ./a.out
planning time: 
0hour:minutes:0

coding time: 
2hour:minutes:40

fix time: 
5hour:minutes:55

time time: 
8hour:minutes:35

// !! 添加加法运算符


'将 Time 类转换为重载的加法运算符很容易'，只要将 Sum() 的名称改为 operator +() 即可。

Time Time::operator+(const Time &t) const
{
    Time sum;
    sum.minutes = minutes + t.minutes;
    sum.hours = hours + t.hours + (minutes + t.minutes)/60;
    sum.minutes = (minutes + t.minutes) % 60;
    return sum;
}

和 Sum() 一样，operator+() 也是由 Time 对象调用的，它将第二个 Time 对象作为参数，并返回一个 Time 对象。因此，可以像调用 Sum() 那样来调用 
operator +() 方法:

total = coding.operator+(fixing);// function notation

但将该方法命令为 operator +() 后，也可以使用运算符表示法：

total = coding + fixing;// operator notation

这两种表示法都将调用 operator+() 方法。'在运算符表示法中，运算符左侧的对象(这里为 coding)是调用对象，运算符右边的对象(这里为 fixing)是作为参数被传递
的对象'。

总之，operator+() 函数的名称使得可以使用函数表示法或运算符表示法来调用它。编译器将根据操作数的类型来确定如何做：

int a,b,c;
Time A,B,C;
c = a + b;// use int addition
C = A + B;// use addition as define for Time object

可以将两个以上的对象相加吗 ？例如，如果 t1、t2、t3 和 t4 都是Time对象，可以这样做吗 ?

t4 = t1 + t2 + t3;

为回答这个问题，来看一些上述语句将被如何转换为函数调用。由于 + 是从左向右结合的运算符，因此上述语句首先被转换成下面这样:

t4 = t1.operator+(t2 + t3); // valid ?

t4 = t1.operator+(t2.operator+(t3));// valid ? YES

上述语句合法吗？ 

是的。函数调用 t2.operator+(t3) 返回一个 Time 对象，后者是 t2 和 t3 的和。然而，该对象成为函数调用 t1.operator+() 的参数，该调用返回t1 与表示 t2 
和 t3 之和的 Time 对象的和。总之，最后的返回值为 t1、t2 和 t3 之和，这正是我们期望的。


// !! 重载限制

多数 C++ 运算符都可以用这样的方式重载。'重载的运算符(有些例外情况)不必是成员函数，但必须至少有一个操作数是用户定义的类型'。下面详细介绍 C++ 对用户定义的运
算符重载的限制。

1. '重载后的运算符必须至少有一个操作数是用户定义的类型，这将防止用户为标准类型重载运算符'。因此，不能将减法运算符(−)重载为计算两个 double 值的和，而不
    是它们的差。虽然这种限制将对创造性有所影响，但可以确保程序正常运行。

2. '使用运算符时不能违反运算符原来的句法规则'。例如，不能将求模运算符(%)重载成使用一个操作数。同样，'不能修改运算符的优先级'。因此，如果将加号运算符重载成将
    两个类相加，则新的运算符与原来的加号具有相同的优先级。

3. '不能创建新运算符'。例如，不能定义 operator**() 函数来表示求幂

4. 不能重载下面的运算符
   sizeof,sizeof 运算符
   ::, 作用域解析运算符
   ?:, 条件运算符
   const_cast, 强制类型转换运算符
   static_cast, 强制类型转换运算符


// !! 其他重载运算符

'还有一些其他的操作对 Time 类来说是有意义的'。例如，可能要将两个时间相减或将时间乘以一个因子，这需要重载减法和乘法运算符。这和重载加法运算符采用的技术相同，
即创建 operator-() 和 operator*() 方法。

也就是说，将下面的原型添加到类声明中:

Time operator-(const Time& other) const;
Time operator*(double n) const;


// !! 友元

'C++ 控制对类对象私有部分的访问'。通常，公有类方法提供唯一的访问途径，但是有时候这种限制太严格，以致于不适合特定的编程问题。'在这种情况下，C++ 提供了另外一种
形式的访问权限：友元'。

友元有 3 种:

1. 友元函数

2. 友元类

3. 友元成员函数

'通过让函数成为类的友元，可以赋予该函数与类的成员函数相同的访问权限'。

介绍如何成为友元前，先介绍为何需要友元。

'在为类重载二元运算符时(带两个参数的运算符)常常需要友元'。将 Time 对象乘以实数就属于这种情况，下面来看看。

在前面的 Time 类示例中，重载的乘法运算符与其他两种重载运算符的差别在于，它使用了两种不同的类型。也就是说，加法和减法运算符都结合两个 Time 值，而乘法运算符将
一个 Time 值与一个 double 值结合在一起。这限制了该运算符的使用方式。记住，左侧的操作数是调用对象。也就是说，下面的语句:

A = B * 2.75;

将被转换为下面的成员函数调用：

A = B.operator*(2.75);

但下面的语句又如何呢 ？

A = 2.75 * B;

从概念上说，2.75 * B 应与 B *2.75 相同，但第一个表达式不对应于成员函数，因为 2.75 不是Time类型的对象。'记住，左侧的操作数应是调用对象，但 2.75 不是对象'。
因此，编译器不能使用成员函数调用来替换该表达式。

解决这个难题的一种方式是，告知每个人(包括程序员自己)，只能按 B * 2.75 这种格式编写，不能写成 2.75 * B 。'这是一种对服务器友好-客户警惕的（server-friendly, 
client-beware）解决方案'，与 OOP 无关。

然而，还有另一种解决方式——非成员函数('记住，大多数运算符都可以通过成员或非成员函数来重载')。非成员函数不是由对象调用的, 它使用的所有值(包括对象)都是显式参数。
这样，编译器能够将下面的表达式:

A = 2.75 * B;// cannot correspond to a member function

与下面的非成员函数调用匹配：

A = operator*(2.75,B);

该函数的原型如下:

Time operator*(double n, const Time &t);

'对于非成员重载运算符函数来说，运算符表达式左边的操作数对应于运算符函数的第一个参数，运算符表达式右边的操作数对应于运算符函数的第二个参数'。而原来的成员函数则按
相反的顺序处理操作数，也就是说，double 值乘以 Time 值。使用非成员函数可以按所需的顺序获得操作数(先是 double，然后是 Time)，但引发了一个新问题：非成员函数不
能直接访问类的私有数据，至少常规非成员函数不能访问。然而，'有一类特殊的非成员函数可以访问类的私有成员，它们被称为友元函数'。


// !! 创建友元

创建友元函数的第一步是将其原型放在类声明中，并在原型声明前加上关键字 friend:

friend Time operator*(double n, const Time &t);

该原型意味着下面两点:

1. 虽然 operator*() 函数是在类声明中声明的，但它不是成员函数，因此不能使用成员运算符来调用

2. 虽然 operator*() 函数不是成员函数，但它与成员函数的访问权限相同

第二步是编写函数定义。'因为它不是成员函数，所以不要使用 Time:: 限定符'。另外，不要在定义中使用关键字 friend，定义应该如下:

Time operator*(double n, const Time &t)
{
    Time result;
    long totalminutes = t.hours * n + t.minutes *n;
    result.hours = totalminutes / 60;
    result.minutes = totalminutes % 60;
    return result;
}


有了上述声明和定义后，下面的语句:

A = 2.75 * B;

将转换为如下语句，从而调用刚才定义的非成员友元函数:

A = operator*(2.75,B);

总之，'类的友元函数是非成员函数, 其访问权限与成员函数相同'。


'友元是否有悖于 OOP'

乍一看，您可能会认为友元违反了 OOP 数据隐藏的原则，因为友元机制允许非成员函数访问私有数据。然而，这个观点太片面了。相反，应将友元函数看作类的扩展接口的组成部分。
例如，从概念上看，double 乘以 Time 和 Time 乘以 double 是完全相同的。也就是说，前一个要求有友元函数，后一个使用成员函数，这是 C++ 句法的结果，而不是概念上
的差别。通过使用友元函数和类方法，可以用同一个用户接口表达这两种操作。'另外请记住，只有类声明可以决定哪一个函数是友元，因此类声明仍然控制了哪些函数可以访问私有
数据'。总之，类方法和友元只是表达类接口的两种不同机制。

实际上，按下面的方式对定义进行修改(交换乘法操作数的顺序)，可以将这个友元函数编写为非友元函数:

Time operator*(double n, const Time &t)
{
    return t*n;// use t.operator*(n)
}

原来的版本显式地访问 t.minutes 和 t.hours，所以它必须是友元。这个版本将 Time 对象 t 作为一个整体使用，让成员函数来处理私有值，因此不必是友元。然而，将该
版本作为友元也是一个好主意。最重要的是，它将该作为正式类接口的组成部分。其次，如果以后发现需要函数直接访问私有数据，则只要修改函数定义即可，而不必修改类原型。

// !! 常用的友元：重载 << 运算符

'一个很有用的类特性是，可以对 << 运算符进行重载，使之能与 cout 一起来显示对象的内容'。

假设 trip 是一个 Time 对象。为显示 Time 的值，前面使用的是 show()。然而，如果可以像下面这样操作将更好:

cout << trip;// make cout recognise Time class ?

'之所以可以这样做，是因为 << 是可被重载的 C++ 运算符之一'。实际上，它已经被重载很多次了。最初，<< 运算符是 C 和 C++ 的位运算符，将值中的位左移。ostream 
类对该运算符进行了重载，将其转换为一个输出工具。前面讲过，'cout 是一个 ostream 对象，它是智能的，能够识别所有的 C++ 基本类型'。这是因为对于每种基本类型，
ostream 类声明中都包含了相应的重载的 operator<<() 定义。也就是说，一个定义使用 int 参数，一个定义使用 double 参数，等等。因此，要使 cout 能够识别 Time 
对象，一种方法是将一个新的函数运算符定义添加到 ostream 类声明中。但修改 iostream 文件是个危险的主意，这样做会在标准接口上浪费时间。相反，通过 Time 类声明来
让 Time 类知道如何使用 cout。

1. << 的第一种重载版本

要使 Time 类知道使用 cout，必须使用友元函数。这是什么原因呢？因为下面这样的语句使用两个对象，其中第一个是 ostream 类对象(cout):

cout << trip;

'如果使用一个 Time 成员函数来重载 <<，Time 对象将是第一个操作数，就像使用成员函数重载 * 运算符那样'。这意味着必须这样使用 <<：

trip << cout; // if operator<<() were a Time  member function

通过使用友元函数，可以像下面这样重载运算符:

void operator<<(ostream &os,const Time &t)
{
    os << t.hours << t.minutes << '\n';
}

这样可以使用下面的语句：

cout << trip;

'友元还是非友元？'

新的 Time 类声明使 operatro<<() 函数成为 Time 类的一个友元函数。但该函数不是 ostream 类的友元(尽管对ostream类并无害处)。operator<<() 函数接受一个 
ostream 参数和一个 Time 参数，因此表面看来它必须同时是这两个类的友元。然而，看看函数代码就会发现，尽管该函数访问了 Time 对象的各个成员，但从始至终都将 
ostream 对象作为一个整体使用。因为 operator<<() 直接访问 Time 对象的私有成员，所以它必须是 Time 类的友元。但由于它并不直接访问 ostream 对象的私有成员，
所以并不一定必须是 ostream 类的友元。这很好，因为这就意味着不必修订 ostream 的定义。注意，新的 operator<<() 定义使用 ostream 引用 os 作为它的第一个参数。
通常情况下，os 引用 cout 对象，如表达式 cout << trip 所示。但也可以将这个运算符用于其他 ostream 对象，在这种情况下，os 将引用相应的对象。


调用 cout << trip 应使用 cout 对象本身，而不是它的拷贝，因此该函数按引用(而不是按值) 来传递该对象。'这样，表达式 cout << trip 将导致 os 成为 cout 的一
个别名'。


2. << 的第二种重载版本

前面介绍的实现存在一个问题。像下面这样的语句可以正常工作：

cout << trip；

但这种实现不允许像通常那样将重新定义的 << 运算符与 cout 一起使用：

cout << "trip time: " << trip << '\n';

要理解这样做不可行的原因以及必须如何做才能使其可行，首先需要了解关于 cout 操作的一点知识。请看下面的语句:

int x = 5;
int y = 10;
cout << x << y << '\n';

C++ 从左至右读取输出语句，意味着它等同于:

(cout << x) << y << '\n';

正如 iosream 中定义的那样，<< 运算符要求左边是一个 ostream 对象。显然，因为 cout 是 ostream 对象，所以表达式 cout << x 满足这种要求。然而，因为表达式
cout << x 位于 << y 的左侧，所以输出语句也要求该表达式是一个 ostream 类型的对象。因此，ostream 类将 operator<<() 函数实现为返回一个指向 ostream 对象
的引用。'具体地说，它返回一个指向调用对象(这里是 cout)的引用'。因此，表达式 (cout << x) 本身就是 ostream 对象 cout，从而可以位于 << 运算符的左侧。

可以对友元函数采用相同的方法。只要修改 operator<<() 函数，让它返回 ostream 对象的引用即可:

ostream & operator<<(ostream & ostream, const Time &t)
{
    os << t.hours << t.minutes << '\n';
    return os;
}

注意，返回类型是 ostream &。这意味着该函数返回 ostream 对象的引用。因为函数开始执行时，程序传递了一个对象引用给它，这样做的最终结果是，函数的返回值就是传递
给它的对象。也就是说，下面的语句:

cout << trip;

将被转换为下面的调用：

operator<<(cout,trip);

而该调用返回 cout 对象。因此，下面的语句可以正常工作：

cout << trip << 'yeah!' << '\n';


有趣的是，这个 operator<<() 版本还可用于将输出写入到文件中:

#include <fstream>

ofstream fout;
fout.open("hello.txt");
Time trip(2,12);
fout << trip;

其中最后一条语句将被转换为这样：

operator<<(fout,trip);

提示：一般来说，要重载 << 运算符来显示 c_name 的对象，可使用一个友元函数，其定义如下：

ostream & operator<<(ostream &os, const c_name &name)
{
    os << ...//display the object element
    return os;
}

mytime3.h 列出了修改后的类定义，其中包括 operator*() 和 operator<<() 这两个友元函数。它将第一个友元函数作为内联函数，因为其代码很短。


// !! 重载运算符：作为成员函数还是非成员函数

'对于很多运算符来说，可以选择使用成员函数或非成员函数来实现运算符重载'。一般来说，非成员函数应是友元函数，这样它才能直接访问类的私有数据。例如，Time 类的加法
运算符在 Time 类声明中的原型如下:

Time operator+(const Time& t) const;

这个类也可以使用下面的原型:

friend Time operator+(const Time & t1, const Time &t2);

加法运算符需要两个操作数。'对于成员函数版本来说, 一个操作数通过 this 指针隐式地传递，另一个操作数作为函数参数显式地传递'； 对于友元版本来说，两个操作数都作为
参数来传递。

这两个原型都与表达式 T2 + T3 匹配，其中 T2 和 T3 都是 Time 类型对象。也就是说，编译器将下面的语句:

T1 = T2 + T3;

转换为下面两个的任何一个:

T1 = T2.operator+(T3)
T1 = operator+(T2,T3);

'记住，在定义运算符时，必须选择其中的一种格式，而不能同时选择这两种格式'。因为这两种格式都与同一个表达式匹配，同时定义这两种格式将被视为二义性错误，导致编
译错误。


那么哪种格式最好呢？

对于某些运算符来说， 成员函数是唯一合法的选择。在其他情况下，这两种格式没有太大的区别。有时，根据类设计，使用非成员函数版本可能更好(尤其是为类定义类型转换时)。


// !! 再谈重载：一个矢量类

矢量（vector），是工程和物理中使用的一个术语，它是一个有大小和方向的量。例如，推东西时，推的效果将取决于推力的大小和推的方向。从某个方向推可能会省力，而从相
反的方向推则要费很大的劲。


// !! 类的自动转换和强制类型转换

在讨论这个问题之前，我们先来复习一下 C++ 是如何处理内置类型转换的。'将一个标准类型变量的值赋给另一种标准类型的变量时，如果这两种类型兼容，则 C++ 自动将这个
值转换为接收变量的类型'。例如，下面的语句都将导致数值类型转换:


long count = 8;
double time = 11;
int side = 3.33;

上述赋值语句都是可行的，因为在 C++ 看来，各种数值类型都表示相同的东西---一个数字，同时 C++ 包含用于进行转换的内置规则。然而，这些转换将降低精度。例如，将
 3.33 赋给 int 变量时，转换后的值为 3，丢失了 0.33。

'C++ 语言不自动转换不兼容的类型'。

例如，下面的语句是非法的，因为左边是指针类型，而右边是数字:

int *p = 10;

'虽然计算机内部可能使用整数来表示地址，但从概念上说，整数和指针完全不同'。例如，不能计算指针的平方。然而，在无法自动转换时，可以使用强制类型转换:

int *p = (int *)10;

'可以将类定义成与基本类型或另一个类相关, 使得从一种类型转换为另一种类型是有意义的'。在这种情况下，程序员可以指示 C++ 如何自动进行转换，或通过强制类型转换来
完成。

#ifndef AD456C3D_BBFF_4001_834D_691A99692B68
#define AD456C3D_BBFF_4001_834D_691A99692B68

class Stonewt
{
private:
    enum{Lbs_per_stn = 14};
    int stone; 
    double psd_left;
    double pounds;
public:
    Stonewt(double lbs);
    Stonewt(int stn, double lbs);
    Stonewt();
    ~Stonewt();
    void show_lbs() const;
    void show_stone() const;
};

#endif /* AD456C3D_BBFF_4001_834D_691A99692B68 */

对于定义类特定的常量来说，如果它们是整数，enum 提供了一种方便的途径。也可以采用下面这种方法：

static const int Lbs_per_stn = 14;

Stonewt 类有 3 个构造函数，让您能够将 Stonewt 对象初始化为一个浮点数(单位为磅)或一个整数、一个浮点数(分别代表英石和磅)。也可以创建 Stonewt 对象，
而不进行初始化:

Stonewt s1(12.21);
Stonewt s2(12,21);
Stonewt s3;

这个类并非真的需要声明构造函数，因为自动生成的默认构造函数就很好。另一方面，提供显式的声明可为以后做好准备，以防必须定义构造函数。

'在 C++ 中，接受一个参数的构造函数为将类型与该参数相同的值转换为类提供了蓝图'。

因此，下面的构造函数用于将 double 类型的值转换为 Stonewt 类型:

Stonewt(double lbs);

也就是说，可以编写这样的代码:

Stonewt cat;
cat = 19.23;

'程序将使用构造函数 Stonewt(double) 来创建一个临时的 Stonewt 对象，并将 19.6 作为初始化值'。随后，采用逐成员赋值方式将该临时对象的内容复制到 myCat 
中,这一过程称为隐式转换，因为它是自动进行的，而不需要显式强制类型转换。

然而，如果给第二个参数提供默认值，它便可用于转换int：

Stonewt(int stn, double lbs = 0);

'将构造函数用作自动类型转换函数似乎是一项不错的特性'。

然而，当程序员拥有更丰富的 C++ 经验时，将发现这种自动特性并非总是合乎需要的，因为这会导致意外的类型转换。

'因此，C++ 新增了关键字 explicit 用于关闭这种自动特性'。

也就是说，可以这样声明构造函数:

explicit Stonewt(double lbs);

这将关闭上述示例中介绍的隐式转换，但仍然允许显式转换，即显式强制类型转换:

myCat = 19.23;// invalid
myCat = Stonewt(19.23);// ok


编译器在什么时候将使用 Stonewt(double) 函数呢 ？ 

如果在声明中使用了关键字 explicit，则 Stonewt(double) 将只用于显式强制类型转换，否则还可以用于下面的隐式转换。

1. 将 Stonewt 对象初始化为 double 值时

2. 将 double 值赋给 Stonewt 对象时

3. 将 double 值传递给接受 Stonewt 参数的函数时

4. 返回值被声明为 Stonewt 的函数试图返回 double 值时

在上述任意一种情况下，使用可转换为 double 类型的内置类型时。


'函数原型化提供的参数匹配过程'，允许使用 Stonewt（double） 构造函数来转换其他数值类型。也就是说，下面两条语句都首先将 int 转换为 double，然后使用 
Stonewt（double） 构造函数。

Stonewt joc;
joc = 121;

'当且仅当转换不存在二义性时，才会进行这种二步转换'。也就是说，如果这个类还定义了构造函数 Stonewt（long），则编译器将拒绝这些语句，可能指出: int 可被转
换为 long 或 double，因此调用存在二义性。


// !!转换函数

程序 stone.cpp 将数字转换为 Stonewt 对象。可以做相反的转换吗？ 也就是说，是否可以将 Stonewt 对象转换为 double 值，就像如下所示的那样？

Stonewt st(321.12);
double host = st;// ???

可以这样做，但不是使用构造函数。'构造函数只用于从某种类型到类类型的转换。要进行相反的转换，必须使用特殊的 C++ 运算符函数——转换函数'。

转换函数是用户定义的强制类型转换，可以像使用强制类型转换那样使用它们。例如，如果定义了从 Stonewt 到 double 的转换函数，就可以使用下面的转换:

Stonewt st(321.12);
double host = double(st);// syntax #1
double host1 = (double)st;// syntax #2


也可以让编译器来决定如何做：

Stonewt well(20,3);
double star = well;

编译器发现，右侧是 Stonewt 类型，而左侧是 double 类型，因此它将查看程序员是否定义了与此匹配的转换函数。(如果没有找到这样的定义，编译器将生成错误消息，
指出无法将 Stonewt 赋给 double)


那么，如何创建转换函数呢 ？ 要转换为 typeName 类型，需要使用这种形式的转换函数












































