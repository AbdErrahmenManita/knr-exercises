#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXOP 100
#define NUMBER '0'
int getop(char[]);
void push(double);
double pop(void);
void showTop();
void duplicate();
void swapTop();
void clearStack();

int main() {
  int type;
  double op2;
  char s[MAXOP];
  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0) {
        push(pop() / op2);
      } else {
        printf("Error : zero divisor\n");
      }
      break;
    case '%':
      if ((op2 = pop()) != 0.0) {
        push(fmod(pop(), op2));
      } else {
        printf("Error : zero divisor\n");
      }
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("Error : Unknown command %s\n", s);
      break;
    }
  }
  return 0;
}
#define MAXVAL 100
int sp;
double val[MAXVAL];

void push(double f) {
  if (sp < MAXVAL) {
    val[sp++] = f;
  } else {
    printf("Stack is Full : Can't push %g\n", f);
  }
  return;
}
double pop() {
  if (sp > 0) {
    return val[sp--];
  } else {
    printf("Error : Stack is Empty");
    return 0.0;
  }
}
int getch();
void ungetch(int);
int getop(char s[]) {
  int i, c;
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  i = 0;
  if (c == '-') {
    if (!isdigit(s[++i] = c = getch()) && c != '.') {
      ungetch(c);
      c = s[--i];
      s[1] = '\0';
    }
  }
  if (!isdigit(c) && c != '.') {
    return c;
  }
  if (isdigit(c)) {
    while (isdigit(s[++i] = c = getch()))
      ;
  }
  if (c == '.') {
    while (isdigit(s[++i] = c = getch()))
      ;
  }
  s[i] = '\0';
  if (c != EOF) {
    ungetch(c);
  }
  return NUMBER;
}
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;
int getch() { return (bufp > 0) ? buf[--bufp] : getchar(); }
void ungetch(int c) {
  if (bufp >= BUFSIZE) {
    printf("Ungetch : Too many arguments\n");
  } else {
    buf[bufp++] = c;
  }
}
