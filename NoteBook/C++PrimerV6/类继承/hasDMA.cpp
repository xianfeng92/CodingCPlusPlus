#include "hasDMA.h"
#include <new>

// baseDMA 复制构造函数将使用 hasDMA 参数的 baseDMA 部分来构造新对象的 baseDMA 部分
hasDMA::hasDMA(const hasDMA& hs):baseDMA(hs)
{
    style = new char[std::strlen(hs.style) + 1];
    std::strcpy(style, hs.style);

}


hasDMA & hasDMA::operator= (const hasDMA& hs)
{
    if(*this == hs)return *this;
    // copy base operator
    baseDMA::operator=(hs);
    delete[] style;
    style = new char[std::strlen(hs.style) + 1];
    std::strcpy(style, hs.style);
    return *this
}

hasDMA::~hasDMA()
{
    delete[] style;
}


