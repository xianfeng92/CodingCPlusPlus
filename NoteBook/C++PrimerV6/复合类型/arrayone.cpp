// arrayone.cpp ---small array of integer


#include <iostream>

int main()
{
    using namespace std;
    int yams[3];// create array with 3 elements
    yams[0] = 7; // assign value to first elements
    yams[1] = 8; // assign value to second elements
    yams[2] = 6; // assign value to third elements

    int yamcost[3] = {20,30,5};// create a initialize array

    cout << "Total yams = " << endl;
    cout << yams[0] + yams[1] + yams[2] << endl;
    cout << "The packaged with " << yams[1] << " yams cost ";
    cout << yamcost[1] << " cents per yam.\n";

    int total = yams[0] * yamcost[0] + yams[1] * yamcost[1] + yams[2] * yamcost[2];
    cout << "The total yams cost " << total << "cents .\n";

    cout << "size of yams array is " << sizeof(yams);
    cout << "bytes.\n";
    cout << "size of one elements is " << sizeof(yams[0]);
    cout << "bytes.\n";
    return 0;
}