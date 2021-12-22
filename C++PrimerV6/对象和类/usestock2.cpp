#include<iostream>
#include "stock10.h"

int main()
{
    using std::cout;
    cout << "Using constructor to create new object\n";
    Stock stock1("Nio",2111,12.32);
    stock1.show();
    Stock stock2 = Stock("NIO",21,23.32);
    stock2.show();

    cout << "Assigning stock1 to stock2\n";
    // 与给结构赋值一样，在默认情况下，给类对象赋值时，将把一个对象的成员复制给另一个
    stock2 = stock1;

    cout << "Listing stock1 and stock2\n";
    stock1.show();
    stock2.show();

    cout << "Using a constructor to reset a object\n";
    // 构造函数不仅仅可用于初始化新对象
    // stock1 对象已经存在，因此这条语句不是对 stock1 进行初始化，而是将新值赋给它
    // 这是通过让构造程序创建一个新的、临时的对象，然后将其内容复制给 stock1 来实现的
    // 随后程序调用析构函数，以删除该临时对象
    stock1 = Stock("XV",21,21.23);// temp object
    cout << "Revised stock1\n";
    stock1.show();
    cout << "Done\n";
    return 0;
}
