#include <iostream>

using namespace std;

int main(int argc, char **argv){

    auto plus10 = [](int i){ return i + 10; };
    cout << plus10(7) << endl;

    auto  plus10times2 = [](int i){ return (i + 10) * 2; };
    cout << plus10times2(7) << endl;

    auto pow3 = [](int i){ return i * i *i; };
    cout << pow3(7) << endl;

    auto inverseDevide = [](double d1, double d2){ return d1 / d2; };
    cout << inverseDevide(7,79) << endl;
    
    return 0;
}