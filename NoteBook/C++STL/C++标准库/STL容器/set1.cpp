#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    std::set<int, std::greater<int>> coll1;

    coll1.insert({4,5,2,8,1});
    coll1.insert(7);

    // print all elements
    for(auto pos = coll1.begin(); pos != coll1.end();++pos){
        cout << *pos << endl;
    }

    for(auto ele: coll1){
        cout << elem << endl
    }

    cout << endl;

    auto status = coll1.insert(4);
    if(status.second){
        std::cout << "4 inserted as a element" << std::endl;
    }else{
        std::cout << "4 already exists" << std::endl;
    }

    set<int> coll2(coll1.begin(), coll1.end());

    copy(coll2.cbegin(),coll2.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;

    coll2.erase(coll2.begin(), coll2.find(3));

    int num;
    num = coll2.erase(5);
    cout << num << "elements removed." << endl;

    copy(coll2.cbegin(),coll2.cend(),ostream_iterator<int>(cout, " "));

    cout << endl;
    
}