#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

#include<numeric>
#include<iterator>
#include<functional>



using namespace std;
using namespace std::placeholders;

int main(int argc, char **argv)
{
//     // 标准库提供了一组算法，这些算法大多数都是独立于任何特定的容器，这些算法都是通用的
//     // 它们可用于不同类型的容器和不同类型的元素

//     int target = 19;
//     vector<int> values = {0,22, 1, 2, 3, 4, 5, 6, 7,10,12,13,14,15,16,17,18,19,20,21,22,34,454,55,33,22,22};

//     // find 返回指向元素 19 的迭代器
//     auto result = find(values.begin(),values.end(),target);

//     cout << *result << endl;

//     string str = "C++ primer 4Th Edition";
//     auto result1 = find(str.cbegin(),str.cend(),'w');

//     // 泛型算法本身不会执行容器的操作，它只会运行于迭代器之上，执行迭代器操作
//     int ia[] = {11,23,12,34,56,76,534,33};
//     auto result2 = find(begin(ia),end(ia),11);
//     // 标准库提供了超过 100 个算法，与容器类似，这些算法有着一致的结构
//     // 除了少数例外，标准库的算法都是对一个范围内的元素进行操作，我们将此范围称为输入范围
//     // 接受收入范围的算法，总是以前两个参数表示此范围，两个参数分别指向要处理的第一个元素和最后一个元素之后位置的迭代器
//     // 理解算法最基本的方法就是了解它们是否读取元素、改变元素或者重排序元素

//     // 只读算法--一些算法之后读取其输入范围内的元素，从不改变元素, find or accumulate
//     // 对于只是读取而不改变元素的算法，通常使用 cbegin 和 cend
//     int val[] = {0,1,2,3,4,5,5};
//     auto result3 = accumulate(begin(val), end(val),100);
//     cout << result3 << endl;

//     vector<string> lists = {"hello","world","i","am","xforg"};

//     auto result4 = accumulate(lists.cbegin(),lists.cend(),string(""));

//     cout << result4 << endl;


//     vector<string> lists1 = {"hello","world","i"};
//     vector<string> lists2 = {"hello","world","i","am","xforg"};
//     // lists2 中的元素应该至少与 lists1 一样多
//     equal(lists1.cbegin(),lists1.cend(),lists2.cbegin());

//     // 写容器元素的算法---一些算法将新值赋予序列中的元素
//     // 当我们使用这类算法必须确保序列原大小至少不小于我们要求算法写入的元素数量
//     // 记住，算法不会执行容器操作，因此它们自身不可能改变容器大小
    
//     vector<int> intVal = {1,2,3,4,5,6,7};
//     fill(intVal.begin(),intVal.end(),100);

//     auto it = back_inserter(intVal);
//     *it = 19922;

//     vector<string> strVal = {"hello","world","i"};

//     // 一种保证算法有足够的空间来容纳输出数据的方式是使用插入迭代器
//     auto strIt = back_inserter(strVal);

//     fill_n(strIt, 10, string("test"));

//     for (auto &it : strVal)
//     {
//         cout << it << endl;
//     }

//     // 拷贝算法---向目的位置迭代器指向的输出序列中的元素写入数据的算法
//     // 传递给 copy 的目的序列至少要包含和输出序列一样多的元素，这一点很重要

//     int source[] = {1,2,3,4,5,6,7};
//     int target1[sizeof(source)/sizeof(*source)];
//     // 把 source 的内容拷贝给 target
//     auto value = copy(begin(source), end(source), target1);

//     cout << *value << endl;

//     for (int i = 0; i < 7; ++i)
//     {
//         cout << target1[i] << endl;
//     }

//     vector<int> intVal1 = {1,6,3,4,5,6,7,6};
//     // 将 intVal1 中所有值为 6 的元素改为10086
//     replace(intVal1.begin(),intVal1.end(),6,10086);

//     // 重排元容器元素算法---某些算法会重排容器中元素的顺序

//     void elimDups(vector<string> &words)
//     {
//         // 按照字典序排序 words，以便查找重复单词
//         sort(words.begin(),words.end());
//         // unique 重排输入范围，使得每个单词只出现一次
//         // 排列在范围的前部，返回指向不重复区域之后一个位置的迭代器
//         auto end_unique = unique(words.begin(), words.end());
//         // 是删除重复的单词
//         words.erase(end_unique,words.end());
//     }

//     bool isShorter(const string &s1, const string &s2){
//         return s1.size() < s2.size();
//     }

//     sort(words.begin(), words.end(),isShorter);

//     // 稳定排序算法维持相等元素的原有顺序
//     stable_sort(words.begin(), words.end());

//     stable_sort(words.begin(), words.end(),isShorter);


//     // 一个 lambda 表达式表示一个可调用的代码单元，我们可以将其理解成一个未命名的内联函数
//     // [capture list](parameter list)-> return type {function body}
//     // capture list (捕获列表)是指一个 lambda 所在函数中定义的局部变量列表--一个 lambda 只有在其捕获列表中捕获一个它所在函数
//     // 中的局部变量，才能在函数体中使用该变量
//     // 我们可以忽参数列表和返回值，但是必须永远包含捕获列表和函数体
//     // 如果不写返回类型，lambda 表达式会根据函数体中表达式
//     auto function = [](const string &s1, const string &s2)
//     {
//         return s1.size() < s2.size();
//     }

//     void biggies(vector<string> & words, vector<string>::size_type sz)
//     {
//         elimDups(words);
//         stable_sort(words.begin(), words.end(), isShorter);

//         auto wc = find_if(words.begin(), words.end(), [sz](const string &a)->
//                           { return a.size() >= sz };);
//         // 计算满足 size >= sz 元素的数量
//         auto count = words.end() - wc;
//     }

//     // 值捕获，被捕获的值在 lambda 创建时拷贝
//     void func1()
//     {
//         size_t v1 = 19;// 局部变量
//         // 将 v1 拷贝到名为 f 的可调用对象
//         auto f = [v1]{return v1;};
//         v1 = 0;
//         // j 为 42， f 保存了我们创建它时 v1 的拷贝
//         auto j = f();
//     }

//     // 引用捕获-- 当以引用方式捕获一个变量时，必须保证在 lambda 执行时该变量是存在的
//     void func2()
//     {
//         size_t v2 = 199;
//         // 对象 f2 包含 v2 的引用
//         // 当我们在 lambda 函数体内使用 v2 变量时，实际上使用的是 v2 所绑定的对象
//         auto f2 = [&v2]{return v2;};
//         v2 = 0;
//         auto j = f2();
//     }

//     // 对于那种只在一两个地方使用的简单操作，lambda 表达式最有用.
//     // 如果我们需要在很多地方使用相同的操作，通常应该定义一个函数，而不是多次编写相同的 lambda 表达式
//     // 如果一个操作需要很多语句才能完成，通常使用函数更好
//     // 对于捕获局部变量的 lambda，用函数来替代它就不那么容易了


//    // 标准库 bind 函数---可以将 bind 函数看做一个通用的函数适配器，它接受一个可调用对象，生产一个新的可调用对象来“原”对象的参数列表
//    // auto newCallable = bind(callable,arg_list);



      // 插入迭代器 --- 是一种迭代器适配器，它接受一个容器，生成一个迭代器，能够实现向给定容器添加元素
      list<int> llist = {1,2,3,4};
      list<int> llist1,llist2;
      // output llist1 is 4,3,2,1
      copy(llist.begin(),llist.end(),front_inserter(llist1));
      // output llist2 is 1,2,3,4
      copy(llist.begin(),llist.end(),inserter(llist2,llist2.begin()));

      // io 迭代器 istream_iterator 读取输入流； ostream_iterator 向一个输出了写数据
      // 这些迭代器将对应的流当做一个特定类型的元素序列来处理


      // 泛型算法结构
      // 输入迭代器： 可以读取序列中的元素。一个输入迭代器必须支持
      // 1. 用于比较两个迭代器相等或者不相等的运算符（== ！=）
      // 2. 用于推进迭代器的前置或者后置递增运算（++）
      // 3. 用于读取元素的解引用云算法（*）
      // 4. 箭头运算符 -> 解引用迭代器，并提取对象的成员
      // 输出迭代器：只写而不读元素. 用作目的位置的迭代器通常是输出迭代器
      // 前向迭代器：可以读写元素，这类迭代器只能在序列中沿一个方向移动
      // 双向迭代器：可以正向、反向读写序列中的元素
      // 随机访问迭代器：提供在常量时间内访问序列中任意元素的能力
      // 随机访问迭代器支持一下额外操作：1. 用于比较两个迭代器的相对位置关系 2. 迭代器和一个整数值加减运算，运算结果是迭代器前进或后退给定整数个元素个位置
      // 用于两个迭代器的减法运算符（-），得到两个迭代器的距离
      // 算法 sort 要求随机访问迭代器。array、deque、string 和 vector 的迭代器都是随机访问迭代器

      // 算法形参模式
      // 接收单个目的迭代器的算法---向输出迭代器写入数据的算法都是假设目的空间足够容纳写入的数据

      // 算法的命名规范
      // 1. 接收谓词参数来代替 < 或 == 的算法：
      // unique(begin, end) -- 使用 ==  运算符比较元素
      // unique(begin, end, comp) -- 使用 comp 比较元素

      // 2. 接收一个元素值的算法，通常有另外一个不同名的版本：
      // _if 版本的算法
      // find(words.begin(), words.end(),val) -- 查找输入范围内 val 出现的第一个位置
      // find_if(words.begin(), words.end(),pred) -- 查找第一个令 pred 为真的元素
      // 这两个算法提供了命名上差异的版本，而非重载版本，因为两个版本的算法都接受相同数量的参数

      // 3.区分拷贝元素的版本和不拷贝的版本
      // 默认情况下，重排元素的算法都将重排后的元素写回给定的输入序列中，这些算法还提供了另外一个版本
      // 将元素写到一个指定的输入目的位置。写到额外目的空间的算法，都在名字后面加一个 copy
      // reverse(words.begin(), words.end()); -- 反转输入范围内的元素的顺序
      // reverse_copy(words.begin(), words.end(),dest); -- 将元素按逆序拷贝到 dest

      // 特定容器的算法
      // 与其他容器不同，链表 list 和 forward_list 定义了几个成员函数形式的算法
      // 特别地，它定义了独有的  sort、 merge、remove、reverse 和 unique
      // 对于 list和forward_list 应该优先使用成员函数版本的算法，而不是通用的算法 --- 通用版本的算法可以用于链表，但是代价太高了
      // 一个链表可以通过改变元素间的链接而不是真的交换他们的值来达到快速交换

      list<int>  lllist1 = {2,6,8,10};
      list<int>  lllist2 = {1,5,7,11};

      lllist1.merge(lllist2); // 将 lllist2 中的元素合并到 lllist1 中。其中 lllist1 和 lllist2 必须时有序的
      // lllist1.merge(lllist2,comp);
      lllist1.remove(2);
      lllist1.reverse();// 反转 lllist1 中的元素
      lllist1.sort();
      lllist1.unique();





}
