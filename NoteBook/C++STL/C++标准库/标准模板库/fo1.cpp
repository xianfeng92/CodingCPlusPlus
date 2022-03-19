#include <deque>
#include <algorithm>
#include <functional>
#include <iostream>
#include "print.hpp"

using namespace std;

int main(int argc, char** argv)
{
    deque<int> coll = {1,2,3,5,7,8,9,11,13};
    PRINT_ELEMENTS(coll,"initialized:");

    std::transform(coll.cbegin(),coll.cend(),coll.begin(),std::negate<int>());

    PRINT_ELEMENTS(coll,"nagate: ");

    std::transform(coll.cbegin(),coll.cend(),coll.cbegin(), coll.begin(),std::multiplies<int>());

    PRINT_ELEMENTS(coll,"square: ");
    return 0;
}