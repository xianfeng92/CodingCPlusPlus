#include <algorithm>
#include <deque>
#include <string>
#include <iostream>

using namespace std;

class Person
{
public:
    string firstname() const;
    string lastname() const;
    ...
};

int main(int argc, char** argv)
{
    deque<Person> coll;
    ...
    std::sort(coll.begin(), coll.end(),[](const Person& a, const Person& b){
        return a.lastname() < b.lastname() || (a.lastname() == b.lastname() && a.firstname() < b.firstname());
    };)
    return 0;
}
