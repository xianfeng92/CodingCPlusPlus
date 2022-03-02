#include <tuple>
#include <iostream>
#include <complex>
#include <string>

using namespace std;

int main()
{
    // create and initialize a tuple with default value
    // 每个元素的内容由 default 构造函数初始化。基础类型都被初始化为 0 (这项保证始自 C++11)
    tuple<string, int, int, complex<double> > t;

    // Create and initialize a tuple explicit
    tuple<int, float, string> t1(41, 6.3, "nico");

    // "iterate" over elements
    cout << get<0>(t1) << endl;
    cout << get<1>(t1) << endl;
    cout << get<2>(t1) << endl;
    cout << endl;

    // 使用 make_tuple() 建立 tuple, 其所有元素类型都自动推导自其初值
    auto t2 = make_tuple(22,44,"nico");
    get<1>(t1) = get<1>(t2);

    if(t1 < t2)
    {
        t1 = t2;
    }

    return 0;
}