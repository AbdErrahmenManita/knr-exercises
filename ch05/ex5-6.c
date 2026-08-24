#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getLine(char *s, int lim) {
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++, s++) {
    *s = c;
  }
  if (c == '\n') {
    *s = '\n';
    s++;
  }
  *s = '\0';
  return i;
}

// chap2 version
int my_atoi_v1(char *s) {
  int n;
  for (n = 0; *s >= '0' && *s <= '9'; s++) {
    n = n * 10 + (*s - '0');
  }
  return n;
}

// chap3 version
int my_atoi_v2(char *s) {
  int n, i;
  n = 0;
  while (isspace(*s))
    s++;
  int sign = (*s == '-') ? -1 : 1;
  if (*s == '-' || *s == '+') {
    s++;
  }
  while (isdigit(s)) {
    n = n * 10 + (*s - '0');
    s++;
  }
  return n;
}
// version 1
void my_reverse_v1(char *s) {
  size_t j = strlen(s) - 1;
  int i = 0;
  while (i < j) {
    int c = *(s + i);
    *(s + i) = *(s + j);
    *(s + j) = c;
    i++;
    j--;
  }
}
// version 2

void my_reverse_v2(char *start) {
  char *end = start;
  while (start < end) {
    char c = *start;
    *start = *end;
    *end = c;
    start++;
    end--;
  }
}
// chap3 version (flawed one)
void my_itoa_v1(char *s, int n) {
  int i, sign;
  sign = (n < 0) ? -1 : 1;
  if (sign < 0)
    n = -n;
  do {
    *(s + i) = n % 10 + '0';
    i++;
  } while ((n /= 10) > 0);
  if (sign < 0) {
    *(s + i) = '-';
    i++;
  }
  *(s + i) = '\0';
  my_reverse_v1(s);
}

// chap3 version (fixed one)
void my_itoa_v2(char *s, int n) {
  int i, sign;
  sign = (n < 0) ? -1 : 1;
  do {
    char diff = n - ((n / 10) * 10);
    *(s + i) = (diff >= 0) ? diff + '0' : -diff + '0';
    i++;
  } while ((n /= 10) > 0);
  if (sign < 0) {
    *(s + i) = '-';
    i++;
  }
  *(s + i) = '\0';
  my_reverse_v1(s);
}

// chap3 version (untill b=36)
void my_itob_v1(char *s, int n, int b) {
  if (b > 36) {
    printf("Sorry we can support this now try later...(Maybe ;)\n");
    exit(1);
  }
  int sign = (n < 0) ? -1 : 1;
  int i = 0;
  do {
    char diff = n - ((n / b) * b);
    *(s + i) = (diff >= 0) ? diff + '0' : -diff + '0';
    i++;
  } while ((n /= b) > 0);
  if (sign < 0) {
    *(s + i) = '-';
    i++;
  }
  *(s + i) = '\0';
  my_reverse_v1(s);
}

// chap3 version
double my_atof_v1(char *s) {
  double val, power;
  while (isspace(*s)) {
    s++;
  }
  int sign = (*s == '-') ? -1 : 1;
  for (val = 0.0; isdigit(*s); s++) {
    val = val * 10 + (*s - '0');
  }
  if (*s == '.')
    s++;
  for (power = 1.0; isdigit(*s); s++) {
    val = val * 10.0 + (*s - '0');
    power *= 10;
  }
  return sign * val / power;
}

// chap4 version
int my_strindex(char *s, char *t) {
  int i = 0, j = 0;
  while (*(s + i) != '\0') {
    i++;
  }
  while (*(t + j) != '\0') {
    j++;
  }
  if (j > i) {
    return -1;
  }
  while (j > 0) {
    if (*(t + j - 1) != *(s + i - 1))
      return -1;
    j--;
    i--;
  }
  return i;
}

// chap4 version
int getch(void);
void ungetch(int);
#define MATH_FUNCTION 1;
#define ANS 2;
#define ALPHABET 3;
#define TYPO 4;
#define NUMBER 5;
int VAR;
int getop(char *s) {
  int i, c;
  while ((*s = c = getch()) == ' ' || c == '\t')
    ;
  s++;
  *s = '\0';
  i = 0;
  if (isalpha(c)) {
    while (isalpha(*s = c = getch()))
      s++;
    if (c != EOF) {
      ungetch(c);
    }
    *s = '\0';
    if (strcmp(s, "cos") == 0 || strcmp(s, "sin") == 0 ||
        strcmp(s, "exp") == 0 || strcmp(s, "pow") == 0) {
      return MATH_FUNCTION;
    }
    if (strcmp(s, "ANS") == 0) {
      return ANS;
    }
    if (strlen(s) == 1) {
      VAR = *(s - 1);
      return ALPHABET;
    }
    return TYPO;
  }
  if (c == '-') {
    if (isdigit(c = getch())) {
      s++;
      *s = c;
    } else if (c != EOF) {
      ungetch(c);
      c = *s;
    }
  }
  if (!isdigit(c) && c != '.') {
    return c;
  }
  if (isdigit(c)) {
    s++;
    while (isdigit(*s = c = getch()))
      s++;
  }
  if (c == '.') {
    s++;
    while (isdigit(*s = c = getch()))
      s++;
  }
  *s = '\0';
  if (c != EOF) {
    ungetch(c);
  }
  return NUMBER;
}

int main() {
  char s[] = "hello";
  char t[] = "hello";
  printf("%d\n", my_strindex(s, t));
  return 0;
}
