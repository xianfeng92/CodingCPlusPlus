#include<iostream>
#include<cstdlib>
#include<ctime>
#include "string1.h"


const int ArSize = 10;
const int MaxLen = 80;

int main()
{
    using namespace std;
    String name;
    cout << "Hi, what your name \n";
    cin >> name;

    cout << name << ", please enter up to " << ArSize << " short sayings<empty to quite>:\n";
    String sayings[ArSize];
    char temp[MaxLen];
    int i = 0;
    for(int i=0; i<ArSize; i++)
    {
        cin.get(temp,MaxLen);
        while(cin && cin.get() != '\n')
        {
            continue;
        }
        if(!cin || temp[0] == '\0')
        {
            break;
        }
        else
        {
            saying[i] = temp;
        }
    }
    int total = i;
    if(total > 0)
    {
        cout << "Here you sayings:\n";
        for(int i = 0 ; i < ArSize; i++)
        {
            cout << sayings[i] << '\n';
        }
        String *shortest = &sayings[0];
        String *first = &sayings[0];
        for(int i = 0 ; i < total; i++)
        {
            if(sayings[i].length() < shortest->length())
            {
                shortest = &sayings[i];
            }
            if(sayings[i] < *first)
            {
                first = &sayings[i];
            }
        }
        cout << "Shortest: " << *shortest << '\n';
        cout << "First: " << *first << '\n';
        srand(time(NULL));
        int choice = rand() % total;
        String *favorite = new String(sayings[choice]);
        cout << "My favorite is " << *favorite << endl;
        delete favorite;
    }
    else
    {
        cout << "Not much to sayings:\n";
    }
    return 0;
}