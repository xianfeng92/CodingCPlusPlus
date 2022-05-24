// !!  以 template 进行编程

Bjarne Stroustrup (C++ 创造者)拟好 C++ 语言中关于 template 的原始设计后, 将 template 称为被参数化的类型: 称其参数化是因为类型相关信息可自 template
定义中剥离, 称其类型则是因为'每一个 class template 或 function template 基本上都随着它所作用或它所内含的类型而有性质上的变化'(因此这些 class template 
或 function template 本身就像是某种类型)。

template 所接受(或说作用于其上)的类型, 系由 template 用户于使用时指定。

其后不久, Stroustrup 将名称改为比较通俗顺口的 template。'Template 定义扮演的乃是处方角色, 能根据用户指定的特定值或特定类型, 自动产生一个函数或类'。

在数据结构中, 所谓树 (tree) 乃是由节点 (node) 以及连接不同节点的链接 (link) 组成。所谓二叉树, 维护着每个节点与下层另两个节点间的两条链接, 一般将此下层
二节点称为左子节点 (left child) 和右子节点 (right child)。最上层第一个节点称为根节点 (root)。无论是左子节点或右子节点, 都可能扮演另一棵子树 (subtree)
的根节点。一个节点如果不再有任何子节点, 便称为叶节点 (leaf)。

我们的二叉树包含两个 class:一个是 BinaryTree, 用以储存一个指针, 指向根节点; 另一个是 BTnode, 用来储存节点实值, 以及连接至左、右两个子节点的链接。此处,
节点实值的类型(value type) 正是我们希望加以参数化的部分。

我们的 BinaryTree 类该提供哪些操作行为呢 ?

用户必须能够将元素插入 (insert) 到 BinaryTree, 必须能够从 BinaryTree 移除 (remove) 特定元素, 也能够在树中搜寻 (find) 某个元素、清除 (clear)所有
元素、以特定的遍历方式打印 (print) 整棵树。 我们必须支持三种遍历方式: 中序 (inorder)、前序 (preorder)、后序 (postorder)。

在我的实现中, 第一个插入空树(empty tree)的值, 会成为此树的根节点。接下来的每个节点都必须以特定规则插入: 如果小于根节点, 就被置于左子树; 如果大于根节点, 就
被置于右子树。任何一个值只能在树中出现一次, 但是此树有能力记录同一值的插入次数。

举个例子, 以下程序代码:

BinaryTree<std::string> bt;
bt.insert("Piglet");

会使 Piglet 成为二叉树的根节点。假设接着插入 Eeyore:

bt.insert("Eeyore");

由于 Eeyore 小于 Piglet (按字典排列顺序), 于是 Eeyore 便成了 Piglet 的左子节点。假设接下来再插入 Roo:

bt.insert("Roo");

由于 Roo 大于 Piglet (按字典排列顺序), 于是 Roo 便成了 Piglet 的右子节点, 以此类推。

任何遍历算法 (traversal algorithm) 皆由根节点出发。'所谓前序 (preorder) 遍历, 是指被遍历的节点本身先被打印, 然后才打印左子树内容, 再往后才轮到右子树内容'。
'所谓中序 (inorder) 遍历, 是先打印出左子树, 然后是节点本身, 最后才轮到右子树'。所谓后序 (postorder) 遍历, 则是先打印左子树，再打印右子树，最后才是节点本身。


// !! 被参数化的类型


Parameterized Types

以下是一个 non-template BTnode class, 其实值储存于 string 对象之中。我把它命名为 string_BTnode, 因为后续我还会定义其他 class, 分别储存 int、double
等节点值。


class string_BTnode{
public:
  std::string val_;
  string_BTnode * lchild;
  string_BTnode * rchild;
};


由于缺乏 template 机制, 为了储存不同类型的数值, 我必须为它们实现各种不同的 BTnode 类, 并且取不同的名称。

'template 机制帮助我们将类定义中与类型相关 type-dependent 和独立于类型之外的两部分分离开来'。


遍历二叉树、插入/移除节点、维护重复次数等行为, 并不会随着处理的类型不同而有所不同, 因此这些程序代码可以在通过 class template 产生出来的所有 class 中使用。


class template 所产生出来的各个 class, 其实值类型都有可能不同: 可能是 string, 也可能是 int 或 double 等。

在一个 class template 中, 与类型相关的部分会被抽取出来, 成为一个或多个参数。


以 BTnode class 为例, data member_val 的类型便可被参数化:

template<typename valueType>
class BTnode;

在此 class template 定义中, valType 被拿来当作一个占位符。其名称可以任意设定。在用户为它指定某个特定类型之前, 它被视为一个可取代为任意类型的东西。

是的, 类型参数 type parameter 可以被拿来用在实际类型(诸如 int、string) 的使用场合。在 BTnode class 中, 我们拿它来声明 val_  所属类型:

template <typename valueType>
class BTnode{
public:
  //...
private:
  valueType val_;
  BTnode *lchild;
  BTnode *rchild;
};

在我的实现中, BTnode class template 必须和 BinaryTree class template 配合使用。BTnode 储存了节点实值、节点实值的重复次数、左右子节点的指针。还记得
两个相互合作的 class 需要建立友谊吗? 针对每一种 BTnode 实际类型, 我们希望对应的 BinaryTree 能够成为其 friend。声明方法如下:


template <typename Type>
class BinaryTree;// forward declaration

template <typename valType>
class BTNode{
friend class BinaryTree<valType>;
...
};

为了通过 class template 实例化类, 我们必须在 class template 名称之后, 紧接一个尖括号,其内放置一个实际类型(准备用来取代 valType)。


BTnode<int> bti;

同样道理, 如果要将 valType 绑定至 string, 可以这么写:

BTnode<std::string> bts;


上述的 bti 和 bts 分别代表两份 BTnode 定义: 前者以 int 取代 val_, 后者以 string 取代 val_。

代入 string 而产生出来的 BinaryTree 是代入 string 所产生出来的 BTnode 的 friend


template <typename elemType>
class BinaryTree{
public:
private:
  BTNode<elemType> *root_;
  //...
};

当我们指定某个实际类型作为 BinaryTree 的参数, 例如:

BinaryTree<std::string> st;

指针 root_ 便指向一个节点值类型为 string 的 BTnode。



// !! Class Template的定义

The Template Class Definition

template<typename elemType>
class BinaryTree{
public:
  BinaryTree();
  BinaryTree(const BinaryTree&);
  ~BinaryTree();
  BinaryTree& operator=(const BinaryTree&);
  bool empty() {return root_ = 0;}
  void clear();
private:
  BTnode<elemType> root_;
  void copy(BTnode<elemType>* tar, BTnode<elemType> *src);
};

为 class template 定义一个 inline 函数, 其做法就像为 non-template class 定义一个 inline 函数一样, 上述的 empty() 示范了这一点。


但是, 在类体外 class template member function 的定义语法却大相径庭--起码乍见之下如此:

template <typename elemType>
inline BinaryTree<elemType>::BinaryTree(){
    
}

这个 member function 的定义始于关键字 template 和一个参数列表, 然后便是函数定义本身, 并带有关键字 inline 及 class scope 运算符。inline 一词必须紧接
在关键字 template 和参数列表之后。

为什么上述第二次出现的 BinaryTree 名称就不再需要限定了呢? 因为,在 class scope 运算符出现之后:

BinaryTree<elemType>::

其后所有东西都被视为位于 class 定义范围内。当我们写:

BinaryTree<elemType>::

BinaryTre();

第二次出现的 BinaryTree 便被视为 class 定义范围内, 所以不需要再加以限定。

以下是 BinaryTree 的 copy constructor、copy assignment operator 及 destructor 的定义:


template <typename elemType>
inline BinaryTree<ElemType>::BinaryTree(const BinaryTree& rhs){
    copy(root_, rhs.root_);
}

template <typename elemType>
inline BinaryTree<elemType>::~BinaryTree(){
    clear();
}


template <typename elemType>
inline BinaryTree<elemType>::operator=(const BinaryTree<elemType>& rhs){
    if(this != &rhs){
        clear();
        copy(root_, rhs.root_);
    }
    return *this;
}

此刻你也许不相信我这句话: 写多了诸如此类的定义之后, 这些语法会变得几乎理所当然。



// !! Template 类型参数的处理

Handling Template Type Parameters

处理一个 template 类型参数比处理一个明确的类型参数复杂一些。

举个例子, 如果要为函数声明一个明确的 int 参数, 我会这么写:

bool find(int val);

它以传值 by value 方式进行参数的传递。

如果声明 Matrix class 为函数的参数, 我们可能会改以传址  by reference 方式传递:

bool find(const Matrix& );

这可避免因 Matrix 对象的复制而造成的不必要开销。

虽然, 以下方式也没有错:

bool find(const Matrix);

但它会花较长的时间来得到相同的结果。

但是当我们处理 template 类型参数时,我们无法得知用户实际要用的类型是否为语言内置类型:

BinaryTree<int> bti;

果真如此,当然可以采用 by value 方式编写 find() 的参数列表。但如果它是一个 class 类型:

BinaryTree<Matrix> btm;

就应该以  by reference 方式来编写 find() 的参数列表。


实际运用中, 不论内置类型或 class 类型, 都可能被指定为 class template  的实际类型。我建议, 将所有的 template 类型参数视为 class 类型来处理。这意味着我们
会把它声明为一个 const reference, 而非以 by value 方式传递。


在 constructor 定义中, 我选择在 member initialization list 内为每个类型参数进行初始化操作:

template <typename valType>
inline BTNode<valType>::BTNode(const valType& val)  : val_(val){
    root_ = 0;
    lchild = rchild = 0;
}

而不选择在 constructor 函数体内进行:

template <typename valType>
inline BTNode<valType>::BTNode(const valType& val){
    val_ = val
    root_ = 0;
    rchild = lchild = 0
}

这么一来, 当用户为 valType 指定一个 class 类型时, 可以保证效率最佳。

例如, 下面将 valType 指定为内置类型 int:

BTnode<int> bti(42);

那么上述两种形式并无效率上的差异。但是如果我们这样写:

BTNode<Matrix> btm(matrix);

效率上就有高下之分了。


因为, constructor 函数体内对 val_ 的赋值操作可分解为两个步骤:

1. 函数体执行前 Matrix 的 default constructor 会先作用于 val_ 身上

2. 函数体内会以 copy assignment operator 将 val 复制给 val_。

但如果我们采用上述第一种方法, 在 constructor 的 member initialization list 中将 val_ 初始化, 那么只需一个步骤就能完成工作: 以 copy constructor
将 val 复制给 val_。

重申一次, 不论我们是以传值方式来传递 valType 或是在 constructor 函数体内为类型为 valType 的 data member 设置值都没有错。但是这会花费较多的时间,而且可
能使你背负不谙 C++ 编程技巧的污名。

如果你才刚开始学习 C++, 其实无须过度关心效率方面的议题。然而指出这两种情形的差异,却是十分有用。




// !! 实现一个 Class Template

Implementing the Template Class

每当我们插入某个新值,都必须建立 BTnode 对象、加以初始化、将它链接至二叉树的某处。我们必须自行以 new 表达式和 delete 表达式来管理每个节点的内存分配和释放。

以 insert() 为例, 如果根节点之值尚未设定, 它会由程序的空闲空间(free store)分配一块新的 BTnode 需要的内存空间。否则就调用 BTnode 的 insert_value(),
将新值插入二叉树中:

template <typename elemType>
inline void BinaryTree<elemType>::insert(const elemType& elem){
    if(!root_){
        root_ = new BTnode<elemType>(elem);
    }
    else{
        root_.insert(elem);
    }
}

new 表达式可分解为两个操作:

1. 向程序的空闲空间 free store 请求内存。如果分配到足够的空间, 就返回一个指针, 指向新对象。

2. 如果第一步成功, 并且外界指定了一个初值, 这个新对象便会以最适当的方式被初始化


对 class 类型来说:

root_ = new BTNode<elemType>(elem);

elem 会被传入 BTnode constructor。如果分配失败, 初始化操作就不会发生。


当根节点存在时, insert_value() 才会被调用。小于根节点的所有数值都放在根节点的左子树, 大于根节点的所有数值都放在根节点的右子树。insert_value() 会通过左右
子节点递归 recursively 调用自己, 直到以下任何一种情形发生才停止: 1. 合乎资格的子树并不存在, 2. 欲插入的数值已在树中。由于每个数值只能在树中出现一次,所以我
以 BTnode 的 data member cnt_ 来记录这个节点的插入次数。


template <typename elemType>
class BTnode{
public:
  BTnode *lchild;
  BTnode *rchild;
  elemType val_;
  int cnt_;
private:
};


template <typename elemType>
void BTNode<elemType>::insert_value(const elemType& val){
    if(val_ == val){
        cnt_++;
        return;
    }
    if(val < val_) {
        if(!lchild){
            lchild = new BTnode<elemType>(val);
        }else{
            lchild->insert_value(val);
        }
    }else{
        if(!rchild) {
            rchild = new BTnode<elemType>(val);
        }else{
            rchild->insert_value(val);
        }
    }
}

移除某值的操作更为复杂, 因为我们必须保持二叉树的次序不变。一般的算法是: 以节点的右子节点取代节点本身, 然后搬移左子节点, 使它成为右子节点的左子树的叶节点。
如果此刻并无右子节点, 那么就以左子节点取代节点本身。为了简化,我把根节点的移除操作以特例处理。

template <typename elemType>
inline void BinaryTree<elemType>::remove(const elemType& elem){
    if(!root_){
        if(root_->val_ == elem){
            remove_root();
        }else{
            root_->remove_value(elem, root_);
        }
    }
}

无论 remove_root() 或 remove_value() 都会搬移左子节点, 使它成为右子节点的左子树的叶节点。我将这一操作剥离至 lchild_leaf(), 那是 BTnode 的
static member function:

template <typename valType>
void BTNode<valType>::lchild_leaf(BTNode *leaf, BTNode *subtree){
    while(subtree->lchild){
        subtree = subtree->lchild;
    }
    subtree.lchild = leaf;
}


// !! 一个以 Function Template 完成的 Output 运算符

A Function Template Output Operator

我希望为我们的 BinaryTree class template 提供一个 output 运算符。针对 non-template class, 我们会这么写:

ostream& operator<<(ostream & os, const BinaryTree & rhs);

如果对象是 class template, 我们可以明确指出生成的每个 class 的名称:

ostream& operator<<(ostream & os, const BinaryTree<int> &rhs);


比较好的解法是, 将 output 运算符定义为一个 function template:

template <typename valueType>
inline ostream& operator<<(ostream& os, const BinaryTree<valueType>& bt){
    os << "Tree " << std::endl;
    bt.print(os);
    return os;
}


于是, 当我们写:


BinaryTree<std::string> bts;
cout << bts << std::endl;


编译器便将前述第二参数指定为 BinaryTree<string> 产生一个对应的 output 运算符。


而当我们写:

BinaryTree<int> bti;
cout << bti << std::endl;

编译器便将前述第二参数指定为 BinaryTree<int> 又产生一个对应的 output 运算符。


print() 乃是 BinaryTree class template 的一个 private member function。为了让上述的 output 运算符得以顺利调用 print(), output 运算符必须成
为 BinaryTree 的一个 friend:

template <typename elemType>
class BinaryTree{
friend ostream& operator<<(ostream & os, const BinaryTree<elemType> &);
//...
};



// !! 常量表达式与默认参数值

Constant Expressions and Default Parameters

'Template 参数并不是非得某种类型 (type) 不可。我们也可以用常量表达式 (constant expression) 作为 template 参数'。


例如,先前的数列类继承体系可以重新以 class template 设计, 将对象所含的元素个数参数化:

template <int len>
class num_sequence{
public:
  num_sequence(int beg_pos);
  //...
};

template <int len>
class Fibonacci : public num_sequence<len>{
public:
  Fibonacci(int beg_pos) : num_sequence<len>(beg_pos){}
  //...
};


Fibonacci<16> fb1;
Fibonacci<16> fb2(17);


两个对象皆属于 Fibonacci 而其基类 num_sequence 会因为参数 len 而导致元素个数为 16。


同样道理, 我们也可以将长度和起始位置一并参数化:

template<int len, int beg_pos>
class num_sequence;

由于大部分数列对象的起始位置为 1, 如果我们能为起始位置提供默认值, 就更理想了:

template<int len, int beg_pos>
class num_sequence{...}


template<int len, int beg_pos = 1>
class Fibonacci : public num_sequence<len, beg_pos>{
    ...
}

以下便是上述类的对象定义方式:

num_sequence<32> *p1 = new Fibonacci<32>();

num_sequence<32, 2> *p2 = new Fibonacci<32,2>();



// !! 以 Template 参数作为一种设计策略

Template Parameters as Strategy

现在 LessThan function object 可以水到渠成地转为 class template 了:

template <typename elemType>
class LessThan{
public:
  LessThan(const elemType& val) : val_(val){}
  bool operator()(const elemType& val) const { return val_ < val; }
  void val(const elemType& val) { val_ = val; }
  elemType val() const { return val_; }
private:
  elemType val_;
};

LessThan<int> lti(1024);
LessThan<std::string> lts("Tool");


但是上述这种做法有一个潜在问题: 一旦用户所提供的类型并未定义 less-than 运算符, 上述做法便告失败。另一种可行策略便是提供第二个 class template, 将
comparison 运算符从类定义中剥离。

但虽然这第二个类提供的是和 LessThan 相同的语义, 我们却得为它另外取个名称，因为 class template 无法基于参数列表的不同而重载。就让我把它命名为
LessThanPred 吧--因为 less-than 运算符被我指定为默认参数值:


template <typename  elemType, typename Comp = less<elemType>>
class LessThanPred{
public:
  LessThanPred(const elemType& val) : val_(val) {}
  bool operator()(const elemType& val) const {
      return Comp(val, val_);
  }

  void val(int newVal) { val_ = newVal; }
  elemType val() const { return val_; }

private:
  elemType val_:
};


class StringLen{
public:
  bool operator()(const std::string &s1, const std::string &s2){
      return s1.size() < s2.size();
  }
};

LessThanPred<int> ltpi(1024);
LessThanPred<std::string, StringLen> ltps("Hello");


我们可能会以另一个更通用的名称来命名 function object, 表示它足以支持任何类型的比较操作。那么, 本例就不需要再提供默认的 function object 了:

template<typename num_seq>
class NumericSequence{
public:
  NumericSequence(int  len = 1, int beg_pos = 1) : ns_(len, beg_pos){

  }

  void calc_elems(int sz) const {ns_.calc_elems(sz);}
  bool is_elem(int  elem) const { return ns_.is_elem(elem);}
private:
  num_seq ns_;
};


// !!  Member Template Function

Member Template Functions

当然, 我们也可以将 member function 定义成 template 形式。


class PrintIt{
public:
  PrintIt(ostream& os) : os_(os){}

  template<typename elemType>
  void print(const elemType& elem, char delimiter = '\n'){
      os_<< elem << delimiter;
  }
};





















