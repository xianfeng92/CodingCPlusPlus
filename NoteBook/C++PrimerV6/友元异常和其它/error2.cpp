#include <iostream>
#include <cfloat> // for DBL_MAX

bool hmean(double a, double b, double *ans);

int main()
{
    double x, y, z;
    std::cout << "Enter two number:\n";
    while (std::cin >> x >> y)
    {
        if (hmean(x, y, &z))
        {
            std::cout << "Harmonic mead of " << x << " and " << y << " is " << z << std::endl;
        }
        else
        {
            std::cout << "One value should not be negative of the other\n";
        }
        std::cout << "Enter next set number(q to quit):" << std::endl;
    }
    std::cout << "Bye~\n";
    return 0;
}

bool hmean(double a, double b, double *ans)
{
    if (a == -b)
    {
        *ans = DBL_MAX;
        return false;
    }
    *ans = 2.0 * a * b / (a + b);
    return true;
}
