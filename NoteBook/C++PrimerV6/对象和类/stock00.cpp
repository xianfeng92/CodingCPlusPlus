#include<iostream>
#include "Stock00.h"

void Stock::acquire(const std::string &co, long n, double pr)
{
    company = co;
    if(n < 0)
    {
        std::cout << "Number of share cannot be negative" << std::endl;
        share = 0;
    }
    else
    {
        share = n;
    }
    share_val = pr;
    set_tot();
}


void Stock::buy(long num, double price)
{
    if(num < 0)
    {
        std::cout << "Number of stock cannot be negative" << std::end
    }
    else
    {
        share += num;
        share_val = price;
        set_tot();
    }
}

void Stock::sell(long num, double price)
{
    using std::cout;
    if(num < 0)
    {
        cout << "Number of Stock can't be negative" << "\n";
    }
    else
    {
        share -= num;
        share_val = price;
        set_tot();
    }
}


void Stock::update(double price)
{
    share_val = price;
    set_tot();
}


void Stock::show()
{
    std::cout << "Company is " << company << " share is " << share <<
    << " Share price is " << share_val << " Total Worth is " << total_val << std::endl;
}
