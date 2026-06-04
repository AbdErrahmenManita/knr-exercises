#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void reverse(char s[]) {
  int c, i, j;
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}
void itob(int n, char s[], int b) {
  if (b < 2 || b > 36) {
    printf("Unsupported base !!!");
    exit(1);
  }
  int sign = 0;
  if (n < 0) {
    sign = '-';
  }
  char map[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int i = 0;
  do {
    if (n < 0) {
      s[i++] = (n % b > 0) ? map[b - (n % b)] : map[-(n % b)];
    } else {
      s[i++] = map[n % b];
    }
  } while ((n /= b) != 0);
  if (sign == '-') {
    s[i++] = '-';
  }
  s[i] = '\0';
  reverse(s);
}

int main() {
  int n = INT32_MIN;
  char s[100];
  int b;
  printf("enter the base you want to convert to (2-36) : ");
  scanf("%d", &b);
  itob(n, s, b);
  printf("%s\n", s);
  return 0;
}
