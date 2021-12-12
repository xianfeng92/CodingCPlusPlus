#include <iostream>

class DisplayThread
{
public:
    void operator()()
    {
        for (int i = 0; i < 100; i++)
            std::cout << "Display Thread Excecuting" << std::endl;
    }
};