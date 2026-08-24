#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINES 5000
#define MAXLEN 1000
char *lineptr[MAXLINES];
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void my_qsort(void *lineptr[], int left, int right,
              int (*comp)(void *, void *, int *), int *flags);
int numcmp(const char *, const char *);
int mastercmp(const char *, const char *, int *);
void getflags(int, char **, int *);
int main(int argc, char *argv[]) {
    int nlines;
    int flags[4] = {0};
    getflags(argc - 1, ++argv, flags);
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        my_qsort((void **)lineptr, 0, nlines - 1,
                 (int (*)(void *, void *, int *))mastercmp, flags);
        writelines(lineptr, nlines);

    } else {
        fprintf(stderr, "Too Much input !!!\n");
        exit(1);
    }
    return 0;
}

// sort algorithm for any data type
void my_qsort(void *v[], int left, int right,
              int (*comp)(void *, void *, int *), int *flags) {
    int i, last;
    void swap(void *v[], int, int);
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if ((*comp)(v[i], v[left], flags) < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    my_qsort(v, left, last - 1, comp, flags);
    my_qsort(v, last + 1, right, comp, flags);
}

int super_cmp(char *s, char *t, int *flags) {
    unsigned char *s1 = (unsigned char *)s;
    unsigned char *t1 = (unsigned char *)t;
    while (*s1 != '\0' || *t1 != '\0') {
        if (flags[3]) {
            while (*s1 != '\0' && !isalpha(*s1) && !isdigit(*s1) &&
                   !isspace(*s1)) {
                s1++;
            }
            while (*t1 != '\0' && !isalpha(*t1) && !isdigit(*t1) &&
                   !isspace(*t1)) {
                t1++;
            }
        }
        if (flags[2]) {
            if (tolower(*s1) != tolower(*t1)) {
                return (int)tolower(*s1) - tolower(*t1);
            }

        } else {
            if (*s1 != *t1) {
                return (int)(*s1 - *t1);
            }
        }
        if (*s1 != '\0') {
            s1++;
            t1++;
        }
    }
    return 0;
}

// this got replaced by the supercmp that handles them all in one

// int fold_strcmp(const char *s, const char *t) {
//      unsigned char *s1 = (unsigned char *)s;
//      unsigned char *t1 = (unsigned char *)t;
//      while (*s1 != '\0' || *t1 != '\0') {
//          if (tolower(*s1) != tolower(*t1)) {
//              return (int)tolower(*s1) - tolower(*t1);
//          }
//          s1++;
//          t1++;
//      }
//      return 0;
// }

// decidor of the comparaison nature
int mastercmp(const char *s, const char *t, int *flags) {
    if (flags[0]) {
        return flags[1] * numcmp(s, t);

    } else {
        return flags[1] * super_cmp((char *)s, (char *)t, flags);
    }
}
// compare numeric value
int numcmp(const char *s, const char *t) {
    double v1, v2;
    v1 = atof(s);
    v2 = atof(t);
    if (v1 < v2) {
        return -1;

    } else if (v1 > v2) {
        return 1;

    } else {
        return 0;
    }
}

// swap two values
void swap(void *v[], int i, int j) {
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// get one line of input
int my_getline(char *s, int lim) {
    int c, i;
    for (i = 0; i < lim - 2 && (c = getchar()) != EOF && c != '\n'; i++, s++) {
        *s = c;
    }
    if (c == '\n' || i > 0 && c == EOF || i == lim - 2) {
        *s = '\n';
        i++;
        s++;
    }
    *s = '\0';
    return i;
}

// fill the table of strings
int readlines(char *lineptr[], int maxlines) {
    int nlines, len;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = my_getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = malloc(len * sizeof(char))) == NULL) {
            return -1;

        } else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

// print the whole array
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}

void getflags(int nb_arg, char **arg, int *flags) {
    int numeric = 0;
    int reverse = 1;
    int fold = 0;
    int directory_order = 0;
    int c;
    while (nb_arg > 0 && (*arg)[0] == '-') {
        while ((c = *++arg[0]) != '\0') {
            switch (c) {
            case 'n':
                if (numeric) {
                    fprintf(stderr, "Repeated the n argument\n");
                    exit(1);
                }
                numeric = 1;
                break;
            case 'r':
                if (reverse == -1) {
                    fprintf(stderr, "Repeated the r argument\n");
                    exit(1);
                }
                reverse = -1;
                break;
            case 'f':
                if (fold) {
                    fprintf(stderr, "Repeated the f argument\n");
                    exit(1);
                }
                fold = 1;
                break;
            case 'd':
                if (directory_order) {
                    fprintf(stderr, "Repeated the d argument\n");
                    exit(1);
                }
                directory_order = 1;
                break;
            default:
                fprintf(stderr, "Wrong or Unsupposrted argument\n");
                exit(1);
            }
        }
        arg++;
        nb_arg--;
    }
    if (nb_arg != 0) {
        fprintf(stderr, "Wrong argument : Usage function -n -r\n");
        exit(1);
    }
    flags[0] = numeric;
    flags[1] = reverse;
    flags[2] = fold;
    flags[3] = directory_order;
}
