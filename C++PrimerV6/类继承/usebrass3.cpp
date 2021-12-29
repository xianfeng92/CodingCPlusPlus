#include <iostream>
#include<string>
#include "acctabc.h"

const int CLIENTS = 4;

int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    AcctABC *p_clients[CLIENTS];
    std::string temp;
    long tempnum;
    double tempbal;
    char kind;

    for(int i=0; i<CLIENTS; i++)
    {
        cout << "Enter Client name:\n";
        getline(cin, temp);
        cout << "Enter Client account number:\n";
        cin>>tempnum;
        cout << "Enter opening balance:\n";
        cin >> tempbal;
        cout << "Enter 1 for Brass Account"
        << " and 2 for BrassPlus Account:\n";
        while(cin >> kind && (kind != '1' && kind != '2'))
        {
            cout << "Enter either 1 or 2: \n";
        }
        if(kind == '1')
        {
            p_clients[i] = new Brass(temp,tempnum,tempbal);
        }
        else
        {
            double tmax,trate;
            cout << "Enter the overdraft limit:\n";
            cin >> tmax;
            cout << "Enter the interst rate:\n";
            cin >> trate;
            p_clients[i] = nnew BrassPlus(temp, tempnum, tempbal, tmax , trate);
        }
        while(cin.get() != '\n')
        {
            continue;
        }
    }
    cout << endl;
    for(int i =0; i< CLIENTS; i++)
    {
        p_clients[i].ViewAcct();
    }
     for(int i =0; i< CLIENTS; i++)
    {
        delete [] p_clients;
    }
    cout << "Done\n";
    return 0;
}