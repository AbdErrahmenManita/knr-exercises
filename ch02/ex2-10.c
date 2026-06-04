#include <stdio.h>
void lower(char s[]) {
  int i = 0;
  while (s[i] != '\0') {
    s[i] = ('A' <= s[i] && s[i] <= 'Z') ? s[i] + ('a' - 'A') : s[i];
    i++;
  }
  return;
}
int main() {
  char s[] = "abskAGEjkhs5_ç125ffsuak1AZJAG";
  lower(s);
  printf("%s\n", s);
  return 0;
}
