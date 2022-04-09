#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include "fopow.hpp"

using namespace std;
using namespace std::placeholders;

int main(int argc, char** argv)
{

    vector<int> coll = {1,2,3,4,5,6,7,8,9};

    std::transform(coll.begin(), coll.end(),ostream_iterator<float>(cout, " "), std::bind(fopow<float, int>,3,_1));

    cout << endl;
    std::transform(coll.begin(), coll.end(),ostream_iterator<float>(cout, " "), std::bind(fopow<float, int>,_1,3));
    cout << endl;

    return 0;
}