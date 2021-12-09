// textin2.cpp

#include <iostream>

int main()
{
    using namespace std;
    char ch;
    int count = 0;

    cout << "Enter character; enter # to quit:\n";
    cin.get(ch);
    while (ch != '#')
    {
        cout << ch;
        ++ count;
        cin.get(ch);
    }
    cout << endl << count << " characters entered\n";
    return 0;
}