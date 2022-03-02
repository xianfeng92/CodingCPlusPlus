// ifelse.cpp

#include<iostream>

int main()
{
    char ch;

    std::cout << "Type and I shall repeat.\n";
    std::cin >> ch;
    while(ch != '.')
    {
        if(ch == '\n')
        {
            std::cout << ch;
        }
        else
        {
            std::cout << ++ch;
        }
        std::cin >> ch;
    }
    std::cout << "\n Please excuse the slight confusion.\n";
    return 0;
}