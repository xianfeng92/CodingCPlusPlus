#include<iostream>




// !! C++ 11 重大改进

C++11 标准对 C++ 有不少影响深远的改进，其中最重要的便是: 移动语义 (Move Semantics)、智能指针 (Smart Pointers)、哈希表和集合(Hash Maps and Sets)。

// !! 移动语义(Move Semantics)

// !! 通过移动语义，我们可以实现更为细致的内存管理

比如, 从一个之后不再使用的对象复制数据时，我们可以通过移动语义手动回收利用这个对象可以被我们直接利用的内存数据,避免大规模的内存复制操作。这对于移动操作的时间复杂度
是常数时间的情况 (vector，map，unordered_map，string 等标准库对象都是这样)，我们的性能收益是巨大的。那么，问题是我们如何知道一个对象在之后不再使用？ 这就需要
了解右值 (rvalue) 的概念，它表示一个临时的，在之后不能被访问的值。

对于下面的代码，user 是一个左值 (lvalue)，字符串字面量 ”Skywalker”  是一个右值 (rvalue)。我们可以在这行代码运行之后访问 user 变量，但却不能访问到原始的
字符串字面量 ”Skywalker”。

std::string user("Skywalker");

下面给出了复制构造和移动构造的一个示例代码，当要复制的对象是一个右值(rvalue)，会调用移动构造函数，其它情况调用复制构造函数。

// Copy constructor
string(const string &rhs)
{
    allocateSpace(myDataPtr);
    deepcopy(rhs.myDataPtr, myDataPtr);
}

// Move constructor
string(string &&rhd)
{
    myDataPtr = rhs.myDataPtr;
    rhs.myDataPtr = nullptr;
}

// !! 对于一个可引用的变量 (lvalue)，如果我们确定之后不会再使用它，可以使用 std::move 手动将其变为右值参数

有时候，我们还会让对象只能进行移动操作不能进行复制操作。对于被移动的对象，如果没有重新初始化，我们不应该使用它。下面的代码演示了这一个过程，标准库中的 unique_ptr 
类生成的对象就是一个只能移动，不能复制的对象。

MoveOnlyObject a;
// ...
MoveOnlyObject b(a); // ERROR – copy constructor doesn't exist
MoveOnlyObject c(std::move(a)); // OK – ownership transferred to c, a is DEAD now
cout << *a ; // RUNTIME ERROR – illegal access


上面的代码在 a 对象已经被移动后仍然访问了它，这样做的后果是不可预料的。我们可以像下面的代码这样，通过作用域来避免这种情况:

MoveOnlyObject c;

{
    MoveOnlyObject a;
    //...
    c = MoveOnlyObject(std::move(a));
}


另一个需要牢记的地方，在向容器插入对象时，如果临时变量以后不再使用，应该通过 std::move 将其转为右值参数，避免不必要的内存数据复制:

std::vector<string > importantUsers;
std::string localUser;
// compute local User
importantUsers.push_back(std::move(localUser));

需要注意的是位于栈上的内存不能被移动操作复用, 也就是说如果一个类只包含编译器自动维护作用域的变量 (类中的变量都实际在栈中占用了连续的内存块，而不是通过类似指针的方式
引用，如 string 对象因为会使用指针引用动态申请内存可以从移动语义收益，而只包含 char str[50] 的类，不能从移动语义收益。尽管不能收益于移动语义，我们仍可能为这样的类
添加移动构造函数，来使操作它们的代码和其它类的代码看上去是一致的，实际上，编译器会为这样的类自动生成移动构造，我们自己添加是多此一举。

基于此， 对于使用标准库容器 (比如 vector) 的程序来说， 可以认为升级到 C++11 会自动获得一定的性能提升。



// !! 建议

1. 认真思考移动语义是如何影响代码的性能表现

2. 对于不再使用的数据, 使用 std::move() 传递数据的所有权给容器

3. 推荐将需要移动的对象定义在一个作用域中，并且在作用域的最后一行代码移动对象, 从而避免再次使用已经被移动的对象


// !! 智能指针

对于大多数 C++ 程序员来说，最让人头疼的莫过于手动进行内存管理。每个 new，要对应一个 delete，每个 malloc ，要对应一个 free ，每个new []，要对应一个 delete []
。这种对应并非看起来那么简单， 我们需要覆盖所有可能的情况 (包括异常处理)， 即使是 C++ 语言专家写的代码也经常会出现内存泄漏。

为了解决这一问题，C++11 为我们提供了智能指针这一工具。

C++11 提供了 3 种智能指针：unique_ptr， shared_ptr 和 weak_ptr。在 C++11 之前，存在一种叫做 auto_ptr 的智能指针尝试完成现在 unique_ptr 的工作，但因为没
有移动语义的支持而失败。现在 auto_ptr 类型已经被废弃，读者不应该继续使用它。除了这 3 种智能指针，在 C++11中，我们将原先的普通指针变量叫做原生指针 (raw pointers)。


unique_ptr 智能指针只具有移动构造函数，没有复制构造函数，也就是说对象所有权只会在 unique_ptr 智能指针间传递，但不会扩散，可以保证只有一个 unique_ptr 智能
指针拥有对象的所有权， 进而可以保证只有一个 unique_ptr 在析构时调用 delete 语句自动清除对象。使用 unique_ptr 智能指针避免了手动调用 delete 的时机不对引发的问题。

我们应该通过 make_unique (这一功能从 C++14 开始提供) 来生成 unique_ptr 智能指针对象。使用这一功能，只需要一条语句就能完成对象的内存分配，并将其传递给 unique_ptr 
智能指针对象。要比我们自己手动 new，然后设置 unique_ptr 智能指针好很多，它保证了分配对象内存和传递对象给智能指针之前不存在其它可以抛出异常的语句。


char[] buffer = new char[bufferSize];

try {
    doStuff(buffer);
}
catch(...){
    delete[] buffer;
    return;
}

delete[] buffer;


通过使用 unique_ptr 智能指针，我们可以轻松避免上述问题:

// Block not needed but good practice to prevent use of buffer after move

{
    std::unique_ptr<char[]> buffer = make_unique<char[]>(bufferSize);
    try{
        doBuffer(std::move(buffer));// transfer ownership
    }catch(...) {

    }
}

上面的代码也给出了 unique_ptr 智能指针的一个用法:强制传递对象所有权。





int main(int argc, char **argv)
{

}