// delete.cpp

#include <iostream>
#include <cstring>

using namespace std;
char *getName();

int main()
{
    char * name;
    name = getName();
    cout << name << " at " << (int*)name << "\n";
    delete [] name;
    return 0;
}

char * getName()
{
    char tmp[80];
    cout << "Enter last name: ";
    cin >> tmp;
    char *pn = new char[strlen(tmp) + 1];
    strcpy(pn, tmp);
    return pn;
}