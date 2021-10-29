#include <iostream>

// !! shell 历史

Shell 的作用是解释执行用户的命令, 由于历史原因，UNIX 系统上有很多种 Shell

1. sh（Bourne Shell）:由 Steve Bourne 开发，各种 UNIX 系统都配有 sh
2. csh（C Shell）: 由 Bill Joy 开发，随 BSD UNIX 发布，它的流程控制语句很像C语言，支持很多 Bourne Shell 所不支持的功能：作业控制，命令历史，命令行编辑
3. bash（Bourne Again Shell）：由 GNU 开发的 Shell，主要目标是与 POSIX 标准保持一致，同时兼顾对 sh 的兼容，bash 从 csh 和 ksh 借鉴了很多功能，
   是各种 Linux 发行版标准配置的 Shell，在 Linux 系统上 /bin/sh 往往是指向 /bin/bash 的符号链接


用户在命令行输入命令后，一般情况下 Shell 会 fork 并 exec 该命令，但是 Shell 的内建命令例外，执行内建命令相当于调用 Shell 进程中的一个函数，并不创建新的进程。

// !! 执行脚本
test.sh
#! /bin/bash

Shell 脚本中用 # 表示注释，相当于 C 语言的, 但如果 # 位于第一行开头，并且是#! 则例外，它表示该脚本使用后面指定的解释器 /bin/bash 解释执行

如果把这个脚本文件加上可执行权限然后执行:

chmod +x test.sh
./test.sh


如果要执行的是一个文本文件，并且第一行用 #! 指定了解释器，则用解释器程序的代码段替换当前进程，并且从解释器的 _start 开始执行，而这个文本文件被当作命令
行参数传给解释器。

因此，执行上述脚本相当于执行程序:

/bin/sh test.sh

以这种方式执行不需要test.sh文件具有可执行权限。

// !! 基本语法

// !! 变量

有两种类型的 shell 变量:

1. 环境变量
   环境变量可以从父进程传给子进程，因此 Shell 进程的环境变量可以从当前 Shell 进程传给 fork 出来的子进程。用 printenv 命令可以显示当前 Shell 进程的环境变量
   printenv;

2. 本地变量
   只存在于当前 Shell 进程，用 set 命令可以显示当前 Shell 进程中定义的所有变量（包括本地变量和环境变量）和函数

   VARNAME="HELL BASH"//  注意等号两边都不能有空格，否则会被 Shell 解释成命令和命令行参数


// !! 一个变量定义后仅存在于当前 Shell 进程，它是本地变量，用 export 命令可以把本地变量导出为环境变量

export VARNAME="HELLO BASH"

用 unset 命令可以删除已定义的环境变量或本地变量

和 C 语言不同的是，Shell 变量不需要明确定义类型，事实上 Shell 变量的值都是字符串，比如我们定义 VAR=45，其实 VAR 的值是字符串 45 而非整数。
Shell 变量不需要先定义后使用，如果对一个没有定义的变量取值，则值为空字符串。


// !! 文件名代换（Globbing）

这些用于匹配的字符称为通配符（Wildcard）

1. * 匹配 0 个或多个任意字符
2. ? 匹配一个任意字符
3. [若干字符] 匹配方括号中任意一个字符的一次出现

ls linux*

ls linux?

ls ch[012] [0-9].doc

注意，Globbing 所匹配的文件名是由 Shell 展开的，也就是说在参数还没传给程序之前已经展开了，比如上述ls ch0[012].doc命令，如果当前目录下有 ch00.doc和ch02.doc，
则传给 ls 命令的参数实际上是这两个文件名，而不是一个匹配字符串


// !! 命令代换

由 “`” 反引号括起来的也是一条命令，Shell 先执行该命令，然后将输出结果立刻代换到当前命令行中
DATA='data'
echo $DATA

命令代换也可以用 $() 表示:

echo $(data)

// !! 算术代换

使用 $(())，用于算术计算，(()) 中的 Shell 变量取值将转换成整数
VAR=45
echo $(($VAR+3))

$(()) 中只能用 +-*/ 和 () 运算符，并且只能做整数运算。

$[base#n]，其中 base 表示进制，n 按照 base 进制解释，后面再有运算数，按十进制解释

echo $[2#10+11]
echo $[8#10+11]
echo $[16#10+11]


// !!转义字符

和 C 语言类似，\ 在 Shell 中被用作转义字符，用于去除紧跟其后的单个字符的特殊意义。换句话说，紧跟其后的字符取字面值。

echo $SHELL ----> /bin/zsh
echo $\SHELL ----> $SHELL

比如创建一个文件名为 “$ $” 的文件（$间含有空格）可以这样

touch \$\$


// !! 单引号

和 C 语言同，Shell 脚本中的单引号和双引号一样都是字符串的界定符, 而不是字符的界定符。单引号用于保持引号内所有字符的字面值，
即使引号内的 \ 和回车也不例外，但是字符串中不能出现单引号。

// !! 如果引号没有配对就输入回车，Shell 会给出续行提示符，要求用户把引号配上对。
~ » '                                                     
\ 
\ 
\ 
\ 
\ '
zsh: command not found: \n\n\n\n\n


// !! 双引号

被双引号用括住的内容，将被视为单一字串。它防止通配符扩展，但允许变量扩展。这点与单引号的处理方式不同


// !! 条件测试

命令test或 [] 可以测试一个条件是否成立，如果测试结果为真，则该命令的Exit Status为0，如果测试结果为假，则命令的Exit Status为 1

~ » i=10                                                        parallels@xforg
--------------------------------------------------------------------------------
~ » test $i -gt 11                                              parallels@xforg
--------------------------------------------------------------------------------
~ » echo $?                                                 1 ↵ parallels@xforg
1

~ » VAR=45                                                      parallels@xforg
--------------------------------------------------------------------------------
~ » [ $VAR -gt 1 ]                                              parallels@xforg
--------------------------------------------------------------------------------
~ » echo $?                                                     parallels@xforg
0


[ -d DIR ] 如果DIR存在并且是一个目录则为真

[ -f FILE ] 如果FILE存在且是一个普通文件则为真

[ -z STRING ] 如果STRING的长度为零则为真

[ -n STRING ] 如果STRING的长度非零则为真

[ STRING1 = STRING2 ] 如果两个字符串相同则为真

[ STRING1 != STRING2 ] 如果字符串不相同则为真


// !! 和 C 语言类似，测试条件之间还可以做与、或、非逻辑运算:

[ ! EXPR ] EXPR可以是上表中的任意一种测试条件，!表示“逻辑反(非)”

[ EXPR1 -a EXPR2 ] EXPR1和EXPR2可以是上表中的任意一种测试条件，-a表示“逻辑与”

[ EXPR1 -o EXPR2 ] EXPR1和EXPR2可以是上表中的任意一种测试条件，-o表示“逻辑或”


// !! 分支

if/then/elif/else/fi

“:”是一个特殊的命令，称为空命令，该命令不做任何事，但 Exit Status 总是真。

if :; then echo "always true"; fi

此外，也可以执行 /bin/true 或 /bin/false 得到真或假的 Exit Status, 再看一个例子：


echo "Is it morning? Please answer yes or no."

read YES_OR_NO

read 命令的作用是等待用户输入一行字符串，将该字符串存到一个 Shell 变量中


此外，Shell 还提供了 && 和 || 语法，和 C 语言类似，具有 Short-circuit 特性，很多 Shell 脚本喜欢写成这样

test "$(whoami)"!="root"&&(echo you are using a non-privileged account; exit 1)

&& 相当于 “if…then…”，而 || 相当于“if not…then…”

test "$VAR" -gt 1 && test "$VAR" -lt 3


// !! case/esac

case命令可类比C语言的 switch/case 语句，esac 表示 case 语句块的结束。Shell 脚本的 case 可以匹配字符串和 Wildcard，每个
匹配分支可以有若干条命令，末尾必须以;;结束。执行时找到第一个匹配的分支并执行相应的命令，然后直接跳到 esac 之后，不需要像 C 语言一样用 break 跳出


echo "Is it morning? Please answer yes or no."

read YES_OR_NO

case "$YES_OR_NO" in

yes|y|Yes|YES)

        echo "Good Morning!";;

[nN]*)

        echo "Good Afternoon!";;

*)
         echo "Sorry, $YES_OR_NO not recognized. Enter yes or no."
         exit 1;;
esac


// !! 循环 for/do/done

Shell 脚本的 for 循环结构和 C 语言很不一样，它类似于某些编程语言的 foreach 循环

for FRUIT in apple banana pear

do

      echo "I like $FRUIT"

done

FRUIT 是一个循环变量，第一次循环 $FRUIT 的取值是 apple，第二次取值是 banana，第三次取值是 pear。

要将当前目录下的 chap0、chap1、chap2 等文件名改为 chap0~、chap1~、chap2~ 等（按惯例，末尾有~字符的文件名表示临时文件），
这个命令可以这样写:

for FILENAME in `ls chap?`; do mv $FILENAME $FILENAME~; done


// !!while/do/done

while 的用法和 C 语言类似。比如一个验证密码的脚本:

echo "Enter password:"

read TRY

while [ "$TRY" != "secret" ]; do

       echo "Sorry, try again"

       read TRY

done


// !! break 和 continue

break[n] 可以指定跳出几层循环；continue 跳过本次循环，但不会跳出循环。

即 break 跳出，continue 跳过。


// !! 位置参数和特殊变量

有很多特殊变量是被 Shell 自动赋值的，我们已经遇到了 $? 和 $1。其他常用的位置参数和特殊变量在这里总结一下：

1. $0 相当于C语言main函数的 argv[0]

2. $1、$2 ... 这些称为位置参数（Positional Parameter），相当于 C 语言 main 函数的 argv[1]、argv[2]...

3. $@ 表示参数列表 "$1" "$2" ...， 例如可以用在 for 循环中的 in 后面

4. $* 表示参数列表"$1" "$2" ...，同上

5. $? 上一条命令的 Exit Status

6. $$ 当前进程号


// !! 输入输出 echo

echo ----> 显示文本行或变量，或者把字符串输入到文件。

-e 解析转义字符
-n 不回车换行。默认情况echo回显的内容后面跟一个回车换行


// !! 管道

可以通过 | 把一个命令的输出传递给另一个命令做输入


tee

tee 命令把结果输出到标准输出，另一个副本输出到相应文件

tee -a a.txt表示追加操作


// !! 文件重定向

cmd > file 把标准输出重定向到新文件中

cmd >> file 追加

cmd < &- 关闭标准输入

cmd > &fd 把文件描述符fd作为标准输出

cmd < &fd 把文件描述符fd作为标准输入


// !! 函数

和 C 语言类似，Shell 中也有函数的概念，但是函数定义中没有返回值也没有参数列表

foo(){ echo "Function foo is called";}

echo "-=start=-"

foo

echo "-=end=-"


注意函数体的左花括号 { 和后面的命令之间必须有空格或换行，如果将最后一条命令和右花括号 } 写在同一行，命令末尾必须有分号; 但不建议将函数定义写至
一行上，不利于脚本阅读。Shell 脚本中的函数必须先定义后调用，一般把函数定义语句写在脚本的前面，把函数调用和其它命令写在脚本的最后。 Shell 函数没有参数
列表并不表示不能传参数，事实上，函数就像是迷你脚本，调用函数时可以传任意个参数，在函数内同样是用 $0、$1、$2 等变量来提取参数，函数中的位置参数相当于函数的
局部变量，改变这些变量并不会影响函数外面的 $0、$1、$2 等变量。函数中可以用 return 命令返回，如果 return 后面跟一个数字则表示函数的 Exit Status。



// !! Shell 脚本调试方法

Shell 提供了一些用于调试脚本的选项，如:

1. -n 读一遍脚本中的命令但不执行，用于检查脚本中的语法错误

2. -v 一边执行脚本，一边将执行过的脚本命令打印到标准错误输出

3. -x 提供跟踪执行信息，将执行的每一条命令和结果依次打印出来


int main(int argc, char **argv)
{
   
}
