#include <iostream>
#include <string>

using namespace std;

// Reference declaration
// Declares a named variable as a reference, that is, an alias to an already-existing object or function.


// !! Lvalue references
// 1. Lvalue references can be used to alias an existing object

// 2. They can also be used to implement pass-by-reference semantics in function calls
void double_string(std::string &s)
{
    s += s; // 's' is the same object as main()'s 'str'
}

// 3. When a function's return type is lvalue reference, the function call expression becomes an lvalue expression
char& char_number(std::string& s, std::size_t n) 
{
    return s.at(n); // string::at() returns a reference to char
}

// !! Rvalue references
// Rvalue references can be used to extend the lifetimes of temporary objects

int main(int argc, char **argv)
{
    std::string s("Example");
    std::string &s1 = &s;
    const std::string &s2 = &s;
    s1 += "Hello";           //  modifies s
                             //  r2 += "!"; // error: cannot modify through reference to const
    std::cout << r2 << '\n'; // prints s, which now holds "Example"

    std::string str = "Test";
    double_string(str);
    std::cout << str << '\n';

    std::string str1 = "Test";
    char_number(str1, 1) = 'a'; // the function call is lvalue, can be assigned to
    std::cout << str1 << '\n';


    std::string s2("TestS2");
    // std::string &&s3 = &s2; // error: can't bind to lvalue
    const std::string &s3 = s2+s2;// okay: lvalue reference to const extends lifetime
    s3 += "Test"; // error: can't modify through reference to const
    std::string&& r3 = s2 + s2; // okay: rvalue reference extends lifetime
    r3 += "Test";                    // okay: can modify through reference to non-const
    std::cout << r3 << '\n';


    return 0;
}
