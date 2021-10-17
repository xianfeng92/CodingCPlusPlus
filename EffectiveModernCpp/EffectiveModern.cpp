
//!!----------------------------------------------------------------

条款五：优先使用 auto 而非显式类型声明

// auto 变量从他们的初始化推导出其类型，所以它们必须被初始化
int x1;  // potentially uninitialized
auto x2;     // error! initializer required
auto x3 = 0; // fine, x's value is well-defined

auto 变量一定要被初始化，并且对由于类型不匹配引起的兼容和效率问题有免疫力，可以简单化代码重构，一般会比显式的声明类型敲击更少的键盘


//!!----------------------------------------------------------------

条款七：区别使用()和{}创建对象

// !! C++11 初始化对象的语法选择既丰富得让人尴尬又混乱得让人糊涂。一般来说，初始化值要用()或者{}括起来或者放到等号"="的右边
int x(0);// 使用小括号初始化
int y = 0;// 使用"="初始化
int z{1};// 使用花括号初始化



Widget w;// 调用默认构造函数
Widget w2 = w; // 不是赋值运算，调用拷贝构造函数
w = w2; // 是赋值运算，调用拷贝赋值运算符（copy operator=）


// !! C++11 使用统一初始化（uniform initialization）来整合这些混乱且不适于所有情景的初始化语法，所谓统一初始化是指使用单一初始化语法在任何地方


// 1.括号初始化让你可以表达以前表达不出的东西。使用花括号，指定一个容器的元素变得很容易
std::vector<int> vec{1,2,3};// vec 的内容为 1，2，3

// 2.括号初始化也能被用于为非静态数据成员指定默认初始值。C++11允许"="初始化不加花括号也拥有这种能力
class Widget
{
    //...
    private:
    int x{9};//没问题，x初始值为9
    int y = 0;//也可以
    int z(0); //错误！
}


// 3.不可拷贝的对象（例如std::atomic）可以使用花括号初始化或者小括号初始化
std::atomic<int> ai1{12};// 没问题
std::atomic<int> ai2(12);// 没问题
std::atomic<int> ai3 = 0;//错误！


因此我们很容易理解为什么括号初始化又叫统一初始化，在 C++ 中这三种方式都被指派为初始化表达式，但是只有括号任何地方都能被使用

// !! 4.括号表达式有一个异常的特性，它不允许内置类型间隐式的变窄转换（narrowing conversion）

double x,y,z;
int sum{x+y+z};// 错误！double 的和可能不能表示为 int


// !!使用小括号和"="的初始化不检查是否转换为变窄转换，因为由于历史遗留问题它们必须要兼容老旧代码
int sum2(x + y +z);             //可以（表达式的值被截为int）
int sum3 = x + y + z;           //同上


// !! 括号表达式对于C++最令人头疼的解析问题有天生的免疫性
// C++ 规定任何能被决议为一个声明的东西必须被决议为声明。这个规则的副作用是让很多程序员备受折磨：当他们想创建一个使用默认构造函数构造的对象，却不小心变成了函数声明
Widget w1(10);// 使用实参 10 调用 Widget 的一个构造函数

//如果你尝试使用相似的语法调用没有参数的Widget构造函数，它就会变成函数声明
Widget w2();// 最令人头疼的解析！声明一个函数 w2，返回 Widget

// 由于函数声明中形参列表不能使用花括号，所以使用花括号初始化表明你想调用默认构造函数构造对象就没有问题
Widget w3{};// 调用没有参数的构造函数构造对象


// !! 括号初始化的缺点是有时它有一些令人惊讶的行为。这些行为使得括号初始化、std::initializer_list和构造函数重载决议本来就不清不楚的暧昧关系进一步混乱

// 在构造函数调用中，只要不包含 std::initializer_list 形参，那么花括号初始化和小括号初始化都会产生一样的结果

class Widget
{
    public:
    Widget(int i, bool b);
    Widget(int i, double d);
    //...
};

Widget w1(10, true);            //调用第一个构造函数
Widget w2{10, true};            //也调用第一个构造函数
Widget w3(10, 5.0);             //调用第二个构造函数
Widget w4{10, 5.0};             //也调用第二个构造函数


// 如果有一个或者多个构造函数的声明一个 std::initializer_list 形参，使用括号初始化语法的调用更倾向于适用 std::initializer_list 重载函数
class Widget { 
public:  
    Widget(int i, bool b);      //同上
    Widget(int i, double d);    //同上
    Widget(std::initializer_list<double> il);      //新添加的
    //...
}; 


Widget w1(10, true);    //使用小括号初始化，同之前一样,调用第一个构造函数
Widget w2{10, true};    //使用花括号初始化，但是现在调用 std::initializer_list 版本构造函数(10 和 true 转化为 double)
Widget w3(10, 5.0);     //使用小括号初始化，同之前一样,调用第二个构造函数 
Widget w4{10, 5.0};     //使用花括号初始化，但是现在调用 std::initializer_list 版本构造函数(10 和 5.0 转化为 double)



class Widget { 
public:  
    Widget();                                   //默认构造函数
    Widget(std::initializer_list<int> il);      //std::initializer_list构造函数

    // …                                           //没有隐式转换函数
};

Widget w;// 调用默认构造函数
Widget w1{};// 也调用默认构造函数
Widget w2();// 最令人头疼的解析！声明一个函数
Widget w3({});// 使用空花括号列表调用 std::initializer_list 构造函数

std::vector<int> v1(10,20);  // 使用非 std::initializer_list 构造函数,创建一个包含 10 个元素的 std::vector，所有的元素的值都是 20
std::vector<int> v2{10,20}; // 使用 std::initializer_list 构造函数,创建包含两个元素的std::vector，元素的值为 10 和 20


// !!请记住

1. 花括号初始化是最广泛使用的初始化语法，它防止变窄转换，并且对于 C++ 最令人头疼的解析有天生的免疫性
2. 在构造函数重载决议中，花括号初始化尽最大可能与 std::initializer_list 参数匹配，即便其他构造函数看起来是更好的选择
3. 对于数值类型的 std::vector 来说使用花括号初始化和小括号初始化会造成巨大的不同

//!!----------------------------------------------------------------

条款八：优先考虑 nullptr 而非 0 和 NULL


// 在 C++98 中，对指针类型和整型进行重载意味着可能导致奇怪的事情
void f(int);
void f(double);
void f(void*);

f(0);// 调用f(int)而不是f(void*)
f(NULL);// 可能不会被编译，一般来说调用f(int),绝对不会调用f(void*)
// !! 这种违反直觉的行为导致 C++98 程序员都将避开同时重载指针和整型作为编程准则

// !! nullptr 的优点是它不是整型。老实说它也不是一个指针类型，但是你可以把它认为是所有类型的指针
f(std::nullptr);//调用重载函数 f(void*) 版本

auto result = findRecord();
if(result == 0)
{
    // do someting
}


auto result1 = findRecord();// 这就没有任何歧义：result 的结果一定是指针类型
if(result1 == std::nullptr)
{
    // do something
}

int f1(std::shared_ptr<Widget> spw);
double f2(std::unique_ptr<Widget> upw);
bool f3(Widget* pw);


std::mutex f1m,f2m,f3m;

using MuxGuard = std::lock_guard(std::mutex);

// ...

{  
    MuxGuard g(f1m);            //为f1m上锁
    auto result = f1(0);        //向f1传递0作为空指针
}                               //解锁 


{  
    MuxGuard g(f2m);            //为f2m上锁
    auto result = f2(NULL);     //向f2传递NULL作为空指针
}                               //解锁 

{
    MuxGuard g(f3m);            //为f3m上锁
    auto result = f3(nullptr);  //向f3传递nullptr作为空指针
}                               //解锁 
























