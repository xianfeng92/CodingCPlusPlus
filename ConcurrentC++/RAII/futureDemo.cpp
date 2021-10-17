#include<thread>
#include<iostream>
#include<future>


using namespace std;

int main(int argc, char **argv)
{

    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::thread t([&p]
    {
        try
        {
             // code that may throw
            throw std::runtime_error("Example");
        }
        catch(...)
        {
            // store anything thrown in the promise
            p.set_exception(std::current_exception());
        }
    });
    try
    {
        std::cout << f.get() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception from the thread: " << e.what() << '\n';
    }
    t.join();
    return 0;
}