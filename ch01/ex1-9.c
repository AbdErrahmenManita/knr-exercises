#include <stdio.h>
int main() {
  int c;
  int d;
  d = getchar();
  putchar(d);
  while ((c = getchar()) != EOF) {
    if (d != ' ' || c != ' ')
      putchar(c);
    d = c;
  }
  return 0;
}
