#include<iostream>
#include<initializer_list>

double sum(std::initializer_list<double> il);
double average(const std::initializer_list<double> &ril);


int main()
{
    using namespace std;

    cout << "List 1 sum: " << sum({1,2,3,4})
    << "ave :" << average({1,2,3,4,5}) << endl;
    std::initializer_list<double> d1 = {1.1, 1.2, 1.3, 1.4, 1.5};
    cout << "List 2 sum: " << sum(d1) << "ave :" << average(d1) << endl;
    d1 = {12.21,34.43,56.65,77.66,89.67};
    cout << "List 3 sum: " << sum(d1) << " ave" << average(d1) << endl;
    return 0;
}

double sum(std::initializer_list<double> il)
{
    double tot = 0;
    for(auto p = il.begin(); p != il.end(); ++p)
    {
        tot += *p;
    }
    return tot;
}

double average(std::initializer_list<double> &ril)
{
    double tot = 0;
    int n = ril.size();
    double ave = 0;
    if(n > 0)
    {
        for(auto p = ril.begin(); p != ril.end; p++)
        {
            total += *p;
        }
        ave = total / n;
    }
    return ave;
}