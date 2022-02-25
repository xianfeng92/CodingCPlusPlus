// !! 通用工具

本章讲解 C++ 标准库的通用工具。'它们由短小精干的类和函数构成, 执行最一般性的工作'。


1. class pair<> 和 class tuple<>

2. smart pointer class(shared_ptr unique_ptr)

3. 数值极值(Numeric limit)

4. Type trait 和 type utility

5.辅助函数--max()、min()、swap()

6. class Radio<>

7. Clock 和 timer

8. 若干重要的 C 函数

大部分通用工具描述于 C++standard 的 "General Utilities"。其余工具则与标准库中一些较主要的组件一起描述, 原因是该类工具主要便是和那些组件共同
使用, 或是基于历史因素。例如某些通用辅助函数被定义于<algorithm> 头文件中, 但按照 STL 的定义它们不算是算法。

这些工具中的一部分也被 C++ 标准库使用, 例如类型pair<>, 凡需要将两个 value 视为一个单元的场合——例如函数必须"返回两个 value"或容器元素是
key/value pair——就必须用到它。而当需要复杂的类型转换时, 就会用上type trait。


// !! Pair和Tuple

C++ 标准库的第 1 版, C++98, 提供了一个简单的class, 用来处理类型不同的两个(一对)值, 而不需为它们再定义特别的 class。当标准函数需要返回一个
value pair, 或者当容器元素是个 key/value pair 时, 就会用上这样一个 C++98 class。


TR1 引入了一个 tuple class, 它将上述概念延伸, 接受任意(但仍有限)个元素。标准库实现保证可移植的范围是: 允许 tuple 带有最多 10 个类型不同的元素。

到了 C++11, tuple class 被重新实现, 采用 variadic template 概念。现在我们有了一个标准的 tuple class, 可用于任意大小的异质集合
(heterogeneous collection)。而与此同时, class pair 仍旧为两个元素服务, 用来组合一个双元素的 tuple。

不过, C++11的 pair class 也有很大扩展, 某种程度上展示了C++语言及其标准库的提升。


// !! Pair

Class pair 可将两个 value 视为一个单元。C++ 标准库内多处用到了这个 class。尤其容器 map、multimap、unordered_map 和 unordered_multimap 
就是使用 pair 来管理其以 key/value pair 形式存在的元素。任何函数如果需返回两个 value, 也需要用到 pair, 例如 minmax()。

Struct pair 定义于 <utility> 。原则上你可以对 pair<> 执行 create、copy/assign/swap及compare操作。此外它还提供 first_type 和 
second_type 类型定义式, 用来表示第一 value 和第二 value 的类型。

namespace std
{
    template <typename T1,typename T2>
    struct pair
    {
        T1 first;
        T2 second;
        ...
    };
}


typedef std::pair<int, float> IntFloatPair;

IntFloatPair p(42,12.22);
p.first;
p.second;
std::get(0)(p);
std::get(1)(p);



// !! 构造函数和赋值

Default 构造函数生成一个 pair 时, 以两个"被 default 构造函数分别初始化"的元素作为初值。根据语言规则, 基础类型(如 int) 的 default 
构造函数也可以引起适当的初始化动作,所以:

std::pair<int, float> p;// initial p.first and p.second with Zero

就是以 int() 和 float() 来初始化 p。这两个构造函数都传回零值。


Copy 构造函数同时存在两个版本, 版本 1 接受相同类型的 pair, 版本 2 是个 member template, 在"构造过程中需要隐式类型转换"时被调用。如果 pair
对象被复制, 调用的是被隐式合成的那个 copy 构造函数。例如:

void f(std::pair<int, const char *>);
void g(std::pair<const int, std::string>);

...

void foo()
{
    std::pair<int, const char *> p(42, "hello");
    f(p);// okay
    g(p);// ok.call template constructor
}

自 C++11 开始, 如果 pair<> 用到了某个类型而该类型只有一个 nonconstant copy 构造函数, 将不再编译成功:


class A
{
public:
    ...
    A(A&);// non const copy constructor
    ...

};

std::pair<A,int> p;// Error. since C++ 11


// !! 逐块式构造（Piecewise Construction）

class pair<> 提供三个构造函数, 用以初始化 first 和 second 成员:

namespace std
{
    template <typename T1, typename T2>
    struct pair
    {
        ...
        pair(const T1& x,const T2& y);
        template <typename U, typename V> pair(U&& x,V&& y);
        template <typename ...Args1, typename ...Args2>
        pair(piecewise_construct_t, tuple<Args1...> first, tuple<Args2...> second);
        ...
    };
}

前两个构造函数提供的是惯常行为: 传递一个实参给 first, 另一个实参给 second, 并且涵盖对 move semantic 和隐式类型转换的支持。

第三个构造函数有点特别, 它允许传递两个 tuple(那是一种“拥有不定个数之元素且元素类型各不相同”的对象), 但以另一种方式处理它们。正常而言, 如果传递
1 或 2 个tuple, 最前面两个构造函数允许初始化一个 pair, 其 first 或 second 是 tuple。但第三个构造函数使用 tuple, 将其元素传递给 first 和
second 的构造函数。为了强迫执行这样的行为, 你必须传递 std::piecewise_construct 作为额外的第一实参。举个例子:

#include <iostream>
#include <tuple>
#include <utility>

using namespace std;

class Foo {
 public:
  Foo(tuple<int, float>) { cout << "Foo::Foo(tup_c)" << endl; }

  template <typename... Args>
  Foo(Args... args) {
    cout << "Foo::Foo(args) " << endl;
  }
};

int main()
{
    tuple<int, float> t(12,12.341);

    // pass the tuple as a whole to the constructor of Foo
    pair<int, Foo> p1(42, t);

    // pass the elements of tuple to the constructor of Foo
    pair<int, Foo> p2(piecewise_construct, make_tuple(42), t);
    
    return 0;
}


 » g++ --std=c++11 pairdemo1.cpp 
--------------------------------------------------------------------------------
 » ./a.out
Foo::Foo(tup_c)
Foo::Foo(args) 

只有当 std::piecewise_construct 被当作第一实参, class Foo 才会被迫使用那个接受 tuple 的元素(一个 int 和一个 float)而非 tuple 整体
的构造函数。这意味着, 此例中被调用的是 Foo 那个"实参数量不定(varargs)的构造函数。如果提供了 Foo::Foo(int, float) 的话,被调用的将是它。

如你所见, 两个实参都必须是 tuple 才会强迫导致这个行为。因此, 第一实参 42 被显式转换为一个 tuple, 用的是 make_tuple()。

// !! 便捷函数 make_pair()

Template 函数 make_pair() 使你无须写出类型就能生成一个 pair 对象。举个例子, 你不必这样写:

std::pair<int, int> p1(1,2);

可以写成这样:

std::make_pair(1,2);

在 C++11 之前, 这个函数的声明和定义如下:

namespace std
{
    template <typename T1, typename T2>
    pair<T1, T2> make_pair(const T1& x1, const T2& x2)
    {
        return pair<T1, T2>(x1, x2);
    }
}

然而自 C++11 起, 事情变得比较复杂, 因为这个 class 也需要应付 move semantic。所以自 C++11 起, C++ 标准库宣称 make_pair() 声明如下:

namespace std
{
    template <typename T1, typename T2>
    pair<V1, V2> make_pair(T1&& x1, T2&& x2);
}


其中返回值的细节和它们的类型 V1 和 V2, 取决于 x 和 y 的类型。无须深入细节, C++ standard 明确指出, 如果可能的话 make_pair() 使用 move 
语义, 否则就使用 copy 语义。


当我们必须对一个"接受 pair 为实参"的函数传递两个 value 时, make_pair() 尤显方便, 请看下例:

void f(std::pair<int,char *>);
void g(std::pair<const int, std::string>);

...

void foo()
{
    f(std::make_pair(12,"jello"));
    g(std::make_pair(111,"jello"));
}


从本例可以看出, make_pair() 即使在类型并不准确吻合的情况下也能借由 template 构造函数提供的支持顺利运作。当你使用 map 和 multimap 时, 经常
需要这样的能力。

注意,自 C++11 开始, 你也可以使用初值列表(initializer list):

f({42, "jello"});
g({42, "jello"});

然而一个表达式如果明白指出类型, 便带有一个优势: 产生出来的 pair 将有绝对明确的类型。例如:

std::pair<int , float> p1(42,21.43);

所得结果不同于:

std::make_pair(42,21.43);

后者所生成的 pair 的第二元素的类型是 double (因为"无任何限定符的浮点字面常量"的类型被视为 double)。当我们使用重载函数(overloaded function) 
或 template 时, 确切的类型非常重要。

例如, 为了提高效能, 程序员可能同时提供分别针对 float 和 double 的重载函数或 template, 这时候确切的类型就非常重要了。

面对 C++11 新语义, 你可以借由强迫使用 move semantic 或 reference semantic 来影响 make_pair() 的产出类型。如果你的选择是 move semantic, 
只需使用 std::move() 声明被传递的实参不再使用:

std::string s, t;
auto p = std::make_pair(std::move(s), std::move(t));
// s, t are no longer used


// !! pair 之间的比较

为了比较两个 pair 对象, C++ 标准库提供了大家惯用的操作符。两个 pair 对象内的所有元素都相等, 这两个 pair 对象才被视为相等(equal):

namespace std
{
    template<typename T1, typename T2>
    bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return x.first == y.first && x.second == y.second;
    }
}

两个 pair 互相比较时, 第一元素具有较高的优先级。所以如果两个 pair 的第一元素不相等, 其比较结果就成为整个比较的结果。如果 first 相等, 才继续比较
second, 并把比较结果当作整体结果:

namespace std
{
    template <typename T1, typename T2>
    bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
    }
}


// !! pair 运用实例

C++ 标准库大量使用 pair。例如(unordered) map 和 multimap 容器的元素类型便是 pair, 也就是一对 key/value。


C++ 标准库中凡"必须返回两个 value"的函数也都使用 pair 对象。


// !! Tuple（不定数的值组）

'Tuple 是 TR1 引入的东西, 它扩展了 pair 的概念, 拥有任意数量的元素'。也就是说, tuple 呈现出一个异质元素列(heterogeneous list of elements)
, 其中每个类型都可以被指定, 或来自编译期推导。







