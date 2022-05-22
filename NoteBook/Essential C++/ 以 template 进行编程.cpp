// !!  以 template 进行编程

Bjarne Stroustrup (C++ 创造者)拟好 C++ 语言中关于 template 的原始设计后, 将 template 称为被参数化的类型: 称其参数化是因为类型相关信息可自 template
定义中剥离, 称其类型则是因为'每一个 class template 或 function template 基本上都随着它所作用或它所内含的类型而有性质上的变化'(因此这些 class template 
或 function template 本身就像是某种类型)。

template 所接受(或说作用于其上)的类型, 系由 template 用户于使用时指定。

其后不久, Stroustrup 将名称改为比较通俗顺口的 template。'Template 定义扮演的乃是处方角色, 能根据用户指定的特定值或特定类型, 自动产生一个函数或类'。

在数据结构中, 所谓树 (tree) 乃是由节点 (node) 以及连接不同节点的链接 (link) 组成。所谓二叉树, 维护着每个节点与下层另两个节点间的两条链接, 一般将此下层二
节点称为左子节点 (left child) 和右子节点 (right child)。最上层第一个节点称为根节点 (root)。无论是左子节点或右子节点, 都可能扮演另一棵子树 (subtree)的
根节点。一个节点如果不再有任何子节点, 便称为叶节点 (leaf)。

我们的二叉树包含两个 class:一个是 BinaryTree, 用以储存一个指针, 指向根节点; 另一个是 BTnode, 用来储存节点实值, 以及连接至左、右两个子节点的链接。此处,
节点实值的类型(value type) 正是我们希望加以参数化的部分。

我们的 BinaryTree 类该提供哪些操作行为呢? 

用户必须能够将元素插入 (insert) 到 BinaryTree, 必须能够从 BinaryTree 移除 (remove) 特定元素, 也能够在树中搜寻 (find) 某个元素、清除 (clear)所有
元素、以特定的遍历方式打印 (print) 整棵树。我们必须支持三种遍历方式: 中序 (inorder)、前序 (preorder)、后序 (postorder)。

















