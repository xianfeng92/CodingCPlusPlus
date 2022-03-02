// protos.cpp

#include <iostream>

void cheer(int);
double cube(double x);

int main()
{
    using namespace std;
    cheer(5);
    cout << "Give me a number: ";
    double side;
    cin >> side;
    double volume = cube(side);
    cout << "A" << side << "-foot cube has a volume of " << volume << " cube feet.\n";
    cheer(cube(2));
    return 0
}

void cheer(int x)
{
    using namespace std;
    for (int i = 0, i < x; i++)
    {
        cout << " Cheers";
    }
    cout << endl;
}

double cube(double x)
{
    return x * x * x;
}





