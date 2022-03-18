#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


class PrintInt{
    public:
        void operator()(int elem) const {
            cout << elem << endl;
        }
};

int main(int argc, char **argv)
{
    vector<int> coll;

    for(int i = 0; i < 9 ; i++){
        coll.push_back(i);
    }

    for_each(coll.begin(), coll.end(),PrintInt());

    cout << endl;
    return 0;
}