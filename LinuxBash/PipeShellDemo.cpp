#include <iostream>

// !! 管道作用

管道实际上就是进程之间的一个通信工具，那么用在 Linux 命令中主要是方便两条命令互相之间可以相互通信。

// !! 管道符

管道符（匿名管道）是 Shell 编程经常用到的通信工具,管道符是 "|"，主要是把两个应用程序连接在一起，然后把第一个应用程序的输出，
作为第二个应用程序的输入。如果还有第三个应用程序的话，可以把第二个程序的输出，作为第三个应用程序的输入，以此类推。

// !! 管道符与分号符

管道符还有一个需要注意的地方，我们可以通过下面的命令观察到，在使用管道符的时候，管道符会为两条命令产生了子进程。

如 ls | grep test.sh ，在当前文件过滤出 test.sh 文件。管道符 "|" 就把 ls 命令的文件列表输出给到了 grep test.sh 命令来过滤文件

» cat | ps -f                                                 parallels@xforg
UID          PID    PPID  C STIME TTY          TIME CMD
paralle+   16176   16168  1 09:17 pts/0    00:00:00 zsh
paralle+   16252   16176  0 09:17 pts/0    00:00:00 cat
paralle+   16253   16176  0 09:17 pts/0    00:00:00 ps -f

父进程 bash 的 pid 为 16176 ，子进程 cat 的 pid 为 16252 ，子进程 ps -f 的 pid 为 16253。

由于管道符是会为连接的命令产生子进程，所以也是不会影响当前环境的。

我们用 cd /home/ | ls 命令验证下，运行结果如下:

~/Stan » cd xforg |  ls                                         parallels@xforg
rsync_xforg.sh  shellcolorconfig  StanBackUp.sh  toolchain  wallpapar  xforg
--------------------------------------------------------------------------------
~/Stan »    

如果使用分号 ";" 连接两条命令会如何呢 ？

~/Stan » cd xforg ;  ls                                         parallels@xforg
back             linux_asr_1.0_1015_forTraceCnPerformance  nomiSocket
CodingCPlusPlus  linux_asr_1.0_1015_GoogleCodingStyle      rsync_xforg.sh
flutterbuffers   linux_asr_1.0_1025
gdb              linux_asr_1.0_GoogleCodingStyle
---------------------------------------------------

可以得知，通过分号 ";" 连接，cd 命令会对当前环境造成影响。

分号符和管道符都可以连接两条命令，但是其作用是不同的:

1. 分号符实际上就是隔开两条命令，第一条执行完，接着执行完第二条，两条命令之间是没有任何关系的。

2. 管道符的作用是把第一条执行的命令结果传递给第二条命令，同时会为第一条和第二条命令建立子进程，由于命令是在子进程运行的，
   如果命令有类似 cd 切换目录这种内建命令，也就不会对当前环境造成影响。所以在使用管道符的时候，要规避使用内建命令。

int main(int argc, char **argv)
{

}