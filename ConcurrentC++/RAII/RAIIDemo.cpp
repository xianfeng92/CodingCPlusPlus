#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<string>


// RAII: Resource acquisition is initialization
// RAII 的做法是使用一个对象，在其构造时获取资源，在对象生命期控制对资源的访问使之始终保持有效，最后在对象析构的时候释放资源
// RAII 在 C++ 中应用很广泛，用于管理资源、避免内存泄露。
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

    std::cout << "Worker thread is processing data" << std::endl;
    data += "after process";
    processed = true;
    std::cout << "Worker thread signals data processing completed" << std::endl;
    lk.unlock();
    cv.notify_one();
}

int main(int argc, char **argv)
{
    data = "Example Data";
    std::thread worker(worker_thread);

    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk,[]{return processed;});
    }
    
    std::cout << "Back in main(), data = " << data << '\n';
    worker.join();
    return 0;
}