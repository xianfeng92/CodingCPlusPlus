#include<iostream>
#include<string>

// definition for 0 parameter ----terminating call
void show_list3(){}

template<typename T,typename .. Args>
void show_list3(const T& value,const Args&... args)
{
    std::cout << value << '\n';
    show_list3(args...);
}

int main()
{

    int n = 14;
    double x = 3.14159;
    std::string mr = "Mr, String Objects";
    show_list(n, x);
    show_list(x * x, '!', 7, mr);
    return 0;
}