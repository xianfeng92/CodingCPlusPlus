
// @file async.cpp
// g++ -std=c++17 async.cpp -o prog -lpthread

#include <iostream>
#include <future>
#include <thread>
#include <chrono>

bool bufferedFileLoading() {
    size_t bytesLoaded = 0;
    while(bytesLoaded < 20000){
        std::cout << "Loading File ..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        bytesLoaded += 100;
    }
    return true;
}

int main() {
    std::future<bool> backgroundThread = std::async(std::launch::async, bufferedFileLoading);
    std::future_status status;
    while(true){
        std::cout << "main thread running" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        status = backgroundThread.wait_for(std::chrono::milliseconds(1));
        if(status == std::future_status::ready) {
            std::cout << "data ready" << std::endl;
            break;
        }
    }
    return 0;
}

