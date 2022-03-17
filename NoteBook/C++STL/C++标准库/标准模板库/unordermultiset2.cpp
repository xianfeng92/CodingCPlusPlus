#include <unordered_set>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    std::unordered_multiset<int> coll;

    coll.insert({1,3,2,9,6,10,34});

    for(auto ele : coll)
    {
        cout << ele << endl;
    }

    coll.insert(21);

    for(auto ele : coll)
    {
        cout << ele << endl;
    }

    return 0;
}







