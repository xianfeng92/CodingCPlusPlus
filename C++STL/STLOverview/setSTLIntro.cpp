// !! set/ multiset 容器

// !! set 基本概念

简介:'所有元素都会在插入时自动被排序'

本质: set/multiset 属于关联式容器, 底层结构是用二叉树实现

set 和 multiset 区别:

1. set 不允许容器中有重复的元素

2. multiset 允许容器中有重复的元素


// !! set构造和赋值

构造:

1. set<T> st; //默认构造函数
2. set(const set &st); //拷贝构造函数


赋值:

1. set& operator=(const set &st); //重载等号操作符

总结:

1. set 容器插入数据时用 insert

2. set 容器插入数据时数据会自动排序


// !! set 大小和交换

统计 set 容器大小以及交换 set 容器

函数原型:

size(); //返回容器中元素的数目
empty(); //判断容器是否为空
swap(st); //交换两个集合容器



总结:

1. 统计大小 --- size

2. 判断是否为空 --- empty

3. 交换容器 --- swap


// !! set 插入和删除

set 容器进行插入数据和删除数据

函数原型:

1. insert(elem); //在容器中插入元素

2. clear(); //清除所有元素

3. erase(pos); //删除 pos 迭代器所指的元素, 返回下一个元素的迭代器

4. erase(beg, end); //删除区间[beg,end)的所有元素, 返回下一个元素的迭代器

5. erase(elem); //删除容器中值为 elem 的元素


总结:

插入 --- insert
删除 --- erase
清空 --- clear

// !! set 查找和统计





































