// twotemps.cpp

#include <iostream>

template <typename T> void Swap(T & a, T & b);// original template

template <typename T> void Swap(T *a, T *b, int n);// new template

void show(int *a);

const int LIM = 8;

int main()
{
    using namespace std;
    int i = 10,j = 20;
    cout << "Using compile generate int swapper:\n";
    Swap(i, j);// matchs original template
    cout << "Now i = " << i << ", j = " << j << '\n';
    int d1[LIM] = {0,1,2,3,4,5,6,7};
    int d2[LIM] = {10,11,12,13,14,15,16,17};
    show(d1);
    show(d2);
    Swap(d1,d2,LIM);
    cout << "Swap arrays\n";
    show(d1);
    show(d2);
    return 0;
}

template <typename T> void Swap(T & a, T & b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

template <typename T> void Swap(T *a, T *b, int n)
{
    T temp;
    for(int i = 0; i < n; i++)
    {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

void show(int *a)
{
    using namespace std;
    cout << a[0] << a[1] << "/";
    cout << a[2] << a[3] << "/";
    for(int i = 4; i < LIM; i++)
    {
        cout << a[i];
    }
    cout << endl;
}