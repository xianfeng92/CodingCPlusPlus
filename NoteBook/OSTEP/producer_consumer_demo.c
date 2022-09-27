int buffer[MAX];
int fill = 0;
int use = 0;

void put(int value) {
    buffer[fill] = value;
    fill = (fill + 1) % MAX;
}

int get() {
    int tmp = buffer[use];
    use = (use + 1) % MAX;
    return tmp;
}


sem_t empty;
sem_t full;

void *producer(void *arg) {
    int i;
    for( i = 0; i < loops ; i++ ) {
        sem_wait(&empty);
        put(i);
        sem_post(&full);
    }
}

void *consumer(void *arg) {
    int i, tmp = 0;
    while(tmp != -1) {
        sem_wait(&full);
        tmp = get();
        sem_post(&empty);
        printf("%d\n", tmp);
    }
}

int main() {
    //...
    sem_init(&empty, 0, MAX);// MAX can be 1
    sem_init(&full, 0, 0);
    //...
}