#include <unordered_set>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    std::unordered_multiset<int> coll;

    coll.insert({1,3,2,9,6,10,34});

    for(auto ele : coll)
    {
        cout << ele << endl;
    }

    coll.insert(21);

    for(auto ele : coll)
    {
        cout << ele << endl;
    }

    return 0;
}


'这些元素的顺序是不明确的, 取决于 hash table 的内部布局, 也取决于 hashing 函数'。甚至即使元素先被排序后才被安插,它们在容器内还是有着不
明确的顺序。

如你所见, 这样的次序实在是杂乱无规则可言, 而且在你的平台上执行这个程序可能获得又不一样的次序。就算只添加一个元素, 也可能全盘改变次序。'唯一
保证的是, 内容(value) 相同的元素会相邻'。




