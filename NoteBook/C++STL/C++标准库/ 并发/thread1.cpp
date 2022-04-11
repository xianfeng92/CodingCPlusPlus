#include <chrono>
#include <iostream>
#include <random>
#include <stdexcept>
#include <thread>

using namespace std;

void doSomething(int num, char c) {
  try {
    default_random_engine dre(c);
    uniform_int_distribution<int> id(10, 1000);
    for (int i = 0; i < num; i++) {
      std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
      cout.put(c).flush();
    }
  }catch (std::exception& e) {
      cout << e.what() << endl;
  }
}

int main(int argc, char** argv) {
    try{
        std::thread t1(doSomething);
        cout << "Staring fg thread" << t1.get_id() << endl;

        for(int i = 0; i < 5 ; i++) {
            thread t(doSomething, 10, i + 'a');
            cout << "detach started fg thread" << t.get_id() << endl;
            t.detach();// detach the thread into background
        }

        cin.get();// wait for any input
        cout << "-join fg thread " << t1.get_id() << endl;
        t1.join();
    }catch(const std::exception& e){
        cout << e.what() << endl;
    }

    return 0;
}