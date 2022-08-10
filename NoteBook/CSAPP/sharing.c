#include "csapp.h"

#define N 2
void *thread(void *vargp);

char **ptr;

int main() {
    int i;
    pthread_t tid;
    char *msgs[N] = {
        "hello from foo",
        "hello from bar"
    };

    ptr = msgs;

    for(int i = 0; i < N; i++) {
        pthread_create(&tid, NULL, thread, (void*)i);
        pthread_exit(NULL);
    }

    void *thread(void *vargp) {
        int myid = (int)vargp;
        static int cnt = 0;
        printf("[%d]: %s (cnt=%d)\n", myid, ptr[myid], ++cnt);
        return NULL;
    }
}