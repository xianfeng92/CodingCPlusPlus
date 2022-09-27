
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    int rc = fork();
    if(rc < 0 ) {
        fprintf(stderr, "fork failed: %d\n", rc);
        exit(1);
    } else if(rc == 0) {
        close(STDOUT_FILENO);
        open("redirectDemo.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

        // now exec "wc"
        char *myargs[3];
        myargs[0] = strdup("wc");
        myargs[1] = strdup("RedirectDemo.c");
        myargs[2] = NULL;

        execvp(myargs[0], myargs);
    } else {
        int wc = wait(NULL);
    }
    return 0;
}