#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Person{
private:
    string name;
public:
    Person(string n): name(n){}

    void print() const {
        cout << name << endl; 
    }

    void print2(const string& prefix) const {
        cout << prefix << name << endl;
    }
};

int main(int argc, char** argv){

    vector<Person> coll = {Person("tick"), Person("amy"), Person("Tony")};

    for_each(coll.begin(), coll.end(), [](const Person& p){
        p.print();
    });

    cout << endl;

    for_each(coll.begin(), coll.end(),[](const Person& p){
        p.print2("Person: ");
    });

    return 0;
}


