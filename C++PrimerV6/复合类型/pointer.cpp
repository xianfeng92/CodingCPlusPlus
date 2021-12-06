//  pointer.cpp

#include<iostream>

int main()
{
    using namespace std;
    int updates = 6;// declare a variable
    int * p_updates;// declare a pointer to an int
    p_updates = &updates;// assign address of int to pointer

    cout << "Address: &update is : " << &updates;
    cout << ", p_updates is : " << p_updates << endl;


    *p_updates = *p_updates + 1;

    cout << "Now update is : " << updates << endl;
    return 0;
}