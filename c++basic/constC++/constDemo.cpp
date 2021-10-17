#include<iostream>
#include<typeinfo>

using namespace std;


int main(int argc, char **argv)
{
    // !! 1.const含义---常类型是指使用类型修饰符 const 说明的类型，常类型的变量或对象的值是不能被更新的

    // !! 2.const作用
    // a. 可以定义常量
    const int a = 100;

    // b. 类型检查
    // const 常量与 #define 宏定义常量的区别:
    // !! const 常量具有类型，编译器可以进行安全检查；#define 宏定义没有数据类型，只是简单的字符串替换，不能进行安全检查

    // c. 防止修改，起保护作用，增加程序健壮性
    void f(const int i)
    {
        i++; //error!
    }

    // d.可以节省空间，避免不必要的内存分配
    // const 定义常量从汇编的角度来看，只是给出了对应的内存地址，而不是像 #define 一样给出的是立即数，所以，const 定义的常量在程序运行过程中只有一份拷贝，
    // 而 #define 定义的常量在内存中有若干个拷贝

    // !! 3.const 对象默认为文件局部变量
    // 非 const 变量默认为 extern。要使 const 变量能够在其他文件中访问，必须在文件中显式地指定它为 extern

    // a. 未被 const 修饰的变量在不同文件的访问
    // file1.cpp
    int ext = 10086;

    // file2.cpp
    extern int ext;
    int main()
    {
        std::cout << (ext + 10) << std::endl;
    }

    // b. const 常量在不同文件的访问
    //extern_file1.cpp
    extern const int ext = 12;

    //extern_file2.cpp
    extern const int ext;
    int main()
    {
        std::cout << ext << std::endl;
    }

    // !! 小结：可以发现未被 const 修饰的变量不需要 extern 显式声明！而 const 常量需要显式声明extern，并且需要做初始化！因为常量在定义后就不能被修改
    // !! 所以定义时必须初始化



    // !! 4.定义常量

    const int value = 100; 
    value = 200;// error: assignment of read-only variable ‘value’
    const std::string str = "helloworld";
    const int i,j=0 // error: uninitialized const ‘i’


    // !! 5.指针与 const

    // 指向 const 对象的指针或者说指向常量的指针
    const char* p;
    // 同上
    char const * p1;

    // 指向类型对象的 const 指针。或者说常指针、const 指针
    char * const p2;

    // 指向 const 对象的 const 指针
    const char * const p3;

    // !! 小结：如果const位于*的左侧，则 const 就是用来修饰指针所指向的变量，即指针指向为常量；
    // !! 如果const位于*的右侧，const就是修饰指针本身，即指针本身是常量
    const int* prt;
    *ptr = 100;//error
    // ptr 是一个指向 int 类型 const 对象的指针，const 定义的是 int 类型，也就是 ptr 所指向的对象类型，而不是 ptr 本身，
    // 所以 ptr 可以不用赋初始值。但是不能通过 ptr 去修改所指对象的值。

    // 不能使用 void* 指针保存 const 对象的地址，必须使用 const void* 类型的指针保存 const 对象的地址
    const int p = 100;
    const int * prt = &p;
    void * pptr = &p;//error

    // !! 允许把非 const 对象的地址赋给指向 const 对象的指针
    const int * prt;
    int val = 0;
    // 我们不能通过 ptr 指针来修改 val 的值，即使它指向的是非 const 对象!
    ptr = &val;


    // b.常指针 -- const 指针必须进行初始化，且 const 指针的值不能修改
    int num=0;
    int * const ptr=&num; // !! const 指针必须初始化！且 const 指针的值不能修改
    int * t = &num;
    *t = 1;
    cout<<*ptr<<endl;


    // c.指向常量的常指针
    const int p = 3;
    // ptr 是一个 const 指针，然后指向了一个 int 类型的 const 对象
    const int * const ptr = &p; 


    // !! 6.函数中使用 const

   // a. 传递过来的参数及指针本身在函数内不可变，无意义
   // !! 输入参数采用“值传递”，由于函数将自动产生临时变量用于复制该参数，该输入参数本来就无需保护，所以不要加 const 修饰
    void func(const int var); // 传递过来的参数不可变
    void func(int *const var); // 指针本身不可变

   // b. 参数指针所指内容为常量不可变
   // 其中 src 是输入参数，dst 是输出参数。给 src 加上 const 修饰后，如果函数体内的语句试图改动 src 的内容，编译器将指出错误。这就是加了 const 的作用之一
   void StringCopy(char *dst, const char *src);

   // c.参数为引用，为了增加效率同时防止修改
   void func(const A &a)

   // 对于非内部数据类型的参数而言，象 void func(A a) 这样声明的函数注定效率比较低。因为函数体内将产生A 类型的临时对象用于复制参数a，而临时对象的构造、
  // 复制、析构过程都将消耗时间。为了提高效率，可以将函数声明改为void func(A &a)，因为“引用传递”仅借用一下参数的别名而已，不需要产生临时对象。
  // 但是函数 void func(A &a) 存在一个缺点：“引用传递”有可能改变参数 a，这是我们不期望的。解决这个问题很容易，加const修饰即可，因此函数最终成为 void func(const A &a)

  // 以此类推，是否应将 void func(int x) 改写为 void func(const int &x)，以便提高效率？完全没有必要，因为内部数据类型的参数不存在构造、析构的过程，
  // 而复制也非常快，“值传递”和“引用传递”的效率几乎相当


  // !! 小结：对于非内部数据类型的输入参数，应该将“值传递”的方式改为“const 引用传递”，目的是提高效率; 对于内部数据类型的输入参数，不要将“值传递”的方式改为
  // !! “const 引用传递”。否则既达不到提高效率的目的，又降低了函数的可理解性


  // 7.类中使用 const

  在一个类中，任何不会修改数据成员的函数都应该声明为 const 类型,如果在编写 const 成员函数时，不慎修改数据成员，或者调用了其它非const成员函数，编译器将指出错误，
  这无疑会提高程序的健壮性。


  对于类中的 const 成员变量必须通过初始化列表进行初始化，如下所示：
 class Apple
 {
   private:
       int people[100];
   public:
      Apple(int i); 
      const int apple_number;
 };

  Apple::Apple(int i):apple_number(i)
 {

 }


 const 对象只能访问 const 成员函数,而非 const 对象可以访问任意的成员函数



    // !! const的基本概念
    // const 名叫常量限定符，用来限定特定变量，以通知编译器该变量是不可修改的。习惯性的使用 const，可以避免在函数中对某些不应修改的变量造成可能的改动

    // 1. const修饰基本数据类型
    // const int a = 10010;         // 等价的书写方式： int const a=10;
    // const int arr[] = {1, 2, 3}; // 等价的书写方式： int const arr[] = {1,2,3};

    // 2.const 修饰指针变量(*)及引用变量(&)
    // 2.1 const修饰指针（*）
    // const int *p;            // 修饰 int，即 *p 所指向的内容无法改变
    // int const *pp;           // 等价的书写方式： int const
    // int *const ppp;          // 修饰 int *,即不能改变 ppp 的指向
    // const int *const ppppp； // 指向和所指向的内容都不能改变

    // !! const 应用到函数中
    // !! 作为函数返回值的 const 修饰符---其意义上是不能修改所在类的的任何变量

    int a = 10;
    const int *p = &a;
    int * const p1 = &a;
    cout << typeid(p).name() << endl;// output type is int
    cout << typeid(p1).name() << endl;// output type is int * 

}
