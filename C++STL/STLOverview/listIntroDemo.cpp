#include <list>
#include <iostream>

using std::list;
using std::cout;
using std::endl;

void printList(list<int>& l)
{
    for(auto it = l.begin(); it != l.end();it++)
    {
        cout << *it << '\n';
    }
    cout << endl;
}

bool myCompare(int v1, int v2)
{
    return (v1 > v2);
}

void test1()
{
    list<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);

    printList(l);

    list<int> l2(l.begin(), l.end());
    printList(l2);

    list<int> l3(l2);
    printList(l3);

    list<int> l4(10,1000);
    printList(l4);
}

// 赋值和交换
void test2()
{
    list<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    l.push_back(40);

    printList(l);

    list<int> l2;
    l2 = l;
    printList(l2);

    list<int> l3;
    l3.assign(l2.begin(), l2.end());
    printList(l3);

    list<int> l4;
    l4.assign(10,1000);
    printList(l4);
}

void test3()
{
    list<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    l.push_back(40);
    printList(l);

    list<int> l2;
    l2.push_back(1);
    l2.push_back(2);
    l2.push_back(3);
    l2.push_back(4);
    printList(l2);

    l2.swap(l);
    printList(l);
    printList(l2);
}

void test4()
{
    list<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    l.push_back(40);
    printList(l);

    if(l.empty())
    {
        cout << "l is empty" << endl;
    }
    else
    {
        cout << "l contains " << l.size() << endl;
    }
    l.resize(10);
    printList(l);

}

void test5()
{
    list<int> l1;
    //尾插
    l1.push_back(1);
    l1.push_back(2);

    //头插
    l1.push_front(10);
    l1.push_front(20);
    printList(l1);

    
    //尾删
    l1.pop_back();
    printList(l1);

    //头删
    l1.pop_front();
    printList(l1);

    //插入
    list<int>::iterator l2 = l1.begin();
    l1.insert(++it, 1000);
    printList(l1);

    //插入
    it = l1.begin();
    l1.erase(++it);
    printList(l1);

    //插入
    l1.push_back(100);
    l1.push_back(100);
    l1.push_back(100);
    l1.push_front(100);
    l1.remove(100);
    printList(l1);

    // 插入
    l1.clear();
    printList(l1);
}

void test6()
{
    list<int> l1;
    l1.push_back(10);
    l1.push_front(20);
    l1.push_back(30);
    l1.push_back(40);

    cout << "first element is " << l1.front() << endl;
    cout << "last element is " << l1.back() << endl;

    /list容器的迭代器是双向迭代器, 不支持随机访问
    list<int>::iterator it = L1.begin();
    //it = it + 1;//错误，不可以跳跃访问, 即使是 +1
}

//反转和排序
void test7()
{
    list<int> l1;
    l1.push_back(10);
    l1.push_back(5);
    l1.push_back(18);
    l1.push_back(98);
    l1.push_back(23);
    printList(l1);

    l1.reverse();
    printList(l1);

    l1.sort();

    l1.sort(myCompare);
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
    return 0;
}