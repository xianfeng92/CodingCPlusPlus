
## 什么是段错误(segmentation fault)

A segmentation fault (often shortened to SIGSEGV) is a particular error condition that can occur during the operation of computer software. 

### A segmentation fault occurs when a program attempts to access a memory location that it is not allowed to access, or attempts to access a memory location in a way that is not allowed (for example, attempting to write to a read-only location, or to overwrite part of the operating system).

Segmentation is one approach to memory management and protection in the operating system. 

It has been superseded by paging for most purposes, but much of the terminology of segmentation is still used, "segmentation fault" being an example. 
Some operating systems still have segmentation at some logical level although paging is used as the main memory management policy.

On Unix-like operating systems, a process that accesses an invalid memory address receives the SIGSEGV signal. 

#### 当程序试图访问不被允许访问的内存区域（比如, 尝试写一块属于操作系统的内存 or access 0 address memory）或以错误的类型访问内存区域（比如, 尝试写一块只读内存）

1. SIGSEGV 是在访问内存时发生的错误, 它属于内存管理的范畴

2. SIGSEGV 是一个用户态的概念, 是操作系统在用户态程序错误访问内存时所做出的处理

3. 当用户态程序访问（访问表示读、写或执行）不允许访问的内存时, 产生 SIGSEGV

4. 当用户态程序以错误的方式访问允许访问的内存时, 产生 SIGSEGV

SIGILL 对应的常数是 11.

