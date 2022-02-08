
// !! 让自己习惯 C++ Accustoming Yourself to C++

不论你的编程背景是什么，C++ 都可能让你觉得有点儿熟悉。它是一个威力强大的语言，带着众多特性，但是在你可以驾驭其威力并有效运用其特性之前，'你必须先习惯
C++ 的办事方式'。

// !! 条款01:视 C++ 为一个语言联邦

一开始，C++ 只是 C 加上一些面向对象特性。C++ 最初的名称 C with Classes 也反映了这个血缘关系。

但是当这个语言逐渐成熟，它变得更活跃更无拘束，更大胆更冒险，'开始接受不同于 C with Classes 的各种观念、特性和编程战略'。

1. Exceptions (异常)对函数的结构化带来不同的做法

2. templates (模板)将我们带到新的设计思考方式

3. STL 则定义了一个前所未见的伸展性做法

'今天的 C++ 已经是个多重范型编程语言(multiparadigm programming language)'，一个同时支持过程形式(procedural)、面向对象形式(object-oriented)、
函数形式(functional)、泛型形式(generic)、元编程形式(metaprogramming)的语言。'这些能力和弹性使 C++ 成为一个无可匹敌的工具'，但也可能引发某些迷惑:
所有“适当用法”似乎都有例外。

我们该如何理解这样一个语言呢？

'最简单的方法是将 C++ 视为一个由相关语言组成的联邦而非单一语言'。在其某个次语言(sublanguage)中，各种守则与通例都倾向简单、直观易懂、并且容易记住。
然而当你从一个次语言移往另一个次语言，守则可能改变。

为了理解C++，你必须认识其主要的次语言。幸运的是总共只有四个:

    1. C: 说到底 C++  仍是以 C 为基础。区块(blocks)、语句(statements)、预处理器(preprocessor)、内置数据类型(built-in data types)、
    数组(arrays)、指针(pointers）等统统来自 C 。'许多时候 C++ 对问题的解法其实不过就是较高级的 C 解法'，但当你以 C++ 内的 C 成分工作时，高效编程守
    则映照出 C 语言的局限：没有模板(templates)，没有异常(exceptions)，没有重载(overloading)……

    2. Object-Oriented C++。这部分也就是 C with Classes 所诉求的: classes(包括构造函数和析构函数)，封装(encapsulation)、继承(inheritance)、
    多态(polymorphism)、virtual函数(动态绑定)……等等。这一部分是面向对象设计之古典守则在 C++ 上的最直接实施。

    3. Template C++。这是 C++ 的泛型编程(generic programming)部分，也是大多数程序员经验最少的部分。'Template 相关考虑与设计已经弥漫整个 C++'，
    良好编程守则中“惟 template 适用”的特殊条款并不罕见。实际上由于 templates 威力强大，它们带来崭新的编程范型(programming paradigm)，也就是所谓的 
    template metaprogramming(TMP，模板元编程)。除非你是 template 激进团队的中坚骨干，大可不必太担心这些。TMP 相关规则很少与 C++ 主流编程互相影响。

    4. STL。STL 是个 template 程序库，看名称也知道，但它是非常特殊的一个。'它对容器(containers)、迭代器(iterators)、算法(algorithms)以及函数对
    象(function objects)的规约有极佳的紧密配合与协调'，然而 templates 及程序库也可以其他想法建置出来。STL 有自己特殊的办事方式，当你伙同 STL 一起工作
    ，你必须遵守它的规约。

记住这四个次语言，当你从某个次语言切换到另一个，高效编程守则要求你改变策略时，不要感到惊讶。

1. 对内置(也就是C-like)类型而言 pass-by-value 通常比 pass-by-reference 高效

2. 当你从 C part of C++ 移往 Object-Oriented C++，'由于用户自定义(user-defined)构造函数和析构函数的存在， pass-by-reference-to-const 往往
   更好'。

3. 而一旦跨入 STL 你就会了解，'迭代器和函数对象都是在 C 指针之上塑造出来的'，所以对 STL 的迭代器和函数对象而言，旧式的 C pass-by-value 守则再次适用

因此我说，C++ 并不是一个带有一组守则的一体语言; 它是从四个次语言组成的联邦政府，每个次语言都有自己的规约。记住这四个次语言你就会发现 C++ 容易了解得多。

// !! 请记住

■ C++ 高效编程守则视状况而变化，取决于你使用 C++ 的哪一部分。


// !! 尽量以 const，enum，inline 替换 ＃define

这个条款或许改为"以编译器替换预处理器"比较好，因为或许 ＃define 不被视为语言的一部分。

那正是它的问题所在。当你做出这样的事情:

#define ASPECT_RATIO 1.653

符号名称 ASPECT_RATIO 也许从未被编译器看见; 也许在编译器开始处理源码之前它就被预处理器移走了。于是符号名称 ASPECT_RATIO 有可能没进入符号表
(symbol table)内。于是当你运用此常量但获得一个编译错误信息时，可能会带来困惑，因为这个错误信息也许会提到 1.653 而不是 ASPECT_RATIO。如果 
ASPECT_RATIO 被定义在一个非你所写的头文件内，你肯定对 1.653 以及它来自何处毫无概念，于是你将因为追踪它而浪费时间。

解决之道是以一个常量替换上述的宏(＃define):

const double AspectRatio = 1.653

1. 作为一个语言常量，AspectRatio 肯定会被编译器看到，当然就会进入符号表内。

2. 此外对浮点常量(floating point constant)而言，使用常量可能比使用 ＃define 导致较小量的码，因为预处理器"盲目地将宏名称 ASPECT_RATIO 替换为 1.653"
  可能导致目标码(object code)出现多份 1.653，若改用常量 AspectRatio 绝不会出现相同情况。

当我们以常量替换 ＃defines，有两种特殊情况值得说说。

1. 第一是定义常量指针(constant pointers)。'由于常量定义式通常被放在头文件内(以便被不同的源码含入)'，因此有必要将指针(而不只是指针所指之物)声明为
   const。例如若要在头文件内定义一个常量的(不变的) char*-based 字符串，你必须写 const 两次:

const char* const authorName = "Scote Meyer";

'这里值得先提醒你的是，string 对象通常比其前辈 char*-based 合宜'，所以上述的  authorName 往往定义成这样更好些:

const std::string authorName("Scote Meyer");

2. 第二个值得注意的是 class 专属常量。'为了将常量的作用域(scope) 限制于 class 内，你必须让它成为 class 的一个成员(member)'；而为确保此常量至多只有
   一份实体，你必须让它成为一个 static 成员:

class GamePlayer
{
private:
    static const int NumTurns = 5;// 常量声明式
    int scores[NumTurns];// 使用该常量
    ...
};

然而你所看到的是 NumTurns 的声明式而非定义式。'通常 C++ 要求你对你所使用的任何东西提供一个定义式'，但如果它是个 class 专属常量又是 static 且为整数类型(integral type，例如 int，chars，bools)，则需特殊处理。只要不取它们的地址，你可以声明并使用它们而无须提供定义式。

但如果你取某个 class 专属常量的地址，或纵使你不取其地址而你的编译器却(不正确地)坚持要看到一个定义式，你就必须另外提供定义式如下:

const GamePlayer::NumTurns;// NumTurns 的定义

请把这个式子放进一个实现文件而非头文件。由于 class 常量已在声明时获得初值(例如先前声明 NumTurns 时为它设初值 5)，因此定义时不可以再设初值。

顺带一提，请注意，我们无法利用 ＃define 创建一个 class 专属常量，因为 ＃defines 并不重视作用域（scope）。一旦宏被定义，它就在其后的编译过程中有效
（除非在某处被＃undef）。这意味 ＃defines  不仅不能够用来定义 class 专属常量，也不能够提供任何封装性，也就是说没有所谓 private＃define 这样的东西。
而当然 const 成员变量是可以被封装的，NumTurns 就是。

旧式编译器也许不支持上述语法，它们不允许 static 成员在其声明式上获得初值。此外所谓的 "in-class 初值设定" 也只允许对整数常量进行。如果你的编译器不支持上述语法，你可以将初值放在定义式:

class CostEstimate
{
private:
    static const double FudgeFactor;// staic class 常量声明，位于头文件中
};

const double CostEstimate::FudgeFactor = 1.35; // static class  常量定义，位于实现文件中

这几乎是你在任何时候唯一需要做的事。唯一例外是当你在 class 编译期间需要一个 class  常量值，例如在上述的  GamePlayer::scores 的数组声明式中(是的，编译器坚持必须在编译期间知道数组的大小)。这时候万一你的编译器(错误地)不允许“static 整数型 class 常量”完成“ in class 初值设定”，可改用所谓的 "the enum hack" 补偿做法。其理论基础是：“一个属于枚举类型(enumerated type)的数值可权充 int  被使用”，于是  GamePlayer 可定义如下:


class GamePlayer
{
    enum {NumTurns = 5};
    int scores[NumTurns];
    ...
};


3. 另一个常见的 ＃define 误用情况是以它实现宏(macros)。宏看起来像函数，但不会招致函数调用(function call)带来的额外开销。下面这个宏夹带着宏实参，
   调用函数f:

   #define CALL_WITH_MAX(a,b) f((a) >  (b) ? (a) : (b))

   这般长相的宏有着太多缺点，光是想到它们就让人痛苦不堪。

   无论何时当你写出这种宏，你必须记住为宏中的所有实参加上小括号，否则某些人在表达式中调用这个宏时可能会遭遇麻烦。但纵使你为所有实参加上小括号，看看下面
   不可思议的事情:

   int a = 5, b = 0;
   CALL_WITH_MAX(++a,b);
   CALL_WITH_MAX(++a,b-10);

   在这里，调用 f 之前，a 的递增次数竟然取决于“它被拿来和谁比较”！

   幸运的是你不需要对这种无聊事情提供温床,'你可以获得宏带来的效率以及一般函数的所有可预料行为和类型安全性(type safety)'——只要你写出 template inline
   函数:

   template <typename T>
   inline void callWithMax(const  T& a, const T& b)
   {
       f(a>b?a:b);
   }

   这个 template 产出一整群函数，每个函数都接受两个同型对象，并以其中较大者调用 f。此外由于 callWithMax 是个真正的函数，它遵守作用域(scope)和访问规则。

有了 consts、enums 和 inlines，我们对预处理器(特别是 ＃define)的需求降低了，但并非完全消除。＃include 仍然是必需品，而'＃ifdef/＃ifndef 也继续扮演控制编译的重要角色'。目前还不到预处理器全面引退的时候，但你应该明确地给予它更长更频繁的假期。

// !! 请记住

■ 对于单纯常量，最好以 const 对象或 enums 替换 ＃defines
■ 对于形似函数的宏(macros)，最好改用 inline 函数替换 ＃defines


// !! 条款03：尽可能使用 const

'const 的一件奇妙事情是，它允许你指定一个语义约束(也就是指定一个"不该被改动"的对象)，而编译器会强制实施这项约束'。它允许你告诉编译器和其他程序员某值应该
保持不变。只要这(某值保持不变)是事实，你就该确实说出来，因为说出来可以获得编译器的帮助，确保这条约束不被违反。


关键字 const 多才多艺。你可以用它在 classes 外部修饰 global 或 namespace 作用域中的常量，或修饰文件、函数、或区块作用域(block scope)中被声明
为 static 的对象。你也可以用它修饰 classes 内部的 static 和 non-static 成员变量。

'面对指针，你也可以指出指针自身、指针所指物，或两者都(或都不)是 const':

char[] greeting = "Hello";
char *p  = greeting;// non const pointer, non const data
const char* p1 = greeting;//  non const pointer, const data
char* const p2 = greeting;// const pointer, non const data
const char* const p3 = greeting;// const pointer, const data

const 语法虽然变化多端，但并不莫测高深。如果关键字 const 出现在星号左边，表示被指物是常量; 如果出现在星号右边，表示指针自身是常量;如果出现在星号两边，表示被指物和指针两者都是常量。


'STL 迭代器是以指针为根据塑模出来，所以迭代器的作用就像个 T* 指针'。'声明迭代器为 const 就像声明指针为 const 一样(即声明一个 T* const 指针)，表示这个迭代器不得指向不同的东西，但它所指的东西的值是可以改动的'。如果你希望迭代器所指的东西不可被改动(即希望 STL 模拟一个 const T* 指针），你需要的是const_iterator:

std::vector<int> vec;
...
const std::vector<int>::iterator iter = vec.begin();// iter 的作用像个 T * const
*iter = 100；// ok,改变 item 所指的物
++iter;// 错误，item 是个 const

std::vector<int>::const_iterator citer = vec.cbegin();
*citer = 100;// 错误，*citer 是个 const
++citer;// ok

'const 最具威力的用法是面对函数声明时的应用'。

在一个函数声明式内，const 可以和函数返回值、各参数、函数自身(如果是成员函数)产生关联。'令函数返回一个常量值，往往可以降低因客户错误而造成的意外，而又不至于放弃安全性和高效性'。

至于 const 参数，没有什么特别新颖的观念，它们不过就像 local const 对象一样，你应该在必要使用它们的时候使用它们。除非你有需要改动参数或 local 对象，否则请将它们声明为 const。只不过多打 6 个字符，却可以省下恼人的错误，像是“想要键入'=='却意外键成'='”的错误，一如稍早所述。


// !! const 成员函数

将 const 实施于成员函数的目的，是为了确认该成员函数可作用于 const 对象身上。

这一类成员函数之所以重要，基于两个理由:

1. 第一，它们使 class 接口比较容易被理解。这是因为，得知哪个函数可以改动对象内容而哪个函数不行，很是重要。

2. 第二，它们使"操作 const 对象"成为可能

这对编写高效代码是个关键，改善 C++ 程序效率的一个根本办法是以 pass by reference-to-const 方式传递对象，而此技术可行的前提是，我们有 const 成员函数可用来处
理取得(并经修饰而成)的 const 对象。


// !! 成员函数如果是 const 意味什么？

这有两个流行概念: bitwise constness(又称 physical constness) 和 logical constness。

'bitwise const 阵营的人相信，成员函数只有在不更改对象之任何成员变量( static 除外)时才可以说是 const'。也就是说它不更改对象内的任何一个 bit。这种论点的好处是
很容易侦测违反点: 编译器只需寻找成员变量的赋值动作即可。bitwise constness 正是 C++ 对常量性(constness)的定义，因此 const 成员函数不可以更改对象内任何 non
-static 成员变量。


不幸的是许多成员函数虽然不十足具备 const 性质却能通过 bitwise 测试。更具体地说，一个更改了“指针所指物”的成员函数虽然不能算是 const，但如果只有指针（而非其所指
物）隶属于对象，那么称此函数为 bitwise const 不会引发编译器异议。这导致反直观结果。假设我们有一个 TextBlock-like class，它将数据存储为 char* 而不是 string，
因为它需要和一个不认识 string 对象的 C API 沟通:

class CTextBook
{
public:
    ...
    char & operator[](std::size_t position) const// bitwise const 声明
    {
        return pText[position];
    }
private:
    char *pText;
};


这个 class 不适当地将其 operator[] 声明为 const 成员函数，而该函数却返回一个 reference 指向对象内部值。假设暂时不管这个事实，请注意，operator[] 实现代
码并不更改 pText。于是编译器很开心地为 operator[] 产出目标码。它是 bitwise const，所有编译器都这么认定。但是看看它允许发生什么事:


const CTextBook cctb("hello");// 声明一个常量对象
char *pc = &cctb[0];// 调用 const operator()[] 取得一个指针，指向 cctb 的数据
*pc = 'J';// cctb 现在的内容为 “Jello”

这其中当然不该有任何错误：你创建一个常量对象并设以某值，而且只对它调用 const 成员函数。但你终究还是改变了它的值。

这种情况导出所谓的 logical constness。这一派拥护者主张，一个 const 成员函数可以修改它所处理的对象内的某些 bits，但只有在客户端侦测不出的情况下才得如此。例如
你的 CTextBlock class 有可能高速缓存（cache）文本区块的长度以便应付询问：

class CTextBook
{
public:
    ...
    char & operator[](std::size_t position) const// bitwise const 声明
    {
        return pText[position];
    }
private:
    char *pText;
    std::size_t textLength;
    bool lengthIsValid;
};

std::size_t CTextBook::length() const
{
    if(!lengthIsValid)
    {
        textLength = std::strlen(pText);
        lengthIsValid = true;
    }
    return textLength;
}


length  的实现当然不是  bitwise const，因为 textLength 和 lengthIsValid 都可能被修改。这两笔数据被修改对 const CTextBlock 对象而言虽然可接受，但编译
器不同意。它们坚持 bitwise constness。怎么办？

解决办法很简单：利用 C++ 的一个与 const 相关的摆动场：mutable（可变的）。mutable 释放掉 non-static 成员变量的 bitwise constness 约束:

// !! 请记住

■ 将某些东西声明为 const 可帮助编译器侦测出错误用法。const  可被施加于任何作用域内的对象、函数参数、函数返回类型、成员函数本体

■ 编译器强制实施 bitwise constness，但你编写程序时应该使用“概念上的常量性”（conceptual constness

■ 当 const 和 non-const 成员函数有着实质等价的实现时，令 non-const 版本调用 const 版本可避免代码重复


// !! 条款04：确定对象被使用前已先被初始化




