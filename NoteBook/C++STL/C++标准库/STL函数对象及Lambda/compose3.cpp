#include <iostream>
#include <algorithm>
#include <iostream>
#include <functional>
#include <locale>
#include <string>

using namespace std;
using namespace std::placeholders;

char myToUpper(char c) {
    std::locale loc;
    return std::use_facet<std::ctype<char>>(loc).toupper(c);
}

int main(int argc, char ** argv){

    string s("Internationalization");
    string sub("Nation");

    string::iterator pos;
    pos =search(s.begin(), s.end(), bind(equal_to<char>(),bind(myToUpper,_1), bind(myToUpper,_2)));

    if(pos != s.end()){
        cout << "\"" << sub << "is part of " << s << endl;
    }
    
}