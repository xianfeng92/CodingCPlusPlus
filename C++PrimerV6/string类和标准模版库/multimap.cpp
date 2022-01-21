#include<iostream>
#include<string>
#include<map>
#include<algorithm>


typedef int keytype;
typedef std::pair<const keytype, std::string> pair;
typedef std::multimap<KeyType, std::string> mapCode;

int main()
{
    using namespace std;
    mapCode codes;

    codes.insert(pair(123,"shanghai"));
    codes.insert(pair(234,"beijing"));
    codes.insert(pair(456,"nanjing"));
    codes.insert(pair(132,"jiangsu"));
    codes.insert(pair(512,"NIOXF"));
    codes.insert(pair(132,"hello"));
    codes.insert(pair(456,"world"));


    cout << "Number of cities with code 132 :"
    << codes.count(132) << endl;

    cout << "Number of cities with code 512 :" 
    << codes.count(512) << endl;

    cout << "Number of cities with code 456 :"
    << codes.count(456) << endl;

    mapCode::iterator it;
    for(it = mapCode.begin(); it != mapCode.end(); it++)
    {
        cout << (*it).first << (*it).second << endl;
    }

    pair<mapCode::iterator, mapCode::iterator> range = codes.equal_range(132);
    cout << "Cities with code 132: ";

    for(it = range.first; it != range.second; it ++)
    {
        cout << (*it).second << endl;
    }

    return 0;
}