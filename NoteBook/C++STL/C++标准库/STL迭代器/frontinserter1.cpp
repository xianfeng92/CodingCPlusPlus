#include <list>
#include <algorithm>
#include <iterator>
#include "print.hpp"

using namespace std;

int main(int argc, char** argv){

    list<int> coll;
    // create front insert for coll
    front_inserter_iterator<list<int> > iter(coll);

    *iter = 1;
    ++iter;
    *iter = 2;
    ++iter;
    *iter = 3;

    PRINT_ELEMENTS(coll);
    // create front insert for coll and insert element
    // convinient way
    front_inserter(coll) = 33;
    front_inserter(coll) = 34;
    PRINT_ELEMENTS(coll);

    std::copy(coll.begin(), coll.end(), front_inserter(coll));

    PRINT_ELEMENTS(coll);
    return 0;
}