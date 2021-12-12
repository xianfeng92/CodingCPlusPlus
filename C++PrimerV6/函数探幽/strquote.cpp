// strquote.cpp

#include<iostream>
#include<string>

using namespace std;

string version1(const string &s1, const string &s2);
const string &version2(string &s1, const string &s2);
const string &version3(string &s1, const string &s2);

int main()
{
    string input;
    string copy;
    string result;

    cout << "enter a string: ";
    getline(cin, input);
    copy = input;
    cout << "Your string has entered : " << input << '\n';
    result = version1(input,"*****");
    cout << "Your string enhanced : " << result << '\n';
    cout << "Your original string : " << input << '\n';

    result = version2(input,"#####");
    cout << "Your string enhanced : " << result << '\n';
    cout << "Your original string : " << input << '\n';

    result = version3(input,"&&&&&");
    cout << "Your string enhanced : " << result << '\n';
    cout << "Your original string : " << input << '\n';

    return 0;
}


string version1(const string &s1, const string &s2)
{
    string temp;
    temp = s2+s1+s2;
    return temp;
}

const string &version2(string s1, const string &s2)// has side effects
{
    s1 += s2 + s1;
    return s1;
}

const string &version3(string &s1, const string &s2)// bad design
{
    string temp;
    temp = s2+s1+s2;
    return temp;
}
