#include "csapp.h"

void *thread(void *vargp);// thread routine prototype

// global shared variables
volatile long cnt = 0;

int main(int argc, char **argv) {
    long niters;
    pthread_t tid1, tid2;

    // check input arguments
    if(argc != 2) {
        printf("Usage: %s <niters>\n", argv[0]);
        exit(0);
    }
    
    niters = atoi(argv[1]);

    // create thread and waiting for them to finish
    pthread_create(&tid1, NULL, thread, &niters);
    pthread_create(&tid2, NULL, thread, &niters);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // check result
    if(cnt != (2 * niters)) {
        printf("BOOM! cnt = %ld\n", cnt);
    }else {
        printf("OK! cnt = %ld\n", cnt);
    }
    exit(0);
}

void *thread(void *vargp) {
    long i, niters = *((long *)vargp);
    for(int i = 0; i < niters; i++) {
        cnt ++;
    }
    return NULL;
}

#include "semaphore.h"

int sem_init(sem_t *sem, 0, unsigned int value);
int sem_wait(sem_t *s);//P(s)
int sem_post(sem_t *s);//V(s)
