// include 标准库头文件时,用 <>. include 非标准库头文件时用 "";
# include<iostream>
# include "Sales_item.h"

using namespace std;

// main function 为操作系统执行我们所定义程序的调用入口
int main(){

    int result = 333；
    int *p = &result;
    
    int &pp = nullptr;
    pp = &result;

    cout << pp << endl;

    cout << *p << endl;

    Sales_item book;
    cin >> book;
    cout << book << endl;

    Sales_item item1, item2;
    cin >> item1 >> item2;
    cout << item1 + item2 << endl;
    return 0;
}