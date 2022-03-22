#include <array>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <functional>
#include "print.hpp"

using namespace std;

int main(int argc, char** argv)
{
    array<int, 10> coll = {11, 12, 13, 14, 15, 16, 17};

    PRINT_ELEMENTS(coll);

    coll.back() = 999999999;
    coll[coll.size() -1 ] = 42;
    PRINT_ELEMENTS(coll);

    cout << accumulate(coll.begin(), coll.end(),0) << endl;

    transform(coll.cbegin(),coll.cend(),a.begin(),negate<int>());
    PRINT_ELEMENTS(coll);

    return 0;
}