// !! stack 容器

// !! stack 基本概念

概念: stack 是一种先进后出(First In Last Out,FILO) 的数据结构, 它只有一个出口

栈中只有顶端的元素才可以被外界使用, 因此栈不允许有遍历行为

栈中进入数据称为 --- 入栈 push

栈中弹出数据称为 --- 出栈 pop


// !! stack 常用接口

功能描述: 栈容器常用的对外接口

构造函数:

1. stack<T> stk; // stack 采用模板类实现, stack 对象的默认构造形式

2. stack(const stack &stk); //拷贝构造函数

赋值操作:

1. stack& operator=(const stack &stk); // 重载等号操作符

数据存取:

push(elem); // 向栈顶添加元素
pop(); // 从栈顶移除第一个元素
top(); // 返回栈顶元素


大小操作:

empty(); //判断堆栈是否为空
size(); //返回栈的大小


总结:

1. 入栈 --- push

2. 出栈 --- pop

3. 返回栈顶 --- top

4. 判断栈是否为空 --- empty

5. 返回栈大小 --- size


