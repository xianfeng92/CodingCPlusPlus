
// !! 程序员的知识结构

// !! 抓住不变量

把知识分为 essential 和 non-essential。 对于前者采取提前深入掌握牢靠的办法, 对于后者采取待用到的时刻 RTM (Read the manual)方法

// !! 对程序员来说 essential 的知识

1. 硬件体系结构是 essential
   并不是说硬件体系结构就要了解到逻辑门、晶体管层面才行（其实要了解到这个层面代价也很小，一两本好书就行了），也并不是说就要通读《Computer Architecture: Quantitative Approach》
   才行。而是关键要了解那些重要的思想（很长时间不变的东西）, 而不是很细的技术细节（易变的东西）

2. 操作系统的一些重要的实现机制是 essential
3. 主流编程范式（OO、FP）是为了满足什么需求出现的（出现是为了解决什么问题）, 是怎么解决的, 自身又引入了哪些新的问题, 从而适用哪些场景

4. 分析问题解决问题的思维方法（这个东西很难读一两本书就掌握，需要很长时间的锻炼和反思）

5. 判断与决策的方法（生活中需要进行判断与决策的地方远远多于我们的想象）,波普尔曾经说过: All Life is Problem-Solving


// !! 为什么需要预先牢靠掌握这些 essential 的知识 ?

1. 编程语言技术是对底层设备的封装, 然而封装总是会出现漏洞的, 于是程序员被迫下到“下水道”当中去解决问题, 一旦往下走, 漂亮的 OO、N 层抽象就
   不复存在了, 这时候不具备坚硬的底层知识就会无法解决问题。简而言之就是这些底层知识会无可避免的需要用到，既然肯定会被用到那还是预先掌握的好,
   否则一来用到的时候再查是来不及.

2. 如果你不知道某个工具的存在, 遇到问题的时候是很难想到需要使用这么样一个工具的 essential knowldge 就是使用最为广泛的工具, 编程当中遇到
   某些问题之后, 如果缺乏底层知识, 你甚至都不知道需要去补充哪些底层知识才能解决这个问题。

3. 你必须首先熟悉你的工具, 才能有效地使用它（须知工具的强是无敌的, 但这一切得以“了解你的工具”为前提, 甚至得以“了解目前可能有哪些工具适合
   你的问题”为前提). 一门语言, 你必须了解它的适用场景, 不适用场景; 你必须了解它支持的主要编程范式; 此外你还必须了解它的 traps 和 pitfalls
   (缺陷和陷阱, 如果不知道陷阱的存在, 掉进去也不知道怎么掉的）