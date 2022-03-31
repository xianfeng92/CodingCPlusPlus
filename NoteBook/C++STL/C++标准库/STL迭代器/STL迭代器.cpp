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

迭代器的递增和递减有个奇怪的问题。一般而言你可以递增或递减临时性迭代器, 但对于 array、vector 和 string 就不行(在某些编译平台上)。

考虑下面的例子：


std::vector<int> coll;
...
if(coll.size() > 1){
    std::sort(++coll.begin(), coll.end());
}

编译 ++coll.begin() 可能会失败,实际情况取决于平台。但如果你换用 deque 取代 vector, 就可以通过编译。

这种奇怪问题的产生原因是, 'vector、array 和 string 的迭代器通常被实现为寻常 pointer,而 C++ 并不允许你修改任何基础类型(包括 pointer)的临时值,但对
于 struct 和 class  则允许'。

为保证可移植, C++11 提供了next(), 所以你应该这么写:

std::vector<int> coll;
...
if(coll.size() > 1){
    std::sort(next(coll.begin()), coll.end());
}






// !!  迭代器相关辅助函数

C++ 标准库为迭代器提供了一些辅助函数:advance()、next()、prev()、distance() 和 iter_swap()。前四者提供给所有迭代器一些"原本只有 random access 迭代
器才有"的能力: 前进(或后退)多个元素, 及处理迭代器之间的距离。最后一个辅助函数允许你交换两个迭代器的 value。


// !! advance()

advance() 可将迭代器的位置增加, 增加幅度由实参决定, 也就是说它令迭代器一次前进(或后退)多个元素:

#include <iterator>

void advance(InputIterator& pos, Dist n);

1. 令名称为 pos 的 input 迭代器前进 (或后退) n 个元素

2. 对 bidirectional 迭代器和 random-access 迭代器而言, n 可为负值, 表示向后退

3. Dist 是个 template 类型。通常它必须是个整数类型, 因为会调用诸如 <、++、-- 等操作, 还要和 0 做比较

4. advance() 并不检查迭代器是否超过序列的 end() (因为迭代器通常不知道其所操作的容器, 因此无从检查)。所以, 调用 advance() 有可能导致不明确行为--因为"对序
   列尾端调用  operator++" 是一种未被定义的行为


此函数总能根据迭代器种类 (category) 采用最佳方案, 这归功于它使用了 iterator trait (迭代器特征)。对于 random-access 迭代器, 此函数只是简单地调用 pos +=
n, 因此具有常量复杂度。对于其他任何类型的迭代器, 则调用 ++pos (或 --pos, 如果 n 为负值) n 次。因此, 对于其他任何类型的迭代器, 本函数具有线性复杂度。


如果你希望你的程序可以轻松更换容器和迭代器种类, 你应该使用 advance() 而不是 operator +=。不过你必须意识到, 这么做可能是拿效能来冒险, 因为将 advance() 应用
于不提供 random-access 迭代器的容器中, 你不太容易感受效能变差(但正是由于运行期效能不佳, random-access 迭代器才会想要提供 operator+=)。另外请注意, 
advance() 不具返回值, 而 operator+= 会返回新位置, 所以后者可作为一个更大表达式的一部分。


下面是 advance() 的运用实例:

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;

int main(int argc, char **argv) {
  list<int> coll;

  for (int i = 1; i < 9; ++i) {
    coll.push_back(i);
  }

  list<int>::iterator pos = coll.begin();

  cout << *pos << endl;

    advance(pos, 3;

    cout << *pos << endl;

    advance(pos,-1);

    cout << *pos << endl;

    return 0;
}



// !! next() 和 prev()

'C++11 提供了两个新增的辅助函数,允许你前进/向退后移动迭代器的位置'。

#include <iterator>

ForwardIterator next(ForwardIterator pos);
ForwardIterator next(ForwardIterator pos, Dist n);

1. 导致 forward 迭代器 pos 前进 1 或 n 个位置

2. 如果处理的是 bidirectional 和 random-access 迭代器, n 可为负值, 导致后退(回头)移动

3. Dist 是类型 std::iterator_traits<ForwardIterator>::difference_type

4. 其内部将对一个临时对象调用 advance(pos,n)

5. 注意, next() 并不检查是否会跨越序列的 end(), 因此调用者必须自行担保其结果有效


#include <iterator>
BidirectionalIterator prev(BidirectionalIterator pos);
BidirectionalIterator prev(BidirectionalIterator pos, Dist n);

1. 导致 bidirectional 迭代器 pos 后退 1 或 n 个位置

2. n 可为负值, 导致向前移动

3. Dist 是类型 std::iterator_traits<BidirectionalIterator>::difference_type

4. 其内部将对一个临时对象调用 advance(pos,-n)

5. 注意, prev() 并不检查是否会跨越序列的 begin(), 因此调用者必须自行担保其结果有效


举个例子, 这些辅助函数允许我们走过容器, 只要我们检查了下一个元素:

auto pos = coll.begin();
while (pos != coll.end() && tsd::next(pos) != coll.end()){
    ...
    ++pos;
}


这么做特别有帮助,  因为 forward 和 bidirectional 迭代器不提供 operator+ 和 -。如果没有它们, 你就需要一个临时对象的协助。


auto pos = coll.begin();
auto nextPos = pos;
++nextPos;
while (pos != coll.end() && nextPos != coll.end())
{
    ...
    ++pos;
    ++nextPos;
}


next() 和 prev() 的第二个应用是避免诸如 ++coll.begin() 这样的表达式需要去处理容器的第二元素。问题在于, 以 ++coll.begin() 取代 
std::next)(coll.begin()) 有可能通不过编译。


// !! distance()

函数 distance() 用来处理两个迭代器之间的距离。

#include <iterator>

Dist distance(InputIterator pos1, InputIterator pos2);

. 返回两个 input 迭代器 pos1 和 pos2 之间的距离
· 两个迭代器必须指向同一个容器
. 如果不是 random-access 迭代器, 则从 pos1 开始前进必须能够到达 pos2, 亦即 pos2 的位置必须与 pos1 相同或在其后


返回类型 Dist 是迭代器相应的 difference 类型:

iterator_traits<InputIterator>::difference_type;


这个函数能够根据迭代器种类采取最佳实现手法, 这必须利用迭代器标志 (iterator tag) 才得以达成。


对于 random-access 迭代器, 此函数仅仅是返回 pos2-pos1, 因此具备常量复杂度。对于其他迭代器种类, distance() 会不断递增 pos1, 直到抵达 pos2 为止, 然后返
回递增次数。也就是说, 对于其他迭代器种类, distance() 具备线性复杂度。因此对于 non-random-access 迭代器而言 distance() 的效能并不好,应该避免使用。

#include <iterator>
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main(int argc, char** argv){
    
    list<int> coll;

    for(int i = 3; i < 9; ++i){
        coll.push_back(i);
    }

    list<int>::iterator pos;

    pos = std::find(coll.begin(), coll.end(),5);

    if(pos != coll.end()){
        cout << "difference between begging and 5 is " << distance(coll.begin(),pos) << endl;
    }else{
        cout << " 5 not found" << endl;
    }

    return 0;
}


处理两个 non-random-access 迭代器之间的距离时, 必须十分小心。第一个迭代器所指的元素绝不能在第二个迭代器所指元素之后方,否则会导致不明确的行为。如果不知道
哪个迭代器在前, 你必须先算出两个迭代器分别至容器起点的距离, 再根据这两个距离来判断。不过, 你一定得清楚知道迭代器所指的目标容器为何。如果两个迭代器指向不同容
器, 那么任你如何挣扎, 都无法摆脱"导致不明确行为"的悲惨命运。



// !! iter_swap()


'这个简单的辅助函数用来交换两个迭代器所指的元素值'

#include <algorithm>

void iter_swap(ForwardIterator pos1, ForwardIterator pos2);

. 交换迭代器 pos1 和 pos2 所指的值
· 迭代器的类型不必相同, 但其所指的两个值必须可以相互赋值 (assignable)


#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include "print.hpp"

using namespace std;

int main(int argc, char** argv){

    list<int> coll;

    for(int i=0; i < 9; ++i){
        coll.push_back(i);
    }

    std::iter_swap(coll.begin(), std::next(coll.begin()));

    PRINT_ELEMENTS(coll);

    std:iter_swap(coll.begin(), std::prev(coll.end()));

    PRINT_ELEMENTS(coll);

    return 0;
}


// !! 迭代器适配器 (Iterator Adapter)

本节讨论 C++ 标准库提供的迭代器适配器。此类特殊迭代器使得算法能够以反向模式 (reverse mode)或安插模式(insert mode) 进行工作, 也可以和 stream(串流)搭配工
作。


// !! Reverse (反向)迭代器

'Reverse 迭代器重新定义了递增运算和递减运算, 使其行为正好颠倒'。因此, 如果你使用这类迭代器, 算法将以反向次序处理元素。所有标准容器都允许使用 reverse 迭代
器来遍历元素。


下面是个例子:


#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

vod print(int elem){
    cout << elem << endl;
}

int  main(int argc, char **argv){

    list<int> coll = {1,2,3,4,5,6,7,8,9};
    for_each(coll.begin(), coll.end(),print);

    for_each(coll.rbegin(), coll.rend(), print);

    cout << endl;
    return 0;
}

容器的成员函数 rbegin() 和 rend() 各返回一个 reverse 迭代器, 它们就像 begin() 和 end() 的返回值一样, 共同定义出一个半开区间(half-open range)。不同
的是它们以相反的方向操作:

. rbegin() 返回反向迭代的第一元素位置, 也就是真实之最末元素的位置

. rend() 返回反向迭代的最末元素的下一位置, 也就是真实之第一元素的前一个位置


自 C++11 起也提供了相应的成员函数 crbegin() 和 crend(), 返回只读反向(read-only reverse) 迭代器。

for_each(coll.crbegin(), coll.crend(), print);



// !! 迭代器和  Reverse 迭代器

你可以将正常迭代器转化成 reverse 迭代器。当然, 原本那个迭代器必须具有双向移动能力。注意, 转换前后的迭代器逻辑位置发生了变化。

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv){

    vector<int> coll = {1,2,3,4,5,6,7,8,9};

    vector<int>::iterator pos;
    pos = std::find(coll.begin(),coll.end(),5);

    cout << "*pos is " << *pos << endl;

    vector<int>::const_reverse_iterator rpos(pos);

    cout << "*rpos is " << *rpos << endl;
    return 0;
}


我们首先打印迭代器的 value (也就是其所指的元素值), 然后将该迭代器转化为一个 reverse 迭代器, 再次打印其 value, 结果竟然变了。这不是 bug, 这是特性！导致这
个性质是因为区间的半开性。

为了指出容器内所有元素, 我们需要采用最末元素的下一位置。然而对 reverse 迭代器而言, 这个位置位于第一元素之前。糟糕的是, 这个位置可能并不存在, 因为容器并不要
求其第一元素之前的位置合法。例如寻常的 string 和 array 也可被视为容器, 而语言本身并不保证 array 不可以从地址 0 开始。


'为此, reverse 迭代器的设计者运用了一个小技巧: 他们实际倒置了"半开原则"。Reverse 迭代器所定义的区间, 并不包括起点. 反倒是包括了终点'。







// !!  Insert (安插型)迭代器


Insert 迭代器, 也称为inserter, 用来将"赋予新值"动作转换为"安插新值"动作。借由这种迭代器,算法将执行安插(insert) 行为而非覆写(overwrite)行为。


// !! Insert 迭代器的功能

通常, 算法会将 value 赋值给标的迭代器。例如 copy() 算法:

namespace std{
    template<typename InputIterator, typename OutputIterator>
    OutputIterator copy(InputIterator from_pos, InputIterator from_end, OutputIterator to_pos){
        while(from_pos != from_end){
            *to_pos = *from_pos;
            ++from_pos;
            ++to_pos;
        }
        return to_pos;
    }
}

循环不断执行, 直到 from_pos 抵达终点。在循环内, 来源端迭代器 from_pos 被赋值给标的端迭代器 to_pos, 然后两个迭代器都递增。

这里需要注意的是:

*to_pos = value;

Insert 迭代器可以把上述的赋值动作转化为安插动作。实际上其内有两个操作: 首先 operator* 传回迭代器当前位置, 然后再由 operator= 赋予新值。Insert 迭代器通
常使用下面两个实现技巧:

1. Operator* 被实现为一个无作用的 no-op, 仅仅返回 *this。所以对 insert 迭代器来说, *pos 与 pos 等价

2. 赋值动作(assignment) 被转化为安插动作(insertion)。事实上, insert 迭代器会调用容器的 push_back()、push_front() 或 insert() 成员函数


所以, 对于 insert 迭代器 pos, 你可以写 pos=value 也可以写 *pos=value, 两者都可以插入新值。


同样道理, 递增操作符也被实现为一个 no-op, 也是仅仅返回一个 *this。


'insert 迭代器的所有操作函数'

*iter;// No-op(返回 iter)
iter = value;// 安插  value
++iter;// No-op(返回 iter)
iter++; // No-op(返回 iter)



// !! Insert 迭代器的种类


C++ 标准库提供三种 insert 迭代器: back inserter, front inserter 和 general inserter。它们之间的区别在于安插的位置。'事实上, 它们各自调用所属容器中
不同的成员函数'。'所以 insert 迭代器初始化时一定要清楚指明所属的容器是哪一种'。


每一种 insert 迭代器都可以由一个对应的便捷函数加以生成和初始化。

back_inserter_iterator   push_back(value)   back_inserter(cont)

front_inserter_iterator pop_front(value)    front_inserter(cont)

insert_iterator         insert(value)       inserter(cont)


当然, 容器本身必须支持 insert 迭代器所调用的函数, 否则这种 insert 迭代器就不可用。

'因此, back inserter 只能用在 vector、deque、list 和 string 身上, front inserter 只能用在 deque 和 list 身上'。




