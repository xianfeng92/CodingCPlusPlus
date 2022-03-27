#include <map>
#include <string>
#include<iostream>
#include <iomanip>

using namespace std;

int main(int argc, char** argv)
{
    multiimap<string, string> dict;

    dict.insert({
        {"day","TAG"},
        {"strange","fremd"},
        {"car","auto"},
        {"smart","elegant"},
        {"strange","sales"},
        {"smart","kind"},
        {"clever","hello"},
    });

    cout.self(ios::left, ios::adjustfield);

    cout << " " << setw(10) << "english" << "german" << endl;

    cout << setfill('-') << setw(20) << "" << setfill(" ") << endl;

    for(auto &elem : coll){
        cout << " " << setw(10) << elem.first << elem.second << endl;
    }

    return 0;
}