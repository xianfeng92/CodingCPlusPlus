
// !! Function语意学（The Semantics of Function）

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

答案是: 我不知道~ C++ 支持三种类型的 member functions: static、nonstatic 和 virtual, 每一种类型被调用的方式都不相同。


不过, 我们虽然不能够确定 normalize() 和 magnitude() 两函数是否为 virtual 或 nonvirtual, 但可以确定它一定不是 static, 原因有二:

1. 它直接存取 nonstatic 数据

2. 它被声明为 const。是的, static member functions 不可能做到这两点。



// !! Member 的各种调用方式

回顾历史, 原始的 C with Classes 只支持 nonstatic member functions。Virtual 函数是在20世纪80年代中期被加进来的, 并且很显然受到许多质疑
(许多质疑至今在 C 族群中仍然存在)。Bjarne 写道:

'有一种常见的观点, 认为 virtual functions 只不过是一种跛脚的函数指针, 没什么用……其意思主要就是, virtual functions 是一种没有效能的形式'。


Static member functions 是最后被引入的一种函数类型。它们在 1987 年的 Usenix C++ 研讨会的厂商研习营中被正式提议加入这个语言, 并由 cfront 2.0 
实现出来。


// !! Nonstatic Member Functions（非静态成员函数）

C++ 的设计准则之一就是: 'nonstatic member function 至少必须和一般的 nonmember function 有相同的效率'。也就是说, 如果我们要在以下两个函数之间做
选择:

float magnitude3d(){}

float Point3d::magnitude3d(){}

选择 member function 不应该带来什么额外负担。'这是因为编译器内部已将 member 函数实例转换为对等的 nonmember函数实例'。


举个例子, 下面是 magnitude() 的一个 nonmember 定义:

float magnitude3d(const Point3d& point)
{
    return (point_x * point.x_ + point.y_ * point.y_ + point.z_ * point.z_);
}

乍见之下似乎 nonmember function 比较没有效率, 它间接地经由参数取用坐标成员, 而 member function 却是直接取用坐标成员。然而实际上
member function 被内化为 nonmember 的形式。下面就是转化步骤:

1. '改写函数的 signature(函数原型)以安插一个额外的参数到 member function 中, 用以提供一个存取管道, 使 class object 得以将此函数调用'。该额外参数
    被称为 this 指针:

    // 如果 member function 是 non const, 则变成:
    Point3d Point3d::magnitude(Point3d* const this)
    {
        //...
    }

    // 如果 member function 是 const, 则变成:

    Point3d Point3d::magnitude(const Point3d* const this)
    {
        //...
    }

2. 将每一个'对 nonstatic data member 的存取操作'改为经由 this 指针来存取:

    {
        return (sqrt(this->x_ * this->x_ + this.y_ * this.y_ + this.z_ * this.z_));
    }


3. 将 member function 重新写成一个外部函数。将函数名称经过"mangling"处理, 使它在程序中成为独一无二的语汇:

    extern magnitude_7Point3dFv(register Point3d * const this);

现在这个函数已经被转换好了, 而其每一个调用操作也都必须转换。于是:

obj.magnitude();

变成了:

magnitude_7Point3dFv(&obj);


而:

ptr->magnitude();

变成了:

magnitude_7Point3dFv(ptr);


本章一开始所提的 normalize() 函数会被转化为下面的形式, 其中假设已经声明有一个 Point3d copy constructor, 而 named returned value(NRV) 的优化
也已施行:


void normalize_7Point3dFv(register const Point3d * const this, Point3d _result){
    register float mag = magnitude();
    _result.Point3d::Point3d();
    _result.x_ = this->x_ / mag;
    _result.y_ = this->y_ / mag;
    _result.z_ = this->z_ / mag;
    return;
}


一个比较有效率的做法是直接建构"normal"值, 像这样:


Point3d Point3d::normalize() const
{
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

一般而言, member 的名称前面会被加上 class 名称, 形成独一无二的命名。例如下面的声明:


class Bar{
    public:
        int ival;
        //...
};


其中的 ival 有可能变成这样:

ival_3Bar;

为什么编译器要这么做 ? 请考虑这样的派生操作(derivation):

class Foo : public Bar{public: int ival;};

记住, Foo 对象内部结合了 base class 和 derived class 两者:


// C++ 伪代码

class Foo{
    public:
        int ival_3Bar;
        int ival_3Foo;
};

不管你要处理哪一个 ival, 通过"name mangling", 都可以绝对清楚地指出来。由于 member functions 可以被重载化(overloaded), 所以需要更广泛的
 mangling 手法, 以提供绝对独一无二的名称。如果把:


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

 会导致两个被重载化(overloaded) 的函数实例拥有相同的名称。为了让它们独一无二, 唯有再加上它们的参数链表(可以从函数原型中参考得到)。如果把参数类型也编码进
 去, 就一定可以制造出独一无二的结果, 使我们的两个 x() 函数有良好的转换(但如果你声明 extern "C", 就会压抑 nonmember functions 的"mangling"效果)


 class Point{
    public:
        void x_5Point_Ff(float newX);
        float x_5Point_Fv();
 }

 以上所示只是 cfront 采用的编码方法。我必须承认, 目前的编译器并没有统一的编码方法——虽然不断有一些活动企图导引出这方面的一个工业标准。'C++ 编译器对
 name mangling 的做法目前还没有统一, 但我们知道它迟早会统一'。


'把参数和函数名称编码在一起, 编译器于是在不同的被编译模块之间达成了一种有限形式的类型检验'。

举个例子, 如果一个print函数被这样定义:

void print(const Point3d& ){...}

但意外地被这样声明和调用:

void print(const Point3d);

两个实例如果拥有独一无二的 name mangling, 那么任何不正确的调用操作在链接时期就因无法决议(resolved) 而失败。有时候我们可以乐观地称此为"确保类型安全的链
接行为"(type-safe linkage)。我说"乐观地"是因为它只可以捕捉函数的标记(signature, 亦即函数名称+参数个数+参数类型）错误; 如果"返回类型"声明错误,就没办
法检查出来!


在目前的编译系统中, 有一种所谓的 demangling 工具, 用来拦截名称并将其转换回去。使用者可以仍然处于"不知道内部名称"的极大幸福之中。然而生命并不是长久以来一直
如此轻松, 在 cfront 1.1 版中, 由于该系统未经世故, 因此总是收藏两种名称(未经 mangled 和经过 mangled 的两种名称); 编译错误消息用的是程序源码函数名称,
然而链接器却不, 它用的是经过 mangled 的内部名称。


// !! Virtual Member Functions（虚拟成员函数）

如果 normalize() 是一个 virtual member function, 那么以下的调用:

ptr->normalize();

将会被内部转化为:

(*prt->vptr[1:])(ptr);

其中:

1. vptr 表示由编译器产生的指针, 指向 virtual table。它被安插在每一个"声明有(或继承自)一个或多个 virtual functions"的 class object 中。事实上其
   名称也会被"mangled", 因为在一个复杂的 class 派生体系中, 可能存在多个 vptrs。

2.  1 是 virtual table slot 的索引值, 关联到 normalize() 函数

3.  第二个 ptr 表示 this 指针

类似的道理, 如果 magnitude() 也是一个 virtual function, 它在 normalize()  之中的调用操作将被转换如下:


register float mag = (*this->vptr[2])(this);


此时, 由于 Point3d::magnitude() 是在 Point3d::normalize() 中被调用的, 而后者已经由虚拟机制而决议(resolved)妥当, 所以显式地调用"Point3d 实例"会
比较有效率, 并因此压制由于虚拟机制而产生的不必要的重复调用操作:

register float mag = Point3d::magnitude();


如果 magnitude() 声明为 inline 函数, 会更有效率。使用 class scope operator 显式调用一个 virtual function, 其决议(resolved) 方式会和
nonstatic member function 一样:

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

这个 this 指针把"在 member function 中存取的 nonstatic class members"绑定于"object 内对应的 members"之上。'如果没有任何一个 members 被直
接存取, 事实上就不需要 this 指针, 因此也就没有必要通过一个 class object 来调用一个 member function'。不过 C++ 语言到目前为止并不能够辨识这种情况。

独立于 class object 之外的存取操作, 在某个时候特别重要: '当 class 设计者希望支持"没有 class object 存在"的情况(就像前述的 object_count() 那样)
时。程序方法上的解决之道是很奇特地把 0 强制转换为一个 class 指针',因而提供出一个 this 指针实例:


object_count((Point3d*)0);


至于语言层面上的解决之道, 是由 cfront 2.0 所引入的 static member functions。'Static member functions 的主要特性就是它没有 this 指针'。以下的
次要特性统统根源于其主要特性:

1. 它不能够直接存取其 class中的 nonstatic members

2. 它不能够被声明为 const、volatile 或 virtual

3. 它不需要经由 class object 才被调用——虽然大部分时候它是这样被调用的

"member selection" 语法的使用是一种符号上的便利, 它会被转化为一个直接调用操作:


if(Point3d::object_count() > 1){}

如果 class object 是因为某个表达式而获得的, 会如何? 例如:

if(foo().object_count() > 1){}

噢, 这个表达式仍然需要被评估求值(evaluated):

(void)foo();
if(Point3d::object_count() > 1){}


