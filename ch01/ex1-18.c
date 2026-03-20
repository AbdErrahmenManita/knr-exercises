#include <stdio.h>
#define MAXLINE 1000
int get_line(char s[], int lim);
int main() {
  int len;
  char line[MAXLINE];
  while ((len = get_line(line, MAXLINE)) > 0) {
    if (len > 1)
      printf("%s", line);
  }
  return 0;
}
int get_line(char s[], int lim) {
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    s[i] = c;
  }
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  if (i > 1) {
    int nb = i - 1;
    while (s[nb] == '\n' || s[nb] == '\t' || s[nb] == ' ') {
      --nb;
    }
    s[nb + 1] = '\n';
    s[nb + 2] = '\0';
  }
  return i;
}
