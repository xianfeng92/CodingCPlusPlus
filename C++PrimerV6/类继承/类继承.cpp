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

注意到该程序实例化对象时将C-风格字符串作为参数:

TableTennisPlayer player1("Chuck","BLer",true);
TableTennisPlayer player2("Tara","Boomda",false);

但构造函数的形参类型被声明为 const string &。这导致类型不匹配，但 string 类有一个将 const char * 作为参数的构造函数，使用C-风格字符串初始化 string
对象时，将自动调用这个构造函数。可将 string 对象或C-风格字符串作为构造函数 TableTennisPlayer 的参数；将前者作为参数时，将调用接受 const string &
作为参数的 string 构造函数，而将后者作为参数时，将调用接受 const char * 作为参数的 string 构造函数。

// !! 派生一个类

Webtown 俱乐部的一些成员曾经参加过当地的乒乓球锦标赛，需要这样一个类，它能包括成员在比赛中的比分。与其从零开始，不如从 TableTennisClass 类派生出一个类。
首先将 RatedPlayer 类声明为从 TableTennisClass 类派生而来:

class RatedPlayer : public TableTennisPlayer
{

}

冒号指出 RatedPlayer 类的基类是 TableTennisplayer 类。'上述特殊的声明头表明 TableTennisPlayer 是一个公有基类，这被称为公有派生'。派生类对象包含基
类对象。'使用公有派生，基类的公有成员将成为派生类的公有成员；基类的私有部分也将成为派生类的一部分，但只能通过基类的公有和保护方法访问'。

上述代码完成了哪些工作呢？ Ratedplayer 对象将具有以下特征：

1. 派生类对象存储了基类的数据成员(派生类继承了基类的实现)

2. 派生类对象可以使用基类的方法(派生类继承了基类的接口)

因此，RatedPlayer 对象可以存储运动员的姓名及其是否有球桌。另外，RatedPlayer 对象还可以使用 TableTennisPlayer 类的 Name()、hasTable() 和 
ResetTable()方法。

需要在继承特性中添加什么呢 ？

1. 派生类需要自己的构造函数

2. 派生类可以根据需要添加额外的数据成员和成员函数

在这个例子中，派生类需要另一个数据成员来存储比分，还应包含检索比分的方法和重置比分的方法。因此，类声明与下面类似:

class RatedPlayer : public TableTennisPlayer
{
    private:
        unsigned int rating;// add a data member
    public:
        RatedPlayer(unsigned int r = 0, const string &fn = "none", const string &ln = "none", bool ht = false);
        RatedPlayer(unsigned int r, const TableTennisPlayer &tp);
        unsigned int rating() const { return rating;}// add a method
        void resetRating(unsigned int r) { rating = r; }// add a method
};


'构造函数必须给新成员(如果有的话)和继承的成员提供数据'。在第一个 RatedPlayer 构造函数中，每个成员对应一个形参；而第二个 Ratedplayer 构造函数使用一个 
TableTennisPlayer 参数，该参数包括 firstname、lastname 和 hasTable。


// !! 构造函数：访问权限的考虑

'派生类不能直接访问基类的私有成员，而必须通过基类方法进行访问'。例如，RatedPlayer 构造函数不能直接设置继承的成员( firstname、lastname 和 hasTable），
而必须使用基类的公有方法来访问私有的基类成员。具体地说, 派生类构造函数必须使用基类构造函数。

'创建派生类对象时，程序首先创建基类对象'。'从概念上说，这意味着基类对象应当在程序进入派生类构造函数之前被创建'。C++ 使用成员初始化列表语法来完成这种工作。
例如，下面是第一个 RatedPlayer 构造函数的代码:

RatedPlayer::RatedPlayer(unsigned int r, const string &fn, const string & ln, bool ht):TableTennisPlayer(fn,ln,ht)
{
    rating = r;
}

其中 TableTennisPlayer(fn,ln,ht) 是成员初始化列表。


如果省略成员初始化列表，情况将如何呢？

RatedPlayer::RatedPlayer(unsigned int r, const string &fn, const string & ln, bool ht)
{
    rating = r;
}

必须首先创建基类对象, 如果不调用基类构造函数，程序将使用默认的基类构造函数，因此上述代码与下面等效:

RatedPlayer::RatedPlayer(unsigned int r, const string &fn, const string & ln, bool ht):TableTennisPlayer()
{
    rating = r;
}

除非要使用默认构造函数，否则应显式调用正确的基类构造函数。


下面来看第二个构造函数的代码：

RatedPlayer::RatedPlayer(unsigned int r, const TableTennisPlayer &tp):TableTennisPlayer(tp)
{
    rating = r;
}

由于 tp 的类型为 TableTennisPlayer &，因此将调用基类的复制构造函数。'基类没有定义复制构造函数，如果需要使用复制构造函数但又没有定义，编译器将自动生成一个'。
在这种情况下，执行成员复制的隐式复制构造函数是合适的, 因为这个类没有使用动态内存分配(string 成员确实使用了动态内存分配，成员复制将使用 string 类的复制构造
函数来复制 string 成员)。

'也可以对派生类成员使用成员初始化列表语法'。在这种情况下，应在列表中使用成员名，而不是类名。所以，第二个构造函数可以按照下述方式编写:

RatedPlayer::RatedPlayer(unsigned int r, const TableTennisPlayer &tp):TableTennisPlayer(tp),rating(r)
{

}


有关派生类构造函数的要点如下:

1. 首先创建基类对象

2. 派生类构造函数应通过成员初始化列表将基类信息传递给基类构造函数

3. 派生类构造函数应初始化派生类新增的数据成员


// !! 使用派生类

要使用派生类，程序必须要能够访问基类声明。tabtenn1.h 将这两种类的声明置于同一个头文件中。也可以将每个类放在独立的头文件中，但由于这两个类是相关的，所以把
其类声明放在一起更合适。

















