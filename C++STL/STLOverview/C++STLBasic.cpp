
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


// !! STL-常用容器

// !! string 容器

// !! string 基本概念

本质:

string 是 C++ 风格的字符串, 而 string 本质上是一个类

string 和 char * 区别：

char * 是一个指针

string 是一个类, 类内部封装了 char*, 管理这个字符串, 是一个 char* 型的容器

特点:

string 类内部封装了很多成员方法

例如: 查找 find, 拷贝 copy, 删除 delete 替换 replace, 插入 insert

string 管理 char* 所分配的内存, 不用担心复制越界和取值越界等, 由类内部进行负责


// !! string 构造函数

构造函数原型:

1. string(); //创建一个空的字符串 例如: string str; 

2. string(const char* s); //使用字符串 s 初始化

3. string(const string& str); //使用一个 string 对象初始化另一个 string 对象

4. string(int n, char c); //使用 n 个字符 c 初始化


总结: string的多种构造方式没有可比性, 灵活使用即可

see: StringDemo.cpp

// !! string 赋值操作

功能描述:

给string字符串进行赋值

赋值的函数原型:

1. string& operator=(const char* s); //char* 类型字符串 赋值给当前的字符串

2. string& assign(const)operator=(const string &s); //把字符串 s 赋给当前的字符串

3. string& operator=(char c); //字符赋值给当前的字符串

4. string& assign(const char *s); //把字符串s赋给当前的字符串

5. string& assign(const char *s, int n); //把字符串s的前n个字符赋给当前的字符串

6. string& assign(const string &s); //把字符串s赋给当前字符串

7. string& assign(int n, char c); //用n个字符c赋给当前字符串

string的赋值方式很多, operator= 这种方式是比较实用的

see: StringDemo.cpp

// !! string 字符串拼接

功能描述:

实现在字符串末尾拼接字符串

函数原型:

1. string& operator+=(const char* str); //重载+=操作符

2. string& operator+=(const char c); //重载+=操作符

3. string& operator+=(const string& str); //重载+=操作符

4. string& append(const char *s); //把字符串s连接到当前字符串结尾

5. string& append(const char *s, int n); //把字符串s的前n个字符连接到当前字符串结尾

6. string& append(const string &s); //同operator+=(const string& str)

7. string& append(const string &s, int pos, int n);//字符串s中从pos开始的n个字符连接到字符串结尾


// !! string 查找和替换

功能描述:

查找: 查找指定字符串是否存在

替换: 在指定的位置替换字符串

'函数原型':

1. int find(const string& str, int pos = 0) const; //查找 str 第一次出现位置,从 pos 开始查找

2. int find(const char* s, int pos = 0) const; //查找 s 第一次出现位置,从 pos 开始查找

3. int find(const char* s, int pos, int n) const; //从 pos 位置查找 s 的前 n 个字符第一次位置

4. int find(const char c, int pos = 0) const; //查找字符 c 第一次出现位置

5. int rfind(const string& str, int pos = npos) const; //查找 str 最后一次位置,从 pos 开始查找

6. int rfind(const char* s, int pos = npos) const; //查找 s 最后一次出现位置,从 pos 开始查找

7. int rfind(const char* s, int pos, int n) const; //从 pos 查找s的前n个字符最后一次位置

8. int rfind(const char c, int pos = 0) const; //查找字符 c 最后一次出现位置

9. string& replace(int pos, int n, const string& str); //替换从 pos 开始 n 个字符为字符串 str

10. string& replace(int pos, int n,const char* s); //替换从 pos 开始的 n 个字符为字符串 s 示例


总结:

1. find 查找是从左往后, rfind从右往左

2. find 找到字符串后返回查找的第一个字符位置, 找不到返回 -1

3. replace 在替换时, 要指定从哪个位置起, 多少个字符, 替换成什么样的字符串

see: StringDemo.cpp

// !! string 字符串比较

功能描述:

字符串之间的比较

比较方式:

'字符串比较是按字符的 ASCII 码进行对比'

= 返回 0

> 返回 1

< 返回 -1

'函数原型':

int compare(const string &s) const; //与字符串 s 比较

int compare(const char *s) const; //与字符串 s 比较

总结: '字符串对比主要是用于比较两个字符串是否相等, 判断谁大谁小的意义并不是很大'


// !! string 字符存取

string 中单个字符存取方式有两种:

1. char& operator[](int n); //通过[]方式取字符

2. char& at(int n); //通过at方法获取字符


总结: string字符串中单个字符存取有两种方式, 利用 [] 或 at

see: StringDemo.cpp


// !! string 插入和删除

功能描述:

对 string 字符串进行插入和删除字符操作

'函数原型':

1. string& insert(int pos, const char* s); // 插入字符串

2. string& insert(int pos, const string& str); //插入字符串

3. string& insert(int pos, int n, char c); // 在指定位置插入 n 个字符 c

4. string& erase(int pos, int n = npos); //删除从 Pos 开始的 n 个字符


// !! string 子串

功能描述:

从字符串中获取想要的子串

'函数原型':

string substr(int pos = 0, int n = npos) const; //返回由 pos 开始的 n 个字符组成的字符串


总结: '灵活的运用求子串功能, 可以在实际开发中获取有效的信息'

see: StringDemo.cpp













