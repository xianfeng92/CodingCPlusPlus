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

如果不是为了努力维护与 C 之间的兼容性, C++ 远可以比现在更简单些。

举个例子, 如果没有 8 种整数需要支持的话, overloaded function 的解决方式将会简单得多。同样道理, 如果 C++ 丢掉 C 的声明语法, 就不需要花脑筋去判断下面
这一行其实是 pf 的一个函数调用操作(invocation) 而不是其声明:

// 不知道下面是个声明还是函数调用
// 直到看到整数常量 1024 才能决定
int(*pf)(1024);

而在下面这个声明中, 像上面那样的 向前预览(lookahead) 甚至起不了作用:

// pf 是一个声明而不是调用
int(*pf)();

当语言无法区分那是一个声明还是一个表达式(expression) 时, 我们需要一个超越语言范围的规则, 而该规则会将上述式子判断为一个"声明"。


同样地, 如果 C++ 并不需要支持 C 原有的 struct, 那么 class 的观念可以借由关键词 class 来支持。但绝对令你惊讶的是, 从 C 迁徙到 C++, 除了效率, 
另一个最常被程序员询问的问题就是:什么时候一个人应该在 C++ 程序中以 struct 取代 class ?


// !! 关键词的困扰

那么, 让我重新问一次: 什么时候一个人应该使用 struct 取代 class ?  答案之一是: 当它让一个人感觉比较好的时候。

虽然这个答案并没有达到高技术水平, 但它的确指出了一个重要的特性: 关键词 struct 本身并不一定要象征其后随之声明的任何东西。我们可以使用 struct 代替 class,
但仍然声明 public、protected、private 等等存取区段与一个完全 public 的接口, 以及 virtual functions 和单一继承、多重继承、虚拟继承……早期, 似乎每个
人都得在一小时的 C++ 简介中花费整整 10 分钟看清楚以下两者的相同:

class c_plusplus_keyword
{
public:
// number
};

和其 C 对等品:

struct c_keyword
{
// the same number
};

当人们以及在教科书中说到 struct 时, 他们的意思是一个数据集合体, 没有 private data, 也没有 data 的相应操作。亦即纯然的 C 用法。这种用途应该和 C++
的"使用者自定义类型"(user-defined type) 用法区别开来。

在 C 这一边, 这个关键词的设计理由因其用法而存在; 而在 C++ 那一边, 选择 struct 或 class 作为关键词, 并用以导入 ADT 的理由, 是希望从此比较健全。这
远比讨论函数需不需要一个大括号, 或是要不要在变量名称和类型名称中使用下画线(例如 IsRight 或 is_right) 更具精神层次。

在 C 所支持的 struct 和 C++ 所支持的 class 之间, 有一个观念上的重要差异。我的重点很简单: 关键词本身并不提供这种差异。也就是说, 如果一个人拥有下面的
C++ 使用者自定义类型, 他可以说喔, 那是一个 class:

// struct 名称或者 class 名称暂时省略
{
public:
    operator int();
    virtual void foo();
    //...
protected:
    static int number_count;
    ...
};


事实上你可以说上面那东西是个 struct, 也可以说它是个 class。这两种声明的观念上的意义取决于对“声明”本身的检验。

举个例子, 在 cfront 之中, 上述两个关键词在语意分析器(parser) 中是以共享的 AGGR 替换的。而在 Foundation 项目中, Rob Murray的 ALF 层次结构保留了程
序员真正使用的关键词。然而这份信息并未在更内层的编译器中被使用, 倒是可以被一个 unparser 工具用来还原程序的 ASCII 面貌。

你可能会争辩说, 如果这个语言只支持一个关键词, 可以省掉许多混淆与迷惑。但你要知道, 如果 C++ 要支持现存的 C 程序代码, 它就不能不支持 struct。

好的, 那么它需要引入新的关键词 class 吗 ? 真的需要吗 ? 不 ! 但引入它的确非常令人满意, 因为这个语言所引入的不只是关键词, 还有它所支持的封装和继承的哲学。

你甚至可以主张说它的用途只是为了方便 C 程序员迁徙至 C++ 部落。


// !! 策略性正确的 struct（The Politically Correct Struct）

C 程序员的巧计有时候却成为 C++ 程序员的陷阱。例如把单一元素的数组放在一个 struct 的尾端, 于是每个 struct objects 可以拥有可变大小的数组:

struct mumble
{
// stuff
char pc[1];
};

// 从文件或者标准输入中取得一个字符串
// 然后为 struct 本身和这个字符串分配足够的空间

struct mumble* p1 = (numble*)malloc(sizeof(struct mumble) + strlen(string) + 1);

strcpy(&numble.pc, string);

如果我们改用 class 来声明, 而该 class 是:

1. 指定多个 access sections

2. 内含数据

3. 从另一个 class派生而来

4. 定义了一个或多个 virtual functions

那么或许可以顺利转化, 但也许不行!

C++ 中凡处于同一个 access section 的数据, 必定保证以其声明顺序出现在内存布局当中。然而被放置在多个 access sections 中的各笔数据, 排列顺序就不一定了。
在下面的声明中, 前述的 C 伎俩或许可以有效运行, 或许不能, 需视 protected data members 被放在 private data members 的前面或后面而定(译注:放在前面
才可以):



组合(composition), 而非继承, 才是把 C 和 C++ 结合在一起的唯一可行方法:


struct C_point{};

class Point
{
public:
    operator C_point(){return c_point;}
private:
    C_point c_point;
};


C struct 在 C++ 中的一个合理用途, 是当你要传递一个复杂的 class object 的全部或部分 到某个 C 函数去时, struct 声明可以将数据封装起来,
并保证拥有与 C 兼容的空间布局。然而这项保证只在组合(composition) 的情况下才存在。


// !! 对象的差异（An Object Distinction）

C++ 程序设计模型直接支持三种 programming paradigms(程序设计范式):

1. 程序模型(procedural model)。就像 C一样, C++ 当然也支持它。字符串的处理就是一个例子, 我们可以使用字符数组以及 str* 函数族群(定义在标准的 C 函数库中)

char boy[] = "Danny";
char * p_son;

p_son = new char[strlen(boy) + 1];
strcpy(p_son, boy);

2. 抽象数据类型模型(abstract data type model, ADT)。'此模型所谓的抽象是和一组表达式(public 接口)一起提供的',那时其运算定义仍然隐而未明。

string girl = "xforg";
string daughter;
...
// string::operator=()
daughter = girl;

...
// string::operator==()
if(daughter == girl)
{

}


3. 面向对象模型(object-oriented model)。在此模型中有一些彼此相关的类型, 通过一个抽象的 base class(用以提供共同接口)被封装起来


在 OO paradigm 之中, 程序员需要处理一个未知实例, 它的类型虽然有所界定, 却有无穷可能。这组类型受限于其继承体系, 然而该体系理论上没有深度和广度的限制。
原则上, 被指定的 object 的真实类型在每一个特定执行点之前, 是无法解析的。在 C++ 中, 只有通过 pointers 和 references 的操作才能够完成。相反地,在
ADT paradigm 中, 程序员处理的是一个拥有固定而单一类型的实例, 它在编译时期就已经完全定义好了。

虽然对于 object 的多态操作要求此 object 必须可以经由一个 pointer 或 reference 存取, 然而 C++ 中的 pointer 或 reference 的处理却不是多态的必要
结果。想想下面的情况:

int *pi;// 没有多态，因为操作对象不是 class object

void *pv;// 没有语言所支持的多态

X *px;// okay

在 C++, 多态只存在于一个个的 public class 体系中。举个例子, px 可能指向某个类型的 object, 或指向根据 public 继承关系派生而来的一个子类型
。Nonpublic 的派生行为以及类型为 void* 的指针可以说是多态的, 但它们并没有被语言明确地支持, 也就是说它们必须由程序员通过显式的转换操作来管理。



C++ 以下列方法支持多态:

1. 经由一组隐式的转化操作。例如把一个 derived class 指针转化为一个指向其 public base type 的指针:

shared *ps = new Cycle();

2. 经由 virtual function 机制

ps->retate();

3. 经由 dynamic_cast 和 typeid 运算符

if(cycle *pc = dynamic_cast<cycle*>(ps))
{

}

'多态的主要用途是经由一个共同的接口来影响类型的封装, 这个接口通常被定义在一个抽象的 base class 中'。


需要多少内存才能够表现一个 class object ? 一般而言要有:

1. 其 nonstatic data members 的总和大小

2. 加上任何由于 alignment 的需求而填补(padding) 上去的空间

3. 加上为了支持 virtual 而由内部产生的任何额外负担(overhead)

// !! 一个指针, 不管它指向哪一种数据类型, 指针本身所需的内存大小是固定的


// !! 指针的类型（The Type of a Pointer）

一个指向 ZooAnimal 的指针是如何地与一个指向整数的指针或一个指向 template Array 的指针有所不同呢?

ZooAnimal *pz;
int *pi;
Array<string> *pa;

以内存需求的观点来说, 没有什么不同! 它们三个都需要有足够的内存来放置一个机器地址 (通常是个 word )。

指向不同类型之各指针间的差异, 既不在其指针表示法不同, 也不在其内容(代表一个地址)不同, 而是在其所寻址出来的 object 类型不同。
// !! 也就是说, 指针类型会教导编译器如何解释某个特定地址中的内存内容及其大小。

1.  一个指向地址 1000 的整数指针, 在 32 位机器上,将'涵盖地址空间' 1000~1003(因为 32 位机器上的整数是 4-bytes)

2.  如果 string 是传统的 8-bytes (包括一个 4-bytes 的字符指针和一个用来表示字符串长度的整数), 那么一个 ZooAnimal 指针将横跨地址空间 1000~1015
    (4+8+4)


嗯, 那么, 一个指向地址 1000 而类型为 void* 的指针, 将涵盖怎样的地址空间呢 ?

是的, 我们不知道! 这就是为什么一个类型为 void* 的指针只能够持有一个地址, 而不能够通过它操作所指之 object 的缘故。


所以, '转换 (cast) 其实是一种编译器指令'。大部分情况下它并不改变一个指针所含的真正地址,它只影响"被指出之内存的大小和其内容" 的解释方式。


// !! 加上多态之后（Adding Polymorphism）


现在, 让我们定义一个 Bear, 作为一种 ZooAnimal。当然, 经由 "public 继承"可以完成这项任务:


class Bear: public ZooAnimal
{
public:
    Bear();
    ~Bear();
    //..
    void rotate();
    virtual void dance();
    //...
protected:
    enum Dances{};
    Dances dance_known;
    int cell_book;
};


Bear b("Yogi");
Bear *pb = &b;
Bear &rb = *pb;

b、pb、rb 会有怎样的内存需求呢 ?

不管是 pointer 或 reference 都只需要一个 word 的空间(在 32 位机器上是 4-bytes)。Bear object 需要 24 bytes, 也就是 ZooAnimal 的 16 bytes 
加上 Bear 所带来的 8 bytes。

好, 假设我们的 Bear object 放在地址 1000 处, 一个 Bear 指针和一个 ZooAnimal 指针有什么不同?


Bear b;
ZooAnimal *pz = &b;
Bear *pb = &b;

'它们每个都指向 Bear object 的第一个 byte'。其间的差别是, pb 所涵盖的地址包含整个 Bear object, 而 pz 所涵盖的地址只包含 Bear object 中的 
ZooAnimal subobject。

 
除了 ZooAnimal subobject 中出现的 members, 你不能够使用 pz 来直接处理 Bear 的任何 members。


pz->cell_book; // 不合法,cell_book 不是 ZooAnimal 的一个 member; 虽然我们知道 pz 现在指向一个 Bear Object

(static_cast<Bear *>(pz))->cell_book;// ok:经过一个显示 downcast 就没问题了

// 下面的会更好，但它是一个 rumtime-operation, 成本较高

if(Bear *bp2 = dynamic_cast<Bear *>(pz))
{
    bp2->cell_book;
}


当我们写:

pz->rotate();

时, pz 的类型将在编译时期决定以下两点:

1. 固定的可用接口。也就是说, pz 只能够调用 ZooAnimal 的 public 接口

2. 该接口的 access level (例如 rotate() 是 ZooAnimal 的一个 public member)

在每一个执行点, pz 所指的 object 类型可以决定 rotate() 所调用的实例。'类型信息的封装并不是维护于 pz 之中, 而是维护于 link 之中, 此 link 存在于
"object 的 vptr" 和"vptr 所指的 virtual table"之间'


现在, 请看以下这种情况:

Bear b;
ZooAnimal za = b;// 这样会引起切割(sliced)
za.rotate();// 调用 ZooAnimal::rotate()

为什么 rotate() 所调用的是 ZooAnimal 实例而不是 Bear 实例 ? 此外, 如果初始化函数(应用于上述 assignment 操作发生时) 将一个 object 内容完整拷贝到
另一个 object 去, 为什么 za 的 vptr 不指向 Bear 的 virtual table ?

1. 第二个问题的答案是, 编译器在初始化(1)及指定(2)(assignment)操作(将一个 class object 指定给另一个 class object) 之间做出了仲裁。编译器必须确保如
   果某个 object 含有一个或一个以上的 vptrs, 那些 vptrs 的内容不会被 base class object 初始化或改变。

2. 至于第一个问题的答案是: za 并不是一个 Bear, 它是一个 ZooAnimal。'多态所造成的"一个以上的类型"的潜在力量, 并不能够实际发挥在"直接存取 objects"这件
   事情上'。有一个似是而非的观念: OO 程序设计并不支持对 object 的直接处理。
   
   举个例子, 下面这一组定义:

   {
       ZooAnimal za;
       ZooAnimal *pza;
       Bear b;
       Panda *pp = new Panda();
       pza = &b;
   }

   其可能的内存布局:


1. 将 za 或 b 的地址, 或 pp 所含的内容(也是个地址), 指定给 pza, 显然不是问题。'一个 pointer 或一个 reference 之所以支持多态, 是因为它们并不引发
   内存中任何"与类型有关的内存委托操作(type-dependent commitment)"'; 会受到改变的, 只有它们所指向的内存的"大小和内容解释方式"而已。

2. 然而, 任何人如果企图改变 object za 的大小, 会违反其定义中受契约保护的"资源需求量"。如果把整个 Bear object 指定给 za, 则会溢出它所配置得到的内存。
   执行结果当然也就不对了。

3. 当一个 base class object 被直接初始化为(或是被指定为)一个 derived class object 时, derived object 就会被切割(sliced) 以塞入较小的 
   base type 内存中, derived type 将没有留下任何蛛丝马迹。多态于是不再呈现, 而一个严格的编译器可以在编译时期解析一个"通过此 object 而触发的
   virtual function 调用操作", 因而回避 virtual 机制。如果 virtual function 被定义为 inline, 则更有效率上的大收获。


总而言之, 多态是一种威力强大的设计机制, 允许你继一个抽象的 public 接口之后, 封装相关的类型。我所举的 Library_materials 体系就是一例。需要付出的代价就
是额外的间接性---不论是在"内存的获得"或是在"类型的决断"上。C++ 通过 class 的 pointers 和 references 来支持多态, 这种程序设计风格就称为"面向对象"。


C++ 也支持具体的 ADT 程序风格, 如今被称为 object-based(OB)。例如 String class, 一种非多态的数据类型。String class 可以展示封装的非多态形式; 
它提供一个 public 接口和一个 private 实现品, 包括数据和算法, 但是不支持类型的扩充。

'一个 OB 设计可能比一个对等的 OO 设计速度更快而且空间更紧凑'。速度快是因为所有的函数调用操作都在编译时期解析完成,对象建构起来时不需要设置 virtual 机制;

空间紧凑则是因为每一个 class object 不需要负担传统上为了支持 virtual 机制而需要的额外负荷。不过, OB 设计比较没有弹性。


OO 和 OB 设计策略都有它们的拥护者和批评者。

// !! 在弹性 (OO) 和 效率 (OB) 之间常常存在着取与舍。一个人能够有效选择其一之前, 必须先清楚了解两者的行为和应用领域的需求。

