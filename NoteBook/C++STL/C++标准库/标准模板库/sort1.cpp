#include <algorithm>
#include <deque>
#include <iostream>
#include <string>

using namespace std;

class Person
{
    public:
        string firstname() const;
        string lastname() const;
    ...
};

bool personSortCriteria(const Person& p1, const Person& p2){
    return p1.lastname() < p2.lastname() || (p1.lastname() == p2.lastname() && p1.firstname() < p2.firstname());
}

int main(int argc, char** argv)
{
    deque<Person> coll;
    ...
    std::sort(coll.begin(), coll.end(), personSortCriteria);
    return 0;
}