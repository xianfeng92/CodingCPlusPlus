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






