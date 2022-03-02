#ifndef FIND_TOOL_
#define FIND_TOOL_

#include<vector>
#include<list>
#include<set>
#include<algorithm>

void arrayFind(int *a, int *collection, int size)
{
    int const value = collection[size/2];
    int *p = find(&a[0], &a[size], value);
}

void vectorFind(vector<int> *a, int *collection, int size)
{
    int const value = collection[size/2];
    vector<int>::iterator it = find(a->begin(), a->end(), value);
}

void listFind(list<int> *a, int *collection, int size)
{
    int const value = collection[size/2];
    list<int>::iterator it = find(a->begin(), a->end(), value);
}

void multisetFind(multiset<int> *a, int *collection, int size)
{
    int const value = collection[size/2];
    multiset<int>::iterator it = find(a->begin(),a->end(), value);// 通用的 find() 算法
}

void multisetFind2(multiset<int> *a, int *collection, int size)
{
    int const value = collection[size/2];
    auto it = a->find(value);// 使用多重集容器提供的 find() 成员方法，应该会更加高效
}

#endif // FIND_TOOL_
