#include <iostream>
#include <cmath>
#include "exc_mean.h"

double hmean(double a, double b);
double gmean(double a, double b);

int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    double x, y;
    double z;
    
    cout << "Enter two numbers: \n";
    while (cin >> x >> y)
    {
        try
        {
            z = hmean(x, y);
        }
        catch(bad_hmean &bg)
        {
            bg.mesg();
            cout << "Try Again: \n";
            continue;
        }
        catch(bad_gmean &bg)
        {
            bg.mesg();
            cout << "Sorry you donnot get to play more\n";
            break;
        }
    }
    cout << "Bye!\n";
    return 0;
}


double hmean(double a, double b)
{
    if(a == -b)
    {
        throw bad_hmean(a,b);
    }
    return 2.0 * a * b/(a+b);
}

double gmean(double a, double b)
{
    if(a < 0 || b < 0)
    {
        throw bad_gmean(a,b);
    }
    return std::sqrt(a*b);
}



