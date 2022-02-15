
#include <deque>
#include <iostream>
#include <algorithm>


using std::vector
using std::cout
using std::endl
using std::sort

void printDeque(const deque<int>& items)
{
    for(auto i = items.begin(); i != items.end(); ++i)
    {
        cout << *i << '\n';
    }
    cout << endl;
}

void test1()
{
    deque<int> d;
    for(auto i = 0; i < 100; ++i)
    {
        d.push_back(i);
    }
    printDeque(d);

    deque<int> d2(d1.begin(), d1.end());
    printDeque(d2);

    deque<int> d3(10,100);
    printDeque(d3);

    deque<int> d4 = d3;
    printDeque(d4);
}

void test2()
{
    deque<int> d1;
    for(int i = 0; i < 10; i++)
    {
        d1.push_back(i);
    }
    printDeque(d1);

    deque<int> d2;
    d2 = d1;
    printDeque(d2);

    deque<int> d3;
    d3.assign(d2.begin(), d2.end());
    printDeque(d3);

    deque<int> d4;
    d4.assign(10,100);
    printDeque(d4);
}

//大小操作
void test3()
{
    deque<int> d1;
    for(int i = 0; i < 10; i++)
    {
        d1.push_back(i);
    }
    printDeque(d1);

    if(d1.empty())
    {
        cout << "d1 is empty" << endl;
    }
    else
    {
        cout << "d1 contains elements of size " << d1.size() << endl;
    }

    d1.resize(10, 1);
    printDeque(d1);
}

//两端操作
void test4()
{
    deque<int> d;

    //尾插
    d.push_back(1);
    d.push_back(2);

    //头插
    d.push_front(10);
    d.push_front(20);

    printDeque(d);

    //尾删
    d.pop_back();

    //头删
    d.pop_front();
    printDeque(d);
}

//插入
void test5()
{
    deque<int> d;
    d.push_back(10);
    d.push_back(20);
    d.push_back(30);
    d.push_back(40);
    printDeque(d);

    d.insert(d.begin(), 1000);
    printDeque(d);

    d.insert(d.begin(), 2, 2000);
    printDeque(d);

    deque<int> d2;
    d2.push_back(1);
    d2.push_back(2);
    d2.push_back(3);

    d.insert(d.begin(),d2.begin(),d2.end());
    printDeque(d);
}

//删除
vod test6()
{
    deque<int> d;
    d.push_back(10);
    d.push_back(20);
    d.push_back(30);
    d.push_back(40);
    printDeque(d);

    d.erase(d.begin());
    printDeque(d);

    d.erase(d.begin(), d.end());
    d.clear();
    printDeque(d);
}

//数据存取
void test7()
{
    deque<int> d;
    d.push_back(10);
    d.push_back(20);
    d.push_front(100);
    d.push_back(200);
    printDeque(d);

    for(int i = 0; i < d.size(); i++)
    {
        cout << d[i] << endl;
    }
    cout << endl;

    for(int i = 0; i < d.size(); i++)
    {
        cout << d.at(i) << endl;
    }
    cout << endl;

    cout << "front: " << d.front() << endl;
    cout << "end: " << d.end() << endl;
}

void test8()
{
    deque<int> d;
    d.push_back(10);
    d.push_back(20);
    d.push_front(100);
    d.push_front(200);
    printDeque(d);
    sort(d.begin(), d.end());
    printDeque(d);
}


int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    return 0;
}









