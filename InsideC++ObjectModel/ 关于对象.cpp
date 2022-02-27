// !! 关于对象

在 C 语言中, "数据"和"处理数据的操作(函数)" 是分开来声明的, 也就是说, 语言本身并没有支持"数据和函数"之间的关联性。

我们把这种程序方法称为程序性的(procedural), 由一组"分布在各个以功能为导向的函数中"的算法所驱动, 它们处理的是共同的外部数据。

举个例子, 如果我们声明一个 struct Point3d , 像这样:

typedef struct point3d
{
    float x;
    float y;
    float z;
} Point3d;

欲打印一个 Point3d, 可能就得定义一个像这样的函数:

void Point3d_print(const Point3d& point)
{
    cout << point.x << ", " << point.y << point.z << endl;
}

或者, 如果要更有效率一些, 就定义一个宏:

#define Point3d_print(const Point3d& point)
        cout << point.x << ", " << point.y << point.z << endl;


抑或是直接在程序中完成其操作:

void my_foo()
{
    Point3d* pd = get_a_point();
    ...
     cout << pd->x << ", " << pd->y << pd->z << endl;
}

同样的道理, 某个点的特定坐标值可以直接存取:

Point3d pt;
pt.x = 100;
pt.y = 12;


也可以经由一个前置处理宏来完成:

#define X(p, val) (p.x) = (val)
...

x(pt,100);


在 C++ 中, Point3d 有可能采用独立的"抽象数据类型(abstract data type,ADT)" 来实现:

class Point3d
{
public:
    Point3d(float x = 0.0, float y = 0.0, float z = 0.0):x_(x), y_(y),z_(x)
    {

    }

    float x() const { return x_; }

    float y() const { return y_; }

    float z() const { return z_; }

    void x(float val)
    {
        x_ = val;
    }

    void y(float val)
    {
        y_ = val;
    }

    void z(float val)
    {
        z_ = val;
    }

private:
    float x_;
    float y_;
    float z_;
};


inline ostream& operator<<(ostream& os, const Point3d& point)
{
    os << point.x << ", " << point.y << point.z << endl;
}


或是'以一个双层或三层的 class 层次结构完成':


class Point
{
public:
    Point(float x = 0.0): x_(x){}

    float x() const { return x_}

    void x(float val)
    {
        x_ = val;
    }
protected:
    float x_;
};


class Point2d : public Point
{
public:
    Point2d(float x = 0.0, float y = 0.0):Point(x), y_(y)
    {

    }

    float y() const { return y_};
    void y(float val)
    {
        y_ = val;
    }

protected:

    float y_;
};


class Point3d : public Point2d
{

public:

    Point3d(float x = 0.0, float y = 0.0, float z = 0.0):Point2d(x,y), z_(z)
    {

    }

    float z() const { return z_};

    void z(float val)
    {
        z_ = val;
    }

protected:

    float z_;
};



更进一步来说, 不管哪一种形式, 它们都可以被参数化。可以是坐标类型的参数化:


template<typename type>
class Point3d
{
public:
    Point3d(type x, type y, type z):x_(x), y_(y), z_(z)
    {

    }

    type x() const { return x_; }

    void x(type val)
    {
        x_ = val;
    }
    // ...
private:
    type x_;
    type y_;
    type z_;
};

也可以是坐标类型和坐标个数两者都参数化:

template<typename type, int dim>
class Point
{
public:
    Point(type coords[dim])
    {
        for(int i = 0; i< dim; i++)
        {
            coords_[i] = coords[i];
        }
    }


    type& operator[](int index)
    {
        return coords_[index];
    }

    type operator[](int index) const
    {
        return coords_[i];
    }

private:
    type coords_[dim];
};

inline template<typename type, int dim>
ostream& operator<<(ostream& os, const Point<type, int>& pt)
{
    for(int i = 0; i < dim - 1; i++)
    {
        os << pt[i] << ' ,';
    }
    os << pt[dim - 1];
}


很明显, 不只在程序风格上有显著的不同, 在程序的思考上也有明显的的差异。有许多令人信服的讨论告诉我们, 从软件工程的眼光来看, 为什么"一个 ADT 或 
class hierarchy 的数据封装" 比 "在 C 程序中程序性地使用全局数据" 好。但是这些讨论往往被那些"被要求快速让一个应用程序上马应战, 并且执行起来又快
又有效率" 的程序员所忽略。'毕竟 C 的吸引力就在于它的精瘦和简易'(相对于 C++ 而言)。


'在 C++ 中实现 3D 坐标点, 比在 C 中复杂, 尤其是使用 template 的情况下'。但这并不意味着 C++ 就不更有威力, 或是(唔,从软件工程的眼光来看)更好。
当然啦, 更有威力或是更好, 也不意味着使用上就更容易。



// !! 加上封装后的布局成本（Layout Costs for Adding Encapsulation）

程序员看到 Point3d 转换到 C++ 之后, 第一个可能会问的问题就是: '加上了封装之后, 布局成本增加了多少'?

答案是 class Point3d 并没有增加成本。

1. 三个 data members 直接内含在每一个 class object 之中, 就像 C struct 的情况一样

2. 而 member functions 虽然含在 class 的声明之内, 却不出现在 object 之中

3. 每一个 non-inline member function 只会诞生一个函数实例

4. 至于每一个"拥有零个或一个定义" 的 inline function 则会在其每一个使用者(模块) 身上产生一个函数实例。Point3d 支持封装性质, 这一点并未带给它任
    何空间或执行期的不良后果


你即将看到, C++ 在布局以及存取时间上主要的额外负担是由 virtual 引起的, 包括:

1. virtual function 机制 用以支持一个有效率的"执行期绑定"(runtime binding)

2. virtual base class 用以实现多次出现在继承体系中的 base class, 有一个单一而被共享的实例

此外还有一些多重继承下的额外负担, 发生在一个 derived class 和其第二或后继之 base class 的转换之间。然而, 一般而言, 并没有什么天生的理由说 C++
 程序一定比其 C 兄弟庞大或迟缓。


// !! C++对象模式（The C++ Object Model）

// !! 加上封装后的布局成本（Layout Costs for Adding Encapsulation）

在 C++ 中, 有两种 class data members: static 和 nonstatic, 以及三种 class member functions: static、nonstatic 和 virtual。


class Point
{
public:
    Point(float val);
    virtual ~Point();

    float x() const;
    static int PointCount();

private:
    virtual ostream& operator<<(ostream& os, const Point& p);
    float x_;
    static int point_count_;
};

这个 class Point 在机器中将会被怎么样表现呢 ? 也就是说, 我们如何模塑(modeling) 出各种 data members 和 function members 呢 ?


// !! 简单对象模型（A Simple Object Model）

我们的第一个模型十分简单。它可能是为了尽量减低 C++ 编译器的设计复杂度而开发出来的, 赔上的则是空间和执行期的效率。

在这个简单模型中, 一个 object 是一系列的 slots, 每一个 slot 指向一个 members。Members 按其声明顺序, 各被指定一个 slot。

每一个 data member 或 function member 都有自己的一个 slot。

在这个简单模型下, members 本身并不放在 object 之中。只有指向 member 的指针才放在 object 内。这么做可以避免 members 有不同的类型, 因而需
要不同的存储空间所招致的问题。

Object 中的 members 是以 slot 的索引值来寻址, 本例之中 _x 的索引是 6, _point_count 的索引是是 7。

一个 class object 的大小很容易计算出来: 指针大小, 乘以 class 中所声明的 members 个数便是。

虽然这个模型并没有被应用于实际产品上, 不过关于索引或 slot 个数的观念, 倒是被应用到 C++ 的指向成员的指针(pointer-to-member)观念之中


// !! 表格驱动对象模型（A Table-driven Object Model）

为了对所有 classes 的所有 objects 都有一致的表达方式, 另一种对象模型是把所有与 members 相关的信息抽出来, 放在一个 data member table 和一个
member function table 之中, class object 本身则内含指向这两个表格的指针。

Member function table 是一系列的 slots, 每一个 slot 指出一个 member function; Data member table 则直接持有 data 本身。

虽然这个模型也没有实际应用于真正的 C++ 编译器身上,但 member function table 这个观念却成为支持 virtual functions 的一个有效方案。



// !! C++ 对象模型（The C++ Object Model）

Stroustrup 当初设计(目前仍占有优势)的 C++ 对象模型是从简单对象模型派生而来的, 并对内存空间和存取时间做了优化。

在此模型中:

1. 'nonstatic data members 被配置于每一个 class object 之内', static data members 则被存放在 class object 之外

2. static 和 nonstatic function members 也被放在 class object 之外

3. virtual functions 则以两个步骤支持之:

   a: 每一个 class 产生出一堆指向 virtual functions 的指针, 放在表格之中。这个表格被称为 virtual table(vtbl)

   b: 每一个 class object 被安插一个指针, 指向相关的 virtual table。通常这个指针被称为 vptr。 vptr 的设定(setting)和重置(resetting) 都由每一个
      class 的 constructor、destructor 和 copy assignment 运算符自动完成。每一个 class 所关联的 type_info object(用以支持 runtime type 
      identification, RTTI) 也经由 virtual table 被指出来, 通常放在表格的第一个 slot


这个模型的主要优点在于它的空间和存取时间的效率; 主要缺点则是, 如果应用程序代码本身未曾改变, 但所用到的 class objects 的 nonstatic data members 有所
修改(可能是增加、移除或更改), 那么那些应用程序代码同样得重新编译。

关于此点,前述的双表格模型就提供了较大的弹性, 因为它多提供了一层间接性, 不过它也因此付出了空间和执行效率两方面的代价。

// !! 加上继承(Adding Inheritance)

C++ 支持单一继承:

class Point{};

class Point2d : public Point{};

C++ 也支持多重继承:

class iostream : public ostream, public istream{};

甚至, 继承关系也可以指定为虚拟(virtual, 也就是共享的意思):

class istream : virtual public ios{};

class ostream : virtual public ios{};

在虚拟继承的情况下, base class 不管在继承串链中被派生(derived) 多少次, 永远只会存在一个实例(称为 subobject)。例如 iostream 之中就只有
virtual ios base class 的一个实例。

一个 derived class 如何在本质上模塑其 base class 的实例呢 ?

在简单对象模型中, 每一个 base class 可以被 derived class object 内的一个 slot 指出, 该 slot 内含 base class subobject 的地址。这个体制的主要
缺点是, 因为间接性而导致的空间和存取时间上的额外负担, 优点则是 class object 的大小不会因其 base classes 的改变而受到影响。

当然啦, 你也可以想象另一种所谓的 base table 模型。这里所说的 base class table 被产生出来时, 表格中的每一个 slot 内含一个相关的 base class 地址, 
这很像 virtual table 内含每一个 virtual function 的地址一样。每一个 class object 内含一个 bptr, 它会被初始化, 指向其 base class table。
这种策略的主要缺点是由于间接性而导致的空间和存取时间上的额外负担, 优点则是在每一个 class object 中对于继承都有一致的表现方式: 每一个 class object 
都应该在某个固定位置上安放一个 base table 指针, 与 base classes 的大小或个数无关。第二个优点是, 无须改变 class objects 本身, 就可以放大、缩小, 或
更改 base class table。

不管上述哪一种体制, 间接性的级数将因为继承的深度而增加。

例如, 一个 Rental_book 需要两次间接存取才能够探取到继承自 Library_materials 的 members, 而 Book 只需要一次。

如果在 derived class 内复制一个指针, 指向继承串链中的每一个 base class, 倒是可以获得一个永远不变的存取时间。当然这必须付出代价, 因为需要额外的空间来
放置额外的指针。

C++ 最初采用的继承模型并不运用任何间接性: base class subobject 的 data members 被直接放置于 derived class object 中。这提供了对 
base class members 最紧凑而且最有效率的存取。缺点呢 ? 当然就是: base class members 的任何改变, 包括增加、移除或改变类型等等, 都使得所有用到
"此 base class 或其 derived class 之 objects" 者必须重新编译。


自 C++2.0 起才新导入的 virtual base class, 需要一些间接的 base class 表现方法。virtual base class 的原始模型是在 class object 中为每一个有关
联的 virtual base class 加上一个指针。其他演化出来的模型则要不是导入一个 virtual base class table, 就是扩充原已存在的 virtual table, 以便维护每
一个 virtual base class 的位置。


// !! 对象模型如何影响程序（How the Object Model Effects Programs）

这对程序员带来什么意义呢 ? 喔, 不同的对象模型, 会导致"现有的程序代码必须修改"以及 "必须加入新的程序代码" 两个结果。

例如下面这个函数, 其中 class X 定义了一个 copy constructor、一个 virtual destructor 和一个 virtual function foo:

X foobar() 
{
    X xx;
    X* px = new X();

    // foo 是一个 virtual function
    xx.foo();
    px->foo();

    delete px;
    
    return xx;
}

这个函数有可能在内部被转化为:

// 可能的内部转换结果
// 虚拟 C++ 代码

void foobar(X& _result)
{
    // 构造 _result
    // _result 用来取代 local xx
    _result.X::X();

    // 扩展 X* px = new X();
    px = _now(sizeof(X));
    if(px != 0)
    {
        px->X::X();
    }

    // 扩展 xx.foo() 但不使用 virtual 机制
    // 以 _result 取代 xx
    foo(&_result);

    // 使用 virtual 机制扩展 px->foo() 
    (*px->vtbl[2])(px);

    // 扩展 delete px
    if(px != 0)
    {
        (*px->vtbl[1])(px);// destructor
        _delete(px);
    }

    // 无需使用 named return statement
    // 无需摧毁 local object xx
    return;
}


喔, 真是差异颇大, 不是吗! 当然, 此刻你并不需要了解所有的转化过程及结果。我会在后继章节解释其中每一个操作的用意, 以及为什么那么做。我想你会回头看,
一边玩弄你的手指头, 一边说 喔欧,是的,当然, 同时奇怪你怎么会曾经迷惘过。


// !! 关键词所带来的差异（A Keyword Distinction）

