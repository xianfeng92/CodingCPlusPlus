#include "minicrt.h"
/* 这部分实现的是字符串相关的操做，主要是包括计算字符串长度、比较两个字符串、整数与字符串之间的转换等，因为这部分无需涉及任何和内核的交互，
是纯粹的用户态的计算。实现较为简单*/
// 将整数 n 转换成字符串存入 str 指向的内存空间 ,radix 为转换时所用基数(保存到字符串中的数据的进制基数)
char *itoa(long n, char *str, long radix)
{
    char digit[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *p = str;
    char *head = str;
    if (!p || radix < 2 || radix > 36)
    {
        return p;
    }

    if (radix != 10 && n < 0)
    {
        return p;
    }

    if (n == 0)// 若是要转换的数字 n 为 0，则直接在输出字符串中直接输出
    {
        *p++ = '0';
        *p = 0;
        return p;
    }

    if (radix == 10 && n < 0)// 若是是 10 进制，且为负数，则先添加负号，而后转正留待后续处理
    {
        *p++ = '-';
        n = -n;
    }

    while (n)
    {
        *p++ = digit[n % radix];
        n /= radix;
    }

    *p = 0;//数字转换完了，末尾添加0
    // 上面的数字字符串是倒序的，这里将数字字符串倒过来
    for (--p; head < p; ++head, --p)
    {
        char temp = *head;
        *head = *p;
        *p = temp;
    }

    return str;
}

long strcmp(const char *src, const char *dst)
{
    long ret = 0;
    unsigned char *p1 = (unsigned char *)src;
    unsigned char *p2 = (unsigned char *)dst;

    while (!(ret = *p1 - *p2) && *p2)
    {
        ++p1, ++p2;
    }
    if (ret < 0)
    {
        ret = -1;
    }
    else if (ret > 0)
    {
        ret = 1;
    }

    return (ret);
}

char * strcpy(char* dest, const char* src)
{
	char* ret	= dest;
	while(*src)
	{
		*dest++ = *src++;
	}
	*dest	= '\0';// 字符串拷贝完后，手动在末尾添加 \0
	return ret;
}

unsigned long strlen(const char *str)
{
    long cnt = 0;
    if (!str)
    {
        return 0;
    }
    for (; *str != '\0'; ++str)
    {
        ++cnt;
    }

    return cnt;
}
