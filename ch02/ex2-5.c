#include <stdio.h>

int any(char s1[], char s2[]) {
  int i = 0;
  int c;
  while (s1[i] != '\0') {
    int j = 0;
    while (s2[j] != '\0') {
      if (s1[i] == s2[j])
        return i + 1;
      j++;
    }
    i++;
  }
  return -1;
}

int main() {
  char s1[] = "hello";
  char s2[] = "my_friend";
  printf("%d\n", any(s1, s2));
  return 0;
}
