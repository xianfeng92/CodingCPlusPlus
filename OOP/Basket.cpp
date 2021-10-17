#include "Basket.h"

using namespace std;


double Basket::total_recipt(ostream &os) const 
{
    double sum = 0;
    // upper_bound() 返回一个迭代器，该迭代器指向这批元素的尾后位置
    // upper_bound()可以使得我们跳过与关键字相同的所以元素
    for(auto iter = items.cbegin(); iter != items.end(); iter = item.upper_bound(*iter))
    {
        sum += print_total(os, **iter,items.count(*iter)); 
    }
    os << "Total sales: " << sum << endl;
    return sum;
}





