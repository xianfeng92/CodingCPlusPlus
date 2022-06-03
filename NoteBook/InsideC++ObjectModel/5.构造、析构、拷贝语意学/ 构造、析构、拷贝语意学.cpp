
// !! 构造、析构、拷贝语意学

Semantics of Construction,  Destruction and Copy


考虑下面这个 abstract base class 声明:

class Abstract_base {
 public:
  virtual ~Abstract_base();
  virtual void interface() = 0;
  virtual const char *mumble() const { return mumble_; }

 protected:
  char *mumble_;
};

你看出了什么问题没有 ?

虽然这个 class 被设计为一个抽象的 base class (有 pure virtual function, 使得 Abstract_base 不可能拥有实例), 但它仍然需要一个显式的构造函数
以初始化其 data member mumble_。

如果没有这个初始化操作, 其 derived class 的局部性对象 mumble_ 将无法决定初值, 例如:

class Concrete_derived : public Abstract_base {
public:
    Concrete_derived();
    //...
private:
    //...
};

void foo(){
    // Abstract_base::mumble_ 未被初始化
    Concrete_derived trouble;
}

你可能会争辩说, 也许 Abstract_base 的设计者意图让其每一个 derived class 提供 mumble_ 的初值。然而如果是这样, derived class 的唯一要求就是
Abstract_base 必须提供一个带有唯一参数的 protected constructor:

Abstract_base::Abstract_base(char *mumble = 0):mumble_(mumble){}

一般而言, class 的 data member 应该被初始化, 并且只在 constructor 中或是在 class 的其他 member functions 中指定初值。其他任何操作都将破坏封
装性质, 使 class 的维护和修改更加困难。

当然,你也可能争辩说设计者的错误并不在于未提供一个 explicit constructor, 而是他不应该在抽象的 base class 中声明 data members。这是比较强而有力的
论点(把 interface 和 implementation 分离), 但它并不是行遍天下皆有理, 因为将"被共享的数据"抽取出来放在 base class 中, 毕竟是一种正当的设计。


// !! “无继承”情况下的对象构造

C++ 新手常常很惊讶地发现, 一个人竟然可以定义和调用 (invoke) 一个 pure virtual function, 不过它只能被静态地调用 (invoked statically), 不能经由虚
拟机制调用。例如, 你可以合法地写下这段代码:

// ok,定义 pure virtual function
// 但只能被静态调用（invocate statically）
inline void Abstract_base::inteface() const {
    //...
}

inline void Concrete_derived::inteface() const {
    // ok, 静态调用（static invocation）
    Abstract_base::inteface();
    //...
}

要不要这样做, 全由 class 设计者决定。唯一的例外就是 pure virtual destructor,  class 设计者一定得定义它。为什么?  因为每一个 derived class 
destructor 会被编译器加以扩张, 以静态调用的方式调用其 "每一个 virtual base class" 以及 "上一层 base class" 的 destructor。因此, 只要缺乏任
何一个 base class destructors 的定义, 就会导致链接失败。

你可能会争辩说, 难道对一个 pure virtual destructor 的调用操作, 不应该在"编译器扩张 derived class 的 destructor"时压抑下来吗? 不! class 设计者
可能已经真的定义了一个 pure virtual destructor 。这样的设计是以 C++ 语言的一个保证为前提: 继承体系中每一个 class object 的 destructors 都会被调
用。所以编译器不能够压抑这一调用操作。

你也可能争辩说, 难道编译器不应该有足够的知识"合成" (如果 class 设计者忘记定义或不知道要定义) 一个 pure virtual destructor 的函数定义吗? 不! 编译器的
确没有足够知识, 因为编译器对一个可执行文件采取"分离编译模型"之故。

一个比较好的替代方案就是, 不要把 virtual destructor 声明为 pure。

// !! 虚拟规格的存在（Presence of a Virtual Specification）

如果你决定把 Abstract_base::mumble() 设计为一个 virtual function, 那将是一个糟糕的选择, 因为其函数定义内容并不与类型有关, 因而几乎不会被后继的
derived class 改写。

一般而言, 把所有的成员函数都声明为 virtual function, 然后再靠编译器的优化操作把非必要的 virtual invocation 去除, 并不是好的设计理念。

// !! 虚拟规格中 const 的存在


// !! 重新考虑 class 的声明

class Abstract_base {
public:
    virtual ~Abstract_base();
    virtual void interface() = 0;
    const char* mumble() const { return mumble_;}
protected:
    char* mumble_;
    Abstract_base(char* pd = 0);
};


考虑下面这个程序片段:

Point global;
Point foobar(){
    Point local;
    Point *pp = new Point();
    *pp = local;
    delete pp;
    return local;
}


L1、L5、L6 表现出三种不同的对象产生方式: global 内存配置、local 内存配置和 heap 内存配置。L7 把一个 class object 指定给另一个, L10 设定返回值, L9
则显式地以 delete 运算符删除 heap object。

// !! 一个 object 的生命, 是该 object 的一个执行期属性

1. local object 的生命从 L5 的定义开始, 到 L10 为止

2. global object 的生命和整个程序的生命相同

3. heap object 的生命从它被 new 运算符配置出来开始, 到它被 delete 运算符摧毁为止


下面是 Point 的第一次声明, 可以写成 C 程序。

// !!  C++Standard 说这是一种所谓的 Plain Old Data 声明形式:

typedef struct{
    float x, y, z;
} Point;


如果我们以 C++ 来编译这段代码, 会发生什么事?

观念上, 编译器会为 Point 声明一个 trivial default constructor、一个 trivial destructor、一个  trivial copy constructor, 以及一个
trivial copy assignment operator。

'但实际上, 编译器会分析这个声明, 并为它贴上 Plain Old Data 标签'。

当编译器遇到这样的定义:

Point global;

观念上 Point 的 trivial constructor 和 destructor 都会被产生并被调用, constructor 在程序起始(startup) 处被调用而 destructor 在程序的
exit() 处被调用 (exit() 是由系统产生的, 放在 main() 结束之前)。然而, 事实上那些 trivial members 要不是没被定义, 就是没被调用, 程序的行为一如
它在 C 中的表现一样。

唔, 只有一个小小的例外。在 C 中, global 被视为一个"临时性的定义", 因为它没有显式的初始化操作。一个"临时性的定义"可以在程序中发生多次。那些实例会被
链接器折叠起来, 只留下单独一个实例, 被放在程序 data segment 中一个"特别保留给未初始化之 global objects 使用"的空间。

由于历史的缘故, 这块空间被称为 BSS, 这是 Block Started by Symbol 的缩写, 是 IBM 704 assembler 的一个 pseudo-op。

C++ 并不支持"临时性的定义", 这是因为 class 构造行为的隐式应用之故。虽然大家公认这个语言可以判断一个 class objects 或是一个 Plain Ol'Data', 但似
乎没有必要搞得那么复杂。

// !! 因此, global 在 C++ 中被视为完全定义(它会阻止第二个或更多个定义)。

C 和 C++ 的一个差异就在于, BSS data segment 在 C++ 中相对地不重要。C++ 的所有全局对象都被以"初始化过的数据"来对待。


foobar() 函数中的 L5, 有一个 Point object local, 同样也是既没有被构造也没有被析构。当然啦, Point object local 如果没有先经过初始化, 可能会成
为一个潜在的程序"臭虫"---万一第一次使用它就需要其初值的话。

至于 heap object 在 L6 的初始化操作:

Point *heap = new Point();

会被转换为对 new 运算符 (由 library 提供) 的调用:

Point *heap = __new(sizeof(Point));

再一次强调一下, 并没有 default constructor 施行于 new 运算符所传回的 Point object 身上。

L7 对此 object  有个指派  (赋值,assign) 操作, 如果 local 曾被适当地初始化过, 一切就没有问题:

*heap = local;

观念上, 这样的指定操作会触发 trivial copy assignment operator 做拷贝搬运操作。然而实际上该 object 是一个 Plain Old Data, '所以赋值操
作(assignment) 将只是像 C 那样的纯粹位搬移操作'。


L9 执行一个 delete 操作:

delete heap;

会被转换为对  delete 运算符(由 library 提供)的调用:

_delete(heap);


观念上, 这样的操作会触发 Point 的 trivial destructor。但一如我们所见, destructor 要不是没有被产生就是没有被调用。最后, 函数以传值(by value)
的方式将 local 当做返回值传回, 这在观念上会触发 trivial copy constructor, 不过实际上 return 操作只是一个简单的位拷贝操作, 因为对象是个
Plain Old Data'。


// !! 抽象数据类型（Abstract Data Type）

以下是 Point 的第二次声明, 在 public 接口之下多了 private 数据, 提供完整的封装性, 但没有提供任何 virtual function:

class Point {
public:
    Point(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x_(x), y_(y), z_(z){}
    // no copy constructor, copy operator
    // or destructor define

private:
    float x_, y_, z_;
};

这个经过封装的 Point class, 其大小并没有改变,还是三个连续的 float。是的,不论 private 或 public 存取层, 或是 member function 的声明, 都不会
占用额外的对象空间。

我们并没有为 Point 定义一个 copy constructor 或 copy operator, 因为默认的位语意( default bitwise semantics) 已经足够。我们也不需要提供一个
destructor, 因为程序默认的内存管理方法也已足够。

对于一个 global 实例:

Point global;// 实施 Point::Point(0.0,0.0,0.0);

现在有了 default constructor 作用于其上。由于 global 被定义在全局范畴中,其初始化操作将延迟到程序启动 (startup) 时才开始。

'如果要将 class 中的所有成员都设定常量初值, 那么给予一个 explicit initialization list 会比较有效率些'。

举个例子, 考虑下面这个程序片段:

void mumble(){
    Point local1 = {1.0,2.3,3.4};
    Point local2;
    local2._x = 10.0;
    local2._y = 2.3;
    local2._z = 3.4;
}


'local1 的初始化操作会比 local2 的有效率些'。这是因为当函数的 activation record 被放进程序堆栈时, 上述 initialization list 中的常量就可以被
放进 local1 内存中了。

Explicit initialization list 带来三项缺点:

1. 只有当 class members 都是 public, 此法才奏效

2. 只能指定常量, 因为它们在编译时期就可以被评估求值(evaluated)

3. 由于编译器并没有自动施行之, 所以初始化行为的失败可能性会高一些

那么, explicit initialization list 所带来的效率优点, 能够补偿其软件工程上的缺点吗?

一般而言, 答案是 no。然而在某些特殊情况下又不一样。例如, 或许你以手工打造了一些巨大的数据结构如调色盘(color palette), 或是你正要把一堆常量数
据(像是以 Alias 或 SoftImage 软件产生出来的复杂几何模型中的控制点和节点)倾倒给程序, 那么 explicit initialization list 的效率会比 inline
constructor 好得多, 特别是对全局对象(global object)而言。

在编译器层面,会有一个优化机制用来识别 inline constructors, 后者简单地提供一个 member-by-member 的常量指定操作。然后编译器会抽取出那些值,并且
对待它们就好像是  explicit initialization list 所供应的一样, 而不会把 constructor 扩展成为一系列的 assignment 指令。


于是, local Point object 的定义:

{
    Point local;
}

现在被附加上 default Point constructor 的 inline expansion:

{
    Point local;
    local.x_ = 0.0f;
    local.y_ = 0.0f;
    local.z_ = 0.0f;
}

L6 配置出一个 heap Point object:

Point *heap = new Point();

现在则被附加一个对 default Point constructor 的有条件调用操作:

Point *heap = _new(sizeof(Point));
if(heap != nullptr){
    heap->Point::Point();
}

然后才又被编译器进行 inline expansion 操作。至于把 local object 赋值给 heap 指针所指向的对象:

*heap = local;

则保持着简单的位拷贝操作。

以传值方式传回 local object, 情况也是一样:

return local;

L9 删除 heap 所指的对象:

delete heap;

该操作并不会导致 destructor 被调用, 因为我们并没有显式地提供一个 destructor 函数实例。

观念上, 我们的 Point class 有一个相关的 default copy constructor、copy operator、和 destructor。然而它们都是无关痛痒的(trivial), 而且编译
器实际上根本没有产生它们。

// !! 为继承做准备

我们的第三个 Point 声明, 将为"继承性质"以及某些操作的动态决议(dynamic resolution)做准备。目前我们限制对 z 成员做存取操作:

class Point {
public:
    Point(float x = 0.0f, float y = 0.0f): x_(x), y_(y){}
    // no copy constructor, copy operator
    // no destructor defined
    virtual float z();
protected:
    float x_, y_;
};

再一次强调一下, 我并没有定义一个 copy constructor、copy operator、destructor。我们的所有 members 都以数值来存储, 因此在程序层面的默认语意之下
行为良好。某些人可能会争辩说, virtual functions 的导入应该总是附带着一个 virtual destructor 的声明。但是, 那么做在这个例子中对我们并无好处。

'virtual functions 的导入促使每一个 Point object 拥有一个 virtual table pointer'。这个指针给我们提供 virtual 接口的弹性, 其成本是: 每一个 object 
需要额外的一个 word 空间。有什么重大影响吗? 视应用情况而定!

除了每一个 class object 多负担一个 vptr 之外, virtual function 的导入也引发编译器对于我们的 Point class 产生膨胀作用:

1. 我们所定义的 constructor 被附加了一些代码, 以便将 vptr 初始化。这些代码必须被附加在任何 base class constructors 的调用之后, 但必须在任何由使用
   者(程序员)供应的代码之前。例如, 下面就是可能的附加结果:

  Point* Point::Point(Point* this, float x, float y) : x_(x), y_(y){

      // 设定 object 的 virtual table pointer(vptr)
      this->__vptr_Point = __vtbl_Point;

      // 扩展 member  initializer list
      this->x_ = x;
      this->y_ = y;

      return *this;
  }


2. 合成一个 copy constructor 和一个 copy assignment operator, 而且其操作不再是 trivial(但 implicit destructor 仍然是 trivial)。如果一个
   Point object 被初始化或以一个 derived class object 赋值, 那么以位为基础(bitwise)的操作可能对 vptr 带来非法设定。

    inline Point* Point::Point(Point* this, const Point& rhs)
    {
        this->__vptr_Point = __vtbl_Point;
        // 将 rhs 坐标中的连续位拷贝到 this 对象
        // 或是经过一个 member assignment 提供一个 member
        return *this;
    }

编译器在优化状态下可能会把 object 的连续内容拷贝到另一个 object 身上, 而不会实现一个精确地"以成员为基础(memberwise")的赋值操作。C++Standard 要求编译
器尽量延迟 nontrivial members 的实际合成操作, 直到真正遇到其使用场合为止。


为了方便, 我把 foobar() 再次列于此:

Point global;

void foobar()
{
    Point local;
    Point *heap = new Point();
    *heap = local;
    delete heap;
    return local;
}


L1 的 global 初始化操作、L6 的 heap 初始化操作以及 L9 的 heap 删除操作, 都还是和稍早的 Point 版本相同, 然而 L7 的 memberwise 赋值操作:

*heap = local;

很有可能触发 copy assignment operator 的合成, 及其调用操作的一个 inline expansion (行内扩张): 以 this 取代 heap, 而以 rhs 取代 local

最戏剧性的冲击发生在以传值方式传回 local 的那一行(L10)。由于 copy constructor 的出现, foobar() 很有可能被转化为下面这样:

Point foobar(Point _result)
{
    Point local;
    local.Point::Point(0.0,0.0);

    _result.Point::Point(local);
    local.Point::~Point();
    return;
}

如果支持 named return value (NRV)优化, 这个函数会进一步被转化为:

Point foobar(Point _result)
{
    _result.Point::Point(0.0,0.0);
    return;
}

'一般而言, 如果你的设计之中, 有许多函数都需要以传值方式(by value) 传回一个 local class object'。例如像这样形式的一个算术运算:

T operator+(const T& t1,const T& t2)
{
    T _result;
    //...
    return result;
}

那么提供一个 copy constructor 就比较合理 -- 甚至即使 default memberwise 语意已经足够。它的出现会触发 NRV 优化。然而, 就像我在前一个例子中所展现的
那样, NRV 优化后将不再需要调用 copy constructor, 因为运算结果已经被直接计算于"将被传回的 object"体内了


// !! 5.2 继承体系下的对象构造

当我们定义一个 object 如下:

T object;

实际上会发生什么事情 ? 如果 T 有一个 constructor(不论是由 user 提供或是由编译器合成的), 它会被调用。这很明显, 比较不明显的是, constructor 的调用真
正伴随了什么?

Constructor 可能内含大量的隐藏码, 因为编译器会扩充每一个 constructor, 扩充程度视 class T 的继承体系而定。

一般而言编译器所做的扩充操作大约如下:

1. 记录在 member initialization list 中的 data members 初始化操作会被放进 constructor 的函数本体, 并以 members 的声明顺序为顺序

2. 如果有一个 member 并没有出现在 member initialization list 之中, 但它有一个 default constructor, 那么该 default constructor 必须被调用

3. 在那之前, 如果 class object 有 virtual table pointer, 它必须被设定初值, 指向适当的 virtual table

4. 在那之前, 所有上一层的 base class constructors 必须被调用, 以 base class 的声明顺序为顺序:

   1. 如果 base class 被列于 member initialization list 中, 那么任何显式指定的参数都应该传递过去

   2. 如果 base class 没有被列于 member initialization list 中, 而它有 default constructor, 那么就调用之

   3. 如果 base class 是多重继承下的第二或后继的 base class, 那么 this 指针必须有所调整

5. 在那之前, 所有 virtual base class constructors 必须被调用, 从左到右, 从最深到最浅

    1. 如果 class 被列于 member initialization list 中, 那么如果有任何显式指定的参数, 都应该传递过去。若没有列于 list 之中, 而 class 有一个
       default constructor, 亦应该调用之
    2. 此外, class 中的每一个 virtual base class subobject 的偏移位置(offset) 必须在执行期可被存取
    3. 如果 class object 是最底层的 class, 其 constructors 可能被调用; 某些用以支持这一行为的机制必须被放进来

在这一节中, 我要从"C++ 语言对 classes 所保证的语意" 这个角度, 探讨 constructors 扩充的必要性。我再次以 Point 为例, 并为它增加一个 
copy constructor、一个copy operator、一个 virtual destructor, 如下所示:

class Point {
public:
    Point(float x = 0.0f, float y = 0.0f);
    Point(const Point &);
    Point& operator=(const Point &);

    virtual ~Point();
    virtual float z(){return 0;}
    //..
protected:
    float x_, y_;
};


在我开始介绍并一步步走过以 Point 为根源的继承体系之前, 我要带你很快地看看 Line class 的声明和扩充结果, 它由 _begin 和 _end 两个点构成:

class Line {
    Point _begin, _end;
    public:
    Line(float x1 = 0.0f, float y1 = 0.0f, float x2 = 0.0f, float y2 = 0.0f);
    Line(const Point &, const Point &);

    draw();
};

每一个 explicit constructor 都会被扩充以调用其两个 member class objects 的 constructor。如果我们定义 constructor 如下:

Line::Line(const Point &begin, const Point &end):_end(end), _begin(begin){}

它会被编译器扩充并转换为:

Line* Line::Line(Line* this, const Point &begin, const Point& end) {
    this->_begin.Point::Point(begin)
    this->_end.Point::Point(end);
    return this;
}

由于 Point 声明了一个 copy constructor、一个 copy operator, 以及一个 destructor, 所以 Line class 的 implicit copy constructor、
copy operator 和 destructor 都将有具体效用(non trivia)。

当程序员写下:

Line a;

时, implicit Line destructor 会被合成出来。其中,它的 member class object 的 destructor 会被调用(以其构造的相反顺序):

inline void Line::~Line(Line *this) {
    this->_end.Point::~Point();
    this->_begin.Point::~Point();
}

当然, 如果 Point destructor 是 inline 函数, 则每一个调用操作会在调用地点被扩展开来。请注意, 虽然 Point destructor 是 virtual, 但其调用操
作(在 containing class destructor 之中) 会被静态地决议出来(resolved statically)

类似的道理, 当一个程序员写下:

Line b = a;

时, implicit Line copy constructor 会被合成出来, 成为一个 inline public member。

最后, 当程序员写下:

a = b;

时, implicit copy assignment operator 会被合成出来,成为一个 inline public member。


// !! 虚拟继承（Virtual Inheritance）


考虑下面这个虚拟继承(继承自我们的 Point):

class Point3d : public virtual Point {
public:
    Point3d(float x= 0.0f, float y = 0.0f, float z = 0.0f) : Point(x), y_(y), z_(z){}
    Point3d(const Point3d &rhs) : Point(rhs.x_, rhs.y_),z_(rhs.z_){}

    ~Point3d();
    virtual float z(){return z_;}
private:
    float z_;
};

传统的"constructor 扩充现象"并没有用, 这是因为 virtual base class 的"共享性"之故:

Point3d* Point3d::Point3d(Point3d* this, float x, float y, float z) {
    this->Point::Point(x,y);
    this->__vptr_Point3d = __vtbl_Point3d;
    this ->__vptr_Point3d_Point = __vtbl_Point3d_Point;
    this->z_ = z;
    return this;
}

你看得出上面的 Point3d constructor 扩充内容有什么错误吗?

试着想想以下三种类的派生情况:

class Vertex : public virtual Point{...};
class Vertex3d : public Point3d, public Vertex{...};
class PVertex : public Vertex3d{...};

// !! vptr 初始化语意学

The Semantics of the vptr Initialization

当我们定义一个 PVertex object 时, constructor 的调用顺序是:

Point(x, y);
Point3d(x,y,z);
Vertex(x, y, z);
Vertex3d(x, y, z);
PVertex(x, y, z);

假设这个继承体系中的每一个 class 都定义了一个 virtual function size(), 此函数负责传回 class 的大小。如果我们写:

PVertex pv;
Point3d p3d;

Point *pt = &pv;

那么这个调用操作:

pt->size();

将传回 PVertex 的大小, 而:

pt = &p3d;
pt->size();

将传回 Point3d 的大小。

更进一步, 我们假设这个继承体系中的每一个 constructors 内含一个调用操作, 像这样:

Point3d::Point3d(float x, float y, float z) :x_(x), y_(y), z_(z) {
    if(spyCn) {
        cerr << "Within Point3d::Point3d()" << "size: " << size() << endl;
    }
}

当我们定义 PVertex object 时, 前述的 5 个 constructors 会如何? 每一次 size() 调用会被决议为 PVertex::size() 吗(毕竟那是我们正在构造的东西)? 或
者每次调用会被决议为"目前正在执行之 constructor 所对应之  class "的 size() 函数实例?

C++ 语言规则告诉我们, 在 Point3d constructor 中调用的 size() 函数, 必须被决议为 Point3d::size() 而不是 PVertex::size()。

更一般性地说, 在一个 class (本例为 Point3d) 的 constructor(和 destructor)中, 经由构造中的对象(本例为 PVertex 对象) 来调用一个 virtual function
, 其函数实例应该是在此 class(本例为 Point3d) 中有作用的那个。 

Constructors 的调用顺序是: 由根源而末端(bottom up)、由内而外(inside out)。当 base class constructor 执行时, derived 实例还没有被构造起来。在
PVertex constructor 执行完毕之前, PVertex 并不是一个完整的对象; Point3d constructor 执行之后, 只有 Point3d subobject 构造完毕。


当每一个 PVertex base class constructors 被调用时, 编译系统必须保证有适当的 size() 函数实例被调用。怎样才能办到这一点?

如果调用操作限制必须在 constructor (或destructor) 中直接调用, 那么答案十分明显: 将每一个调用操作以静态方式决议之, 千万不要用到虚拟机制。如果是在
Point3d constructor 中, 就显式调用 Point3d::size()。

然而如果 size() 之中又调用一个 virtual function, 会发生什么事情 ? 这种情况下, 这个调用也必须决议为Point3d的函数实例。而在其他情况下, 这个调用是纯正
的 virtual, 必须经由虚拟机制来决定其归向。也就是说, '虚拟机制本身必须知道是否这个调用源自于一个 constructor 之中'。

另一个我们可以采取的方法是, 在 constructor (或 destructor) 内设立一个标志, 说"嗨, 不, 这次请以静态方式来决议"。然后我们就可以用标志值作为判断依据,
产生条件式的调用操作。

这的确可行,  虽然感觉起来有点不够优雅和有效率。就算是一种 "hack"行为吧~ 我们甚至可以写一个注释来为自己开脱。

这个解决方法感觉起来比较像是我们的第一个设计策略失败后的一个对策， 而不是釜底抽薪的办法。根本的解决之道是, 在执行一个 constructor 时, 必须限制一组
virtual functions 候选名单。


想一想, 什么是决定一个 class 的 virtual functions 名单的关键? 答案是 virtual table。Virtual table 如何被处理? 答案是通过 vptr。所以为了控制一
个 class 中有所作用的函数, 编译系统只要简单地控制住 vptr 的初始化和设定操作即可。当然, 设定 vptr 是编译器的责任, 任何程序员都不必操心此事。


vptr 初始化操作应该如何处理 ? 本质而言, 这得视 vptr 在  constructor 之中"应该在何时被初始化"而定。

我们有三种选择:

1.在任何操作之前

2.在 base class constructors 调用操作之后, 但是在程序员供应的代码或是 "member initialization list 中所列的 members 初始化操作" 之前

3. 在每一件事情发生之后

答案是 2。另两种选择没什么价值。如果你不相信, 请在 1 或 3 策略下试试看。策略 2 解决了"在 class 中限制一组 virtual functions 名单"的问题。如果每一
个 constructor 都一直等待到其 base class constructors 执行完毕之后才设定其对象的 vptr, 那么每次它都能够调用正确的 virtual function 实例。


令每一个 base class constructor 设定其对象的 vptr, 使它指向相关的 virtual table 之后, 构造中的对象就可以严格而正确地变成"构造过程中所幻化出来的每
一个class" 的对象。也就是说, 一个 PVertex 对象会先形成一个 Point 对象、一个 Point3d 对象、一个 Vertex 对象、一个 Vertex3d 对象, 然后才成为一个
PVertex 对象。在每一个 base class constructor 中, 对象可以与 constructor's class'的完整对象做比较。'对于对象而言, "个体发生学"概括了"系统发生学"'

constructor 的执行算法通常如下:

1. 在 derived class constructor 中, 所有 virtual base classes 及 上一层 base class 的 constructors 会被调用

2. 上述完成之后, 对象的 vptr(s) 被初始化, 指向相关的 virtual table(s)

3. 如果有 member initialization list 的话, 将在 constructor 体内扩展开来。这必须在 vptr 被设定之后才做, 以免有一个 virtual member function
   被调用

4. 最后, 执行程序员所提供的代码


例如, 已知下面这个由程序员定义的 PVertex constructor:

PVertex::PVertex(float x, float y, float z) :  next(0),Point3d(x,y,z)
{
    if(spyOn)
    {
        cerr << "Within PVertex::PVertex(): " << "size is " << size() << endl;
    }
}

它很可能被扩展为:

// C++ 伪代码

PVertex* PVertex::PVertex(PVertex* this,bool _most_derived, float x, float y, float z)
{
    // 条件式用 virtual base constructor
    if(_most_derived)
    {
        this->Point(x,y);
    }

    // 无条件,调用上一层 base constructor
    this->Vertex3d::Vertex3d(x,y,z);

    // 将相应的 vptr 初始化
    this->__vptr_PVertex = __vtbl_PVertex;
    this->__vptr_Point_PVertex = __vtbl_Point_PVertex;

    if(spyOn)
    {
        cerr << "Within PVertex::PVertex() " << "size " << (*this->__vptr_PVertex[3].faddr)(this);
    }

    // 传回被构造的对象
    return this;
}

这就完美地解决了我们所说的有关限制虚拟机制的问题。


// !! 5.3 对象复制语意学

Object Copy Semantics

'当我们设计一个 class, 并将一个 class object 赋值给另一个 class object 时, 我们有三种选择':

1. 什么都不做, 因此得以实施默认行为

2. 提供一个 explicit copy assignment operator

3. 显式地拒绝把一个 class object assign 给另一个 class object

在这一节, 我要验证 copy assignment operator 的语意, 以及它们如何被模塑出来。

再一次, 我利用 Point class 来帮助讨论:

class Point {
public:
    Point(float x = 0.0f, float y = 0.0f): x_(x), y_(y) {}
    //...
protected:
    float x_, y_;
};


'没有什么理由需要禁止拷贝一个 Point object。因此问题就变成了:  默认行为是否足够'?

如果我们要支持的只是一个简单的拷贝操作,那么默认行为不但足够而且有效率,我们没有理由再自己提供一个 copy assignment operator。

'只有在默认行为所导致的语意不安全或不正确时, 我们才需要设计一个 copy assignment operator'。好, 默认的 memberwise copy 行为对于我们的
Point object 不安全吗? 不正确吗? 不, 由于坐标都内含数值, 所以不会发生"别名化(aliasing)"或"内存泄漏(memory leak)"。如果我们自己提供一个
copy assignment operator, 程序反倒会执行得比较慢。

如果我们不对 Point 供应一个 copy assignment operator, 而光是仰赖默认的 memberwise copy, 编译器会产生出一个实例吗? 这个答案和 copy constructor
的情况一样: 实际上不会~ 由于此 class 已经有了 bitwise copy 语意,所以 implicit copy assignment operator 被视为毫无用处, 也根本不会被合成出来。

一个 class 对于默认的 copy assignment operator, 在以下情况, 不会表现出 bitwise copy 语意:

1. 当 class 内含一个 member object, 该 object 对应的 class 有一个 copy assignment operator

2. 当一个 class 的 base class 有一个 copy assignment operator 时

3. 当一个 class 声明了任何 virtual functions 时

4. 当 class 继承自一个 virtual base class

C++Standard 上说 copy assignment operators 并不表示 bitwise copy semantics 是 nontrivial。实际上, 只有 nontrivial instances

才会被合成出来。

于是, 对于我们的  Point class, 这样的赋值(assign)操作:

Point a, b;
...
a = b;

由 bitwise copy 完成, 把 Point b 拷贝到 Point a, 其间并没有 copy assignment operator 被调用。从语意上或从效率上考虑, 这都是我们所需要的。

注意, 我们还是可能提供一个 copy constructor 为的是把 name return value (NRV) 优化打开。copy constructor 的出现不应该让我们以为也一定要提供
一个 copy assignment operator。

现在我要导入一个 copy assignment operator, 用以说明该 operator 在继承之下的行为:

inline Point& Point::operator=(const Point& rhs) {
    this->x_ = rhs.x_;
    this->y_ = rhs.y_;
    return *this;
}

现在派生一个 Point3d class (请注意是虚拟继承):

class Point3d : virtual public Point {
public:
    Point3d(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    //...
protected:
    float z_;
};

如果我们没有为 Point3d 定义一个 copy assignment operator, 编译器就必须合成一个。合成而得的东西可能看起来像这样:

// C++ 伪代码
inline Point3d* Point3d::operator=(Point3d *this, const Point &rhs) {
    // 调用 base class 的函数实例
    this->Point::operator=(rhs);

    // memberwise copy the derived class member
    z_ = rhs.z_;
}

copy assignment operator 有一个非正交性情况(意指不够理想、不够严谨的情况), 就是它缺乏一个 member assignment list

因此我们不能够写:

inline Point3d& Point3d::operator=(const Point3d &p3d) : Point(p3d), z(p3d.z_) {

}

我们必须写成以下两种形式, 才能调用 base class 的 copy assignment operator:

Point::operator=(p3d);

或

(*(Point*)this) = p3d;

缺少 copy assignment list, 看来或许只是一件小事, 但如果没有它,编译器一般而言就没有办法压抑上一层 base class 的 copy operators 被调用。

例如, 下面是个 Vertex copy operator, 其中 Vertex 也是虚拟继承自 Point:

inline Vertex& Vertex::operator=(const Vertex &rhs) {
    this->Point::operator=(rhs);
    _next = rhs._next;
    return *this;
}

现在让我们从 Point3d 和 Vertex 中派生出 Vertex3d。下面是 Vertex3d 的 copy assignment operator:


inline Vertex3d& Vertex3d::operator=(const Vertex3d & rhs) {
    this->Point::operator=(rhs);
    this->Point3d::operator=(rhs);
    this->Vertex::operator=(rhs);
    return *this
}

编译器如何能够在 Point3d 和 Vertex 的 copy assignment operators 中压抑 Point 的 copy assignment operators呢? 编译器不能够重复传统的
constructor 解决方案。这是因为和 constructor 以及 destructor 不同的是, "取 copy assignment operator 地址" 的操作是合法的。因此下面这个
例子是毫无瑕疵的合法程序代码:

typedef Point3d& (Point3d::*pmfPoint3d)(const Point3d&);

pmfPoint3d pmf = &Point3d::operator;

(x.*pmf)(x);



// !! 5.4 对象的效能（Object Efficiency）

在以下的效率测试中, 对象构造和拷贝所需的成本是以 Point3d class 声明为基准的, 从简单形式逐渐到复杂形式, 包括 Plain Old Data、抽象数据类型
(Abstract Data Type, ADT)、单一继承、多重继承、虚拟继承。

以下函数是测试的主角:

Point3d Lots_of_copy(Point3d a, Point3d b)
{
    Point3d pc = a;
    Pc = b;(1)
    b = a;(2)
    return Pc;
}

它内含 4 个 memberwise 初始化操作, 包括两个参数、一个传回值以及一个局部对象 pC。它也内含两个 memberwise 拷贝操作, 分别是标示为(1)和(2)那两行
的 pC 和 b。main() 函数如下:

main()
{
    Point3d pA(1.21,2.32,4.32);
    Point3d pB(0.32,3.32,1.231);

    for(int i = 0; i < 10000000; i++)
    {
        Lots_of_copy(pA, pB);
    }
    return 0;
}


在最初的两个程序中, 数据类型是一个 struct 和一个拥有 public 数据的 class:


对 pA 和 pB 的初始化操作是通过 explicit initialization list 进行的:

    Point3d pA(1.21,2.32,4.32);
    Point3d pB(0.32,3.32,1.231);


这两个操作表现出 bitwise copy 语意, 所以你应该会预期它们的执行有最好的效率。



// !! 析构语意学（Semantics of Destruction）

如果 class 没有定义 destructor, 那么只有在 class 内含的 member object (抑或  class 自己的 base class) 拥有 destructor 的情况下, 
编译器才会自动合成出一个来。否则, destructor 被视为不需要, 也就不需被合成。

例如, 我们的 Point, 默认情况下并没有被编译器合成出一个 destructor -- 甚至虽然它拥有一个 virtual function:

class Point {
public:
    Point(float x = 0.0f, float y = 0.0f);
    Point(const Point &rhs);
    virtual void z();
    //...
private
    float x_, y_;
};


类似的道理, 如果我们把两个 Point 对象组合成一个 Line class:

class Line
{
public:
    Line(const Point &lhs, const Point &rhs);
    //...

    void draw();

private:
    Point begin_, end_;
};

Line 也不会拥有一个被合成出来的 destructor, 因为 Point 并没有 destructor。

当我们从 Point 派生出 Point3d (即使是一种虚拟派生关系)时, 如果我们没有声明一个 destructor, 编译器就没有必要合成一个
destructor。

'不论 Point 还是 Point3d 都不需要 destructor, 为它们提供一个 destructor 反而是低效率的'。你应该拒绝那种被我称为"对称策略"的奇怪想法:"你已经定义了
一个 constructor, 所以你以为提供一个 destructor 也是天经地义的事"。事实上, 你应该因为"需要"而非"感觉"来提供 destructor, 更不要因为你不确定是否需要
一个 destructor, 于是就提供它。

'为了决定 class 是否需要一个程序层面的 destructor (或是 constructor), 请你想想一个 class object 的生命在哪里结束 (或开始) ? 需要什么操作才能保证
对象的完整 ? 这是你写程序时比较需要了解的'

这也是 constructor 和 destructor 什么时候起作用的关键。举个例子, 已知:

{
    Point pt;
    Point *p = new Point3d();
    foo(&pt, p);
    ...
    delete p;
}

我们看到, pt 和 p 在作为 foo() 函数的参数之前, 都必须先初始化为某些坐标值。这时候需要一个 constructor, 否则使用者必须显式地提供坐标值。一般而言, class 
的使用者没有办法检验一个 local 变量或 heap 变量以知道它们是否被初始化。把 constructor 想象为程序的一个额外负担是错误的, 因为它们的工作有其必要性。如果没
有它们, 抽象化(abstraction) 的使用就会有错误的倾向。

当我们显式地 delete 掉 p, 会如何? 有任何程序上必须处理的吗? 是否需要在 delete 之前这么做:

p->x(0);
p->y(0);

不, 当然不需要。'没有任何理由说在 delete 一个对象之前先得将其内容清除干净。你也不需要归还任何资源'。在结束 pt 和 p 的生命之前, 没有任何"class 使用者
层面" 的程序操作是绝对必要的, 因此, 也就不一定需要一个 destructor。

然而请考虑我们的 Vertex class, 它维护了一个由紧邻的"顶点"所形成的链表, 并且当一个顶点的生命结束时, 在链表上来回移动以完成删除操作。如果这(或其他语意)
正是程序员所需要的, 那么这就是 Vertex destructor 的工作。

当我们从 Point3d 和 Vertex 派生出 Vertex3d 时, 如果我们不供应一个 explicit Vertex3d destructor, 那么我们还是希望 Vertex destructor 被调
用, 以结束一个 Vertex3d object。因此编译器必须合成一个 Vertex3d destructor, 其唯一任务就是调用 Vertex destructor。如果我们提供一个
Vertex3d destructor, 编译器会扩展它, 使它调用 Vertex destructor (在我们所供应的程序代码之后)。一个由程序员定义的 destructor 被扩展的方式类
似 constructors 被扩展的方式, 但顺序相反:

1. 如果 object 内含一个 vptr, 那么首先重设(reset)相关的 virtual table

2. destructor 的函数本体现在被执行, 也就是说 vptr 会在程序员的代码执行前被重设

3. 如果 class 拥有 member class objects, 而后者拥有 destructors, 那么它们会以其声明顺序的相反顺序被调用

4. 如果有任何直接的(上一层) non virtual base classes 拥有 destructor, 它们会以其声明顺序的相反顺序被调用

一个 object 的生命结束于其 destructor 开始执行之时。由于每一个 base class destructor 都轮番被调用, 所以 derived object 实际上变成了一个完整的
object。例如一个 PVertex 对象归还其内存空间之前, 会依次变成一个 Vertex3d 对象、一个 Vertex 对象,一个 Point3d 对象,最后成为一个 Point 对象。当
我们在 destructor 中调用 member functions 时, 对象的蜕变会因为 vptr 的重新设定(在每一个 destructor 中, 在程序员所供供应的代码执行之前)而受到影
响。