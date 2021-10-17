#include <iostream>
#include <string>


using namespace std;

#define exp(s) printf("test s is:%s\n",s)
#define exp1(s) printf("test s is:%s\n",#s)
#define exp2(s) #s 

// !! 宏中包含特殊符号: #，##，\

// !! 1. 字符串化操作符（#）
// 在一个宏中的参数前面使用一个#,预处理器会把这个参数转换为一个字符数组，换言之就是：#是“字符串化”的意思，出现在宏定义中的#是把跟在后面的参数转换成一个字符串。
// 注意：其只能用于有传入参数的宏定义中，且必须置于宏定义体中的参数名前


// !! 2. 符号连接操作符（##）
// “##”是一种分隔连接方式，它的作用是先分隔，然后进行强制连接。将宏定义的多个形参转换成一个实际参数名。

// !! 3. 续行操作符（\）
// 当定义的宏不能用一行表达完整时，可以用”\”表示下一行继续此宏的定义。
#define MAX(a,b) ((a)>(b) ? (a) \
   :(b))

int main(int argc, char **argv)
{
    exp("hello");
    exp1(hello);

    string str = exp2(   bac );
    cout<<str<<" "<<str.size()<<endl;
    /**
     * 忽略传入参数名前面和后面的空格。
     */
    string str1 = exp2( asda  bac );

    /**
     * 当传入参数名间存在空格时，编译器将会自动连接各个子字符串，
     * 用每个子字符串之间以一个空格连接，忽略剩余空格。
     */
    cout<<str1<<" "<<str1.size()<<endl;
}