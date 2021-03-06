
// !! STL 初识

// !! STL 的诞生

1. 长久以来, 软件界一直希望建立一种可重复利用的东西

2. C++ 的面向对象和泛型编程思想, 目的就是复用性的提升

3. 大多情况下, 数据结构和算法都未能有一套标准, 导致被迫从事大量重复工作

4. 为了建立数据结构和算法的一套标准,诞生了 STL

// !! STL 基本概念

1. STL(Standard Template Library,标准模板库)

2. STL 从广义上分为: 容器(container) 算法(algorithm) 迭代器(iterator)

3. 容器和算法之间通过迭代器进行无缝连接

4. STL 几乎所有的代码都采用了模板类或者模板函数


// !! STL 六大组件

STL 大体分为六大组件, 分别是:容器、算法、迭代器、仿函数、适配器(配接器)、空间配置器

1. 容器: 各种数据结构, 如 vector、list、deque、set、map 等, 用来存放数据。

2. 算法: 各种常用的算法, 如 sort、find、copy、for_each 等

3. 迭代器: 扮演了容器与算法之间的胶合剂

4. 仿函数: 行为类似函数, 可作为算法的某种策略

5. 适配器: 一种用来修饰容器或者仿函数或迭代器接口的东西

6. 空间配置器: 负责空间的配置与管理


// !! STL 中容器、算法、迭代器

容器: 置物之所也

'STL 容器就是将运用最广泛的一些数据结构实现出来'

常用的数据结构: 数组, 链表, 树, 栈, 队列, 集合, 映射表 等

这些容器分为序列式容器和关联式容器两种:

​序列式容器:'强调值的排序, 序列式容器中的每个元素均有固定的位置'。'关联式容器': 二叉树结构,各元素之间没有严格的物理上的顺序关系


算法: 问题之解法也

有限的步骤, 解决逻辑或数学上的问题, 这一门学科我们叫做算法(Algorithms)


'算法分为:质变算法和非质变算法'。

质变算法: 是指运算过程中会更改区间内的元素的内容。例如拷贝, 替换, 删除等等

非质变算法: 是指运算过程中不会更改区间内的元素内容, 例如查找、计数、遍历、寻找极值等等


'迭代器: 容器和算法之间粘合剂'

提供一种方法, 使之能够依序寻访某个容器所含的各个元素, 而又无需暴露该容器的内部表示方式。

每个容器都有自己专属的迭代器

迭代器使用非常类似于指针, 初学阶段我们可以先理解迭代器为指针

// !! 容器算法迭代器初识

STL 中最常用的容器为 Vector, 可以理解为数组, 下面我们将学习如何向这个容器中插入数据、并遍历这个容器。

// !! vector 存放内置数据类型

容器: vector

算法: for_each

迭代器: vector<int>::iterator

See: vectorDemo.cpp

output:

 » g++ --std=c++11 VectorDemo.cpp
--------------------------------------------------------------------------------
» ./a.out 
10
20
30
40
10
20
30
40
10
20
30
40
--------

// !! vector 存放自定义数据类型

vector 中存放自定义数据类型, 并打印输出

see: vectorDemo2.cpp

注意拷贝构造和 vector 容器的容量自动增长导致的构造和析构

使用 reverse 可优化不必要的容量自动增长导致的 copy 代价

 » g++ --std=c++11 VectorDemo2.cpp                                                                        
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 » ./a.out                                                                                                
Prepare person Data
constructor person aaa with age is 1
constructor person bbb with age is 2
constructor person ccc with age is 3
constructor person ddd with age is 4
constructor person eee with age is 5
Store person In Vector
destructor person aaa with age is 1
destructor person aaa with age is 1
destructor person bbb with age is 2
destructor person aaa with age is 1
destructor person bbb with age is 2
destructor person ccc with age is 3
destructor person ddd with age is 4
persons size: 5
Traverse Vector 
Name:aaa age:1
Name:bbb age:2
Name:ccc age:3
Name:ddd age:4
Name:eee age:5
destructor person eee with age is 5
destructor person ddd with age is 4
destructor person ccc with age is 3
destructor person bbb with age is 2
destructor person aaa with age is 1
destructor person aaa with age is 1
destructor person bbb with age is 2
destructor person ccc with age is 3
destructor person ddd with age is 4
destructor person eee with age is 5

constructor person e with age is 1
constructor person f with age is 2
constructor person g with age is 3
constructor person h with age is 4
constructor person i with age is 5
Name:e Age:1
Name:f Age:2
Name:g Age:3
Name:h Age:4
Name:i Age:5
destructor person i with age is 5
destructor person h with age is 4
destructor person g with age is 3
destructor person f with age is 2
destructor person e with age is 1


// !! vector 容器嵌套容器

容器中嵌套容器, 我们将所有数据进行遍历输出

see:VectorDemo3.cpp