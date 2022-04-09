#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace std::placeholders;

class Person {
 private:
  string name;

 public:
  Person(const string& n) : name(n) {}
  void print() const { cout << name << endl; }

  void print2(const string& prefix) const { cout << prefix << name << endl; }
  ...
};

int main(int argc, char** argv) {
  vector<Person> coll = {Person("alice"), Person("Bob"), Person("Amy"),
                         Person("Tony")};

   for_each(coll.begin(), coll.end(), bind(&Person::print, _1));
   cout << endl;

  for_each(coll.begin(), coll.end(), bind(&Person::print2, _1, "Person: "));
  cout << endl;

  bind(&Person::print2, _1, "This is:")(Person("Stefen"));
}