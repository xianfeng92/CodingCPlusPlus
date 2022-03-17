#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    vector<int> coll = {21,1,2,4,3,6,10,9,8};

    auto mini_pos = std::min_element(coll.begin(), coll.end());
    cout << "mini_pos is " << *mini_pos << endl;

    auto max_pos = std::max_element(coll.begin(), coll.end());
    cout << "max_pos is " << *max_pos << endl;

    std::sort(coll.begin(), coll.end());

    auto pos3 = std::find(coll.begin(), coll.end(),3);

    std::reverse(pos3, coll.end());

    for(auto elem : coll)
    {
        cout << "elem " << elem << endl;
    }
    cout << endl;
    return 0;
}