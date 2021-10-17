#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <array>
#include <iostream>

# include <stack>
# include <queue>




using namespace std;

// 一般来说，应用中占主导地位的操作（执行访问操作更多还是插入删除更多）决定了容器类型的选择
// 一般来说，每个容器都定义在一个头文件中，文件名和类型名相同
int main(int argc, char **argv)
{

    // 通常使用 vector 是最好的选择，除非你有很好的理由选择其他容器
    // vector<string> listers;
    // forward_list<string> forwardlist;
    // deque<string> deq;
    // list<string> lists
    // auto forward = forwardlist.iterator();
    // auto backward = forwardlist.const_iterator();
    // string  str("hello world");

    // vector<string> listers = {"hello","world","I","am","so","happy"};

    // for (auto &l : listers)
    // {
    //     cout << l << endl;
    // }

    // for (auto v = listers.begin(); v != listers.end(); ++v)
    // {
    //     cout << *v << endl;
    // }

    // cout << "list size is " << listers.size() << endl;
    // cout << "list max size is " << listers.max_size() << endl;
    // cout << "list is empty " << listers.empty() << endl;
    // listers.push_back("good");
    // for (auto &l : listers)
    // {
    //     cout << l << endl;
    // }

    // auto begin = listers.cbegin();
    // auto end = listers.cend();
    // while (begin != end)
    // {
    //     cout << *end << endl;
    //     end--;
    // }
    // cout << *end << endl;

    
    // vector<string> list2 = {"tell", "me", "a", "joke"};
    // // 当将一个容器初始化为另外一个容器的拷贝时，两个容器类型和元素类型都必须相同
    // vector<string> list1(list2);
    // auto begList2 = list2.cbegin();
    // auto endList2 = begList2 + 2;
    // // 只有顺序容器的构造函数才接受大小参数，关系容器并不支持
    // vector<string> list3(begList2,endList2);
    // vector<string> list4(10,"nio");
    // vector<string> list5(10);
    // // 当定义一个 array 时，除了指定元素类型，还要指定容器大小
    // array<string,10> arr = {"hello","I","am","xforg"};
    // array<string,10> arr2 = arr;
    //  cout << arr2[2] << endl;
    // // list1 = list2;
    // // for (auto &l : arr)
    // // {
    // //     cout << l << endl;
    // // }

    // vector<string> v1 = {"hello","I","am","xforg"};
    // vector<string> v2 = {"tell","me","a","joke"};
    // // 交换两个相同类型容器的内容，交换两个容器内容的操作保证会很快----元素本身并未交换。
    // // swap 只是交换两个容器的内部数据结构
    // swap(v1,v2);
    // // 比较两个容器实际上就是进行元素的逐对比较
    // // 只有当其元素类型也定义了相应的比较运算符时，我们才可以使用关系运算符来比较两个容器
    // if (v1 >= v2)
    // {
    //     cout << "v1 >= v2" << endl;
    // }
    // else
    // {
    //     cout << "v1 < v2" << endl;
    // }

    // list<int> l1 = {1,2,3,4,5,6,7,8,9,10};
    // list<int> l2 = {10,11,12,13,14,15,16,17,18};

    // swap(l1,l2);

    // if (l1 >= l2)
    // {
    //     cout << "l1 >= l2" << endl;
    // }
    // else
    // {
    //     cout << "l1 < l2" << endl;
    // }

    // for(auto & l : v2){
    //     cout << l << endl;
    // }
    // cout << v1.size() << endl;
    // cout << v1.max_size() << endl;
    
    // 除了 array 外，所以的标准库容器都提供了灵活的内存管理。在运行时可以动态添加或删除元素来改变容器大小

//     vector<string> v11 = {"I", "am", "vector", "container"};
//     v11.push_back("back");
//     for (auto &l : v11)
//     {
//         cout << l << endl;
//     }


//     cout << "---------------------------" << endl;

//     list<string> l11 = {"I","am","list","container"};

//     l11.push_back("back");
//     l11.push_front("front");

//     auto begin = l11.begin();
//     auto end = l11.end();

//     // insert 函数将元素插入到迭代器所指向的位置之前
//     l11.insert(++begin,"insert");
//     l11.insert(end,10,"insert");

//     for (auto &l : l11)
//     {
//         cout << l << endl;
//     }
//     cout << "---------------------------" << endl;

//     // string 是一个字符容器
//     string s11 = "helloworld";
//     s11.push_back('d');
//     for (auto &l : s11)
//     {
//         cout << l << endl;
//     }
//    cout << "---------------------------" << endl;
   
//    deque<string> d11 = {"I", "am", "deque", "container"};

//    d11.push_back("back");
//    d11.push_front("front");

    // vector<string> s12 = {"I", "am", "vector", "container"};
    // // 对一个空容器调用 front 和 back ，就像使用一个越界的下标一样，是一种严重的程序设计错误
    // if (!s12.empty())
    // {
    //     cout << s12.front() << endl;
    //     cout << s12.back() << endl;
    //     s12.front() = "you";
    //     cout << s12.front() << endl;

    // }

    // 下标运算符接受一个下标参数，返回容器中该位置的元素的引用
    // 使用越界的下标是一种严重的程序设计错误，而且编译器不会检查这种错误
//    vector<string> s22;
//    if (!s22.empty())
//    {
//        cout << s22[0] << endl;
//    }

//    s22.push_back("hello");
//    s22.push_back("world");
//    s22.push_back("tell");
//    s22.push_back("me");
//    s22.push_back("a");
//    s22.push_back("joke");

//    s22.pop_back();
//    for (auto &s : s22)
//    {
//        cout << s << endl;
//    }

//    auto begin = s22.begin();
//    s22.erase(begin + 1);
//    for (auto &s : s22)
//    {
//        cout << s << endl;
//    }

//    // 删除 s22 中所有元素
//    s22.clear();
//    s22.erase(s22.begin(), s22.end());
//    s22.resize(100);
//    cout << s22.size() << endl;


// 向容器中添加元素和从容器中删除元素操作可能会使指向容器元素的指针、引用或者迭代器失效
// 一个失效的指针、引用或者迭代器将不再表示任何一个元素
// 使用失效的指针、引用或者迭代器是一种严重的程序设计错误，很可能引起与使用未初始化指针一样的问题
// 必须保证每次改变容器的操作之后都要重新定位迭代器

    // vector<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // auto iter = vi.begin();
    // // 不要保存 end 返回的迭代器
    // while (iter != vi.end())
    // {
    //     if (*iter % 2)
    //     {
    //         // insert 返回指向我们新插入元素的迭代器
    //         iter = vi.insert(iter, *iter);
    //         iter += 2;
    //     }
    //     else
    //     {
    //         // erase 函数返回指向我们删除元素之后元素的迭代器
    //         iter = vi.erase(iter);
    //     }
    // }
    // // 不重新分配内存空间的话，vi 可以存储多少元素 output 10
    // cout << vi.capacity() << endl;
    // vi.resize(88);
    // cout << vi[87] << endl;
    // // 不重新分配内存空间的话，vi 可以存储多少元素 output 88
    // cout << vi.capacity() << endl;
    // cout << vi.capacity() << endl;
    // // vi 中已经保存的元素数量
    // cout << vi.size() << endl;

    // vi.push_back(1);

    // // output 89
    // cout << vi.size() << endl;
    // // output 176
    // // vector 的实现策略似乎是在每次需要分配新内存空间时，将当前容量翻倍
    // cout << vi.capacity() << endl;

    // const char *vi = "Hello, world!";
    // char not_null[] = {'L', 'K'};

    // string ss(vi);

    // string s1(not_null, 2);

    // string s2(not_null);

    // cout << s2 << endl;

    // cout << ss << endl;

    // cout << s1 << endl;

    // cout << ss.substr(0,21) << endl;


    // string str("C++ Primer");
    // // append 总是将新字符追加到原字符串末尾
    // str.append(" 4th Edition");

    // cout << str << endl;


    // string str1("C++ Primer");

    // // 在 pos 位置前插入 " 4Th Edition"
    // str1.insert(str1.size()," 4Th Edition");

    // cout << str1 << endl;

    // str1.replace(0,3,"FUC");

    // cout << str1 << endl;

    // // 从位置5开始，删除两个字符，插入 KILLLLLLL
    // str1.replace(5,2,"KILLLLLLL");
    // cout << str1 << endl;

    // string str2("tony");

    // // assign 总是替换 string 中的所有内容
    // str2.assign("JACK");

    // cout << str2 << endl;

    // string str3("Where have you been? Where did you go fuck you?");

    // auto pos = str3.find("did");
    // cout << pos << endl;

    // cout << str3.substr(pos,3) << endl;

    // auto pos1 = str3.find_first_of("you");

    // cout << pos1 << endl;

    // auto pos2 = str3.find_last_of("you");

    // cout << pos2 << endl;

    // string::size_type pos3 = 0;

    // cout << pos3 << endl;
    
    // // find 操作是由左到右搜索，rfind 是由右到左搜索
    // auto pos4 = str3.find("you");

    // auto pos5 = str3.rfind("you");

    // cout << pos4 << ":   "<< pos5 << endl;


    // string numbers("0123456789"), name("r2d2");
    // string::size_type pos = 0;
    // // s.find_first_of(args) 查找s中任何一个字符第一次出现的位置
    // // s.find(args) 查找 s 中字符串 args 第一次出现的位置
    // while ((pos = name.find_first_of(numbers, pos)) != std::string::npos)
    // {
    //     cout << "found number at index: " << pos << endl;
    //     cout << "element is: " << name[pos] << endl;
    //     ++pos;
    // }

    // int value = 10;

    // // to_string 将整数转换为字符表现形式
    // string name = to_string(value);
    // cout << name << endl;
    // cout << name.size() << endl;


    // 适配器（adaptor）是标准库中的通用概念，能使某种事物的行为看起来像另外一种事物一样
    // 一个容器适配器接受一种已有的容器类型，使其行为看起来像另外一种不同的类型
    // 每个容器适配器都是基于底层容器类型的操作来定义自己的特殊操作
    // stack 底层容器类型为 deque
    stack<int> intStack;
    for(int i = 0; i < 10; ++i){
        intStack.push(i);
    }
    while(!intStack.empty()) 
    {
        // top 返回栈顶元素，但不将元素弹出栈
        int value = intStack.top();
        // 将元素弹出栈
        intStack.pop();
        cout << value << endl;
    }

    // queue 默认基于 deque 实现的
    queue<int> que;
    for (size_t i = 0; i < 10; i++)
    {
       que.push(i);
    }

    while(!que.empty())
    {
        int value = que.front();
        que.pop();
        cout << value << endl;
    }

    // 所以的容器（除 array 外）都提供了高效的动态内存管理，我们可以向容器添加元素，而不必担心元素存储在哪里
    // 容器负责管理自身的存储，很大程度上，容器只是定义了很少的操作。每个容器都定义了构造函数、添加和删除元素的操作、确定容器大小的操作、以及返回指向
    // 特定元素的迭代器的操作，其他的一些如排序和搜索并不是由容器类型定义的，而是由标准库算法实现

    // 当我们使用删除和添加元素的容器操作时，必须注意这些操作可能使指向容器中元素的迭代器、指针或引用失效的操作。如 insert 和 erase 都会返回一个新的
    // 迭代器，来帮助程序员维护容器中的位置。如果循环中使用了改变容器大小的操作，就要尤其小心其中迭代器、指针和引用的使用

    

}