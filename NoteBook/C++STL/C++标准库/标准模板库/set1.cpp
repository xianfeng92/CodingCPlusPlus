#include <set>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    typedef set<int> Intset;

    Intset coll;

    coll.insert(1);
    coll.insert(2);
    coll.insert(3);
    coll.insert(4);
    coll.insert(5);
    coll.insert(6);
    coll.insert(7);
    coll.insert(8);

    Intset::const_iterator pos;
    for(pos = coll.begin(); pos != coll.end(); ++pos)
    {
        cout << *pos << '\n';
    }

    cout << '\n';

    return 0;
}