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
void itoa(int n, char s[], int min_size) {
  int len = sizeof(n) * 8;
  int sign;
  if (n < 0) {
    sign = '-';
  }
  int i = 0;
  do {
    if (n < 0) {
      s[i++] = (n % 10 > 0) ? '0' + 10 - (n % 10) : '0' - (n % 10);
    } else {
      s[i++] = '0' + n % 10;
    }
  } while ((n /= 10) != 0);
  if (sign == '-') {
    s[i++] = '-';
  }
  while (i <= min_size) {
    s[i++] = ' ';
  }
  s[i] = '\0';
  reverse(s);
}
int main() {
  char s[1000];
  int n = INT32_MIN;
  int min_size;
  printf("Enter the string minimum size : ");
  scanf("%d", &min_size);
  itoa(n, s, min_size);
  printf("%s\n", s);
  return 0;
}
