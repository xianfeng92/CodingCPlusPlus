#include <algorithm>
#include <iterator>
#include <list>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    list<int> coll;
    for(int i = 0; i < 6; i++)
    {
        coll.push_front(i);
        coll.push_back(i);
    }

    cout << "pre:";
    copy(coll.begin(), coll.end(),ostream_iterator<int>(cout, " "));
    cout << endl;

    std::remove(coll.begin(), coll.end(), 3);

    cout << "post: " << endl;
    copy(coll.begin(), coll.end(),ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}