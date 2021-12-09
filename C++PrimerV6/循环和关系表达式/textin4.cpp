// textin4.cpp

#include<iostream>

int main()
{
    using namespace std;
    int ch;
    int count = 0;

    cout << "Enter character; enter # to quit:\n";
    while (ch = cin.get()) != EOF;)
    {
        cout.put(char(ch));
        ++ count;
        ch = cin.get();
    }
    cout << endl << count << " characters entered\n";
    return 0;
}