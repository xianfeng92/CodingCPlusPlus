#include <iterator>
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main(int argc, char** argv){
    
    list<int> coll;

    for(int i = 3; i < 9; ++i){
        coll.push_back(i);
    }

    list<int>::iterator pos;

    pos = std::find(coll.begin(), coll.end(),5);

    if(pos != coll.end()){
        cout << "difference between begging and 5 is " << distance(coll.begin(),pos) << endl;
    }else{
        cout << " 5 not found" << endl;
    }

    return 0;
}