#include <stdio.h>
#define TABSTOP 8
void detab(void);
int main() {
  detab();
  return 0;
}
void detab(void) {
  int c;
  int count = 0;
  while ((c = getchar()) != EOF) {
    if(c=='\n'){
        putchar('\n');
        count=0;
    }
    else if (c == '\t') {
      int tab = TABSTOP - (count % TABSTOP);
      for (int i = 0; i < tab; ++i) {
        putchar(' ');
      }
      count=count+tab;
    } else {
      putchar(c);
      ++count;
    }
  }
}
