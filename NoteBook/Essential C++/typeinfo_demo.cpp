#include "num_sequence.h"
#include "Fibonacci.h"
#include <iostream>

int main(int argc, char **argv){
    num_sequence *ps = new num_sequence();
    std::cout << ps->who_i_am() << std::endl;

    num_sequence *ps2 = new Fibonacci();

    std::cout << ps2->who_i_am() << std::endl;
    return 0;
}