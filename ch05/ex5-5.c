#include <stdio.h>

void my_strncpy(char *s, char *t, int n) {
  while (n-- != 0) {
    *s++ = (*t) ? *t++ : '\0';
  }
}

void my_strncat(char *s, char *t, int n) {
  while (*s != '\0') {
    s++;
  }
  while (n-- > 0 && *t != '\0') {
    *s = *t;
    s++;
    t++;
  }
  *s = '\0';
}

int my_strncmp(char *s, char *t, int n) {
  unsigned char *s1 = (unsigned char *)s;
  unsigned char *t1 = (unsigned char *)t;
  while (n > 0) {
    if (*s1 != *t1) {
      return *s1 - *t1;
    }
    if (*s1 == '\0') {
      return 0;
    }
    s1++;
    t1++;
    n--;
  }
  return 0;
}

int main() {

  char s[] = "Hello";
  char t[] = "hello";
  // int n;
  // scanf("%d", &n);
  //  my_strncat(s, t, n);
  //  printf("%s\n", s);
  //  printf("%s\n", t);
  printf("%d\n", my_strncmp(s, t, 6));
  return 0;
}
