//  init_ptr.cpp

#include<iostream>

int main()
{
    using namespace std;
    int higgens = 10;
    int *pt = &higgens;

    cout << "The value of higgens= " << higgens;
    cout << ", Address of higgens= " << &higgens << endl;

    cout << "The value of *pt " << *pt;
    cout << "; value of pt " << pt << endl;
}