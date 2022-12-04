## SIGFPE
### 什么是 SIGFPE？

SIG 是信号名的通用前缀。FPE 是 floating-point exception（浮点异常）的首字母缩略字。在 POSIX 兼容的平台上, SIGFPE 是当一个进程执行了一个错误的算术操作时发送给它的信号。

### 导致 SIGFPE 被发送给进程的原因

1.FPE_INTDIV    整数除以零
2.FPE_INTOVF    整数上溢
3.FPE_FLTDIV    浮点除以零
4.FPE_FLTOVF    浮点上溢
5.FPE_FLTUND    浮点下溢
6.FPE_FLTRES    浮点结果不准
7.FPE_FLTINV    无效浮点操作
8.FPE_FLTSUB    浮点下标越界


## SIGTRAP

### 什么是 SIGTRAP?

通常来说 SIGTRAP 是由断点指令或其它 trap 指令产生.由 debugger 使用。如果没有附加调试器, 则该过程将终止并生成崩溃报告。

### 导致 SIGTRAP 被发送给进程的原因
 
Debugger 模式下, 设置断点, 当程序运行到断点时候, 就会引发 SIGTRAP

