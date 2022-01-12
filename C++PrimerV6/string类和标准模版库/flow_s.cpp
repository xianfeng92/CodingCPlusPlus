#include<iostream>
#include<memory>
#include<string>

int main()
{
    using namespace std;
    shared_ptr<string> films[5] =
    {
        shared_ptr<string> (new string("following")),
        shared_ptr<string> (new string("nio")),
        shared_ptr<string> (new string("apple")),
        shared_ptr<string> (new string("hell")),
        shared_ptr<string> (new string("funck"))
    };

    shared_ptr<string> pwin;
    pwin = films[2];// films[2] lose ownership
    for(int i = 0; i < 5; i++)
    {
        cout << *films[i] << endl;
    }
    cout << "the winter is " << *pwin << endl;
    return 0;
}