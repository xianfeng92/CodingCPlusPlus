// exceed.cpp ---- exceeding some integer limit

#include<iostream>
#define ZERO 0
#include<climits>


int main()
{
    using namespace std;
    short sam = SHRT_MAX;// initialize a variable to maxValue
    unsigned short sue = sam;// ok, if sam is defined

    cout << "Sam has  " << sam << " dollars, and sue has " << sue << " dollars" << endl;

    cout << "Add $1 to each account. " << "Now" << endl;
    sam = sam + 1;
    sue = sue + 1;
    cout << "Sam has " << sam << " dollars, and sue has " << sue;
    cout << " dollars deposit. \nPoor sam" << endl;

    sam = ZERO;
    sue = ZERO;
    cout << "Sam has " << sam << " dollars, and sue has " << sue;
    cout << " dollars deposit. \nPoor sam" << endl;
    cout << "Take $1 to each account. " << "Now" << endl;
    sam = sam -1;
    sue = sue -1;
    cout << "Sam has " << sam << " dollars, and sue has " << sue;
    cout << " dollars deposit. \nPoor sam" << endl;
    return 0;
}