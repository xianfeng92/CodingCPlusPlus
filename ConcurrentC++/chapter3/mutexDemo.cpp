#include<thread>
#include<algorithm>
#include<list>
#include<functional>
#include<mutex>
#include<exception>
#include<memory>//  For std::shared_ptr<>



// !! std::mutex 和 std::lock_guard 都在 <mutex> 头文件中声明

// !! 避免恶性条件竞争
// 最简单的办法就是对数据结构采用某种保护机制，确保只有进行修改的线程才能看到不变量被破坏时的中间状态
// !! 保护共享数据结构的最基本的方式，是使用 C++ 标准库提供的互斥量(mutex)

// 互斥量是 C++ 中一种最通用的数据保护机制，但它不是“银弹”；精心组织代码来保护正确的数据，并在接口内部避免竞争条件是非常重要的。
// 但互斥量自身也有问题，也会造成死锁，或是对数据保护的太多(或太少)


// C++ 标准库为互斥量提供了一个 RAII 语法的模板类 std::lack_guard，其会在构造的时候提供已锁的互斥量，并在析构的时候进行解锁，
// 从而保证了一个已锁的互斥量总是会被正确的解锁

using namespace std;

std::list<int> some_list;

std::mutex some_mutex；


void addToList(int value) 
{
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(value);
}

bool list_contains(int value_to_find) const
{
    std::lock_guard<std::mutex> guard(some_mutex);
    return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}


class some_data
{
    int a;
    std::string b;

    public:
    void do_something();
};

class data_wrapper
{
    private:
    // 互斥资源
    some_data data;
    std::mutex m;
    public:
    template<typename Function>
    void processData(Function func)
    {
        std::lock_guard<std::mutex> guard(m);
        func(data);
    }
};

some_data* unprotected;

// !! 切勿将受保护数据的指针或引用传递到互斥锁作用域之外，无论是函数返回值，还是存储在外部可见内存，亦或是以参数的形式传递到用户提供的函数中去
void malicious_function(some_data& data)
{
    // !! 以参数的形式传递到用户提供的函数中去
    unprotected = &data;
}

data_wrapper x;

void foo()
{
    x.processData(malicious_function);
    unprotected->do_something();
}



template<typename T, typename Container = std::deque<T>>

class Stack
{
    public:
    explicit Stack(const Container &);
    explicit Stack(const Container&& = Container());
    template<class Alloc> explicit Stack(const Alloc&);
    template<class Alloc> explicit Stack(const Container &, const Alloc&);
    template<class Alloc> explicit Stack(Container&&, const Alloc&);
    template<class Alloc> explicit Stack(Stack&&,const Alloc&);

    bool empty() const;
    size_t size() const;
    T& top();
    T const& top() const;
    void push(T const&);
    void push(T&&);
    void pop();
    void swap(Stack&&);
}；


int main(int argc, char **argv)
{
    // !! 以下是单线程安全代码：对一个空栈使用 top() 是未定义行为
    Stack<int> s;
    if(!s.empty())
    {
        const int value = s.top();
        s.pop();
        do_something(value);
    }

// 对于共享的栈对象，这样的调用顺序就不再安全了，因为在调用 empty() 和调用 top() 之间，可能有来自另一个线程的 pop() 调用并删除了最后一个元素。
// 这是一个经典的条件竞争，使用互斥量对栈内部数据进行保护，但依旧不能阻止条件竞争的发生，这就是接口固有的问题
// 另一个潜在的条件竞争在调用 top()  和 pop() 之间


// !! 定义线程安全的堆栈
struct empty_stack:std::exception
{
    const char* what() const throw() 
    {
        return "empty stack";
    };
};


template<typename T>

class threadsafe_stack
{
    private:
    std::stack<T> data;
    mutable std::mutex m;

    public:
    threadsafe_stack():data(std::stack<T>())
    {

    }

    threadsafe_stack(const threadsafe_stack& other)
    {
        std::lock_guard<std::mutex> guard(m);
        data = other.data;// 在构造函数体中的执行拷贝
    }


    threadsafe_stack & operator=(const threadsafe_stack& stack) = delete;// 赋值操作被删除

    void push(T value)
    {
        std::lock_guard<std::mutex> guard(m);
        data.push_back(value);
    }

    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> guard(m);
        if(data.empty())// 在调用 pop 前，检查栈是否为空
        {
            throw empty_stack();
        }
        const std::shared_ptr<T> res(std::make_shared<T>(data.top()));// 在修改堆栈前，分配出返回值
        data.pop();
        return res;
    }


    void pop(T& value)
    {
        std::lock_guard<std::mutex> guard(m);
        if(data.empty())
        {
            throw empty_stack();
        }
        value = data.top();
        data.pop();
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> guard(m);
        return data.empty();
    }

};

// !! 一个给定操作需要两个或两个以上的互斥量时，另一个潜在的问题将出现：死锁(deadlock)
// !! 它的最大问题就是由两个或两个以上的互斥量来锁定一个操作

// !! 避免死锁的一般建议，就是让两个互斥量总以相同的顺序上锁：总在互斥量 B 之前锁住互斥量 A，就永远不会死锁

// !! 很幸运，C++ 标准库有办法解决这个问题，std::lock——可以一次性锁住多个(两个以上)的互斥量，并且没有副作用(死锁风险)

class some_big_object;
void swap(some_big_object& lhs, some_big_object& rhs);

class X
{
    private:
    some_big_object some_detail;
    std::mutex m;
    public:
    X(some_big_object const& sd) : some_detail(sd){}
    friend swap(X& lhs, X& rhs)
    {
        // !! 一个互斥量可以在同一线程上多次上锁，标准库中 std::recursive_mutex 提供这样的功能
        if(&lhs == &rhs) return;
        std::lock(lhs.m,rhs.m);
        std::lock_guard<std::mutex> guard_a(lhs.m,std::adopt_lock);
        std::lock_guard<std::mutex> guard_b(rhs.m,std::adopt_lock);
        swap(lhs.some_detail,rhs.some_detail);
    }
};



// !! 避免死锁的进阶指导

1. 一个线程已获得一个锁时，别再去获取第二个锁了
   如果能坚持这个建议，因为每个线程只持有一个锁，锁上就不会产生死锁
   
2. 避免在持有锁时调用用户提供的代码
   因为代码是用户提供的，你没有办法确定用户要做什么；用户程序可能做任何事情，包括获取锁

3. 使用固定顺序获取锁
   当硬性条件要求你获取两个以上(包括两个)的锁，并且不能使用 std::lock 单独操作来获取它们;那么最好在每个线程上，用固定的顺序获取它们获取它们(锁)




}
