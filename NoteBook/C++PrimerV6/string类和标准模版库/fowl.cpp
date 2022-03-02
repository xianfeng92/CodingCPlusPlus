#include<iostream>
#include<memory>
#include<string>

int main()
{
    using namespace std;
    auto_ptr<string> films[5] =
    {
        auto_ptr<string> (new string("following")),
        auto_ptr<string> (new string("nio")),
        auto_ptr<string> (new string("apple")),
        auto_ptr<string> (new string("hell")),
        auto_ptr<string> (new string("funck"))
    };

    auto_ptr<string> pwin;
    pwin = films[2];// films[2] lose ownership
    for(int i = 0; i < 5; i++)
    {
        cout << *films[i] << endl;
    }
    cout << "the winter is " << *pwin << endl;
    return 0;
}