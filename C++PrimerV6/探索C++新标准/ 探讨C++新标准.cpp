// !!  探讨C++新标准

// !! 新类型

C++11 新增了类型 long long 和 unsigned long long，以支持 64 位(或更宽)的整型；新增了类型 char16_t 和 char32_t，以支持 16 位和 32 位的字符表
示;还新增了“原始”字符串。


// !! 统一的初始化

C++11 扩大了用大括号括起的列表(初始化列表)的适用范围, 使其可用于所有内置类型和用户定义的类型(即类对象)。使用初始化列表时，可添加等号 (=)，也可不添加:

int x = {5};
double y{12.21};
short quar[5] = {1,21,2,4,5};

另外, 列表初始化语法也可用于 new 表达式中:

int *ar = new int[4]{1,2,4.2};// C++ 11

创建对象时，也可使用大括号(而不是圆括号)括起的列表来调用构造函数:

#ifndef A4EF2B25_3509_4FB6_9348_21FCC2CDC562
#define A4EF2B25_3509_4FB6_9348_21FCC2CDC562

class Stump
{
private:
    int roots;
    double weight;
public:
    Stump(int r, double w):roots(r), weight(w){}
    
};

#endif /* A4EF2B25_3509_4FB6_9348_21FCC2CDC562 */


Stump s1(3,13.321);// old style
Stump s2{3,13.321};// C++ 11
Stump s3 = {3,123};// C++ 11

然而，如果类有将模板 std::initializer_list 作为参数的构造函数，则只有该构造函数可以使用列表初始化形式。


1.缩窄

'初始化列表语法可防止缩窄，即禁止将数值赋给无法存储它的数值变量'。常规初始化允许程序员执行可能没有意义的操作:

char c1 = 1.57e27;// double to char, undefined behavior 
char c2 = 237256787;// int to char, undefined behavior

然而，如果使用初始化列表语法，编译器将禁止进行这样的类型转换，即将值存储到比它“窄”的变量中:

char c1{1.57e27};// double to char, compile time error
char c2{237256787};// int to char, compile time error

但允许转换为更宽的类型。另外，只要值在较窄类型的取值范围内，将其转换为较窄的类型也是允许的:

char c1{88};// int to char, in range,allowed
double d1 = {88};// int to double,allowed


2. std::initializer_list

C++11 提供了模板类 initializer_list，可将其用作构造函数的参数。如果类有接受 initializer_list 作为参数的构造函数，则初始化列表语法就只能用于该构造
函数。列表中的元素必须是同一种类型或可转换为同一种类型。STL 容器提供了将 initializer_list 作为参数的构造函数:

vector<int> a1(10);// uninitialized vector with 10 elements
vector<int> a2{10};// initialist list with 1 elements set to 10 
vector<int> a3{1,2,3};// 3 elements set to 1, 2, and 3

头文件 initializer_list 提供了对模板类 initializer_list 的支持。这个类包含成员函数 begin() 和 end()，可用于获悉列表的范围。除用于构造函数外，还
可将 initializer_list 用作常规函数的参数:


#include <initializer_list>

double sum(std::initializer_list<double> d1);

int main()
{
    using namespace std;
    double total = sum(1,2,3);
    cout << total << endl;
    return 0;
}

double sum(std::initializer_list<double> d1)
{
    double tot = 0;
    for(auto p = d1.begin(); p != d1.end();p++)
    {
        tot += *p;
    }
    return tot;
}

// !! 声明

'C++11 提供了多种简化声明的功能，尤其在使用模板时'。

1. auto

以前，关键字 auto 是一个存储类型说明符，C++11 将其用于实现自动类型推断。这要求进行显式初始化，让编译器能够将变量的类型设置为初始值的类型:

auto maton = 12;// maton is type int
auto pt = &maton;// pt is type int *
double fm(double,int);
auto f = fm;// f is type double(*)(double,int)


关键字 auto 还可简化模板声明。例如，如果 il 是一个 std::initializer_list<double> 对象，则可将下述代码:

for(std::initializer_list<double>::iterator p = i1.begin(),p != i1.end(); p ++)
{

}

替换为如下代码:

for(auto p = d1.begin(); p != i1.end(); p ++)
{

}

2. decltype

'关键字 decltype 将变量的类型声明为表达式指定的类型'。下面的语句的含义是，让 y 的类型与 x 相同，其中 x 是一个表达式:

decltype(x) y;// y is type x

下面是几个示例：

double x;
int n;
decltype(x*n) y;// y is same type as x*n
decltype(&x) pd;// pd same as &x

这在定义模板时特别有用，因为只有等到模板被实例化时才能确定类型:

template<typename T, typename U>
void ef(T t, U u)
{
    decltype(T*U) tu;
    ...
}

其中 tu 将为表达式 TU 的类型，这里假定定义了运算 TU。例如，如果 T  为 char，U 为 short，则 tu 将为 int，这是由整型算术自动执行整型提升导致的。

decltype 的工作原理比 auto 复杂，根据使用的表达式，指定的类型可以为引用和 const。下面是几个示例:

int j = 3;
int &k = j;
const int &n = j;
decltype(n) i1;// i1 is type const int &
decltype(j) i2;// i2 is type int
decltype(k+1) i3;// i3 is type int

// !! 返回类型后置

C++11 新增了一种函数声明语法: 在函数名和参数列表后面(而不是前面)指定返回类型:

double f1(double x, int y);// translation syntax
auto f2(double, int) ->double;// new syntax, return type is double

就常规函数的可读性而言, 这种新语法好像是倒退，但让您能够使用 decltype 来指定模板函数的返回类型:

template<typename T, typename U>
auto eff(T t, U u) ->decltype(T*U)
{
    ...
}

这里解决的问题是，'在编译器遇到 eff 的参数列表前，T 和 U 还不在作用域内'，因此必须在参数列表后使用 decltype, 这种新语法使得能够这样做。


// !! 模板别名: using =

对于冗长或复杂的标识符, 如果能够创建其别名将很方便。以前, C++ 为此提供了 typedef:

typedef std::vector<std::string>::iterator itType;

C++11 提供了另一种创建别名的语法:

using itType = std::vector<std::string>::iterator;


// !! nullptr

空指针是不会指向有效数据的指针。以前，C++ 在源代码中使用 0 表示这种指针，但内部表示可能不同。这带来了一些问题，因为这使得 0 即可表示指针常量，又可表示整型
常量。'C++11 新增了关键字 nullptr，用于表示空指针；它是指针类型，不能转换为整型类型'。为向后兼容，C++11 仍允许使用 0 来表示空指针，因此表达式 nullptr
 == 0 为 true，但使用 nullptr 而不是 0 提供了更高的类型安全。例如，可将 0 传递给接受 int 参数的函数，但如果您试图将 nullptr 传递给这样的函数，编译器
 将此视为错误。因此，出于清晰和安全考虑，请使用 nullptr—如果您的编译器支持它。


// !! 智能指针

'如果在程序中使用 new 从堆(自由存储区)分配内存，等到不再需要时，应使用 delete 将其释放'。C++ 引入了智能指针 auto_ptr，以帮助自动完成这个过程。随后的编
程体验(尤其是使用 STL 时)表明，需要有更精致的机制。基于程序员的编程体验和 BOOST 库提供的解决方案，C++11 摒弃了 auto_ptr，并新增了三种智能指针 unique_ptr
、shared_ptr 和 weak_ptr。

所有新增的智能指针都能与 STL 容器和移动语义协同工作。


// !! 异常规范方面的修改

以前，C++ 提供了一种语法，可用于指出函数可能引发哪些异常:

void f501() throw(bad_dog);// can throw type bad_dog exception
void f733(long long) throw(); don't' throw a exception

与 auto_ptr 一样，C++ 编程社区的集体经验表明，异常规范的效果没有预期的好。'因此，C++11 摒弃的异常规范'。然而，标准委员会认为，指出函数不会引发异常有一
定的价值，他们为此添加了关键字 noexcept:


void f857(int) noexcept;// donot throw an exception


// !! 作用域内枚举

'传统的 C++ 枚举提供了一种创建名称常量的方式，但其类型检查相当低级'。另外，枚举名的作用域为枚举定义所属的作用域，这意味着如果在同一个作用域内定义两个枚举，
它们的枚举成员不能同名。最后，枚举可能不是可完全移植的，因为不同的实现可能选择不同的底层类型。'为解决这些问题，C++11 新增了一种枚举。这种枚举使用 class 或 
struct 定义':

enum Old{yes,no,maybe};// translational form
enum class New1{never,sometimes,often, always};// new form
enum struct New2{never,yes,maybe};// new form

'新枚举要求进行显式限定，以免发生名称冲突'。因此，引用特定枚举时，需要使用 New1::never 和 New2::never 等。


// !! 对类的修改

为简化和扩展类设计，C++11 做了多项改进。这包括允许构造函数被继承和彼此调用、更佳的方法访问控制方式以及移动构造函数和移动赋值运算符。

1. 显式转换运算符

有趣的是，C++ 很早就支持对象自动转换。'但随着编程经验的积累，程序员逐渐认识到，自动类型转换可能导致意外转换的问题'。为解决这种问题，'C++ 引入了关键字 
explicit，以禁止单参数构造函数导致的自动转换':

class Plebe
{
    Plebe(int);// automatically int to plebe convention
    explicit Plebe(double);// require explicit use
    ...
}；

Plebe a, b;
a = 5;// implicit conversion, call Plebe(5)
b = 0.5; // not allowed
b = Plebe(0.5); // explicit conversion

'C++11 拓展了 explicit 的这种用法，使得可对转换函数做类似的处理':

class Plebe
{
    Plebe(int);// automatically int to plebe convention
    explicit Plebe(double);// require explicit use

    operator int() const;
    explicit operator double() const;
    ...
}；

...

Plebe a, b;
int n = a;// Plebe to int auto conversion
double x = b;// not allowed
x = double(b);// explicit conversion, allowed


2. '类内成员初始化'

很多首次使用 C++ 的用户都会问：“为何不能在类定义中初始化成员？”

现在可以这样做了，其语法类似于下面这样:

class Session
{
private:
    int mem1 = 10;
    double mem2{12321};
    short mem3;
public:
    Session();
    Session(short s):mem3(s) {}
    Session(int n, double d, short s):mem1(n), mem2(d), mem3(s){}
    ...
};

'使用类内初始化可避免在构造函数中编写重复的代码, 从而减少程序员的工作量、厌倦情绪和出错的机会'。如果构造函数在成员初始化列表中提供了相应的值，这些默认值
将被覆盖, 因此第三个构造函数覆盖了'类内成员初始化'。

// !! 模板和 STL 方面的修改

为改善模板和标准模板库的可用性，C++11 做了多个改进; 有些是库本身，有些与易用性相关。

1. 基于范围的 for 循环

对于内置数组以及包含方法 begin() 和 end() 的类(如 std::string)和 STL 容器，'基于范围的 for 循环可简化为它们编写循环的工作'。

这种循环对数组或容器中的每个元素执行指定的操作:

double prices[5] = {0.0, 1.0, 2.0, 3.0,42.3};
for(double x: prices)
{
    std::cout << x << std::endl;
}

其中，x 将依次为 prices 中每个元素的值。x 的类型应与数组元素的类型匹配。一种更容易、更安全的方式是，使用 auto 来声明 x，这样编译器将根据 prices 声明中
的信息来推断 x 的类型:

double prices[5] = {0.0, 1.0, 2.0, 3.0,42.3};
for(auto x: prices)
{
    std::cout << x << std::endl;
}

如果要在循环中修改数组或容器的每个元素, 可使用引用类型:

std::vector<int> vi(6);
for(auto &x: vi)
{
    x = std::rand();
}


2. 新的 STL 容器

C++11 新增了 STL 容器 forward_list、unordered_map、unordered_multimap、unordered_set 和 unordered_multiset。容器 forward_list 是一种单向
链表，只能沿一个方向遍历；与双向链接的 list 容器相比，它更简单，在占用存储空间方面更经济。其他四种容器都是使用哈希表实现的。

C++11 还新增了模板 array 。要实例化这种模板，可指定元素类型和固定的元素数：

std::array<int,360> ar;// array of 360 ints

这个模板类没有满足所有的常规模板需求。例如，由于长度固定，您不能使用任何修改容器大小的方法，如 put_back()。但 array 确实有方法 begin()和end()，这让您能
够对 array 对象使用众多基于范围的 STL 算法。


3. 新的 STL 方法

C++11 新增了 STL 方法 cbegin()和cend()。与 begin()和 end()一样，这些新方法也返回一个迭代器，指向容器的第一个元素和最后一个元素的后面，因此可用于指定
包含全部元素的区间。'另外，这些新方法将元素视为 const'。


4. valarray 升级

模板 valarray 独立于 STL 开发的，其最初的设计导致无法将基于范围的 STL 算法用于 valarray 对象。C++11 添加了两个函数（begin( )和end( )），它们都接受
valarray 作为参数，并返回迭代器，这些迭代器分别指向 valarray 对象的第一个元素和最后一个元素后面。


5. 摒弃 export

C++98 新增了关键字 export，旨在提供一种途径，让程序员能够将模板定义放在接口文件和实现文件中，其中前者包含原型和模板声明，而后者包含模板函数和方法的定义。
实践证明这不现实，因此 C++11 终止了这种用法，但仍保留了关键字 export，供以后使用。

6. 尖括号

为避免与运算符 >> 混淆，C++ 要求在声明嵌套模板时使用空格将尖括号分开:

std::vector<std::list<int> > v1; // >> not ok

C++11 不再这样要求：

std::vector<std::list<int>> v1; // >> ok in C++ 11


// !! 右值引用

传统的 C++ 引用(现在称为左值引用)使得标识符关联到左值。左值是一个表示数据的表达式(如变量名或解除引用的指针)，程序可获取其地址。最初，左值可出现在赋值语句
的左边，但修饰符 const 的出现使得可以声明这样的标识符，即不能给它赋值，但可获取其地址:

int n;
int *pt = new int;
const int b = 101;
int &rn = n;
int &rt = *pt;
const int &rb = b;

'C++11 新增了右值引用，这是使用 && 表示的'。右值引用可关联到右值，即可出现在赋值表达式右边，但不能对其应用地址运算符的值。右值包括字面常量(C-风格字符串除
外，它表示地址)、诸如 x + y 等表达式以及返回值的函数(条件是该函数返回的不是引用):

int x = 10;
int y = 23;
int &&r1 = 13;
int &&r2 = x + y;
double &&r3 = std::sqrt(2.0);

注意，r2 关联到的是当时计算 x + y 得到的结果。也就是说，r2 关联到的是 23，即使以后修改了 x 或 y，也不会影响到 r2。

有趣的是，'将右值关联到右值引用导致该右值被存储到特定的位置，且可以获取该位置的地址'。也就是说，虽然不能将运算符 & 用于 13，但可将其用于 r1。通过将数据与
特定的地址关联，使得可以通过右值引用来访问该数据。

'引入右值引用的主要目的之一是实现移动语义'。


// !! 移动语义和右值引用

C++11 支持移动语义，这就提出了一些问题: 什么是移动语义？ C++11 如何支持它？ 为何需要移动语义？


1. 为何需要移动语义

先来看 C++11 之前的复制过程。假设有如下代码:

vector<std::string> vstr;
// build up a vector of 20000 strings, each of 10000 characters
...
vector<std::string> vstr_copy(vstr);// make vstr_copy a copy of vstr

vector 和 string 类都使用动态内存分配，因此它们必须定义使用某种 new 版本的复制构造函数。为初始化对象 vstr_copy1，复制构造函数 vector<string> 将使用
new 给 20000 个 string 对象分配内存，而每个 string 对象又将调用 string 的复制构造函数，该构造函数使用 new 为 1000 个字符分配内存。接下来，20000000
个字符都将从 vstr 控制的内存中复制到 vstr_copy1 控制的内存中。这里的工作量很大，但只要妥当就行。

但这确实妥当吗？有时候答案是否定的。例如，假设有一个函数，它返回一个 vector<string> 对象:

vector<string> allcaps(const vector<string> &vs)
{
    vector<string> temp;
    // code the store an all-uppercase version of vs in temp
    return temp;
}

接下来，假设以下面这种方式使用它:

vector<string> vstr;
//  build up a vector of 20000 strings, each of 10000 characters 
vector<string> vstr_copy1(vstr); // #1
vector<string> vstr_copy2(allcaps(vstr)); // #2

从表面上看，语句 #1 和 #2 类似，它们都使用一个现有的对象初始化一个 vector<string> 对象。

这类似于在计算机中移动文件的情形: 实际文件还留在原来的地方，而只修改记录。这种方法被称为移动语义(move semantics)。有点悖论的是，移动语义实际上避免了移
动原始数据，而只是修改了记录。

'要实现移动语义，需要采取某种方式，让编译器知道什么时候需要复制，什么时候不需要'。

这就是右值引用发挥作用的地方。可定义两个构造函数。其中一个是常规复制构造函数，它使用 const 左值引用作为参数，这个引用关联到左值实参，如语 句#1 中的vstr；
另一个是移动构造函数，它使用右值引用作为参数，该引用关联到右值实参，如语句 #2 中 allcaps(vstr) 的返回值。'复制构造函数可执行深复制，而移动构造函数只调整
记录'。在将所有权转移给新对象的过程中，移动构造函数可能修改其实参，这意味着右值引用参数不应是const。

其中最重要的是复制构造函数和移动构造函数的定义。

首先来看复制构造函数:

Useless::Useless(const Useless & f):n(f.n)
{
    ++ct;
    cout "Copy constrctor called, number of objects " << ct << endl;
    pc = new char[n];
    for(int i = 0; i < n; i++)
    {
        pc[i] = f.pc[i];
    }
    showObject();
}

它执行深复制，是下面的语句将使用的构造函数:

Useless two = one;// copy constructor

引用 f 将指向左值对象 one。

接下来看移动构造函数:

Useless::Useless(Useless && f):n(f.n)
{
    ++ct;
    cout << "Move constrctor called, number of objects" << ct << endl;
    pc = f.pc;
    f.pc = nullptr;
    f.n = 0;
    showObject();
}

'它让 pc 指向现有的数据，以获取这些数据的所有权'。此时，pc 和 f.pc 指向相同的数据，调用析构函数时这将带来麻烦，因为程序不能对同一个地址调用 delete [] 
两次。为避免这种问题，该构造函数随后将原来的指针设置为空指针，因为对空指针执行 delete[] 没有问题。这种夺取所有权的方式常被称为窃取(pilfering)。

在下面的语句中，将使用这个构造函数：

Useless four(one + three);// move constructor

表达式 one + three 调用 Useless::operator+()，而右值引用 f 将关联到该方法返回的临时对象。


// !! 移动构造函数解析

虽然使用右值引用可支持移动语义, 但这并不会神奇地发生。要让移动语义发生，需要两个步骤。

1. 首先，右值引用让编译器知道何时可使用移动语义:

Useless two = one;// match Useless(const Useless &f);
Useless four(one + three);//match Useless(Useless &&f);

对象 one 是左值，与左值引用匹配，而表达式 one + three 是右值，与右值引用匹配。因此，'右值引用让编译器使用移动构造函数来初始化对象 four'。

2. 实现移动语义的第二步是，编写移动构造函数, 使其提供所需的行为。

总之，通过提供一个使用左值引用的构造函数和一个使用右值引用的构造函数, 将初始化分成了两组。'使用左值对象初始化对象时，将使用复制构造函数，而使用右值对象初始
化对象时，将使用移动构造函数'。程序员可根据需要赋予这些构造函数不同的行为。

在 C++98 中，下面的语句将调用复制构造函数:

Useless four(one + three);

但左值引用不能指向右值。结果将如何呢？ 如果实参为右值，const 引用形参将指向一个临时变量:

int twice(const &rv)
{
    return 2 * rv;
}

...

int main()
{
    int m = 6;
    // below, rv refers to m
    int n = twice(m);

    // below, rv refers to a temporary variable initialized 21
    int k = twice(21);
    return 0;
}

就 Useless 而言，形参 f 将被初始化一个临时对象，而该临时对象被初始化为 operator+() 返回的值。


// !! 赋值

'适用于构造函数的移动语义考虑也适用于赋值运算符'。例如，下面演示了如何给 Useless 类编写复制赋值运算符和移动赋值运算符:


// !! 强制移动

移动构造函数和移动赋值运算符使用右值。如果要让它们使用左值，该如何办呢？ 

例如，程序可能分析一个包含候选对象的数组，选择其中一个对象供以后使用，并丢弃数组。如果可以使用移动构造函数或移动赋值运算符来保留选定的对象，那该多好啊！然
而，假设您试图像下面这样做:

Useless choices[10];
Useless best;
int pick;
...// select one object, set pick to index
best = choices[pick];

由于 choices[pick] 是左值，因此上述赋值语句将使用复制赋值运算符，而不是移动赋值运算符。但如果能让 choices[pick] 看起来像右值，便将使用移动赋值运算符。
为此，可使用运算符 static_cast<> 将对象的类型强制转换为 Useless &&，'C++11 提供了一种更简单的方式—使用头文件 utility 中声明的函数 std::move()'。

'对大多数程序员来说, 右值引用带来的主要好处并非让他们能够编写使用右值引用的代码，而是能够使用利用右值引用实现移动语义的库代码'。。例如，STL 类现在都有复制
构造函数、移动构造函数、复制赋值运算符和移动赋值运算符。


// !! 新的类功能

// !! 特殊的成员函数

在原有 4 个特殊成员函数(默认构造函数、复制构造函数、复制赋值运算符和析构函数)的基础上，'C++11 新增了移动构造函数和移动赋值运算符'。这些成员函数是编译器在
各种情况下自动提供的。'在没有提供任何参数的情况下，将调用默认构造函数'。如果您没有给类定义任何构造函数，编译器将提供一个默认构造函数。这种版本的默认构造函数
被称为默认的默认构造函数。对于使用内置类型的成员，默认的默认构造函数不对其进行初始化; 对于属于类对象的成员，则调用其默认构造函数。另外，'如果您没有提供复制构
造函数, 而代码又需要使用它，编译器将提供一个默认的复制构造函数'; 如果您没有提供移动构造函数，而代码又需要使用它，编译器将提供一个默认的移动构造函数。


假定类名为 Someclass，这两个默认的构造函数的原型如下:

Someclass::Someclass(const SameClass& f);// copy constructor
Someclass::Someclass(SameClass &&f);// move constructor

在类似的情况下，编译器将提供默认的复制运算符和默认的移动运算符，它们的原型如下:

Someclass & SameClass::operator=(const Someclass &f);//copy assignment
SameClass & SameClass::operator=(SameClass &&f);// move assignment

最后，如果您没有提供析构函数，编译器将提供一个。

如果您提供了析构函数、复制构造函数或复制赋值运算符，编译器将不会自动提供移动构造函数和移动赋值运算符；如果您提供了移动构造函数或移动赋值运算符，编译器将不会
自动提供复制构造函数和复制赋值运算符。

'默认的移动构造函数和移动赋值运算符的工作方式与复制版本类似: 执行逐成员初始化并复制内置类型'。如果成员是类对象，将使用相应类的构造函数和赋值运算符，就像
参数为右值一样。如果定义了移动构造函数和移动赋值运算符，这将调用它们; 否则，将调用复制构造函数和复制赋值运算符。


// !!  默认的方法和禁用的方法

'C++11 让您能够更好地控制要使用的方法'。假定您要使用某个默认的函数，而这个函数由于某种原因不会自动创建。例如，'您提供了移动构造函数，因此编译器不会自动创
建默认的构造函数、复制构造函数和复制赋值构造函数'。在这些情况下，您可'使用关键字 default 显式地声明这些方法的默认版本':

class SameClass
{
public:
    Someclass(SameClass &&f);
    SameClass() = default;
    SameClass(const SameClass &other) = default;
    SameClass &operator=(const SameClass &other) = default;
    ...
};

编译器将创建在您没有提供移动构造函数的情况下将自动提供的构造函数。

另一方面，'关键字 delete 可用于禁止编译器使用特定方法'。

例如，要禁止复制对象，可禁用复制构造函数和复制赋值运算符:

    SameClass(const SameClass &other) = delete;
    SameClass &operator=(const SameClass &other) = delete;

'要禁止复制，可将复制构造函数和赋值运算符放在类定义的 private 部分，但使用 delete 也能达到这个目的，且更不容易犯错、更容易理解'。

如果在启用移动方法的同时禁用复制方法，结果将如何呢？ 前面说过，移动操作使用的右值引用只能关联到右值表达式，这意味着:

Someclass one;
Someclass two;
Someclass three(one);// not allowed, one is left value
Someclass four(one + two);// allowed, expression is right value


关键字 default 只能用于 6 个特殊成员函数，但 delete 可用于任何成员函数。delete 的一种可能用法是禁止特定的转换。

例如，假设 Someclass 类有一个接受 double 参数的方法：

class SameClass
{
public:
    void redo(double);
    ...
};

再假设有如下代码：

Someclass sc;
sc.redo(5);

int 值 5 将被提升为 5.0，进而执行方法 redo()。


现在假设将 Someclass 类的定义改成了下面这样：

class SameClass
{
public:
    void redo(double);
    void redo(int) = delete;
    ...
};

在这种情况下，方法调用 sc.redo(5) 与原型 redo(int) 匹配。编译器检测到这一点以及 redo(int) 被禁用后，将这种调用视为编译错误。这说明了禁用函数的重要一
点: 它们只用于查找匹配函数，使用它们将导致编译错误。


// !! 委托构造函数

如果给类提供了多个构造函数，您可能重复编写相同的代码。也就是说，有些构造函数可能需要包含其他构造函数中已有的代码。为让编码工作更简单、更可靠，'C++11 允许您
在一个构造函数的定义中使用另一个构造函数'。这被称为委托，因为构造函数暂时将创建对象的工作委托给另一个构造函数。

委托使用成员初始化列表语法的变种:

#ifndef B323BD72_50BE_472D_B615_EA0753E70E77
#define B323BD72_50BE_472D_B615_EA0753E70E77

class Notes
{
private:
    int k;
    double x;
    std::string st;
public:
    Notes();
    Notes(int);
    Notes(int,double);
    Notes(int,double,std::string);
};

Notes::Notes(int kk,double xx, std::string st):k(k),xx(xx),st(st)
{

}

Notes::Notes():Notes(0,0.01,"Ah")
{

}

Notes::Notes(int kk):NOtes(kk,0.01,"oh")
{

}

Notes::Notes(int kk, double x):NOtes(kk,x,"Uh")
{

}

#endif /* B323BD72_50BE_472D_B615_EA0753E70E77 */


// !! 继承构造函数

'为进一步简化编码工作，C++11 提供了一种让派生类能够继承基类构造函数的机制'。C++98 提供了一种让名称空间中函数可用的语法:


namespace Box
{
    int void fn(int x)
    {

    }

    int fn(double x)
    {

    }

    int fn(const char *p)
    {

    }
};


using Box::fn;

'这让函数 fn 的所有重载版本都可用'。

也可使用这种方法让基类的所有非特殊成员函数对派生类可用。例如，请看下面的代码:


class C1
{
    ...
public:
    ...
    int fn(int j);
    double fn(double w);
    void fn(const char *);
};


class C2: public C1
{
    ...
public:
    ...
    using C1::fn;
    double fn(double w)
    {

    }
};


......

C2 c2;
int k = c2.fn(3);// using C1::fn(int)
double z = c2.fn(2.4);// using C2::fn(double)

C2 中的 using 声明让 C2 对象可使用 C1 的三个 fn() 方法，但将选择 C2 而不是 C1 定义的方法 fn(double)。


C++11 将这种方法用于构造函数。这让派生类继承基类的所有构造函数(默认构造函数、复制构造函数和移动构造函数除外)，但不会使用与派生类构造函数的特征标匹配的
构造函数:

#ifndef ADC2C2FB_4806_4E01_9BAA_FE2E384944F4
#define ADC2C2FB_4806_4E01_9BAA_FE2E384944F4

class BS
{
private:
    int q;
    double w;
public:
    BS():q(0), w(0){}
    BS(int k):q(k), w(0){}
    BS(double x):q(0),w(x){}
    BS(int k, double x):q(k),w(x){}
    void show() const {std::cout << q << ", " << w << '\n';}
};


class DR: public BS
{
private:
    short j;
public:
    using BS::BS;
    DR():j(-100){}
    DR(double x):BS(2*x),j(int(x)){}
    DR(int i):j(-2),BS(i, 0.5 * i){}
    void show() const {std::cout << j << ", "; BS.show();}

};


int main()
{
    DR o1;// using DR();
    DR o2(18.76);// use DR(double x)
    DR o3(10,1.8);// use BS(int, double)
    ...
}
#endif /* ADC2C2FB_4806_4E01_9BAA_FE2E384944F4 */


由于没有构造函数 DR(int, double)，因此创建 DR 对象 o3 时，将使用继承而来的 BS(int, double)。请注意，继承的基类构造函数只初始化基类成员；如果还要
初始化派生类成员。


// !! 管理虚方法：override 和 final









