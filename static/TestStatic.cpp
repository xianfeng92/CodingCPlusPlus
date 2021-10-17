#include <iostream>
#include <string>

using namespace std;

// 有些时候类需要它的一些成员与类本身直接关联，而不是类的一些对象保持关联
// 类是 c++ 语言中最基本的特性，类允许我们为自己的应用定义新类型，从而使程序更加简洁和易于修改~
class TestStatic
{
// 静态数据成员定义在任何函数之外，因此一旦它被定义，就一直存在于程序的整个生命周期中。
public:
    static int m_count;

public:

    // 构造函数的作用是：控制对象的初始化方式
    // 构造函数应该使用构造函数初始值列表来初始化所有成员
    TestStatic() {
      m_count++;
      cout << "I am creating a test" << endl;
      cout<< m_count<<endl;
    }

    ~TestStatic() {
        cout << "I am destroying a test" << endl;
    }

    static int getDemoCount()
    {
        return m_count;
    }
};
