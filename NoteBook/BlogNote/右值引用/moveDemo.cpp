#include<iostream>
#include<string>

using namespace std;

class A{
    public:
    A(int value) : value_(value){
        cout << "Construct A" << endl;
    }
    ~A(){ cout << "Destroy A" << endl;}
    int value_;
};

void f(A&& a)
{
    cout << "in f() " << a.value_ << endl;
    for(int i = 0; i < 1000000; ++i)
    {

    }
    cout << "end f() "<< endl;
}

int main()
{
    f(A(11111111));
    cout << "ASSSSSSSS" << endl;
    return 0;
}