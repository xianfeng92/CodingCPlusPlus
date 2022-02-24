#include<cstring>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s1("hello world");
    string::size_type pos = s1.find("world");
    s1.replace(pos,5,"nio");

    cout << "s1 is " << s1 << endl;

    string aString("see you");

    aString.insert(4,"hello ");

    cout << "aString is " << aString << endl;

    // string s;

    // s += aString;
    // s += "two \n line ";
    // s.append(aString);
    // s.append(aString, 1, 3);
    // s.append(aString, 2, string::npos);
    
    // s.push_back('\0');


    return 0;
}