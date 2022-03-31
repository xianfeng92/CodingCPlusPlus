#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

vod print(int elem){
    cout << elem << endl;
}

int  main(int argc, char **argv){

    list<int> coll = {1,2,3,4,5,6,7,8,9};
    for_each(coll.begin(), coll.end(),print);

    for_each(coll.rbegin(), coll.rend(), print);

    cout << endl;
    return 0;
}