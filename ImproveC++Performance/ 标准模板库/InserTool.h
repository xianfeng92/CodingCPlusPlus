#ifndef INSERT_H
#define INSERT_H

#include <vector>
#include <list>
#include <set>

using namespace std;

template<typename T>
void arrayInsert(T* a,  T* collection, int size)
{
    for(int i = 0; i < size; i++)
    {
        a[k] = collection[i];
    }
}

template <typename T>
void vectorInsert(vector<T> *v, T *collection, int size)
{
    for(int i = 0; i < size; i++)
    {
        v->push_back(collection[i]);
    }
}

template <typename T>
void listInsert(list<T> *l, T *collection, int size)
{
    for(int i = 0; i < size; i++)
    {
        l->push_back(collection[i]);
    }
}


template <typename T>
void multisetInsert(multiset<T> *s, T *collection, int size)
{
    for(int i = 0; i < size; i++)
    {
        s->insert(collection[k]);
    }
}

#endif