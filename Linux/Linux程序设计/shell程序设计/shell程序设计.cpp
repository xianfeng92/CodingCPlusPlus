// !! shell 程序设计

在其他的一些操作系统中，命令行界面只是对图形化界面的一个补充。但对于 Linux 而言，去并非如此。作为 Linux 灵感来源的 UNIX 系统最初根本就没
有图形化界面，所有的任务都是通过命令行来完成的。因此，UNIX 的命令行系统得到了很大的发展，并且成为一个功能强大的系统。Linux 系统沿袭了这一特
点，许多强大的功能都可以从 shell 中轻松实现。'shell 对 Linux 是如此的重要，并且对自动化简单的任务非常有用'。


// !! 为什么使用 shell 编程

'使用 shell 进行程序设计的原因之一是，你可以快速、简单地完成编程'。而且，即使是最基本的 Linux 安装也会提供一个shell。

shell 也非常适合于编写一些执行相对简单的任务的小工具，因为它们更强调的是易于配置、易于维护和可移植性，而不是很看重执行的效率。

虽然 shell 表面上和 Windows 的命令提示符相似，但是它具备更强大的功能以完成相当复杂的程序。你不仅可以通过它执行命令、调用 Linux 工具，还可以自
己编写程序。


// !! 一点哲学

现在，我们来关注一点 UNIX（当然也是 Linux）的哲学。'UNIX 架构非常依赖于代码的高度可重用性'。'如果你编写了一个小巧而简单的工具，其他人就可以将它作
为一根链条上的某个环节来构成一条命令'。

Linux 让用户满意的原因之一就是它提供了各种各样的优秀工具。下面是一个简单的例子：

 » ls -al|more

总用量 80
drwxrwxr-x 2 parallels parallels  4096 Dec 11 21:41 .
drwxrwxr-x 4 parallels parallels  4096 Dec 11 20:01 ..
-rw-rw-r-- 1 parallels parallels   102 Dec 11 21:30 bill.c
-rw-rw-r-- 1 parallels parallels  1712 Dec 11 21:29 bill.o
-rw-rw-r-- 1 parallels parallels    99 Dec 11 21:30 fred.c
-rw-rw-r-- 1 parallels parallels  1704 Dec 11 21:29 fred.o
-rw-rw-r-- 1 parallels parallels  3626 Dec 11 21:37 libfoo.a
-rw-rw-r-- 1 parallels parallels    41 Dec 11 21:29 lib.h
-rwxrwxr-x 1 parallels parallels 16760 Dec 11 21:41 program
-rw-rw-r-- 1 parallels parallels    89 Dec 11 21:31 program.c
-rw-rw-r-- 1 parallels parallels  1688 Dec 11 21:33 program.o
-rw-rw-r-- 1 parallels parallels 19579 Dec 11 21:57 UNIX、Linux和GNU简介.cpp

这个命令使用了 ls 和 more 工具并通过管道实现了文件列表的分屏显示。'每个工具就是一个组成部件, 通常你可以将许多小巧的脚本程序组合起来以创建一个庞大而
复杂的程序'。

例如，如果你想打印 bash 使用手册的参考副本，可以使用如下命令：

» man bash|col -b|lpr

此外，因为 Linux 具备自动文件类型处理功能，所以使用这些工具的用户一般不必了解它们是用哪种语言编写的。

如果想要这些工具运行得更快，常见的做法是首先在 shell 中实现工具的原型，一旦确定值得这么做，然后再用 C 或 C++、Perl、Python 或者其他执行得更快速的
语言来重新实现它们。相反，如果在 shell 中这些工具工作得已足够好，就不必再重新实现它们。


// !! 什么是 shell

'shell 是一个作为用户与 Linux 系统间接口的程序，它允许用户向操作系统输入需要执行的命令'。

例如，我们可以使用 < 和 > 对输入输出进行重定向，使用|在同时执行的程序之间实现数据的管道传递，使用 $(...) 获取子进程的输出。
在 Linux 中安装多个 shell 是完全可行的，用户可以挑选一种自己喜欢的 shell 来使用。


在Linux系统中，总是作为 /bin/sh 安装的标准 shell 是 GNU 工具集中的 bash（GNU Bourne-Again Shell）。因为它作为一个优秀的 shell，总是安装在 
Linux 系统上，而且它是开源的并且可以被移植到几乎所有的类 UNIX 系统上。在大多数 Linux 发行版中，默认的 shell 程序 /bin/sh 实际上是对程序 /bin/bash 
的一个连接。你可以使用如下命令来查看bash的版本号：

 » /bin/bash --version          
                                                                 
GNU bash，版本 5.0.17(1)-release (x86_64-pc-linux-gnu)
Copyright (C) 2019 Free Software Foundation, Inc.
许可证 GPLv3+: GNU GPL 许可证第三版或者更新版本 <http://gnu.org/licenses/gpl.html>

本软件是自由软件，您可以自由地更改和重新发布。
在法律许可的情况下特此明示，本软件不提供任何担保。



// !! 管道和重定向


1. 重定向输出

读者可能已经对某些类型的重定向比较熟悉了, 例如:

» ls -l > lsoutput.txt 

这条命令把 ls 命令的输出保存到文件 lsoutput.txt 中。

现在你只需知道文件描述符 0 代表一个程序的标准输入，文件描述符 1 代表标准输出，而文件描述符 2 代表标准错误输出。'你可以单独地重定向其中任何一个'。

上面的例子通过 > 操作符把标准输出重定向到一个文件。在默认情况下，如果该文件已经存在，它的内容将被覆盖。如果你想改变默认行为，你可以使用命令 
set –o noclobber 命令设置 noclobber 选项，从而阻止重定向操作对一个已有文件的覆盖。你可以使用 set +o noclobber 命令取消该选项。

你可以用 >> 操作符将输出内容附加到一个文件中。例如:

» cat lsoutput.txt                                                                                 
总用量 72
-rw-rw-r-- 1 parallels parallels   102 Dec 11 21:30 bill.c
-rw-rw-r-- 1 parallels parallels  1712 Dec 11 21:29 bill.o
-rw-rw-r-- 1 parallels parallels    99 Dec 11 21:30 fred.c
-rw-rw-r-- 1 parallels parallels  1704 Dec 11 21:29 fred.o
-rw-rw-r-- 1 parallels parallels  3626 Dec 11 21:37 libfoo.a
-rw-rw-r-- 1 parallels parallels    41 Dec 11 21:29 lib.h
-rw-rw-r-- 1 parallels parallels     0 Dec 11 22:20 lsoutput.txt
-rwxrwxr-x 1 parallels parallels 16760 Dec 11 21:41 program
-rw-rw-r-- 1 parallels parallels    89 Dec 11 21:31 program.c
-rw-rw-r-- 1 parallels parallels  1688 Dec 11 21:33 program.o
-rw-rw-r-- 1 parallels parallels 19579 Dec 11 21:57 UNIX、Linux和GNU简介.cpp
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 » ps >> lsoutput.txt                                                                               
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 » cat lsoutput.txt                                                                                  
总用量 72
-rw-rw-r-- 1 parallels parallels   102 Dec 11 21:30 bill.c
-rw-rw-r-- 1 parallels parallels  1712 Dec 11 21:29 bill.o
-rw-rw-r-- 1 parallels parallels    99 Dec 11 21:30 fred.c
-rw-rw-r-- 1 parallels parallels  1704 Dec 11 21:29 fred.o
-rw-rw-r-- 1 parallels parallels  3626 Dec 11 21:37 libfoo.a
-rw-rw-r-- 1 parallels parallels    41 Dec 11 21:29 lib.h
-rw-rw-r-- 1 parallels parallels     0 Dec 11 22:20 lsoutput.txt
-rwxrwxr-x 1 parallels parallels 16760 Dec 11 21:41 program
-rw-rw-r-- 1 parallels parallels    89 Dec 11 21:31 program.c
-rw-rw-r-- 1 parallels parallels  1688 Dec 11 21:33 program.o
-rw-rw-r-- 1 parallels parallels 19579 Dec 11 21:57 UNIX、Linux和GNU简介.cpp
    PID TTY          TIME CMD
1595416 pts/0    00:00:03 zsh
1608599 pts/0    00:00:00 man
1608608 pts/0    00:00:00 man
1608609 pts/0    00:00:00 less
1609107 pts/0    00:00:00 info
1618464 pts/0    00:00:00 ps

这条命令会将 ps 命令的输出附加到指定文件的尾部。


'如果想对标准错误输出进行重定向，你需要把想要重定向的文件描述符编号加在 > 操作符的前面'。因为标准错误输出的文件描述符编号是 2，所以使用 2> 
操作符。'当需要丢弃错误信息并阻止它显示在屏幕上时，这个方法很有用'。

下面的命令将把标准输出和标准错误输出分别重定向到不同的文件中:

kill -HUP 1234 >killout.txt 2>killerr.txt

如果你想把两组输出都重定向到一个文件中，'你可以用 >& 操作符来结合两个输出'。如下所示:

kill -1 1234 >killouterr.txt 2>&1

这条命令将把标准输出和标准错误输出都重定向到同一个文件中。请注意操作符出现的顺序。这条命令的含义是“将标准输出重定向到文件 killouterr.txt，然后
将标准错误输出重定向到与标准输出相同的地方。


你可以用 Linux 的通用 “回收站” /dev/null 来有效地丢弃所有的输出信息，如下所示:

kill -1 1234 >/dev/null 2>&1


// !! 重定向输入

你不仅可以重定向标准输出，还可以重定向标准输入。例如：

$ more < killout.txt


// !! 管道

'你可以用管道操作符|来连接进程'。

'在 Linux 下通过管道连接的进程可以同时运行，并且随着数据流在它们之间的传递可以自动地进行协调'。

举一个简单的例子，你可以使用 sort 命令对 ps 命令的输出进行排序。

不使用管道，你就必须分几个步骤来完成这个任务，如下所示：

$ ps > psout.txt
$ sort psout.txt > pssort.out

一个更精巧的解决方案是用管道来连接进程，如下所示：

» ps | sort 

1595416 pts/0    00:00:03 zsh
1608599 pts/0    00:00:00 man
1608608 pts/0    00:00:00 man
1608609 pts/0    00:00:00 less
1609107 pts/0    00:00:00 info
1623361 pts/0    00:00:00 ps
1623362 pts/0    00:00:00 sort
    PID TTY          TIME CMD

如果想在屏幕上分页显示输出结果，你可以再连接第三个进程 more，将它们都放在同一个命令行上，如下所示：

» ps | sort | more

允许连接的进程数目是没有限制的。


// !! 作为程序设计语言的 shell

1.交互式程序

'命令行上直接输入 shell 脚本是一种测试短小代码段的简单而快捷的方式'。如果你正在学习 shell 脚本或仅仅是为了进行测试，使用这种方式
是非常有用的。

假设你想要从大量 C 语言源文件中查找包含字符串 POSIX 的文件。与其使用 grep 命令在每个文件中搜索字符串，然后再分别列出包含该字符串的文件，
不如用下面的交互式脚本来执行整个操作:


for file in *
> do
> if grep -l POSIX $file
> then
> more $file
> fi
> done
posix
This is a file with POSIX in it - treat it well
$

如果每次想要执行一系列命令时，你都要经过这么一个冗长的输入过程，将非常令人烦恼。你需要将这些命令保存到一个文件中，即我们常说的 shell 脚本，
这样你就可以在需要的时候随时执行它们了。



2. 创建脚本

首先，你必须用一个文本编辑器来创建一个包含命令的文件，将其命名为 first，它的内容如下所示：

#!/bin/sh
# first
# This file looks through all the files in the current
# directory for the string POSIX, and then prints the names of
# those files to the standard output.

for file in *
do
  if grep -q POSIX $file
  then
    echo $file
  fi
done
exit 0


程序中的注释以 # 符号开始，一直持续到该行的结束。按照惯例，我们通常把 # 放在第一列。在作出这样一个笼统的陈述之后，请注意第一行 #!/bin/sh，它是一
种特殊形式的注释，'#! 字符告诉系统同一行上紧跟在它后面的那个参数是用来执行本文件的程序'。在这个例子中，/bin/sh 是默认的 shell 程序。

'因为脚本程序本质上被看作是 shell 的标准输入，所以它可以包含任何能够通过你的 PATH 环境变量引用到的 Linux 命令'。

exit 命令的作用是确保脚本程序能够返回一个有意义的退出码。当程序以交互方式运行时，我们很少需要检查它的退出码，但如果你打算从另一个脚本程序里调用这个
脚本程序并查看它是否执行成功，那么返回一个适当的退出码就很重要了。

在 shell 程序设计里，0 表示成功。因为这个脚本程序并不能检查到任何错误，所以它总是返回一个表示成功的退出码。

请注意，这个脚本没有使用任何的文件扩展名或后缀。'一般情况下，Linux 和 UNIX 很少利用文件扩展名来决定文件的类型'。

你可以为脚本使用 .sh 或者其他扩展名，但 shell 并不关心这一点。大多数预安装的脚本程序并没有使用任何文件扩展名，'检查这些文件是否是脚本程
序的最好方法是使用 file 命令'，例如，file first 或 file /bin/bash。

» file first.sh

first.sh: POSIX shell script, ASCII text executable


// !!把脚本设置为可执行


现在你已经有了自己的脚本文件，运行它有两种方法。比较简单的方法是调用 shell，并把脚本文件名当成一个参数，如下所示:

 » /bin/bash first.sh                                                                      
first.sh
shell程序设计.cpp
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 » ./first.sh                                                                               
zsh: 权限不够: ./first.sh

 » chmod 777 first.sh                                                                
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 » ./first.sh                                                                               
first.sh
shell程序设计.cpp

用 ./ 来指定路径还有另一个好处，它能够保证你不会意外执行系统中与你的脚本文件同名的另一个命令。

在确信你的脚本程序能够正确执行后，你可以把它从当前目录移到一个更合适的地方去。如果这个命令只供你本人使用，你可以在自己的家目录中创建一个 bin 目录，并且将
该目录添加到你自己的 PATH 变量中。

如果你想让其他人也能够执行这个脚本程序，你可以将 /usr/local/bin 或其他系统目录作为添加新程序的适当位置。

系统管理员用来设置文件属主和访问权限的一系列命令如下所示:

# cp first /usr/local/bin
# chown root /usr/local/bin/first
# chgrp root /usr/local/bin/first
# chmod 755 /usr/local/bin/first

注意，你在这里不是修改访问权限标志的特定部分，而是使用 chmod 命令的绝对格式，因为你清楚地知道你需要的访问权限。


在 Linux 系统中，如果你拥有包含某个文件的目录的写权限，就可以删除这个文件。'为安全起见，应该确保只有超级用户才能对你想保证文件安全的目录执行写操作'。
因为目录只是另一种类型的文件，所以拥有对一个目录文件写权限的用户可以添加和删除目录文件中的名称。


// !! shell 的语法





































