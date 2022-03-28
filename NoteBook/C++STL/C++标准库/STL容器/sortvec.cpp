#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>

using namespace std;

int  main(int argc, char** argv)
{
    vector<string> coll(istream_iterator<string>(cin), istream_iterator<string>());
    sort(coll.begin(), coll.end());
    unique_copy(coll.begin(), coll.end(),ostream_iterator<string>(cout, " "));
    return 0;
}