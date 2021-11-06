#include<stdio.h>

extern char __executable_start[];
extern char etext[], _etext[], __etext[];
extern char edata[], _edata[];
extern char end[], _end[];

int main(int argc, char **argv)
{
    printf("Executable Start %X\n", __executable_start);
    printf("Text End %X\n", etext);
    printf("Data End %X\n", edata);
    printf("Excetable End %X\n", end);

    return 0;
}

// ~/Stan/xforg/CodingCPlusPlus/GCCDeping/ELF(main*) » gcc SpecSymbol.c -o SpecSymbol

// /Stan/xforg/CodingCPlusPlus/GCCDeping/ELF(main*) » ./SpecSymbol
// Executable Start A704C000
// Text End A704D255
// Data End A7050010
// Excetable End A7050018
