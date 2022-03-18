#include <list>
#include <algorithm>
#include <iostream>
#include "print.hpp"

using namespace std;

class AddValue{
private:
    int theValue;
public:
    AddValue(int v):theValue(v){}

    void operator()(int &elem)
    {
        elem += theValue;
    }
};

int main(int argc, char** argv)
{
    list<int> coll;

    for(int i = 0; i < 6 ; i++){
        coll.push_back(i);
    }

    PRINT_ELEMENTS(coll,"initialized: ");

    for_each(coll.begin(), coll.end(),AddValue(10));

    PRINT_ELEMENTS(coll,"After Add 10: ");

    for_each(coll.begin(), coll.end(),AddValue(*coll.begin()));

    PRINT_ELEMENTS(coll,"After add the first element");
    return 0;
}

