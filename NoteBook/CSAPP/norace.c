
#include "csapp.h"
#define N 4

void *thread(void *vargp);

int main() {

    pthread_t tid[N];
    int i, *ptr;

    for(int i = 0; i < N; i++) {
        ptr = malloc(sizeof(int));
        *prt = i;
        pthread_create(&tid[i], NULL, thread, ptr);
    }

    for(i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }

    exit(0);
}

void *thread(void *vargp) {
    int myid = *(int *)vargp;
    printf("Hello from thread %d\n", myid);
    return NULL;
}

