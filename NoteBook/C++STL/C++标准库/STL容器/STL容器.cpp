
// !! STL 容器

// !! 容器的共通能力和共通操作

// !! 容器的共通能力

本节讲述 STL 容器的共通能力。其中大部分都是必要条件, 所有 STL 容器都必须满足它们。三个最核心的能力是:

1. 所有容器提供的都是"value 语义"而非"reference语义"。容器进行元素的安插动作时, 内部实施的是copy 或 move 动作, 而不是管理元素的 reference。因此
   理想上 STL 容器的每个元素都必须能够被 copied 和 moved。如果你想要存放的对象不具有 public copy 构造函数,或如果你要的不是复制(如复制动作花费太多
   时间,或你要的是被多个容器共享的元素), 那么你就只能使用 move 操作, 要么容器元素就必须是 pointer 或"用以指向对象"的 pointer object。

2. '元素在容器内有其特定顺序'。每一种容器都会提供若干"返回迭代器"的操作函数, 这些迭代器可用来遍历各个元素。这是 STL 算法的关键接口。如果你在元素之间迭代
   多次, 你会获得相同的次序, 前提是不曾安插或删除元素。这甚至对无序(unordered) 容器也适用--只要你不调用那种会增加或删除元素的操作,或强迫内部重整。

3. 一般而言, 各项操作并非绝对安全, 也就是说它们并不会检查每一个可能发生的错误。调用者必须确保传给操作函数的实参符合条件。

通常 STL自己不会抛出异常。如果 STL 容器调用的用户自定义操作 (user-defined operation) 抛出异常, 行为各异。



// !! 容器的共通操作

C++standard 具体指定了一系列容器共通要求, 适用于所有 STL 容器。然而由于 C++11 带来了容器的多样化, 因此可能出现若干例外; 某些容器也许并不满足所有这
些总体性的容器条件, 而又有其他一些操作是全体容器都提供的。


// !! 初始化（Initialization）

每个容器类都提供了一个 default 构造函数、一个 copy 构造函数和一个析构函数。你可以以某个已知区间的内容作为容器初值, 自 C++11 起你也可以指定一个
initializer list

1. 针对 initializer list 而写的构造函数, 提供了一种"指明初值"的便捷办法,'这对于常量容器的初始化特别有用':

const vector<int> v1 = {0,1,2,3,4,5,6,7};
const vector<int> v2 = {987,10,11,12,13,14,15,16,17,18};
std::unordered_set<std::string> w = {"hello", std::string()," "};


2. "针对某个给定区间"而写的构造函数, 提供的是以来自"另一容器"或"C-style array"或"标准输入"的元素为初值的能力。这个构造函数是个 member template
    , 所以不只容器不同,连元素类型都可以不同,前提是"来源端的元素类型"和"目标端的元素类型"之间必须存在一个自动转换机制。

    以另一容器的元素为初值, 完成初始化动作:

    std::list<int> l;
    ...
    std::vector<float> v(l.begin(), l.end());

    自 C++11 起你也可以在这种情况中使用一个 move 迭代器来搬移元素:

    std::list<std::string> l;
    ...
    std::vector<std::string> c(std::make_move_iterator(l.begin()),std::make_move_iterator(l.end()));

    以某个寻常 C-style array 的元素为初值, 完成初始化动作:

    int carray[] = {0,1,2,3,4,5,6,7};
    ...
    std::set<int> c(std::begin(carray),std::end(carray));

    作用于 C-style array 身上的 std::begin() 和  std::end() 乃是自 C++11 开始才被定义于 <iterator>。


最后要说的是, 自 C++11 起你可以使用一个 move 构造函数将容器初始化:

std::vector<int> v1;
...
std::vector<int> v2 = std::move(v1);

于是新建容器将拥有"被指定为初值"的那个容器的元素, 而被当作初值的那个容器的内容此后将不再明确。这样的构造函数可显著提升效率,因为在容器内部, 元素被搬移
的方式将会是"调动某些 pointer"而非"逐一复制元素"。'所以任何时候只要你不再需要某个容器, 而它又将被复制, 就该使用 move 构造函数'。



// !! 赋值 (Assignment) 和 swap()

当你对着容器赋予元素时, 来源容器的所有元素被复制到目标容器内, 后者原本的元素全被移除。所以, 容器的赋值动作代价相对高昂。

自 C++11 起, 你可以使用 move assignment 语义取代上述行为。所有容器都提供 move assignment 操作符, 针对 rvalue 而声明, 其内部行为只是将
pointer (指向 value 所在之内存) 交换而已, 并不复制所有 value。

其实 C++11 并没有指明精确行为, 只保证它拥有常量复杂度, 而现实往往就是上述做法。'C++ 标准库仅仅指出, 在一个 move assignment 之后, 赋值操作的左侧容
器将拥有右侧容器的所有元素。至于右侧容器的内容,此后将不明确(不保证任何事情)':

std::vector<int> v1;
std::vector<int> v2;
...
v2 = std::move(v1);

所以,基于效率考虑,如果赋值后右侧容器的内容不再被使用, 你应该使用这种赋值法。

此外, 自 C++98 开始, 所有容器都提供成员函数 swap(), 用来置换两容器的内容。事实上它只是置换若干内部 pointer, 它们被用来指向数据(如元素、分配器
allocator、排序准则sorting criterion等等)

所以 swap() 保证常量复杂度, 不像 copy assignment 是线性复杂度。容器的迭代器和用以指向元素的 reference, 都"密切紧盯"被置换的元素。'因此 swap() 
之后原本存在的迭代器和 reference 都仍然指向原先所指的元素, 只不过那些元素如今位于另一个容器中了'。


// !! 与大小相关的操作函数 (Size Operation)

所有容器都提供三个与大小相关的操作函数:

1. empty() 是 size()==0 的一个快捷形式。empty() 的实现可能比 size()==0 更有效率,你应该尽可能使用它

2. size() 返回当前容器的元素数量

3. max_size() 返回容器所能容纳的最大元素数量。其值因实现版本的不同而异


// !! 比较 (Comparison)

除了无序 (unordered)容器，常用的比较操作符 ==、！=、<、<=、> 和 >= 都依据以下三个规则被定义出来:

1. 比较动作的两端 (两个容器) 必须属于同一类型

2. 如果两个容器的所有元素依序相等, 那么这两个容器相等。操作符 == 被用来检查元素是否相等

3. 采用 "字典式 (lexicographical)比较" 来判断某个容器是否小于另一容器

'无序 (unordered) 容器只定义操作符 == 和 !=, 当容器内的每一个元素在另一容器内有相等元素,这些操作就返回 true'。元素次序无关紧要,因为它们是无序容器。


'若要比较两个不同类型的容器, 必须使用 STL 比较算法'


// !! 元素访问（Element Access)

所有容器都提供迭代器接口, 即它支持 range-based for 循环。因此, 自 C++11 开始, 最容易访问所有元素的办法如下:

for(const auto& elem : coll){
    cout << elem << endl;
}

如果想要涂改元素, 就不要写出 const:

for(auto& elem : coll)
{
    elem = 19;
}

可以使用由 cbegin() 和 cend() 产出的迭代器进行只读操作 (read-only access):

for(auto pos = coll.cbegin(); pos != coll.cend(); ++pos)
{
    std::cout << *pos << std::endl;
}

亦永远可以使用 begin() 和 end() 产出的迭代器进行涂写操作(write access):

for(auto pos = coll.begin(); pos != coll.cend(); ++pos)
{
    ...
}

如果其他元素被删除, 所有容器 (除了 vector 和 deque) 都保证迭代器以及用以指向元素的 reference 继续保持有效。但对于 vector, 只有删除点之前的元
素才保持有效。


如果你以 clear() 移除所有元素, 对 vector、deque 和 string 而言, 任何由 end() 或 cend() 返回的 past-the-end 迭代器都可能失效。

如果你安插元素:

1. 只有 list、forward list 和关联式容器保证原本的迭代器和用以指向元素的 reference 继续保持有效。

2. 对 vector 而言, 这份保证只有当安插动作不超出容量才成立

3. 至于 unordered 容器, 上述保证对于 reference 一般是成立的, 但对于迭代器则只有当"不发生 rehashing"才成立, 而只要安插后的最终元素总数小于
   bucket 个数乘以最大负载系数, 就不会发生 rehashing


// !! 容器提供的类型

所有容器都提供下面列出的共通类型:

size_type  用来表示容器大小的无正负号整数类型

different_type  带正负号的差距值类型

value_type 元素的类型

reference_type 元素的 reference 类型

iterator Iterator 类型

const_iterator 指向只读元素的 iterator 类型

pointer 指向元素的 pointer 类型

const_pointer 指向只读元素的 pointer 类型



// !! Array

一个 array--也就是容器类 array<> 的一份实体--模塑出一个 static array。它包覆一个寻常的 static C-style array 并提供一个 STL 容器接口。
观念上所谓 array 是指一系列元素,有着固定大小。因此你无法借由增加或移除元素而改变其大小。它只允许你替换元素值。


'Class array<> 自 TR1 起被引入 C++ 标准库,  其概念是在 C-style array 身上包覆一个有用的class'。它比寻常的 array 安全,而且效率并没有因此变
差。为使用这样的 array, 首先你必须包含头文件 <array>

#include <array>

该类型被定义为一个 class template, 位于命名空间 std 中:

namespace std{
    template<typename T, size_t N>
    class array;
}


Array 的元素可属于任何被指明的类型 T。第二个 template 参数用来指出这个 array 在其生命期中拥有的元素个数。因此 size() 的结果总是 N。

Array 并不支持(也就是不允许你指定) 分配器 (allocator)。


// !! Array 的能力

'Array 会把元素复制到其内部的 static C-style array 中'。这些元素总是拥有一个明确次序。因此 array 是一种 ordered 集合。Array 允许随机访问, 也
就是你可以在常量时间内直接访问任何元素, 前提是你知道元素位置。Array 的迭代器属于 random-access 迭代器, 所以你可以对它运用任何 STL 算法。

'如果你需要一个有固定元素量的序列,class array<> 将带来最佳效能', 因为内存被分配于 stack 中(如果可能的话), 绝不会被 reallocation, 而且你拥有随机
访问能力。


// !! 初始化(Initialization)

关于初始化, class array<> 有若干独特语义。第一个例子是, default  构造函数并非建立一个空容器, 因为容器的元素个数是个常量, 取决于其第二  template
参数, 并且在整个生命期间不变。

注意, array<> 是唯一一个无任何东西被指定为初值时, 会被 default initialized 的容器。

这意味着对于基础类型, 初值可能不明确, 而不是 0, 例如:

std::array<int,4> x;// OOPs, elements of x has undefined values

你可以为它提供一个 empty initializer list, 这种情况下所有元素保证被初始化, 于是对基础类型而言元素初值为 0:

std::array<int,4> x = {};// ok, all elements has value 0


如果 initializer list 内没有足够元素, array 的元素会经由其类型的 default 构造函数初始化。这种情况下对基础类型而言,其元素保证被初始化为 0。
例如:

std::array<int,10>  c2 = {42};// one element with value 42, followed by 9 elements with value 0

如果初值列内的元素个数多过 array 的大小, 这样的表达式就不对:


std::array<int,5> c3 = {1,2,3,4,5,6,7};// ERROR: too many elements


由于没有提供针对 initializer list 而写的构造函数或 assignment 操作符, 因此在 array 声明期间完成初始化是使用初值列的唯一途径。基于这个原因,你无
法使用小括号语法指明初值:

std::array<int,4> c3({1,2,3,4});// ERROR

std::vector<int> c4({1,2,3,4});// OK

Class array<> 是个聚合体 (aggregate), 这个事实意味着, 用来保存所有元素的那个成员是 public。然而 C++standard 并未明指其名称, 因此对该 public
成员的任何直接访问都会导致不可预期的行为, 也绝对不具移植性。



//!! swap 和 Move 语义


就像所有其他容器一样, array<> 提供 swap() 操作。因此你可以和一个相同类型的容器(元素类型和元素个数都相同)置换彼此的元素。


// !! 大小（Size）

Array 大小为 0 是可能的, 那就是个没有任何元素的 array。这种情况下 begin() 和 end(), cbegin() 和 cend(), 以及相应的 reverse iterator 会释出
同一 value。然而 front() 和 back() 的返回值就不明确了:


std::array<Elem,0> coll;// array with no elements
std::sort(coll.begin(), coll.end());//Ok, but has no effect
coll[5] = elem;// RUNTIME ERROR -> undefined behavior
std::cout << coll.front() << std::endl;// RUNTIME ERROR ->undefined behavior

至于 data(), 其返回值未有明确说明, 意思是你可以将其返回值传至其他地方, 只要你不 dereference 它。


// !!  Array 的操作

// !! Create, Copy, and Destroy

std::array<Elem,N> c    // Default 构造函数, 建立一个 array 带有 default-initialized 元素

std::array<Elem,N> c(c2)  // Copy constructor, 建立另一个 array 的同型拷贝(所以元素都会被复制)

std::array<Elem,N> c = c2; // Copy constructor, 建立另一个 array 的同型拷贝(所以元素都会被复制)

std::array<Elem,N> c(rv); // Move constructor, 取 rvalue rv 的内容建立一个新的 array, since c++ 11

std::array<Elem,N> c = rv; // Move constructor, 取 rvalue rv 的内容建立一个新的 array, since c++ 11

std::array<Elem,N> c = initializer list;// 取 initializer list 的元素为初值, 建立一个 array


// !! Nonmodifying Operation


c.empty();
c.size();
c.max_size();

c1 == c2; //返回 c1 是否等于 c2(对每个元素调用 ==)
c1 != c2; 
c1 < c2;
c1 <= c2;


// !! Assignment


c = c2;// 将 c2 的所有元素赋值给 c
c = rv;// 将 rvalue rv 以 move assign 方式赋值给 c 的每一个元素, since c++ 11
c.fill(val);// 将 val 赋值给 c 的每一个元素
c.swap(c2);// 置换 c 和 c2 的数据
std::swap(c, c2);// 置换 c 和 c2 的数据


'事实上所有这些操作都调用元素类型所提供的 assignment 操作符'


// !! Element Access

欲访问 array 内所有元素, 你必须使用 range-based for 循环, 或者特定的操作函数或迭代器。

对于 nonconstant array 这些操作会返回一个 reference 指向某元素。因此你可以使用这些操作来改动元素, 前提是它不曾因为其他因素而被禁止。

c[idx];// 返回索引 idx 所指的元素(不检查范围)
c.at(idx);// 返回索引 idx 所指的元素(如果 idx 超出范围,就抛出 range-error 异常)
c.front();// 返回第一个元素--不检查是否存在第一个元素
c.back(); // 返回最末元素--不检查是否存在最末元素

对调用端而言, 最重要的议题就是, 这些操作函数是否执行了"范围检查"。好吧, 只有 at() 执行"范围检查"。如果索引逾越范围, at() 会抛出一个 out_of_range
异常。其他函数都不做检查。range error 会引发不明确行为。对于一个空 array<> 调用 operator []、front() 和 back() 总是会导致不明确行为。然而请注
意, 只有声明其大小为 0 它才是空的:

std::array<int,4> coll; // only four elements
coll[6] = 5;// RUNTIME ERROR -> undefined behavior
std::cout << coll.front() << std::endl;

std::array<Elem,0> coll2;// always empty
std::cout << coll2.front() << std::endl;// RUNTIME ERROR -> undefined behavior

所以, 要么你就必须确保 operator[] 所用的索引是合法的, 要么就改用 at():

template <typename C>
void foo(C& coll){
    if(coll.size() > 5){
        coll[5] = ...;// ok
    }
    coll.at(5) = ...;// throw out of range exception
}

注意, 这段代码只在单线程环境中才 OK。在多线程环境中你需要 synchronization mechanism 用以防止在"检查大小"和"访问元素"之间 coll 被改动。


// !! Iterator Function

Array 提供了若干用以获取迭代器的常见操作。'Array 提供的是 random-access 迭代器, 因此原则上你可以对 array 运用任何 STL 算法'。

c.begin();// 返回一个 random-access iterator 指向第一个元素
c.end();// 返回一个 random-access iterator 指向最末元素的下一位置

c.cbegin();// 返回一个 const random-access iterator 指向第一个元素
c.cend();// 返回一个 const random-access iterator 指向最末元素的下一位置

这些迭代器的精确类型由实现决定。然而对 array 而言, begin()、cbegin()、end() 和 cend() 返回的迭代器往往是寻常 pointer, '这很好, 因为 array<> 
内部使用一个 C-style array 存放元素, 并使用寻常 pointer 提供 random-access 迭代器接口'。

然而你不可依赖"迭代器是寻常 pointer"这一事实。举个例子, 如果你用的是安全版 STL (会检查区间差错和其他潜在问题), 那么 array 的迭代器类型往往会是一个
辅助 class。


只要 array 保持有效, 其迭代器也就保持有效。然而不同于任何其他容器, swap() 乃是将新值赋予 iterator、reference 和 pointer 指向的元素身上。


// !! 把 array 当成 C-Style Array

就像对待 class vector<> 一样, C++标准库保证 array<> 的所有元素一定位于连续且相邻的内存内。

于是你可以预期, 对于 array a 的任何有效索引 i, 以下结果必为 true:

&a[i] = &a[0] + i;


这一保证带来某些重要结果。它意味着, 无论何处, 只要你可以使用寻常的 C-style array, 你就可以使用 array<>:

std::array<char, 41> a;
std::strcpy(&a[0],"hello world");// copy a c string into array

然而,如果想直接访问 array 的元素，你不一定要用表达式 &a[0], 因为成员函数 data() 也具备相同用途:

std::array<char, 41> a;
std::strcpy(&a[0],"hello world");
printf("%s\n",a.data());// print contents of array as C-string

当然, 以此种方式使用 array<>, 你必须小心谨慎 (就像你使用寻常的 C-style array 和 pointer 时也总是必须小心谨慎)。举个例子, 你必须确保 array 的
大小足够容纳被复制进来的数据,'而且如果你把其中的内容当作一个 C-string 来看, 你必须放置一个 '\0' 元素于尾端。

注意, 绝对不要以迭代器表现"第一元素的地址"。Class array<> 的迭代器的真实类型取决于实现, 有可能与寻常的 pointer 完全不同:

printf("%s\n", coll.begin());// Error(might work, but not protable)
printf("%s\n", coll.data());// okay


// !! Exception Handling

Array 只提供极少量 logical error 检查。C++standard 规定"可抛出异常"的成员函数只有 at(), 它可说是 subscript 操作符的安全版本。

// !! Array 运用实例

#include <array>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <functional>
#include "print.hpp"

using namespace std;

int main(int argc, char** argv)
{
    array<int, 10> coll = {11, 12, 13, 14, 15, 16, 17};

    PRINT_ELEMENTS(coll);

    coll.back() = 999999999;
    coll[coll.size() -1 ] = 42;
    PRINT_ELEMENTS(coll);

    cout << accumulate(coll.begin(), coll.end(),0) << endl;

    transform(coll.cbegin(),coll.cend(),a.begin(),negate<int>());
    PRINT_ELEMENTS(coll);

    return 0;
}


// !! Vector


vector 模塑出一个 dynamic array。它本身是"将元素置于 dynamic array 中加以管理"的一个抽象概念。不过请注意,C++ standard 并未要求必须以 dynamic
array 实现 vector, 仅仅是规定了其相应条件和操作复杂度。

使用 vector 之前, 必须包含头文件 <vector>:

#include <vector>

在此头文件内, 类型 vector 是一个定义于 namespace std 内的 template:

namespace std{
    template<typename T, typename Allocator = allocator<T>>
    class vector;
}

Vector 的元素可以是任意类型 T。可有可无的第二个 template 参数用来定义内存模型 (memory model)。默认的内存模型是 C++ 标准库提供的 allocator。


// !! Vector 的能力

Vector 将元素复制到内部的 dynamic array 中。元素之间总是存在一定的顺序, 所以 vector 是一种 ordered collection。Vector 支持随机访问, 因此只
要知道位置, 你可以在常量时间内访问任何一个元素。Vector 提供随机访问迭代器, 所以适用于任何 STL 算法。

如果你在末端附加或删除元素, vector 的效率相当好。但如果你在前端或中段安插或删除元素,效率就不怎么样了, 因为作用点之后的每一个元素都必须移到另一位置,而
每一次移动都得调用 assignment 操作符。


// !! Size 和 Capacity

Vector 优异效率的秘诀之一, 就是分配出"较其容纳的元素"更多的内存。为了能够高效运用 vector, 你应该了解大小和容量之间的关系。

Vector 提供用以操作大小的函数有 size()、empty() 和 max_size()。另一个与大小有关的函数是 capacity(), 返回 vector 实际能够容纳的元素量。如果超越
这个量, vector 就有必要重新分配内部内存。

vector 的容量之所以重要, 有两个原因:

1. 一旦内存重新分配, vector 元素相关的所有 reference、pointer、iterator 都会失效

2. 内存重新分配很耗时间

所以, 如果你的程序管理了"与 vector 元素相关"的 reference、pointer 或 iterator, 或如果程序的执行速度对你而言至关重要, 那就必须考虑容量问题。


'你可以使用 reserve() 保留适当容量, 避免重新分配内存'。如此一来, 只要保留的容量尚有富余, 就不必担心 reference 失效。

std::vector<int> coll;// creat an empty vector
coll.reverse(80);// reverse memory for 80 elements

避免重新分配内存的另一个方法是, 初始化期间就向构造函数传递额外实参, 构建足够的空间。如果你的实参是个数值, 它将成为 vector 的起始大小。

std::vector<int> coll(80);

欲获得这种能力, 元素类型必须提供一个 default 构造函数。对基础类型而言, 唯一能够保证的是 zero initialization。但是请注意, 如果类型很复杂, 就算提供
了 default 构造函数, 初始化动作也很耗时。如果你这么做只为了保留足够内存, 那倒不如使用 reserve()。

此外,'如何达到时间和空间的最佳效率, 由实现版本决定'。因此, 具体实现版本中容量的增长幅度可能比你我料想的还大。事实上,为了防止内存破碎, 在许多实现方案中即
使你不调用 reserve(), 当第一次安插元素时也会一口气分配整块内存(例如 2K)。如果你有一大堆 vector, 每个 vector 的实际元素寥寥无几, 浪费的内存相当可观。


既然 vector 的容量不会缩减, 我们便可确定, 即使删除元素, 其 reference、pointer 和 iterator 也会继续有效, 继续指向动作发生前的位置。然而安插动作却
可能使 reference、pointer 和 iterator 失效。


C++11 引入一个 vector 新函数: 一个不具强制力的要求, 可以缩减容量以符合当前的元素个数。

coll.shrink_to_fit();// request to shrink memory, since c++ 11

这个要求不具强制力, 以便为实现可能的特有优化保留回旋余地。因此你不能够期望之后的 coll.capacity == coll.size() 会获得 true。

在 C++11 之前, 有一个间接缩减 vector 容量的小窍门:'两个 vector 交换内容后, 两者的容量也会互换'，因此下面的例子虽然保留了元素,却缩减了容量。

template<typename T>
void shrinkCapacity(std::vector<T> &v) {
    std::vector<T> temp(v);// copy elements to new vector
    v.swap(temp);// swap internal elements data
}


// !! Vector 的操作

// !! 构建、复制和销毁

vector<Elem> c;// Default constructor, 产生一个 empty vector

vector<Elem> c(c2);// Copy constructor,建立 c2 的同型 vector 并成为 c2 的一份拷贝(每个元素都会被复制)

vector<Elem> c = c2;// Copy constructor, 建立 c2 的同型 vector 并成为 c2 的一份拷贝(每个元素都会被复制)

vector<Elem> c(rv);// Move constructor, 取 rvalue rv 的内容建立一个新的 vector, since c++ 11

vector<Elem> c = rv;// Move constructor, 取 rvalue rv 的内容建立一个新的 vector, since c++ 11

vector<Elem> c(n);// 利用元素的 Default 构造函数生成一个大小为 0 的 vector

vector<Elem> c(n,val);// 建立一个大小为 0 的 vector, 每个元素的值为 val

vector<Elem> c(begin,end);// 建立一个 vector,以区间[begin,end) 作为元素初值

vector<Elem> c(initlist);// 建立一个 vector, 以 initlist 的元素为初始值

vector<Elem> c = initlist;// 建立一个 vector, 以 initlist 的元素为初始值

c.~vector();// 销毁所有元素,释放内存


// !! Nonmodifying Operation

c.empty();
c.size();
c.max_size();
c.capacity();

c.shrink_to_fit();

c.reverse(N);

c1 == c2;// 对每个元素调用 ==
c1 < c2;
c1 <= c2;

// !! Assignment

c = c2;// 将 c2 的全部元素值赋给 c

c = rv;// 将 rvalue rv 的所有元素以 move assign 的方式赋值给 c

c = initlist;// 将 initlist 的所有元素赋值给 c

c.assign(n,elem);// 复制 n 个 elem, 赋值给 c

c.assign(beg,end);//将区间[beg,end) 内的元素赋值给 c

c.swap(c2);// 置换 c 和 c2 的数据

std::swap(c, c2);// 置换 c 和 c2 的数据


// !! Element Access

欲访问 vector 的所有元素, 你必须使用 range-based for 循环、特定的操作函数或迭代器。

按 C/C++ 惯例, 第一元素的索引为 0, 最末元素的索引为 size()-1。所以第 n 个元素的索引是 n-1。对于 non-const vector, 这些函数都返回元素的 
reference, 也就是说, 你可以使用这些操作函数更改元素内容。

c[idx];
c.at(idx);
c.front();
c.back();

对调用者来说, 最重要的事莫过于搞清楚这些操作是否执行范围检查。只有 at() 会那么做。如果索引越界, at() 会抛出 out_of_range 异常。其他函数都不做检查,
如果发生越界错误，会引发不明确的行为。


// !! Iterator Function

'vector 提供了一些常规函数来获取迭代器'。vector 提供的是 random-access 迭代器。因此, 理论上说, 你可以把所有 STL 算法作用于 vector 身上。

迭代器的确切类型由实现决定。对 vector 而言, begin()、cbegin()、end() 和 cend() 返回的往往是寻常 pointer。这是好的, 因为 vector 内部结构通常就是
个 array, 而寻常 pointer 也提供了随机访问迭代器的接口。

vector迭代器持续有效, 除非发生两种情况: 1.使用者在一个较小索引位置上安插或移除元素; 2. 由于容量变化而引起内存重新分配

// !! Inserting and Removing

依 STL 惯例, 你必须保证传入的实参合法: 1.迭代器必须指向一个合法位置; 2.区间的起始位置不能在结束位置之后。


一如既往, 当 pop_back() 被调用时, 确保容器不为空是程序员的责任。例如:

std::vector<Elem> coll;// empty vector
coll.pop_back();// RUNTIME ERROR -> undefined behavior

if(!coll.empty())
{
    coll.push_back();// OK
}


然而, 请注意, 在多线程环境中你必须确保: 在"检查容器是否为空"和 pop_back() 动作之间 coll 不被改动:

关于效能, 以下情况你可以预期安插动作和移除动作会比较快些:

· 在容器尾部安插或移除元素

· 容量一开始就够大

· 安插多个元素时, "调用一次"当然比"调用多次"来得快

安插或移除元素, 都会使"作用点"之后的各元素的 reference、pointer 和 iterator 失效。如果安插动作甚至引发内存重新分配, 那么该容器身上的所有
reference、pointer 和 iterator 都会失效。


vector 并未提供任何函数可以直接移除"与某值相等"的所有元素。这是算法发挥威力的时候。以下语句可将值为 val 的所有元素移除:

std::vector<Elem> coll;
...
coll.erase(std::remove(coll.begin(), coll.end(),val),coll.end());

c.push_back(elem);// 附加一个 elem 的拷贝与 c 末尾
c.pop_back();// 移除最后一个元素,但是不返回它
c.insert(pos, elem);// 在 iterator 位置 pos 之前插入一个 elem 拷贝,并返回新元素的位置
c.insert(pos, n, elem);
c.insert(pos,beg. end);
c.emplace(pos, args...);// 在 iterator 位置 pos 之前插入一个以 args... 为初值的元素, 并返回新元素的位置
c.emplace_back(args...);// 附加一个以 args... 为初值的元素于末尾,不返回任何东西

c.erase(pos);// 移除 iterator 位置 pos 上的元素, 返回下一元素的位置
c.resize(N);// 
c.clear();// 移除所有元素,将容器清空

如果只是要移除"与某值相等"的第一个元素, 可以这么做:

std::vector<int> coll;
...
std::vector<int>::iterator pos;
pos = std::find(coll.begin(), coll.end(),val);
if(pos != coll.end()){
    coll.erase(pos);
}


// !! 将 Vector 当作 C-Style Array 使用

就像 class array<> 一样, C++ 标准库保证 vector 的元素必须分布于连续空间中。

因此你可以确定, 对于 vector v 中任意一个合法索引 i, 以下肯定为 true:

&v[i] = &v[0] + i;

保证了这一点, 就可推导出一系列重要结果。

简单的说,'任何地点只要你需要一个 dynamic array, 你就可以使用 vector'。例如你可利用 vector 存放寻常的 C 字符串(类型为 char* 或 const char*):

std::vector<char> v;// create vector as dynamic array
v.resize(41);
std::strcpy(&v[0],"hello world");// Copy C-String into vector
printf("%s\n",&v[0]);// print contents of vector as C-String

自C++11起, 如果想直接访问 vector 的元素, 不一定要用 &a[0], 因为成员函数 data() 也具备相同用途:

std::vector<char, 41> v;// create static array of 41 char
std::strcpy(v.data(),"hello world");// Copy C-String into array
printf("%s\n", v.data());

注意, 千万不要把迭代器当作"第一元素的地址"来传递。Vector 迭代器是由实现定义的, 也许并不是个寻常 pointer。

// !! Exception Handling



// !! Vector 使用实例

#include <vector>
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    vector<string> sentence;// create empty vector for string

    sentence.reverse(5);// reverse memory for five elements to avoid reallocation

    sentence.push_back("hello");
    sentence.insert(sentence.end(),{"how","are","you","?"});

    copy(sentence.cbegin(),sentence.cend(),ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << "max_size() " << sentence.max_size() << endl;
    cout << "size() " << sentence.size() << endl;
    cout << "capacity() " << sentence.capacity() << endl;

    swap(sentence[1], sentence[3]);

    sentence.insert(std::find(sentence.begin(),sentence.end(),"?"), "always");

    sentence.back() = "!";

    copy(sentence.cbegin(),sentence.cend(),ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << "size () " << sentence.size() << endl;
    cout << "capacity ()" << sentence.capacity() << endl;
    cout << endl;

    sentence.shrink_to_fit();

    cout << "size () " << sentence.size() << endl;
    cout << "capacity ()" << sentence.capacity() << endl;
    cout << endl;
    return 0;
}



// !! Class vector<bool>




// !! Deque

容器 deque 和 vector 非常相似。它也采用 dynamic array 来管理元素, 提供随机访问, 并有着和 vector 几乎一模一样的接口。不同的是 deque 的
dynamic array 头尾都开放, 因此能在头尾两端进行快速安插和删除。


为了提供这种能力, deque 通常实现为一组独立区块 (a bunch of individual blocks), 第一区块朝某方向扩展, 最末区块朝另一方向扩展。


使用 deque 之前, 必须先包含头文件 <deque>:

#include <deque>

其中,  deque  类型定义于命名空间 std  内的一个 class template:

namespace std{
    template<Typename T typename Allocator = allocator<T>>
    class  deque;
}

和 vector 相同, 这里的第一个 template 参数用来表明元素类型。第二个 template 实参可有可无, 用来指定 memory model, 默认为 allocator



// !! Deque 的能力

'Deque 与 vector 相比, 功能上的差异如下'

1. 两端都能快速安插元素和移除元素 (vector 只在尾端逞威风), 这些操作可以在摊提的常量时间(amortized constant time)内完成

2. 访问元素时 deque 内部结构会多一个间接过程, 所以元素的访问和迭代器的动作会稍稍慢一些

3. 迭代器需要在不同区块间跳转, 所以必须是个 smart pointer, 不能是寻常 pointer

4. 在内存区块大小有限制的系统中, deque 可以内含更多元素, 因为它使用不止一块内存。因此 deque 的 max_size() 能更大

5. Deque 不支持对容量和内存重新分配时机的控制。特别要注意的是, 除了头尾两端, 在任何地点安插或删除元素都将导致指向  deque 元素的任何 pointer、
   reference 和 iterator 失效。不过, deque 的内存重分配优于 vector, 因为其内部结构显示, deque 不必在内存重新分配时复制所有元素。

6. Deque 会释放不再使用的内存区块。Deque 的内存大小是可缩减的,但要不要这么做，以及如何做，由实现决定



'Deque 的以下特性跟 Vector 差不多'

1. 在中段安插、移除元素的速度相对较慢，因为所有元素都需移动以腾出或填补空间

2. 迭代器属于 random-access iterator


'总之, 以下情形最好采用 deque'

1. 你需要在两端安插和移除元素 (这是 deque 的拿手好戏)

2. 无须指向(refer to)容器内的元素

3. 要求"不再使用的元素必须释放" (不过 C++standard 对此无任何保证)


Vector 和 deque 的接口几乎一样, 所以如果你不需要什么特殊性质，两者都可试试。


// !! Deque 的操作函数


deque<Elem> c;// Default 构造函数, 建立一个空的 deque, 没有任何元素
deque<Elem> c(c2);// Copy constructor, 建立 c2 的同型 deque 并成为 c2 的一份拷贝(每个元素都会被复制)
deque<Elem> c = c2; // Copy constructor, 建立 c2 的同型 deque 并成为 c2 的一份拷贝(每个元素都会被复制)

deque<Elem> c(rv); // Move constructor, 取 rvalue rv 的内容建立一个新的 deque
deque<Elem> c = rv; // Move constructor, 取 rvalue rv 的内容建立一个新的 deque

deque<Elem> c(N);// 利用元素的 Default 构造函数 生成一个大小为 N 的deque

deque<Elem> c(N, elem);// 建立一个大小为 N 的 deque, 每个元素都是 elem

c.~deque();// 销毁所有元素, 释放内存


'Deque 的各项操作只有以下两点和 vector 不同'

1. Deque 不提供容量操作 capacity() 和 reserve()

2. Deque 直接提供函数完成头部元素的安插和删除 push_front() 和 pop_front()


// !! Nonmodifying Operation

c.empty()
c,size()
c.max_size()

c1 == c2
c1 != c2
c1 < c2
c1 <= c2

c[idx]
c.at(idx)

c.front();// 返回第一个元素
c.back();// 返回最末元素
c.begin()
c.end();


// !! Modifying Operation

c = c2;// 将 c2 的全部元素赋值给 c
c =  rv;// 将 rvalue rv 的所有元素以 move assign 的方式给 c

c.assign(n, elem);// 赋值 n 个 elem, 赋值给 c

c1.swap(c2);

c.push_back(elem);// 附加一个 elem 拷贝于末尾
c.pop_back();// 移除最后一个元素,但不返回它

c.push_front(elem);// 在头部插入 elem 的一个拷贝
c.pop_front();//移除第一个元素,但是不返回


c.insert(pos,elem);// 在 iterator 位置 pos 之前插入一个 elem 的拷贝,并返回新元素的位置
c.emplace(pos,args...); // 在 iterator 位置 pos 之前插入一个以 args ... 为初值的元素, 并返回新元素的位置,since c++ 11

c.erase(pos);// 移除 iterator 位置 pos 上的元素,并返回下一元素的位置
c.clear();// 移除所以元素,将容器清空



// !! Deque 运用实例

#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace std;

int main(int argc, char** argv)
{
    deque<string> coll;

    coll.assign(3,string("string"));
    coll.push_back("last string");
    coll.push_front("first string");

    copy(coll.cbegin(),coll.cend(),ostream_iterator<string>(cout, "\n"));
    cout << endl;

    for(unsigned int i = 0 ; i < coll.size() ; i++)
    {
        coll[i] = "another" + coll[i];
    }

    coll.resize(4,"resize string");

    copy(coll.cbegin(),coll.cend(),ostream_iterator<string>(cout, " "));

    cout << endl;
    return 0;
}



// !! List
















