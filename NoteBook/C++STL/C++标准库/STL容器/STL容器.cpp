
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

List 使用一个 doubly linked list 管理元素。按惯例, C++ 标准库并未明定实现方式, 只是遵守 list 的名称、限制和规格。

使用 list 时必须先包含头文件 <list>:

#include <list>

其中的 list 类型系定义于 namespace std 中, 是个 class template:

namespace std{
    template<typename T,typename Allocator = allocator<T>>
    class list;
}


List 的元素可以是任何类型 T。第二个 template 实参可有可无, 用来指定内存模型。默认的内存模型是 C++ 标准库提供的 allocator。


// !! List 的能力

List 的内部结构完全迥异于 array、vector 或 deque。List 对象自身提供了两个 pointer, 或称 anchor (锚点), 用来指向第一个和最末一个元素。每个元素
都有 pointer 指向前一个和下一个元素。如果想要安插新元素, 只需操纵对应的 pointer 即可。

因此, list 在几个主要方面与 array、vector 或 deque 不同:

1. 'List 不支持随机访问'。如果你要访问第 5 个元素, 就得顺着串链逐一爬过前 4 个元素。所以, 在 list 中随机巡访任意元素是很缓慢的行为。然而你可以从两端
    开始航行整个 list, 所以访问第一个或最末一个元素的速度很快。

2. 任何位置上(不只两端)执行元素的安插和移除都非常快, 始终都是常量时间内完成, 因为无须移动任何其他元素。实际上内部只是进行了一些 pointer 操作而已

3. 安插和删除动作并不会造成指向其他元素的各个 pointer、reference 和 iterator 失效



// !! Element Access

欲访问 list 的所有元素, 你必须使用 range-based for 循环、特定操作函数或迭代器。List 不支持随机访问, 只有 front() 和 back() 能够直接访问元素。


c = c2;// 将 c2 的全部元素赋值给 c
c = rv;// 将 rvalue rv 的所有元素以 move assign 的方式给与 c
c = inilist;
c.swap(c2);
swap(c, c2);


c.front();
c.back();

一如既往, 这些操作并不检查容器是否为空。对空容器执行任何操作都会导致不明确的行为。所以调用者必须确保容器至少含有一个元素。

std::list<Elem> coll;
std::cout << coll.front() << std::end;//RUNTIME ERROR -> undefined behavior

if(!coll.empty())
{
    std::cout << coll.front() << std::endl;
}

注意, 这段代码只在单线程环境中才 OK。在多线程环境中你需要同步机制 (synchronization mechanism) 确保"检查大小"和"访问元素"之间 coll 未曾被改动。



// !! Iterator Function

只有运用迭代器, 才能够访问 list 中的各个元素。由于 list 不能随机访问, 这些迭代器只是双向(而非随机)迭代器。所以凡是用到随机访问迭代器的算法
(所有用来操作元素顺序的算法--特别是排序算法——都归此类)你都不能调用它们来处理 list, 不过你可以拿 list 的特殊成员函数 sort() 取而代之。

c.begin();
c.end();
c.cbegin();
c.cend();
c.rbegin();
c.rend();


// !! Inserting and Removing

List 提供 deque 的所有功能, 还增加了适用于 list 的 remove() 和 remove_if() 算法特殊版本。

依 STL 惯例, 你必须保证传入的实参合法: 迭代器必须指向一个合法位置; 区间的起始位置不能在结束位置之后。

为了移除元素, list 特别配备了 remove() 算法的特别版本。这些成员函数比 remove() 算法的速度更快, 因为它们只进行内部 pointer 操作, 不改变元素。

所以, '面对 list, 你应该调用成员函数 remove() 而不是像面对 vector 和 deque 那样调用 STL 算法'


std::list<Elem> coll;
...

// remove all elements with values val
list.remove(val);


然而, 如果只是要移除第一个"带有某值"的元素,讨论 vector 时提到的 std::remove 算法。


你可以使用 remove_if() 以求定义出元素的移除准则(removing criterion), 做法是为该算法提供一个函数或函数对象。remove_if() 会将"造成该函数或函数对
象返回 true"的每一个元素移除。


c.push_back(elem);// 附加一个 elem 与容器末尾
c.pop_back();// 移除最后一个元素,但是不返回它

c.push_front(elem);//在头部插入 elem 的一个拷贝
c.pop_front();// 移除头部的一个元素,但是不返回它
c.insert(pos,elem);//在 iterator 位置 pos 之前插入一个 elem 拷贝,并返回新元素的位置

c.erase(pos);// 移除 iterator 位置 pos 上的元素, 返回下一个元素的位置
c.remove(val);// 移除所有值为 val 的元素

c.clear();// 移除所有元素,将容器清空


// !! Splice (接合)函数以及会改变元素次序的函数

Linked list 的一大好处就是不论在任何位置, 元素的安插和移除都只需要常量时间。如果你有必要将若干元素从 A 容器转放到 B 容器, 那么上述好处就更见其效了
, 因为你只需要重新定向某些指针即可。

为了利用这个优势, list 不仅提供 remove(), 还提供其他若干成员函数, 用来改变元素和区间次序, 或重新链接relink, 我们不仅可以调用这些函数移动单一 list
内的元素, 也可以移动两个 list 之间的元素--只要 list 的类型一致即可。

// !! Special Modifying Operation

c.unique();// 如果存在若干相邻而数值相同的元素,就移除重复元素,只留一个
c.unique(op);//如果存在若干相邻都使得 op() 的结果为 true, 则移除重复元素只留一个
c.splice(pos, c2);// 将 c2 内的所有元素转移（move）到 c 之内, 迭代器 pos 之前
c.sort();// 以 operator< 准则对所有元素排序
c.sort(op);// 以 op() 为准则对所有元素排序

c.merge(c2);// 假设 c 和 c2 容器都包含 op() 准则下已排序(Sorted)的元素, 将 c2 的全部元素转移到 c,保证合并后的 list 仍为已排序(Sorted)


c.merge(c2, op);// 假设 c 和 c2 容器都包含已排序(Sorted)的元素, 将 c2 的全部元素转移到 c,保证合并后的 list 在 op 准则下仍为已排序(Sorted)

c.reverse(); // reverse the order



// !! List 运用实例
#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;

void printlist(const std::list<int>& l1, const std::list<int>& l2) {
  cout << "list1: " << endl;
  copy(l1.cbegin(), l1.cend(), ostream_iterator<int>(cout, " "));
  cout << endl;

  cout << "list2: " << endl;
  copy(l2.cbegin(), l2.cend(), ostream_iterator<int>(cout, " "));
  cout << endl;
}

int main(int argc, char** argv) {
  list<int> list1, list2;

  for (int i = 0; i < 6; i++) {
    list1.push_back(i);
    list2.push_front(i);
  }

  printlist(list1, list2);

  list2.splice(find(list2.cbegin(), list2.cend(), 3), list1);
  printlist(list1, list2);

  list2.splice(list2.end(), list2, list2.begin());
  printlist(list1, list2);

  list2.sort();
  list1 = list2;
  list2.unique();

  printlist(list1, list2);

  list1.merge(list2);

  printlist(list1, list2);

  return 0;
}




// !! Set 和 Multiset

Set 和 multiset 会根据特定的排序准则, 自动将元素排序。两者不同之处在于 multiset 允许元素重复而 set 不允许。


使用 set 或 multiset 之前, 必须先包含头文件<set>:

#include <set>

在这个头文件中, 上述两个类型都被定义为命名空间 std 内的 class template:

namespace std{
    template <typename T, typename Compare = less<T>, typename Allocator = allocator<T>>
    class set;

    template <typename T, typename Compare = less<T>, typename Allocator = allocator<T>>
    class multiset;
}


'只要是可依据某排序准则被比较(所谓 comparable) 的任意类型 T 都可以成为 set 或 multiset 的元素类型'。可有可无的第二个 template 实参用来定义排序准
则。如果没有传入某个排序准则, 就采用默认准则 less--这是个函数对象, 以 operator< 对元素进行比较。可有可无的第三实参用来定义内存模型。默认的内存模型是
allocator, 由 C++ 标准库提供。

所谓"排序准则", 必须定义 strict weak ordering, 其意义如下:

1. 必须是非对称的

对 operato< 而言, 如果 x < y 为 true, 则 y < x 为 false

2. 必须是可传递的 transitive

对 operator< 而言, 如果 x < y 为 true 且 y < z 为 true, 则 x < z 为 true

3. 必须是非自反的

对 operator< 而言, x < x 永远为 false

4. 必须有等效传递性



// !! Set 和 Multiset 的能力

和所有标准的关联式容器类似, set 和 multiset 通常以平衡二叉树 (balanced binary tree) 完成--C++standard 并未明定, 但由 set 和 multiset 各项操
作的复杂度可以得出这个结论。

自动排序的主要优点在于令二叉树于查找元素时拥有良好效能。其查找函数具有对数 (logarithmic) 复杂度。但是, 自动排序造成 set 和 multiset 的一个重要限
制:'你不能直接改变元素值,因为这样会打乱原本正确的顺序'。


因此, 要改变元素值, 必须先删除旧元素,再插入新元素。以下接口反映了这种行为:

1. Set 和 multiset 不提供任何操作函数可以直接访问元素

2. 通过迭代器进行元素间接访问,有一个限制:从迭代器的角度看,元素值是常量


// !! Set 和 Multiset 的操作函数



// !! Create, Copy and Destroy

有两种方式可以定义排序准则:

1. 以template参数定义之。例如:

std::set<int, std::greater<int>> coll;

这种情况下排序准则就是类型的一部分。于是类型系统确保"只有排序准则相同的容器才能被合并"。这是排序准则的通常指定法。更精确地说, 第二参数是排序准则的类型
, 实际的排序准则是容器所产生的函数对象。为了产生它, 容器的构造函数会调用"排序准则类型"的 default 构造函数。


2. 以构造函数参数定义之

这种情况下, 同一个类型可以运用不同的排序准则，而排序准则的初始值或状态也可以不同。如果运行期才获得排序准则, 而且需要用到不同的排序准则（但数据类型必须
相同）, 这一方式可派上用场。


如果用户没有提供特定的排序准则, 就采用默认准则--函数对象 less<>。less<> 通过 operator< 对元素进行排序。


set c;// Default 构造函数, 建立一个空的 set, 不含任何元素
set c(op);// 建立一个空的 set, 以 op 为排序准则

set c = c2;//Copy 构造函数, 为相同类型的另一个 set 建立一份拷贝, 所有元素均被复制
set c(rv);// Move 构造函数, 建立一个新的 set, 有相同类型, 取 rvalue rv 的内容

c.~set();// 销毁所有元素, 释放内存


如果用 operator== 对两个容器做比较, 两个容器内的元素将使用它们自己的 operator== 进行比较, 那意味着元素类型必须提供 operator==。


// !! Nonmodifying Operation

Set 和 multiset 提供常见的非更易型操作, 用来查询大小、相互比较:

c.key_comp(); // 返回比较准则
c.value_comp(); // 返回针对 value 的比较准则(和 key_comp() 相同)
c.empty(); // 判断是否容器为空

c.size(); // 返回目前的元素个数

c.max_size(); //返回元素个数之最大可能性

c1 == c2;
c1 < c2;
c1 <= c2;


元素比较动作只适用于类型相同的容器。'换言之,元素和排序准则必须有相同的类型,否则编译期会产生类型方面的错误'。



std::set<float> c1;
std::set<float, std::greater<float>> c2;
...
if(c1 == c2){// Error different type
    ....
}


比较动作是以 "字典顺序" 检查某个容器是否小于另一容器。


// !! Special Search Operation

'set 和 multiset 在元素快速查找方面有优化设计, 所以提供了特殊的查找函数'。

面对 set 和 multiset 你应该优先采用这些优化算法, 如此可获得对数复杂度, 而非 STL 算法的线性复杂度。


c.count(val);// 返回 元素值为 val 的元素的个数
c.find(val);// 返回 元素值为 val 的第一个元素, 如果找不到则返回 end()
c.lower_bound(val);// 返回 val 的第一个可安插位置, 也就是元素值 >= val 的第一个元素的位置

c.equal_range(val);

成员函数 find() 查找出与实参值相同的第一个元素, 并返回一个迭代器指向该位置。如果没找到这样的元素, 就返回容器的 end()。




// !! Assignment

set 和 multiset 只提供任何容器都提供的基本赋值操作。这些操作函数中, 赋值操作的两端容器必须具备相同类型。尽管"比较较准则"本身可能不同，但其类型必须相同。


// !! Iterator Function

Set 和 multiset 不提供元素直接访问, 所以只能采取 range-based for 循环或采用迭代器。

c.begin();
c.end();
c.cbegin();
c.cend();
c.rbegin();
c.rend();

和所有关联式容器类似， 这里的迭代器是双向迭代器。更重要的是，从迭代器的角度看去， 所有元素都被视为常量， 这可确保元素不会被改动以至于打乱既有顺序。



// !! Inserting and Removing

C++11 保证, multiset 的 insert()、emplace() 和 erase() 成员函数都会保存等值元素间的相对次序, 插入的元素会被放在"既有的等值元素群"的末尾。



注意, 用以安插元素的函数: insert() 和 emplace() , 其返回类型不尽相同:

Set提供如下接口:

pair<iterator, bool> insert(const value_type& val);
iterator insert(const_iterator posHint, const value_type& val);

template <typename ...Args>
pair<iterator, bool> emplace(Args&& ...args);


Multiset提供如下接口:

iterator insert(const value_type& val);

template <typename ...Args>
iterator emplace(const value_type& val);


返回类型之所以不相同, 原因是: multiset 允许元素重复而 set 不允许。

因此, 如果将某元素安插至 set 内, 而该 set 已经内含同值元素, 安插动作将告失败。所以 set 的返回类型是以 pair 组织起来的两个值。

1. pair 结构中的 second 成员表示安插是否成功

2. pair 结构中的 first 成员表示新元素的位置, 或现存的同值元素的位置


以下例子把数值为 3.3 的元素安插到 set c 中, 借此说明如何使用上述接口:

std::set<double> c;
...
if(c.insert(3.3).second){
    std::cout << "3.3 inserted" << std::endl;
}else{
    std::cout << "3.3 already existed" << std::endl
}


如果你还想处理新位置或旧位置, 代码得更复杂些:

auto status = c.insert(value);
if(status.second){
    std::cout << value << "inserted as a element" << std::endl;
}else{
    std::cout << "already exists" << std::endl;
}

std::cout << std::distance(c.begin(),value.first) + 1 << std::endl;



若欲删除"与某值相等"的元素, 只需调用 erase():

std::set<Elem> coll;
...
// remove all elements with values val
coll.erase(val);

它返回的是被删除元素的个数, 在 set 身上其返回值非 0 即 1。


如果 multiset 内含重复元素, 你不能使用 erase() 来删除这些重复元素中的第一个。但你可以这么做:

std::multiset<Elem> coll;
...
// remove first element with value val
std::multiset<Elem>::iterator pos;
pos = coll.find(val);
if(pos != coll.end()){
    coll.erase(pos);
}

这里应该采用成员函数 find(), 而非 STL 算法 find(), 因为前者速度更快。

Multiset 的 insert()、emplace() 和 erase() 操作函数都会保留等价元素的相对次序。自 C++11 起, 调用 insert(val) 或 emplace(args...), 新元素
保证会被安插于等价元素所形成的区间的末端。



// !! Exception Handling

Set 和 multiset 是"以节点(node)为基础"的容器。如果节点构建失败, 容器仍保持原样。此外，由于析构函数通常并不抛出异常，所以节点的移除不可以失败。


// !! Set 和 Multiset 运用实例

以下程序展示了 set 的若干能力:

#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    std::set<int, std::greater<int>> coll1;

    coll1.insert({4,5,2,8,1});
    coll1.insert(7);

    // print all elements
    for(auto pos = coll1.begin(); pos != coll1.end();++pos){
        cout << *pos << endl;
    }

    for(auto ele: coll1){
        cout << elem << endl
    }

    cout << endl;

    auto status = coll1.insert(4);
    if(status.second){
        std::cout << "4 inserted as a element" << std::endl;
    }else{
        std::cout << "4 already exists" << std::endl;
    }

    set<int> coll2(coll1.begin(), coll1.end());

    copy(coll2.cbegin(),coll2.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;

    coll2.erase(coll2.begin(), coll2.find(3));

    int num;
    num = coll2.erase(5);
    cout << num << "elements removed." << endl;

    copy(coll2.cbegin(),coll2.cend(),ostream_iterator<int>(cout, " "));

    cout << endl;
    
}

首先建立一个空 set, 使用不同的 insert() 重载版本安插数个元素:

std::set<int, std::greater<int>> coll1;
coll1.insert({1,2,3,4,5});
coll1.insert(5);


注意数值为 5 的元素被安插两次, 但第二次安插会被忽略, 因为 set 不允许元素值重复。


set<int> coll2(coll1.begin(), coll1.end());

产生一个新的 set, 其内容纳升序(递增)排列的 int, 并以原先那个 set 的元素为初值。

以下语句移除数值为 3 的元素之前的所有元素:

coll2.erase(coll2.begin(),coll2.find(3));

注意上述数值为 3 的元素位于区间尾端, 所以它没被移除



// !! 运行期指定排序准则

'无论是将排序准则作为第二个 template 实参传入, 或是采用默认的排序准则 less<>, 通常你都会将排序准则定义为类型的一部分'。但有时必须在运行期处理排序准
则，或者有时候你需要对同一种数据类型采用不同的排序准则。此时你就需要一个"用来表现排序准则"的特殊类型，使你能够在运行期间才给定某个准则。

以下程序说明了这种做法:

#include <iostream>
#include <set>

#include "print.hpp"

using namespace std;

class RuntimeCmp{
    public:
        enum cmp_mode {normal,reverse};
    private:
        cmp_mode mode;
        RuntimeCmp(cmp_mode m = normal) : mode(m) {}
        template <typename T>
        bool operator()(const T& t1, const T& t2){
            return mode == normal ? t1 < t2 : t1 > t2;
        }
        
        bool operator==(const RuntimeCmp& rc) const {
            return mode == rc.mode;
        }
};

typedef set<int,RuntimeCmp> Intset;

int main() {
    Intset coll1 = {3,2,8,6,7};
    PRINT_ELEMENTS(coll1, "coll1:");

    RuntimeCmp reverse_order(RuntimeCmp::reverse);

    Intset coll2(reverse_order);
    coll2 = {9,1,3,6,4,2};
    PRINT_ELEMENTS(coll2, "coll2:");


    coll1 = coll2;
    coll1.insert(3);
    PRINT_ELEMENTS(coll1, "coll1:");
}


在这个程序中, class RuntimeCmp 提供了一种泛化能力: 允许在运行期间对任何数据类型指定排序准则。其 default 构造函数设定以升序(ascending order)进行
排序, 用的是默认值 normal。它也允许你传递 RuntimeCmp::reverse 作为构造函数实参, 导致以降序 descending order 排序。



// !! Map 和 Multimap

Map 和 multimap 将 key/value pair 当作元素进行管理。它们可根据 key 的排序准则自动为元素排序。Multimap 允许重复元素, map 不允许。

使用 map 和 multimap 之前,你必须先包含头文件 <map>:

#include <map>

在其中, map 和 multimap 被定义为命名空间 std 内的 class template:

namespace std{
    template<Typename Key, typename T,
    Typename Compare = less<Key>, Typename Allocator = allocator<pair<const Key,T>>>
    class map;

    template <typename Key, typename T,
    Typename Compare = less<Key>, typename Allocator = allocator<pair<const Key,T>>>
    class multiset;
}

第一个 template 实参将成为元素的 key 类型, 第二个 template 实参将成为元素的 value 类型。

Map 和 multimap 的元素类型 Key 和 T 必须满足以下两个条件:

1. Key 和 value 都必须是 copyable 或 movable

2. 指定的排序准则而言, key 必须是 comparable


第三个 template 实参可有可无, 用来定义排序准则。如果用户未传入某个排序准则, 就使用默认的 less<> 排序准则--以 operator< 进行比较。

关于 multimap, 我们无法预测所有"拥有等价key"的元素的彼此次序, 不过它们的次序是稳固不变的。'C++11 保证 multimap 的安插和抹除动作都会保留等价元素的相对次序'。

第四个 template 实参也是可有可无, 用来定义内存模型。默认的内存模型是 allocator, 由 C++ 标准库提供。



// !! Map 和 Multimap 的能力

和其他所有关联式容器一样, map/multimap 通常以平衡二叉树完成。C++standard 并未明定这一点, 但是从 map 和 multimap 各项操作的复杂度自然可以得出这一结论。'通常
set、multiset、map 和 multimap 使用相同的内部结构, 因此, 你可以把 set 和 multiset 视为特殊的 map 和 multimap, 只不过 set 元素的 value 和 key 是同一对
象'。

因此, map 和 multimap 拥有 set 和 multiset 的所有能力和所有操作。当然, 某些细微差异还是有的: 首先,它们的元素是 key/value pair, 其次, map 可作为关联式数
组(associative array)来运用。

Map 和 multimap 会根据元素的 key 自动对元素排序。这么一来, 根据已知的 key 查找某个元素时就能够有很好的效率, 而根据已知 value 查找元素时, 效率就很糟糕。

"自动排序"这一性质使得 map 和 multimap 身上有了一条重要限制: 你不可以直接改变元素的 key, 因为这会破坏正确次序。要修改元素的 key, 必须先移除拥有该 key 的元素,
然后插入拥有新 key/value 的元素。从迭代器的观点看, 元素的 key 是常量。'至于元素的 value 倒是可以直接修改, 当然前提是 value 并非常量'。


// !! Map 和 Multimap 的操作函数


// !! Create,Copy, and Destroy

map c;// Default constructor, 建立一个空 map/multimap 
map c(op);// 建立一个空 map/multimap, 以 op 为排序准则

map c(c2);// Copy constructor
map c = c2;// Copy constructor

map c(rv);// Move constructor, 取 rvalue rv 的内容建立一个新的 map/multimap
map c = rv;// Move constructor, 取 rvalue rv 的内容建立一个新的 map/multimap

map c(beg,end);
map c(beg,end,op);

c.~map();// 销毁所有元素, 释放内存


其中, map 可为下列形式:

map<Key,Value> // 一个 map 以 less<> 为排序准则

map<Key,Value,Op> // 一个 map 以 Op 为排序准则

multimap<Key,Value>
multimap<Key,Value,Op>


两种方式可以定义排序准则:

1. 以 template 实参定义之

std::map<float,std::string,std::greater<float>> coll;

这种情况下, 排序准则就是类型的一部分。因此类型系统确保"只有排序准则相同的容器才能被合并"。这是比较常见的一种排序准则指定法。'更精确地说, 第三参数是排序准则的类型。
实际的排序准则是容器所产生的函数对象 (function object)'。为了产生它,构造函数会调用"排序准则类型"的 default 构造函数。

2. 以构造函数参数定义之

这种情况下, 你可以有一个"排序准则类型"并为它指定不同的排序准则实例(也就是说,让该类型所产生的对象(代表一个排序准则)的初值或状态不同)。如果运行期才能获得排序准则,
而且程序需要用到不同的排序准则(但其类型必须相同), 这一方式可派上用场。


如果用户没有指定任何排序准则, 就采用默认准则——函数对象 less<>。less<> 通过 operator< 对元素排序。'再强调一次,排序准则也被用来检验同一容器内的两个元素的等价性'
(例如用来找出重复元素)。只有当比较两个容器时,才需要操作符 ==。

我想你应该宁愿另外定义一个类型, 避免无聊而重复地为了一个类型写那么一长串:

typedef std::set<float, std::string, std::greater<std::string>> StringFloatMap;

...

StringFloatMap coll;



// !! Nonmodifying Operation

Map 和 multimap 提供了若干常见的非更易型操作, 用来查询大小、相互比较。


"元素比较"函数只能用于类型相同的容器身上, 换言之, 两个容器的 key、value、排序准则都必须有相同的类型, 否则编译期会产生类型方面的错误。

std::map<float, std::string> coll1;
std::map<float, std::string, std::greater<std::string> > coll2;

....

if(coll1 == coll2)// Error, different type
{

}


c.key_comp();//返回 比较准则
c.value_comp();//返回针对 value 的比较准则

c.empty();// 返回是否容器为空(相当于 size() == 0,当也许较快)
c.size();//返回目前的元素数量

c.max_size();//返回元素个数之最大可能量

c == c2;// 返回 c 是否等于 c2 ---对每个元素调用 ==


比较函数以"字典顺序"检查某个容器是否小于另一个容器。



// !! Special Search Operation

就像 set 和 multiset 一样, map 和 multimap 也提供特殊查找函数, 以便利用内部树状结构获取较好的效能。

c.count(val);// 返回 key 为 val 的元素个数
c.find(val);//返回 key 为 val 的第一个元素, 找不到就返回 end
c.lower_bound(val);
c.upper_bound(val);
c.equal_range(val);



// !! Assignment

Map 和 multimap 只支持所有容器都提供的基本赋值操作。


c = c2;// 将 c2 的全部元素赋值给 c

c = rv;// 将 rvalue rv 的所有元素以 move assign 的方式给与 c

c.swap(c2);// 置换 c 和 c2 的元素
swap(c,c2);// 置换 c 和 c2 的元素


这些操作函数中, 赋值动作的两端容器必须拥有相同类型。尽管"比较准则"本身可能不同，但其类型必须相同。


// !! Iterator Function and Element Access

Map 和 multimap 不支持元素直接访问, 因此元素的访问通常是经由 range-based for循环或迭代器进行。不过有个例外: map 提供 at() 以及 subscript() 操作符可直接访
问元素。

c.begin();
c.cbegin();
c.end();
c.cend();

c.rbegin();
c.rend();

'和其他所有关联式容器一样,这里的迭代器是双向迭代器'。所以, 对于只能接受随机访问迭代器的 STL 算法(例如排序算法或随机乱序(random shuffling)算法), map 和 
multimap 就无福消受了。


更重要的是, 在 map 和 multimap 中, 所有元素的 key 都被视为常量。因此, 元素的实质类型是 pair<const Key,T>。这个限制是为了确保你不会因为变更元素的 key 而破坏
已排好的元素次序。


下面示范使用 range-based for 循环访问 map 元素:

std::map<std::string, float> coll;
...

for(auto &elem : coll){
    std::cout << "key is " << elem.first << "and value is " << elem.second << std::endl;
}


其中的 elem 是个 reference, 指向"容器 coll 中目前正被处理的元素"。因此 elem 的类型是 pair<const std::string, float>。表达式 elem.first 取得元素的 key, 
而表达式 elem.second 取得元素的 value。

另一个例子是以迭代器访问元素 (C++11 之前必须使用这种方法):

std::map<std::string, float> coll;
...

for(pos = coll.begin(); pos != coll.end(); ++pos){
    std::cout << "key is " << pos->first << ", value is " << pos->second << std::endl;
}

在这里, 迭代器 pos 被用来迭代穿越整个由"以 const string 和 float 组成的 pair"所构成的序列, 你必须使用 operator-> 访问每次访问的那个元素的 key 和 value。

如果你尝试改变元素的 key, 会引发错误:

elem.first = "hello";// ERROR at compile time
pos->first = "world";// ERROR at compile time

不过如果 value 本身的类型并非 const, 改变 value 没有问题:

elem.second = 3.14159;
pos->second = 3.14159;

如果你使用算法或 lambda 来操作 map 元素, 你必须很明确地声明元素类型:

std::map<std::string, float> coll;
...

std::for_each(coll.begin(), coll.end(),[](std::pair<const std::string, float>& elem)
{
    elem.second += 1.2f;
}
);


那么, 可以不写:

std::map<std::string, float>

而改为

std::map<std::string, float>::value_type;

或

decltype(coll)::value_type;

来声明元素类型。



如果你一定得改变元素的 key, 只有一条路: 以一个"value 相同"的新元素替换掉旧元素。

下面是个泛化函数:

namespace MyLib{
    template<typename Cont>
    inline replace_key(Cont& c, const typename Cont::key_type &old_key, const typename Cont::key_type &new_key)
    {
        typename Cont::iterator pos;
        pos = c.find(old_key);
        if(pos != c.end()){
            c.insert(typename Cont::value_type(new_key, pos->second));
            c.erase(pos);
            return true;
        }else{
            return false;
        }
    }
}


这个泛型函数的用法很简单, 把旧 key 和新 key 传递进去就行。例如:

std::map<std::string, float> coll;
...
MyLib::replace_key(coll,"old key","new key");

如果你面对的是 multimap, 情况也一样。


注意, map 提供了一种非常方便的手法, 让你改变元素的 key。只需如此这般:

coll["new key"] = coll["old key"];
coll.erase("old key");




// !! Inserting and Removing


c.insert(val);// 安插一个 val 拷贝,并返回新元素的位置
c.insert(pos, val);//安插一个 val  拷贝,并返回新元素的位置(pos 是个提示,指出安插动作的查找起点, 若提示恰当,可加快查找速度)

c.insert(beg.end);// 将区间[beg,end) 内所有元素的拷贝安插到 c

c.erase(val);// 移除与 val 相等的所有元素, 返回被移除元素的个数

c.erase(pos);// 移除 iterator 位置 pos 上的元素, 无返回值

c.clear();// 移除所有元素, 将容器清空


对于 multimap, C++11 保证 insert()、emplace() 和 erase() 都会保留等价元素的相对次序, 而新增（被安插）的元素则一定被放在既有的等价元素（群）的末尾。

安插一个 key/value pair 时, 你一定要记住, 在 map 和 multimap 内部, key 被视为常量。你要么得提供正确类型, 要么得提供隐式或显式类型转换。

自 C++11 起, 安插元素的最方便做法就是把它们 initializer list 的形式传进去


std::set<std::string, float> coll;
...
coll.insert({"London",2.12});



'有三种不同的方法可以将 value 传入 map 或 multimap 内':

1. 运用 value_type。为了避免隐式类型转换, 你可以利用 value_type 明确传递正确类型。value_type 是容器本身提供的类型定义。

std::map<std::string, float> coll;
...
coll.insert(std::map<std::string, float>::value_type("London",2.12));

或

coll.insert(decltype(coll).value_type("London",2.12));


2. 运用 pair<>。另一个做法是直接运用 pair<>


std::map<std::string, float> coll;

........

// use implicitly conversion
coll.insert(std::pair<std::string, float>("London",2.12));

// use no implicitly conversion
coll.insert(std::pair<const std::string, float>("London",2.12));

上述第一个 insert() 语句内的类型并不正确, 所以会被转换成真正的元素类型。为了做到这一点, insert() 成员函数被定义为 member template


3. 运用 make_pair()。C++11 面世之前最方便的办法是运用 make_pair() 函数, 它根据收到的两个实参构建出一个 pair 对象:


std::map<std::string, float> coll;
...

if(coll.insert(std::make_pair("London",2.12)).second){
    std::cout << "Ok could insert London, 2.12 " << std::endl;
}else{
    std::cout << "OOPs could not insert London, 2.12 " << std::endl;
}

欲移除"携带某个 value"的元素, 调用 erase() 即可办到:

std::map<std::string, float> coll;
...
coll.erase(key);

这个 erase() 版本会返回被移除元素的个数。如果你处理的是 map, erase() 的返回值只可能是 0或 1。

如果 multimap 内含重复元素, 你无法使用 erase() 删除重复元素中的第一个。但你可以这么做:

std::map<std::string, float> coll;
auto pos = coll.find(key);

if(pos != coll.end()){
    coll.erase(pos);
}

这里应该采用成员函数 find(), 而非 STL 算法 find(), 因为前者速度更快。

移除元素时,当心发生意外状况。移除迭代器所指对象时,有一个很大的危险,比如:


std::map<std::string, float> coll;
...

for(auto pos = coll.begin(); pos != coll.end(); ++pos){
    if(pos->second == value){
        coll.erase(pos);// RUNTIME ERROR
    }
}

'对 pos 所指元素调用 erase(), 会使 pos 不再成为 coll 的一个有效迭代器'。如果此后你未对 pos 重新设值就径直使用 pos, 前途未卜!事实上, 只要一个 ++pos 动作就会
导致不明确行为。


C++11 之后的解决方案很容易, 因为 erase() 总是返回一个迭代器指向其后继元素:

std::map<std::string, float> coll;
...
for(auto pos = coll.begin(); pos != coll.end();){
    if(pos->second == value)
    {
        pos = coll.erase(pos);
    }else
    {
        ++pos;
    }
}



// !! 将 Map 视为关联式数组(Associative Array)

通常, 关联式容器并不提供元素的直接访问, 你必须依靠迭代器。不过 map 是例外。Non-const map 提供了 subscript 下标操作符, 支持元素的直接访问。C++11 另外提供一个
成员函数 at(), 可用于 const 和 non-const map。

c[key];// 安插一个带着 key 的元素--如果尚未存在于容器中。返回一个 reference 指向带着 key 的元素
c.at(key);// 返回一个 reference 指向带着 key 的元素

at() 会依据它收到的"元素的 key" 取得元素的 value; 如果不存在这样的元素则抛出 out_of_range 异常。

'至于 operator[], 其索引就是 key。这意味着 operator[] 的索引可能属于任何类型, 不一定是整数。如此的接口就是所谓的关联式数组接口'。


"operator[] 的索引类型不必然是整数"并不是它和寻常 array 唯一不同之处。如果你选择某 key 作为索引, 容器内却没有相应元素, 那么 map 会自动安插一个新元素, 其
value 将被其类型的 default 构造函数初始化。因此, 你不可以指定一个"不具 default 构造函数"的 value 类型。注意, 基础类型都有一个 default 构造函数, 设立初值 0


关联式数组的行为方式可说是毁誉参半:

1. 优点是你可以通过更方便的接口对 map 安插新元素

std::map<std::string, float> coll;

coll["hello"] = 7.7;

其中的语句:

coll["hello"] = 7.7;

处理如下:

1. 处理 coll["hello"]

如果存在 key 为 "hello" 的元素, 上式会返回元素的 reference

如果没有任何元素的 key 是 "hello", 上式便为 map 自动安插一个新元素, 令其 key 为 "hello", 其 value 则以 d efault 构造函数完成, 并返回一个 reference 
指向新元素


2. 将 7.7 赋值给  value

接下来便是将 7.7 赋值给上述刚刚诞生的新元素

这样, map  之内就包含了一个 key 为 "hello" 的元素, 其 value  为 7.7


缺点是你有可能不小心误置新元素


// !! Map 和  Multimap 运用实例


// !! 在 Map/Multimap 身上使用算法和 Lambda

#include <map>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
    map<string, double> coll{{"hello",2.12},{"world",2.32}};

    for_each(coll.begin(), coll.end(),[](pair<const string, double>& elem){
        elem.second *= elem.second;
    });


    for_each(coll.begin(), coll.end(),[](decltype(coll)::value_type &elem){
        cout << elem.first << " " << elem.second << endl;
    });

    return 0;
}

一如所见, 对于 map, for_each() 被调用两次: 一次用来对每个元元素计算平方，一次用来打印每个元素。在第一次调用中, 元素类型被明确声明了出来, 而在第二次调用中, 用
的是 value_type。第一次调用中元素以 by reference 方式传递, 使其 value 得以被改动; 第二次调用用的是一个const reference, 避免产生非必要的拷贝。



// !! 将 Map 当作关联式数组 (Associative Array)


// !! 将 Multimap 当作字典(Dictionary)


// !! 查找具有某特定 Value 的元素


// !! 综合实例:运用 Map、String 并于运行期指定排序准则

这里再示范一个例子, 针对高级程序员而非 STL 初学者。你可以把它视为展现 STL 威力与疑难的一个范例。更明确地说, 这个例子展现了以下技巧:

1. 如何使用 map, 包括使用关联式数组接口

2. 如何撰写和使用函数对象--function object

3. 如何在运行期定义排序准则--sorting criterion

4. 如何在"大小写无关"的情况下比较字符串

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

using namespace std;

class RuntimeStringCmp {
 public:
  enum cmp_mode { normal, nocase };
  RuntimeStringCmp(cmp_mode m = normal) : mode(m) {}

  bool operator()(const string& s1, const string& s2) const {
    if (mode == normal) {
      return s1 < s2;
    } else {
      return lexicographic_compare(s1.begin(), s1.end(), s2.begin(), s2.end(),
                                   nocase_compare);
    }
  }

 private:
  const cmp_mode mode;
  static bool nocase_compare(char c1, char c2) {
    return toupper(c1) < toupper(c2);
  }
};

void fillAndPrint(StringStringMap & coll);

typedef std::map<std::string, std::string> StringStringMap;

int main(int argc, char** argv) {

    StringStringMap coll1;
    fillAndPrint(coll1);

    RuntimeStringCmp ignoreCase(RuntimeStringCmp::nocase);
    StringStringMap coll2(ignoreCase);

    fillAndPrint(coll2);

    return 0;
}

void fillAndPrint(StringStringMap& coll) {
    coll["hello"] = "world";
    coll["tell"] = "me";
    coll["fuck"] = "you";
    coll["bluent"] = "Green";
    coll["black"] = "night";
    coll["bunny"] = "pink";

    // print all elements
    for(auto &elem : coll) {
        cout << elem.first << " " << elem.second << endl;
    }
}




// !! Unordered Container

Hash table, 作为一个重要的用于集合(collection) 的数据结构, 并不是 C++ 标准库第一版的一部分。它们并不是原始 STL  的一部分, 标准委员会认为, 将它们纳入
C++98 的提案太晚呈现了。然而, 自 TR1 起, 带有 hash table 特性的容器终于走入了 C++ 标准。

TR1 引入了一个以 hash table 为基础的容器群, 这些标准化的 class 所提供的特性结合原有实现, 但又不完全吻合其中任何一个。为了避免名称冲突, 它们选择不一样的 class 
名称。最终决议是, 提供所有原本已存在的那些 associative 容器, 但改而带着前缀 unordered_。

这也显示它和其他 associative 容器之间的最重要差异: "以 hash table 为基础"的容器，其内的元素没有清晰明确的次序。


概念上, unordered 容器以一种随意顺序包含你安插进去的所有元素。也就是说, 你可以把这个容器想成一个袋子(bag): 你可以放元素进去, 但当你打开袋子对所有元素做某些事,
你是以一种随机的次序来访问它们。所以, 相比于 set 和 map, 这里不需要排序准则; 相比于  sequence 容器, 你没有语义可用来放元素到某个特定位置。


就像各个 associative 容器那样, 这里的个别 class 也互不相同:

1. Unordered set 和 multiset 存放的是某特定类型的 value, 而 unordered map 和 multimap 存放的元素都是 key/value pair,  其中 key 被用来作为"存放和查
   找某特定元素(包含相应的 value)"的依据。

2. Unordered set 和 map 都不允许元素重复, 而 unordered multiset 和 multimap 都允许


欲使用一个 unordered set 或 unordered multiset,你必须首先包含头文件 <unordered_set>。欲使用一个 unordered map 或  multimap, 你必须首先包含头文件
<unordered_map>:

#include <unordered_map>
#include <unordered_set>


在那里, 上述四种类型分别被定义为 namespace std 内的 class template:

namespace std{

    template <typename T, typename Hash = hash<T>, 
    typename EpPred = equal_to<T>,typename Allocator = allocator<T>>
    class unordered_set;

    template <typename T, typename Hash = hash<T>,
    typename EpPred = equal_to<T>,typename Allocator = allocator<T>>
    class unordered_multiset;

    template <typename Key,typename T, typename Hash = hash<T>,
    typename EpPred = equal_to<T>,typename Allocator = allocator<T>>
    class unordered_map;

    template <typename Key,typename T, typename Hash = hash<T>,
    typename EpPred = equal_to<T>,typename Allocator = allocator<T>>
    class unordered_multimap;
}


一个 unordered set 或 unordered multiset 的元素类型, 可以是任意指派的 T, 只要它是可比的(comparable)

对于 unordered map 和 unordered multimap, 第一个 template 参数是元素的 key 类型, 第二个 template 参数是元素的 value 类型。一个 unordered map 
或 unordered multimap 的元素可拥有任何类型的 Key 和 T,只要它们满足以下两个条件:

1. Key 和 value 都必须可被复制或可被搬移(copyable or movable)

2. Key 必须可被"等价准则"拿来比较

注意, 元素类型 (value_type) 是个 pair<const Key,T>

可有可无的第二或第三 template 参数用来定义 hash function。如果没有指明使用哪个 hash function, 就使用默认的 hash<>, 这是个 function object, 定义于
<functional>, 可用于所有整数类型、浮点数类型、pointer、string 及若干特殊类型。

可有可无的第三或第四 template 参数用来定义等价准则。

可有可无的第四或第五 template 参数用来定义内存模型。默认的内存模型(memory model) 是 allocator, 由 C++ 标准库提供。


// !! Unordered 容器的能力

所有标准化 unordered container class 都以 hash table 为基础。尽管如此, 仍允许种种实现选择。通常 C++ 标准库并不指明所有实现细节, 这样才能允许种种可能的选择
, 但 unordered 容器仍有若干被具体指明的性质, 基于以下假设:

1. 这些 hash table 使用 chaining 做法, 于是一个 hash code 将被关联至一个 linked list

2. 上述那些 linked list 是单链或双链, 取决于实现。C++standard 只保证它们的 iterator 至少是 forward iterator

3. 关于  rehashing, 有各式各样的实现策略:

    1. 传统做法是, 在单一 insert 或 erase 动作出现时, 有时会发生一次内部数据重新组织

    2. 所谓递进式 incremental hashing 做法是, 渐进改变 bucket 或 slot 的数量, 这对即时 real-time 环境特别有用, 因为在其中突然放大 hash table 的代价也
       许太高


对于每个将被存放的元素(一个 key/value pair)=, hash function 会把 key 映射至 hash table 内的某个 bucket (slot) 中。每个 bucket 管理一个单向
linked list, 内含所有会造成 hash function 产出相同数值的元素。


内部使用 hash table, 其主要优点是它惊人的运行期行为。假设拥有良好的 hashing 策略, 并且有良好的实现, 你可以保证在安插、删除、查找元素时获得摊提常量时间(之所以是摊
提的,因为偶尔发生的 rehashing 可能是个大型操作，带着线性复杂度)。


Unordered 容器的几乎所有操作——包括 copy construction 和 assignment, 元素的安插和寻找, 以及等价比较——的预期行为, 都取决于 hash function 的质量。

如果 hash function 对不同的元素竟产生相等数值, hash table 的任何操作都会导致低下的执行效率。这个缺点不完全是由于数据结构本身, 也因为客户对此没有足够的意识。


Unordered 容器比起寻常的 associative 容器, 也有若干缺点:

1. Unordered 容器不提供 operator<, >、<= 和 >= 用以安排布置(order)这些容器的多重实例。然而提供了 == 和 != 

2. 不提供 lower_bound() 和 upper_bound()

3. 由于 iterator 只保证至少是个 forward iterator, 因此反向 iterator 都不提供

由于元素的(key) value 具体关系到元素的位置--这里指的是 bucket entry——你不可以直接改动元素的(key)value。因此, 很像 associative 容器那样, 欲改动一个元素的
value, 你必须先移除拥有旧 value 的元素, 然后安插一个拥有新 value 的新元素。

这个接口反映出以下行为:

1. Unordered 容器不提供直接元素访问操作

2. 通过 iterator 进行的间接访问有其束缚: 从 iterator 的角度观之, 元素的(key) value 是常量


身为一个程序员, 你可以指定若干会影响 hash table 行为的参数:


1. 你可以指定 bucket 的最小数量

2. 你可以(并且有时候必须)提供你自己的 hash function

3. 你可以(并且有时候必须) 提供你自己的等价准则

4. 你可以指定一个最大负载系数 maximum load factor, 一旦超过就会自动 rehashing

5. 你可以强迫 rehashing


但是你不能够影响以下行为:

1. 成长系数(growth factor), 那是自动rehashing时用来成长或缩小 list of buckets 的系数

2. 最小负载系数(minimum load factor), 用来强制进行 rehashing


注意, rehashing 只可能发生在以下调用之后: insert()、rehash()、reserve() 或clear()


在那些支持等价(equivalent) key的容器内, 也就是说在 unordered multiset 和 multimap 内, 带有等价 key 的元素将会被相邻排列。Rehashing 以及其他可能于内部改变
元素次序的操作, 都会维持带有等价 key 的元素的相对次序。



// !! 创建和控制 Unordered 容器


// !! Create, Copy, and Destroy


unordered c;// Default 构造函数, 建立一个












