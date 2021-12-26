#include <cstring>
#include "string1.h"

using std::cin;
using std::cout;

int String::num_strings = 0;

// static method
int String::HowMany() const
{
    return num_strings;
}

// class method
String::String(const char * s)
{
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    ++num_strings;
}

String::String()
{
    len = 4;
    str = new char[len + 1];
    std::strcpy(str,"C++");
    ++num_strings;
}


String::String(const String &st)
{
    ++num_strings;
    len = st.len;
    str = new char[len + 1];
    std::strcpy(str,st.str);
}

String::~String()
{
    --num_strings;
    delete[] str;
}


String & String::operator=(const String &st)
{
    if(*this == st)
    {
        return *this;
    }
    delete[] str;
    len = st.len;
    str = new char[len + 1];
    std::strcpy(str,st.str);
    return *this;
}

String & String::operator=(const char * s)
{
    delete[] str;
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str,s);
    return *this;
}


char & String::operator[](int i)
{
    return str[i];
}


const char & String::operator[](int i) const
{
    return str[i];
}


bool operator<(const String &st1, const String &st2)
{
    return (std::strcmp(st1.str,st2.str) < 0);
}


bool operator>(const String &st1, const String &st2)
{
    return (st2 < st1);
}


bool operator==(const String & st1, const String &st2)
{
    return (std::strcmp(st1.str,st2.str) == 0);
}


ostream & ostream::operator<<(ostream & os, const String & st)
{
    os << st.str;
    return os;
}

// 重载 >> 运算符提供了一种将键盘输入行读入到 String 对象中的简单方法。它假定输入的字符数不多于String::CINLIM的字符数，并丢弃多余的字符。
istream & ostream::operator>>(istream &is, String & st)
{
    char temp[String::CINLIM];
    is.getline(temp, String::CINLIM);
    if(is)
    {
        st = temp;
    }
    while(is && is.get() != '\n')
    {
        continue;
    }
    return is;
}














