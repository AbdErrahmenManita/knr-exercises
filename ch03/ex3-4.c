#include <stdint.h>
#include <stdio.h>
#include <string.h>
void reverse(char s[]) {
  int c, i, j;
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}
void itoa(int n, char s[]) {
  int len = sizeof(n) * 8;
  int sign;
  if (n < 0) {
    sign = '-';
  }
  int i = 0;
  do {
    if (n < 0) {
      s[i++] = (n % 10 > 0) ? 10 - (n % 10) + '0' : -(n % 10) + '0';
    } else {
      s[i++] = n % 10 + '0';
    }
  } while ((n /= 10) != 0);
  if (sign == '-') {
    s[i++] = '-';
  }
  s[i] = '\0';
  reverse(s);
}
int main() {
  char s[1000];
  int n = INT32_MIN;
  itoa(n, s);
  printf("%s\n", s);
  return 0;
}
