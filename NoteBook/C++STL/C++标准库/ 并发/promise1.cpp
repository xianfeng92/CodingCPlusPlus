#include <thread>
#include <future>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <functional>
#include <utility>

using namespace std;

void doSomething(std::promise<std::string> &p){
    try{
        std::cout << "read char ('x' for exception)" << std::endl;
        char c = std::cin.get();
        if(c == 'x'){
            std::string s =  std::runtime_error(std::string("char") + c + "process");
            p.set_value(std::move(s));
        }
    }
}


int main(int argc, char** argv){
    try{
        std::promise<std::string> p;
        std::thread t(doSomething, std::ref(p));
        t.detach();
        ...
        std::future<std::string> f(p.get_future());
        std::cout << "result: " << f.get() << std::endl;
    }catch(const std::exception& e){
        cout << e.what() << endl;
    }catch(...){
        std::cerr << "Exception"  << std::endl;
    }
    return 0;
}