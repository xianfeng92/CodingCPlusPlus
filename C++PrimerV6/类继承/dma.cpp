#include "dma.h"
#include <cstring>


// baseDMA method
baseDMA::baseDMA(const char *l, int r)
{
    label = new char[std::strlen(l) + 1];
    std::strcpy(label, l);
    rating = r;
}

baseDMA::baseDMA(const baseDMA &other)
{
    label = new char[std::strlen(other.label) + 1];
    std::strcpy(label, other.label);
    rating = other.rating;
}

baseDMA::~baseDMA()
{
    delete[] label;
}

baseDMA & baseDMA::operator=(const baseDMA &other)
{
    if(*this == other) return *this;
    delete[] label;
    label = new char[std::strlen(rs.label) + 1];
    std::strcpy(label, rs.label);
    rating = other.rating;
    return *this;
}

std::ostream baseDMA::operator<<(std::ostream &os, const baseDMA &other)
{
    os << other.label << '\n';
    os << other.rating << '\n';
    return os;
}


// lacksDMA methos

lacksDMA::lacksDMA(const char * c, const char * l, int r):baseDMA(l,r)
{
    std::strncpy(color,c,39);
    color[39] = '\0';
}

lacksDMA::lacksDMA(const char * c, const baseDMA * other):baseDMA(other)
{
    std::strncpy(color,c,COL_LEN -1);
    color[COL_LEN -1] = '\0';
}

std::ostream& lacksDMA::operator<<(std::ostream & os, const lacksDMA &ls)
{
    os << (const baseDMA &)ls << '\n';
    os << ls.color << '\n';
    return os;
}


//hasDMA method

hasDMA::hasDMA(const char *s, const char * l, int r):baseDMA(l,r)
{
    style = new char[std::strlen(s) + 1];
    std::strcpy(style,s);
}

hasDMA::hasDMA(const char *s, const baseDMA & rs):baseDMA(rs)
{
    style = new char[std::strlen(hs.style) + 1];
    std::strcpy(style, hs.style);
}

hasDMA::hasDMA(const hasDMA &rs):baseDMA(rs)
{
    style = new char[std::strlen(rs.style) + 1];
    std::strcpy(style, rs.style);
}


hasDMA::~hasDMA()
{
    delete[] style;
}


hasDMA & hasDMA::operator=(const hasDMA & hs)
{
    if(*this == hs) return *this;
    baseDMA::operator=(hs);
    delete[] style;
    style = new char[std::strlen(hs.style) + 1];
    std::strcpy(style, hs.style);
    return *this
}


std::ostream & operator<<(std::ostream &os, const hasDMA & hs)
{
    os << (const baseDMA &)hs << '\n';
    os << hs.style << '\n';
    return os;
}





