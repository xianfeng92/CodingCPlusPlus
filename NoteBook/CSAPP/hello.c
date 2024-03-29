#include "csapp.h"

void* thread(void *vargp);

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, thread, NULL);
    pthread_join(tid, NULL);
    exit(0);
}

void* thread(void *vargp) {// thread routine
    printf("Hello world!\n");
    return NULL;
}


#include <pthread.h>

typedef void* (func)(void *);

int pthread_create(pthread_t *tid, pthread_attr_t *attr, func* f, void *arg);


#include <pthread.h>

pthread_t pthread_self(void *thread_return);

#include <pthread.h>

int pthread_cancel(pthread_t tid);


int pthread_join(pthread_t tid, void **thread_return);


pthread_once_t once_control = PTHREAD_ONCE_INIT;

int pthread_once(pthread_once_t *once_control, void(*init_routine)(void));




