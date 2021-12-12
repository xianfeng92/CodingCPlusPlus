// cubes.cpp

#include <iostream>

double cube(double a);
double refCube(double &ra);

int main()
{
    using namespace std;
    double x = 3.0;
    cout << cube(x);
    cout << " = cube of " << x << "\n";
    cout << refCube(x);
    cout << "= refCube of " << x << "\n";
    return 0;
}

double cube(double a)
{
    a *= a * a;
    return a;
}

double refCube(double &ra)
{
    ra *=  ra * ra;
    return ra;
}