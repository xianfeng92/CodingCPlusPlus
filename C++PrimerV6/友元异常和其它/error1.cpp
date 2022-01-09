#include <iostream>
#include <cstdlib>

double hmean(double a, double b);

int main()
{
    double x, y,z;
    std::cout << "Enter two number:\n";
    while(std::cin >> x >> y)
    {
        z = hmean(x, y);
        std::cout << "Harmonic mead of " << x << " and " << y << " is " << z << std::endl;
        std::cout << "Enter next set number(q to quit):" << std::endl;
    }
    std::cout << "Bye~";
    return 0;
}


double hmean(double a, double b)
{
    if(a == -b)
    {
        std::cout << "untenable argument to hmean\n";
        std::abort();
    }
    return 2.0 * a * b/(a+b);
}