
#include "csapp.h"

int main() {
    pid_t pid;

    if((pid = fork()) == 0) {
        Pause();
        printf("control should never reach here");
        exit(0);
    }
    kill(pid, SIGKILL);
    exit(0);
}



