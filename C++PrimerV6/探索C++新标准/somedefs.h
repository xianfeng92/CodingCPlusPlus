#ifndef E6A2A298_4EC7_4F3F_9F89_D2EB36084BD1
#define E6A2A298_4EC7_4F3F_9F89_D2EB36084BD1
#include<iostream>

template<typename T, typename F>
T use_f(T v, F f)
{
    static int count = 0;
    count++;
    std::cout << "use_f count =" << count << "&count = " << &count << std::endl;
    return f(v);
}

class Fp
{
private:
    double z_;
public:
    Fp(double z = 1.0) : z_(z)
    {

    }
    double operator()(double p){ return p * z_; }
};

class Fq
{
private:
    double z_;
public:
    Fq(double z = 1.0) : z_(z){}
    double operator()(double q) { return z_ + q; }
};

#endif /* E6A2A298_4EC7_4F3F_9F89_D2EB36084BD1 */
