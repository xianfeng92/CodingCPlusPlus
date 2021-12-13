// !! Linux 文件结构

与 UNIX 一样，Linux 环境中的文件具有特别重要的意义，因为它们为操作系统服务和设备提供了一个简单而一致的接口。在 Linux 中，一切（或几乎
一切）都是文件。目录也是文件，但它是一种特殊类型的文件。

// !! 目录

文件，除了本身包含的内容以外，它还会有一个名字和一些属性，即 "管理信息"，包括文件的创建／修改日期和它的访问权限。这些属性被保
存在文件的 "inode(节点)" 中，'它是文件系统中的一个特殊的数据块', 它同时还包含文件的长度和文件在磁盘上的存放位置。

系统使用的是文件的 inode 编号, 目录结构为文件命名仅仅是为了便于人们使用。

'目录是用于保存其他文件的节点号和名字的文件'。目录文件中的每个数据项都是指向某个文件节点的链接，删除文件名就等于删除与之对应的链接。

'删除一个文件时，实质上是删除了该文件对应的目录项'，同时指向该文件的链接数减 1。该文件中的数据可能仍然能够通过其他指向同一文件的链接
访问到。如果指向某个文件的链接数（即 ls -l 命令的输出中跟在访问权限后面的那个数字）变为零，就表示该节点以及其指向的数据不再被使用，
磁盘上的相应位置就会被标记为可用空间。

文件被安排在目录中, 目录中可能还包含子目录。这些构成了我们所熟悉的文件系统层次结构。


注意，许多 UNIX 和 Linux 的 shell 都允许用户通过波浪线符号（~）直接进入自己的家目录。


/home 目录本身又是根目录 / 的一个子目录，'根目录位于目录层次的最顶端'，它在它的各级子目录中包含着系统中的所有文件。

根目录中通常包含用于存放系统程序（二进制可执行文件）的 /bin 子目录、用于存放系统配置文件的 /etc 子目录和用于存放系统函数库的 /lib
子目录。'代表物理设备并为这些设备提供接口的文件按照惯例会被放在 /dev 子目录中'。


// !! 文件和设备

甚至硬件设备在 Linux 中通常也被表示（映射）为文件。

UNIX 和 Linux 中比较重要的设备文件有 3 个: /dev/console、/dev/tty 和 /dev/null。

1. /dev/console

这个设备代表的是系统控制台。错误信息和诊断信息通常会被发送到这个设备。每个 UNIX 系统都会有一个指定的终端或显示屏用来接收控制台消息。过去，它可
能是一台专用的打印终端。在现代的工作站和 Linux 上，它通常是“活跃”的虚拟控制台；

2. /dev/tty

如果一个进程有控制终端的话, 那么特殊文件 /dev/tty 就是这个控制终端（键盘和显示屏，或键盘和窗口）的别名（逻辑设备）。例如，由系统自动运行的进程
和脚本就没有控制终端，所以它们不能打开 /dev/tty 

在能够使用该设备文件的情况下，/dev/tty 允许程序直接向用户输出信息，而不管管用户具体使用的是哪种类型的伪终端或硬件终端。

3. /dev/null

dev/null 文件是空(null)设备。所有写向这个设备的输出都将被丢弃，而读这个设备会立刻返回一个文件尾标志，所以在 cp 命令里可以把它用做复制空文件的
源文件。人们常把不需要的输出重定向到 /dev/null 。


// !! 系统调用和设备驱动程序

你只需用很少量的函数就可以对文件和设备进行访问和控制。这些函数被称为系统调用，由 UNIX (和 Linux)直接提供，它们也是通向操作系统本身的接口。

'操作系统的核心部分，即内核，是一组设备驱动程序'。它们是一组对系统硬件进行控制的底层接口。

为了向用户提供一个一致的接口，设备驱动程序封装了所有与硬件相关的特性。硬件的特有功能通常可通过 ioctl (用于I/O控制)系统调用来提供。

/dev 目录中的设备文件的用法都是相同的，它们都可以被打开、读、写和关闭。例如，用来访问普通文件的 open 调用同样可以用来访问用户终端、打印机或
磁带机。

下面是用于访问设备驱动程序的底层函数(系统调用)。

1. open：打开文件或设备

2. read：从打开的文件或设备里读数据

3. write：向文件或设备写数据

4. close：关闭文件或设备

5. ioctl：把控制信息传递给设备驱动程序


'系统调用 ioctl 用于提供一些与特定硬件设备有关的必要控制'(与正常的输入输出相反)，所以它的用法随设备的不同而不同。例如，ioctl 调用可以用于回绕磁带
机或设置串行口的流控特性。因此，ioctl 并不需要具备可移植性。'此外，每个驱动程序都定义了它自己的一组 ioctl 命令'。

提供系统调用参数列表和返回类型的函数原型及相关的 #define 常量都由 include 文件提供。每个系统调用独有的要求可参见各个系统调用的说明。


// !! 库函数

'针对输入输出操作直接使用底层系统调用的一个问题是它们的效率非常低'。

为什么呢？

1. 使用系统调用会影响系统的性能。与函数调用相比，系统调用的开销要大些，因为在执行系统调用时，Linux 必须从运行用户代码切换到执行内核代码，然后再返回
   用户代码。减少这种开销的一个好方法是，在程序中尽量减少系统调用的次数，并且让每次系统调用完成尽可能多的工作。例如，每次读写大量的数据而不是每次仅读
   写一个字符

2. 硬件会限制对底层系统调用一次所能读写的数据块大小。例如，磁带机通常一次能写的数据块长度是10k。所以，如果你试图写的数据量不是10k的整数倍，磁带机还
   是会以 10k 为单位卷绕磁带，从而在磁带上留下了空隙


'为了给设备和磁盘文件提供更高层的接口，Linux 发行版（和 UNIX）提供了一系列的标准函数库'。它们是一些由函数构成的集合，你可以把它们应用到自己的程序
中，比如提供'输出缓冲功能的标准I/O库'。你可以高效地写任意长度的数据块，库函数则在数据满足数据块长度要求时安排执行底层系统调用。这就极大降低了系统调
用的开销。

库函数的文档一般被放在手册页的第三节, 并且库函数往往会有一个与之对应的标准头文件，例如与标准 I/O 库对应的头文件是 stdio.h。


// !! 底层文件访问

每个运行中的程序被称为进程(process)，它有一些与之关联的文件描述符。这是一些小值整数，你可以通过它们访问打开的文件或设备。

当一个程序开始运行时，它一般会有 3 个已经打开的文件描述符:

0：标准输入

1：标准输出

2：标准错误

你可以通过系统调用 open 把其他文件描述符与文件和设备相关联。使用自动打开的文件描述符就已经可以通过 write 系统调用来创建一些简单的程序了

1. write 系统调用

系统调用 write 的作用是把缓冲区 buf 的前 nbytes 个字节写入与文件描述符 fildes 关联的文件中， 它返回实际写入的字节数。如果文件描述符有错或
者底层的设备驱动程序对数据块长度比较敏感，该返回值可能会小于 nbytes。如果这个函数返回 0 ，就表示未写入任何数据；如果它返回的是 -1，就表示在 
write 调用中出现了错误，错误代码保存在全局变量 errno 里。

下面是 write 系统调用的原型:

#include <unistd.h>

size_t write(int fildes, const void *buf, size_t nbytes);

有了这些知识，你就可以编写第一个程序 simple_write.c 了:

#include <stdlib.h>
#include<unistd.h>

int main()
{
    if(write(1,"Here is some data\n",18) != 18)
    {
        write(2,"A write error has occurred on file descriptor 1\n",46);
    }
    exit(0);
}

» gcc -o simple_write simple_write.c
 » ./simple_write
Here is some data


需要再次提醒的是，write 可能会报告写入的字节比你要求的少。这并不一定是个错误。在程序中，你需要检查 errno 以发现错误，然后再次调用 write 写入剩
余的数据。


// !! read 系统调用

系统调用 read 的作用是：从与文件描述符 fildes 相关联的文件里读入 nbytes 个字节的数据，并把它们放到数据区 buf 中。它返回实际读入的字节数，这可能
会小于请求的字节数。如果 read 调用返回 0，就表示未读入任何数据，已到达了文件尾。同样，如果返回的是 -1，就表示 read 调用出现了错误。

include <unistd.h>
size_t read(int fildes, void *buf, size_t nbytes);

下面这个程序 simple_read.c 把标准输入的前 128 个字节复制到标准输出。如果输入少于 128 个字节，就把它们全体复制过去。

#include <unistd.h>
#include <stdlib.h>

int main()
{
    char buf[128];
    int nread;
    nread = read(0, buf, 128);
    if(nread == -1)
    {
        write(2,"A read error occured\n",26);
    }
    if(write(1,buf,nread) != nread)
    {
        write(2,"A write error occured\n",27);
    }
    exit(0);
}



» gcc -o simple_read simple_read.c 


 » echo "hello world"|./simple_read 
hello world

or

» ./simple_read < hello.txt 
Linux is Everything

第一次运行程序时，你使用 echo 通过管道为程序提供输入。在第二次运行时，你通过文件重定向输入。此时，你可以看到文件 hello.txt 文件内容出现在了标准
输出上。


// !! open 系统调用

为了创建一个新的文件描述符, 你需要使用系统调用 open

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int open(const char *path, int oflags);
int open(const char *path, int oflags, mode_t mode);

'严格来说，在遵循 POSIX 规范的系统上，使用 open 系统调用并不需要包括头文件 sys/types.h 和 sys/stat.h，但在某些 UNIX 系统上，它们可能是必不可少的'。

简单地说，open 建立了一条到文件或设备的访问路径。如果调用成功，它将返回一个可以被 read、write 和其他系统调用使用的文件描述符。

'这个文件描述符是唯一的，它不会与任何其他运行中的进程共享'。如果两个程序同时打开同一个文件，它们会分别得到两个不同的文件描述符。如果它们都对文件进行写操作，
那么它们会各写各的，它们分别接着上次离开的位置继续往下写。它们的数据不会交织在一起，而是彼此互相覆盖。两个程序对文件的读写位置（偏移值）不同。你可以通过使用
文件锁功能来防止出现冲突。


准备打开的文件或设备的名字作为参数 path 传递给函数，oflags 参数用于指定打开文件所采取的动作。

open 调用必须指定文件访问模式：

1. O_RDONLY  以只读方式打开

2. O_WRONLY  以只写方式打开

3. O_RDWR    以读写方式打开

open 调用还可以在 oflags 参数中包括下列可选模式的组合（用“按位或”操作）。

O_APPEND：把写入数据追加在文件的末尾

O_TRUNC：把文件长度设置为零，丢弃已有的内容

O_CREAT：如果需要，就按参数 mode 中给出的访问模式创建文件

O_EXCL：与 O_CREAT 一起使用，确保调用者创建出文件

Open 调用是一个原子操作，也就是说，它只执行一个函数调用。使用这个可选模式可以防止两个程序同时创建同一个文件。如果文件已经存在，open 调用将失败


open 调用在成功时返回一个新的文件描述符（它总是一个非负整数），在失败时返回 -1 并设置全局变量 errno 来指明失败的原因。'新文件描述符总是使用未用描述符的最
小值'，这个特征在某些情况下非常有用。


'任何一个运行中的程序能够同时打开的文件数是有限制的'。这个限制通常是由 limits.h 头文件中的常量 OPEN_MAX 定义的，它的值随系统的不同而不同，但 POSIX 要求它
至少为 16。这个限制本身还受到本地系统全局性限制的影响，所以一个程序未必总是能够打开这么多文件。在 Linux 系统中，这个限制可以在系统运行时调整，所以 OPEN_MAX
并不是一个常量。它通常一开始被设置为 256。

// !!访问权限的初始值


当你使用带有 O_CREAT 标志的 open 调用来创建文件时，你必须使用有 3 个参数格式的 open 调用。第三个参数 mode 是几个标志按位或后得到的，这些标志在头文件 
sys/stat.h.中定义，如下所示:

S_IRUSR：读权限，文件属主; S_IWUSR：写权限，文件属主; S_IXUSR：执行权限，文件属主; S_IRGRP：读权限，文件所属组; S_IWGRP：写权限，文件所属组; 
S_IXGRP：执行权限，文件所属组; S_IROTH：读权限，其他用户; S_lW0TH：写权限，其他用户; S_IXOTH：执行权限，其他用户

请看下面的例子:

open ("myfile", O_CREAT, S_IRUSR|S_IXOTH);

它的作用是创建一个名为 myfile 的文件，文件属主拥有读权限，其他用户拥有执行权限,且只设置了这些权限。

// !! close 系统调用

'使用 close 调用终止文件描述符 fildes 与其对应文件之间的关联', 文件描述符被释放并能够重新使用。close 调用成功时返回 0，出错时返回 -1。


#include <unistd.h>

int close(int fildes);

注意，检查 close 调用的返回结果非常重要。有的文件系统，特别是网络文件系统，可能不会在关闭文件之前报告文件写操作中出现的错误，这是因为在执行写操
作时，数据可能未被确认写入。

// !! ioctl 系统调用

ioctl 调用有点像是个大杂烩。它提供了一个用于控制设备及其描述符行为和配置底层服务的接口。


POSIX 规范只为流(stream) 定义了 ioctl 调用, 下面是 ioctl 的原型：

#include <unistd.h>

int ioctl(int fildes, int cmd, ...);


// !! 实验　一个文件复制程序

在学习了关于 open、read 和 write 系统调用的知识以后，我们来编写一个底层程序 copy_system.c，用来逐个字符地把一个文件复制到另外一个文件。

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    char ch;
    int in, out;
    in = open("file.txt", O_RDONLY);
    out = open("fileout.txt", O_WRONLY|O_CREAT,S_IRUSR|S_IWGRP);
    while(read(in,&ch,1) == 1) 
    {
        write(out,&ch,1);
    }
    exit(0);
}

我们在这里使用 time 工具对这个程序的运行时间进行了测算。Linux 使用 TIMEFORMAT 变量来重置默认的 POSIX 时间输出格式，POSIX 时间格式不包括 CPU 
使用率。


 » time ./copy_system             
./copy_system  1.15s user 4.64s system 99% cpu 5.808 total


// !! 实验　另一个文件复制程序


'可以通过复制大一些的数据块来改善效率较低的问题'，请看下面这个改进后的程序 copy_block.c，它每次复制长度为 1K 的数据块，用的还是系统调用:


#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    char BUF[1024];
    int in, out;
    int nread;
    in = open("file.txt", O_RDONLY);
    out = open("fileout.txt", O_WRONLY|O_CREAT,S_IRUSR|S_IWGRP);
    while((nread = read(in,BUF,1024)) > 0) 
    {
        write(out,BUF,nread);
    }
    exit(0);
}

» gcc -o copy_block copy_block.c 
» time ./copy_block             

./copy_block  0.00s user 0.01s system 96% cpu 0.010 total

改进后的程序只花费了百分之几秒的时间，因为它只需做大约 2 000 次系统调用。当然，这些时间与系统本身的性能有很大的关系，但它们确实显示了系统调用需
要巨大的开支，因此值得对其使用进行优化。


// !! 其他与文件管理有关的系统调用

1. lseek 系统调用

lseek 系统调用对文件描述符 fildes 的读写指针进行设置。也就是说，你可以用它来设置文件的下一个读写位置。读写指针既可被设置为文件中的某个绝对位置，
也可以把它设置为相对于当前位置或文件尾的某个相对位置。

#include <unistd.h>
#include <sys/types.h>

off_t lseek(int fildes, off_t offset, int whence);


offset 参数用来指定位置，而 whence 参数定义该偏移值的用法。

whence 可以取下列值之一:

SEEK_SET：offset 是一个绝对位置

SEEK_CUR：offset 是相对于当前位置的一个相对位置

SEEK_END：offset 是相对于文件尾的一个相对位置

lseek 返回从文件头到文件指针被设置处的字节偏移值，失败时返回 -1。参数 offset 的类型 off_t 是一个与具体实现有关的整数类型，它定义在头文件 
sys/types.h 中。



2. fstat、stat和lstat系统调用

'fstat 系统调用返回与打开的文件描述符相关的文件的状态信息'，该信息将会写到一个 buf 结构中，buf 的地址以参数形式传递给 fstat


下面是它们的原型：

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int fstat(int fildes, struct stat *buf);
int stat(const char *path, struct stat *buf);
int lstat(const char *path, struct stat *buf);


// !! 标准 I/O 库

'标准I/O库(stdio)及其头文件 stdio.h 为底层 I/O 系统调用提供了一个通用的接口'。这个库现在已经成为 ANSI 标准 C 的一部分，而你前面见到的系统调用却
还不是。标准 I/O 库提供了许多复杂的函数用于格式化输出和扫描输入, 它还负责满足设备的缓冲需求。

在很多方面，你使用标准 I/O库 的方式和使用底层文件描述符一样。你需要先打开一个文件以建立一个访问路径。这个操作的返回值将作为其他 I/O 库函数的参数。'在标
准I/O库中，与底层文件描述符对应的是流(stream)，它被实现为指向结构 FILE 的指针'。

在启动程序时，有 3 个文件流是自动打开的。它们是 stdin、stdout 和 stderr。它们都是在 stdio.h 头文件里定义的，分别代表着标准输入、标准输出和标准错误
输出，与底层文件描述符 0、1 和 2 相对应。

// !! fopen 函数

fopen 库函数类似于底层的 open 系统调用。它主要用于文件和终端的输入输出。如果你需要对设备进行明确的控制，那最好使用底层系统调用，因为这可以避免用库函数带
来的一些潜在问题，如输入/输出缓冲。

该函数原型如下:

#include <stdio.h>

FILE *fopen(const char *filename, const char *mode);

fopen 打开 filename 参数指定的文件，并把它与一个文件流关联起来。

'mode 参数指定文件的打开方式，它取下列字符串中的值':

1. "r"或"rb"：以只读方式打开

2. "w"或"wb"：以写方式打开，并把文件长度截短为零

3. "a"或"ab"：以写方式打开，新内容追加在文件尾

4. "r+"或"rb+"或"r+b"：以更新方式打开（读和写）

5. "w+"或"wb+"或"w+b"：以更新方式打开，并把文件长度截短为零

6. "a+"或"ab+"或"a+b"：以更新方式打开，新内容追加在文件尾


字母 b 表示文件是一个二进制文件而不是文本文件。

fopen 在成功时返回一个非空的 FILE * 指针，失败时返回 NULL 值，NULL 值在头文件stdio.h里定义。

可用的文件流数量和文件描述符一样，都是有限制的。实际的限制是由头文件 stdio. h中定义的 FOPEN_MAX 来定义的，它的值至少为 8，在 Linux 系统中，通常
是 16。


// !! fread 函数


'fread 库函数用于从一个文件流里读取数据'。数据从文件流 stream 读到由 ptr 指向的数据缓冲区里。fread 和 fwrite 都是对数据记录进行操作，'size 参数
指定每个数据记录的长度'，'计数器 nitems 给出要传输的记录个数'。它的返回值是成功读到数据缓冲区里的记录个数（而不是字节数）。当到达文件尾时，它的返回
值可能会小于 nitems ，甚至可以是零。

该函数原型如下：

#include <stdio.h>

size_t fread(void *ptr, size_t size, size_t nitems, FILE *stream);

对所有向缓冲区里写数据的标准 I/O 函数来说，为数据分配空间和检查错误是程序员的责任。

// !!fwrite函数

fwrite 库函数与 fread 有相似的接口。它从指定的数据缓冲区里取出数据记录，并把它们写到输出流中, 它的返回值是成功写入的记录个数。

该函数原型如下:

#include <stdio.h>

size_t fwrite (const void *ptr, size_t size, size_t nitems, FILE *stream);

请注意，我们不推荐把 fread 和 fwrite 用于结构化数据。部分原因在于用 fwrite 写的文件在不同的计算机体系结构之间可能不具备可移植性。


// !! fclose 函数

fclose 库函数关闭指定的文件流 stream，使所有尚未写出的数据都写出。。'因为 stdio 库会对数据进行缓冲，所以使用 fclose 是很重要的'。
如果程序需要确保数据已经全部写出, 就应该调用 fclose 函数。虽然当程序正常结束时，会自动对所有还打开的文件流调用 fclose 函数，但这样做
你就没有机会检查由 fclose 报告的错误了。

该函数原型如下:

#include <stdio.h>

int fclose(FILE *stream);


// !! fflush 函数

'fflush 库函数的作用是把文件流里的所有未写出数据立刻写出'。

使用这个函数还可以确保在程序继续执行之前重要的数据都已经被写到磁盘上。有时在调试程序时，你还可以用它来确认程序是正在写数据而不是被挂起了。
注意，调用 fclose 函数隐含执行了一次 flush 操作，所以你不必在调用 fclose 之前调用 fflush。

该函数原型如下：

#include <stdio.h>

int fflush(FILE *stream);

// !! fseek 函数

'fseek 函数是与 lseek 系统调用对应的文件流函数。它在文件流里为下一次读写操作指定位置'。

该函数原型如下：

#include <stdio.h>

int fseek(FILE *stream, long int offset, int whence);


// !! fgetc、getc和getchar函数

fgetc 函数从文件流里取出下一个字节并把它作为一个字符返回。当它到达文件尾或出现错误时，它返回 EOF。你必须通过 ferror或 feof 来区分这两种情况。

这些函数的原型如下：

#include <stdio.h>

int fgetc(FILE *stream);
int getc(FILE *stream);
int getchar();

'getchar 函数的作用相当于 getc(stdin)，它从标准输入里读取下一个字符'


// !! fputc、putc 和 putchar 函数

'fputc 函数把一个字符写到一个输出文件流中'。它返回写入的值，如果失败，则返回 EOF。

#include <stdio.h>

int fputc(int c, FILE *stream);
int putc(int c, FILE *stream);
int putchar(int c); 

'putchar(int c) 函数相当于 putc(c, stdout)，它把单个字符写到标准输出'


// !! fgets 和 gets 函数

fgets 函数从输入文件流 stream 里读取一个字符串。

#include <stdio.h>

char *fgets(char *s, int n, FILE *stream);
char *gets(char *s);


fgets 把读到的字符写到 s 指向的字符串里，直到出现下面某种情况：遇到换行符，已经传输了 n-1 个字符，或者到达文件尾。它会把遇到的换行符也传递到接
收字符串里，再加上一个表示结尾的空字节 \0。一次调用最多只能传输 n-1个 字符，因为它必须把空字节加上以结束字符串。当成功完成时，fgets 返回一个指
向字符串 s 的指针。 

gets 函数类似于 fgets，只不过它从标准输入读取数据并丢弃遇到的换行符, 它在接收字符串的尾部加上一个 null 字节。

'注意'：

'gets 对传输字符的个数并没有限制，所以它可能会溢出自己的传输缓冲区'。因此，你应该避免使用它并用 fgets 来代替。'许多安全问题都可以追溯到在程序中
使用了可能造成各种缓冲区溢出的函数'，gets 就是一个这样的函数，所以千万要小心！

