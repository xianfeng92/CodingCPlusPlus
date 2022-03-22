#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace std;

int main(int argc, char** argv)
{
    deque<string> coll;

    coll.assign(3,string("string"));
    coll.push_back("last string");
    coll.push_front("first string");

    copy(coll.cbegin(),coll.cend(),ostream_iterator<string>(cout, "\n"));
    cout << endl;

    for(unsigned int i = 0 ; i < coll.size() ; i++)
    {
        coll[i] = "another" + coll[i];
    }

    coll.resize(4,"resize string");

    copy(coll.cbegin(),coll.cend(),ostream_iterator<string>(cout, " "));

    cout << endl;
    return 0;
}