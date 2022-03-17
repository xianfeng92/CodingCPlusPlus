#include <algorithm>
#include <vector>
#include <list>
#include <deque>

using namespace std;

int main(int argc, char** argv)
{
    list<int> coll1 = {1,3,2,6,5,8,6};
    vector<int> coll2;

    coll2.resize(coll1.size());

    std::copy(coll1.begin(),coll1.end(),coll2.begin());

    deque<int> coll3(coll2.size());

    std::copy(coll2.begin(),coll2.end(),coll3.begin());
    return 0;
}