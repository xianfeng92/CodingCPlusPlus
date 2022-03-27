#include <iostream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

int main(int argc, char** argv)
{
    typedef map<string, float> StringFloatMap;

    StringFloatMap  stocks;

    stocks["NIO"] = 100.21;
    stocks["Apple"] = 100.21;
    stocks["BMW"] = 90.32;
    stocks["Simens"] = 87.23;
    stocks["VM"] = 9.32;

    // print all elements
    StringFloatMap::iterator pos;
    for(pos = stocks.begin(); pos != stocks.end();++pos)
    {
        cout << pos->first << " " << pos->second << endl;
    }

    // boom(all price double)
    for(pos = stocks.begin(); pos != stocks.end();++pos)
    {
        pos->second *= 2;
    }

    // print all elements
    for(pos = stocks.begin(); pos != stocks.end();++pos)
    {
        cout << pos->first << " " << pos->second << endl;
    }

    stocks["Volkwagen"] = stocks["VM"];

    coll.erase("VM");

    // print all elements

    for(pos = stocks.begin(); pos != stocks.end();++pos)
    {
        cout << pos->first << " " << pos->second << endl;
    }

    return 0;
}