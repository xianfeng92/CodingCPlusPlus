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



int main(int argc, char** argv){

    list<int> coll;
    IntSequence seq(1);

    // insert value from 1 to 4
    // pass function object by reference
    // so that will continue with 5
    generate_n<back_insert_iterator<int>, int, IntSequence&>(back_inserter(coll), 4, seq);
    PRINT_ELEMENTS(coll);

    // insert value from 42 to 45
    generate_n(back_inserter(coll),4, IntSequence(42));
    PRINT_ELEMENTS(coll);
    // so that will continue with 5
    generate_n(back_inserter(coll), 4,seq);
    PRINT_ELEMENTS(coll);

    generate_n(back_inserter(coll), 4 , seq);
    PRINT_ELEMENTS(coll);

    return 0;
}