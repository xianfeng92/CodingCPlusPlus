//!! STL 函数对象及 Lambda

本章详细介绍如何传递特定机能给算法和成员函数, 我们用的是所谓 function object(函数对象), 或简称 functors(仿函数)。


// !! Function Object(函数对象)的概念

所谓 function object (或者说functor), 是一个定义了 operator() 的对象。

FunctionObjectType po;
...
fo();

中表达式 fo() 调用的是 function object fo 的 operator(), 而非调用函数 fo()。你可以将 function object 视为一般函数,只不过用的是一种更复杂的撰写手段,
并非将所有语句放在函数体中:

void fo(){
    statement
}

而是在 function object class 的 operator() 内撰写代码:

class FunctionObjectType{
    public:
        void operator(){
            statement
        }
};


这种定义形式更为复杂, 却有三大优点:


1. Function object 比一般函数更灵巧(smarter), 因为它可以拥有状态(state)。事实上, 对于相同的 function object class 你可以拥有两个状态不同的实例
   (instance), 寻常的函数无法做到这一点。

2. 每个 function object 都有其类型。因此你可以将 function object 的类型当作 template 参数传递, 从而指定某种行为。还有一个好处:容器类型也会因为 
   function object 的不同而不同。

3. 执行速度上, function object 通常比 function pointer 更快



// !! 以 Function Object 为排序准则

程序员经常需要将某些 class object 以排序(sorted)状态置入容器(例如一个 Person 集合)。然而, 或许因为不想,或许因为不能,你无法使用一般的 
operator< 对这些对象排序, 你必须以某种特别规则(通常基于某些成员函数)来排序。此时 function object 可以派上用场, 试看下例:

#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;


class Person{
    public:
        string firstname() const;
        string lastname() const;
        ...
};

class PersonSortCriteria{
    public:
        bool operator()(const Person& a, const Person& b) const{
            return a.firstname() < b.firstname() || (a.firstname() == b.firstname() && a.lastname() < b.lastname());
        }
};

int main(int argc, char **argv){

    set<Person,PersonSortCriteria> coll;
    ...
    for(auto pos = coll.begin(); pos != coll.end(); ++pos){
        ...
    }
    ...

    return 0;
}


这里的 set coll 使用特殊排序准则 PersonSortCriterion, 而它正是一个 function object class。

PersonSortCriterion 这么定义 operator(): 先比较两人的姓, 如果相等再比较其名。coll 构造函数会自动产生 class PersonSortCriterion 的一个实例
(instance), 所有元素都将以此为排序准则进行排序。



// !! Function Object 拥有内部状态(Internal State)

下面展示 function object 如何能够"行为像个函数同时又拥有多个状态":

#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

#include "print.hpp"

using namespace std;

class IntSequence{
private:
    int value;
public:
    IntSequence(int initialValue):value(initialValue){

    }
    int operator(){
        return ++value;
    }
};

int main(int argc, char ** argv){

    list<int> coll;
    
    // start; number of elements;  generate values starting with 1
    generate_n(back_inserter(coll), 9, IntSequence(1));

    PRINT_ELEMENTS(coll);

    //  generate values starting with 42
    generate_n(next(coll.begin()),prev(coll.end()), IntSequence(42));

    PRINT_ELEMENTS(coll);

    return 0;
}


本例以 function object IntSequence 生成一个整数序列。每当其 operator() 被调用, 就返回一个整数值。至于初值, 可通过构造函数的实参加以指定。


本例有两个这样的 function object, 分别被 generate() 和 generate_n() 算法使用。这两个算法的作用是产生数值并写入容器:

generate_n(back_inserter(coll), 9, IntSequence(1));

中的表达式:

IntSequence(1);

便是以 1 为初值产生这么一个 function object。generate_n() 算法前后共 9 次运用它写入元素值, 而它也实实在在地产生了数值 2~10。同样道理,以下表达式:

同样道理, 以下表达式:

IntSequence(42);

会产出以 42 为初值的 function object。

默认情况下 function object 是 passed by value, 不 是passed by reference, 因此算法并不会改变 function object 的状态。例如以下产生的两个
function object 都从 1 开始:


IntSequence seq(1);

// insert sequence begin with value 1
generated_n(back_inserter(coll), 9 , seq);

// insert sequence begin with value 1 again
generate_n(back_inserter(coll), 9, seq);



将函数对象以 by value (而非by reference) 传递的好处是, 你可以传递常量表达式或暂态表达式。


至于缺点就是, 你无法改变 function object 的状态。算法当然可以改变 function object 的状态, 但你无法取得并处理其最终状态, 因为算法所改变的只是
function object 的拷贝(副本)而已。然而有时候我们的确需要其最终状态,问题在于如何从一个算法中获得运算后的"结果"。


有三个办法可以从"运用了 function object"的算法中获取"结果"或"反馈":

1. 在外部持有状态, 并让 function object 指向它

2. 以 by reference 方式传递 function object

3. 利用 for_each() 算法的返回值


为了以 by reference 方式传递 function object, 你需要在调用算法时明白标示 function object 是个 reference 类型。例如:

#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

#include "print.hpp"

using namespace std;

class IntSequence{
private:
    int value;
public:
    IntSequence(int initialValue):value(initialValue){

    }
    int operator(){
        return ++value;
    }
};

int main(int argc, char** argv){

    list<int> coll;
    IntSequence seq(1);

    // insert value from 1 to 4
    // pass function object by reference
    // so that will continue with 5
    generate_n<back_insert_iterator<int>, int, IntSequence&>(back_inserter(coll), 4, seq);
    PRINT_ELEMENTS(coll);

    // insert value from 42 to 45
    generate_n(back_inserter(coll),4, IntSequence(42));
    PRINT_ELEMENTS(coll);
    // so that will continue with 5
    generate_n(back_inserter(coll), 4,seq);
    PRINT_ELEMENTS(coll);

    generate_n(back_inserter(coll), 4 , seq);
    PRINT_ELEMENTS(coll);

    return 0;
}

第一次调用 generate_n() 时 function object seq 是以 by reference 方式传递。是的, 只需将 template 实参明白标示, 就可以达到这个效果:


generate_n<back_insert_iterator<int>, int, IntSequence&>(back_insert(coll), 4, seq);

调用之后, seq 内部值被改变了。第三次调用 generate_n() 时再度使用 seq, 这次产生的序列会接续第一次调用所产生的序列。然而这个调用系以 by value 方式来传
递 seq:


generated_n(back_inserter(coll), 4 , seq);


// !! for_each() 的返回值

如果你使用的算法是 for_each(), 那就不必特别费神以 by reference 方式传递 function object 来获得其最终状态。for_each() 有一个独门绝技, 其他算法概莫
有之, 就是可以传回其 function object。于是你可以通过 for_each() 的返回值来获取 function object 的状态。


下面是一个使用 for_each() 返回值的极佳例子,用来处理一个序列的平均值:

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class MeanValue{
private:
    long num;
    long sum;
public:
    MeanValue():num(0),sum(0) {}

    void operator(int elem){
        ++num;
        sum += elem;
    }

    double value(){
        return static_cast<double>(sum) / static_cast<double>(num);
    }
};

int main(int argc, char **argv){

    vector<int> coll = {0,1,2,3,4,5,6,7,8,9};
    MeanValue mean = for_each(coll.begin(), coll.end(),MeanValue());

    cout << "mean.value() is " << mean.value() << endl;

    return 0;
}


其中的表达式:

MeanValue()

会产生一个 function object 用来记录元素数量, 并计算元素总和。将此 function object 传给 for_each(), 后者便针对容器 coll 内的每一个元素调用 
function object:

MeanValue mv = for_each(coll.begin(), coll.end(),MeanValue());

返回的 function object 被赋值给 mv, 此后你可以调用 mv.value() 查询其状态。



// !! Predicate(判断式) vs.Function Object(函数对象)

所谓 predicate (判断式), 就是返回 Boolean 值(意指任何可转为 bool 的值)的函数或 function object。对 STL 而言并非所有返回 Boolean 值的函数都是合法的
predicate。这可能会导致出人意料的行为。试看下例:

#include <iostream>
#include <list>
#include <algorithm>

#include "print.hpp"


using namespace std;


class Nth{
private:
    int nth;
    int count;
public:
    Nth(int n):nth(n), count(0){}

    bool operator()(int){
        return ++count == nth;
    }
};

int main(int argc, char** argv){

    list<int> coll = {1,2,3,4,5,6,7,8,9,10};
    PRINT_ELEMENTS(coll);

    list<int>::iterator pos;
    pos = std::remove_if(coll.begin(), coll.end(),Nth(3));
    coll.erase(pos);
    PRINT_ELEMENTS(coll,"3th removed");

    return 0;
}


这个程序定义了一个 function object Nth, 当它第 n 次被调用时会返回 true。然而如果你把它传给 remove_if()--此算法会把每一个"令单参数判断式结果为true"
的元素移除。


output: 1 2 3 4 5 6 7 8 9 10

3th removed: 1 2 4 5 7 8 9 10

两个元素--也就是第3和第6个元素——被移除了! 为什么这样? 因为该算法的常见做法会在其内部保留 predicate 的一份拷贝(副本):

template<typename ForwIter, typename Predicate>
ForwIter std::remove_if(ForwIter begin, ForwIter end, Predicate op){
    beg = find_if(beg,end op);
    if(beg == end){
        return beg;
    }else{
        ForwIter next = beg;
        return remove_copy_if(++next,end, beg, op);
    }
}


这个算法使用 find_if() 查找应被移除的第一个元素。然而, 接下来它使用传入的 predicate op 的拷贝去处理剩余元素, 这时原始状态下的 Nth 再次被使用,因而会移
除剩余元素中的第 3 个元素, 也就是整体的第 6 个元素。

这种行为不能说是一种错误, 因为 C++standard 并未明定 predicate 是否可被算法复制一份拷贝。因此, 为了获得 C++ 标准库的保证行为,你传递的 function object 
其行为"不应该因被复制次数或被调用次数而异"。也就是说, 如果你以两个相同的实参调用同一个 unary predicate, 该式应该总是返回相同结果。


'换句话说, predicate 不应该因为被调用而改变自身状态; predicate 的拷贝应该和其正本有着相同状态'。要达到这一点, 你一定得保证不能因为函数调用而改变 predicate
的状态, 你应当将 operator() 声明为 const 成员函数。

其实我们完全可以避免这种尴尬结果, 让算法和 Nth 这样的 function object 一起正常运作, 而且效率不打折扣。你可以这么实现 remove_if(), 直接以其 find_if()
的内容替换其调用:


template <typename ForwIter, typename Predicate>
Forward remove_if(ForwIter beg, ForwIter end, Predicate op){

    while(beg != end && !op(*beg)){
        ++beg;
    }
    if(beg == end){
        return beg;
    }
    else{
        ForwIter next = beg;
        return remove_copy_if(++next, end, beg, op);
    }
}

注意, 如果采用 lambda, 你可以让 function object 的每一个拷贝共享状态, 这个问题就不会发生。



// !! 预定义的 Function Object 和 Binder

C++ 标准库提供了许多预定义的 function object 和 binder, 后者允许你合成更多精巧的 function object。我们称之为机能合成(functional composition)的能
力, 其所要求的基础 function object 和 adapter 都在本节呈现。欲使用它们, 你必须首先包含头文件<functional>:

#include <functional>


// !! 预定义的 Function Object


下面是所有预定义的 function object, 其中 bit_and、bit_or 及 bit_xor 始自 C++11。


negate<type>(); // - param
plus<type>(); // param1 + param2
minus<type>(); // param1 - param
multiplies<type>(); // param1 * param2
divides<type>();// param1 / param2
modules<type>(); // param1 % param2

equal_to<type>(); // param1 == param2
not_equal_to<type>(); // param1 != param2
less<type>(); // param1 < param2
less_equal<type>(); // param1 <= param2
greater<type>(); // param1 > param2
greater_equal<type>(); // param1 >= param

logical_not<type>(); // !param1
logical_and<type>(); // param1 && param2
logical_or<type>(); // param1 || param2

bit_and<type>(); // param1 & param2
bit_or<type>(); // param1 | param2
bit_xor<type>(); // param1 ^ param2


对对象排序或比较(用于排序函数和 associative 容器)时, 默认以 less<> 为比较准则, 因此默认的排序操作总是产生升序(也就是 element < nextElement)。
Unordered 容器的默认相等性准则是 equal_to<>。


// !! Function Adapter 和 Binder

所谓 function adapter (函数适配器), 是指能够将不同的 function object (或是和某值或某寻常函数) 结合起来的东西, 它自身也是个 function object。


自 C++11 开始,C++ 标准库提供的 function adapter。

bind(op, args...);// 将 args 绑定给 op

mem_fn(op);// 调用 op， 把它当做某个 Object 的成员函数


最重要的 adapter 就是 bind()。它允许你:

1. 在既有的或预定义的 function object 之外另配接及合成(adapt and compose) 新的 function object。

2. 调用全局函数(global function)

3. 针对 object、pointer to object 和 smart pointer to object 调用成员函数


// !! bind() Adapter

一般而言 bind() 用来将参数绑定于可调用对象(callable object)。

因此, 如果一个函数、成员函数、函数对象(function object) 或 lambda 需要若干参数, 你可以将参数绑定为"明白指出的"或"被传入的"实参。欲明白指出实参,
你只需写出其名称, 欲使用被传入的实参, 则可利用预定义占位符 _1、_2、..., 它们被定义于命名空间 std::placeholders 内。

Binder 的一个典型应用是, 当使用C++ 标准库提供之预定义 function object 时具体指定参数。例如:

#include <functional>
#include <iostream>

using namespace std;

int main(int argc, char** argv){

    auto plus10 = std::bind(std::plus<int>(), std::placeholder::_1, 10);
    std::cout << "+10    " < plus10(7) << std::endl;

    auto plus10times2 = std::bind(std::multiplies<int>,(std::bind(std::plus<int>(), std::placeholder::_1, 10), 2);
    std::cout << "+10 * 2 " < plus10times2(100) << std::endl;

    auto pow3 = std::bind(std::multiplies<int>(),std::bind(std::multiplies<int>(),std::placeholder::_1,std::placeholder::_1), std::placeholder::_1);
    cout << pow3 << std::endl


    auto inverseDevide = std::bind(std::divide<double>(), std::placeholder::_2, std::placeholder::_1);

    cout << inverseDevide(49,7) << std::endl;

    return 0;
}

这里出现四个不同的 binder, 分别定义出不同的 function object。例如 plus10 定义为:

std::bind(std::plus<int>(), std::placeholder::_1, 10);

它所表现的 function object 内部调用 plus<> (也就是 operator+), 以占位符(placeholder_1 作为第一参数/操作数, 以 10 作为第二参数/操作数。'占位符 _1 表示
实际传入此表达式之第一实参'。于是,对于传给此表达式之任何实参, 这个 function object 会产出"实参+10"的结果值。


为了避免沉闷而令人生厌地重复写出命名空间 placeholders, 你可以使用对应的 using 指示符。有了以下两个 using 指示符, 就可以缩短整个语句如下:

using namespace std;
using namespace std::placeholders;

bind(plus<int>(),_1,10);

也可以直接调用 binder 而不必先为它建立一个对应的 function object。例如:


std::cout << bind(plus<int>(),_1,10)(7) << std::endl;


本例的其他语句示范如何嵌套合成更复杂的 function object。

例如下列表达式定义了一个 function object, 把 10 加在被传入的实参身上,再将结果乘以2:

bind(multiplies<int>(),bind(plus<int>(),_1,10), 2);


如你所预期, 表达式的核定 (evaluated) 次序是由内而外。


// !! 调用全局函数


下面的例子示范了 bind() 如何被用来调用全局函数:

#include <iostream>
#include <algorithm>
#include <iostream>
#include <functional>
#include <locale>
#include <string>

using namespace std;
using namespace std::placeholders;

char myToUpper(char c) {
    std::locale loc;
    return std::use_facet<std::ctype<char>>(loc).toupper(c);
}

int main(int argc, char ** argv){

    string s("Internationalization");
    string sub("Nation");

    string::iterator pos;
    pos =search(s.begin(), s.end(), bind(equal_to<char>(),bind(myToUpper,_1), bind(myToUpper,_2)));

    if(pos != s.end()){
        cout << "\"" << sub << "is part of " << s << endl;
    }
    
}

这里我们使用 search() 算法检验 sub 是否为 s 的一个子字符串,大小写不计。有了以下:

bind(equal_to<char>(),bind(myToUpper,_1), bind(myToUpper,_2))

便是建立一个 function object 并相当于调用:

myToUpper(param1) == myToUpper(param2)


其中 myToupper() 是我们自己写的一个便捷函数, 用来将 string 内的字符转为大写

请注意, bind() 内部会复制被传入的实参。若要改变这种行为, 让 function object 使用一个 reference 指向被传入之实参, 可利用 ref() 或 cref()。例如:


void incr(int& i){
    ++i;
}

int i = 0;
bind(incr,i)();// increment a copy of i, no effect for i
bind(incr, ref(i))();// incrent i



// !! 调用成员函数
