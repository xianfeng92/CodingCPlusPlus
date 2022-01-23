#include <iostream>
#include<valarray>
#include<cstdlib>


const int SIZE = 12;
typedef std::valarray<int> vint;
void show(const vint & v, int cols);

int main()
{
    using std::slice;
    using std::cout;
    vint valint(SIZE);

    int i;
    for(i = 0; i < SIZE; i++)
    {
        valint[i] = std::rand() % 10;
    }
    show(valint,3);
    vint vcol(valint[slice(1,4,3)]);
    cout << "Second columu:\n";
    show(vcol,3);
    valint[slice(2,4,3)] = 10;
    cout << "set last column to 10:\n";
    show(valint,3);
    return 0;
}

void show(const vint & v, int cols)
{
    using std::cout;
    using std::endl;

    int lim = v.size();
    for(int i = 0; i < lim; i++)
    {
        cout.width(3);
        cout << v[i] << " ";
        if(i % cols == cols - 1)
        {
            cout << endl;
        }
        else
        {
            cout << ' ';
        }

    }
    if(lim % cols != 0)
    {
        cout << endl;
    }
}