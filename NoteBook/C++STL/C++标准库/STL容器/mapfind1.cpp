#include <iostream>
#include <map>
#include <algorithm>
#include <utility>


using namespace std;

int main(int argc, char** argv){

    map<float, float> coll = {
        {1.1,2.2},
        {3.3,4.3},
        {5.5,6.5},
        {7.7,8.7},
        {9.9,10.2}
    };

    // search an element with key 3.3
    auto pos = coll.find(3.3);
    if(pos != coll.end()){
        cout << "key 3.3 found" << endl;
        cout << pos->first << " " << pos->second << endl;
    }

    // search an element with value 8.7
    auto pos = std::find_if(coll.begin(), coll.end(),[](decltype(coll)::value_type &elem){
        return elem.second == 8.7;
    });

    if(pos != coll.end())
    {
        cout << "value 8.7 found" << endl;
        cout << pos->first << " " << pos->second << endl;
    }

    return 0;
}