#include "InserTool.h"
#include<algorithm>


int *generateData(int size)
{
    int *data = new int[size];
    generate(&data[0], &data[size], rand;
    return data;
}

void main()
{
    int arr[1000000];
    vector<int> vec;
    list<int> l;
    multist<int> mult;

    arrayInsert<int>(arr, generateData(1000000),1000000);
    vectorInsert<int>(vec, generateData(1000000),1000000);
    listInsert<int>(l, generateData(1000000),1000000);
    multisetInsert<int>(mult, generateData(1000000),1000000);

    return 0;
}
