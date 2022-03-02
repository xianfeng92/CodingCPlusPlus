// calling.cpp

#include<iostream>

void simple();// function prototype

int main()
{
    using namespace std;
    cout << "main will calling simple function.\n";
    simple();
    cout << "main is finished with function called.\n";
    return 0;
}

void simple()
{
    using namespace std;
    cout << "I am simple function.\n";
}

