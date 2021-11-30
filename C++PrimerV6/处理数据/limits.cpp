// limits.cpp --- some integer limits

#include<iostream>
#include<climits>


int main()
{
    using namespace std;
    int n_int = INT_MAX;
    short n_short = SHRT_MAX;
    long n_long = LONG_MAX;
    long long n_llong = LLONG_MAX;


    // sizeof operator yields size of type or of variable
    cout << "int is " << sizeof(n_int) << " bytes" << endl;
    cout << "short is " << sizeof(n_short) << " bytes" << endl;
    cout << "long is " << sizeof(n_long) << " bytes" << endl;
    cout << "long long is " << sizeof(n_llong) << " bytes" << endl;
    
    cout << "Maxmum Value :" << endl;
    cout << "int :" << n_int << endl;
    cout << "short: " << n_short << endl;
    cout << "long: " << n_long << endl;
    cout << "long long :" << n_llong << endl;

    cout << "Max int value is :" << INT_MAX << endl;
    cout << "Bits per Byte is :" << CHAR_BIT << endl;
    
    return 0;
}

