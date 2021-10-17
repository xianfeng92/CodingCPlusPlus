#include<iostream>
#include<string>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>


using namespace std;


int main(int argc, char **argv)
{
    // 关联容器支持高效的关键字查找和访问，两个主要的关联容器类型是：map 和 set
    // map 中的元素是一些关键字-值（key-value）对：关键字起到索引的作用，值则表示与索引向关联的数据
    // set 中 每个元素只包含一个关键字，set 支持高效的关键字查询操作---检查一个关键字是否在 set 中
    // 1. 允许重复关键字的容器的名字都包含 multi；2. 不保持关键字按顺序存储的容器名字都以单词 unordered 开头,无序容器使用 hash 函数来组织元素
    // 按关键字有序保存元素： 1. map ---关联数组，保存关键字和值； 2. set 关键字即值，只保存关键字的容器。 3. multimap -- 关键字可重复出现的 map
    // 无序集合： 1. unordered_map 用哈希函数组织的 map； 2. unordered_set 用哈希函数组织的 set 3. unordered_multi_map 用哈希函数组织的map，关键字可以重复

    // set 就是关键字的简单集合，当想要知道一个值是否存在时，set 是最有用的。

    map<string,size_t> word_count; // string 到 size_t 的空map
    set<string> excluded_words = {"fuck","bad","hate"}; // 使用 set 保存想要忽略的单词
    string word;
    while(cin >> word)
    {
        if (excluded_words.find(word) == excluded_words.end())
        {
            ++word_count[word]; // 提取 word 计数器，并将其加一
            if (word == "q")
            {
                break;
            }
        }
    }
    for(const auto &it : word_count)
    {
         // 从 map 中提取元素会得到一个 pair 类型的对象，pair 是一个模板类型，保存两个名为 first 和 second 的（公有）数据成员
         // first 成员保存关键字，second 成员保存对应的值
        cout << it.first << " occurs " << it.second << ((it.second > 1) ? "times":"time") << endl;
    }

    // 关联容器的迭代器都是双向的
    // 定义关联容器
    map<string,size_t> word_count1;// 空容器
    set<string> excluded_words1 = {"fuck"};// 列表初始化
    map<string,string> authors = {{"Kobe","24"},{"jordan","23"},{"LBJ",“6”}}；

    // 关联容器迭代器
    map<string,string> word_count2 = {{"Kobe","24"},{"jordan","23"},{"LBJ",“6”}}；
    auto map_it = word_count2.begin();
    cout << map_it->first << endl;
    cout << map_it ->second << endl;

    // set 的迭代器是 const 的
    // 遍历关联容器
    while(map_it != word_count2.cend())
    {
        cout << map_it->first << endl;
        ++map_it;// 递增迭代器，移动到下一个元素
    }

    // 添加元素
    // 向 set 中添加元素
    vector<int> ivec = {1,2,3,4,2,3,4,5,6};
    set<int> set2;
    set2.insert(ivec.begin(),ivec.end());
    set2.insert({1,2,3,4,44,444,444,222});

    // 向 map 中添加元素
     map<string,string> word_count3；
     word_count3.insert({"Tell","HELE"});
     word_count3.insert(make_pair("word","222"));
     word_count3.insert(pair<string,string>("word","wwwww"));


     // 使用 insert 重写单词计数器
     map<string,int> word_count4;
     string word4;
     while(cin >> word4)
     {
         // ret 是 insert 的返回值，是一个 pair 类型
         // ret.first 是 pair 的第一个成员，是一个 map 迭代器，指向具有给定关键字的元素
         // ret.first -> 解引用此迭代器，提取 map 中的元素，元素也是一个 make_pair
         // (ret.first)->second map 中元素部分的值（value）
         auto ret = word_count4.insert(word4,1);
         if(!ret->second)
         {
             ++ ((ret.first)->second);
         }
     }

     // 删除元素
         map<string,string> word_count5 = {{"Kobe","24"},{"jordan","23"},{"LBJ",“6”}}；
         auto result = word_count3.erase("LBJ");

         // map 的下标操作：map 和 unordered_map 容器提供下标运算符和一个对应的 at 函数
         // 使用一个不在容器中的关键字作为下标，会添加一个具有此关键字的元素到 map 中
         map<string,string> word_count6；
         // 创建一个关键字为 tony 的元素，关联值进行值初始化；然后将 10 赋予它
         word_count6["tony"] = 10;

         // 访问元素---关联容器提供了多种查找一个指定元素的方法
         set<int> iset21 = {1,2,3,444,5,6,7,8,9,0};
         iset21.find(1);// 返回一个迭代器，指向key == 1 的元素
         iset21.find(999); // 返回一个迭代器，其值等于 iset21.end();
         iset21.count(999);// 返回 0
         iset21.count(1);// 返回 1


         // 在 multimap 或 multiset 中查找元素
         // 如果一个 multimap 或 multiset 有多个元素具有相同的关键字，则这些元素在容器中会相邻存储
         





}