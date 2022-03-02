#include "InserTool.h"
#include<algorithm>
#include<ctime>
#include<iostream>


int *generateData(int size)
{
    int *data = new int[size];
    generate(&data[0], &data[size], rand);
    return data;
}

int main()
{
    int arr[1000000];
    vector<int> *vec = new vector<int>;
    vec->resize(1000000);
    list<int> *l = new list<int>;
    multiset<int> *mult = new multiset<int>;

    clock_t start = clock();
    arrayInsert<int>(arr, generateData(1000000),1000000);
    clock_t end = clock();
    cout << "arrayInsert cost " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    clock_t start1 = clock();
    vectorInsert<int>(vec, generateData(1000000),1000000);
    clock_t end1 = clock();
    cout << "vectorInsert cost " << (double)(end1 - start1) / CLOCKS_PER_SEC << " seconds" << endl;

    clock_t start2 = clock();
    listInsert<int>(l, generateData(1000000),1000000);
    clock_t end2 = clock();
    cout << "listInsert cost " << (double)(end2 - start2) / CLOCKS_PER_SEC << " seconds" << endl;

    clock_t start3 = clock();
    multisetInsert<int>(mult, generateData(1000000),1000000);
    clock_t end3 = clock();
    cout << "multisetInsert cost " << (double)(end3 - start3) / CLOCKS_PER_SEC << " seconds" << endl;

    cout << "Test insert Front consting" << endl;

    clock_t start4 = clock();
    vectorInsertFront<int>(vec, generateData(10000),10000);
    clock_t end4 = clock();
    cout << "arrayInsert cost " << (double)(end4 - start4) / CLOCKS_PER_SEC << " seconds" << endl;

    clock_t start5 = clock();
    listInsertFront<int>(l, generateData(10000),10000);
    clock_t end5 = clock();
    cout << "listInsert cost " << (double)(end5 - start5) / CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}
