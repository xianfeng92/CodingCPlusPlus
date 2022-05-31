
// !! Function语意学

The Semantics of Function

如果我有一个 Point3d 的指针和对象:

Point3d obj;
Point3d *ptr = &obj;

当我这样做:

obj.normalize();
ptr->normalize();

时, 会发生什么事? 其中的 Point3d:normalize() 定义如下:

Point3d Point3d::normalize() const {
    register float mag = magnitude();
    Point3d normal;
    normal.x_ = x_ / mag;
    normal.y_ = y_ / mag;
    normal.z_ = z_ / mag;
    return normal;
}

而其中的 Point3d::magnitude() 又定义如下:

float Point3d::Magnitude(){
    return sqrt(x_*x_ + y_*y_ + z_*z_);
}

答案是: 我不知道~ 'C++ 支持三种类型的 member functions: static、nonstatic 和 virtual, 每一种类型被调用的方式都不相同'。

不过, 我们虽然不能够确定 normalize() 和 magnitude() 两函数是否为 virtual 或 non virtual, 但可以确定它一定不是 static, 原因有二:

1. 它直接存取 non static 数据

2. 它被声明为 const。是的, static member functions 不可能做到这两点。


// !! Member 的各种调用方式

回顾历史, 原始的 C with Classes 只支持 nonstatic member functions。Virtual 函数是在20世纪80年代中期被加进来的, 并且很显然受到许多质疑
(许多质疑至今在 C 族群中仍然存在)。Bjarne 写道:

'有一种常见的观点, 认为 virtual functions 只不过是一种跛脚的函数指针, 没什么用……其意思主要就是 virtual functions 是一种没有效能的形式'。


Static member functions 是最后被引入的一种函数类型。它们在 1987 年的 Usenix C++ 研讨会的厂商研习营中被正式提议加入这个语言, 并由 cfront 2.0 
实现出来。


// !! Nonstatic Member Functions（非静态成员函数）

C++ 的设计准则之一就是: 'nonstatic member function 至少必须和一般的 nonmember function 有相同的效率'。也就是说, 如果我们要在以下两个函数之间做
选择:

float magnitude3d(){}

float Point3d::magnitude3d(){}

选择 member function 不应该带来什么额外负担。'这是因为编译器内部已将 member 函数实例转换为对等的 nonmember函数实例'。

举个例子, 下面是 magnitude() 的一个 nonmember 定义:

float magnitude3d(const Point3d& point) {
    return (point_x * point.x_ + point.y_ * point.y_ + point.z_ * point.z_);
}

乍见之下似乎 nonmember function 比较没有效率, 它间接地经由参数取用坐标成员, 而 member function 却是直接取用坐标成员。然而实际上
member function 被内化为 nonmember 的形式。下面就是转化步骤:

1. '改写函数的 signature(函数原型)以安插一个额外的参数到 member function 中, 用以提供一个存取管道, 使 class object 得以将此函数调用'。该额外参数
    被称为 this 指针:

    // 如果 member function 是 non const, 则变成:
    Point3d Point3d::magnitude(Point3d* const this) {
        //...
    }

    // 如果 member function 是 const, 则变成:
    Point3d Point3d::magnitude(const Point3d* const this) {
        //...
    }

2. 将每一个'对 nonstatic data member 的存取操作'改为经由 this 指针来存取

    {
        return (sqrt(this->x_ * this->x_ + this.y_ * this.y_ + this.z_ * this.z_));
    }


3. '将 member function 重新写成一个外部函数'。将函数名称经过"mangling"处理, 使它在程序中成为独一无二的语汇:

    extern magnitude_7Point3dFv(register Point3d * const this);

现在这个函数已经被转换好了, 而其每一个调用操作也都必须转换。于是:

obj.magnitude();

变成了:

magnitude_7Point3dFv(&obj);

而:

ptr->magnitude();

变成了:

magnitude_7Point3dFv(ptr);

本章一开始所提的 normalize() 函数会被转化为下面的形式, 其中假设已经声明有一个 Point3d copy constructor, 而 named returned value (NRV) 的优化
也已施行:

void normalize_7Point3dFv(register const Point3d * const this, Point3d& _result) {
    register float mag = magnitude();
    _result.Point3d::Point3d();
    _result.x_ = this->x_ / mag;
    _result.y_ = this->y_ / mag;
    _result.z_ = this->z_ / mag;
    return;
}

一个比较有效率的做法是直接建构"normal"值, 像这样:

Point3d Point3d::normalize() const {
    register float mag = magnitude();
    return Point3d(x_/mag, y_/mag, z_/mag);
}

它会被转化为以下的代码(再一次我假设 Point3d 的 copy constructor 已经声明好了, 而 NRV 的优化也已实施):

void normalize_7Point3dFv(register const Point3d * const this, Point3d _result){
    register float mag = magnitude();
    _result.Point3d::Point3d(this->x_ / mag, this->y_ / mag, this-z_ /mag);
    return;
}

这可以节省 default constructor 初始化所引起的额外负担。


// !! 名称的特殊处理（Name Mangling）

一般而言, member 的名称前面会被加上 class 名称, 形成独一无二的命名。

例如下面的声明:

class Bar{
    public:
        int ival;
        //...
};

其中的 ival 有可能变成这样:

ival_3Bar;

为什么编译器要这么做 ? 请考虑这样的派生操作(derivation):

class Foo : public Bar {public: int ival;};

记住, Foo 对象内部结合了 base class 和 derived class 两者:

// C++ 伪代码
class Foo{
    public:
        int ival_3Bar;
        int ival_3Foo;
};

不管你要处理哪一个 ival, 通过"name mangling" 都可以绝对清楚地指出来。由于 member functions 可以被重载化 (overloaded), 所以需要更广泛的
mangling 手法, 以提供绝对独一无二的名称。

如果把:

class Point{
public:
    void x(float newX);
    float x();
    //...
 };


转换为:

class Point{
public:
    void x_5Point(float newX);
    float x_5Point();
    //...
 };

 会导致两个被重载化 (overloaded) 的函数实例拥有相同的名称。为了让它们独一无二, 唯有再加上它们的参数列表。如果把参数类型也编码进去, 就一定可以制造出独一无二
 的结果, 使我们的两个 x() 函数有良好的转换(但如果你声明 extern "C", 就会压抑 nonmember functions 的"mangling"效果)

 class Point{
    public:
        void x_5Point_Ff(float newX);
        float x_5Point_Fv();
 }

 以上所示只是 cfront 采用的编码方法。我必须承认, 目前的编译器并没有统一的编码方法——虽然不断有一些活动企图导引出这方面的一个工业标准。'C++ 编译器对
 name mangling 的做法目前还没有统一, 但我们知道它迟早会统一'。

'把参数和函数名称编码在一起, 编译器于是在不同的被编译模块之间达成了一种有限形式的类型检验'。

举个例子, 如果一个 print 函数被这样定义:

void print(const Point3d& ){...}

但意外地被这样声明和调用:

void print(const Point3d);

两个实例如果拥有独一无二的 name mangling, 那么任何不正确的调用操作在链接时期就因无法决议(resolved) 而失败。有时候我们可以乐观地称此为"确保类型安全的链
接行为"(type-safe linkage)。我说"乐观地"是因为它只可以捕捉函数的标记 (signature, 亦即函数名称+参数个数+参数类型）错误; 如果"返回类型"声明错误,就没办
法检查出来!

在目前的编译系统中, 有一种所谓的 demangling 工具, 用来拦截名称并将其转换回去。使用者可以仍然处于"不知道内部名称"的极大幸福之中。然而生命并不是长久以来一直
如此轻松, 在 cfront 1.1 版中, 由于该系统未经世故, 因此总是收藏两种名称(未经 mangled 和经过 mangled 的两种名称); 编译错误消息用的是程序源码函数名称,
然而链接器却不, 它用的是经过 mangled 的内部名称。

// !! Virtual Member Functions（虚拟成员函数）

如果 normalize() 是一个 virtual member function, 那么以下的调用:

ptr->normalize();

将会被内部转化为:

(*prt->vptr[1])(ptr);

其中:

1. vptr 表示由编译器产生的指针, 指向 virtual table。它被安插在每一个"声明有(或继承自)一个或多个 virtual functions"的 class object 中。事实上其
   名称也会被"mangled", 因为在一个复杂的 class 派生体系中, 可能存在多个 vptr。

2.  1 是 virtual table slot 的索引值, 关联到 normalize() 函数

3.  第二个 ptr 表示 this 指针

类似的道理, 如果 magnitude() 也是一个 virtual function, 它在 normalize()  之中的调用操作将被转换如下:

register float mag = (*this->vptr[2])(this);

此时, 由于 Point3d::magnitude() 是在 Point3d::normalize() 中被调用的, 而后者已经由虚拟机制而决议(resolved)妥当, 所以显式地调用"Point3d 实例"会
比较有效率, 并因此压制由于虚拟机制而产生的不必要的重复调用操作:

register float mag = Point3d::magnitude();

如果 magnitude() 声明为 inline 函数会更有效率。'

使用 class scope operator 显式调用一个 virtual function, 其决议(resolved) 方式会和 nonstatic member function 一样':

register float mag = magnitude_7Point3dFv(this);

对于以下调用:

obj.normalize();

如果编译器把它转换为:

(*obj.vptr[1])(&obj);

虽然语意正确, 却没有必要。

"经由一个 class object 调用一个virtual function", 这种操作应该总是被编译器像对待一般 nonstatic member function 一样地加以决议(resolved):

normalize_7Point3dFv(&obj);

这项优化工程的另一利益是, virtual function 的一个 inline 函数实例可以被扩展(expanded)开来, 因而提供极大的效率利益。


// !! Static Member Functions（静态成员函数）

如果 Point3d::normalize() 是一个 static member function, 以下两个调用操作:

obj.normalize();
ptr->normalize();

将被转换为一般的 nonmember 函数调用, 像这样:

//obj.normalize();
normalize_7Point3dSFv();

//ptr->normalize();
normalize_7Point3dSFv();

在 C++ 引入 static member functions 之前, 我想你很少看到下面这种怪异写法:

((Point3d*)0)->object_count();

其中的 object_count() 只是简单传回 _object_count 这个 static data member。这种习惯是如何演化来的?

在引入 static member functions 之前, C++ 语言要求所有的 member functions 都必须经由该 class 的 object 来调用。而实际上, 只有当一个或多个 
nonstatic data members 在 member function 中被直接存取时, 才需要 class object。Class object 提供了 this 指针给这种形式的函数调用使用。

这个 this 指针把"在 member function 中存取的 nonstatic class members"绑定于"object 内对应的 members"之上。'如果没有任何一个 member 被直
接存取, 事实上就不需要 this 指针, 因此也就没有必要通过一个 class object 来调用一个 member function'。不过 C++ 语言到目前为止并不能够辨识这种情况。

独立于 class object 之外的存取操作, 在某个时候特别重要: '当 class 设计者希望支持没有 class object 存在的情况(就像前述的 object_count() 那样)
时。程序方法上的解决之道是很奇特地把 0 强制转换为一个 class 指针', 因而提供出一个 this 指针实例:

object_count((Point3d*)0);

至于语言层面上的解决之道, 是由 cfront 2.0 所引入的 static member function。'Static member function 的主要特性就是它没有 this 指针'。以下的
次要特性统统根源于其主要特性:

1. 它不能够直接存取其 class 中的 nonstatic members

2. 它不能够被声明为 const、volatile 或 virtual

3. 它不需要经由 class object 才被调用——虽然大部分时候它是这样被调用的

"member selection" 语法的使用是一种符号上的便利, 它会被转化为一个直接调用操作:

if(Point3d::object_count() > 1){}

如果 class object 是因为某个表达式而获得的, 会如何? 例如:

if(foo().object_count() > 1){}

噢, 这个表达式仍然需要被评估求值(evaluated):

(void)foo();
if(Point3d::object_count() > 1){}

一个 static member function, 当然会被提出于 class 声明之外并给予一个经过 "mangled" 的适当名称。例如:

unsigned int Point3d::object_count() {
    return _object_count;
}

会被 cfront 转化为:

unsigned int object_count_5Point3dSFv() {
    return object_count_5Point3d;
}

其中 SFv 表示它是一个 static member function, 拥有一个 void 的参数列表 (argument list)

如果取一个 static member function 的地址, 获得的将是其在内存中的位置, 也就是其地址。由于 static member function 没有 this 指针, 所以其地址的类
型并不是一个"指向 class member function 的指针", 而是一个"nonmember 函数指针"。也就是说:

&Point3d::object_count();

会得到一个数值, 类型是:

unsigned int(Point3d::*)();

'static member function 由于缺乏 this 指针, 因此差不多等同于 nonmember function。它提供了一个意想不到的好处: 成为一个 callback 函数', 使我们
得以将 C++ 和 C-based X Window 系统结合。


// !! 4.2 Virtual Member Functions（虚拟成员函数）

virtual function 的一般实现模型: 每一个 class 有一个 virtual table, 内含该 class 之中有作用的 virtual function 的地址, 然后每个 object 有一
个 vptr, 指向 virtual table 的所在。

'为了支持 virtual function 机制, 必须首先能够对于多态对象有某种形式的执行期类型判断法(runtime type resolution)'。

也就是说以下的调用操作将需要 ptr 在执行期的某些相关信息:

ptr->z();

如此一来才能够找到并调用 z() 的适当实例。

或许最直截了当但是成本最高的解决方法就是把必要的信息加在 ptr 身上。在这样的策略之下, 一个指针(或是一个 reference )持有两项信息:

1.它所参考到的对象的地址(也就是目前它所持有的东西)

2.对象类型的某种编码, 或是某个结构(内含某些信息,用以正确决议出 z() 函数实例)的地址

这个方法带来两个问题:第一,它明显增加了空间负担, 即使程序并不使用多态 (polymorphism); 第二, 它打断了与 C 程序间的链接兼容性

'如果这份额外信息不能够和指针放在一起, 下一个可以考虑的地方就是把它放在对象本身'。但是哪一个对象真正需要这些信息呢? 我们应该把这些信息放进可能被继承的每一
个集合体身上吗? 或许吧~ 但请考虑一下这样的 C struct 声明:

struct data{
    int m, d, y;
};

严格地说, 这符合上述规范。然而事实上它并不需要那些信息。'加上那些信息将使 C struct 膨胀并且打破链接兼容性, 却没有带来任何明显的补偿利益'。

"好吧,"你说: "只有面对那些显式使用了 class 关键词的声明, 才应该加上额外的执行期信息"。这么做就可以保留语言的兼容性了, 不过仍然不是一个够聪明的政策。
举个例子, 下面的 class 符合新规范:

class data{
public:
    int m, d, y;
};

但实际上它并不需要那份信息。

下面的 class 声明虽然不符合新规范, 却需要那份信息:

struct geom{
public:
    ~geom() {}
};

噢, 是的, 我们需要一个更好的规范, 一个"以 class 的使用为基础, 而不在乎关键词是 class 或 struct"的规范。如果 class 真正需要那份信息,它就会存在; 如果
不需要, 它就不存在。

'那么, 到底何时才需要这份信息'? ===  很明显是在必须支持某种形式之"执行期多态(runtime polymorphism)" 的时候。

在 C++ 中. 多态(polymorphism)表示 " 以一个 public base class 的指针(或 reference), 寻址出一个 derived class object" 的意思。

例如下面的声明:

Point *ptr;

我们可以指定 ptr 以寻址出一个 Point2d 对象:

ptr = new Point2d();

或是一个 Point3d 对象:

ptr = new Point3d();

'ptr 的多态机能主要扮演一个输送机制(transport mechanism)的角色', 经由它我们可以在程序的任何地方采用一组 public derived 类型。这种多态形式被称为
是消极的(passive), 可以在编译时期完成 -- virtual base class 的情况除外。

'当被指出的对象真正被使用时, 多态也就变成积极的(active)了'。

下面对于 virtual function 的调用, 就是一例:

ptr->z();

在 runtime type identification(RTTI) 性质于 1993 年被引入 C++ 语言之前, C++ 对"积极多态(active polymorphism)"的唯一支持, 就是对于
virtual function call 的决议(resolution)操作。'有了 RTTI, 就能够在执行期查询一个多态的 pointer 或多态的 reference了'。

if(Point3d *p3d = dynamic_cast<Point*3d>(ptr)) {
    p3d->z();
}

所以, 问题已经被区分出来, 那就是:'欲鉴定哪些 class 展现多态特性, 我们需要额外的执行期信息'。一如我所说, 关键词 class 和 struct 并不能能够帮助我们。
由于没有导入像是 polymorphic 之类的新关键词, 因此'识别一个 class 是否支持多态, 唯一适当的方法就是看看它是否有任何 virtual function'。'只要 class 
拥有一个 virtual function, 它就需要这份额外的执行期信息'。


下一个明显的问题是, '什么样的额外信息是我们需要存储起来的'? 也就是说, 如果我有这样的调用:

ptr->z();

其中 z() 是一个 virtual function, 那么什么信息才能让我们在执行期调用正确的 z() 实例? 我需要知道:

1. ptr 所指对象的真实类型。这可使我们选择正确的 z() 实例

2. z() 实例的位置, 以便我能够调用它

在实现上, 首先我可以在每一个多态的 class object 身上增加两个 members: 

1. 一个字符串或数字, 表示 class 的类型

2. 一个指针指向某表格, 表格中持有程序的 virtual functions 的执行期地址

'表格中的 virtual functions 地址如何被建构起来'?

在 C++ 中, virtual functions (可经由其 class object 被调用) 可以在编译时期获知。此外, 这一组地址是固定不变的, 执行期不可能新增或替换之。由于程序执行时,
表格的大小和内容都不会改变, 所以其建构和存取皆可以由编译器完全掌控, 不需要执行期的任何介入。

然而, 执行期备妥那些函数地址, 只是解答的一半而已。另一半解答是找到那些地址。两个步骤可以完成这项任务:

1. 为了找到表格, 每一个 class object 被安插了一个由编译器内部产生的指针 vptr 指向该表格

2. 为了找到函数地址, 每一个 virtual function 被指派一个表格索引值

'这些工作都由编译器完成。执行期要做的', 只是在特定的 virtual table slot(记录着 virtual function 的地址)中激活 virtual function。

一个 class 只会有一个 virtual table。每一个 table 内含其对应之 class object 中所有 active virtual functions 函数实例的地址。这些 
active virtual functions 包括:

1.  这一 class 所定义的函数实例。它会改写(overriding) 一个可能存在的 base class virtual function 函数实例

2.  继承自 base class 的函数实例。这是在 derived class 决定不改写 virtual function 时才会出现的情况

3.  一个 pure_virtual_called() 函数实例, 它既可以扮演 pure virtual function 的空间保卫者角色, 也可以当做执行期异常处理函数

每一个 virtual function 都被指派一个固定的索引值, 这个索引在整个继承体系中保持与特定的 virtual function 的关系。例如在我们的 Point class 体系中:

class Point {
public:
    virtual ~Point();
    virtual Point multi(float) = 0;
    float x() const { return x_}
    virtual float y(){return 0;}
    virtual float z(){return 0;}
private:
    float x_;
    Point(float x = 0.0f);
};

virtual destructor 被指派 slot 1, 而 mult() 被指派 slot 2。此例并没有 mult() 的函数定义(因为它是一个 pure virtual function), 所以
pure_virtual_called() 的函数地址会被放在 slot 2 中。如果该函数意外地被调用, 通常的操作是结束掉这个程序。y() 被指派 slot 3 而 z() 被指派 slot 4。
x() 的 slot 是多少? 答案是没有, 因为 x() 并非 virtual function。

当一个 class 派生自 Point 时, 会发生什么事 ? 例如 class Point2d: 

class Point2d : public Point {
public:
    Point2d(float x = 0.0f, float y = 0.0f) : Point(x), y_(y){}
    ~Point2d();
    Point2d& multi(float);

    float y() const { return y_};

private:
    float y_;
};

一共有三种可能性:

1. 它可以继承 base class 所声明的 virtual functions 的函数实例。'正确地说是, 该函数实例的地址会被拷贝到 derived class 的 virtual table
   的相对应 slot 之中'

2. 它可以使用自己的函数实例。这表示它自己的函数实例地址必须放在对应的 slot 之中

3. 它可以加入一个新的 virtual function, 这时候 virtual table 的尺寸会增大一个 slot, 而新的函数实例地址会被放进该 slot 之中

Point2d 的 virtual table 在 slot 1 中指出 destructor, 而在 slot 2 中指出 mult()(取代 pure virtual function )。它自己的 y() 函数实例地址放
在 slot 3 中, 继承自 Point 的 z() 函数实例地址则放在 slot 4 中。

类似的情况, Point3d 派生自 Point2d, 如下:

class Point3d : public Point2d {
public:
    Point3d(float x = 0.0f, float y = 0.0f, float z = 0.0f): Point2d(x, y), z_(z){}

    ~Point3d();
    Point3d& multi(float);

protected:
    float z_;
};

其 virtual table 中的 slot 1 放置 Point3d 的 destructor, slot 2 放置 Point3d::mult() 函数地址, slot 3 放置继承自 Point2d 的 y() 函数地址
, slot 4 放置自己的 z() 函数地址。

现在, 如果我有这样的式子:

ptr->z();

我如何有足够的知识在编译时期设定 virtual function 的调用呢?

1. 一般而言, 在每次调用 z() 时, 我并不知道 ptr 所指对象的真正类型。然而我知道, 经由 ptr 可以存取到该对象的 virtual table。

2. 虽然我不知道哪一个 z() 函数实例会被调用, 但我知道每一个 z() 函数地址都被放在 slot 4 中

这些信息使得编译器可以将该调用转化为:

(*(ptr->vptr[4]))(ptr);

在这一转化中 vptr 表示编译器所安插的指针, 指向 virtual table; 4 表示 z() 被指派的 slot 编号(关系到 Point 体系的 virtual table)。唯一一个在执行
期才能知道的东西是: slot 4 所指的到底是哪一个 z() 函数实例 ?

在一个单一继承体系中, virtual function 机制的行为十分良好, 不但有效率而且很容易塑造出模型来。但是在多重继承和虚拟继承之中, 对 virtual function 的
支持就没有那么美好了。


// !! 多重继承下的 Virtual Functions

在多重继承中支持 virtual functions 其复杂度围绕在第二个及后继的 base class 身上, 以及必须在执行期调整 this 指针这一点。

以下面的 class 体系为例:

class Base1{
public:
  Base1();
  virtual ~Base1();
  virtual void speakClearly();
  virtual Base1 *clone() const;
protected:
  float data_Base1;
};

class Base2{
public:
  Base2();
  virtual ~Base2();
  virtual void mumble();
  virtual Base2 *clone() const;
protected:
  float data_Base2;
};

class Derived : public Base1, public Base2{
public:
  Derived();
  virtual ~Derived();
  virtual Derived *clone() const;
protected:
  float data_Derived;
};

Derived 支持 virtual function  的困难度, 统统落在 Base2 subobject 身上。有三个问题需要解决, 以此例而言分别是:

1.  virtual destructor

2.  被继承下来的 Base2::mumble()

3.  一组 clone() 函数实例


首先, 我把一个从 heap 中配置而得的 Derived 对象的地址, 指定给一个 Base2 指针:

Base2 *pbase2 = new Derived();

新的 Derived 对象的地址必须调整以指向其 Base2 subobject。编译时期会产生以下的代码:

Derived *temp = new Derived();
Base2 *pbase2 = temp ? temp + sizeof(Base1) : 0;

如果没有这样的调整, 指针的任何非多态运用 (像下面那样) 都将失败:

pbase2->data_Base2;

当程序员要删除 pbase2 所指的对象时:

delete pbase2;

指针必须被再一次调整,以求再一次指向 Derived 对象的起始处。

一般规则是, 经由指向第二或后继之 base class 的指针(或 reference) 来调用 derived class virtual function。

Base2 *pbase2 = new Derived();
...
delete pbase2;// invoke derived class destructor 

其所连带的必要的 this 指针调整操作, 必须在执行期完成。也就是说, offset 的大小, 以及把 offset 加到 this 指针上头的那一小段程序代码,必须由编译器在某个地方
插入。问题是, 在哪个地方 ?

Bjarne 原先实施于 cfront 编译器中的方法是将 virtual table 加大, 使它容纳此处所需的 this 指针, 调整相关事物。每一个 virtual table slot, 不再只是一个
指针, 而是一个集合体, 内含可能的 offset 以及地址。

(*pbase2->vptr[1])(pbase2);

改变为:

(*pbase2->vptr[1].faddr)
(*pbase2->vptr[1].offset);

其中 faddr 内含 virtual function 地址, offset 内含 this 指针调整值。

比较有效率的解决方法是利用所谓的 thunk。

Thunk 技术初次引进到编译器技术中, 我相信是为了支持 ALGOL 独一无二的 pass-by-name 语意。所谓 thunk 是一小段 assembly 代码,用来 1. 以适当的 offset 值
调整 this 指针,2. 跳到 virtual function 去。

pbase2_dtor_thunk:
this += sizeof(base1);
Derived::~Derived(this);


// !! 虚拟继承下的 Virtual Functions

考虑下面的 virtual base class 派生体系, 从 Point2d 派生出 Point3d:

class Point2d {
public:
    Point2d(float x = 0.0f, float y = 0.0f): x_(x), y_(y) {}
    virtual ~Point2d();

    virtual void mumble();
    void float z();
    //...
protected:
    float x_;
    float y_;
};

class Point3d : public virtual Point2d {
public:
    Point3d(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    ~Point3d();
    float z();
private:
    float z_;
};


虽然 Point3d 有唯一一个(同时也是最左边的) base class, 也就是 Point2d, 但 Point3d 和 Point2d 的起始部分并不像"非虚拟的单一继承"情况那样一致。
由于 Point2d 和 Point3d 的对象不再相符, 两者之间的转换也就需要调整 this 指针。至于在虚拟继承的情况下要消除 thunks, 一般而言已经被证明是一项高难
度技术。


// !! 函数的效能

在下面这组测试中, 我在不同的编译器上计算两个 3D 点, 其中用到一个 nonmember friend function, 一个 member function, 以及一个 virtual member 
function, 并且 Virtual member function 分别在单一、虚拟、多重继承三种情况下执行。下面就是 nonmember function:

'nonmember、static member或 nonstatic member 函数都被转化为完全相同的形式。所以我们毫不惊讶地看到三者的效率完全相同'。

但是我们很惊讶地发现, 未优化的 inline 函数提高了 25% 左右的效率。而其优化版本的表现简直是奇迹。怎么回事?

这项惊人的结果归功于编译器将"被视为不变的表达式(expressions)" 提到了循环之外, 因此只计算一次。此例显示, 'inline 函数不只能够节省一般函数调用所带来的额
外负担, 也提供了程序优化的额外机会'。

我对 virtual function 的调用, 是通过一个 reference, 而不是通过一个对象, 借此我就可以确定调用操作经过了虚拟机制。效率的降低程度从 4% 到 11% 不等, 其
中的一部分反映出 Point3d constructor 对于 vptr 1000 万次的设定操作。


当我在单一继承情况下执行这项测试时, 我也困惑地发现, '每多一层继承, virtual function 的执行时间就有明显的增加'。一开始我无法想象其间发生了什么事。然而
当我成为这些程序代码的"最佳男主角"够久了之后, 我终于渐悟了。

不管单一继承的深度如何, 主循环中用以调用函数的代码事实上是完全相同的; 同样的道理, 对于坐标值的处理也是完全相同的。其间的不同, 同时也是稍早前我没有考虑到的
,就是 cross_product() 中出现的局部性 Point3d class object pC。于是 default Point3d constructor 被调用了 1000 万次。'增加继承深度, 就多增加执
行成本, 这一事实上反映出 pC 身上的 constructor 的复杂度'。这也能够解释为什么多重继承的调用另有一些额外负担。

导入 virtual function 之后, class constructor 将获得参数以设定 virtual table 指针。


// !!  指向 Member Function 的指针(Pointer-to-Member Functions)

取一个 nonstatic data member 的地址, 得到的结果是该 member 在 class 布局中的 bytes 位置(再加 1)。'你可以想象它是一个不完整的值, 它需要被绑定于某
个 class object 的地址上, 才能够被存取'。


'取一个 nonstatic member function 的地址, 如果该函数是 non virtual, 得到的结果是它在内存中真正的地址'。然而这个值也是不完全的。它也需要被绑定于某
个 class object 的地址上, 才能够通过它调用该函数。

所有的 nonstatic member functions 都需要对象的地址(以参数 this 指出)

回顾一下, 一个指向 member function 的指针, 其声明语法如下:

double // return type
(Point::* // class the function is member
pmf)// name of pointer to member
();// argument list

然后我们可以这样定义并初始化该指针:

double (Point::* coord)() = &Point::x;

也可以这样指定其值:

coord =  &Point::x;

欲调用它, 可以这么做:

origin.*coord();

或

ptr->*coord();

指向 member function 的指针的声明语法, 以及指向"member selection 运算符"的指针, 其作用是作为 this 指针的空间保留者。

这也就是为什么 static member functions(没有 this 指针)的类型是"函数指针", 而不是"指向 member function 的指针"之故。

使用一个"member function 指针", 如果并不用于 virtual function、多重继承、virtual base class 等情况的话, 并不会比使用一个"nonmember function
指针"的成本更高。


// !! 支持指向 Virtual Member Functions 的指针

考虑下面的程序片段:

float (Point::* pmf)() = &Point::z;
float *ptr = new Point3d();

pmf, 一个指向 member function 的指针, 被设值为 Point::z() (一个 virtual function) 的地址。

ptr 则被指定以一个 Point3d 对象。如果我们直接经由 ptr 调用 z():

ptr->z();


被调用的是 Point3d::()。但如果我们从 pmf 间接调用 z() 呢?

(ptr->*pmf)();

仍然是 Point3d::z() 被调用吗? 也就是说, '虚拟机制仍然能够在使用"指向 member function 之指针'的情况下运行吗?答案是 yes, 问题是如何实现呢?


在前一小节中, 我们看到了, '对一个 nonstatic member function 取其地址, 将获得该函数在内存中的地址'。然而'面对一个 virtual function, 其地址在编译时
期是未知的, 所能知道的仅是 virtual function 在其相关之 virtual table 中的索引值'。也就是说, 对一个 virtual member function 取其地址, 所能获得的
只是一个索引值。


例如, 假设我们有以下的 Point 声明:

class Point
{
public:
    virtual ~Point();
    float x();
    float y();
    virtual float z();
private:

};

然后取 destructor 的地址:

&Point::~Point;

得到的结果是 1。取 x() 或 y() 的地址:

&Point::x;
&Point::y;

到的则是函数在内存中的地址, 因为它们不是 virtual。

取 z() 的地址:

&Point::z;

得到的结果是 2。

'通过 pmf 来调用 z(), 会被内部转化为一个编译时期的式子', 一般形式如下:

(*ptr->vptr[(int)pmf])(ptr);


对一个 "指向 member function 的指针"评估求值(evaluated), 会因为该值有两种意义而复杂化; 其调用操作也将有别于常规调用操作。pmf 的内部定
义, 也就是:

float(Point::*pmf)();

必须允许此函数能够寻址出 non virtual x() 和 virtual z() 两个 member functions, 而那两个函数有着相同的原型:

float Point()::x() { return x_;}

float Point::z() {return 0;}


只不过其中一个代表内存地址(一长串), 另一个代表 virtual table 中的索引值(一小段)。因此, 编译器必须定义 pmf, 使它能够


1. 持有两种数值

2. 更重要的是其数值可以被区别代表内存地址还是 Virtual table 中的索引值


// !! 4.5 Inline Functions

下面是 Point class 的一个加法运算符的可能实现内容:

class Point {
    friend Point operator+(const Point& p1, const Point& p2);
};


Point operator+(const Point&p1, const Point& p2) {
    Point new_p;
    new_p.x_ = p1.x_ + p2.x_;
    new_p.y_ = p1.y_ + p2.y_;
    return new_p;
}


理论上, 一个比较"干净"的做法是使用 inline 函数来完成 set 和 get 函数:

new_p.x(p1.x() + p2.());

由于我们受限只能在上述两个函数中对 x_ 直接存取, 因此也就将稍后可能发生的 data members 的改变(例如在继承体系中上移或下移)所带来的冲击最小化了。

'如果把这些存取函数声明为 inline, 我们就可以继续保持直接存取 members 的那种高效率---虽然我们亦兼顾了函数的封装性'。

实际上我们并不能够强迫将任何函数都变成 inline。'关键词 inline (或者 class declaration 中的 member function 或 friend function 的定义)
只是一项请求'。如果这项请求被接受, 编译器就必须认为它可以用一个表达式 (expression) 合理地将这个函数扩展开来。

当我说 "编译器相信它可以合理地扩展一个 inline 函数"时, 我的意思是'在某个层次上, 其执行成本比一般的函数调用及返回机制所带来的负荷低'。

cfront 有一套复杂的测试法, 通常是用来计算 assignments、function calls、virtual function calls 等操作的次数。'每个表达式(expression)种类有
一个权值, 而 inline 函数的复杂度就以这些操作的总和来决定'。

一般而言, 处理一个 inline 函数, 有两个阶段:

1. 分析函数定义, 以决定函数的 "intrinsic inline ability"(本质的 inline 能力)

   如果函数因其复杂度, 或因其建构问题, 被判断不可成为 inline, 它会被转为一个 static 函数, 并在"被编译模块"内产生对应的函数定义。在一个支持"模块个别编译"
   的环境中, 编译器几乎没有什么权宜之计。理想情况下, 链接器会将被产生出来的重复东西清理掉。然而一般来说, 目前市面上的链接器并不会将"随此调用而被产生出来的
   重复调试信息"清理掉。

2. 真正的 inline 函数扩展操作是在调用的那一点上, 这会带来参数的求值操作(evaluation)以及临时性对象的管理


// !! 形式参数（Formal Arguments）

'在 inline 扩展期间, 到底真正发生了什么事情'? 

噢,是的, 每一个形式参数都会被对应的实际参数取代。

如果说有什么副作用, 那就是不可以只是简单地一一封塞程序中出现的每一个形式参数, 因为这将导致对于实际参数的多次求值操作(evaluations)。一般而言, 面对
"会带来副作用的实际参数", 通常都需要引入临时性对象。换句话说, 如果实际参数是一个常量表达式(constant expression),我们可以在替换之前先完成其求值操
作(evaluations); 后继的 inline 替换, 就可以把常量直接"绑"上去。如果既不是个常量表达式, 也不是个带有副作用的表达式, 那么就直接代换之。

举个例子, 假设我们有以下的简单 inline 函数:

inline int min(int i, int j) {
    return i < j ? i : j;
}

下面是三个调用操作:

inline int bar() {
    int minVal;
    int v1 = 1021;
    int v2 = 987;

    minVal = min(v1, v2);// 1
    minVal = min(1021,987);// 2
    minVal = min(foo(), bar());// 3
    return minVal;
}

标示为(1) 的那一行会被扩展为:

minVal = v1 < v2 ? v1 : v2;

标示为(2) 的那一行直接拥抱常量:

minVal = 987;

标示为 (3) 的那一行则引发参数的副作用。它需要导入一个临时性对象, 以避免重复求值(multiple evaluations):

int t1;
int t2;
t1 = foo();
t2 = bar();

minVal = t1 < t2 ? t1 : t2;

// !! 局部变量（Local Variables）

如果我们轻微地改变定义, 在 inline 定义中加入一个局部变量, 会怎样?

inline int minVal(int i, int j){
    int minVal = i < j ? i : j;
    return minVal;
}


这个局部变量需要什么额外的支持或处理吗? 如果我们有以下的调用操作:

{
    int local_var;
    int minVal;
    //...
    minVal = min(v1, v2);
}

inline 被扩展开来后, 为了维护其局部变量, 可能会成为这个样子(理论上这个例子中的局部变量可以被优化, 其值可以直接在 minVal 中计算):

{
    int local_var;
    int minVal;
    int _min_lv_min_value;
    minVal = (_min_lv_min_value = v1 < v2 ? v1 : v2,_min_lv_min_value);
}