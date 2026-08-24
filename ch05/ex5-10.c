#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMBER 1
#define TYPO -1
static int stack[100] = {0};
static int sp = 0;

int pop();
void push(int);
int my_getop(char *s, int *);
int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("ERROR : no expression provided");
        exit(1);
    }
    int val = 0;
    int op2;
    while (--argc > 0) {
        char c = my_getop(*++argv, &val);
        switch (c) {
        case NUMBER:
            printf("%d\n", val);
            push(val);
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '+':
            printf("+\n");
            int res1 = pop() + pop();
            push(res1);
            printf("+%d\n", res1);
            break;
        case '*':

            printf("*\n");
            int res2 = pop() * pop();
            push(res2);
            printf("*%d\n", res2);
            break;
        case '/':
            op2 = pop();
            if (op2 == 0) {
                printf("ERROR: can't divide by 0 !!!");
                exit(1);
            }
            push(pop() / op2);
            break;
        case TYPO:
            printf("There is a Typo!!! Please Verify your formula");
            exit(1);
        default:
            printf("Unsupported Math Operation!!!");
            exit(1);
        }
    }
    if (sp == 1) {
        printf("The result is : %d\n", pop());
    } else {
        printf("Malformed expression (too many opearnd)\n");
    }
    return 0;
}

int my_getop(char *arg, int *val) {
    if (!isdigit((unsigned char)*arg) && strlen(arg) == 1) {
        return *arg;
    }
    int sign = (*arg == '-') ? -1 : 1;
    if (*arg == '-' || *arg == '+') {
        arg++;
    }
    *val = 0;
    while (*arg) {
        if (!isdigit(*arg)) {
            return TYPO;
        }
        *val = *val * 10 + (*arg - '0');
        arg++;
    }
    return NUMBER;
}

int pop() {
    if (sp == 0) {
        printf("Stack already empty!!!");
        exit(1);
    }
    return stack[--sp];
}
void push(int val) {
    if (sp == 100) {
        printf("Stack already full!!!");
        exit(1);
    }
    stack[sp++] = val;
    return;
}
