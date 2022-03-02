// strtype.cpp

#include<iostream>
#include<string>

int main()
{
    using namespace std;

    char charr1[20];
    char charr2[20] = "jaguar";
    string str1;// create a empty string
    string str2 = "panther";// create a initialise string

    cout << "Enter a kind of feline: ";
    cin >> charr1;
    cout << "Enter a another kind of feline: ";
    cin >> str1;
    cout << "Here are some felines: \n";
    cout << charr1 << " " << charr2 << " " << str1 << " " << str2 << endl;
    cout << "The third letter in " << str2 << " is " << str2[2] << endl;
    
    return 0;
}