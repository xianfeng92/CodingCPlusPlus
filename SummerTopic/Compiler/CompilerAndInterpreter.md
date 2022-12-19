
# Compiler and Interpreter

## 什么是编译器

A compiler is a computer program (or a set of programs) that transforms source code written in a programming language (the source language) into another computer language (the target language), with the latter often having a binary form known as object code. The most common 
reason for converting source code is to create an executable program.

编译器的产出是「另外一种代码」, 然后这些代码等着被别人拿来执行; 如果还不能直接被执行, 那么还需要再编译或解释一遍，再交由计算机硬件执行。

编译器往往是在「执行」之前完成, 产出是一种可执行或需要再编译或者解释的「代码」。


## 什么是解释器

In computer science, an interpreter is a computer program that directly executes, i.e. performs, instructions written in a programming or scripting language, without previously compiling them into a machine language program. An interpreter generally uses one of the following strategies for program execution:

1. parse the source code and perform its behavior directly.
2. translate source code into some efficient intermediate representation and immediately execute this.
3. explicitly execute stored precompiled code made by a compiler which is part of the interpreter system


在计算机科学中, 解释器是一种计算机程序, 它直接执行由编程语言或脚本语言编写的代码, 并不会把源代码预编译成机器码。一个解释器, 通常会用以下的姿势来执行程序代码:

1. 分析源代码，并且直接执行
2. 把源代码翻译成相对更加高效率的中间码, 然后立即执行它
3. 执行由解释器内部的编译器预编译后保存的代码

可以把解释器看成一个黑盒子, 我们输入源码, 它就会实时返回结果。不同类型的解释器, 黑盒子里面的构造不一样, 有些还会集成编译器, 缓存编译结果, 用来提高执行效率(例如 Chrome V8 也是这么做的)。

解释器通常是工作在「运行时」并且对于我们输入的源码一行一行的解释然后执行, 然后返回结果。


## 分两个维度比较一下

### 表现 Behavior

1. 编译器把源代码转换成其他的更低级的代码(例如二进制码、机器码), 但是不会执行它
2. 解释器会读取源代码,并且直接生成指令让计算机硬件执行, 不会输出另外一种代码


### 性能 Performance

1. 编译器会事先用比较多的时间把整个程序的源代码编译成另外一种代码, 后者往往较前者更加接近机器码, 所以执行的效率会更加高。时间是消耗在预编译的过程中
2. 解释器会一行一行的读取源代码, 解释, 然后立即执行。这中间往往使用相对简单的词法分析、语法分析，压缩解释的时间, 最后生成机器码交由硬件执行。解释器适合比较低级的语言。
   但是相对于预编译好的代码,效率往往会低。如何减少解释的次数和复杂性, 是提高解释器效率的难题。



## 关于代码, 需要知道的几个概念

### 高级语言代码 High-Level Code

高级语言代码, 是指由高级编程语言编写代码, 对计算机的细节有更高层次的抽象。相对于低级编程语言（low-level programming language）更接近自然语言（人类的语言）。
集成一系列的自动工具（垃圾回收，内存管理等）会让程序员延长寿命, 更快乐的编写出更简洁，更易读的程序代码。


### 低级语言代码 Low-Level Code

低级语言代码, 指由低级编程语言编写的代码, 相对高级语言, 少了更多的抽象概念, 更加接近于汇编或者机器指令。但是这也意味着代码的可移植性很差。

越高级的语言，性能、自由度越不及低级语言。但是在抽象、可读可写性、可移植性越比低级语言优秀。

在以前的年代, C/C++语言相对汇编语言, 机器指令来说, 肯定是高级语言。
而到了今天, 我们更多人对 C 语言偏向认知为「低级语言」。


### 汇编语言 Assembly Language


