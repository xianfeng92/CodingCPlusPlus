#include <iostream>
#include "mytime0.h"

int main()
{
    using std::cout;
    using std::endl;
    Time planing;
    Time coding(2,40);
    Time fixing(5,55);
    Time total;
    cout << "planning time: \n";
    planing.show();
    cout << endl;

    cout << "coding time: \n";
    coding.show();
    cout<<endl;

    cout << "fix time: \n";
    fixing.show();
    cout << endl;

    total = coding.sum(fixing);
    cout << "time time: \n";
    total.show();
    cout << endl;
    return 0;
}