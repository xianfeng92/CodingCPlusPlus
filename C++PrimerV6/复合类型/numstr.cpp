// numstr.cpp

#include<iostream>

int main()
{
    using namespace std;
    cout << " What year was your house built? \n";
    int year;
    cin >> year;
    cout << " What is street address.\n";
    char address[80];
    cin.getline(address, 80);
    cout << "Year Built: " << year << endl;
    cout << "Street Address: " << address << endl;
    cout << "Done! \n";
    return 0;
}