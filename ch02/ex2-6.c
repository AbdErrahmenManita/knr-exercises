#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, unsigned int y) {
  unsigned int mask1 = ~(~0 << n) << (p + 1 - n);
  x = x & ~mask1;
  unsigned int mask2 = (y & ~(~0 << n)) << (p + 1 - n);
  x = x | mask2;
  return x;
}

int main() {
  unsigned int x = 0b1011010;
  unsigned int y = 0b10110;
  int n = 3, p = 4;
  printf("%b\n", setbits(x, p, n, y));
  return 0;
}
