#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std;

// std::mutex::lock
// Locks the mutex. If another thread has already locked the mutex, a call to lock will block execution until the lock is acquired
// If lock is called by a thread that already owns the mutex, the behavior is undefined

int g_num = 0;
std::mutex g_mutex;

void slow_increment(int id)
{
    for (auto i = 0; i < 10; i++)
    {
        g_mutex.lock();
        ++ g_num;
        // note, that the mutex also syncronizes the output
        std::cout << "id: " << id << ", g_num: " << g_num << '\n';
        g_mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main(int argc, char **argv)
{
    std::thread t1{slow_increment, 0};
    std::thread t2{slow_increment, 1};
    t1.join();
    t2.join();
}