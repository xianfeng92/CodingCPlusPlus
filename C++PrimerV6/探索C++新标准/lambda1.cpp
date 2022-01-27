#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<cmath>

const long Size = 39000L;

int main()
{
    using std::cout;
    std::vector<int> numbers(Size);

    std::srand(std::time(0));
    std::generate(numbers.begin(),numbers.end(),std::rand);
    cout << "Sample Size = " << Size << endl;
    // using lambda
    int count3;
    count3 = count_if(numbers.begin(), numbers.end(),[](int x) { return x % 3 == 0;});

    cout << "Count of numbers divide by 3 = " << count3 << endl;

    int count13 = 0;
    std::for_each(numbers.begin(), numbers.end(),[&count13](int x) { count13 += x % 13 == 0;});
    cout << "Count of numbers divide by 13 = " << count13 << endl;

    // using a single lambda
    count13 = count3 = 0;
    std::for_each(numbers.begin(), numbers.end(),[&count3,&count13](int x) { count13 += x % 13; count3 += x % 3 == 0;})

    cout << "Count of numbers divide by 3 = " << count3 << endl;
    cout << "Count of numbers divide by 13 = " << count13 << endl;
    return 0;
}