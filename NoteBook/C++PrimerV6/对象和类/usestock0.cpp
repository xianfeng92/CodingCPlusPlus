#include<iostream>
#include "Stock00.h"

int main()
{
    Stock fluffy_the_cat;
    fluffy_the_cat.acquire("hello",20,12.32);
    fluffy_the_cat.show();
    fluffy_the_cat.buy(15,21.32);
    fluffy_the_cat.show();
    fluffy_the_cat.sell(10,21.32);
    fluffy_the_cat.show();
    return 0;
}

