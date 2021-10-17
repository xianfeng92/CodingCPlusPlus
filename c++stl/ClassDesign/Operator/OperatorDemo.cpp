#include <string>
#include <vector>
#include <iostream>

using namespace std;


int main(int argc, char **argv)
{
    // 当运算符作用于类类型的对象时，可以通过运算符重载重新定义该运算符的含义
    // 当一个重载运算符是成员函数时，this 绑定到左侧运算对象。成员运算符函数的（显示）参数数量比实际运算对象的数量少 1

    int operator=(int, int);// 不能为 int 重定义内置运算符
    // !! 当运算符作用于内置类型的运算对象时，我们无法改变该运算符的含义


    // 直接调用一个重载的运算符函数
    // !! 一个非成员运算符函数的等价调用
    data1 + data2;// 普通的表达式
    operator+(data1,data2);// 等价的函数调用

    // !! 一个成员运算符函数的等价调用
    data1 += data2;//基于“调用”的表达式
    // 将 this 绑定到 data1 的地址，将 data2 作为实参传入函数
    data1.operator+=(data2);// 对成员运算符函数的等价调用

    // !! 通常情况下，不应该重载逗号、取地址、逻辑与和逻辑或运算符

    // !! 使用与内置类型一致的含义 !!
    // 在你开始设计一个类时，首先应该考虑的是这个类应该提供哪些操作。在确定类需要哪些操作之后，才能思考到底应该把每个类
    // 操作设成普通函数还是重载的运算符。
    // 如果某些操作在逻辑上与运算符相关，则它们适用于定义成重载的运算符

    // 1. 如果类执行 IO 操作，则定义移位运算符使其与内置的 IO 保持一致；2. 如果类的某个操作是检查相等性，则定义 operator==,如果类有了 operator==,
    // 意味着它通常也应该有 operator!= 3. 如果类包含一个内在的单序比较操作，则定义 operator<; 如果类有了 operator<, 则它也应该含有其它关系操作
    // 3. 重载运算符的返回类型应该和内置版本的返回类型兼容


    // 尽可能明智的使用运算符重载
    // 每个运算符用于内置类型时都有着比较明确的定义
    // !! 只有当操作的含义对于用户来说清晰明了时才使用运算符；如果用户对运算符有着可能几种不同的理解，则使用这样的运算符将产生二义性

    // !! 选择作为成员或者非成员
    // 1. 赋值（=）、下标（[]）、调用（（））、和成员访问运算符（->）必须作为成员函数
    // 2. 符合运算符一般来说应该是成员
    // 3. 改变对象状态的运算符或者与给定类型密切相关的运算符，如递减、递增和接引用运算符、通常应该是成员
    // 4. 具体对称性的运算符可能转换任意一端的运算对象，例如：算术、相等性、关系和位运算符等，因此通常它们应该是普通的非成员函数


    // 当我们把运算符定义成成员函数时，它的左侧运算对象必须是运算符所属类的一个对象

    string s = "world";
    // 等价于 s.operator("!")
    string t = s + "!"; // 正确，我们能把一个 const char * 加到一个 string 对象中

    // !!! "hi"类型是 const char *,这是一种内置类型，根本就没有成员函数
    string u = "hi" + s; // 如果 + 是 string 的成员，则产生错误； 如果 + 是非成员函数，则等价于 operator+（“hi”,s）


    // !! 输入和输出运算符
    // IO 标准库分别使用 >> 和 << 执行输入和输出操作。 对于这两个运算符来说，IO 库定义了用其读写内置类型的版本，而类则需要自定义适合其对象的新版本
    // 以支持 IO 操作


    // !! 重载输出运算符 << 

    // 通常情况下，输出运算符第一个形参是一个非常量 ostream 对象的引用，第二个形参是一个常量的引用，该常量是我们想要打印的类类型
    // 第二次形参是引用的原因是我们希望避免复制实参；而之所以该形参是常量是因为打印对象不会改变对象的内容
    // !! 为了与其他输出运算符保持一致，operator<< 一般返回它的 ostream 形参

    ostream &operator<<(ostream &os, const Sales_data &item)
    {
        os << item.isbn() << " " << item.units_sold << " "
           << item.revenue << " " << item.avg_price() << endl;
        return os;
    }

    // !! 输出运算符尽量减少格式化操作 !! --- 使得用户有权利控制输出细节
    // 用于内置类型的输出运算符不太会考虑格式化操作，尤其不会打印换行符，用户希望类的输出运算符也像如此行事


    // !! 重载输入运算符 >>
    // 输入运算符必须处理输入可能失败的情况，而输出运算符不需要
    istream &operator>>(istream &in,const Sales_data &item)
    {
        double price;// 不需要初始化，因为我们将先读入数据到 price，然后使用它
        in >> item.bookNo >> item.units_sold >> price;
        if(in)// 检查读取是否成功
        {
            item.revenue = item.units_sold * price;
        }
        else
        {
            item = Sales_data();// 输入失败；对象被赋予默认状态
        }
        return in;
    }

    // 执行输入运算符时可能发生以下错误
    // 1. 当流含有错误类型的数据时读取操作可能失败；2. 当读取操作到达文件末尾或遇到输入流中其它错误时也会失败
    // !! 当读取操作发生错误时，输入运算符应该负责从错误中恢复

    // !! 算术和关系运算符
    // 通常情况下我们将算术和关系运算符定义成非成员函数以允许对左右侧运算对象进行转换
    // 因为这些运算符通常不会改变运算对象的状态，所以形参都是常量的引用

    Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
    {
        Sales_data sum = rhs;
        sum += lhs.sum;
        return sum;// 操作完成后返回局部变量 sum 的副本作为其结果
    }

    // !! 相等运算符
    // 通常情况下，C++ 中的类通过定义相等运算符检验两个对象是否相等
    bool operator==(const Sales_data &lhs, const Sales_data &rhs)
    {
        return lhs.bookNo == rhs.bookNo && lhs.units_sold == rhs.units_sold && lhs.revenue == rhs.revenue;
    }


    bool operator!=(const Sales_data &lhs, const Sales_data &rhs)
    {
        return lhs.bookNo != rhs.bookNo || lhs.units_sold != rhs.units_sold || lhs.revenue != rhs.revenue;
    }


    // !! 关系运算符

    // !! 赋值运算符 --- 把类的一个对象赋值给类的另外一个对象


    // 除了拷贝赋值运算符和移动赋值运算符，标准库 vector 还定义了第三种赋值运算符，该运算符接受花括号内的元素作为参数
    vector<string> v;
    v = {"I","am","Joke"};


    StrVec &StrVec::operator=(initializer_list(list<string> il))
    {
        auto data = alloc_n_copy(il.begin(),il.end());
        free();
        elements = data.first;
        first_free = cap =data.second;
        return *this;
    }

    // !! 复合赋值运算符
    // 为了与内置类型的复合赋值运算符保持一致，类中的复合赋值运算符也要返回左侧对象的引用

    Sales_data &Sales_data::operator+=(const Sales_data &rhs)
    {
        units_sold += rhs.units_sold;
        revenue += rhs.revenue;
        return *this;
    }

    // !! 下标运算符
    // 表示容器的类通常可以通过元素在容器中的位置来访问元素，这些类一般会定义下标运算符 operator[]
    // 下标运算符必须是成员函数

    // 为了与下标的原始定义兼容，下标运算符通过以所访问元素的引用作为返回值。
    // 如果一个类包含下标运算符，则它通常定义两个版本：一个返回普通引用，另一个是类的成员常量返回常量引用

    class StrVec
    {
    public:
        std::string &
        operator[](size_t index)
        {
            return elements[index];
        }

        const std::string &operator(size_t index) const
        {
            return elements[index];
        }

    private:
        std::string *elements; // 指向首元素的指针
    };

    const StrVec cvec = svec;
    if(svec.size() && svec[0].empty())
    {
        svec[0] = "hello";// 正确。对 svec 去下标返回的是 string 的引用
        cvec[0] = "world";// 错误，对 cvec 取下标返回的是常量引用
    }


    // !! 递增和递减运算符
    // 迭代器类中通常会实现递增运算符（++）和递减运算符（--），这两种运算符使得类可以在元素序列中前后移动
    // 为了与内置版本保持一致，前置运算符应该返回递增或递减后对象的引用
    class StrBlobPtr
    {
        public:
        // 递增递减运算符
        StrBlobPtr & operator++();// 前置运算符
        StrBlobPtr & operator--();// 前置运算符
    };

    StrBlobPtr &StrBlobPtr::operator++()
    {
        check(curr, "increment past of StrBlobPtr");
        ++curr; // 将 curr 在当前状态向前移动一个元素
        return *this;
    }


    StrBlobPtr &StrBlobPtr::operator--()
    {
        --curr;
        check(curr, "decrease past begin of StrBlobPtr");
        return *this;
    }


    // 后置运算符版本接受一个额外的（不被使用）int 类型的形参。当我们使用后置运算符时，编译器为这个形参提供一个值为 0 的实参。
    // !! 这个实参的唯一作用就是区分前置和后置运算符
    // 为了与内置版本一致，后置运算符应该返回对象的原值，返回形式是一个值而非引用

    class StrBlobPtr
    {
        public:
        StrBlobPtr operator++(int);
        StrBlobPtr operator--(int);
    }


    // !! 对于后置版本来说，在递增或递减对象之前需要记录当前对象的状态
    StrBlobPtr &StrBlobPtr::operator++(int)
    {
        StrBlobPtr ret = *this;
        ++ *this;// 内部调用前置递增运算符
        return ret;
    }

    StrBlobPtr &StrBlobPtr::operator--(int)
    {
        StrBlobPtr ret = *this;
        --*this;// 内部调用前置递减运算符
        return ret;
    }

    // !! 成员访问运算符
    // !! 箭头运算符（->）必须是类的成员。解引用运算符通常也是类的成员，尽管并非必须如此
    StrBlob a1 = {"how", "are", "you~"};
    StrBlobPtr p(a1); // p 指向 a1 中的 vector
    *p = "okay";
    cout << p->size() << endl; // 打印4，这是 a1 首元素的大小
    cout << (*p).size() << endl;

    // 对于形如 point->mem 的表达式，point 必须是指向类对象的指针或者是一个重载了 operator-> 的类的对象
    // 根据 point 的类型不同分别等价于：
    (*point).mem;          // point 是一个内置的指针类型
    point.operator()->mem; //point 是类的一个对象

    // point->mem 执行过程如下：
    1. 如果 point 是指针，则我们应用内置的箭头运算符，表达式等价于 （*point）.mem,首先解引用该指针，然后从所得到的对象中
    获取指定的成员。如果 point 所指的类型没有 mem 成员，程序会发生错误

    2. 如果 point 是定义了一个 operator-> 的类的对象，则我们使用 point.operator()-> 的结果来获取 mem，其中如果该结果是一个指针
    则指向第一步；如果该结果本身含有重载的 operator()-> 则重复调用当前步骤。最终当这一过程结束时程序或者返回了所需的内容，或者返回了一些
    表示程序错误的信息。

    // !! 重载的箭头运算符必须返回类的指针或自定义了箭头运算符的某个类的对象


    struct absInt
    {
        // 定义了函数调用运算符
        int operator()(int val) const{
            return val < 0 ? -val : val;
        }
    }

    int i = -100；
    // absObj 只是一个对象而非函数，我们也能“调用”该对象。调用对象实际上是在运行重载的调用运算符
    absInt absObj;// 含有函数调用运算符的对象
    int ui = absObj(i);// 将 i 传递给 absObj.operator()

    // !! 如果类定义了调用运算符，则该类的对象称为函数对象（function object）。因为可以调用这种对象，所以我们说这类对象的“行为像函数一样”

    class PrintString
    {
    public:
        PrintString(ostream &o = cout, char c = ' ') : os(o), sep(c) {}

        void operator()(string &s)
        {
            os << s << sep << endl;
        }

    private:
        ostream &os;// 用于写入的目的流
        char sep;// 用于将不同的输出隔开的字符
    }

    PrintString printer；
    string ss("helloworld");
    printer(ss);


    //!! lambda 是函数对象
    // 当我们编写了一个 lambda 后，编译器将该表达式翻译成一个未命名类的未命名对象
    // 在 lambda 表达式产生的类中含有一个重载的函数调用运算符

    stable_sort(words.begin(), words.end(),[](const char *a, const char *b){return a.size() < b.size()});


    // !! 其行为类似于下面这个这个类的一个未命名对象

    class Shortertring
    {
    public:
        bool operator()(const string &s1, const string &s2) const
        {
            return s1.size() < s2.size();
        }
    }

    // 用这个 Shortertring 类替代 lambda 后，我们可以重写并重新调用 stable_sort

    stable_sort(words.begin(), words.end(), Shortertring());


    // 表示 lambda 及相应捕获行为的类
    1. 如我们所知，当一个 lambda 表达式通过引用捕获变量时，将由程序负责确保 lambda 表达式执行时引用所引用的对象确实存在
    因此编译器可以直接使用该引用而无需在 lambda 产生的类中将其存储为数据成员。
    2. 相反，通过值捕获的变量被拷贝到 lambda 中。因此这种 lambda 产生的类必须为每个值捕获的变量建立对应的数据成员，
    同时创建构造函数，令其使用捕获的变量的值来初始化数据成员


    auto wc = find_if(words.begin(), words.end(),[sz](const string &a){return a.size() > sz;});

    // !! 该 lambda 表达式产生的类将形如：

    class SizeCompare
    {
        SizeCompare(size_t n) : sz(n) {} // 该形参对应捕获的变量
        // 该调用运算符的返回类型、形参和函数体都与 lambda 一致
        bool operator()(const string &a) const
        {
            return a.size() > sz;
        }

    private:
        size_t sz;// 该数据成员对应通过值捕获的变量
    }

    // !! 标准库定义的函数对象
    1. 标准库定义了一组表示算术运算符、关系运算符和逻辑运算符的类，每个类分别定义了一个执行命名操作的调用运算符
    2. 这些类都被定义成模版的形式，我们可以为其指定具体的应用类型，这里的类型即调用运算符的形参类型
    3. functional 头文件



    plus<string> stringAdd;// 可对 string 执行加法操作
    plus<int> intAdd;// 可对 int 执行加法操作
    negate<int> negateInt;// 可对 int 执行取反操作
    divides<int> intDivides;// 可对 int 执行除法操作
    modulus<int> modulus;// 可对 int 执行取余操作


    int sum =intAdd(100,22);
    int result = negateInt(-11);


    // !! 在算法中使用标准库函数对象
    // !! 1. 表示运算符的函数对象类常用来替代算法中的默认运算符。
    如我们所知，在默认情况下排序算法使用 operator< 将序列按照升序排序。如果要执行降序排序的话，我们可以
    传入一个 greater 类型的对象。该类将产生一个调用运算符并负责执行待排序类型的大于运算。

    sort(words.begin(), words.end(),greater<string>());

    // 可调用对象与 function
    // C++ 语言中有几种可调用的对象：函数、函数指针、lambda表达式、bind 创建的对象以及重载了函数调用运算符的类

    //!! 调用形式（call signature）指明了调用返回的类型以及传递给调用的实参类型. 一种调用形式对应一个函数类型

    int(int a, int b);// 是一个函数类型，它接受两个 int ，返回一个 int


    // !! 不同类型可能具有相同的调用形式

    // !! 对于几个可调用对象共享同一种调用形式的情况，有时我们会希望把它们看成具有相同的类型
    // 普通函数
    int add(int a, int b)
    {
        return a + b;
    }

    // lambda 表达式，其产生一个未命名的函数对象类
    auto divideInt = [](int a, int b){return a % b;};

    // 函数对象类
    struct divide
    {
        int operator()(int a, int b)
        {
            return a * b;
        }
    }

    上面这些可调用对象分别对其参数执行不同的算术运算，尽管它们的类型各不相同，但是共享同一种调用形式

    int(int a, int b);

    我们可能希望使用这些可调用对象构建一个简单的桌面计算器。为了实现这一目的，需要定义一个函数表（function table）用于存储指向这些可调用对象的
    “指针”。当程序需要执行某个特定的操作时，从表中查找该调用的函数

    // 构建从运算符到函数指针的映射关系
    map<string, int(*)(int,int)> binops;

    binops.insert({"+",add});
    binops.insert({"-",sub});


    //!! 标准库 functional 类型

    // functional 是一个模版，当创建具体的 function 类型时，必须提供额外的信息（该functional类型能够表示的对象的调用形式）

    function<int(int,int)> f1 = add;

    function<int(int,int)> f2 = divide();

    function<int(int,int)> f3 = [](int a, int b){return a + b;};

    cout << f1(1,23) << endl;
    cout << f2(2,3) << endl;
    cout << f3(2,909) << endl;


    map<string,function<int(int,int)>> binops = {
        {"+",add},// 函数指针
        {"-",std::minus<int>()},// 标准库函数对象
        {"/",divide()},// 用户自定义函数对象
        {"*",[](int a, int b) {return a*b;}},// 未命名的 lambda 对象
        {"%",mod}};// 命了名的 lambda 对象

    我们的 map 中包含 5 个元素，尽管其中的可调用对象的类型各不相同，我们仍然能够把所以这些类型都存储在同一个
    function<int(int,int)> 类型中。
    当我们索引 map 时将会得到一个 function<int(int,int)> 对象的引用。 function<int(int,int)> 类型重载了调用运算符，该调用运算符接受它
    自己的实参，然后将其传递给存好的可调用对象。

    binops["+"](1,2);// 调用 add(1,2)
    binops["-"](1,2);// 调用 minus<int> 对象的调用运算符
    binops["*"](1,2);// 调用 lambda 函数对象


    




















}