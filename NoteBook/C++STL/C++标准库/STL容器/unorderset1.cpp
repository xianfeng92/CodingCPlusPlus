#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include "print.hpp"

using namespace std;

int main(int argc, char** argv){

    unordered_set<int> coll = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};

    //printf all elements
    PRINT_ELEMENTS(coll);

    coll.insert({1,2,-9,-2});
    PRINT_ELEMENTS(coll);

    coll.erase(2);

    coll.insert(accumulate(coll.begin(), coll.end()));

    if(coll.find(9) != coll.end()){
        cout << "9 is available" << endl;
    }

    unordered_set<int>::iterator pos;
    for(pos = coll.begin(); pos != coll.end();){
        if(*pos < 0){
            pos = coll.erase(pos);
        }else{
            ++pos;
        }
    }

    PRINT_ELEMENTS(coll);
    return 0;
}