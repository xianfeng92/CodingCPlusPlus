
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