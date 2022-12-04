# SIGBUS

## 什么是 SIGBUS

The SIGBUS signal is sent to a process when it causes a bus error. The conditions that lead to the signal being sent are, for example, incorrect 
memory access alignment or non-existent physical address.

通常来说 SIGBUS, 是由于进程引起了一个总线错误（Bus error）。

### 导致 SIGBUS 的原因

#### 未对齐的读或写

事实上, 总线错误几乎都是由于未对齐的读或写引起的。它之所以称为总线错误, 是因为出现未对齐的内存访问请求时, 被阻塞(block)的组件就是地址总线.
##### 对齐(alignment)的意思就是数据项只能存储在地址是数据项大小的整数倍的内存上。

在现代的计算机架构中, 尤其是 RISC 架构, 都需要数据对齐, 因为与任意的对齐有关的额外逻辑会使整个内存系统更大且更慢。

通过迫使每个内存访问局限在一个 cache 行或一个单独的页面内, 可以极大地简化并加速如 cache 控制器和内存管理单元(MMU)这样的硬件。 

我们用地址对齐这个术语来陈述这个问题, 而不是直截了当地说是禁止内存跨页访问, 但它们说但是同一回事。

例如，访问一个8字节的double数据时，地址只允许是8的整数倍。所以一个 double 数据可以存储于地址 24, 地址 8008 或 32768, 但不能存储于地址 1006(因为它无法被8整除)。

##### 页和 cache 的大小都是经过精心设计的, 这样只要遵守对齐规则就可以保证一个原子数据项不会跨过一个页或 cache 块的边界。