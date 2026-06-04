#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXOP 100
#define NUMBER '0'
#define MATH_FUNCTION 1
#define ALPHABET 'A'
#define TYPO 2
#define ANS 3
int VAR = 0;
double last_val = 0.0;
int getop(char[]);
void push(double);
double pop(void);
void showTop(void);
void duplicate(void);
void swapTop(void);
void clearStack(void);
void doMath(char);            // calculate math function (sin , cos , exp , pow)
double variables[26] = {0.0}; // hold values of variables
int main() {
  int type;
  double op2;
  char s[MAXOP];
  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER: // captured a number
      push(atof(s));
      break;
    //
    //
    //
    //
    case '+': // addition
      push(pop() + pop());
      break;
    //
    //
    //
    //
    case '*': // multiplication
      push(pop() * pop());
      break;
    //
    //
    //
    //
    case '-': // substraction
      op2 = pop();
      push(pop() - op2);
      break;
    //
    //
    //
    //
    case '/': // division
      op2 = pop();
      if (op2 != 0.0) {
        push(pop() / op2);
      } else {
        printf("Error : zero divisor\n");
      }
      break;
    //
    //
    //
    //
    case '%':
      if ((op2 = pop()) != 0.0) {
        push(fmod(pop(), op2));
      } else {
        printf("Error : zero divisor\n");
      }
      break;
    //
    //
    //
    //
    case '?':
      showTop();
      break;
    case '#':
      duplicate();
      break;
    case '&':
      swapTop();
      break;
    case '$':
      clearStack();
      break;
    //
    //
    //
    //
    case MATH_FUNCTION:
      doMath(s[0]);
      break;
    //
    //
    //
    //
    case '=':
      if (isalpha(VAR)) {
        pop();
        push(variables[VAR - 'A'] = pop());
        VAR = 0;
      } else {
        printf("Error : There is no variable to assign to\n");
      }
      break;
    //
    //
    //
    //
    case ALPHABET:
      push(variables[VAR - 'A']);
      break;
    //
    //
    //
    //
    case TYPO:
      printf("Error : There is a Typo in the Input\n");
      break;
    //
    //
    //
    //
    case ANS:
      push(last_val);
      break;
    //
    //
    //
    //
    case '\n':
      printf("\t%.8g\n", op2 = pop());
      push(op2);
      last_val = op2;
      break;
    default:
      printf("Error : Unknown command %s\n", s);
      break;
    }
  }
  return 0;
}
//
//
//
//
#define MAXVAL 100
int sp;
double val[MAXVAL];
//
//
//
//
//
void showTop() {
  if (sp > 0) {
    printf("Top of the Stack : %g\n", val[sp - 1]);
    return;
  }
  printf("Can't show Top of Stack : Stack is Empty\n");
}
//
//
//
//
//
//
void duplicate() {
  if (sp > 0) {
    double temp = pop();
    push(temp);
    push(temp);
    return;
  }
  printf("Can't Duplicate : Stack is Empty\n");
}
//
//
//
//
void swapTop() {
  if (sp > 1) {
    double temp1 = pop();
    double temp2 = pop();
    push(temp1);
    push(temp2);
    return;
  }
  printf("Can't Swap Top : Not enough Elements\n");
}
//
//
//
//
void clearStack() { sp = 0; }
//
//
//
//
void push(double f) {
  if (sp < MAXVAL) {
    val[sp++] = f;
  } else {
    printf("Stack is Full : Can't push %g\n", f);
  }
  return;
}
//
//
//
//
double pop() {
  if (sp > 0) {
    return val[--sp];
  } else {
    printf("Error : Stack is Empty");
    return 0.0;
  }
}
//
//
//
//
//
int getch();
void ungetch(int);
//
//
//
//
void doMath(char c) {
  switch (c) {
  case 's':
    push(sin(pop()));
    break;
  case 'c':
    push(cos(pop()));
    break;
  case 'e':
    push(exp(pop()));
    break;
  case 'p': {
    double op2 = pop();
    double op1 = pop();
    if (!op2 && !op1) {
      printf("Error : 0 pow 0");
    } else {
      push(pow(op1, op2));
    }
    break;
  }
  }
}

//
//
//
//
int getop(char s[]) {
  int i, c;
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  i = 0;
  if (isalpha(c)) {
    while (isalpha(s[++i] = c = getch()))
      ;
    if (c != EOF) {
      ungetch(c);
    }
    s[i] = '\0';
    if (strcmp(s, "cos") == 0 || strcmp(s, "sin") == 0 ||
        strcmp(s, "exp") == 0 || strcmp(s, "pow") == 0) {
      return MATH_FUNCTION;
    }
    if (strcmp(s, "ANS") == 0) {
      return ANS;
    }
    if (strlen(s) == 1) {
      VAR = s[0];
      return ALPHABET;
    }
    return TYPO;
  }
  if (c == '-') {
    if (isdigit(c = getch())) {
      s[++i] = c;
    } else if (c != EOF) {
      ungetch(c);
      c = s[i];
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
//
//
//
//
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;
//
//
//
//
int getch() { return (bufp > 0) ? buf[--bufp] : getchar(); }
//
//
//
//
//
void ungetch(int c) {
  if (bufp >= BUFSIZE) {
    printf("Ungetch : Too many arguments\n");
  } else {
    buf[bufp++] = c;
  }
}
