#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{

    vector<int> coll = {1,2,3,4,5,6,7,8,9};

    long sum = 0;
    for_each(coll.begin(), coll.end(), [&sum](int element){
        sum += element;
    };);

    double mv = static_cast<double>((sum)) / static_cast<double>(coll.size());
    cout << mv << endl;
}