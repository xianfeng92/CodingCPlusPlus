#include <iostream>
#include <string>
#include <vector>
#include<bitset>
#include<typeinfo>
#include<stdexcept>



using namespace std;

// 异常处理（exception handling）允许程序独立开发的部分能够在运行时就出现的问题进行通信并做出相应的处理
// 异常使得我们能够将问题的检测和解决过程分离开；程序的一部分负责检测问题，然后解决该问题的任务交给程序的另一部分

// 栈展开（stack unwinding）过程：栈展开过程沿着嵌套函数的调用链不断查找，直到找到了与异常匹配的 catch 子句为止。
// 或者也可能一直没找到匹配的 catch，则退出主函数后查找过程终止（即调用标准库函数 terminate 来终止程序的执行）

// !! 栈展开过程中对象会被自动销毁 --- 如果退出某个块，则同时释放块中局部对象占用的内存

// !! 析构函数与异常----析构函数不应该抛出不能被它处理的异常.所以标准库类型都能确保它的析构函数不会引发异常。

// 异常对象是一种特殊对象，编译器使用异常表达式来对异常对象进行拷贝初始化。
// !! 异常对象处于编译器管理的内存空间中，编译器可以确保无论最终调用的是哪个 catch 子句都能访问该空间。当异常处理完毕后，异常对象将被销毁。
// 当我们抛出一个异常表达式时，该表达式的静态编译时的类型决定了异常对象的类型

catch (myError &eObj)// 引用类型
{
    eObj.status = errCode::serverError;// 修改了异常对象
    throw;// 将异常再次抛出，异常对象的 status 变成 serverError
}
catch (otherError oObj)// 非引用类型
{
    oObj.status = errCode::badError;// 只修改了异常对象的局部副本
    throw;// 将异常再次抛出，异常对象的 status 成员没有改变
}

// 捕获所以异常的处理代码
void manip()
{
    try
    {
        // 可能会抛出异常的操作
    }
    catch (...)// 将会捕获所有的异常
    {
        // 处理异常的某些特殊操作
        throw;
    }
}


// !! 函数 try 语句块与构造函数
template <typename T>
Blob<T>::Blob(std::initializer_list<T> il)
try：data(std::make_shared<std::vector<T>>(il))
{
    // 构造函数体
}
catch (const std::bad_alloc &e)// 既能处理构造函数体抛出的异常，也能处理成员初始化列表抛出的异常
{
    handle_out_of_memory(e);
}

// nonexcept 异常--- C++ 11 中使用 nonexcept 说明指定函数不会抛出异常
void function1() nonexcept;// 不会抛出异常
void function2();// 可能抛出异常


// !! 一旦一个 nonexcept 函数抛出了异常，程序就会调用 terminate 以确保遵守不在运行时抛出异常的约定~
// 通常情况下，编译器不能也不必在编译时验证异常说明


void f() nonexcept// 承诺不会抛出异常
{
    throw exception();// 违反了异常说明
}

// !! C++ 异常体系
// 1. 在异常类继承体系中位于最顶层的通常是 exception， exception 表示的含义是出错了，至于错误的细节则未作描述
// 2. 异常的继承体系第二层将 exception 分为两类：运行时错误（runtime error）和逻辑错误（logic error）
// 运行时错误（runtime error） 表示只有在程序运行时才能检测到的错误；而逻辑错误（logic error）一般指我们可以在程序代码中发现的错误

// !! 语言本身所支持的异常:
// 1. bad_alloc：new操作失败会抛出
// 2. bad_cast：执行期间加在一个引用上面的动态类型转换操作失败时抛出
// 3. bad_typeid：执行RTTI时，交给typeid的参数为零或空指针时抛出

// !! C++标准程序库发出的异常
// 1. invalid_argument：无效参数，比如讲bitset以char而非0或1进行初始化
// 2. length_error：可能超越了最大极限，比如对着某个字符串附加太多字符
// 3. out_of_range：参数不再预期范围内。例如在诸如array的容器或字符串string中采用一个错误索引

// !! 程序作用域之外发出的异常
// 1. range_error：内部计算时发生区间错误
// 2. overflow_error：算数运算时发生上溢
// 3. underflow_error：算数运算时发生下溢


class out_of_stock : public std::runtime_error
{
public:
    explicit out_of_stock(const std::string &msg) : std::runtime_error(msg) {}
};

class isbn_mismatch : public std::logic_error
{
public:
    explicit isbn_mismatch(const std::string &msg) : std::logic_error(msg) {}
    isbn_mismatch(const std::string &msg, const std::string &lhs, const std::string &rhs) ：logic_error(msf), left(lhs), right(rhs) {}

private:
    std::string left, right;
}

// 使用我们自己的异常类型
Sales_data &
Sales_data::operator+=(const Sales_data &rhs)
{
    if (isbn() != rhs.isbn())
    {
        throw isbn_mismatch("wrong isbn", isbn(), rhs.isbn());
    }
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}


Sales_data item1, item2, sum;
while (cin >> item1 >> item2)
{
    try
    {
        sum = item1 + item2;
        // 此处使用 sum
    }catch(const isbn_mismatch &e)
    {
        // what 负责返回用于初始化异常对象的信息
        cerr << e.what() << endl;
    }
}


template<typename T>
class stingyallocator : public allocator<T>
{
    public:
    template<typename U>
    struct rebind
    {
        typedef stingyallocator<U> other;
    };

    size_t max() const
    {
        return 10;
    }

};

int main(int argc, char **argv)
{
    // !! “在恰当的场合使用恰当的特性” 对每个称职的 C++ 程序员来说都是一个基本标准

    try
    {
        string str("Micro");
        string rstr("soft");
        str.append(rstr,5,3);
    }
    catch (exception &e)
    {
        cerr << "Caught" << e.what() << endl;
        cerr << "type" << typeid(e).name() << endl;
    }
}