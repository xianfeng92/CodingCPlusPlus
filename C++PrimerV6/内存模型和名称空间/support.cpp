// compile with external.cpp
#include<iostream>
extern double warming;// using warming from another

// function prototype
void update(double dt);
void local();

using std::cout;
void update(double dt)
{
    extern double warming;
    warming += dt;
    cout << "Updating global warming to " << warming;
    cout << "degrees.\n";
}


void local()
{
    double warming = 0.8;
    cout << "Local warming is " << warming << " degrees.\n";
    cout << "Bit global warming= " << ::warming;
    cout << " degrees.\n";
}

