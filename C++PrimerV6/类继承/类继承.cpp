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

从一个类派生出另一个类时，原始类称为基类，继承类称为派生类。为说明继承，首先需要一个基类。Webtown 俱乐部决定跟踪乒乓球会会员。作为俱乐部的首席程序员，需
要设计一个简单的 TableTennisPlayer 类。



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

要使用派生类，程序必须要能够访问基类声明。tabtenn1.h 将这两种类的声明置于同一个头文件中。也可以将每个类放在独立的头文件中，但由于这两个类是相关的，
所以把其类声明放在一起更合适。

// !!派生类和基类之间的特殊关系

派生类与基类之间有一些特殊关系。

1. 派生类对象可以使用基类的方法,条件是方法不是私有的:

RatedPlayer rplayer1(1140,"Moly","Duck",true);
rplayer1.Name();

2. '基类指针可以在不进行显式类型转换的情况下指向派生类对象; 基类引用可以在不进行显式类型转换的情况下引用派生类对象'

RatedPlayer rplayer1(1140,"Moly","Duck",true);
TableTennisPlayer  &rt = rplayer1;
TableTennisPlayer *pt = &rplayer1;

rt.Name();
pt->Name();

'基类指针或引用只能用于调用基类方法'，因此，不能使用 rt 或 pt 来调用派生类的 resetRating 方法。

通常，C++ 要求引用和指针类型与赋给的类型匹配，但这一规则对继承来说是例外。然而，这种例外只是单向的，不可以将基类对象和地址赋给派生类引用和指针：

TableTennisPlayer player("Besty","NIO",true);

RatedPlayer &rp = player;// not allowed
RatedPlayer *pt = &player;// not allowed

上述规则是有道理的。例如，如果允许基类引用隐式地引用派生类对象，则可以使用基类引用为派生类对象调用基类的方法。因为派生类继承了基类的方法，所以这样做不会出现问
题。如果可以将基类对象赋给派生类引用，将发生什么情况呢？ '派生类引用能够为基对象调用派生类方法，这样做将出现问题'。例如，将 RatedPlayer::Rating() 方法用
于 TableTennisPlayer 对象是没有意义的，因为 TableTennisPlayer 对象没有 rating 成员。


如果基类引用和指针可以指向派生类对象，将出现一些很有趣的结果。其中之一是基类引用定义的函数或指针参数可用于基类对象或派生类对象。

例如，在下面的函数中：

void show(const TableTennisPlayer &rt)
{
    using std::cout;
    cout << "Name ";
    rt.Name();
    cout << "Table:";
    if(rt.hasTable())
    {
        cout << "has a table\n";
    }
    else
    {
        cout << " has no table\n";
    }
}

形参 rt 是一个基类引用，它可以指向基类对象或派生类对象，所以可以在 Show() 中使用 TableTennisPlayer 参数或 RatedPlayer 参数：

TableTennisPlayer player("Besty","NIO",true);
RatedPlayer rplayer1(1140,"Moly","Duck",true);
show(player);
show(rplayer1);

对于形参为指向基类的指针的函数, 也存在相似的关系。它可以使用基类对象的地址或派生类对象的地址作为实参。


'引用兼容性属性也让您能够将基类对象初始化为派生类对象'，尽管不那么直接。假设有这样的代码:

RatedPlayer rplayer1(1140,"Moly","Duck",true);
TableTennisPlayer player2(rplayer1);

要初始化 player2 ，匹配的构造函数的原型如下:

TableTennisPlayer(const RatedPlayer &rplayer);// doesn't exist'

类定义中没有这样的构造函数，但存在隐式复制构造函数:

// implicit copy constructor
TableTennisPlayer(const TableTennisPlayer &player);

'形参是基类引用，因此它可以引用派生类'。这样，将 player2 初始化为 rplayer1 时，将要使用该构造函数，它复制 firstname、lastname 和 hasTable 成
员。换句话来说，它将 player2 初始化为嵌套在 RatedPlayer 对象 rplayer1 中的 TableTennisPlayer 对象。


同样，也可以将派生对象赋给基类对象：

RatedPlayer rplayer1(1140,"Moly","Duck",true);
TableTennisPlayer player;
player = rplayer1;

在这种情况下，程序将使用隐式重载赋值运算符:

TableTennisPlayer &operator=(const TableTennisPlayer &rp) const;

基类引用指向的也是派生类对象，因此 rplayer1 的基类部分被复制给 player。


// !! 继承：is-a 关系

'派生类和基类之间的特殊关系是基于 C++ 继承的底层模型的'。实际上，C++ 有 3 种继承方式：公有继承、保护继承和私有继承。公有继承是最常用的方式，它建立一
种 is-a 关系，即'派生类对象也是一个基类对象, 可以对基类对象执行的任何操作，也可以对派生类对象执行'。

'因为派生类可以添加特性，所以，将这种关系称为 is-a-kind-of(是一种) 关系可能更准确'，但是通常使用术语 is-a。

'继承可以在基类的基础上添加属性, 但不能删除基类的属性'。在有些情况下，可以设计一个包含共有特征的类，然后以 is-a 或 has-a 关系，在这个类的基础上定义
相关的类。

1. '公有继承不建立 has-a 关系'。例如，午餐可能包括水果，但通常午餐并不是水果。所以，不能通过从 Fruit 类派生出 Lunch 类来在午餐中添加水果。在午餐中加
    入水果的正确方法是将其作为一种 has-a 关系: 午餐有水果。最容易的建模方式是，将 Fruit 对象作为 Lunch 类的数据成员

2. '公有继承不能建立 is-like-a 关系'，也就是说，它不采用明喻。人们通常说律师就像鲨鱼，但律师并不是鲨鱼。

3. '公有继承不建立 is-implemented-as-a（作为……来实现）关系'。例如，可以使用数组来实现栈，但从 Array 类派生出 Stack 类是不合适的，因为栈不是数组

4. '公有继承不建立 uses-a 关系'。例如，计算机可以使用激光打印机，但从 Computer 类派生出 Printer类是没有意义的。。然而，可以使用友元函数或类来处理
    Printer 对象和 Computer 对象之间的通信

'在 C++ 中，完全可以使用公有继承来建立 has-a、is-implemented-as-a 或 uses-a 关系；然而，这样做通常会导致编程方面的问题。因此，还是坚持使用 is-a 关系'。


// !! 多态公有继承

RatedPlayer 继承示例很简单, 派生类对象使用基类的方法，而未做任何修改。然而，可能会遇到这样的情况，即'希望同一个方法在派生类和基类中的行为是不同的'。
换句话来说，方法的行为应取决于调用该方法的对象。'这种较复杂的行为称为多态---具有多种形态，即同一个方法的行为随上下文而异'。

有两种重要的机制可用于实现多态公有继承:

1. 在派生类中重新定义基类的方法

2. 使用虚方法

现在来看另一个例子。由于 Webtown 俱乐部的工作经历，您成了 Pontoon 银行的首席程序员。银行要求您完成的第一项工作是开发两个类。一个类用于表示基本支票账户
— Brass Account，另一个类用于表示代表 Brass Plus 支票账户，它添加了透支保护特性。也就是说，如果用户签出一张超出其存款余额的支票——但是超出的数额并不是很
大，银行将支付这张支票，对超出的部分收取额外的费用，并追加罚款。可以根据要保存的数据以及允许执行的操作来确定这两种账户的特征。

下面是用于 Brass Account 支票账户的信息:

客户姓名；
账号；
当前结余。

下面是可以执行的操作:

创建账户；
存款；
取款；
显示账户信息。

Pontoon 银行希望 Brass Plus 支票账户包含 Brass Account 的所有信息及如下信息:

透支上限；
透支贷款利率；
当前的透支总额。
不需要新增操作，但有两种操作的实现不同;
对于取款操作，必须考虑透支保护；
显示操作必须显示 Brass Plus 账户的其他信息。

// !! 开发 Brass 类和 BrassPlus 类

Brass Account 类的信息很简单，但是银行没有告诉您有关透支系统的细节。当您向友好的 Pontoon 银行代表询问时，他提供了如下信息:

1. Brass Plus 账户限制了客户的透支款额。默认为 500 元，但有些客户的限额可能不同

2. 银行可以修改客户的透支限额

3. Brass Plus 账户对贷款收取利息。默认为 11.125%，但有些客户的利率可能不同

4. 银行可以修改客户的利率

5. 账户记录客户所欠银行的金额(透支数额加利息)。用户不能通过常规存款或从其他账户转账的方式偿付，而必须以现金的方式交给特定的银行工作人员。如果有必要，
   工作人员可以找到该客户。欠款偿还后，欠款金额将归零。最后一种特性是银行出于做生意的考虑而采用的，这种方法有它有利的一面——使编程更简单。

上述列表表明，新的类需要构造函数，而且构造函数应提供账户信息，设置透支上限（默认为500元）和利率（默认为11.125%）。另外，还应有重新设置透支限额、利率和
当前欠款的方法。要添加到 Brass 类中的就是这些，这将在 BrassPlus 类声明中声明。有关这两个类的信息声明，类声明应类似于 brass.h。


#ifndef E0360DBD_DD97_4EE2_9D11_7AB406B2FFA6
#define E0360DBD_DD97_4EE2_9D11_7AB406B2FFA6

#include<string>

class Brass
{
private:
    std::string fullName;
    long acctNum;
    double balance;
public:
    Brass(const std::string &s = "NullBody", long an = -1, double bal = 0.0);
    void Deposit(double amt);
    virtual void withDraw(double amt);
    double Balance() const {return balance;}
    virtual void ViewAcct() const;
    virtual ~Brass() {};
};

class BrassPlus : public Brass
{
private:
    double maxLoan;
    double rate;
    double ownsBank;
public:
    BrassPlus(const std::string &s = "NullBody", double an = -1, double bal = 0.0, double ml = 500, double r = 0.11125);
    BrassPlus(const Brass &ba, double ml = 500, double r = 0.11125);
    virtual void ViewAcct() const;
    virtual void withDraw(double amt);
    void ResetMax(double m){ maxLoan = m;}
    void ResetRate(double m){ rate = m;}
    void resetOwns() { ownsBank = 0;}
};

#endif /* E0360DBD_DD97_4EE2_9D11_7AB406B2FFA6 */

需要说明的有下面几点:

1. BrassPlus 类在 Brass 类的基础上添加了 3 个私有数据成员和 3 个公有成员函数

2. Brass 类和 BrassPlus 类都声明了 ViewAcct() 和 Withdraw() 方法，但 BrassPlus 对象和 Brass 对象的这些方法的行为是不同的

3. Brass 类在声明 ViewAcct() 和 Withdraw() 时使用了新关键字 virtual。这些方法被称为虚方法(virtual method)

4. Brass 类还声明了一个虚析构函数，虽然该析构函数不执行任何操作


第一点没有什么新鲜的。RatedPlayer 类在 TableTennisPlayer 类的基础上添加新数据成员和 2 个新方法的方式与此类似。第二点介绍了声明如何指出方法在派生类的
行为的不同。两个 ViewAcct() 原型表明将有 2 个独立的方法定义。基类版本的限定名为 Brass::ViewAcct()，派生类版本的限定名为 BrassPlus::ViewAcct()。
程序将使用对象类型来确定使用哪个版本:

Brass dom("hell0", 11224, 4182.45);
BrassPlus dot("NIO", 12118, 2590.32);

dom.ViewAcct();// using Brass::ViewAcct()
dot.ViewAcct();// using BrassPlus::ViewAcct()

同样，Withdraw() 也有 2 个版本，一个供 Brass 对象使用，另一个供 BrassPlus 对象使用。对于在两个类中行为相同的方法（如Deposit( )和Balance( )），则
只在基类中声明。

第三点(使用 virtual)比前两点要复杂。'如果方法是通过引用或指针而不是对象调用的，它将确定使用哪一种方法'。'如果没有使用关键字 virtual，程序将根据引用类型
或指针类型选择方法'。'如果使用了 virtual，程序将根据引用或指针指向的对象的类型来选择方法'。

如果 ViewAcct() 不是虚的，则程序的行为如下:

Brass dom("hell0", 11224, 4182.45);
BrassPlus dot("NIO", 12118, 2590.32);

Brass &b1_ref = dom;
Brass &b2_ref = dot;

b1_ref.ViewAcct();// using Brass::ViewAcct()
b2_ref.ViewAcct();// using Brass::ViewAcct()

引用变量的类型为 Brass，所以选择了 Brass::ViewAccount()。

如果 ViewAcct() 是虚的，则行为如下：

Brass dom("hell0", 11224, 4182.45);
BrassPlus dot("NIO", 12118, 2590.32);

Brass &b1_ref = dom;
Brass &b2_ref = dot;

b1_ref.ViewAcct();// using Brass::ViewAcct()
b2_ref.ViewAcct();// using BrassPlus::ViewAcct()

这里两个引用的类型都是 Brass，但 b2_ref 引用的是一个 BrassPlus 对象，所以使用的是 BrassPlus::ViewAcct()。


因此，'经常在基类中将派生类会重新定义的方法声明为虚方法'。方法在基类中被声明为虚的后，它在派生类中将自动成为虚方法。然而，在派生类声明中使用关键字 virtual 
来指出哪些函数是虚函数也不失为一个好办法。

第四点是, 基类声明了一个虚析构函数。这样做是为了确保释放派生对象时, 按正确的顺序调用析构函数。


注意:

'如果要在派生类中重新定义基类的方法，通常应将基类方法声明为虚的'。'这样，程序将根据对象类型而不是引用或指针的类型来选择方法版本'。为基类声明一个虚析构函数
也是一种惯例。


// !! 类实现

接下来需要实现类，其中的部分工作已由 brass.h 中的内联函数定义完成了。brass.cpp 列出了其他方法的定义。'注意，关键字 virtual 只用于类声明的方法原型中，
而没有用于 brass.cpp 的方法定义中'。



介绍 brass.cpp 的具体细节(如一些方法的格式化处理)之前, 先来看一下与继承直接相关的方面。

'记住，派生类并不能直接访问基类的私有数据，而必须使用基类的公有方法才能访问这些数据'。访问的方式取决于方法。构造函数使用一种技术，而其他成员函数使用另一
种技术。

'派生类构造函数在初始化基类私有数据时, 采用的是成员初始化列表语法'。RatedPlayer 类构造函数和 BrassPlus 构造函数都使用这种技术：

// BrassPlus Method
BrassPlus::BrassPlus(const string& s, long an, double bal, double ml, double r):Brass(s,an,bal)
{
    maxLoan = ml;
    ownsBank = 0.0;
    rate = r;
}

使用成员初始化列表语法, 将基类信息传递给基类构造函数，然后使用构造函数体初始化 BrassPlus 类新增的数据项。

非构造函数不能使用成员初始化列表语法, 但'派生类方法可以调用公有的基类方法'。

// redefine how ViewAcct works
void BrassPlus::ViewAcct() const
{
    // set up ###.## format
    format initialState = setFormat();
    precis prec = cout.precision(2);

    // 使用作用域解析运算符来调用基类方法
    Brass::ViewAcct();
    cout << " Maximim loan: $" << maxLoan << endl;
    cout << "Own to back $: " << ownsBank << endl;
    cout.precision(3);// ###.### format
    cout << " Loan Rate: " << 100 * rate << "%\n";
    restore(initialState, prec);
}

换句话说， BrassPlus::ViewAcct() 显示新增的 BrassPlus 数据成员，并调用基类方法 Brass::ViewAcct() 来显示基类数据成员。'在派生类方法中，标准技术
是使用作用域解析运算符来调用基类方法'。

方法 ViewAcct() 和 Withdraw() 使用格式化方法 setf() 和 precision() 将浮点值的输出模式设置为定点，即包含两位小数。设置模式后，输出的模式将保持不变
，因此该方法将格式模式重置为调用前的状态。


// !!使用 Brass 和 BrassPlus 类

#include<iostream>
#include "brass.h"

using std::cout;
using std::endl;

int main()
{
    Brass piggy("nio", 234, 32.21);
    BrassPlus hoggy("XF", 122442, 32.21);

    piggy.ViewAcct();
    cout << endl;

    hoggy.ViewAcct();
    cout << endl;

    cout << "Deposit $1000 into the hoggy Account:\n";
    hoggy.Deposit(1000);
    cout << "new Balance :$ " << hoggy.Balance() << endl;

    cout << " Withdraw $4200 from the piggy Account:\n";
    piggy.Withdraw(4200.00);
    cout << "piggy Account balance :$ " << piggy.Balance() << endl;
    cout << "withdraw $4200 from the hoggy Account:\n";
    hoggy.Withdraw(4200);
    hoggy.ViewAcct();

    return 0;
}

// !! 演示虚方法的行为

在 usebrass1.cpp 中，方法是'通过对象(而不是指针或引用)调用的，没有使用虚方法特性'。

下面来看一个使用了虚方法的例子。假设要同时管理 Brass 和 BrassPlus 账户，如果能使用同一个数组来保存 Brass 和 BrassPlus 对象，将很有帮助，但这是不可能的。
数组中所有元素的类型必须相同，而 Brass 和 BrassPlus 是不同的类型。然而，可以创建指向 Brass 的指针数组。这样，每个元素的类型都相同，但由于使用的是公有继承
模型，因此 Brass 指针既可以指向 Brass 对象，也可以指向 BrassPlus 对象。'因此，可以使用一个数组来表示多种类型的对象, 这就是多态性'。


// !! 为何需要虚析构函数

在 usebrass2.cpp 中，'使用 delete 释放由 new 分配的对象的代码说明了为何基类应包含一个虚析构函数'，虽然有时好像并不需要析构函数。如果析构函数不是
虚的，则将只调用对应于指针类型的析构函数。'如果析构函数是虚的，将调用相应对象类型的析构函数'。

// !! 静态联编和动态联编

'程序调用函数时，将使用哪个可执行代码块呢'？

编译器负责回答这个问题。将源代码中的函数调用'解释为'执行特定的函数代码块被称为'函数名联编(binding)'。在 C 语言中，这非常简单，因为每个函数名都对应一个不同
的函数。'在 C++ 中，由于函数重载的缘故，这项任务更复杂。编译器必须查看函数参数以及函数名才能确定使用哪个函数'。然而，C/C++ 编译器可以在编译过程完成这种联编。
'在编译过程中进行联编(binding)被称为静态联编(static binding)'，又称为早期联编(early binding)。然而，虚函数使这项工作变得更困难。使用哪一个函数是不能在
编译时确定的，因为编译器不知道用户将选择哪种类型的对象。

所以，'编译器必须生成能够在程序运行时选择正确的虚方法的代码'，这被称为动态联编(dynamic binding)，又称为晚期联编(late binding)。


// !! 指针和引用类型的兼容性

'在 C++ 中，动态联编与通过指针和引用调用方法相关'，从某种程度上说，这是由继承控制的。公有继承建立 is-a 关系的一种方法是如何处理指向对象的指针和引用。通常，
C++ 不允许将一种类型的地址赋给另一种类型的指针，也不允许一种类型的引用指向另一种类型:

double x = 2.5;
int *pi = &x;// invalid assignment
long &rl = x;// invalid assignment

然而，正如您看到的，'指向基类的引用或指针可以引用派生类对象，而不必进行显式类型转换'。例如，下面的初始化是允许的:

BrassPlus dilly("nio",23333,233.31);
Brass *p = &dilly;// ok
Brass &rp = dilly;// okay

'将派生类引用或指针转换为基类引用或指针被称为向上强制转换(upcasting)'，这使公有继承不需要进行显式类型转换。该规则是 is-a 关系的一部分。BrassPlus 
对象都是 Brass 对象，因为它继承了 Brass 对象所有的数据成员和成员函数。'所以，可以对 Brass 对象执行的任何操作，都适用于 BrassPlus 对象'。因此，
为处理 Brass 引用而设计的函数可以对 BrassPlus 对象执行同样的操作，而不必担心会导致任何问题。将指向对象的指针作为函数参数时，也是如此。向上强制转换是可传
递的，也就是说，如果从 BrassPlus 派生出 BrassPlusPlus 类，则 Brass 指针或引用可以引用 Brass 对象、BrassPlus 对象或 BrassPlusPlus 对象。

相反的过程——'将基类指针或引用转换为派生类指针或引用——称为向下强制转换(downcasting)'。如果不使用显式类型转换，则向下强制转换是不允许的。
原因是 is-a 关系通常是不可逆的。

对于使用基类引用或指针作为参数的函数调用, 将进行向上转换(upcasting)。

请看下面的代码段，这里假定每个函数都调用虚方法 ViewAcct()：

void fr(Brass &rb);// using rb.ViewAcct()
void fp(Brass *pb);// using fp->ViewAcct()
void fv(Brass b);// using fv.ViewAcct()

int main()
{
    Brass b("Hello", 1111,321.21);
    BrassPlus bp("NIO",2332,322.34);
    fr(b);// using Brass::ViewAcct()
    fr(bp);// using BrassPlus::ViewAcct()

    fp(b);// using Brass::ViewAcct()
    fp(bp);// using BrassPlus::ViewAcct()

    fv(b);// using Brass::ViewAcct()
    fv(bp);// using Brass::ViewAcct()
}

按值传递导致只将 BrassPlus 对象的 Brass 部分传递给函数 fv()。但随引用和指针发生的隐式向上转换导致函数 fr() 和 fp() 分别为 Brass 对象和 BrassPlus 
对象使用 Brass::ViewAcct() 和 BrassPlus::ViewAcct()。

隐式向上强制转换使基类指针或引用可以指向基类对象或派生类对象，因此需要动态联编。C++ 使用虚成员函数来满足这种需求。


// !! 虚成员函数和动态联编

来回顾一下使用引用或指针调用方法的过程。请看下面的代码:

BrassPlus nio("hello",122,32.32);
Brass *pb;
pb = &nio;
bp->ViewAcct();

1. 如果在基类中没有将 ViewAcct() 声明为虚的，则 bp->ViewAcct() 将根据指针类型(Brass *) 调用 Brass::ViewAcct(), '指针类型在编译时已知'，因此编译器
   在编译时，可以将 ViewAcct() 关联到 Brass::ViewAcct() 。'总之，编译器对非虚方法使用静态联编'。

2. 然而，如果在基类中将 ViewAcct() 声明为虚的，则 bp->ViewAcct() 根据对象类型(BrassPlus) 调用 BrassPlus::ViewAcct()。在这个例子中，对象类型为 
   BrassPlus，但通常只有在运行程序时才能确定对象的类型。所以编译器生成的代码将在程序执行时，根据对象类型将 ViewAcct() 关联到 Brass::ViewAcct() 或 
   BrassPlus::ViewAcct()。总之，编译器对虚方法使用动态联编。

在大多数情况下，动态联编很好，因为它让程序能够选择为特定类型设计的方法。因此，您可能会问:

1. 为什么有两种类型的联编？

2. 既然动态联编如此之好，为什么不将它设置成默认的？

3. 动态联编是如何工作的？


// !! 为什么有两种类型的联编以及为什么默认为静态联编

如果动态联编让您能够重新定义类方法，而静态联编在这方面很差，为何不摒弃静态联编呢？ 原因有两个--- '效率和概念模型'。

1. 首先来看效率。为使程序能够在运行阶段进行决策，必须采取一些方法来跟踪基类指针或引用指向的对象类型，这增加了额外的处理开销。例如，如果类不会用作基类，
   则不需要动态联编。同样，如果派生类不重新定义基类的任何方法，也不需要使用动态联编。在这些情况下，使用静态联编更合理，效率也更高。'由于静态联编的效率更高，
   因此被设置为 C++ 的默认选择'。Strousstrup 说，C++ 的指导原则之一是，'不要为不使用的特性付出代价(内存或者处理时间)'。仅当程序设计确实需要虚函数时，
   才使用它们。

2. 接下来看概念模型。'在设计类时，可能包含一些不在派生类重新定义的成员函数'。例如，Brass::Balance() 函数返回账户结余，不应该重新定义。不将该函数设置为虚
   函数，有两方面的好处：首先效率更高; 其次, 指出不要重新定义该函数。'这表明，仅将那些预期将被重新定义的方法声明为虚的'。

'当然，设计类时，方法属于哪种情况有时并不那么明显。与现实世界中的很多方面一样，类设计并不是一个线性过程'。


// !! 虚函数的工作原理

'C++ 规定了虚函数的行为，但将实现方法留给了编译器作者'。

不需要知道实现方法就可以使用虚函数，但了解虚函数的工作原理有助于更好地理解概念，因此，这里对其进行介绍。

通常，编译器处理虚函数的方法是: 给每个对象添加一个隐藏成员, 隐藏成员中保存了一个指向函数地址数组的指针。这种数组称为虚函数表(virtual function table，vtbl)
。虚函数表中存储了为类对象进行声明的虚函数的地址。例如，'基类对象包含一个指针, 该指针指向基类中所有虚函数的地址表'。'如果派生类提供了虚函数的新定义，该虚函数表
将保存新函数的地址'; 如果派生类没有重新定义虚函数，该 vtbl 将保存函数原始版本的地址。

如果派生类定义了新的虚函数，则该函数的地址也将被添加到 vtbl 中。

注意，无论类中包含的虚函数是 1 个还是 10 个，都只需要在对象中添加 1 个地址成员，只是表的大小不同而已。

调用虚函数时，程序将查看存储在对象中的 vtbl 地址，然后转向相应的函数地址表。'如果使用类声明中定义的第一个虚函数, 则程序将使用数组中的第一个函数地址，并执行
具有该地址的函数'。如果使用类声明中的第三个虚函数, 程序将使用地址为数组中第三个元素的函数。

总之，使用虚函数时，在内存和执行速度方面有一定的成本，包括:

1. 每个对象都将增大，增大量为存储地址的空间

2. 对于每个类，编译器都创建一个虚函数地址表(数组)

3. 对于每个函数调用，都需要执行一项额外的操作，即到表中查找地址


'虽然非虚函数的效率比虚函数稍高，但不具备动态联编功能'


// !! 有关虚函数注意事项

我们已经讨论了虚函数的一些要点:

1. 在基类方法的声明中使用关键字 virtual 可使该方法在基类以及所有的派生类中是虚的

2. 如果使用指向对象的引用或指针来调用虚方法，程序将使用为对象类型定义的方法，而不使用为引用或指针类型定义的方法。这称为动态联编。这种行为非常重要，因为这样
   基类指针或引用可以指向派生类对象

3. 如果定义的类将被用作基类，则应将那些要在派生类中重新定义的类方法声明为虚的

对于虚方法，还需要了解其他一些知识，其中有的已经介绍过。下面来看看这些内容。


// !! 1. 构造函数

构造函数不能是虚函数。创建派生类对象时，将调用派生类的构造函数，而不是基类的构造函数，然后，派生类的构造函数将使用基类的一个构造函数，这种顺序不同于继承
机制。因此，派生类不继承基类的构造函数，所以将类构造函数声明为虚的没什么意义。


// !! 2. 析构函数

'析构函数应当是虚函数，除非类不用做基类'。例如，假设 Employee 是基类，Singer 是派生类，并添加一个 char * 成员，该成员指向由 new 分配的内存。当 Singer 
对象过期时，必须调用 ~Singer() 析构函数来释放内存。


请看下面的代码：

Employee *pe = new Singer;
...
delete pe;

如果使用默认的静态联编，delete 语句将调用 ~Employee() 析构函数。这将释放由 Singer 对象中的 Employee 部分指向的内存，但不会释放新的类成员指向的内
存。但如果析构函数是虚的，则上述代码将先调用 ~Singer 析构函数释放由 Singer 组件指向的内存，然后，调用 ～Employee() 析构函数来释放由 Employee 组件指向
的内存。

这意味着，即使基类不需要显式析构函数提供服务, 也不应依赖于默认构造函数，而应提供虚析构函数，即使它不执行任何操作:

virtual ~BaseClass();

顺便说一句，'给类定义一个虚析构函数并非错误, 即使这个类不用做基类, 这只是一个效率方面的问题'。


// !! 3. 友元

'友元不能是虚函数，因为友元不是类成员，而只有成员才能是虚函数'。如果由于这个原因引起了设计问题，可以通过让友元函数使用虚成员函数来解决。


// !! 4.没有重新定义

如果派生类没有重新定义函数，将使用该函数的基类版本。

// !!5. 重新定义将隐藏方法

假设创建了如下所示的代码：

class Dwelling
{
public:
    virtual void showperks(int a) const;
    ...
};

class Hotel : public Dwelling
{
public:
    virtual void showperks() const;
    ...
};

这将导致问题，可能会出现编译器警告, 也可能不会出现警告。但不管结果怎样，代码将具有如下含义:

Hotel trump;
trump.showperks();// valid
trump.showperks(5);// invalid


新定义将 showperks() 定义为一个不接受任何参数的函数。重新定义不会生成函数的两个重载版本，而是隐藏了接受一个 int 参数的基类版本。

'总之，重新定义继承的方法并不是重载'。如果在派生类中重新定义函数，将不是使用相同的函数特征标覆盖基类声明，而是隐藏同名的基类方法，不管参数特征标如何。

这引出了两条经验规则：

1. 如果重新定义继承的方法，应确保与原来的原型完全相同，但如果返回类型是基类引用或指针，则可以修改为指向派生类的引用或指针。

class Dwelling
{
private:
    virtual Dwelling & build(int n);
    ...
};

class Hotel : public Dwelling
{
private:
    virtual Hotel & build(int n);
};

注意，这种例外只适用于返回值，而不适用于参数。


2. 如果基类声明被重载了, 则应在派生类中重新定义所有的基类版本。

class Dwelling
{
public:
    virtual void showperks() const;
    virtual void showperks(double x);
    virtual void showperks(int n) const;
    ...
};


class Hotel : public Dwelling
{
public:
    virtual void showperks() const;
    virtual void showperks(double x);
    virtual void showperks(int n) const;
    ...
};


'如果只重新定义一个版本，则另外两个版本将被隐藏，派生类对象将无法使用它们'。注意，如果不需要修改，则新定义可只调用基类版本:

void Hotel::showperks() const
{
    Dwelling::showperks();
}


// !! 访问控制：protected

关键字 protected 与 private 相似，'在类外只能用公有类成员来访问 protected 部分中的类成员'。private 和 protected 之间的区别只有在基类派生的类中才会
表现出来。派生类的成员可以直接访问基类的保护成员, 但不能直接访问基类的私有成员。因此，对于外部世界来说，保护成员的行为与私有成员相似; 
但对于派生类来说，保护成员的行为与公有成员相似。

// !!抽象基类

总之，在原型中使用 =0 指出类是一个抽象基类，在类中可以不定义该函数。

void Move(int x, int y) = 0;

总之，'ABC(abstract base class)描述的是至少使用一个纯虚函数的接口，从 ABC 派生出的类将根据派生类的具体特征, 使用常规虚函数来实现这种接口'。

您可能希望看到一个完整的 ABC 示例，因此这里将这一概念用于 Brass 和 BrassPlus 账户，首先定义一个名为 AcctABC 的 ABC。'这个类包含 Brass 和 BrassPlus 
类共有的所有方法和数据成员'，'那些在 BrassPlus 类和 Brass 类中的行为不同的方法应被声明为虚函数'。至少应有一个虚函数是纯虚函数，这样才能使 AcctABC 成为抽
象类。






