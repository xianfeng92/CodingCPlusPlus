#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;


class Person{
    public:
        string firstname() const;
        string lastname() const;
        ...
};

class PersonSortCriteria{
    public:
        bool operator()(const Person& a, const Person& b) const{
            return a.firstname() < b.firstname() || (a.firstname() == b.firstname() && a.lastname() < b.lastname());
        }
};

int main(int argc, char **argv){

    set<Person,PersonSortCriteria> coll;
    ...
    for(auto pos = coll.begin(); pos != coll.end(); ++pos){
        ...
    }
    ...

    return 0;
}