#include<iostream>
#include "stock20.h"

const int STKS =4;

int main()
{
    Stock stocks[STKS] = {
        Stock("NIO",22,12.21),
        Stock("APPLE",21,12.21),
        Stock("NIOXF",12321,21.234),
        Stock("xforg",12,21.234)
    };

    std::cout << "Stock holdings\n";
    int st;
    for( st =0; st < STKS; st++ )
    {
        stocks[st].show();
    }

    // set pointer to first elements
    const Stock *pStock = &stocks[0];
    for( st = 1; st < STKS; st++ )
    {
        top =  &(top->topval(stocks[st]));
    }

    std::cout << "most valuable holdings:\n";
    top->show();
    return 0;
}