#include <stdio.h>

extern int ext;  
int weak1;  
int strong = 1;  
int __attribute__((weak)) weak2 = 2;  
  
int main()  
{  
        printf("%d,%d,%d\n", weak1,strong,weak2);
        return 0;  
} 


// /Stan/xforg/CodingCPlusPlus/GCCDeping/ELF 目标文件是什么/强符号与弱符号(main*) » gcc main1.c other.c -o test                                   parallels@xforg
// --------------------------------------------------------------------------------
// ~/Stan/xforg/CodingCPlusPlus/GCCDeping/ELF 目标文件是什么/强符号与弱符号(main*) » ./test                                                        parallels@xforg
// 0,1,2
