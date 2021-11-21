/* 在遵循 Mini CRT 的原则下，将 Mini CRT 堆的实现概括为如下几条:
1.实现一个以空闲链表算法为基础的堆空间分配算法
2.为了简单起见，堆空间大小固定为 32MB，初始化后空间再也不扩展或缩小
3.在 Windows 平台下不适用 HeapAlloc 等堆分配算法，采用 VirtualAlloc 向系统直接申请 32MB 空间
4.在 Linux 平台下，使用 brk 将数据段结束地址向后调整32MB，将这块空间做为堆空间
  brk 系统调用能够设置进程的数据段 .data 边界，而 sbrk 能够移动进程的数据段边界，显然若是将数据段边界后移，就至关于分配了必定量的内存。
  可是这段内存初始只是分配了虚拟空间，这些空间的申请一开始是不会提交的（即不会分配物理页面），当进程需要访问一个地址的时候，操作系统会检测到页缺乏
  异常，从而会为被访问的地址所在的页分配物理页面。故而这种被动的物理分配，又被称为按践踏分配，即不打不动。 
*/
//malloc.c
#include "minicrt.h"

typedef struct _heap_header
{
    enum
    {
        HEAP_BLOCK_FREE = 0XABABABAB,// magic number of free block
        HEAP_BLOCK_USED = 0XCDCDCDCD// magic number of used block
    } type;// block type Free/Used
    unsigned long size;// block size include header
    struct _heap_header *next;
    struct _heap_header *prev;
} heap_header;

#define ADDR_ADD(a, o) (((char *)(a)) + o)
#define HEADER_SIZE (sizeof(heap_header))

heap_header* list_head	= NULL;		///static

void free(void *ptr)
{
    heap_header *header = (heap_header *)ADDR_ADD(ptr, -HEADER_SIZE);
    if (header->type != HEAP_BLOCK_USED)
    {
        return;
    }
    // !! 当用户释放某一块空间时，堆分配算法会判断被释放前后两个块是否为空闲块，如果是，将它们合并成一个空闲块
    header->type = HEAP_BLOCK_FREE;
    if (header->prev != NULL && header->prev->type == HEAP_BLOCK_FREE)
    {
        // 释放块的前一个块也正好为空, 需要进行 Merge 操作
        header->prev->next = header->next;
        if (header->next != NULL)
        {
            header->next->prev = header->prev;
        }
        header->prev->size += header->size;

        header = header->prev;
    }

    if (header->next != NULL && header->next->type == HEAP_BLOCK_FREE)
    {
        // 释放块的后一个块也是空块，需要进行 Merge 操作
        header->size += header->next->size;
        header->next = header->next->next;
    }
}

void *malloc(unsigned long size)
{
    heap_header *header;
    if (size == 0)
    {
        return NULL;
    }

    header = list_head;
    while (header != 0)
    {
        if (header->type == HEAP_BLOCK_USED)
        {
            header = header->next;
            continue;
        }
        // 恰好碰到一个空闲快，且其块的大小大于所需 size 加上一个 HEADER_SIZE，可是小于所需 size 加上两个 HEADER_SIZE，即剩余的内部碎片
        // 就算分离出来，也没有利用价值了，直接整个块都分配给 used，等待总体释放
        if ((header->size > size + HEADER_SIZE) && (header->size <= size + HEADER_SIZE * 2))
        {
            header->type = HEAP_BLOCK_USED;
        }
        // !! 空闲块空间足够，且剩余的内部碎片分离出来还能够再使用
        if (header->size > size + HEADER_SIZE * 2)
        {
            heap_header *next = (heap_header *)ADDR_ADD(header, size + HEADER_SIZE);
            next->prev = header;
            next->next = header->next;
            next->type = HEAP_BLOCK_FREE;
            next->size = header->size - (size - HEADER_SIZE);
            header->next = next;
            header->size = size + HEADER_SIZE;
            header->type = HEAP_BLOCK_USED;
            return ADDR_ADD(header, HEADER_SIZE);
        }
        header = header->next;
    }

    return NULL;
}

#ifndef WIN32
//Linux brk system call
//  以 base 为起点分配 32MB 的内存空间 
static long brk(void *end_data_segment)
{
    long ret = 0;
    // brk system call number:45
    // long //usr/include/asm-i386/unistd.h
    //#define __NR_brk 45
    asm("movq $45, %%rax   \n\t"
        "movq %1, %%rbx  \n\t"
        "int $0x80		\n\t"
        "movq %%rax,%0  \n\t"
        : "=r"(ret)
        : "m"(end_data_segment));
}
#endif

#ifdef WIN32
#include <Windows.h>
#endif

long mini_crt_init_heap()
{
    void *base = NULL;
    heap_header *header = NULL;
    // 32MB heap size
    unsigned long heap_size = 1024 * 1024 * 32;

#ifdef WIN32
    base = VirtualAlloc(0, heap_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (base == NULL)
    {
        return 0;
    }

#else
    base = (void *)brk(0);
    void *end = ADDR_ADD(base, heap_size);
    end = (void *)brk(end);
    if (!end)
    {
        return 0;
    }
#endif

    header = (heap_header *)base;

    header->size = heap_size;
    header->type = HEAP_BLOCK_FREE;
    header->next = NULL;
    header->prev = NULL;

    list_head = header;
    return 1;
}
