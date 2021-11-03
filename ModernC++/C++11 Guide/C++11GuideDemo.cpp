#include<iostream>

// !! 一、C++ 11 重大改进

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

shared_ptr 智能指针引用的对象的所有权可以被共享。只要还有一个 shared_ptr 智能指针引用了该对象，这一对象就不会被清除。 shared_ptr 智能指针通过引用计数来维护对象。
对 shared_ptr 智能指针进行复制操作， 其内部的引用计数会加 1， 当 shared_ptr 智能指针被销毁时，其内部的引用计数会减 1。 当引用计数变为 0 时，智能指针引用的对象会
被清除。虽然 shared_ptr 智能指针使用起来非常方便，但一般情况下， 维护引用计数 (共享的引用计数需要额外分配独立的内存空间) 会带来额外的性能损失，我们不应该优先使用它。
下面的代码，给出了一个使用 shared_ptr 智能指针的常见场景:缓存系统。因为缓存系统内部使用的是 shared_ptr 智能指针， 并且用户获取数据获得的也是 shared_ptr，缓存系
统可以安全地在任何时间移除 shared_ptr 智能指针，不需要担心用户无法访问到数据。和使用 unique_ptr 智能指针相同，我们推荐使用 make_shared() 来生成 shared_ptr 
指针对象。

// Simple LRU Cache put() fragment using make_shared()

template<class KEY, class VAL> class

LRUCache::put(const KEY& key, const VAL& value)
{
    //...
    if(!contains(key))
    {
        storage[key] = std::make_shared(value);
    }
    //...
}

std::shared_ptr<LargeObject> localSharedUser = lruCache.get(somekey);

weak_ptr 智能指针也被用来引用共享的对象, 但其对对象的引用计数没有影响。被 weak_ptr 智能指针引用的对象仍然可能被清除; 正因为如此，访问 weak_ptr 智能指针引用的
对象需要先验证对象是否被清除，然后使用 lock() 函数将其转换为一个 shared_ptr 智能指针后再进行使用。通常，我们使用 weak_ptr 智能指针来避免循环引用导致的内存
无法释放。


unique_ptr 智能指针只有一个降落伞，很安全。shared_ptr 智能指针有两个降落伞，虽然也很安全，但代价比 unique_ptr 智能指针高；最后是原生指针，一点都不安全。


// !! 建议

1. 总是使用智能指针，不要直接使用原生指针

2. 对于单一所有权的对象使用 unique_ptr 智能指针; 对于需要共享所有权的对象使用 shared_ptr 智能指针; 对于可能出现的循环引用，使用 weak_ptr 智能指针

3. 总是使用 make_unique()(C++ 14 引入)/make_shared() 来生成智能指针对象 (也就是在对象创建后，立即生成智能指针引用它)

4. 不要继续使用已经废弃的 auto_ptr 智能指针，使用 unique_ptr 智能指针替换它

5. 如果要使用 this 指针生成 shared_ptr 智能指针，应该考虑使用 shared_from_this()。 此外，不应该使用 this 指针生成 unique_ptr 智能指针



// !! 哈希表和集合

无序容器，比如哈希表可以提供 O(1) 时间复杂度的插入，查询和删除操作。我们可以将一个对象的属性进行组合，将其转换为一个整数类型的关键字，然后使用这一关键字作
为键值访问哈希表。C++98 为我们提供了 map 和 set 这两种哈希表的变种， 它们可以提供 O(lgN) 时间复杂度的插入，查询和删除操作 (标准库使用平衡二叉树来实现它们，
所以时间复杂度 不是哈希表的 O(1))。map 和 set 的优点是，它们中所存放的元素的排列是有序的，元素在容器中的位置由元素间进行小于比较运算得到。如果元素在容器中的顺序
对我们不重要，使用无序容器显然是更好的选择。

C++11 为我们提供了 unordered_map 和 unordered_set(还有 un- ordered_multimap 和 unordered_multiset) 等无序容器。我们只需要为容器中存放的对象实现
良好的哈希函数，就可以得到不错的插入，查询和删除操作的性能提升。


下面的代码使用 unordered_map 实现了字符串到整数的映射:

std::unordered_map<std::string, int> usertoindex;


// !! 建议

1. 总是优先使用 std::unordered_map 和 std::unordered_set 作为无序容器，除非其它无序容器可以提供我们所需的额外功能，或是可以带来明显的性能提升

2. 优先使用 std::unordered_map 和 std::unordered_set 作为查询表，除非容器中元素的顺序对我们有用

3. 在某些情况下，比如表中元素较少时，哈希表的操作效率可能不如二叉树，甚至是顺序数组



// !! 二、C++ 11 重大改进

本章介绍的特性对于我们来说非常重要。这些特性可以使我们的工作变得更加轻松，它们有的有利于我们捕获程序 bug，有的让我们的代码变得更简洁，更容易阅读。

// !! 1.代码安全性/错误捕获

C++11 为我们提供了一些新的语言特性使得我们在编译时就可以捕获一些代码逻辑上的错误。


// !! 1.1 nullptr 关键字

NULL 本质上是一个预定义的值为 0 的常量，并非 C/C++ 语言的关键字， 这就造成了一定问题。

1. 不要设置指针变量的值为 0 或 NULL
2. 使用新的 nullptr 关键字代替 NULL


// !! 1.2 override 关键字

子类如果要覆盖父类的函数， 我们需要将父类的函数定义为虚函数 (virtual function)， 子类覆盖对应的虚函数，需要保证它和父类的虚函数完全匹配。很多时候，我们可能会因为
疏忽而没有让两者完全匹配，造成难以察觉到 bug， 比如下面的代码:

class User 
{
    virtual void print();
    virtual string getName() const;
    void performAction(const Action &a); // note: not virtual !
};

class PowerUser : public User
{
    void print();// overrides User::print

    string getName(); // doesn’t override User::getName −missing const

    void performAction(const Action& a); // doesn’t override − base func not virtual
}


C++11 为我们提供了一个新的关键字 override 可以避免这一问题, 使用这一关键字的函数如果没有与之完全匹配的父类虚函数，编译器就会报告错误，我们就可以及时做出修改。


此外，C++11 还为我们提供了 final 关键字， 用于声明函数或类不可被覆盖或继承, 使用这一关键字有助于编译器做出更好的优化。


// !! 建议

1. 覆盖父类虚函数时，总是使用 override 关键字

2. 使用 final 关键字有助于编译器优化 (虽然优化效果不明显)



// !! 1.3 控制类的默认行为

编译器为了方便，会自动生成一些我们没有定义的函数, 比如类的默认构造函数、复制构造函数、赋值运算函数、析构函数等等。

对于复制构造函数来说， 编译器生成的复制构造函数会遍历类的每个成员， 然后执行对应的复制构造函数。

一般来说，使用编译器自动生成的函数是个不错的选择，但有时候我们的一些行为可能导致编译器不会为我们自动生成想要的函数。比如，如果我们自己定义了一个复制构造函数，
编译器就不会再为我们自动生成移动构造函数， 也就享受不到 C++11 带来的潜在的自动的性能提升。

显然，记忆编译器何时会自动生成这些函数，何时不会太过麻烦。

我们可以遵循这样的原则:如果有一个编译器可以自动生成的函数被我们自己定义的， 那么所有其它可以自动生成的函数都应该进行显式标记。C++11 允许我们使用 default 和 delete 
关键字 (default 关键字标记的函数编译器会自动生成，delete 关键字标记的自动生成函数会被编译器移除) 来对编译器可以自动生成的函数进行标记。


class User
{
    User() = default;

    User(const User& other) = default;// accept default copy construction

    User& operator=(const User &) = delete; //disallow copy assignment

    User(User&& other) = default;// accept default move

    User& operator=(const User&& other) = default;// accept default move assignment

    ~User() = default // accept default destructor
}

要么全部，要么一个都不，这一原则也适用于父类包含虚析构函数的情况。通常这种情况下，我们还应该使用 delete 关键字来移除复制构造函数，避免使用子类对象构造父类对象引发的
数据损失。


// !! 建议

我们可以使用下面的原则来避免错误发生:

1. 如果我们只需要编译器自动生成的函数 (大多数情况下)，要么不要对任一函数使用 default 标记，要么对所有函数使用 default 标记

2. 如果我们自己定义了任意一个编译器可以自动生成的函数 (包括虚析构函数)，对于其它自动生成函数，要么我们自己定义它，要么使用 default/delete 对其进行标记

3. 使用 delete 标记子类不需要的父类函数，以及不需要的编译器自动生成的函数 (之前 C++98 通过 private 关键字进行这一工作)


// !! 1.4 array 数组

C++11 为我们带来了 array 数组， 使用它不仅可以像普通的 C 风格数组一样利用栈空间, 还可以利用标准库提供的一些模板算法: 比如 find()， count() 等等。

此外，因为 array 数组是一个类型, 不会有像 C 风格数组一样有被编译器作为一个普通指针传给函数造成的潜在风险。

printMe(User * user) { ... } // prints user pointer
User allUsers [50]; // native C−style array
printMe(allUsers); // OOPS, only the first user is printed

使用 array 数组， 我们可以在编译时就提前发现问题:

array<User, 50> allUsers;
printMe(allUsers); // ERROR − no matching function


// !! 建议

1. 尽量使用 std::array 替代语言自带的固定大小的数组

2. 除非使用 std::array 会带来明显的性能下降

3. 通常在开启常规的编译器优化后， std::array 带来的性能下降非常小，甚至完全没有影响


// !! 1.5 {} 初始化

在之前我们可以使用 = 运算符加上 () 构造函数，或 {} 来对变量进行初始化，但具体在何种情况使用何种方法初始化其实并不简单。C++11 对 {} 初始化进行了扩展，
让它可以用于任意情况的变量初始化。下面是使用 {} 进行变量初始化的三种形式:

std::string name = {"kobe"};
std::string name1{"Kobe"};
std::string name2 = string("Kobe");

目前，C++ 自带的容器都可以接收 std::initializer_list 作为构造函数的参数，我们可以使用 {} 来对容器进行初始化，例子如下:

vector<int> actionIndexes = {1, 2, 3, 4};

map<string , int> nameToIndexMap = { {”Vader” , 1} , {”Skywalker” ,1} };

需要注意的是，初始化列表构造函数会被优先匹配，读者可以考虑下面的代码，第一行代码调用的是普通的构造函数，生成了一个大小为 5 的 vector 对象，第二行代码调用的是
初始化列表构造函数，生成了一个大小为 1，第一个元素为 5 的 vector 对象。

vector<int> v(5) ; // vector of size 5
vector<int> v{5}; // vector with 1 value which is 5



// !! 三、更强大的功能

一般来说，如果某个功能能够为绝大多数开发者带来好处，我们就会在未来将其加入 C++ 标准。

// !! 3.1 constexpr 关键字

现代 C++ 倾向于在编译期就尽可能多地完成代码计算, 直接将计算结果写入最终的二进制代码。这样做之后， 程序运行时所需要实时计算的代码就会少很多，程序在性能表现
上会提高不少。

C++11 引入了 constexpr 关键字，我们可以使用这一关键字来标记能够在编译期预计算的表达式。如果一个表达式被使用 constexpr 进行标记，它的计算不应该依赖于程序 
运行时才能确定的其它变量。

constexpr long long factorial(int n)
{
    return n <= 1 ? 1 : (n * factorial(n - 1));
}

factorial(4); // 24 − computed at compile time!
factorial (someNumber) ; // slower , computed at run time !

// !! 建议

1. 对于静态的 (static)，并且不需要修改的类成员变量使用 constexpr 进行标记，而不是 const; 尽管对于整数类型的变量，两者的意义一样， 但对于其它类型，
   使用 constexpr 更为准确

2. 尽量使用 static constexpr 标记的成员变量来替代 #define 定义的宏， 这样做既可以得到内联代码的好处，又保证了类型安全

3. 如果一个功能的结果可以在编译期预计算， 考虑使用 constexpr 来优化性能表现


// !! 3.2 Lambda 表达式

很多时候，我们可能需要将自定义的函数传递给其它函数。为了简化这一过程，C++11 为我们提供了 Lambda 表达式，可以在原地生成一个函数对象，它的基本形式如下:

[ capture list ] (parameter list ) { function body }

Lambda 表达式的计算结果是一个 std::function 对象。

Lambda 表达式的计算结果是一个 std::function 对象。下面的代码，演示了以往传递自定义函数的方法和使用 Lambda 表达式的方法。可以看出以往方法是传递一个函数指针，
自定义函数的代码和函数调用的地方距离较远，且自定义函数会暴露给其它无关部分。而现在的方法可以在调用函数的地方直接定义函数代码，不需要将自定义的函数暴露给其它无关部分。

// Using named function

bool isLannister(const string& username) 
{
    return username.find(”Lannister”) != string ::npos;
}

int numLannisters = std::count_if(usernames.begin(), usernames.end(), isLannister);

// Using lambda
int numLannisters = std::count_if(usernames.begin(), usernames.end(), [](const string& username){
    return username.find(”Lannister”) != string ::npos;
});


一般来说如果同一个函数被多次作为函数参数使用或者它的代码行数较多, 就不应该使用 Lambda 表达式来定义它。


// !! 建议

1. 在大多数情况下，使用 Lambda 表达式可能会造成代码可读性下降
2. 在下面这些情况考虑使用 Lambda 表达式：
   自定义函数需要访问局部变量，使用 Lambda 表达式要比使用 functor 对象或 std::bind() 更具可读性
   自定义函数的函数体非常简单 
   自定义函数不会被多次使用
3. 使用 Lambda 表达式时:
   不要使用捕捉所有模式 (capture-all modes)，而是在捕捉列表指定需要的变量

为了可读性，建议不要在同一行定义 Lambda 表达式，而是将 Lambda 表达式定义在一个缩进后的新行，并对表达式的函数体缩进一级。


// !! 3.3 原地构造插入

对于很多标准库中的容器, 比如 vector 使用 push_back() 插入一个新元素可能会调用不止一次构造函数。比如下面的代码，字符串字面量首先被作为参数构造了一个局部的 string 
对象，然后 vector 使用复制构造 (copy-construct) 函数生成了一个新的 string 对象，并将其放入了容器尾部。


vector<string> users ;
// first makes string out of ”Draco”, then copy constructs into vector .Slower
users .push_back(”Draco”) ;


更好的选择是使用 emplace_back() 函数，它会直接在 vector 容器的尾部生成对象， 而不是先生成一个临时对象， 然后将其复制到容器，最后清理掉临时对象。

注意: 为了获得性能提升, 使用 emplace_back 应该使用被包含对象的构造函数的参数作为参数， 而不是直接使用被包含对象的一个实例作为参数。

// direct construction in place . Faster
std::vector<std::string> users;
users.emplace_back("Draco");

// !! 建议

下面这些情况，使用 emplace 替换掉 push/insert 可以获得性能表现提升:

1. 我们给插入函数传递的参数的类型和容器中存放的元素的类型不同

2. 容器允许插入的元素和已有元素重复，或着我们能够保证绝大多数情况下插入的元素和容器已有元素不同

3. 插入操作需要构造新对象。通常，除了在 vector，deque 或 string 的中间插入对象外，都满足这一情况


// !! 3.4 并发

C++11 引入的一个重要特性就是对并发操作 (Concurrency) 的支持。 之前因为 C++ 标准并没有直接支持并发操作，人们使用 boost 或者 POSIX 这类第三方库完
成并发操作。现在我们可以使用 C++ 自带的并发 库来完成相关操作。



// !! 3.4.1 线程

C++11 为我们提供了非常简单的方法来创建线程 (thread)，只需要定义一个 std::thread 变量即可。在程序运行时，构造完这个变量线程就自动开始并发执行。线程执行后, 
我们可以使用 join() 来等待它结束执行， 也可以使用 detach() 来将其和创建它的线程分离。另外，我们还可以使用 chrono 库来对线程进行调度, 在特定的时间唤醒线程。
但需要注意的是标准库并没有提供访问操作系统原始线程信息的 API, 比如线程的优先级等等。

下面的代码演示了如何使用 C++11 来创建一个线程，线程在变量构造后会立刻执行。

std::thread workThread(computeStuff);
workThread.join();// pauses until workThread completes

C++11 还提供了 thread_local 关键字允许我们将变量标记为线程局部变量。顾名思义，线程局部变量私有于单个线程，不同线程访问同一个线程局部变量，实际上访问的是不同
的变量。相同线程访问同一个线程局部变量，访问结果是该线程上次对这一变量的操作结果。可以认为，每个线程都有独立的一份线程局部变量。


// !! 3.4.1 原子变量

多线程并发访问共享数据需要保证线程安全。而实现线程安全的最简单方法就是使用 atomic 库。C++ 自带的整数类型和指针类型都可以通过 atomic 库实现原子操作，其它类型只要
满足 trivially copyable 定义，可以通过 atomic 模板实现来定义它的原子版本。

使用 atomic 模板定义了一个原子变量，对这一变量进行的后缀自增操作保证在多个线程间是原子的

std::atomic<int> latestUserId;

int User::getGlobalUserId()
{
    return latestUserId++;
}


// !! 3.4.2 互斥锁

除了原子变量，对于较长的代码还可以使用 mutex(互斥锁) 来保证并发执行的正确性。当一个线程开始进入临界区，可以使用 mutex 加锁，等线程离开临界区进行解锁，保证临界区
的代码不会同时被多个线程执行。


为了更加可靠还可以结合使用 unique_lock 和 mutex， unique_lock 通过 unique_ptr 来保证在析构时解锁 mutex， 从而避免只使用 mutex 的情况下，临界区代码
抛出异常，mutex 没有解锁而导致的死锁问题。

需要注意的是 mutex 的操作代价较大，应该尽可能使用原子变量，只有在操作比较复杂时使用 mutex

int latestUserId;
std::mutex latestUserIdMutex;

int User::getGlobalUserId()
{
    std::unique_lock<std::mutex> mutexLock(latestUserIdMutex);
    return latestUserId++;
}// mutex is released automatically here


// !! 3.4.3 条件变量

通过条件变量，我们可以将一个线程阻塞， 直到另外一个线程将条件满足。 因为条件变量需要被多个线程访问, 我们需要结合 mutex 或其它并发访问保护措施来使用它


// !! 3.4.4 async

C++11 为我们引入了 async() 使用它我们可以异步调用一个任务，并在未来需要的时候等待结果返回； 相比于使用 thread 进行并发操作，它更方便、能够更好地利用 CPU 资源

在默认调度策略下，调度器可以延迟任务执行，直到我们主动获取任务结果时才执行任务。我们可以将调度策略设置为 launch::async 来避免这一问题。

// !! 3.4.5 future/promise

调用 async() 会返回一个 future 对象, 可以通过这一对象获取异步执行的任务的执行结果。因为任务是异步执行的，在获取结果时任务未必已经执行完毕，所以我们调用
future.get() 后，调用线程就可能会阻塞等待任务执行完毕。


std::future<int> idFuture = std::async(getGlobalUserId);
int userid = idFuture.get();// waits for getGlobalUserId to return


// !! 建议

并发编程是一个强大的工具，但用起来却非常容易出错。

1. 在考虑使用 thread 前，尝试使用 async() 和 future 对象

2. 为了线程安全，我们可以使用原子变量(场景非常简单的情况下) 和 mutex(处理复杂操作)

3. 使用 future 对象和 promise 对象可以很好地控制线程的执行, 进行线程间的数据同步


// !! 3.4.6 计时工具

C++ 标准通过 chrono 库为我们提供了计时工具。但 C++11 标准的 chrono 库，还不支持时区、UTC 时间、TAI 时间以及日历功能。所以对于需要依赖日历的物理模拟应用，
应该使用其它计时工具。



// !! 建议

1. 使用 C++ 的 chrono 库来代替原来的 C 计时库进行计时
2. 对于依赖日历的物理模拟应用，应该使用其它计时工具


// !! 3.4.7 随机分布生成器

在游戏、自动化测试和模拟程序中我们经常需要用到伪随机数。以往，我们可能会使用 C 的 rand() 函数来生成一个随机数，然后对其进行模运算，从而获得 0 到某个整数范围的
随机数。比如，使用下面的代码可以获得一个 0 到 100 范围内的伪随机数

int randInt = rand() % 101; // C-style

通过这种方法生成的伪随机数并不是在 0 到 100 之间均匀分布的。 对于需要自然随机分布的应用， 比如进行蒙特卡洛模拟，使用这样的伪随机数会得到错误的结果。

C++ 标准现在提供了一个更通用的随机分布生成器，只是使用它相较于使用 rand() 来说较为繁琐，如果随机数的分布不是很重要，读者可以继续使用 rand() 来生成随机数。
下面是使用 C++ 标准自带的随机分布生成器生成 0 到 100 的随机数

std::default_random_engine generator;
std::uniform_int_distribution distribution(0,100);
int randInt = distribution(generator);


// !! 建议

1. 对于随机数的质量要求不高的应用，可以继续使用 C 库的 rand() 来生成伪随机数

2. 对于需要高质量合理分布的随机数的应用，应该使用 C++ 标准带来的 random 库

3. 对于需要高质量随机数的应用，应该使用 PCG 来替换 C++ 标准自带的 std::default_random_engine


// !! 3.5 更好的编码体验

C++11 提供了一些非功能性的语法糖来帮助我们编码。

// !! 3.5.1 auto 关键字

C++11 提供了 auto 关键字来方便我们通过赋给变量的初始值的类型来确定变量的类型。

auto hero = new User("hero");
User hero = new User("hero");

类型自动推导对于类型名称特别长的情况特别适用:

unordered_map<string , User >:: const_iterator userIt = userLookupMap.find("hero");

auto userId = userLookupMap.find("hero");

另一种比较常见的用法是在 for 循环中使用类型自动推导

for (const auto& user：users) { ... }


使用 auto 关键字定义变量有许多好处： 减少需要键入的代码、强迫人们必须对变量进行初始化、方便以后重构代码、减少类型转换 bug 等等。
另外，在编写部分模板代码、Lambda 表达式代码时，如果没有 auto 关键字，写起来也要麻烦许多

需要注意的是使用 auto 关键字会降低代码可读性。考虑变量类型大量被 auto 关键字代替，人们想要得知类型信息可能需要跳转多个源文件
此外，auto 关键字也会降低 IDE(集成开发环境) 对变量类型的识别，从而造成 IDE 的智能提示失效。


// !! 建议

在下面这些情况可以使用 auto 关键字让编译器自动推导变量类型

1. 变量类型非常复杂，本身可读性就低

2. 没有合适的类型别名来描述复杂的变量类型

3. 变量的类型对于读代码的人来说非常明显的情况



// !! 3.5.2 枚举类 (Enum Class)

C++11 为我们提供了枚举类 (Enum Class), 它的成员不会被隐式转换为整数类型，可以保证类型安全。当我们需要成员的整数值时，也可以使用 static_cast() 来进行类型转换。

此外，我们需要通过类似 FruitType::APPLE 的形式来访问它的成员，要比枚举类型可以直接以类似 FRUIT_TYPE_APPLE 的形式访问要更好，更不容易出现命名冲突。

我们还可以在枚举类的名称后指定成员的类型。 默认情况下，枚举类的成员的值为 int 类型。

enum class FruitType:int{
    APPLE, ORANGE, PEAR
    };

int numUsers = static_cast<int>(FruitType::APPLE)

// !! 建议

1. 我们可以使用枚举类 (Enum Class) 来保证类型安全，减少命名冲突

2. 我们应该在定义枚举类时给出它的成员的类型，这样做既避免了可能的误用，又减少了内存使用


// !! 3.5.3 基于范围的 for 循环

C++11 为我们提供了一个新的 for 循环语法用于遍历容器。相比于之前遍历容器的方法，使用它更为高效。但需要注意的是，如果我们需要对遍历的容器进行修改，或是需要正在遍历
的元素的索引，可能基于范围的 for 循环就不太适用了。

使用基于范围的 for 循环，我们需要注意下面这些细节:

1. 对于不需要修改的类对象，使用 const & 来接收元素

2. 对于需要修改的容器元素，使用 & 来接收元素

3. 对于元素类型是基本变量类型的，且不需要修改的情况，使用值传递来接收元素


// !! 3.5.4 类型别名

// template ” typedef ” allowed in C++11

template <class T>
using StringMap = std::map<std::string, T>; // Only in C++11

// valid C++98 − confusing
typedef bool (*compare)(int , int);

// valid C++11 − less confusing
using compare = bool (*)(int, int);

// !! 建议使用 using 替代 typedef 来定义类型别名



int main(int argc, char **argv)
{

}