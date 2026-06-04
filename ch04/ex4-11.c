#include <ctype.h>
#define NUMBER '0'
int getch();
int getop(char s[]) {
  int i;
  static int c = ' ';
  while (c == ' ' || c == '\t')
    s[0] = c = getch();
  i = 0;
  s[0] = c;
  s[1] = '\0';
  if (!isdigit(c) && c != '.' && c != '-') {
    c = ' ';
    return s[0];
  }
  if (c == '-' && !isdigit(s[++i] = c = getch()) && c != '.') {
    s[1] = '\0';
    return s[0];
  }
  if (isdigit(c))
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  return NUMBER;
}
