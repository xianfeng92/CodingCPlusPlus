#include <map>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
    map<string, double> coll{{"hello",2.12},{"world",2.32}};

    for_each(coll.begin(), coll.end(),[](pair<const string, double>& elem){
        elem.second *= elem.second;
    });


    for_each(coll.begin(), coll.end(),[](pair<const string, double>& elem){
        cout << elem.first << " " << elem.second << endl;
    });

    return 0;
}