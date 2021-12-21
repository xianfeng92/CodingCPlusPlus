#include<iostream>
#include "namesp.h"

void another(void);
void other(void);

int main()
{
    using debts::Debt;
    using debts::showDebt;

    Debt golf = {{"beny","tiom",120.32}};
    showDeb(golf);
    other();
    another();
    return 0;
}


void other(void)
{
    using std::cout;
    using std::endl;
    using namespace debts;
    Person dg = {"hii","jhom"};
    showPerson(dg);
    cout << endl;
    Debt zippy[3];
    for(int i = 0; i < 3; i++)
    {
        getDebt(zippy[i]);
    }
    for(int i = 0; i < 3; i++)
    {
        showDebt(zippy[i]);
    }

    cout << "Total debt: " << sumDebt(zippy,3) << endl;
    return;
}


void another(void)
{
    using pers::Person;
    Person collector = {"Miolo","hal"};
    pers::showPerson(collector);
    std::cout << std::endl;
}
