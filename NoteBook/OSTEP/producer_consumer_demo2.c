
sem_t empty;
sem_t full;
sem_t mutex;


void *producer(void *arg) {
    int i;
    for( i = 0; i < loops; i++ ) {
        sem_wait(&mutex);
        sem_wait(&empty);
        put(i);
        sem_post(&full);
        sem_post(&mutex);
    }
}

void *consumer(void *arg) {
    int i;
    for( i = 0; i < loops; i++ ) {
        sem_wait(&mutex);
        sem_wait(&full);
        int tmp = get();
        sem_post(&empty);
        sem_post(&mutex);
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

