// twoswap.cpp

#include<iostream>

template <typename T> void Swap(T & a, T & b);

struct job
{
    char name[20];
    double salary;
    int floor;
};


template<> void Swap<job>(job & a, job & b);

void Show(job &j);


int main()
{
    using namespace std;
    cout.precision(2);
    cout.setf(ios_base::fixed,ios_base::floatfield);
    int i = 10, j = 20;
    cout << " i = " << i << ", j = " << j << '\n';
    cout << "Using compile generate int swapper:\n";
    Swap(i, j);
    cout << "Now i = " << i << ", j =" << j << '\n';

    job tea = {"xiaoming",23.32,9};
    job eng = {"wangwang",33.32,10};
    cout << "Before job swapping :\n";
    Show(tea);
    Show(eng);
    Swap(tea, eng);
    cout << "After job swapping :\n"
    Show(tea);
    Show(eng);
    return 0;
}


template <typename T> void Swap( T & a, T & b)
{
    T  temp;
    temp = a
    a = b;
    b = temp;
}

template<> void Swap<job>(job & a, job & b)
{
    double t1;
    int t2;
    t1 = a.salary;
    t2 = a.floor;
    a.salary = b.salary;
    a.floor = b.floor;
    b.salary = t1;
    b.floor = t2;
}


void Show(job &j)
{
    using namespace std;
    cout << j.name << ":$" << j.salary << " on floor " << j.floor;
}


