
#include "csapp.h"

#define MAXARGS 128

void eval(char *cmdline);
int parseline(char *buf, char **argv);
int buildin_command(char **argv);

int main (int argc, char **argv) {
    char cmdline[MAXARGS];

    while (1) {
        printf(">");
        Fgets(cmdline, MAXARGS, stdin);
        if(feof(stdin)){
            exit(0);
       }
       eval(cmdline);
    }
}

void eval(char *cmdline) {
    char **argv[MAXARGS];
    char buf[MAXLINE];
    int bg;
    pid_t pid;

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);

    if(argv[0] == NULL) {
        return;
    }

    if(!buildin_command(argv)){
        if((pid = Fork()) == 0) {// child run user job
            if(execve(argv[0], argv, environ) < 0) {
                printf("%s :Command not found\n", argv[0]);
                exit(0);
            }
        }
        if(!bg){
            int status;
            if(waitpid(pid, &status, 0) < 0){
                unix_error("waitpid failed");
            }
        } else {
            printf("%d %s", pid, cmdline);
        }
    }
    return;
}

int buildin_command(char **argv) {
    if(!strcmp(argv[0], "quit") {
        exit(0);
    }
    if(!strcmp(argv[0], "&") {
        return 1;
    }
    return 0;
}


int parseline(char *buf, char *argv[]) {
    char *delim;
    int argc;
    int bg;

    buf[strlen(buf)-1] = ' ';
    
    while( *buf && (*buf == ' ')) {// Ignore leading spaces
        buf++;
    }

    argc = 0;
    while ((delim = strchr(buf, ' '))) {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && *buf == ' ') {// Ignore spaces
            buf++;
        }
    }
    argv[argc] = NULL;

    if(argc == 0) {
        return 0;
    }

    if((bg = (*argv[argc -1] == '&')) != 0) {
        argv[--argc] = NULL;
    }
    return bg;
}