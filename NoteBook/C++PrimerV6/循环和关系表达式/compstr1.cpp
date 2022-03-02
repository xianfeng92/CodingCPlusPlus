// compstr1.cpp

#include <iostream>
#include <cstring>


int main()
{
    using namespace std;
    char word[5] = "?ate";
    for(char ch = 'a'; strcmp(word, "mate"); ch++)
    {
        cout << word << "\n";
        word[0] = ch;
    }
    cout << "After loop ends, word is " << word << "\n";
    return 0;
}