#include <set>
#include <iostream>
#include <string>


using namespace std;

int main()
{
    multiset<string> cities = {"Shanghai", "Beijing", "Nanjing", "Jiangsu","Anhui"};

    for(auto elem : cities)
    {
        cout << elem << endl;
    }

    cout << endl;

    cities.insert({"Shanghai", "Beijing", "Nanjing", "Hangzhou"});

    for(const auto& elem : cities)
    {
        cout << elem << endl;
    }
    cout << endl;
    return 0;
}
