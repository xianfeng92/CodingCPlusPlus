// cctypes.cpp

#include<iostream>
#include<cctype>

int main()
{
    using namespace std;
    cout << "Enter text for analysis, and type S for terminate input .\n";
    char ch;
    int spaces = 0;
    int digits = 0;
    int chars = 0;
    int puncs = 0;
    int other = 0;

    cin.get(ch);
    while (ch != 'S')
    {
        if(isalpha(ch))
        {
            ++chars;
        }
        else if(isdigit(ch))
        {
            ++digits;
        }
        else if(isspace(ch))
        {
            ++spaces;
        }
        else if(ispunct(ch))
        {
            ++puncs;
        }
        else
        {
            ++other;
        }
        cin.get(ch);
    }
}