// !! 内存模型和名称空间

C++ 为在内存中存储数据方面提供了多种选择。可以选择数据保留在内存中的时间长度(存储持续性)以及程序的哪一部分可以访问数据(作用域和链接)等。
可以使用 new 来动态地分配内存，而定位 new 运算符提供了这种技术的一种变种。C++ 名称空间是另一种控制访问权的方式。
通常，大型程序都由多个源代码文件组成，这些文件可能共享一些数据, 这样的程序涉及到程序文件的单独编译。

// !! 单独编译

和 C 语言一样，C++ 也允许甚至鼓励程序员将组件函数放在独立的文件中。可以单独编译这些文件，然后将它们链接成可执行的程序。'如果只修改了一个文件，则可以
只重新编译该文件，然后将它与其他文件的编译版本链接'。

这使得大程序的管理更便捷。另外，大多数 C++ 环境都提供了其他工具来帮助管理。例如，'UNIX 和 Linux 系统都具有 make 程序，可以跟踪程序依赖的文件以及这些文件
的最后修改时间。运行 make 时，如果它检测到上次编译后修改了源文件，make 将记住重新构建程序所需的步骤'。大多数集成开发环境(包括 Embarcadero C++ Builder、
Microsoft Visual C++、Apple Xcode 和 Freescale CodeWarrior) 都在 Project 菜单中提供了类似的工具。

谁希望出现更多的问题呢？

'C 和 C++ 的开发人员都不希望，因此他们提供了 #include 来处理这种情况。与其将结构声明加入到每一个文件中，不如将其放在头文件中，然后在每一个源代码文件中包
含该头文件'。这样，要修改结构声明时，只需在头文件中做一次改动即可。另外，也可以将函数原型放在头文件中。因此，可以将原来的程序分成三部分。

1. 头文件：包含结构声明和使用这些结构的函数的原型
2. 源代码文件：包含与结构有关的函数的代码
3. 源代码文件：包含调用与结构相关的函数的代码

'这是一种非常有用的组织程序的策略'。例如，如果编写另一个程序时，也需要使用这些函数，则只需包含头文件，并将函数文件添加到项目列表或 make 列表中即可。

另外，这种组织方式也与 OOP 方法一致。'一个文件（头文件）包含了用户定义类型的定义'；'另一个文件包含操纵用户定义类型的函数的代码'。这两个文件组成了一个软件包，
可用于各种程序中。


'请不要将函数定义或变量声明放到头文件中'。这样做对于简单的情况可能是可行的，但通常会引来麻烦。

下面列出了头文件中常包含的内容:

1. 函数原型

2. 使用 #define 或 const 定义的符号常量

3. 结构声明

4. 类声明

5. 模板声明

6. 内联函数


将结构声明放在头文件中是可以的，因为它们不创建变量，而'只是在源代码文件中声明结构变量时，告诉编译器如何创建该结构变量'。同样，'模板声明不是将被编译的代
码，它们指示编译器如何生成与源代码中的函数调用相匹配的函数定义'。

被声明为 const 的数据和内联函数有特殊的链接属性，因此可以将其放在头文件中，而不会引起问题。

程序 coordin.h、程序 file1.cpp 和程序 file2.cpp 是将程序分成几个独立部分后得到的结果。注意，在包含头文件时，我们使用 "coordin.h"，而不是 <coodin.h>。
'如果文件名包含在尖括号中，则 C++ 编译器将在存储标准头文件的主机系统的文件系统(/usr/include)中查找'；'但如果文件名包含在双引号中，则编译器将首先查找当前
的工作目录或源代码目录(或其他目录，这取决于编译器)。如果没有在那里找到头文件，则将在标准位置查找'。因此在包含自己的头文件时，应使用引号而不是尖括号。

另外，'不要使用 #include 来包含源代码文件，这样做将导致多重声明'。


1. 头文件管理

在同一个文件中只能将同一个头文件包含一次。记住这个规则很容易，但很可能在不知情的情况下将头文件包含多次。例如，可能使用包含了另外一个头文件的头文件。

有一种标准的 C/C++ 技术可以避免多次包含同一个头文件。它是'基于预处理器编译指令' #ifndef(即if not defined)的。

下面的代码片段意味着仅当以前没有使用预处理器编译指令 #define 定义名称 COORDINH 时，才处理 #ifndef 和 #endif 之间的语句:


将这两个源代码文件和新的头文件一起进行编译和链接，将生成一个可执行程序。顺便说一句，虽然我们讨论的是根据文件进行单独编译，但为保持通用性，C++ 标准使用了
术语翻译单元(translation unit)，而不是文件；文件并不是计算机组织信息时的唯一方式。出于简化的目的，本书使用术语文件，您可将其解释为翻译单元。


'多个库的链接'

C++ 标准允许每个编译器设计人员以他认为合适的方式实现名称修饰，因此由不同编译器创建的二进制模块(对象代码文件)很可能无法正确地链接。也就是说，'两个编译器将为
同一个函数生成不同的修饰名称'。名称的不同将使链接器无法将一个编译器生成的函数调用与另一个编译器生成的函数定义匹配。

'在链接编译模块时，请确保所有对象文件或库都是由同一个编译器生成的。如果有源代码，通常可以用自己的编译器重新编译源代码来消除链接错误'。


// !! 存储持续性、作用域和链接性

C++ 使用三种（在 C++11 中是四种）不同的方案来存储数据，这些方案的区别就在于数据保留在内存中的时间。

1.自动存储持续性：在函数定义中声明的变量(包括函数参数)的存储持续性为自动的。它们在程序开始执行其所属的函数或代码块时被创建，在执行完函数或代码块时，
  它们使用的内存被释放。C++ 有两种存储持续性为自动的变量。静态存储持续性: 在函数定义外定义的变量和使用关键字 static 定义的变量的存储持续性都为静态。
  它们在程序整个运行过程中都存在。C++ 有 3 种存储持续性为静态的变量。

2.线程存储持续性(C++11)：当前，多核处理器很常见，这些 CPU 可同时处理多个执行任务。这让程序能够将计算放在可并行处理的不同线程中。如果变量是使用关键字 
  thread_local 声明的，则其生命周期与所属的线程一样长。

3.动态存储持续性: 用 new 运算符分配的内存将一直存在，直到使用 delete 运算符将其释放或程序结束为止。这种内存的存储持续性为动态，有时被称为自由存储
 (free store)或堆(heap)。


// !! 作用域和链接

'作用域(scope) 描述了名称在文件(翻译单元)的多大范围内可见'。例如，函数中定义的变量可在该函数中使用，但不能在其他函数中使用; 而在文件中的函数定义之前定义
的变量则可在所有函数中使用。

链接性(linkage)描述了名称如何在不同单元间共享。'链接性为外部的名称可在文件间共享，链接性为内部的名称只能由一个文件中的函数共享'。自动变量的名称没有链接性，
因为它们不能共享。

C++ 变量的作用域有多种。作用域为局部的变量只在定义它的代码块中可用。代码块是由花括号括起的一系列语句。例如函数体就是代码块，但可以在函数体中嵌入其他代码块。
作用域为全局(也叫文件作用域)的变量在定义位置到文件结尾之间都可用。'自动变量的作用域为局部，静态变量的作用域是全局还是局部取决于它是如何被定义的'。在函数原型
作用域(function prototype scope)中使用的名称只在包含参数列表的括号内可用(这就是为什么这些名称是什么以及是否出现都不重要的原因)。'在类中声明的成员的作用域
为整个类'。'在名称空间中声明的变量的作用域为整个名称空间'(由于名称空间已经引入到 C++ 语言中，因此全局作用域是名称空间作用域的特例)。

C++ 函数的作用域可以是整个类或整个名称空间（包括全局的），但不能是局部的(因为不能在代码块内定义函数，如果函数的作用域为局部，则只对它自己是可见的，因此不能被
其他函数调用。这样的函数将无法运行)。

'不同的 C++ 存储方式是通过存储持续性、作用域和链接性来描述的'。

下面来看看各种 C++ 存储方式的这些特征。首先介绍引入名称空间之前的情况，然后看一看名称空间带来的影响。

// !! 自动存储持续性

在默认情况下, 在函数中声明的函数参数和变量的存储持续性为自动，作用域为局部，没有链接性。也就是说，如果在 main() 中声明了一个名为 texas 的变量，并在函数 
oil() 中也声明了一个名为 texas 变量，则创建了两个独立的变量——只有在定义它们的函数中才能使用它们。对 oil() 中的 texas 执行的任何操作都不会影响 main() 
中的 texas，反之亦然。


另外，当程序开始执行这些变量所属的代码块时，将为其分配内存; 当函数结束时，这些变量都将消失(注意，执行到代码块时，将为变量分配内存，但其作用域的起点为其声明
位置)。

如果在代码块中定义了变量，则该变量的存在时间和作用域将被限制在该代码块内。

例如，假设在 main() 的开头定义了一个名为 teledeli 的变量，然后在 main() 中开始一个新的代码块，并其中定义了一个新的变量 websight，则 teledeli 在内部代
码块和外部代码块中都是可见的，而 websight 就只在内部代码块中可见，它的作用域是从定义它的位置到该代码块的结尾:

int main()
{
  int teledeli = 5;
  {
    cout << "Hello\n";
    int websight = 10;
    cout << "websight " << websight << ' ' << teledeli << '\n';
  }
  cout << teledeli << '\n';
  return 0;
}

然而，如果将内部代码块中的变量命名为 teledeli，而不是 websight，使得有两个同名的变量(一个位于外部代码块中，另一个位于内部代码块中)，情况将如何呢？在这种情况
下，程序执行内部代码块中的语句时，将 teledeli 解释为局部代码块变量。我们说，新的定义隐藏了(hide)以前的定义，新定义可见，旧定义暂时不可见。在程序离开该代码块时
，原来的定义又重新可见。

程序 auto.cpp 表明，自动变量只在包含它们的函数或代码块中可见。

// auto.cpp

#include<iostream>
void oil(int x);

int main()
{
    using namespace std;
    int teaxs = 31;
    int year = 2021;
    cout << "In main " << "teaxs" << teaxs << '\n';
    cout << &teaxs << '\n';
    cout << "In main " << "year" << year << '\n';
    cout << &year << '\n';
    oil(teaxs);
    cout << "In main " << "teaxs" << teaxs << '\n';
    cout << &teaxs << '\n';
    cout << "In main " << "year" << year << '\n';
    cout << &year << '\n';
    return 0;
}

void oil(int x)
{
    using namespace std;
    int teaxs = 5;
    cout << "In oil " << "teaxs" << teaxs << '\n';
    cout << "&teaxs " << &teaxs << '\n';
    cout << "In oil x " << x << "&x is " << &x << '\n';
    {
        int teaxs = 999;
        cout << "In block " << "teaxs is " << teaxs;
        cout << "&teasx is " << &teaxs << '\n';
        cout << "In block x " << x << "&x is " << &x << '\n';
    }
    cout << "Post-block teaxs is " << teaxs;
    cout << "&teaxs is " << &teaxs;
}

1. 自动变量的初始化

可以使用任何在声明时其值为已知的表达式来初始化自动变量，下面的示例初始化变量 x、y 和 z:

int w;// value of w is indeterminate
int x = 5;// initialized with a numeric literal
int y = x*2 -5;
cin >> w;
int z = 3*w;


2. 自动变量和栈

了解典型的 C++ 编译器如何实现自动变量有助于更深入地了解自动变量。

由于自动变量的数目随函数的开始和结束而增减，因此程序必须在运行时对自动变量进行管理。常用的方法是留出一段内存，并将其视为栈，以管理变量的增减。之所以被称为栈，
是由于新数据被象征性地放在原有数据的上面(也就是说，在相邻的内存单元中，而不是在同一个内存单元中)，当程序使用完后，将其从栈中删除。栈的默认长度取决于实现，但编
译器通常提供改变栈长度的选项。程序使用两个指针来跟踪栈，一个指针指向栈底——栈的开始位置，另一个指针指向堆顶——下一个可用内存单元。当函数被调用时，其自动变量将
被加入到栈中，栈顶指针指向变量后面的下一个可用的内存单元。函数结束时，栈顶指针被重置为函数被调用前的值，从而释放新变量使用的内存。

栈是 LIFO（后进先出）的，即最后加入到栈中的变量首先被弹出。这种设计简化了参数传递。函数调用将其参数的值放在栈顶，然后重新设置栈顶指针。被调用的函数根据其形
参描述来确定每个参数的地址。

当函数执行结束时，'栈顶指针重新指向以前的位置。新值没有被删除，但不再被标记，它们所占据的空间将被下一个将值加入到栈中的函数调用所使用'。



// !! 静态持续变量

和 C 语言一样，'C++ 也为静态存储持续性变量提供了 3 种链接性': 外部链接性(可在其他文件中访问)、内部链接性(只能在当前文件中访问)和无链接性(只能在当前函数或代
码块中访问)。这 3 种链接性都在整个程序执行期间存在，与自动变量相比，它们的寿命更长。由于静态变量的数目在程序运行期间是不变的，因此程序不需要使用特殊的装置
(如栈)来管理它们。

'编译器将分配固定的内存块来存储所有的静态变量，这些变量在整个程序执行期间一直存在'。另外，如果没有显式地初始化静态变量，编译器将把它设置为 0。在默认情况下，
静态数组和结构将每个元素或成员的所有位都设置为 0。


下面介绍如何创建这 3 种静态持续变量，然后介绍它们的特点。

1. 要想创建链接性为外部的静态持续变量，必须在代码块的外面声明它

2. 要创建链接性为内部的静态持续变量，必须在代码块的外面声明它，并使用 static 限定符

3. 要创建没有链接性的静态持续变量，必须在代码块内声明它，并使用 static 限定符

下面的代码片段说明这 3 种变量:


int global = 2021;
static int one_file = 990;

{
  static int count = 0;
}

由于 one_file 的链接性为内部，因此只能在包含上述代码的文件中使用它；由于 global 的链接性为外部，因此可以在程序的其他文件中使用它。


所有的静态持续变量都有下述初始化特征:'未被初始化的静态变量的所有位都被设置为0。这种变量被称为零初始化的(zero-initialized)'。


// !! 静态变量的初始化

那么初始化形式由什么因素决定呢？

首先，所有静态变量都被零初始化，而不管程序员是否显式地初始化了它。接下来，如果使用常量表达式初始化了变量，且编译器仅根据文件内容（包括被包含的头文件）就
可计算表达式，编译器将执行常量表达式初始化。必要时，编译器将执行简单计算。如果没有足够的信息，变量将被动态初始化。

请看下面的代码:

#include <cmath>

int x = 10;
int y = 5;
long z = 13 * 13;
const double ps = 4.0 * atan(1.0);

首先，x、y、z 和 pi 被零初始化。然后，编译器计算常量表达式，并将 y 和 z 分别初始化为 5 和 169。'但要初始化 pi，必须调用函数 atan()，这需要等到该函数
被链接且程序执行时'。

常量表达式并非只能是使用字面常量的算术表达式。例如，它还可使用 sizeof 运算符:

int enough = sizeof(long) +1;

C++11 新增了关键字 constexpr，这增加了创建常量表达式的方式。


// !! 静态持续性、外部链接性

链接性为外部的变量通常简称为外部变量，它们的存储持续性为静态，作用域为整个文件。外部变量是在函数外部定义的，因此对所有函数而言都是外部的。例如，可以在
main() 前面或头文件中定义它们。可以在文件中位于外部变量定义后面的任何函数中使用它，因此外部变量也称全局变量(相对于局部的自动变量)。

1.单定义规则

'一方面，在每个使用外部变量的文件中，都必须声明它'; 另一方面，C++ 有"单定义规则"(One Definition Rule，ODR），该规则指出，变量只能有一次定义。

为满足这种需求，C++ 提供了两种变量声明。一种是定义声明(defining declaration)或简称为定义(definition)，它给变量分配存储空间；'另一种是引用声明
(referencing declaration)或简称为声明(declaration)， 它不给变量分配存储空间，因为它引用已有的变量'。

引用声明使用关键字 extern，且不进行初始化; 否则，声明为定义，导致分配存储空间:

double up;// definition, up is 0
extern int year;// year defined elsewhere
extern char gz = 'Z';// definition because initialized


'如果要在多个文件中使用外部变量, 只需在一个文件中包含该变量的定义(单定义规则)， 但在使用该变量的其他所有文件中，都必须使用关键字 extern 声明它'

如果在函数中声明了一个与外部变量同名的变量，结果将如何呢？

这种声明将被视为一个自动变量的定义，当程序执行自动变量所属的函数时，该变量将位于作用域内。程序 external.cpp 和程序 support.cpp 在两个文件中使用了一个
外部变量, 还演示了自动变量将隐藏同名的全局变量。它还演示了如何使用关键字 extern 来重新声明以前定义过的外部变量，以及如何使用 C++ 的作用域解析运算符来访问
被隐藏的外部变量。

// external.cpp
#include <iostream>
using namespace std;

double warming = 0.3;// warming defined

// function prototype
void update(double dt);
void local();

int main()
{
    cout << "Global warming is " << warming << " degrees\n";
    update(0.1);
    cout << "Global warming is " << warming << " degrees\n";
    local();
    cout << "Global warming is " << warming << " degrees\n";
    return 0;
}

// compile with external.cpp
#include<iostream>
extern double warming;// using warming from another

// function prototype
void update(double dt);
void local();

using std::cout;
void update(double dt)
{
    extern double warming;
    warming += dt;
    cout << "Updating global warming to " << warming;
    cout << "degrees.\n";
}


void local()
{
    double warming = 0.8;
    cout << "Local warming is " << warming << " degrees.\n";
    cout << "Bit global warming= " << ::warming;
    cout << " degrees.\n";
}

C++ 比 C 语言更进了一步——它提供了作用域解析运算符(::)。放在变量名前面时, 该运算符表示使用变量的全局版本。

// !! 全局变量和局部变量

既然可以选择使用全局变量或局部变量, 那么到底应使用哪种呢 ？

首先，全局变量很有吸引力, 因为所有的函数能访问全局变量，因此不用传递参数。但易于访问的代价很大---程序不可靠。

'计算经验表明，程序越能避免对数据进行不必要的访问，就越能保持数据的完整性'。通常情况下，应使用局部变量，应在需要知晓时才传递数据，而不应不加区分地使用全
局变量来使数据可用。读者将会看到，OOP 在数据隔离方面又向前迈进了一步。

然而，全局变量也有它们的用处。例如，可以让多个函数可以使用同一个数据块。'外部存储尤其适于表示常量数据，因为这样可以使用关键字 const 来防止数据被修改'。



// !! 静态持续性、内部链接性

将 static 限定符用于作用域为整个文件的变量时, 该变量的链接性将为内部的。在多文件程序中, 内部链接性和外部链接性之间的差别很有意义。链接性为内部的变量只能
在其所属的文件中使用; 但常规外部变量都具有外部链接性，即可以在其他文件中使用。

如果要在其他文件中使用相同的名称来表示其他变量，该如何办呢 ？只需省略关键字 extern 即可吗？

//files1
int errors = 20;

//file2
int errors = 100;

void froobish()
{
  cout << errors;
}

这种做法将失败，因为它违反了单定义规则。file2 中的定义试图创建一个外部变量，因此程序将包含 errors 的两个定义，这是错误。

但如果文件定义了一个静态外部变量，其名称与另一个文件中声明的常规外部变量相同，则在该文件中，静态变量将隐藏常规外部变量:

//files1
int errors = 20;

//file2
static int errors = 100;

void froobish()
{
  cout << errors;
}

这没有违反单定义规则，因为关键字 static 指出标识符 errors 的链接性为内部，因此并非要提供外部定义。

'可使用外部变量在多文件程序的不同部分之间共享数据'； '可使用链接性为内部的静态变量在同一个文件中的多个函数之间共享数据'。另外，如果将作用域为整个文件的变量
变为静态的，就不必担心其名称与其他文件中的作用域为整个文件的变量发生冲突。

twofile1.cpp 和 twofile2.cpp 演示了 C++ 如何处理链接性为外部和内部的变量。twofile1.cpp 定义了外部变量 tom 和 dick 以及静态外部变量 harry。这
个文件中的 main() 函数显示这 3 个变量的地址，然后调用 remote_access() 函数，该函数是在另一个文件中定义的。twofile2.cpp 列出了该文件。除定义 
remote_access() 外，该文件还使用 extern 关键字来与第一个文件共享 tom。接下来，该文件定义一个名为 dick 的静态变量。static 限定符使该变量被限制在这个文
件内，并覆盖相应的全局定义。然后，该文件定义了一个名为 harry 的外部变量，这不会与第一个文件中的 harry 发生冲突，因为后者的链接性为内部的。随后，
remote-access() 函数显示这 3 个变量的地址，以便于将它们与第一个文件中相应变量的地址进行比较。

// twofile1.cpp

#include<iostream>

int tom = 3;
int dick = 30;
static int harry = 300;

// function prototype
void remote_access();

int main()
{
    using namespace std;
    cout << "main reports the following address: ";
    cout << &tom <<" =tom, " << &dick <<" =dick, " << &harry <<" =harry" << '\n';
    remote_access();
    return 0;
}

// twofile2.cpp
#include<iostream>

extern int tom;
extern int dick;

int harry = 200;

void remote_access()
{
    using namespace std;
    cout << "remote_access reports the following address: ";
    cout << &tom <<" =tom, " << &dick <<" =dick, " << &harry <<" =harry" << '\n';
}

 » g++ --std=c++11 twofile1.cpp twofile2.cpp
--------------------------------------------------------------------------------
 » ./a.out

main reports the following address: 0x561cd7a80010 =tom, 0x561cd7a80014 =dick, 0x561cd7a80018 =harry
remote_access reports the following address: 0x561cd7a80010 =tom, 0x561cd7a8001c =dick, 0x561cd7a80020 =harry

从上述地址可知，这两个文件使用了同一个 tom 变量，但使用了不同的 dick 和 harry 变量。具体的地址和格式可能随系统而异，但两个 tom 变量的地址将相同，
而两个 dick 和 harry 变量的地址不同。


// !! 静态存储持续性、无链接性

接下来介绍静态持续家族中的第三个成员——无链接性的局部变量。这种变量是这样创建的，将 static 限定符用于在代码块中定义的变量。
在代码块中使用 static 时，将导致局部变量的存储持续性为静态的。这意味着虽然该变量只在该代码块中可用，但它在该代码块不处于活动状态时仍然存在。因此在两次函数调用
之间，静态局部变量的值将保持不变。

// static.cpp

#include<iostream>

const int ArSize = 10;

//function prototype
void strcount(const char * str);

int main()
{
    using namespace std;
    char input[ArSize];
    char next;

    cout << "Enter a line:\n";
    cin.getline(input,ArSize);
    while(cin)
    {
        cin.get(next);
        while(next != '\n')
        {
            cin.get(next);
        }
        strcount(next);
        cout << "Enter next line[empty to quite]:\n";
        cin.get(input,ArSize);
    }
    cout << "Bye!" << endl;
    return 0;
}

void strcount(const char * str)
{
    using namespace std;
    static int total = 0;
    int count = 0;

    cout << "\"" << str << "\" contains ";
    while(*str++)
    {
        ++count;
    }
    total += count;
    cout << count << "characters，\n"；
    cout << total << " characters total\n";
}

// !! 说明符和限定符

关键字 static 被用在作用域为整个文件的声明中时，表示内部链接性； 被用于局部声明中，表示局部变量的存储持续性为静态的。关键字 extern 表明是引用声明，即声明引
用在其他地方定义的变量。关键字 thread_local 指出变量的持续性与其所属线程的持续性相同。thread_local 变量之于线程，犹如常规静态变量之于整个程序。


// !! 再谈const

在 C++ 中，const 限定符对默认存储类型稍有影响。在默认情况下全局变量的链接性为外部的，但 const 全局变量的链接性为内部的。也就是说，在 C++ 看来，全局 const 
定义就像使用了 static 说明符一样。

const int fingers = 10;

C++ 修改了常量类型的规则，让程序员更轻松。

例如，假设将一组常量放在头文件中，并在同一个程序的多个文件中使用该头文件。 那么，预处理器将头文件的内容包含到每个源文件中后，所有的源文件都将包含类似下面这
样的定义：

const int fingers = 10;

如果全局 const 声明的链接性像常规变量那样是外部的，则根据单定义规则，这将出错。

也就是说，只能有一个文件可以包含前面的声明，而其他文件必须使用 extern 关键字来提供引用声明。另外，只有未使用 extern 关键字的声明才能进行初始化：

extern const int fingers;

因此，需要为某个文件使用一组定义，而其他文件使用另一组声明。然而，由于外部定义的 const 数据的链接性为内部的，因此可以在所有文件中使用相同的声明。

内部链接性还意味着，每个文件都有自己的一组常量，而不是所有文件共享一组常量。

在函数或代码块中声明 const 时，其作用域为代码块，即仅当程序执行该代码块中的代码时，该常量才是可用的。这意味着在函数或代码块中创建常量时，不必担心其名称与其他
地方定义的常量发生冲突。

// !! 函数和链接性

和变量一样，函数也有链接性，虽然可选择的范围比变量小。和 C 语言一样，C++ 不允许在一个函数中定义另外一个函数，因此所有函数的存储持续性都自动为静态的，即在整
个程序执行期间都一直存在。

'在默认情况下，函数的链接性为外部的，即可以在文件间共享'。

实际上，可以在函数原型中使用关键字 extern 来指出函数是在另一个文件中定义的，不过这是可选的。'要让程序在另一个文件中查找函数，该文件必须作为程序的组成部分被编
译，或者是由链接程序搜索的库文件'。

还可以使用关键字 static 将函数的链接性设置为内部的，使之只能在一个文件中使用。必须同时在原型和函数定义中使用该关键字:


static int privite(double x, double y);


static int privite(double x, double y)
{
  ...
}

'这意味着该函数只在这个文件中可见, 还意味着可以在其他文件中定义同名的的函数'。

和变量一样，在定义静态函数的文件中，静态函数将覆盖外部定义，因此即使在外部定义了同名的函数，该文件仍将使用静态函数。

单定义规则也适用于非内联函数, 因此对于每个非内联函数，程序只能包含一个定义。 对于链接性为外部的函数来说，这意味着在多文件程序中，只能有一个文件(该文件可能是
库文件，而不是您提供的) 包含该函数的定义，但'使用该函数的每个文件都应包含其函数原型'。


'C++ 在哪里查找函数'

假设在程序的某个文件中调用一个函数，C++ 将到哪里去寻找该函数的定义呢？

1. 如果该文件中的函数原型指出该函数是静态的, 则编译器将只在该文件中查找函数定义

2. 否则，编译器(包括链接程序)将在所有的程序文件中查找。如果找到两个定义，编译器将发出错误消息，因为每个外部函数只能有一个定义

3. 如果在程序文件中没有找到，编译器将在库中搜索。这意味着如果定义了一个与库函数同名的函数, 编译器将使用程序员定义的版本，而不是库函数


// !! 语言链接性

另一种形式的链接性——称为语言链接性(language linking) 也对函数有影响。

链接程序要求每个不同的函数都有不同的符号名。在 C 语言中，一个名称只对应一个函数，因此这很容易实现。为满足内部需要，C 语言编译器可能将 spiff 这样的函数名翻
译为 _spiff。这种方法被称为 C 语言链接性(C language linkage)。

但在 C++ 中，同一个名称可能对应多个函数，必须将这些函数翻译为不同的符号名称。因此，C++ 编译器执行名称修饰。

例如，可能将 spiff（int） 转换为 _spoff_i，而将 spiff（double，double） 转换为 _spiff_d_d, 这种方法被称为 C++ 语言链接(C++ language linkage)。

链接程序寻找与 C++ 函数调用匹配的函数时，使用的方法与 C 语言不同。但如果要在 C++ 程序中使用 C 库中预编译的函数，将出现什么情况呢？

例如，假设有下面的代码:

spiff(22);

它在 C 库文件中的符号名称为 _spiff，但对于我们假设的链接程序来说，C++ 查询约定是查找符号名称 _spiff_i。

为解决这种问题，可以用函数原型来指出要使用的约定:

extern "C" void spiff(int i);// using c protocal for name look up

extern void spiff(int);// using c++ protocal for name look up

extern "C++" void spiff(int)// using c++ protocal for name look up

第一个原型使用 C 语言链接性；而后面的两个使用 C++ 语言链接性。第二个原型是通过默认方式指出这一点的，而第三个显式地指出了这一点。

C 和 C++ 链接性是 C++ 标准指定的说明符，但实现可提供其他语言链接性说明符。


// !! 存储方案和动态分配

通常，编译器使用三块独立的内存：一块用于静态变量(可能再细分)，一块用于自动变量，另外一块用于动态存储。虽然存储方案概念不适用于动态内存，但适用于用来跟踪动态内
存的自动和静态指针变量。例如，假设在一个函数中包含下面的语句：


float *p_fees = new float[20];

由 new 分配的 80 个字节(假设float为4个字节)的内存将一直保留在内存中，直到使用 delete 运算符将其释放。但当包含该声明的语句块执行完毕时，p_fees 指针将消失。
如果希望另一个函数能够使用这 80 个字节中的内容，则必须将其地址传递或返回给该函数。另一方面，如果将 p_fees 的链接性声明为外部的，则文件中位于该声明后面的所有
函数都可以使用它。另外，通过在另一个文件中使用下述声明，便可在其中使用该指针:

extern float *p_fees;

1. 使用 new 运算符初始化

如果要初始化动态分配的变量，该如何办呢？在 C++98 中，有时候可以这样做，C++11 增加了其他可能性。下面先来看看 C++98 提供的可能性。如果要为内置的标量类型
(如 int 或 double)分配存储空间并初始化，可在类型名后面加上初始值，并将其用括号括起：

int *pi = new int(6);
double *pd = new double(19);

然而，要初始化常规结构或数组，需要使用大括号的列表初始化，这要求编译器支持 C++11。C++11 允许您这样做:


where *one = new where{2.2,32.32};
int *ar = new int[3]{1,2,3};


2. new 失败时

new 可能找不到请求的内存量。在最初的 10 年中，C++ 在这种情况下让 new 返回空指针，但现在将引发异常 std::bad_alloc。


3. new：运算符、函数和替换函数

运算符 new 和 new[] 分别调用如下函数:

void *operator new(std::size_t);
void *operator new[](std::size_t);

这些函数被称为分配函数(alloction function)，它们位于全局名称空间中。同样，也有由 delete 和 delete[] 调用的释放函数(deallocation function):


void operator delete(void *);
void operator delete[](void *);

std::size_t 是一个 typedef，对应于合适的整型。对于下面这样的基本语句:


int *pi = new int;

将被转换为下面这样:

int *pi = new(sizeof(int));

而下面的语句:

int *pa = new int[40];

将被转换为下面这样:

int *pa = new(40*sizeof(int));


同样，下面的语句：

delete pi;

将转换为如下函数调用：

delete(pi);

有趣的是，C++ 将这些函数称为可替换的(replaceable)。这意味着如果您有足够的知识和意愿，可为 new 和 delete 提供替换函数，并根据需要对其进行定制。例如，可
定义作用域为类的替换函数，并对其进行定制，以满足该类的内存分配需求。在代码中，仍将使用 new 运算符，但它将调用您定义的 new() 函数。

4. 定位 new 运算符


通常，new 负责在堆(heap) 中找到一个足以能够满足要求的内存块。new 运算符还有另一种变体，被称为定位(placement) new 运算符，它让您能够指定要使用的位置。'程
序员可能使用这种特性来设置其内存管理规程、处理需要通过特定地址进行访问的硬件或在特定位置创建对象'。

要使用定位 new 特性，首先需要包含头文件 new，它提供了这种版本的 new 运算符的原型；然后将 new 运算符用于提供了所需地址的参数。除需要指定参数外，句法与常规
new 运算符相同。具体地说，使用定位 new 运算符时，变量后面可以有方括号，也可以没有。下面的代码段演示了 new 运算符的 4 种用法:

#include <new>

struct chaff
{
  char dross[20];
  int slag;
};

char buffer1[50];
char buffer2[100];


int main()
{
  char *p1;
  char *p2;
  int *p3;
  int *p4;
  // first the regular form of new
  p1 = new chaff;// place structure in heap
  p3 = new int[20];// place int array in heap

  // now, the two form of place new
  p2 = new (buffer1) chaff;// place structure in buffer1
  p4 = new (buffer2) int[20];// place int array in buffer2
}

出于简化的目的，这个示例使用两个静态数组来为定位 new 运算符提供内存空间。因此，上述代码从 buffer1 中分配空间给结构 chaff，从 buffer2 中分配空间给一个包
含 20 个元素的 int 数组。

熟悉定位 new 运算符后，来看一个示例程序。newplace.cpp 使用常规 new 运算符和定位 new 运算符创建动态分配的数组。该程序说明了常规 new 运算符和定位 new 运算
符之间的一些重要差别，在查看该程序的输出后，将对此进行讨论。

// newplace.cpp

#include<iostream>
#include<new>

const int BUF = 1024;
const int N = 5;
char buffer[BUF];

int main()
{
    using namespace std;
    double *pd1,*pd2;
    int i;
    cout << "Calling new and placement new:\n";
    pd1 = new double[N];// use heap
    pd2 = new (buffer) double[N]; // use buffer array
    for(int i = 0; i < N; i++)
    {
        pd2[i] = pd1[i] = 1000 + 20.0 * i;
    }
    cout << "Memory address :\n" << " heap: " << pd1 << " static: " << (void*)buffer << endl;
    cout << "Memory contents :\n";
    for(int i = 0; i < N; i++)
    {
        cout << pd1[i] << " at "<< &pd1[i] << ";";
        cout << pd2[i] << " at "<< &pd2[i] << endl;
    }
    cout << "Calling new and placement new a second time:\n";
    double *pd3,*pd4;
    pd3 = new double[N];// find new address
    pd4 = new (buffer)double[N];// override old data
    for(int i = 0; i < N; i++)
    {
        pd4[i] = pd3[i] = 1000+40.0*i;
    }
    cout << "Memory contents :\n";
    for(int i = 0; i < N; i++)
    {
        cout << pd3[i] << " at "<< &pd3[i] << ";";
        cout << pd4[i] << " at "<< &pd4[i] << endl;
    }
    cout << "Calling new and placement new a third time:\n";
    delete[] pd1;
    pd1 = new double[N];
    pd2 = new (buffer+N*sizeof(double))double[N];
    for(int i = 0; i < N; i++
    {
        pd2[i] = pd1[i] = 1000 + 60.0 * i;
    }
    cout << "Memory contents :\n";
    for(int i = 0; i < N; i++)
    {
        cout << pd1[i] << " at "<< &pd1[i] << ";";
        cout << pd2[i] << " at "<< &pd2[i] << endl;
    }
    delete[] pd1;
    delete[] pd3;
    return 0;
}


 » g++ --std=c++11 newplace.cpp
--------------------------------------------------------------------------------
 » ./a.out

Calling new and placement new:
Memory address :
 heap: 0x5584aab722c0 static: 0x5584a8f0c160
Memory contents :
1000 at 0x5584aab722c0;1000 at 0x5584a8f0c160
1020 at 0x5584aab722c8;1020 at 0x5584a8f0c168
1040 at 0x5584aab722d0;1040 at 0x5584a8f0c170
1060 at 0x5584aab722d8;1060 at 0x5584a8f0c178
1080 at 0x5584aab722e0;1080 at 0x5584a8f0c180
Calling new and placement new a second time:
Memory contents :
1000 at 0x5584aab722f0;1000 at 0x5584a8f0c160
1040 at 0x5584aab722f8;1040 at 0x5584a8f0c168
1080 at 0x5584aab72300;1080 at 0x5584a8f0c170
1120 at 0x5584aab72308;1120 at 0x5584a8f0c178
1160 at 0x5584aab72310;1160 at 0x5584a8f0c180
Calling new and placement new a third time:
Memory contents :
1000 at 0x5584aab722c0;1000 at 0x5584a8f0c188
1060 at 0x5584aab722c8;1060 at 0x5584a8f0c190
1120 at 0x5584aab722d0;1120 at 0x5584a8f0c198
1180 at 0x5584aab722d8;1180 at 0x5584a8f0c1a0
1240 at 0x5584aab722e0;1240 at 0x5584a8f0c1a8

1. 首先要指出的一点是，定位 new 运算符确实将数组 p2 放在了数组 buffer 中，p2 和 buffer 的地址都是 0x5584a8f0c160。 然而，它们的类型不同，p1 是 double 
   指针，而 buffer 是 char 指针(顺便说一句，这也是程序使用 (void *)对buffer 进行强制转换的原因，如果不这样做，cout 将显示一个字符串）同时，常规 new 将数
   组 p1 放在很远的地方，其地址为 0x5584aab722c0，位于动态管理的堆中


2. 第二个常规 new 运算符查找一个新的内存块，其起始地址为 0x5584aab722f0 ；但第二个定位 new 运算符分配与以前相同的内存块：起始地址为 0x5584a8f0c160 的内
   存块。'定位 new 运算符使用传递给它的地址，它不跟踪哪些内存单元已被使用，也不查找未使用的内存块'。这将一些内存管理的负担交给了程序员
  
3. 在第三次调用定位 new 运算符时，提供了一个从数组 buffer 开头算起的偏移量，因此将分配新的内存:

  pd2 = new (buffer+N*sizeof(double))double[N];// offset of 40 bytes


4. 是否使用delete来释放内存。对于常规new运算符，下面的语句释放起始地址为 0x5584a8f0c160 的内存块，因此接下来再次调用 new 运算符时，该内存块是可用的

delete[] pd1;

然而，程序没有使用 delete 来释放使用定位 new 运算符分配的内存。事实上，在这个例子中不能这样做。buffer 指定的内存是静态内存，而 delete 只能用于这样的指针
：指向常规 new 运算符分配的堆内存。也就是说，数组 buffer 位于 delete 的管辖区域之外。

5. 定位 new 运算符的另一种用法是，将其与初始化结合使用，从而将信息放在特定的硬件地址处。




// !! 名称空间

在 C++ 中，名称可以是变量、函数、结构、枚举、类以及类和结构的成员。'当随着项目的增大，名称相互冲突的可能性也将增加'。例如, 两个库可能都定义了名为 List、
Tree 和 Node 的类，但定义的方式不兼容。用户可能希望使用一个库的 List 类，而使用另一个库的 Tree 类。这种冲突被称为名称空间问题。

C++ 标准提供了名称空间工具，以便更好地控制名称的作用域。


// !! 传统的 C++ 名称空间

介绍 C++ 中新增的名称空间特性之前，先复习一下 C++ 中已有的名称空间属性，并介绍一些术语，让读者熟悉名称空间的概念。

1. 声明区域(declaration region), 声明区域是可以在其中进行声明的区域。例如，可以在函数外面声明全局变量，对于这种变量，其声明区域为其声明所在的文件。
   对于在函数中声明的变量，其声明区域为其声明所在的代码块。

2. 潜在作用域(potential scope), 变量的潜在作用域从声明点开始，到其声明区域的结尾。因此潜在作用域比声明区域小，这是由于变量必须定义后才能使用。

3. 变量并非在其潜在作用域内的任何位置都是可见的。例如，它可能被另一个在嵌套声明区域中声明的同名变量隐藏。例如，在函数中声明的局部变量(对于这种变量，声明
   区域为整个函数)将隐藏在同一个文件中声明的全局变量(对于这种变量，声明区域为整个文件)


'C++ 关于全局变量和局部变量的规则定义了一种名称空间层次'。每个声明区域都可以声明名称，这些名称独立于在其他声明区域中声明的名称。在一个函数中声明的局部变量
不会与在另一个函数中声明的局部变量发生冲突。


// !! 新的名称空间特性

C++ 新增了这样一种功能，即'通过定义一种新的声明区域来创建命名的名称空间', 这样做的目的之一是提供一个声明名称的区域。一个名称空间中的名称不会与另外一个名称空
间的相同名称发生冲突，同时允许程序的其他部分使用该名称空间中声明的东西。例如，下面的代码使用新的关键字 namespace 创建了两个名称空间：Jack 和 Jill。

namespace jack {
  double pail;
  void fetch();
  int pal;
  struct well{....};
}

namespace jill{
  double bucket(int n ){...};
  double fetch;
  int pal;
  struct hill{....};
}

名称空间可以是全局的, 也可以位于另一个名称空间中，但不能位于代码块中。因此，在默认情况下，在名称空间中声明的名称的链接性为外部的(除非它引用了常量)。


除了用户定义的名称空间外，还存在另一个名称空间——'全局名称空间(global namespace)。它对应于文件级声明区域，因此前面所说的全局变量现在被描述为位于全
局名称空间中'。

'名称空间是开放的(open)，即可以把名称加入到已有的名称空间中'。

例如，下面这条语句将名称 goose 添加到 Jill 中已有的名称列表中:

namespace jill{
  char *goose(const char *);
}

同样，原来的 Jack 名称空间为 fetch() 函数提供了原型。可以在该文件后面（或另外一个文件中）再次使用 Jack 名称空间来提供该函数的代码:

namespace jack {
  void fetch(){
    ....
  }
}


当然，需要有一种方法来访问给定名称空间中的名称。'最简单的方法是，通过作用域解析运算符 ::'，使用名称空间来限定该名称:

jack::pal = 23.32;// use a variable
jack::Hill mole;// creat a type Hill structure
jack::fetch();// use a function

未被装饰的名称（如 pail）称为未限定的名称（unqualified name）; 包含名称空间的名称（如 Jack::pail）称为限定的名称（qualified name）。

// !! using 声明和 using 编译指令

我们并不希望每次使用名称时都对它进行限定，因此 C++ 提供了两种机制(using 声明和 using 编译指令)来简化对名称空间中名称的使用。

'using 声明使特定的标识符可用，using 编译指令使整个名称空间可用'。

using 声明由被限定的名称和它前面的关键字 using 组成:

using jill::fetch;// using a declaration

'using 声明将特定的名称添加到它所属的声明区域中'。例如 main() 中的 using 声明 Jill::fetch 将 fetch 添加到 main() 定义的声明区域中。完成该声明
后，便可以使用名称 fetch 代替 Jill::fetch。下面的代码段说明了这几点:

namespace jill {
  double bucket(double n){...};
  double fetch;
  struct Hill{...};
}

char fetch;

int main()
{
  using jill::fetch;
  double fetch;// error already have a local fetch
  cin >> fetch;// read a value into jill::fetch
  cin >> ::fetch;// read a value into global fetch
  ...
}

'由于 using 声明将名称添加到局部声明区域中'，因此这个示例避免了将另一个局部变量也命名为 fetch。另外，和其他局部变量一样，fetch 也将覆盖同名的全局变量。


'在函数的外面使用 using 声明时，将把名称添加到全局名称空间中':

void other();
namespace Jill{
  double bucket(double n){...};
  double fetch;
  struck Hill{...};
}

using Jill::fetch;// put fetch into global namespace

int main()
{
  cin >> fetch;
  other();
}


void other()
{
  cout << fetch;// display Jill::fetch
}

'using 声明使一个名称可用，而 using 编译指令使所有的名称都可用'。

using 编译指令由名称空间名和它前面的关键字 using namespace 组成，它使名称空间中的所有名称都可用，而不需要使用作用域解析运算符:

using namespace std;
using namespace jack;

在全局声明区域中使用' using 编译指令'，将使该名称空间的名称全局可用。这种情况已出现过多次:

#include <iostream> // place names in namespace std
using namespace std;// make names available globally


在函数中使用 using 编译指令，将使其中的名称在该函数中可用，下面是一个例子:

int main()
{
  using namespace jack;// make names available in main().
  ...
}

'有关 using 编译指令和 using 声明，需要记住的一点是，它们增加了名称冲突的可能性'。也就是说，如果有名称空间 jack 和 jill，并在代码中使用作用域
解析运算符，则不会存在二义性:

jack::pal = 12;
jill::pal = 21;

变量 jack::pal 和 jill::pal 是不同的标识符，表示不同的内存单元。然而，如果使用 using 声明，情况将发生变化:

using jack::pal;
using jill::pal;
pal = 4;// which one ? now have a conflict

事实上，'编译器不允许您同时使用上述两个 using 声明，因为这将导致二义性'。

// !! using 编译指令和 using 声明之比较

使用 using 编译指令导入一个名称空间中所有的名称与使用多个 using 声明是不一样的，using 声明更像是大量使用作用域解析运算符。使用 using 声明时，就好像
声明了相应的名称一样。如果某个名称已经在函数中声明了，则不能用 using 声明导入相同的名称。然而，使用 using 编译指令时，将进行名称解析，就像在包含 using 
声明和名称空间本身的最小声明区域中声明了名称一样。

在下面的示例中，名称空间为全局的。如果使用 using 编译指令导入一个已经在函数中声明的名称，则局部名称将隐藏名称空间名，就像隐藏同名的全局变量一样。不过仍可以
像下面的示例中那样使用作用域解析运算符:


namespace jill {
  double bucket(double n){...};
  double fetch;
  struct hill{...};
}

char fetch// global namespace

int main()
{
  using namespace jill;
  hill Thrill;
  double water = bucket(2);
  double fetch;// not error, hide jill::fetch
  cin >> fetch；
  cin >> ::fetch;// read a value into global fetch
  cin >>jill::fetch;// read a value into jill::fetch
  return 0;
}

在 main() 中，名称 Jill::fetch 被放在局部名称空间中，但其作用域不是局部的，因此不会覆盖全局的 fetch。然而，局部声明的 fetch 将隐藏 Jill::fetch 和
全局 fetch。然而，如果使用作用域解析运算符，则后两个 fetch 变量都是可用的。


'一般说来，使用 using 声明比使用 using 编译指令更安全，这是由于它只导入指定的名称'。'如果该名称与局部名称发生冲突，编译器将发出指示'。using 编译指令导入
所有名称，包括可能并不需要的名称。如果与局部名称发生冲突，则局部名称将覆盖名称空间版本，而编译器并不会发出警告。另外，名称空间的开放性意味着名称空间的名称可
能分散在多个地方，这使得难以准确知道添加了哪些名称。

下面是本书的大部分示例采用的方法:

#include <iostream>
int main()
{
  using namespace std;
  ...
}


1. 首先，#include 语句将头文件 iostream 放到名称空间 std 中。

2. 然后，using 编译指令使该名称空间在 main() 函数中可用


有些示例采取下述方式：

#include<iostream>
using namespace std;

int main()
{

}

这将名称空间 std 中的所有内容导出到全局名称空间中, 使用这种方法的主要原因是方便。


然而，名称空间的支持者希望有更多的选择，既可以使用解析运算符，也可以使用 using 声明。也就是说，不要这样做：

using namespace std;

而应这样做:

int x;
std::cin >> x;
std::cout << x << std::endl;


或者这样做:

using std::cout;
using std::cin;
using std::endl;

int x;
cin >> x;
cout << x << endl;


// !! 名称空间的其他特性

可以将名称空间声明进行嵌套:

namespace elements
{
  namespace fire{
    int flame;
    ...
  }
  float water;
} // namespace elements


这里，flame 指的是 element::fire::flame。同样，可以使用下面的 using 编译指令使内部的名称可用:

using namespace element::fire;

另外，也可以在名称空间中使用 using 编译指令和 using 声明，如下所示:

namespace myth
{
  using jill::fetch;
  using namespace elements;
  using std::cout;
  using std::endl;
}

假设要访问 Jill::fetch。由于 Jill::fetch 现在位于名称空间 myth（在这里，它被叫做 fetch）中，因此可以这样访问它：

std::cin >> myth::fetch;

当然，由于它也位于 Jill 名称空间中，因此仍然可以称作 Jill::fetch:

jill::fetch;
std::cout << jill::fetch;

如果没有与之冲突的局部变量，则也可以这样做：

using namespace myth;
cin >> fetch;

// !! 未命名的名称空间

可以通过省略名称空间的名称来创建未命名的名称空间：

namespace{// unnamed namespace
  int ice;
  int bandycoot;
}


这就像后面跟着 using 编译指令一样，也就是说，在该名称空间中声明的名称的潜在作用域为: 从声明点到该声明区域末尾。

从这个方面看，它们与全局变量相似。然而，由于这种名称空间没有名称，因此不能显式地使用 using 编译指令或 using 声明来使它在其他位置都可用。具体地说，
不能在未命名名称空间所属文件之外的其他文件中，使用该名称空间中的名称。'这提供了链接性为内部的静态变量的替代品'。


static int counts = 0;
int other();

int main()
{
  ...
}

int other()
{
  ...
}


采用名称空间的方法如下：

namespace{
  int counts = 0;
}

int other();

int main()
{
  ...
}

int other()
{
  ...
}


// !!名称空间示例

现在来看一个多文件示例，该示例说明了名称空间的一些特性。'namesp.h 是头文件，其中包含头文件中常包含的内容:常量、结构定义和函数原型'。在这个例子中，
这些内容被放在两个名称空间中。第一个名称空间叫做 pers，其中包含 Person 结构的定义和两个函数的原型——一个函数用人名填充结构，另一个函数显示结构的内容；
第二个名称空间叫做 debts，它定义了一个结构，该结构用来存储人名和金额。该结构使用了 Person 结构，因此，debts 名称空间使用一条 using 编译指令，让 
pers 中的名称在 debts 名称空间可用, debts 名称空间也包含一些原型。

#ifndef BCDA71E0_EE12_45DA_A931_41B2796B18FB
#define BCDA71E0_EE12_45DA_A931_41B2796B18FB

#include <string>
namespace pers{

    struct Person{
        std::string fname;
        std::string lname;
    };

    void getPerson(Person&);
    void showPerson(const Person&);
}

namespace debts{
    using namespace pers;
    struct Debt{
        Person name;
        double amount;
    };
    void getDebt(Debt&);
    void showDebt(const Debt &);
    double sumDebt(const Debt deb[],int n);
}

#endif /* BCDA71E0_EE12_45DA_A931_41B2796B18FB */



'namesp.cpp 是源代码文件，它提供了头文件中的函数原型对应的定义'。'在名称空间中声明的函数名的作用域为整个名称空间，因此定义和声明必须位于同一个名称
空间中'。这正是名称空间的开放性发挥作用的地方。通过包含 namesp.h 导入了原来的名称空间。然后该文件将函数定义添加入到两个名称空间中。

最后，该程序的第三个文件是一个源代码文件，它使用了名称空间中声明和定义的结构和函数。namessp.cpp 演示了多种使名称空间标识符可用的方法。

#include<iostream>
#include "namesp.h"

void another(void);
void other(void);

int main()
{
    using debts::Debt;
    using debts::showDebt;

    Debt golf = {{"beny","tiom",120.32}};
    showDeb(golf);
    other();
    another();
    return 0;
}


void other(void)
{
    using std::cout;
    using std::endl;
    using namespace debts;
    Person dg = {"hii","jhom"};
    showPerson(dg);
    cout << endl;
    Debt zippy[3];
    for(int i = 0; i < 3; i++)
    {
        getDebt(zippy[i]);
    }
    for(int i = 0; i < 3; i++)
    {
        showDebt(zippy[i]);
    }

    cout << "Total debt: " << sumDebt(zippy,3) << endl;
    return;
}


void another(void)
{
    using pers::Person;
    Person collector = {"Miolo","hal"};
    pers::showPerson(collector);
    std::cout << std::endl;
}

namessp.cpp中，main() 函数首先使用了两个 using 声明:

    using debts::Debt;
    using debts::showDebt;

注意，using 声明只使用了名称，例如，第二个 using 声明没有描述 showDebt 的返回类型或函数特征标，而只给出了名称；因此，如果函数被重载，则一个 using 
声明将导入所有的版本。另外，虽然 Debt 和 showDebt 都使用了 Person 类型，但不必导入任何 Person 名称，因为 debt 名称空间有一条包含 pers 名称空间
的 using 编译指令。

接下来，other() 函数采用了一种不太好的方法，即使用一条 using 编译指令导入整个名称空间：

using namespace pers;

由于 debts 中的 using 编译指令导入了 pers 名称空间，因此 other() 函数可以使用 Person 类型和 showPerson() 函数。


最后，another() 函数使用 using 声明和作用域解析运算符来访问具体的名称:

    using pers::Person;


// !! 名称空间及其前途

随着程序员逐渐熟悉名称空间，将出现统一的编程理念。下面是当前的一些指导原则:

1. 使用在已命名的名称空间中声明的变量，而不是使用外部全局变量

2. 使用在已命名的名称空间中声明的变量，而不是使用静态全局变量

3. 如果开发了一个函数库或类库，将其放在一个名称空间中。事实上，C++ 当前提倡将标准函数库放在名称空间 std 中，这种做法扩展到了来自C语言中的函数

4. 仅将编译指令 using 作为一种将旧代码转换为使用名称空间的权宜之计

5. 不要在头文件中使用 using 编译指令。首先，这样做掩盖了要让哪些名称可用；另外，包含头文件的顺序可能影响程序的行为。如果非要使用编译指令 using，应将其放
   在所有预处理器编译指令 #include 之后

6. 导入名称时，首选使用作用域解析运算符或 using 声明的方法

7. 对于 using 声明，首选将其作用域设置为局部而不是全局


// !! 总结

'C++ 鼓励程序员在开发程序时使用多个文件'。一种有效的组织策略是，使用头文件来定义用户类型，为操纵用户类型的函数提供函数原型；并将函数定义放在一个独
立的源代码文件中。头文件和源代码文件一起定义和实现了用户定义的类型及其使用方式。最后，将 main() 和其他使用这些函数的函数放在第三个文件中。

'C++ 的存储方案决定了变量保留在内存中的时间(储存持续性)以及程序的哪一部分可以访问它(作用域和链接性)':

1. 自动变量是在代码块(如函数体或函数体中的代码块)中定义的变量，仅当程序执行到包含定义的代码块时，它们才存在，并且可见

2. 静态变量在整个程序执行期间都存在。对于在函数外面定义的变量，其所属文件中位于该变量的定义后面的所有函数都可以使用它(文件作用域)，并可在程序的其他文件中
   使用(外部链接性)。另一个文件要使用这种变量，必须使用 extern 关键字来声明它。对于文件间共享的变量，应在一个文件中包含其定义声明(无需使用 extern，但如
   果同时进行初始化，也可使用它)，并在其他文件中包含引用声明(使用 extern 且不初始化)。'在函数的外面使用关键字 static 定义的变量的作用域为整个文件'，但
   是不能用于其他文件(内部链接性)。在代码块中使用关键字 static 定义的变量被限制在该代码块内(局部作用域、无链接性)，但在整个程序执行期间，它都一直存在并且
   保持原值。

3. 在默认情况下，C++ 函数的链接性为外部，因此可在文件间共享; 但使用关键字 static 限定的函数的链接性为内部的，被限制在定义它的文件中


动态内存分配和释放是使用 new 和 delete 进行的，它使用自由存储区或堆来存储数据。调用 new 占用内存，而调用 delete 释放内存。程序使用指针来跟踪这些内存单元。

名称空间允许定义一个可在其中声明标识符的命名区域。这样做的目的是减少名称冲突，尤其当程序非常大，并使用多个厂商的代码时。可以通过使用作用域解析运算符、using 
声明或 using 编译指令，来使名称空间中的标识符可用。



