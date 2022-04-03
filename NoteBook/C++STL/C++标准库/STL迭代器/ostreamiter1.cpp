#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main(int argc, char** argv){

    ostream_iterator<int> intWriter(cout," ");

    *intWriter = 42;
    ++intWriter;
    *intWriter = 77;
    ++intWriter;

    *intWriter = -5;

    vector<int> coll = {1,2,3,4,5,6,7,8,9};
    std::copy(coll.begin(),coll.end(),ostream_iterator<int>(cout));
    cout << endl;

    std::copy(coll.begin(),coll.end(),ostream_iterator<int>(cout, "<"));

    return 0;
}