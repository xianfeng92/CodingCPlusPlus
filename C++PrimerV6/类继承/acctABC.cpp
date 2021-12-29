#include<iostream>
#include "acctabc.h"

using std::cout;
using std::endl;
using std::ios_base;
using std::string;

AcctABC::AcctABC(const std::string &s, long an, double bal)
{
    fullName = s;
    acctNum = an;
    balance = bal;
}

AcctABC::Deposit(double amt)
{
    if(amt < 0)
    {
        cout << "Negative deposit not allowed:\n"
        << " default is cancelled:\n";
    }
    else
    {
        balance += amt;
    }
}

AcctABC::Withdraw(double amt)
{
    balance -= amt;
}


AcctABC::Formating AcctABC::setFormat() const
{
    // set up ###.## format
    Formating f;
    f.flag = cout.setf(ios_base::fixed,ios_base::floatfield);
    f.pr = cout.precision(2);
    return f;
}


void AcctABC::restore(Formating &f)
{
    cout.setf(f.flag, ios_base::floatfield);
    cout.precision(f.pr);
}


// Brass Method

void Brass::Withdraw(double amt)
{
    if(amt < 0)
    {
        cout << "Negative deposit not allowed:\n"
        << " default is cancelled:\n";
    }
    else if(amt < Balance())
    {
        AcctABC::Withdraw(amt);
    }
    else
    {
        cout << "Withdraw amount of $: " << amt << " exceeded your balance." << "withdraw cancelled\n";
    }
}

void Brass::ViewAcct() const
{
    Formating f = setFormat();
    cout << "Brass Client: " << FullName() << endl;
    cout << "Account Number: " << AcctNum() << endl;
    cout << " Balance: " << Balance() << endl;
    Restore(f);
}


// Brass Plus Method

BrassPlus::BrassPlus(const string &s, long an, double bal, double ml, double r):AcctABC(s,an,bal)
{
    maxLoan = ml;
    ownsBank = 0.0;
    rate = r;
}

BrassPlus::BrassPlus(const Brass & ba, double ml, double):AcctABC(ba)
{
    maxLoan = ml;
    ownsBank = 0.0;
    rate = r;
}

void BrassPlus::ViewAcct() const
{
    Formating f = setFormat();

    cout << " BrassPlus Clent: " << FullName() << endl;
    cout << " Account Number: " << AcctNum() << endl;
    cout << " Balance： " << Balance() << endl;
    cout << " Max Loan is " << maxLoan << endl;
    cout << " Own to bank " << ownsBank << endl;
    cout.precision(3);
    cout << " Loan rate " << 100 * rate << endl;
    Restore(f);
}


void BrassPlus::Withdraw(double amt)
{
    Formating f = setFormat();

    double bal = Balance();
    if(amt <= bal)
    {
        AcctABC::Withdraw(amt);
    }
    else if(amt <= bal + maxLoan - ownsBank)
    {
        
    }
}
