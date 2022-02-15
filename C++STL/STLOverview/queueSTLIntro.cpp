
// !! queue 容器

// !! queue 基本概念

概念: Queue 是一种先进先出(First In First Out,FIFO)的数据结构, 它有两个出口

队列容器允许从一端新增元素, 从另一端移除元素

'队列中只有队头和队尾才可以被外界使用, 因此队列不允许有遍历行为'

队列中进数据称为 --- 入队 push

队列中出数据称为 --- 出队 pop

// !! queue 常用接口

功能描述: 队列容器常用的对外接口

构造函数:

1. queue<T> que; //queue 采用模板类实现，queue 对象的默认构造形式

2. queue(const queue &que); //拷贝构造函数

赋值操作:

1. queue& operator=(const queue &que); //重载等号操作符


数据存取:

push(elem); //往队尾添加元素
pop(); //从队头移除第一个元素
back(); //返回最后一个元素
front(); //返回第一个元素


大小操作:

empty(); //判断队列是否为空
size(); //返回栈的大小


总结:

1. 入队 --- push
2. 出队 --- pop
3. 返回队头元素 --- front
4. 返回队尾元素 --- back
5. 判断队是否为空 --- empty
6. 返回队列大小 --- size

