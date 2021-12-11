// strgback.cpp

#include<iostream>

char * buildstr(char ch, int n);

int main()
{
    using namespace std;
    int times = 0;
    char ch;
    cout << "Enter a character: ";
    cin >> ch;
    cout << "Enter a integer: ";
    cin >> times
    char *pt = buildstr(ch, times);
    cout << pt << endl;
    delete [] pt;
    pt = buildstr('+', 20);
    cout << pt << "-DONE-" << pt << endl;
    delete [] pt;
    return 0;
}


char * buildstr(char ch, int n)
{
    char *pstr = new char[n+1];
    pstr[n] = '\0';
    while(n-- > 0)
    {
        pstr[n] = ch;
    } 
    return pstr;
}
