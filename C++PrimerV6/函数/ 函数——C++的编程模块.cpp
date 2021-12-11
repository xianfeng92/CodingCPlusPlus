//!! 函数——C++ 的编程模块

乐趣在于发现。仔细研究，读者将在函数中找到乐趣。。C++ 自带了一个包含函数的大型库（标准 ANSI 库加上多个 C++ 类），但真正的编程
乐趣在于编写自己的函数;

另一方面，要提高编程效率，可更深入地学习 STL 和 BOOST C++ 提供的功能。


// !! 复习函数的基本知识

来复习一下介绍过的有关函数的知识。要使用 C++ 函数，必须完成如下工作:

1. 提供函数定义

2. 提供函数原型

3. 调用函数

'库函数是已经定义和编译好的函数，同时可以使用标准库头文件提供其原型，因此只需正确地调用这种函数即可'。

例如，标准 C 库中有一个 strlen() 函数，可用来确定字符串的长度。相关的标准头文件 cstring 包含了 strlen() 和其他一些与字符串
相关的函数的原型。这些预备工作使程序员能够在程序中随意使用 strlen() 函数。

然而，创建自己的函数时，必须自行处理这 3 个方面——定义、提供原型和调用。程序 calling.cpp 用一个简短的示例演示了这 3 个步骤。

// calling.cpp
#include<iostream>

// function prototype
void simple();

int main()
{
    using namespace std;
    cout << "main will calling simple function.\n";
    // calling function
    simple();
    cout << "main is finished with function called.\n";
    return 0;
}

// function definition
void simple()
{
    using namespace std;
    cout << "I am simple function.\n";
}

执行函数 simple() 时，将暂停执行 main() 中的代码；等函数 simple() 执行完毕后，继续执行 main() 中的代码。


1. 定义函数

可以将函数分成两类：没有返回值的函数和有返回值的函数。没有返回值的函数被称为 void 函数，其通用格式如下：

void functionName(parameterList)
{
    statements;
    return;
}

其中， parameterList 指定了传递给函数的参数类型和数量

有返回值的函数将生成一个值，并将它返回给调用函数。

C++ 对于返回值的类型有一定的限制: 不能是数组，但可以是其他任何类型——整数、浮点数、指针，甚至可以是结构和对象！（有趣的是，虽然 C++
函数不能直接返回数组，但可以将数组作为结构或对象组成部分来返回）


'通常，函数通过将返回值复制到指定的 CPU 寄存器或内存单元中来将其返回'。随后，调用程序将查看该内存单元。'返回函数和调用函数必须就该
内存单元中存储的数据的类型达成一致'。

函数原型将返回值类型告知调用程序，而函数定义命令被调用函数应返回什么类型的数据。


2. 函数原型和函数调用

至此，读者已熟悉了函数调用，但对函数原型可能不太熟悉，因为它经常隐藏在 include 文件中。


// protos.cpp
#include <iostream>

void cheer(int);
double cube(double x);

int main()
{
    using namespace std;
    cheer(5);
    cout << "Give me a number: ";
    double side;
    cin >> side;
    double volume = cube(side);
    cout << "A" << side << "-foot cube has a volume of " << volume << " cube feet.\n";
    cheer(cube(2));
    return 0
}

void cheer(int x)
{
    using namespace std;
    for (int i = 0, i < x; i++)
    {
        cout << " Cheers";
    }
    cout << endl;
}

double cube(double x)
{
    return x * x * x;
}

但正如前面指出的，读者应将重点放在原型上。那么，应了解有关原型的哪些内容呢 ？ 首先，需要知道 C++ 要求提供原型的原因。其次，由于 
C++ 要求提供原型，因此还应知道正确的语法。最后，应当感谢原型所做的一切。

1. 为什么需要原型

    '原型描述了函数到编译器的接口'，也就是说，它将函数返回值的类型（如果有的话）以及参数的类型和数量告诉编译器。

    例如，请看原型将如何影响程序 protos.cpp 中下述函数调用:

    double volume = cube(side);

    1. 首先，原型告诉编译器，cube() 有一个 double 参数。如果程序没有提供这样的参数，原型将让编译器能够捕获这种错误。

    2. 其次，cube() 函数完成计算后，将把返回值放置在指定的位置——可能是 CPU 寄存器，也可能是内存中。然后调用函数将从这个位置取得返回值。
    由于原型指出了 cube() 的返回类型为 double，'因此编译器知道应检索多少个字节以及如何解释它们'。如果没有这些信息，编译器将只能进行猜
    测，而编译器是不会这样做的。

    3. 读者可能还会问，为何编译器需要原型，难道它就不能在文件中进一步查找，以了解函数是如何定义的吗 ？ 这种方法的一个问题是效率不高。
    编译器在搜索文件的剩余部分时将必须停止对 main() 的编译。一个更严重的问题是， 函数甚至可能并不在文件中。

    4. C++ 允许将一个程序放在多个文件中，单独编译这些文件，然后再将它们组合起来。在这种情况下，编译器在编译 main() 时，可能无权访问函数代码。
    如果函数位于库中，情况也将如此。 避免使用函数原型的唯一方法是，在首次使用函数之前定义它，但这并不总是可行的。另外，'C++ 的编程风格是将 
    main() 放在最前面，因为它通常提供了程序的整体结构'。


2.  原型的语法

    函数原型是一条语句，因此必须以分号结束。获得原型最简单的方法是，复制函数定义中的函数头，并添加分号。然而，函数原型不要求提供变量名，
    有类型列表就足够了。

    通常，在原型的参数列表中，可以包括变量名，也可以不包括。原型中的变量名相当于占位符，因此不必与函数定义中的变量名相同。


3.  原型的功能

    正如您看到的，'原型可以帮助编译器完成许多工作'；但它对程序员有什么帮助呢 ？它们可以极大地降低程序出错的几率。

    具体来说，原型确保以下几点：

    1. 编译器正确处理函数返回值
    2. 编译器检查使用的参数数目是否正确
    3. 编译器检查使用的参数类型是否正确。如果不正确，则转换为正确的类型


前面已经讨论了如何正确处理返回值。下面来看一看参数数目不对时将发生的情况。例如，假设进行了如下调用:

double z = cube();

如果没有函数原型，编译器将允许它通过。

'在编译阶段进行的原型化被称为静态类型检查'（static type checking）。可以看出，'静态类型检查可捕获许多在运行阶段非常难以捕
获的错误'。


// !!  函数参数和按值传递

C++ 通常按值传递参数，这意味着将数值参数传递给函数，而后者将其赋给一个新的变量。

double volume = cube(side);

其中，side 是一个变量，在前面的程序运行中，其值为 5。cube() 的函数头如下：

double cube(double x);

被调用时，该函数将创建一个新的名为 x 的 double 变量，并将其初始化为 5。这样，cube() 执行的操作将不会影响 main() 中的数据，
因为 cube() 使用的是 side 的副本，而不是原来的数据。

'用于接收传递值的变量被称为形参; 传递给函数的值被称为实参'。出于简化的目的，C++ 标准使用参数（argument）来表示实参，使用参量
（parameter）来表示形参，因此参数传递将参量赋给参数

'在函数中声明的变量（包括参数）是该函数私有的'。在函数被调用时，计算机将为这些变量分配内存；在函数结束时，计算机将释放这些变量
使用的内存。'这样的变量被称为局部变量，因为它们被限制在函数中'。




// !! 函数和数组

到目前为止，本书的函数示例都很简单，参数和返回值的类型都是基本类型。但是，'函数是处理更复杂的类型（如数组和结构）的关键'。

下面来如何将数组和函数结合在一起。


程序 arrfun1.cpp 演示如同使用数组名那样使用指针的情况。程序将数组初始化为某些值，并使用 sum_arr() 函数计算总数。注意到 
sum_arr() 函数使用 arr 时，就像是使用数组名一样。

// arrfun1.cpp
#include <iostream>

const int ArSize = 5;

int sum_arr(int arr[], int n);

int main()
{
    using namespace std;
    int cookies[ArSize] = {1,2,3,4,5,6,7,8,9};
    int sum = sum_arr(cookies,ArSize);
    cout << "Total cookies eaten : " << sum << endl;
    return 0;
}


int sum_arr(int arr[], int n)
{
    int total = 0;
    for(int i=0; i<n; i++)
    {
        total += arr[i];
    }
    return total;
}


1. 函数如何使用指针来处理数组

'在大多数情况下，C++ 和 C 语言一样，也将数组名视为指针'。C++ 将数组名解释为其第一个元素的地址：

cookies == &cookies[0]

该规则有一些例外。首先，数组声明使用数组名来标记存储位置；其次，对数组名使用 sizeof 将得到整个数组的长度（以字节为单位）

'将地址运算符 & 用于数组名时，将返回整个数组的地址，例如 &cookies 将返回一个 32 字节内存块的地址（如果 int 长 4 字节）'。


int sum = sum_arr(cookies,ArSize);

其中，cookies 是数组名，而根据 C++ 规则，cookies 是其第一个元素的地址，因此函数传递的是地址。。由于数组的元素的类型为 int，因此 cookies 
的类型必须是 int 指针，即 int *。这表明，正确的函数头应该是这样的：

int sum_arr(int *arr, int n);

其中用 int * arr 替换了 int arr[]。

这证明这两个函数头都是正确的，因为在 C++ 中，当（且仅当）用于函数头或函数原型中，int *arr 和 int arr[] 的含义才是相同的。它们都意味着 arr 
是一个 int 指针。然而，数组表示法（int arr[ ]）提醒用户，arr 不仅指向 int，还指向 int 数组的第一个 int。

'当指针指向数组的第一个元素时，本书使用数组表示法； 而当指针指向一个独立的值时，使用指针表示法'。

记住，将指针（包括数组名）加1，实际上是加上了一个与指针指向的类型的长度（以字节为单位）相等的值。 对于遍历数组而言，使用指针加法和数组
下标时等效的。




// !! 指针和const

'将 const 用于指针有一些很微妙的地方（指针看起来总是很微妙）'


可以用两种不同的方式将 const 关键字用于指针:

1. 让指针指向一个常量对象，这样可以防止使用该指针来修改所指向的值

2. 是将指针本身声明为常量，这样可以防止改变指针指向的位置


首先，声明一个指向常量的指针 pt：

int age = 39;
const int *pt = &age;

该声明指出，pt 指向一个 const int（这里为 39），因此不能使用 pt 来修改这个值。换句话来说，*pt 的值为 const 不能被修改。

现在来看一个微妙的问题。pt 的声明并不意味着它指向的值实际上就是一个常量，而只是意味着对 pt 而言，这个值是常量。

例如，pt 指向 age，而 age 不是 const。可以直接通过 age 变量来修改 age 的值，但不能使用 pt 指针来修改它。


以前我们将常规变量的地址赋给常规指针，而这里将常规变量的地址赋给指向 const 的指针。因此还有两种可能：将 const 变量的地址赋给指向 const 
的指针、将 const 的变量的地址赋给常规指针。这两种操作都可行吗？ 第一种可行，但第二种不可行。


// !!  函数和 C-风格字符串

'C-风格字符串由一系列字符组成，以空值(\0)字符结尾'。


// !! 将C-风格字符串作为参数的函数


假设要将字符串作为参数传递给函数，则表示字符串的方式有三种:

1. char数组

2. 用引号括起的字符串常量（也称字符串字面值）

3. 被设置为字符串的地址的 char 指针


但上述 3 种选择的类型都是 char 指针（准确地说是 char*），因此可以将其作为字符串处理函数的参数:


char ghost[15] = "galloping";
char *ptr = "hello";
int n1 = strlen(ghost);
int n2 = strlen(ptr);
int n3 = strlen("helloworld");


可以说是将字符串作为参数来传递，但实际传递的是字符串第一个字符的地址。这意味着字符串函数原型应将其表示字符串的形参声
明为 char * 类型。

C-风格字符串与常规 char 数组之间的一个重要区别是，'字符串有内置的结束字符（但不以空值字符结尾的 char 数组只是数组，而不是字符串）'。这
意味着不必将字符串长度作为参数传递给函数，而函数可以使用循环依次检查字符串中的每个字符，直到遇到结尾的空字符(\0)为止。

// strgfun.cpp

#include<iostream>

unsigned int c_in_str(const char *str,char ch);

int main()
{
    using namespace std;
    char mmm[15] = "minimum";
    char *wail = "ululate";
    unsigned int ms = c_in_str(mmm,'m');
    unsigned int us = c_in_str(mmm,'u');

    cout << ms << " m character in " << mmm << endl;
    cout << us << " u character in " << us << endl;
    return 0;
}


unsigned int c_in_str(const char * str, char ch)
{
    unsigned int count = 0;
    while(*str)
    {
        if(*str == ch)
        ++count;
    ++str;
    }
    return count;
}

c_int_str() 函数不应修改原始字符串，因此它在声明形参 str 时使用了限定符 const。这样，如果 c_int_str() 函数修改了字符串的内容，
编译器将捕获这种错误。当然，可以在函数头中使用数组表示法，而不声明 str:

unsigned int c_in_str(const char str[], char ch);


然而，使用指针表示法提醒读者注意，参数不一定必须是数组名，也可以是其他形式的指针。

该函数本身演示了处理字符串中字符的标准方式：

while(*str)
{
    statements;
    ++str;
}

str 最初指向字符串的第一个字符，因此 *str 表示的是第一个字符。例如，第一次调用该函数后，*str 的值将为 m——“minimum” 的第一
个字符。只要字符不为空值字符（\0），*str 就为非零值，因此循环将继续。str++ 将指针增加一个字节，使之指向字符串中的下一个字符。
最终，str 将指向结尾的空值字符，使得 *str 等于0——空值字符的数字编码，从而结束循环。


// !!  返回 C-风格字符串的函数

现在，假设要编写一个返回字符串的函数。是的，函数无法返回一个字符串，但可以返回字符串的地址，这样做的效率更高。

例如，strgback.cpp 定义了一个名为 buildstr() 的函数，该函数返回一个指针。该函数接受两个参数：一个字符和一个数字。函数使用 new 创建
一个长度与数字参数相等的字符串，然后将每个元素都初始化为该字符。然后，返回指向新字符串的指针。

// strgback.cpp
#include<iostream>

char * buildstr(char ch, int n);

int main()
{
    using namespace std;
    int times = 0;
    char ch;
    cout << "Enter a character: ";
    cin >> ch;
    cout << "Enter a integer: ";
    cin >> times
    char *pt = buildstr(ch, times);
    cout << pt << endl;
    delete [] pt;
    pt = buildstr('+', 20);
    cout << pt << "-DONE-" << pt << endl;
    delete [] pt;
    return 0;
}


char * buildstr(char ch, int n)
{
    char *pstr = new char[n+1];
    pstr[n] = '\0';
    while(n-- > 0)
    {
        pstr[n] = ch;
    } 
    return pstr;
}

'要创建包含 n 个字符的字符串，需要能够存储 n + 1 个字符的空间，以便能够存储空值字符'。因此，buildstr 函数请求分配 n + 1 个字节的内存来
存储该字符串，并将最后一个字节设置为空值字符(\0)，然后从后向前对数组进行填充。


注意，'变量 pstr 的作用域为 buildstr 函数内，因此该函数结束时，pstr（而不是字符串）使用的内存将被释放'。但由于函数返回了 pstr 的值，因此程序
仍可以通过 main() 中的指针 pt 来访问新建的字符串。


// !! 函数和结构

现在将注意力从数组转到结构。为结构编写函数比为数组编写函数要简单得多。

虽然结构变量和数组一样，都可以存储多个数据项，但在涉及到函数时，'结构变量的行为更接近于基本的单值变量'。也就是说，与数组不同，'结构将其数据组合成
单个实体或数据对象，该实体被视为一个整体'。

前面讲过，可以将一个结构赋给另外一个结构。同样，也可以按值传递结构，就像普通变量那样。在这种情况下，函数将使用原始结构的副本。另外，函数也可以
返回结构。与数组名就是数组第一个元素的地址不同的是，结构名只是结构的名称，要获得结构的地址，必须使用地址运算符 &。

'使用结构编程时，最直接的方式是像处理基本类型那样来处理结构'; 也就是说，将结构作为参数传递，并在需要时将结构用作返回值使用。然而，按值传递结构有一
个缺点。'如果结构非常大，则复制结构将增加内存要求，降低系统运行的速度'。出于这些原因（同时由于最初 C 语言不允许按值传递结构），许多 C 程序员倾向于
传递结构的地址，然后使用指针来访问结构的内容。


定义结构的工作很简单：

struct travel_time {
    int hour;
    int minute;
};

接下来，看一下返回两个这种结构的总和的 sum() 函数的原型。返回值的类型应为 travel_time，两个参数也应为这种类型。因此，原型应如下所示:

travel_time sum(travel_time t1, travel_time t2);

要将两个时间相加，应首先将分钟成员相加。然后通过整数除法（除数为60）得到小时值，通过求模运算符 （%） 得到剩余的分钟数。sum() 函数中使用了这种计算
方式，并使用 show_time() 函数显示 travel_time 结构的内容。


// travel.cpp
#include<iostream>

struct travel_time {
    int hour;
    int minute;
};

const int Minis_per_hour = 60;

travel_time sum(travel_time t1, travel_time t2);

void show_time(travel_time t);

int main()
{
    using namespace std;
    travel_time day1 = {2,3};
    travel_time day2 = {4,5};
    travel_time trip = sum(day1, day2);
    cout << "two days total:\n";
    show_time(trip);
    travel_time day3 = {5,2};
    cout << "three days total:\n";
    travel_time sum3 = sum(day3,trip);
    show_time(sum3);
    return 0;
}

travel_time sum(travel_time t1, travel_time t2)
{
    travel_time total;
    total.minute = (t1.minute + t2.minute) % Minis_per_hour;
    total.hour = (t1.hour + t2.hour) + (t1.minute + t2.minute)/Minis_per_hour;
    return total;
}

void show_time(travel_time t)
{
    using namespace std;
    cout << t.hour << " hours, " << t.minute << " minite " << endl;
}


// !! 函数和 string 对象

虽然 C-Style string和 string 对象的用途几乎相同，但与数组相比，string 对象与结构的更相似。

例如，可以将一个结构赋给另一个结构，也可以将一个 string 对象赋给另一个 string 对象。可以将结构作为完整的实体传递给函数，也可以将 string 对象
作为完整的实体进行传递。如果需要多个字符串，可以声明一个 string 对象数组，而不是二维 char 数组。



程序 topfive.cpp 提供了一个小型示例，它声明了一个 string 对象数组，并将该数组传递给一个函数以显示其内容。

// topfive.cpp
#include<iostream>
#include<string>

using namespace std;

const int SIZE = 5;

void display(const string str[], int n);

int main()
{
    string list[SIZE];// a array holds five string object
    cout << "Enter your " << SIZE << "favorite astronomical sights:\n";
    for(int i=0; i<SIZE; i++)
    {
        cout << i + 1 << ":";
        getline(cin, list[i]);
    }
    cout << "Your list is: ";
    display(list, SIZE);
    return 0;
}

void display(const string str[], int n)
{
    for(int i=0; i<n; i++)
    {
        cout << i + 1 << ":" << str[i] << endl;
    }
}


// !! 函数与array对象

'在 C++ 中，类对象是基于结构的，因此结构编程方面的有些考虑因素也适用于类'。例如，可按值将对象传递给函数，在这种情况下，函数处理的是原始
对象的副本。另外, 也可传递指向对象的指针，这让函数能够操作原始对象。下面来看一个使用 C++11 模板类 array 的例子。

假设您要使用一个 array 对象来存储一年四个季度的开支：

array<double,4> expenses;

要使用 array 类，需要包含头文件 array，而名称 array 位于名称空间 std 中。如果函数来显示 expenses 的内容，可按值传递 expenses：

show(expenses);

但如果函数要修改对象 expenses，则需将该对象的地址传递给函数:

fill(&expenses);

如何声明这两个函数呢？ expenses 的类型为 array<double, 4>，因此必须在函数原型中指定这种类型:

void show(std::array<double, 4> da);
void fill(std::array<double, 4> * pa);


// arrobj.cpp
#include<iostream>
#include<array>
#include<string>

const int Seasons = 4;
const std::array<double,Seasons> snames = {"Spring","Summer","Fall","Winter"};


void fill(std::array<double,Seasons> *pa);

void show(std::array<double,Seasons> da);


void main()
{
    using namespace std;
    std::array<double,Seasons> expenses;
    fill(&expenses);
    show(expenses);
    return 0;
}


void fill(std::array<double,Seasons> *pa)
{
    using namespace std;
    for(std::size_t i = 0; i < Seasons; i++)
    {
        cout << "Enter " << pa[i] << " expenses";
        cin >> (*pa)[i];
    }
}


void show(std::array<double,Seasons> da)
{
    using namespace std;
    double total = 0.0;
    cout << "\n EXPENSES\n";
    for(std::size_t i = 0; i < Seasons; i++)
    {
        cout << da[i] << ":$ " endl;
        total += da[i];
    }
    cout << "total expenses is : " << total << endl;
}



// !!  递归

C++ 函数有一种有趣的特点——可以调用自己（然而，与 C 语言不同的是，C++ 不允许 main() 调用自己），这种功能被称为递归。尽管递归在特定
的编程（例如人工智能）中是一种重要的工具，但这里只简单地介绍一下它是如何工作的。


// !!  函数指针

'与数据项相似，函数也有地址。函数的地址是存储其机器语言代码的内存的开始地址'。通常，这些地址对用户而言，既不重要，也没有什么用处，但对程
序而言，却很有用。

例如，可以编写将另一个函数的地址作为参数的函数。这样第一个函数将能够找到第二个函数，并运行它。与直接调用另一个函数相比，这种方法很笨拙，
但'它允许在不同的时间传递不同函数的地址，这意味着可以在不同的时间使用不同的函数'。


1. 函数指针的基础知识

    首先通过一个例子来阐释这一过程。假设要设计一个名为 estimate() 的函数，估算编写指定行数的代码所需的时间，并且希望不同的程序员都将使用该
    函数。对于所有的用户来说， estimate() 中一部分代码都是相同的，该函数允许每个程序员提供自己的算法来估算时间。为实现这种目标，采用的机制
    是，将程序员要使用的算法函数的地址传递给 estimate()。为此，必须能够完成下面的工作：

    1. 获取函数的地址
    2. 声明一个函数指针
    3. 使用函数指针来调用函数



2. 获取函数的地址

'获取函数的地址很简单：只要使用函数名（后面不跟参数）即可'。也就是说，如果 think() 是一个函数，则 think 就是该函数的地址。要将函数作为参数
进行传递，必须传递函数名。一定要区分传递的是函数的地址还是函数的返回值：

process(think);
process(think());


3. 声明函数指针

'声明指向某种数据类型的指针时，必须指定指针指向的类型。同样，声明指向函数的指针时，也必须指定指针指向的函数类型'。这意味着声明应指定函数的返
回类型以及函数的特征标（参数列表）。也就是说，声明应像函数原型那样指出有关函数的信息。例如，假设 Pam leCoder 编写了一个估算时间的函数，其原
型如下:

double pam(int); // prototype

则'正确的指针类型声明如下':

double (*pf)(int);

这与 pam() 声明类似，这是将 pam 替换为了 (*pf)。由于 pam 是函数，因此 (*pf) 也是函数。而如果 (*pf) 是函数，则 pf 就是函数指针。

(*pf)(int) 意味着 pf 是一个指向函数的指针:

double (*pf)(int);

正确地声明 pf 后，便可以将相应函数的地址赋给它：

double pam(int);
double (*pf)(int);
pf = pam;

注意，pam() 的特征标和返回类型必须与 pf 相同。如果不相同，编译器将拒绝这种赋值。


现在回过头来看一下前面提到的 estimate() 函数。假设要将将要编写的代码行数和估算算法（如 pam() 函数）的地址传递给它，则其原型将如下:

estimate(int lines, double(*pf)(int));

上述声明指出，第二个参数是一个函数指针，它指向的函数接受一个 int 参数，并返回一个 double 值。要让 estimate() 使用 pam() 函数，需要
将 pam() 的地址传递给它：

estimate(50, pam);

'显然，使用函数指针时，比较棘手的是编写原型，而传递地址则非常简单'。


4. 使用指针来调用函数

现在进入最后一步，即使用指针来调用被指向的函数。线索来自指针声明。前面讲过，(*pf)扮演的角色与函数名相同，因此使用 (*pf) 时，只需将它
看作函数名即可：

double pam(int);
double (*pf)(int);
pf = pam;
doubel x = pam(4);
double y = (*pf)(50);

实际上，C++ 也允许像使用函数名那样使用 pf：

doubel y = pf(50);

第一种格式虽然不太好看，但它给出了强有力的提示——'代码正在使用函数指针'。


// !! 函数指针示例

程序 fun_ptr.cpp 演示了如何使用函数指针。它两次调用 estimate() 函数，一次传递 betsy() 函数的地址，另一次则传递 pam() 函数的地址。在第一种
情况下，estimate() 使用 betsy() 计算所需的小时数；在第二种情况下， estimate() 使用 pam() 进行计算。这种设计有助于今后的程序开发。当 Ralph 
为估算时间而开发自己的算法时，将不需要重新编写 estimate()。相反，他只需提供自己的 ralph() 函数，并确保该函数的特征标和返回类型正确即可。当然，
重新编写 estimate() 也并不是一件非常困难的工作，但同样的原则也适用于更复杂的代码。另外，函数指针方式使得 Ralph 能够修改 estimate() 的行为，
虽然他接触不到 estimate() 的源代码。

// fun_ptr.cpp
double betsy(int);
double pam(int);

void estimate(int lines, double (*pf)(int));

int main()
{
    using namespace std;
    int code = 0;
    cout << "How many lines code you read: ";
    cin >> code
    estimate(code, betsy);
    cout << "Here pams estimate: ";
    estimate(code, pam);
    return 0;
}

doubel betsy(int lines)
{
    return lines * 0.92；
}

double pam(int lines)
{
    return lines * 0.89;
}

void estimate(int lines, double (*pf)(int))
{
    (*pf)(lines);
}


// !! 深入探讨函数指针

'函数指针的表示可能非常恐怖'。 

下面通过一个示例演示使用函数指针时面临的一些挑战。首先，下面是一些函数的原型，它们的特征标和返回类型相同:

const doubel * f1(const doubel ar[], int n);
const doubel * f2(const doubel [], int n);
const doubel * f3(const doubel *, int n);

这些函数的特征标看似不同，但实际上相同。

首先，前面说过，在函数原型中，参数列表 const double ar[] 与 const double * ar 的含义完全相同。其次，在函数原型中，可以省略标识符。因此，
const double ar[] 可简化为 const double []，而 const double * ar 可简化为 const double *。因此，上述所有函数特征标的含义都相同。
另一方面，函数定义必须提供标识符，因此需要使用 const double ar[] 或 const double * ar。


接下来，假设要声明一个指针，它可指向这三个函数之一。假定该指针名为 pa，则只需将目标函数原型中的函数名替换为 (*pa)

const double *(*p1)(const double *, int n);

可在声明的同时进行初始化:

const double *(*p1)(const double *, int n) = f1;

使用 C++11 的自动类型推断功能时，代码要简单得多：

auto p2 = f2;

现在来看下面的语句:

cout << (*p1)(av, 3) << " :" << *(*p1)(av, 3) << endl;
cout << p2(av, 3) << " :" << *p2(av, 3) << endl;

鉴于需要使用三个函数，如果有一个函数指针数组将很方便。这样，将可使用 for 循环通过指针依次调用每个函数。如何声明这样的数组呢？ 显然，这种声
明应类似于单个函数指针的声明，但必须在某个地方加上 [3]，以指出这是一个包含三个函数指针的数组。问题是在什么地方加上 [3]，答案如下:

const double *(*pa[3])(const double *, int) = {f1, f2, f3};

为何将 [3] 放在这个地方呢？

pa 是一个包含三个元素的数组，而要声明这样的数组，首先需要使用 pa[3]。该声明的其他部分指出了数组包含的元素是什么样的。 运算符[]的优先级高于*，
因此 *pa[3] 表明 pa 是一个包含三个指针的数组。上述声明的其他部分指出了每个指针指向的是什么：特征标为 const double *, int，且返回类型为 
const double *的函数。因此，pa 是一个包含三个指针的数组，其中每个指针都指向这样的函数，即将 const double * 和 int 作为参数，并返回一个 
const double *。

这里能否使用 auto 呢？不能。'自动类型推断只能用于单值初始化，而不能用于初始化列表'。

如何使用它们来调用函数呢？ pa[i] 和 pb[i] 都表示数组中的指针，因此可将任何一种函数调用表示法用于它们：

const double *px = pa[0](av, 3);
const double *py = (*pb[0])(av,4);


'C++11 的目标之一是让 C++ 更容易使用，从而让程序员将主要精力放在设计而不是细节上'。自动类型推断功能表明，编译器的角色发生了改变。在 C++98 中，
编译器利用其知识帮助您发现错误，而在 C++11 中，编译器利用其知识帮助您进行正确的声明。

// !! 使用 typedef 进行简化

'除 auto 外，C++ 还提供了其他简化声明的工具'。关键字 typedef 让您能够创建类型别名：

typedef double real;// make real another name for double

这里采用的方法是，将别名当做标识符进行声明，并在开头使用关键字 typedef。

typedef const double * (*p_func)(const double *, int);// p_func now a type name
p_func p1 = f1;// p1 point to f1 function
 
使用 typedef 可减少输入量，让您编写代码时不容易犯错，并让程序更容易理解。

// !! 总结

函数是 C++ 的编程模块。要使用函数，必须提供定义和原型，并调用该函数。

函数定义是实现函数功能的代码； 函数原型描述了函数的接口： 传递给函数的值的数目和种类以及函数的返回类型。函数调用使得程序将参数传递给函数，
并执行函数的代码。'在默认情况下，C++ 函数按值传递参数'。这意味着函数定义中的形参是新的变量，它们被初始化为函数调用所提供的值。因此，'C++ 
函数通过使用拷贝，保护了原始数据的完整性'。

'C++ 将数组名参数视为数组第一个元素的地址'。从技术上讲，这仍然是按值传递的，因为指针是原始地址的拷贝，但函数将使用指针来访问原始数组的内容。
当且仅当声明函数的形参时，下面两个声明才是等价的:

typeName arr[];
typeName *arr;

这两个声明都表明，arr 是指向 typeName 的指针，但在编写函数代码时，可以像使用数组名那样使用 arr 来访问元素：arr[i]。即使在传递指针时，也可以
将形参声明为 const 指针，来保护原始数据的完整性。由于传递数据的地址时，并不会传输有关数组长度的信息，因此通常将数组长度作为独立的参数来传递。'也
可传递两个指针（其中一个指向数组开头，另一个指向数组末尾的下一个元素），以指定一个范围，就像 STL 使用的算法一样'。


'C++ 提供了 3 种表示 C-风格字符串的方法': 字符数组、字符串常量和字符串指针。

它们的类型都是 char* (char指针)，因此被作为 char* 类型参数传递给函数。'C++ 使用空值字符（\0）来结束字符串，因此字符串函数检测空值字符来确定字符
串的结尾'。

C++ 还提供了 string 类，用于表示字符串。函数可以接受 string 对象作为参数以及将 string 对象作为返回值。string 类的方法 size() 可用于判断其存储的字
符串的长度。

'C++ 处理结构的方式与基本类型完全相同，这意味着可以按值传递结构，并可将其用作函数返回类型'。然而，如果结构非常大，则传递结构指针的效率将更高，同时函数能够
使用原始数据。这些考虑因素也适用于类对象。

C++ 函数可以是递归的，也就是说，函数代码中可以包括对函数本身的调用。

'C++ 函数名与函数地址的作用相同。通过将函数指针作为参数，可以传递要调用的函数的名称'。





























