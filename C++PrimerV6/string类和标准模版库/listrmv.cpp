#include<iostream>
#include<list>
#include<algorithm>

void show(int);

const int LIM = 10;

int main()
{
    using namespace std;
    int ar[LIM] = {1,2,3,4,5,6,7,8,9,10};
    list<int> la(ar, ar + LIM);
    list<int> lb(la);

    cout << "Original list content:\n\t";
    for_each(la.begin(), la.end(),show);
    cout << endl;
    la.remove(4);
    cout << "After using remove method:\n\t";
    for_each(la.begin(), la.end(),show);
    cout << endl;
    list<int>::iterator last;
    last = remove(lb.begin(), lb.end(),4);
    cout << "After using remove function:\n";
    cout << "lb:\t";
    for_each(lb.begin(), lb.end(),show);
    cout << endl;
    la.erase(last, lb.end());
    cout << "After using erase method\n";
    cout << "la\t";
    for_each(la.begin(), la.end(),show);
    cout << endl;
    return 0;
}

void show(int v)
{
    std::cout << v << ' ';
}