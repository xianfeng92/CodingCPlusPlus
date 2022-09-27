#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    printf("hello world (pid=%d)\n", (int)getpid());
    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed");
        exit(1);
    } else if (rc == 0) {
        printf("hello, I am child (pid=%d)\n", (int)getpid());
        char *myargs[3];
        myargs[0] = strdup("wc");
        myargs[1] = strdup("forkDemo.c");
        myargs[2] = NULL;
        execvp(myargs[0], myargs);
        printf("this should not print out\n");
    } else {
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc: %d) (pid: %d)\n", rc, wc, (int)getpid());
    }
    return 0;
}