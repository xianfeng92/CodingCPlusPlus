// !! C++ 编程基础

本章,我们将从一个小程序开始,通过它来练习 C++ 程序语言的基本组成。其中包括:

1. 一些基础数据类型: 布尔值(Boolean)、字符(character)、整数(integer)、浮点数(floating point)

2. 算术运算符、关系运算符以及逻辑运算符, 用以操作上述基础数据类型。这些运算符不仅包括一般常见的加法运算符、相等运算符（==）、小于等于(<=) 运算符以及赋值
   (assignment,=) 运算符, 也包含比较特殊的递增(++)运算符、条件运算符(?:) 以及复合赋值(+= 等)运算符

3. 条件分支和循环控制语句, 例如 if 语句和 while 循环, 可用来改变程序的控制流程

4. 一些复合类型, 例如指针及数组。指针可以让我们间接参考一个已存在的对象, 数组则用来定义一组具有相同数据类型的元素

5.一套标准的、通用的抽象化库, 例如字符串和向量(vector)



// !! 如何撰写 C++ 程序


// !! How to Write a C++ Program

此刻, 假设我们需要撰写一个简易程序, 必须能够将一段信息送至用户的终端(terminal)。信息的内容则是要求用户输入自己的名字。然后程序必须读取用户所输入的名字,将这个名
字储存起来,以便后续操作使用。最后，送出一个信息，以指名道姓的方式向用户打招呼。

那么, 该从何处着手呢？

每个 C++ 程序都是从一个名为 main 的函数开始执行, 我们就从这个地方着手吧! main 是个由用户自行撰写的函数, 其通用形式如下:

int main() {
    ...
}

int 是 C++ 程序语言的关键字。所谓关键字 (keyword), 就是程序语言预先定义的一些具有特殊意义的名称。int 用来表示语言内置的整数数据类型。

函数 (function) 是一块独立的程序代码序列(code sequence), 能够执行一些运算。它包含四个部分: 返回值类型(return type)、函数名称、参数列表(parameter list
), 以及函数体(function body)

下面依次简要介绍每一部分:

函数的返回值通常用来表示运算结果。main() 函数返回整数类型。main() 的返回值用来告诉调用者, 这个程序是否正确执行。'习惯上, 程序执行无误时我们令 main() 返回零'。
若返回一个非零值, 表示程序在执行过程中发生了错误。


函数的名称由程序员选定。'函数名最好能够提供某些信息, 让我们容易了解函数实际上在做些什么'。举例来说, min() 和 sort() 便是极佳的命名。f() 和 g() 就没有那么
好了。为什么? 因为后两个名称相形之下无法告诉我们函数的实际执行操作。


main 并非是程序语言定义的关键字。但是, '执行我们这个 C++ 程序的编译系统, 会假设程序中定义有 main() 函数。如果我们没有定义, 程序将无法执行'。

函数的参数列表 (parameter list)由两个括号括住, 置于函数名之后。空的参数列表,  如 main(), 表示函数不接受任何参数。


参数列表用来表示"函数执行时, 调用者可以传给函数的类型列表"。列表之中以逗号隔开各个类型(通常我们会说用户"调用(call 或是 invoke)"某个函数)


函数的主体 (body) 由大括号（{}）标出，其中含有"提供此函数之运算"的程序代码。


数据的输入与输出, 并非 C++ 程序语言本身定义的一部分, 而是'由 C++ 的一套面向对象的类层次体系(classes hierarchy) 提供支持, 并作为 C++ 标准库
(standard library) 的一员'。


'所谓类(class), 是用户自定义的数据类型(user-defined data type)'。class 机制让我们得以将数据类型加入我们的程序中, 并有能力识别它们。

面向对象的类层次体系(class hierarchy) 定义了整个家族体系的各相关类型, 例如终端与文件输入设备、终端与文件输出设备等。
















