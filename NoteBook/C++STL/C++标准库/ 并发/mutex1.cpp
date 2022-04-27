#include <future>
#include <mutex>
#include <iostream>
#include <string>


std::mutex print_mutex;

void print(const std::string& message){
    std::lock_guard<std::mutex> lg(print_mutex);
    for(char c: message){
        std::cout.put(c).flush();
    }
    std::cout << std::endl;
}


int main(int argc, char* argv[]){
    auto f1 = std::async(std::launch::async, print,"hello world");

    auto f2 = std::async(std::launch::async, print, "hello world");

    auto f3 = std::async(std::launch::async, print, "hello world");

    return 0;
}



