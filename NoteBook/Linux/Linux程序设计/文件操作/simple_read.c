#include <unistd.h>
#include <stdlib.h>

int main()
{
    char buf[128];
    int nread;
    nread = read(0, buf, 128);
    if(nread == -1)
    {
        write(2,"A read error occured\n",26);
    }
    if(write(1,buf,nread) != nread)
    {
        write(2,"A write error occured\n",27);
    }
    exit(0);
}