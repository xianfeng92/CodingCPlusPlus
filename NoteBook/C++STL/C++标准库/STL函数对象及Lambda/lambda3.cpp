#include <algorithm>
#include <iostream>
#include <list>

#include "print.hpp"

using namespace std;

int main(int argc, char** argv) {
  list<int> coll = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  PRINT_ELEMENTS(coll);

  int count = 0;
  list<int>::iterator pos;
  pos = remove_if(coll.begin(), coll.end(),
                  [count](int) mutable { return ++count == 3; };);

  coll.erase(pos, coll.end());

  PRINT_ELEMENTS(coll);

  return 0;
}