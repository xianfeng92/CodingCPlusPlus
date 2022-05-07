// !! 泛型编程风格

Standard Template Library(STL) 主要由两种组件构成: 一是容器(container), 包括 vector、list、set、map 等类; 另一种组件是用以操作这些容器的所谓泛型算
法(generic algorithm), 包括 find()、sort()、replace()、merge()等。


vector 和 list 这两种容器是所谓的顺序性容器(sequential container)。顺序性容器会依次维护第一个、第二个……直到最后一个元素。'我们在顺序性容器身上主要进行所谓
的迭代(iterate)操作'。

map 和 set 这两种容器属于关联容器(associative container)。'关联容器可以让我们快速查找容器中的元素值'。所谓 set, 其中仅含有 key。'我们对它进行查询操作, 
为的是判断某值是否存在于其中'。

如果我们想要建立一组索引表, 用来记录出现于新闻、故事中的字眼, 我们可能会希望将一些中性字眼如 the、an、but 排除掉。在让某个字眼进入索引表之前, 我们要先查询
excluded_word 这么一个 set, 如果这个字眼在里面, 我们便忽略它不再计较; 反之则将它加入索引表。

泛型算法提供了许多可作用于容器类及数组类型上的操作。'这些算法之所以被称为泛型 (generic), 是因为它们和它们想要操作的元素类型无关'。

举个例子, 它们和元素类型究竟是 int、double 或  string 全然无关。它们同样也和容器类彼此独立(不论容器是 vector、list 或 array)


泛型算法系通过 function template 技术, 达到"与操作对象的类型相互独立"的目的。而实现"与容器无关"的诀窍, 就是不要直接在容器身上进行操作。

而是借由一对 iterator (first 和 last), 标示我们要进行迭代的元素范围。如果  first 等于 last, 算法便只作用于 first 所指元素。如果 first 不等于 last,算
法便会首先作用于 first  所指元素身上, 并将 first 递增, 指向下一个位置, 然后再比较 first 和  last 是否相等, 如此持续进行, 直到 first 等于  last 为止。



// !! 指针的算术运算

The Arithmetic of Pointers

假设我们需要完成以下工作。给定一个储存整数的 vector,以及一个整数值。如果此值存在于 vector 内, 我们必须返回一个指针指向该值; 反之则返回  0,表示此值并不在
vector 内。

以下便是我的做法:

int * find(const vector<int> &vec, int value){
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] == value){
            return &vec[i];
        }
    }
    return 0;
}

测试这个函数, 发现其结果的确满足我们的需求。

接下来我们又获得一个新任务: 想办法让这个函数不仅可以处理整数, 更可以处理任何类型--前提是该类型定义有 equality 运算符。


template<typename elemType>
elemType * find(const vector<elemType> &vec, elemType elem) {
    for (int i = 0; i < vec.size(); ++i){
        if(vec[i] == elem){
            return &vec[i];
        }
    }
    return 0;
}

再次测试这个函数, 其执行结果同样符合我们的需求。

下一个任务, 便是要让这个函数同时可以处理 vector 与 array 内的任意类型元素--当然该类型的 equality 运算符皆已定义。首先映入脑海的想法便是将此函数重载
(overload), 一份用来处理 vector, 另一份用以处理 array。


有一种存在已久的难题对策, 就是将问题分割为数个较小、相对而言较简单的子问题。

本例之中我们的大问题可切割为:1. 将 array 的元素传入 find(), 而非指明该 array; 2.将 vector 的元素传入 find() 而不指明该 vector。理想情况下, 这两个问
题的解法之中会包含我们最初问题的共通解法。


首先解决 array 的处理问题。如何才能够在不指定 array 的情形之下将其元素传入 find() 呢?

如果我们能够完全理解我们企图解决的问题, 那么编写程序便有如探囊取物。本例中如果能够清楚了解 array 如何被传入函数, 以及 array 如何被函数返回,将非常有助于解
答。当我写下:

int min(int array[24]){
    ...
}

min() 似乎仅能接受某个拥有 24 个元素的 array, 并且以传值方式传入。事实上这两个假设都是错的: array 并不会以传值方式复制一份, 而且我们可以传递任意大小的
array 给 min()。我知道你一定在想, 怎么会这样呢?


指向 array 开头的指针, 使我们得以开始对 array 进行读取操作。接下来我们必须设法告诉 min(), 应该在何处停止对 array 的读取。解法之一是: 增加一个参数, 用来表
示 array 的大小。

以下便是采用此法完成的 find(), 声明如下:

template <typename elemType>
elemType *find(const elemType* array, int size, const elemType &value) {
    ...
}

解法之二则是传入另一个地址, 指示 array 读取操作的终点。(我们将此值称为"标兵")


template <typename elemType>
elemType *find(const elemType* array, elemType *end, const elemType &value) {
    ...
}

这种解法最让人感兴趣的地方便是, array 从参数列表中彻底消失了——这形同解决了我们的第一个小问题。

虽然 array 以第一个元素的指针传入 find()中, 但我们看到, 仍然可以通过 subscript 运算符访问 array 的每个元素, 就如同此 array 是个对象一般。为什么呢?因为事
实上'所谓下标操作就是将 array 的起始地址加上索引值, 产生出某个元素的地址, 然后该地址再被 dereference 以返回元素值'。

template <typename elemType>
elemType * find(const elemType *first, const elemType *last, const elemType &value){
    if(!first || !last) return 0;
    for(; first != last; ++first){
        if(*first == value){
            return first;
        }
    }
    return 0;
}

上述函数完成了我们所设定的两个子任务中的第一个: 我们已经完成 find() 的实现, 而且不论数组元素的类型是什么, 我们都可以访问数组中的每个元素。














