// address.cpp

#include<iostream>

int main()
{
    using namespace std;
    int donuts = 6;
    double cups = 4.5;

    cout << "donuts value is " << donuts;
    cout << " and donuts address is " << &donuts << endl;

    cout << "cups value is " << cups;
    cout << " and cups address is " << &cups << endl;
    return 0;
}
