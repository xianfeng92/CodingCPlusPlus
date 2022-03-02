#include<stdio.h>

using namespace std;

struct Base
{ // public
    int v1;
    //    public:      //error
    int v2;
    //private:
    int v3;
    //void print(){       // c中不能在结构体中嵌入函数
    //    printf("%s\n","hello world");
    //};    //error!
};

void Base()
{
    printf("%s\n", "I am Base func");
}

//struct Base base1;  //ok
//Base base2; //error

int main(int argc, char **argv)
{
    // !! 1.C 中 struct

    // 1. 在 C 中 struct 只单纯的用作数据的复合类型，也就是说，在结构体声明中只能将数据成员放在里面，而不能将函数放在里面
    // 2. 在 C 结构体声明中不能使用 C++ 访问修饰符，如：public、protected、private 而在 C++ 中可以使用
    // 3. 在 C 中定义结构体变量，如果使用了下面定义必须加 struct
    // 4. C 的结构体不能继承（没有这一概念）
    // 5. 若结构体的名字与函数名相同，可以正常运行且正常的调用！例如：可以定义与 struct Base 不冲突的 void Base() {}
    struct Base base;
    base.v1=1;
    //base.print();
    printf("%d\n",base.v1);
    Base();


    // !! 2.C++中struct
    // 1. C++ 结构体中不仅可以定义数据，还可以定义函数
    // 2. C++ 结构体中可以使用访问修饰符，如：public、protected、private 
    // 3. C++ 结构体使用可以直接使用不带struct
    // 4. C++ 继承
    // 5. 若结构体的名字与函数名相同，可以正常运行且正常的调用！但是定义结构体变量时候只用用带struct的！

    // !!3.struct 与class 区别
    // !! 总的来说，struct 更适合看成是一个数据结构的实现体，class 更适合看成是一个对象的实现体
    // !! 区别: 最本质的一个区别就是默认的访问控制,默认的继承访问权限。struct 是 public 的，class 是 private 的

    
}