// !! 面向过程的编程风格

我们将整个程序写在 main() 函数里头。但除非我们仅仅想编写规模不大的程序, 否则这是一种不切实际的做法。

通常我们会抽取通用的操作, 例如计算 Fibonacci 数列元素、产生随机数,等等, 将它们实现为独立函数。

将函数独立出来的做法可带来三个主要好处: 第一, 以一连串函数调用操作, 取代重复编写相同的程序代码, 可使程序更容易读懂。第二, 我们可以在不同的程序中使用这些函数。
第三, 我们可以更容易地将工作分配给协作开发团队。


// !! 如何编写函数


我将在这一节编写一个函数, 该函数返回 Fibonacci 数列中由用户指定的某个位置的元素。例如用户可以询问"Fibonacci 数列的第八个元素是什么? "我们的程序应该回答:21。
这个函数应当如何定义呢 ?

每一个函数必须定义以下四个部分:

1. 返回类型。本例将返回用户指定位置的元素值, 而元素类型是 int, 所以我们的函数返回类型也是 int。函数如果没有返回值, 其返回类型为 void

2. 函数名。foo() 是个常见的名称, 但却不是个好名称, 因为它无法帮助我们理解函数操作的实际内涵

3. 参数列表 parameter list。函数参数扮演着占位符(placeholder) 的角色, 它让用户在每次调用函数时,将要传入的值放在其中, 以便函数使用

4. 函数体。此即操作本身的工作逻辑的实现内容


函数必须先被声明, 然后才能被调用(被使用)。'函数的声明让编译器得以检查后续出现的使用方式是否正确'--是否有足够的参数、参数类型是否正确等等。函数声明不必提供函数
体, 但必须指明返回类型、函数名以及参数列表。此即所谓的函数原型 (function prototype)

int fib_elem(int pos);

'函数的定义则包括函数原型及函数体'。函数以 return 语句将值返回。

如果用户输入了一个不合理的位置值, 程序应该怎么处理呢? 最极端的做法就是终止整个程序。标准库的 exit() 函数可派上用场。我们必须传一个值给 exit(), 此值将成为程
序结束时的状态值。


if(pos < 0){
    exit(-1);
}


为了能使用 exit(), 必须先包含 cstdlib 头文件:

#include <cstdlib>



// !! Pass by Reference 语义

reference 扮演着外界与对象之间一个间接手柄的角色。只要在类型名称和 reference 名称之间插入 &  符号, 便是声明了一个reference:

int ival = 1024;
int & ref_val = ival;


C++ 不允许我们改变 reference 所代表的对象, 它们必须从一而终。

当我们以 by reference 方式将对象作为函数参数传入时, 对象本身并不会复制出另一份--复制的是对象的地址。函数中对该对象进行的任何操作,都相当于是对传入的对象进行
间接操作。

将参数声明为 reference 的理由之一是, 希望得以直接对所传入的对象进行修改。这个理由极为重要, 因为就像我们在前面的例子中所见, 不这么做的话, 程序无法正确工作。

将参数声明为 reference 的第二个理由是, 降低复制大型对象的额外负担。这个理由相比较起来不是那么重要, 因为对程序而言不过是效率问题罢了。


声明了一个 reference to const vector, 因为函数之中并不会更改 vector 的内容。少了 const 并不会造成错误。但加上 const 可以让阅读程序的人了解,我们以传址
的方式来传递 vector, 为的是避免复制操作, 而不是为了要在函数之中对它进行修改。

如果我们愿意, 也可以将 vector 以 pointer 形式传递。这和以 reference 传递的效果相同: 传递的是对象地址, 而不是整个对象的副本。唯一差别在于 reference 和
pointer 的用法不同。

pointer 参数和 reference 参数之间更重要的差异是, pointer 可能 (也可能不)指向某个实际对象。当我们提领 pointer 时, 一定要先确定其值并非 0。至于 reference
, 则必定会代表某个对象, 所以不需要做此检查。


// !! 作用域及范围


除了一个必要的例外(意指 static), 函数内定义的对象, 只存在于函数执行期间。如果将这些所谓局部对象 (local object) 的地址返回, 会导致运行时错误。

还记得吗, 函数是暂时位于程序栈 (内存内的一块特殊区域) 之上。局部对象就放在这块区域中。当函数执行完毕, 这块区域的内容便会被弃置。于是局部对象不复存在。一般而言,
对根本不存在的对象进行寻址操作, 是很不好的习惯。

对象在程序内的存活区域称为该对象的 scope。

'对象如果在函数以外声明, 具有所谓的 file scope'。对象如果拥有 file scope, 从其声明点至文件末尾都是可见的。file scope 内的对象也具备所谓的 static extent
,意即该对象的内存在 main() 开始执行之前便已经分配好了, 可以一直存在至程序结束。

内置类型的对象, 如果定义在 file scope 之内, 必定被初始化为 0。但如果它们被定义于 local scope 之内, 那么除非程序员指定其初值, 否则不会被初始化。



// !! 动态内存管理

































