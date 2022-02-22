#include <iostream>
#include <malloc.h>


using namespace std;

int main()
{
    char *string1;
    char *string2;

    string1 = (char*)malloc(16);
    strcpy(string1,"0123456789AB");
    cout << "string1 is " << string1 << endl;
    string2 = realloc(string1,8);

    cout << "string2 is " << string2 << endl;
    cout << "string1 is " << string1 << endl;

    string1 = (char *)malloc(sizeof(char)*16);
    strcpy(string1,"0123456789AB");
    string2 = realloc(string1, 64));

    cout << "string2 is " << string2 << endl;
    cout << "string1 is " << string1 << endl;

    return 0;
}
