#include "Sales_data.h"


namespace cplusplus_primer// 重新打开命名空间 cplusplus_primer
{
    // Sales_data 成员及其重载运算符的定义
    // 命名空间中定义的成员可以直接使用名字，此时无需前缀
    std::istream& operator>>(std::istream& in, Sales_data &s){};
}

// 命名空间之外定义的成员必须使用含义前缀的名字
cplusplus_primer::Sales_data
std::istream& cplusplus_primer::operator>>(std::istream& in, Sales_data & s){};


int main(int argc, char* argv[])
{
    using namespace cplusplus_primer::Sales_data;
    Sales_data trans1, trans2;
    // ...
    return 0;
}
