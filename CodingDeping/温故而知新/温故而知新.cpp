
// !! 1.1 从 Hello World 说起

从最基本的编译、静态链接到操作系统如何装载程序，动态链接、运行库标准库的实现和一些操作系统的机制， 了解计算机上程序运行的一个基本脉络。


// !! 1.2 变不离其宗

计算机最关键的三个部分: 中央处理器 CPU、内存和 I/O 控制芯片

1. 早期的计算机： 没有复杂的图形功能， CPU 和 内存频率一样， 都连接在同一个总线（BUS）上， 而外设通过 I/O 控制芯片 与 BUS 连接

2. CPU频率提升： 内存跟不上 CPU，产生了和内存频率一致的系统总线，CPU 使用倍频的方式和总线通信

3. 图形界面的出现： 图形芯片需要和内存和 CPU 大量交换数据， 慢速的I/O总线无法满足图形设备的巨大需求。为了高效处理数据，设计了一个高速的北桥芯片。
   后来有设计处理低速处理设备南桥芯片（I/O 桥）。磁盘，USB，键盘都是连接在南桥上， 在由南桥将它们汇总到北桥上

// !! SMP 和多核


现在 CPU 已经达到物理极限, 被 4GHz 所限制，于是开始通过增加 CPU 数量来提高计算机速度。

1. 对称多处理器（SMP）: 最常见的一种形式, '每个 CPU 在系统中所处的地位和所发挥的功能是一样'，是相互对称的。但在处理程序时，我们并不能把它们分成若干个不相干的子
   问题，所以，使得多处理器速度实际提高得并没有理论上那么高。当对于相互独立的问题，多处理器就能最大效能的发挥威力了（比如：大型数据库,网络服务等）。对处理器由于造
   价比较高昂，主要用在商用电脑上，对于个人电脑，主要是 多核处理器

2. 多核处理器: 其实际上是(对称多处理器 SMP)的简化版，思想是'将多个处理器合并在一起打包出售，它们之间共享比较昂贵的缓存部件，只保留了多个核心'。在逻辑上看，
   它们和 SMP 完全相同


// !! 1.3 站得高,看得远

系统软件: 一般用于管理计算机本身的软件， 主要分为两块：

1. 平台性的：操作系统内核、驱动程序、运行库

2. 程序开发：编译器、汇编器、链接器

计算机系统软件体系结构采用一种层的结构， 每个层次之间都需要相互通信，那么它们之间就有通信协议， 我们将它称为接口，接口下层是提供者，定义接口。
上层是使用者，使用接口实现所需功能。

除了硬件和应用程序， 其他的都是中间层，每个中间层都是对它下面的那层的包装和扩展。它们使得应用程序和硬件之间保持相对独立。

从整个层次结构来看，开发工具与应用程序属于同一个层次，因为它们都使用同一个接口—操作系统'应用程序编程接口(API)'。应用程序接口的提供者是运行库（Runtime Lib）, 
什么样的运行库提供什么样的接口。winsows 的运行库提供 Windows API，Linux 下的 Glibc 库提供 POSIX 的 API

'运行库（Runtime Lib）'使用操作系统提供的'系统调用接口（System Call Interface）'， 系统调用接口（System Call Interface）在实现中往往以'软件中断
（Software Interrupt）'的方式提供

'操作系统内核(Kernal)层' 对于硬件（Hardware）层来说是硬件接口的使用者， 而硬件是接口的定义者。这种接口叫做'硬件规格（HardWare Specification）'。


// !! 1.4 操作系统做了什么

'操作系统的一个功能是提供抽象的接口, 另外一个主要功能是管理硬件资源'。一个计算机中的资源主要分 CPU、存储器（包括内存和磁盘）和 I/O 设备。

// !!! 1.4.1 不要让 CPU 打盹

1. 多道程序(MultiPrograming): 编译一个监控程序, 当程序不需要使用CPU时, 将其他在等待 CPU 的程序启动。 但它的弊端是不分轻重缓急，有时候一个交互操作可能要
   等待数十分钟

2. 分时系统（Timing-Sharing System）:每个CPU运行一段时间后, 就主动让出给其他 CPU 使用（完整的操作系统雏形在此时开始出现）， 但当一个程序进入死循环的时候，
   无法主动让出CPU， 那么整个系统都无法响应。

3. 多任务系统（Multi-tasking）：操作系统接管了所有的硬件资源， 并且本身运行在一个受硬件保护的级别。 所有的应用都以进程的方式运行在比操作系统更低的级别，
   每个进程都有自己独立的地址空间，进程之间的地址空间是相互隔离的。CPU 由操作系统进行统一分配，每个进程根据进程优先级的高低都有机会获得 CPU，但如果运行超
   过一定的时间，操作系统会将 CPU 资源分配给其他进程，这种 CPU 分配方式是抢占式。如果操作系统分配每个进程的时间很短，就会造成很多进程都在同时运行的假象，
   即所谓的'宏观并行，微观串行'。

4. 设备驱动

   操作系统作为硬件层的上层， 它是对硬件的管理和抽象。对于操作系统上面的运行库和应用程序来说， 它们只希望看到一个统一的硬件访问模式。当成熟的操作系统
   出现后，硬件逐渐成了抽象的概念。在 UNIX 中， 硬件设备的访问形式和访问普通的文件形式一样。


5. 磁盘的结构

   一个硬盘往往有多个盘片，每个盘片分两面，每面按照同心圆划分为若干磁道，每个磁道划分为若干扇区，每个扇区一般 512 字节


// !! 1.5 内存不够怎么办

在早期计算机中，程序是直接运行在物理内存上的，程序所访问的都是物理地址。那么如何将计算机有限的地址分配给多个程序使用, 直接按物理内存分配将产生很多问题：

1. '地址空间不隔离'

    所有的程序都直接访问物理地址，导致程序使用的物理地址不是相互隔离的, 恶意的程序很容易串改其他程序的内存数据

2. '内存使用效率低'

    由于没有有效的内存管理机制, 通常一个程序执行的时候，监控程序要将整个程序读入。内存不够的时候，需要先将内存中的程序读出，保存在硬盘上，才能将需要运行
    的程序读入。这样会使得整个过程有大量数据换入换出。

3. '程序运行地址不确定'

    每次程序运行都需要内存分配一块足够大的内存空间, 使得这个地址是不确定的。但在程序编写的时候，它访问的数据和指令跳转的目标地址都是固定的，这就涉及到
    了程序的'重定向问题'。

// !! 增加中间层：使用一种间接的地址访问方法, 我们把程序给出的地址看作一种虚拟地址。虚拟地址是物理地址的映射，只要处理好这个过程，就可以起到隔离的作用

// !! 1.5.1 关于隔离

普通的程序它只需要一个简单的执行环境, 一个单一的地址空间，有自己的 CPU

1. 物理空间

   就是物理内存。对于 32 位的机器，地址线就有 32 条，物理空间4G， 但如果值装有 512M 的内存，那么实际有效的空间地址就是 0x00000000~0x1FFFFFFF，其他部
   分都是无效的

2. 虚拟空间

   每个进程都有自己独立的虚拟空间，而且每个进程只能访问自己的空间地址， 这样就有效的做到了进程隔离


// !! 1.5.2 分段（Segmentation）

基本思路: 把一段与程序所需要的内存空间大小的虚拟空间映射到某个地址空间。 虚拟空间的每个字节对应物理空间的每个字节。这个映射过程由软件来完成。'分段的方式可以
解决之前的第一个（地址空间不隔离）和第三个问题（程序运行地址不确定）' 但是第二问题内存使用效率问题依旧没有解决

// !! 1.5.3 分页(Paging)

基本方法：把地址空间人为的分成固定大小的页，每一页大小有硬件决定或硬件支持多种大小的页，由操作系统决定页的大小。目前几乎所有的 PC 上的操作系统都是
4KB 大小的页。

'把进程的虚拟地址空间按页分割'，把常用的数据和代码页转载到内存中， 把不常用的代码和数据保存到磁盘里， 当需要的时候从磁盘取出来

虚拟空间的页叫做'虚拟页（VP）',物理内存中页叫做'物理页(PP)'，把磁盘中的页叫做'磁盘页(DP)'

// !! 虚拟空间有的页被映射到同一个物理页, 这样就可以实现内存共享

当进程需要一个页时, 这个页是磁盘页(DP)时, 硬件会捕获到这个消息，就是所谓的页错误(page fault)，然后操作系统接管进程，负责从磁盘中读取内容装入内存中，
然后再将内存和这个页建立映射关系。

保护也是页映射的目的之一，每个页都可以设置权限属性，只有操作系统可以修改这些属性，这样操作系统就可以保护自己保护进程

虚拟存储的实现需要依靠硬件支持，所有硬件都采用一个叫做 MMU 的部件来进行页映射

'CPU 发出虚拟地址经过 MMU 转换成物理地址'，MMU 一般都集成在 CPU 内部


// !! 1.6 众人拾柴火焰高

