#include <iostream>
#include <string>
#include <cctype>
#include "stacktp.h"

using std::cin;
using std::cout;


int main()
{
    Stack<std::string> st;
    char ch;
    std::string po;
    cout << "Please Enter A to add a purchase order ,\n"
    << " P to process P0, or Q to quit." << std::endl;

    while (cin >> ch && std::toupper(ch) != 'Q')
    {
        
    }
}