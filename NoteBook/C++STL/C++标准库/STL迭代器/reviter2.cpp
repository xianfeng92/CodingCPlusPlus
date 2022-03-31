#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv){
    vector<int> coll = {0,1,2,3,4,5,6,7};

    vector<int>::iterator pos;
    pos = std::find(coll.begin(),coll.end(),5);

    cout << "*pos is " << *pos << endl;

    vector<int>::const_reverse_iterator rpos(pos);

    cout << "*rpos is " << *rpos << endl;
    return 0;
}