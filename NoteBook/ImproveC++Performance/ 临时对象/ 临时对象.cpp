
// !! 临时对象

性能问题有很多种，它们的重要性不尽相同。'性能问题的重要程度与它本身的成本和它在特定程序中出现的频率成正比'。

即使不了解虚继承的复杂性及其对执行速度的(微小)影响，也同样可以编写出高效的 C++ 代码。然而，临时对象的产生对性能而言绝不是潜在的微小影响。'如果不理解临时对象的
起源、开销，以及如何在适当的时候消除它, 就很难写出高效的代码'。

刚入门的 C++ 开发者可能觉得临时对象常常突然在程序中冒出来，因为编译器总是悄无声息地生成临时对象，并且它不出现在源代码中。只有经过训练的开发者才能探查出使编译器
秘密插入临时对象的代码段。

// !! 对象定义

class Rational
{
friend Rational operator+(const Rational&, const Rational&);
public:
    Rational(int a = 0, int b = 1):m(a),n(b){}

private:
    int m, n;
};

我们可以通过下面几种等价的方法来实例化 Rational 对象:

Rational r1(100);// 1
Rational r2 = Rational(100);// 2
Rational r3 = 100;// 3

'只有第一种初始化形式可以保证在编译器的执行过程中不产生临时对象'。如果使用第 2 或第 3 种形式，很可能产生临时对象，这依赖于编译器的实现。

例如第 3 种形式:

Rational r3 = 100;

这种形式可能会使编译器通过构造函数 Rational::Rational(int，int) 将整数 100 放入一个 Rational 类型的临时对象中，然后利用拷贝构造函数以及新创建的临时对象
去初始化 r3:

{// C++ 伪代码
    Rational r3;
    Rational _temp;
    _temp.Rational::Rational(100,1);
    r3.Rational::Rational(_temp);
    _temp.Rational::~Rational();
} 


此处的所有代价是两个构造函数和一个析构函数。

在第 1 种形式中：

Rational r1(100);// 1

只需花费一个构造函数的代价。

然而实际上，'大多数编译器会通过优化省去临时对象，所以此处给出的 3 种初始化形式在效率上是等价的'。



// !! 类型不匹配

'类型不匹配的一般情况是指当需要 X 类型的对象时提供的却是其他类型的对象。编译器需要以某种方式将提供的类型转换成要求的 X 类型'。这一过程可能会产生临时对象。

请看下面代码：

{
    Rational r;
    r = 100;
    ...
}

Rational 类没有声明接收整型参数的赋值运算符。然而编译器希望右边是 Rational 对象，这样可以按字节传给左边。'所以，编译器必须想办法将我们提供的整型参数转换成
Rational 对象'。幸运的是(对性能来说是不幸的)，我们有构造函数知道如何实现:

class Rational
{
// 如果只提供一个整数，第二个参数将默认设置为 1
friend Rational operator+(const Rational&, const Rational&);
public:
    Rational(int a = 0, int b = 1):m(a),n(b){}

private:
    int m, n;
};


构造函数知道如何根据一个整型参数创建 Rational 对象。

源语句

r = 100;

转换成下面的 C++ 伪代码:

Rational _temp;
_temp.Rational::Rational(100);
r.Rational::operator(_temp);
_temp.Rational::~Rational();


'为了易于编程，编译器可以自由地转换类型'。但源代码中有些地方的性能要比方便性更重要。

新的 C++ 标准允许我们限制编译器禁止这种转换。这一点可以通过声明构造函数为 explicit 来实现:


class Rational
{
friend Rational operator+(const Rational&, const Rational&);
public:
    explict Rational(int a = 0, int b = 1):m(a),n(b){}

private:
    int m, n;
};

'关键字 explicit 告诉编译器，我们反对将构造函数用做转换构造函数'。


另一种方法是重载函数 Rational::operator=() 以接收整数参数，从而消除临时对象:

class Rational
{
friend Rational operator+(const Rational&, const Rational&);
public:
    explict Rational(int a = 0, int b = 1):m(a),n(b){}
    Rational& operator=(int a)
    {
        m = a;
        n = 1;
        return *this;
    }
private:
    int m, n;
};


同样的原理可以推广到所有的函数调用。假设 g() 是一个接收 string 引用参数的函数调用:

void g(const string &s)
{
    ...
}


除非重载 g() 让它接收 char＊ 参数，否则调用 g("message") 会生成临时的 string 对象。

void g(const char *s)
{
    ...
}

在下面的代码段中，operator+() 要求将两个 Complex 对象作为参数。因此编译器生成临时的 Complex 对象来代表常量 1.0:

Complex a, b;
...
for(int i = 0;  i < 100000; i++)
{
    a = i * b + 1.0;
}

问题在于每次循环都反复创建该临时对象。把常量表达式移到循环之外是一种简单且常见的优化方法。在语句 a = b + 1.0 中生成临时对象在每次迭代中的值都是恒定的。
这样的话，我们为什么还要一次次地算它的值呢？

下面的方法让我们一劳永逸：

Complex a, b;
Complex one(1.0);
...
for(int i = 0;  i < 100000; i++)
{
    a = i * b + one;
}


我们把临时对象转换成一个命名的 Complex 对象，虽然这样做需要一个构造函数，但是也比每次循环都重复创建临时对象划算。


// !! 按值传递

当按值传递对象时，实参对形参的初始化与下面的形式等价:

T formalArg = actualArg;

其中 T 是类的类型。

假设有某个函数 g() ，它希望被调用时其参数类型是 T:

void g(T formalArg)
{
    ...
}

g() 的典型调用可能是:

T t;
g(t);

因为存在局部参数 formalArg，g() 的激活记录在栈上设置了占位符。编译器必须复制对象 t 的内容至 g() 位于栈上的 formalArg 中。对此，一种常用的做法是生成临时
对象。

'编译器将创建 T 类型的临时对象，并且使用 t 作为输入参数来复制构造它'。然后临时对象作为实参传递给 g()。'该新创建的临时对象将按引用方式传递给 g()'。

C++ 的伪代码为:

T _temp;
_temp.T::T(t);
g(_temp);
_temp.T::~T();

创建和销毁临时对象的代价是比较高的。'倘若可以，我们应该按指针或者引用来传递对象以避免生成临时对象'。



// !! 按值返回

另一种会产生临时对象的情况是函数返回值。如果编写的函数是按值返回对象(与引用或者指针相对)，就很可能生成临时对象。

string f()
{
    string s;
    ...
    return s;
}

f() 的返回值是 string 对象。'编译器生成临时对象来存储返回值'。

例如：

string p;
...
p = f();

然后存储 f() 返回值的临时对象赋给左边的对象 p。


该运算符直观地解释了 string"+" 操作。它接收输入的两个 string 对象并返回一个新的 string 对象，该新对象表示给定的两个 string 的连接结果。该运算符的一种可
能的实现如下：

string operator+(const string &s, const string &p)
{
    char *buffer = new char[strlen(s) + strlen(p) + 1];
    std::strcpy(buffer, s.str);
    std::strcpy(buffer + p.str);
    string result(buffer);
    return result;
}


下面的代码段是 string operator+ 的一种典型调用:

{
    string s1 = "hello";
    string s2 = "world";
    string s3;
    ...
    s3 = s2 + s1;
}

其中语句 s3 = s2 + s1 触发了以下一些函数调用:

● operator+（const string&，const string&）；==> 字符串连接运算。它由 s1+s2 触发

● string::string（const char ＊）；==> 构造函数。在 operator+() 中执行 string result(buffer)会触发此函数

● string::string(const string&)；==> 我们需要一个临时对象存储 operator+() 的返回值。拷贝构造函数使用返回的 result string 时创建该临时对象

● string::～string() ；==> 在operator+() 函数退出之前，将销毁生命期限于自己函数范围内的 result string 对象

● string::operator=(const string&)；==> 调用赋值运算符，将 operator+() 生成的临时对象赋给左边的对象 s3

● string::～string（）；==> 销毁返回值使用的临时对象

'对于一条源代码而言，付出 6 个函数调用的代价是很高的'。即使它们中大多数是内联的，仍需要执行逻辑。


为什么语句 s3 = s1 + s2 在开始处产生临时对象呢？

是因为我们没有权利修改 string s3 的旧内容并用 s1 + s2 的新内容来覆盖它。赋值运算符负责把 string s3 由旧内容变为新内容。然而编译器不允许跳过 
string::operator=()，因此必须生成临时对象。但如果 s3 是没有旧内容的新对象呢？在这种情况下，就无须担心旧内容，此时编译器可以使用 s3 而不是临时对象来存储。
s1 + s2 的结果直接复制构造至 string s3 对象中。s3 取代了不再必需的临时对象。简而言之，即形式:

{
    string s1 = "hello";
    string s2 = "world";
    string s3 = s2 + s1;
}



优于以下形式:

{
    string s1 = "hello";
    string s2 = "world";
    string s3;
    ...
    s3 = s2 + s1;
}


// !! 使用 op=() 消除临时对象

在之前的讨论中，我们给编译器提供了一个已存在的对象，因此它就不会创建临时对象了。同样的思路也适用于其他场合。

假设 s3 有旧值，并且我们不必通过如下声明从头初始化 s3:

string s3 = s2 + s1;

如果是这种情况：

{
    string s1, s2, s3;
    ...
    s3 = s2 + s1;
}

我们仍然可以阻止创建临时对象。使用 string operator+=() 并重写代码，即用 += 代替 + 就可以办到。因此:

s3 = s1 + s2;

被重写成：

s3 = s1;
s3 += s2;

如果 string：：operator+=() 和 operator+() 的实现风格一致，那么这两个代码段在语义上是等价的。它们只是在性能上不同。尽管都调用了拷贝构造函数和运算符函数
，然而前者创建了临时对象而后者没有，因此后者更为高效。


// !! 要点


● 临时对象会以构造函数和析构函数的形式降低一半的性能

● 将构造函数声明为 explicit，可以阻止编译器在幕后使用类型转换

● '编译器常常创建临时对象来解决类型不匹配问题'。'通过函数重载可以避免这种情况'

● 如果可能，应尽量避免使用对象拷贝。按引用传递和返回对象

● 在 <op> 可能是“+、-、＊”或者“/”的地方，使用<op>=运算符可以消除临时对象

