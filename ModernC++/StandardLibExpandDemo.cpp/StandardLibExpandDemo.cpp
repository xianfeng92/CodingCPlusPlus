#include <iostream>

// !! 对标准库的扩充: 新增容器

// !! 一、std::array 和 std::forward_list


std::array

1. 为什么要引入 std::array 而不是直接使用 std::vector ?
   与 std::vector 不同，std::array 对象的大小是固定的，如果容器大小是固定的，那么可以优先考虑使用 std::array 容器。 另外由于 std::vector 是自动扩容的，
   当存入大量的数据后，并且对容器进行了删除操作， 容器并不会自动归还被删除元素相应的内存，这时候就需要手动运行 shrink_to_fit() 释放这部分内存。

   std::vector<int> v;
   std::cout << "V size is " << v.size() << std::endl;// 输出 0
   std::cout << "Capacity is " << v.capacity() << std::endl;// 输出 0
  
    // 如下可看出 std::vector 的存储是自动管理的，按需自动扩张
   // 但是如果空间不足，需要重新分配更多内存，而重分配内存通常是性能上有开销的操作

   v.push_back(1);
   v.push_back(2);
   v.push_back(3);

   std::cout << "size:" << v.size() << std::endl;         // 输出 3
   std::cout << "capacity:" << v.capacity() << std::endl; // 输出 4

   v.push_back(4);
   v.push_back(5);

   std::cout << "size:" << v.size() << std::endl;         // 输出 5
   std::cout << "capacity:" << v.capacity() << std::endl; // 输出 8

   // 如下可看出容器虽然清空了元素，但是被清空元素的内存并没有归还
  v.clear();                                             
  std::cout << "size:" << v.size() << std::endl;         // 输出 0
  std::cout << "capacity:" << v.capacity() << std::endl; // 输出 8

  // 额外内存可通过 shrink_to_fit() 调用返回给系统
  v.shrink_to_fit();
  std::cout << "size:" << v.size() << std::endl;         // 输出 0
  std::cout << "capacity:" << v.capacity() << std::endl; // 输出 0
   

2. 已经有了传统数组，为什么要用 std::array ?

   使用 std::array 能够让代码变得更加“现代化”，而且封装了一些操作函数，比如获取数组大小以及检查是否非空，同时还能够友好的使用标准库中的容器算法，
   比如 std::sort。


std::array 会在编译时创建一个固定大小的数组，std::array 不能够被隐式的转换成指针，使用 std::array 很简单，只需指定其类型和大小即可

std::array<int, 4> arr = {1,2,3,4};

arr.empty();// 检查容器是否为空
arr.size();// 返回容纳的元素数

// 迭代器支持
for(auto & a : arr) {

}

// 用 lambda 表达式排序
std::sort(arr.begin(), arr.end(),[](int a, int b){
    return b < a ;
};)

int len = 4;
std::array<int, len> arr2 = {1,2,3,4} // 非法, 数组大小参数必须是常量表达式

当我们开始用上了 std::array 时，难免会遇到要将其兼容 C 风格的接口，这里有三种做法:

void foo(int *p, int len) {
    return;
}

std::array<int, 4> arr = {1,2,3,4};

// C 风格接口传参
// foo(arr, arr.size());           // 非法, 无法隐式转换
foo(&arr[0], arr.size());
foo(arr.data(), arr.size());

// 使用 `std::sort`
std::sort(arr.begin(), arr.end());


// !! std::forward_list

std::forward_list 使用单向链表进行实现，提供了 O(1) 复杂度的元素插入，不支持快速随机访问（这也是链表的特点），也是标准库容器中唯一一个不
提供 size() 方法的容器。当不需要双向迭代时，具有比 std::list 更高的空间利用率。


// !! 二、无序容器

我们已经熟知了传统 C++ 中的有序容器 std::map/std::set，这些元素内部通过红黑树进行实现, 插入和搜索的平均复杂度均为 O(log(size))。在插入元素时候，
会根据 < 操作符比较元素大小并判断元素是否相同， 并选择合适的位置插入到容器中。当对这个容器中的元素进行遍历时，输出结果会按照 < 操作符的顺序来逐个遍历。

而无序容器中的元素是不进行排序的，内部通过 Hash 表实现，插入和搜索元素的平均复杂度为 O(constant)， 在不关心容器内部元素顺序时，能够获得显著的性能提升。

C++11 引入了两组无序容器：std::unordered_map/std::unordered_multimap 和 std::unordered_set/std::unordered_multiset。

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>


int main(int argc, char **argv)
{
    std::unordered_map<int, std::string> uMap = {
        {1, "1"},
        {3, "3"},
        {2, "2"}
    };

    std::map<int, std::string> v = {
        {1, "1"},
        {3, "3"},
        {2, "2"}
    };

    std::cout << "std::unordered_map" << endl;

    for(const auto &n : uMap)
    {
         std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }

    std::cout << std::endl;
    std::cout << "std::map" << std::endl;
    for(auto &n:v)
    {
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }
}


// !! 三、元组

纵观传统 C++ 中的容器，除了 std::pair 外， 似乎 `没有现成的结构能够用来存放不同类型的数据` （通常我们会自己定义结构）。 但 std::pair 的缺陷是显而易见的，
只能保存两个元素。

// !! 元组基本操作

关于元组的使用有三个核心的函数：

1. std::make_tuple: 构造元组
2. std::get: 获得元组某个位置的值
3. std::tie: 元组拆包


std::get 除了使用常量获取元组对象外，C++14 增加了使用类型来获取元组中的对象:

std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
std::cout << std::get<std::string>(t) << std::endl;
std::cout << std::get<double>(t) << std::endl; // 非法, 引发编译期错误
std::cout << std::get<3>(t) << std::endl;


// !! 运行期索引

如果你仔细思考一下可能就会发现上面代码的问题，std::get<> 依赖一个编译期的常量，所以下面的方式是不合法的:

int index = 0;
std::get<index>(t);


那么要怎么处理？ 答案是，使用 std::variant<>（C++ 17 引入），提供给 variant<> 的类型模板参数可以让一个 variant<>从而容纳提供的几种类型的变量

int i = 1;
std::cout << tuple_index(t, i) << std::endl;


