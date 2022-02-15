#include<vector>
#include<iostream>

using std::string;
using std::cout;
using std::endl;
using std::vector;


void printVector(vector<int>& v)
{
    for(auto it = v.begin(); it != v.end();it++)
    {
        cout << *it << endl;
    }
    cout << endl;
}


void test1()
{
    vector<int> v1;
    for(int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }

    vector<int> v2(v1.begin(), v1.end());
    printVector(v2);

    vector<int> v3(10,100);
    printVector(v3);

    vector<int> v4(v3);
    printVector(v4);
}

//赋值操作
void test2()
{
    vector<int> v1;
    for(int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }

    vector<int> v2;
    v2 = v1;

    vector<int> v3;
    v3.assign(v1.begin(), v1.end());
    printVector(v3);


    vector<int> v4;
    v4.assign(10,100);
    printVector(v4);
}

void test3()
{
    vector<int> v1;
    for(int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }

    printVector(v1);
    if(v1.empty())
    {
        cout << "v1 is empty" << endl;
    }
    else
    {
        cout << "v1 contains " << v1.size() << " elements" << endl;
        cout << "v1 capacity is " << v1.capacity() << endl;
    }

    // resize 重新指定大小 ，若指定的更小，超出部分元素被删除
    v1.resize(5);
}

//插入和删除
void test4()
{
    vector<int> v1;
    // 尾插
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);
    printVector(v1);

    // 尾删
    v1.pop_back();
    printVector(v1);

    // 插入
    v1.insert(v1.begin(),100);
    printVector(v1);

    v1.insert(v1.begin(), 2, 1000);
    printVector(v1);

    // 删除
    v1.erase(v1.begin());

    // 清空
    v1.erase(v1.begin(), v1.end());
    v1.clear();
    printVector(v1);
}


void test5()
{
    vector<int> v1;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }

    for(int i = 0; i < 10; i++)
    {
        cout << v1[i] << '\n';
    }
    cout << endl;

    for(int i = 0; i < 10; i++)
    {
        cout << v.at(i) << '\n';
    }
    cout << endl;

    cout << "first element is " << v.front() << endl;
    cout << "last element is " << v.end() << endl;
}


void test6()
{
    vector<int> v1;
    for(int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }
    printVector(v1);

    vector<int> v2;
    for(int i = 0; i < 10; i++)
    {
        v2.push_back(i*10);
    }
    printVector(v2);

    //互换容器
    cout << "互换后" << endl;
    v1.swap(v2);

    printVector(v1);
    printVector(v2);
}

//预留空间
void test7()
{
    vector<int> v1;
    v1.reverse(10000);
    int num = 0;
    int *p = nullptr;
    for(int i = 0; i < 10000; i++)
    {
        v.push_back(i);
        if(p != &v1[0])
        {
            p = &v1[0];
            num++;
        }
    }

    cout << num << endl;
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

