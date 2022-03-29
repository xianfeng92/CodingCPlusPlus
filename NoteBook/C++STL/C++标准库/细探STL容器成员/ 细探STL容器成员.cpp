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




// !! Direct Element Access

reference container::at (size_type idx)
const_reference container::at (size_type idx) const

· 返回索引 idx 所代表的元素(第一个元素的索引为 0)
· 如果传入一个无效索引 (小于0或大于等于 size()), 会导致 out_of_range 异常
· 后续的改动或内存重新分配, 可能会导致这里所返回的 reference 失效
· 如果调用者保证 idx 合法有效, 那么最好使用速度更快的 operator[]




T& map::operator at (const key_type& key)
const T& map::operator at (const key_type& key) const

· 返回 map 之中 key 所对应的 value
· 如果没有任何元素的 key 等于 key, 会抛出 out_of_range 异常
· 始自 C++11
· 提供者: map 和 unordered map



reference container::operator[] (size_type idx)
const_reference container::operator[] (size_type idx) const

· 两者都返回索引 idx 所代表的元素
· 如果传入一个无效索引(小于 0 或大于等于 size(), 会导致不确定的行为。所以调用者必须确保索引有效, 否则应该使用 at()
· 后续的改动或内存重新分配, 可能会导致这里所返回的 reference 失效



T& map::operator[] (const key_type& key)
T& map::operator[] (key_type&& key)

· 关联式数组 (associative array) 的 operator[]
· 在 map 中, 会返回 key 所对应的 value
· 如果不存在 key 为 key 的元素, 本操作会自动创建一个新元素, 其 key 由 key 而来(复制或搬移), 其 value 则由 value 类型之 default 构造函数给予。不存在
  所谓的无效索引(只是会带来意外的行为)


reference container::front()
const_reference container::front() const

· 两者都返回第一个元素 (第一个元素的索引为 0)
· 调用者必须确保容器内拥有元素 (size() > 0), 否则会导致不明确的行为
· 对 string 的支持始自 C++11 
· 提供者: array、vector、deque、list、forward list 和 string


reference container::back()
const_reference container::back() const

· 两者都返回最后一个元素 (其索引为 size()-1)
· 调用者必须确保容器内拥有元素 (size() >0), 否则会导致不明确的行为
· 对 string 的支持始自 C++11
· 提供者: array、vector、deque、list 和 string


T* container::data ()
const T* container::data () const

· 两者都返回一个带着所有元素的 C-style array (或说一个pointer指向第一元素)
· 本函数用来将一个标准库 array 的所有元素传递给一个 C-style array
· string 只有第二形式--const T* container::data () const
· 对 array 和 vector 的支持始自 C++11
· 提供者: array、vector 和 string



// !! 产出迭代器之各项操作


// !! 各容器提供的迭代器种类

Array --随机访问迭代器
Vector --随机访问迭代器
Deque --随机访问迭代器

List --双向迭代器
Forward list --前向迭代器

Set -- 双向, 元素为常量
Multiset -- 双向, 元素为常量

Map -- 双向, Key 为常量
Multimap --  双向, Key 为常量

Unordered Set -- 前向迭代器, 元素为常量
Unordered Multiset -- 前向迭代器, 元素为常量

Unordered map -- 前向迭代器, key 为常量
Unordered multimap -- 前向迭代器,key 为常量


iterator container::begin ()
const_iterator container::begin () const
const_iterator container::cbegin () const

· 返回一个 iterator, 指向容器起始处(第一元素的位置)
· 如果容器为空, 此操作相当于 container::end() 或 container::cend()
· Unordered 容器也提供带有数值实参的 begin() 和 cbegin(), 用以提供 bucket 接口
· cbegin() 始自 C++11



iterator container::end ()
const_iterator container::end () const
const_iterator container::cend () const

· 返回一个 iterator, 指向容器尾端(最后元素的下一位置)
· 如果容器为空, 则此动作相当于 container::begin() 或 container::cbegin()
· cend() 始自 C++11


reverse_iterator container::rbegin ()
const_reverse_iterator container::rbegin () const
const_reverse_iterator container::crbegin () const

· 返回一个反向 iterator, 指向反向迭代的起点(此起点也就是正向之最末一个元素)
· 如果容器为空, 则此动作相当于 container::rend() 或 container::crend()



// !! Inserting and Removing


// !! Inserting Single Element

iterator container::insert (const T& value)
iterator container::insert (T&& value)
pair<iterator,bool> container::insert (const T& value)
pair<iterator,bool> container::insert (T&& value)


· 在 associative 或 unordered 容器中安插 value
· 第一和第三形式会复制 value
· 第二和第四形式会搬移 value 放进容器中, 所以此后 value 的值将不再明确 (unspecified)
· 容器如果允许元素重复, 亦即 (unordered) multiset 和 multimap, 采用第一和第二形式。它们返回新元素的位置。自  C++11 起, 新安插的元素保证被放置于既有的等
  值元素的尾端。
· 容器如果不允许元素重复, 亦即(unordered) set 和 map, 采用第二和第四形式。如果安插不成功(因为已经存在一个元素有着相同的 value 或相同的 key),它们返回既有
  元素的位置和一个 false。如果安插成功, 它们返回新元素的位置和一个true。
· T 是容器的元素类型, 对(unordered) map 和 multimap 而言那是一个 key/value pair
· 对于 map、multimap、unordered map 和unordered multimap, 带有 move 语义的上述形式是个 member template。因此, value 的类型只要能转换为容器的
  value类型(key/value pair)就可以。之所以引入这个性质是为了允许你传入两个 string 使得第一个可被转换为一个constant string(那是key type)
· 第二和第四形式始自 C++11
· 提供者: set、multiset、map、multimap、unordered set、unordered multiset、unordered map 和 unordered multimap。



iterator container::emplace (args)
pair<iterator,bool> container::emplace (args)


. 在 associative 或 unordered 容器中安插新元素, 以 args 为初值

· 容器如果允许元素重复, 亦即 ordered/unordered 的 multiset 和 multimap, 采用第一形式。它们返回新元素的位置。新安插的元素保证被放置于既有的等值元素的尾端。
· 容器如果不允许元素重复, 亦即 ordered/unordered的 set 和 map, 采用第二形式。如果安插不成功 (因为已经存在一个元素有着相同的 value 或相同的 key),它们返回
  既有元素的位置和一个 false。如果安插成功, 它们返回新元素的位置和一个 true


iterator container::insert (const_iterator pos,const T& value)
iterator container::insert (const_iterator pos,T&& value)

在 iterator pos 位置上安插 value:

· 第一形式会复制 value
· 第二形式会搬移 value 放进容器中, 所以此后 value 的值将不再明确 (unspecified)
· 返回新元素的位置
· 容器如果不允许元素重复, 例如 set、map、unordered set和unordered map, 而又已经存在一个元素有着和 value 相同的 key, 那么调用将无作用, 返回的是既有元素
  的位置



void container::push_front (const T& value)
void container::push_front (T&& value)

· 安插 value 使成为第一个元素
· 第一形式会复制 value
· 第二形式始自 C++11, 会搬移 value 放进容器中, 此后 value 的值不再明确(unspecified)
· T 是容器的元素类型
· 两个形式都相当于 insert(begin(), value)
· 提供者: deque、list 和 forward list


void container::emplace_front (args)

· 安插一个新的第一元素, 由实参列(argument list) args 初始化
· 因此, 容器的元素类型必须带有一个可被调用的 (callable) 构造函数接受 args
· 此函数若失败不会带来任何影响
· 始自 C++11
· 提供者: deque、list和forward list


void container::push_back (const T& value)
void container::push_back (T&& value)

· 追加 value, 使成为新的最末元素
· 第一形式会复制 value
· 第二形式始自 C++11, 会搬移 value 放进容器中, 此后 value 的值不再明确 (unspecified)
· T 是容器的元素类型
· 两个形式都相当于 insert(end(), value)



void container::emplace_back (args)

· 追加一个新的最末元素, 它由实参列(argument list) args 初始化
· 因此, 容器的元素类型必须带有一个可被调用的 (callable) 构造函数接受 args




// !! Inserting Multiple Elements


void container::insert (initializer-list)

. 将 initializer-list 内的元素的拷贝插入一个 associative 容器内


iterator container::insert (const_iterator pos, initializer-list)

· 在 iterator pos 位置上安插 initializer-list 中的元素的拷贝
· 返回第一个被安插元素的位置, 或返回 pos--如果 initializer-list 为空


iterator container::insert (const_iterator pos,size_type num,const T& value)

· 在 iterator pos 的位置上安插 num 个 value 拷贝
· 返回第一个被安插元素的位置, 或返回 pos--如果 num==0


void container::insert (InputIterator beg,InputIterator end)

· 将区间 [beg,end) 内所有元素的拷贝安插到 associative 容器内


iterator container::insert (const_iterator pos、InputIterator beg,InputIterator end)

· 将区间 [beg,end) 内所有元素的拷贝安插于迭代器 pos 所指的位置上
· 返回第一个被安插元素的位置, 或返回 pos--如果 beg==end



// !! Removing Element

size_type container::erase (const T& value)

· 从 associative 容器中移除所有和 value 相等的元素
· 返回被移除的元素个数
· 调用被移除元素的析构函数

· T 是被排序值(sorted value)的类型:
-在 (unordered) set 和 multiset 中, T 是元素类型
-在 (unordered) map 和 multimap 中, T 是 key 的类型


iterator container::erase (const_iterator pos)

· 将 iterator pos 所指位置上的元素移除
· 返回后继元素的位置(或返回 end())
· 调用被移除元素的析构函数。

· 注意, 调用者必须确保 iterator pos 有效。

例如:

coll.erase(coll.end());// Error, undefined behavior


iterator container::erase(const_iterator beg,const_iterator end)

· 移除区间 [beg,end) 内的所有元素
· 返回最后一个被移除元素的位置(或返回  end()
· 一如区间惯例, 始于 beg (含)而终于 end (不含)的所有元素都被移除
· 调用被移除元素的析构函数
· 调用者必须确保 beg 和 end 形成一个有效序列, 并且该序列是容器的一部分

提供者: vector、deque、list、set、multiset、map、multimap、unordered set、unordered multiset、unordered map、unordered multimap 和 string


void container::pop_front()

· 移除容器的第一元素

相当于: coll.erase(coll.begin())

· 如果容器是空的, 会导致不明确的行为。因此调用者必须确保容器至少有一个元素, 也就是 !empty()
· 此函数不抛出异常


void container::pop_back()

· 移除容器的最末元素
  相当于: coll.erase(prev(coll.end()));

· 如果容器是空的, 会导致不明确的行为。因此调用者必须确保容器至少有一个元素, 也就是 !empty()



void container::clear()

· 移除所有元素, 将容器清空
· 调用被移除元素的析构函数



// !! Resizing

void container::resize (size_type num)
void container::resize (size_type num,const T& value)


· 将容器大小改为 num

· 如果 size() 原本就是 num, 则两者皆无效
· 如果 num 大于 size(), 则在容器尾端附加额外元素。第一形式通过 default 构造函数来构建新元素, 第二形式以 value 的拷贝作为新元素
· 如果 num 小于 size(), 则移除尾端元素, 获得新的大小。每个被移除元素的析构函数都会被调用


// !! List 和 Forward List 的特殊成员函数


void list::remove (const T& value)
void list::remove_if (UnaryPredicate op)

· remove() 移除所有带 value 值的元素

· remove_if() 移除所有令单参判断式 op(elem) 产出 true 的元素

· 两个形式都会调用被移除元素的析构函数
· 留下的元素保持原先次序 stable (稳定的)


void list::unique()
void list::unique(BinaryPredicate op)

· 移除 (forward) list 内相邻而重复的元素, 使每一个元素都不同于下一个元素

· 第一形式会将所有和前一元素相等的元素移除

· 第二形式的意义是: 任何一个元素 elem, 如果其前一元素是 e, 而 elem 和 e 造成'双参判断式 (binary predicate)' op(elem, e) 获得 true, 那么就移除 elem



void list::splice (const_iterator pos, list& source)
void list::splice (const_iterator pos, list&& source)


· 将 source 的所有元素搬移到 *this, 并将它们安插到 iterator pos 所指位置
· 调用之后, source 被清空
· 如果 source 和 *this 相同, 会导致不明确的行为。所以调用端必须确定 source 和 *this 是不同的 list
· 调用者必须确定 pos 是 *this 的一个有效位置; 否则会导致不明确的行为


void list::sort()
void list::sort(CompFunc cmpPred)

· 对list内的所有元素排序
· 第一形式以 operator< 对 list 的所有元素进行排序
· 第二形式调用 cmpPred 比较两元素, 以此对 list 中的所有元素排序:
  
  Value相同的元素, 其顺序保持不变


void list::merge (list& source)
void list::merge (list&& source)
void list::merge (list& source,CompFunc cmpPred)
void list::merge (list&& source,CompFunc cmpPred)


 将 list source 内的所有元素并入 *this。
· 调用后 source 变成空
· 前两个形式采用 operator< 作为排序准则
· 后两个形式采用 cmpPred 作为可选的排序准则, 以此比较两元素的大小:

cmpPred(elem, sourceElement);

· 诸元素如果含有相等内容, 它们的次序保持不变 (stable)

如果 *this 和 source 在排序准则 operator< 或 cmpPred 之下 sorted, 则新产生的 list 也将会是已排好序, 而且 *this 内的相等元素会优先于 source 内的相
等元素。严格地说, C++standard 要求两个list 必须已排好序, 但实际上对未排序的 list 进行 merge 动作也是可能的,不过使用前最好先确认一下。



void list::reverse()

· 将 list 内的元素次序颠倒



// !! 容器的策略接口(Policy Interface)


// !! Nonmodifying Policy Function


size_type container::capacity () const

· 返回重分配内存之前所能容纳的最多元素个数
· 提供者: vector 和 string



value_compare container::value_comp() const

· 返回一个被用作比较准则的对象
· 在 set 和 multiset 中相当于 key_comp()
· 在 map 和 multimap 中, 它是一个辅助类, 被用作比较准则, 用来比较 key/value pair 中的key


key_compare container::key_comp () const

· 返回 associative 容器的比较准则


key_equal container::key_eq() const

· 返回 unordered 容器的相等性比较准则


hasher container::hash_function() const

· 返回 unordered 容器的 hash 函数


float container::load_factor() const

· 返回 unordered 容器当前的每个 bucket 的平均元素个数


float container::max_load_factor() const

· 返回 unordered 容器的最大负载系数。容器会自动 rehash (增加必要的 bucket 数量)以保持其负载系数低于或等于此值





// !! Modifying Policy Function


void container::reserve(size_type num)

· 内部保留若干内存, 至少够容纳 num 个元素

. 对于 vector, 这个调用只能增加容量。因此, 如果 num 小于或等于当前的真实容量, 它没有效用



void container::shrink_to_fit()

· 缩减内部内存,使刚好吻合实际的元素数量



void container::rehash(size_type bnum)

· 改变 unordered 容器的 bucket 数量, 令其至少为 bnum


void container::max_load_factor(float loadFactor)

. 设定 unordered 容器的最大负载系数为 loadFactor

· loadFactor 只是个提示, 如此一来实现便能自由地根据其内部的布局哲学调整该值

· 此操作可能造成 rehashing, 那会造成 iterator 失效, 改变元素之间的次序, 改变元素落于哪个 bucket 内



// !! Unordered 容器的 Bucket 相关接口

size_type container::bucket_count() const

· 返回 unordered 容器的当前 bucket 数量



size_type container::max_bucket_count() const

· 返回 unordered 容器的最大可能的 bucket 数量





// !!  对分配器 (Allocator) 的支持


'所有 STL 容器都能够与某个分配器对象 (allocator object) 所定义的某种特定内存模型 (memory model) 搭配合作'。


// !! 基本的分配器成员(Fundamental Allocator Member)

container::allocator_type

· 分配器类型


allocator_type container::get_allocator() const

· 返回容器的内存模型 memory model



// !! 带有可选之分配器参数的构造函数

explicit container::container(const Allocator& alloc)

· 建立一个新的空容器, 使用 alloc 作为内存模型 memory model


container::container(const CompFunc& cmpPred,const Allocator& alloc)

· 建立一个新的空容器, 使用 alloc 作为内存模型, 以 cmpPred 为排序准则



container::container(size_type bnum,const Hasher& hasher,const KeyEqual& eqPred,const Allocator& alloc)

· 建立一个新的空容器, 带有至少 bnum 个 bucket, 以 hasher 为 hashing 函数, 以 eqPred  为相等性准则, 以 alloc 为内存模型








