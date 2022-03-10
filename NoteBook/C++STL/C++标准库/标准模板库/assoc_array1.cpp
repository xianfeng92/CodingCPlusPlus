#include <unordered_map>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    unordered_map<string, float> coll;

    coll["hello"] = 1.0f;
    coll["world"] = 2.0f;
    coll["world2"] = 3.0f;
    coll["world3"] = 4.0f;
    coll["world4"] = 5.0f;
    coll["world5"] = 6.0f;
    coll["world6"] = 7.0f;
    coll["world7"] = 8.0;
    coll["world8"] = 9.0;

    coll["hello"] += 1.0f;

    cout << "coll[hello] is " << coll[hello] << endl;
    return 0;
}