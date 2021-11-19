#include <stdio.h>

void my_init(void)
{
	printf("Hello\n");
}

typedef void (*ctor_t)(void);
// 在 .ctors 段添加一个函数指针
ctor_t __attribute__((section (".ctors"))) my_init_p = &my_init;

int main()
{
	printf("World!\n");
	return 0;
}