// auto.cpp

#include<iostream>
void oil(int x);

int main()
{
    using namespace std;
    int teaxs = 31;
    int year = 2021;
    cout << "In main " << "teaxs" << teaxs << '\n';
    cout << &teaxs << '\n';
    cout << "In main " << "year" << year << '\n';
    cout << &year << '\n';
    oil(teaxs);
    cout << "In main " << "teaxs" << teaxs << '\n';
    cout << &teaxs << '\n';
    cout << "In main " << "year" << year << '\n';
    cout << &year << '\n';
    return 0;
}

void oil(int x)
{
    using namespace std;
    int teaxs = 5;
    cout << "In oil " << "teaxs" << teaxs << '\n';
    cout << "&teaxs " << &teaxs << '\n';
    cout << "In oil x " << x << "&x is " << &x << '\n';
    {
        int teaxs = 999;
        cout << "In block " << "teaxs is " << teaxs;
        cout << "&teasx is " << &teaxs << '\n';
        cout << "In block x " << x << "&x is " << &x << '\n';
    }
    cout << "Post-block teaxs is " << teaxs;
    cout << "&teaxs is " << &teaxs;
}