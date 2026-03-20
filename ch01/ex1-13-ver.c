#include <stdio.h>
int main() {
  int c, nb, max;
  int tab[20] = {0};
  int prev = ' ';
  nb = max = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\t' || c == '\n') {
      if (prev != ' ' && prev != '\t' && prev != '\n') {
        ++tab[nb];
        if (max < tab[nb])
          max = tab[nb];
        nb = 0;
        putchar('\n');
      }
    } else {
      putchar(c);
      ++nb;
    }
    prev = c;
  }
  nb = max;
  for (int i = 0; i < nb; i++) {
    for (int j = 1; j < 20; j++) {
      if (tab[j] == max) {
        printf("* ");
        --tab[j];
      } else {
        printf("  ");
      }
    }
    putchar('\n');
    --max;
  }
  for (int i = 1; i <= 20; i++) {
    printf("%d ", i);
  }
  putchar('\n');
  return 0;
}
