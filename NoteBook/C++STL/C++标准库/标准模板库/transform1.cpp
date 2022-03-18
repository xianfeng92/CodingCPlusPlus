#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "print.hpp"

int square(int value)
{
    return value * value;
}

int main(){
    std::set<int> coll1;
    std::vector<int> coll2;

    for(int i = 0; i <= 9; ++i){
        coll1.insert(i);
    }

    PRINT_ELEMENTS(coll1,"initialized:");

    std::transform(coll1.begin(),coll1.end(),std::insert_iterator(coll2),square);

    PRINT_ELEMENTS(coll2,"squared:");
    cout << endl;
    return 0;
}