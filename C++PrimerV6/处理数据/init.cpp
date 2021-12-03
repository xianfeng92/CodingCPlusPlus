// init.cpp --- type change on initialization

#include<iostream>

int main()
{
    using namespace std;
    cout.setf(ios_base::fixed,ios_base::floatfield);

    float tree = 3;// int convert to float
    int guess(3.1234);// double convert to int
    int debt = 7.2e12;// result not defined in C++
    cout << "Tree: " << tree << endl;
    cout << "Guess: " << guess << endl;
    cout << "Debt: " << debt << endl;
    return 0;
}