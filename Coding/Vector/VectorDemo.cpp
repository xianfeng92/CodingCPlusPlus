#include <vector>
#include <iostream>
#include <unistd.h>

using namespace std;

class Person{
    public:
        int id_;
        Person():id_(0)
        {
            cout << "Person created " << id_ << endl;
        }

        ~Person()
        {
            cout << "Person deleted " << id_ << endl;
        }

        Person(const Person& other)
        {
            this->id_ = other.id_;
            cout << "Person copy constructor\n";
        }

        Person(Person&& other)
        {
            this->id_ = other.id_;
            cout << "Person move constructor\n";
        }

        Person& operator=(const Person & other){
            cout << "Person assigned\n";
            this->id_ = other.id_;
            return *this;
        }

        Person operator=(Person&& other)
        {
            this->id_ = other.id_;
            cout << "Person move assignment\n";
            return *this;
        }
};

int main()
{
    vector<Person> persons;

    cout << endl;

    persons.push_back(std::move(Person()));

    while(1){
        usleep(1000000);
    }

    // Person person(11);
    // persons.push_back(std::move(person));
    // Person person2(22);
    // persons.push_back(std::move(person2));


    // while(1)
    // {
    //     usleep(10000);
    // }
    return 0;
}