#include <initializer_list>

double sum(std::initializer_list<double> d1);

int main()
{
    using namespace std;
    double total = sum(1,2,3);
    cout << total << endl;
    return 0;
}

double sum(std::initializer_list<double> d1)
{
    double tot = 0;
    for(auto p = d1.begin(); p != d1.end();p++)
    {
        tot += *p;
    }
    return tot;
}