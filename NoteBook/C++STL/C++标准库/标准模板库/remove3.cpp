#include <algorithm>
#include <iterator>
#include <iostream>
#include <set>

using namespace std;

int main(int argc, char** argv)
{
    set<int> coll = {1,2,3,4,5,6,7,8,9};

    std::copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    int num = coll.erase(3);

    cout << "the number of remove elements is " << num << endl;

    std::copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}