#include <iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<ctime>

const long Size1 = 39L;
const long Size2 = 100 * Size1;
const long Size3 = 100 * Size2;

bool f3(int x) { return x % 3 == 0;}
bool f13(int x) { return x % 13 == 0;}

int main()
{
    using std::count;
    std::vector<int> numbers(Size1);
    std::generate(numbers.begin(),numbers.end(),std::rand);

    cout << "Sample Size is " << Size1 << std::endl;

    int count3 = count_if(numbers.begin(), numbers.end(),f3);

    int count13 = count_if(numbers.begin(), numbers.end(),f13);

    numbers.resize(Size2);
    std::generate(numbers.begin(),numbers.end(),std::rand);

    cout << "Sample Size is " << Size2 << std::endl;

    // use a functor
    class f_mod
    {
    private:
        int dv;
    public:
        f_mod(int d = 1) : dv(d) {}
        bool operator()(int x) { return x % dv == 0; }
    };

    count3 = count_if(numbers.begin(), numbers.end(),f_mod(3));
    count13 = count_if(numbers.begin(), numbers.end(),f_mod(13));
    
    numbers.resize(Size3);
    std::generate(numbers.begin(),numbers.end(),std::rand());
    cout << "Sample Size is " << Size3 << std::endl;

    count3 = count_if(numbers.begin(), numbers.end(),[](int x) { return x % 3 == 0;});

    count13 = count_if(numbers.begin(), numbers.end(),[](int x) { return x % 13 == 0;});

    return 0;
}