#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    char *str = (char*)malloc(sizeof(char) * 13);
    strcpy(str, "0123456789AB");
    cout << "str is " << str << endl;
    char *str2 = str;
    free(str);
    free(str2);
}