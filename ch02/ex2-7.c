#include <stdio.h>
unsigned int invert(unsigned int x, int p, int n) {
  int mask = ~(~0 << n) << (p + 1 - n);
  x = x ^ mask;
  return x;
}
int main() {
  unsigned int x = 0b1011011010011;
  int n = 4, p = 5;
  printf("%b", invert(x, p, n));
  return 0;
}
