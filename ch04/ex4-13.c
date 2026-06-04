#include <stdio.h>
#include <string.h>
static int end;
void reverse(char[]);
int main() {
  char s[] = "HELLo My FrIend\t";
  end = strlen(s) - 1;
  reverse(s);
  printf("%s\n", s);
  return 0;
}
void reverse(char s[]) {
  static int start = 0;
  if (start < end) {
    int c = s[start];
    s[start] = s[end];
    s[end] = c;
    start++;
    end--;
    reverse(s);
  }
  return;
}
