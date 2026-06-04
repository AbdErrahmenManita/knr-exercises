#include <stdio.h>
#define MAXLINE 1000
void escape(char s[], char t[]) {
  int i = 0, j = 0;
  int c;
  while ((c = t[i]) != '\0' && j < MAXLINE - 1) {
    switch (c) {
    case '\n':
      if (j < MAXLINE - 2) {
        s[j++] = '\\';
        s[j++] = 'n';
      }
      break;
    case '\t':
      if (j < MAXLINE - 2) {
        s[j++] = '\\';
        s[j++] = 't';
      }
      break;
    default:
      s[j++] = t[i];
    }
    i++;
  }
  s[j] = '\0';
}
void getlinee(char t[]) {
  int c;
  int i;
  for (i = 0; i < MAXLINE && (c = getchar()) != EOF; i++) {
    t[i] = c;
  }
  t[i] = '\0';
}
int main() {
  char s[MAXLINE];
  char t[MAXLINE];
  getlinee(t);
  printf("t : %s\n", t);
  escape(s, t);
  printf("s : %s\n", s);
  return 0;
}
