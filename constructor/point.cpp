#include <iostream>

using namespace std;

class point
{
private:
    int x,y;

public:
    // 当对象被默认初始化或值初始化时，自动执行默认构造函数
    point() = default;

    // 能通过一个实参调用的构造函数定义了一条从构造函数参数类型向类类型隐式转换的规则
    point(int x):x(x),y(1){};

    // 在要求隐式转换的程序上下文中， 我们可以通过将构造函数声明为 explicit 加以阻止
    // 关键字 explicit 只对一个实参的构造函数有效，需要多个实参的构造函数不能用于执行隐式转换
    explicit point(int xx = 0, int yy = 0){
        x = xx;
        y = yy;
        cout<<"构造函数被调用"<<endl;
    }
    point(point &p);
    ~point(){
        cout<<"析构函数被调用"<<endl;
    }

    int get_x() const { return x; }

    int get_y() const { return y; }
};

point::point(point &p){
    x = p.x;
    y = p.y;
    cout<<"拷贝构造函数被调用"<<endl;
}

void f(point p){
    cout<<p.get_y()<<" " << p.get_x()<<endl;
}

point g(){
    point p(7,33);
    return p;
}


int main(){
    point pp;
    point a(15,22);//构造函数被调用
    point b(a);//用类的一个已知的对象去初始化该类的另一个对象时  拷贝构造函数被调用 
    cout<<b.get_y()<<" "<<b.get_x()<<endl;
    //函数的形参是类的对象，调用函数进行形参和实参的结合时 拷贝构造函数被调用 
    //在函数体内定义的对象，当函数执行结束时，该对象所在类的析构函数会被自动调用
    f(b);
    b = g();//拷贝构造函数的第三种调用情况，拷贝a的值赋给b： 函数的返回值是类的对象，函数执行完返回调用者
    cout<<b.get_y()<<" "<<b.get_x()<<endl;
    return 100;
}




