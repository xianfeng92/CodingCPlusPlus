// !! 4.4　C++ 相关问题

C++ 的一些语言特性使之必须由编译器和链接器共同支持才能完成工作。最主要的有两个方面, 一个是 C++ 的重复代码消除, 还有一个就是全局构造与析构。另外由于 C++ 语言的各种特性,
比如虚拟函数、函数重载、继承、异常等, 使得它背后的数据结构异常复杂, 这些数据结构往往在不同的编译器和链接器之间相互不能通用, 使得 C++ 程序的二进制兼容性成了一个很大的问题

// !! 4.4.1　重复代码消除

C++ 编译器在很多时候会产生重复的代码, 比如模板(Templates)、外部内联函数 (Extern Inline Function) 和虚函数表 (Virtual Function Table) 都有可能在不同的编译单元
里生成相同的代码。

'最简单的情况就拿模板来说, 模板从本质上来讲很像宏, 当模板在一个编译单元里被实例化时, 它并不知道自己是否在别的编译单元也被实例化了'。

所以当一个模板在多个编译单元同时实例化成相同的类型的时候, 必然会生成重复的代码。

当然, 最简单的方案就是不管这些, 将这些重复的代码都保留下来。不过这样做的主要问题有以下几方面:

• 空间浪费。可以想象一个有几百个编译单元的工程同时实例化了许多个模板, 最后链接的时候必须将这些重复的代码消除掉, 否则最终程序的大小肯定会膨胀得很厉害

• 地址较易出错。有可能两个指向同一个函数的指针会不相等

• 指令运行效率较低。因为现代的 CPU 都会对指令和数据进行缓存, 如果同样一份指令有多份副本, 那么指令 Cache 的命中率就会降低


'一个比较有效的做法就是将每个模板的实例代码都单独地存放在一个段里, 每个段只包含一个模板实例'。比如有个模板函数是 add<T>(), 某个编译单元以 int 类型和 float 类型实例化
了该模板函数, 那么该编译单元的目标文件中就包含了两个该模板实例的段。为了简单起见, 我们假设这两个段的名字分别叫 .temp.add<int> 和 .temp.add<float>。这样, 当别的编译
单元也以 int 或 float 类型实例化该模板函数后, 也会生成同样的名字, 这样链接器在最终链接的时候可以区分这些相同的模板实例段, 然后将它们合并入最后的代码段。

这种做法的确被目前主流的编译器所采用, GNU GCC 编译器和 VISUAL C++ 编译器都采用了类似的方法。

GCC 把这种类似的须要在最终链接时合并的段叫 Link Once, 它的做法是将这种类型的段命名为 .gnu.linkonce.name, 其中 name 是该模板函数实例的修饰后名称。

'这种重复代码消除对于模板来说是这样的, 对于外部内联函数和虚函数表的做法也类似'。比如对于一个有虚函数的类来说, 有一个与之相对应的虚函数表(Virtual Function Table, vtbl),
编译器会在用到该类的多个编译单元生成虚函数表, 造成代码重复; 外部内联函数、默认构造函数、默认拷贝构造函数和赋值操作符也有类似的问题。它们的解决方式基本跟模板的重复代码消除
类似。

这种方法虽然能够基本上解决代码重复的问题, 但还是存在一些问题。比如相同名称的段可能拥有不同的内容, 这可能由于不同的编译单元使用了不同的编译器版本或者编译优化选项, 导致同
一个函数编译出来的实际代码有所不同。那么这种情况下链接器可能会做出一个选择, 那就是随意选择其中任何一个副本作为链接的输入, 然后同时提供一个警告信息。


// !! 函数级别链接

由于现在的程序和库通常来讲都非常庞大, 一个目标文件可能包含成千上百个函数或变量。'当我们须要用到某个目标文件中的任意一个函数或变量时, 就须要把它整个地链接进来, 也就是说
那些没有用到的函数也被一起链接了进来'。

VISUAL C++ 编译器提供了一个编译选项叫函数级别链接 (Functional-Level Linking), 这个选项的作用就是让所有的函数都像前面模板函数一样, 独保存到一个段里面。当链接器须要
用到某个函数时, 它就将它合并到输出文件中, 对于那些没有用的函数则将它们抛弃。这种做法可以很大程度上减小输出文件的长度, 减少空间浪费。但是这个优化选项会减慢编译和链接过程, 
因为链接器须要计算各个函数之间的依赖关系, 并且所有函数都保持到独立的段中, 目标函数的段的数量大大增加, 重定位过程也会因为段的数目的增加而变得复杂目标文件随着段数目的增加
也\会变得相对较大。

GCC 编译器也提供了类似的机制, 它有两个选择分别是 -ffunction-sections 和 -fdata-sections, 这两个选项的作用就是将每个函数或变量分别保持到独立的段中。


// !! 4.4.2　全局构造与析构

一般的一个 C/C++ 程序是从 main 开始执行的, 随着 main 函数的结束而结束。然而, 其实在 main 函数被调用之前, 为了程序能够顺利执行,要先初始化进程执行环境, 比如堆分配初
始化 (malloc、free)、线程子系统等。

C++ 的全局对象构造函数也是在这一时期被执行的, 我们知道 C++ 的全局对象的构造函数在 main 之前被执行, C++ 全局对象的析构函数在 main 之后被执行。

'Linux 系统下一般程序的入口是 _start, 这个函数是 Linux 系统库 Glibc 的一部分'。当我们的程序与 Glibc 库链接在一起形成最终可执行文件以后, 这个函数就是程序的初始化部
分的入口, 程序初始化部分完成一系列初始化过程之后, 会调用 main 函数来执行程序的主体。

在 main 函数执行完成以后, 返回到初始化部分, 它进行一些清理工作, 然后结束进程。

对于有些场合, 程序的一些特定的操作必须在 main 函数之前被执行, 还有一些操作必须在 main 函数之后被执行, 其中很具有代表性的就是 C++ 的全局对象的构造和析构函数。因此 
ELF 文件还定义了两种特殊的段。


• .init 该段里面保存的是可执行指令, 它构成了进程的初始化代码。因此, 当一个程序开始运行时, 在 main 函数被调用之前, Glibc 的初始化部分安排执行这个段的中的代码

• .fini 该段保存着进程终止代码指令。因此, 当一个程序的 main 函数正常退出时, Glibc 会安排执行这个段中的代码

这两个段 .init 和 .fini 的存在有着特别的目的, 如果一个函数放到 .init 段, 在 main 函数执行前系统就会执行它。同理, 假如一个函数放到 .fini 段, 在 main 函数返回后
该函数就会被执行。


// !! 4.4.3　C++ 与 ABI

既然每个编译器都能将源代码编译成目标文件, 那么不同编译器编译出来的目标文件是不能够相互链接的呢? 有没有可能将 MSVC 编译出来的目标文件和 GCC 编译出来的目标文件链接到一起,
形成一个可执行文件呢?

如果要使两个编译器编译出来的目标文件能够相互链接, 那么这两个目标文件必须满足下面这些条件:

采用同样的'目标文件格式、拥有同样的符号修饰标准、变量的内存分布方式相同、函数的调用方式相同等等'。其中我们把符号修饰标准、变量内存布局、函数调用方式等这些跟可执行代码二进
制兼容性相关的内容称为 ABI (Application Binary Interface)。

API 往往是指源代码级别的接口, 比如我们可以说 POSIX 是一个 API 标准、Windows 所规定的应用程序接口是一个 API; 而 ABI 是指二进制层面的接口, ABI 的兼容程度比 API 要
更为严格, 比如我们可以说 C++ 的对象内存分布(Object Memory Layout) 是 C++ ABI 的一部分。

API 更关注源代码层面的, 比如 POSIX 规定 printf() 这个函数的原型, 它能保证这个函数定义在所有遵循 POSIX 标准的系统之间都是一样的, 但是它不保证 printf 在实际的每个系
统中执行时, 是否按照从右到左将参数压入堆栈, 参数在堆栈中如何分布等这些实际运行时的二进制级别的问题。

ABI 的概念其实从开始至今一直存在, 因为人们总是希望程序能够在不经任何修改的情况下得到重用, 最好的情况是'二进制的指令和数据能够不加修改地得到重用'。

影响 ABI 的因素非常多, 硬件、编程语言、编译器、链接器、操作系统等都会影响 ABI。

对于 C 语言的目标代码来说, 以下几个方面会决定目标文件之间是否二进制兼容:

• 内置类型 (如 int、float、char 等) 的大小和在存储器中的放置方式(大端、小端、对齐方式等)

• 组合类型 (如 struct、union、数组等) 的存储方式和内存分布

• 外部符号 (external-linkage) 与用户定义的符号之间的命名方式和解析方式, 如函数名 func 在 C 语言的目标文件中是否被解析成外部符号 _func

• 函数调用方式, 比如参数入栈顺序、返回值如何保持等

• 堆栈的分布方式, 比如参数和局部变量在堆栈里的位置, 参数传递方法等

• 寄存器使用约定, 函数调用时哪些寄存器可以修改, 哪些须要保存等等


到了 C++ 的时代, 语言层面对 ABI 的影响又增加了很多额外的内容, 可以看到, 正是这些内容使 C++ 要做到二进制兼容比 C 来得更为不易:


• 继承类体系的内存分布, 如基类，虚基类在继承类中的位置等

• 指向成员函数的指针 (pointer-to-member) 的内存分布, 如何通过指向成员函数的指针来调用成员函数, 如何传递 this 指针

• 如何调用虚函数, vtable 的内容和分布形式, vtable 指针在 object 中的位置等

• template 如何实例化

• 外部符号的修饰

• 全局对象的构造和析构

• 全局对象的构造和析构

• 标准库的细节问题, RTTI 如何实现等

• 内嵌函数访问细节

C++ 一直为人诟病的一大原因是它的二进制兼容性不好, 或者说比起 C 语言来更为不易。

'很多时候, 库厂商往往不希望库用户看到库的源代码, 所以一般是以二进制的方式提供给用户'。

这样, 当用户的编译器型号与版本与编译库所用的编译器型号和版本不同时, 就可能产生不兼容。

所以人们一直期待着能有统一的 C++ 二进制兼容标准 (C++ABI), 诸多的团体和社区都在致力于 C++ ABI 标准的统一。






















