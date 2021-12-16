// file1.cpp

#include<iostream>
#include"coordin.h"

using namespace std;

int main()
{
    rect rplace;
    polar pplace;
    cout << "Enter the x and y values: \n";
    while(cin >> rplace.x >> rplace.y)
    {
        pplace = rect_to_polar(rect);
        show(pplace);
        cout << "Next two numbers(q to quite):";
    }
    cout << "Bye.\n";
    return 0;
}