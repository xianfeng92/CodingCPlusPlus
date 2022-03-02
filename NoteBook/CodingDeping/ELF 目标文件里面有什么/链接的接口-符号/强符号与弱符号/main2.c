#include <stdio.h>

__attribute__((weakref)) void foo();


int main()
{
    foo();
    printf("call foo()\n");
}

void foo(){

}