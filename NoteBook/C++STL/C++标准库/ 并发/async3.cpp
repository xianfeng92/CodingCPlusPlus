#include <future>
#include <thread>
#include <chrono>
#include <iostream>
#include <random>
#include <exception>

using namespace std;


void doSomething(char c){
    default_random_engine dre(c);
    uniform_int_distribution<int> id(10, 1000);
    for(int i=0; i < 1000; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
        cou.put(c).flush();
    }
}

int main(int argc, char** argv){

    cout << "Starting 2 operation async " << endl;
    auto f1 = std::async([](){doSomething('.');});
    auto f2 = std::async([](){doSomething('+')});
    // if at least one of background task is running
    if(f1.wait_for(std::chrono::seconds(0) != std::future_status::deferred || 
       f2.wait_for(std::chrono::seconds(0) != std::future_status::deferred))){

           while(f1.wait_for(std::chrono::seconds(0) != std::future_status::ready && 
                 f2.wait_for(std::chrono::seconds(0) != std::future_status::ready))){
                     ...
                     this_thread.yield();
                 }
       }
       cout.put('\n').flush();

       try {
           f1.get();
           f2.get();
       }catch(const std::exception& e){
           cout << e.what() << endl;
       }

       cout << "done" << endl;

    return 0;
}