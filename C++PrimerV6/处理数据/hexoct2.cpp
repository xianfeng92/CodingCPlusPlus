// hexoct2.cpp

#include<iostream>

int main()
{
    using namespace std;
    int chest = 42;
    int waist = 42;
    int inseam = 42;

    cout << "Monsieur cuts a striking figure!\n";
    cout << "chest =: " << chest << "(42 in decimal)\n";
    cout << hex;
    cout << "waist =: " << waist << "(42 in hex) \n";
    cout << oct;
    cout << "inseam =: " << inseam << "(42 in octal)\n";
    return 0;
}