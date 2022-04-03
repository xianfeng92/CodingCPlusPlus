#include <iterator>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char** argv){
    istream_iterator<string> cinPos(cin);
    ostream_iterator<string> coutPos(cout, " ");

    while(cinPos != istream_iterator<string>){
        advance(cinPos,2);
        if(cinPos != istream_iterator<string>){
            *coutPos = *cinPos++;
        }
    }
    cout << endl;
    return 0;
}