#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000
size_t get_line(FILE *, char *line, int max);
void find_pattern(FILE *, const char *, const char *);

int except = 0, number = 0, found = 0;
/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[]) {
    int c;
    char *p = *++argv;
    while (--argc > 0 && *p == '-') {
        while ((c = *++p) != '\0') {
            switch (c) {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                fprintf(stderr, "find: illegal option %c\n", c);
                exit(EXIT_FAILURE);
            }
        }
        p = *++argv;
    }
    if (argc < 1) {
        fprintf(stderr, "Usage: find -x -n pattern\n");
        exit(EXIT_FAILURE);
    }
    if (argc == 1)
        find_pattern(stdin, NULL, p);
    else {
        FILE *file;
        while (--argc > 0) {
            if ((file = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "Find: Error while opening %s\n", *argv);
                exit(EXIT_FAILURE);
            }
            find_pattern(file, *argv, p);
            fclose(file);
        }
    }
    return found;
}

void find_pattern(FILE *file, const char *filename, const char *target) {
    char line[MAXLINE];
    long lineno = 0;
    while (get_line(file, line, MAXLINE) > 0) {
        lineno++;
        if ((strstr(line, target) != NULL) != except) {
            if (filename != NULL)
                printf("%s:", filename);
            if (number)
                printf("%ld:", lineno);
            printf("%s", line);
            found++;
        }
    }
}

size_t get_line(FILE *file, char *line, int lim) {
    if (fgets(line, lim, file) == NULL)
        return 0;
    return strlen(line);
}
