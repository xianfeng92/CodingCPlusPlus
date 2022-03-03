#include "ThreadPool.h"
#include <iostream>
#include <unistd.h>

using namespace std;

void func1(int i)
{
    for(int j = 0; j < i; j++)
    {
      cout << "call func " << j << endl;
    }
}

int main()
{
    ThreadPool* asrExecutor = new ThreadPool(1);
    asrExecutor->init();
    auto res = asrExecutor->submit(func1,1);
    while(1)
    {
        usleep(1000000);
        asrExecutor->submit(func1,2);
    }
    return 0;
}