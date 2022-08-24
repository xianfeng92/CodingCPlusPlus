#include <stdio.h>
#include <malloc.h>

int main(int argc, char **argv) {
    int *p = malloc(32);
    free(p);
    return 0;
}

