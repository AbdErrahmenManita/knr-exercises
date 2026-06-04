#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main() {
  char s1[] = "happy";
  char s2[] = "drapppapapappaaapaglppa";
  squeeze(s1, s2);
  printf("%s\n", s1);
  return 0;
}
void squeeze(char s1[], char s2[]) {
  int i = 0;
  int c;
  while ((c = s2[i++]) != '\0') {
    int j = 0;
    int curr = 0;
    while (s1[j] != '\0') {
      if (s1[j] != c) {
        s1[curr++] = s1[j];
      }
      j++;
    }
    s1[curr] = '\0';
  }
}
