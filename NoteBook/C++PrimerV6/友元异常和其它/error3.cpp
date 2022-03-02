#include <iostream>
#include <cstdlib>

double hmean(double a, double b);

int main()
{
    double x, y,z;
    std::cout << "Enter two number:\n";
    while(std::cin >> x >> y)
    {
        try
        {// start of try block
            z = hmean(x, y);
        }// end of try block
        catch(const char *s)// start of exception handler
        {
            std::cout << s << std::endl;
            std::cout << "Enter a new pair of numbers:\n";
            continue;
        }
    }
    std::cout << "Bye~";
    return 0;
}


double hmean(double a, double b)
{
    if(a == -b)
    {
        throw "bad hmean() argument: a = -b not allowed"
    }
    return 2.0 * a * b/(a+b);
}


