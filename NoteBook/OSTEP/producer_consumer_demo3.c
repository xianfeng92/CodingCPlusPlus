
sem_t empty;
sem_t full;
sem_t mutex;


void *producer(void *arg) {
    int i;
    for( i = 0; i < loops; i++ ) {
        sem_wait(&empty);
        sem_wait(&mutex);
        put(i);
        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg) {
    int i;
    for( i = 0; i < loops; i++ ) {
        sem_wait(&full);
        sem_wait(&mutex);
        int tmp = get();
        sem_post(&mutex);
        sem_post(&empty);
        printf("%d\n", tmp);
    }
}

int main(int argc, char **argv) {
    //...
    sem_init(&empty, 0 , MAX);
    sem_init(&full, 0 , 0);
    sem_init(&mutex, 0, 1);
    //...
}

