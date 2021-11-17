// !! 共享库版本


// !! 共享库兼容性


// !! 共享库版本命名

Linux 有一套规则来命名系统中的每一个共享库, 它规定共享库的文件名规则必须如下：libname.so.x.y.z。最前面使用前缀 ”lib”、中间是库的名字和后缀”.so”，最后面跟着的是
三个数字组成的版本号。”x” 表示主版本号(Major Version Number)，”y” 表示次版本号(Minor Version Number)，”z”表示发布版本号(Release Version Number)。


1. 主版本号表示库的重大升级， '不同主版本号的库之间是不兼容的'，依赖于旧的主版本号的程序需要改动相应的部分，并且重新编译，才可以在新版的共享库中运行；或者系统必须保留
   旧版的共享库，使得那些依赖于旧版共享库的程序能够正常运行。

2. 次版本号表示库的增量升级，即增加一些新的接口符号，且保持原来的符号不变。'在主版本号相同的情况下，高的次版本号的库向后兼容低的次版本号的库'。一个依赖于旧的次版本号
   共享库的程序，可以在新的次版本号共享库中运行， 因为新版中保留了原来所有的接口，并且不改变它们的定义和含义。

3. 发布版本号表示库的一些错误的修正、性能的改进等, 并不添加任何新的接口，也不对接口进行更改。相同主版本号、次版本号的共享库，不同的发布版本号之间完全兼容，依赖于某个发
   布版本号的程序可以在任何一个其它发布版本号中正常运行，而无需做任何修改。


// !! SO-NAME

对于 Solaris 和 Linux，普遍采用一种叫做 SO-NAME 的命名机制来记录共享库的依赖关系。每个共享库都有一个对应的”SO-NAME”， 这个SO-NAME 即共享库的文件名去掉次版本号和
发布版本号，保留主版本号。

'在 Linux 系统中，系统会为每个共享库在它所在的目录创建一个跟 ”SO-NAME” 相同的并且指向它的软链接(Symbol Link)'。


2643508 lrwxrwxrwx  1 root root       21 Dec  8  2019 libcairo.so -> libcairo.so.2.11600.0
2627303 lrwxrwxrwx  1 root root       21 Aug  7  2020 libcairo.so.2 -> libcairo.so.2.11600.0
2627304 -rw-r--r--  1 root root  1183496 Dec  8  2019 libcairo.so.2.11600.0
2624990 lrwxrwxrwx  1 root root       22 Apr  8  2021 libcamel-1.2.so.62 -> libcamel-1.2.so.62.0.0
2624989 -rw-r--r--  1 root root  1428192 Apr  8  2021 libcamel-1.2.so.62.0.0
3278636 drwxr-xr-x  2 root root     4096 Apr 23  2020 libcanberra-0.30
2627309 lrwxrwxrwx  1 root root       25 Aug  7  2020 libcanberra-gtk3.so.0 -> libcanberra-gtk3.so.0.1.9
2627310 -rw-r--r--  1 root root    22368 Jun 21  2019 libcanberra-gtk3.so.0.1.9
2627311 lrwxrwxrwx  1 root root       20 Aug  7  2020 libcanberra.so.0 -> libcanberra.so.0.2.5
2627312 -rw-r--r--  1 root root    71680 Jun 21  2019 libcanberra.so.0.2.5
2627313 lrwxrwxrwx  1 root root       18 Aug  7  2020 libcap-ng.so.0 -> libcap-ng.so.0.0.0
2627314 -rw-r--r--  1 root root    27064 Jan 25  2020 libcap-ng.so.0.0.0
2627315 lrwxrwxrwx  1 root root       14 Aug  7  2020 libcap.so.2 -> libcap.so.2.32
2627316 -rw-r--r--  1 root root    31120 Feb 17  2020 libcap.so.2.32
2627317 lrwxrwxrwx  1 root root       16 Aug  7  2020 libcbor.so.0.6 -> libcbor.so.0.6.0
2627318 -rw-r--r--  1 root root    55424 Mar 26  2020 libcbor.so.0.6.0
2623631 lrwxrwxrwx  1 root root       15 May 29 15:49 libcc1.so.0 -> libcc1.so.0.0.0


比如系统中有存在一个共享库 libcairo.so.2.11600.0, 那么 Linux 中的共享库管理程序 ldconfig 就会为它产生一个软链接 libcairo.so.2 指向它。

那么以 ”SO-NAME” 为名字建立软链接有什么用处呢 ？

'实际上这个软链接会指向目录中主版本号相同、次版本号和发布版本号最新的共享库。' 这样保证了所有的以 SO-NAME 为名的软链接都指向系统中最新版的共享库。

建立以 SO-NAME 为名字的软链接目的是，使得所有依赖某个共享库的模块，在编译、链接和运行时，都使用共享库的 SO-NAME，而不使用详细的版本号。

当共享库进行升级的时候，如果只是进行增量升级，即保持主版本号不变，只改变次版本号或发布版本号，那么我们可以直接将新版的共享库替换掉旧版，并且修改 SO-NAME 的软链接指
向新版本共享库，即可实现升级; 当共享库的主版本号升级时，系统中就会存在多个 SO-NAME，由于这些 SO-NAME 并不相同，所以已有的程序并不会受影响。

Linux 中提供了一个工具叫做 ldconfig，当系统中更新一个共享库时，就需要运行这个工具，它会遍历所有的默认共享库目录，比如 /lib、/usr/lib 等，然后更新所有的软
链接，使它们指向最新版的共享库; 如果安装了新的共享库, 那么 ldconfig 会为其创建相应的软链接。



// !! 链接名

当我们在编译器里面使用共享库的时候(比如使用 GCC 的 ”-l” 参数链接某个共享库)，我们使用了更为简洁的方式，比如需要链接一个 libXXX.so.2.6.1 的共享库，只需要在编译器
命令行里面指定 -lXXX 即可，可省略所有其它部分。编译器会根据当前环境，在系统中的相关路径(往往由 -L 参数指定)查找最新版本的”XXX”库。'这个”XXX”又被称为共享库的链接名
(Link Name)'。
