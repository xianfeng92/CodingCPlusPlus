#include <iostream>
#include <cmath>
#include <string>
#include "exc_mean.h"

class demo
{
    private:
        std::string word;

    public:
        demo(const std::string &str)
        {
            word = str;
            std::cout << "demo " << word <<" created\n";
        }

        ~demo()
        {
            std::cout << "demo " << word << " deleted\n";
        }

        void show() const
        {
            std::cout << "demo " << word << " lives!\n";
        }
};

// function prototypes
double hmean(double a, double b);
double gmean(double a, double b);
double means(double a, double b);

int main()
{
    using std::cout;
    using std::endl;
    using std::cin;

    double x, y;
    double z;
    {
        demo d1("found in block in main()");
        cout << "Enter two numbers:\n";
        while (cin >> x >> y)
        {
            try
            {
                z = means(x, y);
                cout << "The means of " << x << " and " << y << "is " << z << endl;
                cout << "Enter next pair:\n";
            }
            catch(bad_hmean &bg)
            {
                bg.mesg();
                cout << "Try Again:\n";
                continue;
            }
            catch(bad_gmean &bg)
            {
                bg.mesg();
                cout << "The values Used " << bg.v1 << " and " << bg.v2 << endl;
                cout << "SOrry , you don't get to play more\n";
                break;
            }    
        }
        d1.show();
    }
    cout << "Bye!\n";
    cin.get();
    cin.get();
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

double means(double a, double b)
{
    double am,hm,gm;
    demo d2("found in means");
    am = (a + b)/2.0;
    try
    {
        hm = hmean(a, b);
        gm = gmean(a, b);
    }
    catch(bad_hmean &bg)
    {
        bg.mesg();
        std::cout << "Caught in means() ";
        throw;// rethrow the exception
    }
    d2.show();
    return (am + hm + gm)/ 3.0;
}

