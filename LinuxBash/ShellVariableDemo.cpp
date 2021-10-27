#include <iostream>


// !! Linux 中常见的环境变量及其作用


// !! 一、环境变量文件介绍

Linux 中环境变量包括系统级和用户级，系统级的环境变量是每个登录到系统的用户都要读取的系统变量，而用户级的环境变量则是该用户使用
系统时加载的环境变量，所以管理环境变量的文件也分为系统级和用户级的。


// !! 二、Linux 的变量种类

按变量的生存周期来划分，Linux 变量可分为两类:

1.永久的： 需要修改配置文件，变量永久生效

2.临时的： 使用export命令声明即可，变量在关闭 shell 时失效

// !! 系统级

1./etc/environment: 是系统在登录时读取的第一个文件，该文件设置的是整个系统的环境，只要启动系统就会读取该文件，用于为所有进程设置环境变量。系统使用此文件时并
不是执行此文件中的命令，而是根据而是根据 KEY=VALUE 模式的代码，对 KEY 赋值以 VALUE，因此文件中如果要定义 PATH 环境变量，只需加入一行形如 PATH=$PATH:/xxx/bin的代码即可
2. /etc/profile: 此文件是系统登录时执行的第二个文件, 为系统的每个用户设置环境信息，当用户第一次登录时，该文件被执行. 并从/etc/profile.d目录的配置文
   件中搜集shell的设置
3. /etc/bashrc: 是针对所有用户的bash初始化文件，在此中设定的环境变量将应用于所有用户的shell中，此文件会在用户每次打开shell时执行一次


// !! 用户级（这些文件处于家目录下）

1. ~/.profile: 对应当前登录用户的 profile 文件，用于定制当前用户的个人工作环境(变量是永久性)，每个用户都可使用该文件输入专用于自己使用的 shell 信息,当用户登录时,
   该文件仅仅执行一次!默认情况下,他设置一些环境变量,执行用户的.bashrc文件。这里是推荐放置个人设置的地方

2.~/.bashrc:该文件包含专用于你的 bash shell 的 bash 信息，当登录时以及每次打开新的 shell 时，该文件被读取


// !! 三、Linux 中常见的环境变量及其作用

Linux中常见的环境变量有:

1. PATH：指定命令的搜索路径
~ » echo $PATH                                                  parallels@xforg
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

2. HOME：指定用户的主工作目录（即用户登陆到Linux系统中时，默认的目录
~ » echo $HOME                                                  parallels@xforg
/home/parallels
--------------------

3.HISTSIZE：指保存历史命令记录的条数。
~ » echo $HISTSIZE                                              parallels@xforg
50000


4.LOGNAME：指当前用户的登录名
~ » echo $LOGNAME                                               parallels@xforg
parallels


5.HOSTNAME：指主机的名称，许多应用程序如果要用到主机名的话，通常是从这个环境变量中来取得的

6.SHELL：指当前用户用的是哪种 Shell
~ » echo $SHELL                                                 parallels@xforg
/bin/zsh

int main(int argc, char **argv)
{

}