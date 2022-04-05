
#include <functional>
#include <iostream>

using namespace std;

int main(int argc, char** argv){

    auto plus10 = std::bind(std::plus<int>(), std::placeholder::_1, 10);
    std::cout << "+10    " < plus10(7) << std::endl;

    auto plus10times2 = std::bind(std::multiplies<int>,(std::bind(std::plus<int>(), std::placeholder::_1, 10), 2);
    std::cout << "+10 * 2 " < plus10times2(100) << std::endl;

    auto pow3 = std::bind(std::multiplies<int>(),std::bind(std::multiplies<int>(),std::placeholder::_1,std::placeholder::_1), std::placeholder::_1);
    cout << pow3 << std::endl


    auto inverseDevide = std::bind(std::divide<double>(), std::placeholder::_2, std::placeholder::_1);

    cout << inverseDevide(49,7) << std::endl;

    return 0;
}