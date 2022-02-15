


// !! vector 基本概念

功能:

vector 数据结构和数组非常相似, 也称为'单端数组'

vector 与普通数组区别:

不同之处在于数组是静态空间, 而 vector 可以动态扩展

动态扩展:

并不是在原空间之后续接新空间, 而是找更大的内存空间, 然后将原数据拷贝新空间, 释放原空间

vector 容器的迭代器是支持随机访问的迭代器

// !! vector 构造函数

功能描述:

创建 vector 容器

函数原型:

1. vector<T> v; //采用模板实现类实现，默认构造函数

2. vector(v.begin(), v.end()); //将v[begin(), end())区间中的元素拷贝给本身

3. vector(n, elem); //构造函数将 n 个 elem 拷贝给本身

4. vector(const vector &vec); //拷贝构造函数

总结: vector 的多种构造方式没有可比性, 灵活使用即可

see:VectorIntroDemo.cpp



// !! vector 赋值操作

功能描述:

给 vector 容器进行赋值

函数原型: 

1. vector& operator=(const vector &vec);//重载等号操作符

2. assign(beg, end); //将[beg, end)区间中的数据拷贝赋值给本身

3. assign(n, elem); //将 n 个 elem 拷贝赋值给本身


总结:: vector 赋值方式比较简单, 使用 operator= 或者 assign 都可以

see:VectorIntroDemo.cpp


// !! vector 容量和大小

功能描述:

对 vector 容器的容量和大小操作

函数原型:

empty(); //判断容器是否为空
capacity(); //容器的容量
size(); //返回容器中元素的个数
resize(int num); //重新指定容器的长度为 num，若容器变长，则以默认值填充新位置;如果容器变短，则末尾超出容器长度的元素被删除
resize(int num, elem); //重新指定容器的长度为 num，若容器变长，则以 elem 值填充新位置; 如果容器变短，则末尾超出容器长度的元素被删除

总结:

1. 判断是否为空 --- empty
2. 返回元素个数 --- size
3. 返回容器容量 --- capacity
4. 重新指定大小 --- resize

see:VectorIntroDemo.cpp


// !! vector 插入和删除

功能描述:

对 vector 容器进行插入、删除操作

函数原型:

1. push_back(ele); //尾部插入元素 ele 

2. pop_back(); //删除最后一个元素

3. insert(const_iterator pos, ele); // 迭代器指向位置 pos 插入元素 ele

4. insert(const_iterator pos, int count,ele);//迭代器指向位置  pos 插入 count 个元素 ele

5. erase(const_iterator pos); //删除迭代器指向的元素

6. erase(const_iterator start, const_iterator end);//删除迭代器从 start 到 end 之间的元素

7. lear(); //删除容器中所有元素

总结:

尾插 --- push_back
尾删 --- pop_back
插入 --- insert (位置迭代器)
删除 --- erase (位置迭代器)
清空 --- clear


see:VectorIntroDemo.cpp


// !! vector 数据存取

功能描述:

对 vector 中的数据的存取操作

函数原型:

1. at(int idx); //返回索引 idx 所指的数据

2. operator[]; //返回索引 idx 所指的数据

3. front(); //返回容器中第一个数据元素

4. back(); //返回容器中最后一个数据元素


总结:

1. 除了用迭代器获取 vector 容器中元素, [] 和 at 也可以
2. front 返回容器第一个元素
3. back 返回容器最后一个元素

see:VectorIntroDemo.cpp


// !! vector 互换容器

功能描述:

实现两个容器内元素进行互换

函数原型:

swap(vec); // 将 vec 与本身的元素互换


总结: swap 可以使两个容器互换, 可以达到实用的收缩内存效果


see:VectorIntroDemo.cpp


// !! vector 预留空间

功能描述:

减少 vector 在动态扩展容量时的扩展次数

函数原型:

reserve(int len);//容器预留 len 个元素长度，预留位置不初始化，元素不可访问

总结: 如果数据量较大, 可以一开始利用 reserve 预留空间

see: VectorIntroDemo.cpp