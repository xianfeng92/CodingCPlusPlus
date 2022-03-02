#include <set>
#include <iostream>

void printSet(set<int>& set)
{
    for(auto it = set.begin(); it != set.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << endl;
}

//构造和赋值
void test1()
{
    set<int> s1;
    s1.insert(10);
    s1.insert(20);
    s1.insert(30);
    s1.insert(40);
    printSet(s1);

    set<int> s2(s1);
    printSet(s2);

    set<int> s3;
    s3 =  s2;
    printSet(s3);
}

void test2()
{
    set<int> s1;

    s1.insert(100);
    s1.insert(200);
    s1.insert(300);
    s1.insert(400);

    set<int>  s2;
    s2.insert(1);
    s2.insert(2);
    s2.insert(43);
    s2.insert(89);

    cout << "交换前" << endl;
    printSet(s1);
    printSet(s2);

    cout << "交换后" << endl;
    s1.swap(v2);

    printSet(s1);
    printSet(s2);
}

void test3()
{
    set<int> s1;
    s1.insert(100);
    s1.insert(200);
    s1.insert(300);
    s1.insert(400);
    printSet(s1);

    //删除
    s1.erase(s1.begin());
    printSet(s1);

    s1.erase(300);
    printSet(s1);

    s1.erase(s1.begin(), s1.end());
    s1.clear();
    printSet(s1);

}

int main()
{
    test1();
    test2();
    test3();
    return 0;
}