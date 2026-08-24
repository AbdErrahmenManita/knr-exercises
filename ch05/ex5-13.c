#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000 // we are accepting only 1000 char per line max

int readline(char *, int);          // reads lines input line by line
void writelines(char **, int, int); // display the latest n lines
int my_atoi(char *); // transform a string into int and ensure the whole string
                     // is all digits
int main(int argc, char *argv[]) {
    int nb_lines = 10;
    char has_n = 0;
    while (--argc > 0) {

        if (has_n) {
            fprintf(stderr, "ERROR: Too much arguments!!!\n");
            exit(1);
        }
        if ((*(*++argv)) != '-') {
            fprintf(stderr, "Wrong arguments : tail -n\n");
            exit(1);
        }
        // printf("%c\n", *(*argv));
        nb_lines = my_atoi(++(*argv));
        // printf("%d\n", nb_lines);
        has_n = 1;
    }
    if (!nb_lines) {
        return 0;
    }
    char **ptrlines = malloc(nb_lines * sizeof(char *));
    int len = 0;
    char s[MAXLINE];
    int i = 0;
    int end = 0;
    char *p;
    int count = 0;
    while ((len = readline(s, MAXLINE)) != 0) {
        if (count >= nb_lines) { // this free allocated memory used before
            free(*(ptrlines + i));
        }
        p = malloc((len) * sizeof(char));
        s[len - 1] = '\0';
        strcpy(p, s);
        *(ptrlines + i) = p;
        // this count variable ensure we know if we exceeded the size so we
        // free the allocated memory before allocating another
        count++;
        // this ensures if we reach the last spot in the array
        // we move to the start of it so we fill the next if there is
        i = count % nb_lines;
        if (end != nb_lines) {
            end++;
        }
    }
    writelines(ptrlines, i, end);
    for (int j = 0; j < end; j++) {
        free(*(ptrlines + j));
    }
    free(ptrlines);
    return 0;
}

int readline(char *s, int lim) {
    int i = 0;
    int c;
    for (i = 0; i < lim - 2 && (c = getchar()) != EOF && c != '\n'; s++, i++) {
        *s = c;
    }
    if (c == '\n' || i > 0 && c == EOF || i == lim - 1) {
        // the conditions above ensure we add always a newline unless the input
        // is just EOF
        *s = c;
        i++;
        s++;
    }
    *s = '\0';
    return i;
}

int my_atoi(char *s) {
    if (strlen(s) == 0) { // empty arguemnt
        fprintf(stderr, "ERROR: Empty arguemnt!!!\n");
        exit(1);
    }
    int n = 0;
    while (*s != '\0') {
        if (!isdigit(*s)) { // argument contain non digital symbols
            fprintf(stderr, "ERROR: Argument only include digits\n");
            exit(1);
        }
        n = n * 10 + (*s - '0');
        s++;
    }
    return n;
}

void writelines(char **ptrlines, int start, int end) {
    for (int i = start; i < end; i++) { // print the values at the start of the
                                        // cycle
        printf("%s\n", *(ptrlines + i));
    }
    for (int i = 0; i < start; i++) { // print the rest of the cycle
        printf("%s\n", *(ptrlines + i));
    }
}
