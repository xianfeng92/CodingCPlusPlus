#include"somedefs.h"
#include<iostream>

double dub(double x) { return 2.0 *x;}
double square(double x) { return x * x; }

int main()
{
    using std::cout;
    using std::endl;

    double y = 1.21;
    cout << "Function point dub:\n";
    cout << " " << use_f(y, dub) << endl;

    cout << "Function point square:\n";
    cout << " " << use_f(y, square) << endl;

    cout << "Function Object fp:\n";
    cout << " " << use_f(y,Fp(5.0)) << endl;
    cout << "Function Object fq:\n";
    cout << " " << use_f(y,Fq(5.0)) << endl;

    cout >> "Lambda expression 1: \n";
    cout << " " << use_f(y,[](int x){return x *2.0;});

    cout >> "Lambda expression 2: \n";
    cout << " " << use_f(y,[](int x){return x * x;});
    return 0;
}