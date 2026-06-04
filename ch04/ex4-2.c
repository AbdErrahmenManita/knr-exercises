#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
double calculate_exp(char s[], int n) {
  double exp = 1.0;
  int i, power = 0;
  if (s[n] == '-' || s[n] == '+')
    n++;
  for (i = n; isdigit(s[i]); i++) {
    power = power * 10 + (s[i] - '0');
  }
  if (s[i] == '.' || power == 0) {
    printf("Wrong Format !!!\n");
    exit(1);
  }
  while (power--) {
    exp *= 10;
  }
  return exp;
}
double atof_me(char s[]) {
  double exp = 1.0, val, power;
  int i = 0, sign = 1;
  for (i = 0; isspace(s[i]); i++)
    ;
  if (s[i] == '-') {
    sign = -1;
  }
  for (val = 0.0; isdigit(s[i]); i++) {
    val = val * 10 + (s[i] - '0');
  }
  if (s[i] == '.') {
    i++;
  }
  for (power = 1.0; isdigit(s[i]); i++) {
    val = val * 10 + (s[i] - '0');
    power *= 10;
  }
  if (s[i] == 'e' || s[i] == 'E') {
    i++;
    exp = calculate_exp(s, i);
  }
  if (s[i] == '-')
    return sign * val / power / exp;
  return sign * val / power * exp;
}

int main() {
  char s[] = "123.543452435212e-6";
  printf("%.15g\n", atof_me(s));
  return 0;
}
