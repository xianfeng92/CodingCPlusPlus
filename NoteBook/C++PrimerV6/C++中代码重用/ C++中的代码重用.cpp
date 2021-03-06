// !! C++ 中的代码重用

'C++ 的一个主要目标是促进代码重用'。

公有继承是实现这种目标的机制之一，但并不是唯一的机制。本章将介绍其他方法，其中之一是使用这样的类成员: '本身是另一个类的对象'。这种方法称为包含(containment)、
组合(composition)或层次化(layering)。另一种方法是'使用私有或保护继承'。


通常，包含、私有继承和保护继承用于实现 has-a 关系，即新的类将包含另一个类的对象。例如，HomeTheater 类可能包含一个 BluRayPlayer 对象。'多重继承使得能够使
用两个或更多的基类派生出新的类，将基类的功能组合在一起'。

'本章将介绍类模板---另一种重用代码的方法'。类模板使我们能够使用通用术语定义类，然后使用模板来创建针对特定类型定义的特殊类。例如，可以定义一个通用的栈模板，然
后使用该模板创建一个用于表示 int 值栈的类和一个用于表示 double 值栈的类，甚至可以创建一个这样的类，即用于表示由栈组成的栈。


// !! 包含对象成员的类

'首先介绍包含对象成员的类'。

有一些类(如 string 类) 为表示类中的组件提供了方便的途径。下面来看一个具体的例子。

学生是什么？入学者？参加研究的人？ 残酷现实社会的避难者？ 有姓名和一系列考试分数的人？显然，最后一个定义完全没有表示出人的特征，但非常适合于简单的计算机表示。
因此，让我们根据该定义来开发 Student 类。

将学生简化成姓名和一组考试分数后，可以使用一个包含两个成员的类来表示它: 一个成员用于表示姓名, 另一个成员用于表示分数。

对于姓名:

1. 可以使用字符数组来表示, 但这将限制姓名的长度。当然，也可以使用 char 指针和动态内存分配，但正如第12章指出的，'这将要求提供大量的支持代码'

2. 一种更好的方法是，使用一个由他人开发好的类的对象来表示。例如，可以使用标准 C++ string类的对象来表示姓名。因为 C++ 库提供了这个类的所有实现代码，且其实
   现更完美。


对于考试分数，存在类似的选择:

1. 可以使用一个定长数组，这限制了数组的长度; 可以使用动态内存分配并提供大量的支持代码

2. 也可以设计一个使用动态内存分配的类来表示该数组

3. 还可以在标准 C++ 库中查找一个能够表示这种数据的类

当然，如果 C++ 库提供了合适的类，实现起来将更简单。C++ 库确实提供了一个这样的类，它就是 valarray。


'valarray 类简介'

valarray 类是由头文件 valarray 支持的。顾名思义，这个类用于处理数值(或具有类似特性的类)，它支持诸如将数组中所有元素的值相加以及在数组中找出最大和最小的值
等操作。'valarray 被定义为一个模板类，以便能够处理不同的数据类型'。


'模板特性意味着声明对象时，必须指定具体的数据类型'。因此，使用 valarray 类来声明一个对象时，需要在标识符 valarray 后面加上一对尖括号，并在其中包含所需的数
据类型:

valarray<int> q_values;
valarray<double> weights;

'类特性意味着要使用 valarray 对象，需要了解这个类的构造函数和其他类方法'。下面是几个使用其构造函数的例子:


double gpa[5] = {1.2, 1.3, 1.4, 1.5, 1.1};
valarray<double> v1;// an array of double size = 0
valarray<int> v2(8);// an array of 8 int elements
valarray<int> v3(10,8);// an array of 8 int elements, each element set to 10
valarray<double> v4(gpa,5);

从中可知，可以创建长度为零的空数组、指定长度的空数组、所有元素度被初始化为指定值的数组、用常规数组中的值进行初始化的数组。

下面是这个类的一些方法:


1. operator：让您能够访问各个元素
2. size()：返回包含的元素数
3. sum()：返回所有元素的总和
4. max()：返回最大的元素
5. min()：返回最小的元素

还有很多其他的方法，但就这个例子而言，上述方法足够了。


'Student 类的设计'

至此，已经确定了 Student 类的设计计划：使用一个 string 对象来表示姓名，使用一个 valarray<double> 来表示考试分数。

那么如何设计呢？您可能想以公有的方式从这两个类派生出 Student 类，这将是多重公有继承，C++ 允许这样做，但在这里并不合适，因为学生与这些类之间的关系不是 is-a 
模型。学生不是姓名，也不是一组考试成绩。这里的关系是 has-a，学生有姓名，也有一组考试分数。通常，用于建立 has-a 关系的 C++ 技术是组合(包含)，即创建一个包含
其他类对象的类。例如，可以将 Student 类声明为如下所示:

class Student
{
    private:
        std::string name;
        valarray<double> scores;
    public:
    ...
};

同样，上述类将数据成员声明为私有的。'这意味着 Student 类的成员函数可以使用 string 和 valarray<double> 类的公有接口来访问和修改 name 和 scores 对象'，但
在类的外面不能这样做，而只能通过 Student 类的公有接口访问 name 和 score。

对于这种情况，通常被描述为 Student 类获得了其成员对象的实现，但没有继承接口。

'对于 has-a 关系来说，类对象不能自动获得被包含对象的接口是一件好事'。例如，string 类将 + 运算符重载为将两个字符串连接起来；但从概念上说，将两个 Student 对象
串接起来是没有意义的。这也是这里不使用公有继承的原因之一。另一方面，被包含的类的接口部分对新类来说可能是有意义的。例如，可能希望使用 string 接口中的 
operator<() 方法将 Student 对象按姓名进行排序，为此可以定义 Student::Operator<() 成员函数，它在内部使用函数 string::Operator<()。


'Student 类示例'

现在需要提供 Student 类的定义，当然它应包含构造函数以及一些用作 Student 类接口的方法。

为简化表示，Student 类的定义中包含下述 typedef:

typedef std::valarray<double> ArrayDb;

这样，在以后的代码中便可以使用 ArrayDb 来表示 std::valarray<double>， 因此类方法和友元函数可以使用 ArrayDb 类型。将该 typedef 放在类定义的私有部分意味
着可以在 Student 类的实现中使用它，但在 Student 类外面不能使用。


请注意关键字 explicit 的用法：

    explicit Student(const std::string &s):name(s),scores(){}
    explicit Student(int n):name("Nully"),scores(n){}

'可以用一个参数调用的构造函数将用作从参数类型到类类型的隐式转换函数', 但这通常不是好主意。

C++和约束

C++ 包含让程序员能够限制程序结构的特性--使用 explicit 防止单参数构造函数的隐式转换，使用 const 限制方法修改数据，等等。这样做的根本原因是:'在编译阶段出现
错误优于在运行阶段出现错误'。


// !! 初始化被包含的对象

构造函数全都使用您熟悉的成员初始化列表语法来初始化 name 和 score 成员对象。在前面的一些例子中，构造函数用这种语法来初始化内置类型的成员:

Queue::Queue(int qs):qsize(qs){...}

另外，前面介绍的示例中的构造函数还使用成员初始化列表初始化派生对象的基类部分:

hasDMA::hasDMA(const hasDMA &dma):baseDMA(dma){...}

对于继承的对象，构造函数在成员初始化列表中使用类名来调用特定的基类构造函数。对于成员对象, 构造函数则使用成员名。

     Student(const char *str, const double *pd, int n):name(str),scores(pd,n){}

因为该构造函数初始化的是成员对象，而不是继承的对象，所以在初始化列表中使用的是成员名，而不是类名。初始化列表中的每一项都调用与之匹配的构造函数，即 name(str) 
调用构造函数 string(const char *)，scores(pd, n) 调用构造函数 ArrayDb(const double *, int)。


如果不使用初始化列表语法，情况将如何呢？

'C++ 要求在构建对象的其他部分之前，先构建继承对象的所有成员对象'。因此，如果省略初始化列表，C++ 将使用成员对象所属类的默认构造函数。



'初始化顺序'

'当初始化列表包含多个项目时，这些项目被初始化的顺序为它们被声明的顺序，而不是它们在初始化列表中的顺序'。

例如，假设Student构造函数如下:

     Student(const char *str, const double *pd, int n):name(str),scores(pd,n){}

则 name 成员仍将首先被初始化，因为在类定义中它首先被声明。对于这个例子来说，初始化顺序并不重要，但如果代码使用一个成员的值作为另一个成员的初始化表达式的一部
分时, 初始化顺序就非常重要了。



// !! 使用被包含对象的接口

被包含对象的接口不是公有的，但可以在类方法中使用它。例如，下面的代码说明了如何定义一个返回学生平均分数的函数:

double Student::average() const
{
    if(scores.size() > 0)
    {
        return scores.sum() / scores.size();
    }
    else
    {
        return 0;
    }
}

上述代码定义了可由 Student 对象调用的方法，该方法内部使用了 valarray 的方法 size() 和 sum()。这是因为 scores 是一个 valarray 对象，所以它可以调用
valarray 类的成员函数。总之，Student 对象调用 Student 的方法，而后者使用被包含的 valarray 对象来调用 valarray 类的方法。

同样，可以定义一个使用 string 版本的 << 运算符的友元函数:

ostream & operator << (ostream & os, const String &st)
{
    os << "Scores for " << st.name << '\n';
    ...
}

因为 st.name 是一个 string 对象，所以它将调用函数 operatot<<(ostream &, const string &)，该函数位于 string 类中。


同样，该函数也可以使用 valarray 的 << 实现来进行输出，不幸的是没有这样的实现；因此，Student 类定义了一个私有辅助方法来处理这种任务:

ostream & Student::arr_out(ostream &os) const
{
    int i;
    int lim = scores.size();
    if(lim > 0)
    {
        for(int i = 0; i < lim; i++)
        {
            os << scores[i] << " ";
            if(i % 5 == 4)
            {
                os << endl;
            }
        }
        if(i % 5 != 0)
        {
            os << endl;
        }

    }
    else
    {
        os << "Empty array";
    }
    return os;
}


通过使用这样的辅助方法，可以将零乱的细节放在一个地方，使得友元函数的编码更为整洁:

ostream operator<<(ostream& os, const Student &stu)
{
    os << "Scores for " << stu.name << " ";
    stu.arr_out(os);
    return os;
}


辅助函数也可用作其他用户级输出函数的构建块——如果您选择提供这样的函数的话。

Student.cpp 是 Student 类的类方法文件，其中包含了让您能够使用 [] 运算符来访问 Student 对象中各项成绩的方法。



// !! 使用新的 Student 类

下面编写一个小程序来测试这个新的 Student 类。出于简化的目的，该程序将使用一个只包含 3 个 Student 对象的数组，其中每个对象保存 5 个考试成绩。






// !! 私有继承

C++ 还有另一种实现 has-a 关系的途径--私有继承。使用私有继承, 基类的公有成员和保护成员都将成为派生类的私有成员。这意味着基类方法将不会成为派生对象公有
接口的一部分, 但可以在派生类的成员函数中使用它们。

使用公有继承, 基类的公有方法将成为派生类的公有方法。总之，派生类将继承基类的接口; 这是 is-a 关系的一部分。使用私有继承，基类的公有方法将成为派生类的私有方法。
总之，派生类不继承基类的接口。正如从被包含对象中看到的，这种不完全继承是 has-a 关系的一部分。


使用私有继承，类将继承实现。例如，如果从 String 类派生出 Student 类，后者将有一个 String 类组件，可用于保存字符串。另外，Student 方法可以使用 String 方法
来访问 String 组件。

'包含将对象作为一个命名的成员对象添加到类中, 而私有继承将对象作为一个未被命名的继承对象添加到类中'。我们将使用术语子对象(subobject)来表示通过继承或包含添加
的对象。

因此私有继承提供的特性与包含相同: '获得实现，但不获得接口'。所以，私有继承也可以用来实现 has-a 关系。

接下来介绍如何使用私有继承来重新设计 Student 类。


// !! Student类示例（新版本）

要进行私有继承，请使用关键字 private 而不是 public 来定义类(实际上，private 是默认值，因此省略访问限定符也将导致私有继承)。Student 类应从两个类派生而来
，因此声明将列出这两个类:

class Student::private std::string,private std::valarray<double>
{

}

使用多个基类的继承被称为多重继承(multiple inheritance，MI)。通常，MI 尤其是公有 MI 将导致一些问题，必须使用额外的语法规则来解决它们。


新的 Student 类不需要私有数据，因为两个基类已经提供了所需的所有数据成员。包含版本提供了两个被显式命名的对象成员，而私有继承提供了两个无名称的子对象成员。这是
这两种方法的第一个主要区别。


1. 初始化基类组件

隐式地继承组件而不是成员对象将影响代码的编写，因为再也不能使用 name 和 scores 来描述对象了，而必须使用用于公有继承的技术。例如，对于构造函数，包含将使这样的
构造函数：

     Student(const char *str, const double *pd, int n):name(str),scores(pd,n){}


对于继承类, 新版本的构造函数将使用成员初始化列表语法，它使用类名而不是成员名来标识构造函数：

 Student(const char *str, const double *pd, int n):std::string(str),ArrayDb(pd,n){}

在这里，ArrayDb 是 std::valarray<double> 的别名。成员初始化列表使用 std::string(str)，而不是 name(str)。这是包含和私有继承之间的第二个主要区别。


2. 访问基类的方法

'使用私有继承时，只能在派生类的方法中使用基类的方法'。但有时候可能希望基类工具是公有的。

然而，私有继承使得能够使用类名和作用域解析运算符来调用基类的方法:

double Student::Average() const
{
    if(ArrayDb::size() > 0)
    {
        return ArrayDb::sum() / ArrayDb::size();
    }
    else
    {
        return 0;
    }
}

总之, 使用包含时将使用对象名来调用方法，而使用私有继承时将使用类名和作用域解析运算符来调用方法。


3. 访问基类对象

'使用作用域解析运算符可以访问基类的方法，但如果要使用基类对象本身，该如何做呢'？

例如，Student 类的包含版本实现了 Name() 方法，它返回 string 对象成员 name；但使用私有继承时，该 string 对象没有名称。那么，Student 类的代码如何访问内部
的 string 对象呢？

'答案是使用强制类型转换'。由于 Student 类是从 string 类派生而来的，因此可以通过强制类型转换，将 Student 对象转换为 string 对象；结果为继承而来的 string 
对象。

const string & Student::Name() const
{
    return (const string &)*this;
}

上述方法返回一个引用，该引用指向用于调用该方法的 Student 对象中的继承而来的 string 对象。


4. 访问基类的友元函数

用类名显式地限定函数名不适合于友元函数，这是因为友元不属于类。然而，可以通过显式地转换为基类来调用正确的函数。例如，对于下面的友元函数定义:

ostream & operator<<(ostream & os, const Student &st)
{
    os << "Scores for" << (const string &)st << "\n";
    ...
}


5. 使用修改后的 Student 类



// !! 使用包含还是私有继承


由于既可以使用包含，也可以使用私有继承来建立 has-a 关系，那么应使用种方式呢？

大多数 C++ 程序员倾向于使用包含。首先，它易于理解。类声明中包含表示被包含类的显式命名对象，代码可以通过名称引用这些对象，而使用继承将使关系更抽象。其次，继承会
引起很多问题，尤其从多个基类继承时，可能必须处理很多问题，如包含同名方法的独立的基类或共享祖先的独立基类。总之，使用包含不太可能遇到这样的麻烦。另外，包含能够包括
多个同类的子对象。如果某个类需要 3 个 string 对象，可以使用包含声明 3 个独立的 string 成员。而继承则只能使用一个这样的对象(当对象都没有名称时，将难以区分)。


通常，应使用包含来建立 has-a 关系；如果新类需要访问原有类的保护成员，或需要重新定义虚函数，则应使用私有继承。

// !! 保护继承

保护继承是私有继承的变体。保护继承在列出基类时使用关键字 protected：

class Student::protected std::string, protected valarray<double>
{

}

'使用保护继承时，基类的公有成员和保护成员都将成为派生类的保护成员'。和私有继承一样，基类的接口在派生类中也是可用的，但在继承层次结构之外是不可用的。当从派生类派生
出另一个类时，私有继承和保护继承之间的主要区别便呈现出来了。使用私有继承时，第三代类将不能使用基类的接口，这是因为基类的公有方法在派生类中将变成私有方法；使用保护
继承时，基类的公有方法在第二代中将变成受保护的，因此第三代派生类可以使用它们。



// !! 使用 using 重新定义访问权限

使用保护派生或私有派生时，基类的公有成员将成为保护成员或私有成员。假设要让基类的方法在派生类外面可用，方法之一是定义一个使用该基类方法的派生类方法。

例如，假设希望 Student 类能够使用 valarray 类的 sum() 方法，可以在 Student 类的声明中声明一个 sum() 方法，然后像下面这样定义该方法:

double Student::sum() const// public student method
{
    return std::valarray<double>::sum();
}

这样 Student 对象便能够调用 Student::sum()，后者进而将 valarray<double>::sum()方法应用于被包含的 valarray 对象（如果ArrayDb typedef在作用域中，
也可以使用 ArrayDb 而不是 std::valarray<double>）。


另一种方法是，将函数调用包装在另一个函数调用中，即使用一个 using 声明(就像名称空间那样)来指出派生类可以使用特定的基类成员，即使采用的是私有派生。例如，假设希望
通过 Student 类能够使用 valarray 的方法 min() 和 max()，可以在 studenti.h 的公有部分加入如下 using 声明:


class Student::private std::string, private std::valarray<double>
{
    public:
        using std::valarray<double>::min;
        using std::valarray<double>::max;
    ...
};


上述 using 声明使得 valarray<double>::min() 和 valarray<double>::max() 可用，就像它们是 Student 的公有方法一样：

cout << "high Score" << ada[i].max() << "\n";

注意，using 声明只使用成员名----没有圆括号、函数特征标和返回类型。

例如，为使 Student 类可以使用 valarray 的 operator 方法，只需在 Student 类声明的公有部分包含下面的 using 声明

using std::valarray<double>::operator[];

这将使两个版本（const和非const）都可用。这样，便可以删除 Student::operator[]() 的原型和定义。'using 声明只适用于继承，而不适用于包含'。



// !! 类模板

'继承(公有、私有或保护)和包含并不总是能够满足重用代码的需要'。例如，Stack 类和 Queue类都是容器类(container class)，容器类设计用来存储其他对象或数据
类型。

例如，Stack 类设计用于存储 unsigned long 值。可以定义专门用于存储 double 值或 string 对象的 Stack 类，除了保存的对象类型不同外，这两种 Stack 类的
代码是相同的。'然而，与其编写新的类声明，不如编写一个泛型(即独立于类型的）栈，然后将具体的类型作为参数传递给这个类'。

这样就可以使用通用的代码生成存储不同类型值的栈。

'C++ 的类模板为生成通用的类声明提供了一种更好的方法'。模板提供参数化(parameterized)类型，即能够将类型名作为参数传递给接收方来建立类或函数。

// !! 定义类模板

template <class Type>

关键字 template 告诉编译器，将要定义一个模板。尖括号中的内容相当于函数的参数列表。可以把关键字 class 看作是变量的类型名，该变量接受类型作为其值，把 Type 
看作是该变量的名称。


较新的 C++ 实现允许在这种情况下使用不太容易混淆的关键字 typename 代替 class：

template<typename Type>// newer choice

当模板被调用时，Type 将被具体的类型值(如 int 或 string)取代。


在模板定义中，可以使用泛型名来标识要存储在栈中的类型。对于 Stack 来说，这意味着应将声明中所有的 typedef 标识符 Item 替换为 Type。

例如，

Item items[MAX];

应改为：

Type items[MAX];

可以使用模板成员函数替换原有类的类方法。每个函数头都将以相同的模板声明打头:

template<typename Type>

同样应使用泛型名 Type 替换 typedef 标识符 Item。另外，还需将类限定符从 Stack::改为 Stack<Type>::。

例如:

bool Stack::push(const Item &item)
{
    ...
}

应该为:

template<typename Type>
bool Stack::push(const Type &item)
{
    ...

}


stacktp.h 列出了类模板和成员函数模板。知道这些模板不是类和成员函数定义至关重要。'它们是 C++ 编译器指令, 说明了如何生成类和成员函数定义'。模板的具体实现---如
用来处理 string 对象的栈类---被称为实例化(instantiation)或具体化(specialization)。不能将模板成员函数放在独立的实现文件中。由于模板不是函数，它们不能单独
编译。模板必须与特定的模板实例化请求一起使用。为此, '最简单的方法是将所有模板信息放在一个头文件中，并在要使用这些模板的文件中包含该头文件'。


// !! 使用模板类

'仅在程序包含模板并不能生成模板类，而必须请求实例化'。为此，需要声明一个类型为模板类的对象，方法是使用所需的具体类型替换泛型名。

例如，下面的代码创建两个栈，一个用于存储 int，另一个用于存储 string 对象:

Stack<int> kernels;
Stack<string> colonels;

看到上述声明后，'编译器将按 Stack<Type> 模板来生成两个独立的类声明和两组独立的类方法'。类声明 Stack<int> 将使用 int 替换模板中所有的 Type，而类声明 
Stack<string> 将用 string 替换 Type。当然，使用的算法必须与类型一致。例如，Stack 类假设可以将一个项目赋给另一个项目。这种假设对于基本类型、结构和类来
说是成立的，但对于数组则不成立。

泛型标识符---例如这里的Type——称为类型参数(type parameter)，这意味着它们类似于变量，但赋给它们的不能是数字，而只能是类型。因此，在 kernel 声明中，类型参数
 Type 的值为 int。

注意，必须显式地提供所需的类型，这与常规的函数模板是不同的，因为编译器可以根据函数的参数类型来确定要生成哪种函数:

template <typename Type>
void sumple(Type t)
{
    cout << t << endl;
}

simple(1);
simple("two");


// !! 深入探讨模板类

1. 不正确地使用指针栈

Stack<char *> st;// create a stack for pointer to char



// !! 数组模板示例和非类型参数

模板常用作容器类, 这是因为类型参数的概念非常适合于将相同的存储方案用于不同的类型。确实，'为容器类提供可重用代码是引入模板的主要动机'。

首先介绍一个允许指定数组大小的简单数组模板。

1. 一种方法是在类中使用动态数组和构造函数参数来提供元素数目

2. 另一种方法是使用模板参数来提供常规数组的大小，C++11 新增的模板 array 就是这样做的。

#ifndef CF3B74C8_81D9_4300_8B7F_5145A19FFF05
#define CF3B74C8_81D9_4300_8B7F_5145A19FFF05

#include<iostream>
#include<cstdlib>

template <typename T,int n>
class ArrayTP
{
    private:
        T ar[n];
    public:
        ArrayTP();
        explicit ArrayTP(const T & v);
        virtual T &operator[](int i);
        virtual T operator[] (int i) const;
};

template <typename T,int n>
ArrayTP<T,n>::ArrayTP(const T & v)
{
    for(int i = 0; i < n; i++)
    {
        ar[i] = v;
    }
}

template <typename T,int n>
T & ArrayTP<T,n>::operator[] (int i)
{
    if(i < 0 || i >= n)
    {
        std::cerr << "Error in array of limits:" << i << " is out of range\n";
        std::Exit(EXIT_FAILURE);
    }
    return ar[i];
}


template <typename T,int n>
T ArrayTP<T,n>::operator[] (int i) const
{
    if(i < 0 || i >= n)
    {
        std::cerr << "Error in array of limits:" << i << " is out of range\n";
        std::Exit(EXIT_FAILURE);
    }
    return ar[i];
}

#endif /* CF3B74C8_81D9_4300_8B7F_5145A19FFF05 */



请注意程序 arraytp.h 中的模板头：

template <typename T,int n>

关键字 typename 指出 T 为类型参数，int 指出 n 的类型为 int。这种参数(指定特殊的类型而不是用作泛型名)称为非类型(non-type)或表达式（expression）参数。

假设有下面的声明：

ArrayTP<double,12> eggweight;

这将导致编译器定义名为 ArrayTP<double, 12> 的类，并创建一个类型为 ArrayTP<double, 12> 的 eggweight 对象。定义类时，编译器将使用 double 替换 T，
使用 12 替换 n。

表达式参数有一些限制。表达式参数可以是整型、枚举、引用或指针。另外，模板代码不能修改参数的值，也不能使用参数的地址。所以，在 ArrayTP 模板中不能使用诸如 n++ 
和 &n 等表达式。另外，实例化模板时，用作表达式参数的值必须是常量表达式。

与 Stack 中使用的构造函数方法相比，这种改变数组大小的方法有一个优点。'构造函数方法使用的是通过 new 和 delete 管理的堆内存'，而'表达式参数方法使用的是为自
动变量维护的内存栈'。这样，执行速度将更快，尤其是在使用了很多小型数组时。

表达式参数方法的主要缺点是: '每种数组大小都将生成自己的模板'。也就是说, 下面的声明将生成两个独立的类声明:

ArrayTP<double,12> eggweight;
ArrayTP<double,13> donuts;

但下面的声明只生成一个类声明, 并将数组大小信息传递给类的构造函数:

Stack<int> eggs(12);
Stack<int> dunkers(13);

另一个区别是，构造函数方法更通用，这是因为数组大小是作为类成员(而不是硬编码)存储在定义中的。这样可以将一种尺寸的数组赋给另一种尺寸的数组，也可以创建允许数组
大小可变的类。


// !!  模板多功能性

'可以将用于常规类的技术用于模板类'。模板类可用作基类，也可用作组件类，还可用作其他模板的类型参数。例如，可以使用数组模板实现栈模板， 也可以使用数组模板来构造数
组---数组元素是基于栈模板的栈。

即可以编写下面的代码：

template<typename T>
class Array
{
    private:
        T entry;
    ...
};

template <typename Type>
class GrowArray: public Array<Type> {...}// inheritance


template <typename Tp>
class Stack
{
    private:
        Array<Tp> ar;// use an array as a component
};


1. 递归使用模板

'另一个模板多功能性的例子是, 可以递归使用模板'。

例如，对于前面的数组模板定义，可以这样使用它：

ArrayTP<ArrayTP<int,5>,10> twodee;

这使得 twodee 是一个包含 10 个元素的数组, 其中每个元素都是一个包含 5 个 int 元素的数组。

与之等价的常规数组声明如下:

int twodee[10][5];

twod.cpp 使用了这种方法，同时使用 ArrayTP 模板创建了一维数组, 来分别保存这 10 个组(每组包含 5 个数)的总数和平均值。方法调用 cout.width(2) 以两个字符的宽
度显示下一个条目(如果整个数字的宽度不超过两个字符)。


2. 使用多个类型参数

'模板可以包含多个类型参数'。假设希望类可以保存两种值，则可以创建并使用 Pair 模板来保存两个不同的值(标准模板库提供了类似的模板，名为 pair) 。pairs.cpp 所示的
小程序是一个这样的示例。其中，方法 first() const 和 second() const 报告存储的值，由于这两个方法返回 Pair 数据成员的引用，因此让您能够通过赋值重新设置存储的值。


3. 默认类型模板参数

类模板的另一项新特性是,可以为类型参数提供默认值:

template <typename T1, typename T2 = int>
class ToPo
{

};


// !! 模板的具体化

'类模板与函数模板很相似,因为可以有隐式实例化、显式实例化和显式具体化，它们统称为具体化(specialization)'。模板以泛型的方式描述类, 而具体化是使用具体的类
型生成类声明。


1. 隐式实例化

到目前为止，本章所有的模板示例使用的都是隐式实例化(implicit instantiation)，即它们声明一个或多个对象，指出所需的类型，而编译器使用通用模板提供的处方生成具
体的类定义:

ArrayTP<int, 100> stuffer;

编译器在需要对象之前, 不会生成类的隐式实例化：

ArrayTP<double, 100> *pt;// a pointer, no object needed yet
pt = new ArrayTP<double, 100>// now object is needed

第二条语句导致编译器生成类定义, 并根据该定义创建一个对象。


2. 显式实例化

'当使用关键字 template 并指出所需类型来声明类时, 编译器将生成类声明的显式实例化'(explicit instantiation)。声明必须位于模板定义所在的名称空间中。例如，下面
的声明将 ArrayTP<string, 100> 声明为一个类:


template class ArrayTP<string, 100>// generate ArrayTP<string, 100> class


在这种情况下, 虽然没有创建或提及类对象, 编译器也将生成类声明(包括方法定义)。和隐式实例化一样，也将根据通用模板来生成具体化。


3．显式具体化

显式具体化(explicit specialization)是特定类型(用于替换模板中的泛型)的定义。有时候，可能需要在为特殊类型实例化时，对模板进行修改，使其行为不同。在这种情况下，
可以创建显式具体化。例如，假设已经为用于表示排序后数组的类(元素在加入时被排序)定义了一个模板:

template <typename T>
class SortedArray
{
    private:

};

另外，假设模板使用 > 运算符来对值进行比较。对于数字，这管用; 如果 T 表示一种类，则只要定义了 T::operator>() 方法，这也管用；但如果 T 是由 const char * 表示的字
符串，这将不管用。实际上，模板倒是可以正常工作，但字符串将按地址(按照字母顺序)排序。这要求类定义使用 strcmp()，而不是 > 来对值进行比较。在这种情况下，可以提供一个显
式模板具体化，这将采用为具体类型定义的模板，而不是为泛型定义的模板。'当具体化模板和通用模板都与实例化请求匹配时，编译器将使用具体化版本'。

具体化类模板定义的格式如下:

template<> class ClassName<specialized-type-name> {...}

要使用新的表示法提供一个专供 const char * 类型使用的 SortedArray 模板，可以使用类似于下面的代码:

template<> class SortedArray<const char *>
{
    ....
};


其中的实现代码将使用 strcmp()（而不是>）来比较数组值。现在，当请求 const char * 类型的 SortedArray 模板时，编译器将使用上述专用的定义，而不是通用的模板
定义:

SortedArray<int> scores;// use general definition
SortedArray<const char*> dates;// use specification definition 

// !! 成员模板

'模板可用作结构、类或模板类的成员'。要完全实现 STL 的设计，必须使用这项特性。tempmemb.cpp 是一个简短的模板类示例，该模板类将另一个模板类和模板函数作为其成员。

#include<iostream>

using std::cout;
using std::endl;

template <typename T>
class beta
{
    private:
        template <typename V>
        class hold
        {
            private:
                V val;
            public:
                hold(V v = 0) : val(v){}
                void show() const { cout << val << std::endl; }
                V value() const { return val; }
        };
        hold<T> q;
        hold<int> n;
    public:
        beta(T t, int i):q(t), n(i){}
        template <typename U>
        U blab(U u, T t){return (n.Value() + q.Value())*u /t;}
        void show() const { q.show(); n.show(); }
};

int main()
{
    beta<double> guy(3.5,3);
    cout << "T was set to double\n";
    guy.show();
    cout << "V was set to T, which is double, Then V was set to int\n";
    cout << guy.blab(10,2.3) << endl;
    cout << "U was set to int\n";
    cout << guy.blab(10.0,2.3) << endl;
    cout << " U was set to double\n"
    cout << "done\n";
    return 0;
}

hold 模板是在私有部分声明的，因此只能在 beta 类中访问它。beta 类使用 hold 模板声明了两个数据成员:

        hold<T> q;
        hold<int> n;

n 是基于 int 类型的 hold 对象，而 q 成员是基于T类型(beta模板参数)的 hold 对象。在 main() 中，下述声明使得 T 表示的是 double，因此 q 的类型为
hold<double>:

beta<double> guy(3.5,3);

blab() 方法的 U 类型由该方法被调用时的参数值显式确定，T 类型由对象的实例化类型确定。在这个例子中，guy 的声明将 T 的类型设置为 double，而下述方法调用的
第一个参数将 U 的类型设置为 int（参数10对应的类型）:

cout << guy.blab(10,2.5) << endl;



// !! 将模板用作参数

模板可以包含类型参数（如 typename T）和非类型参数（如 int n）。'模板还可以包含本身就是模板的参数，这种参数是模板新增的特性，用于实现 STL'。

在程序 tempparm.cpp 所示的示例中, 开头的代码如下:

template<template <typename T> class Thing>
class Crab

模板参数是 template <typename T> class Thing，其中 template <typename T>class 是类型， Thing 是参数。

这意味着什么呢？假设有下面的声明：

Crab<King> legs;

为使上述声明被接受，模板参数 King 必须是一个模板类，其声明与模板参数 Thing 的声明匹配:

template <typename T>
class King
{

};

在 tempparm.cpp 中，Crab 的声明声明了两个对象:

Thing<int> s1;
Thing<double> s2;


// !! 模板别名(C++11)

如果能为类型指定别名，将很方便，在模板设计中尤其如此。可使用 typedef 为模板具体化指定别名:

typedef std::array<double,12> arrd;
typedef std::array<int,12> arri;
typedef std::array<string,12> arrstr;
arrd gallons;
arri days;
arrstr months;

但如果您经常编写类似于上述 typedef 的代码，您可能怀疑要么自己忘记了可简化这项任务的 C++ 功能，要么 C++ 没有提供这样的功能。

C++11 新增了一项功能----使用模板提供一系列别名，如下所示:

template<typename T>
using arrayType = std::array<T,12>;

这将 arrtype 定义为一个模板别名，可使用它来指定类型，如下所示:

arrayType<double> gallons;
arrayType<int> days;
arrayType<std::string> months;

总之, arrtype<T> 表示类型 std::array<T, 12>。

C++11 允许将语法 using = 用于非模板。用于非模板时，这种语法与常规 typedef 等价:

typedef const char * pc1;
using pc2 =  const char *;

习惯这种语法后，您可能发现其可读性更强，因为它让类型名和类型信息更清晰。


// !! 总结

C++ 提供了几种重用代码的手段。

1. 公有继承能够建立 is-a 关系，这样派生类可以重用基类的代码。

2. 私有继承和保护继承也使得能够重用基类的代码，但建立的是 has-a 关系。
   使用私有继承时， 基类的公有成员和保护成员将成为派生类的私有成员； 使用保护继承时，基类的公有成员和保护成员将成为派生类的保护成员。'无论使用哪种继承，基类的
   公有接口都将成为派生类的内部接口'。'这有时候被称为继承实现，但并不继承接口，因为派生类对象不能显式地使用基类的接口'。因此，不能将派生对象看作是一种基类对象
   由于这个原因，在不进行显式类型转换的情况下, 基类指针或引用将不能指向派生类对象

3. 通过开发包含对象成员的类来重用类代码。这种方法被称为包含、层次化或组合，它建立的也是 has-a 关系。'与私有继承和保护继承相比, 包含更容易实现和使用，所以通常
   优先采用这种方式'。

4. 类模板使得能够创建通用的类设计, 其中类型(通常是成员类型)由类型参数表示。


典型的模板如下：

template<typename T>
class IC
{
    private:
        T v;
        ...
    public:
        IC(const T &val):v(val){}
        ...
};


其中，T 是类型参数，用作以后将指定的实际类型的占位符(这个参数可以是任意有效的 C++ 名称，但通常使用 T 和 Type)。

类定义(实例化)在声明类对象并指定特定类型时生成。例如，下面的声明导致编译器生成类声明，用声明中的实际类型 short 替换模板中的所有类型参数 T:

class IC<short> sic;

这里，类名为 IC<short>，而不是 IC, IC<short> 称为模板具体化。具体地说，这是一个隐式实例化。

使用关键字 template 声明类的特定具体化时，将发生显式实例化:

template class IC<int>;

在这种情况下, 编译器将使用通用模板生成一个 int 具体化----IC<int>，虽然尚未请求这个类的对象。


类模板还可以包含本身就是模板的参数：

template<template<typename T1> class CL,typename U, int n>
class Hello{...}

模板类可用作其他类、结构和模板的成员。

'所有这些机制的目的都是为了让程序员能够重用经过测试的代码, 而不用手工复制它们'。这样可以简化编程工作，提供程序的可靠性。




