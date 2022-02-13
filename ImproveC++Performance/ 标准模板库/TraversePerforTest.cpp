#include "TraverseTool.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{

    vector<int> *vec = new vector<int>(1000000,10);
    list<int> *l = new list<int>(1000000,10);

    clock_t start = clock();
    vectorTraversal<int>(vec,1000000);
    clock_t end = clock();
    cout << "Traverse vector cost time is " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    clock_t start1 = clock();
    listTraverse<int>(l,1000000);
    clock_t end1 = clock();
    cout << "Traverse list cost time is " << (double)(end1 - start1) / CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}