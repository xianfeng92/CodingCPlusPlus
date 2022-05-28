// !! 执行期语意学

想象一下我们有下面这个简单的式子:

if(yy == xx.getValue());

其中 xx 和 yy 定义为:

X xx;
Y yy;

class Y 定义为:

class Y{
public:
    Y();
    ~Y();
    bool operator=(const Y& other)const;
    //...
};


class X 定义为:

class X{
public:
    X();
    ~X();
    operator Y() const;
    X getValue();
    //...
};

真的简单,不是吗? 好, 让我们看看本章一开始的那个表达式该如何处理。

首先, 让我们决定 equality(等号)运算符所参考到的真正实例。在这个例子中, 它将被决议(resolves)为"被 overloaded 的 Y 成员实例"。


下面是该式子的第一次转换:

if(yy.operator==(xx.getValue()));

Y 的 equality(等号)运算符需要一个类型为 Y 的参数, 然而 getValue() 传回的却是一个类型为 X 的 object。若非有什么方法可以把一个 X object 转换为一个
Y object, 那么这个式子就算错!

本例中 X  提供一个 conversion 运算符, 把一个 X object 转换为一个 Y object。它必须施行于 getValue() 的返回值身上。下面是该式子的第二次转换:

if(yy.operator=((xx.getValue()).operatorY());

'到目前为止所发生的一切都是编译器根据 class 的隐含语意, 对我们的程序代码所做的增胖操作'。如果我们需要, 我们也可以明确地写出那样的式子。不, 我并没有建议你
那么做。不过如果你那么做, 会使编译速度稍微快一些。

虽然程序的语意是正确的, 其可读性变差了。接下来我们必须产生一个临时对象, 用来放置函数调用所传回的值:

1. 产生一个临时的 class X object, 放置 getValue() 的返回值

X temp = xx.getValue();

2. 产生一个临时的 class Y object, 放置 operator Y() 的返回值

Y temp2 = temp.operatorY();

3. 产生一个临时的 int object, 放置 equality(等号)运算符的返回值

int result = (yy,operator==(temp2));


最后, 适当的 destructor 将被施行于每一个临时性的 class object 身上。

这导致我们的式子被转换为以下形式:

// C++ 伪代码

{
    X temp1 = xx.getValue();
    Y temp2 = temp1.operatorY();
    int temp3 = yy.operator==(temp2);
    if(temp3) ...

    temp2.Y::~Y();
    temp1.X::~X();
}

唔, 似乎不少呢! '这是 C++ 的一件困难事情:不太容易从程序源码看出表达式的复杂度'。


// !! 对象的构造和析构（Object Construction and Destruction）

一般而言, constructor 和 destructor 的安插都如你所预期的那样:

// C++ 伪代码
{
    Point point;
    // point.Point::Point();
    ...
    // point.Point::~Point();
}

如果一个区段 (译注: 以 {} 括起来的区域) 或函数中有一个以上的离开点, 情况会稍微混乱一些。Destructor 必须被放在每一个离开点(当时 object 还存活)之前,
例如:

{
    Point point;
    switch(int(Point.x()))
    {
        case 1:
        // deconstructor 在这里行动 
        return;
        case 2:
        // deconstructor 在这里行动 
        return;
        case 3:
        // deconstructor 在这里行动 
        return;
        default:
        // deconstructor 在这里行动 
        return;
    }
    // deconstructor 在这里行动 
}

在这个例子中, point 的 destructor 必须在 switch 指令 4 个出口的 return 操作前被生成出来。另外也很有可能在这个区段的结束符号(右大括号)之前被生成出
来---即使程序分析的结果发现绝不会进行到那里。

'一般而言我们会把 object 尽可能放置在使用它的那个程序区段附近, 这么做可以节省非必要的对象产生操作和摧毁操作'。以本例而言, 如果我们在检查 cache 之前就定
义了 Point object, 那就不够理想。这个道理似乎非常明显, 但许多 Pascal或C程序员使用 C++ 的时候, 仍然习惯把所有的 objects 放在函数或某个区段的起始处。


// !! 全局对象（Global Objects）

如果我们有以下程序片段:

Matrix identity;

main()
{
    // identity 必须在此处被初始化
    Matrix ml = identity;;
    ...
    return 0;
}

'C++ 保证, 一定会在 main() 函数中第一次用到 identity 之前, 把 identity 构造出来, 而在 main() 函数结束之前把 identity 摧毁掉'。

像 identity 这样的所谓 global object 如果有 constructor 和  destructor  的话, 我们说它需要静态的初始化操作和内存释放操作。

'C++ 程序中所有的 global objects 都被放置在程序的 data segment 中'。如果显式指定给它一个值, 此 object 将以该值为初值。否则 object 所配置到的内存
内容为 0。因此在下面这段代码中:

int v1 = 1024;
int v2;

v1 和 v2 都被配置于程序的 data segment, v1 值为 1024, v2 值为 0(这和 C 略有不同, C 并不自动设定初值)。


虽然 class object 在编译时期可以被放置于 data segment 中并且内容为 0, 但 constructor 一直要到程序启动(startup)时才会实施。必须对一个"放置于
program data segment 中的 object 的初始化表达式"做评估(evaluate), 这正是为什么一个 object 需要静态初始化的原因。



// !! 局部静态对象（Local Static Objects）

假设我们有以下程序片段:

const Matrix&
identity(){
    static Matrix mat_identity;
    //...
    return mat_identity;
}


'Local static class object 保证了什么样的语意'?

1. mat_identity 的 constructor 必须只能施行一次, 虽然上述函数可能会被调用多次

2. mat_identity 的 destructor 必须只能施行一次, 虽然上述函数可能会被调用多次


编译器的策略之一就是, 无条件地在程序起始(startup) 时构造出对象来。然而这会导致所有的 local static class objects 都在程序起始时被初始化, 即使它们所在
的那个函数从不曾被调用过。因此, '只在 identity() 被调用时才把 mat_identity 构造起来, 是比较好的做法 (现在的 C++Standard 已经强制要求这一点)'。我们
应该怎么做呢 ?


以下就是我在 cfront 之中的做法。首先, 我导入一个临时性对象以保护 mat_identity 的初始化操作。第一次处理 identity() 时, 这个临时对象被评估为 false,于是
constructor 会被调用, 然后临时对象被改为 true。这样就解决了构造的问题。

而在相反的那一端, destructor 也需要有条件地施行于 mat_identity 身上, 但只有在 mat_identity 已经被构造起来才算数。要判断 mat_identity 是否被构造起
来, 很简单, 如果那个临时对象为  true, 就表示构造好了。


// !! 对象数组（Array of Objects）

假设我们有下列的数组定义:

Point knot[13];

什么东西需要完成 ? 如果 Point 既没有定义一个 constructor 也没有定义一个 destructor, 那么我们的工作不会比建立一个"内建(build-in)类型所组成的数组"
更多, 也就是说我们只要配置足够内存以存储 10 个连续的 Point 元素即可。

然而 Point 的确定义了一个 default destructor, 所以这个 destructor 必须轮流施行于每一个元素之上。一般而言这是经由一个或多个 runtime library 函数
达成的。

在 cfront 中, 我们使用一个被命名为 vec_new() 的函数, 产生出以 class objects 构造而成的数组。比较新近的编译器, 包括 Borland、Microsoft 和 Sun,
则是提供两个函数, 一个用来处理"没有 virtual base class"的 class, 另一个用来处理"内含 virtual base class" 的 class。后一个函数通常被称为
vec_vnew()。


函数类型通常如下(当然在各平台上可能会有些许差异):

void* vec_new(void* array,size_t element_size, int element_count, void (*constructor)(void*)
, void (*deconstructor)(void*, char)
);

其中的 constructor 和 destructor 参数是这一 class 之 default constructor 和 default destructor 的函数指针。

参数 array 持有的若不是具名数组(本例为 knots)的地址, 就是 0。如果是 0, 那么数组将经由应用程序的 new 运算符, 被动态配置于 heap 中。

参数 elem_size 表示数组中的每个元素的大小。在 vec_new() 中, constructor 施行于 elem_count 个元素之上。

下面是编译器可能针对我们的 10 个 Point 元素所做的 vec_new() 调用操作:

Point knots[10];

vec_new(&knots, sizeof(Point), 10, &Point::Point, 0);

如果 Point 也定义了一个 destructor, 当 knots 的生命结束时, 该 destructor 也必须施行于那 10 个 Point 元素身上。


这是经由一个类似的 vec_delete() 的 runtime library 函数完成,其函数类型如下:

void * vec_delete(void *array, size_t element_size, int element_count, void(*deconstructor)(void*, char));

有些编译器会另外增加一些参数, 用以传递其他数值, 以便能够有条件地导引 vec_delete() 的逻辑。在 vec_delete() 中, destructor 被施行于 elem_count 个
元素身上。


如果程序员提供一个或多个明显初值给一个由 class objects 组成的数组, 像下面这样, 会如何:

Point knots[10] = {Point(), Point(1.0,2.0,3.0), -1.0};

对于那些明显获得初值的元素, vec_new() 不再有必要。对于那些尚未被初始化的元素, vec_new() 的施行方式就像面对"由 class elements 组成的数组, 而该数组没
有 explicit initialization list"一样。因此上一个定义很可能被转换为:


Point knots[10];

// C++ 伪代码

// 显示的初始化前三个元素
Point::Point(&knots[0]);
Point::Point(&knots[1],1.0,2.0,3.0);
Point::Point(&knots[2],-1.0,0.0,0.0);

// 以 vec_new 初始化后面七个元素

vec_new(&knots + 3, sizeof(Point), 7, &Point::Point, 0);


// !! Default Constructors和数组

'如果你想要在程序中取出一个 constructor 的地址, 是不可以的'。

// !! 6.2 new 和 delete 运算符

运算符 new 的使用, 看起来似乎是个单一运算, 像这样:

int *pi = new int(5);

但事实上它是由两个步骤完成的:

1. 通过适当的 new 运算符函数实例, 配置所需的内存

int *pi = _new(sizeof(int));

2. 将配置得来的对象设立初值

*pi = 5;

更进一步地说, 初始化操作应该在内存配置成功 (经由 new 运算符) 后才执行:

// new 运算符两个分离步骤
// given: int *pi = new int(5);

// 重写声明
int *pi;
if(pi = __new(sizeof(int)))
{
    *pi = 5;// 成功了才初始化
}

delete 运算符的情况类似。当程序员写下:

delete pi;

时, 如果 pi 的值是0, C++ 语言会要求 delete 运算符不要有操作。因此编译器必须为此调用构造一层保护膜:

if(pi != 0)
{
    __delete pi;
}

请注意 pi 并不会因此被自动清除为 0, 因此像这样的后继行为:

// 没有良好的定义，但是合法
if(pi && *pi == 5)
{

}

虽然没有良好的定义, 但是可能(也可能不)被评估为真。这是因为对于 pi 所指向之内存的变更或再使用, 可能(也可能不)会发生。

'pi 所指对象的生命会因 delete 而结束。所以后继任何对 pi 的参考操作就不再保证有良好的行为, 并因此被视为是一种不好的程序风格'。然而, 把 pi 继续当做一个
指针来用, 仍然是可以的(虽然其使用受到限制)。


'在这里, 使用指针 pi, 和使用 pi 所指的对象, 其差别在于哪一个的生命已经结束了'。虽然该地址上的对象不再合法,地址本身却仍然代表一个合法的程序空间。

因此 pi 能够继续被使用, 但只能在受限制的情况下, 很像一个 void* 指针的情况

以 constructor 来配置一个 class object, 情况类似。例如:

Point *origin = new Point();

被转换为:

Point *origin;
if(origin = __new(sizeof(Point)))
{
    origin = Point::Point(origin);
}


如果实现出 exception handling, 那么转换结果可能会更复杂些:

// C++ 伪代码
if(origin = __new(sizeof(Point)))
{
    try{
        origin = Point::Point(origin);
    }catch(...){
        __delete(origin);

        throw;
    }
}


在这里, 如果以 new 运算符配置 object, 而其 constructor 抛出一个 exception, 配置得来的内存就会被释放掉。然后 exception 再被 throw。

Destructor 的应用极为类似。下面的式子：

delete origin;

会变成:

if(origin != 0){
    Point::~Point(origin);
    __delete(origin);
}

如果在 exception handling 的情况下, destructor 应该被放在一个 try 区段中。exception handler 会调用 delete 运算符, 然后再一次抛出该
exception。


'new 运算符实际上总是以标准的 C malloc() 完成, 虽然并没有规定一定得这么做不可。相同情况, delete 运算符也总是以标准的 C free() 完成':

extern void operator delete(void *ptr){
    if(ptr){
        free((char*)ptr);
    }
}


// !! 针对数组的 new 语意

当我们这么写:

int *p_arr = new int[5];

时, vec_new() 不会真正被调用, 因为它的主要功能是把 default constructor 施行于 class objects 所组成的数组的每一个元素身上。倒是 new 运算符函数会
被调用

int *p_arr = (int *) new(sizeof(int) * 5);

相同情况, 如果我们写:

simple_aggr * p_aggr = new simple_aggr[5];

vec_new() 也不会被调用。为什么 ? simple_aggr 并没有定义一个 constructor 或 destructor, 所以配置数组以及清除 p_aggr 数组的操作,'只是单纯地获得内
存和释放内存而已。这些操作由 new 和 delete 运算符来完成就绰绰有余了'。

然而如果 class 定义了一个 default constructor, 某些版本的 vec_new() 就会被调用, 配置并构造 class objects 所组成的数组。

例如这个算式:

Point3d *p_array = new Point3d[10];

通常会被编译为:

Point3d *p_array;
p_array = vec_new(0, sizeof(Point3d), 10, &Point3d::Point3d, &Point3d::~Point3d);

还记得吗, 在个别的数组元素构造过程中, 如果发生 exception, destructor 就会被传递给 vec_new()。只有已经构造妥当的元素才需要 destructor 的施行, 因为
它们的内存已经被配置出来了, 'vec_new() 有责任在 exception 发生的时机把那些内存释放掉'。

在 C++2.0 版之前, 将数组的真正大小提供给程序的 delete 运算符, 是程序员的责任。因此如果我们原先写下:

const int array_size = 10;
Point3d *p_array = new Point3d[array_size];

那么我们就必须对应地写下:

delete[array_size] p_array;

在 2.1 版中, 这个语言有了一些修改, 程序员不再需要在  delete  时指定数组元素的个数,  因此我们现在可以这样写:

delete[] p_array;

然而为了回溯兼容,  两种形式都可以接受。支持此种新形式的第一个编译器当然就是 cfront。这项技术支持需要知道的首先是指针所指的内存空间, 然后是其中的元素个数。

'寻找数组维度, 对于 delete 运算符的效率带来极大的冲击, 所以才导致这样的妥协:只有在中括号出现时, 编译器才寻找数组的维度', 否则它便假设只有单独一个
object 要被删除。

如果程序员没有提供必须的中括号, 像这样:

delete p_array;

那么就只有第一个元素会被析构。其他的元素仍然存在——虽然其相关的内存已经被要求归还了。

应该如何记录元素个数 ? '一个明显的方法就是为 vec_new() 所传回的每一个内存区块配置一个额外的 word, 然后把元素个数包藏在那个 word 之中'。
通常这种被包藏的数值称为所谓的 cookie(小甜饼)。


cookie 策略有一个普遍引起忧虑的话题就是, 如果一个坏指针应该被交给  delete_vec(), 取出来的 cookie 自然是不合法的。一个不合法的元素个数和一个坏的起始
地址, 会导致 destructor 以非预期的次数被施行于一段非预期的区域。


如果我们配置一个数组, 内含 10 个 Point3d objects, 我们会预期 Point 和 Point3d 的 constructor 被调用各 10 次, 每次作用于数组中的一个元素:

Point *ptr = new Point3d[10];

而当我们 delete  由 ptr 所指向的 10 个 Point3d 元素时,  会发生什么事情? 很明显, 我们需要虚拟机制的帮助, 以获得预期的 Point destructor 和 Point3d
 destructor 各 10 次的调用(每一次作用于数组中的一个元素):

 delete[] ptr;

施行于数组上的 destructor, 如我们所见, 是根据交给 vec_delete() 函数的"被删除之指针类型的 destructor"---本例中正是 Point destructor。这很明显并非
我们所希望。此外, 每一个元素的大小也一并被传递过去。这就是 vec_delete() 如何迭代走过每一个数组元素的方式。本例中被传递过去的是 Point class object 的
大小而不是 Point3d class object 的大小。整个运作过程非常不幸地失败了, 不只是因为执行了错误的 destructor, 而且自从第一个元素之后, 该 destructor 
即被施行于不正确的内存区块中。


程序员应该怎么做才好? '最好就是避免以一个 base class 指针指向一个 derived class objects 所组成的数组'--如果 derived class object 比其 base 大
的话。如果你真的一定得这样写程序, 解决之道在于程序员层面,而非语言层面:

for(int x = 0; i < element_count; i++){
    Point3d *p = ((Point3d*)ptr)[i];
    delete p;
}

基本上, 程序员必须迭代走过整个数组, 把 delete 运算符实施于每一个元素身上。以此方式, 调用操作将是 virtual, 因此, Point3d 和 Point 的 destructor 都
会施行于数组中的每一个 object 身上。


// !! Placement Operator new 的语意

'有一个预先定义好的重载的 (overloaded) new 运算符, 称为  placement operator new'。

它需要第二个参数, 类型为void*。 调用方式如下:

Point2w *ptr = new(arena) Point2w;

其中 arena 指向内存中的一个区块, 用以放置新产生出来的 Point2w object。

这个预先定义好的 placement operator new 的实现方法简直是出乎意料的平凡。它只要将"获得的指针(上例的 arena )" 所指的地址传回即可。

void operator new(size_t, void *p)
{
    return p;
}

如果它的作用只是传回其第二个参数, 那么它有什么价值呢? 也就是说, 为什么不简单地这么写算了(这不就是实际所发生的操作吗):

Point2w *ptr = (Point2w *)arena;

唔, 事实上这只是所发生的操作的一半而已。另外一半无法由程序员产生出来。想想这些问题:

1. 什么是使 placement new operator 能够有效运行的另一半扩充(而且是 arena 的显式指定操作 (explicit assignment 所没有提供的) ?

2.什么是 arena 指针的真正类型 ? 该类型暗示了什么 ?


Placement new operator 所扩充的另一半是将 Point2w constructor 自动实施于 arena 所指的地址上:

//C++ 伪代码
Point2w *ptr = (Point2w*)arena;

if(ptr != 0)
{
    ptr->Point2w::Point2w();
}

这正是使 placement operator new 威力如此强大的原因。这一份代码决定 object 被放置在哪里; 编译系统保证 object 的 constructor 会施行于其上。


然而却有一个轻微的不良行为。你看得出来吗? 下面是一个有问题的程序片段:

void foobar(){
    Point2w *p2w = new (arena)Point2w;
    //...
    //...
    p2w = new (arena)Point2w;
}


'如果 placement operator 在原已存在的一个 object 上构造新的 object, 而该既存的 object 有个 destructor, 这个 destructor 并不会被调用'。调用该
destructor 的方法之一是将那个指针 delete 掉。

不过在此例中如果你像下面这样做, 绝对是个错误:

delete p2w;
p2w = new (arena)Point2w;

是的, delete 运算符会发生作用, 这的确是我们所期待的。但是它也会释放由 p2w 所指的内存, 这却不是我们所希望的, 因为下一个指令就要用到 p2w 了。

因此, 我们应该显式地调用 destructor 并保留存储空间以便再使用:

// 施行 deconstructor 正确方法
p2w->~Point2w();
p2w = new (arena)Point2w;

剩下的唯一问题是一个设计上的问题: 在我们的例子中对 placement operator 的第一次调用, 会将新 object 构造于原已存在的 object 之上吗? 还是会构造于全
新地址上? 也就是说, 如果我们这样写:

Point2w *p2w = new (arena)Point2w;

我们如何知道 arena 所指的这块区域是否需要先析构? 这个问题在语言层面上并没有解答。'一个合理的习俗是令执行 new 的这一端也要负起执行 destructor 的责任'。


另一个问题关系到 arena 所表现的真正指针类型。'C++Standard 说它必须指向相同类型的 class, 要不就是一块"新鲜"内存, 足够容纳该类型的 object'。注意, 
derived class 很明显并不在被支持之列。对于一个 derived class, 或是其他没有关联的类型, 其行为虽然并非不合法, 却也未经定义。

char *arena = new char[1024];

Point2w *p2w = new (arena)Point2w;



// !! 6.3 临时性对象（Temporary Objects）

如果我们有一个函数, 原型如下:

T operator+(const T&, const T&);

以及两个 T objects, a 和 b,那么

a + b;

可能会导致一个临时性对象, 以放置传回的对象。'是否会导致一个临时时性对象, 视编译器的进取性(aggressiveness) 以及上述操作发生时的程序语境
(program context) 而定'。

例如下面这个片段:

T a,b;
T c = a + b;

编译器会产生一个临时性对象, 放置 a+b 的结果, 然后再使用 T 的 copy constructor, 把该临时性对象当做 c 的初始值。'然而比较更可能的转换是直接以拷贝构造的
方式,将 a+b 的值放到 c 中',于是就不需要临时性对象,以及对其 constructor 和 destructor 的调用了。

此外, 视 operator+() 的定义而定, named return value(NRV) 优化也可能实施起来。'这将导致直接在上述 c 对象中求表达式结果',避免执行 copy constructor
和具名对象(named object)的 destructor。

'三种方式所获得的 c 对象, 结果都一样。其间的差异在于初始化的成本'。一个编译器可能给我们任何保证吗 ? 严格地说是没有。C++Standard 允许编译器对于临时性对象
的产生有完全的自由度:

在某些环境下, 由 processor 产生临时性对象是有必要的, 或是比较方便的。如此的临时性对象由编译器来定义(C++Standard)。


理论上, C++Standard 允许编译器厂商有完全的自由度。但实际上, 由于市场的竞争, 几乎保证任何表达式(expression)如果有这种形式:

T c = a + b;

而其中的加法运算符被定义为:

T operator+(const T&, const T&);

那么实现时根本不产生一个临时性对象。

然而请你注意, 意义相当的 assignment 的 statement:

c = a + b;

不能够忽略临时性对象。反而, 它会导致下面的结果:

// C++ 伪代码
T temp;
temp.operator(a,b);
c.operator=(temp);

temp.T::~T();

所以这样的初始化操作:

T c = a + b;

总是比下面的操作更有效率地被编译器转换:

c = a + b;

第三种运算形式是, 没有出现目标对象:

a + b;

这时候有必要产生一个临时对象以放置运算后的结果。虽然看起来有点怪异, 但这种情况实际上在子表达式(subexpressions)中十分普遍.

例如, 如果我们这样写:

std::string s("hello"), t("world"), u("!");

那么不论:

std::string v;
v = s + t + u;

或

print("%s\n",s + t);

都会导致产生一个临时对象, 与 s+t 相关联。


最后一个表达式带来一些秘教式的论题, 那就是"临时对象的生命期"。

这个论题颇值得深入探讨。在 Standard C++ 之前, 临时对象的生命 (也就是说它的 destructor 何时实施) 并没有显式指定, 而是由编译厂商自行决定。换句话说,
上述的 printf() 并不保证安全, 因为它的正确性和 s+t 何时被摧毁有关。

如果临时对象在调用 printf() 之前就被摧毁了, 经由 conversion 运算符交给它的地址就是不合法的。真正的结果视底部的 delete 运算符在释放内存时的进取性而定。
某些编译器可能会把这块内存标示为 free, 不以任何方式改变其内容。在这块内存被其他地方宣称"主权"之前, 只要它还没有被 deleted 掉, 它就可以被使用。虽然对于
软件工程而言这不足以作为模范, 但像这样, 在内存被释放之后又再被使用, 并非罕见。事实上 malloc() 的许多编译器会提供一个特殊的调用操作:

malloc(0);

它正是用来保证上述行为的。

例如, 下面是对于该算式的一个可能的 pre-Standard 转换。虽然在 pre-Standard 语言定义中是合法的, 却可能造成重大灾难:

std::string temp1 = operator+(s, t);
const char * temp2 = temp1.operator const char*();

// 合法,但过于轻率
temp1.string::~string();
// 这时候并未定义的 temp2 指向何方？
printf("%s\n", temp2);

另一种转换方式是在调用 printf() 之后实施 string destructor。在 C++Standard 之下, 这正是该表达式的必须转换方式。

标准规格上这么说:

'临时性对象的被摧毁, 应该是对完整表达式 (full-expression) 求值过程中的最后一个步骤。该完整表达式造成临时对象的产生'。


什么是一个完整表达式 (full-expression) ? 非正式地说, 它是被涵括的表达式中最外围的那个。

((objA > 1024) && (objB < 23)) ? objA + objB : foo(objA, objB);

一共有五个子算式 (subexpressions), 内含在一个 " ?: 完整表达式"中。任何一个子表达式所产生的任何一个临时对象, 都应该在完整表达式被求值完成后,
才可以毁去。


当临时性对象是根据程序的执行期语意, 有条件地被产生出来时, 临时性对象的生命规则就显得有些复杂了。举个例子, 像这样的表达式:

if( s | t | u |v )

其中的 u+v 子算式只有在 s+t 被评估为 false 时, 才会开始被评估。与第二个子算式有关的临时性对象必须被摧毁, 但是, 很明显地, 不可以被无条件地摧毁。也就是
说, 我们希望只有在临时性对象被产生出来的情况下, 才去摧毁它。


在讨论临时对象的生命规则之前, 标准编译器将临时对象的构造和析构附着于第二个子算式的评估程序。

例如, 对于以下的 class 声明:

class X
{
public:
    X();
    ~X();
    operator int();
    X foo();
private:
    int val;
};


以及对于 class X 的两个 objects 的条件测试:

int main(){
    X xx;
    X yy;
    if(xx.foo() | yy.foo())
    {
        //..
    }
    return 0;
}

临时性对象的生命规则有两个例外。

1. 第一个例外发生在表达式被用来初始化一个 object 时

   C++ Standard要求说:'凡持有表达式执行结果的临时性对象, 应该存留到 object 的初始化操作完成为止'

2. 当一个临时性对象被一个 reference 绑定

   '如果一个临时性对象被绑定于一个 reference, 对象将残留, 直到被初始化之 reference 的生命结束, 或直到临时对象的生命范畴(scope)结束---视哪一种情况
   先到达而定'。


// !! 临时性对象的迷思(神话、传说)

有一种说法是, 由于目前的 C++ 编译器会产生临时性对象, 导致程序的执行比较低效, 因此在工程界或科学界, C++ 只能成为 FORTRAN 以外可怜的第二选择。
更有人认为, 这种效率上的不彰足以掩盖 C++ 在 "抽象化" 上的贡献。




