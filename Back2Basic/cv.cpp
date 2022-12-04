
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

std::mutex gLock;
std::condition_variable gConditionVariable;

int main () {
    std::cout << "main() starts" << std::endl;
    int result = 0;
    bool notified = false;

    std::thread reporter([&]{
        std::unique_lock<std::mutex> lock(gLock);
        if(!notified) {
            gConditionVariable.wait(gLock);
        }
        std::cout << "\t Repoter Result: " << result << std::endl;
    });

    std::thread worker([&]{
        std::unique_lock<std::mutex> lock(gLock);
        result = 42;
        notified = true;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "Work Complete: " << result << std::endl;
        gConditionVariable.notify_one();
    });

    reporter.join();
    worker.join();
    std::cout << "main end " << std::endl;
    return 0;
}