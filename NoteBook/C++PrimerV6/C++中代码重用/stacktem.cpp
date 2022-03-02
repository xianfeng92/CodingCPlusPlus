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
        while(cin.get() != '\n')
        {
            continue;
        }
        if(!std::isalpha(ch))
        {
            cout << '\a';
            continue;
        }
        switch(ch)
        {
            case 'A':
            case 'a':
            cout << "Enter a P0 number to add." << std::endl;
            cin >> po;
            if(st.isFull())
            {
                cout << "stack already full." << std::endl;
            }
            else
            {
                st.push(po);
            }
            break;
            case 'P':
            case 'p':
            if(st.isEmpty())
            {
                cout << "Empty stack." << std::endl;
            }
            else
            {
                st.pop(po);
                cout << "P0 #" << po << "poped\n";
                break;
            }
        }
        cout << "Please add A to add purchase order." << std::endl;
    }
    cout << "Bye~\n";
    return 0;
}
