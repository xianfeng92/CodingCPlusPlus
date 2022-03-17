#include <algorithm>
#include <iterator>
#include <iostream>
#include <list>

using namespace std;

int main(int argc, char** argv)
{
    list<int> coll;

    for(int i=0; i < 6 ; i++)
    {
        coll.push_front(i);
        coll.push_back(i);
    }

    cout << endl;

    // remove all elements with values 3(poor performance)
    coll.erase(std::remove(coll.begin(), coll.end(),3), coll.end());
    // remove all elements with values 4(good performance)
    coll.erase(4);

    return 0;
}