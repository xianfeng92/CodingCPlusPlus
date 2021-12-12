#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    char BUF[1024];
    int in, out;
    int nread;
    in = open("file.txt", O_RDONLY);
    out = open("fileout.txt", O_WRONLY|O_CREAT,S_IRUSR|S_IWGRP);
    while((nread = read(in,BUF,1024)) > 0) 
    {
        write(out,BUF,nread);
    }
    exit(0);
}