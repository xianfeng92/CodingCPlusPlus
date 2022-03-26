#include <iostream>
#include <set>

#include "print.hpp"

using namespace std;

class RuntimeCmp{
    public:
        enum cmp_mode {normal,reverse};
    private:
        cmp_mode mode;
        RuntimeCmp(cmp_mode m = normal) : mode(m) {}
        template <typename T>
        bool operator()(const T& t1, const T& t2){
            return mode == normal ? t1 < t2 : t1 > t2;
        }
        
        bool operator==(const RuntimeCmp& rc) const {
            return mode == rc.mode;
        }
};

typedef set<int,RuntimeCmp> Intset;

int main() {
    Intset coll1 = {3,2,8,6,7};
    PRINT_ELEMENTS(coll1, "coll1:");

    RuntimeCmp reverse_order(RuntimeCmp::reverse);

    Intset coll2(reverse_order);
    coll2 = {9,1,3,6,4,2};
    PRINT_ELEMENTS(coll2, "coll2:");


    coll1 = coll2;
    coll1.insert(3);
    PRINT_ELEMENTS(coll1, "coll1:");
}