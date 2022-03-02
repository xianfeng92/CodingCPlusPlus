#ifndef COMPLEX_H_
#define COMPLEX_H_

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

Complex operator+(const Complex  &a, const Complex &b)
{
    Complex retVal;
    retVal.real = a.real + b.real;
    retVal.imag = a.imag + b.imag;
    return retVal;
}

#endif // COMPLEX_H_
