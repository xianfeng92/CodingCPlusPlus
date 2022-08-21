
#include "csapp.h"

void signal_handler(int sig) {
    printf("Caught SIGINT");
    exit(0);
}

int main(int argc, char **argv) {

    if(signal(SIGINT, signal_handler) == SIG_ERR) {
        unix_error("signal error");
    }
    Pause();

    return 0;
}