// !! 返回值优化

'只要能跳过对象的创建和销毁就可以提高性能'。本章将讨论编译器常用的一种优化技术，它通过转换源代码和消除对象的创建来加快源代码的执行速度。这种优化称为返回值优化
(Return Value Optimization，RVO)。


// !! 按值返回机制

Complex 类实现了复数的一种表示法：

class Complex
{
    friend Complex operator+(const Complex& a, const Complex& b);
public:
    Complex(double r= 0.0, double i = 0.0):real(r),imag(i){}
    Complex(const Complex &c):real(c.real),imag(c.imag){}

    Complex& operator=(const Complex  &c);

    ~Complex();
private:
    double real;
    double imag;
};

加法运算符按值返回一个 Complex 对象，其实现如下：

Complex operator+(const Complex  &a, const Complex &b)
{
    Complex retVal;
    retVal.real = a.real + b.real;
    retVal.imag = a.imag + b.imag;
    return retVal;
}

假设 c1、c2、c3 是 Complex 对象，且执行如下操作：

c3 =  c1 + c2;

那么如何把 c1+c2 的值赋给 c3 呢？

编译器通常使用的技术是创建临时对象 __result，并且将它作为第三个参数传给 Complex::operator+() 。__result 对象是按引用传递的。所以编译器重写:

Complex& Complex::operator+(const Complex  &c1, const Complex &c2)
{
    ...
}

将它写成一个稍微不同的函数:

void ComplexAdd(const Complex & __result,const Complex &c1, const Complex &c2)
{
    ...
}

原来的语句：

c3 = c1 + c2;

现在转变成(伪代码):

struct Complex _tempResult;
Complex_Add(_tempResult, c1, c2);
c3 = _tempResult;


这种按值返回的实现为我们提供了优化的机会:可以通过消除局部对象 retVal(在operator+()内)和直接把返回值放到 __tempResult 临时对象中来实现优化，
这就是返回值优化。

// !! 返回值优化

在没有任何优化的情况下，编译器为 Complex_Add() 生成的代码(伪代码)是:

void ComplexAdd(const Complex & __result,const Complex &c1, const Complex &c2)
{
    struct Complex retVal;
    retVal.Complex::Complex();

    retVal.real = a.real + b.real;
    retVal.imag = a.imag + b.imag;

    __tempResult.Complex::Complex(retVal);
    retVal.Complex::~Complex();
    return;
}

编译器通过消除局部对象 retVal 并用 __tempResult 替代它，对 Complex_Add() 进行了优化。下面是这种 RVO 的实现:

void ComplexAdd(const Complex & __result,const Complex &c1, const Complex &c2)
{
    __tempResult.Complex::Complex();
    __tempResult.real = c1.real + c2.real;
    __tempResult.imag = c1.imag + c2.imag;
    return;
}

RVO 消除了局部对象 retVal，并且省去了构造函数和析构函数的计算。

为了对效率有一个定量的认识，我们测试了 RVO 对执行速度的影响。我们编写两个版本的 operator+()，其中一个是经过优化的，而另一个没有。测试代码由 100 
万次循环迭代组成:

第二个版本没有采取 RVO，执行了 1.89s。第一个版本采取了 RVO，执行得更快——1.30s。

毫无疑问，编译器优化要保证原来计算的正确性。然而对于 RVO 来说，这一点并不总是易于实现的。既然 RVO 不是强制执行的，编译器就不会对复杂的函数执行 RVO。
例如，'如果函数有多个 return 语句返回不同名称的对象，这样就不会执行 RVO'。如果想使用 RVO，就必须返回相同名称的对象。

我们测试过的一款编译器拒绝为如下版本的 operator+ 执行 RVO:

Complex operator+(const Complex  &a, const Complex &b)
{
    Complex retVal;
    retVal.real = a.real + b.real;
    retVal.imag = a.imag + b.imag;
    return retVal;
}

然而，该编译器为以下版本执行 RVO:

Complex operator+(const Complex  &a, const Complex &b)
{
    double real = a.real + b.real;
    double imag = a.imag + b.imag;
    return Complex(real,imag);
}

// !! 计算性构造函数

当编译器无法执行 RVO 时，可按计算性构造函数的形式来实现。我们的编译器不对版本 1 使用 RVO:

Complex operator+(const Complex  &a, const Complex &b)
{
    Complex retVal;
    retVal.real = a.real + b.real;
    retVal.imag = a.imag + b.imag;
    return retVal;
}

该实现创建了一个默认的 Complex 对象，并且没有立即设置它的成员变量。随后它用输入对象提供的信息去填充成员数据。Complex 对象 retVal 的创建需要多个步骤。
计算性构造函数把这些步骤整合成一个调用，并且消除了命名的局部变量。

版本 5 用到的计算性构造函数通过求两个输入参数的和来创建新的 Complex 对象。

Complex operator+(const Complex  &a, const Complex &b):real(a.real+b.real), imag(a.imag+b.imag)
{

}

相对于加法运算符的版本 1，现在编译器更有可能对版本 5 执行 RVO。如果我们想将相同的想法运用到其他的算术运算符，就必须增加第三个参数以区别用于加、减、乘、除的计算
性构造函数的符号。有人批评计算性构造函数：为了效率它竭尽全力，引入了“不自然的”构造函数。我们对此的观点是：在某些情况下, 性能问题压倒其他所有问题。因为这个问
题与具体的场景相关，所以没有正确的答案。


// !! 要点

● 如果必须按值返回对象，通过 RVO 可以省去创建和销毁局部对象的步骤，从而改善性能

● RVO 的应用要遵照编译器的实现而定。这需要参考编译器文档或通过实验来判断是否使用 RVO 以及何时使用

● 通过编写计算性构造函数可以更好地使用 RVO


