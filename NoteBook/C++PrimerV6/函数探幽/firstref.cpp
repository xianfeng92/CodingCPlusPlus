// firstref.cpp

#include<iostream>

int main()
{
    using namespace std;
    int rats = 101;
    int &rodents = rats;
    cout << "rats = " << rats << "\n";
    cout << "rodents = " << rodents << "\n";
    ++rodents;
    cout << "rats = " << rats << "\n";
    cout << "rodents = " << rodents << "\n";

    cout << "rats address is " << &rats << "\n";
    cout << "rodent address is " << &rodents << "\n";
    return 0;
}