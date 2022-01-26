#include<iostream>
#include<utility>

class Useless
{
private:
    int n;
    char *pc;
    static int ct;
    void showObject();
public:
    Useless();
    explicit Useless(int k);
    Useless(int k, char ch);
    Useless(const Useless& f);
    Useless(Useless && f);
    ~Useless();
    Useless& operator+(const Useless& f) const;
    Useless& operator=(const Useless& f);// copy assignment
    Useless& operator(Useless&& f);// move assignment
    void showData() const;

};


// implementation of Useless interface


int Useless::ct = 0；

Useless::Useless()
{
    ++ct;
    n = 0;
    pc = nullptr;
}

Useless::Useless(int k):n(k)
{
    ++ct;
    pc = new char[n];
}

Useless::Useless(int k, char ch):n(k)
{
    ++ct;
    pc = new char[n];
    for(int i = 0; i < n; ++i)
    {
        pc[i] = ch;
    }
}


Useless::Useless(const Useless & f):n(f.n)
{
    ++ct;
    pc = new char[n];
    for(int i = 0; i < n; i++)
    {
        pc [i] = f.pc[i];
    }
}


Useless::Useless(Useless && f):n(f.n)
{
    ++ct;
    pc = f.pc;
    f.pc = nullptr;
    f.n = 0;
}

Useless::~Useless()
{
    delete[] pc;
}


Useless & Useless::operator=(const Useless &f)
{
    std::cout << "Copy Assignment called " << std::endl;
    if(*this == f) return *this;
    delete[] pc;
    n = f.n;
    pc = new char[n];
    for(int i = 0; i < n; i++)
    {
        pc [i] = f.pc[i];
    }
    return *this;
}


Useless & Useless::operator=(Useless &&f)
{
    std::cout << "Move Assignment called " << std::endl;
    if(*this == f) return *this;
    delete[] pc;
    n = f.n;
    pc = f.pc;
    f.pc = nullptr;
    f.n = 0;
    return *this;
}


Useless  Useless::operator+(const Useless& f)
{
    Useless temp = Useless(f.n + n);
    for(int i = 0; i < n; i++)
    {
        temp.pc[i] = pc[i];
    }
    for(i = n; i < temp.n ; i++)
    {
        temp.pc[i] = f.pc[i - n];
    }
    return temp;
}

void showObject()
{
    std::cout << "Number of elements: " << n << std::endl;
    std::cout << "Data address is " << (void *) pc << std::endl;
}

void showData() const;
{
    if(n == 0)
    {
        std::cout << "Empty Object ";
    }
    else
    {
        for(int i = 0; i < n; i++)
        {
            std::cout << pc[i];
        }
    }
    std::cout << endl;
}


// application
int main()
{
    {
        Useless one(10, 'X');
        Useless two = one + one; // calls move constructor
        cout << "Object one:";
        one.showData();
        cout << "Object two:\n";
        two.showData()
        Useless three;
        three = one;// calls copy constructor
        four = one + two; // calls move constructor
        cout<< "Object three:\n";
        three.showData()
        cout<< "Object four:\n";
        four.showData()
    }
    return 0;
}