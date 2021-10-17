# include <iostream>
# include <string>
# include "Sales_data.h"
# include <istream>

using namespace std;

Sales_data Sales_data::add(const Sales_data &lhs, const Sales_data &rhs)
{
    // lhs 将数据成员拷贝给 sum
    // 默认情况下，拷贝类的对象其实拷贝的是对象的数据成员
    // 对象在几种情况下会被拷贝：我们初始化变量以及以值的方式传递或返回一个对象
    Sales_data sum = lhs;
    // rhs 数据成员加到 sum 中
    sum.combine(rhs);
    return sum;
}

Sales_data& Sales_data::combine(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

// 在类外部定义成员函数的名字必须包含它所属的类名
// 一旦编译器看到 Sales_data::avg_price() 这个函数名，就能理解剩余的代码是位于类的作用域内
 double Sales_data::avg_price() const
 {
     if (units_sold)
     {
         return revenue / units_sold;
     }
     else
     {
         return 0;
     }
 }

 ostream &Sales_data::print(ostream &os, const Sales_data &item)
 {
     os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
     return os;
 }


 istream &Sales_data::read(istream &is, Sales_data &item)
 {
     double price = 0;
     is >> item.bookNo >> item.units_sold >> price;
     item.revenue = price * item.units_sold;
     return is;
 }
