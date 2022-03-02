#include "printtuple.h"

#include <tuple>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    tuple<int, float, string> t(77, 12.21, "hello world");
    cout << "io: " << t << endl;
}

