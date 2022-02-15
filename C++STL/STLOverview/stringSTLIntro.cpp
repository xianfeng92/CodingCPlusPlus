// !! STL-常用容器

// !! string 容器

// !! string 基本概念

本质:

string 是 C++ 风格的字符串, 而 string 本质上是一个类

string 和 char * 区别:

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

给 string 字符串进行赋值

赋值的函数原型:

1. string& operator=(const char* s); //char* 类型字符串 赋值给当前的字符串

2. string& assign(const)operator=(const string &s); //把字符串 s 赋给当前的字符串

3. string& operator=(char c); //字符赋值给当前的字符串

4. string& assign(const char *s); //把字符串s赋给当前的字符串

5. string& assign(const char *s, int n); //把字符串s的前n个字符赋给当前的字符串

6. string& assign(const string &s); //把字符串s赋给当前字符串

7. string& assign(int n, char c); //用n个字符c赋给当前字符串

string 的赋值方式很多, operator= 这种方式是比较实用的

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

1. char& operator[](int n); //通过 [] 方式取字符

2. char& at(int n); //通过 at 方法获取字符


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