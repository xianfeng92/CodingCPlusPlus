#include <stdio.h>
#include <pthread.h>

// 定义一个 pthread_create 函数的弱引用，程序在运行时动态判断是否链接到 pthread 库从而决定执行多线程版本还是单线程版本

int pthread_create( pthread_t*, const pthread_attr_t*, 
void* (*)(void*), void*) __attribute__ ((weakref));
int main()
{
    if(pthread_create) 
    {
            printf("This is multi-thread version!\n");
            // run the multi-thread version
            // main_multi_thread()
    } 
    else 
    {
            printf("This is single-thread version!\n");   
            // run the single-thread version
            // main_single_thread()
    }
}