// choices.cpp

#include <vector>
#include<array>
#include<iostream>

int main()
{
    using namespace std;

    // C, original C++
    double a1[4] = {1.2,2.4,4.4,2.7};
    // C++ 98 STL
    vector<double> a2(4);// create a vector with 4 elements
    a2[0] = 1.0/3.0; 
    a2[1] = 1.0/5.0; 
    a2[2] = 1.0/7.0;
    a2[3] = 1.0/9.0; 

    // C++ 11 ---create and initialize array object
    array<double,4> a3 = {1.0,2.0,3.0,4.2};
    array<double,4> a4;

    a4 = a3; // valid for array object of some size

    // using array notation
    cout <<"a1[2] = " << a1[2] << " at " << &a1[2] << endl;
    cout <<"a2[2] = " << a2[2] << " at " << &a2[2] << endl;
    cout <<"a3[2] = " << a3[2] << " at " << &a3[2] << endl;
    cout <<"a4[2] = " << a4[2] << " at " << &a4[2] << endl;

    a1[-2] = 20.222;
    cout <<"a1[-2] = " << a1[-2] << " at " << &a1[-2] << endl;
    cout <<"a3[2] = " << a3[2] << " at " << &a3[2] << endl;
    cout <<"a4[2] = " << a4[2] << " at " << &a4[2] << endl;
    return 0;
}