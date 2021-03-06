#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <regex>

using namespace std;

int main()
{
    string s("The zip code of Braunschweig is Germany is 38100");
    cout << "original: " << s << endl;

    transform(s.cbegin(), s.cend(), s.begin(), [](char c)
    {
        return tolower(c);
    });

    cout << "lowed is " << s << endl;

    transform(s.cbegin(), s.cend(), s.begin(), [](char c)
    {
        return toupper(c);
    });
    cout << "upper is " << s << endl;

    string g("Germany");
    string::const_iterator pos;
    pos = search(s.cbegin(), s.cend(),g.cbegin(), g.cend(),
    [](char c1, char c2){
        return toupper(c1) == toupper(c2);
    });

    if(pos != s.cend())
    {
        cout << "substring " << g << " find at index " << pos - s.cbegin() << endl;
    }
    return 0;
}