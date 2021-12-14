// leftover.cpp

#include<iostream>

unsigned long left(unsigned long num, int ct);
char * left(const char * str, int n);

int main()
{
    using namespace std;
    const char * trip = "helloworld!!!";// test value
    unsigned long n = 12345678;// test value
    int i = 0;
    char *temp;
    for(int i = 0; i < 10; i++)
    {
        cout << left(n,i);
        temp = left(trip,i);
        cout << temp << '\n';
        delete[] temp;
    }
    return 0;
}


unsigned long left(unsigned long num, int ct)
{
    unsigned digits = 1;
    unsigned long n = num;
    if(ct == 0 || num == 0)
    {
        return 0;
    }
    while(n /= 10)
    {
        ++digits;
    }
    if(digits > ct)
    {
        ct = digits -ct;
        while(ct--)
        {
            num /= 10;
        }
        return num;
    }
    else
    {
        return num;
    }
}

char * left(const char * str,int n)
{
    if(n < 0)
    {
        return 0;
    }
    char *p = new char[n+1];
    int i;
    for(i = 0; i <n && str[i]; i++)
    {
        p[i] = str[i];
    }
    while(i <= n)
    {
        p[i++] = '\0';
    }
    return p;
}


