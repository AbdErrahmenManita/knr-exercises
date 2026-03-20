#include <stdio.h>
#define MAXLINE 1000
int get_line(char s[], int lim);
void reverse(char s[]);
int main() {
  int len;
  char line[MAXLINE];
  while ((len = get_line(line, MAXLINE)) > 0) {
    if (len > 2)
      reverse(line);
    if (line[len - 1] == '\n')
      printf("%s", line);
    else
      printf("%s\n", line);
  }
  return 0;
}
int get_line(char s[], int lim) {
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    s[i] = c;
  }
  if (c == '\n') {
    s[i] = '\n';
    ++i;
  }
  s[i] = '\0';
  return i;
}
void reverse(char s[]) {
  int i = 0;
  while (s[i] != '\n' && s[i] != '\0') {
    ++i;
  }
  int len = i;
  for (i = 0; i < len / 2; i++) {
    int c = s[i];
    s[i] = s[len - i - 1];
    s[len - i - 1] = c;
  }
}
