#include <stdio.h>
#define MAXLINE 1000

int get_line(char s[], int lim);
void copy(char to[], char from[]);
int main() {
  int len, max;
  char line[MAXLINE];
  char longest[MAXLINE];
  max = 0;
  while ((len = get_line(line, MAXLINE)) > 0) {
    if (len > max) {
      max = len;
      copy(longest, line);
    }
  }
  if (max > 0) {
    printf("%s\n", longest);
    printf("max= %d\n", max);
  }
  return 0;
}
int get_line(char s[], int lim) {
  int i = 0;
  int c;
  while ((c = getchar()) != EOF && c != '\n') {
    if (i < lim - 1)
      s[i] = c;
    ++i;
  }
  if (i < lim - 1 && c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}
void copy(char to[], char from[]) {
  int i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}
