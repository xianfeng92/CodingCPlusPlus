#ifndef NOTEBOOK_CSAPP_SBUF_H
#define NOTEBOOK_CSAPP_SBUF_H

typedef struct {
    int *buf;
    int n;
    int front;
    int rear;
    sem_t mutex;
    sem_t slots;
    sem_t items;
} sbuf_t;

#endif // NOTEBOOK_CSAPP_SBUF_H
