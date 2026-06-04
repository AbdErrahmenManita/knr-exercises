#include <stdio.h>
#define MAXLINE 1000
void expand(char s1[], char s2[]) {
  int i = 0, j = 0;
  while (s1[i] != '\0' && j < MAXLINE - 1) {
    if (i > 0 && s1[i] == '-' && s1[i - 1] != ' ' && s1[i + 1] != ' ' &&
        s1[i + 1] != '\0') {
      if (s1[i - 1] < s1[i + 1]) {
        for (int c = s1[i - 1] + 1; c <= s1[i + 1] && j < MAXLINE - 1; c++) {
          s2[j++] = c;
        }
      } else if (s1[i - 1] > s1[i + 1]) {
        for (int c = s1[i - 1] - 1; c >= s1[i + 1] && j < MAXLINE - 1; c--) {
          s2[j++] = c;
        }
      }
      i++;
    } else {
      s2[j++] = s1[i];
    }
    i++;
  }
  s2[j] = '\0';
}

int main() {
  char s1[] = "Hello my -a friend how a-z9-0 are a-a you z-";
  char s2[MAXLINE];
  expand(s1, s2);
  printf("%s\n", s2);
  return 0;
}
