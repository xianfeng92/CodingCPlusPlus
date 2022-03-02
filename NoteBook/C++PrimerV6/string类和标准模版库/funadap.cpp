#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<functional>


void show(double);
const int LIM = 6;

int main()
{
    using namespace std;
    double arr1[LIM] = {1,2,3,4,5,6};
    double arr2[LIM] = {6,7,8,9,10,11};

    vector<double> gr8(arr1, arr1 + LIM);
    vector<double> m8(arr2, arr2 + LIM);

    cout.setf(ios_base::fixed);
    cout.precision(1);
    cout << "gr8:\t";
    for_each(gr8.begin(), gr8.end(),show);
    cout << endl;

    cout << "m8:\t";
    for_each(m8.begin(), m8.end(),show);
    cout << endl;

    vector<double> sum(LIM);
    transform(gr8.begin(), gr8.end(),m8.begin(),sum.begin(),plsu<double>());
    cout << "sum:\t";
    for_each(sum.begin(), sum.end(),show);
    cout << endl;

    vector<double> prod(LIM);
    transform(gr8.begin(), gr8.end(),prod.begin(),bind1st(multiplies(),2.5));

    cout << "prod:\t";
    for_each(prod.begin(), prod.end(),show);
    cout << endl;

    return 0;
}

void show(int v)
{
    std::cout.width(6);
    std::cout << v << ' ';
}