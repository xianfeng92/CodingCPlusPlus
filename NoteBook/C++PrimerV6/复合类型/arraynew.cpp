// arraynew.cpp

#include<iostream>

int main()
{
    using namespace std;
    double *p3 = new double[3];// space for 3 doubles
    p3[0] = 0.2;
    p3[1] = 0.5;
    p3[2] = 0.8;

    cout << "p3[1] is " << p3[1] <<"\n";
    p3 = p3 + 1;
    cout << "Now p3[0] is " << p3[0] <<".\n" << "and p3[1] is " << p3[1] << ". \n";
    p3 = p3 - 1;// point back to begin
    delete[] p3;
    return 0;
}