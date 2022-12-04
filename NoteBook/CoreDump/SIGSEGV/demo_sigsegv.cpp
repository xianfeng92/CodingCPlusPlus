#include <iostream>
#include <stdlib.h>
#include <string>

// ulimit -c unlimited
// g++ -std=c++11 -g demo_sigsegv.cpp -o prog\

int main(int argc, char **argv) {
    char *pc = nullptr;
    std::cout << "access 0 address" << *pc << std::endl;
    return 0;
}

// (gdb) bt full
// #0  0x0000563923531204 in main (argc=1, argv=0x7ffeff334f08) at demo_sigsegv.cpp:8
//         pc = 0x0