// !! 类继承

'面向对象编程的主要目的之一是提供可重用的代码'。开发新项目，尤其是当项目十分庞大时, '重用经过测试的代码比重新编写代码要好得多'。使用已有的代码可以节省时间,
由于已有的代码已被使用和测试过, 因此有助于避免在程序中引入错误。另外, 必须考虑的细节越少, 便越能专注于程序的整体策略。

'传统的 C 函数库通过预定义、预编译的函数(如 strlen() 和 rand()，可以在程序中使用这些函数)提供了可重用性'。很多厂商都提供了专用的 C 库，这些专用库提供标
准C 库没有的函数。

C++ 类提供了更高层次的重用性。目前，很多厂商提供了类库，类库由类声明和实现构成。因为'类组合了数据表示和类方法, 因此提供了比函数库更加完整的程序包'。
例如，单个类就可以提供用于管理对话框的全部资源。通常，'类库是以源代码的方式提供的，这意味着可以对其进行修改，以满足需求'。然而，C++ 提供了比修改代码更好的
方法来扩展和修改类。这种方法叫作类继承，它能够从已有的类派生出新的类，而派生类继承了原有类(称为基类)的特征，包括方法。正如继承一笔财产要比自己白手起家容易一
样，通过继承派生出的类通常比设计新类要容易得多。下面是可以通过继承完成的一些工作。

1. 可以在已有类的基础上添加功能。例如，对于数组类，可以添加数学运算

2. 可以给类添加数据。例如，对于字符串类，可以派生出一个类，并添加指定字符串显示颜色的数据成员

3. 可以修改类方法的行为。例如，对于代表提供给飞机乘客的服务的 Passenger 类，可以派生出提供更高级别服务的 FirstClassPassenger 类


当然，可以通过复制原始类代码，并对其进行修改来完成上述工作，但继承机制只需提供新特性，甚至不需要访问源代码就可以派生出类。

'继承是一种非常好的概念，其基本实现非常简单'。但要对继承进行管理，使之在所有情况下都能正常工作，则需要做一些调整。


// !! 一个简单的基类

从一个类派生出另一个类时，原始类称为基类，继承类称为派生类。为说明继承，首先需要一个基类。Webtown 俱乐部决定跟踪乒乓球会会员。作为俱乐部的首席程序员，需要设
计一个简单的 TableTennisPlayer 类。



TableTennisPlayer 类只是记录会员的姓名以及是否有球桌。有两点需要说明:

1. 首先，这个类使用标准 string 类来存储姓名，相比于使用字符数组，更方便、更灵活、更安全

2. 其次，构造函数使用了成员初始化列表语法，但也可以像下面这样做:

TableTennisPlayer::TableTennisPlayer(const string &fn, const string &ln, bool ht)
{
    firstname = fn;
    lastname = ln;
    hastable = ht;
}

这将首先为 firstname 调用 string 的默认构造函数，再调用 string 的赋值运算符将 firstname 设置为 fn，但初始化列表语法可减少一个步骤，它直接使用
string 的复制构造函数将 firstname 初始化为 fn。

#include <iostream>
#include "tabtenn0.h"

int main()
{
    using std::cout;
    TableTennisPlayer player1("Chuck","BLer",true);
    TableTennisPlayer player2("Tara","Boomda",false);
    player1.Name();
    if(player1.HasTable())
    {
        cout << " Has a table\n";
    }
    else
    {
        cout << " Has no table\n";
    }
    player2.Name();
    if(player2.HasTable())
    {
        cout << " Has a table\n";
    }
    else
    {
        cout << " Has no table\n";
    }
    return 0;
}













