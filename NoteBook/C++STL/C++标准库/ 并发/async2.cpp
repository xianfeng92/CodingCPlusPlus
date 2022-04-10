#include <future>
#include <list>
#include <iostream>
#include <exception>

using namespace std;

void task1(){

    list<int> v;
    while(1){
        for(int i=0; i< 1000000; ++i){
            v.push_back(i);
        }
        cout.put('.').flush();
    }
}

int main(int argc, char** argv){

    cout << "Starting 2 task" << endl;
    cout << "-task1: process endless loop of memory consumption" << endl;
    cout << "-task2: wait for  return and the for task1" << endl;

    auto f1 =  std::async(task1);

    cin.get();

    cout << "wait for the end of task1" << endl;
    try{
        f1.get();

    }catch(const std::exception& e){
        cout << "Exception: " << e.what() << endl;
    }

    
}