#include <iostream>
#include <thread>
#include <mutex>
#include <string>


// The class lock_guard is a mutex wrapper that provides a convenient RAII-style mechanism for owning a mutex for 
// the duration of a scoped block.
// When a lock_guard object is created, it attempts to take ownership of the mutex it is given
// When control leaves the scope in which the lock_guard object was created, the lock_guard is destructed and 
// the mutex is released.

// RAII: Resource acquisition is initialization

int g_i = 0;
std::mutex g_i_mutex;

void safe_increment()
{
    const std::lock_guard<std::mutex> lock(g_i_mutex);
    ++g_i;

    std::cout << "g_i: " << g_i << "; in thread #"
              << std::this_thread::get_id() << std::endl;
}//  g_i_mutex is automatically released when lock goes out of scope


int main(int argc, char **argv)
{
    std::cout << "g_i: " << g_i << "; in main()\n";
    std::thread thread1(safe_increment);
    std::thread thread2(safe_increment);
    thread1.join();
    thread2.join();
    return 0;
}