#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    char *str = (char*)malloc(sizeof(char) * 13);
    strcpy(str, "0123456789AB");
    cout << "str is " << str << endl;

    free(str);
    free(str);

    char *str2 = (char *)malloc(sizeof(char) * 13);
    strcpy(str2, "0123456789AB");

    cout << "str is " << str << endl;

    int *pi = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i <10 ; i++)
    {
        pi[i] = i;
    }
    
    for (int i = 0; i < 10; i++)
    {
        cout << pi[i] << " ";
    }

    cout << endl;

    free(pi);
    for (int i = 0; i < 10; i++)
    {
        cout << pi[i] << " ";
    }
}