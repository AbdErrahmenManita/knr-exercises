#include <stdio.h>
unsigned int rightrot(unsigned int x, int n) {
  int size = sizeof(x) * 8;
  n = n % size;
  if (!n)
    return x;
  unsigned int half1 = (x & ~(~0 << n)) << (size - n);
  unsigned int half2 = x >> n;
  return half1 | half2;
}
int main() {
  unsigned int x = 0b1101;
  printf("%b\n", rightrot(x, 2));
  return 0;
}
