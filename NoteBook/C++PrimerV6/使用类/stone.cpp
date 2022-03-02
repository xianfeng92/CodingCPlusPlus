#include<iostream>
using std::cout;
#include "stonewt.h"

void display(const Stonewt &st, int n);

int main()
{
    Stonewt incognito = 275;
    Stonewt wolfe(285.7);
    Stonewt taft(21,8);

    cout << "The celebrity weight ";
    incognito.show_stone();

    cout << "The detective weight ";
    wolfe.show_stone();

    cout << "The presendent weight ";
    taft.show_stone();

    incognito = 276.8;
    taft = 325;

    cout <<"After dinner, the celebrity weight ";
    incognito.show_stone();
    cout << "After dinner, the presendent weight ";
    taft.show_stone();

    cout << "The Wrestler weight even more ";
    display(422,21);

    return 0;
}

void display(const Stonewt &st, int n)
{
    for(int i=0; i<n; i++)
    {
        cout << "Now ";
        st.show_stone();
    }
}



