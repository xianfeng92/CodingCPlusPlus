#include<iostream>

using namespace std;

class Useless
{
private:
    int n;
    char *pc;
    static int ct;
    void showObject() const;
public:
    Useless();
    explicit Useless(int k);
    Useless(int k, char ch);
    Useless(const Useless& other);
    Useless(Useless && other);
    ~Useless();
    Useless operator+(const Useless& other) const;
    void showData() const;
};

// implementation

int Useless::ct = 0;

Useless::Useless()
{
    ++ct;
    n = 0;
    pc = nullptr;
    cout << "Default constructor called, number of objects" << ct << endl;
    showObject();
}

Useless::Useless(int k):n(k)
{
    ++ct;
    cout << "Int constructor called, number of objects" << ct << endl;
    pc = new char[n];
    showObject();
}


Useless::Useless(int k, char ch):n(k)
{
    ++ct;
    cout << "Int, char Constructor called, number of objects " << ct << endl;
    pc = new char[n];
    for(int i = 0; i < n; i++)
    {
        pc[i] = ch;
    }
    showObject();
}

Useless::Useless(const Useless & f):n(f.n)
{
    ++ct;
    cout "Copy constrctor called, number of objects " << ct << endl;
    pc = new char[n];
    for(int i = 0; i < n; i++)
    {
        pc[i] = f.pc[i];
    }
    showObject();
}

Useless::Useless(Useless && f):n(f.n)
{
    ++ct;
    cout << "Move constrctor called, number of objects" << ct << endl;
    pc = f.pc;
    f.pc = nullptr;
    f.n = 0;
    showObject();
}

Useless::~Useless()
{
    cout << "Deconstructor called; objects left" << --ct << endl;
    cout << "delete objects\n";
    showObject();
    delete[] pc;
}

Useless Useless::operator+(const Useless& f) const
{
    cout << "Enter operator + \n";
    Useless temp = Useless(n+f.n);
    for(int i = 0; i < n; i++)
    {
        temp.pc[i] = pc[i];
    }
    for(i = n; i < temp.n; i++)
    {
        temp.pc[i] = f.pc[i -n];
    }
    cout << "temp Object\n";
    cout << "Leaving operator+()\n";
    return temp;
}


void Useless::showObject() const
{
    cout << "Number of elements: " << n;
    cout "Data Address: " << (void *)pc << endl;
}


void Useless::showData() const
{
    if(n == 0)
    {
        cout << "Empty Object\n";
    }
    else
    {
        for(int i = 0; i<n; i++)
        {
            cout << " " << pc[i] << endl;
        }
    }
    cout << endl;
}


int main()
{
    {
        Useless one(10,'X');
        Useless two = one;// calls copy constructor
        Useless three(20,'o');
        Useless four(one+three);// all operator+ , move constructor
        cout << "Object one:";
        one.showData();
        cout << "Object two:\n";
        two.showData()
        cout << "Object three:\n";
        three.showData()
        cout << "Object four:\n";
        four.showData()
    }
    return 0;
}