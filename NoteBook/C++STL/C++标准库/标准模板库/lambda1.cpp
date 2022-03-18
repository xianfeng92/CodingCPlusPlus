#include <algorithm>
#include <deque>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    deque<int> coll = {1,3,12,45,654,233,7,9};
    int x = 5;
    int y = 10;

    auto pos = std::find_if(coll.begin(), coll.end(),[=](int value) { return value > x && value < y; });

    cout << "first y > element > x is " << *pos << endl;
    return 0;
}

