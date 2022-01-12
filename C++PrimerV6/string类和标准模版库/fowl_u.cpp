#include<iostream>
#include<memory>
#include<string>

int main()
{
    using namespace std;
    unique_ptr<string> films[5] =
    {
        unique_ptr<string> (new string("following")),
        unique_ptr<string> (new string("nio")),
        unique_ptr<string> (new string("apple")),
        unique_ptr<string> (new string("hell")),
        unique_ptr<string> (new string("funck"))
    };

    unique_ptr<string> pwin;
    pwin = films[2];// films[2] lose ownership
    for(int i = 0; i < 5; i++)
    {
        cout << *films[i] << endl;
    }
    cout << "the winter is " << *pwin << endl;
    return 0;
}


