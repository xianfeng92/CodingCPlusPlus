#include <iostream>
#include <chrono>


using namespace std;

// C++ includes support for two types of time manipulation
// 1. The chrono library, a flexible collection of types that track time with varying degrees of precision
//     (e.g. std::chrono::time_point).
// 2. C-style date and time library (e.g. std::time)


// std::chrono library
// The chrono library defines three main types as well as utility functions and common typedefs
// clocks
// time points
// durations


long fibonacci(unsigned n)
{
    if (n < 2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}


int main(int argc, char **argv)
{
    auto start = std::chrono::system_clock::now();
    std::cout << "f(30) = " << fibonacci(30) << endl;
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
}