// !! 基于对象的编程风格

根据过去的种种使用经验, 我们明白了 class 的哪些相关事务呢?

首先, 在使用 class 之前, 由于它并非程序语言本身内置, 所以我们必须先让程序知道它。通常我们会包含某个头文件来完成这件事:

#include <string>

std::string words[4] = {"hello", "world", "happy", "today"};

class 名称被视为一个类型 (type)名称, 就像内置类型 int、double 一样。

Class object的初始化做法有很多种:

std::string dummy("dummy");
std::vector<std::string> svec1;
std::vector<std::string> svec2(5);
std::vector<std::string> svec3(5, "hello");
std::vector<std::string> svec4(words, words + 4);


每个 class 都会提供一组操作函数, 让我们作用于其 object 上。这些操作函数包括具名函数: 如 size() 和 empty() 以及重载运算符, 如 equality 和 assignment 
运算符。


if(svec4 != svec3 || !svec2.empty()) {

}

if(svec4.size() == 4){

}


'通常我们并不知道 class 的实现内容'。例如, string 是在每次我们要求计算其大小时才去计算呢? 还是它将自己的大小储存在每个  object 之中呢? vector 的元素究竟
是储存在 vector 对象内呢? 还是存在其他地方, 再通过 vector 对象中的指针加以定位呢? 这些我们都不知道。

一般而言, class 由两部分组成: 一组公开的 public 操作函数和运算符, 以及一组私有的 private 实现细节。

这些操作函数和运算符称为 class 的 member function, 并代表这个 class 的公开接口。身为 class 的用户, 只能访问其公开接口。这也就是我们使用 string、vector
的方式。

例如, 针对 string 的 member function size(), 我们只知其原型声明 (prototype), 亦即: 参数列表为 void, 返回整数值。

'class 的 private 实现细节可由 member function 的定义以及与此 class 相关的任何数据组成'。例如,假设 string class object 的 size() 每次被调用, 都会
重新计算其字符串长度, 那么就不需要任何相关数据来储存这份信息--size() 定义中可能利用 for 循环之类的遍历方式, 取得字符串长度。但如果  string class object 
欲储存其字符串长度,就必须在每个 class object 中定义 private data member, 并在 size() 定义中将该值返回。每当字符串长度有所变动, 这份 data member 都必
须同步更新。


'class 用户通常不会关心此等实现细节。身为一个用户, 我们只利用其公开接口来进行编程'。这种情形下, 只要接口没有更改, 即使实现细节重新打造, 所有的应用程序代码也不
需要变动。

这一章, 我们的境界'将从 class 的使用提升至 class 的设计与实现'。这正是 C++ 程序员的主要工作。



// !! 如何实现一个 Class









