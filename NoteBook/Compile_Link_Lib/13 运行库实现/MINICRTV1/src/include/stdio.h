#ifndef __STDIO_H__
#define __STDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

typedef int FILE;
#define EOF (-1)

#ifdef WIN32
#define stdin ((FILE *)(GetStdHandle(STD_INPUT_HANDLE)))
#define stdout ((FILE *)(GetStdHandle(STD_OUTPUT_HANDLE)))
#define stderr ((FILE *)(GetStdHandle(STD_ERROR_HANDLE)))
#else
#define stdin ((FILE *)0)
#define stdout ((FILE *)1)
#define stderr ((FILE *)2)
#endif

FILE *  fopen(const char *filename, const char *mode);
int64_t fread(void *buffer, uint64_t size, uint64_t count, FILE *stream);
int64_t fwrite(const void *buffer, uint64_t size, uint64_t count, FILE *stream);
int64_t fclose(FILE *fp);
int64_t fseek(FILE *fp, uint64_t offest, int set);

int fputc(int c, FILE *stream);
int fputs(const char *str, FILE *stream);
int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif /* __STDIO_H__ */
