#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <random>
#include <thread>

using namespace std;

int doSomething(char c) {
  std::default_random_engine dre(c);
  std::uniform_int_distribution<int> id(10, 1000);

  for (int i = 0; i < 10; i++) {
        this_thread::sleep_for(std::chrono::microseconds(id(dre)));
        cout.put(c).flush();
  }
  return c;
}

int func1() { return doSomething('.'); }

int func2() { return doSomething('+'); }

int main(int argc, char** argv) {
  std::cout << "starting func1() at background and func2() in foreground: "
            << std::endl;

  // start func1() async(now or later)
  std::future<int> result1(std::async(func1));

  int result2 = func2();  // call func2() sync(here and now)

  // print result(wait func1 to finish) add add it result to result2
  int result = result1.get() + result2;

  std::cout << "result1 + result2 is " << result << std::endl;

  return 0;
}