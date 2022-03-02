#include <string>
#include <iostream>
#include <limits>
#include <exception>

using namespace std;

int main()
{
    try 
    {
        // convert to numeric type
        cout << "stoi(  777) result is " << stoi("  777") << endl;
        cout << "stod(  777) result is " << stod(" 77.77") << endl;
        cout << "stoi(-0x77) result is " <<stoi("-0x77") << endl;

        std::size_t idx;
        cout << stoi(" 42 is the truth", &idx) << endl;
        cout << "idx of first unprocessed char " << idx << endl;

        // convert number to string
        string s = to_string(999);
        cout << "s = " << s << endl;
        cout << stoi(s) << endl;
    }catch(exception e)
    {

    }
    return 0;
}