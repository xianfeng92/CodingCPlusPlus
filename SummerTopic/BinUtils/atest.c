#include <stdio.h>

int globalvar = 100;

int function1(void){
    printf("Within function1\n");
    return 0;
}

int function2(void)
{
   printf("Within function2\n");
   return 0;
}

int main(void)
{
   function1();
   function2();
   printf("Within main\n");
   return 0;
}

