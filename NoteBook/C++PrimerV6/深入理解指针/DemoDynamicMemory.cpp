#include <iostream>
#include <malloc.h>

using namespace std;

int main()
{
    int *pi = (int *)malloc(sizeof(int));
    if(pi != nullptr)
    {
        *pi = 5;
    }
    cout << "sizeof int is " << sizeof(int) << endl;
    free(pi);
    return 0;
}