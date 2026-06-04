#include <limits.h>
#include <stdint.h>
#include <stdio.h>
int i = 0;
void atoi(long int n, char s[]) {
  if (n / 10)
    atoi(n / 10, s);
  if (n < 0) {
    if (i == 0)
      s[i++] = '-';
    s[i++] = (n % 10 <= 0) ? (-(n % 10)) + '0' : 10 - (n % 10) + '0';
  } else {
    s[i++] = n % 10 + '0';
  }
  s[i] = '\0';
  return;
}
int main() {
  int n;
  scanf("%d", &n);
  char s[100];
  atoi(n, s);
  printf("s : %s\n", s);
  return 0;
}
