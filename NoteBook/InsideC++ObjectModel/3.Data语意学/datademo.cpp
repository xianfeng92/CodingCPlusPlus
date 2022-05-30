#include <iostream>

using namespace std;

class X{};
class Y : public virtual X{};
class Z : public virtual X{};
class A : public Y, public Z{};

int main()
{
    cout << "sizeof X is " << sizeof(X) << endl;
    cout << "sizeof Y is " << sizeof(Y) << endl;
    cout << "sizeof Z is " << sizeof(Z) << endl;
    cout << "sizeof A is " << sizeof(A) << endl;

    return 0;
}