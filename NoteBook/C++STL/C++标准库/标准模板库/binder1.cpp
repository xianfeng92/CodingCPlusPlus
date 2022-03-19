#include <set>
#include <deque>
#include <algorithm>
#include <iostream>
#include <iterator>
#include "print.hpp"

using namespace std;
using namespace std::placeholders;

int main(int argc, char** argv)
{
    set<int, std::greater<int>> coll1 = {12,1,9,7,10,8,11,88};
    deque<int> coll2;

    PRINT_ELEMENTS(coll1, "initialzed: ");
    std::transform(coll1.begin(), coll1.end(),std::insert_iterator(coll2),std::bind(multiplies<int>,_1,10));

    PRINT_ELEMENTS(coll2, "transform: ");

    std::replace_if(coll2.begin(),coll2.end(),std::bind(std::equal_to<int>,_1,70));
    PRINT_ELEMENTS(coll2, "replaced ");

    coll2.erase(std::remove_if(coll2.begin(),coll2.end(),bind(logical_and<bool>()),bind(std::greater_equal<int>(),_1,50)), bind(less_equal<int>(),_1,80));
    PRINT_ELEMENTS(coll2, "removed ");
    return 0;
}