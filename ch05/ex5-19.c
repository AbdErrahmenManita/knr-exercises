#include <asm-generic/errno-base.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define MAXTOKEN 100
#define ERROR -2

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int gettoken(void);
void err_msg(void);
void skip_line(void);
int error = 0;
int error_printed = 0;
int tokentype;
char token[MAXTOKEN];
char datatype[MAXTOKEN];
char name[MAXTOKEN];
char out[1000];
//
//
//
//
//
// //
// void dcl(void) {
//     int ns;
//     int c; // holder
//     for (ns = 0; (c = gettoken()) == '*';) {
//         ns++;
//     }
//     if (error) {
//         return;
//     }
//     dirdcl();
//     if (error) {
//         return;
//     }
//     while (ns-- > 0)
//         strcat(out, " pointer to");
// }

//
//
//
//
//
//
//
// //
// void dirdcl(void) {
//     int type;
//
//     if (tokentype == '(') {
//         dcl();
//         if (tokentype != ')') {
//             fprintf(stderr, "error: missing )\n");
//             error = 1;
//             error_printed = 1;
//             return;
//         }
//     } else if (tokentype == NAME) {
//         strcpy(name, token);
//     } else {
//         fprintf(stderr, "ERROR: expected name or (dcl)\n");
//         error = 1;
//         error_printed = 1;
//         return;
//     }
//     while ((type = gettoken()) == PARENS || type == BRACKETS) {
//         if (type == PARENS)
//             strcat(out, " function returning");
//         else {
//             strcat(out, " array");
//             strcat(out, token);
//             strcat(out, " of");
//         }
//     }
// }
////
///
///
///
///
///
///
///
///
///
///
///
int main(void) {
    int type;
    char temp[MAXTOKEN];
    int prev;
    while (gettoken() != EOF) {
        prev = 0;
        strcpy(out, token);
        while ((type = gettoken()) != '\n' && type != EOF) {
            // printf("%s\n", token);
            if (type == PARENS || type == BRACKETS) {
                if (prev == '*') {
                    sprintf(temp, "(%s)", out);
                    strcpy(out, temp);
                    prev = 0;
                }
                strcat(out, token);
            } else if (type == '*') {
                sprintf(temp, "*%s", out);
                strcpy(out, temp);
                prev = '*';
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else {
                printf("invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
    }
    return 0;
}
//
//
//
//
//
//
//
//
//
//
//
//
int gettoken(void) {
    int c, getch(void);
    void ungetch(int);
    char *p = token;
    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = (char)c; isdigit(c = getch()) || c == ' ' || c == '\t';) {
            if (!isspace(c)) {
                *p = (char)c;
                p++;
            }
        }
        if (c != ']') {
            fprintf(stderr, "ERROR: missing ]\n");
            error = 1;
            error_printed = 1;
            return tokentype = ERROR;
        }
        *p = (char)c;
        p++;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c) || c == '_') {
        for (*p++ = (char)c; isalnum(c = getch()) || c == '_';) {
            *p++ = (char)c;
        }
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}

//
//
//
//
//
//
//
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;
int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }
void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("Ungetch : Too many arguments\n");
    } else {
        buf[bufp++] = (char)c;
    }
}

//
//
//
//
//
//
void err_msg(void) { fprintf(stderr, "ERROR: Misplaced %c <<<", tokentype); }
//
//
//
//
//
//
void skip_line(void) {
    tokentype = 0;
    token[0] = '\0';
    datatype[0] = '\0';
    name[0] = '\0';
    out[0] = '\0';

    int c;
    while ((c = getch()) != '\n' && c != EOF && c != ';')
        ;
    if (c == EOF) {
        ungetch(c);
    }
}
