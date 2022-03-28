// !!  细探 STL 容器成员


// !! 容器内的类型

'container::value_type', 元素类型:

1. 用于 (unordered) set 和 multiset 时是常量

2. 用于 (unordered) map 和 multimap 时是 pair<const keyType, mappedType>


提供者: array、vector、deque、list、forward list、set、multiset、map、multimap、unordered set、unordered multiset、unordered map、
       unordered multimap 和 string。



'container::reference', 元素的引用类型 reference type

典型定义: container::value_type&

提供者: array、vector、deque、list、forward list、set、multiset、map、multimap、unordered set、unordered multiset、unordered map、
       unordered multimap 和 string


'container::const_reference'

1. read-only element 的引用类型

2. 典型定义: const container::value_type&

提供者: array、vector、deque、list、forward list、set、multiset、map、multimap、unordered map、unordered multimap 和 string



'container::iterator', 迭代器类型

提供者: array、vector、deque、list、forward list、set、multiset、map、multimap、unordered set、unordered multiset、unordered map、
       unordered multimap 和 string



'container::const_iterator', read-only 迭代器的类型


'container::reverse_iterator', 反向迭代器类型

提供者: array、vector、deque、list、set、multiset、map、multimap 和 string


'container::const_reverse_iterator'

1. read-only 反向迭代器的类型


'container::pointer'

1.  指针 (用以指向元素) 的类型


'container::const_pointer'

1. read-only 指针 (用以指向元素) 的类型



'container::size_type'

1. 无正负号整数类型, 用于表示容器大小

提供者: array、vector、deque、list、forward list、set、multiset、map、multimap、unordered set、unordered multiset、unordered map、
       unordered multimap 和 string



'container::difference_type'

1. 带正负号的整数类型, 用以定义距离



'container::key_type'

1. 用以定义关联式和无序(associative and unordered)容器的元素的 key 类型

提供者: set、multiset、map、multimap、unordered set、unordered multiset、unordered map 和 unordered multimap



'container::mapped_type'

1. 用以定义关联式和无序(associative and unordered) 容器的元素的 value 类型

提供者: map、multimap、unordered map 和 unordered multimap


'container::key_compare'

1. 关联式(associative)容器内的 比较准则 的类型

2.  提供者: set、multiset、map 和 multimap


'container::value_compare'

1. 整个元素之比较准则 (comparison criterion) 的类型

2. 用于 set 和 multiset 时, 相当于 key_compare

3. 在 map 和 multimap 中, 它是比较准则的辅助类,仅比较两元素的 key



'container::hasher'

1. 无序 (unordered) 容器内的 hashing 函数的类型





// !! Create, Copy and Destroy


'container::container()', 建立一个新的空容器


'explicit container::container(const CompFunc& cmpPred)'

1.  以 cmpPred 为排序准则建立一个空容器

提供者: set、multiset、map 和 multimap


'explicit container::container (size_type bnum)'

'explicit container::container (size_type bnum,const Hasher& hasher)'

'explicit container::container (size_type bnum,const Hasher& hasher,const KeyEqual& eqPred)'

'container::container (initializer-list)'

'container::~container()'

1. 析构函数
2. 移除所有元素, 并释放内存
3. 对每个元素调用其析构函数



// !! Nonmodifying Operation

// !! Size Operation

bool container::empty () const

· 检验容器是否为空 (空表示没有元素)
· 相当于 begin() == end(), 但可能更快
· 复杂度: 常量时间


size_type container::size () const

· 返回现有元素的数量
· 欲检查容器是否为空(即不含元素)应使用 empty(), 因为 empty() 可能更快
· 复杂度: 常量时间


size_type container::max_size () const

· 返回容器可内含的最大元素个数
· 这是一个与实现技术相关的值,可能取决于容器的内存模型。更明确地说, 由于 vector 通常使用单一内存区段(memory segment), 所以 vector 的这个值往往小于其他容器
· 复杂度:常量时间


// !! Comparison Operation


bool operator == (const container& c1,const container& c2)
bool operator != (const container& c1,const container& c2)

. 返回两个容器相等或不等

. 两个容器如果拥有相同数量的元素, 且元素内容相同(亦即对应之两两元素施以 operator== 都导致 true) 便是相等。但 unordered 容器还包括必须相等的元素有着相同的
  次序。



// !! Associative 和 Unordered 容器特有的非更易型操作

size_type container::count (const T& value) const

· 返回与 value 相等的元素个数

· T是被排序值的类型:

-在 set 和 multiset 中, T 是元素类型

-在 map 和 multimap 中, T 是 key 的类型

iterator container::find (const T& value)
const_iterator container::find (const T& value) const


· 返回第一个其值等于 value 的元素的位置

· 如果找不到这样的元素就返回 end()

· T是被排序值的类型:

-在 set 和 multiset 中, T 是元素类型
-在 map 和 multimap 中, T 是 key 的类型



// !! Assignment

container& container::operator= (const container& c)

· 这是一个 copy assignment 操作符

. 将 c 的所有元素赋值给现有容器, 亦即以 c 的元素替换所有现有元素

· 这个操作符会针对被覆写(overwritten)的元素调用其 assignment 操作符, 针对被附加(appended)的元素调用其 copy 构造函数, 针对被移除(removed)的元素调用
  其析构函数。


container& container::operator= (container&& c)

· 这是一个 move assignment 操作符
· 将 c 的所有元素搬移给 *this, 亦即以 c 的元素替换所有现有元素
· 调用之后, c 仍然有效, 但内容不明确 (不保证)
· 始自 C++11



void container::swap (container& c)
void swap (container& c1, container& c2)

· 和 c 交换内容;或是交换 c1 和 c2 的内容

· 上述两个操作都互换:
-容器的元素
-排序准则、相等性准则、hash 函数对象--如果有的话





















