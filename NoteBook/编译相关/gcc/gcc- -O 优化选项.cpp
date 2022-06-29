## gcc- -O 优化选项


-O0: 这个等级(字母 O 后面跟个零)关闭所有优化选项, 也是 CFLAGS 或 CXXFLAGS 中没有设置 -O 等级时的默认等级。这样就不会优化代码, 这通常不是我们想
要的。


-O1 : 这是最基本的优化等级。'编译器会在不花费太多编译时间的同时试图生成更快更小的代码'。这些优化是非常基础的, 但一般这些任务肯定能顺利完成。


-O2 : -O1 的进阶。'这是推荐的优化等级, 除非你有特殊的需求'。-O2 会比 -O1 启用多一些标记。设置了 -O2 后, 编译器会试图提高代码性能而不会增大体积和大
量占用的编译时间。


-O3 : O3在O2的基础上进行更多的优化, 例如使用伪寄存器网络, 普通函数的内联以及针对循环的更多优化。

-Os : 主要是对程序的尺寸进行优化。打开了大部分 O2 优化中不会增加程序大小的优化选项, 并对程序代码的大小做更深层的优化。


## 优化代码有可能带来的问题 

1. 调试问题

正如上面所提到的, 任何级别的优化都将带来代码结构的改变。例如: 对分支的合并和消除, 对公用子表达式的消除, 对循环内 load/store 操作的替换和更改等, 都将会使目
标代码的执行顺序变得面目全非, 导致调试信息严重不足。 


2. 内存操作顺序改变所带来的问题

在 O2 优化后, 编译器会对影响内存操作的执行顺序。


## gcc -O0 -g -O3 对程序效率影响很大

gcc 编译选项中 -O0  -g -O3 对程序效率影响很大。如果是 -O0 -g 编译非优化, 会添加调试信息, 编译完成后可执行程序非常大, 运行效率也会很慢。所以如果自己线下调
试程序, 可以用 -O0 -g, 但线上发布时一定要用 -O3 开启优化选项。




