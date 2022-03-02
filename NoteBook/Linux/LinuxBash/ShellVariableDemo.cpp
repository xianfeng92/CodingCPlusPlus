#include <iostream>


// !! Linux 中常见的环境变量及其作用


// !! 一、环境变量文件介绍

Linux 中环境变量包括系统级和用户级，系统级的环境变量是每个登录到系统的用户都要读取的系统变量，而用户级的环境变量则是该用户使用
系统时加载的环境变量，所以管理环境变量的文件也分为系统级和用户级的。

// !! 系统级环境变量：每一个登录到系统的用户都能够读取到系统级的环境变量

// !! 用户级环境变量：每一个登录到系统的用户只能够读取属于自己的用户级的环境变量


// !! 二、Linux 的变量种类

按变量的生存周期来划分，Linux 变量可分为两类:

1.永久的： 需要修改配置文件，变量永久生效

2.临时的： 使用export命令声明即可，变量在关闭 shell 时失效

// !! 系统级

1. /etc/profile

   在系统启动后第一个用户登录时运行，并从 /etc/profile.d 目录的配置文件中搜集 shell 的设置，使用该文件配置的环境变量将应用于登录到系统的每一个用户

/etc/profile.d » ls                                             parallels@xforg
01-locale-fix.sh    cedilla-portuguese.sh  vte.csh
apps-bin-path.sh    im-config_wayland.sh   xdg_dirs_desktop_session.sh
bash_completion.sh  vte-2.91.sh

提示：在 Linux 系统中，使用以下命令可以使配置文件立刻生效
source /etc/profile
echo $PATH

2. /etc/bashrc（ Ubuntu 和 Debian 中是 /etc/bash.bashrc）

在 bash shell 打开时运行，修改该文件配置的环境变量将会影响所有用户使用的 bash shell

这里的 bash shell 有不同的类别，不同的类别所使用的环境变量配置文件也有所不同。一般情况下，非登录 shell 不会执行任何 profile 文件，非交互 shell 
模式不会执行任何 bashrc 文件

// !! 登录 shell 和非登陆 shell
登录 shell //  需要输入用户密码，例如 ssh 登录或者 su - 命令提权都会启动 login shell 模式

非登陆shell // 无需输入用户密码；
 
// !! 交互 shell 和非交互 shell
交互shell // 提供命令提示符等待用户输入命令的是交互 shell 模式

非交互shell // 直接运行脚本文件是非交互 shell 模式


// !! /etc/environment

在系统启动时运行，用于配置与系统运行相关但与用户无关的环境变量，修改该文件配置的环境变量将影响全局。


// !! 用户级（这些文件处于家目录下）

1. ~/.profile: 对应当前登录用户的 profile 文件，用于定制当前用户的个人工作环境(变量是永久性)，每个用户都可使用该文件输入专用于自己使用的 shell 信息,当用户登录时,
   该文件仅仅执行一次。默认情况下,它设置一些环境变量,执行用户的.bashrc文件。这里是推荐放置个人设置的地方

2.~/.bashrc:该文件包含专用于你的 bash shell 的 bash 信息，当登录时以及每次打开新的 shell 时，该文件被读取。不推荐在这里配置用户专用的环境变量，因为每开一个shell，
  该文件都会被读取一次，效率肯定受影响。


// !! ~/.bash_profile 或 ~./bash_login

~/.bash_profile or ~./bash_login - If one of these file exist, bash executes it rather then "~/.profile" 
when it is started as a login shell. (Bash will prefer "~/.bash_profile" to "~/.bash_login"). 
However, these files won't influence a graphical session by default.


// !!~/.bash_logout

当每次退出系统(退出bash shell)时执行该文件。

~ » subl ~/.bash                                                parallels@xforg
.bash_history  .bash_logout   .bashrc      

Linux 系统使用 $VARIABLE_NAME 访问环境变量，多个环境变量之间使用 : 分隔。

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