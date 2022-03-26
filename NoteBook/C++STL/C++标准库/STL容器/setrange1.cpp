#include <iostream>
#include <set>

using namespace std;

int main(int argc, char **argv)
{
    set<int> c;

    c.insert(1);
    c.insert(2);
    c.insert(3);
    c.insert(4);
    c.insert(5);
    c.insert(6);

    cout << lower_bound(3) << endl;
    cout << upper_bound(3) << endl;
    cout << equal_range(3) << endl;
    
}