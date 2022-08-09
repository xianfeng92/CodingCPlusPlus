void echo(int connfd);

void sigchld_handler(int sig) {
    while(waitpid(-1, 0, WNOHANG) > 0) {
        ;
    }
    return;
}

int main(int argc, char **argv) {
    int listenfd, connfd;
    socketlen_t clientlen;
    struct sockaddr_storage clientaddr;

    if(argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    Signal(SIGCHLD, sigchld_handler);
    listenfd = Open_listenfd(argv[1]);
    while(1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA*)&clientaddr, &clientlen);
        if(Fork() == 0) {
            Close(listenfd);// child close its listening socket
            echo(connfd);// child services client
            Close(connfd);// child close connection with client
            exit(0);
        }
        Close(connfd);// parent close connected socket
    }
}