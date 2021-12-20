#include<iostream>
#include "namesp.h"

namespace pers
{
    using std::cout;
    using std::cin;
    void getPerson(Person& rp)
    {
        cout << "Enter your first name: \n";
        cin >> rp.fname;
        cout << "Enter your last name: \n";
        cin >> rp.lname;
    }

    void showPerson(const Person &rp) 
    {
        std::cout << rp.lname << "  " rp.fname << std::endl;
    }
}


