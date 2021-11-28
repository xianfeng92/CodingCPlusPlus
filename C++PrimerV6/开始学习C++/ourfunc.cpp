// ourfunc.cpp

#include<iostream>

void simon(int);// function property for simon()

int main()
{
    using namespace std;
    simon(3);
    cout << "Pick a integer: ";
    int count;
    cin >> count;
    simon(count);
    cout << "Done!" << endl;
    return 0;
}

void simon(int n)// difine the simon function
{
    using namespace std;
    cout << "Simon says touch you toes " << n << "times." << endl;
}