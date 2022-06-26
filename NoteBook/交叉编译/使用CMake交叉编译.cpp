## 交叉编译

### 设置系统和工具链

对于交叉编译, CMake 并不知道目标系统是什么, 所以需要设置一些 CMake 变量来告知 CMake

CMAKE_SYSTEM_NAME: 即目标系统名(Linux、QNX、Windows)

CMAKE_SYSTEM_PROCESSOR : 目标系统的处理器名(x86、aarch64)


对于工具链, 则是通过下面 2 个变量来定位

CMAKE_C_COMPILER: C 编译器的可执行文件名称

CMAKE_CXX_COMPILER: C++ 编译器的可执行文件名称


这些变量可以在调用 CMake 时通过命令行传递, 但是这种做法容易出错, 而且用起来不方便, 所以 'CMake 提供了工具链文件的方式来传递这些变量信息'。


### 工具链文件

我们在工程里新建一个文件叫 arm_linux_setup.cmake ,其内容如下:

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_SYSROOT /home/devel/rasp-pi-rootfs)
set(CMAKE_STAGING_PREFIX /home/devel/stage)

set(tools /home/devel/gcc-4.7-linaro-rpi-gnueabihf)
set(CMAKE_C_COMPILER ${tools}/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/arm-linux-gnueabihf-g++)

tools 是本人使用的交叉工具链路径, 可以根据自己的实际文件来做修改。

### 编译

使用 CMake 的变量 CMAKE_TOOLCHAIN_FILE 来指定工具链文件, cd 到 build 目录, 然后执行下面的命令:

// 注意，工具链文件的指定一定要紧跟cmake命令之后，不能放到 .. 后面
cmake -DCMAKE_TOOLCHAIN_FILE=../arm_linux_setup.cmake ..


ok 后再执行 make 就可以生成 main 的 elf 文件。使用 file 命令去查看这个文件, 可以看到其运行平台是 32 位 ARM 处理器上的 Linux 系统。