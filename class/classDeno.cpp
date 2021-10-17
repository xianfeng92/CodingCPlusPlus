# include <iostream>
# include <string>
# include "Sales_data.h"

using namespace std;

// // 当我们调用一个成员函数时，用请求该函数的对象地址初始化 this 
// struct Sales_data
// {
//     string isbn() const {return this->bookNo;}
//     Sales_data& combine(const Sales_data&);
//     double avg_price() const;

//     string bookNo;
//     unsigned units_sold = 0;
//     double revenue = 0.0;
// }

// Sales_data add(const Sales_data&, const Sales_data&);
// ostream &print(ostream &,const Sales_data &);
// istream &read(istream &,const Sales_data &);

int main(int argc, char **argv)
{
    // Sales_data data;
    // // p pinter to a const
    // const Sales_data * p;
    // // pp is a  const pointer
    // Sales_data * const pp;
    // // ppp is a const pointer and point to a const
    // const Sales_data * const ppp;
    // // Sales_data::isbn(&data);
    // // 编译器负责把 data 的地址传递给 isbn 隐性形参 this
    // data.isbn();

    Sales_data data;
    data.bookNo = "C++ Primer";
    cout << "Sales_data data is " << data.isbn() << endl;

    return 0;
}