// sceref.cpp

#include<iostream>

int main()
{
    using namespace std;
    int rats = 101;
    int &rodents = rats;

    cout << "rats is " << rats << "\n";
    cout << "rodents = " << rodents << "\n";
    cout << "rats address is " << &rats << "\n";
    cout << "rodents address is " << &rodents << "\n";


    int bunnies = 50;
    rodents = bunnies;

    cout << "bunnies is " << bunnies << "\n";
    cout <<"rats = " << rats << "\n";
    cout << "rodents = " << rodents << "\n";

    cout << "rodent address is " << &rodents << "\n";
    cout << "bunnies address is " << &bunnies << "\n";

    return 0;
}