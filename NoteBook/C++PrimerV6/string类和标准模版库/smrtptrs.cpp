#include<iostream>
#include<memory>
#include <string>

class Repoter
{
private:
    std::string str;
public:
    Repoter(const std::string &str) : str(str)
    {
        cout << "Object created\n";
    }

    ~Repoter()
    {
        cout << "Object deleted\n";
    }
    void comment() const
    {
        std::cout << str << "\n";
    }
};


int main()
{
    {
        std::auto_ptr<Repoter> ps(new Repoter("using auto ptr"));
        ps->comment();
    }

    {
        std::shared_ptr<Repoter> ps(new Repoter("using shared_ptr"));
        ps->comment();
    }
    {
        std::unique_ptr<Repoter> ps(new Repoter('using shared_ptr'));
        ps->comment();
    }
}