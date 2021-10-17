#include <string>
#include <iostream>
#include <memory>
#include<new>
#include <vector>



using namespace std;

int main(int argc, char **argv)
{
    // 程序对象的生命周期：1. 全局对象--在程序启动时分配，在程序结束时销毁；2. 局部自动对象--进入程序所在块时被创建，在离开块时被销毁；
    // 3. 局部 static 对象---在第一次使用前分配，在程序结束时销毁；4. 动态分配对象--生命周期与在哪里创建无关系，只有当显示的被释放时，这些对象才会被销毁
    // 动态对象的正确释放被证明是编程中及其容易出错的地方，为了更安全的使用动态对象，标准库定义了两个智能指针来管理动态分配的对象。当一个对象应该被释放时，指向它的
    // 智能指针可以确保自动的释放它~

    // 静态内存：用于保存局部 static 对象；类 static 数据成员；定义在任何函数之外的变量。 
    // 栈内存：用于保存定义在函数内的非 static 对象
    // 分配在静态或栈内存的对象由编译器自动创建和销毁
    // 除了静态内存和栈内存，每个程序还拥有一个内存池，这部分内存称为自由空间或者堆（heap）
    // 在 c++ 中动态内存的管理通过一对运算符完成：new，在动态内存中为对象分配空间，并返回值指向该对象的指针； delete 接受一个动态对象的指针
    // 销毁该对象，并释放与之关联的内存
    // 为了更容易（同时也更安全）的使用动态内存，新的标准库提供了两种智能指针类型来管理动态对象
    // 最安全的分配和使用动态内存的方法是调用一个名为 make_shared 的标准库函数
    // 指向一个值为 42 的 int 类型的 shared_ptr
    // make_shared 用其参数来构造给定类型的对象
    shared_ptr<int> p1 = make_shared<int>(12);
    shared_ptr<string> p2 = make_shared<string>("helloworld");
    // 我们不传递任何参数时，就会进行值初始化
    shared_ptr<int> p3 = make_shared<int>();
    // p4 指向一个动态分配的空 vector<string>
    auto p4 = make_shared<string>();

    // shared_ptr 的拷贝和赋值
    auto p5 = make_shared<int>(122);// p5 指向的对象只有 p5 一个引用者
    auto p6(p5);// p5 和 p6指向相同对象，此对象有两个引用者

    auto p7 = make_shared<int>(12321);// p7 指向的 int 只有一个引用者

    p7 = p5;// p7 原来指向的对象已没有引用者，会自动释放

    // why 使用动态内存， 1.程序不知道自己使用多少对象;2.程序不知道所需对象的准确类型;3.程序需要在多个对象间共享数据

    // bad_alloc 和 nothrow 都定义在头文件 new 中
    int *ppp1 = new int(199);// 如果分配失败，new 抛出 std::bad_alloc
    int *pp2 = new (nothrow) int(1111);// 如果分配失败，new 返回一个空指针

    // 为了防止内存耗尽，在动态内存使用完后，必须将其归还给系统
    delete ppp1;// p1 必须指向一个动态分配的对象或者空指针，将会执行两个动作：1. 销毁给定指针指向的对象，2. 释放对应内存
    delete pp2;

    const int *pp3 = new int(1111);
    // 使用 p3
    delete pp3;// 正确！ 释放一个 const 对象
    pp3 = nullptr;// delete 之后重置指针值，这样就清楚的指示指针不指向任何对象

    // 动态对象的生存期直到被释放为止---由内置指针（而不是智能指针）管理的动态内存在被显示释放前将会一直存在
    // 坚持使用智能指针~~~~对于一块内存，只有在没有任何智能指针指向它的情况下，智能指针才会自动的释放


    int *qp4 = new int(666);
    auto q = qp4; // q 和 qp4 指向相同内存
    delete qp4;// q 和 qp4 均变为无效
    qp4 = nullptr;// 指出 qp4 不再绑定到任何对象

    // shared_ptr 和 new 结合使用
    shared_ptr<double> pp(new double(2.22));// pp 指向一个值为 2.22 的 double
    // 默认情况下，一个用来初始化智能指针的普通指针必须指向动态内存，因为智能指针默认使用 delete 释放它所关联的对象
    // 当将 shared_ptr 绑定到一个普通指针时，我们就将内存的管理职责交给了 shared_ptr。一旦这么做，就不应该使用内置指针访问
    // shared_ptr 所指向的内存了

    // 智能指针类型定义了一个 get 函数，它返回一个内置指针，指向智能指针所管理的对象
    // 此 get 函数是为了向不能使用智能指针的代码传递一个内置指针。使用 get 返回的指针的代码不能 delete 此指针
    shared_ptr<int> pp1 = make_shared<int>(111);
    int *qq = pp1.get(); // 正确~使用 qq 时要注意，不要让它管理的指针被释放
    {
        shared_ptr<int>(qq);
    }// 程序块结束，qq 被销毁，它所指向的内存被释放
    int foo = *pp1;// 未定义：pp1 指向的内存已经被释放

    // get 用来将指针的访问权限传递给代码
    // 永远不要给 get 初始化另外一个智能指针或者为另外一个智能指针赋值

    shared_ptr<string> op = make_shared<string>("xforg");
    // 使用 reset 来将一个新的指针赋予 shared_ptr
    op.reset(new string("hello"));

    if(!op.unique())
    {
        op.reset(new string(*op));// 我们不是唯一用户，分配新的拷贝
    }
    *op += " world";

    cout << *op << endl;
    // 如何正确使用智能指针：
    // 1. 不适用内置指针初始化（或reset）多个智能指针
    // 2. 不 delete get() 返回的指针
    // 3. 不使用 get() 初始化或 reset 另一个智能指针
    // 4. 如果你使用 get 返回的指针，记住当最后一个对应的智能指针被销毁后，你的指针就无效了
    // 5. 如果你使用的智能指针管理的资源不是 new 分配的内存，记得传给它一个删除器


    // unique_ptr
    unique_ptr<double> up1;
    unique_ptr<double> up2(new double(42.22));

    // 由于一个 unique_ptr 拥有它指向的对象，因此 unique_ptr 不支持普通的拷贝和赋值
    
}

// 一个简单的确保资源被释放的方法是使用智能指针
void f()
{
    shared_ptr<int> sp = make_shared<int>(12);
    // 此处抛出一个异常，且未在 f 中捕获
}// 在程序块结束时 sp 自动释放内存


void f2()
{
    int * pp = new int[12];
    // 此处抛出一个异常，且未在 f2 中捕获
    delete pp;
}// 抛出异常后，在f2结束时，new int[12] 分配的内存就永远不会被释放














