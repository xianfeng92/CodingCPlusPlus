#include <iostream>

// !! 语言可用性的强化

// !! 一、nullptr 与 constexpr

// !! nullptr 

nullptr 出现的目的是为了替代 NULL。在某种意义上来说，传统 C++ 会把 NULL、0 视为同一种东西，这取决于编译器如何定义 NULL，
有些编译器会将 NULL 定义为 ((void*)0)，有些则会直接将其定义为 0。

C++ 不允许直接将 void * 隐式转换到其他类型，但如果 NULL 被定义为 ((void*)0)，那么当编译

char *ch = NULL;

时，NULL 只好被定义为 0。而这依然会产生问题，将导致了 C++ 中重载特性会发生混乱，考虑

void foo(char *);
void foo(int);

对于这两个函数来说，如果 NULL 又被定义为了 0 那么 foo(NULL)， 这个语句将会去调用 foo(int)，从而导致代码违反直观


为了解决这个问题，C++11 引入了 nullptr 关键字，专门用来区分空指针、0。nullptr 的类型为 nullptr_t，能够隐式的转换为任何指针或成员指
针的类型，也能和他们进行相等或者不等的比较。


// !! constexpr

C++ 本身已经具备了常数表达式的概念，比如 1+2, 3*4 这种表达式总是会产生相同的结果并且没有任何副作用。如果编译器能够在编译时就把这些表达式
直接优化并植入到程序运行时，将能增加程序的性能。

一个非常显著的例子就是在数组的定义阶段：

#define LEN 10

int len_foo() {
    return 5;
}

int main() {
    char arr_1[10];
    char arr_2[LEN];
    int len = 5;
    char arr_3[len];          // 非法
    const int len_2 = 10;
    char arr_4[len_2];        // 合法
    char arr_5[len_foo()+5];  // 非法

    return 0;
}

在 C++11 之前，可以在常量表达式中使用的变量必须被声明为 const，在上面代码中，len_2 被定义成了常量，因此 len_2 是一个常量表达式，所以能够合法的分
配一个数组；而对于 arr_5 来说，C++98 之前的编译器无法得知 len_foo() 在运行期实际上是返回一个常数，这也就导致了非法的产生。


C++11 提供了 constexpr 让用户显式的声明函数或对象构造函数在编译期会成为常数，这个关键字明确的告诉编译器应该去验证 len_foo 在编译器
就应该是一个常数。

此外，constexpr 的函数可以使用递归：

constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n-1)+fibonacci(n-2);
}

从 C++14 开始，constexptr 函数可以在内部使用局部变量、循环和分支等简单语句，例如下面的代码在 C++11 的标准下是不能够通过编译的:

constexpr int fibonacci(const int n) {
    if(n == 1) return 1;
    if(n == 2) return 1;
    return fibonacci(n-1)+fibonacci(n-2);
}

constexpr int big(){
    return 1086;
}


// !! 二、类型推导

在传统 C 和 C++ 中，参数的类型都必须明确定义，这其实对我们快速进行编码没有任何帮助，尤其是当我们面对一大堆复杂的模板类型时，必须明确的指出变
量的类型才能进行后续的编码，这不仅拖慢我们的开发效率，也让代码变得又臭又长。

C++11 引入了 auto 和 decltype 这两个关键字实现了类型推导，让编译器来操心变量的类型。这使得 C++ 也具有了和其他现代编程语言一样，某种意义上提
供了无需操心变量类型的使用习惯。

// !! auto

使用 auto 进行类型推导的一个最为常见而且显著的例子就是迭代器。在以前我们需要这样来书写一个迭代器:

for(vector<int>::const_iterator itr = vec.cbegin(); itr != vec.cend(); ++itr)


而有了 auto 之后可以:

// 由于 cbegin() 将返回 vector<int>::const_iterator 
// 所以 itr 也应该是 vector<int>::const_iterator 类型
for(auto itr = vec.cbegin(); itr != vec.cend(); ++itr);


一些其他的常见用法:

auto i = 5;             // i 被推导为 int
auto arr = new auto(10) // arr 被推导为 int *


注意：auto 不能用于函数传参，因此下面的做法是无法通过编译的（考虑重载的问题，我们应该使用模板）

int add(auto x, auto y);


此外，auto 还不能用于推导数组类型：

int main() {
 auto i = 5;

 int arr[10] = {0};
 auto auto_arr = arr;
 auto auto_arr2[10] = arr;

 return 0;
}


// !! decltype

decltype 关键字是为了解决 auto 关键字只能对变量进行类型推导的缺陷而出现的。它的用法和 sizeof 很相似

decltype(表达式)

有时候，我们可能需要计算某个表达式的类型，例如：

auto x = 1;
auto y = 2;

decltype(x+y) z;

// !! 尾返回类型、auto 与 decltype 配合

你可能会思考，auto 能不能用于推导函数的返回类型。考虑这样一个例子加法函数的例子，在传统 C++ 中我们必须这么写:

template<typename R, typename T, typename U>
R add(T x, U y) {
    return x+y
}

在 C++11 中这个问题得到解决。虽然你可能马上会反应出来使用 decltype 推导 x+y 的类型，写出这样的代码:

decltype(x+y) add(T x, U y)

但事实上这样的写法并不能通过编译。这是因为在编译器读到 decltype(x+y) 时，x 和 y 尚未被定义。为了解决这个问题，C++11 还引入了
一个叫做尾返回类型（trailing return type），利用 auto 关键字将返回类型后置:

template<typename T, typename U>
auto add(T x, U y) -> decltype(x+y) {
    return x+y;
}


// !! 三、区间迭代

基于范围的 for 循环, 终于，C++11 引入了基于范围的迭代写法，我们拥有了能够写出像 Python 一样简洁的循环语句
int array[] = {1,2,3,4,5};
for(auto &x : array) {
    std::cout << x << std::endl;
}

最常用的 std::vector 遍历将从原来的样子:
std::vector<int> arr(5, 100);
for(std::vector<int>::iterator i = arr.begin(); i != arr.end(); ++i) {
    std::cout << *i << std::endl;
}

变得非常的简单:

// & 启用了引用, 如果没有则对 arr 中的元素只能读取不能修改
for(auto &i : arr) {    
    std::cout << i << std::endl;
}


// !! 四、初始化列表

初始化是一个非常重要的语言特性，最常见的就是对对象进行初始化。在传统 C++ 中，不同的对象有着不同的初始化方法，例如普通数组、POD 
（plain old data，没有构造、析构和虚函数的类或结构体）类型都可以使用 {} 进行初始化，也就是我们所说的初始化列表。而对于类对象的初始化，
要么需要通过拷贝构造、要么就需要使用 () 进行。这些不同方法都针对各自对象，不能通用。

int arr[3] = {1,2,3};   // 列表初始化

class Foo {
private:
    int value;
public:
    Foo(int) {}
};

Foo foo(1);             // 普通构造初始化


为了解决这个问题，C++11 首先把初始化列表的概念绑定到了类型上，并将其称之为 std::initializer_list，允许构造函数或其他函数像参数一样使用
初始化列表，这就为类对象的初始化与普通数组和 POD 的初始化方法提供了统一的桥梁，例如:

#include <initializer_list>

class Magic {
public:
    Magic(std::initializer_list<int> list);
};

Magic magic = {1,2,3,4,5};

std::vector<int> v = {1, 2, 3, 4};

这种构造函数被叫做初始化列表构造函数，具有这种构造函数的类型将在初始化时被特殊关照。

初始化列表除了用在对象构造上，还能将其作为普通函数的形参，例如：

void foo(std::initializer_list<int> list);

foo({1,2,3});

其次，C++11 提供了统一的语法来初始化任意的对象，例如：

struct A {
    int a;
    float b;
};
struct B {

    B(int _a, float _b): a(_a), b(_b) {}
private:
    int a;
    float b;
};

A a {1, 1.1};    // 统一的初始化语法
B b {2, 2.2};


// !! 五、模板增强

传统 C++ 中，模板只有在使用时才会被编译器实例化。换句话说，只要在每个编译单元（文件）中编译的代码中遇到了被完整定义的模板，都会实例化。这就产生了重复实例化而导致的
编译时间的增加。并且，我们没有办法通知编译器不要触发模板实例化。

C++11 引入了外部模板，扩充了原来的强制编译器在特定位置实例化模板的语法，使得能够显式的告诉编译器何时进行模板的实例化：

template class std::vector<MagicClass>;         // 强行实例化
extern template class std::vector<MagicClass>;  // 不在该编译文件中实例化模板


// !! 尖括号 ">"

在传统 C++ 的编译器中，>> 一律被当做 ~~右移运算符~~ 来进行处理。但实际上我们很容易就写出了嵌套模板的代码：

std::vector<std::vector<int>> mtx;

这在传统 C++ 编译器下是不能够被编译的，而 C++11 开始，连续的右尖括号将变得合法，并且能够顺利通过编译。

// !! 类型别名模板

在了解类型别名模板之前，需要理解『模板』和『类型』之间的不同。仔细体会这句话：模板是用来产生类型的。在传统 C++中，typedef 可以为类型定义一个新的名称，但是却
没有办法为模板定义一个新的名称。因为，模板不是类型。例如:

template<typename T, typename U>
class SuckType;

typedef SuckType<std::vector, std::string> NewType; // 不合法

C++11 使用 using 引入了下面这种形式的写法，并且同时支持对传统 typedef 相同的功效：

通常我们使用 typedef 定义别名的语法是：typedef 原名称 新名称;，但是对函数指针等别名的定义语法却不相同，这通常给直接阅读造成了一定程度的困难。

typedef int (*process)(void *);  // 定义了一个返回类型为 int，参数为 void* 的函数指针类型，名字叫做 process
using process = int(*)(void *); // 同上, 更加直观
using NewType = SuckType<std::vector, std::string>;


// !! 默认模板参数

我们可能定义了一个加法函数:

template<typename T, typename U>
auto add(T x, U y) -> decltype(x+y) {
    return x+y
}

但在使用时发现，要使用 add，就必须每次都指定其模板参数的类型。在 C++11 中提供了一种便利，可以指定模板的默认参数:

template<typename T = int, typename U = int>
auto add(T x, U y) -> decltype(x+y) {
    return x+y
}

// !! 变长参数模板

模板一直是 C++ 所独有的黑魔法（一起念：Dark Magic）之一。在 C++11 之前，无论是类模板还是函数模板，都只能按其指定的样子，接受一组固定数
量的模板参数；

// !! C++11 加入了新的表示方法，允许任意个数、任意类别的模板参数，同时也不需要再定义时将参数的个数固定。

template <typename ...Ts> class Magic；

模板类 Magic 的对象，能够接受不受限制个数的 typename 作为模板的形式参数，例如下面的定义：

class Magic<int, 
            std::vector<int>, 
            std::map<std::string, 
                     std::vector<int>>> darkMagic;


既然是任意形式，所以个数为0的模板参数也是可以的：class Magic<> nothing;

如果不希望产生的模板参数个数为 0，可以手动的定义至少一个模板参数：


如果不希望产生的模板参数个数为0，可以手动的定义至少一个模板参数：

template<typename Require, typename... Args> class Magic;


变长参数模板也能被直接调整到到模板函数上:

template<typename... Args> void printf(const std::string &str, Args... args);

那么我们定义了变长的模板参数，如何对参数进行解包呢？

首先，我们可以使用 sizeof... 来计算参数的个数:

template<typename... Args>
void magic(Args... args) {
    std::cout << sizeof...(args) << std::endl;
}

我们可以传递任意个参数给 magic 函数：

magic();        // 输出0
magic(1);       // 输出1
magic(1, "");   // 输出2

// !! 六、面向对象增强

// !! 委托构造

C++11 引入了委托构造的概念，这使得构造函数可以在同一个类中一个构造函数调用另一个构造函数，从而达到简化代码的目的

class Base {
public:
    int value1;
    int value2;
    Base() {
        value1 = 1;
    }
    Base(int value) : Base() {  // 委托 Base() 构造函数
        value2 = 2;
    }
};

int main() {
    Base b(2);
    std::cout << b.value1 << std::endl;
    std::cout << b.value2 << std::endl;
}


// !! 继承构造

在传统 C++ 中，构造函数如果需要继承是需要将参数一一传递的，这将导致效率低下。C++11 利用 ~~关键字 using 引入了继承构造函数的概念~~：

class Base {
public:
    int value1;
    int value2;
    Base() {
        value1 = 1;
    }
    Base(int value) : Base() { // 委托 Base() 构造函数
        value2 = 2;
    }
};
class Subclass : public Base {
public:
    using Base::Base;          // 继承构造
};
int main() {
    Subclass s(3);
    std::cout << s.value1 << std::endl;
    std::cout << s.value2 << std::endl;
}


// !! 显式虚函数重载

在传统 C++中，经常容易发生意外重载虚函数的事情。例如:

struct Base {
    virtual void foo();
};
struct SubClass: Base {
    void foo();
};

SubClass::foo 可能并不是程序员尝试重载虚函数，只是恰好加入了一个具有相同名字的函数。另一个可能的情形是，当基类的虚函数被删除后，子类拥有旧
的函数就不再重载该虚拟函数并摇身一变成为了一个普通的类方法，这将造成灾难性的后果。

C++11 引入了 override 和 final 这两个关键字来防止上述情形的发生

// !! override

当重载虚函数时，引入 override 关键字将显式的告知编译器进行重载，编译器将检查基函数是否存在这样的虚函数，否则将无法通过编译。

struct Base {
    virtual void foo(int);
};
struct SubClass: Base {
    virtual void foo(int) override; // 合法
    virtual void foo(float) override; // 非法, 父类没有此虚函数
};

// !! final

final 则是为了防止类被继续继承以及终止虚函数继续重载引入的。

struct Base {
        virtual void foo() final;
};
struct SubClass1 final: Base {
};                  // 合法

struct SubClass2 : SubClass1 {
};                  // 非法, SubClass1 已 final

struct SubClass3: Base {
        void foo(); // 非法, foo 已 final
};

// !! 显式禁用默认函数

C++11 允许显式的声明采用或拒绝编译器自带的函数, 例如:

class Magic {
public:
    Magic() = default;  // 显式声明使用编译器生成的构造
    Magic& operator=(const Magic&) = delete; // 显式声明拒绝编译器生成构造
    Magic(int magic_number);
}

// !! 七、强类型枚举

在传统 C++ 中，枚举类型并非类型安全，枚举类型会被视作整数，则会让两种完全不同的枚举类型可以进行直接的比较（虽然编译器给出了检查，但并非所有），甚至枚举
类型的枚举值名字不能相同，这不是我们希望看到的结果。

C++11 引入了枚举类（enumaration class），并使用 enum class 的语法进行声明

enum class new_enum : unsigned int {
    value1,
    value2,
    value3 = 100,
    value4 = 100
};

这样定义的枚举实现了类型安全，首先它不能够被隐式的转换为整数，同时也不能够将其与整数数字进行比较，更不可能对不同的枚举类型的枚举值进行比较


if (new_enum::value3 == new_enum::value4) {
    // 会输出
    std::cout << "new_enum::value3 == new_enum::value4" << std::endl;
}

在这个语法中，枚举类型后面使用了冒号及类型关键字来指定枚举中枚举值的类型，这使得我们能够为枚举赋值（未指定时将默认使用 int）


而我们希望获得枚举值的值时，将必须显式的进行类型转换，不过我们可以通过重载 << 这个算符来进行输出，可以收藏下面这个代码段：

#include <iostream>
template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

这时，下面的代码将能够被编译：

std::cout << new_enum::value3 << std::endl



// !! 总结

本节介绍了 C++11/14 中对语言可用性的增强，其中最为重要的几个特性是几乎所有人都需要了解并熟练使用的:

1. auto 类型推导
2. 范围 for 迭代
3. 初始化列表
4. 变参模板


int  main(int argc, char **argv)
{
    
}