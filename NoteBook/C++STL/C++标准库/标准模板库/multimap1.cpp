#include <map>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    multimap<int, string> coll;

    coll = {{1,"hello"},
        {2,"world"},
        {3,"fuck"},
        {4,"you"},
        {100,"Later"}
    };

    for(auto elem : coll)
    {
        cout << elem.second << endl;
    }
    cout << endl;

    return 0;
}