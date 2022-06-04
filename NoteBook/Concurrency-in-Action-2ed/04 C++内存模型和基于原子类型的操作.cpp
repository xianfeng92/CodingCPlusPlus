// !! C++ 内存模型和基于原子类型的操作

// !! 内存模型基础

1. 为了避免 race condition, 线程就要规定执行顺序。一种方式是使用 mutex, 后一线程必须等待前一线程解锁。第二种方式是使用原子操作来避免竞争访问同一内存位置

2. 原子操作是不可分割的操作, 要么做了要么没做, 不存在做一半的状态。原子操作不存在修改过程中值被其他线程看到的情况，也就避免了竞争风险

3. 如果对象不是原子类型，就要通过同步来保证线程遵循每个变量的修改顺序。如果一个变量对于不同线程表现出不同的值序列，就会导致数据竞争和未定义行为。



// !! 原子操作和原子类型

// !! 标准原子类型

标准原子类型定义在 <atomic> 中。也可以用 mutex 模拟原子操作,实际上标准原子类型可能就是这样实现的, 它们都有一个 is_lock_free 函数, 返回 true 说明该原子
类型操作是无锁的, 用的是原子指令, 返回 false 则是用锁


struct A{
  int a[100];
};


struct B{
  int x, y;
};

assert(!std::atomic<A>{}.is_lock_free());
assert(std::atomic<B>{}.is_lock_free());


原子操作的主要用处是替代 mutex 实现同步。如果原子操作内部是用 mutex 实现的,就不会有期望的性能提升, 还不如直接用 mutex 来同步。C++17 中每个原子类型都有一个
is_always_lock_free 成员变量, 为 true 时表示该原子类型在此平台上 lock-free。

assert(std::atomic<int>{}.is_always_lock_free());


C++17 之前可以用标准库为各个原子类型定义的 ATOMIC_xxx_LOCK_FREE 宏来判断该类型是否无锁, 值为 0 表示原子类型是有锁的, 为 2 表示无锁, 为 1 表示运行时才能
确定

// LOCK-FREE PROPERTY
#define ATOMIC_BOOL_LOCK_FREE 2
#define ATOMIC_CHAR_LOCK_FREE 2
#ifdef __cpp_lib_char8_t
#define ATOMIC_CHAR8_T_LOCK_FREE 2
#endif // __cpp_lib_char8_t
#define ATOMIC_CHAR16_T_LOCK_FREE 2
#define ATOMIC_CHAR32_T_LOCK_FREE 2
#define ATOMIC_WCHAR_T_LOCK_FREE  2
#define ATOMIC_SHORT_LOCK_FREE  2
#define ATOMIC_INT_LOCK_FREE    2
#define ATOMIC_LONG_LOCK_FREE   2
#define ATOMIC_LLONG_LOCK_FREE  2
#define ATOMIC_POINTER_LOCK_FREE  2

只有 std::atomic_flag 未提供 is_lock_free,该类型是一个简单的布尔标志, 所有操作都保证 lock-free。基于 std::atomic_flag 就能实现一个简单的锁, 并实现其
他基础原子类型。其余原子类型可以通过特化 std::atomic 来实现，且可以有更完整的功能，但不保证 lock-free 标准库中为 std::atomic 对内置类型的特化定义了类型别
名


namespace std{
    using atomic_bool = std::atomic<bool>;
    using atomic_char = std::atomic<char>;
}


通常类型 std::atomic<T> 的别名就是 atomic_T

namespace std {
using atomic_schar = std::atomic<signed char>;
using atomic_uchar = std::atomic<unsigned char>;
using atomic_uint = std::atomic<unsigned>;
using atomic_ushort = std::atomic<unsigned short>;
using atomic_ulong = std::atomic<unsigned long>;
using atomic_llong = std::atomic<long long>;
using atomic_ullong = std::atomic<unsigned long long>;
}  // namespace std

原子类型不允许由另一个原子类型拷贝赋值，因为拷贝赋值调用了两个对象，破坏了操作的原子性。但可以用对应的内置类型赋值


T operator=(T desired) noexcept;
T operator=(T desired) volatile noexcept;
atomic& operator=(const atomic&) = delete;
atomic& operator=(const atomic&) volatile = delete;

此外 'std::atomic 为支持赋值提供了成员函数'

std::atomic<T>::store;
std::atomic<T>::load;
std::atomic<T>::exchange  // 替换值, 并返回被替换前的值

// 与期望值比较，不等则将期望值设为原子值并返回 false
// 相等则将原子值设为目标值并返回 true
// 在缺少 CAS（compare-and-exchange）指令的机器上，weak 版本在相等时可能替换失败并返回 false
// 因此 weak 版本通常要求循环，而 strong 版本返回 false 就能确保不相等
std::atomic<T>::compare_exchange_weak
std::atomic<T>::compare_exchange_strong

std::atomic<T>::fetch_add        // 原子加法，返回相加前的值
std::atomic<T>::fetch_sub        // 原子减法，返回相减前的值

std::atomic<T>::fetch_and
std::atomic<T>::fetch_or
std::atomic<T>::fetch_xor
std::atomic<T>::operator++       // 前自增等价于 fetch_add(1) + 1
std::atomic<T>::operator++(int)  // 后自增等价于 fetch_add(1)
std::atomic<T>::operator--       // 前自减等价于 fetch_sub(1) - 1
std::atomic<T>::operator--(int)  // 后自减等价于 fetch_sub(1)
std::atomic<T>::operator+=       // fetch_add(x) + x
std::atomic<T>::operator-=       // fetch_sub(x) - x
std::atomic<T>::operator&=       // fetch_and(x) & x
std::atomic<T>::operator|=       // fetch_or(x) | x
std::atomic<T>::operator^=       // fetch_xor(x) ^ x

这些成员函数有一个用来指定内存序的参数 std::memory_order, 后续会解释内存序的含义

typedef enum memory_order {
    memory_order_relaxed,
    memory_order_consume,
    memory_order_acquire,
    memory_order_release,
    memory_order_acq_rel,
    memory_order_seq_cst
} memory_order;

void store(T desired, std::memory_order order = std::memory_order_seq_cst);
// store 的内存序只能是
// memory_order_relaxed、memory_order_release、memory_order_seq_cst

T load(std::memory_order order = std::memory_order_seq_cst);
// load 的内存序只能是
// memory_order_relaxed、memory_order_consume、memory_order_acquire、memory_order_seq_cst


// !! std::atomic_flag

std::atomic_flag 是一个原子的布尔类型, 也是唯一保证 lock-free 的原子类型

std::atomic_flag x = ATOMIC_FLAG_INIT;

x.clear(std::memory_order_release);  // 将状态设为 false
// 不能为读操作语义：memory_order_consume、memory_order_acquire、memory_order_acq_rel

bool y = x.test_and_set();  // 将状态设为 true 且返回之前的值