// carrot.cpp --- food processing program

#include <iostream>
int main()
{
    using namespace std;
    
    int carrots; // declare an integer variable

    carrots = 25;
    cout << "I have ";
    cout << carrots;
    cout << " carrots.";
    cout << endl;
    carrots = carrots - 1;
    cout << "Crunch, crunch. Now I have " << carrots << " carrots." << endl;
    return 0;
}
