// !! 面向对象编程风格

class 的主要用途在于引入一个崭新的数据类型, 能够更直接地在我们所设计的程序系统中, 表现我们想表现的实体。好比图书馆的借阅系统, 如果我们利用 Book、Borrower 、
DueDate 这些类来进行程序设计,往往会比使用基本的字符类型、算术类型、布尔类型轻松多了。

当我们的应用系统布满许多类, 其间有着是一种(is-a-kind-of)的关系时,以对象为基础 object-based 的编程模型反而会拖累我们的程序设计工作。

以对象为基础 (object-based) 的类机制无法轻松针对这四个 are-a-kind-of 的 Book 类的共通性质进行系统化的划分。

为什么? 

因为这种模型无法让我们更进一步地指出类间的关系。类间的关系依赖面向对象编程模型 (object-oriented programming model) 加以设定。



// !! 面向对象编程概念

Object-Oriented Programming Concepts

面向对象编程概念的两项最主要特质是: 继承 (inheritance) 和多态 (polymorphism)。














