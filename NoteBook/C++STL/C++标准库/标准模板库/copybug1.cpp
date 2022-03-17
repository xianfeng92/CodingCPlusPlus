#include <iostream>
#include <algorithm>
#include <list>
#include <vector>

using namespace std;


int main(int argc, char** argv)
{
    list<int> coll1 = {1,2,32,1,2,3,4,5};

    vector<int> coll2;

    // Runtime error
    std::copy(coll1.begin(), coll1.end(),coll2.begin());
    return 0;
}