// !! {fmt} is an open-source formatting library providing a fast and safe alternative to C stdio and C++ iostreams.

#include "fmt/core.h"
#include "fmt/ranges.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    fmt::print("hello world\n");

    // Format a string
    std::string s = fmt::format("The answer is {}.", 42);
    cout << "s is " << s << endl;

    fmt::print("hello {0} {0}\n", "WORLD");

    // Format a string using positional arguments
    std::string s1 = fmt::format("I'd rather be {1} than {0}.", "right", "happy");

    std::vector<int> vec = {42, 42, 42, 42, 42, 42};
    fmt::print("{}\n",vec);
    return 0;
}