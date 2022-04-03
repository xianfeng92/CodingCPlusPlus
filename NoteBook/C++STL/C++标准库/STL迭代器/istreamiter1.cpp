#include <iostream>
#include <iterator>

using namespace std;

int main(int argc, char **argv){

    istream_iterator<int> intReader(cin);

    istream_iterator<T> intReadEOF;

    while(intReader != intReadEOF){
        cout << "once " << *intReader << endl;
        cout << "once again " << *intReader << endl;
        ++intReader;
    }
}