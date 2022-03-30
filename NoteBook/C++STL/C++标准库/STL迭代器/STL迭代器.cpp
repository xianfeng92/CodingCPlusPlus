// !! STL 迭代器


// !! Header Files for Iterators


'所有容器都定义有各自的 iterator 类型, 所以当你打算使用某种容器的 iterator 时, 不必包含什么特殊的头文件'。不过有些特别的 iterator, 例如 reverse 
iterator, 以及若干辅助的 iterator 函数, 被定义于头文件 <iterator> 中。有些实现将所有容器都包含在这个头文件中,用来定义其 reverse iterator 类型。然而这
不具可移植性。因此,当你需要比寻常的 container iterator 和其类型更多东西时, 你应该包含这个头文件。


// !! Iterator Category

Iterator 是一种能够迭代某序列(sequence)内所有元素的对象, 可通过改编自寻常 pointer 的一致性接口来完成工作。'Iterator 奉行一个纯抽象概念: 任何东西,只要行为
类似 iterator, 就是一种 iterator'。然而不同的 iterator 具有不同的能力 (指的是其行进能力)。这很重要, 因为某些算法需要特殊的 iterator 能力。例如 Sorting
算法需要的 iterator 必须能够执行 random access, 否则效能很糟。由于这个原因, 迭代器被分为不同的类型。

迭代器种类及其能力:

Output 迭代器  能力:向前写入   Ostream, inserter

Input 迭代器   能力:向前读取一次 Istream

Forward 迭代器   能力:向前读取  Forward List Unordered Container

双向迭代器   能力:向前或向后读取

Random-access 迭代器 能力:以随机访问方式读取  array vector deque string C-style array

// !! Output 迭代器

Output 迭代器允许一步一步前行并搭配 write 动作。因此你可以一个一个元素地赋值,不能使用 output 迭代器对同一区间迭代两次。事实上, 甚至不保证你可以将一个
value 赋值两次而其迭代器却不累进。我们的目标是将一个 value 以下列方式写入一个"黑洞":

while (true){
    *pos = ...;//assign a value
    ++pos;//   advance
}

'Output 迭代器的操作'

*iter = val;// 将 val 写置迭代器所在位置
++iter;// step forward, 返回新位置
iter++;// step forward, 返回旧位置
TYPE(iter);// 复制迭代器(copy constructor)

Output 迭代器无须比较 (comparison) 操作。你无法检验 output 迭代器是否有效, 或写入是否成功。你唯一可做的就是写入、写入、再写入。通常, 一批写入动作是以
一个"由额外条件定义出"的特定 output 迭代器作为结束。

通常, 迭代器可用来读,也可用来写;几乎所有 reading 迭代器都有 write 的额外功能,  这种情况下它们被称为 mutable (可产生变化的) 迭代器。

'一个典型的 pure output 迭代器例子是:将元素写至标准输出设备(例如屏幕或打印机)'。如果采用两个 output 迭代器写至屏幕, 第二个字将跟在第一个字后面,而不是覆
盖(overwrite) 第一个字。另一个典型例子是 inserter, 那是一种用来将 value 插入容器内的迭代器:如果你赋值(assign)一个value, 你其实是将它插入容器。如果随
后写入第二个 value,并不会覆盖第一个 value, 而是安插进去。



// !! Input 迭代器


'Input 迭代器只能一次一个以前行方向 (forward) 读取元素, 按此顺序一个个返回元素值'。


'Input 迭代器的各项操作'


*iter;// 读取实际元素
iter->member;// 读取实际元素的成员 
++iter;// step forward, 返回新位置
iter++;// step forward, 返回旧位置

iter1 == iter2;// 判断两个迭代是否相等
iter1 != iter2;// 判断两个迭代是否不相等

TYPE(iter);// 复制迭代器(copy constructor)


Input 迭代器只能读取元素一次。如果你复制 input 迭代器,并令原 input 迭代器和新产生的拷贝都向前读取,可能会遍历到不同的值。


所有迭代器都具备 input 迭代器的能力, 而且往往更强。'Pure input 迭代器的典型例子就是从标准输入设备(往往是键盘)读取数据'。同一个值不会被读取两次。一旦从
input stream 读入一个字(离开 input 缓冲区), 下次读取时就会返回另一个字。


'对于 input 迭代器, 操作符 == 和 = 只用来检查某个迭代器是否等于一个 past-the-end 迭代器'。这有其必要, 因为处理 input 迭代器的操作函数通常会有以下行为:

InputIterator beg,end;
...
while(beg != end)
{
    ...// read-only access using  *pos
    ++pos;
}

没有任何保证说, 两个迭代器如果都不是  past-the-end 迭代器, 且指向不同位置, 它们的比较结果会不相等。

也请注意,  input 迭代器的后置式递增操作符 iter++  并不一定得返回什么东西。不过通常它会返回旧位置。

'你应该尽可能优先选用前置式递增操作符 (++iter) 而非后置式递增操作符 (iter++), 因为前者效能更好'。



// !! Forward 迭代器

Forward 迭代器是一种 input 迭代器且在前进读取 (reading forward) 时提供额外保证。


'Forward 迭代器的各项操作'

*iter;// 读取实际元素
iter->member;// 读取实际元素的成员 
++iter;// step forward, 返回新位置
iter++;// step forward, 返回旧位置

iter1 == iter2;// 判断两个迭代是否相等
iter1 != iter2;// 判断两个迭代是否不相等

TYPE(iter);// 复制迭代器(copy constructor)
iter1 = iter2;// 对迭代器进行复制


和 input 迭代器不同的是, 两个 forward 迭代器如果指向同一元素, operator==  会获得 true, 如果两者都递增, 会再次指向同一个元素。

ForwardIterator pos1,  pos2;
pos1 =  pos2 = begin;// both iterator reference to same element

if(pos1 != end){
    ++pos1;
    while(pos1 != end){
        if(*pos1 == *pos2){
            ...
            ++pos1;
            ++pos2;
        }
    }
}


Forward 迭代器由以下对象和类型提供:

class forward_list<>。

unordered container

然而标准库也允许 unordered 容器的实现提供 bidirectional 迭代器。如果 forward 迭代器履行了 output 迭代器应有的条件, 那么它就是一个 mutable forward
迭代器, 既可用于读取, 也可用于涂写。



// !! Bidirectional (双向)迭代器


Bidirectional 迭代器在 forward 迭代器的基础上增加了回头迭代 (iterate backward) 能力。换言之, 它支持递减操作符, 可一步一步后退。

Bidirectional 迭代器的新增操作:

--iter;// 步退
iter--;


Bidirectional 迭代器由以下的对象和类型提供:

class list<>

associated container



// !! Random-Access (随机访问)迭代器

Random-access 迭代器在 bidirectional 迭代器的基础上增加了随机访问能力。因此它必须提供 iterator 算术运算 (和寻常 pointer 的算术运算相当)。
也就是说, 它能增减某个偏移量、计算距离 (difference), 并运用诸如 < 和 > 等关系操作符 (relational operator) 进行比较。


Random-Access 迭代器的新增操作


iter[n];// 访问索引位置为 n 的元素
iter += n; // 前进 n 个元素
iter -= n; // 后退 n 个元素

iter +  n; // 返回 iter 之后的第 n 个元素

iter1 - iter2;// 返回 iter1 和 iter2 之间的距离
iter1 < iter2;// 判断 iter1 是否在 iter2 之前


Random-access 迭代器由以下对象和类型提供:

1. 可随机访问的容器 (array、vector、deque)

2. String

3. 寻常的C-style array (pointer)


以下程序说明了 random-access 迭代器的特殊能力:


#include <vector>
#include <iostream>

using namespace std;


int main(int argc, char** argv){
    vector<int> coll;

    for(int i = -3; i < 9; i++){
        coll.push_back(i);
    }

    cout << "number distance: " << coll.end() - coll.begin() << endl;

    vector<int>::iterator pos;
    for(pos = coll.begin(); pos != coll.end();++pos){
        cout << *pos << endl;
    }

    cout << endl;

    for(int i = 0; i < coll.size(); i++){
        cout << coll.begin()[i] << endl;
    }

    for(pos = coll.begin(); pos < coll.end()-1;pos += 2){
        cout << *pos << endl;
    }
    return 0;
}


特别请注意, 只有在面对 random-access 迭代器时, 你才能以 operator< 作为循环结束与否的判断准则。

如果容器为空, coll.end() -1 便会位于 coll.begin() 之前。虽然如此一来上述比较动作可能仍然有效, 但严格说来，将迭代器移至起点更前面会导致不明确行为。
同样道理, 如果表达式 pos+=2 将迭代器移至 end() 之后, 也会导致不明确行为。




// !! Vector 迭代器的递增(Increment)和递减(Decrement)


