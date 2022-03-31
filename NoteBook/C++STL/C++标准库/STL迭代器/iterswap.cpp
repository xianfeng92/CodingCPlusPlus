#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include "print.hpp"

using namespace std;

int main(int argc, char** argv){

    list<int> coll;

    for(int i=0; i < 9; ++i){
        coll.push_back(i);
    }

    std::iter_swap(coll.begin(), std::next(coll.begin()));

    PRINT_ELEMENTS(coll);

    std:iter_swap(coll.begin(), std::prev(coll.end()));

    PRINT_ELEMENTS(coll);

    return 0;
}