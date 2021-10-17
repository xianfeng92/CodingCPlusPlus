#include <thread>
#include <mutex>
#include<condition_variable>
#include <iostream>
#include <chrono>

using namespace std;

// std::condition_variable::notify_one
// If any threads are waiting on *this, calling notify_one unblocks one of the waiting threads.
std::condition_variable cv;
std::mutex cv_mutex;
int i = 0;
bool done = false;


void waits()
{
    std::unique_lock<std::mutex> lk(cv_mutex);
    std::cout << "Waiting... \n";
    std::this_thread::sleep_for(std::chrono::seconds(4));
    cv.wait(lk,[]{return i == 1;});
    std::cout << "...finished waiting; i == " << i << '\n';
    done = true;
}

void signals()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Notifying falsely...\n";
    // waiting thread is notified with i == 0.
    // cv.wait wakes up, checks i, and goes back to waiting
    cv.notify_one();
    std::unique_lock<std::mutex> lk(cv_mutex);
    i = 1;
    while (!done)
    {
        lk.unlock();
        // waiting thread is notified with i == 1, cv.wait returns
        // notify 并不释放锁，只是告诉调用过 wait 方法的线程可以去参与获得锁的竞争了，但不是马上得到锁，因为锁还在别人手里，别人还没释放
        // 在解锁后放置 notify_one
        // notifying thread: notify
        // notified thread: awaken -> attempt to acquire lock and succeed
        cv.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        lk.lock();
    }
}


int main(int argc, char **argv)
{
    std::thread t1(waits);
    std::thread t2(signals);
    t1.join();
    t2.join();
}