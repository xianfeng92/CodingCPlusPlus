#include <iostream>



using namespace std;

class Concrete4
{
public:
    //...
private:
    int value;
    char c1;
    char c2;
    char c3;
};


class Concrete1
{
public:
    //...
private:
    int value;
    char c1;
};

class Concrete2 : public Concrete1
{
public:
    //...
private:
char c2;
};

class Concrete3 : public Concrete2
{
public:
    //...
private:
    char c3;
};


int main()
{
    cout << "Concrete4 size is " << sizeof(Concrete4) << " bytes" << endl;

    cout << "Concrete1 size is " << sizeof(Concrete1) << " bytes" << endl;

    cout << "Concrete2 size is " << sizeof(Concrete2) << " bytes" << endl;

    cout << "Concrete3 size is " << sizeof(Concrete3) << " bytes" << endl;
}