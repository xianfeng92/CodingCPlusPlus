
typedef struct {
    int maxfd;
    fd_set read_set;
    fd_set ready_set;
    int nready;
    int maxi;
    int clientfd[FD_SETSIZE];
    rio_t clientrio[FD_SETSIZE];
} pool;


int byte_cnt = 0;

int main (int argc, char **argv) {
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    static pool pool;

    if( argc != 2) {
        fprintf(stderr, "usage: %s <port> \n", argv[0]);
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]);
    init_pool(listenfd, &pool);

    while(1) {
        pool.ready_set = pool.read_set;
        pool.nready = Select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL);

        if(FD_ISSET(listenfd, &pool.ready_set)) {
            clientlen = sizeof(struct sockaddr_storage);
            connfd = Accept(listenfd,(SA*)&clientaddr, &clientlen);
            add_client(connfd, &pool);
        }

        check_clients(&pool);
    }
}


void init_pool(int listenfd, pool *p) {
    int i;
    p->maxi = -1;
    for(i = 0; i < FD_SETSIZE; i++) {
        p->clientfd[i] = -1;
    }
    p->maxfd = listenfd;
    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);
}

void add_client(int connfd, pool* p) {
    int i;
    p->nready --;
    for(int i 0; i < FD_SETSIZE; i++) {
        if(p-.clientfd[i] < 0) {
            p->clientfd[i] = connfd;
            Rio_readinitb(&p->clientrio[i], connfd);
            FD_SET(connfd, &p->read_set);
            if(connfd > p->maxfd) {
                p->maxfd = connfd;
            }
            if(i > p->maxi){
                p-maxi = i;
            }
            break;
        }
    }
    if(i = FD_SETSIZE) {
        app_error("add client error, too many clients");
    }
}


