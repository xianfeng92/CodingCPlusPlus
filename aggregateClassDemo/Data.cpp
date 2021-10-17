# include <string>

using namespace std;

// 聚合类使得用户可以直接访问其成员，并且具有特殊的初始化语法形式
struct Data{
    int value;
    string s;
}


int main()
{
    Data data = {1111,"xforg"};
}