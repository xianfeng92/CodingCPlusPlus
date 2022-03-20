
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













