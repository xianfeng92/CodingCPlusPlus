#include <vector>
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
    vector<string> sentence;// create empty vector for string

    sentence.reverse(5);// reverse memory for five elements to avoid reallocation

    sentence.push_back("hello");
    sentence.insert(sentence.end(),{"how","are","you","?"});

    copy(sentence.cbegin(),sentence.cend(),ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << "max_size() " << sentence.max_size() << endl;
    cout << "size() " << sentence.size() << endl;
    cout << "capacity() " << sentence.capacity() << endl;

    swap(sentence[1], sentence[3]);

    sentence.insert(std::find(sentence.begin(),sentence.end(),"?"), "always");

    sentence.back() = "!";

    copy(sentence.cbegin(),sentence.cend(),ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << "size () " << sentence.size() << endl;
    cout << "capacity ()" << sentence.capacity() << endl;
    cout << endl;

    sentence.shrink_to_fit();

    cout << "size () " << sentence.size() << endl;
    cout << "capacity ()" << sentence.capacity() << endl;
    cout << endl;
    return 0;
}
