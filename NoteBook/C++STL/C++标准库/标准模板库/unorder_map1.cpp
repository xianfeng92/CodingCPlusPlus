#include <unordered_map>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    unordered_map<string, double> coll = {{"Shanghai",1.2}, {"Beijing",2.3},{"NanJing",3.21}};

    for(pair<string, double>& elem : coll)
    {
        cout << " " << elem.first << " " << elem.second << endl;
    }

    for(const auto& item : coll)
    {
        cout << item.first << " " << item.second << endl;
    }
    cout << endl;

    return 0;
}