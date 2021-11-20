

// !! 入口函数




// !! 堆的实现













// !! linux (手动编译链接)

gcc -c -fno-builtin -nostdlib  entry.c malloc.c stdio.c string.c printf.c
ar -rs minicrt.a malloc.o printf.o stdio.o string.o
gcc -c -ggdb -fno-builtin -nostdlib MiniCRTDemo.c
ld -static -e mini_crt_entry entry.o MiniCRTDemo.o minicrt.a -o MiniCRTDemo

// !! linux (make)


make
./test
make clean