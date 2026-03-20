#include <stdio.h>
int main() {
  int c, max;
  max = 0;
  int tab[26] = {0};
  while ((c = getchar()) != EOF) {
    if (c >= 'a' && c <= 'z') {
      ++tab[c - 'a'];
      if (max < tab[c - 'a'])
        max = tab[c - 'a'];
    } else if (c >= 'A' && c <= 'Z') {
      ++tab[c - 'A'];
      if (max < tab[c - 'A'])
        max = tab[c - 'A'];
    }
  }
  int nb = max;
  for (int i = 0; i < nb; i++) {
    for (int j = 0; j < 26; j++) {
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
  for (int i = 0; i < 26; i++) {
    printf("%c ", 'a' + i);
  }
  putchar('\n');
  return 0;
}
