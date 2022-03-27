#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

using namespace std;

class RuntimeStringCmp {
 public:
  enum cmp_mode { normal, nocase };
  RuntimeStringCmp(cmp_mode m = normal) : mode(m) {}

  bool operator()(const string& s1, const string& s2) const {
    if (mode == normal) {
      return s1 < s2;
    } else {
      return lexicographic_compare(s1.begin(), s1.end(), s2.begin(), s2.end(),
                                   nocase_compare);
    }
  }

 private:
  const cmp_mode mode;
  static bool nocase_compare(char c1, char c2) {
    return toupper(c1) < toupper(c2);
  }
};

void fillAndPrint(StringStringMap & coll);

typedef std::map<std::string, std::string> StringStringMap;

int main(int argc, char** argv) {

    StringStringMap coll1;
    fillAndPrint(coll1);

    RuntimeStringCmp ignoreCase(RuntimeStringCmp::nocase);
    StringStringMap coll2(ignoreCase);

    fillAndPrint(coll2);

    return 0;
}

void fillAndPrint(StringStringMap& coll) {
    coll["hello"] = "world";
    coll["tell"] = "me";
    coll["fuck"] = "you";
    coll["bluent"] = "Green";
    coll["black"] = "night";
    coll["bunny"] = "pink";

    // print all elements
    for(auto &elem : coll) {
        cout << elem.first << " " << elem.second << endl;
    }
}