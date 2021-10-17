#include "Bulk_Quote.h"


using namespace std;

Bulk_Quote::Bulk_Quote(const string& book,double p,string qty,double disc):Quote(book,p),min_qty(qty),discount(disc){}


double Bulk_Quote::net_price(size_t cnt) const
{
    if (cnt > min_qty)
    {
        return cnt * (1 - discount) * price;
    }
    else
    {
        return cnt * price;
    }
}


