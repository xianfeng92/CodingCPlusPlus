#include <iostream>
#include <string>

// using string constructor
int main()
{
    using namespace std;
    string one("Lottery Winner");// ctor #1
    cout << one << endl;

    string two(20,'$');// ctor #2
    cout << two << endl;

    string three(one);// ctor #3
    cout << three << endl;

    one += "opps";// overloaded +=
    cout << one << endl;

    two = "Sorry! That was ";
    three[0] = 'P';
    string four;// ctor #4
    four = three + two;// overloaded +, =
    cout << four << endl;

    char alls[] = "All's will that end will ";
    string five(alls,20);// ctor #5

    cout << five << endl;
    string six(alls + 6,alls+10);// ctor #6
    cout << six << endl;

    string seven(&five[6],&five[10]);// ctor #6 again
    cout << seven << endl;

    string eight(four,7,16);// ctor #7
    cout << eight << endl;
    return 0;
}