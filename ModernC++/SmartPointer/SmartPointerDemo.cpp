#include<iostream>
#include<memory>


// !! 智能指针与内存管理

// !! 一、RAII 与引用计数

了解 Objective-C/Swift 的程序员应该知道~引用计数~的概念。引用计数这种计数是为了防止内存泄露而产生的。 基本想法是对于动态分配的对象，进行引用计数，每当增加
一次对同一个对象的引用，那么引用对象的引用计数就会增加一次， 每删除一次引用，引用计数就会减一，当一个对象的引用计数减为零时，就自动删除指向的堆内存。

// !! 在传统 C++ 中，『记得』手动释放资源，总不是最佳实践

因为我们很有可能就忘记了去释放资源而导致泄露, 所以通常的做法是对于一个对象而言，在构造函数中申请空间，而在析构函数（在离开作用域时调用）的时候释放空间， 
也就是我们常说的 RAII 资源获取即初始化技术

凡事都有例外，我们总会有需要将对象在自由存储上分配的需求，在传统 C++ 里我们只好使用 new 和 delete 去 『记得』对资源进行释放。而 C++11 引入了智能指针的概念，
使用了引用计数的想法，让程序员不再需要关心手动释放内存。

这些智能指针就包括 std::shared_ptr/std::unique_ptr/std::weak_ptr 使用它们需要包含头文件 <memory>

注意：引用计数不是垃圾回收，引用计数能够尽快收回不再被使用的对象，同时在回收的过程中也不会造成长时间的等待，更能够清晰明确的表明资源的生命周期。


// !! std::shared_ptr

std::shared_ptr 是一种智能指针，它能够记录多个 shared_ptr 共同指向一个对象，从而消除显式的调用 delete，当引用计数变为零的时候就会将对象自动删除。
但还不够，因为使用 std::shared_ptr 仍然需要使用 new 来调用，这使得代码出现了某种程度上的不对称。std::make_shared 就能够用来消除显式的使用 new，
所以std::make_shared 会分配创建传入参数中的对象， 并返回这个对象类型的std::shared_ptr指针。


void foo(std::shared_ptr<int> value)
{
    (*value)++;
}

int main(int argc, char **argv)
{
    // auto pointer = new int(10); 
    // illegal, no direct assignment
    // Constructed a std::shared_ptr
    auto pp = std::make_shared<int>(10);
    foo(pp);
    std::cout << *pointer << std::endl; // output 11
    // The shared_ptr pp will be destructed before leaving the scope

    // std::shared_ptr 可以通过 get() 方法来获取原始指针，通过 reset() 来减少一个引用计数， 并通过 use_count() 来查看一个对象的引用计数
    auto pointer = std::make_shared<int>(10);
    auto pointer2 = pointer; // 引用计数+1
    auto pointer3 = pointer; // 引用计数+1
    int *p = pointer.get(); // 这样不会增加引用计数
    std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl; // 3
    std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 3
    std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 3

    pointer2.reset();
    std::cout << "reset pointer2:" << std::endl;
    std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl; // 2
    std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 0, pointer2 已 reset
    std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 2
    pointer3.reset();
    std::cout << "reset pointer3:" << std::endl;
    std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl; // 1
    std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 0
    std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 0, pointer3 已 reset

    return 0;
}


// !! std::unique_ptr

std::unique_ptr 是一种独占的智能指针，它禁止其他智能指针与其共享同一个对象， 从而保证代码的安全

std::unique_ptr<int> pointer = std::make_unique<int>(1);

std::unique_ptr<int> pointer2 = pointer;

make_unique 并不复杂，C++11 没有提供 std::make_unique，可以自行实现

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args ) {
  return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

// !! 至于为什么没有提供，C++ 标准委员会主席 Herb Sutter 在他的博客中提到原因是因为『被他们忘记了』

既然是独占，换句话说就是不可复制。但是我们可以利用 std::move 将其转移给其他的 unique_ptr

struct Foo 
{
    Foo() { std::cout << "Foo::Foo" << std::endl; }
    ~Foo() { std::cout << "Foo::~Foo" << std::endl; }
    void foo() { std::cout << "Foo::foo" << std::endl; }
};

void f(const Foo &) 
{
    std::cout << "f(const Foo&)" << std::endl;
}

int main()
{
    std::unique_ptr<Foo> p1(std::make_unique<Foo>());
    // p1 不空, 输出
    if (p1)
    {
        p1->foo();
    }

    {
        std::unique_ptr<Foo> p2(std::move(p1));
        // p2 不空, 输出
        f(*p2);
        // p2 不空, 输出
        if (p2)
        {
            p2->foo();
        }
        // p1 为空, 无输出
        if (p1)
        {
            p1->foo();
        }
        p1 = std::move(p2);
        // p2 为空, 无输出
        if (p2)
        {
            p2->foo();
        }
        std::cout << "p2 被销毁" << std::endl;
    }

    // p1 不空, 输出
    if (p1)
    {
        p1->foo();
    }
    // Foo 的实例会在离开作用域时被销毁
}


// !! std::weak_ptr

如果你仔细思考 std::shared_ptr 就会发现依然存在着资源无法释放的问题。

struct A;
struct B;

struct A
{
    std::shared_ptr<B> pointer;
    ~A()
    {
        std::cout << "A 被销毁" << std::endl;
    }
};

struct B
{
    std::shared_ptr<A> pointer;
    ~B()
    {
        std::cout << "B 被销毁" << std::endl;
    }
};

int main()
{
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    a->pointer = b;
    b->pointer = a;
}

运行结果是 A, B 都不会被销毁，这是因为 a,b 内部的 pointer 同时又引用了 a,b，这使得 a,b 的引用计数均变为了 2，而离开作用域时，a,b 智能指针被析构，
却只能造成这块区域的引用计数减一，这样就导致了 a,b 对象指向的内存区域引用计数不为零，而外部已经没有办法找到这块区域了，也就造成了内存泄露。


解决这个问题的办法就是使用弱引用指针 std::weak_ptr，std::weak_ptr是一种弱引用（相比较而言 std::shared_ptr 就是一种强引用）。


// !! 智能指针这种技术并不新奇，在很多语言中都是一种常见的技术，现代 C++ 将这项技术引进，在一定程度上消除了 new/delete 的滥用，是一种更加成熟的编程范式。