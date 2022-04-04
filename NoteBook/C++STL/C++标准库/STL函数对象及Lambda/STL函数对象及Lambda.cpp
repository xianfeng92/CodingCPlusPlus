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

