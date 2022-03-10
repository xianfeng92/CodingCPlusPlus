#include <deque>
#include <string>


using namespace std;


int main()
{
    queue<float> coll;

    for(int i=0; i < 6 ; i++)
    {
        coll.push_front(i * 1.1);
    }

    for(int i=0; i < coll.size(); i++)
    {
        cout << coll[i] << endl;
    }

    cout << endl;

    return 0;
}