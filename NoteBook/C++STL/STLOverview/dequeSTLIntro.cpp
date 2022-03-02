
// !! deque 容器

// !! deque 容器基本概念

功能:

双端数组, 可以对头端进行插入删除操作

1. vector 对于头部的插入删除效率低,数据量越大, 效率越低
2. deque 相对而言, 对头部的插入删除速度回比 vector 快
3. vector 访问元素时的速度会比 deque 快


deque 构造函数功能描述:

deque容器构造函数原型:

1. deque<T> deqT; // 默认构造形式

2. deque(beg, end); //构造函数将 [beg, end) 区间中的元素拷贝给本身

3. deque(n, elem); //构造函数将 n 个 elem 拷贝给本身

4. deque(const deque &deq); //拷贝构造函数


总结:deque 容器和 vector 容器的构造方式几乎一致, 灵活使用即可


// !! deque 赋值操作

功能描述:

给 deque 容器进行赋值

函数原型:

1. deque& operator=(const deque &deq); //重载等号操作符

2. assign(beg, end); //将[beg, end)区间中的数据拷贝赋值给本身

3. assign(n, elem); //将 n 个 elem 拷贝赋值给本身


总结: deque 赋值操作也与 vector 相同, 需熟练掌握


// !! deque 大小操作

功能描述:

对 deque 容器的大小进行操作

函数原型:

1. deque.empty(); //判断容器是否为空

2. deque.size(); //返回容器中元素的个数

3. deque.resize(num); //重新指定容器的长度为 num,若容器变长，则以默认值填充新位置。​如果容器变短，则末尾超出容器长度的元素被删除

4. deque.resize(num, elem); //重新指定容器的长度为 num,若容器变长，则以 elem 值填充新位置。​如果容器变短，则末尾超出容器长度的元素被删除

总结:

deque 没有容量的概念
判断是否为空 --- empty
返回元素个数 --- size
重新指定个数 --- resize


// !! deque 插入和删除

功能描述:

向 deque 容器中插入和删除数据

'函数原型':

两端插入操作:

1. push_back(elem); //在容器尾部添加一个数据

2. push_front(elem); //在容器头部插入一个数据

3. pop_back(); //删除容器最后一个数据

4. pop_front(); //删除容器第一个数据


指定位置操作:

1. insert(pos,elem); //在 pos 位置插入一个 elem 元素的拷贝，返回新数据的位置

2. insert(pos,n,elem); //在 pos 位置插入 n 个 elem 数据，无返回值

3. insert(pos,beg,end); //在pos位置插入 [beg,end) 区间的数据，无返回值

4. clear(); //清空容器的所有数据

5. erase(beg,end); //删除 [beg,end) 区间的数据，返回下一个数据的位置

6. erase(pos); //删除 pos 位置的数据，返回下一个数据的位置


总结:

插入和删除提供的位置是迭代器!

尾插 --- push_back
尾删 --- pop_back

头插 --- push_front
头删 --- pop_front


// !!  deque 数据存取

功能描述:

对 deque 中的数据的存取操作

函数原型:

1. at(int idx); //返回索引 idx 所指的数据
2. operator[]; //返回索引 idx 所指的数据
3. front(); //返回容器中第一个数据元素
4. back(); //返回容器中最后一个数据元素

总结:

1. 除了用迭代器获取 deque 容器中元素, [] 和 at 也可以

2. front 返回容器第一个元素

3. back 返回容器最后一个元素


// !! deque 排序

功能描述:

利用算法实现对 deque 容器进行排序

算法:

sort(iterator beg, iterator end) //对 beg 和 end 区间内元素进行排序

总结: sort 算法非常实用, 使用时包含头文件 algorithm 即可



































