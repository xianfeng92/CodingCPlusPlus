

using namespace std;


class Apple
{
    public:
    int apple;

    void func(int apple) {
        this->apple = apple;
    }
};

int main(int argc, char **argv)
{
    // this 指针的用处
    // !! 一个对象的 this 指针并不是对象本身的一部分，不会影响 sizeof(对象) 的结果
    // !! this 作用域是在类内部，当在类的非静态成员函数中访问类的非静态成员的时候，编译器会自动将对象本身的地址
    // !! 作为一个隐含参数传递给函数。也就是说，即使你没有写上 this 指针，编译器在编译的时候也是加上 this 的


    // this 指针的使用
    // 1. 在类的非静态成员函数中返回类对象本身的时候，直接使用 return *this
    // 2. 当参数与成员变量名相同时，如 this->n = n

    Apple apple;
    apple.func(100);

}