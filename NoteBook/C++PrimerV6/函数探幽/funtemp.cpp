
#include<iostream>

template<typename T> void Swap(T& a, T& b);

int main()
{
    using namespace std;
    int i = 20;
    int j = 30;
    cout << "i = " << i << ", j = " << j << '\n';
    cout << "Using compile generate int swapper:\n";
    Swap(i, j);
    cout << "Now i = " << i << ", j = " << j << '\n';
    double x = 12.21;
    double y = 99.89;
    cout << "x = " << x << ", y = " << y << '\n';
    cout << "Using compile generate double swapper:\n";
    Swap(x, y);
    cout << "Now x = " << x << ", y = " << y << '\n';
    return 0;
}

template<typename T> void Swap(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

