#include<iostream>
#include<string>


using namespace std;

void demo()
{
    // static variable 
    // !! 当变量声明为 static 时，期内存空间将在程序的生命周期内分配。即使多次调用该函数，静态变量的空间也只分配一次，
    // !! 前一次调用中的s变量值通过下一次函数调用传递。这对于在 C / C ++ 或需要存储先前函数状态的任何其他应用程序非常有用。
    static int count = 0; 
    cout << count << " " << endl; 

    // value is updated and 
    // will be carried to next 
    // function calls 
    count++; 
}


class Apple 
{
public: 
    // 由于声明为 static 的变量只被初始化一次，因为它们在单独的静态存储中分配了空间，因此类中的静态变量由对象共享。
    // 对于不同的对象，不能有相同静态变量的多个副本。也是因为这个原因，静态变量不能使用构造函数初始化
    static int fuck;

    Apple()
    {
        // Do nothing 
        cout << " I am Apple" << endl;
    }; 
};


int Apple::fuck = 100;



class Orange 
{ 
    private:
        int i; 
    public: 
        Orange() 
        { 
            i = 0; 
            cout << "Inside Constructor\n"; 
        } 
        ~Orange() 
        { 
            cout << "Inside Destructor\n"; 
        } 
};

class Banana 
{ 
    public: 
        // static member function 
        static void printMsg() 
        {
            cout<<"Welcome to Banana!" << endl; 
        }
}; 


int main(int argc, char **argv)
{
    // !! 静态变量
    // 1. 函数中的静态变量
    for (int i = 0; i < 5; i++)
    {
        demo();
    }

    // 2. 类中的静态变量
    Apple obj1;
    Apple obj2;
    obj1.fuck = 200;
    obj2.fuck = 300;

    // prints value of i
    cout << "Hello " << obj1.fuck << " " << obj2.fuck << endl;
    // !! 静态成员
    // !! 类对象为静态----就像变量一样，对象也在声明为 static 时具有范围直到程序结束的生命周期

    int x = 0; 

    // Inside Constructor
    // Inside Destructor
    // End of main
    if (x==0) 
    {
        Orange obj; 
    }
    cout << "End of main\n";


    // Inside Constructor
    // End of main
    // Inside Destructor
    if (x==0) 
    {
        static Orange obj; 
    }
    cout << "End of main\n";


    // !! 类中的静态函数
    // 就像类中的静态数据成员或静态变量一样，静态成员函数也不依赖于类的对象。我们被允许使用对象和'.'来调用静态成员函数。
    // 但建议使用类名和范围解析运算符调用静态成员

    // invoking a static member function 
    Banana::printMsg();

    return 0;
}
