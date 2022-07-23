// !! 13.2　如何使用 Mini CRT

一般一个 CRT 提供给最终用户时往往有两部分, '一部分是 CRT 的库文件部分', 用于与用户程序进行链接, 如 Glibc 提供了两个版本的库文件: 静态 Glibc 库 libc.a 和动态 
Glibc 库 libc.so; 'CRT 的另外一部分就是它的头文件', 包含了使用该 CRT 所需要的所有常数定义、宏定义及函数声明, 通常 CRT 都会有很多个头文件。

Mini CRT 也将以库文件和头文件的形式提供给用户。首先我们建立一个 minicrt.h 的头文件, 然后将所有相关的常数定义、宏定义, 以及 Mini CRT 所实现的函数声明等放在该头文件
里。当用户程序使用 Mini CRT 时, 仅需要 #include "minicrt.h" 即可, 而无须像标准的 CRT 一样, 需要独立的包含相关文件, 比如 "stdio.h"、"stdlib.h"等。

minicrt.h 的内容如清单 13-6 所示。

#ifndef __MINI_CRT_H__
#define __MINI_CRT_H__

#ifdef __cplusplus
extern "C" {
#endif

//malloc
#ifndef NULL
#define NULL (0)
#endif

void free(void *);
void *malloc(unsigned size);
static int brk(void* end_data_segment);
int mini_crt_heap_init();

// 字符串
char* iota(int n, char* str, int radix);
int strcmp(const char* src, const char* dst);
char* strcpy(char* dst, const char* src);
unsigned strlen(const char* src);


// 文件与IO
typedef int FILE;
#define EOF (-1)

#ifdef WIN32
#define stdin   ((FILE*)(GetStdHandle(STD_INPUT_HANDLE)))
#define stdout  ((FILE*)(GetStdHandle(STD_OUTPUT_HANDLE)))
#define stderr  ((FILE*)(GetStdHandle(STD_ERROR_HANDLE)))
#else
#define stdin ((FILE*)0)
#define stdout ((FILE*)1)
#define stderr ((FILE*)2)
#endif

int mini_crt_io_init();
FILE* fopen(const char* filename, const char* mode);
int fread(void* buffer, int size, int count, FILE* stream);
int fwrite(const void* buffer, int size, int count, FILE* stream);
int fclose(FILE* stream);
int fseek(FILE* stream, int offset, int set);


// printf
int fputc(int c, FILE* stream);
int fputs(const char* str, FILE* stream);
int printf(const char* format, ...);
int fprintf(FILE* stream, const char* format, ...);

// internal
void do_global_ctors();
void mini_crt_call_exit_routine();

// atexit
typedef void (*atexit_func_t )( void );
int atexit(atexit_func_t func);

#ifdef __cplusplus
}
#endif

#endif // __MINI_CRT_H__


由于动态库的实现比静态库要复杂, 所以 Mini CRT 仅仅以静态库的形式提供给最终用户, 在 Linux 下它是 minicrt.a。

在不同平台下编译和制作库文件的步骤如下所示, Linux 下的命令行为:

> gcc -c -fno-builtin -nostdlib -fno-stack-protector entry.c malloc.c stdio.c string.c printf.c
> ar -rs minicrt.a malloc.o printf.o stdio.o string.o

为了测试 Mini CRT 是否能够正常运行, 我们专门编写了一段测试代码, 用于测试 Mini CRT 的功能, 如清单 13-7 所示。

#include "minicrt.h"

int main(int argc, char **argv) {
    int i;
    FILE *fp;
    char** v = malloc(argc*sizeof(char*));
    for (i = 0; i < argc; i++) {
        v[i] = malloc(strlen(argv[i]) + 1);
        strcpy(v[i], argv[i]);
    }
    fp = fopen("test.txt", "w");
    for(int i = 0; i < argc; i++) {
        int len = strlen(v[i]);
        fwrite(&len, 1, sizeof(int), fp);
        fwrite(v[i],1, len, fp);
    }
    fclose(fp);

    fp = fopen("test.txt", "r");
    for(int i = 0; i < argc; i++) {
        int len;
        char* buf;
        fread(&len, 1, sizeof(int), fp);
        buf = malloc(len + 1);
        fread(buf, 1, len, fp);
        buf[len] = '\0';
        printf("%d %s\n", len, buf);
        free(buf);
        free(v[i]);
    }
    fclose(fp);
}

这段代码用到了 Mini CRT 中绝大部分函数, 包括 malloc、free、fopen、fclose、fread、fwrite、printf, 并且测试了 main 参数。它的作用就是将 main 的参数字符串都保存
到文件中, 然后再读取出来, 由 printf 显示出来。

在 Linux 下, 可以用下面的方法编译和运行 test.c:

> gcc -c -ggdb -fno-builtin -nostdlib -fno-stack-protector test.c
> ld -static -e mini_crt_entry entry.o test.o minicrt.a -o test