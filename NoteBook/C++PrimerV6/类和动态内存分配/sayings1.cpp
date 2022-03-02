#include<iostream>
#include "string1.h"

const int ArSize = 10;
const int MaxLen = 80;


int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    String name;
    cout << "Hi, What your name ? " << endl;
    cin >> name;

    cout << name << ", please enter up to " << ArSize << " short sayings <empty line to quite>:\n";
    String sayings[ArSize];
    char temp[MaxLen];
    int i;
    for(i = 0; i < ArSize; i++)
    {
        cout << i+1 << ": ";
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
            sayings[i] = temp;
        }
    }
    int total = i;
    if(total > 0)
    {
        cout << "Here are you says:\n";
        for(int i = 0 ; i < ArSize; i++)
        {
            cout << sayings[i][0] << ": " << sayings[i] << endl;
        }
        int shortest = 0;
        int first = 0;
        for(i=1; i<total; i++)
        {
          if(sayings[i].length() < sayings[shortest].length)
          {
             shortest = i;
          }  
          if(sayings[i] < sayings[first])
          {
              first = i;
          }
        }
        cout << "Shortest: " << sayings[shortest] << endl;
        cout << "First: " << sayings[first] << endl;
        cout << "This Program used " << String::HowMany() << " String objects" << endl;
    }
    else
    {
        cout << " No input , Byte~\n"
    }
    return 0;
}