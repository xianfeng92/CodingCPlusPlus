// !! 执行期语意学

想象一下我们有下面这个简单的式子:

if(yy == xx.getValue());

其中 xx 和 yy 定义为:

X xx;
Y yy;

class Y 定义为:

class Y{
public:
    Y();
    ~Y();
    bool operator=(const Y& other)const;
    //...
};


class X 定义为:

class X{
public:
    X();
    ~X();
    operator Y() const;
    X getValue();
    //...
};

真的简单,不是吗? 好, 让我们看看本章一开始的那个表达式该如何处理。

首先, 让我们决定 equality(等号)运算符所参考到的真正实例。在这个例子中, 它将被决议(resolves)为"被 overloaded 的 Y 成员实例"。


下面是该式子的第一次转换:

if(yy.operator==(xx.getValue()));

Y 的 equality(等号)运算符需要一个类型为 Y 的参数, 然而 getValue() 传回的却是一个类型为 X 的 object。若非有什么方法可以把一个 X object 转换为一个
Y object, 那么这个式子就算错!

本例中 X  提供一个 conversion 运算符, 把一个 X object 转换为一个 Y object。它必须施行于 getValue() 的返回值身上。下面是该式子的第二次转换:

if(yy.operator=((xx.getValue()).operatorY());

'到目前为止所发生的一切都是编译器根据 class 的隐含语意, 对我们的程序代码所做的增胖操作'。如果我们需要, 我们也可以明确地写出那样的式子。不, 我并没有建议你
那么做。不过如果你那么做, 会使编译速度稍微快一些。

虽然程序的语意是正确的, 其可读性变差了。接下来我们必须产生一个临时对象, 用来放置函数调用所传回的值:

1. 产生一个临时的 class X object, 放置 getValue() 的返回值

X temp = xx.getValue();

2. 产生一个临时的 class Y object, 放置 operator Y() 的返回值

Y temp2 = temp.operatorY();

3. 产生一个临时的 int object, 放置 equality(等号)运算符的返回值





