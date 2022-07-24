#include "string.h"
#include "string"
#include "iostream"

extern "C" int main(int argc, char *argv[]) {
    std::cout << "abcd" << std::endl;
    std::cout << 233 << std::endl;
    std::string msg("msg");
    std::cout << msg << std::endl;
    std::cout << msg.c_str() << std::endl;

    return 0;
}
