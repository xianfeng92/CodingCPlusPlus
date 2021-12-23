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
Time operator*(int n) const;


// !! 友元

































