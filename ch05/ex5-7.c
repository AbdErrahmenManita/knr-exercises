#include <stdio.h>
#include <string.h>
#define MAXLINES 5000
#define MAXLEN 1000
#define MAXSTORE MAXLINES *MAXLEN
char *lineptr[MAXLINES];
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void my_qsort(char **, int, int);
int main(void) {
    int nlines;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        my_qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
    }
    return 0;
}

char storelines[MAXSTORE];
int current_size = 0;
int my_getline(char *, int);
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char line[MAXLEN];
    nlines = 0;
    while ((len = my_getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || current_size + len > MAXSTORE - 1) {
            return -1;
        } else {
            line[len - 1] = '\0';
            strcpy(storelines + current_size, line);
            lineptr[nlines++] = storelines + current_size;
            current_size += len + 1;
        }
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}

/* qsort: sort v[left]...v[right] into increasing order */
void my_qsort(char *v[], int left, int right) {
    int i, last;
    void swap(char *v[], int i, int j);
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    my_qsort(v, left, last - 1);
    my_qsort(v, last + 1, right);
}
void swap(char *v[], int i, int j) {
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int my_getline(char *s, int lim) {
    int i, c;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; s++, i++) {
        *s = (char)c;
    }
    if (c == '\n') {
        *s = (char)c;
        s++;
        i++;
    }
    *s = '\0';
    return i;
}
