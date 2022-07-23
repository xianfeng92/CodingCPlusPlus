
#ifndef NOTEBOOK_COMPILE_LINK_LIB_13_20_E8_BF_90_E8_A1_8C_E5_BA_93_E5_AE_9E_E7_8E_B0_MINI_20CRT_SRC_INCLUDE_STDLIB_H
#define NOTEBOOK_COMPILE_LINK_LIB_13_20_E8_BF_90_E8_A1_8C_E5_BA_93_E5_AE_9E_E7_8E_B0_MINI_20CRT_SRC_INCLUDE_STDLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef size_t
#if defined(__i386__)
typedef unsigned int size_t;
#elif defined(__x86_64__)
typedef unsigned long size_t;
#endif
#endif

void  free(void *ptr);
void *malloc(size_t size);

char *itoa(int n, char *str, int radix);

typedef void (*atexit_func_t)(void);
int atexit(atexit_func_t func);

#ifdef __cplusplus
}
#endif

#endif // NOTEBOOK_COMPILE_LINK_LIB_13_20_E8_BF_90_E8_A1_8C_E5_BA_93_E5_AE_9E_E7_8E_B0_MINI_20CRT_SRC_INCLUDE_STDLIB_H
