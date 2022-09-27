

typedef struct _Zem_t {
    int value;
    pthread_cond_t cond;
    pthread_mutex_t lock;
} Zem_t;

// only one thread can call this function
void Zem_init(Zem_t *s, int value) {
    s->value = value;
    cond_init(&s->cond);
    mutex_init(&s->lock);
}

void Zem_wait(Zem_t *s) {
    mutex_lock(&s->lock);
    while (s->value <= 0 ){
        cond_wait(&s->cond, &s->lock);
    }
    s->value --;
    mutex_unlock(&s->lock);
}

void Zem_post(Zem_t *s) {
    mutex_lock(&s->lock);
    s->value ++;
    cond_signal(&s->cond);
    mutex_unlock(&s->lock);
}




