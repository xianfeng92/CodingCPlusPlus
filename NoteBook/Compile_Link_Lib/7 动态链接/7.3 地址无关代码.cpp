// !! 7.3 地址无关代码

// !! 7.3.1　固定装载地址的困扰

共享对象在被装载时, 如何确定它在进程虚拟地址空间中的位置?

为了解决这个模块装载地址固定的问题, 我们设想是否可以让共享对象在任意地址加载? 这个问题另一种表述方法就是: 共享对象在编译时不能假设自己在进程虚拟地址空间中的位置。
与此不同的是, 可执行文件基本可以确定自己在进程虚拟空间中的起始位置, 因为可执行文件往往是第一个被加载的文件, 它可以选择一个固定空闲的地址, 比如 Linux 下一般都是
0x08040000


// !! 7.3.2　装载时重定位

为了能够使共享对象在任意地址装载, 我们首先能想到的方法就是静态链接中的重定位。这个想法的基本思路就是, 在链接时, 对所有绝对地址的引用不作重定位, 而把这一步推迟到装载时
再完成。一旦模块装载地址确定, 即目标地址确定, 那么系统就对程序中所有的绝对地址引用进行重定位。

假设函数 foobar 相对于代码段的起始地址是 0x100, 当模块被装载到 0x10000000时, 我们假设代码段位于模块的最开始, 即代码段的装载地址也是 0x10000000, 那么我们就可以确
定 foobar 的地址为 0x10000100。这时候, '系统遍历模块中的重定位表, 把所有对 foobar 的地址引用都重定位至 0x10000100'。

比如一个程序在编译时假设被装载的目标地址为 0x1000, 但是在装载时操作系统发现 0x1000 这个地址已经被别的程序使用了, 从 0x4000 开始有一块足够大的空间可以容纳该程序, 那么
该程序就可以被装载至 0x4000, 程序指令或数据中的所有绝对引用只要都加上 0x3000 的偏移量就可以了。

我们前面在静态链接时提到过重定位, 那时的重定位叫做链接时重定位 (Link Time Relocation), 而现在这种情况经常被称为装载时重定位 (Load Time Relocation)。

但是装载时重定位的方法并不适合用来解决上面的共享对象中所存在的问题。可以想象, '动态链接模块被装载映射至虚拟空间后, 指令部分是在多个进程之间共享的, 由于装载时重定位的方法
需要修改指令, 所以没有办法做到同一份指令被多个进程共享',因为指令被重定位后对于每个进程来讲是不同的。

当然, '动态连接库中的可修改数据部分对于不同的进程来说有多个副本, 所以它们可以采用装载时重定位的方法来解决'。

Linux 和 GCC 支持这种装载时重定位的方法, 我们前面在产生共享对象时, 使用了两个 GCC 参数 -shared 和 -fPIC, 如果只使用 -shared, 那么输出的共享对象就是使用装载时重定
位的方法。

// !! 7.3.3　地址无关代码

那么什么是 -fPIC 呢? 使用这个参数会有什么效果呢?

装载时重定位是解决动态模块中有绝对地址引用的办法之一, 但是它有一个很大的缺点是指令部分无法在多个进程之间共享, 这样就失去了动态链接节省内存的一大优势。

我们还需要有一种更好的方法解决共享对象指令中对绝对地址的重定位问题。

其实我们的目的很简单, '希望程序模块中共享的指令部分在装载时不需要因为装载地址的改变而改变', 所以实现的基本想法就是把指令中那些需要被修改的部分分离出来, 跟数据部分放在一
起, 这样指令部分就可以保持不变, 而数据部分可以在每个进程中拥有一个副本。

'这种方案就是目前被称为地址无关代码 (PIC, Position-independent Code) 的技术'。

对于现代的机器来说, 产生地址无关的代码并不麻烦。我们先来分析模块中各种类型的地址引用方式。

这里我们把共享对象模块中的地址引用按照是否为跨模块分成两类: 模块内部引用和模块外部引用; 按照不同的引用方式又可以分为指令引用和数据访问, 这样我们就得到了如图 7-4 中的 4
种情况。

• 第一种是模块内部的函数调用、跳转等

• 第二种是模块内部的数据访问, 比如模块中定义的全局变量、静态变量

• 第三种是模块外部的函数调用、跳转等

• 第四种是模块外部的数据访问, 比如其他模块中定义的全局变量


// !! 关于模块内部和模块外部

当编译器在编译 pic.c 时, 它实际上并不能确定变量 b 和函数 ext() 是模块外部的还是模块内部的, 因为它们有可能被定义在同一个共享对象的其他目标文件中。
由于没法确定, 编译器只能把它们都当作模块外部的函数和变量来处理。


// !! 类型一 模块内部调用或跳转

这 4 种情况中, 第一种类型应该是最简单的, 那就是模块内部调用。因为被调用的函数与调用者都处于同一个模块, 它们之间的相对位置是固定的, 所以这种情况比较简单。
'对于现代的系统来讲, 模块内部的跳转、函数调用都可以是相对地址调用, 或者是基于寄存器的相对调用, 所以对于这种指令是不需要重定位的'。

foo 中对 bar 的调用的那条指令实际上是一条相对地址调用指令,我们在第 2 部分已经介绍过相对位移调用指令的指令格式, 相对偏移调用指令如图 7-5 所示。


// !! 类型二 模块内部数据访问

接着来看看第二种类型, 模块内部的数据访问。很明显, 指令中不能直接包含数据的绝对地址, 那么唯一的办法就是相对寻址。

我们知道, 一个模块前面一般是若干个页的代码, 后面紧跟着若干个页的数据, 这些页之间的相对位置是固定的, 也就是说, '任何一条指令与它需要访问的模块内部数据之间的相对位置是固
定的', 那么只需要相对于当前指令加上固定的偏移量就可以访问模块内部数据了。

现代的体系结构中, 数据的相对寻址往往没有相对与当前指令地址的寻址方式, 所以 ELF 用了一个很巧妙的办法来得到当前的 PC 值, 然后再加上一个偏移量就可以达到访问相应变量的目
的了。



// !! 类型三 模块间数据访问

模块间的数据访问比模块内部稍微麻烦一点, 因为模块间的数据访问目标地址要等到装载时才决定, 比如上面例子中的变量 b, 它被定义在其他模块中, 并且该地址在装载时才能确定。

我们前面提到要使得代码地址无关, '基本的思想就是把跟地址相关的部分放到数据段里面, 很明显, 这些其他模块的全局变量的地址是跟模块装载地址有关的'。

'ELF 的做法是在数据段里面建立一个指向这些变量的指针数组, 也被称为全局偏移表 (Global Offset Table, GOT)', 当代码需要引用该全局变量时, 可以通过 GOT 中相对应的项
间接引用, 它的基本机制如图 7-7 所示。


当指令中需要访问变量 b 时, 程序会先找到 GOT, 然后根据 GOT 中变量所对应的项找到变量的目标地址。每个变量都对应一个 4 个字节的地址, '链接器在装载模块的时候会查找每个变量
所在的地址, 然后填充 GOT 中的各个项, 以确保每个指针所指向的地址正确'。

由于 GOT 本身是放在数据段的, 所以它可以在模块装载时被修改, 并且每个进程都可以有独立的副本, 相互不受影响。


// !! 类型四 模块间调用、跳转

对于模块间调用和跳转, 我们也可以采用上面类型四的方法来解决。与上面的类型有所不同的是, GOT 中相应的项保存的是目标函数的地址, 当模块需要调用目标函数时, 可以通过 GOT 中
的项进行间接跳转, 基本的原理如图 7-8 所示。




// !! 地址无关代码小结

// !! -fpic 和-fPIC

使用 GCC 产生地址无关代码很简单, 我们只需要使用 -fPIC 参数即可。实际上 GCC 还提供了另外一个类似的参数叫做 -fpic, 即 PIC 3 个字母小写, 这两个参数从功能上来讲完全一
样, 都是指示 GCC 产生地址无关代码。唯一的区别是,  -fPIC 产生的代码要大, 而 -fpic 产生的代码相对较小, 而且较快。

那么我们为什么不使用 -fpic 而要使用 -fPIC 呢? 原因是, 由于地址无关代码都是跟硬件平台相关的, 不同的平台有着不同的实现, -fpic 在某些平台上会有一些限制, 比如全局符号的
数量或者代码的长度等, 而 -fPIC 则没有这样的限制。所以为了方便起见, 绝大部分情况下我们都使用 -fPIC 参数来产生地址无关代码。


如何区分一个 DSO 是否为 PIC ?

readelf -d foo.so | grep TEXTREL

如果上面的命令有任何输出, 那么 foo.so 就不是 PIC 的, 否则就是 PIC 的。PIC 的 DSO 是不会包含任何代码段重定位表的, TEXTREL 表示代码段重定位表地址。



// !! 7.3.4　共享模块的全局变量问题

有一种很特殊的情况是, 当一个模块引用了一个定义在共享对象的全局变量的时候, 比如一个共享对象定义了一个全局变量 global, 而模块 module.c 中是这么引用的:

extern int global;
int foo() {
    global = 1;
}

'当编译器编译 module.c 时, 它无法根据这个上下文判断 global 是定义在同一个模块的的其他目标文件还是定义在另外一个共享对象之中, 即无法判断是否为跨模块间的调用'。

假设 module.c 是程序可执行文件的一部分, 那么在这种情况下, 由于程序主模块的代码并不是地址无关代码, 也就是说代码不会使用这种类似于 PIC 的机制, 它引用这个全局变量的方
式跟普通数据访问方式一样, 编译器会产生这样的代码:

movl   $0x1,XXXXXXXX

XXXXXXXX 就是 global 的地址。'由于可执行文件在运行时并不进行代码重定位, 所以变量的地址必须在链接过程中确定下来'。

为了能够使得链接过程正常进行, 链接器会在创建可执行文件时, 在它的 .bss 段创建一个 global 变量的副本。那么问题就很明显了, 现在 global 变量定义在原先的共享对象中, 而在
可执行文件的 .bss 段还有一个副本。如果同一个变量同时存在于多个位置中, 这在程序实际运行过程中肯定是不可行的。

'于是解决的办法只有一个, 那就是所有的使用这个变量的指令都指向位于可执行文件中的那个副本'。

ELF 共享库在编译时, 默认都把定义在模块内部的全局变量当作定义在其他模块的全局变量, 也就是说当作前面的类型四, 通过 GOT 来实现变量的访问。

'当共享模块被装载时, 如果某个全局变量在可执行文件中拥有副本, 那么动态链接器就会把 GOT 中的相应地址指向该副本, 这样该变量在运行时实际上最终就只有一个实例'。

如果变量在共享模块中被初始化, 那么动态链接器还需要将该初始化值复制到程序主模块中的变量副本; 如果该全局变量在程序主模块中没有副本, 那么 GOT 中的相应地址就指向模块内部的该
变量副本。

假设 module.c 是一个共享对象的一部分, 那么 GCC 编译器在 -fPIC 的情况下, 就会把对 global 的调用按照跨模块模式产生代码。


// !! Q&A

Q: 如果一个共享对象 lib.so 中定义了一个全局变量 G, 而进程 A 和进程 B 都使用了 lib.so, 那么当进程 A 改变这个全局变量 G 的值时, 进程 B 中的 G 会受到影响吗?

A: 不会。'因为当 lib.so 被两个进程加载时, 它的数据段部分在每个进程中都有独立的副本, 从这个角度看, 共享对象中的全局变量实际上和定义在程序内部的全局变量没什么区别'。任何
   一个进程访问的只是自己的那个副本, 而不会影响其他进程。那么, 如果我们把这个问题的条件改成同一个进程中的线程 A 和线程 B, 它们是否看得到对方对 lib.so 中的全局变量 G 的
   修改呢? 对于同一个进程的两个线程来说, 它们访问的是同一个进程地址空间, 也就是同一个 lib.so 的副本, 所以它们对 G 的修改, 对方都是看得到的。



// !! 7.3.5　数据段地址无关性

通过上面的方法, 我们能够保证共享对象中的代码部分地址无关, 但是数据部分是不是也有绝对地址引用的问题呢? 让我们来看看这样一段代码:

static int a = 10;
static int* p = &a;

如果某个共享对象里面有这样一段代码的话, 那么指针 p 的地址就是一个绝对地址, 它指向变量 a, 而变量 a 的地址会随着共享对象的装载地址改变而改变。那么有什么办法解决这个问题呢?

对于数据段来说, 它在每个进程都有一份独立的副本, 所以并不担心被进程改变。'从这点来看, 我们可以选择装载时重定位的方法来解决数据段中绝对地址引用问题'。

从前面的例子中我们看到, 我们在编译共享对象时使用了 -fPIC 参数, 这个参数表示产生地址无关的代码段。如果我们不使用这个参数来产生共享对象又会怎么样呢?

> gcc -shared pic.c -o pic.so

上面这个命令就会产生一个不使用地址无关代码而使用装载时重定位的共享对象。'如果代码不是地址无关的, 它就不能被多个进程之间共享, 于是也就失去了节省内存的优点'。

但是装载时重定位的共享对象的运行速度要比使用地址无关代码的共享对象快, 因为它省去了地址无关代码中每次访问全局数据和函数时需要做一次计算当前地址以及间接地址寻址的过
程。

'对于可执行文件来说, 默认情况下, 如果可执行文件是动态链接的, 那么 GCC 会使用 PIC 的方法来产生可执行文件的代码段部分, 以便于不同的进程能够共享代码段,节省内存'。