#include <iostream>
#include <algorithm>
#include <list>
#include <locale>
#include <string>

using namespace std;

char myToUpper(char c) {
    std::locale loc;
    return std::use_facet<std::ctype<char>> (loc).toupper(c);
}

int main(int argc, char* argv[]) {

    string s("Internationalization");
    string sub("National");

    string::iterator pos;
    pos = search(s.begin(), s.end(), [](char c1, char c2) {
        return myToUpper(c1) == myToUpper(c2);
    });
}