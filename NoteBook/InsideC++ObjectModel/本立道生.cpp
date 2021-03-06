// !! 本立道生

对于传统的结构化(sequential)语言, 我们向来没有太多的疑惑, '虽然在函数调用的背后, 也有着堆栈建制、参数排列、返回地址、堆栈清除等等幕后机制', 
但函数调用是那么的自然而明显, 好像只是夹带着一个包裹, 从程序的某一个地点跳到另一个地点去执行。

但是对于面向对象(Object Oriented)语言, 我们的疑惑就多了。

'究其因, 这种语言的编译器为我们(程序员)做了太多的服务: 构造函数、析构函数、虚拟函数、继承、多态'……有时候它为我们合成出一些额外的函数(或运算符),
有时候它又扩张我们所写的函数内容, 放进更多的操作。有时候它还会为我们的 objects 加油添醋, 放进一些奇妙的东西, 使你面对 sizeof 的结果大惊失色。

我心里头一直有个疑惑: '计算机程序最基础的形式, 总是脱离不了一行一行的循序执行模式, 为什么 OO(面向对象) 语言却能够"自动完成"这么多事情呢'?
另一个疑惑是, 威力强大的 polymorphism(多态), 其底层机制究竟如何 ?

'如果不了解编译器对我们所写的 C++ 代码做了什么手脚, 这些困惑永远解不开'。

