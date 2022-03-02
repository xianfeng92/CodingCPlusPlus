// structur.cpp

#include<iostream>

struct inflatable// struct declaration
{
    char name[20];
    float volume;
    double price;
};


int main()
{
    using namespace std;
    inflatable guest = 
    {
        "Gloris",
        1.88,
        2.99
    };

    inflatable pal = 
    {
        "Kooo",
        23.11,
        212.32
    };

    cout << "Expand you guest list with  " << guest.name;
    cout << " and " << pal.name << "!\n";
    cout << "You can have both of $ ";
    cout << guest.price + pal.price << "!\n";
    return 0;
}