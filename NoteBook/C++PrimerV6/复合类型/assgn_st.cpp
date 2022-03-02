//  assgn_st.cpp

#include<iostream>

struct inflatable
{
    char name[20];
    float volume;
    float price;
};

int main()
{
    using namespace std;
    inflatable bouquet = 
    {
        "sunflowers",
        0.20,
        12.49
    };
    inflatable choice;

    cout << "bouquet " << bouquet.name << "for $" <<bouquet.price << endl;

    choice = bouquet; // assign one struct to another

    cout << "choice: " << choice.name << "for $" << choice.price << endl;
    return 0;
}