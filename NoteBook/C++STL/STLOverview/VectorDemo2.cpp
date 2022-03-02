#include <string>
#include <vector>

#include <iostream>


using std::string;
using std::vector;
using std::cout;
using std::endl;

//自定义数据类型
class Person
{
public:
    Person(string name, int age) : name_(name), age_(age)
    {
        cout << "constructor person " << name_  << " with age is " << age_ << endl;
    }
    ~Person()
    {
        cout << "destructor person " << name_ << " with age is " << age_ << endl;
    }
public:
    string name_;
    int age_;
};

//自定义数据类型
void test1()
{
    vector<Person> persons;
    
    cout << "Prepare person Data" << endl;
    
    //创建数据
    Person p1("aaa",1);
    Person p2("bbb",2);
    Person p3("ccc",3);
    Person p4("ddd",4);
    Person p5("eee",5);

    cout << "Store person In Vector" << endl;
    persons.push_back(p1);
    persons.push_back(p2);
    persons.push_back(p3);
    persons.push_back(p4);
    persons.push_back(p5);

    cout << "persons size: " << persons.size() << endl;

    cout << "Traverse Vector " << endl;
    for(auto it = persons.begin(); it != persons.end();it++)
    {
        cout << "Name:" << (*it).name_ << " age:" << (*it).age_ << endl;
    }
}

//放对象指针
void test2()
{
    vector<Person*> v;

    //创建数据
    Person p1("e",1);
    Person p2("f",2);
    Person p3("g",3);
    Person p4("h",4);
    Person p5("i",5);


    v.push_back(&p1);
    v.push_back(&p2);
    v.push_back(&p3);
    v.push_back(&p4);
    v.push_back(&p5);


    for (vector<Person*>::iterator it = v.begin(); it != v.end(); it++)
    {
        Person * p = (*it);
        cout << "Name:" << p->name_ << " Age:" << (*it)->age_ << endl;
    }
}

void test3()
{
    vector<Person> persons;
    persons.reverse(10);
    
    cout << "Prepare person Data" << endl;
    
    //创建数据
    Person p1("aaa",1);
    Person p2("bbb",2);
    Person p3("ccc",3);
    Person p4("ddd",4);
    Person p5("eee",5);

    cout << "Store person In Vector" << endl;
    persons.push_back(p1);
    persons.push_back(p2);
    persons.push_back(p3);
    persons.push_back(p4);
    persons.push_back(p5);

    cout << "persons size: " << persons.size() << endl;

    cout << "Traverse Vector " << endl;
    for(auto it = persons.begin(); it != persons.end();it++)
    {
        cout << "Name:" << (*it).name_ << " age:" << (*it).age_ << endl;
    }
}

int main()
{
    test1();
    cout << endl;
    test2();
    cout << endl;
    test3();

    return 0;
}