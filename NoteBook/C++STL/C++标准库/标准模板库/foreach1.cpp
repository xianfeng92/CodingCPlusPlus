#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void print(int elem){
    cout << elem << " ";
}

int main(int argc, char** argv)
{
    vector<int> coll;
    for(int i = 0; i <= 9; ++i){
        coll.push_back(i);
    }

    std::for_each(coll.begin(), coll.end(), print);
    cout << endl;
    
    return 0;
}