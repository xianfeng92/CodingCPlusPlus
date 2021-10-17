#include <iostream>
#include <thread>       

void greeting() {
    std::cout << "Hello multithread!" << std::endl;
    return;
}

int main() {
    std::thread t{greeting};
    t.join();
    return 0;
}