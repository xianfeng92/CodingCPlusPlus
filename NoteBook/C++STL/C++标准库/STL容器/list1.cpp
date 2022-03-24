#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;

void printlist(const std::list<int>& l1, const std::list<int>& l2) {
  cout << "list1: " << endl;
  copy(l1.cbegin(), l1.cend(), ostream_iterator<int>(cout, " "));
  cout << endl;

  cout << "list2: " << endl;
  copy(l2.cbegin(), l2.cend(), ostream_iterator<int>(cout, " "));
  cout << endl;
}

int main(int argc, char** argv) {
  list<int> list1, list2;

  for (int i = 0; i < 6; i++) {
    list1.push_back(i);
    list2.push_front(i);
  }

  printlist(list1, list2);

  list2.splice(find(list2.cbegin(), list2.cend(), 3), list1);
  printlist(list1, list2);

  list2.splice(list2.end(), list2, list2.begin());
  printlist(list1, list2);

  list2.sort();
  list1 = list2;
  list2.unique();

  printlist(list1, list2);

  list1.merge(list2);

  printlist(list1, list2);

  return 0;
}