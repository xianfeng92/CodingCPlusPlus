#include <vector>
#include <iostream>

using namespace std;


int main(int argc, char** argv){
    vector<int> coll;

    for(int i = -3; i < 9; i++){
        coll.push_back(i);
    }

    cout << "number distance: " << coll.end() - coll.begin() << endl;

    vector<int>::iterator pos;
    for(pos = coll.begin(); pos != coll.end();++pos){
        cout << *pos << endl;
    }

    cout << endl;

    for(int i = 0; i < coll.size(); i++){
        cout << coll.begin()[i] << endl;
    }

    for(pos = coll.begin(); pos != coll.end();pos += 2){
        cout << *pos << endl;
    }
    return 0;
}