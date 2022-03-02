#include <cstring>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    string s1("123");
    cout << atoi(s1.c_str())<< endl;

    char buf[100];
    s1.copy(buf,100);

    cout << "s1 max_size is " << s1.max_size() << endl;
    cout << "s1 npos is " << (int)string::npos << endl;
    cout << "s1 capacity is " << s1.capacity() << endl;
}



