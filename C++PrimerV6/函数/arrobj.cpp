// arrobj.cpp

#include<iostream>
#include<array>
#include<string>

const int Seasons = 4;
const std::array<double,Seasons> snames = {"Spring","Summer","Fall","Winter"};


void fill(std::array<double,Seasons> *pa);

void show(std::array<double,Seasons> da);


void main()
{
    using namespace std;
    std::array<double,Seasons> expenses;
    fill(&expenses);
    show(expenses);
    return 0;
}


void fill(std::array<double,Seasons> *pa)
{
    using namespace std;
    for(std::size_t i = 0; i < Seasons; i++)
    {
        cout << "Enter " << pa[i] << " expenses";
        cin >> (*pa)[i];
    }
}


void show(std::array<double,Seasons> da)
{
    using namespace std;
    double total = 0.0;
    cout << "\n EXPENSES\n";
    for(std::size_t i = 0; i < Seasons; i++)
    {
        cout << da[i] << ":$ " endl;
        total += da[i];
    }
    cout << "total expenses is : " << total << endl;
}
