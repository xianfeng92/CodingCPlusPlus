// !! 库

C++ 是可扩展的。用户不能改变底层语言本身——不能增加新的操作符或者改变语法——但是可以为这门语言增加新的类型。

'迄今为止我们所见过的绝大多数类都是为解决特定问题而设计的'。我们曾经考虑过类是否可在所有情况下为所有用户使用。我们曾花费过精力
来改进类，但最关注的还是在原有条件下使用类。这是大部分类被设计和创建的过程。但是，'有时我们想做的不仅仅是为方便自己使用增加新类型，
还希望支持其他用户的使用需求'。

'如果某一组类的设计和实现是希望得到广泛应用，那么我们就称之为库'。

为了设计其他人也能使用的类，库作者需要承担许多类似语言设计者的工作。类的使用者希望这个类足够“聪明”。他们希望类设计者提供的行为，
与我们通常希望编译器提供的行为相似: 正确地创建、复制、赋值或者销毁对象。。他们还希望类有一些合理的语义：要有足够的操作供他们以
直观的或者自然的方式使用这个类。

所谓的“聪明”，还要求类接口的设计有助于减少用户可能犯下的错误，这一点总是被人忽视。








