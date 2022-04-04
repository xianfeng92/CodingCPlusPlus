#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

#include "print.hpp"

using namespace std;

class IntSequence{
private:
    int value;
public:
    IntSequence(int initialValue):value(initialValue){

    }
    int operator(){
        return ++value;
    }
};

int main(int argc, char ** argv){

    list<int> coll;
    
    // start; number of elements;  generate values starting with 1
    generate_n(back_inserter(coll), 9, IntSequence(1));

    PRINT_ELEMENTS(coll);

    //  generate values starting with 42
    generate_n(next(coll.begin()),prev(coll.end()), IntSequence(42));

    PRINT_ELEMENTS(coll);

    return 0;
}