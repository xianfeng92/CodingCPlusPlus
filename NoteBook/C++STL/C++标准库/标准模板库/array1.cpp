#include <array>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    array<string,5> coll = {"hello", "world"};

    for(int i = 0; i < coll.size(); i++)
    {
        cout << coll[i] << endl;
    }

    cout << endl;
    return 0;
}