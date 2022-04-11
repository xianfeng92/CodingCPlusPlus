#include <future>
#include <thread>
#include <iostream>
#include <stdexcept>

using namespace std;

int querrNumber(){
    cout << "Read number: ";
    int num;
    cin >> num;

    if(!cin){
        throw std::runtime_error("no number read");
    }
    return num;
}

void doSomething(char c, shared_future<int> f){

    try{
        f.get();// get result of queryNumber

        for(int i = 0; i < num; i++){
            this_thread::sleep_for(std::chrono::milliseconds(100));
            cout.put(c).flush();
        }
    }catch(const std::exception& e){
        cout << e.what() << endl;
    }
}

int main(int argc, char** argv){

    try{
        shared_future<int> f = std::async(queryNumber);

        auto f1 = std::async(std::launch::async, doSomething, '.', f);
        auto f2 = std::async(std::launch::async, doSomething, '+', f);
        auto f3 = std::async(std::launch::async,doSomething, '-', f);

        f1.get();
        f2.get();
        f3.get();
    }catch(const std::exception& e){
        cout << e.what() << endl;
    }

    cout << "done" << endl;
    return 0;
}



