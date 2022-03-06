#include <iostream>
#include <typeinfo>

using namespace std;

class B{};

class D : public B
{

};


int main(){
    B *pb = new B();
    D *pd = new D();

    cout << "pb type name is " << typeid(pb).name() << endl;
    cout << "pd type name is " << typeid(pd).name() << endl;

    return 0;
}


