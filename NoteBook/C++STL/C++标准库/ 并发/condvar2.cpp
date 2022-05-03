#include <condition_variable>
#include <mutex>
#include <future>
#include <thread>
#include <iostream>
#include <queue>

std::queue<int> queue;
std::mutex queue_mutex;
std::condition_variable queue_condition_variable;

void provider(int val) {
  for (int i = 0; i < 6; i++) {
    {
      std::lock_guard<std::mutex> lock(queue_mutex);
      queue.push_back(i + val);
    } // release lock
    queue_condition_variable.notify_one();
    std::this_thread::sleep_for(std::chrono::milliseconds(val));
  }
}


void consumer(int num){
    while(true){
        int val;
        {
            std::unique_lock<std::mutex> ul(queue_mutex);
            queue_condition_variable.wait(ul, [](){return !queue.isEmpty();})
            val = queue.front();
            queue.pop();
        }// release lock
        std::cout << "consumer " <<  num << val << std::endl;
    }
}


int main(int argc, char** argv){

    auto p1 = std::async(std::launch::async, provider, 100);
    auto p2 = std::async(std::launch::async, provider, 300);
    auto p3 = std::async(std::launch::async, provider, 400);

    auto c1 = std::async(std::launch::async, consumer, 1);
    auto c2 = std::async(std::launch::async, consumer, 2);
}