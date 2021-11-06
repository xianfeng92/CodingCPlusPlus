#include <iostream>


namespace myname
{
    int var = 42;
}

extern "C" int _ZN6myname3varE;

int main()
{
    printf("%d\n", _ZN6myname3varE);
    return 0;
}

// ~/Stan/xforg/CodingCPlusPlus/GCCDeping/ELF/3.5.4SampleCode(main*) » g++ ManualNamingDemo.cpp -o ManualNamingDemo
// --------------------------------------------------------------------------------
// ~/Stan/xforg/CodingCPlusPlus/GCCDeping/ELF/3.5.4SampleCode(main*) » ./ManualNamingDemo                          
// 42
