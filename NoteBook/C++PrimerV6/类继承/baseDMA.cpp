#include<new>
#include "baseDMA.h"


baseDMA::baseDMA(const baseDMA & rs)
{
    label = new char[std::strlen(rs.label) + 1];
    std::strcpy(label, rs.label);
    rating = rs.rating;
}

baseDMA &baseDMA::operator=(const baseDMA & rs)
{
    if(*this == rs) return *this;
    delete[] label;
    label = new char[std::strlen(rs.label) + 1];
    std::strcpy(label, rs.label);
    rating = rs.rating;
    return *this;
}


baseDMA::~baseDMA()
{
    delete[] label;
}

