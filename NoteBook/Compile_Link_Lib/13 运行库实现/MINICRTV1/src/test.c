#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char **argv) {
    char buf[128] = {0};
    FILE * fpw  = fopen("test.txt", "w");
    char **v  = (char **)malloc(argc * sizeof(char *));
    for (int i = 0; i < argc; i++) {
        v[i] = (char *)malloc(strlen(argv[i]) + 1);
        strcpy(v[i], argv[i]);
    }

    for (int i = 0; i < argc; i++) {
        fprintf(fpw, "%s\t", v[i]);
    }
    fclose(fpw);

    FILE *fpr = fopen("test.txt", "r");
    int   len = 128;
    fread(buf, len, 1, fpr);
    printf("%s\n", buf);
    fclose(fpr);
}