#include<iostream>
#include "brass.h"

using std::cout;
using std::endl;
using std::string;

typedef std::ios_base::fmtflags format;
typedef std::streamsize precis;
format setFormat();
void restore(format f, precis p);

// Brass Method
Brass::Brass(const string & s, long an, double bal)
{
    fullName = s;
    accumulate = an;
    balance = bal;
}

void Brass::Deposit(double amt)
{
    if(amt < 0)
    {
        cout << "Negative deposit not allowed"
        << "deposit us cancelled:\n";
    }
    balance += amt;
}

void Brass::Withdraw(double amt)
{
    format initialState = setFormat();
    precis prec = cout.precision(2);
    if(amt < 0)
    {
        cout << "Negative deposit not allowed"
        << "deposit us cancelled:\n";
    }
    else if(amt <= balance)
    {
        balance -= amt;
    }
    else
    {
        cout << "Withdraw amount of $" << amt << " exceed your balance .\n"
        << " Withdraw cancelled:\n";
    }
    restore(initialState, prec);


}

double Brass::Balance() const
{
    return balance;
}


void Brass::ViewAcct() const
{
    format initialState = setFormat();
    precis prec = cout.precision(2);
    cout << "Client :" << fullName << endl;
    cout << " Account Number: " << acctNum << endl;
    cout << " Balance: " << balance << endl;
    restore(initialState, prec);// restore original format
}

// BrassPlus Method
BrassPlus::BrassPlus(const string& s, long an, double bal, double ml, double r):Brass(s,an,bal)
{
    maxLoan = ml;
    ownsBank = 0.0;
    rate = r;
}


BrassPlus::BrassPlus(const Brass &ba, long an, double bal, double ml, double r):Brass(ba)
{
    maxLoan = ml;
    ownsBank = 0.0;
    rate = r;
}


// redefine how ViewAcct works
void BrassPlus::ViewAcct() const
{
    // set up ###.## format
    format initialState = setFormat();
    precis prec = cout.precision(2);
    Brass::ViewAcct();
    cout << " Maximim loan: $" << maxLoan << endl;
    cout << "Own to back $: " << ownsBank << endl;
    cout.precision(3);// ###.### format
    cout << " Loan Rate: " << 100 * rate << "%\n";
    restore(initialState, prec);
}

// redefine how Withdraw works
void BrassPlus::Withdraw(double amt)
{
    // set up ###.## format
    format initialState = setFormat();
    precis prec = cout.precision(2);

    double bal = Balance();
    if(amt < bal)
    {
        Brass::Withdraw(amt);
    }
    else if(amt <= bal + maxLoan - ownsBank)
    {
        double advance = (amt - bal);
        ownsBank += advance *(1.0 + rate);
        cout << "Bank advance: $ " << advance << endl;
        cout << "Finance Charge : $ " << advance * rate << endl;
        Deposit(advance);
        Brass::Withdraw(amt);
    }
    else
    {
        cout << "Credit limit exceeded, Translation cancelled:\n";
    }
    restore(initialState, prec);
}

format setFormat()
{
    // set up ###.## format
    return cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
}


void restore(format f, precis p)
{
    cout.setf(f,std::ios_base::floatfield);
    cout.precision(p);
}








