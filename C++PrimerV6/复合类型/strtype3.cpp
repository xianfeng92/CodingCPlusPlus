// strtype3.cpp

#include <iostream>
#include<string>
#include<cstring>

int main()
{
    using namespace std;
    char charr1[20];
    char charr2[20] = "jaguar";
    string str1;
    string str2 = "panther";

    // assignment for string object and character arrays
    str1 = str2;
    strcpy(charr1, charr2);

    // appending for string object and character arrays
    str1 += " paste";
    strcpy(charr1, "juice");

    // finding the length of the string object and a C-Style string
    int len1 = str1.size();
    int len2 = strlen(charr1);

    cout << "The string " << str1 << " has length " << len1 << " characters.\n";
    cout << "The string " << charr1 << " has length " << len2 << " characters.\n";
    return 0;
}