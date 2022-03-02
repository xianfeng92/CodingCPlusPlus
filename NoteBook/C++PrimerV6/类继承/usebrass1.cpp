#include<iostream>
#include "brass.h"

using std::cout;
using std::endl;

int main()
{
    Brass piggy("nio", 234, 32.21);
    BrassPlus hoggy("XF", 122442, 32.21);

    piggy.ViewAcct();
    cout << endl;

    hoggy.ViewAcct();
    cout << endl;

    cout << "Deposit $1000 into the hoggy Account:\n";
    hoggy.Deposit(1000);
    cout << "new Balance :$ " << hoggy.Balance() << endl;

    cout << " Withdraw $4200 from the piggy Account:\n";
    piggy.Withdraw(4200.00);
    cout << "piggy Account balance :$ " << piggy.Balance() << endl;
    cout << "withdraw $4200 from the hoggy Account:\n";
    hoggy.Withdraw(4200);
    hoggy.ViewAcct();

    return 0;
}