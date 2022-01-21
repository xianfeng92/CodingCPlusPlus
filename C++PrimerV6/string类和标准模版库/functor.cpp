#include<iostream>
#include<list>
#include<algorithm>
#include<iterator>

template<typename T>
class TooBig
{
private:
    T cutoff;
public:
    TooBig(const T &cutoff) : cutoff(cutoff){}
    bool operator()(const T &v) {return v > cutoff;}
};

void outint(int n)
{
    std::cout << n << '\n';
}

int main()
{
    using std::list;
    using std::cout;
    using std::endl;

    TooBig<int> f100(100);
    int vals[10] = {40,70,10,34,42,56,76,78,99,90};
    list<int> yadayada(vals, vals + 10);
    list<int> etcetera(vals, vals + 10);

    // C++ 11 can be using following instead
    //list<int> yadayada = {40,70,10,34,42,56,76,78,99,90};

    cout << "Original list:\n";
    for_each(yadayada.begin(), yadayada.end(),outint);
    cout << endl;
    
    for_each(etcetera.begin(), etcetera.end(),outint);

    yadayada.remove_if(f100);
    etcetera.remove_if(TooBig<int>(200));

    cout << "Trimmed List:\n";
    for_each(yadayada.begin(), yadayada.end(),outint);
    cout << endl;

    for_each(etcetera.begin(), etcetera.end(),outint);
    cout << endl;

    return 0;
}