#include <condition_variable>
#include <mutex>
#include <future>
#include <iostream>

bool readyFlag = false;
std::mutex readyMutex;
std::condition_variable readyConVar;

void thread1(){
    std::cout << "<return>" << std::endl;
    std::cin.get();
    {
        std::lock_guard<std::mutex> lg(readyMutex);
        readyFlag = true;
    }
    readyConVar.notify_one();
}

void thread2(){
    {
        std::unique_lock<std::mutex> ul(readyMutex);
        readyConVar.wait(ul,[](){return readyFlag;});
    }
    std::cout << "done" << std::endl;
}

int  main(int argc, char** argv){
    auto f1 = std::async(std::launch::async, thread1);
    auto f2 = std::async(std::launch::async, thread2);

    return 0;
}