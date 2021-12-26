#include<iostream>
#include<string>
#include<new>

using namespace std;

const int BUF = 512;

class JustTesting
{
    private:
        string words;
        int number;
    public:
        JustTesting(const string& s = "Just Testing", int n = 0)
        {
            words = s;
            number = n;
            cout << words << " constructed\n";
        }
        ~JustTesting()
        {
            cout << words << " destroyed\n";
        }
        void show() const
        {
            cout << words << ", " << number << endl;
        }

};

int main()
{
    char *buffer = new char[BUF];// get a block of memory
    JustTesting *pc1, *pc2;

    pc1 = new(buffer) JustTesting;// place object in buffer
    pc2 = new JustTesting("heap", 20);// place object on heap

    cout << "Memory block address:\n" << "buffer: " << (void *)buffer
    << " heap: " << pc2 << endl;
    cout << "Memory contents:\n";
    cout << pc1 <<": ";
    pc1->show();
    cout << pc2 <<": ";
    pc2->show();

    JustTesting *pc3,*pc4;
    pc3 = new (buffer) JustTesting("bad idea",6);
    pc4 = new JustTesting("heap2",10);

    cout << "Memory contents :\n";
    cout << pc3 << ":";
    pc3->show();

    cout << pc4 << ": ";
    pc4->show();
    delete pc2;// free heap1
    delete pc4;// free heap2

    delete[] buffer;// free buffer
    cout << "done\n";
    return 0;
}

