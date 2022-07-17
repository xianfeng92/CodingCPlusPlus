// !! 6.5　Linux 内核装载 ELF 过程简介

当我们在 Linux 系统的 bash 下输入一个命令执行某个 ELF 程序时, Linux 系统是怎样装载这个 ELF 文件并且执行它的呢?

首先在用户层面, bash 进程会调用 fork() 系统调用创建一个新的进程, 然后新的进程调用 execve() 系统调用执行指定的 ELF 文件, 原先的 bash 进程继续返回等待刚才启动的
新进程结束, 然后继续等待用户输入命令。

execve() 系统调用被定义在 unistd.h, 它的原型如下:

int execve(const char *filename, char *const argv[], char *const envp[]);

它的三个参数分别是被执行的程序文件名、执行参数和环境变量。

下面是一个简单的使用 fork() 和 execlp() 实现的 minibash:

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    char buf[1024] = {0};
    pid_t pid;
    while (1) {
        printf("minibash$");
        scanf("%s", buf);
        if(pid == 0) {
            if(execlp(buf, 0 ) < 0){
                printf("exec error\n");
            }
        }else if(pid > 0){
             int status;
             waitpid(pid,&status,0);
        }else {
             printf("fork error %d\n",pid);
        }
    }
    return 0;
}

'在进入 execve() 系统调用之后, Linux 内核就开始进行真正的装载工作'。在内核中, execve() 系统调用相应的入口是 sys_execve(), 它被定义在 arch\i386\kernel\
Process.c。sys_execve() 进行一些参数的检查复制之后, 调用 do_execve()。do_execve() 会首先查找被执行的文件, 如果找到文件, 则读取文件的前 128 个字节。为什么
要这么做呢? 因为我们知道, Linux 支持的可执行文件不止 ELF 一种, 还有 a.out、Java 程序和以 #! 开始的脚本程序。

这里 do_execve() 读取文件的前 128 个字节的目的是判断文件的格式, 每种可执行文件的格式的开头几个字节都是很特殊的, 特别是开头 4 个字节, 常常被称做 Magic Number,通过
对魔数的判断可以确定文件的格式和类型。

比如 ELF 的可执行文件格式的头 4 个字节为 0x7F、e、l、f; 而 Java 的可执行文件格式的头 4 个字节为c、a、f、e; 如果被执行的是 Shell 脚本或 perl、python 等这种解释型
语言的脚本, 那么它的第一行往往是 #!/bin/sh 或 #!/usr/bin/perl 或 #!/usr/bin/python, 这时候前两个字节 # 和 ! 就构成了魔数, 系统一旦判断到这两个字节,就对后面的字
符串进行解析, 以确定具体的解释程序的路径。

当 do_execve() 读取了这 128 个字节的文件头部之后, 然后调用 search_binary_handle() 去搜索和匹配合适的可执行文件装载处理过程。

'Linux 中所有被支持的可执行文件格式都有相应的装载处理过程, search_binary_handle() 会通过判断文件头部的魔数确定文件的格式, 并且调用相应的装载处理过程'。

a.out 可执行文件的装载处理过程叫做 load_aout_binary(); 而装载可执行脚本程序的处理过程叫做 load_script()。

这里我们只关心 ELF 可执行文件的装载, load_elf_binary() 被定义在 fs/Binfmt_elf.c, 这个函数的代码比较长, 它的主要步骤是:

1. 检查 ELF 可执行文件格式的有效性, 比如魔数、程序头表中段的数量

2. 寻找动态链接的 .interp 段, 设置动态链接器路径

3. 根据 ELF 可执行文件的程序头表的描述, 对 ELF 文件进行映射, 比如代码、数据、只读数据

4. 初始化 ELF 进程环境, 比如进程启动时 EDX 寄存器的地址应该是 DT_FINI 的地址

5. 将系统调用的返回地址修改成 ELF 可执行文件的入口点, 这个入口点取决于程序的链接方式, 对于静态链接的 ELF 可执行文件, 这个程序入口就是 ELF 文件的文件头中 e_entry
   所指的地址; 对于动态链接的 ELF 可执行文件, 程序入口点是动态链接器

当 load_elf_binary() 执行完毕, 返回至 do_execve() 再返回至 sys_execve() 时, 上面的第 5 步中已经把系统调用的返回地址改成了被装载的 ELF 程序的入口地址了。所以当
sys_execve() 系统调用从内核态返回到用户态时, EIP 寄存器直接跳转到了 ELF 程序的入口地址, 于是新的程序开始执行, ELF 可执行文件装载完成。
