#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

int main()
{

    shared_ptr<string> ps1(new string("world"), [](string *p)
    {
        cout << "delete p " << *p << endl;
        delete p;
    }
    );
    shared_ptr<string> ps2(new string("hello"));

    (*ps1)[0] = 'M';

    ps2->replace(0, 1,"X");

    vector<shared_ptr<string> > vec;

    vec.push_back(ps2);
    vec.push_back(ps1);
    vec.push_back(ps2);
    vec.push_back(ps1);
    vec.push_back(ps2);

    for(auto v : vec)
    {
        cout << (*v) << endl;
    }
    cout << endl;

    *ps1 = "FUCK";

    for(auto v : vec)
    {
        cout << (*v) << endl;
    }

    cout << endl;

    return 0;
}