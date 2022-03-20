#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
    vector<int> coll1;
    vector<int> coll2;

    vector<int>::iterator pos = coll1.begin();
    // begining is behind of the range
    std::reverse(++pos,coll1.end());

    for(int i = 0; i < 9; i++)
    {
        coll1.push_back(i);
    }

    // RUNTIME_ERROR
    // overrite nonexistent elements
    std::copy(coll1.cbegin(),coll1.cend(),coll,coll2.begin());


    // RUNTIME_ERROR
    // collection mistaken
    std::copy(coll1.cbegin(),coll2.cend(),coll2.begin());
    return 0;
}