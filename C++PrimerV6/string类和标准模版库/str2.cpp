#include<iostream>
#include<string>

int main()
{
    using namespace std;
    string empty;
    string small = "bit";
    string large = "Are you OK？ See you later\n";
    cout << "Sizes\n";
    cout << "\tempty " << empty.size() << "\n";
    cout<< "\tsmall " << small.size() << "\n";
    cout <<"\tlarge " << large.size() << "\n";

    cout << "Capacities\n";
    cout << "\tempty " << empty.capacity() << "\n";
    cout<< "\tsmall " << small.capacity() << "\n";
    cout <<"\tlarge " << large.capacity() << "\n";

    empty.reserve(50);
    cout << "Capacities after empty.reserve(50):" << empty.capacity() << "\n";
    return 0;
}