#include <iostream>


// !! 什么是 Shell ？

shell 是外壳的意思，就是操作系统的外壳。我们可以通过 shell 命令来操作和控制操作系统，比如 Linux 中的 Shell 命令就包括 ls、cd、pwd 等等

总结来说，Shell 是一个命令解释器，它通过接受用户输入的 Shell 命令来启动、暂停、停止程序的运行或对计算机进行控制。

shell 是一个应用程序，它连接了用户和 Linux 内核，让用户能够更加高效、安全、低成本地使用 Linux 内核，这就是 Shell 的本质。

shell 本身并不是内核的一部分，它只是站在内核的基础上编写的一个应用程序。


// !! 那么什么是 shell 脚本呢 ？

shell 脚本就是由 Shell 命令组成的执行文件，将一些命令整合到一个文件中，进行处理业务逻辑，脚本不用编译即可运行。它通过解释器解释运行，所以速度相对来说比较慢。

// !! shell 脚本中最重要的就是对 shell 命令的使用与组合，再使用 shell 脚本支持的一些语言特性，完成想要的功能。


// !! 变量

运行 shell 时，会同时存在三种变量:

1. 局部变量：局部变量在脚本或命令中定义，仅在当前shell实例中有效，其他shell启动的程序不能访问局部变量。

2. 环境变量：所有的程序，包括shell启动的程序，都能访问环境变量，有些程序需要环境变量来保证其正常运行。必要的时候shell脚本也可以定义环境变量。

3. shell变量：shell变量是由shell程序设置的特殊变量。shell变量中有一部分是环境变量，有一部分是局部变量，这些变量保证了shell的正常运行


// !! 变量操作

1. 创建普通变量： name="test" （=两边不可有空格）

2. 创建只可函数体中使用的局部变量： local name="test" 

3. 使用变量：echo $name 或者 echo ${name} （推荐使用大括号版）

4. 变量重新赋值：name="new_test" （将原值覆盖）

5. 只读变量：name="only_read" -> readonly name （使用 readonly 标识后的变量，不可被修改）

6. 删除变量：unset name; （删除之后不可访问，删除不掉只读变量）


// !! 字符串变量

1）单引号

单引号变量 var='test' ，只能原样输出，变量无效; 单引号中不能出现一个单独的单引号，转义也不可以

2）双引号

双引号变量var="my name is ${name}"，变量有效; 可出现转义符


3）拼接字符串

中间无任何 +，之类的字符

name="this is"" my name"; name="this is my name"; name="this" is "my name" 等效
name='this is'' my nam'; name='this is my name'; name='this' is 'my name' 等效

4）获取字符串长度

在${}中使用“#”获取长度
name="test";
echo ${#name}; # 输出为 4


5）提取子字符串

1:4 从第2个开始 往后截取4个字符
::4 从第一个字符开始 往后截取4个字符

name="this is my name";

echo ${name:1:4} #输出 is i

echo ${name::4} #输出 this


// !! 数组

bash 只支持一维数组，不支持多维数组

1. 定义数组：array_name=(i am good boy) （小括号做边界、使用空格分离）

2. 单独定义数组的元素：array_para[0]="w"; array_para[3]="s" （定义时下标不连续也可以）

3. 赋值数组元素：array_name[0]="ko";

4. 获取数组元素：

array_name[0]="Taylor"
array_name[3]="Swift"
echo ${array_name[0]} # 输出"Taylor"
echo ${array_name[1]} # 输出" "
echo ${array_name[3]} # 输出"Swift"
echo ${array_name[@]} # 输出"Taylor Swift" 输出数组所有元素，没有元素的下标省略

5. 取得元素个数：${#array_name[@]} 或者 ${#array_name}

6. 取得单个元素长度：${#array_name[1]}


// !! 参数传递

获取参数值:

$0 ： 固定，代表执行的文件名
$1 ： 代表传入的第1个参数
$n ： 代表传入的第n个参数

$$：脚本运行的当前进程号
$#：参数个数
$?： 显示最后命令的退出状态。0表示没有错误，其他任何值表明有错误。


// !! 运算符

+ 、-、*、\ : 乘号前必须加\进行转义才可以进行乘法运算


int main(int argc, char **argv)
{

}
