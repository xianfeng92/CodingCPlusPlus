// addpntrs.cpp

#include<iostream>

int main()
{
    using namespace std;
    double wages[3] = {10000.0,20000.0,300000.0};
    short stacks[3] = {3,1,2};

    double *pd = wages;
    short *ps = &stacks[0];

    cout << "pd - " << pd << " *pd " << *pd << endl;
    pd = pd + 1;
    cout << "pd - " << pd << " *pd " << *pd << endl;
    cout << "ps - " << ps << " *ps " << *ps << endl;
    ps = ps + 1;
    cout << "ps - " << ps << " *ps " << *ps << endl;
    cout << "stacks[0] - " << stacks[0] << " stacks[1] " << stacks[1] << endl;
    cout << "*stacks = " << *stacks << " *(stacks+1)" << *(stacks + 1) << endl;
    cout << sizeof(wages) << "= size of wages array\n";
    cout << sizeof(stacks) << "= size of stacks array\n";
    return 0;
}
