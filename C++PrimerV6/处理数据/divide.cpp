// divide.cpp


#include<iostream>

int main()
{
    using namespace std;
    cout.setf(ios_base::fixed,ios_base::floatfield);
    cout << "Integer divide: 9/5 = " << 9/5 << endl;
    cout << "Floating divide: 9.0/5.0 = " << 9.0/5.0 << endl;
    cout << "Mixed divide: 9.0/5 = " << 9.0/5 << endl;
    cout << "Double divide: 1e7/9.0 = " << 1e7/9.0 << endl;
    cout << "Float divide: 1e7/9.0f = " << 1e7/9.0f << endl;
    return 0;
}