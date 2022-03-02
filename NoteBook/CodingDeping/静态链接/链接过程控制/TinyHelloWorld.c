
char * str = "Hello world!\n";
void print(void)
{
    asm("movl $13,%%edx \n"
        "movl %0,%%ecx \n"
        "movl $0,%%ebx \n"
        "movl $4,%%eax \n"
        "int $0x80 \n" ::"r"(str)
        : "edx", "ecx", "ebx");
}
void exit(void)
{
    asm("movl $42,%ebx \n"
        "movl $1, %eax \n"
        "int $0x80 \n");
}
void nomain(void)
{
    print();
    exit();
}