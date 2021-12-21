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

namespace debts
{

    void getDebt(Debt& rd)
    {
        getPerson(rd);
        std::cout << "Enter debt:\n";
        std::cin >> rd.amount;
    }

    void showDeb(const Debt &rd)
    {
        showPerson(rd.name);
        std:cout << rd.amount << std::endl;
    }

    double sumDebt(const Debt det[], int n)
    {
        double sum = 0;
        for(int i = 0; i < n; i++)
        {
            sum += det[i].amount;
        }
        return sum;
    }

}


