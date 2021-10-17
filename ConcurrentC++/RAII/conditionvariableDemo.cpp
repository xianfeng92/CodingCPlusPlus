#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<chrono>

using namespace std;

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

void worker_thread()
{
    std::unique_lock<std::mutex> lk(m);

    cv.wait(lk,[]{return ready;});

    std::cout << "Worker thread is processing data...." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(3));
    data += "after process";
    processed = true;
    std::cout << "Worker thread signals data processing completed" << std::endl;
    // 通知前，手动解锁以防正在等待的线程被唤醒后又立即被阻塞
    lk.unlock();
    cv.notify_one();
}

int main(int argc, char **argv)
{
    data = "Example Data";

    std::thread worker(worker_thread);

    {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "Main thread processing data..." << std::endl;
        // 睡眠一秒以模拟数据准备
        std::this_thread::sleep_for(std::chrono::seconds(3));
        ready = true;
        std::cout << "Main thread notify data is processing completed !! " << std::endl;
    }

    cv.notify_one();

    // 等待工作线程处理数据
    // 与条件变量搭配使用的「锁」，必须是 unique_lock，不能用 lock_guard
    {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, []
                { return processed; });
    }

    std::cout << "Back in main(), data = " << data << '\n';
    worker.join();
    return 0;
}