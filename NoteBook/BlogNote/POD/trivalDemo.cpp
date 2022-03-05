#include <iostream>


using namespace std;

class A{
    public:
    int max(int x, int y){return x > y ? x : y;}
};

class B{
    public:
        B(){}
};

class C{
    public:
        C() = default;
};

int main()
{
    // yield 1
    cout << "A is trivial is " << std::is_trivial<A>::value << endl;
    // yield 0
    cout << "B is trivial is " << std::is_trivial<B>::value << endl;
    // yield 1
    cout << "C is trivial is " << std::is_trivial<C>::value << endl;
    return 0;
}

