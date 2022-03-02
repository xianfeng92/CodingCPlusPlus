#include <iostream>
#include <cstring>
#include "stringbad.h"

using std::cout;

// init static class member
int StringBad::num_strings = 0;

//class method
StringBad::StringBad(const char * s)
{
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    ++num_strings;
    cout << num_strings << ": " << str << "object creat";
}

StringBad::StringBad()
{
    len = 4;
    str = new char[len];
    std::strcpy(str,"C++");
    ++num_strings;
    cout << num_strings << ": " << str << "object creat";
}


StringBad::~StringBad()
{
    cout << str << " object destroy";
    --num_strings;
    cout <<num_strings << " left";
    delete[] str;
}


std::ostream & operator<<(std::ostream &os, const StringBad & st)
{
    os << st.str;
    return os;
}

