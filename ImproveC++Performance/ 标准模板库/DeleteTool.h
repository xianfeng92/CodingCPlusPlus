#ifndef DELETE_TOOL_
#define DELETE_TOOL_

#include<vector>
#include<list>

using namespace std;

template <typename T>
void vectorDelete(vector<T> *v)
{
    while (!v->empty())
    {
        v->pop_back();
    }
}

template <typename T>
void vectorDeleteFront(vector<T> *v)
{
    while (!v->empty())
    {
        v->erase(v->begin());
    }
}

template <typename T>
void listDelete(list<T> *l)
{
    while (!l->empty())
    {
        l->pop_back();
    }
}

template <typename T>
void listDeleteFront(list<T> *l)
{
    while (!l->empty())
    {
        l->pop_front();
    }
}

#endif // DELETE_TOOL_
