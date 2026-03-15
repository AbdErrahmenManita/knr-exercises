#include <stdio.h>
#define IN 1
#define OUT 0
int main() {
  int c, nl, nw, nc, state;
  state = OUT;
  nl = nw = nc = 0;
  while ((c = getchar()) != EOF) {
    ++nc;
    if (c == '\n') {
      ++nl;
    }
    if (c == ' ' || c == '\n' || c = '\t') {
      /*  ➜  ~ nvim ex1-11.c
          ➜  ~ cc ex1-11.c -o ex1-11
          ex1-11.c: In function ‘main’:
          ex1-11.c:13:36: error: lvalue required as left operand of assignment
          13 |     if (c == ' ' || c == '\n' || c = '\t') {
          |                                    ^
          ➜  ~
      */
      state = OUT;
    } else if (state == OUT) {
      state = IN;
      nw;
    }
  }
  printf("%d %d %d\n", nl, nw, nc);
  return 0;
}
