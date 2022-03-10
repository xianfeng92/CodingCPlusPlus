#include <forward_list>
#include <iostream>

using namespace std;

int main()
{
    forward_list<long> coll = {2,3,4,5,6,7,8};

    coll.resize(10);
    coll.resize(10,99);

    for(auto elem : coll)
    {
        cout << elem << endl;
    }
    cout << endl;
    return 0;
}