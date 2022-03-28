#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <iterator>

using namespace std;

int main(int argc, char** argv)
{
    set<string> coll(istream_iterator<string>(cin), istream_iterator<string>());
    copy(coll.cbegin(), coll.cend(),ostream_iterator<string>(cout, "\n"));

    return 0;
}