#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

int main(int argc, char** argv)
{
    list<int> coll;
    for(int i = 20; i <= 40 ; i++)
    {
        coll.push_back(i);
    }

    auto pos3 = std::find(coll.begin(), coll.end(),3);

    std::reverse(pos3, coll.end());

    auto pos25 = std::find(coll.begin(), coll.end(),25);

    auto pos35 = std::find(coll.begin(), coll.end(),35);


    cout << *max_element(coll.begin(), coll.end()) << endl;
    cout << *min_element(coll.begin(), coll.end()) << endl;

    return 0;
}

