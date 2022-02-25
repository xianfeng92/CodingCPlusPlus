#include <cstring>
#include <iostream>
#include <string>

using namespace std;

int main() {
  std::string str("HI, bill. I am ill, please pay the bill!");

  string::size_type pos1 = str.find("il");
  cout << "pos1: " << (int)pos1 << endl;
  string::size_type pos2 = str.find("il", 10);
  cout << "pos2: " << (int)pos2 << endl;
  string::size_type pos3 = str.rfind("il");
  cout << "pos3: " << (int)pos3 << endl;
  string::size_type pos4 = str.find_first_of("il");
  cout << "pos4: " << (int)pos4 << endl;
  string::size_type pos5 = str.find_last_of("il");
  cout << "pos5: " << (int)pos5 << endl;
  string::size_type pos6 = str.find_first_not_of("il");
  cout << "pos6: " << (int)pos6 << endl;
  string::size_type pos7 = str.find_last_not_of("il");
  cout << "pos7: " << (int)pos7 << endl;
  string::size_type pos8 = str.find("hi");
  cout << "pos8: " << (int)pos8 << endl;
  return 0;
}