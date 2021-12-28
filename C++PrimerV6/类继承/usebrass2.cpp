#include <string>
#include<iostream>
#include "brass.h"


const int CLIENTS = 4;

int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    Brass *p_clients[CLIENTS];
    std::string temp;
    long tempnum;
    double tempbal;
    char kind;

    for(int i = 0; i < CLIENTS; i++)
    {
        cout << "Enter a client name: \n";
        getline(cin, temp);
        cout << "Enter a client account number: \n";
        cin >> tempnum;
        cout << "Enter opening balance: \n";
        cin >> tempbal;
        cout << "Enter 1 for Brass account, 2 for BrassPlus account :\n";
        while(cin >> kind && (kind != '1' && kind != '2'))
        {
            cout << "Enter either 1 or 2\n";
        }
        if(kind == '1')
        {
            p_clients[i] = new Brass(temp,tempnum, tempbal);
        }
        else
        {
            double tmax, trate;
            cout << " ENter the overdraft limit :$";
            cin > tmax;
            cout << "Enter interst rate as a decimal fraction";
            cin >trate;
            p_clients[i] = new BrassPlus(temp,tempnum, tempbal, tmax, trate);
        }
        while(cin,get() != '\n')
        {
            continue;
        }
    }
    cout << endl;
    for(int i =0; i< CLIENTS; i++)
    {
        p_clients[i]->ViewAcct();
        cout << endl;
    }
    for(int i =0; i< CLIENTS; i++)
    {
        delete p_clients[i];// free memory
    }
    cout << "Done\n";
    return 0;
}