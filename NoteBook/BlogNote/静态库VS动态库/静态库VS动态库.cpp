// !! 静态库VS动态库

在编程的过程中,使用已经封装好的库函数是十分方便的,也是十分高效的,因此会使用函数库是很重要的。在 C 语言中, 函数库文件分为两种类型,'一种是静态库(库程
序是直接注入目标程序的,不分彼此,库文件通常以.a 结尾)'; '另一种是动态库(库程序是在运行目标程序时(中)加载的,库文件通常以 .so 结尾)'。

下面我们就探索一下这两种库文件的特点和使用方式吧！

// !! 背景知识

'预编译'

预编译是使用预编译器 cpp 进行处理 .cpp 源文件和 .h 头文件, 最终生成一个 .i 的文件。'预编译过程就是处理源代码中以 # 开头的预编译指令',如 #include  
#define 等。预编译过程等价于如下命令:

gcc -E hello.cpp -o hello.i
或则   
cpp hello.cpp > hello.i 

#include 就是将包含的头文件全部展开到 #include 的位置, 所以一个 .cpp 源文件如果包含多个头文件, 头文件的顺序是需要注意的地方。


'编译'

'编译的过程就是将 预处理 完的文件进行一系列的词法分析、语法分析、语义分析及优化, 最后生成 .s 汇编代码文件'。

编译过程等价如下命令:

gcc -S hello.i -o hello.s  

'编译过程是整个程序构建的核心部分, 也是最复杂的部分之一'。


'汇编'

'汇编器是将汇编代码转变成机器可以执行的指令',每一条汇编代码几乎都对应着一条机器指令。最后生成一个 .o 目标文件。

汇编过程等价如下命令:

gcc -c hello.s -o hello.o   

或者

as hello.s -o hello.o

汇编器的汇编过程相对简单一些, 只需要根据汇编指令和机器指令对照表一一翻译就可以了。


'链接'

'链接的作用就是将我们编译出来的目标文件和我们代码所用到的库文件一起打包成一个可执行文件的过程'。例如 hello.cpp 中的打印函数 printf 这个函数不是凭空出
现的, 在链接的过程中就要连同对应库文件一起打包, 最终可执行文件才能正常运行。

// !! 静态库VS动态库

'静态库和动态库的载入时间是不一样的'

1. 静态库的代码在编译的过程中已经载入到可执行文件中, 所以最后生成的可执行文件相对较大

2. 动态库的代码在可执行程序运行时才载入内存, 在编译过程中仅简单的引用, 所以最后生成的可执行文件相对较小

静态库和动态库的最大区别是: 静态库链接的时候把库直接加载到程序中, 而动态库链接的时候, 它只是保留接口, 将动态库与程序代码独立, 这样就可以提高代码的可复用
度和降低程序的耦合度。

1. 静态库在程序编译时会被连接到目标代码中, 程序运行时将不再需要该静态库

2. 动态库在程序编译时并不会被连接到目标代码中, 而是在程序运行是才被载入, 因此在程序运行时还需要动态库存在

'无论静态库, 还是动态库, 都是由 .o 文件创建的。因此, 我们必须将源程序 hello.cpp 通过 gcc 先编译成 .o 文件'。

// !! 静态库


静态库的名字一般是 libxxx.a 在编译的时候直接编译进可执行文件中,运行环境中可以不用存在库文件,但是如果库文件更新了,可执行文件需要重新编译。

'操作静态库'

Linux 下使用 ar 命令进行操作静态库:

ar  archivefile  objfile

objfile:      objfile 是已 .o 为扩展名的中间目标文件名, 可以多个并列

参数        意义

-r            将objfile文件插入静态库尾或者替换静态库中同名文件

-x            从静态库文件中抽取文件objfile

-t            打印静态库的成员文件列表

-d            从静态库中删除文件objfile

-s            重置静态库文件索引

-v            创建文件冗余信息

-c            创建静态库文件


// !! 编译静态库

在编译成静态库之前, 我们需要将源文件编译一下, 生成一个 .o 文件的目标文件。例如写了一个打印 helloworld 的接口, 我们要先执行:

g++ -c hello.cpp
ar crv libhello.a hello.o

第一条命令是生成目标文件 hello.o , 第二条命令是将目标文件 hello.o 打包成静态库文件 libhello.a。

// !! 链接静态库

上面我们说了静态库是如何生成的, 然后我们说一下静态库怎么使用。'静态库是要编译进可执行文件的,在程序运行的环境中,并不需要静态库的存在'。比如我们生成的静态
库文件是 libhello.a 需要编译的文件是 main.c。编译命令如下:

gcc main.c -L . -lhello

-L 后面是静态库文件所在的目录，我这里 . 就是指当前目录的意思。也就是库文件就和源文件在同一路径。真正编译的时候, 这个路径还是要填绝对路径要好,这个需要注
意一下。后面的 -l 加上库名, 这个库名是去掉 lib 和后面的 .a, 静态库的链接就是这样的。

// !! 动态库

动态库中的代码是可执行文件在运行中加载执行的, 也就是说'程序运行环境中要有动态库文件'。一般动态库文件命名为 lib***.so。动态库的优点就是方便升级,动态库
变化了,可执行文件不用重新编译。


// !! 编译动态库

还拿 hello.cpp 来说, 使用下面的命令就可以生成一个动态库文件 libhello.so 

g++ -fPIC -shared -o libhello.so hello.cpp

-fPIC 是创建与地址无关的编译程序(pic, position independent code), 是为了能够在多个应用程序间共享。-shared 指定生成动态链接库。


// !! 调用动态库态库

我们在运行环境中直接运行可执行文件, 前提动态库文件也在运行环境中。'需要注意的是系统在运行程序的时候,需要知道动态库的名称和位置，这样才能加载'，如果找不
到动态库就会直接程序退出报错。

所以在编译程序的时候使用下面方式编译:

g++ main.cpp -o main -L ./ -lhello

同样, '-L 后面是库文件的路径, 最好是用绝对路径'。-l 加上去掉 lib 的库名。然后直接执行可执行文件就可以了。


'使用下面的命令来获知系统的 include 默认搜索路径':

 » g++ -print-prog-name=cc1 -v

Using built-in specs.
COLLECT_GCC=g++
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/9/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none:hsa
OFFLOAD_TARGET_DEFAULT=1
/usr/lib/gcc/x86_64-linux-gnu/9/cc1

'获知库默认搜索路径':

 » g++ -print-search-dirs  

install: /usr/lib/gcc/x86_64-linux-gnu/9/
programs: =/usr/lib/gcc/x86_64-linux-gnu/9/:/usr/lib/gcc/x86_64-linux-gnu/9/:/usr/lib/gcc/x86_64-linux-gnu/:
/usr/lib/gcc/x86_64-linux-gnu/9/:/usr/lib/gcc/x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/9/../../../../x86_64-linux-gnu/bin/x86_64-linux-gnu/9/:
/usr/lib/gcc/x86_64-linux-gnu/9/../../../../x86_64-linux-gnu/bin/x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/9/../../../../x86_64-linux-gnu/bin/
libraries: =/usr/lib/gcc/x86_64-linux-gnu/9/:/usr/lib/gcc/x86_64-linux-gnu/9/../../../../x86_64-linux-gnu/lib/x86_64-linux-gnu/9/:
/usr/lib/gcc/x86_64-linux-gnu/9/../../../../x86_64-linux-gnu/lib/x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/9/../../../../x86_64-linux-gnu/lib/../lib/:
/usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/9/:/usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/9/../../../../lib/:
/lib/x86_64-linux-gnu/9/:/lib/x86_64-linux-gnu/:/lib/../lib/:/usr/lib/x86_64-linux-gnu/9/:/usr/lib/x86_64-linux-gnu/:/usr/lib/../lib/:
/usr/lib/gcc/x86_64-linux-gnu/9/../../../../x86_64-linux-gnu/lib/:
/usr/lib/gcc/x86_64-linux-gnu/9/../../../:/lib/:/usr/lib/


执行程序后出现这样的错误情况：

>> ./main
./main: error while loading shared libraries: libhello.so: cannot open shared object file: No such file or directory

'这是因为执行程序的时候, 系统不知道 libhello.so 的位置，系统无法找到库文件'。尽管我们用 G++ 编译的时候，通过 -L 选项提供了 libhello.so 文件的位置
, 但是这个信息没有被写入到可执行程序里面。

下面用命令 ldd 命令来查看一下 main 所依赖的库文件(ldd 命令是用于显示可执行文件所依赖的库):

» ldd main                parallels@xforg
	linux-vdso.so.1 (0x00007ffce28fc000)
	libhello.so => not found
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f78f1fb6000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f78f21d0000)


可以看出可执行文件 main 无法找到 libhello.so 库文件。

// !! '解决办法有 4 个':

1. 将 libhello.so 放到 G++ 默认搜索目录。比如 /usr/lib/x86_64-linux-gnu 或者 /lib/x86_64-linux-gnu 都可以，这样做简单粗暴。但是这样做需要
   root 权限来完成。而且把第三方库文件直接放到系统库文件目录里, 感觉污染了整个系统。

2. 在 /etc/ld.so.conf.d 目录下新建一个 .conf 文件。比如 mylib.conf ，在里面添加第三方库目录的绝对路径（比如 libhello.so 所在目录的绝对路径）

3. 设置 LD_LIBRARY_PATH 环境变量。比如 export LD_LIBRARY_PATH=. (.代表当前目录）。当设置这个环境变量后，操作系统将在 LD_LIBRARY_PATH 下搜索
   库文件，再到默认路径中搜索文件。但是一旦退出 Terminal, 所设置的 LD_LIBRARY_PATH 环境变量就会消失。如果需要永久添加变量,需要将 
   export LD_LIBRARY_PATH=/xxx/xxx:$LD_LIBRARY_PATH 写入到 ~/.bashrc 里面, 其中 /xxx/xxx 是库文件所在目录的绝对路径。

4. 编译的时候添加 -Wl,-rpath 选项。比如 g++ -o test test.c -l myfunc -L . -Wl,-rpath=. 。 -Wl 选项告诉编译器将后面的参数传递给链接器














