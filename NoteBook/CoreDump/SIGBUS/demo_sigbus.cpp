#include <iostream>
#include <stdlib.h>

union {
  char a[10];
  int i;
} u;

int main() {
  int* p = (int*)(&(u.a[1]));
  /**
   * p 中未对齐的地址将会引起总线错误,
   * 因为数组和int的联合确保了 a 是按照 int 的 4 字节来对齐的
   * 所以 “a+1” 肯定不是 int 对齐的
   */
  *p = 17;
  printf("%d %p %p %p\n", *p, &(u.a[0]), &(u.a[1]), &(u.i));
  printf("%lu %lu\n", sizeof(char), sizeof(int));

  return 0;
}