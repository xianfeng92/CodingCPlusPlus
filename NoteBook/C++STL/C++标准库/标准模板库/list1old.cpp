#include <list>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    list<char> coll;

    for(char c = 'a'; c <= 'z'; c++)
    {
        coll.push_back(c);
    }

    list<char>::const_iterator pos;
    for(pos = coll.begin(); pos != coll.end(); pos++)
    {
        cout << *&pos << endl;
    }
    return 0;
}