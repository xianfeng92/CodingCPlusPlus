#include <iostream>
#include <cstring>

using namespace std;

class A{
    public:
        int i;
        int j;
};

int main(){
    A a;
    a.i = 1;
    a.j = 2;

    char *p = new char[sizeof(A)];// 使用 C 语言的底层函数 memcpy() 拷贝数据到 p 中
    memcpy(p,&a,sizeof(A));

    A * a2 = reinterpret_cast<A*>(p);// 将 p 强制转化为 A 类型

    cout << "a2->i is " << a2->i << endl;
    cout << "a2->j is " << a2->j << endl;
}