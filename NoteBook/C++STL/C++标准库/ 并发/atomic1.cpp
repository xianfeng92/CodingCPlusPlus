#include <atomic>// for atomic types

std::atomic<bool> readyFlag(false);

void thread1(){
    // do something thread2 need as preperation
    ...
    readyFlag.store(true);
}

void thread2(){
    while(!readyFlag.load()){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ...
}

