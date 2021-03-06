
// !! 开篇

// !! 　一次友好的对话

一位程序员曾问我一个很简单的问题:"怎样给一个磁盘文件排序 ?", 想当年我是一上来就犯了错误, 现在, 在讲这个故事之前, 先给大家一个机会, 看看能否比我当年做得更好。
你会怎样回答上述问题呢?

我错就错在马上回答了这个问题。我告诉他一些有关如何在磁盘上实现归并排序的简要思路。'我建议他深入研究算法教材,他似乎不太感冒。他更关心如何解决这个问题,而不是深入
学习'。于是我告诉他在一本流行的程序设计书里有磁盘排序的程序。那个程序有大约 200 行代码和十几个函数,我估计他最多需要一周时间来实现和测试该代码。

我以为已经解决了他的问题, 但是他的踌躇使我返回到了正确的轨道上。

Q:'为什么非要自己编写排序程序呢? 为什么不用系统提供的排序功能呢?'

A: 我需要在一个大系统中排序。由于不明的技术原因, 我不能使用系统中的文件排序程序


Q: '需要排序的内容是什么？文件中有多少条记录？每条记录的格式是什么？'

A: 文件最多包含 1 000 万条记录,每条记录都是 7 位的整数


Q: 等一下, 既然文件这么小, 何必非要在磁盘上进行排序呢？为什么不在内存里进行排序呢？

A: 尽管机器有许多兆字节的内存, 但排序功能只是大系统中的一部分, 所以, 估计到时只有 1 MB 的内存可用


Q: 你还能告诉我其他一些与记录相关的信息吗?

A: 每条记录都是 7 位的正整数, 再无其他相关数据。每个整数最多只出现一次。


这番对话让问题更明确了。在美国, 电话号码由 3 位区号后再跟 7 位数字组成。拨打含免费区号 800 (当时只有这一个号码) 的电话是不收费的。实际的免费电话号码数据库包含
大量的信息:免费电话号码、呼叫实际中转到的号码(有时是几个号码,这时需要一些规则来决定哪些呼叫在什么时间中转到哪里)、主叫用户的姓名和地址等。

这位程序员正在开发这类数据库的处理系统的一小部分,'需要排序的整数就是免费电话号码'。输入文件是电话号码的列表（已删除所有其他信息）,号码重复出现算出错。期望的输出
文件是以升序排列的电话号码列表。

应用背景同时定义了相应的性能需求。当与系统的会话时间较长时,用户大约每小时请求一次有序文件,并且在排序未完成之前什么都干不了。因此,排序最多只允许执行几分钟,10 
秒是比较理想的运行时间。



// !! 准确的问题描述

对程序员来说, 这些需求加起来就是:"如何给磁盘文件排序?",在试图解决这个问题之前, 先将已知条件组织成一种更客观、更易用的形式。

输入: 一个最多包含 n 个正整数的文件,每个数都小于 n, 其中 n = 10^7。如果在输入文件中有任何整数重复出现就是致命错误。没有其他数据与该整数相关联。

输出: 按升序排列的输入整数的列表。

约束: 最多有(大约) 1 MB 的内存空间可用, 有充足的磁盘存储空间可用。运行时间最多几分钟, 运行时间为 10 秒就不需要进一步优化了。

请花上一分钟思考一下该问题的规范说明。现在你打算给程序员什么样的建议呢? 



// !! 程序设计

显而易见的方法是以一般的基于磁盘的归并排序程序为起点,但是要对其进行调整, 因为我们是对整数进行排序。这样就可以将原来的 200 行程序减少为几十行, 同时也使得程序
运行得更快, 但是完成程序并使之运行可能仍然需要几天的时间。


另一种解决方案更多地利用了该排序问题的特殊性。如果每个号码都使用 7 字节来存储, 那么在可用的 1 MB 存储空间里大约可以存 143 000 个号码。如果每个号码都使用 32 
位整数来表示的话, 在 1 MB 存储空间里就可以存储 250 000 个号码。因此, 可以使用遍历输入文件 40 趟的程序来完成排序。

只有在输入文件中的所有整数都可以在可用的 1 MB 内存中表示的时候才能够实现该方案。

'于是问题就归结为是否能够用大约 800 万个可用位来表示最多 1 000 万个互异的整数'。

// !! 实现概要

'由是观之, 应该用位图或位向量表示集合'。可用一个 20 位长的字符串来表示一个所有元素都小于 20 的简单的非负整数集合。例如, 可以用如下字符串来表示集合
{1, 2, 3, 5, 8, 13}:

0 1 1 1 0 1 0 0 1 0 0 0 0 1 0 0 0 0 0 0

代表集合中数值的位都置为 1, 其他所有的位都置为 0。

在我们的实际问题中, 每个 7 位十进制整数表示一个小于 1 000 万的整数。我们使用一个具有 1 000 万个位的字符串来表示这个文件, 其中, 当且仅当整数 i 在文件中存
在时,第 i 位为 1。

这种表示利用了该问题的三个在排序问题中不常见的属性:输入数据限制在相对较小的范围内; 数据没有重复;而且对于每条记录而言,除了单一整数外,没有任何其他关联数据。

若给定表示文件中整数集合的位图数据结构,则可以分三个自然阶段来编写程序。第一阶段将所有的位都置为 0, 从而将集合初始化为空。第二阶段通过读入文件中的每个整数来建
立集合, 将每个对应的位都置为 1。第三阶段检验每一位, 如果该位为 1, 就输出对应的整数, 由此产生有序的输出文件。

令 n 为位向量中的位数(在本例中为 10 000 000), 程序可以使用伪代码表示如下:

phase 1: initialize set to empty
     for i = [0, n)
         bit[i] = 0
phase 2: insert present elements into the set
     for each i in the input file
         bit[i] = 1
phase 3: write sorted output
     for i = [0, n)
         if bit[i] == 1
              write i on the output file


这个实现概要已经足以解决那个程序员的问题了。


// !! 原理

那个程序员打电话把他的问题告诉我, 然后我们花了大约一刻钟时间明确了问题所在, 并找到了位图解决方案。他花了几小时来实现这个几十行代码的程序。该程序远远优于我们在电
话刚开始时所担心的需要花费一周时间编写的几百行代码的那个程序。而且程序执行得很快: 磁盘上的归并排序可能需要许多分钟的时间,该程序所需的时间只比读取输入和写入输出
所需的时间多一点点——大约 10 秒。

从这些事实中可以总结出该实例研究所得到的第一个结论:'对小问题的仔细分析有时可以得到明显的实际益处'。

除了需要精巧的编程以外，该实例阐明了如下一般原理。

1. 正确的问题。明确问题, 这场战役就成功了 90%

2. 位图数据结构。该数据结构描述了一个有限定义域内的稠密集合, 其中的每一个元素最多出现一次并且没有其他任何数据与该元素相关联

3. 多趟算法。这些算法多趟读入其输入数据, 每次完成一步

4. 时间-空间折中与双赢。编程文献和理论中充斥着时间—空间的折中: 通过使用更多的时间, 可以减少程序所需的空间

5. 简单的设计。Antoine de Saint-Exupéry 是法国作家兼飞机设计师，他曾经说过:"设计者确定其设计已经达到了完美的标准不是不能再增加任何东西, 而是不能再减少任何
   东西"。更多的程序员应该使用该标准来检验自己完成的程序。'简单的程序通常比具有相同功能的复杂的程序更可靠、更安全、更健壮、更高效，而且易于实现和维护'。


// !! 习题

1. 如果不缺内存, 如何使用一个具有库的语言来实现一种排序算法以表示和排序集合?

#include <set>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
    set<int> s;
    int input_num;
    fstream input_file("num_sequence_input.txt");
    if(infile.is_open()){
        while(getline(infile, input_num)){
            s.insert(input_num);
        }
    }
    for(auto elem : s){
        cout << elem.first << endl;
    }
    return 0;
}


// !! 2. 如何使用位逻辑运算 (如与、或、移位) 来实现位向量?

1. 位运算: & (按位与)、| (按位或)、>> 和 << (移位)、^ (异或)、~(取反)

位运算实现位向量主要用前三个位运算。


2. 位向量：顾名思义, 位向量就是用一些二进制位组成的向量。在很多的情况下, 我们可以用一个二进制表示一个对象。但是, 我们不能直接用一个变量名直接表示一个位
  (单独一个位组成的数据类型是不存在的),于是,我们就可以考虑将多个位组成基本的数据类型, 然后通过对这个基本的数据类型进行操作, 从而达到对位进行操作的目的。同时,
  为了方便, 把由位组成的基本数据类型组成数组, 这样就可以对一定范围的为位数据集合进行操作了。

3. 如何真正的操作位向量: 对位向量各位的操作不能直接通过名称去访问, 只能通过位置去操作, 也就是我们要操作第几位数。在我们看来, 位是由 0-n 连续的,实际上,我们是
   用基本数据类型数组来存储的,因为这些位存在于不同的数组元素之中,分布于不同数组的不同位置当中。假设我们以 int 类型作为基本数据类型,则一个 int 类型可以存储 32
   个位。则对于一个特定的位(pos), 我们要先求出它处于哪个数组之中 (pos/32), 然后求出该位在这个数组中具体的位置(pos%32)


4. 对于位的具体操作有三个:对特定位 置1, 对特定位 清0, 判断特定位

5. 想要对位进行操作, 还要理解下面几个表示:
