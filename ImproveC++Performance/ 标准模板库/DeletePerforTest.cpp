#include "DeleteTool.h"
#include <ctime>
#include <iostream>

using std::vector;
using std::list;

int main()
{
    vector<int> *vec = new vector<int>(10000,10);
    list<int> *l = new list<int>(10000,10);

    clock_t start = clock();
    vectorDelete<int>(vec);
    clock_t end = clock();
    cout << "vector delete cost time is " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    clock_t start1 = clock();
    listDelete<int>(l);
    clock_t end1 = clock();
    cout << "vector delete cost time is " << (double)(end1 - start1) / CLOCKS_PER_SEC << " seconds" << endl;

    cout << "Test delete front element" << endl;
    vector<int> *vec1 = new vector<int>(10000,10);
    list<int> *l1 = new list<int>(10000,10);


    clock_t start2 = clock();
    vectorDeleteFront<int>(vec1);
    clock_t end2 = clock();
    cout << "vector delete front cost time is " << (double)(end2 - start2) / CLOCKS_PER_SEC << " seconds" << endl;

    clock_t start3 = clock();
    listDeleteFront<int>(l);
    clock_t end3 = clock();
    cout << "vector delete front cost time is " << (double)(end3 - start3) / CLOCKS_PER_SEC << " seconds" << endl;


    return 0;
}