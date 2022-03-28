#include <unordered_set>
#include "print.hpp"

using namespace std;

int main(int argc, char **argv){
    unordered_multiset<int> coll = {1,2,3,4,5,6,7,8,9,10};

    coll.insert({1,2,3,4,5,6,7,8,9,10});
    PRINT_ELEMENTS(coll);

    coll.erase(2);

    auto pos = coll.find(9);
    if(pos != coll.end()){
        coll.erase(pos);
    }
    PRINT_ELEMENTS(coll);
    return 0;
}