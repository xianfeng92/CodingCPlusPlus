#include <iostream>


using namespace std;

// 枚举有如下问题：
// !! 作用域不受限,会容易引起命名冲突。例如下面无法编译通过的
// enum Color {RED,BLUE};
// enum Feeling {EXCITED,BLUE};

// !! 会隐式转换为 int

// !! 用来表征枚举变量的实际类型不能明确指定，从而无法支持枚举类型的前向声明

// !! 经典做法
// namespace Color
// {
//     enum Type
//     {
//         RED=15,
//         YELLOW,
//         BLUE
//     };
// };

//  !! 因为命名空间是可以随后被扩充内容的，所以它提供的作用域封闭性不高, 更“有效”的办法是用一个类或结构体来限定其作用域
// struct Color1
// {
//     enum Type
//     {
//         RED=102,
//         YELLOW,
//         BLUE
//     };
// };



// !! C++11 的枚举类
// 新的 enum 的作用域不在是全局的
// 不能隐式转换成其他类型
enum class Color2
{
    RED=1000,
    YELLOW,
    BLUE
};


class Person
{
public:
    typedef enum
    {
        BOY = 0,
        GIRL
    } SexType;
};

// 访问的时候通过，Person::BOY或者Person::GIRL来进行访问

int main(int argc, char **argv)
{
    Color2 c2 = Color2::RED;
    cout << "Red is " << static_cast<int>(c2) << endl; //必须转！ << endl;
    cout << "Red is " << static_cast<int>(Color2::YELLOW) << endl; //必须转！ << endl;
    cout << "Red is " << static_cast<int>(Color2::BLUE) << endl; //必须转！ << endl;

    // !! 类中的枚举类型
    cout << "Person boy is " << Person::BOY << endl;

}