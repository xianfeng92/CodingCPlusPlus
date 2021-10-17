#include "Blob.h"
#include<string>
#include<vector>

using namespace std;

// !! 类模版的成员函数的定义

template<typename T>
void Blob<T>::check(size_type t, const std::string& msg) const
{
    if(i > data->size())
    {
        throw std::out_of_range(msg);
    }
}

template<typename T>
T& Blob<T>::back()
{
    check(0,"back om empty blob");
    return data->back();
}


template<typename T>
T& Blob<T>::operator[](size_type i)
{
    check(i, "out of range");
    return (*data)[i];
}


template<typename T>
void Blob<T>::pop_back()
{
    check(0,"pop_back om empty blob");
    data->pop_back();
}


template<typename T>
Blob<T>::Blob():data(std::make_shared<std::vector<T>>){}




template<typename T>
Blob<T>::Blob(std::initializer_list<T> il):data(std::make_shared<std::vector<T>>(il)){}




