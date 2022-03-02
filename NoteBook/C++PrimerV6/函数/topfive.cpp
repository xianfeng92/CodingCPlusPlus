// topfive.cpp

#include<iostream>
#include<string>

using namespace std;

const int SIZE = 5;

void display(const string str[], int n);

int main()
{
    string list[SIZE];// a array holds five string object
    cout << "Enter your " << SIZE << "favorite astronomical sights:\n";
    for(int i=0; i<SIZE; i++)
    {
        cout << i + 1 << ":";
        getline(cin, list[i]);
    }
    cout << "Your list is: ";
    display(list, SIZE);
    return 0;
}

void display(const string str[], int n)
{
    for(int i=0; i<n; i++)
    {
        cout << i + 1 << ":" << str[i] << endl;
    }
}