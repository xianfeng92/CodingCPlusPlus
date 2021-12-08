// !! 为什么用 C++ 工作

// !! 小项目的成功

很多最成功的、最有名的软件最初是由少数人开发出来的。这些软件后来可能逐渐成长，然而，令人吃惊的是许多真正的赢家都是从
小系统做起的。

'绝大多数称职的程序员能在一两个小时内写完一个 100 行的程序，而在大项目中通常每个程序员每天平均只写 10 行代码'

1. 开销

'有些负面的经济效益是由于项目组成员之间相互交流需要大量时间'

基于这一点，就必须要有某种正规的机制，保证每个项目成员对于其他人在做什么都了解得足够清楚，这样才能确保所有的部分最终能拼
在一起。随着项目的扩大，这种机制将占用每个人更多的时间，同时每个人要了解的东西也会更多。


2. // !! 质疑软件工厂

当项目达到一定规模时，尽管作了百般努力，所有的一切好像还是老出错。

有些人认为大项目的开销是在所难免的, 这种态度的结果就是产生了有着'过多管理开销的复杂系统'。然而，更常见的情况是，'这些所谓的管理最终不过
是另一种经过精心组织的开销。开销还在，只是被放进干净的盒子和图表中，因此也更易于理解'。

有些人沉迷于这种开销。他们心安理得地那么做，就好像它是件“好事”——就好像这种开销真地能促进而不是阻碍高效的软件开发。'毕竟，如果一定的管理和
组织是有效的，那么更多的管理和组织就应该更有效'。

我猜想，这个想法给程序项目引进的纪律和组织，与为工厂厂房引进生产流水线一样。

我希望这些人错了。实际上我所接触过的软件工厂给我的感觉很不愉快。'每个单独的功能都是一个巨大机器的一部分，“系统”控制一切，人也要遵从它。正是
这种强硬的控制导致生产线成为劳资双方众多矛盾的焦点'。

所幸的是，我并不认为软件只能朝这个方向发展。'软件工厂忽视了编程和生产之间的本质区别'。工厂是制造大量相同（或者基本相同）产品的地方。它讲求规模
效益，在生产过程中充分利用了分工的优势。最近，它的目标已经变成了要完全消除人力劳动。相反，'软件开发主要是要生产数目相对较少的、彼此完全不同的人
造产品'。这些产品可能在很多方面相似，但是如果太相似，开发工作就变成了机械的复制过程了，这可能用程序就能完成。因此，软件开发的理想环境应该不像工厂，
而更像机械修理厂——在那里，'熟练的技术工人可以利用手边所有可用的精密工具来尽可能地提高工作效率'。

'实际上，只要在能控制的范围内，程序员（当然指称职的）就总是争取让他们的机器代替自己做它们所能完成的机械工作'。毕竟，机器擅长干这样的活儿，而人很
容易产生厌倦情绪。随着项目规模越来越大，越来越难以描述，'这种把程序员看成是手工艺人的观点也渐渐变得难以支持了'。因此，我曾尝试描述应该如何将一个
庞大的编程问题当作一系列较小的、相互独立的编程问题看待。为了做到这一点，我们首先必须把大系统中各个小项目之间存在的关系理顺，使得相关人员不必反复
互相核查。'换言之，我们需要项目之间有接口，这样，每个项目的成员几乎不需要关心接口之外的东西'。这些接口应该像那些常用的子程序和数据结构的抽象一样
成为程序员开发工具中的重要组成部分。



3. 抽象

我最钟情的工具有一个共性，那就是抽象的概念。当我在处理大问题的时候，这样的工具总是能帮助我将问题分解成独立的子问题，并能确保它们相互独立。也就是
说，当我处理问题的某个部分的时候，完全不必担心其他部分

'高级语言提供了更复杂的抽象'。甚至用表达式替代一连串单独的算术指令的想法，也是非常重大的。。

抽象如此有用，因此程序员们不断发明新的抽象，并且运用到他们的程序中。结果就是'几乎所有重要的程序都给用户提供了一套抽象'。

// !! 有些抽象不是语言的一部分

考虑一下文件的概念。事实上每种操作系统都以某种方式使文件能为用户所用。每个程序员都知道文件是什么。但是，在大多数情况下，文件根本不是物理存
在的！文件只是组织长期存储的数据的一种方式，并由程序和数据结构的集合提供支持来实现这个抽象。

// !! 抽象和规范

'操作系统提供了一定程度的保护措施，而编程语言通常没有'。那些编写新的抽象给其他程序员用的程序员，往往不得不依靠用户自己去遵守编程语言技术上的
限制。这些用户不仅要遵守语言的规则，还要遵守其他程序员制定的规范

'要成功地使用抽象，必须遵循一些规范'。要成功地使用动态内存，程序员必须：

1. 知道要分配多大内存
2. 不使用超出分配的内存范围外的内存
3. 不再需要时释放内存
4. 只有不再需要时，才释放内存
5. 只释放分配的内存
6. 切记检查每个分配请求，以确保成功


// !! 抽象和内存管理

有些语言通过垃圾收集（garbage collection）来解决这个问题，这是一种当内存空间不再需要时自动回收内存的技术。垃圾收集使得编写程序时能更方
便地采用灵活的数据结构，但要求系统在运行速度、编译器和运行时系统复杂度方面付出代价。另外，垃圾回收只回收内存，不管理其他资源。

C++ 采用了另外一种更不同寻常的方法：'如果某种数据结构需要动态分配资源，则数据结构的设计者可以在构造函数和析构函数中精确定义如何释放该结构
所对应的资源'。

这种机制不是总像垃圾收集那样灵活，但是在实践中，它与许多应用更接近。另外，与垃圾收集比起来它有一个明显的优势，就是对环境要求低得多：内存一旦
不用了就会被释放，而不是等待垃圾收集机制发现之后才释放。

'用抽象的眼光看待数据结构，它们中的许多都有关于初始化和终止的概念，而不是单纯地只有内存分配'。

C++ 的很多地方也都用到了抽象和接口。其间的关键就是要能够把问题分解为完全独立的小块。这些小块不是通过规则相互联系的，而是通过类定义和对成员函数
和友元函数的调用联系起来的。不遵守规则，就会马上收到由编译器而不是由异常征兆的出错程序发出的诊断消息。


// !! 机器应该为人服务

为什么我要关注语言和抽象？

因为我认为大项目是无法高效地、顺利地投入使用的，也不可能加以管理。我从没见过，也不能想象，会有一种方法使得一个庞大的项目能够对抗所有这些问题。
'如果我能找到把大项目化解为众多小问题的方法，就能引入个体优于混乱的整体、人类优于机器的因素'。// !! 我们必须做工具的主人，而不是其他任何角色。
















