#include<iostream>
#include<vector>
#include<iterator>

int main()
{
    using namespace std;

    int casts[10] = {0,1,2,3,4,5,6,7,8,9};
    vector<int> dice(10);
    // copy from array to vector
    copy(casts, casts+10, dice.begin());

    cout << "Let the dice be cast!\n";
    // create an ostream_iterator
    ostream_iterator<int, char> out_iter(cout, " ");
    // copy from vector to ostream_iterator
    copy(dice.begin(), dice.end(), out_iter);

    cout << endl;
    cout << "Implicit use of reverse iterator\n";
    copy(dice.rbegin(), dice.rend(), out_iter);

    cout << endl;

    cout << "Explicit use of reverse iterator\n";
    vector<int>::reverse_iterator ri;
    for(ri = dice.rbegin(); ri != dice.rend(); ++ri)
    {
        cout << *ri << endl;
    }
    cout << endl;
    return 0;
}