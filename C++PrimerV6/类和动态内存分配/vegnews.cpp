#include<iostream>
#include "stringbad.h"
using std::cout;


void callme1(StringBad &);// pass by reference
void callme2(StringBad);// pass by value

int main()
{
    using std::endl;
    {
        cout << "starting a inner block:\n";
        StringBad headline1("Celery Stalks at Midnight");
        StringBad headline2("Lettuce Prey");
        StringBad sports("Spinach Leaves bowl for Dollar");
        
        cout << "headline1: " << headline1 << endl;
        cout << "headline2: " << headline2 << endl;
        cout << "sports: " <<sports << endl;

        callme1(headline1);
        cout << "headline1: " << headline1 << endl;
        callme2(headline2);
        cout << "headline2: " << headline2 << endl;

        cout << "Initialize one object to another:\n";
        StringBad sailor = sports;

        cout << "Assign one object to another:\n";
        StringBad knot;
        knot = headline1;
        cout << "knot " << knot << endl;
        cout << "Exit the block:\n";
    }
    cout << "End of main()\n";
    return 0;
}

void callme1(StringBad &rsb)
{
    cout << "string pass by reference:\n";
    cout << rsb << '\n';
}

void callme2(StringBad rsb)
{
    cout << "string pass by value:\n";
    cout << rsb << '\n';
}
