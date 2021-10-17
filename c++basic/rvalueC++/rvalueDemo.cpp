#include <iostream>
#include "NioThreadPool.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <termios.h>
#include <time.h>
#include <sys/ioctl.h>
#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctime>
#include <signal.h>
#include <fcntl.h>
#include <memory>

using namespace std;

static void func1(int value)
{
    cout << "func right " << value << endl;
}


template <typename T>
void funccccc(T&& value)
{
    cout << "funcccccc value is " << value <<endl;
}

template <typename F>
void funkkkkkk(F && value)
{
    cout << "funkkkk value is " << value <<endl;
}



void func11 (std::string & value)
{
    
    cout << "func lvalue " << value << endl;
}
int main(int argc, char **argv)
{
    // NioThreadPool pool(1);
    // std::vector<std::future<int>> results;

    // int avargc = 10086;

    // for (int i = 0; i < 4; ++i)
    // {
    //         pool.enqueue(funccccc,i);
    // }
    int a = 111;
    std::string str("hello world");
    funccccc(a);
    funkkkkkk(str);
    return 0;
}