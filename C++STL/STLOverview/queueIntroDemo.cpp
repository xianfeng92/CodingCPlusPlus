#include<queue>
#include<string>
#include<iostream>

using std::string;


class Person
{
public:
    Person(string name, int age) : name_(name), age_(age){ }

public:
    string name_;
    int age_;
};

void test1()
{
    queue<Person> q;

    //准备数据
    Person p1("唐僧", 30);
    Person p2("孙悟空", 1000);
    Person p3("猪八戒", 900);
    Person p4("沙僧", 800);

    q.push(p1);
    q.push(p2);
    q.push(p3);
    q.push(p4);

    while(!q.empty())
    {
        cout <<" name is " << q.front().name_ << " age is " << q.front().age_ << endl;
        cout << endl;
        q.pop();
    }
    cout << "q size is " << q.size() << endl;
}

int main()
{
    test1();

    return 0;
}