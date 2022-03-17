// !! 标准模板库

'STL (standard template library, 标准模板库) 是 C++ 标准库的核心, 它深刻影响了标准库的整体结构'。

STL 是一个泛型(generic)程序库,提供一系列软件方案,'利用先进、高效的算法来管理数据'。程序员无须了解 STL 的原理,便可享受数据结构和算法领域中的这一革新
成果。

从程序员的角度看来, STL 是由一些可适应不同需求的集合类 (collection class) 和一些能够在这些数据集合上运作的算法构成。STL 内的所有组件都由 template
(模板) 构成, 所以其元素可以是任意类型。'更妙的是, STL 建立了一个框架(framework), 在此框架下你可以提供其他集合类或算法, 与现有的组件搭配共同运作'。

'总之, STL 赋予了 C++ 新的抽象层次'。抛开 dynamic array (动态数组)、linked list(链表)、binary tree(二叉树)、hash table(散列)之类的东西吧,
也不必再烦心各种 search (查找)算法了。'你只需使用恰当的集合类,然后调用其成员函数和(或)算法来处理数据,就万事大吉'。

'当然, 如此的灵活性并非免费午餐, 代价总是有的。首要的一点是, STL 并不好懂'。


// !! STL 组件(Component)

若干精心勾画的组件共同合作, 构筑起 STL 的基础。这些组件中最关键的是'容器'、'迭代器'和'算法'。

'容器(Container)'

用来管理某类对象的集合。'每一种容器都有其优点和缺点, 所以, 为了应付不同的需求, STL 准备了不同的容器类型'。容器可以是 array 或 linked list,或者每个元
素有一个特别的 key。

'迭代器(Iterator)'

用来在一个对象集合 (collection of objects) 内遍历元素。这个对象集合或许是个容器, 或许是容器的一部分。'迭代器的主要好处是, 为所有各式各样的容器提供了一
组很小的共通接口'。例如其中一个操作是行进至集合内的下一元素。至于如何做到当然取决于集合的内部结构。不论这个集合是 array 或 tree 或 hash table, 此一行进
动作都能成功,'因为每一种容器都提供了自己的迭代器, 而这些迭代器了解容器的内部结构, 知道该做些什么'。迭代器的接口和寻常的 pointer 差不多, 调用 operator++
就累进, 调用 operator* 就访问被指向的值。'所以你可以把迭代器视为一种 smart pointer, 能够把“前进至下一元素”的意图转换成合适的操作'。


'算法(Algorithm)'

用来处理集合内的元素。它们可以出于不同的目的而查找、排序、修改、使用元素。'通过迭代器的协助, 我们只需撰写一次算法, 就可以将它应用于任意容器, 因为所有容器的
迭代器都提供一致的接口'。你还可以提供一些特殊的辅助函数供算法调用, 从而获取更佳的灵活性。'这样你就可以一方面运用标准算法, 一方面配合自己特殊或复杂的需求'。
例如, 你可以提供自己的查找准则 (search criterion) 。'特别是由于 C++11 新引入了 lambda, 你得以轻松指明在容器元素身上进行任何种类的动作'。



'STL 的基本观念就是将数据和操作分离'。数据由容器类加以管理, 操作则由可定制 (configurable) 的算法定义之。迭代器在两者之间充当黏合剂, 使任何算法都可以和
任何容器交互运作。

STL将数据和算法分开对待, 而不是合并考虑。'从某种意义上说,STL 的概念和面向对象编程 (OOP) 的最初思想是矛盾的'。然而这么做有着很重要的因素。首先, 你可以将
各种容器与各种算法结合起来,在很小的框架(framework)内达到非常大的弹性。

STL 的一个根本特性是, 所有组件都可以针对任意类型 (type) 运作。顾名思义, 所谓 standard template library 意味着其内的所有组件都是"可接受任意类型"的
template, 前提是这些类型必须能够执行必要的操作。因此 STL 成了泛型编程 (generic programming) 概念下的一个出色范例。容器和算法被泛化为可适用于任意 type
和 class。

STL 甚至提供更泛化的组件, 借由特定的适配器 (adapter) 和函数对象 (function object, functor),你可以补充、约束或定制算法以满足特别需求。目前说这些为时
太早, 眼下我还是先通过实例, 循序渐进地讲解概念, 这才是理解并熟悉 STL 的最佳方法。


// !! 容器 (Container)

容器用来管理一大群元素。为了适应不同需要, STL 提供了不同的容器。


总的来说, 容器可分为三大类:

// !! 1. 序列式容器 Sequence container

这是一种有序 (ordered) 集合,其内每个元素均有确凿的位置--取决于插入时机和地点, 与元素值无关。如果你以追加方式对一个集合置入 6 个元素, 它们的排列次序
将和置入次序一致。STL 提供了 5 个定义好的序列式容器: array 、 vector 、deque 、list 和 forward_list


// !! 2. 关联式容器 Associative container

这是一种已排序 (sorted) 集合, 元素位置取决于其 value (或 key--如果元素是个 key/value pair) 和给定的某个排序准则。如果将 6 个元素置入这样的集合中,
它们的值将决定它们的次序, 和插入次序无关。STL 提供了 4 个关联式容器: set、multiset、map 和 multimap。


// !! 3. 无序容器 (Unordered （associative） container)

这是一种无序集合 (unordered collection), 其内每个元素的位置无关紧要, 唯一重要的是某特定元素是否位于此集合内。元素值或其安插顺序, 都不影响
元素的位置, 而且元素的位置有可能在容器生命中被改变。如果你放 6 个元素到这种集合内, 它们的次序不明确, 并且可能随时间而改变。STL 内含 4 个预
定义的无序容器: unordered_set、unordered_multiset、unordered_map 和 unordered_multimap。

这里介绍的 3 个容器分类, 只是根据"元素次序"而完成的一种逻辑分类。STL 的集合类型彼此之间完全不同, 有着十分不同的实现, 彼此没有派生关系。我们
即将看到:

1. Sequence 容器通常被实现为 array 或 linked list

2. Associative 容器通常被实现为 binary tree

3. Unordered 容器通常被实现为 hash table

严格地说, C++ 标准库并未规定任何容器必须使用任何特定的实现, 然而由于  C++standard 对于行为和复杂度的明确要求, 使得这方面的变化余地不多。所
以现实中各实现之间只可能存在微小细节上的差异。

当你面临如何选择适当的容器时, 排序以外的能力也必须考虑。事实上, 关联式容器自动对其元素排序, 并非意味着它们就是用来排序的。你也可以对序列式容
器的元素排序。自动排序带来的主要优势是, 查找元素时可获得较佳效率。更明确地说, 你可以放心使用二分查找法 (binary search) , 它具备对数
(logarithmic)复杂度, 而非线性复杂度。


// !! 序列式容器(Sequence Container)

STL 内部预先定义好了以下序列式容器:

1. Array (其class名为array)

2. Vector

3. Deque

4. List(singly/doubly linked)

以下讨论从 vector 开始, 因为 array 是 TR1 新引入的, 进入 C++ 标准库的时间比较短, 而且它有一些特殊属性, 与其他 STL 容器不共通。


// !! Vector

Vector 将其元素置于一个 dynamic array 中管理。它允许随机访问, 也就是说, 你可以利用索引直接访问任何一个元素。在 array 尾部附加元素或移除
元素都很快速,但是在 array 的中段或起始段安插元素就比较费时, 因为安插点之后的所有元素都必须移动, 以保持原本的相对次序。


以下例子针对整数类型定义了一个 vector, 插入 6 个元素, 然后打印所有元素:

#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> coll;

    for(int i=0; i < 6 ; i++)
    {
        coll.push_back(i);
    }

    for(int i=0; i < coll.size(); i++)
    {
        cout << coll[i] << endl;
    }

    cout << endl;

    return 0;
}

Vector 的头文件通过以下语句包含进来:

#include <vector>

以下声明式建立了一个元素类型为 int 的 vector:

vector<int> coll;

由于没有任何初始化参数, 所以 default 构造函数将它构造为一个空集合。push_back() 为容器附加新元素:

coll.push_back(i);

所有序列式容器都提供这个成员函数, 因为尾附一个元素永远是可能的, 而且效率相当高。size() 成员函数返回容器的元素个数:

for(int i = 0; i < coll.size(); i++)
{
    cout << coll[i] << endl;
}

所有容器类都提供这个函数, 唯一例外是 singly linked list(class forward_list)。

你可以通过 subscript(下标) 操作符 [], 访问 vector 内的某个元素:

cout << coll[i] << endl;

// !! Deque

所谓 deque (double-ended queue), 它是一个 dynamic array, 可以向两端发展, 因此不论在尾部或头部安插元素都十分迅速。在中间部分安插元素
则比较费时, 因为必须移动其他元素。

以下例子声明了一个元素为浮点数的 deque, 并在容器头部安插 1.1 至 6.6 共 6 个元素, 最后打印出所有元素:

#include <deque>
#include <string>

using namespace std;

int main()
{
    queue<float> coll;

    for(int i=0; i < 6 ; i++)
    {
        coll.push_front(i * 1.1);
    }

    for(int i=0; i < coll.size(); i++)
    {
        cout << coll[i] << endl;
    }

    cout << endl;

    return 0;
}

本例中, 下面这一行将 deque 的头文件包含进来:

#include<deque>

下面的声明式则是产生一个空的浮点数集合:

deque<float> coll;

push_front() 函数用来安插元素:

coll.push_front(i * 1.1);

push_front() 会将元素安插于集合前端。注意, 这种安插方式造成的结果是, 元素排放次序与安插次序恰好相反, 因为每个元素都安插于上一个元素的前面。

你也可以使用成员函数 push_back() deque 尾端附加元素。Vector 并未提供 push_front(), 因为其时间效率不佳(在 vector 头端安插一个元素,需
要先移动全部元素)。

// !! 一般而言, STL 容器只提供具备良好时间效率的成员函数, 所谓"良好"通常意味着其复杂度为常量或对数, 以免程序员调用性能很差的函数。

// !! Array

一个 array 对象是在某个固定大小的 array (有时称为一个 static array 或 C array)内管理元素。因此, 你不可以改变元素个数, 只能改变元素值。
你必须在建立时就指明其大小。Array 也允许随机访问, 意思是你可以直接访问任何一个元素--只要你指定相应的索引。

#include <array>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    array<string,5> coll = {"hello", "world"};

    for(int i = 0; i < coll.size(); i++)
    {
        cout << coll[i] << endl;
    }

    cout << endl;
    return 0;
}


下面这行将 array 的头文件包含进来:

#include <array>

以下声明式会建立一个 array, 带有 5 个类型为 string 的元素:

array<string, 5> coll = {"hello", "world"};

默认情况下这些元素都被元素的 default 构造函数初始化。这意味着, 对基础类型而言, 初值不明确 (undefined)。

然而本程序用了一个 initializer list, 这东西允许我们以一系列值将对象初始化于创建期。自 C++11 起这种初始化方法受到每一种容器的支持, 所以当
然我们也可以在 vector 和 deque 中使用它。既然如此, 基础类型用的是 zero initialization, 意味着基础类型保证被初始化为 0。

注意, 元素个数是 array 类型的一部分。因此 array<int, 5> 和 array<int, 10> 是两个不同的类型, 你不能对此二者进行赋值或比较。


// !! List

从历史角度看, 我们只有一个 list class。然而自 C++11 开始, STL 竟提供了两个不同的 list 容器: class list<> 和 class forward_list<>。

然而就某种程度来说, forward list 只不过是受到更多限制的 list, 现实中二者的差异并不怎么重要。因此当我使用术语 list, 通常我指的是 class 
list<>, 它的能力往往超越 class forward_list<>。如果特别需要指出 class forward_list<>, 我会使用术语 forward list。

list<> 由双向链表(doubly linked list) 实现而成。这意味着 list 内的每个元素都以一部分内存指示其前导元素和后继元素。List 不提供随机访问,
因此如果你要访问第 10 个元素, 你必须沿着链表依次走过前 9 个元素。不过, 移动至下一个元素或前一个元素的行为, 可以在常量时间内完成。

List 的优势是: 在任何位置上执行安插或删除动作都非常迅速, 因为只需改变链接(link) 就好。这表示在 list 中段处移动元素比在 vector 和 deque
快得多。

#include <list>
#include <iostream>

using namespace std;

int main()
{
    list<char> coll;

    for( char c = 'a'; c <= 'z'; c++ )
    {
        coll.push_back(c);
    }

    for(auto elem : coll)
    {
        cout << elem << '\n';
    }
    return 0;
}

为了打印所有元素, 我使用一个 range-based for 循环, 这种循环自 C++11 之后提供, 允许对每个元素执行指定的语句。

List 并不提供作为元素直接访问之用的操作符 []。这是因为 list 并不提供随机访问, 因此操作符 [] 会带来低下的效率。

在此循环中, 当前正被处理的 coll 元素的类型被声明为 auto。因此 elem 的类型被自动推导为 char, 因为 coll 是个 char 集合。


// !! Forward List

自 C++11 之后, C++ 标准库提供了另一个 list 容器: forward list。forward_list<> 是一个由元素构成的单向 (singly) linked list。就像
寻常 list 那样, 每个元素有自己一段内存, 为了节省内存, 它只指向下一元素。

因此, forward list 原则上就是一个受限的 list, 不支持任何后退移动或效率低下的操作。基于这个原因, 它不提供成员函数如 push_back() 乃至
size()。

现实中, 这个限制比乍听之下甚至更尴尬棘手。问题之一是, 你无法查找某个元素然后删除它, 或是在它的前面安插另一个元素。因为, 为了删除某个元素,
你必须位于其前一元素的位置上, 因为正是那个元素才能决定一个新的后继元素。

#include <forward_list>
#include <iostream>

using namespace std;

int main()
{
    forward_list<long> coll = {2,3,4,5,6,7,8};

    coll.resize(8);
    coll.resize(9,99);

    for(auto elem : coll)
    {
        cout << elem << endl;
    }
    cout << endl;
    return 0;
}

一如以往, 我们使用 forward list 的头文件 <forward_list> 定义一个类型为 forward_list 的集合, 以长整数(long integer) 为元素。

然后使用 resize() 改变元素个数。如果数量成长, 你可以传递一个额外参数, 指定新元素值。否则就使用默认值(对基础类型而言是 0)。

注意, resize() 是一个昂贵的动作, 它具备线性复杂度, 因为为了到达尾端你必须一个一个元素地前进, 走遍整个 list。不过这是一个几乎所有
sequence 容器都会提供的操作, 就暂时忽略它那可能的低劣效率吧。只有 array 不提供 resize(), 因为其大小固定不变。

像先前对待 list 那样, 我们使用一个 range-based for 循环打印所有元素。

    for(auto elem : coll)
    {
        cout << elem << endl;
    }



// !! 关联式容器 (Associative Container)

关联式容器依据特定的排序准则, 自动为其元素排序。元素可以是任何类型的 value, 也可以是 key/value pair, 其中 key 可以是任何类型, 映射至一个
相关 value, 而 value 也可以是任意类型。

排序准则以函数形式呈现, 用来比较 value, 或比较 key/value 中的 key。默认情况下所有容器都以操作符 < 进行比较, 不过你也可以提供自己的比较函
数, 定义出不同的排序准则。

通常关联式容器由二叉树 (binary tree) 实现出来。在二叉树中, 每个元素 (节点) 都有一个父节点和两个子节点; 左子树的所有元素都比自己小,右子树的
所有元素都比自己大。'关联式容器的差别主要在于元素的种类以及处理重复元素时的方式'。

'关联式容器的主要优点是,它能很快找出一个具有某特定 value 的元素,因为它具备对数复杂度(logarithmic complexity)', 而任何循序式容器的复杂度
是线性。因此, 使用关联式容器, 面对 1 000 个元素, 平均而言你将有 10 次而不是 500 次比较动作。然而它的一个缺点是, 你不能直接改动元素的
value, 因为那会破坏元素的自动排序。

下面是 STL 定义的关联式容器

1. Set 元素依据其 value 自动排序, 每个元素只能出现一次, 不允许重复

2. Multiset 和 set 的唯一差别是: 元素可以重复。也就是 multiset 可包括多个 value 相同的元素

3. Map 每个元素都是 key/value pair, 其中 key 是排序准则的基准。每个 key 只能出现一次, 不允许重复。Map 也可被视为一种关联式数组
   (associative array), 也就是"索引可为任意类型"的数组

4. Multimap 和 map 的唯一差别是: 元素可以重复, 也就是 multimap 允许其元素拥有相同的 key。Multimap 可被当作字典(dictionary)使用

所有关联式容器都有一个可供选择的 template 实参, 指明排序准则; 默认采用操作符 <。'排序准则也被用来测试等同性(equivalence): 如果两个元素的
value/key 互不小于对方, 则两者被视为重复'。

你可以将 set 视为一种特殊的 map: 元素的 value 等同于 key。'实际产品中所有这些关联式容器通常都由二叉树 (binary tree) 实现而成'。

// !! Set 和 Multiset 实例

下面是第一个例子, 使用 multiset:

#include <set>
#include <iostream>
#include <string>

int main()
{
    multiset<string> cities = {"Shanghai", "Beijing", "Nanjing", "Jiangsu","Anhui"};

    for(auto elem : cities)
    {
        cout << elem << endl;
    }

    cout << endl;

    cities.insert({"Shanghai", "Beijing", "Nanjing", "Hangzhou"});

    for(const auto& elem : cities)
    {
        cout << elem << endl;
    }
    cout << endl;
    return 0;
}


包含头文件 <set> 后, 我们可以声明 cities 是个以 string 为元素的 multiset。

multiset<string> cities;

声明之后, 若干字符串以 initializer list 形式成为元素初值并于稍后被安插到容器内。为打印所有元素, 我们使用一个 range-based for 循环。
'注意我们声明元素为 const auto&, 意思是希望从容器推断元素类型并免除为"被此循环叫唤"的每个元素制造一份拷贝'。在这个容器内部, 所有元素都已
经过排序。

如你所见, 由于这里用的是一个 multiset 而不是 set, 因此允许元素重复。如果我们声明的是 set 而不是 multiset, 每个 value 就只会被打印一次。
如果我们用的是一个 unordered multiset, 元素的次序就无法明确得知了。


// !! Map 和 Multimap 实例


下面的例子示范了如何使用 map 和 multimap:

#include <map>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    multimap<int, string> coll;

    coll = {{1,"hello"},
        {2,"world"},
        {3,"fuck"},
        {4,"you"},
        {100,"Later"}
    };

    for(auto elem : coll)
    {
        cout << elem.second << endl;
    }
    cout << endl;

    return 0;
}

包含 <map> 之后, 我们声明一个 map, 其元素拥有一个 int 作为 key 和一个 string 作为 value。

multimap<int, string> coll;

由于 map 和 multimap 的元素都是 key/value pair, 因此声明式、元素安插、元素访问等动作略有不同:

1. 首先, 为了初始化(或赋值或安插)元素, 你必须传递 key/value pair, 本例以 nested initializer list 完成, 内层定义的是每个元素的 key 和
   value, 外层定义出所有元素。

2. 处理元素时你再一次需要和 key/value pair 打交道。每个元素的类型实际上是 pair<constkey,value>。Key 之所以必须是常量, 因为其内容如果
   被改动, 会破坏元素的次序, 而元素次序是由容器自动排序的。由于 pair 缺乏 output 操作符, 你无法视它们为一个整体加以打印。因此你必须分别处理
   pair 结构中的成员, 它们分别名为 first 和 second。

下面的式子取得 key/value pair 的第二成分, 也就是 multimap 元素的 value

coll.second;


// !! 无序容器 (Unordered Container)

在无序 (unordered) 容器中, 元素没有明确的排列次序。也就是如果安插 3 个元素, 当你迭代容器内的所有元素时会发现, 它们的次序有各种可能。如果安
插第 4 个元素, 先前 3 个元素的相对次序可能会被改变。'我们唯一关心的是, 某个特定元素是否位于容器内'。甚至如果你有 2 个这种容器, 其内有着完全
相同的元素, 元素的排列次序也可能不同。试着想象它是个袋子(bag)。


无序 (unordered) 容器常以 hash table 实现出来, 内部结构是一个"由 linked list 组成"的 array。通过某个 hash 函数的运算, 确定元素落于
这个 array 的位置。'Hash 函数运算的目标是: 让每个元素的落点(位置) 有助于用户快速访问'。

任何一个元素, 前提则是 hash 函数本身也必须够快。由于这样一个快速而完美的 hash 函数不一定存在(或不一定被你找到), 抑或由于它造成 array 耗费
巨额内存而显得不切实际, 因此, 退而求其次的 hash 函数有可能让多个元素落于同一位置上。所以设计上就让 array 的元素再被放进一个 linked list
中, 如此一来 array 的每个位置就得以存放一个以上的元素。

无序 (unordered) 容器的主要优点是, 当你打算查找一个带某特定值的元素, 其速度甚至可能快过关联式容器。事实上无序容器提供的是摊提的常量复杂度
(amortized constant complexity), 前提是你有一个良好的 hash 函数。然而提供一个良好的 hash 函数并非易事。你可能需要提供许多内存作为
bucket。

根据关联式容器的分类法, STL 定义出下面这些无序容器:

1. Unordered set 是无序元素的集合, 其中每个元素只可出现一次。也就是不允许元素重复

2. Unordered multiset 和 unordered set 的唯一差别是它允许元素重复。也就是 unordered multiset 可能内含多个有着相同 value 的元素

3. Unordered map 的元素都是 key/value pair。每个 key 只可出现一次, 不允许重复。它也可以用作关联式数组(associative array), 那是索引可
   为任意类型的 array。 

4. Unordered multimap 和 unordered map 的唯一差别是允许重复。也就是 unordered multimap 可能内含多个"拥有相同 key"的元素。它可以用
   作字典 (dictionary)

所有这些无序容器的 class 都有若干可有可无的 template 实参, 用来指明 hash 函数和等效准则(equivalence criterion), 该准则被用来寻找某给
定值, 以便判断是否发生重复。默认的等效准则是操作符 ==。

你可以把 unordered set 视为一种特殊的 unordered map, 只不过其元素的 value 等同于 key。现实中所有无序容器通常都使用 hash table 作为
底层实现。


// !! Unordered Set/Multiset 实例

下面是第一个例子, 使用 unordered multiset, 元素是 string:

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int main()
{
    unordered_set<string> cities = {"Shanghai", "Beijing", "Nanjing","Jiangsu"};

    for(const auto& elem : coll)
    {
        cout << elem << endl;
    }
    cout << endl;

    cities.insert({"London","Anhui"});

    for(const auto& elem : cities)
    {
        cout << elem << endl;
    }

    cout << endl;
    return 0;
}


包含必要的头文件:

#include <unordered_set>

后, 我们可以声明一个"元素为 string" 的 unordered set 并给予初值:

unordered_set<string> cities;

现在, 如果打印所有元素, 出现的次序可能不同于程序中所给的次序, 因为其次序是不明确的。唯一保证的是重复元素——这的确有可能因为我们用的是
multiset。

'任何安插动作都有可能改变上述次序。事实上任何操作只要可能引发 rehashing 就可能改变上述次序'。

此外, 为确保你在处理所有元素的同时还可以删除元素, C++standard 保证, 删除元素不会引发 rehashing。但是删除之后的一次安插动作就有可能引发
rehashing。


// !! Unordered Map 和 Multimap 实例

下面是一个 unordered map 例子。此例使用的 unordered map, 其 key 是个 string 而其 value 是个 double:

#include <unordered_map>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    unordered_map<string, double> coll = {{"Shanghai",1.2}, {"Beijing",2.3},{"NanJing",3.21}};

    for(pair<string, double>& elem : coll)
    {
        cout << " " << elem.first << " " << elem.second << endl;
    }

    for(const auto& item : coll)
    {
        cout << item.first << " " << item.second << endl;
    }
    cout << endl;

    return 0;
}

像此前很多例子一样, 自 C++11 开始, 我们不再需要明白指出元素类型, 因为在一个 range-based for 循环内, 类型可被推导出来(根据容器)。基于此
, 负责输出所有元素的第二循环中使用 auto。事实上, 由于声明 elem 为 const auto&, 我们得以避免产生很多拷贝(copy)。


// !! 关联式数组 (Associative Array)

不论 map 或 unordered map, 都是 key/value pair 形成的集合, 每个元素带着独一无二的 key。如此的集合也可被视为一个关联式数组(associative
array), 也就是"索引并非整数"的 array。也因此, 刚才说的那两个容器都提供了下标操作符 []。

#include <unordered_map>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    unordered_map<string, float> coll;

    coll["hello"] = 1.0f;
    coll["world"] = 2.0f;
    coll["world2"] = 3.0f;
    coll["world3"] = 4.0f;
    coll["world4"] = 5.0f;
    coll["world5"] = 6.0f;
    coll["world6"] = 7.0f;
    coll["world7"] = 8.0;
    coll["world8"] = 9.0;

    coll["hello"] += 1.0f;

    cout << "coll[hello] is " << coll[hello] << endl;
    return 0;
}


根据 associative array 的观念, 你可以使用下标操作符 [] 访问元素。然而请注意,这个操作符的行为和寻常array的下标操作符不太一样:其索引不是
整数;'它接受一个新索引并以此建立和安插一个新元素,该元素以该索引为 key。因此你绝不能给予一个无效索引'。

一如以往, 使用 unordered map 和使用 map 的差异在于, 元素在 unordered map 内的次序有各种可能, 但元素在 map 内一定是被排序过的。


// !! 其他容器

// !! String

你可以把 string 当作一种 STL 容器。说到 string 我指的是 C++string class 对象。string 很类似 vector , 但其元素都是字符。


// !! 寻常的 C-Style Array

另一种容器由 C/C++ 语言内核提供, 是个 type 而不是个 class: 那就是寻常的 array, 或所谓的 C-style array。声明它时应该给予一个固定大小,
或一个来自 malloc() 的动态大小。然而这种寻常 array 并不是 STL 容器, 因为它们不提供成员函数如 size() 和 empty()。尽管如此, STL 算法还
是可以作用在它们身上。

C++ 程序不再需要直接使用 C-style array。vector 和 array 提供了寻常 C-style array 的所有特性, 并具备更安全更方便的接口。


// !! 用户自定义容器(User-Defined Container)


// !! 容器适配器 (Container Adapter)

除了以上数个根本的容器类,为满足特殊需求,C++ 标准库还提供了一些所谓的容器适配器,它们也是预定义的容器,提供的是一定限度的接口,用以应付特
殊需求。这些容器适配器都是根据基本容器实现而成, 包括:

1. Stack

Stack 容器对元素采取 LIFO 管理策略

2. Queue

Queue 对元素采取 FIFO 管理策略。也就是说, 它是个寻常的缓冲区 (buffer)

3. Priority queue

其内的元素拥有各种优先权。所谓优先权乃是基于程序员提供的排序准则(默认为操作符<)而定义。这种特殊容器的效果相当于这样一个缓冲区:"下一元素永远是
容器中优先权最高的元素"。如果同时有多个元素具备最高优先权, 则其次序无明确定义。

从历史观点来看, 容器适配器是 STL 的一部分。从程序员的观点来看, 它们只不过是一种特别的容器类, 使用"由 STL 提供的容器、迭代器和算法所形成的总
体框架'。


// !! 迭代器 (Iterator)

自 C++11 起, 我们可以使用一个 range-based for 循环来处理所有元素, 然而如果只是要找出某元素, 并不需要处理所有元素。我们应该迭代所有元素,
直到找到目标。

此外, 我们或许希望将这个(被找到的元素的)位置存放在某处, 以便稍后能够继续迭代或进行其他处理。

// !! 因此我们需要这样的概念: 以一个对象表现出容器元素的位置。

这样的概念的确存在。实践这个概念的对象就是所谓的迭代器(iterator)。事实上我们将会看到, range-based for 循环其实就是此概念的一个便捷接口,
也就是说, 其内部使用迭代器对象迭代(遍历)所有元素。

迭代器是一个 "可遍历STL容器全部或部分元素" 的对象。"迭代器用来表现容器中的某一个位置"。基本操作如下":

1. Operator* 返回当前位置上的元素值。如果该元素拥有成员, 你可以通过迭代器直接以操作符 -> 取用它们

2. Operator++ 令迭代器前进至下一元素。大多数迭代器还可使用  operator-- 退至前一元素

3. Operators == 和 != 判断两个迭代器是否指向同一位置

4. Operator= 对迭代器赋值(也就是指明迭代器所指向的元素的位置)

// !! 这些操作和 C/C++  运用 pointer 操作寻常的 array 元素时的接口一致。

差别在于, 迭代器是所谓的 smart pointer, 具有遍历复杂数据结构的能力,其内部运作机制取决于其所遍历的数据结构。因此, 每一种容器都必须提供自己
的迭代器。事实上每一种容器的确都将其迭代器以嵌套 (nested) 方式定义于 class 内部

// !! 因此各种迭代器的接口虽然相同, 类型却各自不同。

这直接引出了泛型程序设计的概念: 所有操作都使用相同接口, 纵使类型不同。因此, 你可以使用 template 将泛型操作公式化, 使之得以顺利运作那些能够
满足接口需求的任何类型。

// !! 所有容器类都提供一些基本的成员函数,使我们得以取得迭代器并以之遍历所有元素。这些函数中最重要的是:

1. begin() 返回一个迭代器, 指向容器起点, 也就是第一元素(如果有的话)的位置

2. end() 返回一个迭代器, 指向容器终点。终点位于最末元素的下一位置, 这样的迭代器又称作 past-the-end 迭代器


于是, begin() 和 end() 形成了一个半开区间(half-open range), 从第一元素开始, 到最末元素的下一位置结束。半开区间有两个优点:

1. "遍历元素时的 loop 结束时机" 提供一个简单的判断依据。只要尚未到达 end(), loop 就可以继续进行

2. 必对空区间 (empty range) 采取特殊处理手法。空区间的 begin() 就等于 end()

下面这个例子示范了迭代器的用法, 将 list 容器的所有元素打印出来:

#include <list>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    list<char> coll;

    for(char c = 'a'; c <= 'z'; c++)
    {
        coll.push_back(c);
    }

    list<char>::const_iterator pos;
    for(pos = coll.begin(); pos != coll.end(); pos++)
    {
        cout << *&pos << endl;
    }
    return 0;
}

首先创建一个 list, 然后填入字符 'a' 到 'z', 然后打印出所有元素。但这这次不是使用 range-base for循环:

for(auto ele: coll)
{
    cout << ele << endl;
}


所有元素是被一个寻常的 for 循环打印, 使用迭代器走遍容器内的每一个元素:


list<char>::const_iterator pos;
for(pos = coll.begin(); pos != coll.end(); pos++)
{
    cout << *pos << endl;
}

迭代器 pos 被声明于循环之前, 其类型是"指向容器内的常量元素"的迭代器:

list<char>::const_iterator pos;

任何容器都定义有两种迭代器类型:

1.container::iterator 以读/写模式遍历元素

2.container::const_iterator 以只读模式遍历元素

例如在 class list 中, 它们的定义可能如下:

namespace std{
    template<typename T>
    class list{
        public:
            typedef ... iterator;
            typedef ... const_iterator;
    };
}

至于其中 iterator 和 const_iterator 的确切类型, 则由 implementation 定义之。


你不能改变元素内容, 因为 pos 是个 const_iterator, 从这样一个迭代器的观点看, 元素是常量, 不能更改。不过如果你采用非常量 (nonconstant)
迭代器, 而且元素本身的类型也是非常量(nonconstant), 就可以通过迭代器来改变元素值:

list<char>::iterator pos;

for(pos = list.begin(); pos != list.end(); ++pos)
{
    *pos = toupper(*pos);
}


如果我们使用迭代器遍历 (unordered) map和 multimap 的元素, pos 会指向 key/value pair。那么表达式:

pos->second;

将取得 key/value pair 的第二成分, 也就是元素的 value, 而表达式:

pos->first;

会取得其 (constant) key。


// !! ++pos vs  pos++

这里使用前置式递增 (preincrement) ,因为它比后置式递增 (postincrement) 效率高。后者内部需要一个临时对象, 因为它必须存放迭代器的原
本位置并返回之, 所以一般情况下最好使用 ++pos, 不要用 pos++。

也就是说, 你应该避免这么写:

for(pos = cout.begin(); pos != cout.end(); pos++)
{
    cout << *pos << endl;
}

'这种效率改善几乎总是无关紧要的。所以, 不要把这里的推荐解读为"你应该竭尽所能不计代价地做任何事情, 只为了如此微小的效率损失"'。

// !! 程序的可读性, 以及可维护性, 远比效率优化重要。


// !! cbegin() 和 cend() 

自 C++11 开始, 我们可以使用关键字 auto 代替迭代器的精确类型 (前提是你在迭代器声明期间就初始化,使其类型可以取决于初值)。因此如果我们直接以
begin() 初始化迭代器, 就可以使用 auto 声明其类型:


for(auto pos = cbegin(); pos != cend(); ++pos)
{
    cout << *pos << endl;
}


如你所见, '使用 auto 的优点之一就是, 程序比较浓缩精简'。

如果没有 auto, 在循环内声明迭代器的动作应该如下:

for(list<char>::iterator pos = begin(); pos != end(); ++pos)
{
    cout << *pos << endl;
}


另一个优点是, '采用这种循环写法, 万一容器类型有所改变,程序整体仍能保持较佳的强壮性'。

然而其缺点是, 迭代器丧失常量性 (constness), 可能引发"计划外的赋值"风险。因为


auto pos = coll.begin();

会使 pos 成为一个非常量迭代器, 此乃因为 begin() 返回的是个类型为 cont::iterator 的对象。

// !! 为确保仍可使用常量迭代器, 自 C++11 起容器提供 cbegin() 和 cend(), 它们返回一个类型为 cont::const_iterator 的对象

现在我来总结改善方案。自 C++11 起, 一个允许"迭代容器内所有元素"的循环如果不使用 range-based for 循环, 看起来应如下:

for(auto pos = coll.cbegin(); pos != coll.cend(); ++pos)
{
    ...
}


// !! Range-Based for 循环 vs 迭代器

介绍过迭代器之后, 我们可以解释 range-based for 循环的精确行为了。对容器而言, range-based for 循环其实不过是个便捷接口, 用来迭代它"所接
收到的集合区间" 内的每一个元素。在循环体内, 真实元素被"当前迭代器所指向的 value"初始化。


for(type elem : coll)
{
    ...
}

被解释为:

for(auto pos = coll.cbegin; pos != coll.cend(); ++pos)
{
    ...
}

现在我们可以了解为什么声明 elem 为一个 constant reference 可以避免非必要复制了。



// !!  关联式（Associative）及无序（Unordered）容器的更多实例


// !! 使用 C++11 之前的 Set

#include <set>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    typedef set<int> Intset;

    Intset coll;

    coll.insert(1);
    coll.insert(2);
    coll.insert(3);
    coll.insert(4);
    coll.insert(5);
    coll.insert(6);
    coll.insert(7);
    coll.insert(8);

    Intset::const_iterator pos;
    for(pos = coll.begin(); pos != coll.end(); ++pos)
    {
        cout << *pos << '\n';
    }

    cout << '\n';

    return 0;
}

一如以往, include 指示符定义了 set 的所有必要类型和操作:

#include <set>

既然容器的类型要用到好几次, 不妨先定义一个短一点的名字:

typedef set<int> Intset;

'所有关联式容器都提供了 insert() 成员函数, 用来安插新元素':

coll.insert(1);
coll.insert(2);
coll.insert(3);
coll.insert(4);
coll.insert(5);

C++11 允许我们这么写:

coll.insert({1,2,3,4,5});

每一个被安插的元素就会根据排序准则自动被放到正确位置。

'不可使用序列式容器才会有的 push_back() 或 push_front(), 它们在这里毫无意义, 因为 set 不允许你指定新元素的位置'。


所有元素 (不论以任何次序) 安插完毕后, 元素以排序后 (sorted) 的状态存放于内部 tree 结构中。'任何元素(节点)的左子树的所有元素都小于右子树的
所有元素'(此处"小于" 是指就当前排序准则而言)。



// !! 使用无序的 Multiset

让我们仔细观察另一个例子,遍历一个无序(unordered) multiset 的所有元素时会发生什么事:

'这些元素的顺序是不明确的, 取决于 hash table 的内部布局, 也取决于 hashing 函数'。甚至即使元素先被排序后才被安插,它们在容器内还是有着不
明确的顺序。

如你所见, 这样的次序实在是杂乱无规则可言, 而且在你的平台上执行这个程序可能获得又不一样的次序。就算只添加一个元素, 也可能全盘改变次序。'唯一
保证的是, 内容(value) 相同的元素会相邻'。

'再一次, for 循环内的迭代器 pos 拥有一个由容器提供的类型, 所以它"知道"如何逐一遍历所有元素'。


// !! 迭代器种类 (Iterator Category)

除了基本操作, 迭代器还有其他能力。'这些能力取决于容器的内部结构'。STL 总是只提供效率比较出色的操作, 因此如果容器允许随机访问(例如 vector 
或 deque), 它们的迭代器也必定能进行随机操作(例如直接让迭代器指向第5元素)。


根据能力的不同, 迭代器被划分为五种不同类别。STL 预先定义好的所有容器, 其迭代器均属于以下三种分类:

1. '前向迭代器' (Forward iterator) 只能够以累加操作符 (increment operator) 向前迭代。Class forward_list的迭代器就属此类。其他容器如 
    unordered_set、unordered_multiset、unordered_map 和 unordered_multimap 也都至少是此类别(但标准库其实为它们提供的是双向迭代器)。 

2. 双向迭代器(Bidirectional iterator) 顾名思义它可以双向行进: 以递增 (increment) 运算前进或以递减 (decrement) 运算后退。list、set、
   multiset、map 和 multimap 提供的迭代器都属此类。

3. "随机访问迭代器" (Random-access iterator) 它不但具备双向迭代器的所有属性, 还具备随机访问能力。。更明确地说, 它们提供了迭代器算术运算的必要操作
   符(和寻常指针的算术运算完全对应)。你可以对迭代器增加或减少一个偏移量、计算两迭代器间的距离, 或使用 < 和 > 之类的 relational(相对关系)操作符进行
   比较。'vector、deque、array 和string 提供的迭代器都属此类'。

除此之外, STL 还定义了两个类别:

4. 输入型迭代器 (Input iterator) 向前迭代时能够读取/处理 value。Input stream 迭代器就是这样一个例子

5. 输出型迭代器 (Output iterator) 向前迭代时能够涂写 value


'为了写出尽可能与容器类型无关的泛型代码, 你最好不要使用 random-access iterator 的特有操作'。例如, 以下动作可在任何容器上运作:


for(auto it = coll.begin(); it != coll.end(); ++it)
{

}

但下面这样的代码就不是所有容器都适用了:

for(auto it = coll.begin(); it < coll.end(); ++it)
{

}




// !! 算法（Algorithm）

'为了处理容器内的元素, STL 提供了一些标准算法, 包括查找、排序、拷贝、重新排序、修改、数值运算等基本而普遍的算法'。

算法并非容器类的成员函数, 而是一种搭配迭代器使用的全局函数。这么做有一个重要优势: 所有算法只需实现一份, 就可以对所有容器运作, 不必为每一种容器量身定制。
算法甚至可以操作不同 type 之容器内的元素, 也可以与用户自定义的容器搭配。这个概念大幅降低了代码量, 提高了程序库的能力和弹性。


注意, 这里所阐述的并非面向对象思维 (OOP paradigm), 而是泛型函数编程思维 (generic functional programming paradigm)。'在 OOP 概念里, 数据与操
作合为一体, 在这里则被明确划分开来, 再通过特定的接口彼此互动'。

当然这需要付出代价:首先是用法有失直观, 其次某些数据结构和算法之间并不兼容。更有甚者, 某些容器和算法虽然勉强兼容却毫无用处(也许导致很糟的效率)。'因此,深
入学习 STL 概念并了解其缺陷,显得十分重要,唯其如此方能取其利而避其害'。


#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    vector<int> coll = {21,1,2,4,3,6,10,9,8};

    auto mini_pos = std::min_element(coll.begin(), coll.end());
    cout << "mini_pos is " << *mini_pos << endl;

    auto max_pos = std::max_element(coll.begin(), coll.end());
    cout << "max_pos is " << *max_pos << endl;

    std::sort(coll.begin(), coll.end());

    auto pos3 = std::find(coll.begin(), coll.end(),3);

    std::reverse(pos3, coll.end());

    for(auto elem : coll)
    {
        cout << "elem " << elem << endl;
    }
    cout << endl;
    return 0;
}


为了能够调用算法, 首先必须包含头文件 <algorithm> (某些算法需要特别的头文件):

#include <algorithm>

最先出现的算法是 min_element() 和 max_element() 。'调用它们时必须传入两个实参, 定义出欲处理的元素范围'。如果想处理容器内所有元素, 可使用 
cbegin() 和 cend(), 或 begin() 和 end()。两个算法都返回一个迭代器, 分别指向最小或最大元素。因此, 语句:

auto mini_pos = std::min_element(coll.begin(), coll.end());

中, 算法 min_element() 返回最小元素的位置。


接下来出现的算法是 sort()。顾名思义, 它将"由两个实参指出来"的区间内的所有元素加以排序。你可以(选择性地)传入一个排序准则, 默认使用 operator<。

std::sort(coll.begin(), coll.end());

注意, 这里不可使用 cbegin() 和 cend(), 因为 sort() 会改动元素的 value, 但 const_iterator 不允许如此。

再来便是算法 find()。它在给定范围内查找某值。

auto pos3 = std::find(coll.begin(), coll.end(),3);

'如果 find() 成功, 返回一个迭代器指向目标元素。如果失败, 返回第二实参所指示的区间末端', 本例是 coll 的逾尾 past-the-end 迭代器。

本例所展示的最后一个算法是 reverse(), 将区间内的元素反转放置:

std::reverse(pos3, coll.end());

这个动作会将第三元素至最末元素的排列次序逆转。由于这是一种改动, 我们必须使用一个非常量迭代器, 这就是为什么我调用 find() 并传入 begin() 和 end()


// !! 区间（Range）


所有算法都是用来处理一或多个区间内的元素。这样的区间可以(但非必须)涵盖容器内的全部元素。为了操作容器元素的某个子集, 我们必须将区间首尾当作两个实参
argument 传给算法, 而不是一口气把整个容器传递进去。

这样的接口灵活又危险。调用者必须确保经由两实参定义出来的区间是有效的 valid。所谓有效就是, 从起点出发, 逐一前进, 能够到达终点。也就是说, 程序员自己必须
确保两个迭代器隶属同一容器, 而且前后的放置是正确的, 否则结果难料, 可能引起无穷循环, 也可能访问到内存禁区。就此而言,迭代器就像寻常指针一样危险。不过请
注意,所谓"结果难料"(或说行为不明确 undefined behavior) 意味着任何 STL 实现均可自由选择合适的方式来处理此类错误。稍后你会发现,确保区间有效并不像听起
来那么简单。


'所有算法处理的都是半开区间 (half-open range)---包括起始元素的位置但不包括末尾元素的位置'。


#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

int main(int argc, char** argv)
{
    list<int> coll;
    for(int i = 20; i <= 40 ; i++)
    {
        coll.push_back(i);
    }

    auto pos3 = std::find(coll.begin(), coll.end(),3);

    std::reverse(pos3, coll.end());

    auto pos25 = std::find(coll.begin(), coll.end(),25);

    auto pos35 = std::find(coll.begin(), coll.end(),35);


    cout << *max_element(coll.begin(), coll.end()) << endl;
    cout << *min_element(coll.begin(), coll.end()) << endl;

    return 0;
}

本例首先以 20 至 40 的整数作为容器初值。查找元素值 3 的任务失败后, find() 返回区间的结束位置 (本例为 coll.end()) 并赋值给 pos3。以此作为稍后调用
reverse() 时的区间起点, 纯粹是空摆架子, 因为其结果相当于:

std::reverse(coll.begin(), coll.end());


这其实就是反转一个空区间, 当然毫无效果了。


如果使用 find() 获取某个子集的第一和最后元素, 你必须考虑一点: 半开区间并不包含最后一个元素。

所以上述例子中首次调用 max_element():

std::max_element(pos25, pos35);


找到的是 34, 而不是 35。


为了处理最后一个元素, 你必须把该元素的下一位置传给算法:

std::max_element(pos25, ++pos35);

这样才能得到正确的结果 35。

注意, 本例用的是 list 容器, 所以你只能以 ++ 取得 pos35 的下一个位置。如果面对的是 vector 或 deque 的随机访问迭代器(random-access iterator),
你可以写 pos35+1。这是因为随机访问迭代器允许迭代器算术运算。



// !! 处理多重区间(Multiple Ranges)

'有数个算法可以(或说需要)同时处理多重区间。通常你必须设定第一个区间的起点和终点, 至于其他区间, 只需设定起点即可, 终点通常可由第一区间的元素数量推导出
来'。例如以下程序片段中, equal() 从头开始逐一比较 coll1 和 coll2 的所有元素:

if(std::equal(coll1.begin(), coll1.end(), coll2.begin()))
{
    ...
}

于是, coll2 之中参与比较的元素数量, 间接取决于 coll1 内的元素数量。

这使我们收获一个重要心得: '如果某个算法用来处理多重区间, 那么当你调用它时, 务必确保第二(以及其他)区间所拥有的元素个数至少和第一区间内的元素个数相同'。
特别是执行涂写动作时, 务必确保目标区间 destination range 够大。


#include <iostream>
#include <algorithm>
#include <list>
#include <vector>

using namespace std;


int main(int argc, char** argv)
{
    list<int> coll1 = {1,2,32,1,2,3,4,5};

    vector<int> coll2;

    // Runtime error
    std::copy(coll1.begin(), coll1.end(),coll2.begin());
    return 0;
}

这里调用了 copy() 算法, 将第一区间内的全部元素拷贝至目标区间。如上所述, 第一区间的起点和终点都已指定, 第二区间只指出起点。然而, 由于该算法执行的是
覆写动作(overwrite)而非安插动作(insert), 所以目标区间必须拥有足够的元素被覆写, 否则就会像这个例子一样,导致不明确行为。

'如果目标区间内没有足够的元素供覆写, 通常意味着你会覆写 coll2.end() 之后的任何东西, 幸运的话程序立即崩溃——这起码还能让你知道出错了'。

想要避免上述错误,你可以(1):确认目标区间内有足够的元素空间, 或是(2):采用insert iterator。

我首先解释如何修改目标区间使它拥有足够空间。

为了让目标区间够大, 你要不一开始就给它一个正确大小, 要不就显式变更其大小。这两个办法都只适用于序列式容器(vector、deque、list 和 forward_list)。
关联式容器根本不会有此问题, 因为关联式容器不可能被当作覆写式算法 (overwriting algorithm) 的操作目标。

以下例子展示了如何扩充容器大小:

#include <algorithm>
#include <vector>
#include <list>
#include <deque>

using namespace std;

int main(int argc, char** argv)
{
    list<int> coll1 = {1,3,2,6,5,8,6};
    vector<int> coll2;

    coll2.resize(coll1.size());

    std::copy(coll1.begin(),coll1.end(),coll2.begin());

    deque<int> coll3(coll2.size());

    std::copy(coll2.begin(),coll2.end(),coll3.begin());
    return 0;
}

在这里, resize() 的作用是改变 coll2 的元素个数:

coll2.resize(coll1.size());

coll3 则是在初始化时就指明要有足够空间, 以容纳 coll1 中的全部元素:

deque<int> coll3(coll2.size());

注意, 这两种方法都会产出新元素并赋予初值。这些元素由 default 构造函数初始化, 没有任何实参。你可以传递额外的实参给构造函数和 resize(), 这样就可以按
你的意愿将新元素初始化。


// !! 迭代器之适配器 (Iterator Adapter)

'迭代器 (Iterator) 是一个纯抽象概念: 任何东西, 只要其行为类似迭代器, 它就是一个迭代器'。

C++ 标准库提供了数个预定义的特殊迭代器,亦即所谓迭代器适配器 (iterator adapter)。它们不仅是辅助性质而已,它们赋予整个迭代器抽象概念更强大的威力。


// !! 用户自定义的泛型函数 (User-Defined GenericFunction)

'STL 是一个可扩充框架。它的意思是你可以写你自己的函数和算法, 用以处理集合内的元素'。

当然这些操作函数也可以是泛化的(generic)。然而, 若要在这些操作函数内声明一个合法的迭代器,必须与容器类型相应, 因为不同的容器有不同的迭代器。为了协助写
出泛型函数, 每一个容器类型都提供有若干内部的类型定义。考虑以下例子:


#include<iostream>
#include<string>

template<typename T>
inline void PRINT_ELEMENT(const T& coll, const std::string& str = ""){
    std::cout << str;
    for(const auto& elem : coll)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

这个例子定义了一个泛型函数, 打印出一个可有可无的 string, 后面紧接着是给定的容器的全部元素。


在 C++11 之前, 一个 "遍历所有元素" 的循环看起来如下:

typenname T::const_iterator pos;
for(pos = coll.begin(); pos != coll.end(); ++ pos)
{
    ...
}

这里声明 pos 为拥有 "被传入的容器" 的类型内的某个迭代器类型。


在 PRINT_ELEMENTS 函数中, 可有可无的第二实参是个 string, 用作被写出的每一个元素的前缀(prefix)。因此, 使用 PRINT_ELEMENTS(), 你可以像这样注释
或介绍你的输出:

PRINT_ELEMENTS(coll, "all elements:");


// !! 更易型算法（Manipulating Algorithm）


到目前为止, 已经介绍了 STL 作为框架 framework 的整个概念: '容器表述"管理集合数据"的种种不同概念, 算法在这些集合内执行读取和涂写操作,迭代器则是容器
和算法之间的黏合剂, 由容器提供, 允许你迭代所有元素, 也允许你选择不同的方向, 或采用特殊模式'。

然而现在, 是说明 STL 框架的 BUT 的时候了: 现实中存在某些限制和某些需要避开的事物, 这都是应该让你知道的, 其中许多和容器/元素的改动(modification)相
伴相生。

有些算法(更明确地说是那些可能移除元素的算法)会改动标的区间。如果这种情况发生, 特殊规定会起作用, 本节将解释它们。

// !! 移除（Removing）元素

算法 remove() 某个区间删除元素。然而如果你用它来删除容器内的所有元素, 其行为肯定会让你吃惊。例如:

#include <algorithm>
#include <iterator>
#include <list>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    list<int> coll;
    for(int i = 0; i < 6; i++)
    {
        coll.push_front(i);
        coll.push_back(i);
    }

    cout << "pre:";
    copy(coll.begin(), coll.end(),ostream_iterator<int>(cout, " "));
    cout << endl;

    std::remove(coll.begin(), coll.end(), 3);

    cout << "post: " << endl;
    copy(coll.begin(), coll.end(),ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}

对 STL 缺乏深层认识的人, 看了这个程序, 必然认为所有数值为 3 的元素都会从集合中被移除。然而, 程序的输出却如下:

pre: 6 5 4 3 2 1 1 2 3 4 5 6
post:6 5 4 2 1 1 2 4 5 6 5 6

remove() 并没有改变集合中的元素数量。

cend() 返回的是当初那个终点, size() 返回的还是当初那个大小。不过某些事情还是有了变化: 元素的次序改变了, 有些元素被删除了。数值为 3 的元素被其后的元
素覆盖了。'至于集合尾端那些未被覆盖的元素, 原封不动——但从逻辑角度来说, 那些元素已经不属于这个集合了'。


'事实上, 这个算法返回了一个新终点。你可以利用该终点获得新区间、缩减后的容器大小, 或是获得被删除元素的个数'。

看看下面这个改进版本:                      

#include <algorithm>
#include <iterator>
#include <list>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    list<int> coll;
    for(int i = 0; i < 6; i++)
    {
        coll.push_front(i);
        coll.push_back(i);
    }

    cout << "pre:";
    copy(coll.begin(), coll.end(),ostream_iterator<int>(cout, " "));
    cout << endl;

    list<int>::iterator end = std::remove(coll.begin(), coll.end(), 3);

    cout << "post: " << endl;
    copy(coll.begin(), end,ostream_iterator<int>(cout, " "));

    cout << "number of remove elements: " << std::distance(end, coll.end()) << endl;

    std::erase(endl, coll.end());

    std::copy(coll.begin(), coll.end(),ostream_iterator<int>(cout, ""));
    cout << endl;
    return 0;
}


在这个版本中, remove() 的返回值被赋予迭代器 end。

list<int>::iterator end = std::remove(coll.begin(), coll.end(), 3);

这个 end 正是 "被修改集合" 经过元素移除动作后的新逻辑终点。


接下来你便可以拿它当作新终点使用:

copy(coll.begin(), end, ostream_iterator<int>(cout, " "));

另一种可能用法是, 借由测定集合之逻辑终点和实际终点之间的距离, 获得"被删除元素"的数量:

std::distance(end, coll.end());

'在这里, 原本为了迭代器而设计的辅助函数 distance() 发挥了作用, 它的功用是返回两个迭代器之间的距离'。如果这两个迭代器都是随机访问迭代器 (
random-access iterator) , 你可以使用 operator- 直接计算其距离。不过本例所用的容器是 list, 只提供双向迭代器。

'如果真想把那些被删除的元素斩草除根, 你必须调用该容器的相应成员函数'。容器所提供的成员函数 erase() 正适用于此目的。erase() 可以删除"实参所指示的区
间"内的全部元素:

coll.erase(end, coll.end());

如果你需要以单一语句来删除元素, 可以这么做:

coll.erase(std::remove(coll.begin(), coll.end(),3), coll.end());

为何算法不自己调用 erase() 呢 ? '这个问题正好点出 STL 为获取弹性而付出的代价'。

通过"以迭代器为接口", STL 将数据结构和算法分离开来。然而迭代器只不过是"容器内部某一位置"的抽象概念而已。一般说来, 迭代器对自己所属的容器一无所知。
任何"以迭代器访问容器"的算法, 都不得(无法) 通过迭代器调用容器类所提供的任何成员函数。


这个设计导致一个重要结果:算法的操作对象不一定得是"容器内的全部元素"所形成的区间, 而可以是那些元素的子集。甚至算法可作用于一个"并未提供成员函数 erase()"
的容器身上 (array 就是个例子)。'所以, 为了达成算法的最大弹性, 不强求"迭代器必须了解其容器细节"还是很有道理的'。

注意, 通常并无必要删除那些"已被移除"的元素。'以逻辑终点取代容器的实际终点, 通常就足以应对现实情况'。你可以拿这个逻辑终点搭配任何算法演出。


// !! 更易 Associative（关联式）和 Unordered（无序）容器

更易型算法(指那些会移除 remove、重排 reorder、修改 modify 元素的算法) 若用于关联式容器或无序容器, 会出问题。'关联式和无序容器不能被当作操作目标, 
原因很简单: 如果更易型算法用于关联式和无序容器身上, 会改变某位置上的值, 进而破坏容器本身对次序的维护'(对关联式容器而言是其已排序 sorted 特性, 对无序
容器而言则是其 hash 函数的运算结果)。'为避免累及内部次序,关联式容器和无序容器的所有迭代器均被声明为指向常量(不变量)的 value 或 key'。如果你更动关联
式容器或无序容器的元素, 会导致编译错误。

这使你无法在关联式容器身上运用移除型 (removing) 算法, 因为这类算法实际上悄悄更易了元素: "被移除元素"被其后的"未被移除元素"覆盖。

现在问题来了, 如何从关联容器和无序容器中删除元素?

好吧, 很简单:调用它们的成员函数! 每一种关联式容器和无序容器都提供用以移除元素的成员函数。例如你可以调用 erase():

#include <algorithm>
#include <iterator>
#include <iostream>
#include <set>

using namespace std;

int main(int argc, char** argv)
{
    set<int> coll = {1,2,3,4,5,6,7,8,9};

    std::copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    int num = coll.erase(3);

    cout << "the number of remove elements is " << num << endl;

    std::copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}

注意, 容器类提供了多个不同的 erase() 成员函数。其中一种形式是以"欲删除之元素值"为唯一实参, 并返回被删除元素的个数。


// !! 算法vs.成员函数

就算我们符合种种条件, 得以使用某个算法, 那也未必就一定是好。容器本身可能提供功能相似而效能更佳的成员函数。

一个极佳例子便是对 list 的元素调用 remove()。算法本身并不知道它工作于 list 身上, 因此它在任何容器中都一样, 做些四平八稳的工作: 改变元素值, 从而重
新排列元素。如果它移除第一个元素, 后面所有元素就会分别被设给各自的前一个元素。这就违反了 list 的主要优点--借由修改链接 (link) 而非实值 (value)来安
插、移动、移除元素。


为了避免这么糟糕的表现, list 针对所有更易型算法提供了一些对应成员函数。是的, 如果你使用 list 就应该使用这些成员函数。

#include <algorithm>
#include <iterator>
#include <iostream>
#include <list>

using namespace std;

int main(int argc, char** argv)
{
    list<int> coll;

    for(int i=0; i < 6 ; i++)
    {
        coll.push_front(i);
        coll.push_back(i);
    }

    cout << endl;

    // remove all elements with values 3(poor performance)
    coll.erase(std::remove(coll.begin(), coll.end(),3), coll.end());
    // remove all elements with values 4(good performance)
    coll.erase(4);

    return 0;
}


'如果高效能是你的首要目标, 你应该总是优先选用成员函数'。问题是你必须先知道, 某个容器确实存在效能明显突出的成员函数。面对 list 却使用 remove()算法
, 决不会收到任何警告信息或报错通知。然而如果你决定使用成员函数, 一旦换用另一种容器, 就不得不更改代码。
































