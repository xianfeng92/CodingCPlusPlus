#include <stdio.h>
#include <pthread.h>
#include "mythread.h"

static volatile int counter = 0;

void *mythread(void *arg) {
    printf("%s: begin\n", (char *)arg);
    int i;
    for(i = 0; i < le7; i++) {
        counter++;
    }
    printf("%s:done\n", (char *)arg);
    return NULL;
}

int main(int argc, char **argv) {
    pthread_t p1, p2;
    printf("main: begin (counter = %d)\n", counter);
    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("main: done with both (counter = %d)\n", counter);
    return 0;
}

