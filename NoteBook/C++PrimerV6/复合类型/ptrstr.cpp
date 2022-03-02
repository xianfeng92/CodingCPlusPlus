// ptrstr.cpp

#include <iostream>
#include <cstring>

int main()
{
    using namespace std;
    char animal[20] = "bear";
    const char * bird = "wren";
    char * ps;

    cout << animal << " and " << bird << "\n";
    // cout << ps << "\n";// may display garbage or cause a crash
    cout << "Enter a kind of animal: ";
    cin >> animal;// ok, if input < 20 characters
    // cin >> ps;// Too horrible, ps doesn't' pointer to allocated space

    ps = animal;
    cout << ps << "\n";
    cout << "Before using strcpy(): " << "\n";
    cout << animal << " at " << (int*)animal << "\n";
    cout << ps << " at " << (int*)ps << "\n";
    ps = new char[strlen(animal) + 1];// get new storage
    strcpy(ps,animal);
    cout << " After Using strcpy():\n";
    cout << animal << " at " << (int*)animal << "\n";
    cout << ps << " at " << (int*)ps << "\n";
    delete[] ps;
    return 0;
}