
// !! 编译准备

// !! 安装编译所需依赖

1. 更新软件源

sudo apt update

2. 安装所需依赖

sudo apt install libncurses5-dev openssl libssl-dev build-essential pkg-config libc6-dev bison flex libelf-dev zlibc minizip libidn11-dev libidn11

值得注意的是，这些依赖可能并不是最小依赖集，可能在去掉一部分依赖后编译安装仍然能够进行


// !! 下载 Linux 内核源代码

进入 Linux 内核官网（kernel.org）进行下载：选择一个合适的版本（最好是 stable 或者 longterm，当然其他版本的内核也是可以的，但是可能会造成问题）下载（tarball，即
源代码）；或者直接点击那个硕大的下载按钮即可。

如： linux-5.15.2.tar.xz


// !! 解压 Linux 内核源代码

1. 需要将源代码解压到指定的目录

sudo tar -xavf  linux-5.15.2.tar.xz  -C /usr/src


// !! 编译内核

1. 配置内核编译选项

Linux 具有庞大的模块库，允许用户根据自身需求进行配置。但是其中大部分功能对于一般用户来说没有很大的意义，没有对其进行编译的必要，所以对编译选项进行合理的配置是极其
必要的。

为了简便和兼容性考虑，这里直接采用原有内核的配置文件来进行配置

首先需要将现有内核的配置文件复制到新内核的配置目录中:


sudo cp /boot/config-5.11.0-38-generic /usr/src/inux-5.15.2/.config

需要注意的是，由于系统预装的内核版本往往不只有一个，在 boot 目录下往往有很多版本的启动配置文件。为了兼容性考虑，最好采用系统目前使用的内核版本配置文件。可以通过如下
命令查看当前内核版本：


$ uname -r

5.11.0-38-generic


2. make menuconfig（基于文本的菜单式配置界面）

这是一个图形化配置界面，在进入该界面后，只需依序选择 Load -> OK -> Save -> OK -> Exit -> Exit 即可完成配置，极其简单


// !! 编译内核

编译内核是一个较为费时的工作:

# -j 参数后的数字根据你分配的核心数目选择合适的数字，代表同时进行编译的线程数
$ sudo make bzImage -j8


// !! 编译模块

同编译内核相比，编译模块将会花费更多的时间:

# -j 参数后的数字根据你分配的核心数目选择合适的数字，代表同时进行编译的线程数
$ sudo make modules -j8


// !! 安装模块

在模块编译完成后，需要进行模块的安装:

$ sudo make modules_install

在模块安装完成后，在 /lib/modules 目录下，可以看到新版内核的模块文件


// !! 安装内核

复制编译结果到指定目录:

$ sudo mkinitramfs /lib/modules/5.15.2 -o /boot/initrd.img-5.15.2-generic
$ sudo cp /usr/src/linux-5.15.2/arch/x86_64/boot/bzImage /boot/vmlinuz-5.15.2-generic
$ sudo cp /usr/src/linux-5.15.2/System.map /boot/System.map-5.15.2


// !! 更改引导信息

在更改引导信息前，最好将现有引导配置文件进行备份，以防不测

自动更新引导信息可以在 /boot/grub 目录下执行 update-grub2 命令即可。在更新完成后，可以对比新旧 grub.cfg 文件，发现多了新版内核的相关配置


在完成上述步骤后，如果没有意外，在系统重启之后，再此执行 uname -r 命令可以发现自己的内核已经更新成功了！



// !!其他

如果在编译过程中出现中断、错误或其他导致编译未完成的情况，或者在编译完成后想重新编译内核，可以执行如下命令:

# mrproper 选项将会删除包括配置文件在哪的一切编译信息及结果
$ sudo make mrproper

# clean 选项在删除编译结果的同时会保留配置文件
$ sudo make clean