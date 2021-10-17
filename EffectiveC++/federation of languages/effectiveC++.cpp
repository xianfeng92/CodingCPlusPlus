


// !! 将 C++ 视为 federation of languages（语言联合体）
int main(int argc, char **argv)
{
    ## Item 1: 将 C++ 视为 federation of languages（语言联合体）

    1. 最初，C++ 仅仅是在 C 的基础上附加了一些 object-oriented 的特性。C++ 最初的名称—— "C with Classes" 就非常直观地表现了这一点
    2. 作为一个语言的成熟过程，C++ 的成长大胆而充满冒险，它吸收的思想，特性，以至于编程策略与 C with Classes 越来越不同
    3. 今天的 C++ 已经成为一个 multiparadigm programming language（多范式的编程语言），一个囊括了 procedural（过程化），
       object-oriented（面向对象），functional（函数化），generic（泛型）以及 metaprogramming（元编程）特性的联合体

    //!! 为了感受 C++，你必须将它的主要的 sublanguages 组织到一起。幸运的是，它只有 4 个:
    1. C ——归根结底，C++ 依然是基于 C 的--->在很多方面。C++ 提出了比相应的 C 版本更高级的解决问题的方法
    2. Object-Oriented C++ —— C++ 的这部分就是 C with Classes 涉及到的全部---C++ 的这一部分直接适用于 object-oriented design 的经典规则
    3. Template C++ ——这是 C++ 的 generic programming（泛型编程）部分
    4. STL —— STL 是一个 template library（模板库），但它一个非常特殊的 template library（模板库）

    // !! effective C++ programming 规则的变化，依赖于你使用 C++ 的哪一个部分
    1. 在头脑中保持这四种 sublanguages，当你从一种 sublanguage 转到另一种时，为了高效编程你需要改变你的策略

   // !!---------------------------------------------------------------------------------------------------

    ## Item 2: 用 consts, enums 和 inlines 取代 #define

    1."用 compiler 取代 preprocessor" 也许更好一些，因为 #define 根本就没有被看作是语言本身的一部分
    #define ASPECT_RATIO 1.653
    // compiler 也许根本就没有看见这个符号名 ASPECT_RATIO，在编译器得到源代码之前，这个名字就已经被 preprocessor 消除了。
    // 结果，名字 ASPECT_RATIO 可能就没有被加入 symbol table

    // !! 解决方案是用 constant 来取代 macro（宏）
    const double AspectRatio = 1.653;// 作为一个语言层面上的常量，AspectRatio 被编译器明确识别并确实加入 symbol tables

    // 头文件中，定义一个基于 char * 的字符串常量
    const char* const authorname = "Tony Scope";

    //!!!! string objects 通常比它的 char*-based（基于 char*）的更可取 ~~~~~
    const std::string authorname("Tony Scope");


    // !! class-specific constants（类内部专用的常量）

    class GamePlayer
    {
        // 通常，C++ 要求你为你使用的任何东西都提供一个 definition（定义），但是一个 static 的 integral type（例如：integers（整型），chars，bool）
        // 的 class-specific constants 是一个例外
        static const int NUM_PLAYERS = 5; // constant declaration
        int scores[NUM_PLAYERS];
        /...
    }

   // !!---------------------------------------------------------------------------------------------------

    ##  Item 3: 只要可能就用 const
    // 关于 const 的一件美妙的事情是它允许你指定一种 semantic（语义上的）约束: 一个特定的 object 不应该被修改,而编译器将执行这一约束


    // 如果 const 出现在 * 左边，则指针 pointed to 的内容为 constant（常量）
    // 如果 const 出现在 * 右边，则 pointer itself 为 constant（常量）
    // 如果 const 出现在 * 两边，则两者都为 constant（常量）
    char greeting[] = "Hello";
    char *p = greeting;// non-const pointer, non-const data
    const char * pp = greeting;// non-const pointer,const data
    char * const ppp = greeting;// const pointer,non-const data
    const char * const ppppp = greeting;// const pointer,const data

    void f1(const Widget * pw)// f1 takes a pointer to a constant Widget object

    void f2(Widget const *pw); // so does f2

    // !! STL iterators（迭代器）以 pointers（指针）为原型
    std::vector<int> vec;
    /........
    std::vector::iterator iter = vec.begin();// iter acts like a T* const, 不能改变 pointer 的指向的位置
    *iter = 10086;//  OK, changes what iter points to
    ++ iter;// error! iter is const

    std::vector<int> cvec;
    /........
    std::vector::iterator cIter = cvec.cbegin();// cIter acts like a const T*
    *cIter = 10086;// error! *cIter is const
    ++cIter;     // fine, changes cIter



    // !! const member functions（const 成员函数）
    // member functions（成员函数）被声明为 const 的目的是标明这个 member functions（成员函数）可能会被 const objects（对象）调用
    // 1. 首先，它使一个 class（类）的 interface（接口）更容易被理解---知道哪个函数可以改变 object 而哪个不可以是很重要的
    // 2. 它们可以和 const objects（对象）一起工作
    class TextBlock
    {
        public:
        /...
        const char& operator[](std::size_t position)
        {
            return text[position];// const objects
        }
        char& operator[](std::size_t position)
        {
            return text[position]; // non-const objects
        }
    };

    // 提升一个 C++ 程序的性能的基本方法就是 pass objects by reference-to-const（以传引用给 const 的方式传递一个对象）
    void print(const TextBlock& ctb)// in this function, ctb is const
    {
        std::cout << ctb[0];// calls const TextBlock::operator[]
    }


   // !!---------------------------------------------------------------------------------------------------
    Item 4: 确保 objects（对象）在使用前被初始化

    // !! C++ 看上去在对象的值的初始化方面变化莫测
    class Point
    {
        int i,j;
    };
    /...
    // p 的 data members（数据成员）有时会被初始化（为 0），但有时没有. 读取一个 uninitialized values 会引起 undefined behavior（未定义行为)
    Point p;

    // 通常，如果你使用 C++ 的 C 部分，而且 initialization （初始化）可能会花费一些运行时间，它就不能保证发生。如果你使用 C++ 的 non-C 部分，事情会有些变化
    // 这就是为什么一个 array（来自 C++ 的 C 部分）不能确保它的元素被初始化，但是一个 vector （来自 C++ 的 STL 部分）就能够确保
    int x = 0; // manual initialization of an int
    const char *text = "A C-style string"; // manual initialization of a pointer
    double d; // "initialization" by reading from
    std::cin >> d; // an input stream


    // !! 确保 all constructors（所有的构造函数）都初始化了 object 中的每一样东西
    class PhoneNumber{};

    class ABEnter
    {
    public:
        ABEntry(const std::string &name, const std::string &address,
                const std::list<PhoneNumber> &phones);

    private:
        std::string theName;

        std::string theAddress;

        std::list<PhoneNumber> thePhones;

        int num TimesConsulted;
    };

    // !! C++ 的规则规定一个 object 的 data members（数据成员）在进入 constructor（构造函数）的函数体之前被初始化
    ABEntry::ABEntry(const std::string &name, const std::string &address,
                     const std::list<PhoneNumber> &phones)
    {
         // 这样做虽然使得 ABEntry objects（对象）具有了你所期待的值，但还不是最佳的实践
        // initialization（初始化）发生得更早 —— 在进入 ABEntry 的 constructor（构造函数）的函数体之前，它们的 default constructors（缺省的构造函数）已经被自动调用
        theName = name; // these are all assignments,

        theAddress = address; // not initializations

        thePhones = phones;

        numTimesConsulted = 0;
    }

    // 一个更好的写 ABEntry constructor（构造函数）的方法是用 member initialization list（成员初始化列表）来代替 assignments（赋值)
    ABEntry::ABEntry(const std::string &name, const std::string &address,
                     const std::list<PhoneNumber> &phones)
                     // 这个 constructor（构造函数）的最终结果和前面那个相同，但是通常它有更高的效率
        : theName(name),
          theAddress(address), // these are now all initializations
          thePhones(phones),
          numTimesConsulted(0)

    {

    } // the ctor body is now empty


    // !! 一个 static object（静态对象）的生存期是从它创建开始直到程序结束,主要包括：
    // 1. global objects（全局对象）
    // 2. objects defined at namespace scope（定义在命名空间范围内的对象）
    // 3. objects declared static inside classes（在类内部声明为静态的对象）
    // 4. objects declared static inside functions（在函数内部声明为静态的对象）
    // 5. objects declared static at file scope（在文件范围内被声明为静态的对象）
    // !! 程序结束时 static objects（静态对象）会自动销毁，也就是当 main 停止执行时会自动调用它们的 destructors（析构函数）


    // 一个 translation unit（编译单元）是可以形成一个单独的 object file（目标文件）的 source code（源代码）
    // 基本上它是一个单独的 source file（源文件），再加上它全部的 #include 文件

    class FileSystem
    {
        public:
        /...
        std::size_t numDisks() const;// one of many member functions
        /...
    };

    extern FileSystem tfs;// object for clients to use;

    class Directory
    { // created by library client

    public:
        Directory(params);
        ...
    };

    Directory::Directory(params)
    {
        // ... 
        std::size_t disks = tfs.numDisks(); // use the tfs object
        // ...
    }

    Directory tempDir(params); // directory for temporary files

    // 现在 initialization order（初始化顺序）的重要性变得明显了：除非 tfs 在 tempDir 之前初始化，否则，tempDir 的 constructor（构造函数）
    // 就会在 tfs 被初始化之前试图使用它。但是，tfs 和 tempDir 是被不同的人于不同的时间在不同的 source files（源文件）中创建的——它们是定义在不同 
    // translation units（编译单元）中的 non-local static objects（非局部静态对象）

    // !! 定义在不同编译单元内的非局部静态对象的初始化的相对顺序是没有定义的

    // 用 local static objects（局部静态对象）取代 non-local static objects（非局部静态对象）
    // 这个方法建立在 C++ 保证 local static objects（局部静态对象）的会在“该函数被调用期间”，“首次该对象的定义”时被初始化
    class FileSystem {};

    FileSystem& fs()
    {
        static FileSystem fs;
        return fs;
    }

    class Directory{};

    Directory::Directory(params)
    {
        /...
        std::size_t disks = tfs().numDisks();
        /...
    }

    Directory &tempDir()     // this replaces the tempDir object; it
    {                        // could be static in the Directory class
        static Directory td; // define/initialize local static object
        return td;           // return reference to it
    }

    // !! Things to Remember
    1. 手动初始化 built-in type 的 objects（对象），因为 C++ 只在某些时候才会自己初始化它
    2. 在 constructor（构造函数）中，用 member initialization list（成员初始化列表）代替函数体中的 assignment（赋值）
    3. 通过用 local static objects（局部静态对象）代替 non-local static objects（非局部静态对象）来避免跨 translation units（编译单元）的 
       initialization order problems（初始化顺序问题）

    // !!----------------------------------------------------------------
    
    Item 5: 了解 C++ 为你偷偷地加上和调用了什么函数
    // 编译器可以隐式生成一个 class（类）的 default constructor（缺省构造函数），copy constructor（拷贝构造函数），
    // copy assignment operator（拷贝赋值运算符）和 destructor（析构函数）
    class Empty{};


    class Empty
    {
        public:
        Empty(){}
        Empty(const Empty & rhs){}
        ~Empty(){}
        Empty & operator=(const Empty & rhs){}
    };

    Empty e1; // default constructor

    Empty e2(e1); // copy constructor

    e2 = e1; // copy assignment operator

    // !! default constructor（缺省构造函数）和 destructor（析构函数）主要是给编译器一个地方放置 "behind the scenes" code（“幕后”代码）
    // 诸如 base classes（基类）和 non-static data members（非静态数据成员）的 constructors（构造函数） 和 destructor（析构函数）的调用

    // !!  copy constructor（拷贝构造函数）和 copy assignment operator（拷贝赋值运算符），compiler-generated versions（编译器生成版本）
    // 只是简单地从 source object（源对象）拷贝每一个 non-static data member（非静态数据成员）到 target object（目标对象）



    template <typename T>
    class NamedObject
    {
    public:
        // !! 因为 NamedObject 中声明了一个 constructors（构造函数），编译器就不会再生成一个 default constructor（缺省构造函数）
        NamedObject(const char *name, const T &value);
        NamedObject(const std::string &name, const T &value);
        


    private:
        std::string nameValue;
        T objectValue;
    };

    NamedObject<int> no1("Smallest Prime Number", 2);
    // NamedObject 既没有声明 copy constructor（拷贝构造函数）也没有声明 copy assignment operator（拷贝赋值运算符），所以编译器将为其生成这些函数
    NamedObject<int> no2(no1); // calls copy constructor



    template <typename T>
    class NamedObject
    {
    public:
        NamedObject(std::string &name, const T &value);

    private:
    private:
        // 如果你希望一个包含 reference member（引用成员）的 class（类）支持 assignment（赋值），你必须自己定义 copy assignment operator
        std::string &nameValue; // this is now a reference
        const T objectValue;    // this is now const
    };

    //!! Things to Remember
    1. 编译器可以隐式生成一个 class（类）的 default constructor（缺省构造函数），copy constructor（拷贝构造函数），
       copy assignment operator（拷贝赋值运算符）和 destructor（析构函数）


    // !!----------------------------------------------------------------

    Item 6: 如果你不想使用 compiler-generated functions（编译器生成函数），就明确拒绝

    class HomeForSale{ };// 表示被出售的房屋

    HomeForSale h1;
    HomeForSale h2;
    HomeForSale h3(h1); // attempt to copy h1 — should not compile!
    h1 = h2; // attempt to copy h2 — should not compile!

    // 通常，如果你不希望一个 class（类）支持某种功能，你可以简单地不声明赋予它这种功能的函数

    // 如果你不声明 copy constructor（拷贝构造函数）或 copy assignment operator（拷贝赋值运算符），编译器也可以替你生成它们。你的 class 还是会支持 copying
    // 另一方面，如果你声明了这些函数，你的 class 依然会支持 copying, 而我们此时的目的却是 prevent copying（防止拷贝）


    // !! 通过显式声明一个 member function（成员函数），可以防止编译器生成它自己的版本，而且将这个函数声明为 private 的，可以防止别人调用它
    class HomeForSale
    {
    public:
        //...
    private:// !! 编译器将阻止客户拷贝 HomeForSale objects 的企图
        HomeForSale(const HomeForSale &rhs); //declarations only
        HomeForSale &operator=(const HomeForSale &rhs);
    };

    // 声明一个 prevent copying 而特意设计的 base class
    class UnCopyable
    {
    public:
        UnCopyable();
        ~UnCopyable();

    private:
        UnCopyable(const UnCopyable &rhs);
        UnCopyable &operator=(const UnCopyable &rhs);
    };

    // 为了阻止拷贝 HomeForSale objects，我们现在必须让它从 UnCopyable 继承

    class HomeForSale :public UnCopyable// HomeForSale class no longer declares copy ctor or copy assign. operator
    {
        //...
    }

    // !! Things to Remember

    1. 为了拒绝编译器自动提供的机能，将相应的 member functions（成员函数）声明为 private，而且不要给出 implementations（实现）
    // 使用一个类似 UnCopyable 的 base class 是方法之一


   // !!----------------------------------------------------------------

   Item 8: 防止因为 exceptions 而离开 destructors（析构函数）

   // C++ 并不禁止从 destructors 中引发 exceptions ，但是它坚决地阻止这样的实践
   class Widget
   {
       public:
       //...
       ~Widget()
       {
           // assume this might emit an exception
       }
   };

   void doSomeThing()
   {
       std::vector<Widget> v;
       //...
   }//  v is automatically destroyed here,当 vector v 被析构时，它有责任析构它包含的所有 Widgets

   // !! Things to Remember
   1. destructor（析构函数）应该永不引发 exceptions（异常）。如果 destructor（析构函数）调用了可能抛出异常的函数，destructor（析构函数）应该捕捉所有异常，
      然后抑制它们或者终止程序
   2. 如果 class（类）客户需要能对一个操作抛出的 exceptions（异常）做出回应，则那个 class（类）应该提供一个常规的函数（也就是说，non-destructor（非析构函数））来完成这个操作


   // !!----------------------------------------------------------------

   Item 13: 使用对象管理资源

   class Investment { };

   Investment* createInvestment(); //  return ptr to dynamically allocated object in the Investment hierarchy

   void f()
   {
       Investment *pInvest = createInvestment();
       // ...
       // !! 依赖于 f 总能到达它的 delete 语句根本靠不住
       // 如果这个 delete 被跳过，我们泄漏的不仅仅是容纳 investment 对象的内存，还包括那个对象持有的任何资源
       delete pInvest;
   }

   // !! 将资源放到一个对象的内部，我们可以依赖 C++ 的自动地调用析构函数来确保资源被释放
  // 为了确保 createInvestment 返回的资源总能被释放，我们需要将那些资源放入一个类中，这个类的析构函数在控制流程离开 f 的时候会自动释放资源


  // !!----------------------------------------------------------------

  Item 16: 使用相同形式的 new 和 delete

  std::string *strArray = new std::string[100];
  //...
  delete strArray;// stringArray 指向的 100 个 string 对象中的 99 个不太可能被完全销毁，因为它们的析构函数或许根本没有被调用


  // 当你使用了一个 new 表达式,有两件事情会发生:
  1. 首先，分配内存---通过一个被称为 operator new 的函数
  2. 第二，一个或多个构造函数在这些内存上被调用

  // 当你使用一个 delete 表达式，有另外的两件事情会发生:
  1. 一个或多个析构函数在这些内存上被调用
  2. 内存被回收


  // 对于 delete 来说有一个大问题：在要被删除的内存中到底驻留有多少个对象？这个问题的答案将决定有多少个析构函数必须被调用
  // 一个数组的内存布局通常包含数组的大小，这样可以使得 delete 更容易知道有多少个析构函数需要被调用。而一个单一对象的内存中缺乏这个信息

  // !! 当你对一个指针使用 delete，delete 知道是否有数组大小信息的唯一方法就是由你来告诉它
  1. 如果你在你使用的 delete 中加入了方括号，delete 就假设那个指针指向的是一个数组。否则，就假设指向一个单一的对象

  std::string *p1 = new std::string;
  std::string *p2 = new std::string[10086];
  // ...
  delete p1;                     // delete an object
  delete [] p2;                  // delete an array of objects

  // !! 规则很简单: 如果你在 new 表达式中使用了 []，你也必须在相应的 delete 表达式中使用 []。如果你在 new 表达式中没有使用 []，在匹配的 delete 表达式中也不要使用 []

 // !!----------------------------------------------------------------

 Item 17: 在一个独立的语句中将 new 出来的对象存入智能指针

 // !! 在一个独立的语句中将 new 出来的对象存入智能指针。如果疏忽了这一点，当异常发生时，可能引起微妙的资源泄漏

 // !!----------------------------------------------------------------
 Item 18: 使接口易于正确使用，而难以错误使用

// 引入简单的包装类型来区别日，月和年，并将这些类型用于 Data 的构造函数
 struct Day
 {
     explicit Day(int day):val(day){}
     int val;
 };

 struct Month
 {
     explicit Month(int month):val(month){}
     int val;
 };

 struct Year
 {
     explicit Year(int year):val(year){}
     int val;
 };


 class Data
 {
     public:
     Data(const Month& month, const Day& day,const Year& year);
     //...
 };

Date d(Day(30), Month(3), Year(1995));    // error! wrong types

Date d(Month(3), Day(30), Year(1995));    // okay, types are correct


 // !!----------------------------------------------------------------
Item 20: 用 pass-by-reference-to-const（传引用给 const）取代 pass-by-value（传值）

// !! 缺省情况下，C++ 以传值方式将对象传入或传出函数（这是一个从 C 继承来的特性）
1. 除非你特别指定其它方式，否则函数的参数就会以实际参数（actual argument）的拷贝进行初始化，而函数的调用者会收到函数返回值的一个拷贝
   这个拷贝由对象的拷贝构造函数生成, 这就使得传值（pass-by-value）成为一个代价不菲的操作


class Person
{
public:
    Person();
    virtual ~Person();
    //...
private:
    std::string name;
    std::string address;
};


class Student:public Person
{
public:
    Student();
    virtual ~Student();
    //...
private:
    std::string schoolName;
    std::string schoolAddress;
};



bool validateStudent(Student s); // function taking a Student  by value

Student plato;

// Student 的拷贝构造函数被调用，用 plato 来初始化参数 s,同样明显的是，当 validateStudent 返回时，s 就会被销毁
// !! 这个函数的参数传递代价是一次 Student 的拷贝构造函数的调用和一次 Student 的析构函数的调用
bool platoIsOK = validateStudent(plato);
// Student 对象的拷贝被销毁时，每一个构造函数的调用都对应一个析构函数的调用，所以以传值方式传递一个 Student 的全部代价是六个构造函数和六个析构函数！


// !! 传引用给 const（pass by reference-to-const）
// 这样做非常有效：没有任何构造函数和析构函数被调用，因为没有新的对象被构造。被修改的参数声明中的 const 是非常重要的
bool validateStudent(const Student& s);


//!! 如果你掀开编译器的盖头偷看一下，你会发现用指针实现引用是非常典型的做法，所以以引用传递某物实际上通常意味着传递一个指针
// !! 由此可以得出结论
1. 如果你有一个内建类型的对象（例如，一个 int），以传值方式传递它常常比传引用方式更高效; 同样的建议也适用于 STL 中的迭代器和函数对象（function objects）



// !! Things to Remember

1. 用传引用给 const 取代传值。典型情况下它更高效而且可以避免切断问题
2. 这条规则并不适用于内建类型及 STL 中的迭代器和函数对象类型。对于它们，传值通常更合适


 // !!----------------------------------------------------------------

Item 21: 当你必须返回一个对象时不要试图返回一个引用

class Rationale
{
public:
    Rationale(int numerator = 0, int denominator = 1);
    //...
private:
    int n, d;
// return type is const
friend const Rational operator*(const Rational &lhs,const Rational &rhs);
};

// !! 请记住一个引用仅仅是一个名字，一个实际存在的对象的名字。无论何时只要你看到一个引用的声明，你应该立刻问自己它是什么东西的另一个名字，
// !! 因为它必定是某物的另一个名字



// !! 一个函数创建一个新对象仅有两种方法：在栈上或者在堆上。栈上的可以通过定义一个局部变量而生成
const Rational& operator*(const Rational& lhs,   // warning! bad code!
                          const Rational& rhs)
{
  // !! 基于栈上的对象可以通过定义一个局部变量而生成
  Rational result(lhs.n * rhs.n, lhs.d * rhs.d);
  return result;
} // 一个严重的问题是这个函数返回一个引向 result 的引用，但是 result 是一个局部对象，而局部对象在函数退出时被销毁

// !! 任何返回一个引向局部变量的引用的函数都是错误的----> 对于任何返回一个指向局部变量的指针的函数同样成立

// !! 基于堆上的对象通过使用 new 创建

const Rational & operator*(const Rational & lhs,const Rational & rhs)// warning! more bad code
{
    Rational * result = new Rational(lhs.n * rhs.n, lhs.d * rhs.d);
    return *result;
}// 现在你有另一个问题：谁是删除你用 new 出来的对象的合适人选？????

// !! 如果需要在返回一个引用和返回一个对象之间做出决定，你的工作就是让那个选择能提供正确的行为。让你的编译器厂商去绞尽脑汁使那个选择尽可能地廉价

// !! Things to Remember
1. 绝不要返回一个局部栈对象的指针或引用，绝不要返回一个被分配的堆对象的引用，如果存在需要一个以上这样的对象的可能性时，绝不要返回一个局部 static 对象的指针或引用


// !!----------------------------------------------------------------

Item 22: 将数据成员声明为 private


// 如果你使用函数去访问它的值，很容易就可以实现禁止访问，只读访问和读写访问
class AccessLevels
{
public:
    // ...
    int getReadOnly() const { return readOnly; }
    void setReadWrite(int value) { readWrite = value; }
    int getReadWrite() const { return readWrite; }
    void setWriteOnly(int value) { writeOnly = value; }

private:
    int noAccess; // no access to this int

    int readOnly; // read-only access to this int

    int readWrite; // read-write access to this int

    int writeOnly; // write-only access to this int
};




// !!----------------------------------------------------------------

Item 26: 只要有可能就推迟变量定义

// 只要你定义了一个带有构造函数和析构函数的类型的变量，当控制流程到达变量定义的时候会使你担负构造成本;
// 而当变量离开作用域的时候会使你担负析构成本
// !! 如果有无用变量造成这一成本，你就要尽你所能去避免它

std::string encryptPassword(const std::string &encryptPassword)
{
    using namespace std;
    string encrypted;// 对象 encrypted 在这个函数中并不是完全无用，但是如果抛出了一个异常，它就是无用
    if (password.length() < MinimumPasswordLength)
    {
        throw logic_error("Password is too short");
    }
    // ...                        // do whatever is necessary to place an encrypted version of password in encrypted
    return encrypted;
}

// 你最好将 encrypted 的定义推迟到你确信你真的需要它的时候
std::string encryptPassword(const std::string &encryptPassword)
{
    using namespace std;
    if (password.length() < MinimumPasswordLength)
    {
        throw logic_error("Password is too short");
    }
    string encrypted;
    // ...                        // do whatever is necessary to place an encrypted version of password in encrypted
    return encrypted;
}


// 假设 encryptPassword 的核心部分是在这个函数中完成的
void encrypt(std::string& s); // encrypts s in place


// this function postpones encrypted's definition until
// it's necessary, but it's still needlessly inefficient
std::string encryptPassword(const std::string& password)
{
  ...                                   // check length as above

  string encrypted;                     // default-construct encrypted
  encrypted = password;                 // assign to encrypted

  encrypt(encrypted);
  return encrypted;
}


// 一个更可取得方法是用 password 初始化 encrypted，从而跳过毫无意义并可能很昂贵的缺省构造

// finally, the best way to define and initialize encrypted
std::string encryptPassword(const std::string& password)
{
  ...                                     // check length

  string encrypted(password);             // define and initialize via copy constructor
  encrypt(encrypted);
  return encrypted;
}



// !! 如果一个变量仅仅在一个循环内使用，是循环外面定义它并在每次循环迭代时赋值给它更好一些，还是在循环内部定义这个变量更好一些呢？
// Approach A: define outside loop
Widget w;
for(int i = 0; i < n; i++)
{
    w = some value dependent on i;
    //...
}// 方法 A：1 个构造函数 + 1 个析构函数 + n 个赋值

// Approach B: define inside loop
for(int i = 0; i < n; i++)
{
    Widget w(some value dependent on i);
    //...
}// 方法 B：n 个构造函数 + n 个析构函数

// 对于那些赋值的成本低于一个构造函数/析构函数对的成本的类，方法 A 通常更高效。特别是在 ｎ 变得很大的情况下。否则，方法 B 可能更好一些


// !! Things to Remember

1. 只要有可能就推迟变量定义。这样可以增加程序的清晰度并提高程序的性能


// !!----------------------------------------------------------------

Item 27: 将强制转型减到最少

// !! C++ 同时提供了四种新的强制转型形式

// !! const_cast<T>(expression)
1. const_cast 用于移除类型的 const、volatile 属性。常量指针被转换成非常量指针，并且仍然指向原来的对象；
   常量引用被转换成非常量引用，并且仍然引用原来的对象。

   const char *pc = "hello";
   char *p = const_cast<char*>(pc);


// !! static_cast<T>(expression)

1. 任何编写程序时能够明确的类型转换都可以使用 static_cast.由于不提供运行时的检查，所以叫 static_cast，
   因此，需要在编写程序时确认转换的安全性
2. 主要在以下几种场合中使用:用于类层次结构中，父类和子类之间指针和引用的转换、用于基本数据类型之间的转换，例如把int转char，int转enum等，
   需要编写程序时来确认安全性、把void指针转换成目标类型的指针（这是极其不安全的）

int i, j;
double slope = static_cast<double>(j) / i;
void *p = &d;
double *dp = static_cast<double*>(p);


class Widget {
public:
  explicit Widget(int size);
  ...
};

void doSomeWork(const Widget& w);

doSomeWork(Widget(15)); // create Widget from int with function-style cast

doSomeWork(static_cast<Widget>(15)); // create Widget from int with C++-style cast


// !! dynamic_cast<T>(expression)

1. 相比 static_cast， dynamic_cast 会在运行时检查类型转换是否合法，具有一定的安全性，由于运行时的检查，所以会额外消耗一些性能。
2. dynamic_cast 使用场景与 static 相似，在类层次结构中使用时，上行转换和 static_cast 没有区别，都是安全的；下行转换时，dynamic_cast 会检查转换的类型，相比 static_cast 更安全
3. dynamic_cast 会运行时检查该转换是否类型安全，只在多态类型时合法，即该类至少具有一个虚拟方法


class Base
{
public:
    virtual void print()
    {
        cout << "Base print" << endl;
    }
    void work()
    {
        cout << "Base do work" << endl;
    }
};


class Derived:public Base
{
public:
    virtual void print()
    {
        cout << "Derived print" << endl;
    }
    void work() 
    {
        cout << "Derived do work" << endl;
    }
};

int main(int argc, char* argv[])
{
    Base *pBase = new Derived();
    // !! print()是虚函数，在运行时的类型来决定运行结果
    pBase->print();// Derived print
    // !! work()函数不是虚函数，只是类的普通成员函数，在编译期间决定,所以调用的 Base::work()
    pBase->work();// Base do work

    return 0;
}

// 如果我们希望通过指针调用 Derived::work()，该怎么做呢？
Derived *pp = dynamic_cast<Derived*>(pBase);// 若转型成功，则 dynamic_cast 返回 新类型 类型的值


int main() 
{
    Base *pBase = new Derived();
    pBase->work();
    pBase->print();

    Derived *pDerived = dynamic_cast<Derived*>(pBase);// 向下转换成功，成功返回 Derived *
    if(pDerived != nullptr)
    {
        pDerived->print();
        pDerived->work();
    }


    Base * realBase = new Base();
    pDerived = dynamic_cast<Derived*>(realBase);// 向下转换失败，返回 nullptr
    if(pDerived != nullptr)
    {
        pDerived->print();
        pDerived->work();
    }

    Base base;
    Base &realBase = base;
    try
    {
        Derived refDerived = dynamic_cast<Derived*>(realBase);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    Derived derived;
    Base & refBaseNew = derived;
    try
    {
        Derived refDerived = dynamic_cast<Derived*>(refBaseNew);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}


// !!----------------------------------------------------------------
Item 30: 理解 inline 化的介入和排除




// !!----------------------------------------------------------------

Item 31 把文件之间的编译依赖降到最低

假设在 Person.h 中

#beginPerson.h

#include <string>
#include "date.h"
#include "address.h"// 建立了定义 Person 的文件和这些头文件之间的编译依赖关系

// 如果这些头文件中的一些发生了变化，或者这些头文件所依赖的文件发生了变化，包含 Person 类的文件和使用了 Person 的文件一样必须重新编译，
// 这样的层叠编译依赖关系为项目带来数不清的麻烦
class Person
{
public:
    Person(const std::string &name, const Date &birthday,
           const Address &addr);
    std::string name() const;
    std::string birthDate() const;
    std::string address() const;
    //...
private:
    std::string theName; // implementation detail
    Date theBirthDate;   // implementation detail
    Address theAddress;  // implementation detail
};

#endPerson.h

// !! 尝试将类的实现分离出来

// !!----------------------------------------------------------------

Item 41: 理解 implicit interfaces（隐式接口）和 compile-time polymorphism（编译期多态）

// !! object-oriented programming（面向对象编程）的世界是围绕着 explicit interfaces（显式接口）和 runtime polymorphism（执行期多态）为中心的

class Widget {
public:
  Widget();
  virtual ~Widget();
  virtual std::size_t size() const;
  virtual void normalize();
  void swap(Widget& other);
  // ...
};

void doProcess(Widget& w)
{
    if(w.size() > 10 && w != someNastyWidget)
    {
        Widget temp(w);
        temp.normalize();
        temp.swap(w);
    }
}

1. 因为 w 被声明为 Widget 类型的引用，w 必须支持 Widget interface（接口）,我们可以在源代码中找到这个 interface（接口）（例如: Widget 的 .h 文件）
   以看清楚它是什么样子的，所以我们称其为一个 explicit interface（显式接口）—— 它在源代码中显式可见
2. 因为 Widget 的一些 member functions（成员函数）是虚拟的，w 对这些函数的调用就表现为 runtime polymorphism（执行期多态）,被调用的特定函数在执行期基于 w 
   的 dynamic type（动态类型）来确定

// !! templates（模板）和 generic programming（泛型编程）的世界是根本不同的
// 在这个世界 explicit interfaces（显式接口）和 runtime polymorphism（执行期多态）继续存在，但是它们不那么重要了。作为替代，把 implicit interfaces
// （隐式接口） 和 compile-time polymorphism（编译期多态）推到了前面

templates<typename T>
void doProcess(T &w)
{
    if (w.size() > 10 && w != someNastyWidget)
    {
        T temp(w);
        temp.normalize();
        temp.swap(w);
    }
}

1. w 必须支持的 interface（接口）是通过 template （模板）中在 w 身上所执行的操作确定的,在本例中，它显现为 w 的 type (T) 必须支持 size，normalize 和 swap member 
   functions（成员函数）; copy construction（用于创建 temp）；以及对不等于的比较（用于和 someNastyWidget 之间的比较）

2. 对诸如 operator> 和 operator!= 这样的包含 w 的函数的调用可能伴随 instantiating templates（实例化模板）以使这些调用成功.这样的 instantiation 发生在编译期间。
   因为用不同的 template parameters（模板参数）实例化 function templates （函数模板）导致不同的函数被调用，因此以 compile-time polymorphism（编译期多态）著称



// !! Things to Remember
1. classes（类）和 templates（模板）都支持 interfaces（接口）和 polymorphism（多态）
2. 对于 class（类），interface（接口）是 explicit （显式）的并以 function signatures 为中心的;
   polymorphism（多态性）通过 virtual functions（虚拟函数）出现在运行期
3. 对于 template parameters（模板参数），interfaces（接口）是 implicit（隐式）的并基于 valid expressions（合法表达式）
   polymorphism（多态性）通过 template instantiation（模板实例化）和 function overloading resolution（函数重载解析）出现在编译期


// !!----------------------------------------------------------------
Item 33: 避免覆盖（hiding）“通过继承得到的名字”

// !!在 C++ 中，我们该用哪种态度对待通过继承得到的名字呢?----事情的实质与继承没什么关系, 它与作用域有关

int x;//  global variable

void func()
{
    double x; // local variable
    // 读入 x 的语句指涉 local 变量 x，而不是 global 变量 x，因为内层作用域的名字覆盖（“遮蔽”）外层作用域的名字
    std::cin >> x;// read a new value for local x
}



class Base
{
private:
    int x;

public:
    virtual void mf1() = 0;
    virtual void mf2();
    void mf3();
};


// !! derived class 的作用域是嵌套在 base class 作用域之中
class Derived : public Base
{
    public:
    virtual void mf1();
    void mf4();
    //...
};

void Derived::mf4()
{
    //...
    // 当编译器看到这里对名字 mf2 的使用，它就必须断定它指涉什么
    // 1. 首先它在 local 作用域中搜索（也就是 mf4 的作用域），但是它没有找到被称为 mf2 的任何东西的声明
    // 2. 然后它搜索它的包含作用域，也就是 class Derived 的作用域
    // 3. 它依然没有找到叫做 mf2 的任何东西，所以它上移到它的上一层包含作用域，也就是 base class 的作用域, 在那里它找到了名为 mf2 的东西，所以搜索停止
    // 如果在 Base 中没有 mf2，搜索还会继续，首先是包含 Base 的 namespace（如果有的话），最后是 global 作用域
    mf2();
    //...
}


class Base
{
private:
    int x;

public:
    virtual void mf1() = 0;
    virtual void mf1(int);
    virtual void mf2();

    void mf3();
    void mf3(double);
    //...
};


class Derived : public Base
{
public:
    virtual void mf1();
    void mf3();
    void mf4();
    //...
};

Derived d; //
int x = 10; //

d.mf1(); // fine, calls Derived::mf1

// !! 内层作用域的名字覆盖（“遮蔽”）外层作用域的名字
d.mf1(x);// error! Derived::mf1 hides Base::mf1

d.mf2(); // fine, calls Base::mf2

// !! 内层作用域的名字覆盖（“遮蔽”）外层作用域的名字
d.mf3(); // fine, calls Derived::mf3

f.mf3(x);// error! Derived::mf3 hides Base::mf3



class Base
{
    private:
    int x;
    public:
    virtual void mf1() = 0;
    virtual void mf1(int);
    virtual void mf2();
    void mf3();
    void mf3(double);
};


class Derived : public Base
{
public:
    // !! 这意味着如果你从一个带有重载函数的 base class 继承，而且你只想重定义或替换它们中的一部分，你需要为每一个你不想覆盖的名字使用 using declaration
    using Base::mf1; //  make all things in Base named mf1 and mf3 visible (and public) in Derived's scope
    using Base::mf3;

    virtual void mf1();
    void mf3();
    void mf4();
};

Derived d;
int x = 19;
//...
d.mf1();  // still fine, still calls Derived::mf1
d.mf1(x); // now okay, calls Base::mf1
d.mf2();  // still fine, still calls Base::mf2
d.mf3();  // fine, calls Derived::mf3
d.mf3(x); // now okay, calls Base::mf3

// !! Things to Remember
1. derived classes 中的名字覆盖 base classes 中的名字，在 public inheritance 中，这从来不是想要的
2. 为了使隐藏的名字重新可见，使用 using declarations


// !!----------------------------------------------------------------

Item 34: 区分 inheritance of interface（接口继承）和 inheritance of implementation（实现继承）

1. (public) inheritance 这个表面上简单易懂的观念，一旦被近距离审视，就会被证明是由两个相互独立的部分组成的：inheritance of function 
    interfaces（函数接口的继承）和 inheritance of function implementations（函数实现的继承）


// Shape 是一个 abstract class, 它的 pure virtual function 表明了这一点
class Shape
{
    public:
    // pure virtual functions 必须被任何继承它们的具体类重新声明;抽象类中一般没有它们的定义
    // !! 声明一个 pure virtual function（纯虚拟函数）的目的是使 derived classes 继承一个函数(interface only)
    virtual void draw() = 0;

    // 声明一个 simple virtual function 的目的是让 derived classes 继承一个函数 interface as well as a default implementation
    virtual void error(const string&msg);


    int objectId() const;
    //...
};


class Rectangle:public Shape{};

class Ellipse:public Shape {};


//!! 对 pure virtual，simple virtual，和 non-virtual functions 声明的不同允许你精确指定你需要 derived classes 继承什么东西
1. pure virtual -----> interface only
2. simple virtual -----> interface and a default implementation
3. non-virtual functions -----> interface and a mandatory implementation（接口和一个强制的实现）


//!! Things to Remember

1. Inheritance of interface（接口继承）与 inheritance of implementation（实现继承）不同。在 public inheritance（公开继承）下，derived classes（派生类）
   总是继承 base class interfaces（基类接口）

2. Pure virtual functions（纯虚函数）指定 inheritance of interface only

3. Simple (impure) virtual functions（简单虚函数）指定 inheritance of interface（接口继承）加上 inheritance of a default implementation

4. Non-virtual functions（非虚拟函数）指定 inheritance of interface（接口继承）加上 inheritance of a mandatory implementation（强制实现继承）



// !!----------------------------------------------------------------

Item 48: 感受 template metaprogramming （模板元编程）

// !! template metaprogramming (TMP)（模板元编程）是写 template-based（基于模板）的运行于编译期间的 C++ 程序的过程
// !! 当一个 TMP 程序运行完成，它的输出——从 templates（模板）实例化出的 C++ 源代码片断——随后被正常编译

// TMP 有两个强大的力量
1.首先，它使得用其它方法很难或不可能的一些事情变得容易
2.因为 template metaprograms（模板元程序）在 C++ 编译期间执行，它们能将工作从运行时转移到编译时。一个结果就是通常在运行时才能被察觉的错误能够在编译期间被发现。
  另一个结果是使用了 TMP 的 C++ 程序在以下几乎每一个方面都可能更有效率：更小的可执行代码，更短的运行时间，更少的内存需求;然而，将工作从运行时转移到编译时的一个结
  果就是编译过程变得更长。使用 TMP 的程序可能比它们的 non-TMP 对等物占用长得多的编译时间

// !! Things to Remember
1. template metaprogramming（模板元编程）能将工作从运行时转移到编译时，这样就能够更早察觉错误并提高运行时性能
2. TMP 能用于在 policy choices 的组合的基础上生成自定义代码，也能用于避免为特殊类型生成不适当的代码



// !! 元编程的思路----元（meta）可以理解为自身，所谓元编程，就是用自身的代码来生成更多的代码
// 简单来说，元编程所做的事就类似于递归
int f(int n)
{
    if(n == 0)
    {
        return 1;
    }
    // 看似只有一句，但是实际调用时会不断展开，以达到计算阶乘的效果
    return n*f(n-1);
}

// 函数重载的繁琐

// !! 所谓模板，简单来说就是利用一个符号来泛指所有类型，这就是所谓的泛型（generic）

// 假设需要返回两个整型数中的较大者，可以写成这样的函数
int max(int x, int y)
{
    return x > y ? x:y;
}


// 现在仍然希望实现相同的目的, 但参数类型可能不只是int，还可能是其他类型。这点可以通过函数重载来实现
int max(int x, int y)
{
    return x > y ? x:y;
}


double max(double x, double y)
{
    return x > y ? x:y;
}

char max(char x, char y)
{
    return x > y ? x:y;
}


// !! 模板的基本使用
// 冗余重复在编程中是最令人厌烦的事，而使用模板就可以轻松解决这个问题
Template<typename T>//  加上这行来表示这是一个模板
T max(T x, T y)
{
    return x > y ? x:y;
}

// !! 上述模板中，用T来泛指任意类型，而具体类型可以在调用时再指定

std::cout << max<int>(10,20) << endl;
std::cout << max<double>(10.8,9.89) << endl;


// 甚至可以不显式指定，而是让编译器自行推断出T的类型

std::cout << max(19,20) << endl;

//!! 由此也可以知道，模板实际是在编译期而非运行期执行的，这正是模板的另一优势（减少运行时间），但同时也是一大劣势（增加编译时间）

// !! 模板元编程的编译期值计算

1. 模板元编程编程的主要目的，就是利用编译期完成计算，尽可能减少运行时间，从而达到减少开销的效果

template<int N>
class Fac
{
public:
    static const int value = N * Fac<N - 1>::value;
};


template<>
class Fac<0>
{
    public:
    static const int value = 1;
};

std::cout << Fac<5>::value << std::endl;// 120



// !!----------------------------------------------------------------

Item 50: 领会何时替换 new 和 delete 才有意义

// !! 为什么有些人想要替换编译器提供的 operator new 或 operator delete 版本呢？

1. 为了监测使用错误。对由 new 产生的内存没有实行 delete 会导致内存泄漏。在 new 出的内存上实行多于一次的 delete 会引发未定义行为。如果 operator new 保存一个已分配地址的列表，而 operator delete 
   从这个列表中移除地址，这样就很容易监测到上述使用错误。同样，某种编程错误会导致 data overruns（数据上溢）（在一个已分配块的末端之后写入）和 underruns（下溢）（在一个已分配块的始端之前写入）

2. 为了提升性能。由编译器加载的 operator new 和 operator delete 版本是为了多种用途而设计的。它们必须被长时间运行的程序接受，但是它们也必须被运行时间少于一秒的程序接受。
   它们必须处理大内存块，小内存块，以及两者混合的情况。它们必须适应广泛的分配模式，从存在于整个程序的持续期间的少数几个区块的动态分配到大量短寿命 objects 的持续不断的分配和释放。
   它们必须为堆碎片化负责，对这个过程，如果不进行控制，最终会导致不能满足对大内存块的请求，即使有足够的自由内存分布在大量小块中。

3. 为了收集使用方法的统计数据。在一头扎入编写自定义 news 和 deletes 的道路之前，收集一下你的软件如何使用动态内存的信息还是比较明智的。被分配区块大小的分布如何？生存期的分布如何？
   它们的分配和释放的顺序是趋向于 FIFO ("first in, first out")，或者 LIFO ("last in, first out")的顺序，还是某种接近于随机的顺序？使用模式会随着时间而变化吗？


// 在概念上，编写一个自定义 operator new 相当简单
static const int signature = 0xDEADBEEF;
typedef unsigned char Byte;

void *operator new(std::size_t size) throw(std::bad_alloc)
{
    using namespace std;
    size_t realSize = size + 2*sizeof(int);
    void *pMem = malloc(realSize);
    if(!pMem)
    {
        throw bad_alloc();
    }
    // write signature into first and last parts of the memory
    *(static_cast&lt;int*&gt;(pMem)) = signature;
    *(reinterpret_cast&lt;int*&gt;(static_cast&lt;
    Byte*&gt;(pMem)+realSize-sizeof(int))) = signature;
     // return a pointer to the memory just past the first signature
      return static_cast&lt;
      Byte*&gt;
      (pMem) + sizeof(int);
}

// !! 很多计算机架构要求特定类型的数据要放置在内存中具有特定性质的地址中
1. 例如: 一种架构可能要求 pointer（指针）要出现在四的倍数的地址上（也就是说，按照四字节对齐）或者 double（双精度浮点型）必须出现在八的倍数的地址上（也就是说，按照八字节对齐）。
   不遵守这样的约束会导致 hardware exceptions at runtime（运行时硬件异常）。其它的架构可能会宽容一些，但是如果满足了排列对齐的次序会得到更好的性能。例如: 在 Intel x86 架构上
    double （双精度浮点型）可以按照任意字节分界排列，但是如果他们按照八字节对齐，访问速度会快得多

//!! 我们现在应该比前面更详细地总结一下何时替换 new 和 delete 的缺省版本时机问题

1. 为了监测使用错误
2. 为了收集有关动态分配内存的使用的统计数据
3. 为了提升分配和回收的速度
   general-purpose allocators（通用目的的分配器）通常比自定义版本慢很多，特别是如果自定义版本是为某种特定类型的 objects 专门设计的。 class-specific allocators（类专用分配器）是
   fixed-size allocators（固定大小分配器）（就像 Boost 的 Pool library 所提供的那些）的一种典范应用。
4. 为了减少缺省内存管理的空间成本
   general-purpose memory managers（通用目的的内存管理器）通常不仅比自定义版本慢，而且还经常使用更多的内存。
5. 为了调整缺省分配器不适当的排列对齐
   在 x86 架构上，当 doubles 按照八字节对齐时访问速度是最快的。有些随编译器提供的 operator news 不能保证 doubles 的动态分配按照八字节对齐。在这种情况下，用保证按照八字节对齐的
   operator new 替换掉缺省版本，可以使程序性能得到较大提升


// !! Things to Remember

有很多正当的编写 new 和 delete 的自定义版本的理由，包括改进性能，调试 heap（堆）用法错误，以及收集 heap（堆）用法信息


// !!----------------------------------------------------------------

Item 51: 编写 new 和 delete 时要遵守惯例


一个 non-member（非成员）的 operator new 的伪代码如下:

void *operator new(std::size_t size) throw(std::bad_alloc)
{
    using namespace std;
    if(size == 0)
    {
        size = 1;
    }
    while(true)
    {
        // attempt to allocate size bytes
        if (_the allocation was successful_)
        {
             return (_a pointer to the memory_);
        }
        // allocation was unsuccessful; find out what the current new-handling function is (see below)
        new_handler globalHandler = set_new_handler(0);
        set_new_handler(globalHandler);
        if (globalHandler)
        {
           (*globalHandler)();
        }
        else 
        {
           throw std::bad_alloc();
        }
    }
}









}