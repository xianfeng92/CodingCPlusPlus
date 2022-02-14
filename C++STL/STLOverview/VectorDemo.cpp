#include <vector>
#include <algorithm>

#include <iostream>


using std::cout;
using std::endl;
using std::vector;
using std::for_each;

void myPrint(int value)
{
    cout << value << endl;
}

void test1()
{
    // 创建 vector 容器对象，并且通过模板参数指定容器中存放的数据的类型
    vector<int> vec;

    // 向容器中放数据
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);


    //每一个容器都有自己的迭代器, 迭代器是用来遍历容器中的元素
    //v.begin()返回迭代器, 这个迭代器指向容器中第一个数据
    //v.end()返回迭代器, 这个迭代器指向容器元素的最后一个元素的下一个位置
    //vector<int>::iterator 拿到 vector<int> 这种容器的迭代器类型

    vector<int>::iterator pBegin = vec.begin();
    vector<int>::iterator pEnd = vec.end();

    //第一种遍历方式：
    while (pBegin != pEnd)
    {
        cout << *pBegin << endl;
        pBegin++;
    }

    //第二种遍历方式：
    for(auto p = vec.begin(); p != vec.end(); ++p)
    {
        cout << *p << endl;
    }

    // 第三种遍历方式:
    // 使用 STL 提供标准遍历算法---头文件 algorithm
    for_each(vec.begin(), vec.end(),myPrint);
}

int main()
{
  test1();
  return 0;
}