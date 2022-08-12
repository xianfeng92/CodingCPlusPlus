
void rio_readinitb(rio_t *rp, int fd);

ssize_t rio_readn(int fd, void *usrbuf, size_t n) {
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;
    while (nleft > 0) {
        if(nread = read(fd, bufp, nleft) < 0) {
            if(error == EINTR) {
                nread = 0;
            } else {
                return -1;
            }
        }else if(nread == 0) {
            break;
        }
        nleft -= nread;
        bufp += nread;
    }
    return n - nleft;
}


ssize_t rio_writen(int fd, void *usrbuf, size_t n) {
    size_t nleft = n;
    ssize_t nwritten;
    char *bufp = usrbuf;

    while(nleft > 0){
        if(nwritten = write(fd, bufp, nleft) <= 0) {
            if(error == EINTR){
                nwritten = 0;
            }else {
                return -1;
            }
        }
        nleft -= nwritten;
        bufp += nwritten;
    }
    return n;
}


int main(int argc, char **argv){
    int n;
    rio_t rio;
    char buf[MAXLINE];

    rio_readinitb(&rio, STDIN_FILENO);
    
    while((n = rio_readlineb(&rio, buf, MAXLINE)) != 0){
        rio_writen(STDOUT_FILENO, buf, n);
    }
}

#define RIO_BUFSIZE 8192

typedef struct {
    int rio_fd;
    int rio_cnt;
    char *rio_bufptr;
    char rio_buf[RIO_BUFSIZE];
} rio_t;


void rio_readinitb(rio_t *rp, int fd) {
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}


static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n) {
    int cnt;
    while (rp->rio_cnt <= n) {// refill if buf is empty
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));
        if(rp->rio_cnt < 0) {
            if(error != EINTR) {
                return -1;
            } 
        }else if(rp->rio_cnt == 0) {// EOF
                return 0;
        } else {
                rp->rio_bufptr = rp->rio_buf;//Reset buf pointer
        }
    }
    cnt = n;
    if(rp->rio_cnt < n) {
       cnt = rp->rio_cnt;
    }
    memcpy(usrbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
    }


static rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen) {
    int n, rc;
    char c, *buf = usrbuf;

    for(n = 1; n < maxlen; n++) {
        if((rc = rio_read(rp, &c, 1) == 1)){
            *buf++ = c;
            if(c == '\n'){
                n++;
                break;
            }
        } else if( rc == 0 ){
            if(n == 1){
                return 0;
            }else {
                break;
            }
        } else {
            return -1;
        }
    }

    *bufp = '\0';
    return n - 1;
}


ssize_t rio_readn(rio_t *rp, void *usrbuf, size_t n) {
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while (nleft > 0){
        if((nread = rio_readn(rp, bufp, nleft)) < 0) {
            return -1;
        }else if(nread == 0) {
            break;
        }
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
}