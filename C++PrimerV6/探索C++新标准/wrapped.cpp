#include"somedefs.h"
#include<iostream>
#include<functional>

double dub(double x) { return 2.0 *x;}
double square(double x) { return x * x; }


int main()
{
    using std::cout;
    using std::endl;
    using std::function;

    double y = 1.21;
    function<double(double)> ef1 = dub;
    function<double(double)> ef2 = square;
    function<double(double)> ef3 = Fp(10.0);
    function<double(double)> ef4 = Fq(10.0);
    function<double(double)> ef5 = [](int x){return x % 2.0;};
    function<double(double)> ef6 = [](int x){return x % x;};

    cout << "Function point dub:\n";
    cout << " " << use_f(y, ef1) << endl;

    cout << "Function point square:\n";
    cout << " " << use_f(y, ef2) << endl;

    cout << "Function Object fp:\n";
    cout << " " << use_f(y,ef3) << endl;
    cout << "Function Object fq:\n";
    cout << " " << use_f(y,ef4) << endl;

    cout >> "Lambda expression 1: \n";
    cout << " " << use_f(y,ef5);

    cout >> "Lambda expression 2: \n";
    cout << " " << use_f(y,ef6);
}