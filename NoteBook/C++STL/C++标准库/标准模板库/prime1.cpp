#include <list>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

bool isPrime(int number) {
    number = std::abs(number);
    if(number == 0 || number == 1) {
        return false;
    }
    int divisor;
    for(divisor = number/2; number % divisor != 0; --divisor) {
        ;
    }
    return divisor == 1;
}

int main(int argc, char** argv){
    list<int> coll;
    for(int i = 24; i < 40 ; ++i) {
        coll.push_back(i);
    }

    auto pos = std::find_if(coll.begin(), coll.end(),isPrime);

    if(pos != coll.end()) {
        cout << *pos << "is the first prime" << std::endl;
    }else{
        cout <<  "no primer found" << std::endl;
    }

    return 0;
}