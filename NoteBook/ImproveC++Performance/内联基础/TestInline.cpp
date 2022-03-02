#include<iostream>

using std::endl;
using std::cout;

inline int calc(int x, int y)
{
    return x + y;
}

int main()
{
    int x[1000];
    int y[1000];
    int z[1000];

    cout << "process start" << endl;
    for(int i=0; i<1000; i++)
    {
        for(int j=0; j<1000; j++)
        {
            for(int k=0; k<1000; k++)
            {
                z[i] = calc(x[j], y[k]);
            }
        }
    }
    cout << "process end" << endl;
}