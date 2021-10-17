#include<iostream>
#include<string>
#include"TestStatic.cpp"

using namespace std;

int TestStatic::m_count = 1000;

int main()
{
    TestStatic demo;
    TestStatic demo1;
    TestStatic demo2;
    TestStatic demo3;
    cout << demo.getDemoCount() << endl;
}
