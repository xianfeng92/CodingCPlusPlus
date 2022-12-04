# Core dump

## 启用 Core dump, 系统默认关闭

Core 文件其实就是内存的映像, 当程序崩溃时, 存储内存的相应信息, 主用用于对程序进行调试。

用到的命令是: ulimit

// 输入目录查看状态, 0 说明是禁止生成 core 文件
[root@ ~]# ulimit -c
0

我们可以直接在 ulimit -c 后面加上参数:

# unlimited: 字面意思, 没有限制 core 文件大小
[root@ ~]# ulimit -c unlimited

这个只是针对当前这个 bash environment, 如果想要永久修改可以修改配置文件：

vim /etc/profile，然后添加上面的命令 ulimit - c unlimited. 然后执行 source /etc/profile 或者重启使刚刚的配置可以生效。

##  设置 core 文件的存储目录和命名格式

设置 core 的存储目录和命名格式, 主要是修改配置文件 /proc/sys/kernel/core_pattern:

# 1. 默认在当前程序执行目录下生成, core-程序名-程序pid-时间 [core-test-3451-1516257740]
[root@ ~]# echo "core-%e-%p-%t" > /proc/sys/kernel/core_pattern

# 2. 添加路径, 可以把所有的 core 集中到一个文件夹里 [把所有的 core 文件放到 /root/core-file 目录下]
[root@ ~]# echo "/root/core-file/core-%e-%p-%t" > /proc/sys/kernel/core_pattern


## Ubuntu

ubuntu20 的服务 apport.service 会自动生成崩溃报告, 这个服务导致 core_pattern 不能生效。

### 关闭apport.service服务

sudo systemctl disable apport.service

如果这个命令无法关闭的话, 可以修改 /etc/default/apport 文件, 将 enable 改成 0

/etc/default/apport

### Ubuntu core_pattern config
sudo bash -c 'echo /home/xforg/Desktop/CodingCPlusPlus/NoteBook/CoreDump/core.%e.%p > /proc/sys/kernel/core_pattern'




#define SIG_KERNEL_COREDUMP_MASK (\
        rt_sigmask(SIGQUIT)   |  rt_sigmask(SIGILL)    | \
>   rt_sigmask(SIGTRAP)   |  rt_sigmask(SIGABRT)   | \
        rt_sigmask(SIGFPE)    |  rt_sigmask(SIGSEGV)   | \
>   rt_sigmask(SIGBUS)    |  rt_sigmask(SIGSYS)    | \
        rt_sigmask(SIGXCPU)   |  rt_sigmask(SIGXFSZ)   | \
>   SIGEMT_MASK>>   >   >          )
 
#define sig_kernel_coredump(sig)>   siginmask(sig, SIG_KERNEL_COREDUMP_MASK)