#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int main()
{
    unordered_set<string> cities = {"Shanghai", "Beijing", "Nanjing","Jiangsu"};

    for(const auto& elem : coll)
    {
        cout << elem << endl;
    }
    cout << endl;

    cities.insert({"London","Anhui"});

    for(const auto& elem : cities)
    {
        cout << elem << endl;
    }

    cout << endl;
    return 0;
}

