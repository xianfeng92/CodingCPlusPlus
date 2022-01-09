#include <iostream>
#include <ctime>
#include <cstdlib>

using std::cout;
class Grand
{
    private:
        int hold;
    public:
        Grand(int h = 0) : hold(h){}
        virtual void speak() const { cout << "I am good grand class!\n";}
        virtual int Value() const { return hold; }
};

class Superb: public Grand
{
    public:
        Superb(int h = 0):Grand(h){}
        void speak() const { cout << "I am good superb class!\n";}
        virtual void say() const { cout << "I hold the superb value of " << Value() <<"!\n"; }
};

class Magnificent: public Superb
{
    private:
        char ch;
    public:
        Magnificent(int h = 0, char c = 'A'):Superb(h),ch(c){}
        void speak() const { cout << "I am good Magnificent class!\n";}
        void say() const { cout << "I hold the character " << ch << "and an integer " << Value() << "!\n";}
};


Grand * GetOne();

int main()
{
    std::srand(std::time(0));
    Grand *pg;
    Superb *ps;
    for(int i = 0; i < 5; i++)
    {
        pg = GetOne();
        pg->speak();
        if(ps = dynamic_cast<Superb*>(pg))
        {
            ps->say();
        }
    }
    return 0;
}

Grand * GetOne()
{
    Grand *p;
    switch(std::rand() % 3)
    {
        case 0: p = new Grand(std::rand() % 100);
            break;
        case 1: p = new Superb(std::rand() % 100);
            break;
        case 2: p = new Magnificent(std::rand() % 100, 'A' + std::rand() % 26);
            break;
    }
    return p;
}