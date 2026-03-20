#include <stdio.h>
int main() {
  int c;
  int nb = 0;
  int prev = ' ';
  while ((c = getchar()) != EOF) {
    if (c == '\t' || c == '\n' || c == ' ') {
      if (prev != ' ' && prev != '\t' && prev != '\n') {
        printf(" : %d -> ", nb);
        for (int i = 0; i < nb; i++) {
          printf("*");
        }
        nb = 0;
        putchar('\n');
      }
    } else {
      putchar(c);
      ++nb;
    }
    prev = c;
  }
  return 0;
}
