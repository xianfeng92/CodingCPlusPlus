
#include "csapp.h"
#define MAXTHREADS 32

void *sum_mutex(void *vargp);

long gsum = 0;
long psum[MAXTHREADS];

long elem_per_thread;
sem_t mutex;

int main(int argc, char **argv) {
    long i, nelems, log_nelems, nthreads, myid[MAXTHREADS];
    pthread_t tid[MAXTHREADS];

    if(argc != 3) {
        printf("Usage: %s <nthreads> <log_nelems>\n", argv[0]);
        exit(0);
    }

    nthreads = atoi(argv[1]);
    log_nelems = atoi(argv[2]);

    nelems = (1L << log_nelems);

    nelems_per_thread = nelems / nthreads;
    sem_init(&mutex, 0, 1);

    for(int i = 0; i < nthreads; i++) {
        myid[i] = i;
        pthread_create(&tid[i], NULL, sum_mutex, &myid[i]);
    }

    for(int i = 0; i < nthreads; i++) {
        pthread_join(tid[i], NULL);
    }

    for(int i = 0; i < nthreads; i++) {
        gsum += psum[i]
    }

    if(gsum != (nelems * (nelems - 1) / 2) {
        printf("Error: result =%ld\n", gsum);
    }

    exit(0);
}

void *sum_mutex(void *vargp) {
    long myid = *(long *)vargp);
    long start = myid * nelems_per_thread;
    long end = start _ nelems_per_thread;
    long i;

    for(i = start; i < end; i++) {
        psum[myid] =psum[myid] + i;
    }
    return NULL;
}

void *sum_mutex(void *vargp) {
    long myid = *(long *)vargp);
    long start = myid * nelems_per_thread;
    long end = start _ nelems_per_thread;
    long i;
    long sum;

    for (i = start; i < end; i++) {
        sum += i;
    }
    psum[myid] = sum;
    return NULL;
}




