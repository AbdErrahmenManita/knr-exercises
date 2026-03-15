#include <stdio.h>
int main() {
  int c;
  int d = ' ';
  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\t' || c == '\n') {
      if (d != ' ' && d != '\t' && d != '\n') {
        putchar('\n');
      }
    } else {
      putchar(c);
    }
    d = c;
  }
  return 0;
}
