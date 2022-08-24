#ifndef NOTEBOOK_CSAPP_INTERPOSE_MALLOC_H
#define NOTEBOOK_CSAPP_INTERPOSE_MALLOC_H

#define malloc(size) mymalloc(size)
#define free(size) myfree(size)

void *mymalloc(size_t size);
void *myfree(void *ptr);

#endif // NOTEBOOK_CSAPP_INTERPOSE_MALLOC_H
