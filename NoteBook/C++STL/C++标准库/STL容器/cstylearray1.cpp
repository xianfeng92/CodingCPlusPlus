#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main(int argc, char** argv){
    int vals[] = {1,2,3,4,5,6,7};

    std::vector<int> v(std::begin(vals), std::end(vals));

    std::copy(std::begin(vals), std::end(vals),ostream_iterator<int>(cout, " "));

    cout << endl;

    return 0;
}