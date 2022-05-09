// !! 泛型编程风格

Standard Template Library(STL) 主要由两种组件构成: 一是容器(container), 包括 vector、list、set、map 等类; 另一种组件是用以操作这些容器的所谓泛型算
法(generic algorithm), 包括 find()、sort()、replace()、merge()等。


vector 和 list 这两种容器是所谓的顺序性容器(sequential container)。顺序性容器会依次维护第一个、第二个……直到最后一个元素。'我们在顺序性容器身上主要进行所谓
的迭代(iterate)操作'。

map 和 set 这两种容器属于关联容器(associative container)。'关联容器可以让我们快速查找容器中的元素值'。所谓 set, 其中仅含有 key。'我们对它进行查询操作, 
为的是判断某值是否存在于其中'。

如果我们想要建立一组索引表, 用来记录出现于新闻、故事中的字眼, 我们可能会希望将一些中性字眼如 the、an、but 排除掉。在让某个字眼进入索引表之前, 我们要先查询
excluded_word 这么一个 set, 如果这个字眼在里面, 我们便忽略它不再计较; 反之则将它加入索引表。

泛型算法提供了许多可作用于容器类及数组类型上的操作。'这些算法之所以被称为泛型 (generic), 是因为它们和它们想要操作的元素类型无关'。

举个例子, 它们和元素类型究竟是 int、double 或  string 全然无关。它们同样也和容器类彼此独立(不论容器是 vector、list 或 array)


泛型算法系通过 function template 技术, 达到"与操作对象的类型相互独立"的目的。而实现"与容器无关"的诀窍, 就是不要直接在容器身上进行操作。

而是借由一对 iterator (first 和 last), 标示我们要进行迭代的元素范围。如果  first 等于 last, 算法便只作用于 first 所指元素。如果 first 不等于 last,算
法便会首先作用于 first  所指元素身上, 并将 first 递增, 指向下一个位置, 然后再比较 first 和  last 是否相等, 如此持续进行, 直到 first 等于  last 为止。



// !! 指针的算术运算

The Arithmetic of Pointers

假设我们需要完成以下工作。给定一个储存整数的 vector,以及一个整数值。如果此值存在于 vector 内, 我们必须返回一个指针指向该值; 反之则返回  0,表示此值并不在
vector 内。

以下便是我的做法:

int * find(const vector<int> &vec, int value){
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] == value){
            return &vec[i];
        }
    }
    return 0;
}

测试这个函数, 发现其结果的确满足我们的需求。

接下来我们又获得一个新任务: 想办法让这个函数不仅可以处理整数, 更可以处理任何类型--前提是该类型定义有 equality 运算符。


template<typename elemType>
elemType * find(const vector<elemType> &vec, elemType elem) {
    for (int i = 0; i < vec.size(); ++i){
        if(vec[i] == elem){
            return &vec[i];
        }
    }
    return 0;
}

再次测试这个函数, 其执行结果同样符合我们的需求。

下一个任务, 便是要让这个函数同时可以处理 vector 与 array 内的任意类型元素--当然该类型的 equality 运算符皆已定义。首先映入脑海的想法便是将此函数重载
(overload), 一份用来处理 vector, 另一份用以处理 array。


有一种存在已久的难题对策, 就是将问题分割为数个较小、相对而言较简单的子问题。

本例之中我们的大问题可切割为:1. 将 array 的元素传入 find(), 而非指明该 array; 2.将 vector 的元素传入 find() 而不指明该 vector。理想情况下, 这两个问
题的解法之中会包含我们最初问题的共通解法。


首先解决 array 的处理问题。如何才能够在不指定 array 的情形之下将其元素传入 find() 呢?

如果我们能够完全理解我们企图解决的问题, 那么编写程序便有如探囊取物。本例中如果能够清楚了解 array 如何被传入函数, 以及 array 如何被函数返回,将非常有助于解
答。当我写下:

int min(int array[24]){
    ...
}

min() 似乎仅能接受某个拥有 24 个元素的 array, 并且以传值方式传入。事实上这两个假设都是错的: array 并不会以传值方式复制一份, 而且我们可以传递任意大小的
array 给 min()。我知道你一定在想, 怎么会这样呢?


指向 array 开头的指针, 使我们得以开始对 array 进行读取操作。接下来我们必须设法告诉 min(), 应该在何处停止对 array 的读取。解法之一是: 增加一个参数, 用来表
示 array 的大小。

以下便是采用此法完成的 find(), 声明如下:

template <typename elemType>
elemType *find(const elemType* array, int size, const elemType &value) {
    ...
}

解法之二则是传入另一个地址, 指示 array 读取操作的终点。(我们将此值称为"标兵")


template <typename elemType>
elemType *find(const elemType* array, elemType *end, const elemType &value) {
    ...
}

这种解法最让人感兴趣的地方便是, array 从参数列表中彻底消失了——这形同解决了我们的第一个小问题。

虽然 array 以第一个元素的指针传入 find()中, 但我们看到, 仍然可以通过 subscript 运算符访问 array 的每个元素, 就如同此 array 是个对象一般。为什么呢?因为事
实上'所谓下标操作就是将 array 的起始地址加上索引值, 产生出某个元素的地址, 然后该地址再被 dereference 以返回元素值'。

template <typename elemType>
elemType * find(const elemType *first, const elemType *last, const elemType &value){
    if(!first || !last) return 0;
    for(; first != last; ++first){
        if(*first == value){
            return first;
        }
    }
    return 0;
}

上述函数完成了我们所设定的两个子任务中的第一个: 我们已经完成 find() 的实现, 而且不论数组元素的类型是什么, 我们都可以访问数组中的每个元素。

接下来, 我们该如何调用 find() 呢? 下列程序代码会用到先前所说的指针算术运算:

int ia[8] = {0,1,2,3,4,5,6,7};
double da[8] = {0,1,2,3,4,5,6,7};
string sa[4] = {"hello", "world", "today", "yes"};

int *pa = find(ia, ia + 8, 4);
double *pd = find(da, da + 8, 4);
string *ps = find(sa, sa + 4, 4);

我们传入第二个地址, 标示出数组最后一个元素的下一个地址。这合法吗 ? 是的, '不过倘若我们企图对此地址进行读取或写入操作, 那就不合法'。

如果我们仅仅是将该地址拿来和其他元素的地址进行比较, 那就完全不会有任何问题。'数组最后一个元素的下一个地址, 扮演着我们所说的标兵角色, 用以指示我们的迭代操作何
时完成'。


应该如何完成第二个子任务呢? 这个任务是说, 不论 vector 的元素类型是什么, 都能一一访问 vector 内的每个元素。要知道, vector 和 array 相同, 都是以一块连续内
存储存其所有元素, 所以我们可以使用和 array 一样的处理方式, 将一组用来表示"启始地址/结束地址"的参数传入 find()。但是, 切记, vector 可以是空的, array
则不然。


vector<string> svec;

比较保险的方法是, 先确定 svec 不为空:

if(!svec.empty()) {
    ...
}


虽然这样比较安全, 但对用户来说过于累赘。

'通常我们会将"取用第一个元素的地址"的操作包装为函数', 像下面这样:

template <typename elemType>
inline elemType* begin(const std::vector<elemType> & vec){
    return vec.empty() ? 0 : vec;
}


其对应函数 end(), 会返回 0 或是 vector 最后元素的下一个地址。

采用这种方式, 我们便有了安全的、放之四海而皆准的方式, 使 find() 应用于任意 vector 之上:

find(begin(vec), end(vec), search_value);

开始有人击节叫好了。现在让我们扩展 find() 的功能, 令它也能支持标准库所提供的 list 类别。说实在的，这又是一个难题。

list 也是一个容器。不同的是, list 的元素以一组指针相互链接(linked): 前向(forward) 指针指向下一个 next 元素, 后向 backward 指针指向上一个 preceding 
元素。

因此,指针的算术运算并不适用于 list, 因为指针的算术运算必须首先假设所有元素都储存在连续空间里, 然后才能根据当前的指针,加上元素大小之后,指向下一个元素。这是
先前 find() 的实现之中最基本的假设。不幸的是, 当我们想要取得 list 的下一个元素时, 这一假设并不成立。


首先浮起的念头, 便是再写一份 find() 函数, 使其有能力处理 list 对象。于是我们宣布, array、vector、list 的指针行为大相径庭, 以致于无法以一个共通的语法来取
得其下一元素。

这样的说法对错参半。对的部分是, 它们的底层指针工作方式, 就标准语法而言的确是大不相同。错的部分则是, 我们不需要提供另一个 find() 函数来支持 list。事实上,除
了参数列表之外, find() 的实现内容一点也不需要改变。

'解决这个问题的办法是,在底层指针的行为之上提供一层抽象,取代程序原本的"指针直接操作"方式'。我们把底层指针的处理通通放在此抽象层中, 让用户无须直接面对指针操作。
这个技巧使得我们只需提供一份 find()函数, 便可以处理标准库所提供的所有容器类。


// !! 了解 Iterator (泛型指针)


Making Sense of Iterators

很显然,我们一定会问,这个抽象层如何实现?

是的, 我们需要一组对象,可提供有如内置运算符 (++, *, ==, !=)一般的运算符, 并允许我们只为这些运算符提供一份实现代码即可。我们可以利用 C++ 的类机制来达到目
的。接下来我要设计一组 iterator class, 让我们得以使用"和指针相同的语法"来进行程序的编写。

举个例子, 如果 first 和 last 都是 list 的 iterator, 我们可以这样写:

while (first != last) {
    cout << *first << " ";
    ++first;
}

这就好像把 first 和 last 当作指针一样。唯一的差别在于其 dereference (*)运算符、inequality (!=)运算符、increment (++) 运算符乃是由 iterator class 
内相关的 inline 函数提供。

对 list iterator 而言, 其递增函数会沿着 list 的指针前进到下一个元素; 对 vector iterator 而言, 其递增函数前进至下一个元素的方式, 是将目前的地址加上一个
元素的大小。


如何取得 iterator 呢 ?

每个标准容器都提供有一个名为 begin() 的操作函数, 可返回一个 iterator, 指向第一个元素。另一个名为 end() 的操作函数会返回一个 iterator, 指向最后一个元素的
下一位置。因此, 不论此刻如何定义 iterator 对象, 以下都是对 iterator 进行赋值 assign、比较 compare、递增 increment、提领 dereference 操作:

for(iter = svec.begin(); iter != svec.end();++iter){
    cout << *iter << " ";
}

在我开始解说如何定义 iterator 之前, 让我们思考一下, 哪些信息是这份定义应该提供的: 1. 迭代对象(某个容器)的类型, 这可用来决定如何访问下一元素; 2. iterator 所
指的元素类型, 这可决定 iterator 提领操作的返回值。

iterator 的一个可能的定义形式, 便是将上述两个类型作为参数传给 iterator class:

iterator<vector, string> iter;


实际语法看起来更复杂些(至少第一眼是如此), 并提供了更优雅的解法。


vector<string> svec;
...
vector<string>::iterator iter = svec.begin();

此处 iter 被定义为一个 iterator, 指向一个 vector, 后者的元素类型为 string。

'双冒号 :: 表示此 iterator 乃是位于 string vector 定义内的嵌套 nested 类型'。

现在我要重新实现 find(), 让它同时支持两种形式: 一对指针, 或是一对指向某种容器的 iterator。还不错。我们让 find() 有了更大的通用性——远超过我们先前所能想
象的境界。

template<typename IteratorType, typename elemType>
IteratorType find(IteratorType begin, IteratorType end, const elemType& value){
    for(; begin != end; ++begin){
        if(*begin == value){
            return begin;
        }
    }
    return 0;
}

find() 的实现使用了底部元素所属类型的 equality 运算符。如果底部元素所属类型并未提供这个运算符, 或如果用户希望赋予 equality 运算符不同的意义, 这个 find()
的弹性便嫌不足了。如何才能增加其弹性? 解法之一便是传入一个函数指针, 取代原本固定使用的 equality 运算符。

总共有超过 60 的泛型算法, 以下列出一部分。

1. 搜索算法 search algorithm: find(), count(), adjacent_find(), find_if(), count_if(), binary_search(), find_first_of()


2. 排序 sorting 及次序整理 ordering 算法: merge(), partial_sort(), partition(), random_shuffle(), reverse(), rotate(), sort()


3. 复制 copy、删除 deletion、替换 substitution 算法: copy(), remove(), remove_if(), replace(), replace_if(), swap(), unique()


4. 关系 relational 算法: equal(), includes(), mismatch()

5. 生成 generation 与质变 mutation 算法

6. 数值 numeric 算法: accmulate()

7. 集合 set 算法: set_union(), set_difference()



// !! 所有容器的共通操作


Operations Common to All Containers

下列为所有容器类 (以及string类) 的共通操作:

● equality == 和 inequality != 运算符, 返回 true 或 false

● assignment =运算符, 将某个容器复制给另一个容器

● empty() 会在容器无任何元素时返回 true, 否则返回 false

● size() 返回容器内目前持有的元素个数

● clear() 删除所有元素


以下函数实际演练了上述操作:

void comp(vector<int> &vl, vector<int> &v2){
    if(v1 == v2) return;
    if(v1.empty() || v2.empty()) return;

    vector<int> t;
    t = v1.size() > v2.size() ? v1 : v2;
    //...
    t.clear();
}


每个容器都提供了 begin() 和 end() 两个函数, 分别返回指向容器的第一个元素和最后一个元素的下一位置的 iterator:


● begin() 返回一个 iterator, 指向容器的第一个元素

● end() 返回一个 iterator, 指向容器的最后一个元素的下一位置


'通常我们在容器身上进行的迭代操作都是始于 begin() 而终于 end()'。所有容器都提供 insert() 用以插入元素, 以及  erase() 用以删除元素。

● insert() 将单一或某个范围内的元素插入容器内


● erase() 将容器内的单一元素或某个范围内的元素删除


// !! 使用顺序性容器

Using the Sequential Containers

顺序性容器用来维护一组排列有序、类型相同的元素, 其中有第一、第二……以此类推,乃至最后一个元素。

vector 和 list 是两个最主要的顺序性容器。vector 以一块连续内存来存放元素。对 vector 进行随机访问 random access -- 例如先取其第 5 个元素, 再取其第
17  个元素, 然后取其第 9 个元素--颇有效率; vector 内的每个元素都被储存在距离起始点的固定偏移位置上。如果将元素插入任意位置, 而此位置不是 vector 的末端,那
么效率将很低, 因为插入位置右端的每个元素, 都必须被复制一份, 依次向右移动。同样道理,  删除 vector 内最后一个元素以外的任意元素, 同样缺乏效率。


list 系以双向链接 double-linked 而非连续内存来储存内容, 因此可以执行前进或后退操作。

list 中的每个元素都包含三个字段: value、back 指针、front 指针。在 list 的任意位置进行元素的插入或删除操作, 都颇具效率, 因为 list 本身只需适当设定 back
指针和 front 指针即可。但是如果要对 list 进行随机访问操作, 则效率不彰。


'vector 比较适合表示数列。为什么这么说呢? 因为我们会有许多随机访问的机会'。

什么时候使用 list 较为恰当呢? 如果我们想要从档案中读取分数, 并希望由低而高地加以排序储存, 那么, 每当我们读入一个分数, 便可能需要将它随机插入到容器内。这种
情况下 list 比较适当。

第三种顺序性容器是所谓的 deque (读作 deck)。deque 的行为和 vector 颇为相似--都以连续内存储存元素。


和 vector 不同的是, deque 对于最前端元素的插入和删除操作, 效率更高;  末端元素亦同。如果我们需要在容器最前端插入元素, 并执行末端删除操作，那么 deque 便很理
想。 标准库的 queue 便是以 deque 实现, 也就是说, 以 deque 作为底部储存元素。


要使用顺序性容器, 首先必须包含相关的头文件,也就是以下三者之一:

#include <vector>
#include <list>
#include <deque>


定义顺序性容器对象的方式有五种:

1. 产生空的容器

list<string> slist;
vector<int> ivec;


2. 产生特定大小的容器, 每个元素都以其默认值作为初值

list<string> slist(1024);
vector<int> ivec(1024);


3. 产生特定大小的容器, 并为每个元素指定初值


vector<int> ivec(1024, -10);


4. 通过一对 iterator 产生容器, 这对 iterator 用来标示一整组作为初值的元素的范围

5. 根据某个容器产生出新容器。复制原容器内的元素,作为新容器的初值

vector<int> ivec(1024, 100);

vector<int> ivec1(ivec);// copy  constructor


有两个特别的操作函数, 允许我们在容器末尾进行插入和删除操作: push_back() 和 pop_back()。push_back() 会在末端插入一个元素, pop_back() 会删除最后一个元素。

除此之外, list 和 deque (但不包括 vector)还提供了 push_front() 和 pop_front()。pop_back() 和  pop_front() 这两个操作函数并不会返回被删除的元素值。
因此, 如果要读取最前端元素的值, 应该采用 front()。如果要读取末端元素的值, 应该采用 back()。


下面是个例子:

#include <deque>

std::deque<int> a_line;
int ival;
while (cin >> ival){
    a_line.push_back(ival);
    int current = a_line.front();
    ...
    a_line.pop_front();
}

push_front() 和 push_back() 都属于特殊化的插入 insertion 操作。每个容器除了拥有通用的插入函数  insert(), 还支持四种变形。

1. iterator insert(iterator position,elemType value) 可将 value 插入 position 之前。它会返回一个 iterator, 指向被插入的元素。
以下程序代码会将 ival 插入 list 内, 并维持其递增次序:

list<int> i_list;
// fill list with elements
list<int>::iterator iter = i_list.begin();

while(iter != i_list.end()) {
    if(*iter > ival){
        i_list.insert(iter, ival);
        break;
    }
    --iter;
}
if(iter == i_list.end()) {
    l_list.push_back(ival);
}


2. void insert(iterator position, int count, elemType value)  可在 position 之前插入 count 个元素,这些元素的值都和 value 相同。


string sval("Dart Two");
list<string> s_list;
// fill s_list with values

list<string>::iterator iter = std::find(s_list.begin(), s_list.end(), sval);
s_list.insert(iter, 8, string("dummy"));


3. void insert(iterator1 position, iterator2 first,iterator2 last) 可在 position 之前插入 [first,last) 所标示的各个元素

int ia1[10] = {1,2,3,4,5,6,7,8,9,10};
int ia2[3] = {4,5,6};

list<int> elems(ia1, ia1 + 7);

list<int>::iterator iter = find(elems.begin(), elems.end(), 5);
elems.insert(iter,ia2, ia2 + 2);



pop_front() 和 pop_back() 都属于特殊化的删除 erase 操作。每个容器除了拥有通用的删除函数 erase(), 还支持两种变形。

1. iterator erase(iterator posit) 可删除 posit 所指的元素。例如, 面对先前定义的 slist, 我删除其中第一个"元素值为 str"的元素:

list<string>::iterator iter = find(slist.begin(), slist.end(), "str");
slist.erase(iter);


2. iterator erase(iterator first, iterator last) 可删除 [first, last) 范围内的元素



// !! 使用泛型算法

Using the Generic Algorithms

欲使用泛型算法, 首先得包含对应的 algorithm 头文件:

#include <algorithm>

让我们以 vector 来储存数列, 以此练习泛型算法的运用。如果给定的值已存在于数列之中, is_elem() 必须返回 true; 否则返回 false。

下面为四种可能被我们采用的泛型搜索算法:

1. find() 用于搜索无序 unordered 集合中是否存在某值。搜索范围由 iterator [first, last)标出。如果找到目标, find() 会返回一个 iterator 指向该值, 否则
   返回一个 iterator 指向 last


2. binary_search() 用于有序(sorted) 集合的搜索。如果搜索到目标, 就返回 true; 否则返回 false。binary_search() 比 find() 更有效率


3. count() 返回数值相符的元素数目


4. search() 比对某个容器内是否存在某个子序列。例如给定序列 {1,3,5,7,2,9}, 如果搜索子序列 {5,7,2}, 则 search() 会返回一个 iterator 指向子序列起始处。
   如果子序列不存在, 就返回一个 iterator 指向容器末尾。


由于我们的 vector 必定以递增顺序储存其值, 因此 binary_search() 是我们的最佳选择:

#include <algorithm>

bool is_elem(vector<int> &vec, int elem){
    return binary_search(vec.begin(), vec.end(), elem);
}


有个方法可以帮助我们取得数列最大元素值---泛型算法 max_element()。


binary_search() 要求, 其作用对象必须经过排序 sorted, 这一责任由程序员承担。


// !! 如何设计一个泛型算法

How to Design a Generic Algorithm

下面是我们的新任务。用户给予一个整数 vector, 我们必须返回一个新的  vector, 其中内含原  vector 之中小于 10 的所有数值。

一个快速但缺乏弹性的解法是:

vector<int> less_than_10(vector<int> &vec){
    vector<int> nvec;
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] < 10){
            nvec.push_back(ival[i]);
        }
    }
    return nvec;
}

如果用户想找到所有小于 11 的元素, 我们要么得建立一个新函数, 要么就得将此函数通用化, 让用户得以指定某个上限值,像下面这样:

vector<int> less_than(const vector<int> &vec, int less_than_value){
    //...
}

下一个任务难度颇高。我们必须允许用户指定不同的比较操作, 像是大于、小于，等等。

如何才能将"比较操作"参数化呢?

有一个解法: 以函数调用来取代 less-than 运算符。

加入第三个参数 pred, 用它来指定一个函数指针, 其参数列表有两个整数, 返回值为 bool。至此, less_than() 的名称已不再适当,让我们称它为 filter() 吧:

vector<int> filter(vector<int> &vec, int filter_value, bool(*pred)(int,int));

站在用户的角度来考虑,为方便起见, 我们同时定义了许多可传给 filter() 的关系(relational)比较函数:

bool less_than(int v1,  int v2) {
    return v1 < v2 ? true : false;
}

bool greater_than(int v1,  int v2){
    return v1 > v2 ? true : false;
}

调用 filter() 时, 用户亦可传入上述函数,或其他自定义的关系比较函数。'唯一一个限制就是, 这些函数必须返回 bool, 而且参数列表中只接受两个整数'。


以下是 filter() 的使用方式:

vector<int> big_vec;
int value;
vector<int> lt_10 = filter(big_vec, value, less_than);


vector<int> filter(vector<int> &vec, int filter_value, bool(*pred)(int, int)){
    vector<int> nvec;
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] < filter_value){
            nvec.push_back(vec[i]);
        }
    }
    return nvec;
}

这个 filter() 使用 for 循环遍历每个元素。

现在让我们以泛型算法 find_if() 来取代 for 循环的使用。我将 find_if() 反复作用于数列身上, 找出符合条件的每一个元素——所谓"条件"则由用户指定的函数指针定义。
这要怎么做到呢?

以下程序代码中, count_occurs() 说明如何在"不对任一元素进行两次以上的查看"前提下, 反复地在容器身上进行 find():

int count_occurs(const vector<int> &vec, int val){
    vector<int>::const_iterator iter = vec.begin();
    int occurs_count = 0;
    while((iter = find(iter, vec.end(), val)) != vec.end()) {
        ++occurs_count;
        ++iter;
    }
}

我们在 while 循环之内将 find() 的返回值设给 iter。find() 返回一个 iterator, 指向元素值为 val 的元素。如果没有找到任何符合条件的元素, 就返回一个等同于
vec.end() 的 iterator。一旦  iter 等同于 vec.end(), 循环即终止。


// !! Function Object

重新实现 filter() 以便支持 find_if() 之前,让我们先看看标准库预先定义好的许多 function object。'所谓 function object 是某种 class 的实例对象,这类
class 对 function call 运算符做了重载操作, 如此一来可使 function object 被当成一般函数来使用'。

function object 实现了我们原本可能以独立函数加以定义的事物。但又何必如此呢? 

主要是为了效率。我们可以令 call 运算符成为 inline, 从而消除"通过函数指针来调用函数"时需付出的额外代价。


标准库事先定义了一组 function object, 分为算术运算(arithmetic)、关系运算(relational) 和逻辑运算(logical)三大类。

1. 六个算术运算: plus<type>, minus<type>, negate<type>, multiplies<type>, divides<type>, modules<type>

2. 六个关系运算: less<type>, less_equal<type>, greater<type>, greater_equal<type>, equal_to<type>, not_equal_to<type>

3. 三个逻辑运算，分别对应于 &&、||、!运算符: logical_and<type>, logical_or<type>, logical_not<type>


欲使用事先定义的function object,首先得包含相关头文件:

#include <functional>

举个例子, 默认情形下, sort() 会使用底部元素的类型所提供的 less_than 运算符, 将元素升序排序。如果我们传入 greater_than function object, 元素就会以降序
排序:

std::vector<int> svec;
// fill the vector with elements
std::sort(svec.begin(), svec.end(), std::greater<int>());

其中的:

greater<int>

会产生一个未命名的 class template object, 传给 sort()。


binary_search() 期望其搜索对象先经过 less_than 运算符排序。为了正确搜索 vector, 我们现在必须传给它某个 function object object, 供 vector 排序使用:


std::binary_search(vec.begin(), vec.end(),value, std::less<int>());




// !! Function Object Adapter

上述的 function object 并不那么恰好符合 find_if() 的需求。举个例子, function object less<type> 期望外界传入两个值, 如果第一个值小于第二个值就返回
true。本例中, 每个元素都必须和用户所指定的数值进行比较。理想情形下, 我们需要做的就是将 less<type> 转化为一个一元运算符。这可通过"将其第二个参数绑定 bind 至
用户指定的数值"完成。

这么一来 less<type> 便会将每个元素拿出来一一与用户指定的数值比较。真的可以做到这样吗? 是的, 标准库提供的所谓 adapter 便应此而生。

function object adapter 会对 function object 进行修改操作。

所谓 binder adapter 会将 function object 的参数绑定至某特定值, 使 binary  function object 转化为 unary function object。

标准库提供了两个 binder adapter: bind1st 会将指定值绑定至第一操作数, bind2nd 则将指定值绑定至第二操作数。以下是修改后的  filter(), 使用了
bind2nd adapter:

vector<int> filter(const vector<int> &vec, int value, std::less<int> &le){
    vector<int> nvec;
    vector<int>::const_iterator iter = vec.begin();
    std::bind2nd(less<int>, value);
    while((iter = std::find(vec.begin(), vec.end(), value)) != vec.end()){
        nvec.push_back(*iter);
        ++iter;
    }
    return nvec;
}

接下来如何消除 filter() 与 vector 元素类型, 以及 filter() 与 vector 容器类型的依赖关系, 以使 filter() 更加泛型化呢? 为了消除它和元素类型间的依赖性,
我们将 filter() 改为 function template, 并将元素类型加入 template 的声明中。为了消除它和容器类型间的依赖性, 我们传入一对 iterator [first,last),
并在参数列表中增加另一个 iterator, 用以指定从何处开始复制元素。


template<typename InputIterator, typename OutputIterator, typename elemType, typename comp>
OutputIterator filter(InputIterator first, InputIterator last, OutputIterator output, const elemType &value, const comp &pred) {
    while((first = find_if(first, last,bind2nd(pred, value))) != last) {
        cout << "find value " << *first << " ";
        *output = *first;
    }
    return output;
}



一开始我写了一个函数, 它可以找出 vector 内小于 10 的所有元素。然而函数过于死板, 没有弹性。

接下来, 我为函数加上了一个数值参数, 让用户得以指定某个数值, 以此和 vector 中的元素做比较。

接着, 我又加上了一个新参数: 一个函数指针, 让用户得以指定比较方式。

然后, 我引入 function object 的概念, 使我们得以将某组行为传给函数, 此法比函数指针的做法效率更高。

最后, 我将函数以 function template 的方式重新实现。

为了支持多种容器, 我传入了一对 iterator, 标示出一组元素范围; 为了支持多种元素类型, 我将元素类型参数化, 也将应用于元素上的"比较操作"参数化, 以便得以同时支持
函数指针和 function object 两种方式。

现在, 我们的函数和元素类型无关, 也和比较操作无关, 更和容器类型无关。简单的说,我们已经将最初的函数转化为一个泛型算法了。


// !! 使用 Map

Using a Map

map 被定义为一对 pair 数值, 其中的 key 通常是个字符串, 扮演索引的角色, 另一个数值是 value。字典便是 map 的一个不错实例。

如果要编写一个能对文章内每个字眼的出现次数加以分析的程序,  可以建立一份 map, 带有 string key 和 int value (前者表现单字, 后者表示出现次数)


#include <map>
#include <string>

std::map<string, int> words;
words["version"] = 10;

std::string twodee;
while(cin >> twodee)
{
    words[twodee]++;
}

其中：

words[twodee]

会取出与 twodee 相应的 value。如果 twodee  不在 map  内, 它便会因此被放到 map 内, 并获得默认值 0。稍后出现的 increment 运算符会将其值递增 1。


以下的  for  循环会打印出所有单字及其出现次数:

map<string,int>::const_iterator it = words.begin();
while (it != words.end()){
    cout << (*it).first << "occurs" << (*it).second << endl;
}

map 对象有一个名为 first 的 member, 对应于 key, 本例中便是单字字符串。另有一个名为 second 的 member, 对应于 value, 本例中便是单字的出现次数。

欲查询 map 内是否存在某个 key, 有三种方法。最直觉的做法就是把 key 当成索引使用:

int count = 0;
if(!(count - words["tee"])){
    // tee 并不存在与 map 中
}

这种写法的缺点是,如果我们用来索引的 key 并不存在于 map 内, 这个 key 会自动被加入 map 中, 而其相应的 value 会被设置为所属类型的默认值。


第二种 map 查询法是利用 map 的 find() 函数, 我们将 key 传入 find()并调用:

words.find("tee") != words.end()

任何一个 key 值在 map 内最多只会有一份。如果我们需要储存多份相同的 key 值, 就必须使用 multimap。



// !! 使用 Set

Using a Set

'set 由一群 key 组合而成。如果我们想知道某值是否存在于某个集合内, 就可以使用 set'。

例如, 在 graph traversal (图形遍历)算法中, 我们可以使用 set 储存每个遍历过的节点 node。在移至下一节点前, 我们可以先查询 set,判断该节点是否已经遍历过。

以前一节的字数统计程序为例, 它可能不想统计一般中性词汇的出现次数。为实现此目的, 我们定义一个用来记录"排除字眼"的 set, 元素类型为 string:

#include <set>
#include <string>

std::set<std::string> excluded_word;

程序将某个单字放进 map 之前, 应该先检查它是否存在于 word_exclusion set 中:

while (cin >> word){
    if(excluded_word.find(word) != excluded_word.end()){
        continue;
    }
    //okay
    words[word]++;
}

其中的 continue 语句会跳出当前迭代。

对于任何 key 值, set 只能储存一份。如果要储存多份相同的 key 值, 必须使用 multiset。


默认情形下, set 元素皆依据其所属类型默认的 less_than 运算符进行排列。例如, 如果给定:

int ia[10] = {0, 1, 21, 3, 41, 5, 16,7, 18, 9};

vector<int> vec(ia, ia + 10);
set<int> s(vec.begin(), vec.end());

如果要为 set 加入单一元素, 可使用单一参数的 insert():

s.insert(22);

如果要为 set 加入某个范围的元素, 可使用双参数的 insert():

s.insert(vec.begin(), vec.end());


在set身上进行迭代, 其形式和你所预期的一致:

set<int>::const_iterator it = s.begin();
while(it != s.end()){
    cout << it->first << endl;
    ++it;
}


// !! 如何使用 Iterator Inserter

How to Use Iterator Inserters

回到先前对 filter() 的实现, 我们将源端(容器)中每一个符合条件的元素一一赋值(assign)至目的端(容器):

while((first = find_if(first, last, bind2nd(pred, value))) != vec.end()){
    *output++ = *first++;
}

这种形式下, 目的端的容器必须够大, 以储存被赋值进来的每个元素。filter() 没有办法知道每次对 output 递增之后, output 是否仍指向一个有效的容器位置。

"确保 output 所指目的端容器的空间够大", 这是程序员的责任。

在测试程序中, 我们设定了目的端容器的大小, 使它等于源端容器的大小, 借此方式来确保以上条件:

这个解法的问题在于, 大部分情形下, 目的端容器的大小显然太大了。

另一种解法是先定义一个空容器, 而后每当有元素被插入进来, 再加以扩展。不幸的是, filter() 目前的实现是将元素赋值至某个已存在的容器位置上, 如果我们重新以插入方式
实现 filter(), 那对我们目前已有的应用程序会产生什么影响呢? 此外, 我们又应该提供什么样的插入操作呢?

所有"会对元素进行复制行为"的泛型算法, 例如 copy()、copy_backwards()、remove_copy()、replace_copy()、unique_copy() 等等, 都和 filter() 的实现极
为相似。每个算法都接受一个 iterator, 标示出复制的起始位置。每复制一个元素, 都会被赋值 assigned, iterator 则会递增至下个位置。'我们必须保证在每一次复制操作
中, 目的端容器都足够大, 可以储存这些被赋值进来的元素'。既然有了这些算法, 我们实在不需要重新写一个。

这意味着我们必须总是传入某个固定大小的容器至上述算法吗? 这绝对不符合 STL 的精神。标准库提供了三个所谓的 insertion adapter, 这些 adapter 让我们得以避免使
用容器的 assignment 运算符:

1. 'back_inserter() 会以容器的 push_back() 函数取代 assignment 运算符'。对 vector 来说, 这是比较适合的 inserter。传入 back_inserter 的参数, 应该
    就是容器本身

   vector<int> result_vector;
   std::unique_copy(ivec.begin(), ivec.end(), std::back_inserter(result_vector));

2. inserter() 会以容器的 insert() 函数取代 assignment 运算符。inserter() 接受两个参数: 一个是容器,  另一个是  iterator, 指向容器内的插入操作起点。
   以 vector 而言, 我们会这么写:

   vector<string> svec_result;
   std::unique_copy(vec.begin(), vec.end(),inserter(svec_result, svec_result.end()));


3. front_inserter() 会以容器的 push_front() 函数取代 assignment 运算符。这个 inserter 只适用于 list 和  deque:

    list<int> i_list;
    std::copy(l.begin(),l.end(), std::front_inserter(i_list));

欲使用上述三种 adapter, 首先必须包含 iterator 头文件:

#include <iterator>

然而这些 adapter 并不能用在 array 上, array 并不支持元素插入操作。




// !! 使用 iostream Iterator

Using the iostream Iterators

想象我们的新任务如下: 从标准输入设备读取一串 string 元素, 将它们存到 vector 内, 并进行排序，最后再将这些字符串写回标准输出设备。

一般的解法看起来像下面这样:

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]){
    string word;
    vector<string> text;
    while(cin >> word) {
        text.push_back(word);
    }

    sort(text.begin(), text.end());

    for(int i = 0; i < text.size(); i++) {
        cout << text << endl;
    }
}

标准库定义有供输入及输出使用的 iostream iterator 类, 称为 istream_iterator 和 ostream_iterator, 分别支持单一类型的元素读取和写入。使用这两个
iterator class 之前, 先得包含 iterator 头文件:

#include <iterator>

现在让我们看看如何利用 istream_iterator 从标准输入设备读取字符串。就像所有的 iterator 一样, 我们需要一对 iterator first 和 last,用来标示元素范围。


istream_iterator<string> is(cin);

为我们提供了一个 first iterator, 它将 is 定义为一个"绑至标准输入设备"的 istream_iterator。我们还需要一个 last iterator, 表示"要读取的最后一个元素的
下一位置"。

对标准输入设备而言, end-of-file 即代表 last。这该如何表示呢? 噢, 只要在定义 istream_iterator 时不为它指定 istream 对象, 它便代表了 end-of-file。
例如:

istream_iterator<string> eof;

我们应该如何使用这对 iterator 呢? 

下面的例子中, 我将它们和储存字符串元素的 vector,  一起传给泛型算法 copy()。由于不知道该为 vector 保留多少空间, 所以我选用了 back_inserter:

std::copy(is, eof, std::back_inserter(text));


现在我还需要一个 ostream_iterator, 标示字符串元素的输出位置。一旦不再有任何元素需要输出, 我就停止输出操作。

ostream_iterator<string> os(cout, " ");

上述第二个参数可以是 C-style 字符串, 也可以是字符串常量。'它用来表示各个元素被输出时的分隔符'。默认情形下, 输出的各个元素之间并无任何分隔符。

本例我选择在各输出字符串之间以空格加以分隔。以下便是可能的使用方式:

std::copy(text.begin(), text.end(), os);

copy() 会将储存在 text 中的每个元素一一写到由 os 所表示的 ostream 上。

#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv){
    istream_iterator<string> is(cin);
    istream_iterator<string> eof;
    vector<string> text;

    copy(is, eof, back_inserter(text));

    ostream_iterator<string> os(cout, " ");
    copy(text.begin(), text.end(), os);
}

然而, 我们常常并不是要从标准输入设备读数据, 也不是要写到标准输出设备去, 而是希望从文件中读取, 写到文件去。

这该如何办到? 啊, 只需将 istream_iterator 绑定至 ifstream object, 将  ostream_iterator 绑定至 ofstream object 即可:

#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char* *argv){
    ifstream infile("input.txt");
    ofstream outfile("output.txt");
    if(!infile.is_open() || !outfile.is_open()){
        return -1;
    }

    istream_iterator<string> is(infile);
    istream_iterator<string> eof;
    copy(is, eof, back_inserter(text));

    sort(text.begin(), text.end());

    ostream_iterator<string> os(outfile, " ");
    copy(text.begin(), text.end(), os);
    return 0;
}






















