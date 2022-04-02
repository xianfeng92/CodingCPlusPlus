#include <vector>
#include <algorithm>
#include <iterator>
#include "print.hpp"

using namespace std;

int main(int argc, char** argv){

    vector<int> coll;
    // create back insert for coll
    back_insert_iterator<vector<int> > iter(coll);

    // insert element with usually iterator interface
    *iter = 1;
    ++iter;
    *iter = 2;
    ++iter;
    *iter = 3;
    PRINT_ELEMENTS(coll);

    // create back insert and insert elements
    // convinienty way of inserting
    back_inserter(coll) = 44;
    back_inserter(coll) = 55;
    PRINT_ELEMENTS(coll);


    coll.resize(2 * coll.size());

    std::copy(coll.begin(), coll.end(),back_inserter(coll));
    PRINT_ELEMENTS(coll);

    return 0;
}