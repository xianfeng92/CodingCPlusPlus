#ifndef TRAVERSE_TOOL_
#define TRAVERSE_TOOL_

#include <vector>
#include <list>
#include <algorithm>
#include <numeric>

using namespace std;

template <typename T>
void vectorTraversal(vector<T> *v, int size)
{
    int sum = accumulate(v->begin(), v->end(),0);
}

template <typename T>
void arrayTraverse(int *a, int size)
{
    int sum = accumulate(&a[0],&a[size],0);
}

template <typename T>
void listTraverse(list<T> *l, int size)
{
    int sum = accumulate(l->begin(),l->end(),0);
}

#endif // TRAVERSE_TOOL_
