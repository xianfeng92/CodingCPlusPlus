
// !! 函数探幽

C++ 提供许多新的函数特性，使之有别于 C 语言。新特性包括'内联函数'、'按引用传递变量'、'默认的参数值'、'函数重载(多态)'以及'模板函数'。

// !! C++ 内联函数

'内联函数是 C++ 为提高程序运行速度所做的一项改进'。常规函数和内联函数之间的主要区别不在于编写方式，而在于 C++ 编译器如何将它们组合到程序中。
要了解内联函数与常规函数之间的区别，必须深入到程序内部。

编译过程的最终产品是可执行程序——由一组机器语言指令组成。运行程序时，操作系统将这些指令载入到计算机内存中，因此每条指令都有特定的内存地址。计算机随
后将逐步执行这些指令。有时(如有循环或分支语句时)，将跳过一些指令，向前或向后跳到特定地址。常规函数调用也使程序跳到另一个地址(函数的地址)，并在函数结
束时返回。

执行到函数调用指令时，程序将在函数调用后立即存储该指令的内存地址，并将函数参数复制到堆栈（为此保留的内存块），跳到标记函数起点的内存单元，执行函数代码
(也许还需将返回值放入到寄存器中)，然后跳回到地址被保存的指令处。来回跳跃并记录跳跃位置意味着以前使用函数时，需要一定的开销。


C++ 内联函数提供了另一种选择, '内联函数的编译代码与其他程序代码“内联”起来了'。也就是说，编译器将使用相应的函数代码替换函数调用。

对于内联代码，程序无需跳到另一个位置处执行代码，再跳回来。因此，'内联函数的运行速度比常规函数稍快，但代价是需要占用更多内存'。如果程序在 10 个不同的
地方调用同一个内联函数，则该程序将包含该函数代码的 10 个副本。

'应有选择地使用内联函数':

1. 如果执行函数代码的时间比'处理函数调用机制'的时间长，则节省的时间将只占整个过程的很小一部分

2. 如果代码执行时间很短，则内联调用就可以节省非内联调用使用的大部分时间

3. 另一方面，由于这个过程相当快，因此尽管节省了该过程的大部分时间，'但节省的时间绝对值并不大，除非该函数经常被调用'


要使用这项特性，必须采取下述措施之一:

1. 在函数声明前加上关键字 inline

2. 在函数定义前加上关键字 inline


'通常的做法是省略原型, 将整个定义（即函数头和所有函数代码）放在本应提供原型的地方'。

程序员请求将函数作为内联函数时, 编译器并不一定会满足这种要求。它可能认为该函数过大或注意到函数调用了自己(内联函数不能递归)，因此不将其作为内联函数；
而有些编译器没有启用或实现这种特性。


inline.cpp 通过内联函数 square() 演示了内联技术。'注意到整个函数定义都放在一行中，但并不一定非得这样做。然而，如果函数定义占用多行(假定没有使用
冗长的标识符)，则将其作为内联函数就不太合适'。

// inline.cpp---using a inline function
#include<iostream>

// an inline function definition
inline double square(double x){return x*x;};

int main()
{
    using namespace std;
    double a,b;
    double c = 13.0;

    a = square(5.0);
    b = square(4.5+7.5);

    cout << "a = " << a << " b = " << b << endl;
    cout << "c = " << c << endl;
    cout << " c square " << square(c++) << endl;
    cout << "Now c = " << c << endl;
    return 0;
}


尽管程序没有提供独立的原型，但 C++ 原型特性仍在起作用。'这是因为在函数首次使用前出现的整个函数定义充当了原型'。这意味着可以给 square() 传递 int
 或 long 值，将值传递给函数前，程序自动将这个值强制转换为 double 类型。


// !! 内联与宏

inline 工具是 C++ 新增的特性。'C 语言使用预处理器语句 #define 来提供宏——内联代码的原始实现'。例如,下面是一个计算平方的宏:


#define SQUARE(X) X*X

这并不是通过传递参数实现的，而是通过文本替换来实现的——X是“参数”的符号标记。

a = SQUARE(5.0); is replaced by a = 5.0 * 5.0;
b = SQUARE(4.5 + 7.5); is replaced by a = (4.5+ 7.5) * (4.5+ 7.5);

这里的目的不是演示如何编写 C 宏，而是要指出，'如果使用 C 语言的宏执行了类似函数的功能，应考虑将它们转换为 C++ 内联函数'。


// !! 引用变量

C++ 新增了一种复合类型——引用变量。引用是已定义的变量的别名(另一个名称)。

'引用变量的主要用途是用作函数的形参。通过将引用变量用作参数，函数将使用原始数据，而不是其副本'。

1. 创建引用变量

C 和 C++ 使用 & 符号来指示变量的地址。C++ 给 & 符号赋予了另一个含义，将其用来声明引用。

int rats;
int &rodents = &rats;

其中，& 不是地址运算符，而是类型标识符的一部分。

// firstref.cpp

#include<iostream>

int main()
{
    using namespace std;
    int rats = 101;
    int &rodents = rats;
    cout << "rats = " << rats << "\n";
    cout << "rodents = " << rodents << "\n";
    ++rodents;
    cout << "rats = " << rats << "\n";
    cout << "rodents = " << rodents << "\n";

    cout << "rats address is " << &rats << "\n";
    cout << "rodent address is " << &rodents << "\n";
    return 0;
}


请注意，下述语句中的 & 运算符不是地址运算符，而是将 rodents 的类型声明为 int &，即指向 int 变量的引用:

    int &rodents = rats;

但下述语句中的 & 运算符是地址运算符，其中 &rodents 表示 rodents 引用的变量的地址：

    cout << "rodent address is " << &rodents << "\n";

 » g++ --std=c++11 firstref.cpp
--------------------------------------------------------------------------------
 » ./a.out
rats = 101
rodents = 101
rats = 102
rodents = 102
rats address is 0x7ffd79b0953c
rodent address is 0x7ffd79b0953c


引用更接近 const 指针，必须在创建时进行初始化，一旦与某个变量关联起来，就将一直效忠于它。也就是说:

    int &rodents = rats;

实际上是下述代码的伪装表示：

    int * const pt = &rats;


sceref.cpp 演示了试图将 rats 变量的引用改为 bunnies 变量的引用时，将发生的情况。

// sceref.cpp

#include<iostream>

int main()
{
    using namespace std;
    int rats = 101;
    int &rodents = rats;

    cout << "rats is " << rats << "\n";
    cout << "rodents = " << rodents << "\n";
    cout << "rats address is " << &rats << "\n";
    cout << "rodents address is " << &rodents << "\n";


    int bunnies = 50;
    rodents = bunnies;

    cout << "bunnies is " << bunnies << "\n";
    cout <<"rats = " << rats << "\n";
    cout << "rodents = " << rodents << "\n";

    cout << "rodent address is " << &rodents << "\n";
    cout << "bunnies address is " << &bunnies << "\n";

    return 0;
}


 » g++ --std=c++11 sceref.cpp
--------------------------------------------------------------------------------
 » ./a.out
rats is 101
rodents = 101
rats address is 0x7ffc53e3e358
rodents address is 0x7ffc53e3e358
bunnies is 50
rats = 50
rodents = 50
rodent address is 0x7ffc53e3e358
bunnies address is 0x7ffc53e3e35c

'简而言之，可以通过初始化声明来设置引用，但不能通过赋值来设置'。

2. 将引用用作函数参数

引用经常被用作函数参数,使得函数中的变量名成为调用程序中的变量的别名。这种传递参数的方法称为按引用传递。

3. 引用的属性和特别之处

使用引用参数时，需要了解其一些特点。首先，请看 cubes.cpp, 它使用两个函数来计算参数的立方，其中一个函数接受 double 类型的参数，另一个接受 
double 引用。

// cubes.cpp

#include <iostream>

double cube(double a);
double refCube(double &ra);

int main()
{
    using namespace std;
    double x = 3.0;
    cout << cube(x);
    cout << " = cube of " << x << "\n";
    cout << refCube(x);
    cout << "= refCube of " << x << "\n";
    return 0;
}

double cube(double a)
{
    a *= a * a;
    return a;
}

double refCube(double &ra)
{
    ra *=  ra * ra;
    return ra;
}

» g++ --std=c++11 cubes.cpp 
--------------------------------------------------------------------------------
» ./a.out
27 = cube of 3
27= refCube of 27


refcube() 函数修改了 main() 中的 x 值，而cube( )没有，这提醒我们为何通常按值传递。

'如果程序员的意图是让函数使用传递给它的信息，而不对这些信息进行修改，同时又想使用引用，则应使用常量引用'。

double refCube(const double &ra);

double refCube(const double &ra)
{
    ra *=  ra * ra;
    return ra;
}

如果这样做，当编译器发现代码修改了 ra 的值时，将生成错误消息。

顺便说一句，如果要编写类似于上述示例的函数(即使用基本数值类型)，应采用按值传递的方式，而不要采用按引用传递的方式。'当数据比较大（如结构和类）时，
引用参数将很有用'。

按值传递的函数cube(), 可使用多种类型的实参。例如，下面的调用都是合法的:

double z = cube(x + 2.0);
z = cube(8.0);
int k = 10;
z = cube(k);

如果将与上面类似的参数传递给接受引用参数的函数，将会发现，传递引用的限制更严格。毕竟，如果 ra 是一个变量的别名，则实参应是该变量。下面的代码不合理，
因为表达式 x + 3.0 并不是变量:

doubel z = refCube(x + 2.0);// should not compile


// !! 临时变量、引用参数和 const

如果实参与引用参数不匹配, C++ 将生成临时变量。'当前，仅当参数为 const 引用时，C++ 才允许这样做，但以前不是这样'。

下面来看看何种情况下，C++ 将生成临时变量，以及为何对 const 引用的限制是合理的。

首先，什么时候将创建临时变量呢？ 如果引用参数是 const，则编译器将在下面两种情况下生成临时变量：

1. 实参的类型正确，但不是左值

2. 实参的类型不正确，但可以转换为正确的类型

左值是什么呢？ 左值参数是可被引用的数据对象，例如，变量、数组元素、结构成员、引用和解除引用的指针都是左值。非左值包括字面常量（用引号括起的字符串除外，
它们由其地址表示）和包含多项的表达式。

在 C 语言中，左值最初指的是可出现在赋值语句左边的实体, 但这是引入关键字 const 之前的情况。现在，常规变量和 const 变量都可视为左值，因为可通过地址访问
它们。但常规变量属于可修改的左值，而 const 变量属于不可修改的左值。


回到前面的示例。假设重新定义了 refcube()，使其接受一个常量引用参数:

    double refcube(const double &ra)
    {
        return ra * ra * ra;
    }

现在考虑下面的代码:

double side = 3.0;
double * pd = &side;
double & rd = side;

long edge = 5L;
double lens[4] = {2.0,5.0,9.0,12.3};

double c1 = refCube(side);// ra is side
double c2 = refCube(lens[2]);// ra is lens[2]
double c3 = refCube(rd);// ra is rd is side
double c4 = refCube(*pd);// ra is pd is side
double c5 = refCube(edge);// ra is temporary variable
double c6 = refCube(7.0);// ra is temporary variable
double c7 = refCube(side + 4.0); // ra is temporary variable

'参数 side、lens[2]、rd 和 *pd 都是有名称的、double 类型的数据对象，因此可以为其创建引用，而不需要临时变量'。'参数 7.0 和 side + 10.0 的类
型都正确，但没有名称，在这些情况下，编译器都将生成一个临时匿名变量，并让 ra 指向它'。这些临时变量只在函数调用期间存在，此后编译器便可以随意将其删除。


那么为什么对于常量引用，这种行为是可行的，其他情况下却不行的呢？

void swap(int &a, int &b)
{
    int temp;
    temp = a
    a = b;
    b = temp;
}

如果在早期 C++ 较宽松的规则下，执行下面的操作将发生什么情况呢？

long a =3,b = 5;
swap(a,b);

这里的类型不匹配，因此编译器将创建两个临时 int 变量，将它们初始化为 3 和 5，然后交换临时变量的内容，而 a 和 b 保持不变。


'简而言之，如果接受引用参数的函数的意图是修改作为参数传递的变量，则创建临时变量将阻止这种意图的实现'。

解决方法是，禁止创建临时变量，现在的 C++ 标准正是这样做的。


现在来看 refcube() 函数。该函数的目的只是使用传递的值，而不是修改它们，因此临时变量不会造成任何不利的影响，'反而会使函数在可处理的参数种类方面更通用'。
因此，如果声明将引用指定为 const，C++ 将在必要时生成临时变量。实际上，对于形参为 const 引用的 C++ 函数，如果实参不匹配，则其行为类似于按值传递，为
确保原始数据不被修改，将使用临时变量来存储值。

// !! 应尽可能使用 const

将引用参数声明为常量数据的引用的理由有三个：

1. 使用 const 可以避免无意中修改数据的编程错误

2. 使用 const 使函数能够处理 const 和非 const 实参，否则将只能接受非 const 数据

3. 使用 const 引用使函数能够正确生成并使用临时变量

'因此，应尽可能将引用形参声明为 const'


// !! 将引用用于结构

'引用非常适合用于结构和类(C++ 的用户定义类型)。确实，引入引用主要是为了用于这些类型的，而不是基本的内置类型'。

使用结构引用参数的方式与使用基本变量引用相同, 只需在声明结构参数时使用引用运算符 & 即可。

假设有如下结构定义:

struct free_throws{
    std::string name;
    int made;
    int attempts;
    float percent;
};


则可以这样编写函数原型，在函数中将指向该结构的引用作为参数:

void set_sc(free_throws &ft);

如果不希望函数修改传入的结构，可使用 const:

void set_sc(const free_throws &ft);

strtref.cpp 的程序正是这样做的。它还通过让函数返回指向结构的引用添加了一个有趣的特点，这与返回结构有所不同。

// strtref.cpp
#include <iostream>
#include <string>

struct free_throws
{
    std::string name;
    int made;
    int attempts;
    float percent;
};

void display(const free_throws &ft);
void set_pc(free_throws &ft);
free_throws &accumulate(free_throws &target, const free_throws & sources);

int main()
{
    // partital initializations --- remaining members set to 0
    free_throws one = {"hello",11,12};
    free_throws two = {"you",2,3};
    free_throws three = {"are",123,326};
    free_throws four = {"smart",23,32};
    free_throws five = {"too",12,21};
    free_throws team = {"xforg",12,989};

    // no initialization

    free_throws dup;

    set_pc(one);
    display(one);
    accumulate(team,one);
    display(team);

    // use return value as parameter
    display(accumulate(team,two));
    accumulate(accumulate(team,three),four);
    display(team);
    // using return as assign
    dup = accumulate(team,five);

    std::cout << "Display Team: ";
    display(team);
    std::cout << "Display dup after assignment: ";
    display(dup);
    set_pc(four);
    // ill advice assignment
    accumulate(team,five) = four;
    std::cout << "Display dup after ill advice assignment: ";
    display(dup);
    return 0;
}


void display(const free_throws &ft)
{
    using std::cout;
    cout << "Name: " << ft.name << '\n';
    cout << " Made by: " << ft.made << '\n';
    cout << "attempts: " << ft.attempts << '\n';
    cout << "Percent: " << ft.percent << '\n';
}


void set_pc(free_throws &ft)
{
    if(ft.attempts != 0)
    {
        ft.percent = 100.0f * float(ft.made)/float(ft.attempts);
    }
    else
    {
        ft.percent = 0;
    }
}


free_throws & accumulate(free_throws &target, const free_throws &sources)
{
    target.attempts += sources.attempts;
    target.made += sources.made;
    set_pc(target);
    return target;
}

 » g++ --std=c++11 strtref.cpp                    
-------------------------------------------------------------------------------------------------------------------------------
 » ./a.out      

Name: hello
 Made by: 11
attempts: 12
Percent: 91.6667
Name: xforg
 Made by: 23
attempts: 1001
Percent: 2.2977
Name: xforg
 Made by: 25
attempts: 1004
Percent: 2.49004
Name: xforg
 Made by: 171
attempts: 1362
Percent: 12.5551
Display Team: Name: xforg
 Made by: 183
attempts: 1383
Percent: 13.2321
Display dup after assignment: Name: xforg
 Made by: 183
attempts: 1383
Percent: 13.2321
Display dup after ill advice assignment: Name: xforg
 Made by: 183
attempts: 1383
Percent: 13.2321


1. 该程序首先初始化了多个结构对象。如果指定的初始值比成员少，余下的成员(这里只有 percent)将被设置为零


2. 由于 display() 显示结构的内容，而不修改它，因此这个函数使用了一个 const 引用参数。就这个函数而言，也可按值传递结构，但与复制原始结构的
   拷贝相比，使用引用可节省时间和内存

3. 函数 accumulate() 接收两个结构参数，并将第二个结构的成员 attempts 和 made 的数据添加到第一个结构的相应成员中。只修改了第一个结构，因此第
   一个参数为引用，而第二个参数为 const 引用

4. free_throws &accumulate(free_throws &target, const free_throws & sources), 如果返回类型被声明为 free_throws 而不是 free_throws &，
   上述返回语句将返回 target(也就是 team)的拷贝。但返回类型为引用，这意味着返回的是最初传递给 accumulate() 的 team 对象

5. 接下来，将 accumulate() 的返回值作为参数传递给了 display()，这意味着将 team 传递给了 display()。display() 的参数为引用，这意味着函数 display()
   中的 ft 指向的是 team，因此将显示 team 的内容。所以，下述代码：

   display(accumulate(team,two));

   与下面的代码等效：

   accumulate(team,two);
   display(team);

6. 为何要返回引用 ?

    传统返回机制与按值传递函数参数类似: 计算关键字 return 后面的表达式，并将结果返回给调用函数。从概念上说，这个值被复制到一个临时位置，而调用程序将
    使用这个值。请看下面的代码：

    double m = sqrt(16.0);
    cout << sqrt(25.0) << end

    在第一条语句中，值 4.0 被复制到一个临时位置，然后被复制给 m。在第二条语句中，值 5.0 被复制到一个临时位置，然后被传递给 cout。

    现在来看下面的语句：

    dup = accumulate(team,five);

    如果 accumulate() 返回一个结构，而不是指向结构的引用，将把整个结构复制到一个临时位置，再将这个拷贝复制给 dup。但在返回值为引用时，将直接把 
    team 复制到 dup，其效率更高。


    // !! 返回引用时需要注意的问题

    '返回引用时最重要的一点是, 应避免返回函数终止时不再存在的内存单元引用'。


7. 为何将 const 用于引用返回类型

    accumulate(team,five) = four;

    其效果如下：首先将 five 的数据添加到 dup 中，再使用 four 的内容覆盖 dup 的内容。

    '这条语句为何能够通过编译呢' ？ 

    在赋值语句中，左边必须是可修改的左值。也就是说，'在赋值表达式中，左边的子表达式必须标识一个可修改的内存块'。在这里，函数返回指向 dup 的引用，它确
    实标识的是一个这样的内存块，因此这条语句是合法的。另一方面，常规（非引用）返回类型是右值——不能通过地址访问的值。这种表达式可出现在赋值语句的右边，但不
    能出现在左边。其他右值包括字面值（如 10.0）和表达式（如 x + y）。显然，获取字面值（如10.0）的地址没有意义。
    
    '但为何常规函数返回值是右值呢？这是因为这种返回值位于临时内存单元中，运行到下一条语句时，它们可能不再存在'。

    假设您要使用引用返回值，但又不允许执行像给 accumulate() 赋值这样的操作，只需将返回类型声明为 const 引用：

    const free_throws & accumulate(free_throws &target, const free_throws & sources);

    现在返回类型为 const，是不可修改的左值，因此下面的赋值语句不合法:

    accumulate(team,five) = four;

    通过省略 const，可以编写更简短代码，但其含义也更模糊。'应避免在设计中添加模糊的特性，因为模糊特性增加了犯错的机会'。将返回类型声明为 const 
    引用，可避免您犯糊涂。然而，有时候省略 const 确实有道理。


// !! 将引用用于类对象

'将类对象传递给函数时，C++ 通常的做法是使用引用'。例如，可以通过使用引用，让函数将类 string、ostream、istream、ofstream 和 ifstream 等类的对象
作为参数。

下面来看一个例子，它使用了 string 类，并演示了一些不同的设计方案，其中的一些是糟糕的。这个例子的基本思想是，创建一个函数，它将指定的字符串加入到另
一个字符串的前面和后面。strquote.cpp 提供了三个这样的函数，然而其中的一个存在非常大的缺陷，可能导致程序崩溃甚至不无法通过编译。

// strquote.cpp
#include<iostream>
#include<string>

using namespace std;

string version1(const string &s1, const string &s2);
const string &version2(string &s1, const string &s2);
const string &version3(string &s1, const string &s2);

int main()
{
    string input;
    string copy;
    string result;

    cout << "enter a string: ";
    getline(cin, input);
    copy = input;
    cout << "Your string has entered : " << input << '\n';
    result = version1(input,"*****");
    cout << "Your string enhanced : " << result << '\n';
    cout << "Your original string : " << input << '\n';

    result = version2(input,"#####");
    cout << "Your string enhanced : " << result << '\n';
    cout << "Your original string : " << input << '\n';

    result = version3(input,"&&&&&");
    cout << "Your string enhanced : " << result << '\n';
    cout << "Your original string : " << input << '\n';

    return 0;
}


string version1(const string &s1, const string &s2)
{
    string temp;
    temp = s2+s1+s2;
    return temp;
}

const string &version2(string s1, const string &s2)// has side effects
{
    s1 += s2 + s1;
    return s1;
}

const string &version3(string &s1, const string &s2)// bad design
{
    string temp;
    temp = s2+s1+s2;
    return temp;
}


1. 将 C-风格字符串 用作 string 对象引用参数

    对于函数 version1()， 您可能注意到了很有趣的一点：该函数的两个形参(s1和s2)的类型都是 const string &，但实参（input和“***”）的类型分别是 string 
    和 const char *。由于 input 的类型为 string，因此让 s1 指向它没有任何问题。

    然而，'程序怎么能够接受将 char 指针赋给 string 引用呢'？

    1. 这里有两点需要说明。首先，string 类定义了一种 char * 到 string 的转换功能，这使得可以使用C-风格字符串来初始化 string 对象

    2. 其次是本章前面讨论过的类型为 const 引用的形参的一个属性。假设实参的类型与引用参数类型不匹配，但可被转换为引用类型，程序将创建一个正确类型的临时变量
    ，使用转换后的实参值来初始化它，然后传递一个指向该临时变量的引用



// !! 对象、继承和引用

ostream 和 ofstream 类凸现了引用的一个有趣属性。ofstream 对象可以使用 ostream 类的方法，这使得文件输入/输出的格式与控制台输入/输出相同。
简单地说，ostream 是基类（因为 ofstream 是建立在它的基础之上的），而 ofstream 是派生类（因为它是从 ostream 派生而来的）。派生类继承了基类的方法，这意味
着 ofstream 对象可以使用基类的特性，如格式化方法 precision() 和 setf()。

继承的另一个特征是，基类引用可以指向派生类对象，而无需进行强制类型转换。

filefunc.cpp 通过调用同一个函数（只有函数调用参数不同）将数据写入文件和显示到屏幕上来说明了这一点。

// filefunc.cpp
#include<iostream>
#include<fstream>
#include<cstdlib>

void file_it(ostream& os,double fo,const double fe[],int n);
const int LIMIT = 5;

int main()
{
    ofstream fout;
    const char* fn = "ep_data.txt";
    fout.open(fn);
    if(!fout.is_open())
    {
        cout << "Can't open file " << fn << '\n';
        exit(EXIT_FAILURE);
    }
    double objective;
    cout << "Enter the focal length your telescope objective in mm: ";
    cin >> objective;
    double eps[LIMIT];
    cout << "Enter the focal lengths, in mm , of " << LIMIT << " eyepieces: \n";
    for(int i = 0; i < LIMIT; i++)
    {
        cout <<"Eyepieces #" << i+1 <<'\n';
        cin >> eps[i];
    }
    file_it(fout,objective,eps,LIMIT);
    file_it(cout,objective,eps,LIMIT);
    cout << "Done!\n";
    return 0;
}

void file_it(ostream &os,double f0,const double fe[], int n)
{
    ios_base::fmtflags initial;
    initial = os.setf(ios_base::fixed);// save initial foemat state
    os.precision(0);
    os << "Focal length of objective: " << fo << " mm" << '\n';
    os.setf(ios_base::showpoint);
    os.precision(1);
    os.width(12);
    os << "f.1. eyepieces";
    os.width(15);
    os << "magnification" << endl;
    for(int i=0; i< n ; ++i)
    {
        os.width(12);
        os << fe[i];
        os.width(15);
        os << int (fo/fe[i] + 0.5);
    }
    os.setf(initial);
}

对于该程序，最重要的一点是，参数 os（其类型为 ostream &）可以指向 ostream 对象（如 cout），也可以指向 ofstream 对象（如 fout）。

该程序还演示了如何使用ostream类中的格式化方法:

1. 方法 setf() 让您能够设置各种格式化状态。例如，方法调用 setf(ios_base::fixed) 将对象置于使用定点表示法的模式; setf(ios_base::showpoint) 
   将对象置于显示小数点的模式，即使小数部分为零

2. 方法 precision() 指定显示多少位小数。所有这些设置都将一直保持不变，直到再次调用相应的方法重新设置它们

3. 方法 width() 设置下一次输出操作使用的字段宽度，这种设置只在显示下一个值时有效, 然后将恢复到默认设置.'默认的字段宽度为零，这意味着刚好能容纳下要显示的
   内容'

4. 方法 setf() 返回调用它之前有效的所有格式化设置。ios_base::fmtflags 是存储这种信息所需的数据类型名称


// !! 何时使用引用参数

使用引用参数的主要原因有两个:

1. 程序员能够修改调用函数中的数据对象

2. 通过传递引用而不是整个数据对象，可以提高程序的运行速度

当数据对象较大时（如结构和类对象），第二个原因最重要。这些也是使用指针参数的原因。


对于使用传递的值而不作修改的函数:

1. 如果数据对象很小，如内置数据类型或小型结构，则按值传递

2. 如果数据对象是数组，则使用指针，因为这是唯一的选择，并将指针声明为指向 const 的指针

3. 如果数据对象是较大的结构，则使用 const 指针或 const 引用，以提高程序的效率。这样可以节省复制结构所需的时间和空间

4. 如果数据对象是类对象，则使用 const 引用。类设计的语义常常要求使用引用，这是 C++ 新增这项特性的主要原因。

对于修改调用函数中数据的函数:

1. 如果数据对象是内置数据类型，则使用指针

2. 如果数据对象是数组，则只能使用指针

3. 如果数据对象是结构，则使用引用或指针

4. 如果数据对象是类对象，则使用引用


当然，这只是一些指导原则，很可能有充分的理由做出其他的选择。例如，对于基本类型，cin 使用引用，因此可以使用 cin>>n，而不是 cin >> &n。

// !! 默认参数

'默认参数指的是当函数调用中省略了实参时自动使用的一个值'。例如，如果将 void wow(int n) 设置成 n 有默认值为 1，则函数调用 wow() 相当于 wow(1)。
这极大地提高了使用函数的灵活性。假设有一个名为 left() 的函数，它将字符串和 n 作为参数，并返回该字符串的前 n 个字符。更准确地说，该函数返回一个指针，该指针
指向由原始字符串中被选中的部分组成的字符串。例如，函数调用 left(“theory”, 3) 将创建新字符串 “the”，并返回一个指向该字符串的指针。现在假设第二个参数的默认
值被设置为 1，则函数调用left(“theory”, 3) 仍像前面讲述的那样工作，3 将覆盖默认值。。但函数调用left(“theory”)不会出错，它认为第二个参数的值为1，并返回指
向字符串 “t” 的指针。'如果程序经常需要抽取一个字符组成的字符串，而偶尔需要抽取较长的字符串，则这种默认值将很有帮助'。

如何设置默认值呢？

'必须通过函数原型。由于编译器通过查看原型来了解函数所使用的参数数目， 因此函数原型也必须将可能的默认参数告知程序'。方法是将值赋给原型中的参数。例如，left( )
的原型如下:

char * left(const char *str, int n = 1);

您希望该函数返回一个新的字符串，因此将其类型设置为 char *；您希望原始字符串保持不变，因此对第一个参数使用了 const 限定符；您希望 n 的默认值为1，因此将这个
值赋给 n。默认参数值是初始化值，因此上面的原型将 n 初始化为 1。如果省略参数 n， 则它的值将为 1；否则，传递的值将覆盖 1。


'对于带参数列表的函数，必须从右向左添加默认值。也就是说，要为某个参数设置默认值，则必须为它右边的所有参数提供默认值':

int fun1(int i,int j = 8, int k = 12);// valid
int fun2(int i, int j = 8, int k);// invalid
int fun3(int i, int j, int k = 12);// valid

left.cpp 使用了默认参数。请注意，只有原型指定了默认值。函数定义与没有默认参数时完全相同:

» g++ --std=c++11 left.cpp
» ./a.out

Enter a string: 
hello world
hell

该程序使用 new 创建一个新的字符串, 以存储被选择的字符。一种可能出现的尴尬情况是，不合作的用户要求的字符数目可能为负。在这种情况下，函数将字符计数设置为 0,
并返回一个空字符串。另一种可能出现的尴尬情况是, 不负责任的用户要求的字符数目可能多于字符串包含的字符数，为预防这种情况，函数使用了一个组合测试:

i < n && str[i];

i < n 测试让循环复制了 n 个字符后终止。测试的第二部分——表达式 str[i]，是要复制的字符的编码, 遇到空值字符(其编码为 0)后，循环将结束。这样，while 循环将
使字符串以空值字符(\0)结束，并将余下的空间（如果有的话）设置为空值字符。

另一种设置新字符串长度的方法是， 将 n 设置为传递的值和字符串长度中较小的一个：

int len = strlen(str);
n = (n < len) ? n : len;
char *p = new char[n + 1];

'这将确保 new 分配的空间不会多于存储字符串所需的空间'。如果用户执行像 left("Hi!", 32767) 这样的调用，则这种方法很有用。第一种方法将把 "Hi!" 复制到由 32767 
个字符组成的数组中，并将除前 3 个字符之外的所有字符都设置为空值字符；第二种方法将 "Hi!" 复制到由 4 个字符组成的数组中。但由于添加了另外一个函数调用(strlen())
，因此程序将更长，运行速度将降低，同时还必须包含头文件 cstring(或 string.h)。'C 程序员倾向于选择运行速度更快、更简洁的代码，因此需要程序员在正确使用函数方面
承担更多责任'。然而， C++ 的传统是更强调可靠性。毕竟，速度较慢但能正常运行的程序，要比运行速度虽快但无法正常运行的程序好。如果调用 strlen() 所需的时间很长，则
可以让 left() 直接确定 n 和字符串长度哪个小。例如，当 m 的值等于 n 或到达字符串结尾时，下面的循环都将终止:

int m = 0;
while (m <=n && str[m] != '\0')
{
    m++;
}
char *p = new char[m + 1];

别忘了，在 str[m] 不是空值字符时，表达式 str[m] != '\0' 的结果为 true，否则为 false。由于在 && 表达式中，非零值被转换为 true，而零被转换为 false，因此
也可以这样编写这个 while 测试:

while(m <=n && str[m]);


// !!函数重载

函数多态是 C++ 在 C 语言的基础上新增的功能。默认参数让您能够使用不同数目的参数调用同一个函数，而函数多态（函数重载）让您能够使用多个同名的函数。'术语"多态"指的
是有多种形式，因此函数多态允许函数可以有多种形式'。类似地，术语"函数重载"指的是可以有多个同名的函数,因此对名称进行了重载。这两个术语指的是同一回事，但我们通常使
用函数重载。可以通过函数重载来设计一系列函数——它们完成相同的工作，但使用不同的参数列表。

重载函数就像是有多种含义的动词。例如，Piggy 小姐可以在棒球场为家乡球队助威 (root)，也可以在地里种植 (root) 菌类作物。根据上下文可以知道在每一种情况下，root 
的含义是什么。同样，C++ 使用上下文来确定要使用的重载函数版本。

'函数重载的关键是函数的参数列表---也称为函数特征标(function signature)'。

'如果两个函数的参数数目和类型相同, 同时参数的排列顺序也相同，则它们的特征标相同，而变量名是无关紧要的'。C++ 允许定义名称相同的函数，条件是它们的特征标不同。如果
参数数目或参数类型不同，则特征标也不同。例如，可以定义一组原型如下的 print() 函数:

void print(const char *str, int width);// #1
void print(double d, int width);// #2
void print(long l, int width);// #3
void print(int i, int width);// #4
void print(const char * str);// #5


使用 print() 函数时，编译器将根据所采取的用法使用有相应特征标的原型:

print("hello",15);// using #1
print("helloworld");// using #5
print(1992.05,15);// using #2

使用被重载的函数时, 需要在函数调用中使用正确的参数类型。例如，对于下面的语句:

unsigned int year = 2021;
print(year,6);// ambiguous call


print() 调用与哪个原型匹配呢？它不与任何原型匹配！没有匹配的原型并不会自动停止使用其中的某个函数，因为 C++ 将尝试使用标准类型转换强制进行匹配。如果 #2 原型是 
print() 唯一的原型，则函数调用 print(year, 6) 将把 year 转换为 double 类型。但在上面的代码中，有 3 个将数字作为第一个参数的原型，因此有 3 种转换 year 的
方式。'在这种情况下，C++ 将拒绝这种函数调用，并将其视为错误'。

一些看起来彼此不同的特征标是不能共存的。例如，请看下面的两个原型：


double cube(double x);
double cube(double &x);

您可能认为可以在此处使用函数重载，因为它们的特征标看起来不同。然而，请从编译器的角度来考虑这个问题。假设有下面这样的代码：

cout << cube(x) << endl;

参数 x 与 double x 原型和 double &x 原型都匹配，因此编译器无法确定究竟应使用哪个原型。

'为避免这种混乱，编译器在检查函数特征标时，将把类型引用和类型本身视为同一个特征标'。

匹配函数时，并不区分 const 和非 const 变量。请看下面的原型:


// !!重载引用参数

类设计和 STL 经常使用引用参数，因此知道不同引用类型的重载很有用。请看下面三个原型：

void sink(double &r1);// match modifiable value
void sank(const double &r2);// match modifiable or const value lvalue,rvalue
void sunk(double && r3);// match rvalue

左值引用参数 r1 与可修改的左值参数(如 double 变量)匹配； const 左值引用参数 r2 与可修改的左值参数、const 左值参数和右值参数(如两个 double 值的和)匹配；
最后，左值引用参数 r3 与右值匹配。注意到与 r1 或 r3 匹配的参数都与 r2 匹配。

这就带来了一个问题：如果重载使用这三种参数的函数，结果将如何？

'答案是将调用最匹配的版本'：

void staff(double &rs);
void staff(const double &rcs);
void stove(double &r1);
void stove(const double &r2);
void stove(double &&r3);

这让您能够根据参数是左值、const 还是右值来定制函数的行为:

double x = 55.5;
const double y = 32.0;
stove(x);// call staff(double &rs)
stove(y);// call staff(const double &rcs)
stove(x+y);// call stove(double &&r3)

如果没有定义函数 stove(double &&)，stove(x+y) 将调用函数 stove(const double &)。


// !! 重载示例


本章前面创建了一个 left() 函数，它返回一个指针，指向字符串的前 n 个字符。下面添加另一个 left() 函数，它返回整数的前 n 位。例如，可以使用该函数来查看被存储
为整数的、美国邮政编码的前 3 位。

该函数的整数版本编写起来比字符串版本更困难些，因为并不是整数的每一位被存储在相应的数组元素中。一种方法是，先计算数字包含多少位。将数字除以 10 便可以去掉一位，因此
可以使用除法来计算数位。更准确地说，可以用下面的循环完成这种工作：

unsigned digits = 1;
while(n /= 10)
{
    ++digits;
}

现在假设知道数字共有 5 位，并要返回前 3 位，则将这个数除以 10 后再除以 10，便可以得到所需的值。每除以 10 次就删除数字的最后一位。要知道需要删除多少位，只需将总
位数减去要获得的位数即可。例如，要获得 9 位数的前 4 位，需要删除后面的 5 位。可以这样编写代码:

ct = digits - ct;
while(ct--)
{
    num /= 10;
}
return num;


leftover.cpp 将上述代码放到了一个新的 left() 函数中。该函数还包含一些用于处理特殊情况的代码，如用户要求显示 0 位或要求显示的位数多于总位数。由于新 left() 的特
征标不同于旧的 left()， 因此可以在同一个程序中使用这两个函数。

// leftover.cpp
#include<iostream>

unsigned long left(unsigned long num, int ct);
char * left(const char * str, int n);

int main()
{
    using namespace std;
    const char * trip = "helloworld!!!";// test value
    unsigned long n = 12345678;// test value
    int i = 0;
    char *temp;
    for(int i = 0; i < 10; i++)
    {
        cout << left(n,i);
        temp = left(trip,i);
        cout << temp << '\n';
        delete[] temp;
    }
    return 0;
}


unsigned long left(unsigned long num, int ct)
{
    unsigned digits = 1;
    unsigned long n = num;
    if(ct == 0 || num == 0)
    {
        return 0;
    }
    while(n /= 10)
    {
        ++digits;
    }
    if(digits > ct)
    {
        ct = digits -ct;
        while(ct--)
        {
            num /= 10;
        }
        return num;
    }
    else
    {
        return num;
    }
}

char * left(const char * str,int n)
{
    if(n < 0)
    {
        return 0;
    }
    char *p = new char[n+1];
    int i;
    for(i = 0; i <n && str[i]; i++)
    {
        p[i] = str[i];
    }
    while(i <= n)
    {
        p[i++] = '\0';
    }
    return p;
}

» g++ --std=c++11 leftover.cpp
--------------------------------------------------------------------------------
 » ./a.out
0
1h
12he
123hel
1234hell
12345hello
123456hellow
1234567hellowo
12345678hellowor
12345678helloworl


// !! 何时使用函数重载

虽然函数重载很吸引人，但也不要滥用。'仅当函数基本上执行相同的任务，但使用不同形式的数据时，才应采用函数重载'。


// !! 什么是名称修饰

C++ 如何跟踪每一个重载函数呢？

它给这些函数指定了秘密身份。使用 C++ 开发工具中的编辑器编写和编译程序时，C++ 编译器将执行一些神奇的操作——名称修饰(name decoration)，它根据函数原型中指定
的形参类型对每个函数名进行加密。请看下述未经修饰的函数原型:

long MyFunctionFoo(int,float);

这种格式对于人类来说很适合; 我们知道函数接受两个参数(一个为 int 类型，另一个为 float 类型)，并返回一个 long 值。而编译器将名称转换为不太好看的内部表示，来描
述该接口，如下所示:


?MyFunctionFoo@@YAXH

对原始名称进行的表面看来无意义的修饰将对参数数目和类型进行编码。添加的一组符号随函数特征标而异，而修饰时使用的约定随编译器而异。


// !!  函数模板

现在的 C++ 编译器实现了 C++ 新增的一项特性——函数模板。'函数模板是通用的函数描述，也就是说，它们使用泛型来定义函数，其中的泛型可用具体的类型
(如 int 或 double)替换'。通过将类型作为参数传递给模板, 可使编译器生成该类型的函数。

由于类型是用参数表示的，因此模板特性有时也被称为参数化类型(parameterized types)。

下面介绍为何需要这种特性以及其工作原理。


在前面的程序中，定义了一个交换两个 int 值的函数。假设要交换两个 double 值，则一种方法是复制原来的代码，并用 double 替换所有的 int。如果需要交换两个 char
值，可以再次使用同样的技术。'进行这种修改将浪费宝贵的时间，且容易出错'。如果进行手工修改，则可能会漏掉一个 int。如果进行全局查找和替换(如用 double 替换 int)
时，可能将：

int x;
short interval;

转换为：

double x;
short doubleInterval;


C++ 的函数模板功能能自动完成这一过程，可以节省时间，而且更可靠。

函数模板允许以任意类型的方式来定义函数。例如，可以这样建立一个交换模板:

template <typename T> void swap(T& a, T& b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}


第一行指出要建立一个模板，并将类型命名为 T 。关键字 template 和 typename 是必需的，除非可以使用关键字 class 代替 typename。另外，必须使用尖括号。类型
名可以任意选择，只要遵守 C++ 命名规则即可；许多程序员都使用简单的名称，如 T。余下的代码描述了交换两个 T 值的算法。


模板并不创建任何函数，而只是告诉编译器如何定义函数。需要交换 int 的函数时，编译器将按模板模式创建这样的函数，并用 int 代替 T。。同样，需要交换 double 的函
数时，编译器将按模板模式创建这样的函数，并用 double 代替 T 。

要让编译器知道程序需要一个特定形式的交换函数，只需在程序中使用 Swap() 函数即可。编译器将检查所使用的参数类型，并生成相应的函数。


funtemp.cpp 演示为何可以这样做。该程序的布局和使用常规函数时相同，在文件的开始位置提供模板函数的原型，并在 main() 后面提供模板函数的定义。


#include<iostream>
template<typename T> void Swap(T& a, T& b);

int main()
{
    using namespace std;
    int i = 20;
    int j = 30;
    cout << "i = " << i << ", j = " << j << '\n';
    cout << "Using compile generate int swapper:\n";
    Swap(i, j);
    cout << "Now i = " << i << ", j = " << j << '\n';
    double x = 12.21;
    double y = 99.89;
    cout << "x = " << x << ", y = " << y << '\n';
    cout << "Using compile generate double swapper:\n";
    Swap(x, y);
    cout << "Now x = " << x << ", y = " << y << '\n';
    return 0;
}

template<typename T> void Swap(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

第一个 Swap() 函数接受两个 int 参数，因此编译器生成该函数的 int 版本。也就是说，用 int 替换所有的T，生成下面这样的定义:

void Swap(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

程序员看不到这些代码，但编译器确实生成并在程序中使用了它们。第二个 Swap() 函数接受两个 double 参数，因此编译器将生成 double 版本。也就是说，用 double 替
换 T，生成下述代码：

double Swap(double &a, double &b)
{
    double temp;
    temp = a;
    a= b;
    b = temp;
}


下面是程序的输出，从中可知，这种处理方式是可行的:

 » g++ --std=c++11 funtemp.cpp 
--------------------------------------------------------------------------------
 » ./a.out
i = 20, j = 30
Using compile generate int swapper:
Now i = 30, j = 20
x = 12.21, y = 99.89
Using compile generate double swapper:
Now x = 99.89, y = 12.21
-------------------------


注意，'函数模板不能缩短可执行程序'。对于 funtemp.cpp，最终仍将由两个独立的函数定义，就像以手工方式定义了这些函数一样。最终的代码不包含任何模板，而
只包含了为程序生成的实际函数。使用模板的好处是, 它使生成多个函数定义更简单、更可靠。

// !! 重载的模板

需要多个对不同类型使用同一种算法的函数时, 可使用模板。然而，并非所有的类型都使用相同的算法。为满足这种需求, 可以像重载常规函数定义那样重载模板定义。
和常规重载一样，被重载的模板的函数特征标必须不同。例如，twotemps.cpp 新增了一个交换模板，用于交换两个数组中的元素。原来的模板的特征标为(T &, T &)，而新模
板的特征标为(T [], T [], int)。注意，在后一个模板中，最后一个参数的类型为具体类型(int)，而不是泛型。并非所有的模板参数都必须是模板参数类型。

// twotemps.cpp

#include <iostream>

template <typename T> void Swap(T & a, T & b);// original template

template <typename T> void Swap(T *a, T *b, int n);// new template

void show(int *a);

const int LIM = 8;

int main()
{
    using namespace std;
    int i = 10,j = 20;
    cout << "Using compile generate int swapper:\n";
    Swap(i, j);// matchs original template
    cout << "Now i = " << i << ", j = " << j << '\n';
    int d1[LIM] = {0,1,2,3,4,5,6,7};
    int d2[LIM] = {10,11,12,13,14,15,16,17};
    show(d1);
    show(d2);
    Swap(d1,d2,LIM);
    cout << "Swap arrays\n";
    show(d1);
    show(d2);
    return 0;
}

template <typename T> void Swap(T & a, T & b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

template <typename T> void Swap(T *a, T *b, int n)
{
    T temp;
    for(int i = 0; i < n; i++)
    {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

void show(int *a)
{
    using namespace std;
    cout << a[0] << a[1] << "/";
    cout << a[2] << a[3] << "/";
    for(int i = 4; i < LIM; i++)
    {
        cout << a[i];
    }
    cout << endl;
}


 » g++ --std=c++11 twotemps.cpp
--------------------------------------------------------------------------------
 » ./a.out        
Using compile generate int swapper:
Now i = 20, j = 10
01/23/4567
1011/1213/14151617
Swap arrays
1011/1213/14151617
01/23/4567


// !! 模板的局限性

假设有如下模板函数：

template <typename T> void f(T a, T b)
{
    ...
}

'通常，代码假定可执行哪些操作'。例如，下面的代码假定定义了赋值，但如果 T 为数组，这种假设将不成立：

a = b;

同样，下面的语句假设定义了 <，但如果 T 为结构，该假设便不成立：

if( a < b )


另外，为数组名定义了运算符 >，但由于数组名为地址，因此它比较的是数组的地址，而这可能不是您希望的。


'总之，编写的模板函数很可能无法处理某些类型'。另一方面，有时候通用化是有意义的，但 C++ 语法不允许这样做。。例如，将两个包含位置坐标的结构相加
是有意义的，虽然没有为结构定义运算符 +。一种解决方案是，C++ 允许您重载运算符 +，以便能够将其用于特定的结构或类


// !! 显式具体化

假设定义了如下结构:

struct job
{
    char name[20];
    double salary;
    int floor;
}

另外，假设希望能够交换两个这种结构的内容。原来的模板使用下面的代码来完成交换：

temp = a;
a = b;
b = temp;


由于 C++ 允许将一个结构赋给另一个结构，因此即使 T 是一个 job 结构，上述代码也适用。然而，假设只想交换 salary 和 floor 成员，而不交换 name 成员，则
需要使用不同的代码，但 Swap() 的参数将保持不变（两个 job 结构的引用），因此无法使用模板重载来提供其他的代码。

然而，可以提供一个具体化函数定义——称为显式具体化（explicit specialization），其中包含所需的代码。当编译器找到与函数调用匹配的具体化定义时，将使用该定义，
而不再寻找模板。具体化机制随着 C++ 的演变而不断变化。下面介绍 C++ 标准定义的形式。

1. 第三代具体化(ISO/ANSI C++ 标准)

试验其他具体化方法后，C++98 标准选择了下面的方法:

    1. 对于给定的函数名，可以有'非模板函数'、'模板函数'和'显式具体化模板函数'以及它们的'重载版本'
    2. 显式具体化的原型和定义应以 template<> 打头，并通过名称来指出类型
    3. 具体化优先于常规模板，而非模板函数优先于具体化和常规模板

    下面是用于交换 job 结构的非模板函数、模板函数和具体化的原型:

    void Swap(job &a, job &b);

    template <typename T> void Swap(T & a, T & b);

    template<> void Swap<job>(job &a, job &b);

    正如前面指出的，如果有多个原型，则编译器在选择原型时，非模板版本优先于显式具体化和模板版本，而显式具体化优先于使用模板生成的版本。


程序 twoswap.cpp 演示了显式具体化的工作方式。

// twoswap.cpp

#include<iostream>

template <typename T> void Swap(T & a, T & b);

struct job
{
    char name[20];
    double salary;
    int floor;
};


template<> void Swap<job>(job & a, job & b);

void Show(job &j);


int main()
{
    using namespace std;
    cout.precision(2);
    cout.setf(ios_base::fixed,ios_base::floatfield);
    int i = 10, j = 20;
    cout << " i = " << i << ", j = " << j << '\n';
    cout << "Using compile generate int swapper:\n";
    Swap(i, j);
    cout << "Now i = " << i << ", j =" << j << '\n';

    job tea = {"xiaoming",23.32,9};
    job eng = {"wangwang",33.32,10};
    cout << "Before job swapping :\n";
    Show(tea);
    Show(eng);
    Swap(tea, eng);
    cout << "After job swapping :\n"
    Show(tea);
    Show(eng);
    return 0;
}


template <typename T> void Swap( T & a, T & b)
{
    T  temp;
    temp = a
    a = b;
    b = temp;
}

template<> void Swap<job>(job & a, job & b)
{
    double t1;
    int t2;
    t1 = a.salary;
    t2 = a.floor;
    a.salary = b.salary;
    a.floor = b.floor;
    b.salary = t1;
    b.floor = t2;
}


void Show(job &j)
{
    using namespace std;
    cout << j.name << ":$" << j.salary << " on floor " << j.floor;
}



// !! 实例化和具体化

为进一步了解模板，必须理解术语实例化和具体化。'记住，在代码中包含函数模板本身并不会生成函数定义，它只是一个用于生成函数定义的方案'。
编译器使用模板为特定类型生成函数定义时, 得到的是模板实例(instantiation)。

例如，在 twoswap.cpp 中，函数调用 Swap(i, j) 导致编译器生成 Swap() 的一个实例，该实例使用 int 类型。'模板并非函数定义，但使用 int 的模板实例是函数
定义'。这种实例化方式被称为隐式实例化(implicit instantiation)，因为编译器之所以知道需要进行定义，是由于程序调用 Swap() 函数时提供了 int 参数。

最初，编译器只能通过隐式实例化，来使用模板生成函数定义，但现在 C++ 还允许显式实例化(explicit instantiation)。

这意味着可以直接命令编译器创建特定的实例，如 Swap<int>()。其语法是，声明所需的种类——用 <> 符号指示类型，并在声明前加上关键字 template：

template void Swap<int>(int, int);

实现了这种特性的编译器看到上述声明后，将使用 Swap() 模板生成一个使用 int 类型的实例。也就是说，该声明的意思是'使用 Swap() 模板生成 int 类型的函数定义'

与显式实例化不同的是，显式具体化使用下面两个等价的声明之一：

template<> void Swap<int>(int &, int &);
template<> void Swap(int &, int &);

区别在于，这些声明的意思是" 不要使用 Swap() 模板来生成函数定义，而应使用专门为 int 类型显式地定义的函数定义"。这些原型必须有自己的函数定义。显式具体化声
明在关键字 template 后包含 <>，而显式实例化没有。

还可通过在程序中使用函数来创建显式实例化。例如，请看下面的代码：

template <typename T> T add(T a, T b)// pass by value
{
    return a + b;
}


...

int m = 10;
double x = 12.23;
cout << add<double>(x,m) << endl;

这里的模板与函数调用 Add(x, m) 不匹配，因为该模板要求两个函数参数的类型相同。但通过使用 Add<double>(x, m)，可强制为 double 类型实例化，并将参数 m 强
制转换为 double 类型，以便与函数 Add<double>(double, double) 的第二个参数匹配。

隐式实例化、显式实例化和显式具体化统称为具体化（specialization）。它们的相同之处在于，它们表示的都是使用具体类型的函数定义，而不是通用描述。

引入显式实例化后，必须使用新的语法——在声明中使用前缀 template 和 template <>，以区分显式实例化和显式具体化。通常，功能越多，语法规则也越多。



// !! 编译器选择使用哪个函数版本

对于函数重载、函数模板和函数模板重载，C++ 需要（且有）一个定义良好的策略，来决定为函数调用使用哪一个函数定义，尤其是有多个参数时。这个过程称为重载解析
(overloading resolution)。详细解释这个策略将需要将近一章的篇幅，因此我们先大致了解一下这个过程是如何进行的:

1. 创建候选函数列表。其中包含与被调用函数的名称相同的函数和模板函数
2. 使用候选函数列表创建可行函数列表。这些都是参数数目正确的函数，为此有一个隐式转换序列，其中包括实参类型与相应的形参类型完全匹配的情况。例如，使用 float 
   参数的函数调用可以将该参数转换为 double，从而与 double 形参匹配，而模板可以为 float 生成一个实例

3. 确定是否有最佳的可行函数。如果有，则使用它，否则该函数调用出错


考虑只有一个函数参数的情况，如下面的调用：

may('B');

1. 首先，编译器将寻找候选者，即名称为 may() 的函数和函数模板。。例如，下面的函数符合要求，因为其名称与被调用的函数相同，且可只给它们传递一个参数：

void may(int x);// #1
float may(float x, float y = 10);// #2
void may(char ch);// #3
char *may(const char *);// #4
char may(char &);// #5
template <typename T> void may(T &);// #6
template <typename T> void may(T *);// #7


1. 注意，只考虑特征标，而不考虑返回类型。其中的两个候选函数（#4和#7）不可行，因为整数类型不能被隐式地转换（即没有显式强制类型转换）为指针类型

2. 剩余的一个模板可用来生成具体化，其中 T 被替换为 char 类型。这样剩下 5 个可行的函数，其中的每一个函数，如果它是声明的唯一一个函数，都可以被使用


接下来, 编译器必须确定哪个可行函数是最佳的。'它查看为使函数调用参数与可行的候选函数的参数匹配所需要进行的转换'。

通常，从最佳到最差的顺序如下所述:

1. 完全匹配，但常规函数优先于模板
2. 提升转换(例如，char 和 shorts 自动转换为 int，float 自动转换为 double)
3．标准转换( 例如，int 转换为 char，long 转换为 double)
4．用户定义的转换，如类声明中定义的转换。

例如，函数 #1优于函数 #2，因为 char 到 int 的转换是提升转换，而 char 到 float 的转换是标准转换。函数#3、函数#5和函数 #6都优于函数 #1和 #2，因为它们都
是完全匹配的。#3 和 #5 优于 #6，因为 #6 函数是模板。

这种分析引出了两个问题。什么是完全匹配？

如果两个函数（如#3和#5）都完全匹配，将如何办呢？ 通常，有两个函数完全匹配是一种错误，但这一规则有两个例外。显然，我们需要对这一点做更深入的探讨。

// !! 完全匹配和最佳匹配

然而，有时候，即使两个函数都完全匹配，仍可完成重载解析。首先，指向非 const 数据的指针和引用优先与非 const 指针和引用参数匹配。


'简而言之，重载解析将寻找最匹配的函数'。如果只存在一个这样的函数，则选择它；如果存在多个这样的函数，但其中只有一个是非模板函数，则选择该函数；如果存在多个
适合的函数，且它们都为模板函数，但其中有一个函数比其他函数更具体，则选择该函数。如果有多个同样合适的非模板函数或模板函数，但没有一个函数比其他函数更具体，则
函数调用将是不确定的，因此是错误的；当然，如果不存在匹配的函数，则也是错误。



// !! 模板函数的发展

在 C+ +发展的早期，大多数人都没有想到模板函数和模板类会有这么强大而有用，它们甚至没有就这个主题发挥想象力。但聪明而专注的程序员挑战模板技术的极限，阐述了各
种可能性。根据熟悉模板的程序员提供的反馈，C++98 标准做了相应的修改，并添加了标准模板库。

从此以后，模板程序员在不断探索各种可能性，并消除模板的局限性。C++11 标准根据这些程序员的反馈做了相应的修改。


1. 是什么类型

在 C++98 中，编写模板函数时，一个问题是并非总能知道应在声明中使用哪种类型。请看下面这个不完整的示例：

template<class T1, class T2> void f(T1 x, T2 y)
{
    ...
    ?type? xpy = x + y;
    ...
}

xpy 应为什么类型呢？

由于不知道 ft() 将如何使用，因此无法预先知道这一点。正确的类型可能是 T1、T2 或其他类型。例如，T1 可能是double，而 T2 可能是 int，在这种情况下，两个变量的
和将为 double 类型。T1 可能是 short，而 T2 可能是 int，在这种情况下，两个变量的和为 int 类型。T1 还可能是 short，而 T2 可能是 char，在这种情况下，加法
运算将导致自动整型提升，因此结果类型为 int。。因此，在 C++98 中，没有办法声明 xpy 的类型。


2. 关键字 decltype（C++11）

C++11 新增的关键字 decltype 提供了解决方案。可这样使用该关键字：

int x;
decltype(x)y;// make y the same type as x

给 decltype 提供的参数可以是表达式，因此在前面的模板函数 ft() 中，可使用下面的代码：

decltype(x+y) xpy; // make xpy the same type as x+y

另一种方法是，将这两条语句合而为一：

decltype(x+y)xpy = x + y;

因此，可以这样修复前面的模板函数 ft():

template<class T1, class T2> void f(T1 x, T2 y)
{
    ...
    decltype(x+y) xpy = x + y;
    ...
}

decltype 比这些示例演示的要复杂些。为确定类型，编译器必须遍历一个核对表。假设有如下声明：

decltype(expression) var;

则核对表的简化版如下：

1. 如果 expression 是一个没有用括号括起的标识符，则 var 的类型与该标识符的类型相同，包括 const 等限定符:

double x = 1.2;
double y = 9.87;
double &rx = x;
const double *pd;
decltype(x)w;// w is type double
decltype(rx)u;// u is type double&
decltype(pd)v;// v is type const double *


2. 如果 expression 是一个函数调用，则 var 的类型与函数的返回类型相同:

long indeed (int);
decltype(indeed(3)) m;

3.如果 expression 是一个左值，则 var 为指向其类型的引用

double xx = 4.4;
double((xx))r2 = xx;// r2 is double &


// !! 另一种函数声明语法（C++11后置返回类型）

有一个相关的问题是 decltype 本身无法解决的。请看下面这个不完整的模板函数：
 
template <class T1, class T2> ?type? gt(T1 x, T2 y)
{
    ...
    return x + y;
}

同样，无法预先知道将 x 和 y 相加得到的类型。好像可以将返回类型设置为 decltype ( x + y)，但不幸的是，此时还未声明参数 x 和 y，它们不在作用域内（编译器
看不到它们，也无法使用它们）。必须在声明参数后使用 decltype。

为此，C++ 新增了一种声明和定义函数的语法。下面使用内置类型来说明这种语法的工作原理。对于下面的原型：

double h(int x, float y);

使用新增的语法可编写成这样:

auto h(int x, float y) -> double;

这将返回类型移到了参数声明后面。'->double 被称为后置返回类型（trailing return type）'。其中 auto 是一个占位符，表示后置返回类型提供的类型，这是 C++11 
给 auto 新增的一种角色。这种语法也可用于函数定义:

通过结合使用这种语法和 decltype，便可给 gt() 指定返回类型，如下所示:

template <class T1, class T2> auto gt(T1 x, T2 y)->decltype(x+y)
{
    ...
    return x + y;
}

现在，decltype 在参数声明后面，因此 x 和 y 位于作用域内，可以使用它们。


// !! 总结

C++ 扩展了 C 语言的函数功能。通过将 inline 关键字用于函数定义，并在首次调用该函数前提供其函数定义，可以使得 C++ 编译器将该函数视为内联函数。
也就是说，'编译器不是让程序跳到独立的代码段，以执行函数，而是用相应的代码替换函数调用'。只有在函数很短时才能采用内联方式。

'引用变量是一种伪装指针，它允许为变量创建别名（另一个名称）'。引用变量主要被用作处理结构和类对象的函数的参数。通常，被声明为特定类型引用的标识符只能指
向这种类型的数据；然而，如果一个类（如 ofstream）是从另一个类（如 ostream）派生出来的，则基类引用可以指向派生类对象。

C++ 原型让您能够定义参数的默认值。如果函数调用省略了相应的参数，则程序将使用默认值。

函数的特征标是其参数列表。程序员可以定义两个同名函数，只要其特征标不同。这被称为函数多态或函数重载。通常，'通过重载函数来为不同的数据类型提供相同的服务'。


函数模板自动完成重载函数的过程。只需使用泛型和具体算法来定义函数，'编译器将为程序中使用的特定参数类型生成正确的函数定义'。

