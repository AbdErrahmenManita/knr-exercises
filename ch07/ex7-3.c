#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXSPECIFIER 1000
/* minprintf: minimal printf with variable argument list */
int isspecifier(int);
void *xmalloc(size_t);
int has_asterik(char *);
void minprintf(char *, ...);
void collect_buff(char **, char *, int *);
void handle_int_like(char *, int, va_list *);
void handle_unsigned_int_like(char *, int, va_list *);
void handle_floating_point(char *, int, va_list *);
void handle_strings(char *, int, va_list *);
void handle_ptr(char *, int, va_list *);

int main(void) { minprintf("%kqkq%d", 10); }

void minprintf(char *fmt, ...) {
    va_list ap;
    char *p;
    int asterik_count;
    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        p++;
        char buff[MAXSPECIFIER];
        collect_buff(&p, buff, &asterik_count);

        switch (*p) {
        case 'd':
        case 'i':
        case 'c':
            handle_int_like(buff, asterik_count, &ap);
            break;
        case 'u':
        case 'x':
        case 'X':
        case 'o':
            handle_unsigned_int_like(buff, asterik_count, &ap);
            break;
        case 'f':
        case 'g':
        case 'G':
        case 'e':
        case 'E':
            handle_floating_point(buff, asterik_count, &ap);
            break;
        case 's':
            handle_strings(buff, asterik_count, &ap);
            break;
        case 'p':
            handle_ptr(buff, asterik_count, &ap);
            break;
        default:
            printf("%s", buff);
            break;
        }
        if (*p == '\0')
            break;
    }
    va_end(ap);
}
int isspecifier(int c) {
    char target[] = {'c', 'd', 'e', 'E', 'f', 'g', 'G', 'i',
                     'o', 'p', 's', 'u', 'x', 'X', '%', '\0'};

    for (int i = 0; target[i]; i++) {
        if (target[i] == c)
            return 1;
    }
    return 0;
}

void collect_buff(char **p, char *buff, int *count) {
    char *end = buff;
    *end++ = '%';
    *count = 0;
    for (int i = 0;
         i < MAXSPECIFIER - 1 && **p != '\0' && **p != '%' && !isspecifier(**p);
         end++, (*p)++, i++) {
        if (**p == '*')
            (*count)++;
        *end = **p;
    }
    if (**p == '\0' || **p == '%') {
        *end = '\0';
        return;
    }
    *end++ = **p;
    *end = '\0';
}
void handle_int_like(char *buff, int count, va_list *ap) {
    int asterik_arg1 = 0;
    int ival;
    switch (count) {
    case 0:
        ival = va_arg(*ap, int);
        printf(buff, ival);
        break;
    case 1:
        asterik_arg1 = va_arg(*ap, int);
        ival = va_arg(*ap, int);
        printf(buff, asterik_arg1, ival);
        break;
    default:
        printf("%s", buff);
        break;
    }
}
void handle_unsigned_int_like(char *buff, int count, va_list *ap) {
    int asterik_arg1 = 0;
    unsigned int uival;
    switch (count) {
    case 0:
        uival = va_arg(*ap, unsigned int);
        printf(buff, uival);
        break;
    case 1:
        asterik_arg1 = va_arg(*ap, int);
        uival = va_arg(*ap, unsigned int);
        printf(buff, asterik_arg1, uival);
        break;
    default:
        printf("%s", buff);
        break;
    }
}

void handle_floating_point(char *buff, int count, va_list *ap) {
    int asterik_arg1 = 0;
    int asterik_arg2 = 0;
    double fval;
    switch (count) {
    case 0:
        fval = va_arg(*ap, double);
        printf(buff, fval);
        break;
    case 1:
        asterik_arg1 = va_arg(*ap, int);
        fval = va_arg(*ap, double);
        printf(buff, asterik_arg1, fval);
        break;
    case 2:
        asterik_arg1 = va_arg(*ap, int);
        asterik_arg2 = va_arg(*ap, int);
        fval = va_arg(*ap, double);
        printf(buff, asterik_arg1, asterik_arg2, fval);
        break;
    default:
        printf("%s", buff);
        break;
    }
}

void handle_strings(char *buff, int count, va_list *ap) {
    int asterik_arg1 = 0;
    int asterik_arg2 = 0;
    char *sval;
    switch (count) {
    case 0:
        sval = va_arg(*ap, char *);
        printf(buff, sval);
        break;
    case 1:
        asterik_arg1 = va_arg(*ap, int);
        sval = va_arg(*ap, char *);
        printf(buff, asterik_arg1, sval);
        break;
    case 2:
        asterik_arg1 = va_arg(*ap, int);
        asterik_arg2 = va_arg(*ap, int);
        sval = va_arg(*ap, char *);
        printf(buff, asterik_arg1, asterik_arg2, sval);
        break;
    default:
        printf("%s", buff);
        break;
    }
}
void handle_ptr(char *buff, int count, va_list *ap) {
    int asterik_arg1 = 0;
    void *ptr;
    switch (count) {
    case 0:
        ptr = va_arg(*ap, void *);
        printf(buff, ptr);
        break;
    case 1:
        asterik_arg1 = va_arg(*ap, int);
        ptr = va_arg(*ap, void *);
        printf(buff, asterik_arg1, ptr);
        break;
    default:
        printf("%s", buff);
        break;
    }
}
