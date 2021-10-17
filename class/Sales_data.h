#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
#include<iostream>

using namespace std;

// 使用 class 和 struct 定义类唯一的区别就是默认的访问权限
// struct default is public
// class default is private
class Sales_data
{
// 可以被类的成员访问，但是不能被使用该类的代码访问
private:
    unsigned units_sold = 0;
    double revenue = 0.0;
// 在整个程序内可被访问
public:
    // 构造函数的任务是初始化类对象的数据成员，无论何时只要类的对象被创建，就会执行构造函数
    Sales_data(){
        cout << "I am creat" << __FUNCTION__ << endl;
    }
    ~Sales_data(){
        cout << "I am done" << __FUNCTION__ << endl;
    }
    // 很多需要动态内存的类，应该使用 vector 对象或者 string 对象管理必要的存储空间
    // 使用 vector 对象或者 string 的类能够避免分配和释放内存带来的复杂性
    string bookNo;
    Sales_data add(const Sales_data &, const Sales_data &);
    ostream &print(ostream &, const Sales_data &);
    istream &read(istream &, Sales_data &);
    string isbn() const { return this->bookNo; };
    Sales_data &combine(const Sales_data &);
    double avg_price() const;
};

#endif