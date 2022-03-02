// strtype4.cpp

#include<iostream> 
#include<string> // make string class available
#include<cstring>// C-style string library

int main()
{
    using namespace std;
    char charr[20];
    string str;

    cout << "The length of the string in charr before input :" << strlen(charr) << endl;
    cout << "The length of the string str before input :" << str.size() << endl;

    cout << "Enter a line of text: \n";
    cin.getline(charr,20);// indicate maximum length
    cout << "You Entered : " << charr << endl;

    cout << "Enter another line of text: \n";
    getline(cin,str);// cin now an argument; no length specifier
    cout << "You entered : " << str << endl;

    cout << "The length of string in charr after input : " << strlen(charr) << endl;
    cout << "The length of string in str after input : " << str.size() << endl;
    return 0;
}