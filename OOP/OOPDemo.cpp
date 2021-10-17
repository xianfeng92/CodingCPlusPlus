#include <string>
#include <vector>


using namespace std;


int main(int argc, char **argv)
{
    // 继承与静态成员

    // 如果基类中定义了一个静态成员，则在整个继承体系中只存在该成员的唯一定义
    class Base
    {
        static void statMem();
    };

    class Derived : public Base
    {
        void f(const Derived &)
        {
            Base::statMem();// 正确；Base 定义了 statMem
            Derived::statMem();正确；Derived 继承了 statMem
            derived_obj.statMem();// 正确；派生类的对象能访问基类的成员
            statMem();// 正确；通过 this 对象访问
        }
    }

    // 派生类的声明
    // !! 一条声明语句的作用是令程序知晓某个名字的存在以及该名字表示一个什么样的实体
    // 派生类的声明中只包含类名，不包含派生列表
    class Bulk_Quote: public Quote;// 错误；派生列表不能出现在这这里
    class Bulk_Quote;// 正确；声明派生类的正确方式

    // 被用作基类的类----如果我们要将某个类用做基类，该类需要已经定义，而非仅仅声明
    class Quote；// 声明但未定义
    class Bulk_Quote：public Quote{}；

    // Base 是 D1 的直接基类
    // Base 是 D2 的间接基类
    class Base{}；
    class D1：public Base{}；
    class D2：public D1{}；


    // 防止继承的发生
    // !! C++ 11 新标准提供了一种防止继承发生的方法，即在类的后面跟一个关键字 final
    class NoDerived final {};

    // !! 类型转换与继承 ---理解基类与派生类之间的关系是 C++ 语言面向对象编程的关键所在

    // !! 静态类型和动态类型
    // 1. 表达式的静态类型在编译时总是已知的，它是变量声明时的类型或表达式生成的类型
    // 2. 变量或表达式表示的内存中的对象类型，动态类型直到运行时才知道。

    // !! 基类的引用和指针的静态类型可能与其动态类型不一致~

    // !! 不存在基类向派生类的隐式类型转换~~~~

    // 之所以存在派生类向基类的类型转换是因为每个派生类都包含一个基类部分，而基类的引用或指针可以绑定到该基类的部分
    // 一个基类的对象既可以以独立的形式存在，也可以作为派生类的一部分而存在
    // 当我们用一个派生类对象向基类对象进行初始化或赋值时，只有该派生类对象中的基类部分会被拷贝、赋值和移动，它的派生类部分将会被忽略掉

    // !! 存在继承关系的类类型之间的转换规则
    // 1. 从派生类向基类类的转换只对引用或者指针类型有效
    // 2. 基类向派生类不存在隐式的转换
    // 3. 和其他任何成员一样，从派生类向基类的类型转换也可能由于访问受限而变得不可行

    // 尽管自动类型转换只对指针和引用有效，但是继承体系中的大多数类任然定义了拷贝控制成员。因此，我们
    // 通常能够将一个派生类对象拷贝、移动、赋值给一个基类对象。值得注意的是，这种操作只处理派生类中的基类部分。

    // !! 虚函数--- 对虚函数的调用可能在运行时才能被解析
    Quote base("0-1000-111-2221",50);
    print_total(cout, base,10);// 调用 Quote:;net_price()
    Bulk_Quote bulk_quote("1-111-222111-234",50,5,0.19);
    print_total(cout,bulk_quote,10);// 调用 Bulk_Quote::net_price()
    // !! 动态绑定必须只有当我们通过指针或引用调用虚函数时才会发生



    base = bulk_quote;// 把 bulk_quote 的部分拷贝给 base
    base.net_price(20);// 调用 Quote::net_price

    // !! 当我们通过一个普通的类型（非引用或指针）的表达式调用虚函数时，在编译时就会将调用的版本确认下来

    // !! C++ 多态性
    // !! 引用或指针的静态类型和动态类型不同这一事实是 C++ 语言支持多态性的根本所在
    // 当我们使用引用或指针调用基类中定义的一个函数时，我们不知道该函数真正作用的对象是什么，因为它可能是一个基类的对象
    // 也可能是一个派生类的对象。如果该函数是一个虚函数，则直到运行时才能决定到底执行哪个版本，判断的依据是引用或指针所
    // 绑定的真实类型；另一方面，对非虚函数的调用在编译时进行绑定的。类似地，通过对象进行函数调用（虚函数或非虚函数）也是在编译时绑定的。

    // !! 当且仅当通过指针或引用调用虚函数时，才会在运行时解析该调用。也只有这种情况下，对象的动态类型才有可能和静态类型不一致。
    
    // !! final 和 override
    // C++ 11 的标准中我们可以使用 override 关键字来说明派生类中的虚函数，这么做的好处是使得程序员的意图更加清晰的同时
    // 让编译器可以为我们发现这一错误。

    // 如果我们使用 override 标记某个函数，但是该函数没有覆盖已存在的虚函数，此时编译器将会报错

    struct B
    {
        virtual void f1(int) const;
        virtual void f2();
        void f3();
    };

    struct A
    {
        void f1(int) const override;// 正确；f1 与 基类中的 f1 匹配
        void f2(int) override;// 错误；B 中没有形如 f2(int) 的函数
        void f3() override;// 错误；f3 不是虚函数
        void f4() override;// 错误； B 中没有 f4 函数
    }

    // 如果将某个函数定义为 final，则之后任何尝试覆盖都会报错

    struct C
    {
        void f11() const; //
    }

    struct D : public C
    {
        void f11()const override;//错误，D 已经将 f11 声明成 final 了
    }

    // !! 纯虚函数（pure virtual）

    class Disk_quoted : public Quote
    {
    public:
        Disk_quoted() = default;
        Disc_quoted(const string &book, double price, std::size_t qty, double disc) : Quote(book, price), quantity(qty), discount(disc) {}

        //  纯虚函数（pure virtual）
        double net_price(std::size_t) const = 0; //
    private:
        std::size_t quantity = 0;
        double discount = 0.0; //
    }

    // !! 含义纯虚函数的类是抽象基类(abstract base class),抽象基类负责定义接口
    // !! 我们不能创建抽象基类的对象

    // !! 派生类的构造函数只能初始化它的直接基类

    // !! 访问控制与继承,每个类控制着其成员对于派生类来说是否可访问（accessable）。

    // 1.受保护的成员(protected),一个类使用 protected 关键字来声明那些它希望与派生类分享但是不想被其它
    // 公共访问使用的成员。
    // 派生类的成员或友元只能访问派生类对象中基类部分的受保护成员；对于普通的基类对象的成员不具有特殊的访问权限

    // !! 公有、私有和受保护继承
    // !! 某个类对于继承而来的成员的访问权限受到两个因素的影响：1. 基类中该成员的访问说明符。2. 派生类的派生列表中的访问说明符

    // 派生类的派生列表中的访问说明符---控制派生类用户对于基类成员的访问权限

    // !! 类的设计与受保护的成员
    // 不考虑继承的话，我们认为一个类有两种不同的用户：普通用户和类的实现者。其中普通用户编写的代码使用类的对象,这部分代码只能访问类的公有成员
    // 实现者负责编写类的成员和友元的代码，类的成员和友元既能访问类的公有部分，也能访问类的私有部分。

    // 如果进一步考虑继承的话就会出现第三种用户，即派生类。基类把它希望派生类能够使用的部分声明成受保护的。普通用户不能访问受保护的成员，而派生类及友元仍旧
    // 不能访问私有成员。

    // 和其它类一样，基类应该将其接口声明为公有的；同时将其实现的部分分为两组：一组供派生类访问；一组只能由基类和基类的友元访问。对于前者应该声明成
    // 受保护的，这样派生类就能够在实现自己的功能时使用基类的这些操作和数据；对于后者应该声明为私有的；


    // !! 友元与继承
    // !! 不能继承友元关系；每个类负责控制各自成员的访问权限
    class Base
    {
        friend class Pal;

    };

    class Pal
    {
    public:
        int f(Base b) { return b.prot_mem; }
        int f2(Sneaky s) { return s * j; }
        int f3(Sneaky s) { return s.prot_mem; }
    };

    // !! 改变个别成员的访问权限
    // !! 通过使用 using 声明，我们可以改变派生类继承的某个名字的访问级别
    // 1. 如果 using 声明语句出现在类的 private 部分，则该名字只能被类的成员或友元访问
    // 2. 如果 using 声明语句出现在类的 public 部分，则该名字能被类的所有用户访问
    // 3. 如果 using 声明语句出现在类的 protected 部分，则该名字能被类的成员、派生类、友元访问

    // !! 派生类只能为那些它可以访问的成员使用 using 声明

    class Base
    {
    public:
        std::size_t size() const { return n; }

    protected:
        std::size_t n;
    }

    class Derived : private Base
    {
    public:
        // 使用 using 声明语句改变了这些成员的可访问性
        using Base::size;// Derived 的用户将可以使用 size 成员

    protected:
        using Base::n;// Derived 的派生类将可以使用 n
    }

    // !! 默认的继承保护级别
    // class 关键字定义的派生类是私有继承的; struct 关键字定义的派生类是公有继承的

    class Base{}；

    class BaseA : Base{}；// 默认 private 继承

    struct BaseB : Base{};// 默认 public 继承

    // !! class 和 struct 定义类的唯一区别是：默认成员访问说明符以及默认派生访问说明符

    // !! 继承中类的作用域
    // 每个类定义了自己的作用域，在这个作用域了我们定义了类的成员；

    // !! 当存在继承关系时，派生类的作用域嵌套在其基类的作用域之内

    // 如果一个名字在其派生类中无法正确解析，则编译器会继续在外层的基类作用域中寻找该名字的定义。
    // 恰恰因为类的作用域这种继承关系，所以派生类才能像使用自己的成员一样使用基类的成员

    Bulk_Quote bulk_quote;
    cout << bulk_quote.isbn() << endl;

    // !! 名字 isbn 的解析过程：
    // 1. 因为我们通过 bulk_quote 对象调用 isbn ，所以首先在 Bulk_Quote 中查找，这一步没有找到名字 isbn
    // 2. 因为 Bulk_Quote 是 Disc_Quote 的派生类，所以接下来在 Disc_Quote 中查找，仍然找不到
    // 3. 因为 Disc_Quote 是 Quote 的派生类，所以接下来在 Quote 中查找，此时找到了名字 isbn。所以我们使用的 isbn 最终被解析为 Quote 中的 isbn

    // !! 在编译时进行名字查找
    // !! 一个对象、引用和指针的静态类型决定了该对象的哪些成员是可见的。即使静态类型和动态类型可能不一致，但是我们能使用哪些成员是由静态类型决定的。

    Bulk_Quote bulk_quote;
    Bulk_Quote * p = &bulk_quote;
    Quote * quote = &bulk_quote;
    bulk_quote->discount_police();// ok
    quote->discount_police();// fail


    // !! 名字冲突与继承----派生类的成员将隐藏同名的基类成员

    // !! 通过作用域运算符（:：）来使用隐藏的成员

    struct Derived : public Base
    {
        public:
        // 作用域运算符（::）将覆盖原有的查找规则，并指示编译器从 Base 类的作用域开始查找 mem；
        int get_mem() { return Base::mem; }

    }

    // !! 理解函数调用的解析过程对于理解 C++ 继承至关重要，假设我们调用 p->mem(),则依次执行以下四个步骤：
    // 1. 首先确定 p 的静态类型。因为我们调用的是一个成员，所以该类型必须是类类型
    // 2. 在 p 的静态类型中查找 mem 成员。如果找不到，则依次在直接基类中不断查找直至达到继承链的顶端。如果还是找不到，则直接报错
    // 3. 一旦找到 mem，就会对其进行常规的类型检查已确认对于当前找到的 mem，本次调用是否合法。
    // 假设调用合法，编译器会根据调用是否是虚函数而产生不同的代码：
    // 如果 mem 是虚函数且我们通过引用或指针进行调用，则编译器产生的代码将在运行时确定到底运行该虚函数的哪个版本，依据的是对象的动态类型
    // 反之，如果 mem 不是虚函数或者我们是通过对象进行的调用，则编译器将产生一个常规的函数调用。

    // !! 一如既往，名字查找先于类型检查
    // 如果派生类成员和基类的某个成员同名，则派生类将在其作用域内隐藏该基类成员。即使派生类中成员和基类成员的形参列表不一致。s
    class Base{
        void memfcn();
    };

    class Derived: public Base{
        void memfcn(int a);// 隐藏基类的 memfcn
    };



    Derived d;
    Base b;
    b.memfcn();// 调用 Base::memfcn
    d.memfcn(10);// 调用 Derived::memfcn
    d.memfcn();// 错误，参数列表为空的 memfcn 被隐藏了
    d.Base::memfcn();// 正确，调用 Base::memfcn


    // !! 虚函数与作用域
    class Base
    {
    public:
        virtual int fcn();
    };


    class D1 : public Base
    {
    public:
        int fcn(int);// 形参列表与 Base 中的 fcn 不一致
        virtual void f2(); // 是一个新的虚函数，在 Base 中不存在
    };


    class D2 : public D1
    {
    public:
        int fcn(int);// 是一个非虚函数，隐藏了 D1::fcn(int)
        int fcn();// 覆盖了 Base 中的虚函数 fcn
        void f2(); //覆盖了 D1 中的虚函数 f2
    };


    // !! 通过基类调用隐藏的虚函数
    Base bobj;
    D1 d1obj;
    D2 d2obj;

    Base *bp1 = &bobj;
    Base *bp2 = &d1obj;
    Base *bp3 = &d2obj;

    bp1->fcn();// 虚调用，将在运行期调用 Base::fcn
    bp2->fcn();// 虚调用，将在运行期调用 Base::fcn
    bp3->fcn();// 虚调用，将在运行期调用 D2::fcn

    D1 *dp1 = &d1obj;
    D2 *dp2 = &d2obj;

    bp2->f2();// 错误；Base 中没有 f2 的成员
    dp1->f2();//虚调用，将在运行其调用 D1::f2;
    d2p->f2();//虚调用，将在运行其调用 D2::f2;

    Base *p1 = &d1obj;
    D1 *p2 = &d2obj;
    D2 *p3 = &d2obj;

    p1->fcn(42);// 错误，Base 中没有一个接受 int 的 fcn
    p2->fcn(42);// 静态绑定，调用 D1::fcn(int)
    p3->fcn(42);// 静态绑定，调用 D2::fcn(int)

    // !! 虚析构函数 --我们通过在基类中将析构函数定义为虚函数以确保执行正确的析构函数版本

    class Quote
    {
        public:
        // 如果我们删除的是一个指向派生类对象的基类指针，则需要虚析构函数
        virtual ~Quote() = default;// 动态绑定析构函数
    }

    // !! 对于派生类的析构函数而言，它除了销毁派生类自己的成员外，还负责销毁派生类的直接基类
    // !! 该直接基类又会负责销毁它的直接基类，依次类推直到继承链顶端

    // !!派生类的拷贝控制成员
    // 派生类的构造函数在其初始阶段不但要初始化派生类自己的成员，还负责初始化派生类对象的基类部分

    // !! 定义派生类的拷贝和移动构造函数

    class Base
    {

    };

    class D : public Base
    {
    public:
        D(const D &d) : Base(d) {// 拷贝基类成员---Base 的拷贝构造函数负责 d 的基类部分拷贝给要创建的对象
            // D 的成员初始化
        }
        D(const &&d) : Base(d) {}
    };


    // !! 派生类的赋值运算符

    D &D::operator=(const D&rhs)
    {
        Base::operator(rhs);// 为基类部分赋值
        return *this;
    }


    // !! 派生类的析构函数
    // 在析构函数体执行完成后，对象的成员会被隐式的销毁；类似地，对象的基类部分也是被隐式销毁的。
    class D : public Base
    {
        // Base::~Base 被自动调用执行
        ~D()
        {
            // 该处由用户定义清楚派生类成员的操作
        }
    }

    // !! 在构造函数和析构函数中调用虚函数

    // 派生类对象的基类部分将首先被构建。当执行基类的构造函数时，该对象的派生类是未被初始化状态。
    // 类似地，销毁派生类对象的顺序正好相反，因此当执行基类的析构函数时，派生类已经被销毁掉了

    // 如果构造函数和析构函数调用了某个虚函数，则我们应该执行与构造函数或析构函数所属类型相对应的虚函数版本


    // !! 继承的构造函数----C++ 11 新标准中，派生类能够重用其直接基类定义的构造函数
    // 类不能继承默认、拷贝和移动构造函数；如果派生类没有直接定义这些构造函数，则编译器会为派生类合成它们

    // 派生类继承基类构造函数的方式是提供一条注明了（直接）基类名的 using 声明语句
    // !! 通常情况下，使用 using 语句只是令某个名字在当前作用域类可见~~
    // 而当作用与构造函数时，using 声明语句将令编译器产生代码。
    class Bulk_Quote: public Quote
    {
        public:
        using Disc_Quote::Disc_Quote;// 继承 Disc_Quote 的构造函数
        double net_price(std::size_t) const;
    };

    // 对于基类的每个构造函数，编译器都会生产一个与之对应的派生类构造函数
    // 编译器生产的构造函数形式如下：
    Derived(parms):base(args);

    // !! 容器与继承

    vector<Quote> basket;
    basket.push_back(Quote("1-2-333-111",10));
    // 正确；但是只能把 Bulk_Quote 对象的 Quote 部分拷贝给 basket
    basket.push_back(Bulk_Quote("1-22-111111",50,10,25));
    cout << basket.back().net_price(15)<< endl;

    // !! 当派生类对象被赋值给基类对象时，其中派生类部分将会被“切换”，因此容器和存在继承关系的类型无法兼容

    // !! 在容器中放置（智能）指针而非对象
    // 当我们希望在容器中存放具有继承关系的对象时，我们实际上存放的应该是基类的指针（更好的选择是智能指针）

    vector<shared_ptr<Quote>> basket;
    basket.push_back(make_shared<Quote>("1-22-222-222-2",50));
    basket.push_back(make_shared<Bulk_Quote>("1-2-11-111-1",50,10,0.25));

    // !! 实际调用的 net_price 依赖于指针所指对象的动态类型
    cout << basket.back()->net_price(15) << endl;


    // 对于 C++ 面向对象编程来说，一个悖论是我们无法直接使用对象进行面向对象编程；相反，我们必须使用指针和引用。

    // !! 继承与组合
    // 继承体系的设计本身就是一个非常复杂的问题，然而有一条设计准则非常重要也非常基础，每个程序员都应该熟悉它。
    // 1. 当我们令一个类公有的继承另外一个类，派生类应但反应与基类的“是一种（Is A）”关系。在设计良好的类体系中，
    // 公有派生类的对象应该可以用在任何需要基类对象的地方。
    // 2. 类型之间另外一种常见的关系是“有一个 Has A”关系，具有这种关系的类暗含成员的意思。



    



}