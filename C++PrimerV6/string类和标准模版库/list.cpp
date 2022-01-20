#include<iostream>
#include<list>
#include<string>
#include<algorithm>

void out_int(int n){std::cout << n << std::endl;}

int main()
{
    using namespace std;
    list<int> one(5,2);
    int stuff[5] = {1,2,3,4,5};
    list<int> two;
    two.insert(t.begin(),stuff,stuff+5);
    int more[6] = {6,7,8,9,10,11};
    list<int> three(two);

    three.insert(three.end(),more,more+ 6);
    cout << "List one\n";
    for_each(one.begin(),one.end(),out_int);

    cout << "List two\n";
    for_each(two.begin(),two.end(),out_int);

    cout << "List three\n"
    for_each(three.begin(), three.end(),out_int);

    three.remove(2);

    cout << "List three three.remove(2)\n";
    for_each(three.begin(),three.end(),out_int);
    three.unique();
    cout << "List three after unique\n";
    for_each(three.begin(), three.end(),out_int);

    three.sort();

    for_each(three.begin(), three.end(),out_int);

    return 0;
}